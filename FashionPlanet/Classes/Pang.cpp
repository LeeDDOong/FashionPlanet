//
//  Pang.cpp
//  FridayNight
//
//
//

#include "Global.h"

XPANG xPang;
XPANGEFF xPangEff;
XPANGCOMBO xPangCombo;
XPANGSCOREEFF xPangScoreEff[PANGSCOREEFFMAX];
XPANGGEAR xPangGear[PANGGEARMAX];


XIMG imgPangAuto[5];
XIMG imgPang_BG[5];					//배경
XIMG imgPangPause[5];					//pause

XIMG imgPangUi[10];


XIMG imgPangNum[5];
XIMG imgPangObj;
XIMG imgPangObjSelect;
XIMG imgPangStart[3];
XIMG imgPangTimeover;
XIMG imgPangCombo[5];
XIMG imgPangDir[15];
XIMG imgPangGear[10];


void initPang()
{
    //상태관리
	xPang.state = PANG_STATE_IN;
	xPang.beforeState = PANG_STATE_IN;
    xPang.anyCnt = 0;
    
    //콤보
    xPang.totalCombo = 0;
    xPang.comboCnt = DONT;
    //점수
    initSecurity(&xPang.totalScore, 0);
    
    for(int k=0;k<5;k++)
    {
        initSecurity(&xPang.score[k], 0);
        initSecurity(&xPang.comboScore[k],0);
        initSecurity(&xPang.buffScore[k],0);
    }
    
    
    
    
    int modelTimeBuff = 0;
    for(int k=0;k<FASHIONWEEKSETTINGMAX;k++)
    {
        xPang.effCnt[k] = 999;
        if(xFashionWeekModel[k].modelKey != DONT)
        {
            modelTimeBuff += getPangBuffTime(xFashionWeekModel[k].modelKey);
        }        
    }
    
    //시간
    initSecurity(&xPang.time, xPang.PANG_TIME_MAX+modelTimeBuff);
    xPang.timeMax = xPang.PANG_TIME_MAX+modelTimeBuff;
    xPang.prcTime = 0;
    //선택관련
    xPang.autoPangSpeed = 0;
	xPang.selectCnt = 0;
	xPang.isSelect = false;
    //위치관련
    xPang.bgX = cx+200;
    xPang.bgY = cy+5;
    //팡팡초기화
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		memset(&xPang.xObjSub[i], 0x00, sizeof(XPANGOBJ));
		for(int j = 0; j < PANG_HEIGHT; j++)
		{
			memset(&xPang.xObj[i][j], 0x00, sizeof(XPANGOBJ));
		}
	}
	xPang.xObjDir[0][0].state = xPang.xObj[0][0].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[0][5].state = xPang.xObj[0][5].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[1][5].state = xPang.xObj[1][5].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[3][5].state = xPang.xObj[3][5].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[5][5].state = xPang.xObj[5][5].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[6][0].state = xPang.xObj[6][0].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[6][5].state = xPang.xObj[6][5].state = PANG_OBJSTATE_DONT;
	
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		for(int j = 0; j < PANG_HEIGHT; j++)
		{
			xPang.xObjSub[i].x = xPang.bgX - (86*3) + 86*i;
			xPang.xObjDir[i][j].x = xPang.bgX - (86*3) + 86*i;
			
			if(i%2 == 0)
				xPang.xObjDir[i][j].y = xPang.bgY -(256) + 100*j;
			else
				xPang.xObjDir[i][j].y = xPang.bgY -(256)  + 100*j + 50;
			
			if(xPang.xObj[i][j].state == PANG_OBJSTATE_DONT)
				continue;
			
			xPang.xObj[i][j].chargeState = PANG_CHARGESTATE_MOVE;
			
			xPang.xObjDir[i][j].state = PANG_OBJSTATE_PLAY;
			xPang.xObjSub[i].state = PANG_OBJSTATE_PLAY;
			xPang.xObj[i][j].state = PANG_OBJSTATE_PLAY;
			
			xPang.xObjSub[i].type = PANG_OBJTYPE_DONT;
			
			xPang.xObj[i][j].type = PANG_OBJTYPE_DONT;
			xPang.xObjDir[i][j].type = PANG_OBJTYPE_DONT;
			
			xPang.xTouchObj[i][j].xPos = xPang.xObj[i][j].x - 50;
			xPang.xTouchObj[i][j].yPos = xPang.xObj[i][j].y - 50;
			xPang.xTouchObj[i][j].wPos = 100;
			xPang.xTouchObj[i][j].hPos = 100;
		}
	}
	
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		xPang.chargeState[i] = PANG_CHARGESTATE_DONT;
		makePang(i);
	}
	
	xPang.isSelect = false;
    xPang.autoPangSpeed = 0;
	xPang.selectCnt = 0;
	xPang.currentSelectObj.x = DONT;
	xPang.currentSelectObj.y = DONT;
	xPang.currentSelectObj.type = PANG_OBJTYPE_DONT;
	for(int i = 0; i < PANGOBJ_MAX; i++)
	{
		xPang.selectOBJ[i].x = DONT;
		xPang.selectOBJ[i].y = DONT;
		xPang.selectOBJ[i].type = PANG_OBJTYPE_DONT;
		xPang.selectOBJ[i].dir = PANG_DIR_DONT;
		xPang.selectOBJ[i].effCnt = 0;
	}
	
	checkBlankPang();
}

void delPangObj(int wNum, int hNum)
{
	xPang.xObjDir[wNum][hNum].type = PANG_OBJTYPE_DONT;
	xPang.xObj[wNum][hNum].type = PANG_OBJTYPE_DONT;
	xPang.chargeState[wNum] = PANG_CHARGESTATE_DONT;
	xPang.xObjSub[wNum].chargeState = PANG_CHARGESTATE_DONT;
}

bool checkBlankPang()
{
	bool isCharge[7];
	bool isReturn = true;
	
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		isCharge[i] = true;
		for(int j = PANG_HEIGHT-1; j >= 0; j--)
		{
			if(xPang.xObj[i][j].state == PANG_OBJSTATE_PLAY)
			{
				if(xPang.xObjDir[i][j].type == PANG_OBJTYPE_DONT)
				{
					if(i%6 == 0)//0,6열(4줄 짜리)
					{
						for(int k = 1; k < j; k++)
						{
//							xPang.xObjDir[i][k].type = PANG_OBJTYPE_DONT;
							xPang.xObj[i][k].chargeState = PANG_CHARGESTATE_MOVE;
						}
					}
					else
					{
						for(int k = 0; k < j; k++)
						{
//							xPang.xObjDir[i][k].type = PANG_OBJTYPE_DONT;
							xPang.xObj[i][k].chargeState = PANG_CHARGESTATE_MOVE;
						}
					}
					
					isCharge[i] = false;
					isReturn = false;
					break;
				}
			}
		}
	}
	
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		if(isCharge[i] == true)
		{
			for(int j = 0; j < PANG_HEIGHT; j++)
			{
				xPang.xObj[i][j].chargeState = PANG_CHARGESTATE_FINISH;
				xPang.xObjDir[i][j].type = xPang.xObj[i][j].type;
			}
			xPang.chargeState[i] = PANG_CHARGESTATE_FINISH;
		}
		else
		{
			makePang(i);
		}
	}
	
	return isReturn;
}


void makePang(int num)
{
	if(xPang.chargeState[num] == PANG_CHARGESTATE_FINISH)
		return;
	if(xPang.xObjSub[num].chargeState == PANG_CHARGESTATE_MOVE)
		return;
	
	xPang.xObjSub[num].chargeState = PANG_CHARGESTATE_MOVE;
	xPang.xObjSub[num].state = PANG_OBJSTATE_PLAY;
//임시
	xPang.xObjSub[num].type = ranDom(0, 4);
	
	if(num % 6 == 0)
		xPang.xObjSub[num].y = xPang.xObjDir[num][0].y;
	else
		xPang.xObjSub[num].y = xPang.xObjDir[num][0].y - 100;
	
	xPang.chargeState[num] = PANG_CHARGESTATE_MOVE;
}


void chargePang()
{
	bool isCharge[7];
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		isCharge[i] = false;
		for(int j = PANG_HEIGHT-1; j >= 0; j--)
		{
			switch (xPang.chargeState[i])
			{
				case PANG_CHARGESTATE_MOVE:
					if(xPang.xObj[i][j].chargeState == PANG_CHARGESTATE_MOVE && xPang.xObj[i][j].type != PANG_OBJTYPE_DONT)
					{
						xPang.xObj[i][j].y += 30;
						if(xPang.xObj[i][j].y >= xPang.xObjDir[i][j+1].y)
						{
							xPang.xObj[i][j+1] = xPang.xObj[i][j];
							xPang.xObj[i][j+1].y = xPang.xObjDir[i][j+1].y;
							xPang.xObj[i][j].type = xPang.xObjDir[i][j].type = PANG_OBJTYPE_DONT;
							xPang.xObj[i][j+1].chargeState = PANG_CHARGESTATE_FINISH;
							xPang.xObjDir[i][j+1].type = xPang.xObj[i][j+1].type;
							
							isCharge[i] = true;
						}
					}
					break;
				case PANG_CHARGESTATE_FINISH:
					break;
				default:
					break;
			}
		}
		
		if(xPang.chargeState[i] != PANG_CHARGESTATE_FINISH && xPang.xObjSub[i].type != PANG_OBJTYPE_DONT)
		{
			xPang.xObjSub[i].y += 25;
			
			if(i%6 == 0)
			{
				if(xPang.xObjSub[i].y >= xPang.xObjDir[i][1].y)
				{
					xPang.xObj[i][1].y = xPang.xObjDir[i][1].y;
					xPang.xObj[i][1] = xPang.xObjSub[i];
					xPang.xObjSub[i].chargeState = PANG_CHARGESTATE_FINISH;
					
					xPang.xObjDir[i][1].type = xPang.xObj[i][1].type;
				}
			}
			else
			{
				if(xPang.xObjSub[i].y >= xPang.xObjDir[i][0].y)
				{
					xPang.xObj[i][0].y = xPang.xObjDir[i][0].y;
					xPang.xObj[i][0] = xPang.xObjSub[i];
					xPang.xObjSub[i].chargeState = PANG_CHARGESTATE_FINISH;
					
					xPang.xObjDir[i][0].type = xPang.xObj[i][0].type;
				}
			}
		}
		
		if(isCharge[i] == true)
		{
			for(int j = PANG_HEIGHT-1; j >= 0; j--)
				xPang.xObj[i][j].y = xPang.xObjDir[i][j].y;
		}
		
	}
	
    
	if(checkBlankPang() ==  true)
	{
		switch (xPang.beforeState)
		{
			case PANG_STATE_IN:
                setPangState(PANG_STATE_READY);
				break;
			case PANG_STATE_EFFECT:
				if(checkPang() == true)
					xPang.state = PANG_STATE_PLAY;
				else
					xPang.state = PANG_STATE_SORT;
				break;
			default:
				break;
		}
	}
}


void prcPang()
{
	switch (xPang.state)
	{
		case PANG_STATE_IN:         //세팅
			chargePang();
			xPang.prcTime = xCalendar.nowSec;
			break;
		case PANG_STATE_READY:      //레디연출
            if(++xPang.anyCnt > 43)
            {
                xPang.anyCnt = 0;
                setPangState(PANG_STATE_PLAY);
                xPang.prcTime = xCalendar.nowSec;
            }
			break;
		case PANG_STATE_PLAY:
			if(checkPang() == false)
			{
				setPangState(PANG_STATE_SORT);
			}
            
			if(xCalendar.nowSec != xPang.prcTime)
			{
				xPang.prcTime = xCalendar.nowSec;
                
                
                setSecurity(&xPang.time, xPang.time.oriData-1);
                
                
                
				if(xPang.time.oriData < 0)
				{
                    initSecurity(&xPang.time, 0);
                    
                    if(getSecurity(&xPang.totalScore) == false)
                    {
                        
                    }
                    else if(getSecurity(&xPang.score[0]) == false){}
                    else if(getSecurity(&xPang.score[1]) == false){}
                    else if(getSecurity(&xPang.score[2]) == false){}
                    else if(getSecurity(&xPang.score[3]) == false){}
                    else if(getSecurity(&xPang.score[4]) == false){}
                    else if(getSecurity(&xPang.comboScore[0]) == false){}
                    else if(getSecurity(&xPang.comboScore[1]) == false){}
                    else if(getSecurity(&xPang.comboScore[2]) == false){}
                    else if(getSecurity(&xPang.comboScore[3]) == false){}
                    else if(getSecurity(&xPang.comboScore[4]) == false){}
                    else if(getSecurity(&xPang.buffScore[0]) == false){}
                    else if(getSecurity(&xPang.buffScore[1]) == false){}
                    else if(getSecurity(&xPang.buffScore[2]) == false){}
                    else if(getSecurity(&xPang.buffScore[3]) == false){}
                    else if(getSecurity(&xPang.buffScore[4]) == false){}
                    else
                    {
                        playSnd(SND_POPUP_SHOW);
                        setPangState(PANG_STATE_GORESULT);
                        xPang.isNet_pangResult = true;
                        ///////////////////////////////////////////////////
                        addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PANGRESULT, TRUE);
                        ///////////////////////////////////////////////////
                        //////////////////////////////////////////////////////////////////////////////////////////
                        xFashionWeek.isNet_Dress = true;
                        addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_FASHIONWEEKDRESSLIST, TRUE);
                        //////////////////////////////////////////////////////////////////////////////////////////
                        //////////////////////////////////////////////////////////////////////////////////////////
                        xFashionWeek.isNet_FittingList = true;
                        addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_FASHIONWEEKFITTINGLIST, TRUE);
                        //////////////////////////////////////////////////////////////////////////////////////////
                    }
				}
			}
			break;
		case PANG_STATE_EFFECT:
			chargePang();
			xPang.prcTime = xCalendar.nowSec;
			break;
		case PANG_STATE_SORT:
			sortPang();
			if(checkPang() == true)
			{
				setPangState(PANG_STATE_PLAY);
			}
			break;
		case PANG_STATE_PAUSE:
			xPang.prcTime = xCalendar.nowSec;
			break;
		case PANG_STATE_GORESULT:
            if(++xPang.anyCnt > 33)
            {
                
                
                

                setPangState(PANG_STATE_RESULT);
            }
			break;
		case PANG_STATE_RESULT:
            if(++xPang.anyCnt > 30)
            {
                
            }
			break;
		default:
			break;
	}
}

