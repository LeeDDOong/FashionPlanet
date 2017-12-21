#ifndef __GAMEMENU__
#define __GAMEMENU__

#define MENU_STATE_IN		0
#define MENU_STATE_OUT		1
#define MENU_STATE_WAIT		2

#define MENUMAX		10

typedef struct
{
	M_Int32 selectCnt[MENUMAX];
	M_Int32 anyCnt[MENUMAX];
	M_Int32 moveOutCnt[MENUMAX];
	M_Int32 moveInCnt[MENUMAX];
	
	M_Int32 moveOutGab;
	M_Int32 moveInGab;
} XMENU;
extern XMENU xMenu;

//**************스크롤****************
#define SCROLL_TYPE_0			0
#define SCROLL_TYPE_1			1

typedef struct

{
	M_Int32 totalNum;

	M_Int32 selectNumBefor;
	M_Int32 selectNum;
	
	M_Int32 touchXpos;
	M_Int32 touchYpos;
	M_Int32 touchXposBefore;
	M_Int32 touchYposBefore;
	
	M_Int32 pos;
	M_Int32 posGab;
	
	M_Int32 w;
	M_Int32 h;
	
	M_Int32 endPos;
	
	M_Int32 speed;
} XDRAGSCROLL;

//***********************************************************************



#define POPUPYES		0		
#define POPUPNO			1		
#define POPUPTEXTMAX	512




typedef struct
{
	M_Int32 state;
	M_Int32 selectNum;
	M_Int32 anyCnt;
	
	M_Int32 msgType;		
	M_Int32 btnType;		
	M_Int32 textLine;		
	M_Int32 select;			
	M_Int32 yes;			
	M_Int32 no;
	M_Char strTitle[POPUPTEXTMAX];
	M_Char strText[POPUPTEXTMAX];
	
	int totalLine;
	M_Char strTextLine[10][128];
	
	M_Int32 num;			
	
	int speakingNpcNum;
    int fontGab;
	
} XPOPUP;
extern XPOPUP xPopup;




#define BTN_OK_CONFIRM			0	
#define BTN_CLR_CLEAR			1	
#define BTN_YESNO				2	
#define BTN_LINKNO				3
#define BTN_OK_LINK			4







//*********게임중 메뉴***********
#define	CLR_STATE_IN		0
#define	CLR_STATE_OUT		1
#define	CLR_STATE_WAIT		2

typedef struct
{
	int state;
	int selectNum;
	int anyCnt;
} XCLR;
extern XCLR xClr;
//*************************************



//*********달력***********
typedef struct
{
	int nowYear;
	int nowMonth;
	int nowDay;
	int nowHour;
	int nowMinute;
	int nowSec;
	int nowTotalDay;
	M_Int64 nowTime;
	M_Int64 nowTimeMillisecond;
	
	int nowMilSec;
    
    long nowMilSec_Pre;
    
	
	int nowYear_Hacking;
	int nowMonth_Hacking;
	int nowDay_Hacking;
	int nowHour_Hacking;
	int nowMinute_Hacking;
	int nowSec_Hacking;
	
	M_Boolean isHackingCheck;
	M_Int64 hackingCheckTime;
	
		
	M_Int64 gameInfoCheckTime;
	
} XCALENDAR;
extern XCALENDAR xCalendar;
//*************************************
#define SCROLLMENUMAX			120



extern XIMG imgScrollMenu[SCROLLMENUMAX];	

extern XIMG imgPopupNpc[4];
extern XIMG imgPopupSub[10];
extern XIMG imgPopupNpcProfile[10];
extern XIMG imgPopupNpcProfileIcon[10];


#define DIALOG_TEXT_FILENAME	20	
#define DIALOG_TEXT_COL			20	
#define DIALOG_TEXT_ROW			512

#define DIALOG_VIEWLINE		3
//#define DIALOG_WIDTH		300

#define DIALOG_WIDTH		20000


#define DIALOG_KORWIDTH		14
#define DIALOG_ENGWIDTH		8

#define DIALOG_FADEIN		0
#define DIALOG_FADEOUT		1
#define DIALOG_PLAY			2
typedef struct
{
	M_Int32 state;
	M_Int32 anyCnt;
	
	M_Int32 isUiShow;


	M_Int32 x;
	M_Int32 y;
	M_Int32 ank;


	
	
	
	M_Int32 showFontCnt;	
	M_Int32 showFontLineCnt;
	M_Char strFile[DIALOG_TEXT_FILENAME];
	
	
	XIMG imgPlayer[2][4];

	M_Int32 whoAnyCnt;
	M_Int32 playerLeft;
	M_Int32 playerRight;
	
	M_Int32 playerLeftTemp;
	M_Int32 playerRightTemp;


	M_Int32 player;		
	M_Int32 face;		
	M_Int32 place;
	M_Int32 next;

	M_Int32 pageT;		
	M_Int32 pageC;		
	M_Int32 lineT;		
	M_Int32 lineV;		
	M_Int32 lineC;		
	M_Int32 lineF;		
	M_Char strText[DIALOG_TEXT_COL][DIALOG_TEXT_ROW];
	
	
	XTOUCH xTouchSkip;


} Xdialog;
extern Xdialog xDialog;
//**************************************************


