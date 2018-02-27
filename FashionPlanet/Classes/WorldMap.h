#ifndef WORLDMAP_
#define WORLDMAP_




#define FLOORTILEINITCODE		9000
#define WALLTILEINITCODE		10000

//여자
#define STAFF0_HAIRCODE			0
#define STAFF0_FACECODE			0
#define STAFF0_FASHIONCODE0		1011
#define STAFF0_FASHIONCODE1		2013
#define STAFF0_FASHIONCODE2		DONT
#define STAFF0_FASHIONCODE3		4022

//남자
#define STAFF1_HAIRCODE			1
#define STAFF1_FACECODE			14
#define STAFF1_FASHIONCODE0		1017
#define STAFF1_FASHIONCODE1		2019
#define STAFF1_FASHIONCODE2		DONT
#define STAFF1_FASHIONCODE3		4031


#define FLOORMAX				3
#define LVUPDATAMAX					100
#define LVMAX					60


#define MYSHOPREFRESHCNTMAX 299

typedef struct
{
	int item_index[16];
	int item_count[16];
	int item_category[16];
	int totalNum;
	int sleepCount;
	M_Int64 time;
	M_Boolean isSleep;
}XAUTOPRODUCT;
extern XAUTOPRODUCT xAutoProduct;

#define ROCKET_STATE_WAIT	0
#define ROCKET_STATE_MOVE	1
#define ROCKET_STATE_BACK	2

typedef struct{
	int x;
	int y;
	int rot;
	int scale;
	int alpha;
	M_Boolean isPlay;
}XEFFROCKET;

typedef struct
{
	/////////////////////////
	//LJW 로켓 연출용
	int state;
	int frame;
	XEFFROCKET xFire;//불꽃
	XEFFROCKET xSmoke[4];//연기4개
	XEFFROCKET xRocket;//로켓
	/////////////////////////
	
	int item_index[16];
	int item_count[16];
	int item_category[16];
	int totalNum;
	M_Int64 time;
	M_Boolean isSleep;
	int gold;
}XAUTOSELL;
extern XAUTOSELL xAutoSell;


typedef struct
{
	float BaseDressScore;//(의상기본점수)
	float GoldDressScore;//(골드의상점수산출)
	float CashDressScore;//(캐쉬의상점수산출)
	float TrendBonus;//(유행보너스)
	float ConceptBonus;//(컨셉보너스)
	float ColorBonus;//(색상보너스)
	float SexBonus;//(성별보너스)
	float TuckBonus;//(턱인턱아웃보너스)
	float LayeredBonus;//(레이어드횟수보너스)
	
	float LuckyMin;//(행운점수min)
	float LuckyMax;//(행운점수max)
	
		
	float Model[5];
	float Upgrade[10];//(1단계업그레이드)
} XBALANCE;
extern XBALANCE xBalance;


typedef struct
{
	int fameMax[LVUPDATAMAX];
	SECURITY expMax[LVUPDATAMAX];
	int buildHangerMax[FLOORMAX][LVUPDATAMAX];
	int buildAccecssoryMax[FLOORMAX][LVUPDATAMAX];
	int buildFittingRoomMax[FLOORMAX][LVUPDATAMAX];
	int buildShowwindowMax[FLOORMAX][LVUPDATAMAX];
		
	
	int trend1Per[LVUPDATAMAX];
	int trend11Per[LVUPDATAMAX];
	int trend21Per[LVUPDATAMAX];
	int trend31Per[LVUPDATAMAX];
	int trend41Per[LVUPDATAMAX];
	
} XBALANCEDATA;
extern XBALANCEDATA xBalanceData;


#define F_TYPE_OUTER		0
#define F_TYPE_TOP			1
#define F_TYPE_BOTTOM		2
#define F_TYPE_ONEPIECE		3
#define F_TYPE_SHOES		4
#define F_TYPE_BAG			5
#define F_TYPE_ACCECSSORY	6

typedef struct
{
	M_Boolean isInFitting;
	M_Boolean isHighHeeled;
	int layeredNum;
	int code[SPRIT_IMGLAYERMAX];
} XFITTINGLAYER;



///////////////////////반짝이이펙트/////////////////////

#define GLITTEREFFMAXSUB			10


#define GLITTEREFF_STATE_DONT		0
#define GLITTEREFF_STATE_PLAY		1
typedef struct
{
	M_Int32 state;
	M_Int32 anyCnt;
	M_Int32 type;
	float x;
	float y;
	
	float rx;
	float ry;
	
	float resizeMax;
	
} XGLITTEREFF;










////////////////////인테리어 슬롯
#define CODETEAMMAX		4
typedef struct
{

	M_Int32 totalTeam;
	char strTeamName[128];
	M_Int32 codeTeam[CODETEAMMAX];
	
	M_Int32 num;
	M_Boolean isNew;
	M_Boolean isHot;
	M_Boolean isEvent;
	M_Int32 sale;
} XINTERIORSLOT;

typedef struct
{
	M_Int32 code;
	M_Int32 num;
	M_Boolean isInfoOpen;
	M_Boolean isSelectV;
	
	M_Boolean isModelUse;
	
	M_Boolean isNew;
	M_Boolean isHot;
	M_Boolean isEvent;
	
} XCATALOGSLOT;




typedef struct
{
	M_Int32 waitSlot;
	M_Int32 code;
	M_Int32 maxNum;
	M_Int32 num;
	M_Int64 flowTime;
	M_Boolean isInfoOpen;
	M_Int32 useCook;
	
	
	M_Boolean isProduction;
	int productionSelectType;
	int productionSelectSlot;
} XSELLSLOT;

////////////////////////////

///////////////////////////////////////////////////인테리어 인벤
#define XINVENTORYINTERIORMAX			30000
typedef struct
{
	M_Int32 totalNum;
	M_Int16 itemCode[XINVENTORYINTERIORMAX];
	 
} XINVENTORYINTERIOR;
extern XINVENTORYINTERIOR xInventoryInterior;


////////////////////청소
#define SOCIALSLOTMAX	128
typedef struct
{
	int cleanKey;
	int interiorKey;
	int friendDataSlotNum;
} XSOCIALSLOT;
////////////////////////////





////////////////////////////////////////////////카탈로그관련 인벤
#define FASHIONDATATYPEMAX		7
#define FASHIONDATAMAX			512
#define FASHIONDATALAYERMAX		19


typedef struct
{
	M_Boolean isOpen[FASHIONDATATYPEMAX][FASHIONDATAMAX];
	M_Int32 haveNum[FASHIONDATATYPEMAX][FASHIONDATAMAX];
} XINVENTORYFASHION;
extern XINVENTORYFASHION xInventoryFashion;
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
#define SHOPTITLEMAX		50

#define PUSHONOFF_PRODUCTION	0
#define PUSHONOFF_SELLTABLE		1
#define PUSHONOFF_ORDER			2
#define PUSHONOFF_MAIL			3
typedef struct
{
	M_Boolean isKakaoLogin;
	
	char strId[64];
	char strIdGuest[64];
	M_Int32 resVer;
	M_Int32 noticeDay;
	M_Int32 socialDay;
	M_Int32 runwayDay;
	
	M_Boolean is4inch;
	
	int totalProductionRecord;
	int productionRecord[32];
	
	///////옵션/////
	int bgmVol;
	int effVol;
    
    int tempVol;
    
    
	M_Boolean isPushOnOff[10];
	
	M_Int8 fashionNew[10][300];		//0아무상태아님 1new상태 2확인상태 3완료상태
	
	M_Int32 orderNew[256];
	
	M_Int32 mailLastKey;
	M_Int32 giftLastKey;

		
	M_Int32 socialCntHanger;
	M_Int32 socialCntAccessory;
	
	M_Boolean isKakaoPhoto;
	int kakaoPhotoState;
    
	///temp사용///
	//char temp[1024];
	M_Int32 noticeDayPopup[10];	//1024-40 = 984
    
    int hotTimeShowDay;
    
    int reviewState;
    
	char temp[976];
	
	M_Int64 autoSellTime;
	M_Int64 autoProductTime;
	
} XSAVE;
extern XSAVE xSave;





#define SAVE_KAKAOINVITEMAX		1024
typedef struct
{
	int totalInvite;
	M_Boolean isDel[SAVE_KAKAOINVITEMAX];
	char strInviteId[SAVE_KAKAOINVITEMAX][32];
	char strNickName[SAVE_KAKAOINVITEMAX][64];
} XSAVEKAKAO;
extern XSAVEKAKAO xSaveKakao;
extern XSAVEKAKAO xSaveKakaoApp;



#define SAVE_KAKAOHELPMAX		512
typedef struct
{
	int totalNum;
	char strHelpId[SAVE_KAKAOHELPMAX][32];
	int helpDay[SAVE_KAKAOHELPMAX];
} XSAVEKAKAOHELP;
extern XSAVEKAKAOHELP xSaveKakaoHelp;




#define SAVE_NOTICEPOPUP            64
typedef struct
{
    int day;
    int totalNum;
    int code[SAVE_NOTICEPOPUP];
} XSAVENOTICEPOPUP;
extern XSAVENOTICEPOPUP xSaveNoticePopup;


/////////////////////////////////////////////
//내 캐릭터 LJW 2018.02.12
#define MYCHARACTER_STATE_WAIT	0
#define MYCHARACTER_STATE_MOVE	1

typedef struct{
	int state;
	int actingType;
	int moveType;
	int floorTarget;
	int floor;
	int x;
	int y;
	int actLook;
	int speed;
	int drawX;
	int drawY;
	int makeX;
	int makeY;
	int gender;
	int bestX[128];
	int bestY[128];
	int bestTotalCnt;
	int bestNowCnt;
	int nowDelay;
	int nowFrame;
	char strName[64];
	XFACE xFace;
	XFITTINGLAYER xF;
	M_Boolean isActEnd;
}XMYCHARACTER;
extern XMYCHARACTER xMyCharacter;
/////////////////////////////////////////////

typedef struct
{
//////////////////서버저장용///////////////////
	SECURITY money;
	SECURITY cash;
	SECURITY fame;	
	SECURITY exp;	
	SECURITY lv;
	SECURITY tired;
    SECURITY mileage;
    SECURITY carrot;
    
		
	M_Int64 tiredTime;

	char profileUrl[128];
	char strNickName[64];
		
	M_Int32 trendAmDay;
	M_Int32 trendPmDay;
	
	M_Int32 orderAmDay;
	M_Int32 orderPmDay;
/////////////////////////////////////////////
	
	
		
	M_Int32 makeNum;
	M_Int32 makeCashNum;
	M_Int32 buyCashInteriorNum;
	M_Int32 buyCashStaffNum;
	M_Boolean isModelMiniGame;
	M_Int32 sellTrendNum;
	M_Int32 sellFittingNum;
	
	M_Int32 friendOrderNum;
	
	M_Int32 sex;
	M_Int32 age;
	
	M_Int32 friendNum;
	int area;
	
	M_Int32 socialDay;
	M_Int32 socialItem[2];
	
	M_Int32 socialHelpCnt;
	M_Int32 socialModelVoteCnt;
		
} XSAVETEMP;
extern XSAVETEMP xSaveTemp;



#define WORLDMAP_STATE_PLAY				0		//걍 플레이
#define WORLDMAP_STATE_INTERIORSHOP		1		//인테리어 상점
#define WORLDMAP_STATE_INTERIOR			2		//가구 배치 모드
#define WORLDMAP_STATE_SEVERSELL		3		//서버판매
#define WORLDMAP_STATE_SELL				4		//판매
#define WORLDMAP_STATE_FITTING			5		//피팅
#define WORLDMAP_STATE_STAFF			6		//스태프꾸미기
#define WORLDMAP_STATE_MINIGAME			7		//캔디머신


#define WORLDMAP_STATE_NOTICE			10		//공지사항
#define WORLDMAP_STATE_PROFILE			11		//프로필
#define WORLDMAP_STATE_PROFILEPRC		12		//그냥 키막기용


#define WORLDMAP_STATE_CARSTORAGE		14		//자동차변경
#define WORLDMAP_STATE_CARORDERINFO		15		//인포
#define WORLDMAP_STATE_FRIENDLIST		17		//친구샵

#define WORLDMAP_STATE_FRIENDORDER			18		//친구샵 주문
#define WORLDMAP_STATE_FRIENDORDERITEM		19		//친구샵 주문
#define WORLDMAP_STATE_MAIL					20		//방명록
#define WORLDMAP_STATE_QUESTINFO			21		//퀘스트
#define WORLDMAP_STATE_STAFFMAKE			22		//스태프생성
#define WORLDMAP_STATE_MODEL				23		//모델





#define WORLDMAP_STATE_FASHIONSHOWNEW		25		//패션쇼
#define WORLDMAP_STATE_MODEL_FRIEND			26		//친구 모델 리스트



#define WORLDMAP_STATE_ORDERRECVINFO			28		//주문배송보상




#define WORLDMAP_STATE_PRODUCTIONMENU				31	//새로운 생산



#define WORLDMAP_STATE_OPTION					34		//옵션

#define WORLDMAP_STATE_CARPARKSELECTMODE_PRODUCTIOHN			35	//차량선택

#define WORLDMAP_STATE_CARPARKSELECTMODE_CAR				36	//차량변경선택


#define WORLDMAP_STATE_ACCESSBONUS				37

#define WORLDMAP_STATE_MODELMAINGIFTINFO				38

#define WORLDMAP_STATE_TODAYSOCIAL				39
#define WORLDMAP_STATE_TODAYRUNWAY				40
#define WORLDMAP_STATE_SALESHOP					41



#define WORLDMAP_STATE_NOTICEPOPUP				42		//공지사항팝업형태
#define WORLDMAP_STATE_COLLECTION					43

#define WORLDMAP_STATE_MILEAGESHOP					44




#define WORLDMAP_STATE_ACCESSBONUSSHOW				45


#define WORLDMAP_STATE_PREPAY                       46
#define WORLDMAP_STATE_PREPAYDAY                    47

#define WORLDMAP_STATE_EVENTQUEST                    48



#define WORLDMAP_STATE_HOTDEAL                      49


#define WORLDMAP_STATE_RIVALWORLDMAP                      50
#define WORLDMAP_STATE_RIVAL                      51
#define WORLDMAP_STATE_RIVALINFO                      52

#define WORLDMAP_STATE_HELPLIST                      53

#define WORLDMAP_STATE_JEWELQUEST                      54


#define WORLDMAP_STATE_JEWELRESULT                      55

#define WORLDMAP_STATE_PANG                      56

#define WORLDMAP_STATE_CLUBLIST                      57
#define WORLDMAP_STATE_CLUBLOBBY                      58


#define WORLDMAP_STATE_CANDYFORMER                  59//캔디 제작기
#define WORLDMAP_STATE_LULUPANG						60
/////////////////////////////////////////////////////////////////
//월드맵의 상태 KBY
#define WORLDMAP_STATE_FITTING_FP                   61
#define WORLDMAP_STATE_SENDMACHINE_FP				WORLDMAP_STATE_FITTING_FP+1
#define WORLDMAP_STATE_GREENHOUSE_FP                WORLDMAP_STATE_SENDMACHINE_FP+1
#define WORLDMAP_STATE_SPINNINGWHEEL_FP             WORLDMAP_STATE_GREENHOUSE_FP+1
#define WORLDMAP_STATE_SHOP_FP                         WORLDMAP_STATE_SPINNINGWHEEL_FP+1


#define NEWMODELANYCNTMAX			100




#define INSHOPPER_TYPE_START			0
#define INSHOPPER_TYPE_SELLTABLE		1
#define INSHOPPER_TYPE_FAME				2
#define INSHOPPER_TYPE_SHOWWINDOW		3
#define INSHOPPER_TYPE_MODEL			4
#define INSHOPPER_TYPE_TREND			5


#define INSHOPPER_TYPE_STAFF			8


#define INSHOPPERMAX		9

typedef struct
{
	
	M_Boolean isAliceShockOpen;
	M_Boolean isAliceShock;
	M_Boolean isAliceShockResult;
	M_Boolean isAliceShockResultKeyReturn;
	
	
	
	
	
	
	M_Boolean isKeyReturn;
	M_Boolean isExternal;
	
	M_Boolean isCashShop;
	M_Boolean isTrend;
	M_Boolean isLvUp;
	M_Boolean isMiniProfile;
	M_Boolean isCashGift;
	M_Boolean isSocialProfile;
	
	int trendInType;

	
	
	M_Int32 state;
	M_Int32 anyCnt;
	
	M_Int32 people;
	M_Int32 worldMapNpcMax;
	M_Int32 worldMapNpcNow;
	M_Int32 shopNpcNow;
	
    int npcMakeFlowTime;
	
	
	M_Boolean isDoorOpen;
	
	float fscale;
	
	
	M_Boolean isFriendMap;
	
	M_Boolean isQuestKey;
	
	M_Boolean isTuto;
	
	M_Boolean isQuestResult;
	M_Boolean isNewModel;
	int newModelAnyCnt;
	int newModelType;
		
	int dropIconUiAnyCnt[20];
	
	
	int uiShowMoney;
	int uiShowExp;
	int uiShowFame;
	
	
	int DropTypeNum[12];
	
	
	
	float eventShowY;
	float eventShowScale;
	float eventShowRot;
	
	
	int uiHideCnt;
	
	

	
	
	int doorX;
	int doorY;
	int doorCode;
	int doorKey;
	int doorMakeX;
	int doorMakeY;
	
	int floorUpX;
	int floorUpY;
	int floorDownX;
	int floorDownY;
	
	M_Boolean isInitLoading;		//메인메뉴에서 최초 세팅시에만
	
	
	int ranDomUserCode;
	
	M_Boolean isExtensionEvent_Tile;
	int extensionEventAnyCnt_Tile;
	
	M_Boolean isExtensionEvent;
	int extensionEventAnyCnt;
	
	M_Boolean isExternalWall;
	int externalWallEventAnyCnt;
	
	M_Boolean isExternalShake;
	int externalShakeEventAnyCnt;

	M_Boolean isExternalScale;
	int externalScaleEventAnyCnt;
	
	int initCnt;
	
	int totalHairData;
	int totalFaceData;
	
	
	M_Boolean isLoginInit;
	M_Boolean isTodaySocial;
	M_Boolean isTodayRunway;
	int todayRunwayAnyCnt;
	XTOUCH xTouchTodayRunwayLink[3];
	
	
	
	XTOUCH xTouchFriendMapSocialInfo;
	M_Boolean isFriendMapSocialInfo;
	M_Boolean isFriendMapFloorInfo;
	
	
	
	M_Boolean isSubLoading;
	M_Boolean subLoadingState;
	int subLoadingAntCnt;
	
	M_Boolean isStartClet;
	
	
	int npcSpeakPer;
	
	M_Boolean isAppReview;

	M_Boolean isFirstIap;
    
    
    int reviewQuestNum;
	
	
	
	int hackingTimeSec;
	
	
	M_Boolean isCashHacking;
	
	
	M_Boolean is5RocksHackingLog;
	
	
	XTOUCH xTouchFriendMapUiKakao;
	M_Boolean isKakaoFriendMap_NET;
	
    
    
    XTOUCH xTouchAccessBonusShow;
    
    
	
	
	
	M_Boolean isOpen_CASH10000;
	
	M_Boolean isOpen_Tnk;
    
    int uiShowType;
    
    
    int pushTime[10];
    
    
    XTOUCH xTouchCafeUi;
    
	
    bool isSetDeviceId;
    
    int myShopRefreshCnt;
    bool isMyShopRefreshNet;
    
} XWORLDMAP;
extern XWORLDMAP xWorldMap;











typedef struct
{
	int selectTab;
	XTOUCH xTouchTab[5];
	
	
	XTOUCH xTouchOnOff[10];
	
	
	XTOUCH xTouch4inch;
	XTOUCH xTouchHelp;
	XTOUCH xTouchLogout;
	XTOUCH xTouchAccountDel;
	
	
	XTOUCH xTouchBgmVol;
	XTOUCH xTouchEffVol;

	int effBackup;
	int bgmBackup;
	
	
} XOPTION;
extern XOPTION xOption;


typedef struct
{
	SECURITY inShopPerTotal;
	int inShopPer[INSHOPPERMAX];
	M_Boolean isInShopPerTemp[INSHOPPERMAX];
	int inShopPerTemp[INSHOPPERMAX];
	
	
	M_Boolean isSellTime;
	
} XINSHOPPER;
extern XINSHOPPER xInShopPer;


typedef struct
{
	M_Boolean isState;
	int sellNum;
	int sellNumMax;
	int sleepTime;
	int sellTime;
	
} XSERVERSELL;
extern XSERVERSELL xServerSell;





#define FASHIONSHOWLIGHTMAX	7

#define FASHINGSHOWLIGHT_STATE_OFF		0
#define FASHINGSHOWLIGHT_STATE_ON		1
#define FASHINGSHOWLIGHT_STATE_SET		2
typedef struct
{
	int state;
	int x;
	int y;
	int imgNum;
	int anyCnt;
	int anyCntMax;

} XFASHIONSHOWLIGHT;
extern XFASHIONSHOWLIGHT xFashionShowLight[FASHIONSHOWLIGHTMAX];

typedef struct
{
	M_Int32 totalNum;
	
	M_Boolean isPlayerInfo;
	M_Int64 playInfoTime;
    
    XTOUCH xTouchMyShopRefresh;
    XTOUCH xTouchClubMenu;
    
} XWORLDMAPUI;
extern XWORLDMAPUI xWorldMapUi;





////////////////////피팅////////////////
#define FITTINGTABMAX		7
#define FITTINGSLOTBMAX		20
#define FITTINGSLOTSMAX		800


typedef struct
{
	int state;
	int selectTabB;
	int selectSlot;
	int totalNumS;
	
	int inOutCnt;
	M_Boolean isInOutMenu;
		
	M_Int32 totalSlot[FITTINGSLOTBMAX];
	XCATALOGSLOT xSlot[FITTINGSLOTBMAX][FITTINGSLOTSMAX];
	
    
    int blinkEffAnyCnt_trend[FITTINGSLOTSMAX];
    int blinkEffAnyCnt_color[FITTINGSLOTSMAX];
    int blinkEffAnyCnt_concept[FITTINGSLOTSMAX];
    
    
    
    
	int gender;
	XFACE xFace;
	XFITTINGLAYER xF[2];		//남녀 두개
	
	int selectShowWindowNum;
	
	int totalShowWindow[FLOORMAX];
	int showWindowSlotNum[FLOORMAX][128];
		
	int fittingLayeredMax;
	
	
	int sellTableItemNum[2];
	
	
} XFITTING;
extern XFITTING xFitting;




#define STAFF_STATE_PLAY			0
#define STAFF_STATE_BUYPOPUP		1

#define FITTINGTABMAX_STAFF			6

#define STAFF_SLOT_PAYMENTASSISTANT_1F		0
#define STAFF_SLOT_SHOPASSISTANT1_1F		1


#define STAFF_SLOT_PAYMENTASSISTANT_2F		2
#define STAFF_SLOT_SHOPASSISTANT1_2F		3


#define STAFF_SLOT_PAYMENTASSISTANT_3F		4
#define STAFF_SLOT_SHOPASSISTANT1_3F		5


typedef struct
{
	int state;
	int totalPopupItemSlot;
	int popupItemSlotTab[15];
	int popupItemSlotCode[15];
	int sellGold;
	int sellCash;
	int sellGoldCnt;
	int sellCashCnt;
	XDRAGSCROLL xDragScrollPopupItemSlot;
	
	M_Int32 totalSlot[FITTINGSLOTBMAX];
	XCATALOGSLOT xSlot[FITTINGSLOTBMAX][FITTINGSLOTSMAX];
	
	M_Int32 selectStaffSlot;
	M_Int32 totalStaffSlot;
	M_Int32 staffSlot[10];
	
	XTOUCH xTouchEdit;
	
} XSTAFF;
extern XSTAFF xStaff;

#define STAFFMAKE_INTYPE_INIT	0
#define STAFFMAKE_INTYPE_EDIT	1
typedef struct
{
	int type;
	int sex;
	char strName[128];
	XTOUCH xTouchSex[2];
	XTOUCH xTouchName;
	
	
	XFITTINGLAYER xF[2];
	XFACE xFace[2];
	
	int inType;
} XSTAFFMAKE;
extern XSTAFFMAKE xStaffMake;




////////////////////카탈로그////////////////
#define CATALOGTABMAX		2

#define CATALOGSLOTBMAX		20
#define CATALOGSLOTSMAX		800

typedef struct
{
	int state;
	int selectTabB;
	int selectTabS;
	int selectSlot;
	
	
	M_Int32 totalNumB;
	M_Int32 totalNumS;

	
	////////////////////////////////사용///////////////
	M_Int32 totalSlotS;
	XCATALOGSLOT xSlotS[512];
	/////////////////////////////////데이터////////////////
	M_Int32 totalSlot[CATALOGSLOTBMAX];
	XCATALOGSLOT xSlot[CATALOGSLOTBMAX][CATALOGSLOTSMAX];
	
	
	M_Int32 totalSlotFriendOrder[CATALOGSLOTBMAX];
	XCATALOGSLOT xSlotFriendOrder[CATALOGSLOTBMAX][CATALOGSLOTSMAX];
	
	M_Int32 totalSlotFriendOrderTemp[CATALOGSLOTBMAX];		//정렬용
	XCATALOGSLOT xSlotFriendOrderTemp[CATALOGSLOTBMAX][CATALOGSLOTSMAX];//정렬용
	
	/////////////////////////////////////////////////////
	M_Boolean isListOpen;
	int selectTabList;	
} XCATALOG;
extern XCATALOG xCatalog;



typedef struct
{
	int selectTabS;
	int type;		//0:일반1:리스트확인용
	
} XPRODUCTIONLIST;
extern XPRODUCTIONLIST xProductionList;



#define EXTERNALWALLMAX		30
typedef struct
{
	int selectWallChange;
	int selectWall;
	int totalNum;
	int listSlot[EXTERNALWALLMAX];
} EXTERNALWALL;
extern EXTERNALWALL xExternalWall;

typedef struct
{
	char strName[EXTERNALWALLMAX][64];
	int priceType[EXTERNALWALLMAX];
	int price[EXTERNALWALLMAX];
	M_Boolean isOpen[EXTERNALWALLMAX];
} EXTERNALWALLDATA;
extern EXTERNALWALLDATA xExternalWallData;



#define EMOTICON_STATE_DONT		0
#define EMOTICON_STATE_PLAY		1

#define EMOTICON_TYPE_SMILE		0
#define EMOTICON_TYPE_ANGER		1

typedef struct
{
	int state;
	int type;
	int anyCnt;
} XEMOTICON;


////////////////////판매////////////////

#define SELL_STATE_MAIN						0
#define SELL_STATE_CASHPOPUP				1
#define SELL_STATE_CASHPOPUP_PRODUCTION		2



typedef struct
{
	int state;
	
	int selectSellTable;
	int selectSlot;
	int selectMapX;
	int selectMapY;
	
	
	int totalSlot;

	XSELLSLOT xSlot[1024];
	int selectSellSelectItemSlot;
	

	int totalTotal[FLOORMAX];
	int totalTrend[FLOORMAX];
	int totalSell[FLOORMAX];
	int totalHanger[FLOORMAX];
	int totalAccessory[FLOORMAX];	
	int totalSex[2][FLOORMAX];
	
	int totalItemNum[FLOORMAX];
	int totalEmpty[FLOORMAX];
	int totalIngHangerSlot[FLOORMAX];
	int totalIngAccessorySlot[FLOORMAX];

	
	
	
	int tableNumSlot_Total[FLOORMAX][60];
	int tableNumSlot_Trend[FLOORMAX][60];
	int tableNumSlot_Sell[FLOORMAX][60];
	int tableNumSlot_Hanger[FLOORMAX][30];
	int tableNumSlot_Accessory[FLOORMAX][30];
	int tableNumSlot_Sex[2][FLOORMAX][30];
	
	int tableNumSlot_Empty[FLOORMAX][30];
	
	M_Boolean isSlotInfo;
	
} XSELL;
extern XSELL xSell;

////////////////////인테리어 모드
#define INTERIORSELLPER		10
#define INTERIORSELLCASH	2700

#define INTERIORTABMAX		6

#define INTERIORSLOTBMAX		24
#define INTERIORSLOTSMAX		512

#define INTERIORBUILD_TYPE_SHOP			0
#define INTERIORBUILD_TYPE_INVENTORY	1
#define INTERIORBUILD_TYPE_GAME			2

#define INTERIORBUILD_MODE_OBJ		0
#define INTERIORBUILD_MODE_TILE		1


#define INTERIOR_STATE_PLAY				0
#define INTERIOR_STATE_THEMASELECT		1
#define INTERIOR_STATE_EXTERNAL			2
#define INTERIOR_STATE_CASHSHOP			3
#define INTERIOR_STATE_SELLPOPUP		4
#define INTERIOR_STATE_TEAM				5

#define INTERIORBUILD_MOVETYPE_WORLDMAP		0
#define INTERIORBUILD_MOVETYPE_OBJ			1
typedef struct
{
	int state;
    int totalCount;
	/////////////////////////////////설치관련//////////////////////////
	XINTERIORSLOT xBuildSlot;
	int buildType;		//이동타입
	int buildInType;		//진입타입
	int buildMode;		//타일 오브젝트 모드
	
	
	int buildMapTileXpos;
	int buildMapTileYpos;
	int buildMapMoveXpos;
	int buildMapMoveYpos;
	int buildMapMoveXposStart;
	int buildMapMoveYposStart;
	
	M_Int64 buildModeTime64;
	int buildModeTimeXpos;
	int buildModeTimeYpos;
	/////////////////////////////////메뉴쪽//////////////////////////
	M_Int32 selectTabB;
	M_Int32 selectTabS;
	M_Int32 selectSlotS;
	M_Int32 selectThema;
	M_Int32 selectSlotTeam;
	////////////////////팀슬롯
	XDRAGSCROLL xDragScrollTeam;
	////////////////////판매
	int sellNum;	//판매 개수
	XINTERIORSLOT xSellSlot;	//판매슬롯복사용저장
	/////////////////공통슬롯
	M_Int32 totalNumS;
	XINTERIORSLOT xSlotS[INTERIORSLOTSMAX];
	////////////////데이터엑셀 슬롯
	int totalNum;
	M_Int32 totalSlot[INTERIORSLOTBMAX];
	XINTERIORSLOT xSlot[INTERIORSLOTBMAX][INTERIORSLOTSMAX];
	
	//////////////테마슬롯
	int totalNumThema;
	int themaCode[INTERIORSLOTBMAX];
	char strThemaName[INTERIORSLOTBMAX][64];
	M_Int32 totalSlotThema[INTERIORSLOTBMAX];
	XINTERIORSLOT xSlotThema[INTERIORSLOTBMAX][INTERIORSLOTSMAX];
		
	///////////////설치 제한
	M_Int32 buildlimitMax[FLOORMAX][15];
	M_Int32 buildlimitNum[FLOORMAX][15];
	
	
	XTOUCH xBuildMode[2];
	
    
	M_Boolean isBuildOkBtn;
} XINTERIOR;
extern XINTERIOR xInterior;
////////////////////////////



typedef struct
{
	SECURITY price;
	int priceType;

	int lv;
	SECURITY exp;
	int gender;
	SECURITY fame;
	int layer;
	char strName[64];
	
	SECURITY makeTime;
	SECURITY makeNum;
	int makePoint;
	int inShopPer;
	
	SECURITY sellPrice;
	
	M_Boolean isStaff;
	int color;
	int concept;
	
	int type2FashionShowScore;
	
	M_Boolean isImg[2][19];
	M_Boolean isImgF[19];
	
	int theme;
    
    
    int clubLv;
    int clubPrice;
    int clubScore;
    int clubCostMax;
    int clubExp;
    
	
} XFASHOINDATA;
extern XFASHOINDATA xFashionData[FASHIONDATATYPEMAX][FASHIONDATAMAX];


typedef struct
{
    int lv;
    
    int makeTime;
    SECURITY price;
    
    int materialType[3];
    int materialCnt[3];
    
    char strName[64];
    
    
}XFASHIONDATA_FP;
extern XFASHIONDATA_FP xFashionData_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX];

typedef struct
{
    M_Int32 code;
    M_Int32 num;
    M_Boolean isInfoOpen;
    M_Boolean isSelectV;
    
    M_Boolean isModelUse;
    
    M_Boolean isNew;
    M_Boolean isHot;
    M_Boolean isEvent;
    M_Boolean isSale;
    
} XCATALOGSLOT_FP;

typedef struct
{
    int state;
    int selectTabB;
    int selectTabS;
    int selectSlot;
    
    
    M_Int32 totalNumB;
    M_Int32 totalNumS;
    
    
    ////////////////////////////////사용///////////////
    M_Int32 totalSlotS;
    XCATALOGSLOT_FP xSlotS[512];
    /////////////////////////////////데이터////////////////
    M_Int32 totalSlot[CATALOGSLOTBMAX];
    XCATALOGSLOT_FP xSlot[CATALOGSLOTBMAX][CATALOGSLOTSMAX];
    
    
    M_Int32 totalSlotFriendOrder[CATALOGSLOTBMAX];
    XCATALOGSLOT_FP xSlotFriendOrder[CATALOGSLOTBMAX][CATALOGSLOTSMAX];
    
    M_Int32 totalSlotFriendOrderTemp[CATALOGSLOTBMAX];		//정렬용
    XCATALOGSLOT_FP xSlotFriendOrderTemp[CATALOGSLOTBMAX][CATALOGSLOTSMAX];//정렬용
    
    /////////////////////////////////////////////////////
    M_Boolean isListOpen;
    int selectTabList;	
} XCATALOG_FP;
extern XCATALOG_FP xCatalog_FP;

typedef struct
{
    int code;
    int isNew;
    int price;
    int priceType;
    int lv;
    int warmth;
    int sale;
    int buffType;
    int buff;
    int SetNum;
    int layer;
    int SellOnOff;
    bool isOpen;
    char strName[512];
}XFASHIONLISTSLOT_FP;

typedef struct
{
    int totalNum;//데이터 원본 전체합계
    int parsingTotalNum;//판매중지된거 뺀 전체합계
    int parsingSlotTotalNum[FASHIONDATATYPEMAX];//판매중지된거 빼고 타입별 총합
    int totalSlotNum[FASHIONDATATYPEMAX];//데이터 원본 타입별 합계
    XFASHIONLISTSLOT_FP xSlot[FASHIONDATATYPEMAX][FASHIONDATAMAX];//읽기용
    XFASHIONLISTSLOT_FP xSlotS[FASHIONDATAMAX];//전체용
    XFASHIONLISTSLOT_FP xSlotTemp[FASHIONDATATYPEMAX][FASHIONDATAMAX];//실 사용데이터
}XFASHIONLIST_FP;
extern XFASHIONLIST_FP xFashionList_FP;


/////////////헤어데이터///////////////////
#define HAIRDATAMAX			100
typedef struct
{
	char strName[64];
	int lv;
	int gender;
	SECURITY price;
	int priceType;
	int useType;
	
	int haveNum;
	
	int inShopPer;
    
    //클럽
    bool isClubOpen;
    int clubLv;
    int clubScore;
    int clubPrice;
} XHAIRDATA;
extern XHAIRDATA xHairData[HAIRDATAMAX];


#define PACKAGEDATAMAX      128


#define PACKAGEUISHOW_STATE_CLOSE       0
#define PACKAGEUISHOW_STATE_OPEN        1
typedef struct
{
    bool isPlay;
    
    int selectType;
    XTOUCH xTouchOk;
    XTOUCH xTouchExit;
    
    
    
    XTOUCH xTouchUiMain;
    int uiShowNum;
    int uiShowRemainTime;
    
    
    
    int uiShowState;
    int uiShowHH;
    XTOUCH xTouchUi[PACKAGEDATAMAX];
} XPACKAGEPOPUP;
extern XPACKAGEPOPUP xPackagePopup;