int pangX, pangY, pangW, pangH;

void drawPang()
{
    int px = cx;
    int py = cy;
    
	int effX,effY;

    
    //댄스팡판 배경
    drawImage(&imgPang_BG[0], 0, 0, 0, 0, imgPang_BG[0].w, imgPang_BG[0].h, TL);
    
    drawPangGear();
    
    drawImage(&imgPang_BG[2], 0, lcdH-imgPang_BG[2].h, 0, 0, imgPang_BG[2].w, imgPang_BG[2].h, TL);
    
    
    
	drawImage(&imgPang_BG[1], xPang.bgX, xPang.bgY-5, 0, 0, imgPang_BG[1].w, imgPang_BG[1].h, VH);
    
	//점수
    subTemp[XPOS] = lcdW-110;
    subTemp[YPOS] = 155;
    gSetColor(132, 83, 42);
    setCommaNum(strTempS,xPang.totalScore.oriData);
    setFontSizeORI(46);
    gDrawString(subTemp[XPOS], subTemp[YPOS], strTempS, VH);
    setFontSize(11);
    
    
    if(getSecurity(&xPang.time) == false)
    {
        //해킹처리
    }
    
    
    
    drawPangUi();
    
    
    
    
    
    //////////20160617 오토팡
    xPang.isAutoPang = false;
    /*
    subTemp[XPOS] = 65;
    subTemp[YPOS] = 55;
    
    xPang.xTouchAutoPang.wPos = imgPangAuto[0].w;
    xPang.xTouchAutoPang.hPos = imgPangAuto[0].h;
    xPang.xTouchAutoPang.xPos = subTemp[XPOS]-xPang.xTouchAutoPang.wPos/2;
    xPang.xTouchAutoPang.yPos = subTemp[YPOS]-xPang.xTouchAutoPang.hPos/2;
    
    if(xPang.isAutoPang == false)
    {
        drawImage(&imgPangAuto[0], subTemp[XPOS], subTemp[YPOS], 0, 0, imgPangAuto[0].w, imgPangAuto[0].h, VH);
    }
    else
    {
        drawImage(&imgPangAuto[1], subTemp[XPOS], subTemp[YPOS], 0, 0, imgPangAuto[1].w, imgPangAuto[1].h, VH);
        
        xGame.isBlend = true;
        xGame.blendType = BLEND_ADDP;
        xGame.isRotate = true;
        xGame.rotateNum = (gameCnt*3)%360;
        drawImage(&imgPangAuto[2], subTemp[XPOS], subTemp[YPOS], 0, 0, imgPangAuto[2].w, imgPangAuto[2].h, VH);
        xGame.isRotate = false;
        xGame.isBlend = false;
    }
    */
    
    if(xPang.state == PANG_STATE_PLAY && xPang.isAutoPang == true)
    {
        if(xPang.totalCheckPangObj >= 3)
        {
            xPang.autoPangSpeed += xGame.prcCnt;
            if(xPang.autoPangSpeed > 8)
            {
                xPang.autoPangSpeed = 0;
                if(xPang.totalCheckPangObj >= 4)
                {
                    int tempX[3];
                    int tempY[3];
                    
                    
                    tempX[2] = xPang.checkPangObjX[xPang.totalCheckPangObj-1];
                    tempY[2] = xPang.checkPangObjY[xPang.totalCheckPangObj-1];
                    
                    tempX[1] = xPang.checkPangObjX[xPang.totalCheckPangObj-2];
                    tempY[1] = xPang.checkPangObjY[xPang.totalCheckPangObj-2];
                    
                    tempX[0] = xPang.checkPangObjX[xPang.totalCheckPangObj-3];
                    tempY[0] = xPang.checkPangObjY[xPang.totalCheckPangObj-3];
                    
                    
                    xPang.checkPangObjX[0] = tempX[0];
                    xPang.checkPangObjY[0] = tempY[0];
                    xPang.checkPangObjX[1] = tempX[1];
                    xPang.checkPangObjY[1] = tempY[1];
                    xPang.checkPangObjX[2] = tempX[2];
                    xPang.checkPangObjY[2] = tempY[2];
                    xPang.totalCheckPangObj = 3;
                }
                
                xTouch.wPos = 5;
                xTouch.hPos = 5;
                xTouch.xPos = xPang.xObj[xPang.checkPangObjX[xPang.selectCnt]][xPang.checkPangObjY[xPang.selectCnt]].x-xTouch.wPos/2;
                xTouch.yPos = xPang.xObj[xPang.checkPangObjX[xPang.selectCnt]][xPang.checkPangObjY[xPang.selectCnt]].y-xTouch.hPos/2;
                
                switch(xPang.selectCnt)
                {
                    case 0:
                        touchTypeTemp = MH_KEY_PRESSEVENT;
                        touchType = USER_POINT_PRESS_EVENT;
                        xPang.isAutoKey = true;
                        keyPang(USER_POINT_PRESS_EVENT, xPang.xObj[xPang.checkPangObjX[xPang.selectCnt]][xPang.checkPangObjY[xPang.selectCnt]].x, xPang.xObj[xPang.checkPangObjX[xPang.selectCnt]][xPang.checkPangObjY[xPang.selectCnt]].y);
                        xPang.isAutoKey = false;
                        break;
                    default:
                        if(xPang.selectCnt >= xPang.totalCheckPangObj)
                        {
                            touchTypeTemp = MH_KEY_RELEASEEVENT;
                            touchType = USER_POINT_RELEASE_EVENT;
                            xPang.isAutoKey = true;
                            keyPang(USER_POINT_RELEASE_EVENT, cx, cy);
                            xPang.isAutoKey = false;
                        }
                        else
                        {
                            touchTypeTemp = MH_KEY_PRESSEVENT;
                            touchType = USER_POINT_MOVE_EVENT;
                            xPang.isAutoKey = true;
                            keyPang(USER_POINT_MOVE_EVENT, xPang.xObj[xPang.checkPangObjX[xPang.selectCnt]][xPang.checkPangObjY[xPang.selectCnt]].x, xPang.xObj[xPang.checkPangObjX[xPang.selectCnt]][xPang.checkPangObjY[xPang.selectCnt]].y);
                            xPang.isAutoKey = false;
                        }
                        break;
                }
            }
        }
    }
    //////////20160617 오토팡
    
    
    
    
	
	//댄스팡 오브젝트
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		for(int j = 0; j < PANG_HEIGHT; j++)
		{
			if(xPang.xObj[i][j].state == PANG_OBJSTATE_DONT)
				continue;
			if(xPang.xObj[i][j].type != PANG_OBJTYPE_DONT)
			{
				effX = 0;
				effY = 0;
				if(xPang.isSelect == true)
				{
					for(int k = 0; k < xPang.selectCnt; k++)
					{
						if(xPang.selectOBJ[k].x == i && xPang.selectOBJ[k].y == j)
						{
                            
							switch (xPang.selectOBJ[k].effCnt)
							{
                            case 0:effX=0;effY=0;break;
                            case 1:effX=1;effY=-2;break;
                            case 2:effX=1;effY=1;break;
                            case 3:effX=0;effY=4;break;
                            case 4:effX=-1;effY=1;break;
                            case 5:effX=-2;effY=-2;break;
                            case 6:effX=-0;effY=-1;break;
                            case 7:effX=1;effY=1;break;
                            case 8:effX=0;effY=1;break;
                            case 9:effX=-1;effY=0;break;
                            case 10:effX=1;effY=0;break;
                            default:effX=0;effY=0;break;
							}
						}
					}
				}
                
                if(xPang.state != PANG_STATE_PAUSE)
                    drawImage(&imgPangObj, xPang.xObj[i][j].x+effX, xPang.xObj[i][j].y+effY, 0, imgPangObj.h/5*xPang.xObj[i][j].type, imgPangObj.w, imgPangObj.h/5, VH);
			}
            
			if(xPang.chargeState[i] == PANG_CHARGESTATE_MOVE)
            {
                drawImage(&imgPangObj, xPang.xObjSub[i].x, xPang.xObjSub[i].y, 0, imgPangObj.h/5*xPang.xObjSub[i].type, imgPangObj.w, imgPangObj.h/5, VH);
                

            }
            /*
			sprintf(strTemp, "%d/%d", i,j);
			gSetColor(255, 255, 255);
			gDrawString(xPang.xObj[i][j].x, xPang.xObj[i][j].y, strTemp, VH, 30, FONT_XL);
             */
		}
	}
	
	if(xPang.isSelect == true)
	{
        xGame.isBlend = true;
        xGame.blendType = BLEND_ADDP;
		for(int i = 0; i < xPang.selectCnt; i++)
		{
            if(xPang.selectOBJ[i].dir != PANG_DIR_DONT)
            {
                switch (xPang.selectOBJ[i].dir)
                {
                    case PANG_DIR_12:
                        drawImage(&imgPangDir[12], xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].x, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].y, 0, 0, imgPangDir[12].w, imgPangDir[12].h, VH);
                        break;
                    case PANG_DIR_2:
                        drawImage(&imgPangDir[2], xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].x, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].y, 0, 0, imgPangDir[2].w, imgPangDir[2].h, VH);
                        break;
                    case PANG_DIR_4:
                        drawImage(&imgPangDir[4], xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].x, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].y, 0, 0, imgPangDir[4].w, imgPangDir[4].h, VH);
                        break;
                    case PANG_DIR_6:
                        drawImage(&imgPangDir[6], xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].x, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].y, 0, 0, imgPangDir[6].w, imgPangDir[6].h, VH);
                        break;
                    case PANG_DIR_8:
                        drawImage(&imgPangDir[8], xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].x, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].y, 0, 0, imgPangDir[8].w, imgPangDir[8].h, VH);
                        break;
                    case PANG_DIR_10:
                        drawImage(&imgPangDir[10], xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].x, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].y, 0, 0, imgPangDir[10].w, imgPangDir[10].h, VH);
                        break;
                }
            }

            effX = 0;
            effY = 0;
            switch (xPang.selectOBJ[i].effCnt)
            {
                case 0:effX=0;effY=0;break;
                case 1:effX=1;effY=-2;break;
                case 2:effX=1;effY=1;break;
                case 3:effX=0;effY=4;break;
                case 4:effX=-1;effY=1;break;
                case 5:effX=-2;effY=-2;break;
                case 6:effX=-0;effY=-1;break;
                case 7:effX=1;effY=1;break;
                case 8:effX=0;effY=1;break;
                case 9:effX=-1;effY=0;break;
                case 10:effX=1;effY=0;break;
                default:effX=0;effY=0;break;
            }
            
            for(int prcI=0;prcI<xGame.prcCnt;prcI++)
                xPang.selectOBJ[i].effCnt++;
            
            drawImage(&imgPangObjSelect, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].x+effX, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].y+effY, 0, 0, imgPangObjSelect.w, imgPangObjSelect.h, VH);
		}
        xGame.isBlend = false;
	}
    
    
	
	if(xPang.state == PANG_STATE_SORT)
	{
        /*
		gSetColor(255, 0, 0);
		gDrawString(lcdW/2, lcdH/2, "정렬중...", VH, 100);
         */
		gSetColor(255, 255, 255);
	}
	