#define POPUP_TEST_AFTERMAKE		0
#define POPUP_MONEYEMPTY			1
#define POPUP_BUILDMAXERR			2
#define POPUP_FASHIONBUYYESNO				6
#define POPUP_FAMEEMPTY						7
#define POPUP_INPUTINVENTORYERR				10
#define POPUP_FITTING_LAYEREDERR			11
#define POPUP_TIREDEMPTY					12
#define POPUP_ADDSELLTABLEERR				13

#define POPUP_SERVERCHECK					14
#define POPUP_SERVERERR						15
#define POPUP_APPSTOREUPGRADEYESNO			16
#define POPUP_RESUPGRADEYESNO				17

#define POPUP_LOGINERR					18
#define POPUP_LOGINERR2					19
#define POPUP_BLACKUSER					20
#define POPUP_IDMAKEERR					21
#define POPUP_RESDOWNYESNO				22
#define POPUP_PROFILEERR				23

#define POPUP_SHOP_PREMIUM_BUYYESNO		25

#define POPUP_CARQUESTOPEN				26
#define POPUP_CAR_BUYYESNO				27
#define POPUP_EXTENSION_BUYYESNO		28
#define POPUP_ORDER_SLOTFULL			29

#define POPUP_ORDER_5LIMIT				30
#define POPUP_ORDER_10LIMIT				31

#define POPUP_FRIEND_100LIMIT				32

#define POPUP_SOCIALPOINT_3LIMIT		33

#define POPUP_MAIL_DELYESNO				34

#define POPUP_QUEST_FASTCASHYESNO			36

#define POPUP_TUTO_LIMIT			37

#define POPUP_TEST_ALLTILE			38

#define POPUP_ORDER_OPENERR			39

#define POPUP_MODEL_SELLYESNO		40


#define POPUP_BESTDESIGNERCLOSE			42



#define POPUP_TAKEPART_ERR0				43
#define POPUP_TAKEPART_ERR1				44

#define POPUP_VOTEERR0				45

#define POPUP_MARKETINGMAX				46
#define POPUP_ORDER_1DAY1			47

#define POPUP_PRODUCTION_FLOORERR		48
#define POPUP_CASHEMPTY					49
#define POPUP_MODEL_SLOTMAX				50

#define POPUP_QUESTDELERR				51

#define POPUP_ORDER_OPENERR_CAR			52

#define POPUP_PAYMENTBUILDERR			54

#define POPUP_EXTENSION_BUYYESNO_TILE		55
#define POPUP_PRODUCTION_OPENYESNO			56

#define POPUP_LOCK_MAINQUEST			58

#define POPUP_ORDERQUESTDELERR			59
#define POPUP_SERVER_TIMEOVER			60


#define POPUP_LOGOUT					61


#define POPUP_CARORDER_FASTCASH			62

#define POPUP_MODELGUESTERR				63

#define POPUP_MODELUPGRADEFAIL			64
#define POPUP_RUNWAYSTARTERR			65

#define POPUP_MODELVOTEERR				66

#define POPUP_GUESTMODE					67


#define POPUP_UNREGISTEREDYESNO			68
#define POPUP_UNREGISTEREDOK			69


#define POPUP_LOGOUTYESNO				70

#define POPUP_GUESTLOGINYESNO			71
#define POPUP_USERTEXT					72



#define POPUP_EXTENSION_ERR				73

#define POPUP_MODELMAIN_DEL				74



#define POPUP_EXTENSIONWALL_BUYYESNO		76
#define POPUP_EXTENSIONWALL_EQUIPYESNO		77

#define POPUP_BUILD_PAYMENTERR				78


#define POPUP_MUSIC_BUYYESNO				79
#define POPUP_MUSIC_CHANGEYESNO				80


#define POPUP_KAKAOINVEITEYESNO				81

#define POPUP_HACKINGPACKAGE				82





#define POPUP_MODELMAIN_SLOTOPENGOLD		83
#define POPUP_MODELMAIN_SLOTOPENCASH		84

#define POPUP_SHOP_BUYYESNOCASH				85
#define POPUP_SHOP_BUYYESNOGOLD				86

#define POPUP_SHOP_GUESTLOGINEND			87


#define POPUP_LOGINERRRRRRRRR					88


#define POPUP_PRODUCTIONLINKFASHIONSHOWYESNO	89


#define POPUP_SHOP_REVIEWYESNO				90

#define POPUP_SALESHOPBUYYESNO				92
#define POPUP_ORDERDEL						93

