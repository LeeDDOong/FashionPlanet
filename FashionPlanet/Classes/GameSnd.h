#ifndef __GAME_SND_H__
#define __GAME_SND_H__


#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define SOUND_TYPE		"Yamaha_MA3"

#define BGM_TRACK		20

//bgm
#define SND_WORLDMAP_BG0		0		
#define SND_WORLDMAP_BG1		4
#define SND_WORLDMAP_BG2		5
#define SND_WORLDMAP_BG3		6
#define SND_WORLDMAP_BG4		7
#define SND_WORLDMAP_BG5		8
#define SND_WORLDMAP_BG6		9
#define SND_WORLDMAP_BG7		10
#define SND_WORLDMAP_BG8		11
#define SND_WORLDMAP_BG9		12


#define SND_CLUB		13







#define SND_FASHIONSHOWMENU_BG	1		//패션쇼메뉴
#define SND_FASHIONSHOWGAME_BG	2		//패션쇼게임중
#define SND_SCENARIO_BG	3		//시나리오


//eff
#define SND_PRODUCTION_HANGERMAKEING		20
#define SND_PRODUCTION_ACCESSORYMAKEING		21


#define SND_FASHION					22

#define SND_SELLTABLE_INPUT			23


#define SND_INTERIOR_BUILD			24
#define SND_INTERIOR_INPUT			25
#define SND_INTERIOR_SELL			26
#define SND_CAR						27

#define SND_GOLD					28
#define SND_EXP						29
#define SND_FAME					30

#define SND_MENU_OK					31
#define SND_POPUP_SHOW				32

#define SND_LVUP_POPUP				33
#define SND_QUEST_RESULT			34
#define SND_TREND_POPUP				35

#define SND_FRIEND_HELP				36
#define SND_MINIGAME_INPUTCANDY		37
#define SND_MINIGAME_START			38
#define SND_MINIGAME_RESULT			39


#define SND_MODEL_CASTING			40
#define SND_MODEL_RESULT			41
#define SND_MODEL_UPGRADE			42


#define SND_NPC_ACTION0				42
#define SND_NPC_ACTION1				43
#define SND_NPC_ACTION2				44

#define SND_CARBBANGBBANG			45
#define SND_HELPINFO				46
#define SND_FITTING					47
#define SND_APPLAUD					48
#define SND_DSLR					49
#define SND_WALL					50
#define SND_JEWEL					51



#define SND_PANG0           52
#define SND_PANG1           53
#define SND_PANG2           54
#define SND_PANG3           55




typedef struct
{
	M_Int32 nVolLevel;		
	M_Boolean isPlay;
	M_Boolean isLoop;
	M_Int32 nTrack;
	M_Int32 bgTrack;
	M_Int32 effTrack;
	
	M_Int64 repeatTime;
	M_Int64 repeatTime2;

	M_Int32 size;
	M_Int32 id;
    int checkFlowTime;

    
	char strBgmName[128];
    char strEffName[128];
} XMEDIA;


extern XMEDIA xmedia;
extern M_Int32 isGetVol;

void checkSound(void);
void playSnd(M_Int32 track);
void stopSnd(void);

#endif