//	setAlpha(100);
//	gSetColor(255, 0, 0);
//	fillRect(xPang.xTouchExit.xPos, xPang.xTouchExit.yPos, xPang.xTouchExit.wPos, xPang.xTouchExit.hPos);
//	for(int i = 0; i < xPang.selectCnt; i++)
//	{
//		fillRect(xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].x-imgPang_ObjClover.w/2, xPang.xObjDir[xPang.selectOBJ[i].x][xPang.selectOBJ[i].y].y-imgPang_ObjClover.h/2, imgPang_ObjClover.w, imgPang_ObjClover.h);
//	}
//	gSetColor(255, 255, 255);
//	fillRect(xPang.xObjDir[xPang.currentSelectObj.x][xPang.currentSelectObj.y].x-imgPang_ObjClover.w/2, xPang.xObjDir[xPang.currentSelectObj.x][xPang.currentSelectObj.y].y-imgPang_ObjClover.h/2, imgPang_ObjClover.w, imgPang_ObjClover.h);
//	setAlpha(ALPHA_MAX);
    
    
    
    
    //친구슬롯과 겹치는게 있나
    
    
    drawPangEff();
    drawPangScoreEff();
    drawPangCombo();

    
    
    subTemp[XPOS] = lcdW-50;
    subTemp[YPOS] = 50;
    drawImage(&imgPangPause[0], subTemp[XPOS], subTemp[YPOS], 0, 0, imgPangPause[0].w, imgPangPause[0].h, VH);
    
    xPang.xTouchPause.wPos = imgPangPause[0].w;
    xPang.xTouchPause.hPos = imgPangPause[0].h;
    xPang.xTouchPause.xPos = subTemp[XPOS]-xPang.xTouchPause.wPos/2;
    xPang.xTouchPause.yPos = subTemp[YPOS]-xPang.xTouchPause.hPos/2;
    
    
    
    
    
    
    switch(xPang.state)
    {
    case PANG_STATE_READY:
        drawPangStart();
        break;
    case PANG_STATE_GORESULT:
        drawPangTimeOver();
        break;
    case PANG_STATE_RESULT:
        drawPangResult();
        break;
    case PANG_STATE_PAUSE:
        drawBgFillRect();
        drawImage(&imgPangPause[1], px, py, 0, 0, imgPangPause[1].w, imgPangPause[1].h, VH);
        
        xPang.xTouchPauseOk.wPos = 200;
        xPang.xTouchPauseOk.hPos = 100;
        xPang.xTouchPauseOk.xPos = px-xPang.xTouchPauseOk.wPos/2;
        xPang.xTouchPauseOk.yPos = py-xPang.xTouchPauseOk.hPos/2;
            
        /*
        gSetColor(255, 0, 0);
        setAlpha(100);
        fillRect(xPang.xTouchPauseOk.xPos, xPang.xTouchPauseOk.yPos, xPang.xTouchPauseOk.wPos, xPang.xTouchPauseOk.hPos);
        setAlpha(ALPHA_MAX);
        */
        break;
    }
}


void makePangEff(int x,int y,int objType)
{
    int waitCnt = 0;
    for(int i=0;i<PANGEFFMAX;i++)
    {
        if(xPangEff.isPlay[i] == true)
            waitCnt++;
    }
    
    for(int i=0;i<PANGEFFMAX;i++)
    {
        if(xPangEff.isPlay[i] == false)
        {
            xPangEff.isPlay[i] = true;
            xPangEff.anyCnt[i] = 0;
            xPangEff.waitCnt[i] = waitCnt;
            xPangEff.x[i] = x;
            xPangEff.y[i] = y;
            xPangEff.objType[i] = objType;
            
            xPangEff.rot[i] = 0;
            xPangEff.rotSpeed[i] = ranDom(-10,10);
            break;
        }
    }
}

void drawPangEff()
{
    //0~10 각도
    int scale = 100;
    int alpha = ALPHA_MAX;
    
    for(int i=0;i<PANGEFFMAX;i++)
    {
        if(xPangEff.isPlay[i] == false)
            continue;
        if(xPangEff.waitCnt[i]-- > 0)
        {
            drawImage(&imgPangObj, xPang.xObj[xPangEff.x[i]][xPangEff.y[i]].x, xPang.xObj[xPangEff.x[i]][xPangEff.y[i]].y, 0, imgPangObj.h/5*xPangEff.objType[i], imgPangObj.w, imgPangObj.h/5, VH);
            continue;
        }
        
        scale = 100;
        alpha = ALPHA_MAX;
        
        switch(xPangEff.anyCnt[i])
        {
        case 0:alpha=100;scale=100;
                makeFire(xPang.xObj[xPangEff.x[i]][xPangEff.y[i]].x, xPang.xObj[xPangEff.x[i]][xPangEff.y[i]].y, 10);
                break;
        case 1:alpha=76;scale=124;break;
        case 2:alpha=62;scale=138;break;
        case 3:alpha=52;scale=148;break;
        case 4:alpha=45;scale=155;break;
        case 5:alpha=38;scale=162;break;
        case 6:alpha=33;scale=167;break;
        case 7:alpha=28;scale=172;break;
        case 8:alpha=24;scale=176;break;
        case 9:alpha=20;scale=180;break;
        case 10:alpha=17;scale=183;break;
        case 11:alpha=15;scale=185;break;
        case 12:alpha=12;scale=188;break;
        case 13:alpha=10;scale=190;break;
        case 14:alpha=8;scale=192;break;
        case 15:alpha=7;scale=193;break;
        case 16:alpha=5;scale=195;break;
        case 17:alpha=4;scale=196;break;
        case 18:alpha=3;scale=197;break;
        case 19:alpha=2;scale=198;break;
        case 20:alpha=1;scale=199;break;
        case 21:alpha=1;scale=199;break;
        case 22:alpha=1;scale=199;break;
        case 23:alpha=0;scale=200;break;
        case 24:alpha=0;scale=200;break;
        default:alpha=0;scale=200;break;
        }
        
        if(alpha != 100)
            setAlpha(alpha*ALPHA_MAX/100);
        
        if(scale != 100)
        {
            xGame.isReSizeDraw =true;
            xGame.reSize = scale;
        }
        xGame.isRotate = true;
        xGame.rotateNum = xPangEff.rot[i]%360;
        
        
        drawImage(&imgPangObj, xPang.xObj[xPangEff.x[i]][xPangEff.y[i]].x, xPang.xObj[xPangEff.x[i]][xPangEff.y[i]].y, 0, imgPangObj.h/5*xPangEff.objType[i], imgPangObj.w, imgPangObj.h/5, VH);
        
        xGame.isRotate = false;
        setAlpha(ALPHA_MAX);
        xGame.isReSizeDraw =false;
        
        for(int prcI=0;prcI<xGame.prcCnt*2;prcI++)
        {
            xPangEff.rot[i] +=  xPangEff.rotSpeed[i];
            if(++xPangEff.anyCnt[i] > 24)
            {
                xPangEff.isPlay[i] = false;
                
            }
        }
    }
}


bool isPangObjTouch()
{
//	XTOUCH xTouch;
	int length = 0;
	int wNum = DONT;
	int hNum = DONT;
	int i = 0;
	int j = 0;
	
    
    
	if(xTouch.xPos < xPang.xObjDir[0][0].x - imgPangObj.w/2 || xTouch.xPos > xPang.xObjDir[PANG_WIDTH-1][0].x + imgPangObj.w/2)
		return false;
	if(xTouch.yPos < xPang.xObjDir[0][0].y - imgPangObj.h/5/2 || xTouch.yPos > xPang.xObjDir[0][PANG_HEIGHT-1].y + imgPangObj.h/5/2)
		return false;
		
	if(touchType == USER_POINT_PRESS_EVENT || touchType == USER_POINT_MOVE_EVENT)
	{
		for(i = 0; i < PANG_WIDTH; i++)
		{
			for(j = 0; j < PANG_HEIGHT; j++)
			{
                if(xPang.selectCnt == 0)
                {
                    if(length == 0 || getPangObjLength(xTouch.xPos, xTouch.yPos, xPang.xObjDir[i][j].x, xPang.xObjDir[i][j].y) < length)
                    {
                        length = (int)getPangObjLength(xTouch.xPos, xTouch.yPos, xPang.xObjDir[i][j].x, xPang.xObjDir[i][j].y);
                        wNum = i;
                        hNum = j;
                    }
                }
                else
                {
                    if(length == 0 || (getPangObjLength(xTouch.xPos, xTouch.yPos, xPang.xObjDir[i][j].x, xPang.xObjDir[i][j].y) < length
                                       && xPang.selectOBJ[xPang.selectCnt-1].type == xPang.xObjDir[i][j].type))
                    {
                        length = (int)getPangObjLength(xTouch.xPos, xTouch.yPos, xPang.xObjDir[i][j].x, xPang.xObjDir[i][j].y);
                        wNum = i;
                        hNum = j;
                    }
                }
			}
		}
	}
	
	if(wNum == DONT && hNum == DONT)
		return false;
	
	//if(length > 51)
    if(length > 65)
		return false;
	
	i = wNum;
	j = hNum;
	
	if(xPang.xObj[i][j].state == PANG_OBJSTATE_DONT)
		return false;
	
	if(i == xPang.currentSelectObj.x && j == xPang.currentSelectObj.y)
		return false;
	
	if(xPang.selectCnt > 1)
	{
		if(i == xPang.selectOBJ[xPang.selectCnt-2].x && j == xPang.selectOBJ[xPang.selectCnt-2].y)
		{
			xPang.selectOBJ[xPang.selectCnt-1].x = DONT;
			xPang.selectOBJ[xPang.selectCnt-1].y = DONT;
			xPang.selectOBJ[xPang.selectCnt-1].type = PANG_OBJTYPE_DONT;
			xPang.selectOBJ[xPang.selectCnt-1].effCnt = 0;
			xPang.selectOBJ[xPang.selectCnt-2].dir = PANG_DIR_DONT;
			xPang.selectCnt--;
			xPang.currentSelectObj.x = i;
			xPang.currentSelectObj.y = j;
			return false;
		}
	}
	
	if(xPang.currentSelectObj.x != i || xPang.currentSelectObj.y != j)
	{
		if(xPang.selectCnt > 0)
		{
			for(int k = 0; k < xPang.selectCnt; k++)
			{
				if (xPang.xObjDir[i][j].type != xPang.selectOBJ[0].type)
				{
					return false;
				}
			}
			
			if(xPang.currentSelectObj.x == 1 || xPang.currentSelectObj.x == 3 || xPang.currentSelectObj.x == 5)
			{
				if(i > xPang.currentSelectObj.x+1 || i < xPang.currentSelectObj.x-1 || j > xPang.currentSelectObj.y+1 || j < xPang.currentSelectObj.y-1)
					return false;
				
				if(j == xPang.currentSelectObj.y)
				{
					if(i == xPang.currentSelectObj.x)
						return false;
				}
				else if(j < xPang.currentSelectObj.y)
				{
					if(i != xPang.currentSelectObj.x)
						return false;
				}
				else if(j > xPang.currentSelectObj.y)
				{
					if(i > xPang.currentSelectObj.x+1 || i < xPang.currentSelectObj.x-1)
						return false;
				}
				else if(xPang.xObjDir[i][j].type != xPang.selectOBJ[xPang.selectCnt-1].type)
				{
					return false;
				}
			}
			else
			{
				if(i > xPang.currentSelectObj.x+1 || i < xPang.currentSelectObj.x-1 || j > xPang.currentSelectObj.y+1 || j < xPang.currentSelectObj.y-1)
					return false;
				
				if(j == xPang.currentSelectObj.y)
				{
					if(i == xPang.currentSelectObj.x)
						return false;
				}
				else if(j < xPang.currentSelectObj.y)
				{
					if(i > xPang.currentSelectObj.x+1 || i < xPang.currentSelectObj.x-1)
						return false;
				}
				else if(j > xPang.currentSelectObj.y)
				{
					if(i != xPang.currentSelectObj.x)
						return false;
				}
				else if(xPang.xObjDir[i][j].type != xPang.selectOBJ[xPang.selectCnt-1].type)
				{
					return false;
				}
			}
			
		}
		
		if(xPang.selectCnt > 1)
		{
			for(int k = 0; k < xPang.selectCnt; k++)
			{
				if(i == xPang.selectOBJ[k].x && j == xPang.selectOBJ[k].y)
				{
					return false;
				}
			}
		}
		
		xPang.currentSelectObj.x = i;
		xPang.currentSelectObj.y = j;
		xPang.currentSelectObj.type = xPang.xObjDir[i][j].type;
		
		return true;
	}
	return false;
}