#define POPUP_IDREMAKE					94
#define POPUP_KAKAOLOGINERR					95
#define POPUP_KAKAOLOGINERR22					96


#define POPUP_KAKAOCARSTORAGE					97
#define POPUP_KAKAOFRIENDMAP					98
#define POPUP_KAKAOORDERITEM					99

#define POPUP_G9_LINK							100


#define POPUP_MODELGIFTFASTCASHYESNO			101

#define POPUP_SHOP_PREPAYBUY				102


#define POPUP_SHOP_PACKAGEBUY				103

#define POPUP_SHOP_HOTDEALBUY				104


#define POPUP_FRIENDDEL				105

#define POPUP_RIVALSTOP             106


#define POPUP_SELLFAST             107
#define POPUP_PRODUCTIONFAST             108
#define POPUP_PRODUCTIONFAST2             109


#define POPUP_AMULETBUY             110

#define POPUP_AMULETPAGEBUY				111



#define POPUP_CLUBMAKE				112
#define POPUP_CLUBMAKEOK				113

#define POPUP_CLUBJOINOK				114

#define POPUP_CLUBMASTERYESNO           115
#define POPUP_CLUBFORCEOUTYESNO         116


#define POPUP_CLUBUNREGYESNO            117
#define POPUP_CLUBUNREGOK               118


#define POPUP_CLUBBOOKDEL               119


#define POPUP_FASHIONWEEKHAIRBUY        120
#define POPUP_FASHIONWEEKFACEBUY        121
#define POPUP_FASHIONWEEKFASHIONBUY     122

#define POPUP_CLUBSHOPITEMBUYCHECK           123
#define POPUP_CLUBSHOPITEMBUYOK              124
#define POPUP_CLUBSHOPTOLACKPOINT            125
#define POPUP_CLUBSHOPNOTMASTER              126
#define POPUP_CLUBSHOPLOWLV                  127
#define POPUP_CLUBITEMTOLACKAMOUNT           128
#define POPUP_CLUBGIFTNOTMASTER              129
#define POPUP_CLUBGIVEGIFTCHECK              130
#define POPUP_CLUBGIVEGIFTOK                 131
#define POPUP_PANGTIMESRESETCHECK            132
#define POPUP_PANGTIMESOK                    133
#define POPUP_PANGTIMESNOCLUB                134
#define POPUP_PANGTIMESMAXTIMESEXCEED        135
#define POPUP_CLUBDONATIONGOLDCHECK          136
#define POPUP_CLUBDONATIONGOLDOK             137
#define POPUP_CLUBDONATIONTOLEAKGOLD         138
#define POPUP_CLUBDONATIONTOLEAKGOLDCOUNT    139
#define POPUP_CLUBDONATIONCANDYCHECK         140
#define POPUP_CLUBDONATIONCANDYOK            141
#define POPUP_CLUBDONATIONTOLEAKCANDY        142
#define POPUP_CLUBDONATIONTOLEAKCANDYCOUNT   143
#define POPUP_CLUBICONBUYCHECK               144
#define POPUP_CLUBICONBUYOK                  145
#define POPUP_CLUBICONBUYNOMASTER            146
#define POPUP_CLUBICONBUYHAVEALREADYICON     147
#define POPUP_CLUBICONBUYTOLEAKPOINT         148
#define POPUP_CLUBICONBUYTOLEAKLV            149
#define POPUP_CLUBICONCHANGECHECK            150
#define POPUP_CLUBICONCHANGENOMASTER         151
#define POPUP_CLUBICONDONTHAVEICON           152
#define POPUP_CLUBNAMEMODIFYNOMASTER         153
#define POPUP_CLUBNAMEMODIFYOK               154

#define POPUP_INPUTINVENTORYFORMERERR1       155
#define POPUP_NOTFORMER                      156
#define POPUP_FORMERCANT                     157
#define POPUP_FORMERCANTTAKE                 158
#define POPUP_NONFORMER                      159
#define POPUP_INPUTINVENTORYFORMERERR2       160   

#define POPUP_AUTOPRODUCTSLEEP       161
#define POPUP_AUTOSELLSLEEP       162


//#define POPUP_TESTTEST        123













void setPopup(M_Int32 type, M_Int32 yes, M_Int32 no,int speakingNpc,M_Int32 setTemp);
void keyPopup(M_Int32 type,M_Int32 param1,M_Int32 param2);
void drawPopup(void);
void drawBtn(M_Int32 x,M_Int32 y,M_Int32 type);
void setPopupResult(void);
void dragScrollPrc(XDRAGSCROLL *dragScroll,M_Int32 type,M_Boolean isRolling);
void dragScrollKeyPrc(XDRAGSCROLL *dragScroll, M_Int32 type);
void setPopupStringLine(M_Char *pChar,M_Int32 w);


#endif


