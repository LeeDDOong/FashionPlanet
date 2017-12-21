//
//  Pang_Solo.h
//  RuleTheStyle
//
//  Created by kby5686 on 2017. 10. 30..
//
//

#ifndef Pang_Solo_h
#define Pang_Solo_h

#define PANG_SOLO_STATE_IN			0	//진입연출
#define PANG_SOLO_STATE_READY		1	//3,2,1,GO
#define PANG_SOLO_STATE_PLAY			2	//플레이
#define PANG_SOLO_STATE_EFFECT		3	//3개이상 터트렸을때 연출
#define PANG_SOLO_STATE_SORT			4	//3개이상 연결된 오브젝이 없을떈 재배치
#define PANG_SOLO_STATE_PAUSE		5	//일시정지
#define PANG_SOLO_STATE_GORESULT		6	//결과화면으로 이동및 연출
#define PANG_SOLO_STATE_RESULT		7	//결과화면
#define PANG_SOLO_STATE_CHANGERANK      8   //순위변화





#define PANG_SOLO_WIDTH				7
#define PANG_SOLO_HEIGHT				6
#define PANG_SOLO_OBJ_MAX				42

#define PANG_SOLO_OBJSTATE_DONT		-1
#define PANG_SOLO_OBJSTATE_PLAY		0

#define PANG_SOLO_OBJTYPE_DONT		-1
#define PANG_SOLO_OBJTYPE_GOLD		0
#define PANG_SOLO_OBJTYPE_CLOVER		1
#define PANG_SOLO_OBJTYPE_JUWEL		2
#define PANG_SOLO_OBJTYPE_MUSIC		3
#define PANG_SOLO_OBJTYPE_HEART		4
#define PANG_SOLO_OBJ_TYPE_MAX		5

#define PANG_SOLO_DIR_DONT			-1
#define PANG_SOLO_DIR_12				0
#define PANG_SOLO_DIR_2				1
#define PANG_SOLO_DIR_4				2
#define PANG_SOLO_DIR_6				3
#define PANG_SOLO_DIR_8				4
#define PANG_SOLO_DIR_10				5

#define PANG_SOLO_CHARGESTATE_DONT		-1
#define PANG_SOLO_CHARGESTATE_MAKE		0
#define PANG_SOLO_CHARGESTATE_MOVE		1
#define PANG_SOLO_CHARGESTATE_FINISH		2

#define PANG_SOLO_EFFECT_MIN				3	//3개 이상 연결시 터트리기




typedef struct
{
    int x;											//가로줄 넘버
    int y;											//세로줄 넘버
    int dir;										//연결선
    int type;										//오브젝트 종류(골드, 클로버, 보석, 뮤직)
    int state;										//오브젝트 상태(빈공간, 플레이)
    int chargeState;								//채우기 상태
    int effCnt;										//연출 카운트
}XPANG_SOLO_OBJ;

typedef struct
{
    int inState;
    int state;										//게임 상태(DONT, IN, PLAY, EFFECT, CHARGE, PAUSE, RESULT, GORESULT, OUT)
    int anyCnt;
    int chargeState[PANG_SOLO_WIDTH];					//오브젝트 채우기 상태
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
    
    
    XPANG_SOLO_OBJ selectOBJ[PANG_SOLO_OBJ_MAX];				//선택된 오브젝트 위치ID
    XPANG_SOLO_OBJ currentSelectObj;						//현재 선택된 오브젝트 위치
    
    XPANG_SOLO_OBJ xObjDir[PANG_SOLO_WIDTH][PANG_SOLO_HEIGHT];		//오브젝트 위치 저장용
    XPANG_SOLO_OBJ xObjSub[PANG_SOLO_WIDTH];					//오브젝트 기본 예비(오브젝트 생성용)
    XPANG_SOLO_OBJ xObj[PANG_SOLO_WIDTH][PANG_SOLO_HEIGHT];			//오브젝트
    XTOUCH xTouchObj[PANG_SOLO_WIDTH][PANG_SOLO_HEIGHT];		//오브젝트 터치
    
    
    
    
    
    
    
    XTOUCH xTouchExit;
    
    
    bool isNet_pangResult;
    
    
    
    XTOUCH xTouchPause;
    XTOUCH xTouchPauseExit;
    XTOUCH xTouchPauseGoLobby;
    XTOUCH xTouchReStart;
    
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
    
    
    
}XPANG_SOLO;
extern XPANG_SOLO xPang_SOLO;




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
}XPANG_SOLO_EFF;
extern XPANG_SOLO_EFF xPang_SOLO_Eff;