bool isPangObjCheck(int touchX, int touchY, int x, int y, int rad)
{
	int circleX, circleY;
	int minX, minY;
	int maxX, maxY;
	XTOUCH xTouch;
	
	minX = minY = maxX = maxY = 0;
	
	for(int angle = 0; angle <= 360; angle++)
	{
		for(int rrad = 0; rrad <= rad; rrad++)
		{
			circleX = x + cos(angle* 3.14/180) *rad;
			circleY = y - sin(angle *3.14/180) *rad;
			
			if(minX == 0 && maxX == 0)
				minX = maxX = circleX;
			if(minY == 0 && maxY == 0)
				minY = maxY = circleY;
			
			if(minX > circleX)
				minX = circleX;
			
			if(maxX < circleX)
				maxX = circleX;
			
			if(minY > circleY)
				minY = circleY;
			
			if(maxY < circleY)
				maxY = circleY;
		}
	}
	
	xTouch.wPos = maxX - minX;
	xTouch.hPos = maxY - minY;
	xTouch.xPos = minX;
	xTouch.yPos = minY;
	
	pangX = xTouch.xPos;
	pangY = xTouch.yPos;
	pangW = xTouch.wPos;
	pangH = xTouch.hPos;
	
	
	return touchCheck(&xTouch);
}


void keyPang(int type, int param1, int param2)
{
	bool isSame;
    
    if(xPang.isNet_pangResult == true)
        return;
    
    switch (xPang.state)
    {
    case PANG_STATE_PAUSE:
        if(touchCheck(&xPang.xTouchPauseOk) == true && touchType == USER_POINT_PRESS_EVENT)
        {
            playSnd(SND_MENU_OK);
            xWorldMap.isKeyReturn = true;
            xPang.state = PANG_STATE_PLAY;
        }
        break;
    case PANG_STATE_RESULT:
        if(touchTypeTemp == MH_KEY_PRESSEVENT)
        {
            if(touchCheck(&xPang.xTouchExit) == true && touchType == USER_POINT_PRESS_EVENT)
            {
                playSnd(SND_MENU_OK);
                xWorldMap.isKeyReturn = true;
                
                freePangImg();
                xWorldMap.state = WORLDMAP_STATE_CLUBLOBBY;
            }
        }
        break;
    case PANG_STATE_PLAY:
        if(touchCheck(&xPang.xTouchPause) == true && touchType == USER_POINT_PRESS_EVENT)
        {
            playSnd(SND_MENU_OK);
            xWorldMap.isKeyReturn = true;
            xPang.state = PANG_STATE_PAUSE;
        }
        //////////20160617 오토팡
        else if(touchCheck(&xPang.xTouchAutoPang) == true && touchType == USER_POINT_PRESS_EVENT)
        {
            playSnd(SND_MENU_OK);
            xWorldMap.isKeyReturn = true;
            if(xPang.isAutoPang == true)
            {
                xPang.isAutoPang = false;
                
                if(xPang.totalCheckPangObj > 0)
                {
                    touchTypeTemp = MH_KEY_RELEASEEVENT;
                    touchType = USER_POINT_RELEASE_EVENT;
                    
                    xPang.isAutoKey = true;
                    keyPang(USER_POINT_RELEASE_EVENT, cx, cy);
                    xPang.isAutoKey = false;
                }
                
                
            }
            else
                xPang.isAutoPang = true;
        }
        else if(xPang.isAutoPang == true && xPang.isAutoKey == false)
        {
            
            
            
            xWorldMap.isKeyReturn = false;
        }
        //////////20160617 오토팡
        else
        {
            if(touchTypeTemp == MH_KEY_PRESSEVENT)
            {
                if(xPang.selectCnt == 0)
                {
                    xPang.checkTouchX[0] = xTouch.xPos;
                    xPang.checkTouchY[0] = xTouch.yPos;
                    xPang.checkTouchX[1] = xTouch.xPos;
                    xPang.checkTouchY[1] = xTouch.yPos;
                    xPang.checkTouchXPang[xPang.totalCheckTouchPang] = xPang.checkTouchX[0];
                    xPang.checkTouchYPang[xPang.totalCheckTouchPang] = xPang.checkTouchY[0];
                    xPang.totalCheckTouchPang++;
                }
                else
                {
                    xPang.checkTouchX[1] = xTouch.xPos;
                    xPang.checkTouchY[1] = xTouch.yPos;
                }
                xPang.totalCheckTouchPang = 0;
                
                
                //바로전 터치좌표 저장
                //현재 터치좌표 저장후
                //속도별 이동체크
                while (true)
                {
                    int targetX = xPang.checkTouchX[1];
                    int targetY = xPang.checkTouchY[1];
                    int nowX = xPang.checkTouchX[0];
                    int nowY = xPang.checkTouchY[0];
                    
                    float rad = getArcTan(nowX,nowY,targetX,targetY);
                    float speedMax = getRadiusSpeed(targetX,targetY,nowX,nowY,rad);
                    
                    
                    if(speedMax <= 10)
                    {
                        xPang.checkTouchX[0] = xPang.checkTouchX[1];
                        xPang.checkTouchY[0] = xPang.checkTouchY[1];
                        
                        xPang.checkTouchXPang[xPang.totalCheckTouchPang] = xPang.checkTouchX[0];
                        xPang.checkTouchYPang[xPang.totalCheckTouchPang] = xPang.checkTouchY[0];
                        xPang.totalCheckTouchPang++;
                        break;
                    }
                    else
                    {
                        getRadiusPos(nowX,nowY,10,rad);
                        xPang.checkTouchX[0] = xRadius.pos[XPOS];
                        xPang.checkTouchY[0] = xRadius.pos[YPOS];
                        xPang.checkTouchXPang[xPang.totalCheckTouchPang] = xPang.checkTouchX[0];
                        xPang.checkTouchYPang[xPang.totalCheckTouchPang] = xPang.checkTouchY[0];
                        xPang.totalCheckTouchPang++;
                    }
                }
                
                for(int reI = 0;reI<xPang.totalCheckTouchPang;reI++)
                {
                    xTouch.xPos = xPang.checkTouchXPang[reI];
                    xTouch.yPos = xPang.checkTouchYPang[reI];
                    
                    if(isPangObjTouch() == true)
                    {
                        xPang.isSelect = true;
                        isSame = false;
                        
                        
                        
                        
                        if(xPang.selectCnt > 0)
                        {
                            if(xPang.xObjDir[xPang.currentSelectObj.x][xPang.currentSelectObj.y].y  < xPang.xObjDir[xPang.selectOBJ[xPang.selectCnt-1].x][xPang.selectOBJ[xPang.selectCnt-1].y].y)
                            {
                                if(xPang.xObjDir[xPang.currentSelectObj.x][xPang.currentSelectObj.y].x  < xPang.xObjDir[xPang.selectOBJ[xPang.selectCnt-1].x][xPang.selectOBJ[xPang.selectCnt-1].y].x)
                                    xPang.selectOBJ[xPang.selectCnt-1].dir = PANG_DIR_10;
                                else if(xPang.xObjDir[xPang.currentSelectObj.x][xPang.currentSelectObj.y].x  > xPang.xObjDir[xPang.selectOBJ[xPang.selectCnt-1].x][xPang.selectOBJ[xPang.selectCnt-1].y].x)
                                    xPang.selectOBJ[xPang.selectCnt-1].dir = PANG_DIR_2;
                                else
                                    xPang.selectOBJ[xPang.selectCnt-1].dir = PANG_DIR_12;
                            }
                            else if(xPang.xObjDir[xPang.currentSelectObj.x][xPang.currentSelectObj.y].y  > xPang.xObjDir[xPang.selectOBJ[xPang.selectCnt-1].x][xPang.selectOBJ[xPang.selectCnt-1].y].y)
                            {
                                if(xPang.xObjDir[xPang.currentSelectObj.x][xPang.currentSelectObj.y].x  < xPang.xObjDir[xPang.selectOBJ[xPang.selectCnt-1].x][xPang.selectOBJ[xPang.selectCnt-1].y].x)
                                    xPang.selectOBJ[xPang.selectCnt-1].dir = PANG_DIR_8;
                                else if(xPang.xObjDir[xPang.currentSelectObj.x][xPang.currentSelectObj.y].x  > xPang.xObjDir[xPang.selectOBJ[xPang.selectCnt-1].x][xPang.selectOBJ[xPang.selectCnt-1].y].x)
                                    xPang.selectOBJ[xPang.selectCnt-1].dir = PANG_DIR_4;
                                else
                                    xPang.selectOBJ[xPang.selectCnt-1].dir = PANG_DIR_6;
                            }
                        }
                        
                        xPang.selectOBJ[xPang.selectCnt].x = xPang.currentSelectObj.x;
                        xPang.selectOBJ[xPang.selectCnt].y = xPang.currentSelectObj.y;
                        xPang.selectOBJ[xPang.selectCnt].type = xPang.currentSelectObj.type;
                        xPang.selectOBJ[xPang.selectCnt].effCnt = 0;
                        xPang.selectCnt++;
                    }
                }
            }
            else if(touchTypeTemp == MH_KEY_RELEASEEVENT)
            {
                //댄스팡 터졌을때
                if(xPang.selectCnt >= PANG_EFFECT_MIN)
                {
                    //콤보연산
                    if(xPang.comboCnt == DONT || (xCalendar.nowMilSec - xPang.comboTime < 2000))
                    {
                        ++xPang.comboCnt;
                        if(xPang.comboCnt > 0)
                        {
                            makePangCombo(xPang.xObj[xPang.selectOBJ[xPang.selectCnt/2].x][xPang.selectOBJ[xPang.selectCnt/2].y].x,xPang.xObj[xPang.selectOBJ[xPang.selectCnt/2].y][xPang.selectOBJ[xPang.selectCnt/2].y].y,xPang.comboCnt);
                            
                            //최대콤보
                            if(xPang.comboCnt > xPang.totalCombo)
                                xPang.totalCombo = xPang.comboCnt;
                            
                        }
                    }
                    else
                    {
                        xPang.comboCnt = 0;
                    }
                    xPang.comboTime = xCalendar.nowMilSec;
                    
                    
                    for(int i = 0; i < xPang.selectCnt; i++)
                    {
                        makePangEff(xPang.selectOBJ[i].x,xPang.selectOBJ[i].y,xPang.selectOBJ[i].type);
                        delPangObj(xPang.selectOBJ[i].x, xPang.selectOBJ[i].y);
                    }
                    xPang.state = PANG_STATE_EFFECT;
                    xPang.beforeState = PANG_STATE_EFFECT;
                    checkBlankPang();
                    //점수계산
                    setPangScore();
                    
                    
                }
                
                //댄스팡 게임 상태 리셋
                xPang.isSelect = false;
                xPang.autoPangSpeed = 0;
                xPang.selectCnt = 0;
                xPang.currentSelectObj.x = DONT;
                xPang.currentSelectObj.y = DONT;
                xPang.currentSelectObj.type = PANG_OBJTYPE_DONT;
                xPang.currentSelectObj.dir = PANG_DIR_DONT;
                for(int i = 0; i < PANGOBJ_MAX; i++)
                {
                    xPang.selectOBJ[i].x = DONT;
                    xPang.selectOBJ[i].y = DONT;
                    xPang.selectOBJ[i].type = PANG_OBJTYPE_DONT;
                    xPang.selectOBJ[i].dir = PANG_DIR_DONT;
                    xPang.selectOBJ[i].effCnt = 0;
                }
            }
        }
        break;
    }
}

void addPangScoreCombo(int type,int score)
{
    setSecurity(&xPang.comboScore[type], xPang.comboScore[type].oriData+score);
}
void addPangScore(int type,int score)
{
    setSecurity(&xPang.score[type], xPang.score[type].oriData+score);
}

void addPangScoreBuff(int type,int score)
{
    setSecurity(&xPang.buffScore[type], xPang.buffScore[type].oriData+score);
}



void setPangScore()
{
    int objType = xPang.selectOBJ[0].type;
    int comboScore = 0;
    int buffScore = 0;
    
    int defaultScore = xPang.DEFAULTSCORE*(xPang.selectCnt-2);
    
    xPang.effCnt[objType] = 0;
    
    
    buffScore = defaultScore*getPangBuffScore(xFashionWeekModel[objType].modelKey)/100;
    //콤보점수
    if(xPang.comboCnt >0)
    {
        comboScore = (xPang.comboCnt*1)*defaultScore/100;
    }
    
    //기본점수
    addPangScore(objType,defaultScore);
    addPangScoreCombo(objType,comboScore);
    addPangScoreBuff(objType, buffScore);
    
    
    switch(xPang.comboCnt)
    {
    case 0:
    case 1:
    case 2:
        playSnd(SND_PANG0);
        break;
    case 3:
    case 4:
    case 5:
        playSnd(SND_PANG1);
        break;
    case 6:
    case 7:
    case 8:
        playSnd(SND_PANG2);
        break;
    default:
        playSnd(SND_PANG3);
        break;
    }
    
    //총점수
    initSecurity(&xPang.totalScore, (xPang.score[0].oriData
                                     +xPang.score[1].oriData
                                     +xPang.score[2].oriData
                                     +xPang.score[3].oriData
                                     +xPang.score[4].oriData
                                     +xPang.comboScore[0].oriData
                                     +xPang.comboScore[1].oriData
                                     +xPang.comboScore[2].oriData
                                     +xPang.comboScore[3].oriData
                                     +xPang.comboScore[4].oriData
                                     +xPang.buffScore[0].oriData
                                     +xPang.buffScore[1].oriData
                                     +xPang.buffScore[2].oriData
                                     +xPang.buffScore[3].oriData
                                     +xPang.buffScore[4].oriData
                                     ));
    
    setPangScoreEff(290,cy-75+(objType*80),0,defaultScore+comboScore+buffScore);
}

