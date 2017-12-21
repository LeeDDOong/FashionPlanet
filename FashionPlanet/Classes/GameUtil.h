#ifndef GAMEUTIL_
#define GAMEUTIL_



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <curl/include/ios/curl/curl.h>
#include "platform/ios/iosUtil.h"
using namespace CocosIosUtil;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "curl.h"

#include <curl/include/android/curl/curl.h>
#endif



#define SETCOLOR(r,g,b)			MC_grpSetContext(&xConf.gc, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(r,g,b))
//#define SWAP(a, b) { (a)^=(b)^=(a)^=(b); }
#define SWAP(a, b) { subTemp[33]=a;a=b;b=subTemp[33];}

#define MEMSET(p)				memset((p), 0, sizeof(p))
#define ALPHA_MAX		255			//���ĸƽ���

#define ChannelBlend_Subtract(B,L)   ((M_Uint8)((B + L < 255) ? 0:(B + L - 255)))


#define JAEGOB(x)	(x)*(x)




//Ŭ����
#define CLIPX					0
#define CLIPY					1
#define CLIPW					2
#define CLIPH					3
//Ű��
#define POS_UP					0
#define POS_DOWN				1
#define POS_LEFT				2
#define POS_RIGHT				3

//ȭ��ǥ�׸���
#define ARROW_UP		0
#define ARROW_DOWN		1
#define ARROW_LEFT		2
#define ARROW_RIGHT		3

//��Ŀ
#define TL						0
#define TR						1
#define TH						2
#define VH						3
#define BH						4
#define BL						5
#define BR						6
#define VL						7
#define VR						8


#define DATADOWNLOAD_TYPE_SDCARD        0
#define DATADOWNLOAD_TYPE_BUFF          1


#define DOWNLOADER_STATE_DONT			0
#define DOWNLOADER_STATE_ING			1
#define DOWNLOADER_STATE_ERR			2
#define DOWNLOADER_STATE_SUCCESS		3



extern cocos2d::ClippingNode* clip;
extern cocos2d::DrawNode* shape;

extern char *openGalleryBuf;


extern M_Int32 rmask;		
extern M_Int32 gmask;		
extern M_Int32 bmask;		

extern XIMG imgRect;





extern M_Uint32 ranDomN;		//������ ����
//***********��ũ�ѱ���ü**************
#define SCROLL_TYPE_0		0		//������
#define SCROLL_TYPE_1		1		//������
typedef struct
{
	M_Int32 cSelect;	//���缱�õȰ�
	M_Int32 vLine;		//������ ���μ�
	M_Int32 tLine;		//�Ѷ��μ�
	M_Int32 cLine;		//�������
	M_Int32 tPage;		//��Ż������
	M_Int32 cPage;		//����������
} Xscroll;
//*************************************
extern Xscroll xScroll;
extern M_Int32 ScrollCnt;


//***********�Ի簢 �ݻ簢 ����ü**************
typedef struct
{
	float pos[2];		//������ġ ��ȯ��
	float clip[4];	//����
	
} XRADIUS;
extern XRADIUS xRadius;
//*************************************



extern M_Boolean isCollLineUp;
extern M_Boolean isCollLineDown;
extern M_Boolean isCollLineLeft;
extern M_Boolean isCollLineRight;

typedef struct
{
	int x;
	int y;
} XLINE;






void initContext(void);
void setState(M_Int8 nexts, M_Int8 plays,M_Int8 subplays);
void loadImg(const char* strFileName, XIMG* pImg);
void freeImg(XIMG* pImg);
void gSetColor(M_Int32 r, M_Int32 g, M_Int32 b);

void setAlpha(M_Int32 alpha);

void gSetClip(bool isClip,M_Int32 x, M_Int32 y, M_Int32 w, M_Int32 h);

void fillArc(M_Int32 x, M_Int32 y, M_Int32 w, M_Int32 h);
void fillRect(M_Int32 x, M_Int32 y, M_Int32 w, M_Int32 h);


void drawImage(XIMG* img,float x,float y,float imgX,float imgY,float imgW,float imgH,int ank);

void naverPlug(int type);

M_Int32 getByteToInt(char data[], M_Int32 idx);
M_Int16 getByteToInt16(M_Byte data[], M_Int32 idx);
void getIntToByte(M_Int32 num32, M_Byte data[], M_Int32 idx);
void getInt16ToByte(M_Int16 num16, M_Byte data[], M_Int32 idx);
M_Int32 getByteToIntRe(char data[], M_Int32 idx);
M_Int16 getByteToInt16Re(char data[], M_Int32 idx);
bool gameLoad(M_Int8 slot);
void drawNum(XIMG* img,M_Int32 x, M_Int32 y, M_Int32 value, M_Int32 gab,M_Int32 ank);
void gameSave(M_Int32 slot);
M_Int32 getReflexRadius(M_Int32 dir,M_Int32 inRad);
void getRadiusPos(float x,float y,float speed,float rad);
float getArcTan(float x,float y,float tx,float ty);
M_Int32 ranDom(M_Int32 startNum,M_Int32 endNum);
M_Boolean isChungCheck(M_Int32 x,M_Int32 y,M_Int32 w,M_Int32 h,M_Int32 tx,M_Int32 ty,M_Int32 tw,M_Int32 th);
float getRadiusSpeed(float x,float y,float beforX,float beforY,float rad);
float getRoot(float num);
void getInt16ToByteRe(M_Int16 num16, M_Byte data[], M_Int32 idx);
void getIntToByteRe(M_Int32 num32, M_Byte data[], M_Int32 idx);
M_Boolean checkArc(float x1,float y1,float r1,float x2,float y2,float r2);
void getTime(void);
double Newton_Raphson(double n, double r);
void drawNumComma(XIMG* img,M_Int32 x, M_Int32 y, M_Int32 value, M_Int32 gab,M_Int32 ank,XIMG* imgComma,int commagab);
void drawNumDollar(XIMG* img,M_Int32 x, M_Int32 y, M_Int32 value, M_Int32 gab,M_Int32 ank,XIMG* imgComma,int commagab);
void loadImgCash(const char* strFileName, XIMG* img);
bool checkCollLineLine(XLINE v1, XLINE v2, XLINE v3, XLINE v4);
void drawArrow(XIMG *img,M_Int32 x,M_Int32 y,M_Int32 type);
void writeNativeFileData(char *fileName, char *fileBuf, long fileSize);
void loadNativeFileData(char *fileName, char *fileBuf, long *fileSize);
void writeSdFileData(char *fileName, char *fileBuf, long fileSize);
void loadSdFileData(char *fileName, char *fileBuf, long *fileSize);
void loadFileData(char *fileName, char *fileBuf, long *fileSize);


void urlFileDownLoad(char *fileName, char *url);
void startWebView(char *strUrl);
void nativePopupExit(char *strText);

void sendPush(int num, int sec,const char *strText,const char *strSound);
void canclePush(int num);
void googleInApp(char *strProductId);
void unZip(const char *strFileName);
void openGallery(char *buf, int userNum);
void googleSignIn();
void googleSignOut();
void nativeOnOffPush(int state);
void nativeExitYesNo();
void getDeviceInfo();
void oneStoreInApp(char *strProductId);
void naverGameUserId(char *strId);


void naverGameUserId();

void checkBluetoothPermission();
void startBluetoothPermission();


#endif