#define PANGCOMBOMAX     20
typedef struct
{
    bool isPlay[PANGCOMBOMAX];
    int anyCnt[PANGCOMBOMAX];
    int x[PANGCOMBOMAX];
    int y[PANGCOMBOMAX];
    int comboNum[PANGCOMBOMAX];
}XPANG_SOLO_COMBO;
extern XPANG_SOLO_COMBO xPang_SOLO_Combo;




#define PANGSCOREEFFMAX         20
typedef struct
{
    bool isPlay;
    int x;
    int y;
    int num;
    int type;
    int anyCnt;
}XPANG_SOLO_SCOREEFF;
extern XPANG_SOLO_SCOREEFF xPang_SOLO_ScoreEff[PANGSCOREEFFMAX];



#define PANGGEARMAX         14
typedef struct
{
    int type;
    int x;
    int y;
    int speed;
    int rot;
}XPANG_SOLO_GEAR;
extern XPANG_SOLO_GEAR xPang_SOLO_Gear[PANGGEARMAX];










//////////20160617 오토팡
extern XIMG imgPang_SOLO_Auto[5];
//////////20160617 오토팡

extern XIMG imgPang_SOLO_BG[5];					//배경
extern XIMG imgPang_SOLO_Pause[5];					//pause

extern XIMG imgPang_SOLO_Ui[20];

extern XIMG imgPang_SOLO_Num[5];
extern XIMG imgPang_SOLO_Obj;
extern XIMG imgPang_SOLO_ObjSelect;
extern XIMG imgPang_SOLO_Start[3];
extern XIMG imgPang_SOLO_Timeover;
extern XIMG imgPang_SOLO_Combo[5];
extern XIMG imgPang_SOLO_Dir[15];
extern XIMG imgPang_SOLO_Gear[10];







void initPang_Solo();						//댄스팡 초기화
void loadPang_SoloImg();						//댄스팡 이미지 로드
void freePang_SoloImg();						//댄스팡 이미지 해제
void delPang_SoloObj(int wNum, int hNum);	//댄스팡 삭제
void keyPang_Solo(int type, int param1, int param2);
void prcPang_Solo();
void drawPang_Solo();
void chargePang_Solo();						//오브젝트 채우기
void makePang_Solo(int num);					//오브젝스 한개 생성
bool checkBlankPang_Solo();					//빈칸 검사
bool checkPang_Solo();						//할것이 있는지 검사
void sortPang_Solo();						//오브젝 재배치
bool isPang_SoloObjTouch();					//오브젝트 터치
bool isPang_SoloObjCheck(int touchX, int touchY, int x, int y, int rad);
void addPang_SoloScoreCombo(int type,int score);
void addPang_SoloScore(int type,int score);			//점수추가

void setPang_SoloScore();					//점수계산공식
void setPang_SoloState(int state);			//상태값 설정
double getPang_SoloObjLength(int x1, int y1, int x2, int y2);
void makePang_SoloEff(int x,int y,int objType);
void drawPang_SoloEff(void);
void makePang_SoloCombo(int x,int y,int comboNum);
void drawPang_SoloCombo();

int getPangBuffScore(int modelKey);
int getPangBuffTime(int modelKey);
int getPangBuffScore_LuluPang(int modelKey);
int getPangBuffTime_LuluPang(int modelKey);
float getPangBuffmagnification_Lulupang(int modelKey);

void drawPang_SoloStart();
void drawPang_SoloTimeOver();
void drawPang_SoloResult();
void drawPang_SoloScoreEff();
void setPang_SoloScoreEff(int x,int y,int type,int num);
void drawPang_SoloHeartEff();
void drawPang_SoloGear();
void drawPang_SoloUi();
void addPang_SoloScoreBuff(int type,int score);
void drawRankChange_luluPang();

#endif /* Pang_Solo_h */
