//
//  Pang.h
//  FridayNight
//
//
//

#ifndef FridayNight_Pang_h
#define FridayNight_Pang_h



#define PANG_STATE_IN			0	//진입연출
#define PANG_STATE_READY		1	//3,2,1,GO
#define PANG_STATE_PLAY			2	//플레이
#define PANG_STATE_EFFECT		3	//3개이상 터트렸을때 연출
#define PANG_STATE_SORT			4	//3개이상 연결된 오브젝이 없을떈 재배치
#define PANG_STATE_PAUSE		5	//일시정지
#define PANG_STATE_GORESULT		6	//결과화면으로 이동및 연출
#define PANG_STATE_RESULT		7	//결과화면






#define PANG_WIDTH				7
#define PANG_HEIGHT				6
#define PANGOBJ_MAX				42

#define PANG_OBJSTATE_DONT		-1
#define PANG_OBJSTATE_PLAY		0

#define PANG_OBJTYPE_DONT		-1
#define PANG_OBJTYPE_GOLD		0
#define PANG_OBJTYPE_CLOVER		1
#define PANG_OBJTYPE_JUWEL		2
#define PANG_OBJTYPE_MUSIC		3
#define PANG_OBJTYPE_HEART		4
#define PANGOBJ_TYPE_MAX		5

#define PANG_DIR_DONT			-1
#define PANG_DIR_12				0
#define PANG_DIR_2				1
#define PANG_DIR_4				2
#define PANG_DIR_6				3
#define PANG_DIR_8				4
#define PANG_DIR_10				5

#define PANG_CHARGESTATE_DONT		-1
#define PANG_CHARGESTATE_MAKE		0
#define PANG_CHARGESTATE_MOVE		1
#define PANG_CHARGESTATE_FINISH		2

#define PANG_EFFECT_MIN				3	//3개 이상 연결시 터트리기




typedef struct
{
	int x;											//가로줄 넘버
	int y;											//세로줄 넘버
	int dir;										//연결선
	int type;										//오브젝트 종류(골드, 클로버, 보석, 뮤직)
	int state;										//오브젝트 상태(빈공간, 플레이)
	int chargeState;								//채우기 상태
	int effCnt;										//연출 카운트
}XPANGOBJ;

typedef struct
{
    int inState;
	int state;										//게임 상태(DONT, IN, PLAY, EFFECT, CHARGE, PAUSE, RESULT, GORESULT, OUT)
    int anyCnt;									
	int chargeState[PANG_WIDTH];					//오브젝트 채우기 상태
	int beforeState;								//댄스팡 게임전 월드맵 상태
    
	
   
    SECURITY totalScore;
    SECURITY score[5];										//획득점수
    SECURITY buffScore[5];										//획득점수
    SECURITY comboScore[5];									//콤보점수



    
    int totalCombo;									//최대콤보
	int comboCnt;									//콤보카운트

	int prcTime;									//시간 저장용
	int timeMax;									//게임시간
	SECURITY time;										//현재시간
    
    
    int PANG_TIME_MAX;
    int DEFAULTSCORE;
    
    
    
	
	int bgX;										//댄스팡 배경 x좌표
	int bgY;										//댄스팡 배경 y좌표
	
	int selectCnt;									//오브젝트 선택 갯수
	
	bool isSelect;									//오브젝트 터치시

	
	XPANGOBJ selectOBJ[PANGOBJ_MAX];				//선택된 오브젝트 위치ID
	XPANGOBJ currentSelectObj;						//현재 선택된 오브젝트 위치
	
	XPANGOBJ xObjDir[PANG_WIDTH][PANG_HEIGHT];		//오브젝트 위치 저장용
	XPANGOBJ xObjSub[PANG_WIDTH];					//오브젝트 기본 예비(오브젝트 생성용)
	XPANGOBJ xObj[PANG_WIDTH][PANG_HEIGHT];			//오브젝트
	XTOUCH xTouchObj[PANG_WIDTH][PANG_HEIGHT];		//오브젝트 터치
    

    
    
  
    
    
    XTOUCH xTouchExit;

    
    bool isNet_pangResult;
    
    
    
    XTOUCH xTouchPause;
    XTOUCH xTouchPauseOk;
    
    
    
    int nowFrameResult;
    int nowFrameResultFriend[10];
    
    
    int checkTouchX[2];
    int checkTouchY[2];
    
    int totalCheckTouchPang;
    int checkTouchXPang[32];
    int checkTouchYPang[32];
    
    
    long comboTime;
    
    

    
    
    
    
    
    
    int totalCheckPangObj;
    int checkPangObjX[32];
    int checkPangObjY[32];
    
    
    //////////20160617 오토팡
    bool isAutoPang;
    int autoPangSpeed;
    XTOUCH xTouchAutoPang;
    //////////20160617 오토팡
    
    bool isAutoKey;
    
    
    
    
    int effCnt[10];
    
    
    
}XPANG;
extern XPANG xPang;




