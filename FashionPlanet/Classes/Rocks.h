#ifndef __ROCKS__
#define __ROCKS__

typedef struct
{
	char strTemp[256];
	
} XROCKS;
extern XROCKS xRocks;

void setFiveRocksUser(char *strId,int lv,int friendsNum,char *strVer,char *strSex,char *strArea,char *strAge);
void setFiveRocksPurchase(char*strName, int price);
void setFiveRocksCustom(char*strCategory,char*strName,char*strPar1,char*strPar2,int value);

#endif


