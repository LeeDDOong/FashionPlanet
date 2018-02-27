#ifndef __MAINMENU_H__
#define __MAINMENU_H__


#define MAINMENU_STATE_VERCHECK			0
#define MAINMENU_STATE_INITFILEDOWN		1
#define MAINMENU_STATE_HACKINGCHECK		2

#define MAINMENU_STATE_RESCHECK			3
#define MAINMENU_STATE_IDMAKE			4
#define MAINMENU_STATE_LOGIN			5
#define MAINMENU_STATE_INITCHECK		6
#define MAINMENU_STATE_SERVERNOTICE		7


#define MAINMENU_STATE_PERMISSIONCHECK_NET		8
#define MAINMENU_STATE_PERMISSIONCHECK		9















typedef struct
{
	int state;
	int anyCnt;
	

	int initCnt;
	M_Boolean isInitNet;
	
	
	M_Int64 loadTextCnt;
	M_Int64 loadTipCnt;

	int textType;
	int totalLoadingImg;
	int loadingImgSlot[16];
	
	
} XMAINMENU;
extern XMAINMENU xMainMenu;








#define RESVERMAX			32
#define RESFILELISTMAX		512

#define RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_START		1
#define RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_ING			2

#define RESCHECK_STATE_FILESCRIPT_DOWNLOAD_POPUP		0
#define RESCHECK_STATE_FILESCRIPT_DOWNLOAD_START		3
#define RESCHECK_STATE_FILESCRIPT_DOWNLOAD_ING			4
#define RESCHECK_STATE_FILE_DOWNLOAD_START				5
#define RESCHECK_STATE_FILE_DOWNLOAD_ING				6

#define RESCHECK_STATE_FILE_DOWNLOAD_UNZIP				7



typedef struct
{
	int resInit;		//다운카운터 최초에는 경고 팝업띄우기 위해

	int state;
	int anyCnt;
	
	int totalVer;
	char strUrlDir[RESVERMAX][128];
	char strUrl[RESVERMAX][128];
	
	M_Boolean isZip[RESVERMAX];

	
	
	int totalFileList;
	int nowFileList;
	char strFileList[RESFILELISTMAX][64];
	
	
	
} XRESCHECK;
extern XRESCHECK xResCheck;





typedef struct
{
	int state;
} XETCDOWNLOAD;
extern XETCDOWNLOAD xEtcDownLoad;


#define IDMAKE_STATE_CLAUSE				0
#define IDMAKE_STATE_LOGINKAKAO			1
#define IDMAKE_STATE_LOGINKAKAOING		2


#define IDMAKE_STATE_IDMAKE			3

#define IDMAKE_STATE_STAMP			4

////////////////////////////////////////////
//닉네임 입력중 추가 KBY 2018.2.26
#define IDMAKE_STATE_INPUTNAME           5



#define IDMAKEERR_TYPE_DONT			0//문제없음
#define IDMAKEERR_TYPE_EMAILERR		1//이메일형식에러
#define IDMAKEERR_TYPE_EMAILERR2	2//이메일중복

#define IDMAKEERR_TYPE_PASSERR		3//비밀번호틀림
#define IDMAKEERR_TYPE_PASSERR2		4//비밀번호두개가 다름

#define IDMAKEERR_TYPE_NICKNAMEERR		5//너무짧은
#define IDMAKEERR_TYPE_NICKNAMEERR2		6//중복

#define IDMAKEERR_TYPE_NICKNAMEERR3		7//특수문자





#define AREAMAX			16
#define AGEMAX			100

#define AGESTART		2017



//회원 가입 구조체 수정 : 2018.2.23
typedef struct
{
	int state;
	int anyCnt;
	
	char strNickName[64];
    char strUID[64];
	
	XTOUCH xTouchLoginBtn;
	XTOUCH xTouchLoginIdMakeBtn;
	XTOUCH xTouchEmail;
	XTOUCH xTouchPass[2];
	XTOUCH xTouchNickName;
	
	XTOUCH xTouchSex[2];
    XTOUCH xTouchHair[3];
    XTOUCH xTouchFace[3];
    XTOUCH xTouchArrow[2];
    XTOUCH xTouchStar[12];
    
//	XTOUCH xTouchAge;
//	XTOUCH xTouchArea;
	
	
	M_Boolean isSelectArea;
	M_Boolean isSelectAge;
			
	
	XDRAGSCROLL xDragScrollArea;
	XDRAGSCROLL xDragScrollAge;



	
	
	int emailErr;
	int passErr;
	int nickNameErr;
	int ageErr;
	
	int sex;

    int selectHair;
    int selectFace;
    int selectStar;
	
    int pos;
    
    bool isTouchMan;
    bool isTouchWoman;
    bool isTouchLeftArrow;
    bool isTouchRightArrow;
    bool isTouchOk;
    
    XTOUCH xTouchClauseLink[2];

	
	XTOUCH xTouchClauseBtn[2];
	M_Boolean isClause[2];

	

} XIDMAKE;
extern XIDMAKE xIdMake;
///////////////////////////////////////////
//회원가입 KBY 2018.2.26 수정
extern XIMG imgIdMake[30];
void idmakeFreeLoad_FP(bool isLoad);
///////////////////////////////////////////
extern XIMG imgLoadingBg;
extern XIMG imgYoung;
extern XIMG imgTitleBG;


extern XIMG imgPermissions;






void initMainMenu(void);
void paintMainMenu(void);
void MainMenuCletEvent(int type, int param1, int param2,int touchId);
void drawIdMake(void);
M_Boolean checkEmail(const char*strText);
M_Boolean checkAge(const char*strText);
void getSprintfArea(char*strText,int code);
void getSprintfAge(char*strText,int code);
int getScrollW(XDRAGSCROLL *xDragScroll,int fullWidth,int imgWidth);
void drawServerNotice(void);
void dataDownLoad(const char*strUrl,const char*strFileName,int type);
void gameExit(void);
void drawLodingText(void);
void googleLogin();
void startVerCheck();
#endif