void setPangState(int state)
{
	xPang.state = state;
    xPang.anyCnt = 0;
}

bool checkPang()
{
    

    
    
	XPANGOBJ obj[PANGOBJ_TYPE_MAX][PANGOBJ_MAX];
	int objType[PANGOBJ_TYPE_MAX];
	int totalNum[PANGOBJ_TYPE_MAX];
	bool isExist = false;
	int num = 0;
	
	objType[PANG_OBJTYPE_GOLD] = PANG_OBJTYPE_GOLD;
	objType[PANG_OBJTYPE_CLOVER] = PANG_OBJTYPE_CLOVER;
	objType[PANG_OBJTYPE_JUWEL] = PANG_OBJTYPE_JUWEL;
	objType[PANG_OBJTYPE_MUSIC] = PANG_OBJTYPE_MUSIC;
	objType[PANG_OBJTYPE_HEART] = PANG_OBJTYPE_HEART;
	
	totalNum[PANG_OBJTYPE_GOLD] = 0;
	totalNum[PANG_OBJTYPE_CLOVER] = 0;
	totalNum[PANG_OBJTYPE_JUWEL] = 0;
	totalNum[PANG_OBJTYPE_MUSIC] = 0;
	totalNum[PANG_OBJTYPE_HEART] = 0;
	
	//각 오브젝트별 총 갯수 및 위치 저장
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		for(int j = 0; j < PANG_HEIGHT; j++)
		{
			if(xPang.xObjDir[i][j].state == PANG_OBJSTATE_PLAY)
			{
				obj[xPang.xObjDir[i][j].type][totalNum[xPang.xObjDir[i][j].type]].x = i;
				obj[xPang.xObjDir[i][j].type][totalNum[xPang.xObjDir[i][j].type]].y = j;
				obj[xPang.xObjDir[i][j].type][totalNum[xPang.xObjDir[i][j].type]].type = xPang.xObjDir[i][j].type;
				totalNum[xPang.xObjDir[i][j].type]++;
			}
		}
	}
	
	for(int k = 0; k < PANGOBJ_TYPE_MAX; k++)
	{
		num = 0;
		for(int i = 0; i < totalNum[k]; i++)
		{
            xPang.totalCheckPangObj = 0;
			for(int j = 0; j < totalNum[k]; j++)
			{
				if(i == j) continue;
				
				
				if(obj[k][i].x == 1 || obj[k][i].x == 3 || obj[k][i].x == 5)
				{
					isExist = true;
					if(obj[k][j].x > obj[k][i].x+1 || obj[k][j].x < obj[k][i].x-1 || obj[k][j].y > obj[k][i].y+1 || obj[k][j].y < obj[k][i].y-1)
						isExist = false;
					
					if(obj[k][j].y == obj[k][i].y)
					{
						if(obj[k][j].x == obj[k][i].x)
							isExist = false;
					}
					else if(obj[k][j].y < obj[k][i].y)
					{
						if(obj[k][j].x != obj[k][i].x)
							isExist = false;
					}
					else if(obj[k][j].y > obj[k][i].y)
					{
						if(obj[k][j].x > obj[k][i].x+1 || obj[k][j].x < obj[k][i].x-1)
							isExist = false;
					}
					else if(obj[k][j].type != obj[k][i].type)
					{
						isExist = false;
					}
                    
                    
                    if(isExist == true)
                    {
                        xPang.checkPangObjX[xPang.totalCheckPangObj] = obj[k][i].x;
                        xPang.checkPangObjY[xPang.totalCheckPangObj++] = obj[k][i].y;
                        
                        xPang.checkPangObjX[xPang.totalCheckPangObj] = obj[k][j].x;
                        xPang.checkPangObjY[xPang.totalCheckPangObj++] = obj[k][j].y;
                        
                    }
				}
				else
				{
					isExist = true;
					if(obj[k][j].x > obj[k][i].x+1 || obj[k][j].x < obj[k][i].x-1 || obj[k][j].y > obj[k][i].y+1 || obj[k][j].y < obj[k][i].y-1)
						isExist = false;
					
					if(obj[k][j].y == obj[k][i].y)
					{
						if(obj[k][j].x == obj[k][i].x)
							isExist = false;
					}
					else if(obj[k][j].y < obj[k][i].y)
					{
						if(obj[k][j].x > obj[k][i].x+1 || obj[k][j].x < obj[k][i].x-1)
							isExist = false;
					}
					else if(obj[k][j].y > obj[k][i].y)
					{
						if(obj[k][j].x != obj[k][i].x)
							isExist = false;
					}
					else if(obj[k][j].type != obj[k][i].type)
					{
						isExist = false;
					}
                    
                    
                    if(isExist == true)
                    {
                        xPang.checkPangObjX[xPang.totalCheckPangObj] = obj[k][i].x;
                        xPang.checkPangObjY[xPang.totalCheckPangObj++] = obj[k][i].y;
                        
                        xPang.checkPangObjX[xPang.totalCheckPangObj] = obj[k][j].x;
                        xPang.checkPangObjY[xPang.totalCheckPangObj++] = obj[k][j].y;
                        
                    }
				}
				
				
				if(isExist == true)
				{
					for(int t = 0; t < totalNum[k]; t++)
					{
						if(t == j || t == i) continue;
						
						if(obj[k][j].x == 1 || obj[k][j].x == 3 || obj[k][j].x == 5)
						{
							isExist = true;
							if(obj[k][t].x > obj[k][j].x+1 || obj[k][t].x < obj[k][j].x-1 || obj[k][t].y > obj[k][j].y+1 || obj[k][t].y < obj[k][j].y-1)
								isExist = false;
							
							if(obj[k][t].y == obj[k][j].y)
							{
								if(obj[k][t].x == obj[k][j].x)
									isExist = false;
							}
							else if(obj[k][t].y < obj[k][j].y)
							{
								if(obj[k][t].x != obj[k][j].x)
									isExist = false;
							}
							else if(obj[k][t].y > obj[k][j].y)
							{
								if(obj[k][t].x > obj[k][j].x+1 || obj[k][t].x < obj[k][j].x-1)
									isExist = false;
							}
							else if(obj[k][t].type != obj[k][j].type)
							{
								return false;
							}
                            
                            if(isExist == true)
                            {
                                xPang.checkPangObjX[xPang.totalCheckPangObj] = obj[k][t].x;
                                xPang.checkPangObjY[xPang.totalCheckPangObj++] = obj[k][t].y;
                            }
						}
						else
						{
							isExist = true;
							if(obj[k][t].x > obj[k][j].x+1 || obj[k][t].x < obj[k][j].x-1 || obj[k][t].y > obj[k][j].y+1 || obj[k][t].y < obj[k][j].y-1)
								isExist = false;
							
							if(obj[k][t].y == obj[k][j].y)
							{
								if(obj[k][t].x == obj[k][j].x)
									isExist = false;
							}
							else if(obj[k][t].y < obj[k][j].y)
							{
								if(obj[k][t].x > obj[k][j].x+1 || obj[k][t].x < obj[k][j].x-1)
									isExist = false;
							}
							else if(obj[k][t].y > obj[k][j].y)
							{
								if(obj[k][t].x != obj[k][j].x)
									isExist = false;
							}
							else if(obj[k][t].type != obj[k][j].type)
							{
								return false;
							}
                            
                            if(isExist == true)
                            {
                                xPang.checkPangObjX[xPang.totalCheckPangObj] = obj[k][t].x;
                                xPang.checkPangObjY[xPang.totalCheckPangObj++] = obj[k][t].y;
                            }
						}
						
						if(isExist == true)
						{
							return true;
						}
						else
						{
							//재배치
						}
					}
				}
				isExist = false;
			}
		}
	}
	return false;
}

void sortPang()
{
	XPANGOBJ obj;
	int notRan1[7];
	int notRan2[7];
	int ran1;
	int ran2;
	int dir[42][2];
	int total = 0;
	
	notRan1[0] = 0;
	notRan1[1] = 0;
	notRan1[2] = 1;
	notRan1[3] = 3;
	notRan1[4] = 5;
	notRan1[5] = 6;
	notRan1[6] = 6;
	
	notRan2[0] = 0;
	notRan2[1] = 5;
	notRan2[2] = 5;
	notRan2[3] = 5;
	notRan2[4] = 5;
	notRan2[5] = 0;
	notRan2[6] = 5;
	
	xPang.xObjDir[0][0].state = xPang.xObj[0][0].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[0][5].state = xPang.xObj[0][5].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[1][5].state = xPang.xObj[1][5].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[3][5].state = xPang.xObj[3][5].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[5][5].state = xPang.xObj[5][5].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[6][0].state = xPang.xObj[6][0].state = PANG_OBJSTATE_DONT;
	xPang.xObjDir[6][5].state = xPang.xObj[6][5].state = PANG_OBJSTATE_DONT;
	
	
	for(int i = 0; i < PANG_WIDTH; i++)
	{
		for(int j = 0; j < PANG_HEIGHT; j++)
		{
			if(xPang.xObjDir[i][j].state == PANG_OBJSTATE_PLAY)
			{
				dir[total][0] = i;
				dir[total][1] = j;
				total++;
			}
		}
	}
	
	for(int i = 0; i < 100; i++)
	{
		ran1 = ranDom(0, total-1);
		ran2 = ranDom(0, total-1);
		
		obj.type = xPang.xObj[dir[ran1][0]][dir[ran1][1]].type;
		xPang.xObjDir[dir[ran1][0]][dir[ran1][1]].type = xPang.xObj[dir[ran1][0]][dir[ran1][1]].type = xPang.xObj[dir[ran2][0]][dir[ran2][1]].type;
		xPang.xObjDir[dir[ran2][0]][dir[ran2][1]].type = xPang.xObj[dir[ran2][0]][dir[ran2][1]].type = obj.type;
	}
}

double getPangObjLength(int x1, int y1, int x2, int y2)
{
	double result = 0.f, val=0.f;
	int w,h;
	w = x2 - x1;
	h = y2 - y1;
	val = (w*w) + (h*h);
	result = sqrt(val);
	return result;
}

void loadPangImg()
{
    
    loadImgDocuments("pang_bg0.png",&imgPang_BG[0]);
    loadImgDocuments("pang_bg1.png",&imgPang_BG[1]);
    loadImgDocuments("pang_bg2.png",&imgPang_BG[2]);
    loadImgDocuments("pang_bg3.png",&imgPang_BG[3]);

    
    loadImgDocuments("pangpause0.png",&imgPangPause[0]);
    loadImgDocuments("pangpause1.png",&imgPangPause[1]);
    
    //////////20160617 오토팡
    loadImgDocuments("pangauto0.png", &imgPangAuto[0]);
    loadImgDocuments("pangauto1.png", &imgPangAuto[1]);
    loadImgDocuments("pangauto2.png", &imgPangAuto[2]);
    //////////20160617 오토팡
    
    
    

    
    loadImgDocuments("pangnum0.png", &imgPangNum[0]);
    loadImgDocuments("pangnum1.png", &imgPangNum[1]);
    loadImgDocuments("pangnum2.png", &imgPangNum[2]);
    
    loadImgDocuments("pangobjselect.png", &imgPangObjSelect);
    
    loadImgDocuments("pangstart0.png", &imgPangStart[0]);
    loadImgDocuments("pangstart1.png", &imgPangStart[1]);
    
    loadImgDocuments("pangtimeover.png", &imgPangTimeover);
    
    loadImgDocuments("pangcombo0.png", &imgPangCombo[0]);
    loadImgDocuments("pangcombo1.png", &imgPangCombo[1]);
    loadImgDocuments("pangcombo2.png", &imgPangCombo[2]);
    
    loadImgDocuments("pangdir2.png", &imgPangDir[2]);
    loadImgDocuments("pangdir4.png", &imgPangDir[4]);
    loadImgDocuments("pangdir6.png", &imgPangDir[6]);
    loadImgDocuments("pangdir8.png", &imgPangDir[8]);
    loadImgDocuments("pangdir10.png", &imgPangDir[10]);
    loadImgDocuments("pangdir12.png", &imgPangDir[12]);



    loadImgDocuments("panggear0.png", &imgPangGear[0]);
    loadImgDocuments("panggear1.png", &imgPangGear[1]);
    loadImgDocuments("panggear2.png", &imgPangGear[2]);
    loadImgDocuments("panggear3.png", &imgPangGear[3]);
    loadImgDocuments("panggear4.png", &imgPangGear[4]);
    loadImgDocuments("panggear5.png", &imgPangGear[5]);
    loadImgDocuments("panggear6.png", &imgPangGear[6]);
    
    
    loadImgDocuments("pangui0.png", &imgPangUi[0]);
    loadImgDocuments("pangui1.png", &imgPangUi[1]);
    loadImgDocuments("pangui2.png", &imgPangUi[2]);
    loadImgDocuments("pangui3.png", &imgPangUi[3]);
    loadImgDocuments("pangui4.png", &imgPangUi[4]);
    loadImgDocuments("pangui5.png", &imgPangUi[5]);
    loadImgDocuments("pangui6.png", &imgPangUi[6]);
    loadImgDocuments("pangui7.png", &imgPangUi[7]);
    
    
}

