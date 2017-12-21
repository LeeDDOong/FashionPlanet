#ifndef CHEF_
#define CHEF_


class FashionShop : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(FashionShop);
    
    
    
    virtual void onHttpRequestCompleted(Node *sender,void *data);
    
    
    
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *unused_event);
    virtual void run(float fDelay);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};


//GAME_STATE
#define GAME_LOGO				0
#define GAME_MAINMENU			1
#define GAME_WORLDMAP			2
#define GAME_LOADING			3

//PLAY_STATE
#define PLAY_PLAY				0		

#define PLAY_MSG				1		
#define PLAY_DIALOG				2




//***************화면관리***************
extern M_Int32 lcdW;
extern M_Int32 lcdH;
extern M_Int32 cx;				
extern M_Int32 cy;

extern int orilcdW;
extern int orilcdH;

//*************************************

//***************인앱관리***************
#define IAP_STATE_DONT			0//사용안함(평상시)
#define IAP_STATE_ING_TP		1//결제중(키만 막아주자)
#define IAP_STATE_SUCCED_TP 	2//성공
#define IAP_STATE_FAIL_TP		3//실패
#define IAP_STATE_ING_CP		4//결제중(키만 막아주자)
#define IAP_STATE_SUCCED_CP 	5//성공
#define IAP_STATE_FAIL_CP		6//실패

typedef struct
{
	M_Boolean isBilling;
	char strReceipt[4096];
    char strSignature[4096];

	int billLen;
	
	
	
} XBILL;

extern XBILL xBill;

//*************************************
//***************시스템관리***************
extern M_Boolean isCall;			
//*************************************
//***************테스트용***************
extern M_Int32 pdh[10];
//*************************************
//***************상태관리***************
#define LASTLOADINGNUM	40
extern M_Int32 loadingCnt;		
extern M_Int32 gameCnt;			
//GAME_STATE
extern M_Int32 beforState;			
extern M_Int32 nextState;			
extern M_Int32 nowState;			
extern M_Int32 playState;			
extern M_Int32 subState;			
extern M_Int32 subStateTemp;
//*************************************
extern M_Boolean isFontLoading;

extern bool isKeyPress[2];




typedef struct
{
    cocos2d::Image *image;
    bool isSdCard;
    cocos2d::Texture2D *texture;
    
    int w;
    int h;
    
} XIMG;

#define BLEND_SCREEN			0	
#define BLEND_ADDP				1	
#define BLEND_BLACK_WHITE		2	
#define BLEND_MULTIPLY			3	
#define BLEND_DIFFERENCE		4	
#define BLEND_BLACK				5	
#define	BLEND_WHITE				6
#define BLEND_HARDLIGHT			8	
#define BLEND_SHADOW			9	
#define BLEND_RED				10	
#define BLEND_LINEARLIGHT		11	
#define	BLEND_WHITEALPHA		12	
#define	BLEND_REDALPHA			13	
#define	BLEND_SETCOLOR			15


typedef struct
{
    
    cocos2d::Scene* scene;
    cocos2d::Layer *layer;
    cocos2d::Layer *layerTextField;
    
    cocos2d::experimental::ui::WebView *webView;
    bool isTextField;
    
    char strAndDataPack[64];
    char strAndSDCard[64];
    
    char strVerName[64];
    char strDeviceID[128];
    
    
	int r;
	int g;
	int b;
    bool isClip;
	int clipX;
	int clipY;
	int clipW;
	int clipH;
    int alpha;


	int textWidht;
    
    
    
    M_Boolean isBlend;
    M_Int32 blendType;
    M_Int32 blendNum;
    bool isDrawRect;
    M_Boolean isReverse;
    M_Boolean isRotate;
    int rotateNum;
    M_Boolean isReSizeDraw;
	M_Boolean isReSizeDrawXY;
    float reSize;
    float reSizeX;
    float reSizeY;
    float fgameScale;
    float fgameScaleCx;
    float fgameScaleCy;
    float fDelay;
    int prcI;
    int prcCnt;
    
    
    long prcSec;
    long delaySec;
    
    long totalPrcSec;
    
    
    
    
    M_Boolean isAlphaTest;
    bool isMask;
    XIMG *imgMask;
    bool isSpriteGroupBuf;
    bool isSpriteGroupDraw;
    cocos2d::Sprite *spriteGroup;
    
    int nativePopupYesNoType;
    
    bool isNotCache;
    char strNotCacheCnt[128];
    
    
    
    bool isSetTileGroup;
    int tileGroupW;
    int tileGroupH;
    cocos2d::ClippingNode *tileGroup;
    cocos2d::ClippingNode *wallGroup;

    
    
    
    

	
    float deviceW;
	float deviceH;
	M_Boolean isUnAnti;
	M_Boolean isBlendImgLoad;			
	
	
	
    unsigned char* bitmap;		
	
	M_Boolean isHacking;
	int hackingType;
	int hackingNetCnt;
	
	M_Boolean isOrientation;
	
	M_Boolean isResume;
	int resumeAnyCnt;
	
	M_Boolean is4inch;
	
	
	M_Int64 fpsEndTime64;
	int fpsCnt;
	int fpsNow;
	M_Boolean isFpsLimit;	
	float fpsSleep;
        
} XGAME;
extern XGAME xGame;








//*********************************************

typedef struct
{
	M_Int32 clip[4];			
} XCONF;
extern XCONF xConf;
//*********************************************

//*********************************************
typedef struct
{
	M_Char strIOFileName[30];
	M_Char* pBufID;
	M_Int32 resID;
	M_Int32 bufID;
	M_Int32 resSize;
    
    char strChache[128];
    int imgChcheCnt;
    
    
} XIOSTREAM;
extern XIOSTREAM xIOStream;