typedef struct
{
    char strName[64];
    int price;
    int cnt;
    int max;
    int lv;
    bool isUiShow;
    
    char strOneStoreIapId[128];
} XPACKAGEDATA;
extern XPACKAGEDATA xPackageData[PACKAGEDATAMAX];

typedef struct
{
    char strName[64];
    int clublv;
    int coin;
    int count;
    int num;
}XCLUBITEM;
extern XCLUBITEM xClubItem[128];

#define CLUBITEMMAX 20
extern XIMG imgClubItem[CLUBITEMMAX];
extern XIMG imgClubCostIcon;
extern XIMG imgClubPointIcon;
extern XIMG imgClubScoreIcon;
extern XIMG imgClubFitting[5];


extern XIMG imgTest[10];
extern XIMG imgProduction[30];
extern XIMG imgWealthIcon[5];
extern XIMG imgWealth;
extern XIMG imgMenu;
extern XIMG imgMenuIcon1;
extern XIMG imgMenuIcon2;

extern XIMG imgMainExpWarmth;
extern XIMG imgBarExp;
extern XIMG imgBarWarmth;
extern XIMG imgBarEmpty;
extern XIMG imgBtnYesNo;
extern XIMG imgBtn;
extern XIMG imgProductionBg;
extern XIMG imgProductionTitle;
extern XIMG imgFashionWeek[30];

extern XIMG imgMasterUi[10];

extern XIMG imgClubLobbyTab[10];
extern XIMG imgClubLobby[15];
extern XIMG imgClubDonation[10];
extern XIMG imgChangeClubIcon[10];
extern XIMG imgClubShop[10];
extern XIMG imgClubNameModify[10];
extern XIMG imgClubShopGift[20];
extern XIMG imgClubIconShop[20];
extern XIMG imgClubStorage[20];
extern XIMG imgClubWealth;
extern XIMG imgAmuletSlot[2][5];

extern XIMG imgAmuletSetting[15];
extern XIMG imgAmuletIcon[32];
extern XIMG imgAmuletBg[32];
extern XIMG imgAmuletUiIcon[32];


extern XIMG imgJewelBuffBg[10];
extern XIMG imgJewelIcon[64];


extern XIMG imgJewelQuestType[20];

extern XIMG imgJewelQuest[16];
extern XIMG imgJewelQuestTab[2];


extern XIMG imgMyShopRefresh[3];
extern XIMG imgFastScroll;
extern XIMG imgFriendList[5];

extern XIMG imgHelpListIcon;
extern XIMG imgHelpList[10];

extern XIMG imgMyShop[2];
extern XIMG imgRivalUi[15];
extern XIMG imgRivalGuest[15];
extern XIMG imgRivalResult[10];
extern XIMG imgCafeIcon;
extern XIMG imgFriendDelBtn2;
extern XIMG imgProductionLatest;
extern XIMG imgProductionMenuExitIcon;

extern XIMG imgRival[10];

extern XIMG imgRivalWorldMap[10];
extern XIMG imgRivalInfo[10];


extern XIMG imgRivalWorldMapSlot[32];
extern XIMG imgRivalTitle[32];
extern XIMG imgRivalBuilding[32];
extern XIMG imgRivalNpc[32];
extern XIMG imgRivalNpcIcon[32];

extern XIMG imgLoginTime;
extern XIMG imgBlinkEff2;

extern XIMG imgDressCodeEff[5];

extern XIMG imgHotDealUi[5];
extern XIMG imgHotDeal[10];
extern XIMG imgNewDancerEff[5];



extern XIMG imgCastingAIcon;
extern XIMG imgCastingSIcon;
extern XIMG imgCastingASIcon;



extern XIMG imgEventQuest[15];
extern XIMG imgEventQuestIcon[128];
extern XIMG imgEventQuestBg[128];

extern XIMG imgPackage[64];
extern XIMG imgPackagePopup[PACKAGEDATAMAX];
extern XIMG imgPackageUiIcon[PACKAGEDATAMAX];


extern XIMG imgPrePayUi[5];
extern XIMG imgPrePay[5];


extern XIMG imgMileageIcon[5];
extern XIMG imgMileageShop[10];


extern XIMG imgCashEvent;


extern XIMG imgBuffIcon[10];
extern XIMG imgBuffObj[10];


extern XIMG imgGiftExpIcon;
extern XIMG imgGiftGoldIcon;
extern XIMG imgGiftLookIcon;
extern XIMG imgGiftCandyIcon;
extern XIMG imgGiftModelCastingCAIcon;
extern XIMG imgGiftModelCastingBSIcon;
extern XIMG imgGiftTrendHangerIcon;
extern XIMG imgGiftTrendAccessoryIcon;

extern XIMG imgHair[HAIRDATAMAX][20][2][2];		//[헤어코드][두상번호][pos][2]
extern XIMG imgHairF[HAIRDATAMAX][2];		//[헤어코드][두상번호][pos][2]
extern XIMG imgHairF_Model[HAIRDATAMAX][2];		//[헤어코드][두상번호][pos][2]
extern XIMG imgHair_Model[HAIRDATAMAX][20][2][2];		//[헤어코드][두상번호][pos][2]
extern XIMG imgHair_Npc[HAIRDATAMAX][20][2][2];		//[헤어코드][두상번호][pos][2]
extern M_Boolean isImgHair[HAIRDATAMAX];
extern M_Boolean isImgHair_Model[HAIRDATAMAX];
//////////////////////////////////////

/////////////표정데이터///////////////////
#define FACEDATAMAX			100

#define FACETYPEMAX			3
#define FACE_TYPE_NORMAL	0
#define FACE_TYPE_SMILE		1
#define FACE_TYPE_ANGRY		2
typedef struct
{
	char strName[64];
	int lv;
	int gender;
	SECURITY price;
	int priceType;
	
	int haveNum;
	int inShopPer;
    
    
    
    //클럽
    bool isClubOpen;
    int clubLv;
    int clubScore;
    int clubPrice;
    
    
} XFACEDATA;
extern XFACEDATA xFaceData[FACEDATAMAX];





extern XIMG imgFace[FACEDATAMAX][FACETYPEMAX][20][2];		//[표정코드][표정액팅][두상번호][pos][2]
extern XIMG imgFace_Model[FACEDATAMAX][FACETYPEMAX][20][2];		//[표정코드][표정액팅][두상번호][pos][2]
extern XIMG imgFace_Npc[FACEDATAMAX][FACETYPEMAX][20][2];		//[표정코드][표정액팅][두상번호][pos][2]
extern XIMG imgFaceF[FACEDATAMAX];							//[표정코드][표정액팅][두상번호][pos][2]
extern XIMG imgFaceF_Model[FACEDATAMAX];							//[표정코드][표정액팅][두상번호][pos][2]
extern M_Boolean isImgFace[FACEDATAMAX];
extern M_Boolean isImgFace_Model[FACEDATAMAX];
extern M_Boolean isImgFace_Npc[FACEDATAMAX];
//////////////////////////////////////

////////////////////생산 모드
typedef struct
{
	int selectSlot;
	int selectMapX;
	int selectMapY;
	
	XTOUCH xTouchDelBtn;
	XTOUCH xTouchList;
	XTOUCH xTouchFastCash;
	
	///선택모드
	int selectModeCode;
	
	
	//////////재고파악//////////
	int haveItemCnt[FLOORMAX][2];
	
} XPRODUCTION;
extern XPRODUCTION xProduction;
////////////////////////////


////////////////////생산 모드
#define PRODUCTIONMENU_STATE_MAIN		0
#define PRODUCTIONMENU_STATE_FASTCASHPOPUP	1


#define PRODUCTIONMENU_TYPE_NORMAL		0
#define PRODUCTIONMENU_TYPE_PREMIUM		1

#define PRODUCTIONMENUSLOTMAX	6
#define PRODUCTIONMENUSLOT_STATE_WAIT	0
#define PRODUCTIONMENUSLOT_STATE_PLAY	1
#define PRODUCTIONMENUSLOT_STATE_RECV	2
typedef struct
{
	int state2;
	
	
	//관리운영부분
	int selectType;
	int state[2][PRODUCTIONMENUSLOTMAX];
	int recvAnyCnt[2][PRODUCTIONMENUSLOTMAX];
	int selectSlot;
	XTOUCH xTouchType;
	XTOUCH xTouchSlot[PRODUCTIONMENUSLOTMAX];
	
	XTOUCH xTouchDelBtn;
	
	int makeMoney;
	int makeCnt;
	XTOUCH xTouchFast;
	XTOUCH xTouchFastAll;
	XTOUCH xTouchDel[PRODUCTIONMENUSLOTMAX];
	
	//데이타부분
	int lv[2][PRODUCTIONMENUSLOTMAX];
	SECURITY openCash[2][PRODUCTIONMENUSLOTMAX];
	SECURITY openCashOri[2][PRODUCTIONMENUSLOTMAX];

	//네트워크 연동부분
	M_Boolean isUpData[2][PRODUCTIONMENUSLOTMAX];
	M_Boolean isOpen[2][PRODUCTIONMENUSLOTMAX];
	int slotCode[2][PRODUCTIONMENUSLOTMAX];
	M_Int64 slotFlowTime[2][PRODUCTIONMENUSLOTMAX];
	M_Boolean isFriend[2][PRODUCTIONMENUSLOTMAX];
	int orderKey[2][PRODUCTIONMENUSLOTMAX];
	int minigameBonus[2][PRODUCTIONMENUSLOTMAX];
	
	//푸쉬
	int pushState[2][PRODUCTIONMENUSLOTMAX];
	int pushTime[2][PRODUCTIONMENUSLOTMAX];
	
	int useLook[2][PRODUCTIONMENUSLOTMAX];
	
	int totalSuccess;
	int totalSuccessSub;
	int totalWaitSlot;
	
	int worldMapInfoSuccessCnt;
	
	int totalSuccessType[2];
	
	int totalSuccessInteriorType[2];
	int totalIng;
	
	M_Boolean isMakeBtnInfo;
	
	XTOUCH xTouchSlotInfo;
	M_Boolean isSlotInfo;
	
	XTOUCH xTouchSortLv;
	XTOUCH xTouchSortTime;
	M_Boolean isSortLv;
	M_Boolean isSortTime;
	
    
    
    
    
    XTOUCH xTouchSexSortState[3];
    int sexSortState;
    
    
    
	
	
	
	
	M_Boolean isSlotSaleEventOpen;
	
	XGLITTEREFF xGlitterEff;
	
	int startYY;
	int startMM;
	int startDD;
	int startHH;
	
	int endYY;
	int endMM;
	int endDD;
	int endHH;
	
	
	
	
	
} XPRODUCTIONMENU;
extern XPRODUCTIONMENU xProductionMenu;
////////////////////////////
#define PRODUCTMENUSLOTMAX 12
#define PRODUCTLISTMAX     24
#define PRODUCTIONMAX      64
typedef struct
{
    int state;//슬롯의 상태 -1: 잠금(자물쇠) 0: 잠금(추가), 1: 대기, 2: 제작중, 3: 제작완료
    int itemCode;//의상번호
    int endTime;//생산완료시간
    bool produce;//생산중인가?
}XPRODUCTION_FP_SLOT;

typedef struct
{
    int key;//제작기의 고유번호
    int code;//제작기의 인테리어번호
    int Upgrade;//업그레이드 정
    int totalSlot;//슬롯 수
    int index;//슬롯 찾는 인덱스
    XPRODUCTION_FP_SLOT xSlot[PRODUCTMENUSLOTMAX];
}XPRODUCTIONDATA;

typedef struct
{
    int state;
    int selectProduct;//선택된 제작기
    int index;//제작기의 인덱스
    int totalData;//등록된 제작기의 수
    int EndTimer[PRODUCTIONMAX][PRODUCTMENUSLOTMAX];//앞은 제작기번호, 뒤는 슬롯번호
    int selectSlot;
    bool isTouchProduct;//제작할 의상을 터치했는가
    bool isTouchLeftBtn;//의상 리스트 왼쪽 버튼 눌렀는가?
    bool isTouchRightBtn;//의상 리스트 오른쪽 버튼 눌렀는가?
    bool isTouchLeftArrow;//제작 슬롯 왼쪽 화살표를 눌렀는가?
    bool isTouchRightArrow;//제작 슬롯 오른쪽 화살표를 눌렀는가?
    bool isTouchClr;//닫기 버튼을 눌렀는가?
    bool isTouchOpen;//확장버튼을 눌렀는가?
    bool isTouchPopupClr;//제작취소의 닫기버튼을 눌렀는가?
    bool isTouchYes;
    bool isTouchNo;
    
    XDRAGSCROLL xDragScrollProductionS;//의상리스트 스크롤
    XDRAGSCROLL xDragScrollProductionB;//제작슬롯 스크롤
    
    XTOUCH  xTouchLeftBtn;//의상 리스트 왼쪽 버튼
    XTOUCH  xTouchRightBtn;//의상 리스트 오른쪽 버튼
    XTOUCH  xTouchLeftArrow;//제작 슬롯 왼쪽 버튼
    XTOUCH  xTouchRightArrow;//제작 슬롯 오른쪽 버튼
    XTOUCH  xTouchList[PRODUCTLISTMAX];//의상 리스트 터치영역들
    XTOUCH  xTouchSlot[PRODUCTMENUSLOTMAX];//제작 슬롯의 터치 영역들
    XTOUCH  xTouchOpen;//확장버튼
    XTOUCH  xTouchFast[PRODUCTMENUSLOTMAX];//즉시 완료 버튼
    XTOUCH  xTouchYes;//제작취소 팝업의 yes
    XTOUCH  xTouchNo;//제작취소 팝업의 No
    
    XPRODUCTIONDATA xData[PRODUCTIONMAX];//제작기 데이터들
} XPRODUCTION_FP;
extern XPRODUCTION_FP xProduction_FP;

#define PRODUCTIONMENULATESTMAX     10
typedef struct
{
    int code[PRODUCTIONMENULATESTMAX];
    
    XTOUCH xTouchSlot[PRODUCTIONMENULATESTMAX];
    
    int selectSlot;
} XPRODUCTIONMENULATEST;
extern XPRODUCTIONMENULATEST xProductionMenuLatest;


#define SELLSLOTSAVEMAX     6
typedef struct
{
    int code[PRODUCTIONMENULATESTMAX];
} XPRODUCTIONMENULATESTSAVE;
extern XPRODUCTIONMENULATESTSAVE xProductionMenuLatestSave;

typedef struct
{
	int code[PRODUCTIONMENULATESTMAX];
} XSELLSLOTSAVE;
extern XSELLSLOTSAVE xSellSlotSave;







#define SELLSLOTMAX			9
#define SELLTABLEINFOMAX		20
typedef struct
{
	M_Boolean isEventBox;
	
	int imgEventBox;
	int eventBoxAnyCnt;
	
	M_Boolean isUpdata;
	M_Boolean isUse;
	int interiorCode;
	int x;
	int y;
	
	M_Boolean isAstarErr;
	
	
	XSELLSLOT xSlot[SELLSLOTMAX];
	int sellOkTotal;
	int useTotal;
	int useXslotNum[SELLSLOTMAX];

	M_Boolean isSocial;
	int totalSocialSlot;
	XSOCIALSLOT xSocialSlot[SOCIALSLOTMAX];
	
	int eventBoxShowAntCnt;
		
	int orderingCnt;
	
	int inShopPer;
	int inShopPerTemp;
	
	M_Boolean isTrendTouchAny0;
	int trendTouchAny0;
	M_Boolean isTrendTouchAny1;
	int trendTouchAny1;
	
	
	XGLITTEREFF xGlitterEff[GLITTEREFFMAXSUB];
	
} XSELLTABLE;
extern XSELLTABLE xSellTableInfo[FLOORMAX][SELLTABLEINFOMAX];

#define SELLTABLEUPDATATIME			90
#define SELLTABLEUPDATAMAX	64
typedef struct
{
	int sellUpdataTime;
	int total;
	int floor[SELLTABLEUPDATAMAX];
	int sellTableNum[SELLTABLEUPDATAMAX];
} XSELLTABLEUPDATA;
extern XSELLTABLEUPDATA xSellTableUpdata;



#define FITTINGROOMINFOMAX		32

#define FITTINGROOMINFO_STATE_WAIT		0
#define FITTINGROOMINFO_STATE_PLAY		1

typedef struct
{
	int totalNumWait;		//사용가능한
	int waitSlot[FITTINGROOMINFOMAX];		//사용가능한
	
	int totalNumAll;
	int codeNum[FITTINGROOMINFOMAX];		
	
	M_Boolean isAstarErr[FITTINGROOMINFOMAX];
	
	int x[FITTINGROOMINFOMAX];
	int y[FITTINGROOMINFOMAX];
	

	int state[FITTINGROOMINFOMAX];
	int npcNumcode[FITTINGROOMINFOMAX];
} XFITTINGROOMINFO;
extern XFITTINGROOMINFO xFittingRoomInfo[FLOORMAX];


#define CHAIRMAX		32
typedef struct
{
	int totalNum;
		
	int interiorCode[CHAIRMAX];
	int npcCode[CHAIRMAX];
	int x[CHAIRMAX];
	int y[CHAIRMAX];
	
	M_Boolean isAstarErr[CHAIRMAX];
			
} XCHAIRINFO;
extern XCHAIRINFO xChairInfo[FLOORMAX];


typedef struct
{
	int codeNum;
	int key;
	int x;
	int y;
	
	int interiorModeCode;
	
	M_Boolean isAstarErr;
	M_Boolean isEventBox;
    
	int imgEventBox;
	int eventBoxAnyCnt;
	int eventBoxShowAntCnt;
	
} XPAYMENTINFO;
extern XPAYMENTINFO xPayMentInfo[FLOORMAX];


#define SHOWWINDOWINFOMAX			32
#define SHOWWINDOWINFO_STATE_WAIT		0
#define SHOWWINDOWINFO_STATE_PLAY		1
typedef struct
{
	M_Boolean isEventBox;
	int eventBoxAnyCnt;
	int imgEventBox;
	M_Boolean isUse;
	M_Boolean isFitting;
	int state;
	int x;
	int y;
	int totalNum;
	int interiorCode;
	
	M_Boolean isAstarErr;
	

	
	int npcNumcode;
	
		
	int gender;
	XFITTINGLAYER xF;
	

	
	M_Boolean isSocial;
	int totalSocialSlot;
	XSOCIALSLOT xSocialSlot[SOCIALSLOTMAX];
			
	int eventBoxShowAntCnt;
		
	
	int fameEventStart;
	M_Boolean isFameEvent;
	int fameEvent;

	
	

	XGLITTEREFF xGlitterEff[GLITTEREFFMAXSUB];
} XSHOWWINDOWINFO;
extern XSHOWWINDOWINFO xShowWindowInfo[FLOORMAX][SHOWWINDOWINFOMAX];

////////////////////////////////////////////////////방명록//////////////////////

typedef struct
{
	int friendDataSlotNum;
	int key;
	char strTime[64];
	char strText[1024];

	int type;
	int giftType;
	SECURITY giftValue;
	
	M_Boolean isRecvOk;
	M_Boolean isSecret;
	
	
} XMAILSLOTDATA;

#define MAILSLOTMAX		256


#define MAIL_STATE_MAIN				0
#define MAIL_STATE_TEXTBOX			1
#define MAIL_STATE_GIFT_RESULT	2

typedef struct
{
	int state;
	
	int selectTab;
	
	char strToday[256];
	
	char strTextBox[1024];
	XTOUCH xTouchTab[3];
	XTOUCH xTouchTextBox;
	XTOUCH xTouchSendBtn;
	XTOUCH xTouchSecret;
	M_Boolean isSecret;
	XTOUCH xTouchToday;
	XTOUCH xTouchGiftBtn[4];
	XTOUCH xTouchDelBtn[4];
	XTOUCH xTouchProFileBtn[4];
	XDRAGSCROLL xDragScrollSlot;
	int selectSlot;
	
	
	
	int totalMailSlot;
	XMAILSLOTDATA xMailSlot[MAILSLOTMAX];
	int pageNum;
	int rowNum;

	
    bool bTemp;
	int mailLastKey;
	int giftLastKey;
	
	XTOUCH xTouchWorldMapicon;
	
	XTOUCH xTouchMenuicon;
	
	
	
	XTOUCH xTouchCashGiftBtn;
	
	///////////////레베카정보
	int pmUserId;
	char strTodayPm[256];
	
    
    int giftModelCode;
	
} XMAIL;
extern XMAIL xMail;
//////////////////////////////////////////////////////////////////////////////






#define MINIPROFILE_STATE_PROFILE			0


typedef struct
{
	int state;
	
	int friendDataSlotNum;
	char strToday[256];
	
	XTOUCH xTouchGiftBtn;
	XTOUCH xTouchFriendShopBtn;
} XMINIPROFILE;
extern XMINIPROFILE xMiniProfile;


#define LOCKMAX	10

#define LOCK_TYPE_CANDY				0
#define LOCK_TYPE_TREND				1
#define LOCK_TYPE_ORDER				2
#define LOCK_TYPE_FASHIONSHOW		3
#define LOCK_TYPE_MODEL				4

#define LOCK_TYPE_HANGER				5
#define LOCK_TYPE_ACCESSORY				6
#define LOCK_TYPE_SHOWWINDOW			7

typedef struct
{
	M_Boolean isLock[LOCKMAX];
	int mainQuestNum[LOCKMAX];
	int lv[LOCKMAX];
} XLOCK;
extern XLOCK xLock;


//////////////////////////////////////////////////////////////////////////////
#define GIFTSHOPSLOTMAX		7
typedef struct
{
	int userNum;
	XDRAGSCROLL xDragScroll;
	XTOUCH xTouchSelectSlot[4];
	int selectSlot;	
} XGIFTSHOP;
extern XGIFTSHOP xGiftShop;

#define WINNERMODELMAX		10
typedef struct
{
	int totalNum;
	int type[WINNERMODELMAX];
	int friendDataNum[WINNERMODELMAX];
	int modelNum[WINNERMODELMAX];
	XFITTINGLAYER xF[WINNERMODELMAX];
	int nowDelay[WINNERMODELMAX];
	int nowFrame[WINNERMODELMAX];
	
} XWINNERMODEL;
extern XWINNERMODEL xWinnerModel;



#define LOADIMGINTERIORMAX	3
#define LOADIMGCATALOGMAX	3
#define LOADIMGSTAFFMAX		3
typedef struct
{
	M_Boolean isLoad;
	M_Boolean isLoadFittingF;
	
	M_Boolean isLoadHairF;
	M_Boolean isLoadFaceF;
	
	M_Boolean prcTemp;
} XLOADIMG;
extern XLOADIMG xloadImg;


#define ACTLAYERMAX		20


///////////////////////샵/////////////////////

#define SHOPTAB_TYPE_MONEY			0
#define SHOPTAB_TYPE_PREMIUM		1
#define SHOPTAB_TYPE_MUSIC			2
#define SHOPTAB_TYPE_COUPON			3



#define SHOPTABPREMIUMMAX			7


#define CARDATAMAX		50


#define CASHSHOPICONMAX		20

typedef struct
{
	int selectTabB;
	XTOUCH xTouchTabB[5];
	XDRAGSCROLL xDragScroll;
	XTOUCH xTouchSelectSlot[12];
	XTOUCH xTouchSelectBtn[12];
	int selectSlot;
	
	
	int moneyType[20];
	SECURITY moneyPrice[20];
	SECURITY moneyPoint[20];
	int moneyPriceBonus[20];
	int moneyPriceFirstBonus[20];
	
	
	int premiumPriceType[SHOPTABPREMIUMMAX];
	SECURITY premiumPrice[SHOPTABPREMIUMMAX];
	SECURITY premiumPoint[SHOPTABPREMIUMMAX];
	char strPremiumName[SHOPTABPREMIUMMAX][128];
	
	
	int carTotalNum;
	int carSlot[CARDATAMAX];
	
	
	
	int totalMoneyTab;
	
	
	int totalTabB;
	
	
	XTOUCH xTouchCoupon;
	char strCoupon[64];
	
	
} XSHOP;
extern XSHOP xShop;





typedef struct
{
	int w;
	int h;
	int reSize;
} XDRAWOBJCENTER;
extern XDRAWOBJCENTER xDrawObjCenter;


typedef struct
{
	int total;
	char strTemp[3][128];
	
} XLINKINFO;
extern XLINKINFO xLinkInfo;



extern XIMG imgFriendMaxIcon;

extern XIMG imgCouponBg;
extern XIMG imgSaleShop[5];

extern XIMG imgCashShop[5];


extern XIMG imgSelectSongSlot;

extern XIMG imgBestRunway[10];

extern XIMG imgTodaySocialFashionBg;

extern XIMG imgShopOutLine[5];

extern XIMG imgAccessBonusBg[10];
extern XIMG imgAccessBonusIcon[5];
extern XIMG imgAccessBonusSlot[5];


extern XIMG imgModelName[100][4];

extern XIMG imgAliceShockBg;
extern XIMG imgAliceShockIcon;
extern XIMG imgAliceShockSlot;
extern XIMG imgAliceShockArrow;


extern XIMG imgExternalWallIcon[20];


extern XIMG imgModelMainGiftIcon[5];

extern XIMG imgStaffMakeBg;
extern XIMG imgStaffMake[5];

extern XIMG imgQuestIcon[80];

extern XIMG imgFriendOrderBg;
extern XIMG imgFriendOrderItemBg;
extern XIMG imgFriendOrderSelectSlot;

extern XIMG imgShopMusicIcon;
extern XIMG imgShopPremiumIcon[CASHSHOPICONMAX];
extern XIMG imgShopMoneyIcon[CASHSHOPICONMAX];


extern XIMG imgShopBg;

extern XIMG imgShopTabIcon;
extern XIMG imgShopTab;


extern XIMG imgNotice[10];




extern XIMG imgMiniGameIcon[20];





extern XIMG imgExternalWall[3];
extern XIMG imgExternalWallS[10];

extern XIMG imgExternalWallChange[FLOORMAX];;
extern XIMG imgExternalWallSChange;



extern XIMG imgLvUp[10];


extern XIMG imgActBodySub[ACTLAYERMAX][2];
extern XIMG imgActBody[ACTLAYERMAX][2];
extern XIMG imgFittingBodyStaff[2][ACTLAYERMAX];
extern XIMG imgFittingBody[2][ACTLAYERMAX];
extern XIMG imgFittingBodyBlack3Sub[2];
extern XIMG imgFittingBodyBlack[2][ACTLAYERMAX];

extern M_Boolean isFreeFittingF[FASHIONDATATYPEMAX][FASHIONDATAMAX];
extern M_Boolean isFreeFittingF_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX];
extern M_Boolean isImgFittingF[FASHIONDATATYPEMAX][FASHIONDATAMAX];
extern M_Boolean isImgFittingF_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX];