void freePangImg()
{

    
    freeImg(&imgPang_BG[0]);
    freeImg(&imgPang_BG[1]);
    freeImg(&imgPang_BG[2]);
    freeImg(&imgPang_BG[3]);

    
    freeImg(&imgPangPause[0]);
    freeImg(&imgPangPause[1]);
    
    //////////20160617 오토팡
    freeImg(&imgPangAuto[0]);
    freeImg(&imgPangAuto[1]);
    freeImg(&imgPangAuto[2]);
    //////////20160617 오토팡
    
    

    freeImg(&imgPangNum[0]);
    freeImg(&imgPangNum[1]);
    freeImg(&imgPangNum[2]);
    
    freeImg(&imgPangObjSelect);
    
    freeImg(&imgPangStart[0]);
    freeImg(&imgPangStart[1]);
    
    freeImg(&imgPangTimeover);
    
    freeImg(&imgPangCombo[0]);
    freeImg(&imgPangCombo[1]);
    freeImg(&imgPangCombo[2]);
    
    freeImg(&imgPangDir[2]);
    freeImg(&imgPangDir[4]);
    freeImg(&imgPangDir[6]);
    freeImg(&imgPangDir[8]);
    freeImg(&imgPangDir[10]);
    freeImg(&imgPangDir[12]);
    
    
    freeImg(&imgPangGear[0]);
    freeImg(&imgPangGear[1]);
    freeImg(&imgPangGear[2]);
    freeImg(&imgPangGear[3]);
    freeImg(&imgPangGear[4]);
    freeImg(&imgPangGear[5]);
    freeImg(&imgPangGear[6]);
    
    
    freeImg(&imgPangUi[0]);
    freeImg(&imgPangUi[1]);
    freeImg(&imgPangUi[2]);
    freeImg(&imgPangUi[3]);
    freeImg(&imgPangUi[4]);
    freeImg(&imgPangUi[5]);
    freeImg(&imgPangUi[6]);
    freeImg(&imgPangUi[7]);
    
}



void makePangCombo(int x,int y,int comboNum)
{
    for(int i=0;i<PANGCOMBOMAX;i++)
    {
        if(xPangCombo.isPlay[i] == false)
        {
            xPangCombo.isPlay[i] = true;
            xPangCombo.anyCnt[i] = 0;
            xPangCombo.x[i] = x;
            xPangCombo.y[i] = y;
            xPangCombo.comboNum[i] = comboNum;
            break;
        }
    }
}

void drawPangCombo()
{
    int alpha;
    int scale;
    int rot;
    
    
    for(int i=0;i<PANGCOMBOMAX;i++)
    {
        if(xPangCombo.isPlay[i] == false)
            continue;
        
        for(int kk=0;kk<2;kk++)
        {
            alpha = 100;
            scale = 100;
            rot = 0;
            
            switch(xPangCombo.anyCnt[i]-(kk*4))
            {
            case 0:alpha=100;scale=0;rot=0;break;
            case 1:alpha=100;scale=104;rot=-5;break;
            case 2:alpha=100;scale=120;rot=-2;break;
            case 3:alpha=100;scale=118;rot=5;break;
            case 4:alpha=100;scale=110;rot=8;break;
            case 5:alpha=100;scale=105;rot=6;break;
            case 6:alpha=100;scale=103;rot=3;break;
            case 7:alpha=100;scale=101;rot=-0;break;
            case 8:alpha=100;scale=101;rot=-2;break;
            case 9:alpha=100;scale=100;rot=-1;break;
            case 10:alpha=100;scale=100;rot=0;break;
            case 11:alpha=100;scale=99;rot=0;break;
            case 12:alpha=100;scale=99;rot=0;break;
            case 13:alpha=100;scale=98;rot=0;break;
            case 14:alpha=100;scale=97;rot=0;break;
            case 15:alpha=100;scale=97;rot=0;break;
            case 16:alpha=100;scale=96;rot=0;break;
            case 17:alpha=100;scale=95;rot=0;break;
            case 18:alpha=100;scale=95;rot=0;break;
            case 19:alpha=100;scale=94;rot=0;break;
            case 20:alpha=100;scale=93;rot=0;break;
            case 21:alpha=100;scale=93;rot=0;break;
            case 22:alpha=100;scale=92;rot=0;break;
            case 23:alpha=100;scale=91;rot=0;break;
            case 24:alpha=100;scale=91;rot=0;break;
            case 25:alpha=100;scale=90;rot=0;break;
            case 26:alpha=80;scale=61;rot=0;break;
            case 27:alpha=60;scale=20;rot=0;break;
            case 28:alpha=40;scale=7;rot=0;break;
            case 29:alpha=20;scale=1;rot=0;break;
            default:alpha=0;scale=0;rot=0;break;
            }
            
            if(alpha != 100)
                setAlpha(alpha*ALPHA_MAX/100);
            
            if(scale != 100)
            {
                xGame.isReSizeDraw = true;
                xGame.reSize = scale;
            }
            
            if(rot != 0)
            {
                xGame.isRotate = true;
                xGame.rotateNum  = rot;
            }
            
            if(kk == 0)
            {
                drawImage(&imgPangCombo[0], xPangCombo.x[i], xPangCombo.y[i], 0, 0, imgPangCombo[0].w, imgPangCombo[0].h, VH);
            }
            else
            {
                drawImage(&imgPangCombo[1], xPangCombo.x[i]-25, xPangCombo.y[i]+70, 0, 0, imgPangCombo[1].w, imgPangCombo[1].h, VH);
                drawNum(&imgPangCombo[2], xPangCombo.x[i]-5, xPangCombo.y[i]+70, xPangCombo.comboNum[i], -15,VL);
            }
            
            xGame.isRotate = false;
            xGame.isReSizeDraw = false;
            setAlpha(ALPHA_MAX);
        }
        
        for(int prcI=0;prcI<xGame.prcCnt;prcI++)
            ++xPangCombo.anyCnt[i];
        if(xPangCombo.anyCnt[i] > 40)
        {
            xPangCombo.isPlay[i] = false;
        }
    }
}




void drawPangStart()
{
    int px = cx;
    int py = cy;
    
    int alpha;
    int scale;
    int yy;
    int rot;
    switch(xPang.anyCnt)
    {
    case 0:alpha=100;scale=0;break;
    case 1:alpha=100;scale=65;break;
    case 2:alpha=100;scale=145;break;
    case 3:alpha=100;scale=177;break;
    case 4:alpha=100;scale=173;break;
    case 5:alpha=100;scale=163;break;
    case 6:alpha=100;scale=151;break;
    case 7:alpha=100;scale=137;break;
    case 8:alpha=100;scale=123;break;
    case 9:alpha=100;scale=109;break;
    case 10:alpha=100;scale=100;break;
    case 11:alpha=100;scale=100;break;
    case 12:alpha=100;scale=100;break;
    case 13:alpha=100;scale=100;break;
    case 14:alpha=100;scale=100;break;
    case 15:alpha=100;scale=100;break;
    case 16:alpha=100;scale=100;break;
    case 17:alpha=100;scale=100;break;
    case 18:alpha=100;scale=100;break;
    case 19:alpha=100;scale=100;break;
    case 20:alpha=100;scale=100;break;
    case 21:alpha=100;scale=100;break;
    case 22:alpha=100;scale=100;break;
    case 23:alpha=100;scale=100;break;
    case 24:alpha=100;scale=100;break;
    case 25:alpha=100;scale=100;break;
    case 26:alpha=100;scale=100;break;
    case 27:alpha=100;scale=100;break;
    case 28:alpha=100;scale=100;break;
    case 29:alpha=100;scale=100;break;
    case 30:alpha=100;scale=100;break;
    case 31:alpha=100;scale=100;break;
    case 32:alpha=100;scale=100;break;
    case 33:alpha=100;scale=100;break;
    case 34:alpha=100;scale=100;break;
    case 35:alpha=100;scale=100;break;
    case 36:alpha=100;scale=100;break;
    case 37:alpha=100;scale=100;break;
    case 38:alpha=100;scale=100;break;
    case 39:alpha=100;scale=100;break;
    case 40:alpha=100;scale=100;break;
    case 41:alpha=67;scale=74;break;
    case 42:alpha=33;scale=26;break;
    case 43:alpha=0;scale=0;break;
    }
    
    
    if(alpha != 100)
        setAlpha(alpha*ALPHA_MAX/100);
    if(scale != 100)
    {
        xGame.isReSizeDraw = true;
        xGame.reSize = scale;
    }
    
    drawImage(&imgPangStart[1], px, py+52, 0, 0, imgPangStart[1].w, imgPangStart[1].h, VH);
    xGame.isReSizeDraw = false;
    setAlpha(ALPHA_MAX);
    
    
    switch(xPang.anyCnt)
    {
    case 0:alpha=20;scale=20;yy=280;rot=0;break;
    case 1:alpha=47;scale=37;yy=88;rot=-3;break;
    case 2:alpha=73;scale=55;yy=26;rot=-5;break;
    case 3:alpha=100;scale=72;yy=-6;rot=-2;break;
    case 4:alpha=100;scale=90;yy=-22;rot=5;break;
    case 5:alpha=100;scale=107;yy=-26;rot=8;break;
    case 6:alpha=100;scale=106;yy=-26;rot=5;break;
    case 7:alpha=100;scale=105;yy=-23;rot=1;break;
    case 8:alpha=100;scale=104;yy=-17;rot=-2;break;
    case 9:alpha=100;scale=103;yy=-6;rot=-1;break;
    case 10:alpha=100;scale=102;yy=-2;rot=0;break;
    case 11:alpha=100;scale=101;yy=-0;rot=0;break;
    case 12:alpha=100;scale=100;yy=-0;rot=0;break;
    case 13:alpha=100;scale=100;yy=-0;rot=0;break;
    case 14:alpha=100;scale=100;yy=-0;rot=0;break;
    case 15:alpha=100;scale=100;yy=-0;rot=0;break;
    case 16:alpha=100;scale=100;yy=-0;rot=0;break;
    case 17:alpha=100;scale=100;yy=-0;rot=0;break;
    case 18:alpha=100;scale=100;yy=-0;rot=0;break;
    case 19:alpha=100;scale=100;yy=-0;rot=0;break;
    case 20:alpha=100;scale=100;yy=-0;rot=0;break;
    case 21:alpha=100;scale=100;yy=-0;rot=0;break;
    case 22:alpha=100;scale=100;yy=-0;rot=0;break;
    case 23:alpha=100;scale=100;yy=-0;rot=0;break;
    case 24:alpha=100;scale=100;yy=-0;rot=0;break;
    case 25:alpha=100;scale=100;yy=-0;rot=0;break;
    case 26:alpha=100;scale=100;yy=-0;rot=0;break;
    case 27:alpha=100;scale=100;yy=-0;rot=0;break;
    case 28:alpha=100;scale=100;yy=-0;rot=0;break;
    case 29:alpha=100;scale=100;yy=-0;rot=0;break;
    case 30:alpha=100;scale=100;yy=-0;rot=0;break;
    case 31:alpha=100;scale=100;yy=-0;rot=0;break;
    case 32:alpha=100;scale=100;yy=-0;rot=0;break;
    case 33:alpha=100;scale=100;yy=-0;rot=0;break;
    case 34:alpha=100;scale=100;yy=-0;rot=0;break;
    case 35:alpha=100;scale=100;yy=-0;rot=0;break;
    case 36:alpha=100;scale=100;yy=-0;rot=0;break;
    case 37:alpha=100;scale=100;yy=-0;rot=0;break;
    case 38:alpha=100;scale=100;yy=-0;rot=0;break;
    case 39:alpha=100;scale=100;yy=-0;rot=0;break;
    case 40:alpha=100;scale=100;yy=-0;rot=0;break;
    case 41:alpha=67;scale=67;yy=-0;rot=0;break;
    case 42:alpha=33;scale=33;yy=-0;rot=0;break;
    case 43:alpha=0;scale=0;yy=-0;rot=0;break;
    }
    if(alpha != 100)
        setAlpha(alpha*ALPHA_MAX/100);
    if(scale != 100)
    {
        xGame.isReSizeDraw = true;
        xGame.reSize = scale;
    }
    if(rot != 0)
    {
        xGame.isRotate = true;
        xGame.rotateNum = rot;
    }
    drawImage(&imgPangStart[0], px, py-52+yy, 0, 0, imgPangStart[0].w, imgPangStart[0].h, VH);
    
    xGame.isRotate = false;
    xGame.isReSizeDraw = false;
    setAlpha(ALPHA_MAX);
}


