#include "global.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	unsigned long int nowTime;

	LoadAndSet();

	oldTime = GetNowCount();

	while (ProcessMessage() == 0 && !endflag) {

		GetDateTime(&time);

		Event();

		Mouse();

		DrawGraph(graphX, graphY, graphand, TRUE);
		DrawGraph(frameX, frameY, framehand, TRUE);

		if (option) {


			DrawGraph(topX[topflag], topY[topflag], tophand[topflag], TRUE);
			DrawGraph(endX, endY, endhand, TRUE);
		}else {

			DrawFormatStringToHandle(hourminX, hourminY, hourminCol, fontHhm, "%02d:%02d", time.Hour, time.Min);
			DrawFormatStringToHandle(secX, secY, secCol, fontHsec, "%02d", time.Sec);
		}

		nowTime = GetNowCount() - oldTime;
		if (nowTime < looptime) WaitTimer(looptime - nowTime);
		oldTime = GetNowCount();

		ScreenFlip();
		ClearDrawScreen();

	}

	DxLib_End();

	return 0;
}

void Mouse() {
	int mX, mY, mp;

	mp = GetMouseInput();

	switch (mp) {


	case MOUSE_INPUT_RIGHT:
		if (oldmp != mp) {
			option = option == false;
		}
		break;

	case MOUSE_INPUT_LEFT:
	case MOUSE_INPUT_LEFT + MOUSE_INPUT_RIGHT:

		GetMousePoint(&mX, &mY);

		if (option && oldmp != mp) {
			if (mX >= topX[topflag] && mX <= topX[topflag] + topSzX[topflag] && mY >= topY[topflag] && mY <= topY[topflag] + topSzY[topflag]) {
				if (topflag == 0) {

					topflag = 1;
					SetWindowPos(winhand, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW));
				}else {

					topflag = 0;
					SetWindowPos(winhand, HWND_NOTOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW));
				}
			}else if (mX >= endX && mX <= endX + endSzX && mY >= endY && mY <= endY + endSzY) {
				
				endflag = true;
				PlaySoundFile(endsoundPass.c_str(), DX_PLAYTYPE_NORMAL);
			}
		}

		if (oldmX == 0) {

			oldmX = mX;
			oldmY = mY;
		}else {
		
			winposX += mX - oldmX;
			winposY += mY - oldmY;
		}
		SetWindowPosition(winposX, winposY);
		break;

	default:
		oldmX = 0;
		break;
	}
	oldmp = mp;

}