extern XIMG imgFittingF0[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingInOut0[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingF1[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingInOut1[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingF2[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingInOut2[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingF3[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingInOut3[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingF4[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingInOut4[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingF5[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingInOut5[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingF6[FASHIONDATAMAX][ACTLAYERMAX][20];
extern XIMG imgFittingInOut6[FASHIONDATAMAX][ACTLAYERMAX][20];

extern XIMG imgFittingItem[FASHIONDATATYPEMAX][FASHIONDATAMAX];
extern XIMG imgFittingFBackPack[FASHIONDATAMAX];

extern XIMG imgFittingF_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX];
extern XIMG imgFittingItem_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX];


extern  XIMG imgFittingBg[5];



extern M_Boolean isImgFLayer[FASHIONDATATYPEMAX][FASHIONDATAMAX];
extern  XIMG imgFLayer[FASHIONDATATYPEMAX][FASHIONDATAMAX][FASHIONDATALAYERMAX][2];
extern  XIMG imgFLayerSub[FASHIONDATATYPEMAX][FASHIONDATAMAX][FASHIONDATALAYERMAX][2];
////////////////////////////////////////////////////////////////////////////////////////////////
//LJW 추가 2018.02.05
extern M_Boolean isImgFLayerBig_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX];
extern M_Boolean isImgFLayer_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX];
extern XIMG ImgFLayerBig_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX][FASHIONDATALAYERMAX][2];
extern XIMG ImgFLayer_FP[FASHIONDATATYPEMAX][FASHIONDATAMAX][FASHIONDATALAYERMAX][2];
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////월드맵 건물 인벤
#define BUILDINGMAX		10
#define ROCKET_EFF_SMOKE	0
#define ROCKET_EFF_FIRE		1

extern  XIMG imgWorldMapRocketEFF[2];//0:연기,1:불꽃
extern  XIMG imgWorldMapRocket[BUILDINGMAX];//로켓
extern  XIMG imgWorldMapRocketBottom[BUILDINGMAX];//로켓 발사대
extern  XIMG imgWorldMapStorage[BUILDINGMAX];//창고
extern  XIMG imgWorldMapVinylHouse[BUILDINGMAX];//비닐하우스
extern  XIMG imgWorldMapAntenna[BUILDINGMAX];//안테나
////////////////////////////////////////////////



extern XTOUCH xTouchLink;
extern XTOUCH xTouchFriendMapRandom;
extern XTOUCH xTouchFriendMapAdd;
extern XTOUCH xTouchFriendMapPre;
extern XTOUCH xTouchFriendMapNext;

extern XTOUCH xTouchFriendMapMail;
extern XTOUCH xTouchFriendMapMail2;
extern XTOUCH xTouchFriendMapModel;




extern XTOUCH xTouchEventIcon;
extern XTOUCH xTouchWorldMapTrendIcon;
extern XTOUCH xTouchWorldMapInShopPerIcon;
extern XTOUCH xTouchWorldMapFashionShow;
extern XTOUCH xTouchWorldMapKakao;


extern XTOUCH xTouchWorldMapTired;
extern XTOUCH xTouchFittingMenu[4];

extern XTOUCH xTouchFittingReset;
extern XTOUCH xTouchFittingSave;
extern XTOUCH xTouchGenderLeft;
extern XTOUCH xTouchGenderRight;

extern XTOUCH xTouchSellInput;

extern XTOUCH xTouchSellCancel[SELLSLOTMAX];
extern XTOUCH xTouchSellFast[SELLSLOTMAX];

extern XTOUCH xTouchSellSlot[SELLSLOTMAX];

extern XTOUCH xTouchSelectBtn;
extern XTOUCH xTouchMake;
extern XTOUCH xTouchBuy;
extern XTOUCH xTouchAllBuy;

extern XTOUCH xTouchProductionFastCash;
extern XTOUCH xTouchProductionPush;
extern XTOUCH xTouchProductionCancel;


extern XTOUCH xTouchBuildIconOk;
extern XTOUCH xTouchBuildIconClr;
extern XTOUCH xTouchBuildIconMove;
extern XTOUCH xTouchBuildIconMoveObj;
extern XTOUCH xTouchBuildIconInven;
extern XTOUCH xTouchBuildIconRot;

///////////////////////////////////////////
//인테리어 체크 여부 KBY
extern bool isTouchBuildIconOk;
extern bool isTouchBuildIconClr;
extern bool isTouchBuildIconMove;
extern bool isTouchBuildIconMoveObj;
extern bool isTouchBuildIconInven;
extern bool isTouchBuildIconRot;
///////////////////////////////////////////

///////////////////////////////////////////
//사진 등록 터치 여부 KBY
extern bool isTouchPhotoSelect;
extern bool isTouchPhotoDel;
extern bool isTouchPhotoClr;
///////////////////////////////////////////

extern XTOUCH xTouchPlayerInfoIcon;


extern XDRAGSCROLL xDragScrollSellSelectItemSlot;


extern XDRAGSCROLL xDragScrollProductionSlot;



extern XDRAGSCROLL xDragScrollFriendSlot;

extern XDRAGSCROLL xDragScrollCarStorageSlot;
extern XDRAGSCROLL xDragScrollDeliverySlot;


extern XDRAGSCROLL xDragScrollInteriorS;


extern XDRAGSCROLL xDragScrollCatalogS;
extern XDRAGSCROLL xDragScrollFittingS;


extern XTOUCH xTouchSellSelectItemSlot[10];
extern XTOUCH xTouchSellSelectItemSlotInfo[10];

extern XTOUCH xTouchDelivery[20];


extern XTOUCH xTouchInteriorTabB[8];
extern XTOUCH xTouchInteriorTabS[12];
extern XTOUCH xTouchInteriorS[32];

extern XTOUCH xTouchCatalogTabB[5];
extern XTOUCH xTouchCatalogTabS[12];

extern XTOUCH xTouchCatalogS[10];
extern XTOUCH xTouchCatalogDel[10];
extern XTOUCH xTouchCatalogSInfo[10];

extern XTOUCH xTouchCatalogSYes[10];
extern XTOUCH xTouchCatalogSNo[10];

extern XTOUCH xTouchOrderMakeBtn[10];


extern XTOUCH xTouchFittingTabB[15];
extern XTOUCH xTouchFittingS[10];

extern XTOUCH xTouchInteriorBtn[4][2];


extern XTOUCH xTouchWorldMapFriendIcon;
extern XTOUCH xTouchWorldMapMainMenuIcon;

extern XTOUCH xTouchWorldMapMoneyIcon;
extern XTOUCH xTouchWorldMapCashIcon;
extern XTOUCH xTouchWorldMapItemShop;
extern XTOUCH xTouchWorldMapCandyIcon;

extern XTOUCH xTouchCandyFormer;

//맵데이터 타입갯수
#define MAPMAX		10
#define MAPDATAXMAX	100
#define TILEW			64
#define TILEH			32

///////////////////////////////////////////////맵데이터에서 관리하는 레이어이야 인테리어 카테고리와 헷갈리지 말자//////////////////////////////
#define MAP_TYPE_FLOORTILE0		0
#define MAP_TYPE_FLOORTILE1		1
#define MAP_TYPE_WALL0			2
#define MAP_TYPE_WALL1			3
#define MAP_TYPE_OBJ			4
#define MAP_TYPE_PROPERTY		5
#define MAP_TYPE_WORLDSTOP		6

#define MAP_TYPE_MOVE			7
#define MAP_TYPE_STATICNPC		8
#define MAP_TYPE_SHOPNPC		9
#define MAP_TYPE_NPC			10
#define MAP_TYPE_CAR			11
#define MAP_TYPE_SHOPASSISTANT			12
#define MAP_TYPE_PAYMENTASSISTANT		13

#define MAP_TYPE_CARPARK			14
#define MAP_TYPE_MODELNPC			15

#define MAP_TYPE_BEST				16
#define MAP_TYPE_SONG				17

#define MAP_TYPE_ITEMSHOPOBJ		18
#define MAP_TYPE_RUNWAYOBJ			19
#define MAP_TYPE_TVOBJ				20
#define MAP_TYPE_MAPOBJ0			21
#define MAP_TYPE_MAPOBJ1			22
#define MAP_TYPE_MAIL				23
#define MAP_TYPE_MAPOBJ2			24
#define MAP_TYPE_WASTE				25

////////////////////////////////////////카테고리////////////////////////////////////////////
#define INTERIOR_TYPE_PAYMENT		0		//계산대
#define INTERIOR_TYPE_FITTINGROOM 	1		//피팅룸
#define INTERIOR_TYPE_HANGER		2		//옷걸이
#define INTERIOR_TYPE_ACCESSORY 	3		//진열대
#define INTERIOR_TYPE_PRODUCTION 	4		//생산
#define INTERIOR_TYPE_SHOWWINDOW	5		//쇼윈도
#define INTERIOR_TYPE_OBJ			6		//오브젝트
#define INTERIOR_TYPE_WALLITEM		7		//벽장식
#define INTERIOR_TYPE_DOOR			8		//문
#define INTERIOR_TYPE_FLOORTILE		9		//타일
#define INTERIOR_TYPE_WALLTILE		10		//벽타일
#define INTERIOR_TYPE_WORLDMAP		11		//월드맵
#define INTERIOR_TYPE_OBJFLOOR		12		//바닥타일2


/////////////////////////////////////////////////////////////////////////////////////////

#define SHOPMAPDATAMAX			5
#define SHOPMAP_TYPE_MOVE		0
typedef struct
{
	M_Int32 totalTileX;
	M_Int32 totalTileY;
	
	M_Int32 shopPointX;
	M_Int32 shopPointY;
	M_Int32 shopPointW;
	M_Int32 shopPointH;
	
	M_Int32 pointClipX;
	M_Int32 pointClipY;
	M_Int32 pointCy;
	M_Int32 pointCx;
	
	M_Int32 pointX;
	M_Int32 pointY;
		
	M_Int32 selectX;
	M_Int32 selectY;
	
	int data[FLOORMAX][MAPMAX][MAPDATAXMAX][MAPDATAXMAX];
	int dataKey[FLOORMAX][MAPMAX][MAPDATAXMAX][MAPDATAXMAX];
	
	int shopData[FLOORMAX][SHOPMAPDATAMAX][MAPDATAXMAX][MAPDATAXMAX];
	
	int interiorData[FLOORMAX][MAPDATAXMAX][MAPDATAXMAX];
	int interiorDataWall[FLOORMAX][2][MAPDATAXMAX];	//[xy][줄]
	
	int worldMapNpc[MAPDATAXMAX][MAPDATAXMAX];	//npc위치파악용
	
	int totalFloor;
	int nowFloor;
	int extension;
	M_Boolean isOpen[FLOORMAX];
	
	//////////그냥 자주쓰이는 지역변수
	int rever;
	int abxMapData;
	int type;
	int listNum;
	float speedTable[10];
	
	int floorInitCode[FLOORMAX];
	int wallInitCode[FLOORMAX];
	int tileInitW;
	int tileInitH;
    
    
    XTOUCH xTouchTile[FLOORMAX][MAPDATAXMAX][MAPDATAXMAX];
} XMAP;
extern XMAP xMap;

//오브젝트정보
#define OBJMAX			13
#define OBJDATAMAX		512
typedef struct 
{
	int x[2];
	int y[2];
	int w[2];
	int h[2];
	SECURITY price;
	int priceType;
	int slot;
	int thema;
	int lv;
	int fame;
    int special;
    int specialType;
    int specialCount;
    int specialTime;
	M_Boolean isChair;
	char strName[128];
	int productionType;
	M_Boolean isRotLock;
} XOBJDATA;


typedef struct 
{
	int totalNum[OBJMAX];
	
    
	M_Boolean isImgUse[OBJMAX][OBJDATAMAX];
	
	XIMG img[OBJMAX][OBJDATAMAX];
	XIMG imgDoorOpen[OBJDATAMAX];
	XIMG imgFittingRoomOpen[OBJDATAMAX];
	XIMG imgShowWindowTop[OBJDATAMAX];
	XIMG imgHangerLayer[OBJDATAMAX];
	XIMG imgAccessoryLayer[OBJDATAMAX][3];
	XIMG imgWallTop[OBJDATAMAX];
	
	XOBJDATA xObjData[OBJMAX][OBJDATAMAX];
   
} XOBJ;
extern XOBJ xObj;




////////////////////////타일선택이펙트/////////////////////
#define SELECTTILEMAX				10
#define SELECTTILE_STATE_DONT		0
#define SELECTTILE_STATE_PLAY		1

typedef struct
{
	M_Int32 state;
	
	M_Int32 tileNumX;		
	M_Int32 tileNumY;	
	M_Int32 selectType;
	M_Int32 anyCnt;	
	M_Int32 npcCode;	
	M_Int32 carCode;	
	
} XSELECTTILE;

extern XSELECTTILE xSelectTileOne;





////////////////////////정렬/////////////////////
#define OBJSORTMAX		1024
typedef struct
{
	
	int totalNum;
	M_Boolean isEventItem[OBJSORTMAX];
	M_Boolean isBuildItem[OBJSORTMAX];
	M_Boolean isEventQueue[OBJSORTMAX];
	int interiorNum[OBJSORTMAX];
	int	viewType[OBJSORTMAX];
	int	code[OBJSORTMAX];
	int	codeSub[OBJSORTMAX];
	int x[OBJSORTMAX];
	int y[OBJSORTMAX];
	int drawX[OBJSORTMAX];
	int drawY[OBJSORTMAX];
	M_Boolean isDraw[OBJSORTMAX];	
} XOBJSORT;
extern XOBJSORT xObjSort[4];

#define EVENTITEM_TYPE_FLOORUP		0
#define EVENTITEM_TYPE_FLOORDOWN	1

////////////////////////샵 NPC/////////////////////
#define SHOPNPCMAX		64

#define SHOPNPC_STATE_DONT		0
#define SHOPNPC_STATE_MOVE		1
#define SHOPNPC_STATE_WAIT		2
#define SHOPNPC_STATE_EMPTY		3
#define SHOPNPC_STATE_ASTARERR	4

#define SHOPNPC_STATE_TABLESEE					5	//보기
#define SHOPNPC_STATE_TABLEBUY					6	//구매

#define SHOPNPC_STATE_FITTINGROOM				8
#define SHOPNPC_STATE_FITTINGROOM_OPEN_IN		9
#define SHOPNPC_STATE_FITTINGROOM_CLOSE_WAIT	10
#define SHOPNPC_STATE_FITTINGROOM_OPEN_OUT		11

#define SHOPNPC_STATE_PAYMENTWAIT				12	//계산대기
#define SHOPNPC_STATE_PAYMENT					13		//계산중

#define SHOPNPC_STATE_LOOKINGMIRROR				14
#define SHOPNPC_STATE_CALLSHOPASSISTANT			15	//호출중(무한검색)
#define SHOPNPC_STATE_CALLSHOPASSISTANTWAIT		16	//호출대기중(올때까지 대기)

#define SHOPNPC_STATE_CALLSHOPASSISTANT_RCMD		17
#define SHOPNPC_STATE_CALLSHOPASSISTANTWAIT_RCMD	18

#define SHOPNPC_STATE_FLOORUPMOVE		19
#define SHOPNPC_STATE_FLOORUP			20
#define SHOPNPC_STATE_FLOORDOWNMOVE		21
#define SHOPNPC_STATE_FLOORDOWN			22

#define SHOPNPC_STATE_ETC				23


#define SHOPNPC_STATE_CHAIR_SIT			24	//앉기
#define SHOPNPC_STATE_CHAIR_ACT			25	//행동
#define SHOPNPC_STATE_CHAIR_WAIT		26	//요청대기
#define SHOPNPC_STATE_CHAIR_STANDUP		27	//일어나기
#define SHOPNPC_STATE_CHAIR_EVENTFAIL	28	//일어나서 짜증내기

#define SHOPNPC_STATE_PORTER_WM_WOMAN_TYPE0_0	29	//여자 의상 몸에 대보기
#define SHOPNPC_STATE_PORTER_WM_WOMAN_TYPE0_1	30	//남자 대사중 잠시대기
#define SHOPNPC_STATE_PORTER_WM_WOMAN_TYPE0_2	31	//여자화내기


#define SHOPNPC_STATE_PORTER_WM_WOMAN_TYPE1_0	32	//여자 의상 몸에 대보기
#define SHOPNPC_STATE_PORTER_WM_WOMAN_TYPE1_1	33	//남자 대사중 잠시대기

#define SHOPNPC_STATE_PORTER_WM_MAN_WAIT		34
#define SHOPNPC_STATE_PORTER_WM_MAN_TYPE0_0	35
#define SHOPNPC_STATE_PORTER_WM_MAN_TYPE1_0	36

#define SHOPNPC_STATE_PORTER_WM_MAN_TIRED		37



////////////////////////////////////남남
#define SHOPNPC_STATE_PORTER_MM_WOMAN_TYPE1_0	38	//주인 의상 몸에 대보기
#define SHOPNPC_STATE_PORTER_MM_WOMAN_TYPE1_1	39	//남자 대사중 잠시대기

#define SHOPNPC_STATE_PORTER_MM_MAN_TYPE1_0		40	//남자 대사중
////////////////////////////////////
///////////////////////////////////여여
#define SHOPNPC_STATE_PORTER_WW_WOMAN_TYPE1_0	41	//주인 의상 몸에 대보기
#define SHOPNPC_STATE_PORTER_WW_WOMAN_TYPE1_1	42	//주인 의상 몸에 대보기


#define SHOPNPC_STATE_PORTER_WW_MAN_TYPE1_0		43	//남자 대사중
//////////////////////////////////////




#define MOVETYPE_XPLUS		0
#define MOVETYPE_XMINUS		1
#define MOVETYPE_YPLUS		2
#define MOVETYPE_YMINUS		3



#define NPC_BUYACT_SELLTABLE		0
#define NPC_BUYACT_TREND			1
#define NPC_BUYACT_FITTING			2
#define NPC_BUYACT_FITTINGROOM		3
#define NPC_BUYACT_LOOKINGMIRROR	4
#define NPC_BUYACT_PAYMENT			5
#define NPC_BUYACT_EXIT				6
#define NPC_BUYACT_CHAIR			7


typedef struct
{
	int	state;

	int anyCnt;
	int imgCnt;
	int	type;	
	int	x;
	int	y;
	int	x_befor;
	int	y_befor;
	float drawX;
	float drawY;	
	float speed;
	int	moveType;
	int	beforMoveType;
	
	int floorTarget;
	int floor;
	
	
	XSPEAK xSpeak;
	XFACE xFace;
	XFITTINGLAYER xF;
	int nowFrame;
	int nowDelay;
	M_Boolean isActEnd;
	int actingType;
	
	
	
	int bestTotalCnt;
	int bestNowCnt;
	int bestX[128];
	int bestY[128];
		
	M_Int32 buyAct;
	M_Boolean isBuyAct[10];
	M_Int32 actXpos;
	M_Int32 actYpos;
	M_Int32 actLook;	//바라보는방향
	M_Int32 actInteriorNum;
	
	
	int	buyItemCode;				//실제 들고있는 물품
	int	buyItemCode_ASSISTCALL;		//요청한 물품
	
	int inOutCnt;
	
	
	M_Boolean isSitEventBox;
	M_Boolean isSitEventFail;
	
	M_Boolean payMentEvent;
	M_Int64 payMentTime;
	int payMentType;
	
	
	M_Boolean isTrendEvent;
		
	
	
	M_Boolean isFloorExit;		//층간이동시 사용
		
	int	genDer;
	

	int modelNum;
	int eventBoxShowAntCnt;
		
	XEMOTICON xEmoticon;
	
	XGLITTEREFF xGlitterEff[GLITTEREFFMAXSUB];
	
	
	int actCount;
	int subAct;
	
	int etcAct;
	int etcAct_BackUp;
	
	
	//의자관련
	M_Boolean isChair;
	int chairNum;
	M_Boolean isEventBox;
	int eventBoxAnyCnt;

	
	
	//짐꾼관련
	M_Boolean isPorter_woman;
	M_Boolean isPorter_man;
	int porterNpcNum;
	int porterOptionType;
	int porterOptionTypeSub;
	
	
	///////////AI변경부분///////////
	int buyType20;
	int buySex20;
	int buyFtype;
	

	int imgEventBox;
	
	M_Boolean isFittingRoom;	
	
} XSHOPNPC;
extern XSHOPNPC xShopNpc[SHOPNPCMAX];


///////////////////////모델NPC//////////////////////
#define MODELNPCMAX		10
#define MODELNPC_STATE_DONT			0
#define MODELNPC_STATE_WAIT			1
#define MODELNPC_STATE_WAITMOVE		2

#define MODELNPC_STATE_FLOORUPMOVE		3
#define MODELNPC_STATE_FLOORUP			4
#define MODELNPC_STATE_FLOORDOWNMOVE	5
#define MODELNPC_STATE_FLOORDOWN		6

#define MODELNPC_STATE_ASTARERR			7

#define MODELNPC_STATE_INTERIORINFOMOVE		8
#define MODELNPC_STATE_INTERIORINFO			9


typedef struct
{
	int	state;
	int anyCnt;
	int mainSlotNum;
	int invenNum;

	int floorTarget;
	int floor;
	
	int	makeX;
	int	makeY;
	
	int x;
	int y;
	float drawX;
	float drawY;
	float speed;
	int	moveType;
	int nowDelay;
	int nowFrame;
	
	
	int bestTotalCnt;
	int bestNowCnt;
	int bestX[128];
	int bestY[128];
	
	int actingType;
	M_Boolean isActEnd;
	
	XSPEAK xSpeak;
	
	int actLook;
	
	////////////////////인테리어소개
	int interiorInfoCnt;
	int interiorInfoType;
	
	M_Boolean isEventBox;
	int eventBoxAnyCnt;
	int eventBoxShowAntCnt;
	XGLITTEREFF xGlitterEff[GLITTEREFFMAXSUB];
	
	int imgEventBox;
	
} XMODELNPC;
extern XMODELNPC xModelNpc[MODELNPCMAX];


////////////////////////점원 NPC/////////////////////
#define SHOPASSISTANTMAX		1


#define SHOPASSISTANT_STATE_DONT			0
#define SHOPASSISTANT_STATE_WAIT			1
#define SHOPASSISTANT_STATE_SELLTABLEMOVE	2
#define SHOPASSISTANT_STATE_SHOPNPCMOVE		3
#define SHOPASSISTANT_STATE_WAITMOVE		4
#define SHOPASSISTANT_STATE_SELLTABLE		5
#define SHOPASSISTANT_STATE_SHOPNPC			6

#define SHOPASSISTANT_STATE_ORDERINGMOVE	7
#define SHOPASSISTANT_STATE_ORDERING		8
#define SHOPASSISTANT_STATE_ORDERING2		9


#define SHOPASSISTANT_STATE_RCMDMOVE		10
#define SHOPASSISTANT_STATE_RCMD			11


typedef struct
{
	int	state;
	
	int anyCnt;
	int imgCnt;
	int	type;
	int	makeX;
	int	makeY;
	int	shopNpcNum;
	int	sellTableNum;
	int	x;
	int	y;
	float drawX;
	float drawY;
	float speed;
	int	moveType;
	int	beforMoveType;
	
	char strName[64];
	XSPEAK xSpeak;
	XFACE xFace;
	XFITTINGLAYER xF;
	M_Boolean isActEnd;
	int gender;
	int actingType;
	int nowDelay;
	int nowFrame;
	
	int bestTotalCnt;
	int bestNowCnt;
	int bestX[128];
	int bestY[128];
	
	int actLook;
	
	int buyItemCode;
	
} XSHOPASSISTANT;
extern XSHOPASSISTANT xShopAssistant[FLOORMAX][SHOPASSISTANTMAX];



////////////////////////점원 NPC/////////////////////
#define PAYMENTASSISTANT_STATE_DONT		0
#define PAYMENTASSISTANT_STATE_WAIT		1
#define PAYMENTASSISTANT_STATE_DANCE	2
#define PAYMENTASSISTANT_STATE_PHONE	3
#define PAYMENTASSISTANT_STATE_FASHIONCHECK	4

#define PAYMENTASSISTANT_STATE_PLAY		5

#define PAYMENTASSISTANTSHOPNPCSLOT		64

typedef struct
{
	int npcNum;
} XSHOPNPCSLOT;


typedef struct
{
	int	state;
	int	x;
	int	y;
	float drawX;
	float drawY;
	int moveType;
	
	char strName[64];
	
	float PayMentPosX;
	float PayMentPosY;

	XSPEAK xSpeak;
	XFACE xFace;
	XFITTINGLAYER xF;
	M_Boolean isActEnd;
	int gender;
	int actingType;
	int nowDelay;
	int nowFrame;
	
	
	int	payMentCntMax;
	int	payMentCntNow;
	
	int	totalSlot;
	int	selectSlot;
	XSHOPNPCSLOT xShopNpcSlot[PAYMENTASSISTANTSHOPNPCSLOT];
	
	
	int waitAnyCnt;
	
} XPAYMENTASSISTANT;
extern XPAYMENTASSISTANT xPaymentAssistant[FLOORMAX];
////////////////////////월드맵 NPC/////////////////////
#define WORLDMAPNPCMAX		64

#define WORLDMAPNPC_STATE_DONT		0
#define WORLDMAPNPC_STATE_MAKE		1
#define WORLDMAPNPC_STATE_MOVE		2
#define WORLDMAPNPC_STATE_DIE		3
#define WORLDMAPNPC_STATE_WAIT		4

#define WORLDMAPNPC_STATE_SEE		5
#define WORLDMAPNPC_STATE_TALKING	6
#define WORLDMAPNPC_STATE_GREETING	7

#define WORLDMAPNPC_STATE_CROSSARMS		8
#define WORLDMAPNPC_STATE_WAVINGHAND	9
#define WORLDMAPNPC_STATE_SMILE			10

#define WORLDMAPNPC_STATE_ETC			11

#define WORLDMAPNPC_STATE_WATCH			12
#define WORLDMAPNPC_STATE_PHONE			13



#define WORLDMAPNPC_EVENT_XPLUS_STOP	-5
#define WORLDMAPNPC_EVENT_XMINUS_STOP	-6
#define WORLDMAPNPC_EVENT_YPLUS_STOP	-7
#define WORLDMAPNPC_EVENT_YMINUS_STOP	-8


#define WORLDMAPNPC_EVENT_DIE		3
#define WORLDMAPNPC_EVENT_INSHOP	4		//y진입4 x진입-4
#define WORLDMAPNPC_EVENT_XPLUS		5
#define WORLDMAPNPC_EVENT_XMINUS	6
#define WORLDMAPNPC_EVENT_YPLUS		7
#define WORLDMAPNPC_EVENT_YMINUS	8
#define WORLDMAPNPC_EVENT_XMINUS_YMINUS		9
#define WORLDMAPNPC_EVENT_XPLUS_YMINUS		10
#define WORLDMAPNPC_EVENT_XPLUS_YPLUS		11
#define WORLDMAPNPC_EVENT_XMINUS_YPLUS		12


#define BUY_TYPE20_SEX			0
#define BUY_TYPE20_SELLTABLE	1
#define BUY_TYPE20_TREND		2
#define BUY_TYPE20_RANDOM		3
#define BUY_TYPE20_FITTING		4

typedef struct
{
	int	state;
	int anyCnt;
	int imgCnt;
	int	type;	
	int	x;
	int	y;
	float drawX;
	float drawY;	
	float speed;
	int	moveType;
	int	beforMoveType;
	
	
	int	genDer;
	M_Boolean isFittingRoom;
	XFACE xFace;
	XFITTINGLAYER xF;
	int nowFrame;
	int nowDelay;
	M_Boolean isActEnd;
	int actingType;

		
		
	int moveTurnCnt;
	int actingNum;
	M_Boolean isActingTurn;
		
	
	M_Boolean isInShop;
	M_Boolean isOutShop;
	
	int buyItemCode;
	
	

	int modelNum;

	XEMOTICON xEmoticon;
	
	XGLITTEREFF xGlitterEff[GLITTEREFFMAXSUB];
	
	int etcAct;
	
	M_Boolean isDie;
	int dieCnt;
	
} XWORLDMAPNPC;
extern XWORLDMAPNPC xWorldMapNpc[WORLDMAPNPCMAX];


////////////////////////고정NPC/////////////////////
#define STATICNPCMAX		30

#define STATICNPC_GUITAR	0
#define STATICNPC_SONG		1

typedef struct
{
	int nowDelay;
	int nowFrame;
	
	int hairNum;
	int faceNum;
	XFITTINGLAYER xF;
	

} XSTATICNPC;
extern XSTATICNPC xStaticNpc[STATICNPCMAX];


////////////////////////월드맵 자동차/////////////////////
#define WORLDMAPCARMAX				7

#define WORLDMAPCAR_STATE_DONT		0
#define WORLDMAPCAR_STATE_MOVE		1
#define WORLDMAPCAR_STATE_WAIT		2


#define WORLDMAPCAR_MAKEPOSX		17
#define WORLDMAPCAR_MAKEPOSY		48

#define WORLDMAPCAR_MAKEPOSX_2		54
#define WORLDMAPCAR_MAKEPOSY_2		24

typedef struct
{
	int	state;
	int anyCnt;
	int imgCnt;
	int	type;	
	int	x;
	int	y;
	float drawX;
	float drawY;	
	float speed;
	int	moveType;
	
	
	
	
	
} XWORLDMAPCAR;
extern XWORLDMAPCAR xWorldMapCar[WORLDMAPCARMAX];








#define SWITCHMAX      10

#define SWITCH_STATE_OFF    0
#define SWITCH_STATE_ON     1
#define SWITCH_STATE_OFFANY 2
#define SWITCH_STATE_ONANY  3
typedef struct
{
    M_Int32 state;
    M_Int32 anyCnt;
	
	M_Int32 textAlpha[SWITCHMAX];
    M_Int32 clickAnyCnt[SWITCHMAX];
    XTOUCH xTouch[SWITCHMAX];
	
	M_Int32 closeCnt;
} XSWITCH;


/////////////////////////////////////이벤트큐/////////////////////////////
#define BONUSEFFMAX		10
#define BONUSEFF_STATE_DONT		0
#define BONUSEFF_STATE_PLAY		1

#define ICON_TYPE_EXP		0
#define ICON_TYPE_FAME		1
#define ICON_TYPE_GOLD		2
#define ICON_TYPE_LOOK		3
#define ICON_TYPE_TIME		4
#define ICON_TYPE_FASHION_HANGER	5
#define ICON_TYPE_CANDY				6
#define ICON_TYPE_FASHION_ACCESSORY	7

#define ICON_TYPE_MILEAGE				8

typedef struct
{
    M_Int32 state;
	M_Int32 anyCnt;
	M_Int32 type;
	M_Int32 num;
	M_Int32 x;
	M_Int32 y;
	
} XBONUSEFF;
extern XBONUSEFF xBonusEff[BONUSEFFMAX];


#define BLINKEFFMAX			150

#define BLINKEFF_STATE_DONT			0
#define BLINKEFF_STATE_PLAY			1
typedef struct
{
	int totalNum;

	M_Int32 anyCnt[BLINKEFFMAX];
	M_Int32 anyCntMax[BLINKEFFMAX];
	
	float fx[BLINKEFFMAX];
	float fy[BLINKEFFMAX];
	float fspeedY[BLINKEFFMAX];
	float frot[BLINKEFFMAX];
	float fspeedRot[BLINKEFFMAX];
	int scale[BLINKEFFMAX];
	
} XBLINKEFF;
extern XBLINKEFF xBlinkEff;



/////////////////////////////////////npc피팅데이타테이블/////////////////////////////
#define NPCSETMAX			100
typedef struct
{	
	M_Int32 hairTotalNum[2];
	M_Int32 hairCode[2][10];
	
	M_Int32 totalNum[2];	//총가짓수
	M_Int32 slot[2][64];	//타입
	
	M_Int32 gender[NPCSETMAX];
	M_Int32 lvMin[NPCSETMAX];
	M_Int32 lvMax[NPCSETMAX];
    M_Int32 code[NPCSETMAX][7];
	M_Boolean isFittingRoom[NPCSETMAX];
	
	int total;
		
} XNPCSET;
extern XNPCSET xNpcSet;


typedef struct
{
	int total[2];
	M_Int32 gender[2][NPCSETMAX];
	M_Int32 hair[2][NPCSETMAX];
	M_Int32 face[2][NPCSETMAX];
	M_Int32 code[2][NPCSETMAX][7];
	
	
	
	
	M_Int32 totalSong;
	M_Boolean isSongOpen[10];
	M_Int32 songSlot[10];
	char strSongTitle[10][64];
	M_Int32 songPriceType[10];
	M_Int32 songPrice[10];
	int selectSong;
	int selectSongTemp;
} XSONGSET;
extern XSONGSET xSongSet;


/////////////////////////////////////이벤트큐/////////////////////////////
#define EVENTQUEUE_TYPE_INTERIOR		0
#define EVENTQUEUE_TYPE_INPUTINVEN		1
#define EVENTQUEUE_TYPE_OUTPUTINVEN		2
#define EVENTQUEUE_TYPE_MOVE			3
#define EVENTQUEUEMAX		256
typedef struct
{
    M_Int32 totalNum;
	M_Int32 anyCntMax[EVENTQUEUEMAX];
	M_Int32 anyCnt[EVENTQUEUEMAX];
	M_Int32 type[EVENTQUEUEMAX];
	M_Int32 floor[EVENTQUEUEMAX];
	M_Int32 x[EVENTQUEUEMAX];
	M_Int32 y[EVENTQUEUEMAX];
	M_Int32 startX[EVENTQUEUEMAX];
	M_Int32 startY[EVENTQUEUEMAX];
	XINTERIORSLOT xInteriorSlot[EVENTQUEUEMAX];
	
} XEVENTQUEUE;

extern XEVENTQUEUE xEventQueue;
////////////////////////////////////////////////////////////////////////


#define NETQUEUE_TYPE_GAMEINFO					0
#define NETQUEUE_TYPE_FASHION					1
#define NETQUEUE_TYPE_INTERIOR					2
#define NETQUEUE_TYPE_MAP						3
#define NETQUEUE_TYPE_SELLTABLE					4
#define NETQUEUE_TYPE_SHOWWINDOW				5
#define NETQUEUE_TYPE_STAFF						6
#define NETQUEUE_TYPE_FACE						7
#define NETQUEUE_TYPE_TREND						8
#define NETQUEUE_TYPE_CAR						9
#define NETQUEUE_TYPE_ADDORDER					10
#define NETQUEUE_TYPE_ORDER						11
#define NETQUEUE_TYPE_CARPARK					12
#define NETQUEUE_TYPE_ORDEROK					13
#define NETQUEUE_TYPE_DELRECVORDER				14
#define NETQUEUE_TYPE_FRIENDIMGDOWNLOAD			15
#define NETQUEUE_TYPE_FLOOR						16
#define NETQUEUE_TYPE_GETFRIENDLIST				17
#define NETQUEUE_TYPE_GETFRIENDSEARCH			18
#define NETQUEUE_TYPE_ADDFRIEND					19
#define NETQUEUE_TYPE_DELFRIEND					20
#define NETQUEUE_TYPE_FRIENDSOCIAL				21
#define NETQUEUE_TYPE_DELCLEAN					22
#define NETQUEUE_TYPE_LVUP						23
#define NETQUEUE_TYPE_TODAY						24
#define NETQUEUE_TYPE_SENDMAIL					25
#define NETQUEUE_TYPE_MAILLIST					26
#define NETQUEUE_TYPE_DELMAIL					27
#define NETQUEUE_TYPE_MINIPROFILE				28
#define NETQUEUE_TYPE_SENDGIFT					29
#define NETQUEUE_TYPE_GIFTLIST					30
#define NETQUEUE_TYPE_DELGIFT					31
#define NETQUEUE_TYPE_QUEST						32
#define NETQUEUE_TYPE_TILE						33
#define NETQUEUE_TYPE_MODELTOTALSLOT			34
#define NETQUEUE_TYPE_SETMODEL					35

#define NETQUEUE_TYPE_MODELGROUPGIFT			37
#define NETQUEUE_TYPE_GETFASHIONSHOWINFO		38
#define NETQUEUE_TYPE_GETMODELLIST				39
#define NETQUEUE_TYPE_MODELVOTE					40

#define NETQUEUE_TYPE_SETMODELMAIN				41




#define NETQUEUE_TYPE_SETFASHIONSHOW			43

#define NETQUEUE_TYPE_GETFASHIONSHOWRANK		44
#define NETQUEUE_TYPE_VOTE						45
#define NETQUEUE_TYPE_EXTERNALWALL				46

#define NETQUEUE_TYPE_SELLTABLEUPDATA			53

#define NETQUEUE_TYPE_ORDERRECVLIST				54
#define	NETQUEUE_TYPE_ORDERLIST					55

#define	NETQUEUE_TYPE_RANDOMFRIEND				56
#define NETQUEUE_TYPE_NOTICEIMGDOWNLOAD			57

#define NETQUEUE_TYPE_GETFRIENDMODEL			59
#define NETQUEUE_TYPE_SETPUSH					60
#define NETQUEUE_TYPE_RESETSOCIAL				61
#define NETQUEUE_TYPE_SETACCESS					62
#define NETQUEUE_TYPE_KAKAOPHOTOINIT			64
#define NETQUEUE_TYPE_PROFILEPHOTOUPLOAD			65
#define NETQUEUE_TYPE_KAKAOINVITE				66

#define NETQUEUE_TYPE_BILL						67
#define NETQUEUE_TYPE_ADDFRIENDID					68
#define NETQUEUE_TYPE_SETSOUND					69
#define NETQUEUE_TYPE_SETETC					70

#define NETQUEUE_TYPE_GETPMDATA					71
#define NETQUEUE_TYPE_BUYGOLD					72


#define NETQUEUE_TYPE_COUPON					73
#define NETQUEUE_TYPE_HACKINGCHECK					74

#define NETQUEUE_TYPE_TIMEHACKING					75

#define NETQUEUE_TYPE_KAKAOHELP						76


#define NETQUEUE_TYPE_ALICESHOCK_GETLIST			77
#define NETQUEUE_TYPE_ALICESHOCK_CLICK				78
#define NETQUEUE_TYPE_ALICESHOCK_LOOKSHOW			79
#define NETQUEUE_TYPE_ALICESHOCK_LOOKOK				80

#define NETQUEUE_TYPE_ALICESHOCK_LOOKOK				81


#define NETQUEUE_TYPE_ALICESHOCK_PHOTO				82

#define NETQUEUE_TYPE_G9EVENT				83

#define NETQUEUE_TYPE_MILEAGESHOPCOUNT				84

#define NETQUEUE_TYPE_MILEAGESHOPBUY				85
#define NETQUEUE_TYPE_MILEAGESHOPINFO				86

#define NETQUEUE_TYPE_MILEAGESHOPUPDATE				87


#define NETQUEUE_TYPE_PRODUCTIONSTART				88
#define NETQUEUE_TYPE_PRODUCTIONCANCLE				89
#define NETQUEUE_TYPE_PRODUCTIONFASTPOP				90
#define NETQUEUE_TYPE_PRODUCTIONCOMPLETE            91
#define NETQUEUE_TYPE_PRODUCTIONOPEN            92


#define NETQUEUE_TYPE_SELLSTART				93
#define NETQUEUE_TYPE_SELLCANCLE				94
#define NETQUEUE_TYPE_SELLFASTPOP				95
#define NETQUEUE_TYPE_SELLCOMPLETE            96

#define NETQUEUE_TYPE_PREPAYBUY				97
#define NETQUEUE_TYPE_PREPAYDAY				98

#define NETQUEUE_TYPE_PACKAGEBUY				99
#define NETQUEUE_TYPE_PACKAGELIST				100



#define NETQUEUE_TYPE_EVENTQUESTMAINLIST				101
#define NETQUEUE_TYPE_EVENTQUESTMAINCOMPLETE				102
#define NETQUEUE_TYPE_EVENTQUESTDETAILLIST				103
#define NETQUEUE_TYPE_EVENTQUESTDETAILUPDATE				104
#define NETQUEUE_TYPE_EVENTQUESTDETAILCOMPLETE				105



#define NETQUEUE_TYPE_HOTDEALMAINLIST       106
#define NETQUEUE_TYPE_HOTDEALDETAILLIST     107
#define NETQUEUE_TYPE_HOTDEALMAINOPEN       108
#define NETQUEUE_TYPE_HOTDEALDETAILOPEN     109
#define NETQUEUE_TYPE_HOTDEALDETAILBUY      110


#define NETQUEUE_TYPE_RIVALLIST             111
#define NETQUEUE_TYPE_RIVALSTART            112
#define NETQUEUE_TYPE_RIVALSTOP             113
#define NETQUEUE_TYPE_RIVALUPDATE           114
#define NETQUEUE_TYPE_RIVALCOMPLETE         115



#define NETQUEUE_TYPE_SOCIALLIST            116


#define NETQUEUE_TYPE_SETDEVICEID            117

#define NETQUEUE_TYPE_BOOKMARK            118

#define NETQUEUE_TYPE_JEWELQUESTLIST            119
#define NETQUEUE_TYPE_JEWELQUESTUPDATE            120
#define NETQUEUE_TYPE_JEWELQUESTCOMPLETE            121


#define NETQUEUE_TYPE_AMULETLIST            122
#define NETQUEUE_TYPE_AMULETUPDATE            123

#define NETQUEUE_TYPE_AMULETBUY            124
#define NETQUEUE_TYPE_AMULETBUYLIST            125


#define NETQUEUE_TYPE_AMULETPAGEBUY            126

#define NETQUEUE_TYPE_CLUBLIST            127

#define NETQUEUE_TYPE_CLUBMAKE            128
#define NETQUEUE_TYPE_CLUBJOIN            129
#define NETQUEUE_TYPE_CLUBUNREG            130
#define NETQUEUE_TYPE_CLUBSEARCH            131

#define NETQUEUE_TYPE_CLUBDATA            132
#define NETQUEUE_TYPE_CLUBMEMBER            133

#define NETQUEUE_TYPE_SETCLUBJOINTYPE            134
#define NETQUEUE_TYPE_SETCLUBNOTICE            135
#define NETQUEUE_TYPE_SETCLUBJOININFO            136
#define NETQUEUE_TYPE_SETCLUBFORCEOUT            137
#define NETQUEUE_TYPE_SETCLUBMASTER            138



#define NETQUEUE_TYPE_CLUBJOINLIST              139
#define NETQUEUE_TYPE_CLUBJOINAPPLY             140
#define NETQUEUE_TYPE_CLUBJOINACCEPT            141
#define NETQUEUE_TYPE_CLUBJOINDEL               142


#define NETQUEUE_TYPE_CLUBHISTORYLIST            143
#define NETQUEUE_TYPE_CLUBBOOKLIST               144


#define NETQUEUE_TYPE_CLUBBOOKADD               145
#define NETQUEUE_TYPE_CLUBBOOKDEL               146

#define NETQUEUE_TYPE_CLUBRANKLIST               147


#define NETQUEUE_TYPE_FASHIONWEEKDRESSLIST       148
#define NETQUEUE_TYPE_FASHIONWEEKFITTINGLIST      149



#define NETQUEUE_TYPE_CLUBDRESSBUY              150


#define NETQUEUE_TYPE_FASHIONWEEKFITTINGUPDATE              151

#define NETQUEUE_TYPE_PANGSTART              152

#define NETQUEUE_TYPE_PANGRESULT              153




#define NETQUEUE_TYPE_FASHIONWEEKEXP                154
#define NETQUEUE_TYPE_FASHIONWEEKSCOREUPDATE        155

#define NETQUEUE_TYPE_CLUBSTORAGEUPDATE             156
#define NETQUEUE_TYPE_CLUBITEMBUY                   157
#define NETQUEUE_TYPE_CLUBGIVEGIFT                  158
#define NETQUEUE_TYPE_PANGTIMESRESET                159
#define NETQUEUE_TYPE_CMD_CLUBITEMDELETE            160
#define NETQUEUE_TYPE_CMD_CLUBDONATIONCOUNT         161
#define NETQUEUE_TYPE_CLUBDONATION                  162
#define NETQUEUE_TYPE_CLUBICONLISTUPDATE            163
#define NETQUEUE_TYPE_CLUBICONBUY                   164
#define NETQUEUE_TYPE_CLUBICONUPDATE                165
#define NETQUEUE_TYPE_CLUBNAMEMODIFY                166
#define NETQUEUE_TYPE_PANGCOUNTCHECK                167

#define NETQUEUE_TYPE_FORMERLISTUPDATE              168
#define NETQUEUE_TYPE_FORMERSTART                   169
#define NETQUEUE_TYPE_FORMERTAKEWEALTH              170

#define NETQUEUE_TYPE_AUTOSELL						171
#define NETQUEUE_TYPE_AUTOPRODUCT					172
#define NETQUEUE_TYPE_AUTOPRODUCTSLOTUPDATE			173

#define NETQUEUE_TYPE_PRODUCTIONINFOUPDATE          174
#define NETQUEUE_TYPE_PRODUCTIONSLOTINFOUPDATE      175
#define NETQUEUE_TYPE_PRODUCTIONREGIST              176
#define NETQUEUE_TYPE_PRODUCTIONSLOTOPEN            177
#define NETQUEUE_TYPE_PRODUCTIONDELETE              178
#define NETQUEUE_TYPE_PRODUCTIONSLOTUPDATE          179

#define NETQUEUE_TYPE_SENDMACHINEINFO				NETQUEUE_TYPE_PRODUCTIONSLOTUPDATE + 1
#define NETQUEUE_TYPE_SENDMACHINESLOTINFO			NETQUEUE_TYPE_SENDMACHINEINFO + 1
#define NETQUEUE_TYPE_SENDMACHINESLOTOPEN			NETQUEUE_TYPE_SENDMACHINESLOTINFO + 1
#define NETQUEUE_TYPE_SENDMACHINESLOTUPDATE			NETQUEUE_TYPE_SENDMACHINESLOTOPEN + 1
#define NETQUEUE_TYPE_GETDRESSINFO					NETQUEUE_TYPE_SENDMACHINESLOTUPDATE + 1
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////온실, 물레, 상점관련 EVENTQUEUE KBY
#define NETQUEUE_TYPE_GREENHOUSEINFOUPDATE          NETQUEUE_TYPE_GETDRESSINFO+1
#define NETQUEUE_TYPE_GREENHOUSESLOTINFOUPDATE      NETQUEUE_TYPE_GREENHOUSEINFOUPDATE+1

#define NETQUEUE_TYPE_SPINNINGWHEELINFOUPDATE       NETQUEUE_TYPE_GREENHOUSESLOTINFOUPDATE+1
#define NETQUEUE_TYPE_SPINNINGWHEELSLOTINFOUPDATE   NETQUEUE_TYPE_SPINNINGWHEELINFOUPDATE+1

#define NETQUEUE_TYPE_GETCARROT                     NETQUEUE_TYPE_SPINNINGWHEELSLOTINFOUPDATE+1

#define NETQUEUE_TYPE_GETWARDROBEINFO               NETQUEUE_TYPE_GETCARROT+1
#define NETQUEUE_TYPE_BUYDRESSCHAR                  NETQUEUE_TYPE_GETWARDROBEINFO+1

#define NETQUEUE_TYPE_GETDRESSROOMINFO				NETQUEUE_TYPE_BUYDRESSCHAR + 1
#define NETQUEUE_TYPE_UPDATEMYDRESS					NETQUEUE_TYPE_GETDRESSROOMINFO + 1

//#define NETQUEUE_TYPE_GETDRESSROOMINFO				NETQUEUE_TYPE_GETDRESSINFO + 1
//#define NETQUEUE_TYPE_UPDATEMYDRESS					NETQUEUE_TYPE_GETDRESSROOMINFO + 1

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    M_Int32 totalNum;
	M_Boolean isKeyReturn[EVENTQUEUEMAX];
	M_Boolean isNetOk[EVENTQUEUEMAX];
	M_Int32 type[EVENTQUEUEMAX];
	M_Int32 anyCnt[EVENTQUEUEMAX];
	M_Int32 x[EVENTQUEUEMAX];
	M_Int32 y[EVENTQUEUEMAX];
	///////////////////////////////////////////
	//XEVENTQUEUENET 변수 추가 LJW 2018.01.22
	M_Int32 typeNum[EVENTQUEUEMAX];
	M_Int32 bkey[EVENTQUEUEMAX];
	M_Int32 idx[EVENTQUEUEMAX];
	M_Int32 start_time[EVENTQUEUEMAX];
	M_Int64 end_time[EVENTQUEUEMAX];
	///////////////////////////////////////////
	
	M_Int32 code[EVENTQUEUEMAX];
	M_Int32 haveNum[EVENTQUEUEMAX];
	
	
	M_Int32 floor[EVENTQUEUEMAX];
	M_Int32 action[EVENTQUEUEMAX];
	M_Int32 key[EVENTQUEUEMAX];
	M_Int32 mapX[EVENTQUEUEMAX];
	M_Int32 mapY[EVENTQUEUEMAX];
    
    M_Int32 questType[EVENTQUEUEMAX];
    M_Int32 questIndex[EVENTQUEUEMAX];
    M_Int32 questValue[EVENTQUEUEMAX];
    
    
    
	
	XSELLSLOT xSellSlot[EVENTQUEUEMAX][9];
	
	M_Int32 layer[EVENTQUEUEMAX][16];
	
	M_Int32 sex[EVENTQUEUEMAX];
	char strNickName[EVENTQUEUEMAX][64];

	
    int EXP[EVENTQUEUEMAX];
    int GOLD[EVENTQUEUEMAX];
    int POP[EVENTQUEUEMAX];
    int SLOT[EVENTQUEUEMAX];
    int ITEM_INDEX[EVENTQUEUEMAX];
	int ITEM_COUNT[EVENTQUEUEMAX];
	int ITEM_CATEGORY[EVENTQUEUEMAX];
    int COUNT[EVENTQUEUEMAX];
    int SELL_COUNT[EVENTQUEUEMAX];
    
    
    int resultGold[EVENTQUEUEMAX];
    int resultCash[EVENTQUEUEMAX];
    int resultCount[EVENTQUEUEMAX];
    
    int result[EVENTQUEUEMAX];
    int formerType[EVENTQUEUEMAX];
    
	M_Int32 slotNum[EVENTQUEUEMAX];
	M_Int32 open[EVENTQUEUEMAX];
	M_Int32 time[EVENTQUEUEMAX];
	
	M_Int32 friendNum[EVENTQUEUEMAX];
	
	M_Int32 item_total[EVENTQUEUEMAX];
	M_Int32 item_index[EVENTQUEUEMAX][12];
	M_Int32 item_count[EVENTQUEUEMAX][12];
	M_Int32 item_category[EVENTQUEUEMAX][12];
    
    int imgBufSize[EVENTQUEUEMAX];
    int imgBuf[209600];  //이미지전용
	
	
} XEVENTQUEUENET;
extern XEVENTQUEUENET xEventQueueNet;


///////////////////////캔디머신/////////////////////



#define MINIGAMESLOTMAX		64

#define MINIGAME_TYPE_TREND			0
#define MINIGAME_TYPE_TIRED			1
#define MINIGAME_TYPE_GOLD			2
#define MINIGAME_TYPE_LOOK			3
#define MINIGAME_TYPE_MODEL			4
#define MINIGAME_TYPE_INTERIOR		5
#define MINIGAME_TYPE_FASHIONOPEN	6
#define MINIGAME_TYPE_INTERIOR222	7


#define MINIGAME_STATE_MAIN			0
#define MINIGAME_STATE_PLAY			1
#define MINIGAME_STATE_RESULT		2

#define MINIGAME_STATE_RESULTSUB		3

typedef struct
{
	int slotType;
	SECURITY slotCode;
	int slotImgNum;
	int count;
	int perCount[10];
	int per[10];
	
} XMINIGAMESLOT;

typedef struct
{
	int state;
	int mainAnyCnt;
	int anyCnt;
	int selectSlot;
	
	int nowTired;
	int showTired;
	int inputCandyAnyCnt;
	
	int playCandyAnyCnt;
	int playCandyAnyCnt2;
	

	XTOUCH xTouchBtnPlay;
	
	XDRAGSCROLL xDragScroll;
	

	int autoCnt;
	
	
	
	XMINIGAMESLOT xMiniGameSlot[MINIGAMESLOTMAX];
	
	int resultCode;
	int resultType;
	int resultPer;
	
	int gageAnyCnt;
	
	
	
	int playCount;
	int perSlotNum;
	
	SECURITY userTired;
    
    
    bool isSkip;
		
} XMINIGAME;
extern XMINIGAME xMiniGame;














///////////////////////트랜드/////////////////////
#define EVENTBOXMAX			128

#define EVENTBOX_TYPE_DONT				0
#define EVENTBOX_TYPE_SELLTABLE			1
#define EVENTBOX_TYPE_SHOWWINDOW		2
#define EVENTBOX_TYPE_MAIL				3
#define EVENTBOX_TYPE_PAYMENT			4
#define EVENTBOX_TYPE_CARPARK			5
#define EVENTBOX_TYPE_SELLTABLEFRIEND	6
#define EVENTBOX_TYPE_SHOWWINDOWFRIEND	7



#define EVENTBOX_TYPE_SELLTABLEUSER		9
#define EVENTBOX_TYPE_SHOWWINDOWUSER	10


#define EVENTBOX_TYPE_CHAIREVENT		13
#define EVENTBOX_TYPE_SHOWWINDOWFAME	14

#define EVENTBOX_TYPE_FRIENDORDER		15
#define EVENTBOX_TYPE_TRENDNPC			16
#define EVENTBOX_TYPE_MODELEVENT		17
#define EVENTBOX_TYPE_PRODUCTION		18
#define EVENTBOX_TYPE_SONG				19

#define EVENTBOX_TYPE_WASTE				20

#define EVENTBOX_TYPE_FORMER            21

typedef struct
{
	int totalNum;
	int code[EVENTBOXMAX];
	int slot[EVENTBOXMAX];
	int type[EVENTBOXMAX];
	XTOUCH xTouch[EVENTBOXMAX];
} XEVENTBOX;
extern XEVENTBOX xEventBox[FLOORMAX];

///////////////////////트랜드/////////////////////
#define TRENDMAX			2


#define TREND_STATE_NEW				0
#define TREND_STATE_EMPTYERR		1
#define TREND_STATE_CHANGESLOT		2
#define TREND_STATE_MAIN			3


typedef struct
{
	int state;
	int selectSlot;
	int totalNum;
	M_Boolean isOpen[TRENDMAX];
	int lv[TRENDMAX];
	int itemCode[TRENDMAX];

	int per[TRENDMAX];

	M_Int64 endTime[TRENDMAX];
	
	int bonus;
		
	int itemCodeTemp;

	int perTemp;
	int timeTemp;
	
	
	
	
	
	
	
	
	/////////////////////발생관련엑셀테이블//////////////////
	int totalParser;
	int parserMakeTime[30];
	int parserPer[30];
	int parserTime[30];
	int parserCheckPer[30];
	
	
} XTREND;
extern XTREND xTrend;



extern XTOUCH xTouchTrendSlot[TRENDMAX];

//////////////////////공지/////////////////////////
typedef struct
{
	XTOUCH xTouchOneDay;
	M_Boolean isOneDay;
	
	
	
	XDRAGSCROLL xDragScroll;
	XTOUCH xTouchRankInfo;
	
	char strText[2048];
	
	
	char strGameTip[512];
	
} XNOTICE;
extern XNOTICE xNotice;


#define NOTICEWORLDMAPMAX	128
typedef struct
{
	XTOUCH xTouchLeft;
	XTOUCH xTouchRight;
	XTOUCH xTouchOk;
	XTOUCH xTouchOneDay;
		
	XDRAGSCROLL xDragScroll;
	M_Boolean isOneDay;
		
	int totalNum;
    int code[NOTICEWORLDMAPMAX];
	char strImgUrl[NOTICEWORLDMAPMAX][128];
	char strRinkUrl[NOTICEWORLDMAPMAX][128];
	
	int downLoadImgState[NOTICEWORLDMAPMAX];
	
	XIMG imgNotice[NOTICEWORLDMAPMAX];
			
	int nowPopupNum;
    
    
    XTOUCH xTouchFriendDel;
	
} XNOTICEWORLDMAP;
extern XNOTICEWORLDMAP xNoticeWorldMap;
///////////////////////레벨업/////////////////////



#define LVUPSLOTMAX			64

#define LVUPSLOT_TYPE_FASHION	0
#define LVUPSLOT_TYPE_INTERIOR	1
typedef struct
{
	int anyCnt;
	int totalSlotNum;
	int slotCode[LVUPSLOTMAX];
	int slotType[LVUPSLOTMAX];
	XDRAGSCROLL xDragScroll;
	
	XTOUCH xTouchSlot[LVUPSLOTMAX];
	
	int interiorInfoCode;
	int productionInfoCode;
} XLVUP;
extern XLVUP xLvUp;

///////////////////////프로필/////////////////////
typedef struct
{
	XTOUCH xTouchClr;
	XTOUCH xTouchShopTitle;
	XTOUCH xTouchPhoto;

	
	
	XTOUCH xTouchPhotoDel;
	XTOUCH xTouchPhotoSelect;
	
	M_Boolean isPhoto;
	
} XPROFILE;
extern XPROFILE xProfile;

#define FRIENDMAX				2048
///////////////////////친구데이터/////////////////////
#define FRIENDDOWNLOADIMG_STATE_DONT		0
#define FRIENDDOWNLOADIMG_STATE_EVENT		1
#define FRIENDDOWNLOADIMG_STATE_DOWNING		2
#define FRIENDDOWNLOADIMG_STATE_OK			3
#define FRIENDDOWNLOADIMG_STATE_ERR			4

typedef struct
{
	int userNum;
	int lv;
	int todayVisit;
	int todayOrder;
	int friendState;
	int socialCount;
	int sex;
	int age;
	int area;
	
	int isFriend;		//친구여부
	
    int waitCnt;
	int downLoadImgState;
	char strUrl[128];
	char strNickName[64];
	char strKakaoId[128];
		
	M_Boolean isAdd;
	M_Boolean isPM;	
	M_Boolean isMarketing;
    bool isBookMark;
    
    int loginDay;
    
    
    
	
	M_Boolean isAlliance;
	
	
	///////////////////////////카카오톡////////////////
	M_Boolean isKakao;			//카카오친구여부
	
	
	M_Boolean isKakaoHelp;		//카카오헬프여부
	
	M_Boolean isKakaoMessage;	//TRUE:수신가능 FALSE:수신불가능
	
	M_Boolean isVote;
	
	int message_blocked;
	
    int loginFlowTime;
	
} XFRIENDDATA;
extern XFRIENDDATA xFriendData[FRIENDMAX];
///////////////////////////////////////////////////

///////////////////////친구/////////////////////
#define FRIEND_STATE_PLAY		0
#define FRIEND_STATE_FOLLOW		1
#define FRIEND_STATE_KAKAO		2

#define FRIEND_STATE_ADD		4

#define FRIENDADD_STATE_PLAY		0
#define FRIENDADD_STATE_NOTUSER		1
#define FRIENDADD_STATE_RESULT		2

typedef struct
{
    
    int totalFriend;
    
	int totalNumFriendData;

	int selectTabB;
	
	//랜덤 친구 리스트
	int totalNumListRanDom;
	int dataSlotNumListRanDom[512];
	XDRAGSCROLL xDragScrollRanDomList;
	
	
	//친구 주문장
	int stateOrder;
	XDRAGSCROLL xDragScrollOrderList;
	XTOUCH xTouchFriendOrderBtn;
	
	
	
	
	XTOUCH xTouchAddBtn;
	XTOUCH xTouchEditBtn;
	XTOUCH xTouchRandomBtn;
	int selectSlot;
	
	XTOUCH xTouchTabB[3];
	XTOUCH xTouchSelectSlot[17];
	XTOUCH xTouchSelectDelBtn[17];
    
    XTOUCH xTouchSelectBookMark[17];
    
    
	int state;
	
	
	//친구 리스트
	int totalNumList;	
	int dataSlotNumList[FRIENDMAX];
	int nowRowNumList;
	int nowPageNumList;
	//팔로우
	int totalNumListFollow;
	int dataSlotNumListFollow[FRIENDMAX];
	int nowRowNumListFollow;
	int nowPageNumListFollow;

	
	//친구추가
	int addState;
	XTOUCH xTouchAddTab[5];
	XTOUCH xTouchSearch;
	XTOUCH xTouchTextBox;
	XTOUCH xTouchFriendAddBtn[10];
	
	int addFriendTab;
	char strUserName[64];
	
	M_Boolean isDelMode;
	
	
	M_Boolean isInvite;

		
		
} XFRIEND;
extern XFRIEND xFriend;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////친구행성 KBY
#define FRIEND_FP_STATE_PLAY		0
#define FRIEND_FP_STATE_SEARCH		FRIEND_FP_STATE_PLAY+1

#define FRIENDSEARCH_FP_STATE_PLAY          0
#define FRIENDSEARCH_FP_STATE_NOTUSER		FRIENDSEARCH_FP_STATE_PLAY+1
#define FRIENDSEARCH_FP_STATE_RESULT		FRIENDSEARCH_FP_STATE_NOTUSER+1
#define FRIENDSEARCH_FP_STATE_OK            FRIENDSEARCH_FP_STATE_RESULT+1
#define FRIENDSEARCH_FP_STATE_INPUT         FRIENDSEARCH_FP_STATE_OK+1
#define FRIENDSLOTMAX                       512
typedef struct
{
    XTOUCH xTouchLeftArrow;
    XTOUCH xTouchRightArrow;
    XTOUCH xTouchSearch;
    XTOUCH xTouchSearchFriend;
    XTOUCH xTouchRecommend;
    XTOUCH xTouchEdit;
    XTOUCH xTouchFavorite[FRIENDSLOTMAX];
    XTOUCH xTouchDel[FRIENDSLOTMAX];
    XTOUCH xTouchJoin[FRIENDSLOTMAX];
    XTOUCH xTouchVisit[FRIENDSLOTMAX];
    XTOUCH xTouchSearchBar;
    XTOUCH xTouchTab[2];
    
    XDRAGSCROLL xDragScrollFriendResult;
    int selectTabB;
    int state;
    int SearchState;
    
    bool isTouchLeftArrow;
    bool isTouchRightArrow;
    bool isTouchSearchLeftArrow;
    bool isTouchSearchRightArrow;
    bool isTouchSearch;
    bool isTouchPopUpSearch;
    bool isTouchRecommend;
    bool isTouchVisit[FRIENDSLOTMAX];
    bool isTouchDel[FRIENDSLOTMAX];
    bool isTouchJoin[FRIENDSLOTMAX];
    bool isTouchSearchJoin[FRIENDSLOTMAX];
    bool isTouchSearchVisit[FRIENDSLOTMAX];
    bool isTouchSearchBar;
    bool isTouchEdit;
    bool isTouchClr;
    bool isTouchSearchClr;
    
    char strName[128];
    
} XFRIEND_FP;
extern XFRIEND_FP xFriend_FP;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////친구맵/////////////////////
#define FRIENDMAP_STATE_LOADING0_START			0
#define FRIENDMAP_STATE_LOADING0_ING			1

#define FRIENDMAP_STATE_LOADING1_START			2
#define FRIENDMAP_STATE_LOADING1_ING			3

#define FRIENDMAP_STATE_LOADING2_START			4
#define FRIENDMAP_STATE_LOADING2_ING			5

#define FRIENDMAP_STATE_LOADING3_START			6
#define FRIENDMAP_STATE_LOADING3_ING			7

#define FRIENDMAP_STATE_PLAY					8
typedef struct
{
	M_Boolean isPlay;
	M_Boolean isLoadingOk;
	int state;
	int anyCnt;
	
	int selectDataSlotNum;
	
	
	///진입타입(0:보통1:랜덤2:메일)
	int type;
	
	
	
	//////////친구정보///////////////
	int fame;
	int lv;
} XFRIENDMAP;
extern XFRIENDMAP xFriendMap;
///////////////////////////////////////////////////



extern XIMG imgFriend[FRIENDMAX];











#define EXTENSIONSHOPFLOORMAX		2
#define EXTENSIONSHOPTILEMAX		7

typedef struct
{
	int floor;
	int tile;
	
	int priceType;
} XEXTENSIONSLOT;

typedef struct
{
	int floorLv[EXTENSIONSHOPFLOORMAX];
	SECURITY floorPrice[EXTENSIONSHOPFLOORMAX][2];
	
	int tileLv[EXTENSIONSHOPTILEMAX];
	int tileFame[EXTENSIONSHOPTILEMAX];
	SECURITY tilePrice[EXTENSIONSHOPTILEMAX][2];
		
	XDRAGSCROLL xDragScroll;
	////////////////////////증축///////
	int totalFloor;
	XEXTENSIONSLOT xSlotFloor[20];
	///////////////////////확장////////
	int totalTile;
	XEXTENSIONSLOT xSlotTile[20];
	
	/////////////////////외벽/////////
	int selectSlot;
	
	
	
	M_Boolean isCheckExtension;
	M_Boolean isExtensionErr;
	M_Int64 extensionErrTime;
				
} XEXTENSIONSHOP;
extern XEXTENSIONSHOP xExtensionShop;






///////////////////////자동차데이터/////////////////////
typedef struct
{
	char strName[128];
	int lv;
	SECURITY price;
	int priceType;
	SECURITY timePer;
} XCARDATA;
extern XCARDATA xCarData[CARDATAMAX];



extern XIMG imgCar[CARDATAMAX][2];


///////////////////////자동차/////////////////////
typedef struct
{
	M_Boolean isOpen[CARDATAMAX];
	
	int tireX[CARDATAMAX][2][2];
	int tireY[CARDATAMAX][2][2];
	
	int boxX[CARDATAMAX][2];
	int boxY[CARDATAMAX][2];
	
	int selectCarPark;
	int toalSlot;
	int slotCode[CARDATAMAX];
	M_Boolean isSlotInfo[CARDATAMAX];
	
	XTOUCH xTouchChangeBtn[CARDATAMAX];
	XTOUCH xTouchInfoBtn[CARDATAMAX];
	
	
	
	
	int selectTabS;
	XTOUCH xTouchTabS[3];
	int selectSlot;
	
} XCAR;
extern XCAR xCar;

extern XIMG imgCar[CARDATAMAX][2];

///////////////////////주차장관리/////////////////////
#define CARKPARKMAX			3

#define CARPARK_STATE_READ			0
#define CARPARK_STATE_GO			1
#define CARPARK_STATE_ING			2








typedef struct
{
	M_Boolean isEventBox;
	M_Boolean eventBoxAnyCnt;
	int imgEventBox;
	int anyCnt;
	int state;
	int carNum;
	int lv;
	int orderKey;
	M_Int64 endTime;
	
	XTOUCH xTouch;
} XCARPARK;
extern XCARPARK xCarPark[CARKPARKMAX];

///////////////////////주문장관리/////////////////////
#define ORDERSLOT_STATE_CLOSE		0
#define ORDERSLOT_STATE_END			1
#define ORDERSLOT_STATE_CAR			2

typedef struct
{
	M_Int32 state;
	M_Int32 code;
	M_Int64 endTime;
	M_Int32 key;
	M_Int32 friendNum;
	M_Int32 friendType;
	M_Boolean isNew;
} XORDERSLOT;

#define ORDERSLOTMAX		128

typedef struct
{
	int totalNumListData;
	XORDERSLOT xSlotListData[ORDERSLOTMAX];
		
	int totalNumListDataFriend;
	XORDERSLOT xSlotListDataFriend[ORDERSLOTMAX];
		
	int totalNumList;
	int totalNumRecv;
	
	int slotNumList[ORDERSLOTMAX];
	XORDERSLOT xSlotNumRecv[ORDERSLOTMAX];
	
	XTOUCH xTouchOrderIcon;
	
	//////////////주문장리스트
	XDRAGSCROLL xDragScroll;
	int selectSlot;
	XTOUCH xTouchBtn[2];
	
	///////////통합
	int selectTabS;
		
	//////////자동차 선택모드
	int carParkSelectMode_Code;
	int carParkSelectMode_OrderKey;
	M_Boolean isCarPakrGo;
		
	/////////퀘스트 마구 틀어가는거 방지용 로딩후 처리
	M_Boolean isNetLoad;
	
	//////////////////
	M_Boolean isNew;
	
	
	M_Boolean isKakaoMessage_Net;
    
    
    XTOUCH xTouchProfile[20];
    
} XORDER;
extern XORDER xOrder;







///////////////////////이펙트/////////////////////
#define EFFMAX			10

#define EFF_STATE_DONT		0
#define EFF_STATE_PLAY		1
typedef struct
{
	int state;
	int anyCnt;
	int x;
	int y;
	int reSize;
} XEFF;
extern XEFF xEff[EFFMAX];


#define TUTOLIMIT_WORLDMAP		0
#define TUTOLIMIT_PRODUCE		1
#define TUTOLIMIT_DP			2
#define TUTOLIMIT_EDIT			3
#define TUTOLIMIT_STORE			4
#define TUTOLIMIT_FRIENDS		5
#define TUTOLIMIT_ADDFRIENDS	6
#define TUTOLIMIT_FRIENDSHOP	7
#define TUTOLIMIT_FITTING		8
#define TUTOLIMIT_FASHIONSHOW	9
#define TUTOLIMIT_STAFF			10
#define TUTOLIMIT_MODEL			11
#define TUTOLIMIT_MINIGAME			12
#define TUTOLIMIT_MAIL			13
#define TUTOLIMIT_TREND			14
#define TUTOLIMIT_DELIVERY			15


#define TUTOLIMITMAX		300






#define TUTOLIMIT_TYPE_EDIT_OK				0
#define TUTOLIMIT_TYPE_EDIT_CANCEL			1
#define TUTOLIMIT_TYPE_EDIT_SAVE			2
#define TUTOLIMIT_TYPE_EDIT_SHOP			3
#define TUTOLIMIT_TYPE_EDIT_EXIT			4
#define TUTOLIMIT_TYPE_EDIT_ALL				5
#define TUTOLIMIT_TYPE_EDIT_REVERSE			6
#define TUTOLIMIT_TYPE_EDIT_TILEMODE		7//	타일모드
#define TUTOLIMIT_TYPE_EDIT_INTERIORMODE	8//	가구모드
#define TUTOLIMIT_TYPE_EDIT_SELECT			9
#define TUTOLIMIT_TYPE_EDIT_MOVE			10



#define TUTOLIMIT_TYPE_WORLDMAP_MAINMANU		20
#define TUTOLIMIT_TYPE_WORLDMAP_FRIENDS			21
#define TUTOLIMIT_TYPE_WORLDMAP_TREND			22
#define TUTOLIMIT_TYPE_WORLDMAP_DELIVERY		23
#define TUTOLIMIT_TYPE_WORLDMAP_GOLDCASH		24
#define TUTOLIMIT_TYPE_WORLDMAP_PROFILE			25
#define TUTOLIMIT_TYPE_WORLDMAP_POSTBOX			26
#define TUTOLIMIT_TYPE_WORLDMAP_EXPEND1			27
#define TUTOLIMIT_TYPE_WORLDMAP_FASHIONSHOW		28
#define TUTOLIMIT_TYPE_WORLDMAP_QUEST			29
#define TUTOLIMIT_TYPE_WORLDMAP_PARKING			30
#define TUTOLIMIT_TYPE_WORLDMAP_COUNTER			31
#define TUTOLIMIT_TYPE_WORLDMAP_DP2				32
#define TUTOLIMIT_TYPE_WORLDMAP_DP1				33
#define TUTOLIMIT_TYPE_WORLDMAP_MANNEQUIN		34
#define TUTOLIMIT_TYPE_WORLDMAP_PREFERENCE		35
#define TUTOLIMIT_TYPE_WORLDMAP_EDITINTERIOR	36
#define TUTOLIMIT_TYPE_WORLDMAP_MODEL			37
#define TUTOLIMIT_TYPE_WORLDMAP_EVENT			38

#define TUTOLIMIT_TYPE_WORLDMAP_CANDY			39//캔디머신
#define TUTOLIMIT_TYPE_WORLDMAP_MODELMENU		40//모델
#define TUTOLIMIT_TYPE_WORLDMAP_STAFF			41//직원
#define TUTOLIMIT_TYPE_WORLDMAP_STORE			42//상점
#define TUTOLIMIT_TYPE_WORLDMAP_EDIT			43//편집
#define TUTOLIMIT_TYPE_WORLDMAP_OPTION			44//설정
#define TUTOLIMIT_TYPE_WORLDMAP_SALESHOP			45//설정
#define TUTOLIMIT_TYPE_WORLDMAP_COLLECTION			46//스타일북



#define TUTOLIMIT_TYPE_PRODUCE_CLOSE			50//창닫기(화면밖터치포함)
#define TUTOLIMIT_TYPE_PRODUCE_PREMIUM			51//프리미엄제작슬롯
#define TUTOLIMIT_TYPE_PRODUCE_LICENCE			52//라이선스 구매
#define TUTOLIMIT_TYPE_PRODUCE_COMPLETE0		53//제작슬롯에서의 즉시완료
#define TUTOLIMIT_TYPE_PRODUCE_COMPLETE1		54//즉시완료 와면에서의 즉시완료
#define TUTOLIMIT_TYPE_PRODUCE_COMPLETE2		55//즉시완료 화면에서의 주문취소
#define TUTOLIMIT_TYPE_PRODUCE_CATEGORY0		56//아우터
#define TUTOLIMIT_TYPE_PRODUCE_CATEGORY1		57//상의
#define TUTOLIMIT_TYPE_PRODUCE_CATEGORY2		58//하의
#define TUTOLIMIT_TYPE_PRODUCE_CATEGORY3		59//원피스
#define TUTOLIMIT_TYPE_PRODUCE_CATEGORY4		60//신발
#define TUTOLIMIT_TYPE_PRODUCE_CATEGORY5		61//가방
#define TUTOLIMIT_TYPE_PRODUCE_CATEGORY6		62//액세서리
#define TUTOLIMIT_TYPE_PRODUCE_CATEGORY7		63//전체보기
#define TUTOLIMIT_TYPE_PRODUCE_MOVE				64//좌우이동버튼
#define TUTOLIMIT_TYPE_PRODUCE_CANCEL			65//빼는것 방지
#define TUTOLIMIT_TYPE_PRODUCE_FASHIONSHOW		66//패션쇼 막기


#define	TUTOLIMIT_TYPE_DP_CLOSE					70//창닫기
#define	TUTOLIMIT_TYPE_DP_COMPLETE0				71//진열슬롯에서의 즉시완료
#define	TUTOLIMIT_TYPE_DP_COMPLETE1				72//즉시완료 화면에서의 즉시완료
#define	TUTOLIMIT_TYPE_DP_COMPLETE2				73//즉시완료 화면에서의 주문취소
#define	TUTOLIMIT_TYPE_DP_SCROLL				74//스크롤
#define	TUTOLIMIT_TYPE_DP_ORDER					75//주문하러가기

#define	TUTOLIMIT_TYPE_STORE_CATEGORY0	80//	기능성
#define	TUTOLIMIT_TYPE_STORE_CATEGORY1	81//	꾸미기
#define	TUTOLIMIT_TYPE_STORE_CATEGORY2	82//	확장
#define	TUTOLIMIT_TYPE_STORE_CATEGORY3	83//	테마
#define	TUTOLIMIT_TYPE_STORE_CATEGORY4	84//	유료샵
#define	TUTOLIMIT_TYPE_STORE_CATEGORY5	85//	보관함
#define	TUTOLIMIT_TYPE_STORE_MENU0		86//	0번메뉴
#define	TUTOLIMIT_TYPE_STORE_MENU1		87//	1번메뉴
#define	TUTOLIMIT_TYPE_STORE_MENU2		88//	2번메뉴
#define	TUTOLIMIT_TYPE_STORE_MENU3		89//	3번메뉴
#define	TUTOLIMIT_TYPE_STORE_MENU4		90//	4번메뉴
#define	TUTOLIMIT_TYPE_STORE_MENU5		91//	5번메뉴
#define	TUTOLIMIT_TYPE_STORE_MENU6		92//	6번메뉴
#define	TUTOLIMIT_TYPE_STORE_MENU7		93//	7번메뉴
#define	TUTOLIMIT_TYPE_STORE_MOVE		94//	좌우이동버튼
#define	TUTOLIMIT_TYPE_STORE_CLOSE		95//	창닫기
#define	TUTOLIMIT_TYPE_STORE_ITEMSELECT	96//	선택제어

//친구리스트
#define	TUTOLIMIT_TYPE_FRIENDS_LIST		100//	리스트메뉴
#define	TUTOLIMIT_TYPE_FRIENDS_FOLLOW	101//	팔로우메뉴
#define	TUTOLIMIT_TYPE_FRIENDS_EDIT		102//	편집
#define	TUTOLIMIT_TYPE_FRIENDS_MODEL	103//	모델보기
#define	TUTOLIMIT_TYPE_FRIENDS_ADD		104//	친구추가
#define	TUTOLIMIT_TYPE_FRIENDS_RANDOM	105//	랜덤친구
#define	TUTOLIMIT_TYPE_FRIENDS_CLOSE	106//	창닫기
#define	TUTOLIMIT_TYPE_FRIENDS_FRIENDS	107//	친구리스트
#define	TUTOLIMIT_TYPE_FRIENDS_FRIENDS_PM	108//	친구리스트


#define	TUTOLIMIT_TYPE_ADDFRIENDS_RECOMMEND 110//	추천친구
#define	TUTOLIMIT_TYPE_ADDFRIENDS_FIND		111//	친구검색
#define	TUTOLIMIT_TYPE_ADDFRIENDS_KAKAOAPP	112//	카카오친구목록
#define	TUTOLIMIT_TYPE_ADDFRIENDS_KAKAO		113//	카카오친구목록
#define	TUTOLIMIT_TYPE_ADDFRIENDS_INVITE	114//	초대보상
#define	TUTOLIMIT_TYPE_ADDFRIENDS_CLOSE		115//	창닫기
#define	TUTOLIMIT_TYPE_ADDFRIENDS_ADD		116//	친구추가

#define TUTOLIMIT_TYPE_FRIENDSHOP_MODEL		120//	친구모델
#define TUTOLIMIT_TYPE_FRIENDSHOP_GUESTBOOK	121//	방명록
#define TUTOLIMIT_TYPE_FRIENDSHOP_HOME		122//	카카오친구목록
#define TUTOLIMIT_TYPE_FRIENDSHOP_FRIENDS	123//	친구리스트
#define TUTOLIMIT_TYPE_FRIENDSHOP_PREVIOUS	124// 이전친구
#define TUTOLIMIT_TYPE_FRIENDSHOP_NEXT		125//	다음친구
#define TUTOLIMIT_TYPE_FRIENDSHOP_QUEST		126//	내 퀘스트
#define TUTOLIMIT_TYPE_FRIENDSHOP_HELP		127//	HELP아이콘
#define TUTOLIMIT_TYPE_FRIENDSHOP_PHOTO		128//	사진아이콘
#define TUTOLIMIT_TYPE_FRIENDSHOP_ORDER		129//	카운터주문

#define TUTOLIMIT_TYPE_FRIENDSHOP_EXTERNAL		130//	외각
#define TUTOLIMIT_TYPE_FRIENDSHOP_FLOOR1		131//	1층
#define TUTOLIMIT_TYPE_FRIENDSHOP_FLOOR2		132//	2층



#define TUTOLIMIT_TYPE_FITTING_SAVE			140//	사진아이콘
#define TUTOLIMIT_TYPE_FITTING_EXIT			141//	카운터주문
#define TUTOLIMIT_TYPE_FITTING_CATEGORY0	142
#define TUTOLIMIT_TYPE_FITTING_CATEGORY1	143
#define TUTOLIMIT_TYPE_FITTING_CATEGORY2	144
#define TUTOLIMIT_TYPE_FITTING_CATEGORY3	145
#define TUTOLIMIT_TYPE_FITTING_CATEGORY4	146
#define TUTOLIMIT_TYPE_FITTING_CATEGORY5	147
#define TUTOLIMIT_TYPE_FITTING_CATEGORY6	148
#define TUTOLIMIT_TYPE_FITTING_MAN			149
#define TUTOLIMIT_TYPE_FITTING_WOMAN		150
#define TUTOLIMIT_TYPE_FITTING_TUCKMENU		151
#define TUTOLIMIT_TYPE_FITTING_TUCKIN		152
#define TUTOLIMIT_TYPE_FITTING_TUCKOUT		153
#define TUTOLIMIT_TYPE_FITTING_RESET		154
#define TUTOLIMIT_TYPE_FITTING_LEFT			155
#define TUTOLIMIT_TYPE_FITTING_RIGHT		156
#define TUTOLIMIT_TYPE_FITTING_FITTING		157
#define TUTOLIMIT_TYPE_FITTING_LINK			158




#define TUTOLIMIT_TYPE_FASHIONSHOW_RANK0			160
#define TUTOLIMIT_TYPE_FASHIONSHOW_RANK1			161
#define TUTOLIMIT_TYPE_FASHIONSHOW_RANK2			162
#define TUTOLIMIT_TYPE_FASHIONSHOW_EXIT				163
#define TUTOLIMIT_TYPE_FASHIONSHOW_READBTN			164
#define TUTOLIMIT_TYPE_FASHIONSHOW_NOTICE			165
#define TUTOLIMIT_TYPE_FASHIONSHOW_VOTE				166
#define TUTOLIMIT_TYPE_FASHIONSHOW_INFO				167
#define TUTOLIMIT_TYPE_FASHIONSHOW_INFOEXIT			168
#define TUTOLIMIT_TYPE_FASHIONSHOW_INFOFRIENDSHOP	169
#define TUTOLIMIT_TYPE_FASHIONSHOW_INFOREPLAY		171
#define TUTOLIMIT_TYPE_FASHIONSHOW_DRESSCODE		172
#define TUTOLIMIT_TYPE_FASHIONSHOW_BACK				173
#define TUTOLIMIT_TYPE_FASHIONSHOW_START			174
#define TUTOLIMIT_TYPE_FASHIONSHOW_FITTING			175
#define TUTOLIMIT_TYPE_FASHIONSHOW_SELECTMODEL		176
#define TUTOLIMIT_TYPE_FASHIONSHOW_SKIP				177


#define TUTOLIMIT_TYPE_STAFF_SAVE			180//	사진아이콘
#define TUTOLIMIT_TYPE_STAFF_EXIT			181//	카운터주문
#define TUTOLIMIT_TYPE_STAFF_CATEGORY0		182
#define TUTOLIMIT_TYPE_STAFF_CATEGORY1	183
#define TUTOLIMIT_TYPE_STAFF_CATEGORY2	184
#define TUTOLIMIT_TYPE_STAFF_CATEGORY3	185
#define TUTOLIMIT_TYPE_STAFF_CATEGORY4	186
#define TUTOLIMIT_TYPE_STAFF_CATEGORY5	187
#define TUTOLIMIT_TYPE_STAFF_LEFT		189
#define TUTOLIMIT_TYPE_STAFF_RIGHT		190
#define TUTOLIMIT_TYPE_STAFF_TUCKMENU	191
#define TUTOLIMIT_TYPE_STAFF_TUCKIN		192
#define TUTOLIMIT_TYPE_STAFF_TUCKOUT	193
#define TUTOLIMIT_TYPE_STAFF_RESET		194
#define TUTOLIMIT_TYPE_STAFF_EDIT		195

#define TUTOLIMIT_TYPE_MODEL_EXIT			200
#define TUTOLIMIT_TYPE_MODEL_SALE			201
#define TUTOLIMIT_TYPE_MODEL_EMPTY			202
#define TUTOLIMIT_TYPE_MODEL_WAIT			203
#define TUTOLIMIT_TYPE_MODEL_PLAY			204
#define TUTOLIMIT_TYPE_MODEL_SUCCESS		205
#define TUTOLIMIT_TYPE_MODEL_INFO			206
#define TUTOLIMIT_TYPE_MODEL_CASTING			207
#define TUTOLIMIT_TYPE_MODEL_CASTINGCASH		208
#define TUTOLIMIT_TYPE_MODEL_MODELLIST			209
#define TUTOLIMIT_TYPE_MODEL_INFOBTN0			210
#define TUTOLIMIT_TYPE_MODEL_INFOBTN1			211
#define TUTOLIMIT_TYPE_MODEL_INFOBTN2			212
#define TUTOLIMIT_TYPE_MODEL_INFOEXIT			213
#define TUTOLIMIT_TYPE_MODEL_SELECTMODELEXIT	214
#define TUTOLIMIT_TYPE_MODEL_GIFTINFOCASH		215
#define TUTOLIMIT_TYPE_MODEL_HELP				216


#define TUTOLIMIT_TYPE_MINIGAME_EXIT			220
#define TUTOLIMIT_TYPE_MINIGAME_PLAY			221


#define TUTOLIMIT_TYPE_MAIL_EXIT				230
#define TUTOLIMIT_TYPE_MAIL_TEXTBOX				231
#define TUTOLIMIT_TYPE_MAIL_SEND				232
#define TUTOLIMIT_TYPE_MAIL_TODAY				233
#define TUTOLIMIT_TYPE_MAIL_USERINFO			234
#define TUTOLIMIT_TYPE_MAIL_GIFTTAB				235
#define TUTOLIMIT_TYPE_MAIL_DEL					236
#define TUTOLIMIT_TYPE_MAIL_EXITFRIEND			237
#define TUTOLIMIT_TYPE_MAIL_TEXTBOXFRIEND		238
#define TUTOLIMIT_TYPE_MAIL_SENDFRIEND			239


#define TUTOLIMIT_TYPE_TREND_BUY				250
#define TUTOLIMIT_TYPE_TREND_LINK				251
#define TUTOLIMIT_TYPE_TREND_EXIT				252


#define TUTOLIMIT_TYPE_DELIVERY_ORDER			260//	주문장 메뉴
#define TUTOLIMIT_TYPE_DELIVERY_PARKING			261//	주차장 메뉴
#define TUTOLIMIT_TYPE_DELIVERY_CAR				262//	차량구매 메뉴
#define TUTOLIMIT_TYPE_DELIVERY_CLOSE			263//	주문리스트
#define TUTOLIMIT_TYPE_DELIVERY_ORDERLIST		264//	창닫기
#define TUTOLIMIT_TYPE_DELIVERY_SLOT1			265//	주차장 슬롯1
#define TUTOLIMIT_TYPE_DELIVERY_SLOT2			266//	주차장 슬롯2
#define TUTOLIMIT_TYPE_DELIVERY_SLOT3			267//	주차장 슬롯3
#define TUTOLIMIT_TYPE_DELIVERY_SELECTCLOSE		268//	차량선택화면 창닫기
#define TUTOLIMIT_TYPE_DELIVERY_COMPLETE		269//	즉시완료
#define TUTOLIMIT_TYPE_DELIVERY_OK				270//	확인







//미구현
/*
TUTOLIMIT_TYPE_WORLDMAP_EXPEND2	 //증축
TUTOLIMIT_TYPE_WORLDMAP_BROADCASTING	//방송국
TUTOLIMIT_TYPE_WORLDMAP_RIVAL	 //라이벌
 
#define TUTOLIMIT_TYPE_FRIENDSHOP_1F		120//	1층
#define TUTOLIMIT_TYPE_FRIENDSHOP_2F		120//	2층
#define TUTOLIMIT_TYPE_FRIENDSHOP_ETC		120//	UI사라짐
 */

typedef struct
{
	M_Boolean isLock[TUTOLIMITMAX];
} XTUTOLIMIT;
extern XTUTOLIMIT xTutoLimit;





#define TUTOINFOMAX				15
#define TUTOINFO_TYPE_SHOW				0
#define TUTOINFO_TYPE_ARROW				1
#define TUTOINFO_TYPE_ARROW_NOTBG		2
#define TUTOINFO_TYPE_TEXT	3




typedef struct
{
	int totalNum;
	int x[TUTOINFOMAX];
	int y[TUTOINFOMAX];
	int type[TUTOINFOMAX];
	char strText[TUTOINFOMAX][256];
		
} XTUTOINFO;
extern XTUTOINFO xTutoInfo;



#define QUEST_TUTO_WAIT		0
#define QUEST_TUTO_DIALOG	1
#define QUEST_TUTO_SHOW		2
#define QUEST_TUTO_KEY		3
#define QUEST_TUTO_RESULT	4



#define TUTO_0_PAYMENT1F						0
#define TUTO_0_PAYMENT1F_SEXINFO				1
#define TUTO_0_PAYMENT1F_NAMEINFO				2
#define TUTO_0_PAYMENT1F_MAKETOUCH				3
#define TUTO_0_PAYMENT1F_NPCINFO				4
#define TUTO_0_SHOPASSISTANT1F					5
#define TUTO_0_SHOPASSISTANT1F_MAKETOUCH		6
#define TUTO_0_SHOPASSISTANT1F_NPCINFO			7
#define TUTO_0_RESULT							8



#define TUTO_1_PRODUCTIONTOUCH					1000
#define TUTO_1_PRODUCTIONOPENFASHIONSHOW		1001
#define TUTO_1_PRODUCTIONTOPTABTOUCH			1002
#define TUTO_1_PRODUCTIONTOPFASHIONTOUCH		1003
#define TUTO_1_PRODUCTIONTOPFASHIONWAITSHOW		1004
#define TUTO_1_PRODUCTIONMAKE					1005
#define TUTO_1_PRODUCTIONINGSHOW				1006
#define TUTO_1_PRODUCTIONFASTCASH0				1007
#define TUTO_1_PRODUCTIONFASTCASH1				1008
#define TUTO_1_PRODUCTIONOK						1009
#define TUTO_1_PRODUCTIONEXIT					1010
#define TUTO_1_SELLTABLETOUCH					1011
#define TUTO_1_SELLTABLESTART0					1012
#define TUTO_1_SELLTABLESTART1					1013
#define TUTO_1_RESULT							1014



#define TUTO_2_PRODUCTIONTOUCH					2000
#define TUTO_2_PRODUCTIONTOPFASHIONTOUCH		2001
#define TUTO_2_PRODUCTIONMAKE					2002
#define TUTO_2_PRODUCTIONFASTCASH				2003
#define TUTO_2_PRODUCTIONOK						2004
#define TUTO_2_PRODUCTIONEXIT					2005
#define TUTO_2_SELLTABLETOUCH					2006
#define TUTO_2_SELLTABLESTART0					2007
#define TUTO_2_SELLTABLESTART1					2008
#define TUTO_2_RESULT							2009
#define TUTO_6_INTERIOR_MENUTOUCH0				6000
#define TUTO_6_INTERIOR_TABTOUCH				6001
#define TUTO_6_INTERIOR_ITEMTOUCH				6002
#define TUTO_6_INTERIOR_MOVE					6003
#define TUTO_6_INTERIOR_ROT						6004
#define TUTO_6_INTERIOR_CLR						6005
#define TUTO_6_INTERIOR_OK						6006
#define TUTO_6_INTERIOR_EXIT					6007
#define TUTO_6_INTERIOR_MENUTOUCH1				6008
#define TUTO_6_INTERIOR_EDITMENUTOUCH			6009
#define TUTO_6_INTERIOR_EDITITEM				6010
#define TUTO_6_INTERIOR_INVEN					6011
#define TUTO_6_INTERIOR_OK2						6012
#define TUTO_6_RESULT							6013
#define TUTO_7_RESULT							7000
#define TUTO_8_INTERIOR_TABTOUCH				8000
#define TUTO_8_INTERIOR_OK						8001
#define TUTO_8_INTERIOR_EXIT					8002
#define TUTO_8_INTERIOR_MAKENPC					8003
#define TUTO_8_INTERIOR_NPCTOUCH				8004
#define TUTO_8_RESULT							8005
#define TUTO_9_INTERIOR_TABTOUCH				9000
#define TUTO_9_INTERIOR_OK						9001
#define TUTO_9_RESULT							9002
#define TUTO_10_INTERIOR_TABTOUCH				10000
#define TUTO_10_INTERIOR_EXTENSION				10001
#define TUTO_10_RESULT							10002
#define TUTO_11_SHOWWINDOWSELECT				11000
#define TUTO_11_SHOWWINDOWLAYEREDSHOW			11001
#define TUTO_11_SHOWWINDOWLAYERED5				11002
#define TUTO_11_SHOWWINDOWRESET					11003
#define TUTO_11_RESULT							11004
#define TUTO_12_SHOWWINDOWSELECT				12000
#define TUTO_12_SHOWWINDOWFITTING				12001
#define TUTO_12_SHOWWINDOWIN0					12002
#define TUTO_12_SHOWWINDOWIN1					12003
#define TUTO_12_SHOWWINDOWOUT					12004
#define TUTO_12_RESULT							12005
#define TUTO_13_STAFF_MENUTOUCH					13000
#define TUTO_13_STAFF_BUY						13001
#define TUTO_13_RESULT							13002
#define TUTO_14_STAFF_MENUTOUCH					14000
#define TUTO_14_STAFF_BUY						14001
#define TUTO_14_RESULT							14002
#define TUTO_15_MINIGAME_MENUTOUCH				15000
#define TUTO_15_MINIGAME_START					15001
#define TUTO_15_RESULT							15002
#define TUTO_16_FAMESHOW						16000
#define TUTO_16_RESULT							16001
#define TUTO_17_MAILSELECT						17000
#define TUTO_17_MAIL_FRIEND						17001
#define TUTO_17_RESULT							17002
#define TUTO_18_FRIENDMODEL_MENUTOUCH			18000
#define TUTO_18_RESULT							18001
#define TUTO_19_INSHOPPERSELECT					19000
#define TUTO_19_RESULT							19001
#define TUTO_20_ORDER_MENUTOUCH					20000
#define TUTO_20_ORDER_INFOSHOW					20001
#define TUTO_20_ORDER_ORDERSELECT				20002
#define TUTO_20_ORDER_CARSELECT					20003
#define TUTO_20_ORDER_CARINFOSELECT				20004
#define TUTO_20_ORDER_CARINFOEXIT				20005
#define TUTO_20_ORDER_OK						20006
#define TUTO_20_RESULT							20007
#define TUTO_21_TRENDNEW						21000
#define TUTO_21_TRENDOK							21001
#define TUTO_21_TRENDICON						21002
#define TUTO_21_RESULT							21003





#define TUTO_22_MODELCASTING					22000
#define TUTO_22_MODELCASTINGEXIT				22001
#define TUTO_22_MODELMAINSLOTSELECT				22002
#define TUTO_22_MODELSELECTMODEL				22003
#define TUTO_22_MODELMODELINFO					22004
#define TUTO_22_MODELGIFTINFOSHOW				22005
#define TUTO_22_MODELFITTINGBTN					22006
#define TUTO_22_MODELFITTINGOK					22007
#define TUTO_22_MODELEXIT						22008
#define TUTO_22_MODELMAPMODELSTART				22009
#define TUTO_22_MODELMAPMODELINFO				22010
#define TUTO_22_MODELMAPMODELINFOEXIT			22011
#define TUTO_22_RESULT							22012





#define TUTO_23_FASHIONSHOWSELECT				23000
#define TUTO_23_FASHIONSHOWDRESSCODE			23001
#define TUTO_23_FASHIONSHOWSTART				23002
#define TUTO_23_RESULT							23003



#define TUTO_24_UI_PHOTO						24000
#define TUTO_24_UI_NICKNAME						24001
#define TUTO_24_UI_LV							24002
#define TUTO_24_UI_FAME0						24003
#define TUTO_24_UI_FAME1						24004
#define TUTO_24_UI_CANDY						24005
#define TUTO_24_UI_LOOK							24006
#define TUTO_24_UI_GOLD							24007
#define TUTO_24_UI_QUEST0						24008
#define TUTO_24_UI_QUEST1						24009
#define TUTO_24_UI_ETC							24010
#define TUTO_24_UI_MENU							24011
#define TUTO_24_UI_FRIEND						24012
#define TUTO_24_RESULT							24013
#define TUTO_25_FASHIONOPEN_PRODUCTIONTOUCH		25000
#define TUTO_25_FASHIONOPEN_TAB					25001
#define TUTO_25_FASHIONOPEN_ITEM				25002
#define TUTO_25_FASHIONOPEN_BUY					25003
#define TUTO_25_FASHIONOPEN_BUYTAB				25004
#define TUTO_25_RESULT							25005

#define TUTO_26_INTERIOR_MENUTOUCH0				26000
#define TUTO_26_INTERIOR_TABTOUCH0				26001
#define TUTO_26_INTERIOR_ITEMTOUCH0				26002
#define TUTO_26_INTERIOR_ALL0					26003
#define TUTO_26_INTERIOR_OK0					26004

#define TUTO_26_INTERIOR_MENUTOUCH1				26005
#define TUTO_26_INTERIOR_TABTOUCH1				26006
#define TUTO_26_INTERIOR_ITEMTOUCH1				26007
#define TUTO_26_INTERIOR_ALL1					26008
#define TUTO_26_INTERIOR_OK1					26009
#define TUTO_26_RESULT							26010


#define TUTO_27_HELP_FLOORMOVE0					27000
#define TUTO_27_HELP_FLOORMOVE1					27001

#define TUTO_27_HELP_HELP						27002

#define TUTO_27_HELP_SOCIALINFO					27003
#define TUTO_27_RESULT							27004


#define TUTO_28_ADDFRIEND_MENUTOUCH				28000
#define TUTO_28_ADDFRIEND_ADDTOUCH				28001
#define TUTO_28_ADDFRIEND_ADDINFO				28002
#define TUTO_28_ADDFRIEND_ADDEXIT				28003
#define TUTO_28_ADDFRIEND_ADDRESULT				28004
#define TUTO_28_RESULT							28005


#define TUTO_29_FASHIONSHOWRANK_MENUTOUCH		29000
#define TUTO_29_FASHIONSHOWRANK_REPLAY			29001
#define TUTO_29_RESULT							29002


#define TUTO_30_INTERIOR_TABTOUCH				30000
#define TUTO_30_INTERIOR_OK						30001
#define TUTO_30_RESULT							30002


typedef struct
{
	int totalNum;
	int nowNum;
	int anyCnt;
	int state;
	
	M_Boolean isTutoClean;
	int resultNum;
	
	
	M_Boolean isTemp;
	int tempValue;
	
} XQUESTTUTO;
extern XQUESTTUTO xQuestTuto;


///////////////////////퀘스트/////////////////////
#define QUEST_STATE_WAIT		0	//받기전 발생체크하여 컷씬발생
#define QUEST_STATE_NEW			1	//확인안한것
#define QUEST_STATE_PLAY		2	//퀘스트 진행 달성조건 확인하기
#define QUEST_STATE_RESULT		3	//달성 성공


typedef struct
{
	int totalNum;
	int nowNum;
	int state;
} XQUESTMAIN;
extern XQUESTMAIN xQuestMain;





#define QUESTMAINMAX			512
typedef struct
{
	int lv;
	int endQuestNum;
	int npcCode;
	int dialogNum;
	int fastCash;
	
	M_Boolean isCheckClean[3];
	int checkType[3];
	int checkMax[3];
	int checkNow[3];
	int checkCode[3];
	int checkCodeSub[3];
	
	int giftType[3];
	int giftCode[3];
	SECURITY giftMax[3];
	int giftNow[3];
	
	char strTitle[128];
	char strInfo[512];
	char strEnd[256];
	
	char strSubInfo[256];
	int iconNum;
	
} XQUESTDATAMAIN;
extern XQUESTDATAMAIN xQuestDataMain[QUESTMAINMAX];








#define QUESTNORMALMAX			512

typedef struct
{
	M_Boolean isClear;
	
	int state;
	int lv;
	int npcCode;
	int endQuestNum;
	int dialogNum;
	int fastCash;
	
	M_Boolean isCheckClean[3];
	int checkType[3];
	int checkMax[3];
	int checkNow[3];
	int checkCode[3];
	int checkCodeSub[3];
	
	int giftType[3];
	int giftCode[3];
	SECURITY giftMax[3];
	int giftNow[3];
	
	char strTitle[128];
	char strInfo[512];
	char strEnd[256];
	char strSubInfo[256];
	int iconNum;
	
} XQUESTDATANORMAL;
extern XQUESTDATANORMAL xQuestDataNormal[QUESTNORMALMAX];





#define QUEST_TYPE_MAIN		0
#define QUEST_TYPE_NORMAL	1

#define QUESTSLOTMAX		40

typedef struct
{
	int type;
	int questNum;
	
	int barCheckNum;
	int barAnyCnt;
} XQUESTINFOSLOT;


#define QUESTINFO_STATE_PLAY			0
#define QUESTINFO_STATE_GIFTPOPUP		1

typedef struct
{
	int state;
	int totalNumNormal;
	
	//월드맵 아이콘 부분
	XDRAGSCROLL xDragScrollSlot;
	XTOUCH xTouchSlot[5];
	XTOUCH xTouchClip;
	
	int totalNum;
	XQUESTINFOSLOT xSlot[QUESTSLOTMAX];
	char strBarText[QUESTSLOTMAX][64];
	int selectSlot;
	
	
	//퀘스트 인포부분
	XTOUCH xTouchMove[3];
	XTOUCH xTouchFastCash;
	XTOUCH xTouchGiftIcon;
	
	int cleanNormal;
	
	
	
	/////////
	M_Boolean isCC;
	int totalProductionSlotCode;
	int totalInteriorSlotCode;
	int totalStaffSlotCode;
	int staffSlotCode[32];
	int productionSlotCode[32];
	int interiorSlotCode[32];

	
	
	
	/////////////////
	M_Boolean isShowwindowInfo;
	M_Boolean isProductionInfo;
	
} XQUESTINFO;
extern XQUESTINFO xQuestInfo;



#define NPCMAX		12

typedef struct
{
	char strName[64];

} XNPC;
extern XNPC xNpc[NPCMAX];



#define MODELSKILLMAX		128

#define MODELSKILL_TYPE_SELLMONEY_FLOOR1		0
#define MODELSKILL_TYPE_SELLEXP_FLOOR1			1
#define MODELSKILL_TYPE_TREND_TIME				2
#define MODELSKILL_TYPE_TREND_PER				3
//4
#define MODELSKILL_TYPE_FAME					5
#define MODELSKILL_TYPE_MODELGIFT_TIME			6
#define MODELSKILL_TYPE_MODELGIFT_PER			7
#define MODELSKILL_TYPE_MINIGAME_CANDY			8
#define MODELSKILL_TYPE_RUNWAY_CANDY			9
#define MODELSKILL_TYPE_MINIGAME_SNOW			10

#define MODELSKILL_TYPE_CHAIR_COFFEE			11
#define MODELSKILL_TYPE_CHAIR_PHONE				12
#define MODELSKILL_TYPE_CHAIR_IPAD				13
#define MODELSKILL_TYPE_CHAIR_BOOK				14


#define MODELSKILL_TYPE_SEX_MAN					15
#define MODELSKILL_TYPE_SEX_WOMAN				16
#define MODELSKILL_TYPE_SEX_PORTER				17
#define MODELSKILL_TYPE_SEX_PORTER_MM			18
#define MODELSKILL_TYPE_SEX_PORTER_WW			19


#define MODELSKILL_TYPE_HELPCOUNT				20
#define MODELSKILL_TYPE_MODELVOTE				21



#define MODELSKILL_TYPE_ORDER_SELECTITEM		22		//주문요청

#define MODELSKILL_TYPE_ORDER_TIME				23
#define MODELSKILL_TYPE_ORDER_MONEY				24
#define MODELSKILL_TYPE_ORDER_RECV				25


#define MODELSKILL_RUNWAY_CENCEPT_BONUS0		26
#define MODELSKILL_RUNWAY_CENCEPT_BONUS1		27
#define MODELSKILL_RUNWAY_CENCEPT_BONUS2		28
#define MODELSKILL_RUNWAY_CENCEPT_BONUS3		29
#define MODELSKILL_RUNWAY_CENCEPT_BONUS4		30
#define MODELSKILL_RUNWAY_CENCEPT_BONUS5		31
#define MODELSKILL_RUNWAY_CENCEPT_BONUS6		32
#define MODELSKILL_RUNWAY_CENCEPT_BONUS7		33


#define MODELSKILL_RUNWAY_SNOW					34

#define MODELSKILL_RUNWAY_COLOR_BONUS0			35
#define MODELSKILL_RUNWAY_COLOR_BONUS1			36
#define MODELSKILL_RUNWAY_COLOR_BONUS2			37
#define MODELSKILL_RUNWAY_COLOR_BONUS3			38
#define MODELSKILL_RUNWAY_COLOR_BONUS4			39
#define MODELSKILL_RUNWAY_COLOR_BONUS5			40
#define MODELSKILL_RUNWAY_COLOR_BONUS6			41
#define MODELSKILL_RUNWAY_COLOR_BONUS7			42
#define MODELSKILL_RUNWAY_COLOR_BONUS8			43
#define MODELSKILL_RUNWAY_COLOR_BONUS9			44
#define MODELSKILL_RUNWAY_COLOR_BONUS10			45
#define MODELSKILL_RUNWAY_COLOR_BONUS11			46
#define MODELSKILL_RUNWAY_LAYERED			47

#define MODELSKILL_RUNWAY_GOLD					49
#define MODELSKILL_RUNWAY_EXP					50

#define MODELSKILL_TYPE_CAR_SPEED				51
#define MODELSKILL_TYPE_SELLMONEY_FLOOR2		55
#define MODELSKILL_TYPE_SELLEXP_FLOOR2			56



typedef struct
{
	int bonusPer[MODELSKILLMAX];
	
	
	
	
	M_Boolean isWorldMapUiInfoBoxOpen;
	int totalWorldMapUiSlot;
	int slotWorldMapUiSlot[12];
	int selectWorldMapUiSlot;
	XTOUCH xTouchWorldMapUiSlot[12];
	XTOUCH xTouchWorldMapUiIcon;
	
} XMODELSKILL;
extern XMODELSKILL xModelSkill;







#define MODELDATAMAX		256


#define MODEL_GIFTTYPE_GOLD		0
#define MODEL_GIFTTYPE_LOOK		1
#define MODEL_GIFTTYPE_CANDY	2
#define MODEL_GIFTTYPE_EXP		3
typedef struct
{
	char strName[64];
	int imgNum;
	int grade;
	int sex;
	int lv;
	int layeredNum;
	int tema;
	int priceType;
	int price;
	
	int upGradeMax;
		
	SECURITY giftTime;
	int giftType;
	SECURITY giftNum;
	
	int giftPer[10];
	int giftPerType;
	int giftIconNum;
	
	
	M_Boolean isOpen;
	
	M_Boolean isOneHead;
	M_Boolean isSell;
	
	int modelSkillType;
	int totalSkillNum;
	int skillType[5];
	int skillPer[5];
	
	
	int totalFittingLayered;
	int fittingLayered[16];
	M_Boolean isFittingInOut;
	
} XMODELDATA;
extern XMODELDATA xModelData[MODELDATAMAX];









#define MODELSELLPER		10
#define MODELSELLCASH		2700

#define INVENTORYMODELMAX		256


#define MODELCOLLECT_STATE_MAIN						0
#define MODELCOLLECT_STATE_MAINCASTING				1
#define MODELCOLLECT_STATE_MAININFO					2
#define MODELCOLLECT_STATE_MAINUPGRADE				3

#define MODELCOLLECT_STATE_SELECTMODEL				4
#define MODELCOLLECT_STATE_SELECTMODELCASTING		5


#define MODELCOLLECT_STATE_LIST						6
#define MODELCOLLECT_STATE_LISTCASTING				7
#define MODELCOLLECT_STATE_LISTINFO					8
#define MODELCOLLECT_STATE_LISTUPGRADE				9

#define MODELCOLLECT_STATE_MAINGIFTINFO				10
#define MODELCOLLECT_STATE_MAINGIFTRESULT			11

#define MODELCOLLECT_STATE_FITTING					12

#define MODELCOLLECT_STATE_HELP						13




#define MODELCOLLECT_FRIEND_STATE_MAIN			0
#define MODELCOLLECT_FRIEND_STATE_SHOP			1
#define MODELCOLLECT_FRIEND_STATE_BUYPOPUP		2


typedef struct
{
	int state;
	
	int totalInventoryModel;
	int totalInventoryModelMax;
	
	int totalInventoryModel_FRIEND;
	

	int inventoryNum;


	XDRAGSCROLL xDragScrollS;
		
	
	XTOUCH xTouchEditBtn;
	XTOUCH xTouchCastingBtn;
	XTOUCH xTouchFashionShowBtn;
	XTOUCH xTouchModelListBtn;
	XTOUCH xTouchHelpBtn;
	
	
	XTOUCH xTouchCasting[2];
	
	
	
	int totalListNum;
	int listNumSlot[INVENTORYMODELMAX];
	

	
	//모델
	XTOUCH xTouchGiftBtn;
	
	
	//모델리스트
	M_Boolean isListTabOpen;
	XTOUCH xTouchListTab[6];
	int listTabNum;
	
	XTOUCH xTouchSelectSlot[20];
	XTOUCH xTouchBtn[5];
		
	

	//등급별 슬롯
	int totalRanDomSlot;
	int totalRanDomSlotA;
	int totalRanDomSlotB;
	int totalRanDomSlotC;
	int totalRanDomSlotS;
	int ranDomSlot[MODELDATAMAX];
	int ranDomSlotC[MODELDATAMAX];
	int ranDomSlotB[MODELDATAMAX];
	int ranDomSlotA[MODELDATAMAX];
	int ranDomSlotS[MODELDATAMAX];
	
	
	///모델뽑기
	int newModelCode;

	int newModelCountNum;
	int newModelTotal[2];
	int newModelPer[10][4];
	int newModelPer_Cash[10][4];
	
	int newModelCount[10];
	int newModelCount_Cash[10];
	
	
	int newModelCountPlus[10][4];
	int newModelCountPlus_Cash[10][4];

			
	//////////////////친구////////////
	int modelFriendDataSlotNum;
	int totalModelFriendShop;
	
	int selectModelShopSlot;
	XCATALOGSLOT modelFriendShopSlot[30];
	
	XDRAGSCROLL xDragScrollFriendShop;
	XTOUCH xTouchFriendVote[10];
	
	XTOUCH xTouchAllV;

	XTOUCH xTouchV[5];
	XTOUCH xTouchBuyBtn[5];
	
	///////////////////////
	XTOUCH xTouchInfoBtn[3];
	
	int fittingInState;
	
	///////////////main/////
	int selectMainSlot;
	
	int selectListSlot;
	
	int infoInventoryNum;
	
	XTOUCH xTouchGiftFastCash;
	
	
	int selectHelpTab;
	XTOUCH xTouchHelpTab[2];
	
	
	//모델 업그레이드 확률 및 가격
	int upgradePer[10][10][10];//[냐등급][업그레이드단계][재료등급]
	int upgradePrice[10][10];
	int mixPer[10];
	int mixPrice[10];
	
	//패션쇼 모델보너스
	int fashionShowBonusTotal[5];
	int fashionShowBonusPer[5][10];
	int fashionShowBonusPointMin[5][10];
	int fashionShowBonusPointMax[5][10];
	int fashionShowBonusPointType[5][10];
	
    
    
    int blinkEffAnyCnt_sex[MODELDATAMAX];
    
    
    
    
    
	
} XMODELD;
extern XMODELD xModel;






#define MODELMAINSLOTMAX	5

#define MODELMAINSLOT_STATE_LOCK		0
#define MODELMAINSLOT_STATE_EMPTY		1
#define MODELMAINSLOT_STATE_WAIT		2
#define MODELMAINSLOT_STATE_PLAY		3
typedef struct
{
	int state;
	int modelKey;
	int inventoryNum;
	
	M_Int64 endTime;
	XTOUCH xTouchSlot;
	XTOUCH xTouchBtn;
	
	int okAnyCnt;
	
	
	int ingAnyCnt;
	
	int openLv;
	int openPrice[2];
	
	
	
	
} XMODELMAINSLOT;
extern XMODELMAINSLOT xModelMainSlot[MODELMAINSLOTMAX];
extern XMODELMAINSLOT xModelMainSlotFRIEND[MODELMAINSLOTMAX];


#define MODELEFFMAX	10

typedef struct
{
	int totalNum;	
	int anyCnt[MODELEFFMAX];
	int x[MODELEFFMAX];
	int y[MODELEFFMAX];
	int resize[MODELEFFMAX];
} XMODELEFF;
extern XMODELEFF xModelEff;



#define MODELUPGRADEANYCNT		100

#define MODELUPGRADE_STATE_SLOTMOVE				0
#define MODELUPGRADE_STATE_GAGE					1
#define MODELUPGRADE_STATE_RESULT_SUCCESS		2
typedef struct
{
	int inventoryNum;
	
	
	int totalModelList;
	int modelListSlot[INVENTORYMODELMAX];
	
	
	XDRAGSCROLL xDragScrollS;
	int selectSlot;
	XTOUCH xTouchSelectSlot[4];
	
	
	M_Boolean isUpgrade;
	int upgradeType;
	int anyCnt;
	int upgradeState;

	
	
	
	
	///////////////날라가는 슬롯
	int slotX;
	int slotY;
	int slotEndX;
	int slotEndY;
	
} XMODELUPGRADE;


extern XMODELUPGRADE xModelUpGrade;


typedef struct
{
	int inventoryNum;
} XMODELFITTING;
extern XMODELFITTING xModelFitting;



typedef struct
{
	int code;
	int upGrade;
	int key;
	
	XFITTINGLAYER xF;
	
	M_Boolean isMapShow;
		
	int vote;
    

    

} XINVENTORYMODEL;
extern XINVENTORYMODEL xInventoryModel[INVENTORYMODELMAX];
extern XINVENTORYMODEL xInventoryModel_FRIEND[INVENTORYMODELMAX];






#define FASHIONSHOW_SELECTMAX				5

#define FASHIONSHOW_STATE_MAIN				0
#define FASHIONSHOW_STATE_SELECTMODEL		1
#define FASHIONSHOW_STATE_FITTING			2
#define FASHIONSHOW_STATE_RUNWAY			3
#define FASHIONSHOW_STATE_RUNWAYRESULT_NETWAIT	4
#define FASHIONSHOW_STATE_RUNWAYRESULT			5
#define FASHIONSHOW_STATE_RANKCHANGE			6

#define FASHIONSHOW_STATE_INFO				7
#define FASHIONSHOW_STATE_NOTICE_MAIN				8

#define FASHIONSHOW_STATE_DRESSCODE				9

#define FASHIONSHOW_STATE_RESULTBONUS			10
#define FASHIONSHOW_STATE_LICENCEOPEN			11




typedef struct
{
	
	M_Boolean isVote;
	int userCode;
	int friendDataNum;
	int totalPeople;
	int rank;
	int score;
	int vote;
	
	int totalModel;
	int modelUpgrade[5];
	int modelCode[5];
	XFITTINGLAYER xF[5];
	
} XFASHIONSHOWRANKSLOT;


#define FASHIONSHOWRANKMAX		100

typedef struct
{
	int state;
	//////메인
	XTOUCH xTouchNoticeBtn;
	XTOUCH xTouchStartBtn;
	char strNoticeBar[256];
	char strNotice[512];

	int noticeBarAnyCnt;
	
	//////랭킹
	XTOUCH xTouchRankTabSBtn[3];
	int selectRankTabS;
	int selectRankSlot;
	XDRAGSCROLL xDragScrollRank;
	XTOUCH xTouchRankSlot[10];
	XTOUCH xTouchRankBtn[2][10];
	
	int nowPageNumList[5];
	
	int totalRankList[5];
	XFASHIONSHOWRANKSLOT xRankSlot[5][FASHIONSHOWRANKMAX];
	XFASHIONSHOWRANKSLOT xMyRankSlot[5];
	XFASHIONSHOWRANKSLOT xRankChangeSlot;
	
	
	
			
	//모델선택
	XDRAGSCROLL xDragScrollSelectModel;
	int selectModelSlot;
	int selectSlot[5];
	int selectSlotCnt;
	XTOUCH xTouchSelectSlot[5];
	XTOUCH xTouchFittingSlot[5];
	
	
	
	XTOUCH xTouchDressCodeIcon;
	
	
	//서버 조건
	int severNum;
	M_Boolean isSeverNumLoad;
	int serverTotalTrend;
	int severTrendSlot[5];
	
	int serverTotalConcept;
	int severConceptSlot[5];
	
	int serverTotalColor;
	int severColorSlot[5];
	
	int serverSex;
	int serverInOut;
	int serverLayeredMin;
	int serverLayeredMax;
	
	M_Boolean isShowDressCode;
	
	
	//베스트스코어연출
	M_Boolean isBestScoreEvent;
	int bestScoreAnyCnt;
	int bestScore;
	int bestRank;
	//순위변경연출
	M_Boolean isRankChangeEvent;
	int rankChangeAnyCnt;
	//보상
	int selectNoticeTab;
	
	int rankGiftLookWorld[20];
	int rankGiftLookFriend;
	
	
	M_Boolean isTodayFree;
	
	
	
	int	totalFashionLicence;
	int fashionLicenceSlot[64];
	int fashionLicenceAnyCnt;
	
	
	SECURITY userTired;
	
    
    int maxCount;
    int remainCount;
    
    
    
    
    
} XFASHIONSHOW;
extern XFASHIONSHOW xFashionShow;





#define FASHIONSHOWSERVERMAX		30

typedef struct
{
	int trend[3];
	int concept[2];
	int color[2];
	int sex;
	int inOut;
	int layeredMin;
	int layeredMax;
} XFASHIONSHOWSERVER;
extern XFASHIONSHOWSERVER xFashionShowServer[FASHIONSHOWSERVERMAX];



#define VOTELISTMAX		100
typedef struct
{
	int totalNum;
	int userNum[VOTELISTMAX];
} XVOTELIST;
extern XVOTELIST xVoteList;



typedef struct
{
	XTOUCH xTouchBtn[2];
	XFASHIONSHOWRANKSLOT xRankSlot;
} XFASHIONSHOWINFO;
extern XFASHIONSHOWINFO xFashionShowInfo;






typedef struct
{
	int totalMarketing;
	int maketingSlot[100];
	XDRAGSCROLL xDragScroll;
} XTRENDMAKERMODELINFO;
extern XTRENDMAKERMODELINFO xTrendMakerModelInfo;




#define RUNWAYMODEL_STATE_WAIT				0
#define RUNWAYMODEL_STATE_START0			1
#define RUNWAYMODEL_STATE_START1			2
#define RUNWAYMODEL_STATE_START2			3
#define RUNWAYMODEL_STATE_SHOW				4
#define RUNWAYMODEL_STATE_END0				5
#define RUNWAYMODEL_STATE_END1				6
#define RUNWAYMODEL_STATE_END2				7

#define RUNWAYMODEL_STATE_END				8


#define RUNWAY_STATE_PLAY		0

#define RUNWAY_INTYPE_PLAY		0
#define RUNWAY_INTYPE_REPLAY	1
typedef struct
{
	int state;
	int anyCnt;
	
	int inType;

	int nowModel;
	int maxModel;
	XTOUCH xTouchSkip;
	
	int modelScore[5];
	int totalFashionShowScore;
	

	int modelCode[5];
	int modelUpgrade[5];
	XFITTINGLAYER xF_Model[5];
	int nowDelay[5];
	int nowFrame[5];
	int modelState[5];
	int modelAnyCnt[5];
	int modelX[5];
	int modelY[5];
	
	int modelBonusAnyCnt;
	int totalModelBonus;
	int modelBonusType[5];					
	int modelBonusPoint[5];
	int modelBonusModelCode[5];
	XIMG imgBonusIcon[5];
	
	int totalFriendModel;
	XFITTINGLAYER xF_Friend[20];
	int modelCode_Friend[20];
	int friendDataSlot[20];

	
	
	
	int applaudNum[20];
	int actType_Guest[20];
	int nowFrame_Guest[20];
	int nowDelay_Guest[20];
	char strNickName_Guest[20][64];
	XFACE xFace_Guest[20];
	XFITTINGLAYER xF_Guest[20];
	
	
	int dslrCnt;
	
	
	
	
	
	//////점수
	float fashionColorPer[15][15];
	float fashionConceptPer[15][15];
	
} XRUNWAY;
extern XRUNWAY xRunWay;


#define DROPMOVE_GOLDX	(lcdW-167)
#define DROPMOVE_GOLDY	28
//
#define DROPMOVE_EXPX	131
#define DROPMOVE_EXPY	73
//
#define DROPMOVE_FAMEX	131
#define DROPMOVE_FAMEY	100

#define DROPMOVE_FASHIONX_ACCESSORY	(lcdW-60)
#define DROPMOVE_FASHIONY_ACCESSORY	(150)

#define DROPMOVE_FASHIONX_HANGER	(lcdW-150)
#define DROPMOVE_FASHIONY_HANGER	(150)




#define DROPMOVE_CANDYX	(lcdW-127)
#define DROPMOVE_CANDYY	28

#define DROPICONMAX			12
#define DROPICON_STATE_DONT			0
#define DROPICON_STATE_DROP			1
#define DROPICON_STATE_MOVE			2

typedef struct
{
	int state;
	int xPos;
	int yPos;
	
	int type[3];
	int num[3];
	int anyCnt;
	int x[3];
	int y[3];
	int w[3];
	int h[3];
	int hoveX[3];
	int moveY[3];
	int alpha[3];
	int blend[3];
	int scale[3];

} XDROPICON;
extern XDROPICON xDropIcon[DROPICONMAX];



#define FASHIONDROPMAX				6
#define FASHIONDROP_STATE_DONT		0
#define FASHIONDROP_STATE_PLAY		1

typedef struct
{
	int state[FASHIONDROPMAX];
	int anyCnt[FASHIONDROPMAX];
	int xPos[FASHIONDROPMAX];
	int yPos[FASHIONDROPMAX];
	int scale[FASHIONDROPMAX];
	int xPosEnd[FASHIONDROPMAX];
	int yPosEnd[FASHIONDROPMAX];
	int scaleEnd[FASHIONDROPMAX];
	int code[FASHIONDROPMAX];
	
	
	//////////////////생산정보///////////////
	int x_productionList[8];
	int y_productionList[8];
	int scale_productionList[8];
		
	int x_productionMenu[PRODUCTIONMENUSLOTMAX];
	int y_productionMenu[PRODUCTIONMENUSLOTMAX];
	int scale_productionMenu[PRODUCTIONMENUSLOTMAX];
	
	
	int x_sellList[15];
	int y_sellList[15];
	int scale_sellList[15];
	
	int x_sellSlot[15];
	int y_sellSlot[15];
	int scale_sellSlot[15];
	
	
} XFASHIONDROP;
extern XFASHIONDROP xFashionDrop;



#define COLORPAPERMAX		128
#define COLORPAPER_STATE_DONT	0
#define COLORPAPER_STATE_PLAY	1
typedef struct
{
	int state;
	int endCntNow;
	int endCntMax;
	int xPos;
	int yPos;
	int speed;
	int reSize;
	int rot;
	int rotSpeed;
	int r;
	int g;
	int b;
} XCOLORPAPER;
extern XCOLORPAPER xColorPaper[COLORPAPERMAX];


#define FLASHEFF		20

#define FLASHEFF_STATE_DONT	0
#define FLASHEFF_STATE_PLAY	1
typedef struct
{
	int state;
	int anyCnt;
	int x;
	int y;
	int resize;
	M_Boolean isMapMode;
} XFLASHEFF;
extern XFLASHEFF xFlashEff[FLASHEFF];

#define RUNWAYEFFMAX		30
#define RUNWAYEFF_STATE_DONT	0
#define RUNWAYEFF_STATE_PLAY	1

#define RUNWAYEFF_TYPE_DONT		0
#define RUNWAYEFF_TYPE_0		1
#define RUNWAYEFF_TYPE_1		2
#define RUNWAYEFF_TYPE_2		3

#define RUNWAYEFF

typedef struct
{
	//플레쉬 관리
	int flashSpeed;
	M_Boolean isFlashFast;
	int flashAnyCnt;
	
	
	//무대관리
	int changeTime;
	int type;
	int state[RUNWAYEFFMAX];
	int x[RUNWAYEFFMAX];
	int speed[RUNWAYEFFMAX];
	int rectW[RUNWAYEFFMAX];
	int anyCnt[RUNWAYEFFMAX];
	int r[RUNWAYEFFMAX];
	int g[RUNWAYEFFMAX];
	int b[RUNWAYEFFMAX];
} XRUNWAYEFF;
extern XRUNWAYEFF xRunWayEff;


#define SPOTLIGHTMAX	2
typedef struct
{
	int wait[SPOTLIGHTMAX];
	
	int type[SPOTLIGHTMAX];
	int x[SPOTLIGHTMAX];
	int y[SPOTLIGHTMAX];
	float fspeed[SPOTLIGHTMAX];
	int pointX[SPOTLIGHTMAX];
	int pointY[SPOTLIGHTMAX];
		
} XSPOTLIGHT;
extern XSPOTLIGHT xSpotLight;


#define RUNWAYMINIGAMEMAX		5
#define RUNWAYMINIGAME_STATE_DONT	0
#define RUNWAYMINIGAME_STATE_PLAY	1
#define RUNWAYMINIGAME_STATE_END	2
typedef struct
{
	int x;
	int y;
	int state;
	int anyCnt;
	int type;
	
	M_Boolean isOk;
	int bonusType;
	int bonusPoint;
	
	XTOUCH xTouch;
} XRUNWAYMINIGAME;
extern XRUNWAYMINIGAME xRunWayMiniGame[RUNWAYMINIGAMEMAX];

#define KAKAOINVITE_TYPE_GOLD		0
#define KAKAOINVITE_TYPE_LOOK		1
#define KAKAOINVITE_TYPE_CANDY		2
#define KAKAOINVITE_TYPE_INTERIOR	3

#define KAKAOINVITE_TYPE_MODEL_CA	4
#define KAKAOINVITE_TYPE_MODEL_BS	5

typedef struct
{
	SECURITY totalKakaoInvite;
	int inviteType[5];
	SECURITY inviteNum[5];
	int inviteIconNum[5];
	char strInviteText[5][128];
	
	int bonusXPos;
	int bonusYPos;
} XKAKAO;
extern XKAKAO xKakao;









#define HELPINFOMAX		10

#define HELPINFO_STATE_PLAY	0
#define HELPINFO_STATE_DIE	1
typedef struct
{
	int totalNum;
	int anyCnt;
	int state;
	char strText[HELPINFOMAX][128];
	
	XTOUCH xTouchInfoBar;
} XHELPINFO;
extern XHELPINFO xHelpInfo;


extern XHELPINFO xHelpInfoCenter;
#define DEBUGMAX		20
typedef struct
{
	int logCnt;
	char strSprintf[128];
	int totalNum;
	char strTextp[DEBUGMAX][128];
} XDEBUG;
extern XDEBUG xDebug;



#define FIREMAX			150
#define FIRE_STATE_DONT	0
#define FIRE_STATE_PLAY	1
typedef struct
{
	int state;
	int x;
	int y;
	float fSpeed;
	float fRad;
	int imageNum;
	M_Boolean isReSize;
	int resizeCnt;
	int reSize;
	int anyCnt;
	int anyCntMax;
	
} XFIRE;
extern XFIRE xFire[FIREMAX];


typedef struct
{
	int selectSellTableNum;
	
	XTOUCH xTouchSlot[3];

} XSOCIALPROFILE;
extern XSOCIALPROFILE xSocialProfile;



#define ACCESSBONUS_LIMITDAY		3
#define ACCESSBONUSSLOTMAX			20

#define ACCESSBONUS_TYPE_GOLD		0
#define ACCESSBONUS_TYPE_LOOK		1
#define ACCESSBONUS_TYPE_CANDY		2
#define ACCESSBONUS_TYPE_MODEL		3
#define ACCESSBONUS_TYPE_TREND		4

#define ACCESSBONUS_STATE_MAIN		0
#define ACCESSBONUS_STATE_STAMP		1
#define ACCESSBONUS_STATE_RESULT	2
typedef struct
{
	int state;
	int anyCnt;
	int stampX;
	int stampY;
	
	int accessCountShow;
	int accessCount;
	int accessDay;
	
	
	int slotType[ACCESSBONUSSLOTMAX];
	int slotNum[ACCESSBONUSSLOTMAX];
	int iconNum[ACCESSBONUSSLOTMAX];
	XIMG imgIcon[ACCESSBONUSSLOTMAX];
	
	
} XACCESSBONUS;
extern XACCESSBONUS xAccessBonus;


#define WASTEMAX	3

#define WASTE_STATE_DONT		0
#define WASTE_STATE_WAIT		1
#define WASTE_STATE_CLEAN		2
typedef struct
{
	int state[FLOORMAX][WASTEMAX];
	int anyCnt[FLOORMAX][WASTEMAX];
	int type[FLOORMAX][WASTEMAX];
	
	int mapX[FLOORMAX][WASTEMAX];
	int mapY[FLOORMAX][WASTEMAX];
} XWASTE;
extern XWASTE xWaste;








typedef struct
{
	double endTime;
} XSLEEPTIME;
extern XSLEEPTIME xSleepTime;



typedef struct
{
	int totalNum;
	int slotCode[30];
	int slotSalePrice[30];
	
	XDRAGSCROLL xDragScroll;
	XTOUCH xTouchSlot[30];
	
	int selectSlot;
	char strDay[128];
	
	M_Boolean isOpen;
	
	
	XTOUCH xTouchWorldMapIcon;
	
	
	
	XGLITTEREFF xGlitterEff;
	
} XSALESHOP;
extern XSALESHOP xSaleShop;



#define FLOORWALLTILEERRQUEUEMAX	128
typedef struct
{
	M_Boolean isOneLoop;	//한번만 사용
	int totalNum;
	int code[FLOORWALLTILEERRQUEUEMAX];
	int key[FLOORWALLTILEERRQUEUEMAX];
	int floor[FLOORWALLTILEERRQUEUEMAX];
	int x[FLOORWALLTILEERRQUEUEMAX];
	int y[FLOORWALLTILEERRQUEUEMAX];
	
} XFLOORWALLTILEERRQUEUE;
extern XFLOORWALLTILEERRQUEUE xFloorWallTileErrQueue;




#define BUFFMAX		16

#define BUFF_TYPE_SELLMONEY		0
#define BUFF_TYPE_SELLEXP		1
#define BUFF_TYPE_CARORDER		2
#define BUFF_TYPE_INSHOP		3

typedef struct
{
	//선호도 증가버프
	//경험치 추가 획득버프
	//골드 추가 획득버프
	//주문배송 시간 감소버프
		
	M_Boolean isOpen[BUFFMAX];
	int bonusPer[BUFFMAX];
	
	int startYY;
	int startMM;
	int startDD;
	int startHH;
	
	int endYY;
	int endMM;
	int endDD;
	int endHH;
	
	
} XBUFF;
extern XBUFF xBuff;


#define G9BONUSCASH		10

typedef struct
{
	M_Boolean isNet;
	M_Boolean isOpen;
	
	M_Boolean isInstallOkNetSend;
	
	M_Boolean isCheckInstall;
	int checkInstallCnt;

	XTOUCH xTouch;
	XIMG imgG9Icon;
} XG9;
extern XG9 xG9;




#define COLLECTIONSLOT_TYPE_MODELCODE			0
#define COLLECTIONSLOT_TYPE_MODELGRADEBAR		1
typedef struct
{
	int type;
	int code;
	M_Boolean isNew;
	XTOUCH xTouch;
} XCOLLECTIONSLOT;


#define COLLECTION_STATE_MAIN				0
#define COLLECTION_STATE_MODELINFOPOPUP		1



#define COLLECTION_STATE_FASHIONTHEMESELECT		2
#define COLLECTION_STATE_FASHIONTHEMEMAIN		3



#define COLLECTIONSLOTMAX		256
#define COLLECTIONTABMAX		2

#define FASHIONTHEMEMAX			64
typedef struct
{
	int state;
	
	int selectTabB;
	int selectSlot;
	int selectSkill;
	XTOUCH xTouchTabB[COLLECTIONTABMAX];
	XTOUCH xTouchSkill[3];
	XTOUCH xTouchInfo;
	
	
	XDRAGSCROLL xDragScroll;
	
	int totalSlot;
	XCOLLECTIONSLOT xSlot[COLLECTIONSLOTMAX];
	
	
	/////패션테마
	int totalFashionTheme;
	int fashionThemeList[FASHIONTHEMEMAX];
	char strFashionTheme[FASHIONTHEMEMAX][32];
	M_Boolean isFashionThemeNew[FASHIONTHEMEMAX];
	M_Boolean isFashionThemeFittingInOut[FASHIONTHEMEMAX];
	XTOUCH xTouchFashionThemeList[FASHIONTHEMEMAX];
	
	
	int selectFashionThemeList;
	XDRAGSCROLL xDragScrollTheme;
	XIMG imgFashionThemeIcon[FASHIONTHEMEMAX];
	
	
	/////패션리스트
	int selectSlotFashion;
	int totalFashionList;
	XTOUCH xTouchFashionList[64];
	int fashionList[64];
	XDRAGSCROLL xDragScrollFashionList;

	
	
	
	int totalFashionThemeOpen[COLLECTIONSLOTMAX];
	int totalFashionThemeClose[COLLECTIONSLOTMAX];
	
} XCOLLECTION;
extern XCOLLECTION xCollection;




#define RTF_TYPE_ALL		0	//전체루프
#define RTF_TYPE_ONE		1	//최종단일루프
typedef struct
{
	int type;
	int beforeFrame;
	int nowFrame;
	M_Int64 startTimeMillisecond;
} XRTF;
extern XRTF *xRtfMain;
extern XRTF xRtfDemo;

#define RTFQUEUEMAX	32
typedef struct
{
	int totalNum;
	int caseNum[RTFQUEUEMAX];
} XRTFQUEUE;
extern XRTFQUEUE xRtfQueue;


typedef struct
{
	XTOUCH xTouchWorldMapIcon;
	int totalSlot;
	XDRAGSCROLL xDragScroll;
	XTOUCH xTouhSlot[12];
	int friendUserNum;
} XCASHGIFT;
extern XCASHGIFT xCashGift;



typedef struct
{
    char strName[128];
    char strNameLine[128];
    int event;
    int sort;
    int price;
    int nowCount;
    int maxCount;
    int state;
    char strInfo[128];
    
    char strUrl[128];
    
} XMILEAGEDATASLOT;


#define MILEAGETYPEMAX      4
#define MILEAGELISTEMAX     128
typedef struct
{
    XMILEAGEDATASLOT xSlot[MILEAGETYPEMAX][MILEAGELISTEMAX];
} XMILEAGEDATA;
extern XMILEAGEDATA xMileageData;



#define MILEAGEPRICEUNIT      1000


#define MILEAGESHOPCATEGORYMAX      7
#define MILEAGESHOP_CATEGORY_10000      0
#define MILEAGESHOP_CATEGORY_20000      1
#define MILEAGESHOP_CATEGORY_30000      2
#define MILEAGESHOP_CATEGORY_TOP        3
#define MILEAGESHOP_CATEGORY_BOTTOM     4
#define MILEAGESHOP_CATEGORY_ONEPIECE     5
#define MILEAGESHOP_CATEGORY_ETC     6



#define MILEAGESHOP_STATE_INITDATA      0
#define MILEAGESHOP_STATE_INITNET       1
#define MILEAGESHOP_STATE_PLAY          2
#define MILEAGESHOP_STATE_POPUP         3
#define MILEAGESHOP_STATE_SENDPOPUP      4
#define MILEAGESHOP_STATE_SENDPOPUP_BUY      5
#define MILEAGESHOP_STATE_SENDPOPUP_POPUP      6
#define MILEAGESHOP_STATE_BUYNET        7





#define MILEAGESHOP_STATE_INFO          8
#define MILEAGESHOP_STATE_INFO_POPUP    9
#define MILEAGESHOP_STATE_INFO_EDIT     10
#define MILEAGESHOP_STATE_INFO_EDITPOPUP     11


typedef struct
{
    bool isOpen;
    int prcChs;
    
    int cashBonus[32];
    
    int state;
    
    int selectCategoryTab;
    int selectSlot;
    
    int totalList;
    int listCode[256];

    
    
    char strPopupTitle[128];
    char strPopupText[256];
    
    XTOUCH xTouchPopupOk;
    XTOUCH xTouchPopupClr;
    
    
    
    XTOUCH xTouchBuy;
    XTOUCH xTouchName;
    XTOUCH xTouchAddress;
    XTOUCH xTouchPhone;
    
    char strName[128];
    char strAddress[256];
    char strPhone[128];
    
    
    
    XTOUCH xTouchInfo;
    XTOUCH xTouchExit;
    XTOUCH xTouchSlotLink[10];
    XTOUCH xTouchSlotBuy[10];
    
    XTOUCH xTouchCategory[10];
    
    XDRAGSCROLL xDragScroll;
    
} XMILEAGESHOP;
extern XMILEAGESHOP xMileageShop;



typedef struct
{
    int key;
    int code;
    int state;
    char strAddress[256];
    char strName[128];
    char strPhone[64];
    char strDate[64];
} XMILEAGESHOPINFOSLOT;


typedef struct
{
    
    XTOUCH xTouchExit;
    XDRAGSCROLL xDragScroll;
    
    XTOUCH xTouchEdit[16];
    
    int selectSlot;
    int totalNum;
    XMILEAGESHOPINFOSLOT xSlot[128];
    
} XMILEAGESHOPINFO;
extern XMILEAGESHOPINFO xMileageShopInfo;




#define MILEAGEUI_STATE_WAIT        0
#define MILEAGEUI_STATE_NEXT        1
typedef struct
{
    int state;
    
    
    XTOUCH xTouchMenu;
    
    int flowTime;
    int anyCnt;
    
    int selectSlot;
    int totalNum;
    int listCode[128];
} XMILEAGEUI;
extern XMILEAGEUI xMileageUi;




#define PROFILEPHOTOURLMAX          512

typedef struct
{
    int totalNum;
    char strUrl[PROFILEPHOTOURLMAX][256];
    XIMG imgPhoto[PROFILEPHOTOURLMAX];
    int downLoadImgState[PROFILEPHOTOURLMAX];
    
    
} XPROFILEPHOTOURL;
extern XPROFILEPHOTOURL xProfilePhotoUrl;



typedef struct
{
    int type;
    bool isSend;
    bool isNetOk;
    int slotNum;
    
} XNETEVENTSLOT;


#define NETEVENTMAXPHOTOURL        16

typedef struct
{
    int totalNum;
    XNETEVENTSLOT xSlot[NETEVENTMAXPHOTOURL];
} XNETEVENTPHOTOURL;
extern XNETEVENTPHOTOURL xNetEventPhotoUrl;



typedef struct
{
    bool isRecv;
    int remainDay;
    
    
    int pointDay;
    int price;

    
    XTOUCH xTouchUi;
    
    
    XTOUCH xTouchExit;
    XTOUCH xTouchOk;
    
} XPREPAY;
extern XPREPAY xPrePay;



#define EVENTQUESTMAX       128
#define EVENTQUESTDATAMAX       128


typedef struct
{
    int state;
    
    int giftType;
    int giftValue;
    
    
    
    
    
    
    int startYear;
    int startMonth;
    int startDay;
    int startHour;
    
    int endYear;
    int endMonth;
    int endDay;
    int endHour;
    
    
    
    int giftCnt;
    
    
} XEVENTQUESTMAIN;


typedef struct
{
    int state;
    
    int checkType;
    int checkCode;
    int checkCodeSub;
    int checkMax;
    int checkNow;
    
    int giftType;
    int giftValue;
    int giftMax;
    
    
    
    
    bool isCheckClean;
    
    
    
    
} XEVENTQUESTDETAIL;


#define EVENTQUESTMAIN_STATE_CLOSE          -1
#define EVENTQUESTMAIN_STATE_PLAY           0
#define EVENTQUESTMAIN_STATE_END            1


#define EVENTQUESTDETAIL_STATE_PLAY         0
#define EVENTQUESTDETAIL_STATE_END          1



typedef struct
{
    int totalNum[EVENTQUESTMAX];
    XEVENTQUESTMAIN xMain[EVENTQUESTMAX];
    XEVENTQUESTDETAIL xData[EVENTQUESTMAX][EVENTQUESTDATAMAX];
    
    
    XTOUCH xTouchExit;
    
    
    
    int totalTab;
    int listTab[128];
    int selectTab;
    
    
    XDRAGSCROLL xDragScrollTab;
    XTOUCH xTouchTab[32];
    
    
    XDRAGSCROLL xDragScroll[EVENTQUESTMAX];
    
    
    
    XTOUCH xTouchMainGift;
    int totalList;
    int listCode[EVENTQUESTDATAMAX];
    int selectSlot;
    XTOUCH xTouchGift[32];
    
    
    XTOUCH xTouchTabBg;
    int selectScroll;
    bool isNetLoad;
    
} XEVENTQUEST;
extern XEVENTQUEST xEventQuest;








#define EVENTQUESTUI_STATE_WAIT        0
#define EVENTQUESTUI_STATE_NEXT        1
typedef struct
{
    int state;
    
    XTOUCH xTouchMenu;
    
    int flowTime;
    int anyCnt;
    
    int selectSlot;
    int totalNum;
    int listCode[128];
} XEVENTQUESTUI;
extern XEVENTQUESTUI xEventQuestUi;










typedef struct
{
    int itemType;
    int itemCode;
    
    int perPer[5];
    int salePer[5];
    
    
    
    int filteringPer[3];
    
} XHOTDEALDATA;

typedef struct
{
    int state;
    int itemType;
    int itemCode;
    int salePer;
    int price;
    
    
    
    
    bool isCardOpen;
    int actFlow;
    int anyCnt;
    
    
    
} XHOTDEALSLOT;

#define HOTDEALSLOTMAX  10


#define HOTDEAL_ITEMTYPE_INTERIOR       0
#define HOTDEAL_ITEMTYPE_CASTING        1


#define HOTDEAL_STATE_CLOSE             0
#define HOTDEAL_STATE_OPEN              1
#define HOTDEAL_STATE_BUY               2



#define HOTDEAL_MAINSTATE_NET           0
#define HOTDEAL_MAINSTATE_PLAY          1




typedef struct
{

    char strInitInfo[128];
    int hotDealTimeMax;
    bool isOpen;
    
    int state;
    
    bool isReset;
    int remainTime;
    
    int openLv;
    
    
    int hotDealCode;

    int castingPrice[5];
    int castingPer[5];
    
    
    int selectSlot;
    
    
    XTOUCH xTouchUi;
    
    
    XTOUCH xTouchExit;
    
    
    XTOUCH xTouchSlot[HOTDEALSLOTMAX];
    
    XHOTDEALDATA xData[10][HOTDEALSLOTMAX];
    XHOTDEALSLOT xSlot[HOTDEALSLOTMAX];
    
    
    
} XHOTDEAL;
extern XHOTDEAL xHotDeal;




#define BLINK2_STATE_DONT       0
#define BLINK2_STATE_PLAY       1

#define BLINK2EFFMAX    32
typedef struct
{
    int state;
    int type;
    int x;
    int y;
    int anyCnt;
} XBLINKEFF2;
extern XBLINKEFF2 xBlinkEff2[BLINK2EFFMAX];








#define COMINGSOON_STATE_DOWNWAIT   0
#define COMINGSOON_STATE_DOWN       1

#define COMINGSOON_STATE_UPWAIT     2
#define COMINGSOON_STATE_UP         3




#define RIVALWORLDMAPMAX        32
#define RIVALSTAGEMAX        10
#define RIVALQUESTMAX        8



typedef struct
{
    
    int npcImgNum;
    int buildingImgNum;
    
    
    char strNpcName[64];
    char strInfo[256];
    int limitTime;
    
    

    bool isCheckClean[10];
    int checkMax[10];
    
    
    int giftType[3];
    int giftValue[3];
    
    
    
    int buffSell;
    int buffExp;
    int buffFame;
    
    
} XRIVALDATA;

#define RIVAL_STATE_WAIT        0
#define RIVAL_STATE_PLAY        1
#define RIVAL_STATE_SUCCESS      2
#define RIVAL_STATE_FAIL      3

typedef struct
{
    
    int state;
    int remainTime;
    
    
    int comingSoonState;
    int comingAnyCnt;
    
    XTOUCH xTouchUi;
    
    
    int nowCount;
    int maxCount;
    int openLv;
    int openMain;

    
    
    
    XTOUCH xTouchStart;
    XTOUCH xTouchExit;
    
    
    
    int totalWorldMap;

    XRIVALDATA xData[RIVALWORLDMAPMAX][RIVALSTAGEMAX];
    
    
    int completeMain;
    int completeDetail;
    
    int nowMain;
    int nowDetail;
    int checkNow[10];
    
    int checkNowNpc[10];

    
    
    
    int selectMain;
    int selectDetail;
    
    
    XTOUCH xTouchStage[RIVALSTAGEMAX];
    
    
    bool isNetLoad;
    
    
    XTOUCH xTouchUi2;
    
    int buffSell;
    int buffExp;
    int buffFame;
    
   
    int progressPerTime;
    int progressPerValueNpc;
    int progressPerValue;
    
    
} XRIVAL;
extern XRIVAL xRival;




typedef struct
{
    XTOUCH xTouchExit;
    
    XTOUCH xTouchSlot[RIVALWORLDMAPMAX];
    
  
    XDRAGSCROLL xDragScroll;
    
    
} XRIVALWORLDMAP;
extern XRIVALWORLDMAP xRivalWorldMap;


#define RIVALINFO_STATE_PLAY        0
#define RIVALINFO_STATE_FAILANY        1
#define RIVALINFO_STATE_SUCCESSANY     2

#define RIVALINFO_STATE_FAIL            3
#define RIVALINFO_STATE_SUCCESS         4


typedef struct
{
    XTOUCH xTouchExit;
    XTOUCH xTouchStop;
    
    int state;
    int resultAnyCnt;
} XRIVALINFO;
extern XRIVALINFO xRivalInfo;



#define RIVALGUEST_STATE_WAIT           0
#define RIVALGUEST_STATE_MOVE           1

typedef struct
{
    int state;
    bool isRever;
    int anyCnt;
    int imgNum;
    int x;
    int y;
    int targetX;
    int targetY;
    int speed;
    int waitTime;
    
} XRIVALGUESTSLOT;

#define RIVALGUESTMAX   100
typedef struct
{
    XRIVALGUESTSLOT xSortSort;
    XRIVALGUESTSLOT xSlot[RIVALGUESTMAX];
    
    
    
    int totalTouchBg[2];
    XTOUCH xTouchBg[2][10];
    
    XTOUCH xTouchMake;
    
} XRIVALGUEST;
extern XRIVALGUEST xRivalGuest;



#define NAVERPLUG_TYPE_HOME     0
typedef struct
{
    int aa;
} XNAVERPLUG;
extern XNAVERPLUG xNaverPlug;


#define HELPLISTMAX 32

#define HELPLIST_STATE_WAIT 0
#define HELPLIST_STATE_NEXT 1

typedef struct
{
    XTOUCH xTouchExit;
    XDRAGSCROLL xDragScroll;
    
    int selectSlot;
    int totalNum;
    int listUserKey[HELPLISTMAX];
    
    
    XTOUCH xTouchSelectSlot[32];

    
    //유아이
    int state;
    int flowTime;
    int anyCnt;
    int selectUiSlot;
    XTOUCH xTouchUi;
    
} XHELPLIST;
extern XHELPLIST xHelpList;




typedef struct
{
    int x;
    int y;
    int w;
    int h;
    XTOUCH xTouchBar;
    XDRAGSCROLL *xDragScroll;
}XFASTSCROLL;
extern XFASTSCROLL xFastScroll;


#define JEWELQUEST_STATE_PLAY           0
#define JEWELQUEST_STATE_COMPLETE       1

typedef struct
{
    int state;
    
    int checkType;
    int checkCode;
    int checkMax;
    int checkNow;
    
    int giftType[2];
    int giftValue[2];
    int giftMax[2];
    
    bool isCheckClean;
    
    int jewelCode;
    char strName[64];

    
    int openQuestCode;
    
    
    
    
} XJEWELQUESTDATA;


#define JEWELQUESTMAX       1024
typedef struct
{
    bool isNetLoad;
    int totalData;
    XJEWELQUESTDATA xData[JEWELQUESTMAX];
    
    
    XTOUCH xTouchExit;
    XDRAGSCROLL xDragScroll;
    int selectTab;
    XTOUCH xTouchTab[2];
    
    
    
    int totalList;
    int listCode[JEWELQUESTMAX];
    XTOUCH xTouchList[JEWELQUESTMAX];
    
    
}XJEWELQUEST;
extern XJEWELQUEST xJewelQuest;









#define JEWELDATAMAX       256

typedef struct
{
    char strName[128];
    int grade;
    int size;
    int buffType;
    int buffValue;
    
    
    int haveNum;
    
}XJEWELSLOT;


typedef struct
{
    XJEWELSLOT xData[JEWELDATAMAX];
}XJEWEL;
extern XJEWEL xJewel;






typedef struct
{
    int anyCnt;
    int resultJewelQuestCode;
    XTOUCH xTouchExit;
    
}XJEWELRESULT;
extern XJEWELRESULT xJewelResult;





typedef struct
{
    XTOUCH xTouchUi;
    
    
}XJEWELUI;
extern XJEWELUI xJewelUi;



#define AMULETPAGEMAX       3
#define AMULETDATAMAX       64
#define AMULETSOCKETMAX     32

#define JEWELBUFF_TYPE_JEWEL               0
#define JEWELBUFF_TYPE_FASHIONSHOW         1
#define JEWELBUFF_TYPE_CASTING_S           2
#define JEWELBUFF_TYPE_MINIGAME            3
#define JEWELBUFF_TYPE_INSHOP              4
#define JEWELBUFF_TYPE_FAME                5
#define JEWELBUFF_TYPE_SELL_EXP            6
#define JEWELBUFF_TYPE_SELL_GOLD           7
#define JEWELBUFF_TYPE_SOCIAL              8
#define JEWELBUFF_TYPE_SEX_PORTER          9
#define JEWELBUFFMAX       10

typedef struct
{
    bool isOpen;
    int amuletCode;
    int pagePrice;
    int socketJewelCode[AMULETSOCKETMAX];
}XAMULETPAGE;

#define AMULETSETTING_STATE_PLAY                0
#define AMULETSETTING_STATE_SELECTSOCKET        1

typedef struct
{
    
    int state;
    
    XTOUCH xTouchAmuletPage[AMULETPAGEMAX];
    XAMULETPAGE xEditPage;
    XTOUCH xTouchAmulet[AMULETDATAMAX];
    
    
    int totalList;
    int listCode[JEWELDATAMAX];
    
    
    XTOUCH xTouchList[JEWELDATAMAX];
    XDRAGSCROLL xDragScroll;
    
    
    XTOUCH xTouchReset;
    
    XTOUCH xTouchSocket[AMULETSOCKETMAX];
    
    
    int selectSocket;
    
    XTOUCH xTouchAmuletBuy;
    
    
    int selectSocketAnyCnt;
    
    
    
    
    int amuletSocketJewelCodeTemp[AMULETDATAMAX][AMULETSOCKETMAX];
    
    
    
}XAMULETSETTING;
extern XAMULETSETTING xAmuletSetting;






typedef struct
{
    int size;
    int x;
    int y;
    int uiX;
    int uiY;
}XAMULETSOCKET;


typedef struct
{
    char strName[64];
    int lv;
    int priceType;
    int priceValue;
    int buffType;
    int buffValue;
    int totalSocket;
    XAMULETSOCKET xSocket[AMULETSOCKETMAX];
    
    bool isOpen;
    
}XAMULETDATA;



typedef struct
{
    int selectAmuletPage;
    XAMULETPAGE xAmuletPage[AMULETPAGEMAX];
    XAMULETPAGE xAmuletFriend;
    XAMULETDATA xData[AMULETDATAMAX];
    
    int totalAmulet;
    
    
    int buff[JEWELBUFFMAX];
    
    
    bool isNetLoad;
    
    

    int uiAnyCnt;
    
    bool isOpen;
    
    
}XAMULET;
extern XAMULET xAmulet;



#define CLUBDATAMAX     32
typedef struct
{
    int memberMax;
    int expMax;
    int layeredMax;

}XCLUBDATA;



typedef struct
{
    int clubKey;
    int clubIcon;
    int clubLv;
    int clubExp;
    int joinType;
    
    int memberNow;
    int masterKey;
    char strName[64];
    char strJoinInfo[256];
    char strNickName[64];
    
    char strNotice[512];
    
    int fashionWeekScore;
    int fashionWeekRank;
    float fashionWeekRankPer;
    
    
    
    int fashionWeekScore_LASTWEEK;
    int fashionWeekRank_LASTWEEK;
    float fashionWeekRankPer_LASTWEEK;
    
    

    int gender;
    XFACE xFace;
    XFITTINGLAYER xF;    
}XCLUBLISTSLOT;






#define CLUBICONMAX     32

#define CLUBLISTMAX     32

#define CLUBLIST_STATE_NET              0
#define CLUBLIST_STATE_PLAY             1
#define CLUBLIST_STATE_SEARCH           2
#define CLUBLIST_STATE_SEARCHNET           3
#define CLUBLIST_STATE_MAKE             4
#define CLUBLIST_STATE_MAKENET          5



typedef struct
{
    int state;
    XTOUCH xTouchExit;
    XTOUCH xTouchMake;
    XDRAGSCROLL xDragScroll;
    
    
    
    XTOUCH xTouchRefresh;
    XTOUCH xTouchSearch;
    
    
    
    int selectList;
    int totalList;
    
    XCLUBLISTSLOT xListSlot[CLUBLISTMAX];
    
    XTOUCH xTouchSlot[10];
}XCLUBLIST;
extern XCLUBLIST xClubList;



typedef struct
{
    XTOUCH xTouchExit;
    XTOUCH xTouchText;
    XTOUCH xTouchSearch;
    XTOUCH xTouchJoin;
    char strName[128];
    XCLUBLISTSLOT xSearchSlot;
    
    
   
}XCLUBSEARCH;
extern XCLUBSEARCH xClubSearch;



typedef struct
{
    XTOUCH xTouchExit;
    XTOUCH xTouchName;
    XTOUCH xTouchJoinInfo;
    XTOUCH xTouchJoinType[2];
    XTOUCH xTouchMake;
    XTOUCH xTouchIcon[32];
    

    int selectIconSlot;
    
    int totalIconList;
    int iconListCode[32];
    
    int selectJoinType;
    
    
    char strName[128];
    char strJoinInfo[256];
    
}XCLUBMAKE;
extern XCLUBMAKE xClubMake;



typedef struct
{
    int userKey;
    int loginTime;
    
    int totalContribution;
    
    bool touched;

    char strJoinApplyTime[128];
    
}XCLUBMEMBER;

typedef struct
{
    int DonationWeath;//한번 기부시 소모되는 재화 1이 골드, 2가 캔디
    
    int point;//한번 기부시 충전되는 클럽포인트
    
    int maxDonationCount;// 최대 기부 가능 횟수
    int donationCount; //기부 가능 횟수
    
    char strItem[128];
    
    bool touched;
}XCLUBDONATION;
extern XCLUBDONATION xClubDonation[128];

#define CLUBMEMBERMAX       32

typedef struct
{
    int index;
    int clublv;
    int coin;
    bool isOpen;
}XCLUBICON;
extern XCLUBICON xClubIcon[128];

#define CLUBICONMAX         20
typedef struct
{
    int makePrice;
    bool isOpen;
    int lvLimit;
    XCLUBDATA xData[CLUBDATAMAX];

    
    XCLUBLISTSLOT xMy;
    
    
    int totalMember;
    XCLUBMEMBER xMember[CLUBMEMBERMAX];
    

    int selectedIcon;
    XCLUBICON xIcon[CLUBICONMAX];
    int bestPangScore;
    
    int fashionWeekPlayCountMax;
    int fashionWeekPlayCount;
    
    int donationType; //골드는 0, 캔디는 1
    
    XCLUBDONATION xDonation[2];
    int money;
    int totalDonation;
    
    XTOUCH xTouchDonateGold;
    XTOUCH xTouchDonateCandy;
    XTOUCH xTouchDonation;
    XTOUCH xTouchDonationMainFrame;
}XCLUB;
extern XCLUB xClub;

typedef struct
{
    int totalData;
    XTOUCH xTouchSlot[30];
    XTOUCH xTouchChange;
    XTOUCH xTouchExit;
    XDRAGSCROLL xDragScroll;
    
    bool isSlot;
    
    int selectedNum;
    int sortCount;
    int indexingcount;
    int memberCode[CLUBICONMAX];
    int touched[CLUBICONMAX];
    
}XCHANGECLUBICON;
extern XCHANGECLUBICON xChangeClubIcon;





#define CLUBMENUMAX   4

#define CLUBLOBBYNOTICETABMAX   2

#define CLUBLOBBYTAB_TYPE_MEMBER            0
#define CLUBLOBBYTAB_TYPE_CLUBBOOK       1
#define CLUBLOBBYTAB_TYPE_JOIN              2


#define CLUBLOBBY_STATE_DATANET         0
#define CLUBLOBBY_STATE_PLAY            1
#define CLUBLOBBY_STATE_NET             2
#define CLUBLOBBY_STATE_DONATION        3
#define CLUBLOBBY_STATE_CHANGEICON      4
#define CLUBLOBBY_STATE_MODIFYTEXT      5


#define CLUBLOBBY_MENU_MAIN                 0
#define CLUBLOBBY_MENU_FASHIONWEEK          1
#define CLUBLOBBY_MENU_SHOP                 2
#define CLUBLOBBY_MENU_MISSION              3

#define CLUBSHOP_STATE_PLAY                 0
#define CLUBSHOP_STATE_CLUBNAMEMODIFY       1

#define CLUBSTORAGE_STATE_PLAY              0
#define CLUBSTORAGE_STATE_TAKEGIFT          1

#define CLUBITEM_NAMEMODIFY                 2

#define CLUBNAME_STATE_START                0
#define CLUBNAME_STATE_TOLEAKWORD           1
#define CLUBNAME_STATE_OVERLAPWORD          2
#define CLUBNAME_STATE_OK                   3

typedef struct
{
    int state;
    
    XTOUCH xTouchExit;
    XTOUCH xTouchUnReg;
    XTOUCH xTouchClubDonate;
    
    int selectScroll;
    XDRAGSCROLL xDragScrollHistory;
    XTOUCH xTouchHistoryBg;
    XTOUCH xTouchListBg;
    XTOUCH xTouchChangeIcon;
    
    
    XDRAGSCROLL xDragScroll[5];
    
    int selectSlot;
    
    int selectTab;
    XTOUCH xTouchTab[10];
 
    bool isMaster;
    

    XTOUCH xTouchJoinType[2];
    
    
    
    XTOUCH xTouchNoticeEdit;
    XTOUCH xTouchNotice[CLUBLOBBYNOTICETABMAX];
    int selectNoticeTab;
    
    
    XTOUCH xTouchMemberPhoto[10];
    XTOUCH xTouchMemberBtn0[10];
    XTOUCH xTouchMemberBtn1[10];

    
    
    XTOUCH xTouchClubMenu[CLUBMENUMAX];
    

    
    int selectMenu;
    
    
    
    
}XCLUBLOBBY;
extern XCLUBLOBBY xClubLobby;






typedef struct
{
    int totalNum;
    
    XCLUBMEMBER xJoinMember[128];
}XCLUBJOINMEMBER;
extern XCLUBJOINMEMBER xClubJoinMember;



typedef struct
{
    int userKey;
    int key;
    char strText[256];
    char strDate[32];
}XCLUBBOOKSLOT;

#define CLUBBOOKMAX     1024
typedef struct
{
    char strText[256];
    XTOUCH xTouchText;
    XTOUCH xTouchSend;

    int totalNum;
    int selectSlot;
    XCLUBBOOKSLOT xSlot[CLUBBOOKMAX];
    int rowNum;
    int pageNum;
}XCLUBBOOK;
extern XCLUBBOOK xClubBook;



#define CLUBHISTORYMAX      1024
typedef struct
{
    int userKey;
    int ToUserKey;
    int type;
    int value;
    
    int writeTime;
    
}XCLUBHISTORYSLOT;

typedef struct
{
    int totalNum;
    XCLUBHISTORYSLOT xSlot[CLUBHISTORYMAX];
    
    int rowNum;
    int pageNum;
}XCLUBHISTORY;
extern XCLUBHISTORY xClubHistory;


#define FASHIONSTUDIOMAX    12

#define FASHIONWEEKLOBBY_STATE_LOBBY            0
#define FASHIONWEEKLOBBY_STATE_FITTING          1
#define FASHIONWEEKLOBBY_STATE_SETTING          2
#define FASHIONWEEKLOBBY_STATE_SELECTMODEL          3
#define FASHIONWEEKLOBBY_STATE_SETTING_FITTING          4
#define FASHIONWEEKLOBBY_STATE_GIFTINFO          5





typedef struct
{
    int state;
    
    
    
    int selectScroll;
    XTOUCH xTouchStudioSlot[FASHIONSTUDIOMAX];
    XTOUCH xTouchStart;
    XTOUCH xTouchPreview;
    XTOUCH xTouchModelSetting;
    
    
    bool isPreview;

    
    XTOUCH xTouchGiftInfo;
    
    
    
}XFASHIONWEEKLOBBY;
extern XFASHIONWEEKLOBBY xFashionWeekLobby;





typedef struct
{
    int code;
    
}XFASHIONWEEKHAIRLIST;

typedef struct
{
    int code;
}XFASHIONWEEKFACELIST;

typedef struct
{
    M_Int32 code;
    M_Boolean isNew;
    M_Boolean isHot;
    M_Boolean isEvent;
    
}XFASHIONWEEKFASHIONLIST;

#define FASHIONWEEKHAIRLISTMAX      256
#define FASHIONWEEKFACELISTMAX      256




typedef struct
{
    int key;
    bool isOpen;
    int nowCost;
    
    bool isExp;
    
}XFASHIONWEEKITEM;
extern XFASHIONWEEKITEM xFashionWeekItem[FASHIONDATATYPEMAX][FASHIONDATAMAX];



typedef struct
{
    int totalHairList;
    int totalFaceList;
    int totalFashionList[CATALOGSLOTBMAX];
    XFASHIONWEEKHAIRLIST xHairList[FASHIONWEEKHAIRLISTMAX];
    XFASHIONWEEKFACELIST xFaceList[FASHIONWEEKFACELISTMAX];
    XFASHIONWEEKFASHIONLIST xFashionList[CATALOGSLOTBMAX][CATALOGSLOTSMAX];
    
    
    
    int totalScore;
    
    
    
    bool isNet_Ranking;
    bool isNet_FittingList;
    bool isNet_Dress;
    bool isNet_FittingUpdate;
    bool isNet_PangStart;
    
    
    bool isNet_Exp;
    bool isNet_Score;
    
    
    bool isOpen;
    
    
    
    int rankGiftLook[30];
    
    
    
    
}XFASHIONWEEK;
extern XFASHIONWEEK xFashionWeek;







typedef struct
{
    int totalNum;
    int itemCode[FASHIONSTUDIOMAX];
    
    
    bool isInfo;
    int selectInfoSlot;
    XTOUCH xTouchExit;
    
}XFASHIONSTUDIO;
extern XFASHIONSTUDIO xFashionStudio;







#define FASHIONWEEKRANKMAX      128
typedef struct
{
    int totalNum;
    XDRAGSCROLL xDragScroll;
    XTOUCH xTouchBg;
    XTOUCH xTouchSlot[10];
        
    XCLUBLISTSLOT xSlot[FASHIONWEEKRANKMAX];


    
}XFASHIONWEEKRANK;
extern XFASHIONWEEKRANK xFashionWeekRank;




#define FASHIONWEEKSETTINGMAX       5

typedef struct
{
    XTOUCH xTouchModelSlot[FASHIONWEEKSETTINGMAX];
    XTOUCH xTouchItemSlot[FASHIONWEEKSETTINGMAX];
    XTOUCH xTouchFittingSlot[FASHIONWEEKSETTINGMAX];
    
    
    int selectModelSlot;
    
    
}XFASHIONWEEKSETTING;
extern XFASHIONWEEKSETTING xFashionWeekSetting;

typedef struct
{
    int modelKey;
    int studioSlotNum;
}XFASHIONWEEKMODEL;
extern XFASHIONWEEKMODEL xFashionWeekModel[FASHIONWEEKSETTINGMAX];




#define CLUBSHOPMAX     128
typedef struct
{
    char strName[128];
    int price;
}XCLUBSHOPDATA;



typedef struct
{
    XTOUCH xTouchExit;
    XTOUCH xTouchPrimium;
    XTOUCH xTouchICON;
    XTOUCH xTouchStorage;
    XTOUCH xTouchClubShopMenu[3];
    
    int OnOff;
    int selectMenu;
    int state;
    int selectedNum;
    int totalData;
    XDRAGSCROLL xDragScroll;
    XCLUBITEM xData[CLUBSHOPMAX];
    XTOUCH xTouchSlot[30];
}XCLUBSHOP;
extern XCLUBSHOP xClubShop;


typedef struct
{
    XTOUCH xTouchExit;
    XTOUCH xTouchPrimium;
    XTOUCH xTouchICON;
    XTOUCH xTouchStorage;
    XTOUCH xTouchClubShopMenu[3];
    int state;
    int selectedNum;
    int totalData;
    XDRAGSCROLL xDragScroll;
    XTOUCH xTouchSlot[30];
    

}XCLUBICONSHOP;
extern XCLUBICONSHOP xClubIconShop;
typedef struct
{
    XTOUCH xTouchExit;
    XTOUCH xTouchPrimium;
    XTOUCH xTouchICON;
    XTOUCH xTouchStorage;
    XTOUCH xTouchClubShopMenu[3];
    
    int totalData;
    int state;
    int selectedNum;
    bool isSlot;
    
    XDRAGSCROLL xDragScroll;
    XCLUBITEM xData[CLUBSHOPMAX];
    XTOUCH xTouchSlot[30];
    XTOUCH xTouchTakeGift[30];
}XCLUBSTORAGE;
extern XCLUBSTORAGE xClubStorage;

typedef struct
{
    char strName[128];
    bool bTemp;
    int state;
    XTOUCH xTouchMainFrame;
    XTOUCH xTouchName;
    XTOUCH xTouchOK;
}XCLUBNAMEMODIFY;
extern XCLUBNAMEMODIFY xClubNameModify;

typedef struct
{
    int totalData;
    int memberCode[CLUBMEMBERMAX];
    
    int touched[CLUBMEMBERMAX];
    int giftCount;
    int sortCount;
    
    int selectedIndex[CLUBMEMBERMAX];
    XTOUCH xTouchGiftBtn;
    XTOUCH xTouchGiftMainframe;
    XTOUCH xTouchSend;
    XDRAGSCROLL xDragScroll;
    XTOUCH xTouchSlot[15];
    XTOUCH xTouchCan;
}XCLUBSHOPGIFT;
extern XCLUBSHOPGIFT xClubShopGift;



#define CLUBSHOP        0
#define CLUBICONSHOP    1
#define CLUBSTORAGE     2
#define CLUBSHOPGIFT    3

typedef struct
{
    int key;
    int index;
    int state; //0: 시작전 1: 미완성 2: 완성
    int endTime;
    int ingAnyCnt;
    
    int x;
    int y;
    int imgEventBox;
}XFORMERDATA;
extern XFORMERDATA xFormerData;

#define FORMERMAX 64
typedef struct
{
    int totalData;
    XFORMERDATA xData[FORMERMAX];
    
    int itemCnt[FORMERMAX];
    int buildlimitMax[FORMERMAX];
    int EndTimer[FORMERMAX];
    int index;
    int count[FORMERMAX];
    int OnOff;
    XTOUCH xTouchStart;
    XTOUCH xTouchTake;
    XTOUCH xTouchOK;
    
}XFORMER;
extern XFORMER xFormer;

extern XIMG imgLuluPangLobby[10];
extern XIMG imgLuluPang;

#define LULUPANGSETTINGMAX      5

#define LULUPANG_STATE_LOBBY        0
#define LULUPANG_STATE_PLAY         1
#define LULUPANG_STATE_RANKCHANGE   2
#define LULUPANG_STATE_RESULTBONUS  3

typedef struct
{
	int state;
	int score[2];//0: 이번주 점수, 1: 지난주 점수
	int HighScore;
	int myRank;
	int bestRank;
	int TiredCost;
	int rankGiftLook[30];
	int rankChangeAnyCnt;
	M_Boolean isChangeRankEvent;
	
	XTOUCH xTouchStart;
}XLULUPANG;
extern XLULUPANG xLuluPang;

#define LULUPANG_LOBBY_STATE_MAIN           0
#define LULUPANG_LOBBY_STATE_RESULTBONUS    1
#define LULUPANG_LOBBY_STATE_SETTINGMODEL   2
#define LULUPANG_LOBBY_STATE_SETTINGFITTING 3
typedef struct
{
	int state;
	int type;//0: 이번주 순위, 1: 지난주 순위
	
	bool isThisWeek;
	
	XTOUCH xTouchThisWeek;
	XTOUCH xTouchLastWeek;
	XTOUCH xTouchRankArea;
	XTOUCH xTouchStart;
	XTOUCH xTouchExit;
	XTOUCH xTouchReward;
	
	XDRAGSCROLL xDragScroll;
	
	XDRAGSCROLL xDragScrollSelectModel;
	int selectModelSlot;
	int selectSlot[5];
	int selectSlotCnt;
	XTOUCH xTouchSelectSlot[5];
	XTOUCH xTouchFittingSlot[5];
	
}XLULUPANGLOBBY;
extern XLULUPANGLOBBY xLuluPangLobby;

typedef struct
{
	int modelKey;
	int studioSlotNum;
	
}XLULUPANGMODEL;
extern XLULUPANGMODEL xLuluPangModel[LULUPANGSETTINGMAX];

#define LULUPANGRANKMAX         128


typedef struct
{
	int rank;
	int usernum;
	char strUserNick[64];
	int LV;
	int Score;
	int BestScore;
}XLULUPANGRANKSLOT;

typedef struct
{
	int totalNum;
	XLULUPANGRANKSLOT Slot[LULUPANGRANKMAX];
	XLULUPANGRANKSLOT xRankChangeSlot;
}XLULUPANGRANK;
extern XLULUPANGRANK xLuluPangRank;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//헤어,메이크업 데이터 LJW 2018.02.01
#define HAIRMAKEUPTYPEMAX			2
#define HAIRMAKEUPDATAMAX			100

typedef struct
{
	char strName[64];
	int lv;
	int price;
	int priceType;
	int layerNum;
} XHAIRMAKEUPDATA;


typedef struct
{
	int total;
	XHAIRMAKEUPDATA xData[HAIRMAKEUPTYPEMAX][HAIRMAKEUPDATAMAX];
} XHAIRMAKEUP;
extern XHAIRMAKEUP xHairMakeUp;
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//레이어 데이터 LJW 2018.02.01
#define LAYERTYPEMAX			128
#define LAYERDATAMAX			15

typedef struct
{
	char strName[64];
	int xData[2][LAYERDATAMAX];
} XLAYERDATA;


typedef struct
{
	int total;
	XLAYERDATA xData[LAYERTYPEMAX];
} XLAYER;
extern XLAYER xLayer;
////////////////////////////////////////////////////////////////////////////////////////


//////////옷장 KBY
typedef struct
{
	bool isfitting;
	int buff;
	int code;
	char strItemName[512];
	char buffinfo[512];
	
}XFITTING_FP_SLOT;

#define FITTING_FP_TAPMAX       6
#define FITTING_FP_SLOTMAX      512
#define FITTING_FP_PLACEMAX     12
typedef struct
{
	bool isTouchClr;
	bool isinfo;
	bool isTouchLeftArrow;
	bool isTouchRightArrow;
	bool isRollBack;
	bool isSave;
	int buff[10];
	int maxPlace;
	int nowPlace;
	int totalNum;
	int selectTabB;
	int selectSlot;
	////////////////////////////////////
	//옷장 구조체 변수추가 LJW 2018.02.01
	XSPRIT xSprit;
	XFACE xFace;
	XFITTINGLAYER xFG;
	XWORLDMAPNPC xModel;
	XIMG imgFace;
	XIMG imgHair[2][LAYERDATAMAX];//[방향(앞/뒤)][이미지번호]
	int pos;
	int faceNum;
	int hairNum;
	bool isChange;//의상이 변경됐을시
	XTOUCH xTouchRollBack;
	XTOUCH xTouchSave;
	////////////////////////////////////
	XTOUCH xTouchInfo;
	XTOUCH xTouchOpenPlace;
	XTOUCH xTouchShop;
	XTOUCH xTouchLeftArrow;
	XTOUCH xTouchRightArrow;
	XTOUCH xTouchSelectTap[FITTING_FP_TAPMAX];
	XTOUCH xTouchSlot[FITTING_FP_SLOTMAX];
	XFITTING_FP_SLOT xSlot[FITTING_FP_SLOTMAX];
	XDRAGSCROLL xDragScrollFittingList;
}XFITTING_FP;
extern XFITTING_FP xFitting_FP;
///////////////////////////////////////////
#define SENDMACHINE_MAX	1
#define SENDMACHINE_SLOTMAX	15

#define SENDMACHINE_STATE_WAIT	0
#define SENDMACHINE_STATE_START	1
#define SENDMACHINE_STATE_LOOP	2

#define SENDMACHINE_SUBSTATE_NONE	0
#define SENDMACHINE_SUBSTATE_INFO	1
#define SENDMACHINE_SUBSTATE_ADD	2
#define SENDMACHINE_SUBSTATE_END	3


#define SENDMACHINE_BTNTYPE_NONE	0
#define SENDMACHINE_BTNTYPE_EXIT	SENDMACHINE_BTNTYPE_NONE+1
#define SENDMACHINE_BTNTYPE_UPGRADE	SENDMACHINE_BTNTYPE_EXIT+1
#define SENDMACHINE_BTNTYPE_STORAGEL	SENDMACHINE_BTNTYPE_UPGRADE+1
#define SENDMACHINE_BTNTYPE_STORAGER	SENDMACHINE_BTNTYPE_STORAGEL+1
#define SENDMACHINE_BTNTYPE_SLOTL	SENDMACHINE_BTNTYPE_STORAGER+1
#define SENDMACHINE_BTNTYPE_SLOTR	SENDMACHINE_BTNTYPE_SLOTL+1
#define SENDMACHINE_BTNTYPE_LOCK	SENDMACHINE_BTNTYPE_SLOTR+1

#define SENDMACHINE_BTNDIR_LEFT 0
#define SENDMACHINE_BTNDIR_RIGHT 1

#define DRESS_TYPE_MAX 16
#define DRESS_COUNT_MAX 512

//보유 의상 정보
typedef struct
{
	int state;//0:대기,1:드래그중
	int itemNum;//보유의상번호
	int itemCnt;//보유의상개수
}XPRODUCTDRESSINFO_FP;

//전송기 슬롯 구조체
typedef struct
{
	int key;//전송테이블 큐 키값(슬롯업데이트시 보내줘야 함!!!)
	int state;//0:오픈, 1:잠김
	int itemNum;//보유의상번호
	int itemCnt;//보유의상개수
	long startTime;//시작시간
	long endTime;//완료시간
}XSENDMACHINESLOT;

//전송기 데이터
typedef struct
{
	int state;//상태(0:대기, 1:전송준비, 2:전송중)
	int bkey;//인테리어키
	int itemNum;//인테리어 번호
	int totalSlot;//전송기 슬롯개수
	int lv;//전송기 레벨
	int startTime;//전송시작시간
}XSENDMACHINEDATA_FP;

//전송기 구조체
typedef struct
{
	int state;//상태(0:대기, 1:전송시작, 2:전송중)
	int stateSub;//상태(0:슬롯정보, 1:대기슬롯에 의상추가, 2:전송완료)
	int anyCnt;//전송연출용 카운트
	int gameCnt;//게임카운트
	int endCnt;
	int startTime;//전송시작 시간(대기 -> 전송준비 할때)
	int btnType;//버튼 Pressed 이미지 변경용
	int total;//전송기 총개수
	int dressSlotTotal;//총유저보유의상슬롯
	int selectNum;//보유의상 터치 인덱스
	bool isSelectDress;
	bool isSendEnd;//전송완료 연출
	
	XDRAGSCROLL xDragScrollS;//의상리스트 스크롤
	XDRAGSCROLL xDragScrollB;//제작슬롯 스크롤
	XTOUCH xTouchExit;
	XTOUCH xTouchUpgrade;
	XTOUCH xTouchLock;
	XTOUCH xTouchArrow[2][2];
	XTOUCH xTouchStorage[16];
	XTOUCH xTouchOpenSlot;
	XTOUCH xTouchSlot;
	XSENDMACHINESLOT xSendSlot;//전송기 전송슬롯
	XSENDMACHINESLOT xSlot[SENDMACHINE_SLOTMAX];//전송기 대기슬롯 데이터
	XSENDMACHINESLOT xDressSlot[SENDMACHINE_SLOTMAX];//전송기 보유의상슬롯 데이터
	XPRODUCTDRESSINFO_FP xDress[DRESS_TYPE_MAX*DRESS_COUNT_MAX];//유저 보유의상
	XSENDMACHINEDATA_FP xData[SENDMACHINE_MAX];//유저 전송기 데이터
}XSENDMACHINE;
extern XSENDMACHINE xSendMachine_FP;
///////////////////////////////////////////






extern XTOUCH xTouchBuildIconExit;
extern XTOUCH xTouchBuildIconShop;

extern XTOUCH xTouchScrollOk;
extern XTOUCH xTouchScrollStepUp;
extern XTOUCH xTouchScrollStepDown;
extern XSWITCH xSwitchWorldMapUi;
extern XSWITCH xSwitchWorldMapUi_Up;
extern XTOUCH xTouchRocket;






extern XIMG imgClubMenu[10];

extern XIMG imgClubUi[5];
extern XIMG imgClubBook[10];

extern XIMG imgClubList[10];
extern XIMG imgClubIcon[CLUBICONMAX];

extern XIMG imgClubMake[5];




extern XIMG imgJewelResult[10];

extern XIMG imgEventQuestUi[10];
extern XIMG imgMileageUi[10];
extern XIMG imgWebView[5];
extern XIMG imgThemaIconB[32];
extern XIMG imgRivalComingSoon[10];
extern XIMG imgMapBg;
extern XIMG imgStaticNpc[20][2][40];

extern XIMG imgFormer[10];
extern XIMG imgMerchin[20];

extern XIMG imgFitting[20];

///////////////////////////////////////////
//전송기UI 이미지
extern XIMG imgSendMachine_DisplayArrow;
extern XIMG imgSendMachine_Controler;
extern XIMG imgSendMachine_Display;
extern XIMG imgSendMachine_Num;
extern XIMG imgSendMachine_Rail;
extern XIMG imgSendMachine_RailRabbit;
extern XIMG imgSendMachine_Slot[5];
extern XIMG imgSendMachine_Sticker[7];
extern XIMG imgSendMachine_StorageTitle;
extern XIMG imgSendMachine_Title;
extern XIMG imgSendMachine_BG;
extern XIMG imgSendMachine_BtnExit;
extern XIMG imgSendMachine_Storage[4];
extern XIMG imgSendMachine_BtnArrow[2];
extern XIMG imgSendMachine_Lock;
extern XIMG imgSendMachine_BtnUpgrade;
///////////////////////////////////////////

///////////////////////////////////////////
//캐릭터 레이어 시스템 LJW 2018.02.08
extern XIMG imgLayer[40][2];
extern bool isLayer[40][2];
///////////////////////////////////////////

//////////////////////////////////////////////////////
//헤어, 얼굴표정 이미지 추가 LJW 2018.02.08
extern M_Boolean isImgHair_FP[HAIRDATAMAX];
extern M_Boolean isImgHairBig_FP[HAIRDATAMAX];
extern M_Boolean isImgFace_FP[FACEDATAMAX];
extern M_Boolean isImgFaceBig_FP[FACEDATAMAX];
extern XIMG imgHair_FP[HAIRDATAMAX][2][2];//[헤어코드][방향][헤어파일]
extern XIMG imgHairBig_FP[HAIRDATAMAX][2][2];//[헤어코드][방향][헤어파일]
extern XIMG imgFace_FP[HAIRDATAMAX];
extern XIMG imgFaceBig_FP[HAIRDATAMAX];
//////////////////////////////////////////////////////

void worldMapCarPrc(void);
void worldMapNpcPrc(void);
void shopNpcPrc(void);
void makeCloud(int i);

void setMapPosScale(int type, int param1, int param2,int touchId);
void initWorldMap(void);
void WorldMapCletEvent(int type, int param1, int param2,int touchId);
void paintWorldMap(void);
float getMapW(void);
float getMapH(void);
void setSelectTileKeyEvent(int type,int floor);
void setMapData(int objCode);
void prcWorldMap(void);
void setScaleRotLimit(void);
void drawWorldMap(void);
void drawObjSort(int num,int floor,int b_a);
void checkMapDataAstar(int type,int floor);
void makeShopNpc(int worldMapNpcCode,int optionType,int optionNum);
int makeWorldMapNpc(int x,int y,int type,float speed,int moveType);

void drawSwitch(int x,int y,XSWITCH * xSwitch,int XIMG,int totalNum, int gab);
//////////////////////////////////////////////////////////////////////////////
//메뉴 버튼 연출 KBY
void drawSwitchImg(int x,int y,XSWITCH * xSwitch, XIMG xImg,int totalNum, int gab);
////////////////////////////////////////////////////////////////////////////////////
void drawWorldMapUi(void);
void drawInteriorShop(void);
void initDragScroll(void);


void setInteriorTabChange(void);
void setBuildCheck(void);
void setInteriorBuildMode(int slotNum,int teamNum);
void drawInteriorSellPopup(void);
void setCash(int cash);
void setMoney(int money);
void setExp(int exp);
void inputInventoryInterior(int itemCode);
void outputInventoryInterior(int itemCode);
M_Int32 getInventoryInteriorCount(int itemCode);
void drawInteriorBuild(void);
int getWorldMapPosTouch(int pos,int posCxy);
int getWorldMapPos(int pos,int posCxy);
void checkBuildMapData(void);
void addEventQueue(int x,int y,int type,int floor,int startX,int startY);
void addEventQueueNet(int x,int y,int type,M_Boolean isReturnKey);
void outPutEventQueue(int eventNum);



int getNumLen(int num);
int getNumW(XIMG * imgNum,int gab);


int getFastTimeCash(int time);

void setCatalogTabChange(int tabS);
void inputInventoryFashion(int code,int inputNum);
int getSellNum(int mapX,int mapY);
int getSellTable(int mapX,int mapY,int floor);
int getSellTableInfo(int key,int floor);
void drawSellMain(void);

int getFastSellCash(int num);
void drawSellSelectItem(void);
void setSellSelectItemSlot(void);
void outputInventoryFashion(int code,int inputNum);
void drawBonus(void);
void setBonus(int x,int y,int type,int num);
int addSellTableInfo(int key,int floor);
void resetSellTableInfo(int floor);

void resetFittingRoomInfo(int floor);
void resetPayMentInfo(int floor);
void resetShowWindowInfo(void);
void setNpcStateFittingRoom(int npcNum,int floor);
void setNpcStatePayMent(int npcNum,int floor);
void setNpcStateExit(int npcNum,int floor);
void makeShopAssistant(void);
void setSpritF(XSPRIT *xSprit,XFITTINGLAYER *xF,int pos);
void drawFittingBody(int drawX,int drawY,XFITTINGLAYER *xF,XFACE *xFace,M_Boolean isStaff,int sex);
void drawFittingF(int drawX,int drawY,int itemCode,int reSize);
void drawFitting(void);
void setFittingTabChange(void);

int getShowWindow(int mapX,int mapY,int floor);
int addShowWindowInfo(int key,int floor);
void initMenuOut(void);
void drawLvUp(void);
int getFittingRoom(int mapX,int mapY,int floor);
void checkDelFittingItem();
void drawHair(int x,int y,int hairNum,int layerNum,int pos,int sub);
void drawFace(int x,int y,XFACE *xFace,int layerNum,int pos);
void setFace(XFACE * xFace,int faceType);
void setSpeak(XSPEAK * xSpeak,const char *strText,int frameMax);
void drawSpeak(XSPEAK * xSpeak, int x,int y);
void drawFitting_STAFF(void);
void drawHairF(int drawX,int drawY,int hairCode,int sub,int reSize);
void drawFaceF(int drawX,int drawY,int faceCode,int faceType,int reSize);
void drawIcon(int x,int y,int type);
void drawStaffBuyPopup(void);
void resetStaff(void);
void drawHanger(int x, int y,int interiorCode,int interiorNum,int floor);
void drawAccessory(int x, int y,int interiorCode,int interiorNum,int floor);
void drawHangerItem(int x,int y,int itemCode);
int selectEventBox(int floor,int eventType);
void setFame(int fame);
void setNpcStateFloorUp(int npcNum,int floor);
void setNpcStateFloorDown(int npcNum,int floor);
void initShopNpcMove(int npcNum);
void drawMiniGame(void);
void initMiniGame(void);
void setTired(int tired);
void setMiniGamePlay(void);
void drawMiniGameResult(void);
void setEff(int x,int y,int reSize);
void drawEff(void);




void setLvUp(void);
void keyLvUp(int type, int param1, int param2);
void drawObj(int x,int y,int type,int listNum,int rever,M_Boolean isFrame,int mapX,int mapY);

void drawTrend(void);
void drawNotice(void);
void outPutEventQueueNet(int eventNum);
void npcSet(void);
void freeInterior(void);
void freeFashion(void);
void loginInit(void);
void setWorldMapPeople(void);
void drawProfilePhoto(void);
void addTrend(int itemCode);
void prcTrend(void);
void drawTrendInfo(void);
void drawTimeSprintf(char * strTemp,int time,int type);
void setShop(int type);
void drawShop(void);
void setShopTab(int selectTab);
void drawShopMoneyIcon(int x,int y,int index);
void drawShopPremiumIcon(int x,int y,int index);

void drawCar(int x,int y,int code,int pos,int anyCnt,int reSize);

void setOrderList(void);
void addOrderNpc(void);

void setCarStorage(int type);
void drawCarStorage(void);
void drawCarOrderInfo(void);


int getOrderSlotNum(int key);
void drawFriendProfile(int x,int y,int userNum,int reSize);
int getFriendSlot(int userNum);
int getFriendSlot_KAKAOID(char* strId);
void prcOrderList(void);
void drawFriendList(void);

void drawFriendAdd(void);
int addFriendData(int userNum);
void drawFriendMapLoading(void);
void drawFriendOrder(void);

int getShowWindowInfo(int key,int floor);
void drawFriendOrderItem(void);
void drawMail(void);
void drawMiniProFile(void);

void keyDialog(M_Int32 type,M_Int32 param1,M_Int32 param2);
void drawDialog(void);
void setDialog(M_Char *fileName, M_Int32 sentence, M_Int32 width, M_Int8 line);
void prcQuest(void);
void drawQuestIcon(void);
void drawQuestInfo(void);
void drawQuestInfoGiftPopup(void);
void drawNpcPhoto(int x,int y,int npcNum,int reSize);
void getSprintfQuestCheck(int slotNum,int checkNum);
int	getQuestCheckTotalNum(int slotNum);
void setQuest(int checkType,int num,int code);
int questShortCut(int questType,M_Boolean isState,int questCode);
void drawTutoInfo(void);
void prcTuto(void);
void drawStaffMake(void);
void stateStaffMake(int type,int inType);
void drawQuestResult(void);
void addOrderQuest(int code);
void drawCarWorldMap(int x,int y,int code,int pos,int anyCnt,int reSize);
void drawNpcIcon(int x,int y,int npcNum);
//void drawModelList(void);
//void drawModelUpGrade(void);
//void drawNewModel(void);
//int addInventoryModel(int modelCode);
//void setModelList(int grade);
//void outPutInventoryModel(int slotNum);
//void setModelUpGradeList(int slotNum);
//void setNewModel(int type);





int getModelKeyToSlotNum(int key);



void setStaffFitting(void);
void drawModelFitting(void);
void drawRunWay(void);
void drawRunWayResult(void);


void setFashionShowResult(void);


void drawInteriorTeam(void);
void setFriendOrderTab(void);




void drawOrderRecv(void);

void checkExternMove(void);
void drawDropIcon(void);
void setDropIcon(int x,int y,int type0,int num0,int type1,int num1,int type2,int num2);
void drawEventBoxTouch(int x,int y,int img,int anyCnt);
void drawColorPaper(void);
void makeColorPaper(int makeNum);
void drawFlashEff(M_Boolean isMapMode);
void setFlashEff(int x,int y,int resize,M_Boolean isMapMode);

void drawFashionEff(void);
void makeFashionEff(int rectW,int speed);
void drawSpotLight(void);
void setSpotLight(int code,int x,int y,float fspeed);
void setEventBoxPos(int cnt);
void drawEmoticon(int x,int y,XEMOTICON *xEmoticon);
void addDebug(const char*strText);
void drawDebug(void);
void worldMapInitImgLoad(int type);
void setEmoticon(XEMOTICON *xEmoticon,int type);
void drawGlitterEff(XGLITTEREFF *xGlitterEff);
void drawCarBox(int x,int y,int carCode,int anyCnt,int pos);
void drawProductionArrow(int x,int y);
void setUiHide(void);
void getUiHide(void);
M_Boolean checkOrderQuest(int code);
void setTrendTemp(int type,int makeType);




void resetDoor(void);
void drawExternalWallIcon(int x,int y,int code);
void setCallShopAssistant(int shopNpcNum,int assistantNum);
void setStateFashion(void);
void modelImgLoad(M_Boolean isLoad);
void setStateMail(void);
void setStateFriendList(void);
void makeBlinkEff(int x,int y);
void drawBlinkEff(void);
XIMG* getImgFittingF(int type,int list,int layer1,int layer2);
XIMG* getImgFittingFInOut(int type,int list,int layer1,int layer2);
void resetChair(int floor);
void setNpcStatePorterMove(int manNum,int womanNum);
M_Boolean keyQuestIcon(int type, int param1, int param2,int touchId);
void setStateStaff(int slot);
M_Boolean drawStamp(int x,int y,int anyCnt,int type);

void drawExtensionStamp(void);
M_Boolean drawExtensionContract(int x,int y,int anyCnt);
void drawExtensionTile(int anyCnt);
void drawProductionMenu(void);

int inputProductionMenu(int code);
int getProductionMenu(int code);
void outputProductionMenu(int code);
void setProductionMenuMake(void);
void makeProductionMain(void);
void inputProductionRecord(int code);
int getEmptySlot(void);

int linkProductionMenu(int code);
int linkInteriorShop(int code);
void drawExternalWall(int x,int y,int floor);
void drawExternalWallChange(void);
M_Boolean checkProductionOrderKey(int orderKey);
int getCarParkSlotNum(int orderKey);
int getProductionMenuSlotNum(int orderKey);
void setLock(void);
int linkStaffMenu(int code);
void drawCarParkSelectMode(void);
void drawFashionDrop(void);
void setFashionDrop(int slot,int x,int y,int scale,int endX,int endY,int scaleEnd,int code);
void initFashionDrop(int slot);

void initSongNpc(void);
void prcShowWindow(void);
void checkTimeHacking(void);
void drawSwitchUp(int x,int y,XSWITCH * xSwitch,int XIMG,int totalNum, int gab);
void drawBgFillRect(void);
void drawCashUi(M_Boolean isAfter);
void drawMailTextBox(void);
void drawOption(void);
void setStateOption(void);
M_Boolean isOrderNew(int key);
void setOrderNewSave(void);
void setHelpInfo(const char* text);
void drawHelpInfo(void);

void keyTrend(int type, int param1, int param2);
void setHelpInfoCenter(const char* text);
void resetFame(void);
void drawModelName(int x,int y,int code);

void drawModelEff(void);
void setModelEff(int x,int y);
//void drawModelCasting(void);
void drawModelSlot(int x,int y,int selectNum);

//int getModelUpgradePrice(int oriInvenSlot,int targetInvenSlot);
//int getModelUpgradePer(int oriInvenSlot,int targetInvenSlot);


void drawModelShow(int modelCode,XFITTINGLAYER *xF,int anyCnt);
//void drawModelRotEff(int xPos,int yPos,int anyCnt);
void drawModelUpgradeOn(void);
void drawFashionShowMainNew(void);
void drawFashionShowInfo(void);
void drawNoticeFS(void);
void setStateRunWay(void);
M_Boolean getIsVote(int userNum);
void addIsVote(int userNum);
void loadImgFreeImgFashionShow(M_Boolean isLoad);

//int addInventoryModel_FRIEND(int modelCode);
void drawModelShop_FRIEND(void);
void drawModelShopBuyPopup_FRIEND(void);

int checkKakaoInvite(char *strId);
void addKakaoInvite(char *strId);
void addKakaoAppInvite(char *strId,M_Boolean isFail);
int checkKakaoAppInvite(char *strId);
void prcInShopPer(void);
void shopNpcErrSpeak(int npcNum);
void loadFashionFImg(int imgType,int imgList);

void drawGiftShopResult(void);
void makeModelShopNpc(void);
//void prcModelShopNpc(void);
//void setModelNpcStateFloorUp(int npcNum,int floor);
//void setModelNpcStateFloorDown(int npcNum,int floor);
//void setModelNpcSpeakWelCome(int floor,M_Boolean isIn);
void freeFashionFLayer(void);
void loadFashionFImgWorldMap(int type, int listNum);
void shopImgFreeLoad(M_Boolean isLoad);
void optionImgFreeLoad(M_Boolean isLoad);
void minigameFreeLoad(M_Boolean isLoad);
void mailFreeLoad(M_Boolean isLoad);
void friendListFreeLoad(M_Boolean isLoad);
void setStateModel(void);
void staffMakeFreeLoad(M_Boolean isLoad);
void lvUpFreeLoad(M_Boolean isLoad);
void worldMapNoticeFreeLoad(M_Boolean isLoad);
void trendFreeLoad(M_Boolean isLoad);
void friendOrderItemFreeLoad(M_Boolean isLoad);
void friendOrderFreeLoad(M_Boolean isLoad);
void drawThemaIcon(int x, int y,int code);
void interiorShopFreeLoad(M_Boolean isLoad);
void carStorageFreeLoad(M_Boolean isLoad);

int checkSellTableSlotItem(int floor,int code);
void setDrawObjCenter(int type,int listNum);
float getFashionColorPer(int main,int target);

void initFashionColor(int main,float t0,float t1,float t2,float t3,float t4,float t5,float t6,float t7,float t8,float t9,float t10,float t11);
float getFashionConceptPer(int main,int target);
void initFashionConcept(int main,float t0,float t1,float t2,float t3,float t4,float t5,float t6,float t7,float t8);

M_Boolean checkXfLimit(XFITTINGLAYER *xF);
int getWorldmapNpcMakeTime(void);
void drawProductionCashPopup(void);
void drawProductionCashPopup_FP();
void drawSellTableCashPopup(void);
float getSellPer(void);
float getSellTime(void);
int getSellEndTime(void);
void drawWorldmapQuestIcon(int x,int y,int code);
void drawLinkInfo(int x,int y,int colorType);
void drawNewIcon(int x,int y);
void drawMiniGameResultSub(void);
void drawServerSell(void);
void loadImgObj(int type,int listNum);
void makeFire(int x,int y,int makeNum);
void drawFire(void);
M_Boolean drawTrendTouchAny0(int x,int y,int anyCnt);
M_Boolean drawTrendTouchAny1(int x,int y,int anyCnt);
void setFashionShow(int severNum);
M_Boolean checkModelFittingCode(int code,int inventoryModelNum);
void addEventBox(int img,int x,int y,int floor,int type,int h,int anyCnt,float touchImgWH);
void makeGlitterEff(XGLITTEREFF xGlitterEff[],int w,int h);
void prcGlitterEff(XGLITTEREFF xGlitterEff[],int x,int y);
void npcSetImgLoad(int k);
void getFashionColorStr(char *strText,int code);
void getFashionConceptStr(char *strText,int code);
void setCommaNum(char *strTempS,int num);
//void sortModelList(void);
//void sortModelListFriend(void);
void checkSocialDay(void);
int getSocialTemp(int type);

void drawDressCode(void);
void drawSocialProfile(void);
int getProductionMenuIng(int code);
M_Boolean checkBuildPos(int type,int listNum,int rever);
void buildModeClr(void);
int getMonthToDay(int month);
void checkAccessBonus(void);
void drawAccessBonus(void);
void accessBonusFreeLoad(M_Boolean isLoad);
void initAccessBonus(int code,int type,int num,int iconNum);
void setSprintfAccessBonusName(char * strText,int type,int num);
void drawAccessBonusResult(void);
void drawDialogTuto(void);
void keyDialogTuto(M_Int32 type,M_Int32 param1,M_Int32 param2);
void drawFingerPoint(int x,int y,M_Boolean isBgImg);
void prcKakaoPhotoInit(void);
void setLinkSellTable(int code,int sellTableType);
int getChair(int floor,int x,int y);
int getStaffHairNum(int code);
int getStaffFaceNum(int code);
int getStaffFashionNum(int code);
int getUserW(int totalCnt,int nowCnt,int rever);
int getUserH(int totalCnt,int nowCnt,int rever);
//void drawModelMain(void);
//void drawModelInfo(void);
int getModelMainSlot(int key);
void drawModelNameString(int x,int y,int ank,int modelCode);
int getModelGiftNum(int inventoryNum,int gab);
int getModelGiftTime(int inventoryNum,int gab);
void drawModelMainGiftInfo(void);
void drawModelMainGiftResult(void);
void drawModelMainGiftIcon(int x,int y,int type);
void makeWaste(void);
//void drawModelMain_FRIEND(void);
int getModelKeyToSlotNumFRIEND(int key);
void initTutoLimit(int type);
void drawFriendInvite(void);
void setKakaoinviteOk(void);
void loadModelShopNpcImg(int slotNum);
void prcExternalShake(void);
void friendListAddFreeLoad(M_Boolean isLoad);
void subLoading(void);
void loadImgFreeImgRunWay(M_Boolean isLoad);
int getStringByte(char *strText);
void drawBackBuffer(char* backBuffer,char *imgBuffer,int x,int y,int bufW,int bufH,M_Boolean isRever);
void makeBackBuffer(int floor);
void drawArrowPacker(int img,M_Int32 x,M_Int32 y,M_Int32 type);
void drawNumPacker(int img,M_Int32 x, M_Int32 y, M_Int32 value, M_Int32 gab,M_Int32 ank);
void drawNumCommaPacker(int img,M_Int32 x, M_Int32 y, M_Int32 value, M_Int32 gab,M_Int32 ank,int imgComma,int commagab);
void drawTodaySocialFashion(void);
void checkTodaySocialFashion(void);
void drawRankChange(void);
void checkTodayRunway(void);
void drawTodayRunway(void);
void initKakaoAppInviteAuto(void);
int getModelLayered(int inventoryNum,int gab);
int getUserWSocial(int totalCnt,int nowCnt,int rever);
int getUserHSocial(int totalCnt,int nowCnt,int rever);
void drawModelHelp(void);
void checkFashionShowLicence(int score);
void drawFashionShowLicence(void);
void drawRunWayResultBonus(void);
void setRunWayResultBonus(void);
void drawRunWayBonusIcon(int x,int y,int type);
void setSaleShop(void);
void drawSaleShop(void);
void saleShopFreeLoad(M_Boolean isLoad);
void drawQuestArrow(int x, int y);
void drawNoticePopup(void);
int nextNoticePopup(int nowNum);
void getRtf(XRTF *xRtf,int speedMillisecond);
void demoRtf(void);
void testMiniGame(int loop);
void setStateCarSelectMode_Production(void);
void orderSelectItemOk(void);
int getCharSpecialCnt(char *strText);
void aliceShockFreeLoad(M_Boolean isLoad);
void drawAliceShock(void);
void drawAliceShockResult(void);
void drawBuffBonus(void);
int checkYMDS(int year,int month,int day,int hour);
void drawCollection(void);
void collectionFreeLoad(M_Boolean isLoad);
void setStateCollection(void);
void getSprintfSKillInfo(char*strText,int code,int selectSKill,int getType);
void getSprintfModelSKillType(char*strText,int code);
int getSkillPer(int modelCode,int skillType);
void setCollectionTab(void);
void drawCollectionFashionThemeIcon(int x,int y,int themeNum);
void setThemeList(void);
void faceHairImgFree(void);
void drawRunwaySkillUi(void);
void drawCashGift(void);
void setCashGift(void);
void getUiShowType();
void setStateMileageShop();
void mileageShopFreeLoad(M_Boolean isLoad);
void drawMileageShop();
void setMileageShopCategory();
int getProfilePhotoUrlNum(char* strUrl);
void drawProfilePhotoUrl(int x,int y,char* strUrl);
void prcNetEventPhotoUrl();
void addNetEventPhotoUrl(int type);
void delNetEventPhotoUrl(int eventNum);
void setMileage(int mileage);
void drawMileageShopSendPopup();
void setStateMileageShopSendPopup();
void drawMileageShopInfo();
void setAccessBonusShow();
void drawPrepayUi(int x,int y);
void setPrepayDay();
void drawPrepay();
void drawPrepayDay();
void prepayFreeLoad(M_Boolean isLoad);
void setPackagePopup(int type);
void drawPackagePopup();
void keyPackagePopup(int type, int param1, int param2);
bool isSellPackage(int type);
void drawPackageUi(int x,int y,int type);
void prcEventQuest();
void setEventQuest(int checkType,int num,int code);
void eventQuestFreeLoad(M_Boolean isLoad);
void drawEventQuest();
void drawEventQuestIcon(int x,int y,int type);
void keyEventQuest(int type, int param1, int param2);
void drawEventQuestUi(int x,int y);
void prcEventQuest();
int getTimeSec(int year,int month,int day,int hour,int minute,int sec);
void setEventQuestList(int questType);
void drawEventQuestBg(int x,int y,int type);
void drawRivalComingSoon();
void drawHotDeal();
void keyHotDeal(int type, int param1, int param2);
void setHotDealSlot(int slotNum);
void hotDealFreeLoad(M_Boolean isLoad);
void prcHotDeal(void);
void setHotDeal();
bool isInteriorUse(int code);
int getBlinkAlpha();
void makeBlinkEff2(int x,int y,int type);
void drawBlinkEff2(int type);
void drawRivalWorldMap();
void keyRivalWorldMap(int type, int param1, int param2);
void drawRival();
void keyRival(int type, int param1, int param2);
void rivalFreeLoad(M_Boolean isLoad);
void rivalWorldMapFreeLoad(M_Boolean isLoad);
void setRivalWorldMap();
void setRival();


void drawRivalBuilding(int x,int y,int code,int ank);
void drawRivalNpc(int x,int y,int code,int ank);
void drawProductionMenuLatest();
void setProductionMenuLatest();
void addProductionMenuLatest(int code);
void drawRivalTitle(int x,int y,int code,int ank);
void drawRivalInfo();
void keyRivalInfo(int type, int param1, int param2);
void setRivalQuest(int type,int num);
void prcRivalQuest();
void addHelpList(int userKey);
void setRivalInfo();
void drawRivalNpcIcon(int x,int y,int code,int ank);
void drawRivalResult();
void drawRivalGuest();
void initRivalGuest();
bool isRivalGuestBg(int type,int x,int y);
void rivalUi(int x,int y);
void drawHelpList();
void keyHelpList(int type, int param1, int param2);
void helpListFreeLoad(bool isLoad);
void setHelplist();
void drawHelpListUi(int x,int y);
char *getGradeName(int grade);
void setFastScroll(int x,int y,int w,int h,XDRAGSCROLL *xDragScroll);
void drawFastScroll();
bool keyFastScroll(int type, int param1, int param2,int touchId,int touchCount);
void drawMyShopRefresh(int x,int y);
void setMyShopRefresh();
void setJewelQuest(int type,int num,int code);
void prcJewelQuest();

void drawJewelQuest();
void keyJewelQuest(int type, int param1, int param2);
void jewelQuestFreeLoad(bool isLoad);
void initJewelQuest();
void sortJewelQuest();
char *getJewelQuestName(int type,int code,int value);
void drawJewelIcon(int x,int y,int code);
void keyJewelResult(int type, int param1, int param2);
void drawJewelResult();
int isInteriorUseCount(int code);

void jewelResultFreeLoad(bool isLoad);
void setJewelResult(int jewelCode);
void drawJewelCard(int x,int y,int jewelQuestCode);
void drawAmuletSetting();
void keyAmuletSetting(int type, int param1, int param2);
void drawAmuletUiIcon(int x,int y,int code,int open);
void drawAmuletIcon(int x,int y,int code);
int getAmuletSocketUse(int jewelCode);
void drawAmuletUi(int x,int y);
char *getJewelBuffName(int buffType,int buffValue);
void drawAmuletSlot(int x,int y,int size,int type);
void makeBlinkEffAmulet(int x,int y);
void drawAmuletBg(int x,int y,int code);
bool isJewelQuestOpenCard(int jewelQuestCode);
void clubListFreeLoad(bool isLoad);
void drawClubList();
void keyClubList(int type, int param1, int param2);
void refreshClubList();
void drawClubIcon(int x,int y,int code);
void drawClubItem(int x,int y,int code);
void drawClubListSearch();
void drawClubMake();
void drawClubLobby();
void keyClubLobby(int type, int param1, int param2);
void clubLobbyFreeLoad(bool isLoad);
void clubDonationFreeLoad(bool isLoad);
void initClubDonation();
void drawClubDonation();
void keyClubDonation(int type, int param1, int param2);
void drawClubUi(int x,int y);
void setClubHistoryText(char * strTemp,int slot);
void initFashionWeekLobby();
void fashionWeekFreeLoad(bool isLoad);
void drawFashionWeekLobby();
void keyFashionWeekLobby(int type, int param1, int param2);
void drawFitting_FASHIONWEEK();
void keyFitting_FASHIONWEEK(int type, int param1, int param2);
void keyFashionWeekSetting(int type, int param1, int param2);
void drawFashionWeekSetting();
void drawFashionWeekSelectModel();
void keyFashionWeekSelectModel(int type, int param1, int param2);
void keyFitting_FASHIONWEEK_SELECTMODEL(int type, int param1, int param2);

void setFashionStudioSlot();
void drawFashionStudioInfo();
void drawFashionStudio();
int getModelMainSlot_FASHIONWEEK(int key);
void drawLoadingIcon(int x,int y);
void drawFashionWeekGiftInfo();

void clubShopFreeLoad(bool isLoad);
void initClubShop();
void drawClubShop();
void keyClubShop(int type, int param1, int param2);

void clubShopICONFreeLoad(bool isLoad);
void initClubShopICON();
void drawClubShopICON();
void keyClubShopICON();

void clubStorageFreeLoad(bool isLoad);
void initClubStorage();
void drawClubStorage();
void keyClubStorage(int type, int param1, int param2);

void clubShopGiftFreeLoad(bool isLoad);
void initClubShopGift();
void drawClubShopGift();
void keyClubShopGift(int type, int param1, int param2);

void clubIconShopFreeLoad(bool isLoad);
void initClubIconShop();
void drawClubIconShop();
void keyClubIconShop(int type, int param1, int param2);

void changeClubIconFreeLoad(bool isLoad);
void initChangeClubIcon();
void drawChangeClubIcon();
void keyChangeClubIcon(int type, int param1, int param2);

void clubnameModifyFreeLoad(bool isLoad);
void initClubNameModify();
void drawClubNameModify();
void keyClubNameModify(int type, int param1, int param2);


void CandyFormerFreeLoad(bool isLoad);
void initCandyFormer();
void drawCandyFormer();
void keyCandyFormer(int type, int param1, int param2);
int getFormerIndex(int key);
int getFormerIndex2(int index);
void prcFormerTimer();
void prcFormerCount();

void prcProductionSlotTimer();
int getProductionIndex(int key);
void initWorldMapRocket();
void playWorldMapRocket();
void prcWorldMapRocket();

void drawWorldMapRocket();
void drawWorldMapStorage();
void drawWorldMapVinylHouse();
void drawWorldMapAntenna();

void prcProductTime();
void prcAutoProduct();
void sleepAutoProduct();
int getSellMaxNum(int code);
void prcSellTime();
void prcAutoSell();
void sleepAutoSell();

void LuluPangLobbyFreeLoad(bool isLoad);
void initLuluPangLobby();
void drawLuluPangLobby();
void keyLuluPangLobby(int type, int param1, int param2);
void LuluPangSelectModelFreeLoad(bool isLoad);
void drawLuluPangSelectModel();
void keyLuluPangSelectModel(int type, int param1, int param2);
void keyLuluPangSettingFitting(int type, int param1, int param2);
void drawNoticeLuluPang();
int getModelMainSlot_LULUPANG(int key);

//여기서부터 작업한 것....KBY
////////////////////
//제작기
void loadFashionFImg_FP(int imgType,int imgList);
///////////////////////////////////////////////////////////////////
//추가 수정 사항 KBY 2018.2.26
void productionFreeLoad_FP(bool isLoad);
///////////////////////////////////////////////////////////////////
void setStateProductionMenu(void);
void drawProduction_FP();
/////////////////////
//옷장
extern XTOUCH xTouchFitting;
void initFitting_FP();
void loadFittingImg_FP(int imgType, int imgListNum);
void fittingFreeLoad_FP(bool isLoad);
void drawFitting_FP();
void keyFitting_FP(int type, int param1, int param2, int touchId);
bool keyFastScroll_FP(int type, int param1, int param2,int touchId,int touchCount);
/////////////////////
//온실
#define MATERIALSLOTMAX                     64
#define GREENHOUSESLOT_LV_MAX               5
#define GREENHOUSE_STATE_MAIN               0
#define GREENHOUSE_STATE_CANCLEPOPUP      GREENHOUSE_STATE_MAIN+1

//온실의 제작 요소
typedef struct
{
    int code;
    int lv;
    int makeTime;
    int cnt;
    
    char strName[64];
}XGREENHOUSE_MATERIALSLOT_FP;

typedef struct
{
    int totalNum;
    XGREENHOUSE_MATERIALSLOT_FP xSlot[MATERIALSLOTMAX];

}XGREENHOUSE_MATERIALDATA_FP;
extern XGREENHOUSE_MATERIALDATA_FP xGreenHouse_MaterialData_FP;

typedef struct
{
    int state;//온실 토양의 상태
    int MaterialCode;//재배중인 꽃
    int endTime;//꽃 수확완료 시간
    int itemCnt;//한번에 수확시 획득되는 양
    int Upgrade;//업그레이드 정도
    bool produce;//생산중인가?
}XGREENHOUSE_FP_SLOT;

typedef struct
{
    int state;//온실의 상태
    int EndTimer[MATERIALSLOTMAX];//각 슬롯별 온료시간
    int selectSlot;//선택된 토양
    int selectProduct;//선택된 꽃
    int totalSlot;//총 슬롯 수
    int index;
    int imgNum[MATERIALSLOTMAX];
    int AnyCnt[MATERIALSLOTMAX];
    //버튼 연출을 위한 변수
    bool isTouchMaterial;
    bool isTouchUpgrade[MATERIALSLOTMAX];
    bool isTouchFast[MATERIALSLOTMAX];
    bool isTouchLeftBtn;
    bool isTouchRightBtn;
    bool isTouchLeftArrow;
    bool isTouchRightArrow;
    bool isTouchClr;
    bool isTouchOpen;
    bool isTouchProduct;
    bool isTouchPopupClr;
    bool isTouchYes;
    bool isTouchNo;
    
    //온실 스크롤
    XDRAGSCROLL xDragScrollGreenHouseS;//토양 스크롤
    XDRAGSCROLL xDragScrollGreenHouseB;//꽃 스크롤
    
    XTOUCH  xTouchLeftBtn;//꽃 왼쪽버튼
    XTOUCH  xTouchRightBtn;//꽃 오른쪽 버튼
    XTOUCH  xTouchLeftArrow;//토양 왼쪽 버튼
    XTOUCH  xTouchRightArrow;//토양 오른쪽 버튼
    XTOUCH  xTouchList[MATERIALSLOTMAX];//꽃 터치영역
    XTOUCH  xTouchSlot[MATERIALSLOTMAX];//토양 토치영역
    XTOUCH  xTouchOpen;//토양 해금 터치영역
    XTOUCH  xTouchFast[MATERIALSLOTMAX];//즉시완료 터치영역
    XTOUCH  xTouchUpgrade[MATERIALSLOTMAX];//업그레이드 터치영역
    XTOUCH  xTouchYes;//제작 취소 터치영역
    XTOUCH  xTouchNo;//제작 취소의 취소 터치영역

    XGREENHOUSE_FP_SLOT xSlot[MATERIALSLOTMAX];
}XGREENHOUSE_FP;
extern XGREENHOUSE_FP xGreenHouse_FP;

extern XTOUCH xTouchGreenHouse;
extern XIMG imgGreenHouse[30];
extern XIMG imgFlower[128][4];
extern XIMG imgSlotLv[GREENHOUSESLOT_LV_MAX];
void initGreenHouse_FP();
void greenHouseFreeLoad_FP(bool isLoad);
void drawGreenHouse_FP();
void keyGreenHouse_FP(int type, int param1, int param2);
void prcGreenHouseSlotTimer();
void drawGreenHouseSlotCanclePopup_FP();
void keyGreenHouseSlotCanclePopup_FP(int type, int param1, int param2);
/////////////////////
//친구리스트
extern XIMG imgfriendList[30];
void friendListFreeLoad_FP(bool isLoad);
void drawfriendList_FP();
void keyfriendList_FP(int type, int param1, int param2);
/////////////////////
//친구리스트 검색
void drawfriendSearch_FP();
void keyfriendSearch_FP(int type, int param1, int param2);

///////////////////////////////////////////
//전송기
void startSendMachine_FP();
void endSendMachine_FP();
void drawSendMachine_FP();
void prcSendMachine_FP();
void FreeLoadSendMachine_FP(bool isLoad);
void keySendMachine_FP(M_Int32 type,M_Int32 param1,M_Int32 param2);
void setSendMachineBtnType_FP(int btnType);
void setSlotDress(int dressNum, int dressCnt);
bool isPlaySendMachine();
void setSendMachineGameCnt(int cnt);

///////////////////////////////////////////
//물레
#define SPINNINGWHEEL_STATE_MAIN               0
#define SPINNINGWHEEL_STATE_CANCLEPOPUP      GREENHOUSE_STATE_MAIN+1
//물레의 실타래 정보
typedef struct
{
    int code;
    int lv;
    int makeTime;
    int cnt;
    
    char strName[64];
}XSPINNING_MATERIALSLOT_FP;

typedef struct
{
    int totalNum;
    XSPINNING_MATERIALSLOT_FP xSlot[MATERIALSLOTMAX];
    
}XSPINNING_MATERIALDATA_FP;
extern XSPINNING_MATERIALDATA_FP xSPinning_MaterialData_FP;

typedef struct
{
    int state;//물레의 상태
    int MaterialCode;//물레가 제작중인 실타래
    int endTime;//완료 시간
    int itemCnt;//생산되는 개수
    int Upgrade;//업그레이드 정도
    bool produce;//생산중인가?
}XSPINNING_FP_SLOT;

typedef struct
{
    int state;//물레의 상태
    int EndTimer[MATERIALSLOTMAX];//물레 슬롯들의 완료시간
    int selectSlot;//선택된 물레
    int selectProduct;//선택된 실타래
    int totalSlot;//총 슬롯의 수
    int index;
    int AnyCnt[MATERIALSLOTMAX];
    int imgNum[MATERIALSLOTMAX];
    int StarAnyCnt[MATERIALSLOTMAX];
    
    //버튼 이팩트를 위한 변수
    bool isTouchMaterial;
    bool isTouchUpgrade[MATERIALSLOTMAX];
    bool isTouchFast[MATERIALSLOTMAX];
    bool isTouchLeftBtn;
    bool isTouchRightBtn;
    bool isTouchLeftArrow;
    bool isTouchRightArrow;
    bool isTouchClr;
    bool isTouchOpen;
    bool isTouchProduct;
    bool isTouchPopupClr;
    bool isTouchYes;
    bool isTouchNo;
    
    //스크롤
    XDRAGSCROLL xDragScrollSpinningS;//제작 스크롤
    XDRAGSCROLL xDragScrollSpinningB;//슬롯 스크롤
    
    XTOUCH  xTouchLeftBtn;//제작 스크롤 왼쪽
    XTOUCH  xTouchRightBtn;//제작 스크롤 오른쪽
    XTOUCH  xTouchLeftArrow;//슬롯 스크롤 왼쪽
    XTOUCH  xTouchRightArrow;//슬롯 스크롤 오른쪽
    XTOUCH  xTouchList[MATERIALSLOTMAX];//제작 터치영역
    XTOUCH  xTouchSlot[MATERIALSLOTMAX];//슬롯 터치영역
    XTOUCH  xTouchOpen;//슬롯 해금 버튼 터치영역
    XTOUCH  xTouchFast[MATERIALSLOTMAX];//즉시완료 터치영역
    XTOUCH  xTouchUpgrade[MATERIALSLOTMAX];//업그레이드 터치영역
    XTOUCH  xTouchYes;//제작 취소 확인
    XTOUCH  xTouchNo;//제작 취소의 취소버튼
    
    XSPINNING_FP_SLOT xSlot[MATERIALSLOTMAX];//물레의 정보
}XSPINNING_FP;
extern XSPINNING_FP xSpinning_FP;

extern XTOUCH xTouchSpinningWheel;
extern XIMG imgSpinningWheel[30];
void initSpinningWheel_FP();
void spinningWheelFreeLoad_FP(bool isLoad);
void drawSpinningWheel_FP();
void keySpinningWheel_FP(int type, int param1, int param2);
void drawSpinningWheelSlotCanclePopup_FP();
void keySpinningWheelSlotCanclePopup_FP(int type, int param1, int param2);
void prcSpinningWheelSlotTimer();
///////////////////////////////////////////
//Variable

typedef struct
{
    int levelMax;
    int carrotMax;
    int carrotTime;
    
}XCHS;
extern XCHS xChs;

///////////////////////////////////////////
//당근 획득

typedef struct
{
    int carrotComplete;
    int carrotTemp;
    int time;
    int TimeTemp;
    bool isAdd;
}XCALCCARROT;
extern XCALCCARROT xCalcCarrot;
void prcCarrot();

///////////////////////////////////////////
//상점
#define SHOPSELECTTABBMAX       5
#define SHOPSELECTTABSMAX       20
#define SHOP_FP_SLOTMAX         512

#define SHOP_STATE_MAIN         0
#define SHOP_STATE_DRESSPOPUP   SHOP_STATE_MAIN+1
#define SHOP_STATE_POPUP        SHOP_STATE_DRESSPOPUP+1

#define SHOPPOPUP_STATE_MAIN    0
#define SHOPPOPUP_STATE_POPUP   SHOPPOPUP_STATE_MAIN+1

extern XIMG imgShop[30];
extern XIMG imgInterior_FP[INTERIORSLOTBMAX][INTERIORSLOTSMAX];
typedef struct
{
    int buff;
    int code;
    char strItemName[512];
    char buffInfo[512];
}XSHOP_FP_SLOT;
typedef struct
{
    bool isTouchInfo;//정보 보기 버튼을 눌렀는가?
    bool isTouchClr;//상점의 닫기버튼을 눌렀는가?
    bool isTouchPopUpClr;//구매확인 팝업의 닫기버튼을 눌렀는가?
    bool isTouchPreviewClr;//미리보기 창의 닫기버튼을 눌렀는가?
    bool isTouchYes;//구매확인 버튼을 눌렀는가?
    bool isTouchNo;//구매취소 버튼을 눌렀는가?
    bool isTouchLeftArrow;//미리보기에서 왼쪽화살표를 눌렀는가?
    bool isTouchRightArrow;//미리보기에서 오른쪽화살표를 눌렀는가?
    
    
    int state;//상점 메인 상태
    int state2;//상점 팝업의 상태
    int totalNum;//아이템의 총개수
    int selectTabB;//선택된 왼쪽 탭
    int selectTabS;//선택된 윗쪽 탭
    int selectSlot;//선택된 슬롯
    int totalTabS;//윗쪽 탭의 총 개수
    int index;//
    int pos;//캐릭터가 바라보는 방향
    
    XTOUCH xTouchSlot[SHOP_FP_SLOTMAX];//슬롯 터치영역
    XTOUCH xTouchTabB[SHOPSELECTTABBMAX];//왼쪽 탭의 터치영역
    XTOUCH xTouchTabS[SHOPSELECTTABSMAX];//위쪽 탭의 터치영역
    XTOUCH xTouchInfo;//정보보기 터치영역
    XTOUCH xTouchPreview;//미리보기 터치영역
    XTOUCH xTouchYes;//구매확인 터치영역
    XTOUCH xTouchNo;//구매취소 터치영역
    XTOUCH xTouchLeftArrow;//미리보기 왼쪽회전 터치영역
    XTOUCH xTouchRightArrow;//미리보기 오른쪽 회전 터치영역
    
    XSHOP_FP_SLOT xSlot[SHOP_FP_SLOTMAX];
    XDRAGSCROLL xDragScrollShopList;//상점의 스크롤
    
}XSHOP_FP;
extern XSHOP_FP xShop_FP;

void shopFreeload_FP(bool isLoad);
void initShop_FP();
void drawShop_FP();
void keyShop_FP(int type, int param1, int param2,int touchId);
void drawDressShop_PopUp_FP();
void keyDressShopPopUp_FP(int type, int param1, int param2);
void drawDressShopPreview_FP();
void keyDressShopPreview_FP(int type, int param1, int param2);
void drawShopPopUp();
void keyShopPopUp(int type, int param1, int param2);
void loadInteriorImg_FP(int imgType, int imgListNum);

///////////////////////////////////////////
//상점 함수 추가 (Cash UI에서 재화를 누를 경우 연결할때 쓰는 함수들...) KBY 2018.2.23

void setShop_FP(int selectTabB, int selectTabS);


///////////////////////////////////////////

///////////////////////////////////////////
//npc 헤어, 얼굴 draw함수 추가
void loadFashionFImgWorldMap_FP(XSPRIT *xSprit, int code, int pos);
void loadFashionFImgWorldMapBig_FP(XSPRIT *xSprit, int code, int pos);
void freeFashionFLayerBig_FP();
void setSpritF_FP(XSPRIT *xSprit,XFITTINGLAYER *xF,int pos);
void setSpritFBig_FP(XSPRIT *xSprit,XFITTINGLAYER *xF,int pos);
void setNpcBody_FP(XSPRIT *xSprit, int pos);
void setNpcBodyBig_FP(XSPRIT *xSprit, int pos);
void setFittingSlot_FP(int tab);
void setNpcHair_FP(XSPRIT *xSprit, int hairNum, int pos);
void setNpcFace_FP(XSPRIT *xSprit, int faceNum, int pos);
void setNpcHairBig_FP(XSPRIT *xSprit, int hairNum, int pos);
void setNpcFaceBig_FP(XSPRIT *xSprit, int faceNum, int pos);
bool isDressChange();
///////////////////////////////////////////

void makeShopAssistant();
void makeMyCharacter();
void drawMyCharacter();
///////////////////////////////////////////
//인테리어 편집
extern XIMG imgInteriorBuild[20];

//추가 사항 KBY 2018.2.26
void interiorbuildFreeLoad_FP(bool isLoad);
///////////////////////////////////////////
//우편함 KBY

extern XIMG imgMail[30];
void mailFreeLoad_FP(bool isLaod);
void drawMail_FP();
void keyMail_FP(int type, int param1, int param2);

///////////////////////////////////////////
//프로필 편집 KBY 2018.2.26
extern XIMG imgProfile;
extern XIMG imgPhoto[10];
extern XIMG imgNonProfile;

void profilePhotoFreeLoad_FP(bool isLoad);
#endif