void drawPangTimeOver()
{
    int px = cx;
    int py = cy;
    int yy;
    int rot;
    
    switch(xPang.anyCnt)
    {
    case 0:yy=-297;rot=0;break;
    case 1:yy=-288;rot=0;break;
    case 2:yy=-262;rot=1;break;
    case 3:yy=-225;rot=2;break;
    case 4:yy=-179;rot=4;break;
    case 5:yy=-130;rot=5;break;
    case 6:yy=-80;rot=7;break;
    case 7:yy=-34;rot=8;break;
    case 8:yy=3;rot=9;break;
    case 9:yy=29;rot=9;break;
    case 10:yy=38;rot=8;break;
    case 11:yy=42;rot=5;break;
    case 12:yy=39;rot=1;break;
    case 13:yy=22;rot=-3;break;
    case 14:yy=3;rot=-6;break;
    case 15:yy=-15;rot=-7;break;
    case 16:yy=-32;rot=-6;break;
    case 17:yy=-44;rot=-4;break;
    case 18:yy=-48;rot=-1;break;
    case 19:yy=-43;rot=2;break;
    case 20:yy=-30;rot=4;break;
    case 21:yy=-13;rot=5;break;
    case 22:yy=5;rot=4;break;
    case 23:yy=18;rot=2;break;
    case 24:yy=23;rot=-1;break;
    case 25:yy=19;rot=-2;break;
    case 26:yy=8;rot=-1;break;
    case 27:yy=-5;rot=-1;break;
    case 28:yy=-16;rot=0;break;
    case 29:yy=-21;rot=0;break;
    case 30:yy=-18;rot=0;break;
    case 31:yy=-11;rot=0;break;
    case 32:yy=-3;rot=0;break;
    case 33:yy=0;rot=0;break;
    }
    
    if(rot != 0)
    {
        xGame.isRotate = true;
        xGame.rotateNum = rot;
    }
    
    
    
    drawImage(&imgPangTimeover, px, py+yy, 0, 0, imgPangTimeover.w, imgPangTimeover.h, VH);
    xGame.isRotate = false;
}


void drawPangResult()
{
    int px = cx;
    int py = cy;
    
    drawBgFillRect();
    drawImage(&imgPangUi[1], px, py, 0, 0, imgPangUi[1].w, imgPangUi[1].h, VH);
    
    subTemp[XPOS] = px+320;
    subTemp[YPOS] = py-270;
    
    xPang.xTouchExit.wPos = 100;
    xPang.xTouchExit.hPos = 100;
    xPang.xTouchExit.xPos = subTemp[XPOS]-xPang.xTouchExit.wPos/2;
    xPang.xTouchExit.yPos = subTemp[YPOS]-xPang.xTouchExit.hPos/2;
    

    /*
    gSetColor(255, 0, 0);
    setAlpha(100);
    fillRect(xPang.xTouchExit.xPos, xPang.xTouchExit.yPos, xPang.xTouchExit.wPos, xPang.xTouchExit.hPos);
    setAlpha(ALPHA_MAX);
    */

    
    
    for(int k=0;k<FASHIONWEEKSETTINGMAX;k++)
    {
        subTemp[XPOS] = px-156;
        subTemp[YPOS] = py-145+(k*80);
        
        
        if(xFashionWeekModel[k].studioSlotNum != DONT)
        {
            if(xFashionStudio.itemCode[xFashionWeekModel[k].studioSlotNum] != DONT)
            {
                setMapData(xFashionStudio.itemCode[xFashionWeekModel[k].studioSlotNum]);
                drawFittingF(subTemp[XPOS]-70,subTemp[YPOS],(xMap.type*1000)+xMap.listNum,40);
                
                
                
                int sumNowCost = xFashionWeekItem[xMap.type][xMap.listNum].nowCost;
                
                int gageWW = sumNowCost*imgPangUi[3].w/xFashionData[xMap.type][xMap.listNum].clubCostMax;
                
                if(gageWW > imgPangUi[3].w)
                    gageWW = imgPangUi[3].w;
                
                drawImage(&imgPangUi[3], subTemp[XPOS]+193-imgPangUi[3].w/2, subTemp[YPOS]+1, 0, 0, gageWW, imgPangUi[3].h, VL);
                
                gSetColor(255, 255, 255);
                setFontSizeORI(15);
                
                char strTempPPPP[2][64];
                setCommaNum(strTempPPPP[0], sumNowCost);
                setCommaNum(strTempPPPP[1], xFashionData[xMap.type][xMap.listNum].clubCostMax);
                sprintf(strTempS, "%s/%s",strTempPPPP[0],strTempPPPP[1]);
                gDrawString(subTemp[XPOS]+193, subTemp[YPOS]+1, strTempS, VH);
                setFontSize(11);
            }
        }
        
        
        
        //빈슬롯
        int invenModelSlot = DONT;
        if(xFashionWeekModel[k].modelKey == DONT)
            invenModelSlot = DONT;
        else
        {
            invenModelSlot = getModelKeyToSlotNum(xFashionWeekModel[k].modelKey);
        }
        
        int scoreBuff = 0;
        int timeBuff = 0;
        if(invenModelSlot == DONT)
        {
            
        }
        else
        {
            int code = xInventoryModel[invenModelSlot].code;
            XFACE xFaceTemp;
            xFaceTemp.hairNum = code+1000;
            xFaceTemp.faceNum = code+1000;
            xFaceTemp.faceType = FACE_TYPE_NORMAL;
            
            XFITTINGLAYER xFTemp;
            
            memset(&xFTemp, 0, sizeof(xFTemp));
            for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
            {
                xFTemp.code[ff] = DONT;
            }
            int dx = 0;
            int dy = 0;
            
            if(xModelData[code].sex == 0)
            {
                dx = subTemp[XPOS];
                dy = subTemp[YPOS]+64;
                xGame.fgameScale = 0.7f;
            }
            else
            {
                dx = subTemp[XPOS];
                dy = subTemp[YPOS]+85;
                xGame.fgameScale = 0.8f;
            }
            xGame.fgameScaleCx = dx;
            xGame.fgameScaleCy = lcdH-(dy);
            gSetClip(true, subTemp[XPOS]-50, subTemp[YPOS]-54, 100, 88);
            drawFittingBody(dx, dy,&xFTemp,&xFaceTemp,TRUE,xModelData[code].sex);
            gSetClip(false, subTemp[XPOS]-50, subTemp[YPOS]-54, 100, 88);
            
            xGame.fgameScaleCx = cx;
            xGame.fgameScaleCy = cy;
            xGame.fgameScale = 1.0f;
        }
        
        
        switch(k)
        {
            case 0:gSetColor(255, 175, 175);break;
            case 1:gSetColor(255, 239, 175);break;
            case 2:gSetColor(183, 255, 175);break;
            case 3:gSetColor(175, 222, 255);break;
            case 4:gSetColor(252, 175, 255);break;
        }
        
        setFontSizeORI(25);
        int score = xPang.score[k].oriData+xPang.comboScore[k].oriData+xPang.buffScore[k].oriData;
        setCommaNum(strTempS, score);
        gDrawString(subTemp[XPOS]+406, subTemp[YPOS], strTempS, VH);
        setFontSize(11);
        
        
        
        
        
    }
    
    //베스트
    gSetColor(255, 255, 255);
    setFontSizeORI(20);
    setCommaNum(strTempS, xClub.bestPangScore);
    gDrawString(px-170, py-245, strTempS, VL);
    setFontSize(11);
    
    
    //총점
    subTemp[XPOS] = px+50;
    subTemp[YPOS] = py-203;
    xDrawObjCenter.reSize = 90;
    if(xDrawObjCenter.reSize != 100)
    {
        xGame.fgameScaleCx =subTemp[XPOS];
        xGame.fgameScaleCy =lcdH-(subTemp[YPOS]);
        xGame.fgameScale = xDrawObjCenter.reSize*0.01f;
    }
    drawNum(&imgPangUi[6], subTemp[XPOS], subTemp[YPOS], xPang.totalScore.oriData, -8, VH);
    xGame.fgameScale = 1.0f;
    xGame.fgameScaleCx =cx;
    xGame.fgameScaleCy =cy;
    
    
    if(xPang.totalScore.oriData > xClub.bestPangScore)
    {
        drawImage(&imgPangUi[2], subTemp[XPOS]+100, subTemp[YPOS]-35, 0, 0, imgPangUi[2].w, imgPangUi[2].h, VH);
    }    
    
    //기여도
    subTemp[XPOS] = px+50;
    subTemp[YPOS] = py+252;
    xDrawObjCenter.reSize = 90;
    if(xDrawObjCenter.reSize != 100)
    {
        xGame.fgameScaleCx =subTemp[XPOS];
        xGame.fgameScaleCy =lcdH-(subTemp[YPOS]);
        xGame.fgameScale = xDrawObjCenter.reSize*0.01f;
    }
    
    int resultClub= xPang.totalScore.oriData/100;
    if(resultClub == 0)
        resultClub = 1;
    
    drawImage(&imgPangUi[5], subTemp[XPOS]-10, subTemp[YPOS], 0, 0, imgPangUi[5].w, imgPangUi[5].h, VH);
    drawNum(&imgPangUi[6], subTemp[XPOS], subTemp[YPOS], resultClub, -8, VL);
    xGame.fgameScale = 1.0f;
    xGame.fgameScaleCx =cx;
    xGame.fgameScaleCy =cy;
    
    
    
    
    
    
    
    
    
    if(xPang.isNet_pangResult == true)
        drawLoadingIcon(cx, cy);
}



void setPangScoreEff(int x,int y,int type,int num)
{
    for(int i=0;i<PANGSCOREEFFMAX;i++)
    {
        if(xPangScoreEff[i].isPlay == false)
        {
            xPangScoreEff[i].isPlay = true;
            xPangScoreEff[i].anyCnt = 0;
            xPangScoreEff[i].type = type;
            xPangScoreEff[i].num = num;
            xPangScoreEff[i].x = x;
            xPangScoreEff[i].y = y;
            break;
        }
    }
}

void drawPangScoreEff()
{
    int scale;
    int yy;
    
    for(int i=0;i<PANGSCOREEFFMAX;i++)
    {
        if(xPangScoreEff[i].isPlay == true)
        {
            switch(xPangScoreEff[i].anyCnt)
            {
            case 0:scale=0;yy=0;break;
            case 1:scale=62;yy=-20;break;
            case 2:scale=124;yy=-41;break;
            case 3:scale=122;yy=-42;break;
            case 4:scale=116;yy=-41;break;
            case 5:scale=108;yy=-38;break;
            case 6:scale=102;yy=-36;break;
            case 7:scale=100;yy=-35;break;
            case 8:scale=100;yy=-35;break;
            case 9:scale=100;yy=-35;break;
            case 10:scale=100;yy=-35;break;
            case 11:scale=100;yy=-35;break;
            case 12:scale=100;yy=-35;break;
            case 13:scale=100;yy=-35;break;
            case 14:scale=100;yy=-35;break;
            case 15:scale=100;yy=-35;break;
            case 16:scale=100;yy=-35;break;
            case 17:scale=100;yy=-35;break;
            case 18:scale=100;yy=-35;break;
            case 19:scale=100;yy=-35;break;
            case 20:scale=100;yy=-35;break;
            case 21:scale=100;yy=-35;break;
            case 22:scale=100;yy=-35;break;
            case 23:scale=104;yy=-36;break;
            case 24:scale=112;yy=-39;break;
            case 25:scale=120;yy=-43;break;
            case 26:scale=124;yy=-41;break;
            case 27:scale=62;yy=-20;break;
            case 28:scale=0;yy=0;break;
            }
            
            xDrawObjCenter.reSize = scale;
            if(xDrawObjCenter.reSize != 100)
            {
                xGame.fgameScaleCx =xPangScoreEff[i].x;
                xGame.fgameScaleCy =lcdH-(xPangScoreEff[i].y+yy);
                xGame.fgameScale = xDrawObjCenter.reSize*0.01f;
            }
            
            
            drawNum(&imgPangNum[0+xPangScoreEff[i].type], xPangScoreEff[i].x, xPangScoreEff[i].y+yy, xPangScoreEff[i].num, -10, VH);
            xGame.fgameScale = 1.0f;
            xGame.fgameScaleCx =cx;
            xGame.fgameScaleCy =cy;
            
            for(int prcI=0;prcI<xGame.prcCnt;prcI++)
                ++xPangScoreEff[i].anyCnt;
            
            if(xPangScoreEff[i].anyCnt > 28)
            {
                xPangScoreEff[i].isPlay = false;
            }
        }
    }
}


