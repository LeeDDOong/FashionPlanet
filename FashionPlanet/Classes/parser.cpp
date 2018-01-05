#include "Global.h"

int dataVer;
char bufData[15240000];
long bufDataSize;

XSPRIT xSpritNpc[SPRITNPCMAX][2];		//[액팅번호][앞뒤구분]
XSPRIT xSpritDrawSub;
XSPRIT xSpritShowWindow[2];
char strFileNameTemp[64];
int sortSlot[2][20];

///////////////////////엑셀 파싱//////////////////////////
void loadData(const char* strFileName,M_Boolean isSdCard)
{
	int resSize = 0;
	bufDataSize = 0;
    
    if(isSdCard == FALSE)
        loadFileData((char*)strFileName, bufData, &bufDataSize);
    else
        loadNativeFileData((char*)strFileName, bufData, &bufDataSize);
}

void loadExcelParserByte(int type)
{
	int i;
	int colsNow;
	int rowsNow;
	int colsMax = 0;
	int rowsMax = 0;
	int index;
	char isParsingStart;
		
	int size1, size2, size3;
	size1 = 1024;
	size2 = 52;
	size3 = 256;
	
	int j;
	char ***bData = (char***)malloc(sizeof(char***)*size1);
	
	for( i = 0; i < size1; i++)
	{
		bData[i] = (char**)malloc(sizeof(char**)*size2);
		
		for( j = 0; j < size2; j++)
		{
			bData[i][j] = (char*)malloc(sizeof(char)*size3);
			memset(bData[i][j], 0, size3);
		}
	}
	
		
	index = 0;
	colsNow = 0;
	rowsNow = 0;
	isParsingStart = FALSE;
	
	M_Byte checkSum0 = bufData[bufDataSize-1];
	M_Byte checkSum1 = 0;
		
	
    /*
	if(bufDataSize != 0)
	{
		for(int i=0;i<bufDataSize-1;i++)
		{
			checkSum1 += bufData[i];
		}
				
		
		if(checkSum0 != checkSum1)
		{
			printf("hhh>>%d\n",type);
			setHackingPopup(2);
			return;
		}
	}
    */

	bufDataSize--;
	
	for(int i=0;i<bufDataSize;i++)
	{
		if(bufData[i] == '/')		//항목변화
		{
			if(colsMax == 0)
			{
				colsMax = atoi(bData[0][0]);
			}
			else if(rowsMax == 0)
			{
				rowsMax = atoi(bData[0][0]);
			}
			else
			{
				rowsNow++;
			}
			index = 0;
		}
		else if(bufData[i] == '*')	//줄변화
		{
			i++;
			if(isParsingStart == FALSE)
				isParsingStart = TRUE;
				else
					colsNow++;
			rowsNow = 0;
		}
		else
		{
			bData[colsNow][rowsNow][index++] = bufData[i];
		}
	}
			
	switch(type)
	{
	case EXCEL_PS_THEME:
		xInterior.totalNumThema = colsMax;
						
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			sprintf(xInterior.strThemaName[i-1], "%s",bData[i][1]);
						
			xInterior.themaCode[i-1] = atoi(bData[i][2]);
			xInterior.totalSlotThema[i-1] = 0;
			
			for(int f=0;f<xInterior.totalNum;f++)
			{
				for(int z=0;z<xInterior.totalSlot[f];z++)
				{
					for(int t=0;t<xInterior.xSlot[f][z].totalTeam;t++)
					{
						setMapData(xInterior.xSlot[f][z].codeTeam[t]);
						
						if(xObj.xObjData[xMap.type][xMap.listNum].thema == xInterior.themaCode[i-1])
						{
							xInterior.xSlotThema[i-1][xInterior.totalSlotThema[i-1]].totalTeam = 1;
							xInterior.xSlotThema[i-1][xInterior.totalSlotThema[i-1]].codeTeam[0] = xInterior.xSlot[f][z].codeTeam[t];
							
							xInterior.xSlotThema[i-1][xInterior.totalSlotThema[i-1]].isNew = xInterior.xSlot[f][z].isNew;
							xInterior.xSlotThema[i-1][xInterior.totalSlotThema[i-1]].isHot = xInterior.xSlot[f][z].isHot;
							xInterior.xSlotThema[i-1][xInterior.totalSlotThema[i-1]].isEvent = xInterior.xSlot[f][z].isEvent;
							xInterior.xSlotThema[i-1][xInterior.totalSlotThema[i-1]].sale = xInterior.xSlot[f][z].sale;							
							xInterior.totalSlotThema[i-1]++;
						}
					}
				}
			}
		}
		break;
	case EXCEL_PS_INTERIOR_DATA:
		colsMax +=1;
        
		for(i=1;i<colsMax;i++)
		{
			int interiorType = atoi(bData[i][2])/1000;
			int interiorListNum = atoi(bData[i][2])%1000;
            
			
			sprintf(xObj.xObjData[interiorType][interiorListNum].strName, "%s",bData[i][1]);
			xObj.xObjData[interiorType][interiorListNum].lv = atoi(bData[i][3]);
			xObj.xObjData[interiorType][interiorListNum].thema = atoi(bData[i][4]);
			xObj.xObjData[interiorType][interiorListNum].slot = atoi(bData[i][6]);
			xObj.xObjData[interiorType][interiorListNum].fame = atoi(bData[i][9]);
			initSecurity(&xObj.xObjData[interiorType][interiorListNum].price, atoi(bData[i][10]));
			xObj.xObjData[interiorType][interiorListNum].priceType = atoi(bData[i][11]);
			xObj.xObjData[interiorType][interiorListNum].productionType = atoi(bData[i][12]);
            xObj.xObjData[interiorType][interiorListNum].special=atoi(bData[i][13]);
            xObj.xObjData[interiorType][interiorListNum].specialType=atoi(bData[i][14]);
            xObj.xObjData[interiorType][interiorListNum].specialCount=atoi(bData[i][15]);
            xObj.xObjData[interiorType][interiorListNum].specialTime=atoi(bData[i][16]);
            
            
			switch(xObj.xObjData[interiorType][interiorListNum].productionType)
			{
			case 2:
				xObj.xObjData[interiorType][interiorListNum].isChair = TRUE;
				break;
			case 3:
				xObj.xObjData[interiorType][interiorListNum].isRotLock = TRUE;
				break;
			}
		}
			
		break;
	case EXCEL_PS_INTERIOR_LIST:
		xInterior.totalNum = 12;
					
		for(int t=0;t<xInterior.totalNum;t++)
		{
			xInterior.totalSlot[t] = 0;
		}
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			int interiorType = atoi(bData[i][1]);
				
			//(팀명,아이템코드0,아이템코드1,아이템코드2,아이템코드3,new표시,소캣속성1,소캣속성2,소캣속성3)
			
			sprintf(xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].strTeamName, "%s",bData[i][2]);
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].totalTeam = 0;
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].codeTeam[0] = atoi(bData[i][3]);
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].codeTeam[1] = atoi(bData[i][4]);
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].codeTeam[2] = atoi(bData[i][5]);
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].codeTeam[3] = atoi(bData[i][6]);
			
						
			for(int k=0;k<CODETEAMMAX;k++)
			{
				if(xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].codeTeam[k] != 0)
					xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].totalTeam++;
			}
						
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].isNew = atoi(bData[i][7]) == 0?FALSE:TRUE;
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].isHot = atoi(bData[i][8]) == 0?FALSE:TRUE;
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].isEvent = atoi(bData[i][9]) == 0?FALSE:TRUE;
			xInterior.xSlot[interiorType][xInterior.totalSlot[interiorType]].sale = atoi(bData[i][10]);
			xInterior.totalSlot[interiorType]++;
		}
		break;
	case EXCEL_PS_DRESS_IMG:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			
			int fashionType = atoi(bData[i][2])/1000;
			int fashionList = atoi(bData[i][2])%1000;
            
            
			
			xFashionData[fashionType][fashionList].isImg[0][0] = atoi(bData[i][3]);
			xFashionData[fashionType][fashionList].isImg[0][1] = atoi(bData[i][3+1]);
			xFashionData[fashionType][fashionList].isImg[0][2] = atoi(bData[i][3+2]);
			xFashionData[fashionType][fashionList].isImg[0][3] = atoi(bData[i][3+3]);
			xFashionData[fashionType][fashionList].isImg[0][4] = atoi(bData[i][3+4]);
			xFashionData[fashionType][fashionList].isImg[0][5] = atoi(bData[i][3+5]);
			xFashionData[fashionType][fashionList].isImg[0][6] = atoi(bData[i][3+6]);
			xFashionData[fashionType][fashionList].isImg[0][7] = atoi(bData[i][3+7]);
			xFashionData[fashionType][fashionList].isImg[0][8] = atoi(bData[i][3+8]);
			xFashionData[fashionType][fashionList].isImg[0][9] = atoi(bData[i][3+9]);
			xFashionData[fashionType][fashionList].isImg[0][10] = atoi(bData[i][3+10]);
			xFashionData[fashionType][fashionList].isImg[0][11] = atoi(bData[i][3+11]);
			xFashionData[fashionType][fashionList].isImg[0][12] = atoi(bData[i][3+12]);
			xFashionData[fashionType][fashionList].isImg[0][13] = atoi(bData[i][3+13]);
			xFashionData[fashionType][fashionList].isImg[0][14] = atoi(bData[i][3+14]);
			xFashionData[fashionType][fashionList].isImg[0][15] = atoi(bData[i][3+15]);
			xFashionData[fashionType][fashionList].isImg[0][16] = atoi(bData[i][3+16]);
			xFashionData[fashionType][fashionList].isImg[0][17] = atoi(bData[i][3+17]);
			xFashionData[fashionType][fashionList].isImg[0][18] = atoi(bData[i][3+18]);
			xFashionData[fashionType][fashionList].isImg[1][0] = atoi(bData[i][22]);
			xFashionData[fashionType][fashionList].isImg[1][1] = atoi(bData[i][22+1]);
			xFashionData[fashionType][fashionList].isImg[1][2] = atoi(bData[i][22+2]);
			xFashionData[fashionType][fashionList].isImg[1][3] = atoi(bData[i][22+3]);
			xFashionData[fashionType][fashionList].isImg[1][4] = atoi(bData[i][22+4]);
			xFashionData[fashionType][fashionList].isImg[1][5] = atoi(bData[i][22+5]);
			xFashionData[fashionType][fashionList].isImg[1][6] = atoi(bData[i][22+6]);
			xFashionData[fashionType][fashionList].isImg[1][7] = atoi(bData[i][22+7]);
			xFashionData[fashionType][fashionList].isImg[1][8] = atoi(bData[i][22+8]);
			xFashionData[fashionType][fashionList].isImg[1][9] = atoi(bData[i][22+9]);
			xFashionData[fashionType][fashionList].isImg[1][10] = atoi(bData[i][22+10]);
			xFashionData[fashionType][fashionList].isImg[1][11] = atoi(bData[i][22+11]);
			xFashionData[fashionType][fashionList].isImg[1][12] = atoi(bData[i][22+12]);
			xFashionData[fashionType][fashionList].isImg[1][13] = atoi(bData[i][22+13]);
			xFashionData[fashionType][fashionList].isImg[1][14] = atoi(bData[i][22+14]);
			xFashionData[fashionType][fashionList].isImg[1][15] = atoi(bData[i][22+15]);
			xFashionData[fashionType][fashionList].isImg[1][16] = atoi(bData[i][22+16]);
			xFashionData[fashionType][fashionList].isImg[1][17] = atoi(bData[i][22+17]);
			xFashionData[fashionType][fashionList].isImg[1][18] = atoi(bData[i][22+18]);
			
			xFashionData[fashionType][fashionList].isImgF[1] = atoi(bData[i][41]);
			xFashionData[fashionType][fashionList].isImgF[3] = atoi(bData[i][41+1]);
			xFashionData[fashionType][fashionList].isImgF[5] = atoi(bData[i][41+2]);
			xFashionData[fashionType][fashionList].isImgF[6] = atoi(bData[i][41+3]);
			xFashionData[fashionType][fashionList].isImgF[11] = atoi(bData[i][41+4]);
			xFashionData[fashionType][fashionList].isImgF[12] = atoi(bData[i][41+5]);
			xFashionData[fashionType][fashionList].isImgF[13] = atoi(bData[i][41+6]);
			xFashionData[fashionType][fashionList].isImgF[17] = atoi(bData[i][41+7]);
						
		}
		break;
	case EXCEL_PS_DRESS_DATA:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			int fashionType = atoi(bData[i][2])/1000;
			int fashionList = atoi(bData[i][2])%1000;
            
			sprintf(xFashionData[fashionType][fashionList].strName, "%s",bData[i][1]);
			xFashionData[fashionType][fashionList].lv = atoi(bData[i][3]);
           
			xFashionData[fashionType][fashionList].layer = atoi(bData[i][5]);
			xFashionData[fashionType][fashionList].gender = atoi(bData[i][6]);
			
			initSecurity(&xFashionData[fashionType][fashionList].fame, atoi(bData[i][7]));
			initSecurity(&xFashionData[fashionType][fashionList].price, atoi(bData[i][8]));
			xFashionData[fashionType][fashionList].priceType = atoi(bData[i][9]);		//0:골드1:룩2:패션쇼
			initSecurity(&xFashionData[fashionType][fashionList].makeTime, atoi(bData[i][10]));
			initSecurity(&xFashionData[fashionType][fashionList].makeNum, atoi(bData[i][11]));
			initSecurity(&xFashionData[fashionType][fashionList].exp, atoi(bData[i][12]));
			initSecurity(&xFashionData[fashionType][fashionList].sellPrice, atoi(bData[i][13]));
			xFashionData[fashionType][fashionList].isStaff = atoi(bData[i][14]);
			xFashionData[fashionType][fashionList].color = atoi(bData[i][15]);
			xFashionData[fashionType][fashionList].makePoint = atoi(bData[i][16]);
			xFashionData[fashionType][fashionList].inShopPer = atoi(bData[i][17]);
			xFashionData[fashionType][fashionList].concept = atoi(bData[i][18]);	//컨셉
			xFashionData[fashionType][fashionList].type2FashionShowScore = atoi(bData[i][19]);	//패션쇼점수공식용
			xFashionData[fashionType][fashionList].theme = atoi(bData[i][20]);	//테마
            
            
            
		}
		break;
	case EXCEL_PS_DRESS_LIST:
		for(int t=0;t<7;t++)
			xCatalog.totalSlot[t] = 0;
						
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			//(아이템코드)
			int fashionType = atoi(bData[i][1]);
            
            
           
            
			xCatalog.xSlot[fashionType][xCatalog.totalSlot[fashionType]].code = atoi(bData[i][2]);
			xCatalog.xSlot[fashionType][xCatalog.totalSlot[fashionType]].isNew = atoi(bData[i][3]) == 0?FALSE:TRUE;
			xCatalog.xSlot[fashionType][xCatalog.totalSlot[fashionType]].isHot = atoi(bData[i][4]) == 0?FALSE:TRUE;
			xCatalog.xSlot[fashionType][xCatalog.totalSlot[fashionType]].isEvent = atoi(bData[i][5]) == 0?FALSE:TRUE;
			
			xCatalog.totalSlot[fashionType]++;
		}
		break;
	case EXCEL_PS_STAFF_DATA:
		xWorldMap.totalHairData = 0;
		xWorldMap.totalFaceData = 0;

		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			int staffType = atoi(bData[i][2]);
			
			switch(staffType)
			{
			case 0:	//헤어
				sprintf(xHairData[xWorldMap.totalHairData].strName, "%s",bData[i][1]);
				xHairData[xWorldMap.totalHairData].lv = atoi(bData[i][3]);
				xHairData[xWorldMap.totalHairData].gender = atoi(bData[i][4]);
				initSecurity(&xHairData[xWorldMap.totalHairData].price, atoi(bData[i][5]));
				xHairData[xWorldMap.totalHairData].priceType = atoi(bData[i][6]);
				xHairData[xWorldMap.totalHairData].useType = atoi(bData[i][7]);
				xHairData[xWorldMap.totalHairData].inShopPer = atoi(bData[i][8]);
				xWorldMap.totalHairData++;
				break;
			case 1:	//얼굴
				sprintf(xFaceData[xWorldMap.totalFaceData].strName, "%s",bData[i][1]);
				xFaceData[xWorldMap.totalFaceData].lv = atoi(bData[i][3]);
				xFaceData[xWorldMap.totalFaceData].gender = atoi(bData[i][4]);
				initSecurity(&xFaceData[xWorldMap.totalFaceData].price, atoi(bData[i][5]));
				xFaceData[xWorldMap.totalFaceData].priceType = atoi(bData[i][6]);
				xFaceData[xWorldMap.totalFaceData].inShopPer = atoi(bData[i][8]);
				xWorldMap.totalFaceData++;
				break;
			}
		}
		break;
	case EXCEL_PS_STAFF_LIST:
		for(int t=0;t<6;t++)
			xStaff.totalSlot[t] = 0;
						
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			int staffType = atoi(bData[i][1]);
			//(아이템코드)
			xStaff.xSlot[staffType][xStaff.totalSlot[staffType]++].code = atoi(bData[i][2]);
		}
		break;
	case EXCEL_PS_LVTABLE:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			initSecurity(&xBalanceData.expMax[i-1], atoi(bData[i+1][1]));
			xBalanceData.fameMax[i-1] = atoi(bData[i][2]);
			
			xBalanceData.buildHangerMax[0][i-1] = atoi(bData[i][3]);
			xBalanceData.buildAccecssoryMax[0][i-1] = atoi(bData[i][4]);
			xBalanceData.buildFittingRoomMax[0][i-1] = atoi(bData[i][5]);
			xBalanceData.buildShowwindowMax[0][i-1] = atoi(bData[i][6]);
			
			xBalanceData.buildHangerMax[1][i-1] = atoi(bData[i][7]);
			xBalanceData.buildAccecssoryMax[1][i-1] = atoi(bData[i][8]);
			xBalanceData.buildFittingRoomMax[1][i-1] = atoi(bData[i][9]);
			xBalanceData.buildShowwindowMax[1][i-1] = atoi(bData[i][10]);
						
			xBalanceData.trend1Per[i-1] = atoi(bData[i][11]);	//트랜드확률1~10
			xBalanceData.trend11Per[i-1] = atoi(bData[i][12]);	//트랜드확률11~20
			xBalanceData.trend21Per[i-1] = atoi(bData[i][13]);	//트랜드확률21~30
			xBalanceData.trend31Per[i-1] = atoi(bData[i][14]);	//트랜드확률31~40
			xBalanceData.trend41Per[i-1] = atoi(bData[i][15]);	//트랜드확률41~
            
            printf("xBalanceData.trend41Per[%d]>>%d\n",i-1,xBalanceData.trend41Per[i-1]);
            printf("xBalanceData.expMax[%d]>>%d\n",i-1,xBalanceData.expMax[i-1].oriData);
		}
		break;
	case EXCEL_PS_RESDOWN:
		xResCheck.totalVer = colsMax;
		for(i=1; i<colsMax+1;i++)
		{
			sprintf(xResCheck.strUrlDir[i-1], "%s",bData[i][1]);
			for(int f=0;f<strlen(xResCheck.strUrlDir[i-1]);f++)
			{
				if(xResCheck.strUrlDir[i-1][f] == '?')
					xResCheck.strUrlDir[i-1][f] = '/';
			}
			xResCheck.isZip[i-1] = TRUE;
		}
		break;
	case EXCEL_PS_MINIGAME:
		colsMax +=1;
        
		xMiniGame.xDragScroll.totalNum = 0;
			
		for(i=1;i<colsMax;i++)
		{
			
			xMiniGame.xMiniGameSlot[i-1].slotType = atoi(bData[i][1]);
			initSecurity(&xMiniGame.xMiniGameSlot[i-1].slotCode, atoi(bData[i][2]));
			xMiniGame.xMiniGameSlot[i-1].slotImgNum = atoi(bData[i][3]);
			xMiniGame.xMiniGameSlot[i-1].count = atoi(bData[i][4]);
			
			xMiniGame.xMiniGameSlot[i-1].perCount[0] = atoi(bData[i][5]);
			xMiniGame.xMiniGameSlot[i-1].per[0] = atoi(bData[i][6]);
			
			xMiniGame.xMiniGameSlot[i-1].perCount[1] = atoi(bData[i][7]);
			xMiniGame.xMiniGameSlot[i-1].per[1] = atoi(bData[i][8]);
			
			xMiniGame.xMiniGameSlot[i-1].perCount[2] = atoi(bData[i][9]);
			xMiniGame.xMiniGameSlot[i-1].per[2] = atoi(bData[i][10]);
			
			xMiniGame.xMiniGameSlot[i-1].perCount[3] = atoi(bData[i][11]);
			xMiniGame.xMiniGameSlot[i-1].per[3] = atoi(bData[i][12]);
			
			xMiniGame.xMiniGameSlot[i-1].perCount[4] = atoi(bData[i][13]);
			xMiniGame.xMiniGameSlot[i-1].per[4] = atoi(bData[i][14]);			
			xMiniGame.xDragScroll.totalNum++;
		}
		break;
	case EXCEL_PS_MODELCASTING:
		xModel.newModelTotal[0] = 0;
		xModel.newModelTotal[1] = 0;
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			int type = atoi(bData[i][1]);
			
			switch(type)
			{
			case 0:	//일반캐스팅
				xModel.newModelCount[xModel.newModelTotal[type]] = atoi(bData[i][2]);
				
				xModel.newModelPer[xModel.newModelTotal[type]][0] = atoi(bData[i][3]);
				xModel.newModelCountPlus[xModel.newModelTotal[type]][0] = atoi(bData[i][4]);
				xModel.newModelPer[xModel.newModelTotal[type]][1] = atoi(bData[i][5]);
				xModel.newModelCountPlus[xModel.newModelTotal[type]][1] = atoi(bData[i][6]);
				xModel.newModelPer[xModel.newModelTotal[type]][2] = atoi(bData[i][7]);
				xModel.newModelCountPlus[xModel.newModelTotal[type]][2] = atoi(bData[i][8]);
				xModel.newModelPer[xModel.newModelTotal[type]][3] = atoi(bData[i][9]);
				xModel.newModelCountPlus[xModel.newModelTotal[type]][3] = atoi(bData[i][10]);
				xModel.newModelTotal[type]++;
				break;
			case 1:	//고급캐스팅
				xModel.newModelCount_Cash[xModel.newModelTotal[type]] = atoi(bData[i][2]);
					
				xModel.newModelPer_Cash[xModel.newModelTotal[type]][0] = atoi(bData[i][3]);
				xModel.newModelCountPlus_Cash[xModel.newModelTotal[type]][0] = atoi(bData[i][4]);
				xModel.newModelPer_Cash[xModel.newModelTotal[type]][1] = atoi(bData[i][5]);
				xModel.newModelCountPlus_Cash[xModel.newModelTotal[type]][1] = atoi(bData[i][6]);
				xModel.newModelPer_Cash[xModel.newModelTotal[type]][2] = atoi(bData[i][7]);
				xModel.newModelCountPlus_Cash[xModel.newModelTotal[type]][2] = atoi(bData[i][8]);
				xModel.newModelPer_Cash[xModel.newModelTotal[type]][3] = atoi(bData[i][9]);
				xModel.newModelCountPlus_Cash[xModel.newModelTotal[type]][3] = atoi(bData[i][10]);
				xModel.newModelTotal[type]++;
				break;
			}
		}
		break;
	case EXCEL_PS_SONG:
		colsMax +=1;
		xSongSet.total[0] = 0;
		xSongSet.total[1] = 0;
		for(i=1;i<colsMax;i++)
		{
			int type = atoi(bData[i][1]);
			xSongSet.gender[type][xSongSet.total[type]] = atoi(bData[i][2]);
			xSongSet.hair[type][xSongSet.total[type]] = atoi(bData[i][3]);
			xSongSet.face[type][xSongSet.total[type]] = atoi(bData[i][4]);
			
			xSongSet.code[type][xSongSet.total[type]][0] = atoi(bData[i][5]);
			xSongSet.code[type][xSongSet.total[type]][1] = atoi(bData[i][6]);
			xSongSet.code[type][xSongSet.total[type]][2] = atoi(bData[i][7]);
			xSongSet.code[type][xSongSet.total[type]][3] = atoi(bData[i][8]);
			xSongSet.code[type][xSongSet.total[type]][4] = atoi(bData[i][9]);
			xSongSet.code[type][xSongSet.total[type]][5] = atoi(bData[i][10]);
			xSongSet.code[type][xSongSet.total[type]][6] = atoi(bData[i][11]);
			xSongSet.total[type]++;
		}
		break;
	case EXCEL_PS_NPCSET:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			xNpcSet.gender[i-1] = atoi(bData[i][2]);
			xNpcSet.lvMin[i-1] = atoi(bData[i][3]);
			xNpcSet.lvMax[i-1] = atoi(bData[i][4]);
			
			xNpcSet.code[i-1][0] = atoi(bData[i][5]);
			xNpcSet.code[i-1][1] = atoi(bData[i][6]);
			xNpcSet.code[i-1][2] = atoi(bData[i][7]);
			xNpcSet.code[i-1][3] = atoi(bData[i][8]);
			xNpcSet.code[i-1][4] = atoi(bData[i][9]);
			xNpcSet.code[i-1][5] = atoi(bData[i][10]);
			xNpcSet.code[i-1][6] = atoi(bData[i][11]);
			xNpcSet.isFittingRoom[i-1] = atoi(bData[i][12])==0?TRUE:FALSE;
			xNpcSet.total++;
			}
		break;
	case EXCEL_PS_CAR:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			sprintf(xCarData[i-1].strName, "%s",bData[i][1]);
			xCarData[i-1].lv = atoi(bData[i][2]);
			initSecurity(&xCarData[i-1].price, atoi(bData[i][3]));
			xCarData[i-1].priceType = atoi(bData[i][4]);
			initSecurity(&xCarData[i-1].timePer,atoi(bData[i][5]));
		}
		
		//0,1,2
		for(int i=0;i<=2;i++)
		{
			xCar.tireX[i][0][0] = -9;
			xCar.tireY[i][0][0] = -25;
			
			xCar.tireX[i][0][1] = 71;
			xCar.tireY[i][0][1] = -64;
			
			xCar.tireX[i][1][0] = -18;
			xCar.tireY[i][1][0] = -31;
			
			xCar.tireX[i][1][1] = 68;
			xCar.tireY[i][1][1] = -74;
			
			
			xCar.boxX[i][0] = -17;
			xCar.boxY[i][0] = -99;
			xCar.boxX[i][1] = -17;
			xCar.boxY[i][1] = -99;
			
			
		}
		
		//3,4,5
		for(int i=3;i<=5;i++)
		{
			xCar.tireX[i][0][0] = -13;
			xCar.tireY[i][0][0] = -25;
			
			xCar.tireX[i][0][1] = 54;
			xCar.tireY[i][0][1] = -57;
			
			xCar.tireX[i][1][0] = -10;
			xCar.tireY[i][1][0] = -25;
			
			xCar.tireX[i][1][1] = 56;
			xCar.tireY[i][1][1] = -57;
			
			xCar.boxX[i][0] = 2;
			xCar.boxY[i][0] = -99;
			xCar.boxX[i][1] = 2;
			xCar.boxY[i][1] = -99;
		}
		
		//6,7,8
		for(int i=6;i<=8;i++)
		{
			xCar.tireX[i][0][0] = -20;
			xCar.tireY[i][0][0] = -24;
			
			xCar.tireX[i][0][1] = 70;
			xCar.tireY[i][0][1] = -69;
			
			xCar.tireX[i][1][0] = -19;
			xCar.tireY[i][1][0] = -25;
			
			xCar.tireX[i][1][1] = 65;
			xCar.tireY[i][1][1] = -66;
			
			xCar.boxX[i][0] = -12;
			xCar.boxY[i][0] = -83;
			xCar.boxX[i][1] = -12;
			xCar.boxY[i][1] = -73;
		}
		
		//9,10,11
		for(int i=9;i<=11;i++)
		{
			xCar.tireX[i][0][0] = -15;
			xCar.tireY[i][0][0] = -19;
			
			xCar.tireX[i][0][1] = 66;
			xCar.tireY[i][0][1] = -58;
			
			xCar.tireX[i][1][0] = -23;
			xCar.tireY[i][1][0] = -23;
			
			xCar.tireX[i][1][1] = 61;
			xCar.tireY[i][1][1] = -64;
			
			xCar.boxX[i][0] = -12;
			xCar.boxY[i][0] = -96;
			xCar.boxX[i][1] = -12;
			xCar.boxY[i][1] = -81;
		}
		
		//12,13,14
		for(int i=12;i<=14;i++)
		{
			xCar.tireX[i][0][0] = -12;
			xCar.tireY[i][0][0] = -16;
			
			xCar.tireX[i][0][1] = 64;
			xCar.tireY[i][0][1] = -53;
			
			xCar.tireX[i][1][0] = -18;
			xCar.tireY[i][1][0] = -23;
			
			xCar.tireX[i][1][1] = 61;
			xCar.tireY[i][1][1] = -62;
			
			xCar.boxX[i][0] = -5;
			xCar.boxY[i][0] = -94;
			xCar.boxX[i][1] = -6;
			xCar.boxY[i][1] = -81;
		}
		
		//15,16,17
		for(int i=15;i<=17;i++)
		{
			xCar.tireX[i][0][0] = -10;
			xCar.tireY[i][0][0] = -20;
			
			xCar.tireX[i][0][1] = 71;
			xCar.tireY[i][0][1] = -60;
			
			xCar.tireX[i][1][0] = -11;
			xCar.tireY[i][1][0] = -24;
			
			xCar.tireX[i][1][1] = 69;
			xCar.tireY[i][1][1] = -64;
			
			xCar.boxX[i][0] = -13;
			xCar.boxY[i][0] = -96;
			xCar.boxX[i][1] = -6;
			xCar.boxY[i][1] = -86;
		}
		
		//18,19,20
		for(int i=18;i<=20;i++)
		{
			xCar.tireX[i][0][0] = -15;
			xCar.tireY[i][0][0] = -28;
			
			xCar.tireX[i][0][1] = 65;
			xCar.tireY[i][0][1] = -68;
			
			xCar.tireX[i][1][0] = -21;
			xCar.tireY[i][1][0] = -21;
			
			xCar.tireX[i][1][1] = 69;
			xCar.tireY[i][1][1] = -70;
			
			xCar.boxX[i][0] = 0;
			xCar.boxY[i][0] = -115;
			xCar.boxX[i][1] = 0;
			xCar.boxY[i][1] = -115;
		}
		
		//21,22,23
		for(int i=21;i<=23;i++)
		{
			xCar.tireX[i][0][0] = -13;
			xCar.tireY[i][0][0] = -11;
			
			xCar.tireX[i][0][1] = 68;
			xCar.tireY[i][0][1] = -50;
			
			xCar.tireX[i][1][0] = -13;
			xCar.tireY[i][1][0] = -17;
			
			xCar.tireX[i][1][1] = 65;
			xCar.tireY[i][1][1] = -56;
			
			xCar.boxX[i][0] = -12;
			xCar.boxY[i][0] = -96;
			xCar.boxX[i][1] = -12;
			xCar.boxY[i][1] = -86;
		}
		
		//24,25,26
		for(int i=24;i<=26;i++)
		{
			xCar.tireX[i][0][0] = -18;
			xCar.tireY[i][0][0] = -30;
			
			xCar.tireX[i][0][1] = 72;
			xCar.tireY[i][0][1] = -74;
			
			xCar.tireX[i][1][0] = -18;
			xCar.tireY[i][1][0] = -31;
			
			xCar.tireX[i][1][1] = 74;
			xCar.tireY[i][1][1] = -76;
			
			xCar.boxX[i][0] = 2;
			xCar.boxY[i][0] = -76;
			xCar.boxX[i][1] = 2;
			xCar.boxY[i][1] = -76;
		}
		
		//27,28,29
		for(int i=27;i<=29;i++)
		{
			xCar.tireX[i][0][0] = -21;
			xCar.tireY[i][0][0] = -24;
			
			xCar.tireX[i][0][1] = 70;
			xCar.tireY[i][0][1] = -68;
			
			xCar.tireX[i][1][0] = -22;
			xCar.tireY[i][1][0] = -21;
			
			xCar.tireX[i][1][1] = 72;
			xCar.tireY[i][1][1] = -68;
			
			xCar.boxX[i][0] = -6;
			xCar.boxY[i][0] = -83;
			xCar.boxX[i][1] = -6;
			xCar.boxY[i][1] = -83;
		}
		break;
	case EXCEL_PS_CARSLOT:
		xShop.carTotalNum = colsMax;
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			xShop.carSlot[i-1] = atoi(bData[i][1]);
		}
		break;
	case EXCEL_PS_HACK:
		xHacking.totalNum = 0;
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			sprintf(xHacking.strPackage[xHacking.totalNum], "%s",bData[i][1]);
			xHacking.type[xHacking.totalNum] = atoi(bData[i][2]);
			xHacking.totalNum++;
		}
		break;
	case EXCEL_PS_QUESTMAIN:
			
		xQuestMain.totalNum = colsMax;
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			sprintf(xQuestDataMain[i-1].strTitle, "%s",bData[i][1]);
			xQuestDataMain[i-1].lv = atoi(bData[i][2]);
			xQuestDataMain[i-1].endQuestNum = atoi(bData[i][3]);
			xQuestDataMain[i-1].npcCode = atoi(bData[i][4]);
			xQuestDataMain[i-1].dialogNum = atoi(bData[i][5]);
			sprintf(xQuestDataMain[i-1].strInfo, "%s",bData[i][6]);
			sprintf(xQuestDataMain[i-1].strEnd, "%s",bData[i][7]);
			
			
			
			xQuestDataMain[i-1].checkType[0] = atoi(bData[i][8]);
			xQuestDataMain[i-1].checkCode[0] = atoi(bData[i][9]);
			xQuestDataMain[i-1].checkCodeSub[0] = xQuestDataMain[i-1].checkCode[0]/1000;
			xQuestDataMain[i-1].checkMax[0] = xQuestDataMain[i-1].checkCode[0]%1000;
			if(xQuestDataMain[i-1].checkMax[0] == -1)
				xQuestDataMain[i-1].checkMax[0] = 1;
				
				
				
			xQuestDataMain[i-1].checkType[1] = atoi(bData[i][10]);
			xQuestDataMain[i-1].checkCode[1] = atoi(bData[i][11]);
			xQuestDataMain[i-1].checkCodeSub[1] = xQuestDataMain[i-1].checkCode[1]/1000;
			xQuestDataMain[i-1].checkMax[1] = xQuestDataMain[i-1].checkCode[1]%1000;
			if(xQuestDataMain[i-1].checkMax[1] == -1)
				xQuestDataMain[i-1].checkMax[1] = 1;
					
			xQuestDataMain[i-1].checkType[2] = atoi(bData[i][12]);
			xQuestDataMain[i-1].checkCode[2] = atoi(bData[i][13]);
			xQuestDataMain[i-1].checkCodeSub[2] = xQuestDataMain[i-1].checkCode[2]/1000;
			xQuestDataMain[i-1].checkMax[2] = xQuestDataMain[i-1].checkCode[2]%1000;
			if(xQuestDataMain[i-1].checkMax[2] == -1)
				xQuestDataMain[i-1].checkMax[2] = 1;
						
			xQuestDataMain[i-1].fastCash = atoi(bData[i][14]);
			xQuestDataMain[i-1].giftType[0] = atoi(bData[i][15]);
			initSecurity(&xQuestDataMain[i-1].giftMax[0], atoi(bData[i][16]));
			xQuestDataMain[i-1].giftType[1] = atoi(bData[i][17]);
			initSecurity(&xQuestDataMain[i-1].giftMax[1], atoi(bData[i][18]));
			xQuestDataMain[i-1].giftType[2] = atoi(bData[i][19]);
			initSecurity(&xQuestDataMain[i-1].giftMax[2], atoi(bData[i][20]));
						
			sprintf(xQuestDataMain[i-1].strSubInfo, "%s",bData[i][21]);
			xQuestDataMain[i-1].iconNum = atoi(bData[i][22]);



			
			
			
			
			if(xQuestDataMain[i-1].checkType[0] == 20)
			{
				xQuestDataMain[i-1].fastCash = -1;
			}
			
			for(int k=0;k<3;k++)
			{
				switch(xQuestDataMain[i-1].checkType[k])
				{
				case 0:
				case 19:
				case 34:
				case 20:
				case 54:// xx등급 이상 모델 캐스팅하기
					xQuestDataMain[i-1].checkMax[k] = 1;
					break;
				case 85://	(특정의상카테고리)만 이용해 골드 x 벌기 카테고리/99999
					xQuestDataMain[i-1].checkMax[k] = xQuestDataMain[i-1].checkCode[k]%100000;
					xQuestDataMain[i-1].checkCode[k] = xQuestDataMain[i-1].checkCode[k]/100000;
					break;
				case 1:
				case 2:
				case 5:
				case 6:
				case 21:
				case 35:
				case 42://	주문된 %s 진열하기
				case 84://	xx 테마 인테리어 구매하기0 테마번호/999
				case 88://	선호도 x% 상태로 의상 x벌 판매하기
					xQuestDataMain[i-1].checkCode[k] = xQuestDataMain[i-1].checkCode[k]/1000;
					break;
				case 11:	//명성도
				case 12:	//골드
				case 17:	//칭호 갯수
				case 36:	//얼마이상구매
				case 37://	판매 단가 %d원 이상 의상 주문
				case 38://	주문수량 %d벌 이상 의상 주문
				case 39://	명성도 %d 이상 의상 구매
				case 40://	의상 라이센스 %d개 이상 보유하기
				case 46://	패션쇼 %d점 달성하기
				case 48://	마네킹 레이어드 %d회 달성하기
				case 51://	여자 모델 %d명 피팅하기
				case 52://	남자 모델 %d명 피팅하기
				case 55://	모델 %d명 보유하기
				case 56://	선호도 %d%% 달성하기
				case 57://	캔디 모으기
				case 69://	남자마네킹 레이어드 %d회 달성하기(%d/%d)
				case 78://	모델 활동으로 %d원 벌기(%d/%d)
				case 79://	모델 활동으로 경험치 %d획득하기(%d/%d)
				case 87://	캔디머신으로 x원 모으기
				case 95://	남자 모델만 이용해 패션쇼 xx점 달성하기
				case 96://	여자 모델만 이용해 패션쇼 xx점 달성하기
                case 102:
                case 103:
                case 104:
                case 105:
                case 107:
					xQuestDataMain[i-1].checkMax[k] = xQuestDataMain[i-1].checkCode[k];
					break;
				}
			}
			
			
			
			
			
			
			for(int k=0;k<3;k++)
			{
				switch(xQuestDataMain[i-1].giftType[k])
				{
					case 3:	//의상
					
						xQuestDataMain[i-1].giftCode[k] = xQuestDataMain[i-1].giftMax[k].oriData/1000;
						initSecurity(&xQuestDataMain[i-1].giftMax[k], xQuestDataMain[i-1].giftMax[k].oriData%1000);
						break;
					case 4:	//인테리어
					case 5:	//자동차
						xQuestDataMain[i-1].giftCode[k] = xQuestDataMain[i-1].giftMax[k].oriData;
						break;
				}
			}
			
		}
		break;
	case EXCEL_PS_QUESTNORMAL:
		xQuestInfo.totalNumNormal = colsMax;
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			sprintf(xQuestDataNormal[i-1].strTitle, "%s",bData[i][1]);
			
			
			xQuestDataNormal[i-1].lv = atoi(bData[i][2]);
			xQuestDataNormal[i-1].endQuestNum = atoi(bData[i][3]);
			xQuestDataNormal[i-1].npcCode = atoi(bData[i][4]);
			xQuestDataNormal[i-1].dialogNum = atoi(bData[i][5]);
			sprintf(xQuestDataNormal[i-1].strInfo, "%s",bData[i][6]);
			sprintf(xQuestDataNormal[i-1].strEnd, "%s",bData[i][7]);
			
			xQuestDataNormal[i-1].checkType[0] = atoi(bData[i][8]);
			xQuestDataNormal[i-1].checkCode[0] = atoi(bData[i][9]);
			xQuestDataNormal[i-1].checkCodeSub[0] = xQuestDataNormal[i-1].checkCode[0]/1000;
			xQuestDataNormal[i-1].checkMax[0] = xQuestDataNormal[i-1].checkCode[0]%1000;
			if(xQuestDataNormal[i-1].checkMax[0] == -1)
				xQuestDataNormal[i-1].checkMax[0] = 1;
								
			xQuestDataNormal[i-1].checkType[1] = atoi(bData[i][10]);
			xQuestDataNormal[i-1].checkCode[1] = atoi(bData[i][11]);
			xQuestDataNormal[i-1].checkCodeSub[1] = xQuestDataNormal[i-1].checkCode[1]/1000;
			xQuestDataNormal[i-1].checkMax[1] = xQuestDataNormal[i-1].checkCode[1]%1000;
			if(xQuestDataNormal[i-1].checkMax[1] == -1)
				xQuestDataNormal[i-1].checkMax[1] = 1;
										
			xQuestDataNormal[i-1].checkType[2] = atoi(bData[i][12]);
			xQuestDataNormal[i-1].checkCode[2] = atoi(bData[i][13]);
			xQuestDataNormal[i-1].checkCodeSub[2] = xQuestDataNormal[i-1].checkCode[2]/1000;
			xQuestDataNormal[i-1].checkMax[2] = xQuestDataNormal[i-1].checkCode[2]%1000;
			if(xQuestDataNormal[i-1].checkMax[2] == -1)
				xQuestDataNormal[i-1].checkMax[2] = 1;
												
			xQuestDataNormal[i-1].fastCash = atoi(bData[i][14]);
			xQuestDataNormal[i-1].giftType[0] = atoi(bData[i][15]);
			initSecurity(&xQuestDataNormal[i-1].giftMax[0], atoi(bData[i][16]));
			xQuestDataNormal[i-1].giftType[1] = atoi(bData[i][17]);
			initSecurity(&xQuestDataNormal[i-1].giftMax[1], atoi(bData[i][18]));
			xQuestDataNormal[i-1].giftType[2] = atoi(bData[i][19]);
			initSecurity(&xQuestDataNormal[i-1].giftMax[2], atoi(bData[i][20]));
			sprintf(xQuestDataNormal[i-1].strSubInfo, "%s",bData[i][21]);
			xQuestDataNormal[i-1].iconNum = atoi(bData[i][22]);
			
			for(int k=0;k<3;k++)
			 {
				switch(xQuestDataNormal[i-1].checkType[k])
				{
				case 0:
				case 19:
				case 34:
				case 20:
				case 54:    //  xx등급 이상 모델 캐스팅하기
					xQuestDataNormal[i-1].checkMax[k] = 1;
					break;
				case 85:    //  (특정의상카테고리)만 이용해 골드 x 벌기 카테고리/999
					xQuestDataNormal[i-1].checkMax[k] = xQuestDataNormal[i-1].checkCode[k]%100000;;
					xQuestDataNormal[i-1].checkCode[k] = xQuestDataNormal[i-1].checkCode[k]/100000;
					break;
				case 1:
				case 2:
				case 5:
				case 6:
				case 21:
				case 35:
				case 42:    //  주문된 %s 진열하기
				case 84:    //	xx 테마 인테리어 구매하기0 테마번호/999
				case 88:    //	선호도 x% 상태로 의상 x벌 판매하기
					xQuestDataNormal[i-1].checkCode[k] = xQuestDataNormal[i-1].checkCode[k]/1000;
					break;
				case 11:	//  명성도
				case 12:	//  골드
				case 17:	//  칭호 갯수
				case 36:	//  얼마이상구매
				case 37:    //	판매 단가 %d원 이상 의상 주문
				case 38:    //	주문수량 %d벌 이상 의상 주문
				case 39:    //	명성도 %d 이상 의상 구매
				case 40:    //	의상 라이센스 %d개 이상 보유하기
				case 46:    //	패션쇼 %d점 달성하기
				case 48:    //	마네킹 레이어드 %d회 달성하기
				case 51:    //	여자 모델 %d명 피팅하기
				case 52:    //	남자 모델 %d명 피팅하기
				case 55:    //	모델 %d명 보유하기
				case 56:    //	선호도 %d%% 달성하기
				case 57:    //	캔디 모으기
				case 69:    //	남자마네킹 레이어드 %d회 달성하기(%d/%d)
				case 78:    //	모델 활동으로 %d원 벌기(%d/%d)
				case 79:    //	모델 활동으로 경험치 %d획득하기(%d/%d)
				case 87:    //	캔디머신으로 x원 모으기
				case 95:    //	남자 모델만 이용해 패션쇼 xx점 달성하기
				case 96:    //	여자 모델만 이용해 패션쇼 xx점 달성하기
                case 102:
                case 103:
                case 104:   //  허니팡 점수 넘기기
                case 105:   //  루루팡 점수 넘기기
                case 107:
					xQuestDataNormal[i-1].checkMax[k] = xQuestDataNormal[i-1].checkCode[k];
					break;
				}
			}
		}
		break;
	case EXCEL_PS_SPECIALSALE:
		xSaleShop.totalNum = 0;
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			xSaleShop.slotCode[xSaleShop.totalNum] = atoi(bData[i][1]);
			xSaleShop.slotSalePrice[xSaleShop.totalNum] = atoi(bData[i][2]);
			xSaleShop.totalNum++;
		}
		break;
	case EXCEL_PS_GOODSLIST:
		for(int i=0;i<6;i++)
			xModel.fashionShowBonusTotal[i] = 0;
		
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			int grade = atoi(bData[i][1]);
			xModel.fashionShowBonusPer[grade][xModel.fashionShowBonusTotal[grade]] = atoi(bData[i][2]);
			xModel.fashionShowBonusPointMin[grade][xModel.fashionShowBonusTotal[grade]] = atoi(bData[i][3]);
			xModel.fashionShowBonusPointMax[grade][xModel.fashionShowBonusTotal[grade]] = atoi(bData[i][4]);
			xModel.fashionShowBonusPointType[grade][xModel.fashionShowBonusTotal[grade]] = atoi(bData[i][5]);
			xModel.fashionShowBonusTotal[grade]++;
            
		}
		break;
	case EXCEL_PS_MODEL:
		xModel.totalRanDomSlot = 0;
		xModel.totalRanDomSlotA = 0;
		xModel.totalRanDomSlotB = 0;
		xModel.totalRanDomSlotC = 0;
		xModel.totalRanDomSlotS = 0;
        
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			xModelData[i-1].imgNum = atoi(bData[i][1]);//이미지 번호
			sprintf(xModelData[i-1].strName, "%s",bData[i][2]);//모델명
			xModelData[i-1].grade = atoi(bData[i][3]);//등급
			xModelData[i-1].isOneHead = atoi(bData[i][4])==0?FALSE:TRUE;//얼굴 구분
			xModelData[i-1].sex = atoi(bData[i][5]);//성별
			xModelData[i-1].isSell = atoi(bData[i][6])==0?FALSE:TRUE;//판매구분
			xModelData[i-1].layeredNum = atoi(bData[i][7]);//레이어드 횟수
			xModelData[i-1].tema = atoi(bData[i][8]);//진짜 안씀....
			xModelData[i-1].price = atoi(bData[i][9]);//판매시 받는 재화의 양
			xModelData[i-1].priceType = atoi(bData[i][10]);//판매시 받는 재화의 종류
			xModelData[i-1].upGradeMax = atoi(bData[i][11]);//최대 강화치
            //12열도 안씀....
			initSecurity(&xModelData[i-1].giftTime, atoi(bData[i][13]));//홍보시간
			initSecurity(&xModelData[i-1].giftNum, atoi(bData[i][14]));//홍보시 획득하는 재화의 량
			xModelData[i-1].giftType= atoi(bData[i][15]);		//0:골드1:룩2:캔디3:경험치 //홍보시 재화의 종류
			
			xModelData[i-1].giftPer[0]= 0;
			xModelData[i-1].giftPer[1]= atoi(bData[i][16]);//강화시 얻는 이득...gifttype 0일 경우 각 강화정도에 따라 재화의 양이 증가, 1일 경우 강화정도에 따라 시간 값이 차감... 
			xModelData[i-1].giftPer[2]= atoi(bData[i][17]);
			xModelData[i-1].giftPer[3]= atoi(bData[i][18]);
			xModelData[i-1].giftPer[4]= atoi(bData[i][19]);
			xModelData[i-1].giftPer[5]= atoi(bData[i][20]);
			xModelData[i-1].giftPerType = atoi(bData[i][21]);		//0:수치1:시간  증가타입이라는데 확인 필요
			xModelData[i-1].giftIconNum = atoi(bData[i][22]);       //가이드라인(아이콘 번호)에서 보상을 뭘 주는지 그리는 아이콘
												
			xModelData[i-1].modelSkillType = atoi(bData[i][23]);    //모델타입(이미지 표시용)(예시 타입: 복합 이런거 나타냄)
			xModelData[i-1].totalSkillNum = atoi(bData[i][24]);     //기능 개수
			xModelData[i-1].skillType[0] = atoi(bData[i][25]);      //스킬 종류
			xModelData[i-1].skillPer[0] = atoi(bData[i][26]);       //스킬의 수치
			xModelData[i-1].skillType[1] = atoi(bData[i][27]);
			xModelData[i-1].skillPer[1] = atoi(bData[i][28]);
			xModelData[i-1].skillType[2] = atoi(bData[i][29]);
			xModelData[i-1].skillPer[2] = atoi(bData[i][30]);
            xModelData[i-1].skillType[3] = atoi(bData[i][31]);
            xModelData[i-1].skillPer[3] = atoi(bData[i][32]);
            xModelData[i-1].skillType[4] = atoi(bData[i][33]);
            xModelData[i-1].skillPer[4] = atoi(bData[i][34]);
			xModelData[i-1].totalFittingLayered = 0;
			xModelData[i-1].fittingLayered[0] = atoi(bData[i][35]); //스타일북에서 모델리스트에서 보이는 의상들...(레이어)
			xModelData[i-1].fittingLayered[1] = atoi(bData[i][36]);
			xModelData[i-1].fittingLayered[2] = atoi(bData[i][37]);
			xModelData[i-1].fittingLayered[3] = atoi(bData[i][38]);
			xModelData[i-1].fittingLayered[4] = atoi(bData[i][39]);
			xModelData[i-1].fittingLayered[5] = atoi(bData[i][40]);
			xModelData[i-1].fittingLayered[6] = atoi(bData[i][41]);
			xModelData[i-1].fittingLayered[7] = atoi(bData[i][42]);
			xModelData[i-1].fittingLayered[8] = atoi(bData[i][43]);
			xModelData[i-1].fittingLayered[9] = atoi(bData[i][44]);
			xModelData[i-1].isFittingInOut = atoi(bData[i][45])==0?FALSE:TRUE;//모델리스트에서 보이는 의상인데 내어입기 했느냐 안해느냐
			
			for(int ll=0;ll<10;ll++)
			{
				if(xModelData[i-1].fittingLayered[ll] != DONT)
					xModelData[i-1].totalFittingLayered++;
			}
			//모델 리스트 등급별로 분류
			if(xModelData[i-1].isSell == TRUE)
			{
				xModel.ranDomSlot[xModel.totalRanDomSlot++] = i-1;
				
				switch(xModelData[i-1].grade)
				{
				case 0:
					xModel.ranDomSlotC[xModel.totalRanDomSlotC++] = i-1;
					break;
				case 1:
					xModel.ranDomSlotB[xModel.totalRanDomSlotB++] = i-1;
					break;
				case 2:
					xModel.ranDomSlotA[xModel.totalRanDomSlotA++] = i-1;
					break;
				case 3:
					xModel.ranDomSlotS[xModel.totalRanDomSlotS++] = i-1;
					break;
				}
			}
		}
		break;
	case EXCEL_PS_STYLEBOOK:
		int totalGrade[5];
		int gradeSlot[5][128];
		int isNew[5][128];
		totalGrade[0] = 0;
		totalGrade[1] = 0;
		totalGrade[2] = 0;
		totalGrade[3] = 0;
        totalGrade[4] = 0;
		memset(gradeSlot, 0, sizeof(gradeSlot));
		memset(isNew, 0, sizeof(isNew));
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			int grade = atoi(bData[i][3]);
									
			gradeSlot[grade][totalGrade[grade]] = atoi(bData[i][1]);	//모델코드
			isNew[grade][totalGrade[grade]] = atoi(bData[i][4]);	//new
			totalGrade[grade]++;
		}
            
		//모델 등급별 슬롯
		xCollection.totalSlot = 0;
		for(int gradeI=3;gradeI>=0;gradeI--)
		{
			xCollection.xSlot[xCollection.totalSlot].type = COLLECTIONSLOT_TYPE_MODELGRADEBAR;
			xCollection.xSlot[xCollection.totalSlot].code = gradeI;
			xCollection.totalSlot++;
			for(int i=0;i<totalGrade[gradeI];i++)
			{
				xCollection.xSlot[xCollection.totalSlot].type = COLLECTIONSLOT_TYPE_MODELCODE;
				xCollection.xSlot[xCollection.totalSlot].code = gradeSlot[gradeI][i];
				xCollection.xSlot[xCollection.totalSlot].isNew = isNew[gradeI][i] == 0?FALSE:TRUE;
				xCollection.totalSlot++;
			}
		}

        break;
	case EXCEL_PS_STYLEDRESS:
		xCollection.totalFashionTheme = 0;
			
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			xCollection.fashionThemeList[xCollection.totalFashionTheme] = atoi(bData[i][1]);
			sprintf(xCollection.strFashionTheme[xCollection.totalFashionTheme], "%s",bData[i][2]);
			xCollection.isFashionThemeNew[xCollection.totalFashionTheme] = atoi(bData[i][3]) == 0?FALSE:TRUE;
			xCollection.isFashionThemeFittingInOut[xCollection.totalFashionTheme] = atoi(bData[i][4]) == 0?FALSE:TRUE;
            
            
			xCollection.totalFashionTheme++;
		}
		break;
   
	case EXCEL_PS_DRESSCOLOR:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			//검정	 화이트	 그레이	 베이지	 빨강	 노랑	 파랑	 브라운	 초록	 보라	 핑크	 오렌지
			initFashionColor(i-1,atof(bData[i][1]),atof(bData[i][2]),atof(bData[i][3]),atof(bData[i][4]),atof(bData[i][5]),atof(bData[i][6])
							 ,atof(bData[i][7]),atof(bData[i][8]),atof(bData[i][9]),atof(bData[i][10]),atof(bData[i][11]),atof(bData[i][12]));
		}
		break;
	case EXCEL_PS_DRESSCONCEPT:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			//여성	 귀여운	 베이직	 클럽	 드레스	 시크	 섹시	 에스닉	 유니크
			initFashionConcept(i-1,atof(bData[i][1]),atof(bData[i][2]),atof(bData[i][3]),atof(bData[i][4]),atof(bData[i][5]),atof(bData[i][6])
							   ,atof(bData[i][7]),atof(bData[i][8]),atof(bData[i][9]));
		}
		break;
	case EXCEL_PS_BALANCE:
		///////////////////
		i = 1;
		xBalance.BaseDressScore = atof(bData[i][1]);//(의상기본점수)
		xBalance.GoldDressScore = atof(bData[i][2]);//(골드의상점수산출)
		xBalance.CashDressScore = atof(bData[i][3]);//(캐쉬의상점수산출)
		xBalance.TrendBonus = atof(bData[i][4]);//(유행보너스)
		xBalance.ConceptBonus = atof(bData[i][5]);//(컨셉보너스)
		xBalance.ColorBonus = atof(bData[i][6]);//(색상보너스)
		xBalance.SexBonus = atof(bData[i][7]);//(성별보너스)
		xBalance.TuckBonus = atof(bData[i][8]);//(턱인턱아웃보너스)
		xBalance.LayeredBonus = atof(bData[i][9]);//(레이어드횟수보너스)
			
		xBalance.LuckyMin = atof(bData[i][10]);//(행운점수min)
		xBalance.LuckyMax = atof(bData[i][11]);//(행운점수max)
									
		//////////////////
		i = 3;
        xBalance.Model[4] = atof(bData[i][1]);//(R등급모델)
		xBalance.Model[3] = atof(bData[i][2]);//(S등급모델)
		xBalance.Model[2] = atof(bData[i][3]);//(A등급모델)
		xBalance.Model[1] = atof(bData[i][4]);//(B등급모델)
		xBalance.Model[0] = atof(bData[i][5]);//(C등급모델)
		xBalance.Upgrade[0] = 0;//(0단계업그레이드)
		xBalance.Upgrade[1] = atof(bData[i][6]);//(1단계업그레이드)
		xBalance.Upgrade[2] = atof(bData[i][7]);//(2단계업그레이드)
		xBalance.Upgrade[3] = atof(bData[i][8]);//(3단계업그레이드)
		xBalance.Upgrade[4] = atof(bData[i][9]);//(4단계업그레이드)
		xBalance.Upgrade[5] = atof(bData[i][10]);//(5단계업그레이드)
		//////////////////
		
            
		//////////////////캐스팅확률
		i = 5;
		/////////////////
			
		//////////////////확장레벨
		i = 7;
		xExtensionShop.tileLv[0] = atof(bData[i][1]);
		xExtensionShop.tileLv[1] = atof(bData[i][2]);
		xExtensionShop.tileLv[2] = atof(bData[i][3]);
		xExtensionShop.tileLv[3] = atof(bData[i][4]);
		xExtensionShop.tileLv[4] = atof(bData[i][5]);
		xExtensionShop.tileLv[5] = atof(bData[i][6]);
		xExtensionShop.tileLv[6] = atof(bData[i][7]);
		/////////////////
			
		//////////////////확장골드
		i = 9;
		initSecurity(&xExtensionShop.tilePrice[0][0], atof(bData[i][1]));
		initSecurity(&xExtensionShop.tilePrice[1][0], atof(bData[i][2]));
		initSecurity(&xExtensionShop.tilePrice[2][0], atof(bData[i][3]));
		initSecurity(&xExtensionShop.tilePrice[3][0], atof(bData[i][4]));
		initSecurity(&xExtensionShop.tilePrice[4][0], atof(bData[i][5]));
		initSecurity(&xExtensionShop.tilePrice[5][0], atof(bData[i][6]));
		initSecurity(&xExtensionShop.tilePrice[6][0], atof(bData[i][7]));
		/////////////////
			
		//////////////////확장룩
		i = 11;
		initSecurity(&xExtensionShop.tilePrice[0][1], atof(bData[i][1]));
		initSecurity(&xExtensionShop.tilePrice[1][1], atof(bData[i][2]));
		initSecurity(&xExtensionShop.tilePrice[2][1], atof(bData[i][3]));
		initSecurity(&xExtensionShop.tilePrice[3][1], atof(bData[i][4]));
		initSecurity(&xExtensionShop.tilePrice[4][1], atof(bData[i][5]));
		initSecurity(&xExtensionShop.tilePrice[5][1], atof(bData[i][6]));
		initSecurity(&xExtensionShop.tilePrice[6][1], atof(bData[i][7]));
		/////////////////
			
		//////////////////확장명성도
		i = 13;
		xExtensionShop.tileFame[0] = atof(bData[i][1]);
		xExtensionShop.tileFame[1] = atof(bData[i][2]);
		xExtensionShop.tileFame[2] = atof(bData[i][3]);
		xExtensionShop.tileFame[3] = atof(bData[i][4]);
		xExtensionShop.tileFame[4] = atof(bData[i][5]);
		xExtensionShop.tileFame[5] = atof(bData[i][6]);
		xExtensionShop.tileFame[6] = atof(bData[i][7]);
		/////////////////
			
			
		//////////////////증축
		i = 15;
		xExtensionShop.floorLv[0] = atof(bData[i][1]);
		initSecurity(&xExtensionShop.floorPrice[0][0],atof(bData[i][2]));//골드
		initSecurity(&xExtensionShop.floorPrice[0][1],atof(bData[i][3]));//룩
		/////////////////
			
		////////////////카톡초대보상0
		i = 17;
		xKakao.inviteIconNum[0] = 0;
		xKakao.inviteIconNum[1] = 0;
		xKakao.inviteIconNum[2] = 0;
		xKakao.inviteIconNum[3] = 0;
		xKakao.inviteIconNum[4] = 0;
			
		initSecurity(&xKakao.inviteNum[0], atoi(bData[i][1]));
		xKakao.inviteType[0] = atoi(bData[i][2]);
		
		initSecurity(&xKakao.inviteNum[1], atoi(bData[i][3]));
		xKakao.inviteType[1] = atoi(bData[i][4]);
		
		
		initSecurity(&xKakao.inviteNum[2], atoi(bData[i][5]));
		xKakao.inviteType[2] = atoi(bData[i][6]);
		
		initSecurity(&xKakao.inviteNum[3], atoi(bData[i][7]));
		xKakao.inviteType[3] = atoi(bData[i][8]);
		
		initSecurity(&xKakao.inviteNum[4], atoi(bData[i][9]));
		xKakao.inviteType[4] = atoi(bData[i][10]);
					
		/////////////////////
		////////////////카톡초대보상0
		i = 19;
		sprintf(xKakao.strInviteText[0], "%s",bData[i][1]);
		sprintf(xKakao.strInviteText[1], "%s",bData[i][2]);
		sprintf(xKakao.strInviteText[2], "%s",bData[i][3]);
		sprintf(xKakao.strInviteText[3], "%s",bData[i][4]);
		sprintf(xKakao.strInviteText[4], "%s",bData[i][5]);
		/////////////////////
			
		////////////////패션쇼보상
		i = 21;
		xFashionShow.rankGiftLookWorld[0] = atoi(bData[i][1]);
		xFashionShow.rankGiftLookWorld[1] = atoi(bData[i][2]);
		xFashionShow.rankGiftLookWorld[2] = atoi(bData[i][3]);
		xFashionShow.rankGiftLookWorld[3] = atoi(bData[i][4]);
		xFashionShow.rankGiftLookWorld[4] = atoi(bData[i][5]);
		xFashionShow.rankGiftLookWorld[5] = atoi(bData[i][6]);

		/////////////////////
		////////////////패션쇼보상
		i = 23;
		xFashionShow.rankGiftLookWorld[6] = atoi(bData[i][1]);
		xFashionShow.rankGiftLookWorld[7] = atoi(bData[i][2]);
		xFashionShow.rankGiftLookWorld[8] = atoi(bData[i][3]);
		xFashionShow.rankGiftLookWorld[9] = atoi(bData[i][4]);
		xFashionShow.rankGiftLookWorld[10] = atoi(bData[i][5]);
		xFashionShow.rankGiftLookWorld[11] = atoi(bData[i][6]);
		xFashionShow.rankGiftLookFriend = atoi(bData[i][7]);
		/////////////////////
						
		////////////////유료샵0
		xShop.totalMoneyTab = 0;

		i = 30;
		//인덱스,0:룩1:골드,구매가격,제공포인트
		setShopMoneyData(xShop.totalMoneyTab++,0,3300	,atoi(bData[i+1][1]),atoi(bData[i][1]),atoi(bData[i+2][1]));
		setShopMoneyData(xShop.totalMoneyTab++,0,5500	,atoi(bData[i+1][2]),atoi(bData[i][2]),atoi(bData[i+2][2]));
		setShopMoneyData(xShop.totalMoneyTab++,0,11000	,atoi(bData[i+1][3]),atoi(bData[i][3]),atoi(bData[i+2][3]));
		setShopMoneyData(xShop.totalMoneyTab++,0,33000	,atoi(bData[i+1][4]),atoi(bData[i][4]),atoi(bData[i+2][4]));
		setShopMoneyData(xShop.totalMoneyTab++,0,55000	,atoi(bData[i+1][5]),atoi(bData[i][5]),atoi(bData[i+2][5]));
		setShopMoneyData(xShop.totalMoneyTab++,0,110000	,atoi(bData[i+1][6]),atoi(bData[i][6]),atoi(bData[i+2][6]));
		//setShopMoneyData(xShop.totalMoneyTab++,0,165000	,atoi(bData[i+1][7]),atoi(bData[i][7]),atoi(bData[i+2][7]));
		/////////////////////
		
		////////////////유료샵1
		i = 33;
		//인덱스,0:룩1:골드,구매가격,제공포인트
		setShopMoneyData(xShop.totalMoneyTab++,1,atoi(bData[i+2][1])	,atoi(bData[i+1][1]),atoi(bData[i][1]),0);
		setShopMoneyData(xShop.totalMoneyTab++,1,atoi(bData[i+2][2])	,atoi(bData[i+1][2]),atoi(bData[i][2]),0);
		setShopMoneyData(xShop.totalMoneyTab++,1,atoi(bData[i+2][3])	,atoi(bData[i+1][3]),atoi(bData[i][3]),0);
		setShopMoneyData(xShop.totalMoneyTab++,1,atoi(bData[i+2][4])	,atoi(bData[i+1][4]),atoi(bData[i][4]),0);
		setShopMoneyData(xShop.totalMoneyTab++,1,atoi(bData[i+2][5])	,atoi(bData[i+1][5]),atoi(bData[i][5]),0);
		setShopMoneyData(xShop.totalMoneyTab++,1,atoi(bData[i+2][6])	,atoi(bData[i+1][6]),atoi(bData[i][6]),0);
		setShopMoneyData(xShop.totalMoneyTab++,1,atoi(bData[i+2][7])	,atoi(bData[i+1][7]),atoi(bData[i][7]),0);
		/////////////////////
					
		////////////////유료샵2
		i = 37;
		//코드,타입,가격,포인트,타이틀
		setPremiumData(0,0,atoi(bData[i][1])	,1,"일반 캐스팅");
		setPremiumData(1,1,atoi(bData[i][2])	,1,"고급 캐스팅");
		setPremiumData(2,2,atoi(bData[i][3])	,1,"의상 유행 티켓");
		setPremiumData(3,2,atoi(bData[i][4])	,1,"잡화 유행 티켓");
		setPremiumData(4,1,atoi(bData[i][5])	,30,"캔디 30개");
		setPremiumData(5,1,atoi(bData[i][6])	,60,"캔디 60개");
		setPremiumData(6,1,atoi(bData[i][7])	,90,"캔디 90개");
		/////////////////////
			
		/////////////////////
		////////////////모델슬롯레벨제한
		i = 39;
		xModelMainSlot[0].openLv = atoi(bData[i][1]);
		xModelMainSlot[1].openLv = atoi(bData[i][2]);
		xModelMainSlot[2].openLv = atoi(bData[i][3]);
		xModelMainSlot[3].openLv = atoi(bData[i][4]);
		xModelMainSlot[4].openLv = atoi(bData[i][5]);						
		/////////////////////
			
		/////////////////////
		////////////////모델슬롯오픈가격
		i = 41;
		xModelMainSlot[0].openPrice[0] = atoi(bData[i][1]);
		xModelMainSlot[0].openPrice[1] = atoi(bData[i][2]);
		xModelMainSlot[1].openPrice[0] = atoi(bData[i][3]);
		xModelMainSlot[1].openPrice[1] = atoi(bData[i][4]);
		xModelMainSlot[2].openPrice[0] = atoi(bData[i][5]);
		xModelMainSlot[2].openPrice[1] = atoi(bData[i][6]);
		xModelMainSlot[3].openPrice[0] = atoi(bData[i][7]);
		xModelMainSlot[3].openPrice[1] = atoi(bData[i][8]);
		xModelMainSlot[4].openPrice[0] = atoi(bData[i][9]);
		xModelMainSlot[4].openPrice[1] = atoi(bData[i][10]);
		/////////////////////
			
		xSongSet.totalSong = 0;
		xSongSet.isSongOpen[0] = TRUE;
		/////////////////////
		////////////////음악가격
		i = 43;
		sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "Lively");
		xSongSet.songPriceType[xSongSet.totalSong] = 1;
		xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][1]);
		xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG0;
		sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "Start");
		xSongSet.songPriceType[xSongSet.totalSong] = 1;
		xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][2]);
		xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG1;
		sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "In my dream");
		xSongSet.songPriceType[xSongSet.totalSong] = 1;
		xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][3]);
		xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG2;
		sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "내 맘과 같다면");
		xSongSet.songPriceType[xSongSet.totalSong] = 1;
		xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][4]);
		xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG3;
		sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "널 위해");
		xSongSet.songPriceType[xSongSet.totalSong] = 1;
		xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][5]);
		xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG4;
		
		sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "다가와");
		xSongSet.songPriceType[xSongSet.totalSong] = 1;
		xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][6]);
		xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG5;
						
		if(atoi(bData[i][11]) == 1)
		{
			sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "Shining star");
			xSongSet.songPriceType[xSongSet.totalSong] = 1;
			xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][7]);
			xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG6;
			
			sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "UFO");
			xSongSet.songPriceType[xSongSet.totalSong] = 1;
			xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][8]);
			xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG7;
			
			sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "고백해");
			xSongSet.songPriceType[xSongSet.totalSong] = 1;
			xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][9]);
			xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG8;
			
			sprintf(xSongSet.strSongTitle[xSongSet.totalSong], "무적소녀");
			xSongSet.songPriceType[xSongSet.totalSong] = 1;
			xSongSet.songPrice[xSongSet.totalSong] = atoi(bData[i][10]);
			xSongSet.songSlot[xSongSet.totalSong++] = SND_WORLDMAP_BG9;
		}
						
		/////////////////////
		////////////////음악가격
		i = 45;
		//int upgradePrice[냐등급][업그레이드단계][재료등급]
		xModel.upgradePer[0][0][0] = atoi(bData[i][1]);
		xModel.upgradePer[0][1][0] = atoi(bData[i][2]);
		xModel.upgradePer[0][2][0] = atoi(bData[i][3]);
		xModel.upgradePer[0][3][0] = atoi(bData[i][4]);
		xModel.upgradePer[0][4][0] = atoi(bData[i][5]);
		xModel.upgradePer[1][0][0] = atoi(bData[i][6]);
		xModel.upgradePer[1][1][0] = atoi(bData[i][7]);
		xModel.upgradePer[1][2][0] = atoi(bData[i][8]);
		xModel.upgradePer[1][3][0] = atoi(bData[i][9]);
		xModel.upgradePer[1][4][0] = atoi(bData[i][10]);
		i = 46;
		xModel.upgradePer[0][0][1] = atoi(bData[i][1]);
		xModel.upgradePer[0][1][1] = atoi(bData[i][2]);
		xModel.upgradePer[0][2][1] = atoi(bData[i][3]);
		xModel.upgradePer[0][3][1] = atoi(bData[i][4]);
		xModel.upgradePer[0][4][1] = atoi(bData[i][5]);
		xModel.upgradePer[1][0][1] = atoi(bData[i][6]);
		xModel.upgradePer[1][1][1] = atoi(bData[i][7]);
		xModel.upgradePer[1][2][1] = atoi(bData[i][8]);
		xModel.upgradePer[1][3][1] = atoi(bData[i][9]);
		xModel.upgradePer[1][4][1] = atoi(bData[i][10]);
		i = 47;
		xModel.upgradePer[0][0][2] = atoi(bData[i][1]);
		xModel.upgradePer[0][1][2] = atoi(bData[i][2]);
		xModel.upgradePer[0][2][2] = atoi(bData[i][3]);
		xModel.upgradePer[0][3][2] = atoi(bData[i][4]);
		xModel.upgradePer[0][4][2] = atoi(bData[i][5]);
		xModel.upgradePer[1][0][2] = atoi(bData[i][6]);
		xModel.upgradePer[1][1][2] = atoi(bData[i][7]);
		xModel.upgradePer[1][2][2] = atoi(bData[i][8]);
		xModel.upgradePer[1][3][2] = atoi(bData[i][9]);
		xModel.upgradePer[1][4][2] = atoi(bData[i][10]);
		i = 48;
		xModel.upgradePer[0][0][3] = atoi(bData[i][1]);
		xModel.upgradePer[0][1][3] = atoi(bData[i][2]);
		xModel.upgradePer[0][2][3] = atoi(bData[i][3]);
		xModel.upgradePer[0][3][3] = atoi(bData[i][4]);
		xModel.upgradePer[0][4][3] = atoi(bData[i][5]);
		xModel.upgradePer[1][0][3] = atoi(bData[i][6]);
		xModel.upgradePer[1][1][3] = atoi(bData[i][7]);
		xModel.upgradePer[1][2][3] = atoi(bData[i][8]);
		xModel.upgradePer[1][3][3] = atoi(bData[i][9]);
		xModel.upgradePer[1][4][3] = atoi(bData[i][10]);
		i = 49;
		//가격
		xModel.upgradePrice[0][0] = atoi(bData[i][1]);
		xModel.upgradePrice[0][1] = atoi(bData[i][2]);
		xModel.upgradePrice[0][2] = atoi(bData[i][3]);
		xModel.upgradePrice[0][3] = atoi(bData[i][4]);
		xModel.upgradePrice[0][4] = atoi(bData[i][5]);
		xModel.upgradePrice[1][0] = atoi(bData[i][6]);
		xModel.upgradePrice[1][1] = atoi(bData[i][7]);
		xModel.upgradePrice[1][2] = atoi(bData[i][8]);
		xModel.upgradePrice[1][3] = atoi(bData[i][9]);
		xModel.upgradePrice[1][4] = atoi(bData[i][10]);
			
		i = 51;
		//int upgradePrice[냐등급][업그레이드단계][재료등급]
		xModel.upgradePer[2][0][0] = atoi(bData[i][1]);
		xModel.upgradePer[2][1][0] = atoi(bData[i][2]);
		xModel.upgradePer[2][2][0] = atoi(bData[i][3]);
		xModel.upgradePer[2][3][0] = atoi(bData[i][4]);
		xModel.upgradePer[2][4][0] = atoi(bData[i][5]);
		xModel.upgradePer[3][0][0] = atoi(bData[i][6]);
		xModel.upgradePer[3][1][0] = atoi(bData[i][7]);
		xModel.upgradePer[3][2][0] = atoi(bData[i][8]);
		xModel.upgradePer[3][3][0] = atoi(bData[i][9]);
		xModel.upgradePer[3][4][0] = atoi(bData[i][10]);
		i = 52;
		xModel.upgradePer[2][0][1] = atoi(bData[i][1]);
		xModel.upgradePer[2][1][1] = atoi(bData[i][2]);
		xModel.upgradePer[2][2][1] = atoi(bData[i][3]);
		xModel.upgradePer[2][3][1] = atoi(bData[i][4]);
		xModel.upgradePer[2][4][1] = atoi(bData[i][5]);
		xModel.upgradePer[3][0][1] = atoi(bData[i][6]);
		xModel.upgradePer[3][1][1] = atoi(bData[i][7]);
		xModel.upgradePer[3][2][1] = atoi(bData[i][8]);
		xModel.upgradePer[3][3][1] = atoi(bData[i][9]);
		xModel.upgradePer[3][4][1] = atoi(bData[i][10]);
		i = 53;
		xModel.upgradePer[2][0][2] = atoi(bData[i][1]);
		xModel.upgradePer[2][1][2] = atoi(bData[i][2]);
		xModel.upgradePer[2][2][2] = atoi(bData[i][3]);
		xModel.upgradePer[2][3][2] = atoi(bData[i][4]);
		xModel.upgradePer[2][4][2] = atoi(bData[i][5]);
		xModel.upgradePer[3][0][2] = atoi(bData[i][6]);
		xModel.upgradePer[3][1][2] = atoi(bData[i][7]);
		xModel.upgradePer[3][2][2] = atoi(bData[i][8]);
		xModel.upgradePer[3][3][2] = atoi(bData[i][9]);
		xModel.upgradePer[3][4][2] = atoi(bData[i][10]);
      
        i = 54;
		xModel.upgradePer[2][0][3] = atoi(bData[i][1]);
		xModel.upgradePer[2][1][3] = atoi(bData[i][2]);
		xModel.upgradePer[2][2][3] = atoi(bData[i][3]);
		xModel.upgradePer[2][3][3] = atoi(bData[i][4]);
		xModel.upgradePer[2][4][3] = atoi(bData[i][5]);
		xModel.upgradePer[3][0][3] = atoi(bData[i][6]);
		xModel.upgradePer[3][1][3] = atoi(bData[i][7]);
		xModel.upgradePer[3][2][3] = atoi(bData[i][8]);
		xModel.upgradePer[3][3][3] = atoi(bData[i][9]);
		xModel.upgradePer[3][4][3] = atoi(bData[i][10]);
       
        xModel.upgradePer[4][0][4] = 100;
        xModel.upgradePer[4][1][4] = 100;
        xModel.upgradePer[4][2][4] = 100;
        xModel.upgradePer[4][3][4] = 100;
        xModel.upgradePer[4][4][4] = 100;
        i = 55;
		//가격
		xModel.upgradePrice[2][0] = atoi(bData[i][1]);
		xModel.upgradePrice[2][1] = atoi(bData[i][2]);
		xModel.upgradePrice[2][2] = atoi(bData[i][3]);
		xModel.upgradePrice[2][3] = atoi(bData[i][4]);
		xModel.upgradePrice[2][4] = atoi(bData[i][5]);
		xModel.upgradePrice[3][0] = atoi(bData[i][6]);
		xModel.upgradePrice[3][1] = atoi(bData[i][7]);
		xModel.upgradePrice[3][2] = atoi(bData[i][8]);
		xModel.upgradePrice[3][3] = atoi(bData[i][9]);
		xModel.upgradePrice[3][4] = atoi(bData[i][10]);
       
		/////////////////////
		//모델 업그레이드 확률 및 가격
		i = 57;
		xModel.mixPer[0] = atoi(bData[i][1]);
		xModel.mixPer[1] = atoi(bData[i][2]);
		xModel.mixPer[2] = atoi(bData[i][3]);
        xModel.mixPer[3] = atoi(bData[i][4]);
        
        
		
        i = 58;
		xModel.mixPrice[0] = atoi(bData[i][1]);
		xModel.mixPrice[1] = atoi(bData[i][2]);
		xModel.mixPrice[2] = atoi(bData[i][3]);
        xModel.mixPrice[3] = atoi(bData[i][4]);
		/////////////////////
		/////////////////////
		//퀘스트잠금
		i = 60;
		xLock.mainQuestNum[LOCK_TYPE_HANGER] = atoi(bData[i][1]);
		xLock.mainQuestNum[LOCK_TYPE_SHOWWINDOW] = atoi(bData[i][2]);
		xLock.mainQuestNum[LOCK_TYPE_CANDY] = atoi(bData[i][3]);
		xLock.mainQuestNum[LOCK_TYPE_ACCESSORY] = atoi(bData[i][4]);
		xLock.mainQuestNum[LOCK_TYPE_MODEL] = atoi(bData[i][5]);
		xLock.mainQuestNum[LOCK_TYPE_ORDER] = atoi(bData[i][6]);
		xLock.mainQuestNum[LOCK_TYPE_TREND] = atoi(bData[i][7]);
		xLock.mainQuestNum[LOCK_TYPE_FASHIONSHOW] = atoi(bData[i][8]);
		
						
			
		xCalendar.isHackingCheck = atoi(bData[i][9]) == 0?FALSE:TRUE;
		xWorldMap.is5RocksHackingLog = atoi(bData[i][10]) == 0?FALSE:TRUE;
		xWorldMap.hackingTimeSec = atoi(bData[i][11]);
            
            
            
			
			
		/////////////////////
		//소모
		i = 62;
		initSecurity(&xMiniGame.userTired, atoi(bData[i][1]));		//미니게임 사용갯수
		initSecurity(&xFashionShow.userTired, atoi(bData[i][2]));	//패션쇼 사용갯수
		//////////////////////
			
			
		/////////////////////
		//카카오톡 소셜피드
		i = 64;
		xKakaoData.socialBonusHelp = atoi(bData[i][1]);
		xKakaoData.socialBonusOrderSelectItem = atoi(bData[i][2]);
		xKakaoData.socialBonusCarStorage = atoi(bData[i][3]);
		//////////////////////
			
			
		/////////////////////
		//엘리스쇼크
		i = 66;
		xWorldMap.isAliceShockOpen = atoi(bData[i][1])==0?FALSE:TRUE;
		xWorldMap.isAliceShockOpen = FALSE;
		//////////////////////
			
		/////////////////////
		//이미지로딩
		i = 68;
		xMainMenu.totalLoadingImg = 0;
		if(atoi(bData[i][1])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 0;
		if(atoi(bData[i][2])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 1;
		if(atoi(bData[i][3])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 2;
		if(atoi(bData[i][4])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 3;
		if(atoi(bData[i][5])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 4;
		if(atoi(bData[i][6])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 5;
		if(atoi(bData[i][7])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 6;
		if(atoi(bData[i][8])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 7;
		if(atoi(bData[i][9])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 8;
		if(atoi(bData[i][10])==1)
			xMainMenu.loadingImgSlot[xMainMenu.totalLoadingImg++] = 9;
		//////////////////////
		
			
		/////////////////////
		//버프이벤트
		i = 70;
		xBuff.isOpen[0] = atoi(bData[i][1])==1?TRUE:FALSE;
		xBuff.isOpen[1] = atoi(bData[i][2])==1?TRUE:FALSE;
		xBuff.isOpen[2] = atoi(bData[i][3])==1?TRUE:FALSE;
		xBuff.isOpen[3] = atoi(bData[i][4])==1?TRUE:FALSE;
		xG9.isOpen = FALSE;
			
			
		xWorldMap.isOpen_CASH10000 = atoi(bData[i][6])==1?TRUE:FALSE;
		xWorldMap.isOpen_Tnk = atoi(bData[i][7])==1?TRUE:FALSE;
			
			

            
            
									
		i = 71;
		xBuff.bonusPer[0] = atoi(bData[i][1]);
		xBuff.bonusPer[1] = atoi(bData[i][2]);
		xBuff.bonusPer[2] = atoi(bData[i][3]);
		xBuff.bonusPer[3] = atoi(bData[i][4]);
			
		i = 72;
		xBuff.startYY = atoi(bData[i][1]);
		xBuff.startMM = atoi(bData[i][2]);
		xBuff.startDD = atoi(bData[i][3]);
		xBuff.startHH = atoi(bData[i][4]);
		i = 73;
		xBuff.endYY = atoi(bData[i][1]);
		xBuff.endMM = atoi(bData[i][2]);
		xBuff.endDD = atoi(bData[i][3]);
		xBuff.endHH = atoi(bData[i][4]);
		//////////////////////
								
		//프리미엄슬롯세일
		i = 75;
		xProductionMenu.isSlotSaleEventOpen = atoi(bData[i][7])==1?TRUE:FALSE;
			
		initSecurity(&xProductionMenu.openCashOri[1][0], atoi(bData[i][1]));
		initSecurity(&xProductionMenu.openCashOri[1][1], atoi(bData[i][2]));
		initSecurity(&xProductionMenu.openCashOri[1][2], atoi(bData[i][3]));
		initSecurity(&xProductionMenu.openCashOri[1][3], atoi(bData[i][4]));
		initSecurity(&xProductionMenu.openCashOri[1][4], atoi(bData[i][5]));
		initSecurity(&xProductionMenu.openCashOri[1][5], atoi(bData[i][6]));
		
		i = 76;
		initSecurity(&xProductionMenu.openCash[1][0], atoi(bData[i][1]));
		initSecurity(&xProductionMenu.openCash[1][1], atoi(bData[i][2]));
		initSecurity(&xProductionMenu.openCash[1][2], atoi(bData[i][3]));
		initSecurity(&xProductionMenu.openCash[1][3], atoi(bData[i][4]));
		initSecurity(&xProductionMenu.openCash[1][4], atoi(bData[i][5]));
		initSecurity(&xProductionMenu.openCash[1][5], atoi(bData[i][6]));
				
		if(xProductionMenu.isSlotSaleEventOpen == FALSE)
		{
			initSecurity(&xProductionMenu.openCash[1][0], xProductionMenu.openCashOri[1][0].oriData);
			initSecurity(&xProductionMenu.openCash[1][1], xProductionMenu.openCashOri[1][1].oriData);
			initSecurity(&xProductionMenu.openCash[1][2], xProductionMenu.openCashOri[1][2].oriData);
			initSecurity(&xProductionMenu.openCash[1][3], xProductionMenu.openCashOri[1][3].oriData);
			initSecurity(&xProductionMenu.openCash[1][4], xProductionMenu.openCashOri[1][4].oriData);
			initSecurity(&xProductionMenu.openCash[1][5], xProductionMenu.openCashOri[1][5].oriData);
		}
			
		i = 77;
		xProductionMenu.startYY = atoi(bData[i][1]);
		xProductionMenu.startMM = atoi(bData[i][2]);
		xProductionMenu.startDD = atoi(bData[i][3]);
		xProductionMenu.startHH = atoi(bData[i][4]);
		i = 78;
		xProductionMenu.endYY = atoi(bData[i][1]);
		xProductionMenu.endMM = atoi(bData[i][2]);
		xProductionMenu.endDD = atoi(bData[i][3]);
		xProductionMenu.endHH = atoi(bData[i][4]);
		/////////////////////
        i = 80;
        xMileageShop.isOpen = atoi(bData[i][0]) == 0?false:true;
        xMileageShop.prcChs = atoi(bData[i][1]);
        dataVer = atoi(bData[i][2]);
        xHotDeal.isOpen = atoi(bData[i][3]) == 0?false:true;
        xHotDeal.hotDealTimeMax = atoi(bData[i][4]);
            
        sprintf(xHotDeal.strInitInfo, "%s",bData[i][5]);
        xFashionShow.maxCount = atoi(bData[i][6]);

        xHotDeal.openLv = atoi(bData[i][7]);
            
        
        xRival.maxCount = atoi(bData[i][8]);
        xRival.openLv = atoi(bData[i][9]);
        xRival.openMain = atoi(bData[i][10]);
        xWorldMap.reviewQuestNum = atoi(bData[i][11]);
            
            
        
            
            
        i = 82;
        xMileageShop.cashBonus[0] = atoi(bData[i][0]);
        xMileageShop.cashBonus[1] = atoi(bData[i][1]);
        xMileageShop.cashBonus[2] = atoi(bData[i][2]);
        xMileageShop.cashBonus[3] = atoi(bData[i][3]);
        xMileageShop.cashBonus[4] = atoi(bData[i][4]);
        xMileageShop.cashBonus[5] = atoi(bData[i][5]);
        xMileageShop.cashBonus[6] = atoi(bData[i][6]);

        i = 84;
        sprintf(strTempS, "캔디 %d개",atoi(bData[i][0]));
        setPremiumData(4,1,atoi(bData[i][1])	,atoi(bData[i][0]),strTempS);
        sprintf(strTempS, "캔디 %d개",atoi(bData[i][2]));
        setPremiumData(5,1,atoi(bData[i][3])	,atoi(bData[i][2]),strTempS);
        sprintf(strTempS, "캔디 %d개",atoi(bData[i][4]));
        setPremiumData(6,1,atoi(bData[i][5])	,atoi(bData[i][4]),strTempS);

        xPrePay.price = atoi(bData[i][6]);
        xPrePay.pointDay = atoi(bData[i][9]);
        i = 86;
    
        xHotDeal.castingPrice[0] = atoi(bData[i][1]);
        xHotDeal.castingPrice[1] = atoi(bData[i][2]);
        xHotDeal.castingPrice[2] = atoi(bData[i][3]);
        xHotDeal.castingPrice[3] = atoi(bData[i][4]);
        xHotDeal.castingPrice[4] = atoi(bData[i][5]);
        
        i = 87;
        xHotDeal.castingPer[0] = atoi(bData[i][1]);
        xHotDeal.castingPer[1] = atoi(bData[i][2]);
        xHotDeal.castingPer[2] = atoi(bData[i][3]);
        xHotDeal.castingPer[3] = atoi(bData[i][4]);
        xHotDeal.castingPer[4] = atoi(bData[i][5]);
        
        i = 89;
        xAmulet.xAmuletPage[0].pagePrice = 0;
        xAmulet.xAmuletPage[1].pagePrice = atoi(bData[i][1]);
        xAmulet.xAmuletPage[2].pagePrice = atoi(bData[i][2]);
                        
        xAmulet.isOpen = atoi(bData[i][0]) == 0?false:true;
            
        i = 91;
        xClub.makePrice = atoi(bData[i][0]);
        xClub.fashionWeekPlayCountMax = atoi(bData[i][2]);
        xClub.lvLimit = atoi(bData[i][3]);
        xClub.isOpen = atoi(bData[i][4]) == 0?false:true;
            
        xFashionWeek.isOpen = atoi(bData[i][5]) == 0?false:true;

        xPang.PANG_TIME_MAX = atoi(bData[i][6]);
        xPang_SOLO.PANG_TIME_MAX = atoi(bData[i][6]);

            
        xPang.DEFAULTSCORE = atoi(bData[i][7]);
        xPang_SOLO.DEFAULTSCORE = atoi(bData[i][7]);
    
            
            
            
        ////////////////패션쇼보상
        i = 93;
        xFashionWeek.rankGiftLook[0] = atoi(bData[i][1]);
        xFashionWeek.rankGiftLook[1] = atoi(bData[i][2]);
        xFashionWeek.rankGiftLook[2] = atoi(bData[i][3]);
        xFashionWeek.rankGiftLook[3] = atoi(bData[i][4]);
        xFashionWeek.rankGiftLook[4] = atoi(bData[i][5]);
        xFashionWeek.rankGiftLook[5] = atoi(bData[i][6]);
        
        /////////////////////
        ////////////////패션쇼보상
        i = 95;
        xFashionWeek.rankGiftLook[6] = atoi(bData[i][1]);
        xFashionWeek.rankGiftLook[7] = atoi(bData[i][2]);
        xFashionWeek.rankGiftLook[8] = atoi(bData[i][3]);
        xFashionWeek.rankGiftLook[9] = atoi(bData[i][4]);
        xFashionWeek.rankGiftLook[10] = atoi(bData[i][5]);
        xFashionWeek.rankGiftLook[11] = atoi(bData[i][6]);
        
        ////////////////////
        ////////////////클럽
        i=97;
        xClub.xDonation[0].DonationWeath=atoi(bData[i][3]);
        xClub.xDonation[1].DonationWeath=atoi(bData[i][4]);
        xClub.xDonation[0].point = atoi(bData[i][5]);
        xClub.xDonation[1].point = atoi(bData[i][6]);
        xClub.xDonation[0].maxDonationCount=atoi(bData[i][7]);
        xClub.xDonation[1].maxDonationCount=atoi(bData[i][8]);
        xClubShop.OnOff=atoi(bData[i][9]);
        
        ////////////////////
        ////////////////생산기
        i=99;
        xFormer.OnOff=atoi(bData[i][0]);
        
       
        break;
    case EXCEL_PS_PACKAGE:
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int code = atoi(bData[i][0]);
            sprintf(xPackageData[code].strName, "%s",bData[i][3]);
            xPackageData[code].price = atoi(bData[i][4]);
            xPackageData[code].lv = atoi(bData[i][7]);
            xPackageData[code].max = atoi(bData[i][8]);
            xPackageData[code].isUiShow = atoi(bData[i][9])==0?false:true;
            sprintf(xPackageData[code].strOneStoreIapId, "%s",bData[i][10]);
        }
        break;
	case EXCEL_PS_FASHIONSHOW:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			xFashionShowServer[i-1].trend[0] = atoi(bData[i][1]);
			xFashionShowServer[i-1].trend[1] = atoi(bData[i][2]);
			xFashionShowServer[i-1].trend[2] = atoi(bData[i][3]);
			xFashionShowServer[i-1].concept[0] = atoi(bData[i][4]);
			xFashionShowServer[i-1].concept[1] = atoi(bData[i][5]);
			
			xFashionShowServer[i-1].color[0] = atoi(bData[i][6]);
			xFashionShowServer[i-1].color[1] = atoi(bData[i][7]);
			xFashionShowServer[i-1].sex = atoi(bData[i][8]);
			xFashionShowServer[i-1].inOut = atoi(bData[i][9]);
			xFashionShowServer[i-1].layeredMin = atoi(bData[i][10]);
			xFashionShowServer[i-1].layeredMax = atoi(bData[i][11]);
		}
		break;
	case EXCEL_PS_DRESSSECTION:
		xTrend.totalParser = 0;
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			xTrend.parserMakeTime[xTrend.totalParser] = atoi(bData[i][1]);	//제작시간
			xTrend.parserPer[xTrend.totalParser] = atoi(bData[i][2]);		//배율
			xTrend.parserTime[xTrend.totalParser] = atoi(bData[i][3]);		//제한시간
			xTrend.parserCheckPer[xTrend.totalParser] = atoi(bData[i][4]);//확률
			xTrend.totalParser++;
		}
		break;
	case EXCEL_PS_ACCESSBONUS:
		colsMax +=1;
		/*
		 #define ACCESSBONUS_TYPE_GOLD		0
		 #define ACCESSBONUS_TYPE_LOOK		1
		 #define ACCESSBONUS_TYPE_CANDY		2
		 #define ACCESSBONUS_TYPE_MODEL		3
		 #define ACCESSBONUS_TYPE_TREND		4
		 
		 골드		0-[수치]
		 룩		1-[수치]
		 캔디		2-[수치]
		 모델		3-[0]골드[1]유료[2]a~s급
		 유행		4-[0]의상[2]잡화
		 */
		for(i=1;i<colsMax;i++)
		{
			initAccessBonus(i-1,atoi(bData[i][1]),atoi(bData[i][2]),atoi(bData[i][3]));
		}
		break;
	case EXCEL_PS_EXPANDDATA:
		colsMax +=1;
		for(i=1;i<colsMax;i++)
		{
			sprintf(xExternalWallData.strName[i-1], "%s",bData[i][1]);
			xExternalWallData.price[i-1] = atoi(bData[i][2]);
			xExternalWallData.priceType[i-1] = atoi(bData[i][3]);
		}
		break;
	case EXCEL_PS_EXPANDLIST:
		colsMax +=1;
		xExternalWall.totalNum = 0;
		for(i=1;i<colsMax;i++)
		{
			xExternalWall.listSlot[xExternalWall.totalNum++] = atoi(bData[i][2]);
		}
		break;
    case EXCEL_PS_MILEAGE:
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int type = atoi(bData[i][0])/10000;
            int listNum = atoi(bData[i][0])%10000;
            
            sprintf(xMileageData.xSlot[type][listNum].strNameLine, "%s",bData[i][1]);
            xMileageData.xSlot[type][listNum].event = atoi(bData[i][2]);
            xMileageData.xSlot[type][listNum].sort = atoi(bData[i][3]);
            xMileageData.xSlot[type][listNum].price = atoi(bData[i][4]);
            xMileageData.xSlot[type][listNum].maxCount = atoi(bData[i][5]);
            xMileageData.xSlot[type][listNum].state = atoi(bData[i][6]);
            sprintf(xMileageData.xSlot[type][listNum].strName, "%s",bData[i][7]);
            sprintf(xMileageData.xSlot[type][listNum].strUrl, "%s",bData[i][8]);
                        
            for(int f=0;f<strlen(xMileageData.xSlot[type][listNum].strUrl);f++)
            {
                if(xMileageData.xSlot[type][listNum].strUrl[f] == '?')
                    xMileageData.xSlot[type][listNum].strUrl[f] = '/';
            }
        }
        break;
    case EXCEL_PS_EVENTTYPE:
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int questType = atoi(bData[i][0]);
            xEventQuest.xMain[questType].giftType = atoi(bData[i][3]);
            xEventQuest.xMain[questType].giftValue = atoi(bData[i][4]);
            
            int ymd = atoi(bData[i][11]);
            xEventQuest.xMain[questType].startYear = ymd/10000;
            xEventQuest.xMain[questType].startMonth = (ymd/100%100);
            xEventQuest.xMain[questType].startDay = ymd%100;
            xEventQuest.xMain[questType].startHour = atoi(bData[i][12]);
            ymd = atoi(bData[i][13]);
            xEventQuest.xMain[questType].endYear = ymd/10000;
            xEventQuest.xMain[questType].endMonth = (ymd/100%100);
            xEventQuest.xMain[questType].endDay = ymd%100;
            xEventQuest.xMain[questType].endHour = atoi(bData[i][14]);

        }
        break;
    case EXCEL_PS_EVENTQUEST:
        colsMax +=1;
         
        for(int k=0;k<EVENTQUESTMAX;k++)
            xEventQuest.totalNum[k] = 0;
            
        for(i=1;i<colsMax;i++)
        {
            int questType = atoi(bData[i][0])/1000;
            int questList = atoi(bData[i][0])%1000;

        
            
            xEventQuest.xData[questType][questList].checkType = atoi(bData[i][2]);
            xEventQuest.xData[questType][questList].checkCode = atoi(bData[i][3]);
            
            
            xEventQuest.xData[questType][questList].checkCodeSub = xEventQuest.xData[questType][questList].checkCode/1000;
            xEventQuest.xData[questType][questList].checkMax = xEventQuest.xData[questType][questList].checkCode%1000;
            if(xEventQuest.xData[questType][questList].checkMax == -1)
                xEventQuest.xData[questType][questList].checkMax = 1;

            switch(xEventQuest.xData[questType][questList].checkType)
            {
            case 0:
            case 19:
            case 34:
            case 20:
            case 54:// xx등급 이상 모델 캐스팅하기
                xEventQuest.xData[questType][questList].checkMax = 1;
                break;
            case 85://	(특정의상카테고리)만 이용해 골드 x 벌기 카테고리/99999
                xEventQuest.xData[questType][questList].checkMax = xEventQuest.xData[questType][questList].checkCode%100000;
                xEventQuest.xData[questType][questList].checkCode = xEventQuest.xData[questType][questList].checkCode/100000;
                break;
            case 1:
            case 2:
            case 5:
            case 6:
            case 21:
            case 35:
            case 42://	주문된 %s 진열하기
            case 84://	xx 테마 인테리어 구매하기0 테마번호/999
            case 88://	선호도 x% 상태로 의상 x벌 판매하기
                xEventQuest.xData[questType][questList].checkCode = xEventQuest.xData[questType][questList].checkCode/1000;
                break;
            case 11:	//명성도
            case 12:	//골드
            case 17:	//칭호 갯수
            case 36:	//얼마이상구매
            case 37://	판매 단가 %d원 이상 의상 주문
            case 38://	주문수량 %d벌 이상 의상 주문
            case 39://	명성도 %d 이상 의상 구매
            case 40://	의상 라이센스 %d개 이상 보유하기
            case 46://	패션쇼 %d점 달성하기
            case 48://	마네킹 레이어드 %d회 달성하기
            case 51://	여자 모델 %d명 피팅하기
            case 52://	남자 모델 %d명 피팅하기
            case 55://	모델 %d명 보유하기
            case 56://	선호도 %d%% 달성하기
            case 57://	캔디 모으기
            case 69://	남자마네킹 레이어드 %d회 달성하기(%d/%d)
            case 78://	모델 활동으로 %d원 벌기(%d/%d)
            case 79://	모델 활동으로 경험치 %d획득하기(%d/%d)
            case 87://	캔디머신으로 x원 모으기
            case 95://	남자 모델만 이용해 패션쇼 xx점 달성하기
            case 96://	여자 모델만 이용해 패션쇼 xx점 달성하기
                xEventQuest.xData[questType][questList].checkMax = xEventQuest.xData[questType][questList].checkCode;
                break;
            case 104:
                xEventQuest.xData[questType][questList].checkMax = xEventQuest.xData[questType][questList].checkCode;
                break;
            }
        
            
            
            
            
            xEventQuest.xData[questType][questList].giftType = atoi(bData[i][4]);
            switch(xEventQuest.xData[questType][questList].giftType)
            {
            case 3:	//의상
                
                xEventQuest.xData[questType][questList].giftValue = xEventQuest.xData[questType][questList].giftMax/1000;
                xEventQuest.xData[questType][questList].giftMax = xEventQuest.xData[questType][questList].giftMax%1000;
                break;
            case 4:	//인테리어
            case 5:	//자동차
                xEventQuest.xData[questType][questList].giftValue = xEventQuest.xData[questType][questList].giftMax;
                break;
            }
            xEventQuest.xData[questType][questList].giftValue = atoi(bData[i][5]);
            xEventQuest.totalNum[questType]++;
        }
        break;
    case EXCEL_PS_HOTDEAL:
        colsMax +=1;
            
        for(int k=0;k<10;k++)
        {
            for(int z=0;z<HOTDEALSLOTMAX;z++)
            {
                xHotDeal.xData[k][z].itemType = 0;
                xHotDeal.xData[k][z].itemCode = DONT;
            }
        }
            
        for(i=1;i<colsMax;i++)
        {
            int tempCode = atoi(bData[i][0]);
            int hotDealCode = tempCode/100;
            int hotDealList = tempCode%100;
            
            xHotDeal.xData[hotDealCode][hotDealList].itemType = atoi(bData[i][1]);
            xHotDeal.xData[hotDealCode][hotDealList].itemCode = atoi(bData[i][2]);
            xHotDeal.xData[hotDealCode][hotDealList].perPer[0] = atoi(bData[i][3]);
            xHotDeal.xData[hotDealCode][hotDealList].perPer[1] = atoi(bData[i][4]);
            xHotDeal.xData[hotDealCode][hotDealList].perPer[2] = atoi(bData[i][5]);
            xHotDeal.xData[hotDealCode][hotDealList].perPer[3] = atoi(bData[i][6]);
            xHotDeal.xData[hotDealCode][hotDealList].perPer[4] = atoi(bData[i][7]);
            
            xHotDeal.xData[hotDealCode][hotDealList].salePer[0] = atoi(bData[i][8]);
            xHotDeal.xData[hotDealCode][hotDealList].salePer[1] = atoi(bData[i][9]);
            xHotDeal.xData[hotDealCode][hotDealList].salePer[2] = atoi(bData[i][10]);
            xHotDeal.xData[hotDealCode][hotDealList].salePer[3] = atoi(bData[i][11]);
            xHotDeal.xData[hotDealCode][hotDealList].salePer[4] = atoi(bData[i][12]);
            
            
            xHotDeal.xData[hotDealCode][hotDealList].filteringPer[0] = atoi(bData[i][13]);
            xHotDeal.xData[hotDealCode][hotDealList].filteringPer[1] = atoi(bData[i][14]);
            xHotDeal.xData[hotDealCode][hotDealList].filteringPer[2] = atoi(bData[i][15]);
            
            
        }
        break;
    case EXCEL_PS_COLLECTION:
        xJewelQuest.totalData = 0;
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int code = atoi(bData[i][0]);
            
            sprintf(xJewelQuest.xData[code].strName, "%s",bData[i][1]);
            xJewelQuest.xData[code].checkType = atoi(bData[i][2]);
            xJewelQuest.xData[code].checkCode = atoi(bData[i][3]);
            xJewelQuest.xData[code].checkMax = atoi(bData[i][4]);
            xJewelQuest.xData[code].jewelCode = atoi(bData[i][5]);
            
            xJewelQuest.xData[code].giftType[0] = atoi(bData[i][6]);
            xJewelQuest.xData[code].giftValue[0] = atoi(bData[i][7]);
            xJewelQuest.xData[code].giftType[1] = atoi(bData[i][8]);
            xJewelQuest.xData[code].giftValue[1] = atoi(bData[i][9]);            
            xJewelQuest.xData[code].openQuestCode = atoi(bData[i][10]);
            
            xJewelQuest.totalData++;
        }
        break;
    case EXCEL_PS_JEWEL:
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int code = atoi(bData[i][0]);
            
            sprintf(xJewel.xData[code].strName, "%s",bData[i][1]);
            xJewel.xData[code].grade = atoi(bData[i][2]);
            xJewel.xData[code].size = atoi(bData[i][3]);
            xJewel.xData[code].buffType = atoi(bData[i][4]);
            xJewel.xData[code].buffValue = atoi(bData[i][5]);
        }
        break;
    case EXCEL_PS_AMULET:
        xAmulet.totalAmulet = 0;
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int code = atoi(bData[i][0]);
            sprintf(xAmulet.xData[code].strName, "%s",bData[i][1]);
            
            xAmulet.xData[code].lv = atoi(bData[i][2]);
            xAmulet.xData[code].priceType = atoi(bData[i][3]);
            xAmulet.xData[code].priceValue = atoi(bData[i][4]);
            xAmulet.xData[code].buffType = atoi(bData[i][5]);
            xAmulet.xData[code].buffValue = atoi(bData[i][6]);
            xAmulet.totalAmulet++;
        }            
        break;
    case EXCEL_PS_AMULETXY:
        for(int k = 0;k<AMULETDATAMAX;k++)
        {
            xAmulet.xData[k].totalSocket = 0;
        }
            
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int code = atoi(bData[i][0])/100;
            int socket = atoi(bData[i][0])%100;
            xAmulet.xData[code].xSocket[socket].size = atoi(bData[i][1]);
            xAmulet.xData[code].xSocket[socket].x = atoi(bData[i][2]);
            xAmulet.xData[code].xSocket[socket].y = atoi(bData[i][3]);
            xAmulet.xData[code].xSocket[socket].uiX = atoi(bData[i][4]);
            xAmulet.xData[code].xSocket[socket].uiY = atoi(bData[i][5]);
            xAmulet.xData[code].totalSocket++;
        }
        break;
    case EXCEL_PS_RIVAL:
        xRival.totalWorldMap = 0;
            
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int tempCode = atoi(bData[i][0]);
            int rivalMain = tempCode/100;
            int rivalDetail = tempCode%100;
            

            sprintf(xRival.xData[rivalMain][rivalDetail].strNpcName, "%s",bData[i][1]);
            sprintf(xRival.xData[rivalMain][rivalDetail].strInfo, "%s",bData[i][2]);
            xRival.xData[rivalMain][rivalDetail].limitTime = atoi(bData[i][3]);
            
            
            xRival.xData[rivalMain][rivalDetail].checkMax[0] = atoi(bData[i][4]);
            xRival.xData[rivalMain][rivalDetail].checkMax[1] = atoi(bData[i][5]);
            xRival.xData[rivalMain][rivalDetail].checkMax[2] = atoi(bData[i][6]);
            xRival.xData[rivalMain][rivalDetail].checkMax[3] = atoi(bData[i][7]);
            xRival.xData[rivalMain][rivalDetail].checkMax[4] = atoi(bData[i][8]);
            xRival.xData[rivalMain][rivalDetail].checkMax[5] = atoi(bData[i][9]);
            xRival.xData[rivalMain][rivalDetail].checkMax[6] = atoi(bData[i][10]);
            xRival.xData[rivalMain][rivalDetail].checkMax[7] = atoi(bData[i][11]);

            xRival.xData[rivalMain][rivalDetail].giftType[0] = atoi(bData[i][12]);
            xRival.xData[rivalMain][rivalDetail].giftValue[0] = atoi(bData[i][13]);
            xRival.xData[rivalMain][rivalDetail].giftType[1] = atoi(bData[i][14]);
            xRival.xData[rivalMain][rivalDetail].giftValue[1] = atoi(bData[i][15]);
            xRival.xData[rivalMain][rivalDetail].giftType[2] = atoi(bData[i][16]);
            xRival.xData[rivalMain][rivalDetail].giftValue[2] = atoi(bData[i][17]);
            
            xRival.xData[rivalMain][rivalDetail].buffSell = atoi(bData[i][18]);
            xRival.xData[rivalMain][rivalDetail].buffExp = atoi(bData[i][19]);
            xRival.xData[rivalMain][rivalDetail].buffFame = atoi(bData[i][20]);
            
            xRival.xData[rivalMain][rivalDetail].npcImgNum = atoi(bData[i][21]);
            xRival.xData[rivalMain][rivalDetail].buildingImgNum = atoi(bData[i][22]);
                                    
            if(xRival.totalWorldMap < rivalMain+1)
                xRival.totalWorldMap = rivalMain+1;
        }
        break;
    case EXCEL_PS_CLUB:
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int lvTemp = atoi(bData[i][0]);
            
            xClub.xData[lvTemp].memberMax = atoi(bData[i][1]);
            xClub.xData[lvTemp].expMax = atoi(bData[i][2]);
            xClub.xData[lvTemp].layeredMax = atoi(bData[i][3]);
        }
        break;
    case EXCEL_PS_CLUBICON:
        xClubIconShop.totalData= 0 ;
        colsMax+=1;
        for(i=1;i<colsMax;i++)
        {
            int Num = atoi(bData[i][0]);
            xClub.xIcon[Num].index=atoi(bData[i][0]);
            xClub.xIcon[Num].clublv=atoi(bData[i][1]);
            xClub.xIcon[Num].coin=atoi(bData[i][2]);
            xClubIconShop.totalData++;
        }
        break;
    case EXCEL_PS_FASHIONWEEKMAKEUP:
        xFashionWeek.totalHairList = 0;
        xFashionWeek.totalFaceList = 0;
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            int type = atoi(bData[i][2]);
            int code = atoi(bData[i][0]);

            switch(type)
            {
            case 0:	//헤어
                xFashionWeek.xHairList[xFashionWeek.totalHairList++].code = code;
                xHairData[code].clubLv = atoi(bData[i][3]);
                xHairData[code].clubPrice = atoi(bData[i][4]);
                xHairData[code].clubScore = atoi(bData[i][5]);
                break;
            case 1:	//얼굴
                xFashionWeek.xFaceList[xFashionWeek.totalFaceList++].code = code;
                xFaceData[code].clubLv = atoi(bData[i][3]);
                xFaceData[code].clubPrice = atoi(bData[i][4]);
                xFaceData[code].clubScore = atoi(bData[i][5]);
                break;
            }
        }
        break;
    case EXCEL_PS_FASHIONWEEKDRESS:
        for(int k=0;k<CATALOGSLOTBMAX;k++)
        {
            xFashionWeek.totalFashionList[k] = 0;
        }
        
        colsMax +=1;
        for(i=1;i<colsMax;i++)
        {
            //(아이템코드)            
            int fashionCode = atoi(bData[i][2]);
            int fashionType = fashionCode/1000;
            int fashionList = fashionCode%1000;

            
            xFashionWeek.xFashionList[fashionType][xFashionWeek.totalFashionList[fashionType]].code = fashionCode;
            xFashionWeek.xFashionList[fashionType][xFashionWeek.totalFashionList[fashionType]].isNew = atoi(bData[i][3]) == 0?FALSE:TRUE;
            xFashionWeek.xFashionList[fashionType][xFashionWeek.totalFashionList[fashionType]].isHot = atoi(bData[i][4]) == 0?FALSE:TRUE;
            xFashionWeek.xFashionList[fashionType][xFashionWeek.totalFashionList[fashionType]].isEvent = atoi(bData[i][5]) == 0?FALSE:TRUE;
            xFashionWeek.totalFashionList[fashionType]++;
            
            xFashionData[fashionType][fashionList].clubLv = atoi(bData[i][6]);
            xFashionData[fashionType][fashionList].clubPrice = atoi(bData[i][7]);
            xFashionData[fashionType][fashionList].clubScore = atoi(bData[i][8]);
            xFashionData[fashionType][fashionList].clubCostMax = atoi(bData[i][9]);
            xFashionData[fashionType][fashionList].clubExp = atoi(bData[i][10]);
        }
        break;
    case EXCEL_PS_CLUBSTORE:
        xClubShop.totalData=colsMax;
        colsMax+=1;
        for(i=1;i<colsMax;i++)
        {
            int Num = atoi(bData[i][0]);
            sprintf(xClubShop.xData[Num].strName, "%s",bData[i][1]);
            xClubShop.xData[Num].clublv=atoi(bData[i][2]);
            xClubShop.xData[Num].coin=atoi(bData[i][3]);
        }
        break;
   
	}
    
	for( i = 0; i < size1; i++)
		for( j = 0; j < size2; j++)
			free(bData[i][j]);
	for( i = 0; i < size1; i++)
		free(bData[i]);
	free(bData);
}

