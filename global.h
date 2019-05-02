#pragma once

//2017.4.3~6
//デスクトップマスコット

#include "DxLib.h"
#include "fstream"
#include "sstream"
#include "string"

#define  LOGFLAG		false
#define  ALRUNFLAG		true
#define  APPLINAME		"デスクトップマスコット"
#define  SETFILEPASS	"設定.ini"
#define  GRAPHNUM		0
#define  FRAMENUM		1
#define  TOPNUM			2
#define  ENDNUM			4
#define  BOOTNUM		7
#define  TIMENUM		9
#define  HOURMINCOLNUM	0
#define  FONTPASSNUM	6
#define  APPLINAMENUM	11

#define  SIZEXNUM		10
#define  SIZEFONTNUM	12
#define  BKCOLORNUM		6
#define  GRAPHPOSNUM	15
#define  FRAMEPOSNUM	17
#define  TIMEPOSNUM		19
#define  TOPPOSNUM		23
#define  ENDPOSNUM		27
#define  CHARMANYNUM	30
#define  LOOPTIMENUM	31


using namespace std;

const char	*graphFE = ".png",
			*soundFE = ".wav";

bool	option = false,
		endflag = false;
int		fontHhm,	 fontHsec,
		hourminCol,  secCol,
		graphand,	 framehand,
		tophand[2],  endhand,
		graphX,		 graphY,
		frameX,		 frameY,
		hourminX,	 hourminY,
		secX,		 secY,
		topX[2],	 topY[2],
		endX,		 endY,
		graphMax,	 hindo,
		topflag = 1,
		oldmX,		 oldmY,
		oldmp = 0,
		topSzX[2],	 topSzY[2],
		endSzX,		 endSzY,
		winposX = 0, winposY = 0;
unsigned int looptime;
unsigned long int oldTime;

string		graphPass,
			endsoundPass,
			timesoundPass, htimesoundPass;
HWND		winhand;
DATEDATA	time;

void Event();
void Mouse();
void LoadAndSet();
inline char* randf(const char *pass, const char *extension, int number);