void drawPangGear()
{
    
    //왼쪽
    int px = 120;
    int py = lcdH-170;
    xPangGear[0].type = 0;
    xPangGear[0].x = px-107;
    xPangGear[0].y = py-88;
    xPangGear[0].speed = 10;

    
    xPangGear[1].type = 1;
    xPangGear[1].x = px;
    xPangGear[1].y = py;
    xPangGear[1].speed = 5;

    
    xPangGear[2].type = 6;
    xPangGear[2].x = px+150;
    xPangGear[2].y = py+30;
    xPangGear[2].speed = 13;
    
    
    xPangGear[3].type = 5;
    xPangGear[3].x = px+146;
    xPangGear[3].y = py-69;
    xPangGear[3].speed = 11;

    
    xPangGear[4].type = 2;
    xPangGear[4].x = px-73;
    xPangGear[4].y = py-15;
    xPangGear[4].speed = 3;

    
    
    xPangGear[5].type = 4;
    xPangGear[5].x = px+95;
    xPangGear[5].y = py+32;
    xPangGear[5].speed = 2;

    
    xPangGear[6].type = 3;
    xPangGear[6].x = px+56;
    xPangGear[6].y = py-22;
    xPangGear[6].speed = 1;

    
    //오른쪽
    px = lcdW-250;
    py = lcdH-140;
    
    xPangGear[7].type = 6;
    xPangGear[7].x = px+105;
    xPangGear[7].y = py+25;
    xPangGear[7].speed = 1;
    
    xPangGear[8].type = 5;
    xPangGear[8].x = px;
    xPangGear[8].y = py;
    xPangGear[8].speed = 2;
    
    xPangGear[9].type = 6;
    xPangGear[9].x = px+175;
    xPangGear[9].y = py+75;
    xPangGear[9].speed = 2;
    
    xPangGear[10].type = 0;
    xPangGear[10].x = px+213;
    xPangGear[10].y = py-31;
    xPangGear[10].speed = 3;
    
    xPangGear[11].type = 4;
    xPangGear[11].x = px+62;
    xPangGear[11].y = py+53;
    xPangGear[11].speed = 1;
    
    xPangGear[12].type = 2;
    xPangGear[12].x = px+175;
    xPangGear[12].y = py+75;
    xPangGear[12].speed = 2;
    
    xPangGear[13].type = 3;
    xPangGear[13].x = px+109;
    xPangGear[13].y = py+57;
    xPangGear[13].speed = 4;
    
    
    xGame.isRotate = true;
    for(int k=0;k<PANGGEARMAX;k++)
    {
        for(int prcI=0;prcI<xGame.prcCnt;prcI++)
            xPangGear[k].rot += xPangGear[k].speed;
        
        xPangGear[k].rot = xPangGear[k].rot%360;
        xGame.rotateNum = xPangGear[k].rot;
        drawImage(&imgPangGear[xPangGear[k].type], xPangGear[k].x, xPangGear[k].y, 0, 0, imgPangGear[xPangGear[k].type].w,imgPangGear[xPangGear[k].type].h, VH);
    }
    xGame.isRotate = false;

}


void drawPangUi()
{
    
    int px = 0;
    int py = 0;
    //시간
    subTemp[XPOS] = 15;
    subTemp[YPOS] = 57;
    
    int gageW = xPang.time.oriData*imgPang_BG[3].w/xPang.timeMax;;
    
    drawImage(&imgPang_BG[3], subTemp[XPOS], subTemp[YPOS], 0, 0, imgPang_BG[3].w, imgPang_BG[3].h/2, VL);
    drawImage(&imgPang_BG[3], subTemp[XPOS], subTemp[YPOS], 0, imgPang_BG[3].h/2, gageW, imgPang_BG[3].h/2, VL);
    
    
    drawImage(&imgPangUi[4], subTemp[XPOS]+100, subTemp[YPOS]-20, 0, 0, imgPangUi[4].w, imgPangUi[4].h, VH);
    
    
    
    xDrawObjCenter.reSize = 60;
    if(xDrawObjCenter.reSize != 100)
    {
        xGame.fgameScaleCx =subTemp[XPOS]+100+28;
        xGame.fgameScaleCy =lcdH-(subTemp[YPOS]-20);
        xGame.fgameScale = xDrawObjCenter.reSize*0.01f;
    }
    drawNum(&imgPangUi[6], subTemp[XPOS]+100+28, subTemp[YPOS]-20, xPang.time.oriData, -8, VH);
    xGame.fgameScale = 1.0f;
    xGame.fgameScaleCx =cx;
    xGame.fgameScaleCy =cy;
    
    px = 190;
    py = cy+30;
    drawImage(&imgPangUi[0], px, py, 0, 0, imgPangUi[0].w, imgPangUi[0].h, VH);
    
    for(int k=0;k<FASHIONWEEKSETTINGMAX;k++)
    {
        subTemp[XPOS] = px+3;
        subTemp[YPOS] = py-127+(k*80);
        
        if(xFashionWeekModel[k].studioSlotNum != DONT)
        {
            if(xFashionStudio.itemCode[xFashionWeekModel[k].studioSlotNum] != DONT)
            {
                setMapData(xFashionStudio.itemCode[xFashionWeekModel[k].studioSlotNum]);
                drawFittingF(subTemp[XPOS]-70,subTemp[YPOS],(xMap.type*1000)+xMap.listNum,40);
            }
        }
        
        //빈슬롯
        int invenModelSlot = DONT;
        if(xFashionWeekModel[k].modelKey == DONT)
            invenModelSlot = DONT;
        else
        {
            invenModelSlot = getModelKeyToSlotNum(xFashionWeekModel[k].modelKey);
        }
            
        int scoreBuff = 0;
        int timeBuff = 0;
        if(invenModelSlot == DONT)
        {
            
        }
        else
        {
            int code = xInventoryModel[invenModelSlot].code;
            XFACE xFaceTemp;
            xFaceTemp.hairNum = code+1000;
            xFaceTemp.faceNum = code+1000;
            xFaceTemp.faceType = FACE_TYPE_NORMAL;
            
            XFITTINGLAYER xFTemp;
            
            memset(&xFTemp, 0, sizeof(xFTemp));
            for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
            {
                xFTemp.code[ff] = DONT;
            }
            
            
            int dx = 0;
            int dy = 0;
            
            if(xModelData[code].sex == 0)
            {
                dx = subTemp[XPOS];
                dy = subTemp[YPOS]+64;
                xGame.fgameScale = 0.7f;
            }
            else
            {
                dx = subTemp[XPOS];
                dy = subTemp[YPOS]+85;
                xGame.fgameScale = 0.8f;
            }
            xGame.fgameScaleCx = dx;
            xGame.fgameScaleCy = lcdH-(dy);
            gSetClip(true, subTemp[XPOS]-50, subTemp[YPOS]-54, 100, 88);
            drawFittingBody(dx, dy,&xFTemp,&xFaceTemp,TRUE,xModelData[code].sex);
            gSetClip(false, subTemp[XPOS]-50, subTemp[YPOS]-54, 100, 88);
            xGame.fgameScaleCx = cx;
            xGame.fgameScaleCy = cy;
            xGame.fgameScale = 1.0f;
        }
        
        
        switch(k)
        {
        case 0:gSetColor(255, 175, 175);break;
        case 1:gSetColor(255, 239, 175);break;
        case 2:gSetColor(183, 255, 175);break;
        case 3:gSetColor(175, 222, 255);break;
        case 4:gSetColor(252, 175, 255);break;
        }
        
        setFontSizeORI(25);
        setCommaNum(strTempS, xPang.score[k].oriData+xPang.comboScore[k].oriData+xPang.buffScore[k].oriData);
        gDrawString(subTemp[XPOS]+103, subTemp[YPOS], strTempS, VH);
        setFontSize(11);
        
        
        xPang.effCnt[k]++;
        
        int alpha = 0;
        int scale = 0;
        
        switch(xPang.effCnt[k])
        {
        case 0:alpha=100.0;break;
        case 1:alpha=100.0;break;
        case 2:alpha=95.0;break;
        case 3:alpha=90.0;break;
        case 4:alpha=85.0;break;
        case 5:alpha=80.0;break;
        case 6:alpha=75.0;break;
        case 7:alpha=70.0;break;
        case 8:alpha=65.0;break;
        case 9:alpha=60.0;break;
        case 10:alpha=55.0;break;
        case 11:alpha=50.0;break;
        case 12:alpha=45.0;break;
        case 13:alpha=40.0;break;
        case 14:alpha=35.0;break;
        case 15:alpha=30.0;break;
        case 16:alpha=25.0;break;
        case 17:alpha=20.0;break;
        case 18:alpha=15.0;break;
        case 19:alpha=10.0;break;
        case 20:alpha=5.0;break;
        case 21:alpha=0.0;break;
        }
        
        
        if(alpha != 0)
        {
            setAlpha(alpha*ALPHA_MAX/100);
            xGame.isReSizeDraw = true;
            xGame.reSize = 50;
            drawImage(&imgPangObjSelect, subTemp[XPOS]-140, subTemp[YPOS]+1, 0, 0, imgPangObjSelect.w, imgPangObjSelect.h, VH);
            xGame.isReSizeDraw = false;
            setAlpha(ALPHA_MAX);
        }
        
        
        alpha = 0;
        switch(xPang.effCnt[k])
        {
        case 0:alpha=100;scale=100;break;
        case 1:alpha=100;scale=100;break;
        case 2:alpha=95;scale=121;break;
        case 3:alpha=90;scale=134;break;
        case 4:alpha=85;scale=144;break;
        case 5:alpha=80;scale=151;break;
        case 6:alpha=75;scale=157;break;
        case 7:alpha=70;scale=163;break;
        case 8:alpha=65;scale=167;break;
        case 9:alpha=60;scale=171;break;
        case 10:alpha=55;scale=175;break;
        case 11:alpha=50;scale=178;break;
        case 12:alpha=45;scale=181;break;
        case 13:alpha=40;scale=184;break;
        case 14:alpha=35;scale=186;break;
        case 15:alpha=30;scale=188;break;
        case 16:alpha=25;scale=190;break;
        case 17:alpha=20;scale=191;break;
        case 18:alpha=15;scale=193;break;
        case 19:alpha=10;scale=194;break;
        case 20:alpha=5;scale=195;break;
        case 21:alpha=0;scale=196;break;
        }

        
        if(alpha != 0)
        {
            setAlpha(alpha*ALPHA_MAX/100);
            xGame.isReSizeDraw = true;
            xGame.reSize = 50*scale/100;
            
            drawImage(&imgPangObj, subTemp[XPOS]-140, subTemp[YPOS]+1, 0, imgPangObj.h/5*k, imgPangObj.w, imgPangObj.h/5, VH);
            drawImage(&imgPangObjSelect, subTemp[XPOS]-140, subTemp[YPOS]+1, 0, 0, imgPangObjSelect.w, imgPangObjSelect.h, VH);
            xGame.isReSizeDraw = false;
            setAlpha(ALPHA_MAX);
        }
    }
    
    //베스트
    gSetColor(255, 255, 255);
    setFontSizeORI(20);
    setCommaNum(strTempS, xClub.bestPangScore);
    gDrawString(px+8, py-182, strTempS, VL);
    setFontSize(11);
        
    //총점
    subTemp[XPOS] = px+30;
    subTemp[YPOS] = py-220;
    xDrawObjCenter.reSize = 90;
    if(xDrawObjCenter.reSize != 100)
    {
        xGame.fgameScaleCx =subTemp[XPOS];
        xGame.fgameScaleCy =lcdH-(subTemp[YPOS]);
        xGame.fgameScale = xDrawObjCenter.reSize*0.01f;
    }
    drawNum(&imgPangUi[6], subTemp[XPOS], subTemp[YPOS], xPang.totalScore.oriData, -8, VH);
    xGame.fgameScale = 1.0f;
    xGame.fgameScaleCx =cx;
    xGame.fgameScaleCy =cy;
}