#define STRTEMPSMAX		512	
#define STRTEMPBMAX		2048	
#define SUBTEMPMAX		50	
extern M_Char strTempS[STRTEMPSMAX];	
extern M_Char strTempB[STRTEMPBMAX];	
extern M_Int32 subTemp[SUBTEMPMAX];		
extern float fsubTemp[SUBTEMPMAX];	
extern M_Int32 isSubTemp[SUBTEMPMAX];		
extern M_Int32 posTemp[SUBTEMPMAX];		


extern M_Char saveTemp[2560000];
extern M_Char strInfo[2][STRTEMPBMAX];
//*************************************


typedef struct{
	int state;
	int totalSize;
	int nowSize;
		
	char strFileName[128];
    
    
    char strTempUrl[512];
    

}XDownloader;
extern XDownloader xDownLoader;
extern M_Char strTextBox[STRTEMPSMAX];
extern M_Char strTextBoxSub[STRTEMPSMAX];
extern M_Boolean isTextBox;
extern M_Int32 textBoxTypeJava;
extern char strRecvTextBox[256];
//********************************
typedef struct
{
	M_Int32 xPos;		
	M_Int32 yPos;
	M_Int32 wPos;
	M_Int32 hPos;
	
	M_Int32 xPosStart;
	M_Int32 yPosStart;

	M_Int32 buffCnt;
    bool touched;
} XTOUCH;

#define TOUCHANYMAX		128

#define TOUCHANY_TYPE_DONT		0
#define TOUCHANY_TYPE_START		1
#define TOUCHANY_TYPE_MOVE		2

typedef struct
{
	M_Int32 state;
	M_Int32 anyCnt;
	
	M_Int32 xPos;
	M_Int32 yPos;
} XTOUCHANY;
extern XTOUCHANY xTouchAny[TOUCHANYMAX];
extern M_Int32 touchAnyNum;


extern XTOUCH xTouch;
extern XTOUCH xTouchS;
extern XTOUCH xTouchTile;
extern XTOUCH xTouchTemp;



extern XTOUCH xTouchBack;

extern XTOUCH xTouchOk;
extern XTOUCH xTouchClr;

extern XTOUCH xTouchArrowUp;
extern XTOUCH xTouchArrowDown;
extern XTOUCH xTouchArrowLeft;
extern XTOUCH xTouchArrowRight;

extern M_Boolean isTouch;
extern M_Int32 touchTypeTemp;
extern M_Int32 touchType;
extern M_Int32 touchTotal;
extern M_Int32 touchScaleCnt;
extern M_Int32 scaleXnow[2];
extern M_Int32 scaleYnow[2];
extern M_Int32 scaleXbefore[2];
extern M_Int32 scaleYbefore[2];




//*******************이미지********************
extern M_Boolean	isResume;
extern M_Boolean	bResume;
extern M_Int32		iResumeNum;




typedef struct{
	int type;
	
}XLOCALPUSH;
extern XLOCALPUSH xLocalPush;


#define LOGO_STATE_KAKAOGAME		0
#define LOGO_STATE_COMPANY			1
typedef struct{
	int state;
	int anyCnt;
	M_Int64 endTime;
	XIMG img[2];

}XLOOG;
extern XLOOG xLogo;

#define HACKINGPACKAGEMAX	256
#define HACKINGPACKAGE_TYPE_IOS			0
#define HACKINGPACKAGE_TYPE_ANDROID		1
typedef struct{
	int totalNum;
	int resultNum;
	char strPackage[HACKINGPACKAGEMAX][32];
	int type[HACKINGPACKAGEMAX];
}XHACKING;
extern XHACKING xHacking;


//*************************************
void startClet(void);

void pauseClet(void);
void resumeClet(void);
void destroyClet(void);
void pauseApp(void);
void resumeApp(void);
void keyMainEvent(int type, int param1, int param2,int touchId,int touchCount);
void paintClet(int x, int y, int w, int h);
void run();
void drawLoading(void);
void freeLoading(M_Int32 type);
void initGame(void);
void initSave(void);
M_Boolean touchCheck(XTOUCH *touch);
M_Boolean rectCheck(M_Int32 x1,M_Int32 y1,M_Int32 w1,M_Int32 h1,M_Int32 x2,M_Int32 y2,M_Int32 w2,M_Int32 h2);
void initTouchCletEvent(int type, int param1, int param2);
void drawTouchTrace(void);
void reResLoad(void);

M_Boolean touchCheckS(XTOUCH *touch);
void drawNetBar(int x,int y);
void setHackingPopup(int type);
void loadObjData();
void loadMapData(const char* strFileName,int floor);
void setShopMoneyData(int code,int type,int price,int point,int bonusPoint,int firstBonusPoint);
void drawGameTip(int x,int y);
void loadImgDocuments(const char* strFileName, XIMG* pImg);
void setPremiumData(int code,int type,int price,int point,const char* strTitle);
void addLocalPush(int sec,const char *strText,int pushCode);
void delLocalPush(int pushCode);
void startIap(void);
void prcIap(void);
void initLogo(void);
void drawLogo(void);
void checkHackingPackage(void);
void checkShopHacking(void);
void checkProductionHacking(void);
void checkInteriorHacking(void);
void checkCarHacking(void);
void checkUserInfoHacking(void);
void checkQuestHacking(void);
void checkExtensionHacking(void);
void checkStaffHacking(void);
void checkGiftHacking(void);
void checkMinigameHacking(void);
void checkModelHacking(void);
void checkEtcHacking(void);
#endif