void loadExcelParser(const char* strFileName,M_Boolean isSdCard)
{
	int type = getExcelTypeNum(strFileName);
    loadData(strFileName,isSdCard);
    loadExcelParserByte(type);
}

void loadSpriteData(const char* strFileName,XSPRIT* Xsprit)
{
	
	int i,z;
	int index;
	char strFileSprite[32];
	
	memset(strFileSprite,0,sizeof(strFileSprite));
			
	sprintf(strFileSprite,"%s",strFileName);
	loadData(strFileSprite,FALSE);
			

    
    
    
	index = 0;
	//이미지 갯수 1개 구조체 1:1대응할꺼임 쓸꺼임
	Xsprit->totalImg = getByteToInt(bufData, index);
	index += 4;
	//스프라이트 후 액션번호
	Xsprit->endAction = getByteToInt(bufData, index);
	index += 4;
	//총프레임
	Xsprit->totalFrame = getByteToInt(bufData, index);
	index += 4;
		
	for(i=0;i<Xsprit->totalFrame;i++)
	{
		//방어영역
		index += 4;index += 4;index += 4;index += 4;
		//공격영역
		index += 4;index += 4;index += 4;index += 4;
		//딜레이
		Xsprit->xFrame[i].delay = getByteToInt(bufData, index);
		index += 4;
		//사운드
		Xsprit->xFrame[i].snd = getByteToInt(bufData, index);
		index += 4;		
		//총레이어
		Xsprit->xFrame[i].totalLayer = getByteToInt(bufData, index);
		index += 4;
		
		
		for(z=0;z<Xsprit->xFrame[i].totalLayer;z++)
		{
			//이미지번호
			Xsprit->xFrame[i].xLayer[z].imgNum = getByteToInt(bufData, index);
			
			index += 4;
			//이미지x
			Xsprit->xFrame[i].xLayer[z].imgX = getByteToInt(bufData, index);
			index += 4;
			//이미지y
			Xsprit->xFrame[i].xLayer[z].imgY = getByteToInt(bufData, index);
			index += 4;
			//이미지w
			Xsprit->xFrame[i].xLayer[z].imgW = getByteToInt(bufData, index);
			index += 4;
			//이미지h
			Xsprit->xFrame[i].xLayer[z].imgH = getByteToInt(bufData, index);
			index += 4;
			//드로우x
			Xsprit->xFrame[i].xLayer[z].drawX = getByteToInt(bufData, index);
			index += 4;
			//드로우y
			Xsprit->xFrame[i].xLayer[z].drawY = getByteToInt(bufData, index);
			index += 4;
			//회전
			Xsprit->xFrame[i].xLayer[z].imgRot = getByteToInt(bufData, index);
			index += 4;
			//스케일
			Xsprit->xFrame[i].xLayer[z].imgScale = getByteToInt(bufData, index);
			index += 4;
			//반전
			Xsprit->xFrame[i].xLayer[z].isReverse = bufData[index++];
		}				
	}
    

    
		
	sortSlot[ACT_FRONT][0] = 0;
	sortSlot[ACT_FRONT][1] = 2;
	sortSlot[ACT_FRONT][2] = 1;
	sortSlot[ACT_FRONT][3] = 4;
	sortSlot[ACT_FRONT][4] = 5;
	sortSlot[ACT_FRONT][5] = 6;
	sortSlot[ACT_FRONT][6] = 3;
	sortSlot[ACT_FRONT][7] = 10;
	sortSlot[ACT_FRONT][8] = 11;
	sortSlot[ACT_FRONT][9] = 12;
	sortSlot[ACT_FRONT][10] = 9;
	sortSlot[ACT_FRONT][11] = 7;
	sortSlot[ACT_FRONT][12] = 8;
	sortSlot[ACT_FRONT][13] = 13;
	sortSlot[ACT_FRONT][14] = 14;
	sortSlot[ACT_FRONT][15] = 15;
	sortSlot[ACT_FRONT][16] = 16;
	sortSlot[ACT_FRONT][17] = 18;
	sortSlot[ACT_FRONT][18] = 17;
	
	sortSlot[ACT_BACK][0] = 1;
	sortSlot[ACT_BACK][1] = 2;
	sortSlot[ACT_BACK][2] = 0;
	sortSlot[ACT_BACK][3] = 6;
	sortSlot[ACT_BACK][4] = 3;
	sortSlot[ACT_BACK][5] = 4;
	sortSlot[ACT_BACK][6] = 5;
	sortSlot[ACT_BACK][7] = 11;
	sortSlot[ACT_BACK][8] = 8;
	sortSlot[ACT_BACK][9] = 9;
	sortSlot[ACT_BACK][10] =10;
	sortSlot[ACT_BACK][11] = 7;
	sortSlot[ACT_BACK][12] = 15;
	sortSlot[ACT_BACK][13] = 12;
	sortSlot[ACT_BACK][14] = 13;
	sortSlot[ACT_BACK][15] = 14;
	sortSlot[ACT_BACK][16] = 17;
	sortSlot[ACT_BACK][17] = 18;
	sortSlot[ACT_BACK][18] = 16;
	
	xSpritNpc[NPC_ACT_SONG][ACT_FRONT].isMike = TRUE;
	xSpritNpc[NPC_ACT_GUITAR][ACT_FRONT].isGuitar = TRUE;
	xSpritNpc[NPC_ACT_PHONE][ACT_FRONT].isPhone_Right = TRUE;
	xSpritNpc[NPC_ACT_CLEAN][ACT_BACK].isCleaning = TRUE;
	
	xSpritNpc[NPC_ACT_CHAIR_BOOK][ACT_FRONT].isChairBook = TRUE;
	xSpritNpc[NPC_ACT_CHAIR_COFFEE][ACT_FRONT].isChairCoffee = TRUE;
	xSpritNpc[NPC_ACT_CHAIR_IPAD][ACT_FRONT].isIpad = TRUE;
	xSpritNpc[NPC_ACT_CHAIR_PHONE][ACT_FRONT].isPhone_Left = TRUE;
	
	xSpritNpc[NPC_ACT_PORTER_FITTING][ACT_BACK].isFitting = TRUE;
	
	xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION1][ACT_FRONT].isIpad = TRUE;
	xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION1][ACT_BACK].isIpad = TRUE;
	xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION2][ACT_FRONT].isPhone_Right = TRUE;
	
	xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION0][ACT_FRONT].isPen = TRUE;
	xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION0][ACT_BACK].isPen = TRUE;
	xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION0][ACT_FRONT].isNote = TRUE;
	xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION0][ACT_BACK].isNote = TRUE;	
}