#define PANGEFFMAX     12
typedef struct
{
    bool isPlay[PANGEFFMAX];
    int waitCnt[PANGEFFMAX];
    int anyCnt[PANGEFFMAX];
    int x[PANGEFFMAX];
    int y[PANGEFFMAX];
    int objType[PANGEFFMAX];
    int rotSpeed[PANGEFFMAX];
    int rot[PANGEFFMAX];
}XPANGEFF;
extern XPANGEFF xPangEff;


#define PANGCOMBOMAX     20
typedef struct
{
    bool isPlay[PANGCOMBOMAX];
    int anyCnt[PANGCOMBOMAX];
    int x[PANGCOMBOMAX];
    int y[PANGCOMBOMAX];
    int comboNum[PANGCOMBOMAX];
}XPANGCOMBO;
extern XPANGCOMBO xPangCombo;




#define PANGSCOREEFFMAX         20
typedef struct
{
    bool isPlay;
    int x;
    int y;
    int num;
    int type;
    int anyCnt;
}XPANGSCOREEFF;
extern XPANGSCOREEFF xPangScoreEff[PANGSCOREEFFMAX];



#define PANGGEARMAX         14
typedef struct
{
    int type;
    int x;
    int y;
    int speed;
    int rot;
}XPANGGEAR;
extern XPANGGEAR xPangGear[PANGGEARMAX];










//////////20160617 오토팡
extern XIMG imgPangAuto[5];
//////////20160617 오토팡

extern XIMG imgPang_BG[5];					//배경
extern XIMG imgPangPause[5];					//pause

extern XIMG imgPangUi[10];

extern XIMG imgPangNum[5];
extern XIMG imgPangObj;
extern XIMG imgPangObjSelect;
extern XIMG imgPangStart[3];
extern XIMG imgPangTimeover;
extern XIMG imgPangCombo[5];
extern XIMG imgPangDir[15];
extern XIMG imgPangGear[10];







void initPang();						//댄스팡 초기화
void loadPangImg();						//댄스팡 이미지 로드
void freePangImg();						//댄스팡 이미지 해제
void delPangObj(int wNum, int hNum);	//댄스팡 삭제
void keyPang(int type, int param1, int param2);
void prcPang();
void drawPang();
void chargePang();						//오브젝트 채우기
void makePang(int num);					//오브젝스 한개 생성
bool checkBlankPang();					//빈칸 검사
bool checkPang();						//할것이 있는지 검사
void sortPang();						//오브젝 재배치
bool isPangObjTouch();					//오브젝트 터치
bool isPangObjCheck(int touchX, int touchY, int x, int y, int rad);
void addPangScoreCombo(int type,int score);
void addPangScore(int type,int score);			//점수추가

void setPangScore();					//점수계산공식
void setPangState(int state);			//상태값 설정
double getPangObjLength(int x1, int y1, int x2, int y2);
void makePangEff(int x,int y,int objType);
void drawPangEff(void);
void makePangCombo(int x,int y,int comboNum);
void drawPangCombo();

void drawPangStart();
void drawPangTimeOver();
void drawPangResult();
void drawPangScoreEff();
void setPangScoreEff(int x,int y,int type,int num);
void drawPangHeartEff();
void drawPangGear();
void drawPangUi();
void addPangScoreBuff(int type,int score);
#endif