void LoadAndSet() {
	
	int			tempn[32], i;
	string		str, s,
				temp[12];
	ifstream	ifs(SETFILEPASS);

	getline(ifs, str);
	getline(ifs, str);

	for (i = 0; i < 12; i++) {
		
		getline(ifs, str);
		stringstream s1(str);

		getline(s1, s, '=');
		getline(s1, s, '=');

		temp[i] = s;
	}

	getline(ifs, str);

	for (i = 0; i < 33; i++) {

		getline(ifs, str);
		stringstream s2(str);

		getline(s2, s, '=');
		getline(s2, s, '=');

		tempn[i] = atoi(s.c_str());
	}


	SetOutApplicationLogValidFlag(LOGFLAG);
	ChangeWindowMode(TRUE);
	SetMainWindowText(temp[APPLINAMENUM].c_str());
	SetWindowStyleMode(2);
	SetUseBackBufferTransColorFlag(TRUE);

	DxLib_Init();

	SetGraphMode(tempn[SIZEXNUM], tempn[SIZEXNUM+1], 16);

	winhand = GetMainWindowHandle();
	SetWindowPos(winhand, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW));
	SetAlwaysRunFlag(ALRUNFLAG);

	SetWindowPosition(0, 0);
	SetBackgroundColor(tempn[BKCOLORNUM], tempn[BKCOLORNUM +1], tempn[BKCOLORNUM +2]);
	SetTransColor(tempn[BKCOLORNUM], tempn[BKCOLORNUM +1], tempn[BKCOLORNUM +2]);

	SetDrawScreen(DX_SCREEN_BACK);

	AddFontResourceEx(temp[FONTPASSNUM].c_str(), FR_PRIVATE, NULL);

	fontHhm		   = CreateFontToHandle(temp[FONTPASSNUM -1].c_str(), tempn[SIZEFONTNUM], -1, DX_FONTTYPE_NORMAL);
	fontHsec	   = CreateFontToHandle(temp[FONTPASSNUM -1].c_str(), tempn[SIZEFONTNUM +1], -1, DX_FONTTYPE_NORMAL);
	hourminCol     = GetColor(tempn[HOURMINCOLNUM], tempn[HOURMINCOLNUM +1], tempn[HOURMINCOLNUM +2]);
	secCol		   = GetColor(tempn[HOURMINCOLNUM +3], tempn[HOURMINCOLNUM +4], tempn[HOURMINCOLNUM +5]);
	graphPass      = temp[GRAPHNUM];
	graphMax	   = tempn[CHARMANYNUM];
	graphand	   = LoadGraph(randf(graphPass.c_str(), graphFE, GetRand(graphMax)));
	framehand	   = LoadGraph(temp[FRAMENUM].c_str());
	tophand[1]	   = LoadGraph(temp[TOPNUM].c_str());
	tophand[0]     = LoadGraph(temp[TOPNUM +1].c_str());
	endhand		   = LoadGraph(temp[ENDNUM].c_str());
	GetGraphSize(tophand[1], &topSzX[1], &topSzY[1]);
	GetGraphSize(tophand[0], &topSzX[0], &topSzY[0]);
	GetGraphSize(endhand, &endSzX, &endSzY);

	endsoundPass   = temp[BOOTNUM +1];
	timesoundPass  = temp[TIMENUM];
	htimesoundPass = temp[TIMENUM + 1];

	graphX   = tempn[GRAPHPOSNUM];
	graphY   = tempn[GRAPHPOSNUM +1];
	frameX   = tempn[FRAMEPOSNUM];
	frameY   = tempn[FRAMEPOSNUM +1];
	hourminX = tempn[TIMEPOSNUM];
	hourminY = tempn[TIMEPOSNUM +1];
	secX	 = tempn[TIMEPOSNUM +2];
	secY	 = tempn[TIMEPOSNUM +3];
	topX[1]  = tempn[TOPPOSNUM];
	topY[1]  = tempn[TOPPOSNUM +1];
	topX[0]  = tempn[TOPPOSNUM +2];
	topY[0]  = tempn[TOPPOSNUM +3];
	endX     = tempn[ENDPOSNUM];
	endY     = tempn[ENDPOSNUM +1];

	looptime = tempn[LOOPTIMENUM];
	hindo	 = tempn[LOOPTIMENUM +1];

	PlaySoundFile(temp[BOOTNUM].c_str(), DX_PLAYTYPE_BACK);
}

void Event() {
	if (time.Sec == 0) {
		if (time.Min == 0) {

			PlaySoundFile(randf(timesoundPass.c_str(), soundFE, time.Min), DX_PLAYTYPE_BACK);
		}else if (time.Min == 30) {

			PlaySoundFile(randf(timesoundPass.c_str(), soundFE, time.Min), DX_PLAYTYPE_BACK);
			PlaySoundFile(htimesoundPass.c_str(), DX_PLAYTYPE_BACK);
		}
	}
	if (GetNowCount() % looptime == GetRand(looptime + hindo)) {
		graphand = LoadGraph(randf(graphPass.c_str(), graphFE, GetRand(graphMax)));
	}
}

inline char* randf(const char *pass, const char *extension, int number) {
	char cStr[50];

	sprintf(cStr, "%s%d%s", pass, number, extension);

	return cStr;
}