void initSprit(XSPRIT *Xsprit)
{
	Xsprit->nowFrame = -1;
	Xsprit->nowDelay = 0;
}
int prcSprit(XSPRIT *Xsprit ,int *nowDelay,int *nowFrame)
{
	if(++(*nowDelay) >= Xsprit->xFrame[Xsprit->nowFrame].delay)
	{
		++(*nowFrame);
		(*nowDelay) = 0;
	}
	//클때
	if((*nowFrame) >= Xsprit->totalFrame)
	{	
		(*nowFrame) = 0;
		(*nowDelay) = 0;
		return 1;
	}
	return 0;
}

void drawSprit(XSPRIT *Xsprit,int x,int y,int pos,XFACE *xFace)
{
	int i;
	int imgX,imgY,imgW,imgH,drawX,drawY,imgNum;
	int origI=0;
	int drawXsub;
	int drawYsub;
	if(Xsprit->nowFrame >= Xsprit->totalFrame || Xsprit->nowFrame < 0)
	{
		return;
	}		
	
	Xsprit->hairResize = 100;
	xGame.isReSizeDraw = TRUE;
	xGame.reSize = Xsprit->hairResize;
	if(xFace->hairNum != DONT)
	{
		if(pos == ACT_FRONT)
		{
			//xFace.hair
			//13두상(정면)
			if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgScale == 100)
			{								
				imgX = Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgX;
				imgY = Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgY;
				imgW = Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgW;
				imgH = Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgH;
				drawX = x+Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].drawX;
				drawY = y+Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].drawY+Xsprit->hairResizeY;
				if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgRot != 0)
				{
					xGame.isRotate = TRUE;
					xGame.rotateNum = 360-Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgRot;
					
				}
				drawHair(drawX, drawY, xFace->hairNum,8, pos, 0);
				xGame.isRotate = FALSE;
			}
		}
	}
	
	
	xGame.isReSizeDraw = FALSE;
	
	
	//그리기
	for(i=0;i<Xsprit->xFrame[Xsprit->nowFrame].totalLayer;i++)
	{
		imgX = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgX;
		imgY = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgY;
		imgW = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgW;
		imgH = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgH;
		drawX = x+Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].drawX;
		drawY = y+Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].drawY;
		imgNum = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgNum;
		
		
		//ppppppppppp
		/*
		 for(int imgI=0;imgI<ACTLAYERMAX;imgI++)
		 xSpritNpc[xShopNpc[xObjSort[b_a].code[num]].actingType][ACT_FRONT].img[imgI] = &imgActBody[imgI][ACT_FRONT];
		 for(int imgI=0;imgI<ACTLAYERMAX;imgI++)
		 xSpritNpc[xShopNpc[xObjSort[b_a].code[num]].actingType][ACT_BACK].img[imgI] = &imgActBody[imgI][ACT_BACK];
		 */
		
		
		
		if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgRot != 0)
		{			
			xGame.isRotate = TRUE;			
			xGame.rotateNum = 360-Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgRot;
		}
		xGame.isReSizeDraw = TRUE;
		xGame.reSize = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgScale;
		if(pos == ACT_FRONT)
		{
			//xFace.hair
			//13두상(정면)
			//14두상(우측)
			//15두상(좌측)
			switch(imgNum)
			{
                case 8:
                    if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgScale == 100)
                    {
                        xGame.isReSizeDraw = TRUE;
                        xGame.reSize = Xsprit->hairResize;
                        drawY+=Xsprit->hairResizeY;
                    }
                    break;
			}
		}
		else
		{
			//xFace.hair
			//12두상(정면)
			//13두상(우측)
			//14두상(좌측)
			switch(imgNum)
			{
			
                case 6:
                    if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgScale == 100)
                    {
                        xGame.isReSizeDraw = TRUE;
                        xGame.reSize = Xsprit->hairResize;
                        drawY+=Xsprit->hairResizeY;
                    }
                    break;
			}
		}
		
		if(Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum] != NULL)
		{
			drawXsub = drawX-(Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum]->w - imgActBody[imgNum][pos].w)/2;
			drawYsub = drawY-(Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum]->h - imgActBody[imgNum][pos].h)/2;
			drawImage(Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum], drawXsub, drawYsub, imgX, imgY, Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum]->w, Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum]->h, TL);
		}
		
		
		if(pos == ACT_FRONT)
		{
            drawImage(&imgActBody[imgNum][pos], drawX, drawY, imgX, imgY, imgW, imgH, TL);
		}
		else if(pos == ACT_BACK)
		{
            drawImage(&imgActBody[imgNum][pos], drawX, drawY, imgX, imgY, imgW, imgH, TL);
		}
				
		for(int layerI=0;layerI<SPRIT_IMGLAYERMAX;layerI++)
		{
			if(Xsprit->img[layerI][imgNum] != NULL)
			{
				 drawXsub = drawX-(Xsprit->img[layerI][imgNum]->w - imgActBody[imgNum][pos].w)/2;
				 drawYsub = drawY-(Xsprit->img[layerI][imgNum]->h - imgActBody[imgNum][pos].h)/2;
				
				drawImage(Xsprit->img[layerI][imgNum], drawXsub, drawYsub, imgX, imgY, Xsprit->img[layerI][imgNum]->w, Xsprit->img[layerI][imgNum]->h, TL);
			}
			//특정레이어뒤에 한번만 그려주자
			if(layerI == FACELAYER)
			{
				if(pos == ACT_FRONT)
				{
					//xFace.hair
					//13두상(정면)
					//14두상(우측)
					//15두상(좌측)
					switch(imgNum)
					{
                        case 8:
                            if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[imgNum].imgScale == 100)
                            {
                                //표정그리고
                                if(xFace->faceNum != DONT)
                                {
                                    drawFace(drawX, drawY,xFace,imgNum,pos);
                                }
                                //헤어그리기
                                if(xFace->hairNum != DONT)
                                {
                                    drawHair(drawX, drawY, xFace->hairNum,imgNum, pos, 1);
                                }
                            }
                            break;
					}
				}
				else
				{
					//xFace.hair
					//12두상(정면)
					//13두상(우측)
					//14두상(좌측)
					switch(imgNum)
					{
                        case 6:
                            if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[imgNum].imgScale == 100)
                            {
                                //표정그리고
                                if(xFace->faceNum != DONT)
                                {
                                    drawFace(drawX, drawY,xFace,imgNum,pos);
                                }
                                //헤어그리기
                                if(xFace->hairNum != DONT)
                                {
                                    drawHair(drawX, drawY, xFace->hairNum,imgNum, pos, 1);
                                }
                            }
                            break;
					}
				}
			}
		}
		xGame.isRotate = FALSE;
		xGame.isReSizeDraw = FALSE;
		
	}	
}

void reverseSprit(XSPRIT *Xsprit,int x,int y,int pos,XFACE *xFace)
{
	int i;
	int imgX,imgY,imgW,imgH,drawX,drawY,imgNum;
	int drawXsub;
	int drawYsub;
	int reverX;
	
	if(Xsprit->nowFrame >= Xsprit->totalFrame || Xsprit->nowFrame < 0)
	{
		return;
	}
	
	Xsprit->hairResize = 100;
	
	xGame.isReSizeDraw = TRUE;
	xGame.reSize = Xsprit->hairResize;
	
	if(xFace->hairNum != DONT)
	{
		xGame.isReverse = TRUE;
		if(pos == ACT_FRONT)
		{
			//xFace.hair
			//13두상(정면)
			if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgScale == 100)
			{
				imgX = Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgX;
				imgY = Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgY;
				imgW = Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgW;
				imgH = Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgH;
				reverX = (Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].drawX+imgW/2)*2;
				drawX = x+Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].drawX-(reverX);
				drawY = y+Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].drawY+Xsprit->hairResizeY;
				if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgRot != 0)
				{
					xGame.isRotate = TRUE;
					xGame.rotateNum = 360-Xsprit->xFrame[Xsprit->nowFrame].xLayer[8].imgRot;
					xGame.rotateNum = -xGame.rotateNum;
					
				}
				drawHair(drawX, drawY, xFace->hairNum,8, pos, 0);
				xGame.isRotate = FALSE;
			}
		}
		xGame.isReverse = FALSE;
	}
	xGame.isReSizeDraw = FALSE;
	
	//그리기
	for(i=0;i<Xsprit->xFrame[Xsprit->nowFrame].totalLayer;i++)
	{
		imgX = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgX;
		imgY = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgY;
		imgW = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgW;
		imgH = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgH;
		
		reverX = (Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].drawX+imgW/2)*2;
		
		drawX = x+Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].drawX-(reverX);
		drawY = y+Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].drawY;
		
		imgNum = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgNum;
				
		if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgRot != 0)
		{
			xGame.isRotate = TRUE;
			xGame.rotateNum = 360-Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgRot;
			xGame.rotateNum = -xGame.rotateNum;
		}
		
		xGame.isReSizeDraw = TRUE;
        
		xGame.reSize = Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgScale;
		if(pos == ACT_FRONT)
		{
			//xFace.hair
			//13두상(정면)
			//14두상(우측)
			//15두상(좌측)
			switch(imgNum)
			{
                case 8:
                    if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgScale == 100)
                    {
                        xGame.isReSizeDraw = TRUE;
                        xGame.reSize = Xsprit->hairResize;
                        drawY+=Xsprit->hairResizeY;
                    }
                    break;
            }
		}
		else
		{
			//xFace.hair
			//12두상(정면)
			//13두상(우측)
			//14두상(좌측)
			switch(imgNum)
            {
                case 6:
                    if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[i].imgScale == 100)
                    {
                        xGame.isReSizeDraw = TRUE;
                        xGame.reSize = Xsprit->hairResize;
                        drawY+=Xsprit->hairResizeY;
                    }
                    break;
            }
		}
		
		xGame.isReverse = TRUE;
				
		if(Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum] != NULL)
		{
			drawXsub = drawX-(Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum]->w - imgActBody[imgNum][pos].w)/2;
			drawYsub = drawY-(Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum]->h - imgActBody[imgNum][pos].h)/2;
			drawImage(Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum], drawXsub, drawYsub, imgX, imgY, Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum]->w, Xsprit->img[SPRIT_IMGLAYER_BACKLAYER][imgNum]->h, TL);
		}
		
		if(pos == ACT_FRONT)
		{
            drawImage(&imgActBody[imgNum][pos], drawX, drawY, imgX, imgY, imgW, imgH, TL);
		}
		else if(pos == ACT_BACK)
		{
            drawImage(&imgActBody[imgNum][pos], drawX, drawY, imgX, imgY, imgW, imgH, TL);
		}

		
		
		
		
		for(int layerI=0;layerI<SPRIT_IMGLAYERMAX;layerI++)
		{
			if(Xsprit->img[layerI][imgNum] != NULL)
			{
				drawXsub = drawX - (Xsprit->img[layerI][imgNum]->w - imgActBody[imgNum][pos].w)/2;
				drawYsub = drawY - (Xsprit->img[layerI][imgNum]->h - imgActBody[imgNum][pos].h)/2;
				drawImage(Xsprit->img[layerI][imgNum], drawXsub, drawYsub, imgX, imgY, Xsprit->img[layerI][imgNum]->w, Xsprit->img[layerI][imgNum]->h, TL);
			}
			
			
			
			//특정레이어뒤에 한번만 그려주자
			if(layerI == FACELAYER)
			{
				if(pos == ACT_FRONT)
				{
					//xFace.hair
					//13두상(정면)
					//14두상(우측)
					//15두상(좌측)
					switch(imgNum)
					{
                        case 8:
                            if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[imgNum].imgScale == 100)
                            {
                                //표정그리고
                                if(xFace->faceNum != DONT)
                                {
                                    drawFace(drawX, drawY,xFace,imgNum,pos);
                                }
                                //헤어그리기
                                if(xFace->hairNum != DONT)
                                {
                                    drawHair(drawX, drawY, xFace->hairNum,imgNum, pos, 1);
                                }
                            }
                            break;
					}
				}
				else
				{
					//xFace.hair
					//12두상(정면)
					//13두상(우측)
					//14두상(좌측)
                    switch(imgNum)
                    {
                        case 6:
                            if(Xsprit->xFrame[Xsprit->nowFrame].xLayer[imgNum].imgScale == 100)
                            {
                                //표정그리고
                                if(xFace->faceNum != DONT)
                                {
                                    drawFace(drawX, drawY,xFace,imgNum,pos);
                                }
                                //헤어그리기
                                if(xFace->hairNum != DONT)
                                {
                                    drawHair(drawX, drawY, xFace->hairNum,imgNum, pos, 1);
                                }
                            }
                            break;
                    }
				}
			}
		}
		
		xGame.isReverse = FALSE;
		xGame.isRotate = FALSE;
		xGame.isReSizeDraw = FALSE;
		
	}
}

XSPRITFRAME xFrame[50];
//Byte -> int 변환
//(byte[]데이터,시작포인터)
int getByteToIntPar(unsigned char data[], int idx)
{
	int result = 0;
	
	result = 
	((data[idx] & 0xFF)		<< 24) |
	((data[idx+1] & 0xFF)	<< 16) |
	((data[idx+2] & 0xFF)	<<  8) | 
	( data[idx+3] & 0xFF);
	
	return result;
}

int getExcelTypeNum(const char* strFileName)
{
		
	if(strcmp(strFileName, EXCEL_PS_INTERIOR_DATA_FILE) == 0)
	return EXCEL_PS_INTERIOR_DATA;
	
	if(strcmp(strFileName, EXCEL_PS_INTERIOR_LIST_FILE) == 0)
	return EXCEL_PS_INTERIOR_LIST;
	
	if(strcmp(strFileName, EXCEL_PS_THEME_FILE) == 0)
	return EXCEL_PS_THEME;

	if(strcmp(strFileName, EXCEL_PS_DRESS_DATA_FILE) == 0)
	return EXCEL_PS_DRESS_DATA;
	
	if(strcmp(strFileName, EXCEL_PS_DRESS_LIST_FILE) == 0)
	return EXCEL_PS_DRESS_LIST;
	
	if(strcmp(strFileName, EXCEL_PS_STAFF_DATA_FILE) == 0)
	return EXCEL_PS_STAFF_DATA;


	if(strcmp(strFileName, EXCEL_PS_STAFF_LIST_FILE) == 0)
	return EXCEL_PS_STAFF_LIST;


	if(strcmp(strFileName, EXCEL_PS_LVTABLE_FILE) == 0)
	return EXCEL_PS_LVTABLE;
		
	if(strcmp(strFileName, EXCEL_PS_RESDOWN_FILE) == 0)
	return EXCEL_PS_RESDOWN;
	

	if(strcmp(strFileName, EXCEL_PS_MINIGAME_FILE) == 0)
	return EXCEL_PS_MINIGAME;


	if(strcmp(strFileName, EXCEL_PS_NPCSET_FILE) == 0)
	return EXCEL_PS_NPCSET;

	if(strcmp(strFileName, EXCEL_PS_CAR_FILE) == 0)
	return EXCEL_PS_CAR;

	if(strcmp(strFileName, EXCEL_PS_CARSLOT_FILE) == 0)
	return EXCEL_PS_CARSLOT;

	if(strcmp(strFileName, EXCEL_PS_QUESTMAIN_FILE) == 0)
	return EXCEL_PS_QUESTMAIN;

	if(strcmp(strFileName, EXCEL_PS_QUESTNORMAL_FILE) == 0)
	return EXCEL_PS_QUESTNORMAL;

	if(strcmp(strFileName, EXCEL_PS_MODEL_FILE) == 0)
	return EXCEL_PS_MODEL;

	if(strcmp(strFileName, EXCEL_PS_SONG_FILE) == 0)
	return EXCEL_PS_SONG;
		  
			
	if(strcmp(strFileName, EXCEL_PS_WOBD_FILE) == 0)
	return EXCEL_PS_WOBD;
		
		
	if(strcmp(strFileName, EXCEL_PS_BALANCE_FILE) == 0)
	return EXCEL_PS_BALANCE;
	
	if(strcmp(strFileName, EXCEL_PS_DRESSCOLOR_FILE) == 0)
	return EXCEL_PS_DRESSCOLOR;
	
	if(strcmp(strFileName, EXCEL_PS_DRESSCONCEPT_FILE) == 0)
	return EXCEL_PS_DRESSCONCEPT;
	
	if(strcmp(strFileName, EXCEL_PS_FASHIONSHOW_FILE) == 0)
	return EXCEL_PS_FASHIONSHOW;
	
	if(strcmp(strFileName, EXCEL_PS_DRESSSECTION_FILE) == 0)
	return EXCEL_PS_DRESSSECTION;
	
	if(strcmp(strFileName, EXCEL_PS_ACCESSBONUS_FILE) == 0)
	return EXCEL_PS_ACCESSBONUS;
	
	if(strcmp(strFileName, EXCEL_PS_EXPANDDATA_FILE) == 0)
		return EXCEL_PS_EXPANDDATA;

	if(strcmp(strFileName, EXCEL_PS_EXPANDLIST_FILE) == 0)
		return EXCEL_PS_EXPANDLIST;

	if(strcmp(strFileName, EXCEL_PS_DRESS_IMG_FILE) == 0)
		return EXCEL_PS_DRESS_IMG;
	
	if(strcmp(strFileName, EXCEL_PS_HACK_FILE) == 0)
		return EXCEL_PS_HACK;
	
	if(strcmp(strFileName, EXCEL_PS_GOODSLIST_FILE) == 0)
		return EXCEL_PS_GOODSLIST;
	
	if(strcmp(strFileName, EXCEL_PS_SPECIALSALE_FILE) == 0)
		return EXCEL_PS_SPECIALSALE;
	
	if(strcmp(strFileName, EXCEL_PS_MODELCASTING_FILE) == 0)
		return EXCEL_PS_MODELCASTING;
	
	if(strcmp(strFileName, EXCEL_PS_STYLEBOOK_FILE) == 0)
		return EXCEL_PS_STYLEBOOK;
	
	if(strcmp(strFileName, EXCEL_PS_STYLEDRESS_FILE) == 0)
		return EXCEL_PS_STYLEDRESS;
    
    if(strcmp(strFileName, EXCEL_PS_MILEAGE_FILE) == 0)
        return EXCEL_PS_MILEAGE;
    
    
    if(strcmp(strFileName, EXCEL_PS_PACKAGE_FILE) == 0)
        return EXCEL_PS_PACKAGE;
    
    
    if(strcmp(strFileName, EXCEL_PS_EVENTTYPE_FILE) == 0)
        return EXCEL_PS_EVENTTYPE;
    
    if(strcmp(strFileName, EXCEL_PS_EVENTQUEST_FILE) == 0)
        return EXCEL_PS_EVENTQUEST;
    
    
    if(strcmp(strFileName, EXCEL_PS_HOTDEAL_FILE) == 0)
        return EXCEL_PS_HOTDEAL;

    
    if(strcmp(strFileName, EXCEL_PS_RIVAL_FILE) == 0)
        return EXCEL_PS_RIVAL;
    
    
    if(strcmp(strFileName, EXCEL_PS_COLLECTION_FILE) == 0)
        return EXCEL_PS_COLLECTION;
    
    if(strcmp(strFileName, EXCEL_PS_JEWEL_FILE) == 0)
        return EXCEL_PS_JEWEL;
    
    if(strcmp(strFileName, EXCEL_PS_AMULET_FILE) == 0)
        return EXCEL_PS_AMULET;
    
    
    if(strcmp(strFileName, EXCEL_PS_AMULETXY_FILE) == 0)
        return EXCEL_PS_AMULETXY;
    
    
    if(strcmp(strFileName, EXCEL_PS_CLUB_FILE) == 0)
        return EXCEL_PS_CLUB;
    
    if(strcmp(strFileName, EXCEL_PS_CLUBICON_FILE) == 0)
        return EXCEL_PS_CLUBICON;
    
    
    
    if(strcmp(strFileName, EXCEL_PS_FASHIONWEEKMAKEUP_FILE) == 0)
        return EXCEL_PS_FASHIONWEEKMAKEUP;
    
    if(strcmp(strFileName, EXCEL_PS_FASHIONWEEKDRESS_FILE) == 0)
        return EXCEL_PS_FASHIONWEEKDRESS;
    
    
    if(strcmp(strFileName, EXCEL_PS_CLUBSTORE_FILE)==0)
        return EXCEL_PS_CLUBSTORE;
    
    if(strcmp(strFileName, EXCEL_PS_BROOCHSHOP_FILE)==0)
        return EXCEL_PS_BROOCHSHOP;
		
    if(strcmp(strFileName, EXCEL_PS_R_STYLEBOOK_FILE)==0)
        return EXCEL_PS_R_STYLEBOOK;
    
    if(strcmp(strFileName, EXCEL_PS_R_UPGRADE_FILE)==0)
        return EXCEL_PS_R_UPGRADE;
    
	printf("여기까지들어온거면 완전에러!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>>%s\n",strFileName);
	
	return DONT;
}

