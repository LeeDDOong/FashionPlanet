//
//  Pang_Solo.cpp
//  RuleTheStyle
//
//  Created by kby5686 on 2017. 10. 30..
//
//

#include "Global.h"

XPANG_SOLO xPang_SOLO;
XPANG_SOLO_EFF xPang_SOLO_Eff;
XPANG_SOLO_COMBO xPang_SOLO_Combo;
XPANG_SOLO_SCOREEFF xPang_SOLO_ScoreEff[PANGSCOREEFFMAX];
XPANG_SOLO_GEAR xPang_SOLO_Gear[PANGGEARMAX];


XIMG imgPang_SOLO_Auto[5];
XIMG imgPang_SOLO_BG[5];					//배경
XIMG imgPang_SOLO_Pause[5];					//pause

XIMG imgPang_SOLO_Ui[20];


XIMG imgPang_SOLO_Num[5];
XIMG imgPang_SOLO_Obj;
XIMG imgPang_SOLO_ObjSelect;
XIMG imgPang_SOLO_Start[3];
XIMG imgPang_SOLO_Timeover;
XIMG imgPang_SOLO_Combo[5];
XIMG imgPang_SOLO_Dir[15];
XIMG imgPang_SOLO_Gear[10];


void initPang_Solo()
{
    //상태관리
    xPang_SOLO.state = PANG_SOLO_STATE_IN;
    xPang_SOLO.beforeState = PANG_SOLO_STATE_IN;
    xPang_SOLO.anyCnt = 0;
    
    //콤보
    xPang_SOLO.totalCombo = 0;
    xPang_SOLO.comboCnt = DONT;
    //점수
    initSecurity(&xPang_SOLO.totalScore, 0);
    
    for(int k=0;k<5;k++)
    {
        initSecurity(&xPang_SOLO.score[k], 0);
        initSecurity(&xPang_SOLO.comboScore[k],0);
        initSecurity(&xPang_SOLO.buffScore[k],0);
    }
    
    
    
    
    int modelTimeBuff = 0;
    for(int k=0;k<FASHIONWEEKSETTINGMAX;k++)
    {
        xPang_SOLO.effCnt[k] = 999;
        if(xLuluPangModel[k].modelKey != DONT)
        {
            modelTimeBuff += getPangBuffTime_LuluPang(xLuluPangModel[k].modelKey);
        }
    }
    
    //시간
    initSecurity(&xPang_SOLO.time, xPang_SOLO.PANG_TIME_MAX+modelTimeBuff);
    
//    initSecurity(&xPang_SOLO.time, 1000000);
	initSecurity(&xPang_SOLO.time, 30);
    xPang_SOLO.timeMax = 30;
    xPang_SOLO.prcTime = 0;
    //선택관련
    xPang_SOLO.autoPangSpeed = 0;
    xPang_SOLO.selectCnt = 0;
    xPang_SOLO.isSelect = false;
    //위치관련
    xPang_SOLO.bgX = cx+200;
    xPang_SOLO.bgY = cy+5;
    //팡팡초기화
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        memset(&xPang_SOLO.xObjSub[i], 0x00, sizeof(XPANG_SOLO_OBJ));
        for(int j = 0; j < PANG_SOLO_HEIGHT; j++)
        {
            memset(&xPang_SOLO.xObj[i][j], 0x00, sizeof(XPANG_SOLO_OBJ));
        }
    }
    xPang_SOLO.xObjDir[0][0].state = xPang_SOLO.xObj[0][0].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[0][5].state = xPang_SOLO.xObj[0][5].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[1][5].state = xPang_SOLO.xObj[1][5].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[3][5].state = xPang_SOLO.xObj[3][5].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[5][5].state = xPang_SOLO.xObj[5][5].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[6][0].state = xPang_SOLO.xObj[6][0].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[6][5].state = xPang_SOLO.xObj[6][5].state = PANG_SOLO_OBJSTATE_DONT;
    
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        for(int j = 0; j < PANG_SOLO_HEIGHT; j++)
        {
            xPang_SOLO.xObjSub[i].x = xPang_SOLO.bgX - (86*3) + 86*i;
            xPang_SOLO.xObjDir[i][j].x = xPang_SOLO.bgX - (86*3) + 86*i;
            
            if(i%2 == 0)
                xPang_SOLO.xObjDir[i][j].y = xPang_SOLO.bgY -(256) + 100*j;
            else
                xPang_SOLO.xObjDir[i][j].y = xPang_SOLO.bgY -(256)  + 100*j + 50;
            
            if(xPang_SOLO.xObj[i][j].state == PANG_SOLO_OBJSTATE_DONT)
                continue;
            
            xPang_SOLO.xObj[i][j].chargeState = PANG_SOLO_CHARGESTATE_MOVE;
            
            xPang_SOLO.xObjDir[i][j].state = PANG_SOLO_OBJSTATE_PLAY;
            xPang_SOLO.xObjSub[i].state = PANG_SOLO_OBJSTATE_PLAY;
            xPang_SOLO.xObj[i][j].state = PANG_SOLO_OBJSTATE_PLAY;
            
            xPang_SOLO.xObjSub[i].type = PANG_SOLO_OBJTYPE_DONT;
            
            xPang_SOLO.xObj[i][j].type = PANG_SOLO_OBJTYPE_DONT;
            xPang_SOLO.xObjDir[i][j].type = PANG_SOLO_OBJTYPE_DONT;
            
            xPang_SOLO.xTouchObj[i][j].xPos = xPang_SOLO.xObj[i][j].x - 50;
            xPang_SOLO.xTouchObj[i][j].yPos = xPang_SOLO.xObj[i][j].y - 50;
            xPang_SOLO.xTouchObj[i][j].wPos = 100;
            xPang_SOLO.xTouchObj[i][j].hPos = 100;
        }
    }
    
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        xPang_SOLO.chargeState[i] = PANG_SOLO_CHARGESTATE_DONT;
        makePang_Solo(i);
    }
    
    xPang_SOLO.isSelect = false;
    xPang_SOLO.autoPangSpeed = 0;
    xPang_SOLO.selectCnt = 0;
    xPang_SOLO.currentSelectObj.x = DONT;
    xPang_SOLO.currentSelectObj.y = DONT;
    xPang_SOLO.currentSelectObj.type = PANG_SOLO_OBJTYPE_DONT;
    for(int i = 0; i < PANG_SOLO_OBJ_MAX; i++)
    {
        xPang_SOLO.selectOBJ[i].x = DONT;
        xPang_SOLO.selectOBJ[i].y = DONT;
        xPang_SOLO.selectOBJ[i].type = PANG_SOLO_OBJTYPE_DONT;
        xPang_SOLO.selectOBJ[i].dir = PANG_SOLO_DIR_DONT;
        xPang_SOLO.selectOBJ[i].effCnt = 0;
    }
    
    checkBlankPang_Solo();
}

void delPang_SoloObj(int wNum, int hNum)
{
    xPang_SOLO.xObjDir[wNum][hNum].type = PANG_SOLO_OBJTYPE_DONT;
    xPang_SOLO.xObj[wNum][hNum].type = PANG_SOLO_OBJTYPE_DONT;
    xPang_SOLO.chargeState[wNum] = PANG_SOLO_CHARGESTATE_DONT;
    xPang_SOLO.xObjSub[wNum].chargeState = PANG_SOLO_CHARGESTATE_DONT;
}

bool checkBlankPang_Solo()
{
    bool isCharge[7];
    bool isReturn = true;
    
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        isCharge[i] = true;
        for(int j = PANG_SOLO_HEIGHT-1; j >= 0; j--)
        {
            if(xPang_SOLO.xObj[i][j].state == PANG_SOLO_OBJSTATE_PLAY)
            {
                if(xPang_SOLO.xObjDir[i][j].type == PANG_SOLO_OBJTYPE_DONT)
                {
                    if(i%6 == 0)//0,6열(4줄 짜리)
                    {
                        for(int k = 1; k < j; k++)
                        {
                            //							xPang.xObjDir[i][k].type = PANG_OBJTYPE_DONT;
                            xPang_SOLO.xObj[i][k].chargeState = PANG_SOLO_CHARGESTATE_MOVE;
                        }
                    }
                    else
                    {
                        for(int k = 0; k < j; k++)
                        {
                            //							xPang.xObjDir[i][k].type = PANG_OBJTYPE_DONT;
                            xPang_SOLO.xObj[i][k].chargeState = PANG_SOLO_CHARGESTATE_MOVE;
                        }
                    }
                    
                    isCharge[i] = false;
                    isReturn = false;
                    break;
                }
            }
        }
    }
    
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        if(isCharge[i] == true)
        {
            for(int j = 0; j < PANG_SOLO_HEIGHT; j++)
            {
                xPang_SOLO.xObj[i][j].chargeState = PANG_SOLO_CHARGESTATE_FINISH;
                xPang_SOLO.xObjDir[i][j].type = xPang_SOLO.xObj[i][j].type;
            }
            xPang_SOLO.chargeState[i] = PANG_SOLO_CHARGESTATE_FINISH;
        }
        else
        {
            makePang_Solo(i);
        }
    }
    
    return isReturn;
}


void makePang_Solo(int num)
{
    if(xPang_SOLO.chargeState[num] == PANG_SOLO_CHARGESTATE_FINISH)
        return;
    if(xPang_SOLO.xObjSub[num].chargeState == PANG_SOLO_CHARGESTATE_MOVE)
        return;
    
    xPang_SOLO.xObjSub[num].chargeState = PANG_SOLO_CHARGESTATE_MOVE;
    xPang_SOLO.xObjSub[num].state = PANG_SOLO_OBJSTATE_PLAY;
    //임시
    xPang_SOLO.xObjSub[num].type = ranDom(0, 4);
    
    if(num % 6 == 0)
        xPang_SOLO.xObjSub[num].y = xPang_SOLO.xObjDir[num][0].y;
    else
        xPang_SOLO.xObjSub[num].y = xPang_SOLO.xObjDir[num][0].y - 100;
    
    xPang_SOLO.chargeState[num] = PANG_SOLO_CHARGESTATE_MOVE;
}


void chargePang_Solo()
{
    bool isCharge[7];
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        isCharge[i] = false;
        for(int j = PANG_SOLO_HEIGHT-1; j >= 0; j--)
        {
            switch (xPang_SOLO.chargeState[i])
            {
                case PANG_SOLO_CHARGESTATE_MOVE:
                    if(xPang_SOLO.xObj[i][j].chargeState == PANG_SOLO_CHARGESTATE_MOVE && xPang_SOLO.xObj[i][j].type != PANG_SOLO_OBJTYPE_DONT)
                    {
                        xPang_SOLO.xObj[i][j].y += 30;
                        if(xPang_SOLO.xObj[i][j].y >= xPang_SOLO.xObjDir[i][j+1].y)
                        {
                            xPang_SOLO.xObj[i][j+1] = xPang_SOLO.xObj[i][j];
                            xPang_SOLO.xObj[i][j+1].y = xPang_SOLO.xObjDir[i][j+1].y;
                            xPang_SOLO.xObj[i][j].type = xPang_SOLO.xObjDir[i][j].type = PANG_SOLO_OBJTYPE_DONT;
                            xPang_SOLO.xObj[i][j+1].chargeState = PANG_SOLO_CHARGESTATE_FINISH;
                            xPang_SOLO.xObjDir[i][j+1].type = xPang_SOLO.xObj[i][j+1].type;
                            
                            isCharge[i] = true;
                        }
                    }
                    break;
                case PANG_SOLO_CHARGESTATE_FINISH:
                    break;
                default:
                    break;
            }
        }
        
        if(xPang_SOLO.chargeState[i] != PANG_SOLO_CHARGESTATE_FINISH && xPang_SOLO.xObjSub[i].type != PANG_SOLO_OBJTYPE_DONT)
        {
            xPang_SOLO.xObjSub[i].y += 25;
            
            if(i%6 == 0)
            {
                if(xPang_SOLO.xObjSub[i].y >= xPang_SOLO.xObjDir[i][1].y)
                {
                    xPang_SOLO.xObj[i][1].y = xPang_SOLO.xObjDir[i][1].y;
                    xPang_SOLO.xObj[i][1] = xPang_SOLO.xObjSub[i];
                    xPang_SOLO.xObjSub[i].chargeState = PANG_SOLO_CHARGESTATE_FINISH;
                    
                    xPang_SOLO.xObjDir[i][1].type = xPang_SOLO.xObj[i][1].type;
                }
            }
            else
            {
                if(xPang_SOLO.xObjSub[i].y >= xPang_SOLO.xObjDir[i][0].y)
                {
                    xPang_SOLO.xObj[i][0].y = xPang_SOLO.xObjDir[i][0].y;
                    xPang_SOLO.xObj[i][0] = xPang_SOLO.xObjSub[i];
                    xPang_SOLO.xObjSub[i].chargeState = PANG_SOLO_CHARGESTATE_FINISH;
                    
                    xPang_SOLO.xObjDir[i][0].type = xPang_SOLO.xObj[i][0].type;
                }
            }
        }
        
        if(isCharge[i] == true)
        {
            for(int j = PANG_SOLO_HEIGHT-1; j >= 0; j--)
                xPang_SOLO.xObj[i][j].y = xPang_SOLO.xObjDir[i][j].y;
        }
        
    }
    
    
    if(checkBlankPang_Solo() ==  true)
    {
        switch (xPang_SOLO.beforeState)
        {
            case PANG_SOLO_STATE_IN:
                setPang_SoloState(PANG_SOLO_STATE_READY);
                break;
            case PANG_SOLO_STATE_EFFECT:
                if(checkPang_Solo() == true)
                    xPang_SOLO.state = PANG_SOLO_STATE_PLAY;
                else
                    xPang_SOLO.state = PANG_SOLO_STATE_SORT;
                break;
            default:
                break;
        }
    }
}


void prcPang_Solo()
{
    switch (xPang_SOLO.state)
    {
        case PANG_SOLO_STATE_IN:         //세팅
            chargePang_Solo();
            xPang_SOLO.prcTime = xCalendar.nowSec;
            break;
        case PANG_SOLO_STATE_READY:      //레디연출
            if(++xPang_SOLO.anyCnt > 43)
            {
                xPang_SOLO.anyCnt = 0;
                setPang_SoloState(PANG_SOLO_STATE_PLAY);
                xPang_SOLO.prcTime = xCalendar.nowSec;
            }
            break;
        case PANG_SOLO_STATE_PLAY:
            if(checkPang_Solo() == false)
            {
                setPang_SoloState(PANG_SOLO_STATE_SORT);
            }
            
            if(xCalendar.nowSec != xPang_SOLO.prcTime)
            {
                xPang_SOLO.prcTime = xCalendar.nowSec;
                
                
                setSecurity(&xPang_SOLO.time, xPang_SOLO.time.oriData-1);
                
                
                
                if(xPang_SOLO.time.oriData < 0)
                {
                    initSecurity(&xPang_SOLO.time, 0);
//                    initSecurity(&xPang_SOLO.totalScore, 150010);
                    if(getSecurity(&xPang_SOLO.totalScore) == false)
                    {
                        
                    }
                    else if(getSecurity(&xPang_SOLO.score[0]) == false){}
                    else if(getSecurity(&xPang_SOLO.score[1]) == false){}
                    else if(getSecurity(&xPang_SOLO.score[2]) == false){}
                    else if(getSecurity(&xPang_SOLO.score[3]) == false){}
                    else if(getSecurity(&xPang_SOLO.score[4]) == false){}
                    else if(getSecurity(&xPang_SOLO.comboScore[0]) == false){}
                    else if(getSecurity(&xPang_SOLO.comboScore[1]) == false){}
                    else if(getSecurity(&xPang_SOLO.comboScore[2]) == false){}
                    else if(getSecurity(&xPang_SOLO.comboScore[3]) == false){}
                    else if(getSecurity(&xPang_SOLO.comboScore[4]) == false){}
                    else if(getSecurity(&xPang_SOLO.buffScore[0]) == false){}
                    else if(getSecurity(&xPang_SOLO.buffScore[1]) == false){}
                    else if(getSecurity(&xPang_SOLO.buffScore[2]) == false){}
                    else if(getSecurity(&xPang_SOLO.buffScore[3]) == false){}
                    else if(getSecurity(&xPang_SOLO.buffScore[4]) == false){}
                    else
                    {
                        playSnd(SND_POPUP_SHOW);
                        setPang_SoloState(PANG_SOLO_STATE_GORESULT);
                        xPang_SOLO.isNet_pangResult = false;
//                        addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_LULUPANGSCOREUPDATE, TRUE);
                    }
                }
            }
            break;
        case PANG_SOLO_STATE_EFFECT:
            chargePang_Solo();
            xPang_SOLO.prcTime = xCalendar.nowSec;
            break;
        case PANG_SOLO_STATE_SORT:
            sortPang_Solo();
            if(checkPang_Solo() == true)
            {
                setPang_SoloState(PANG_SOLO_STATE_PLAY);
            }
            break;
        case PANG_SOLO_STATE_PAUSE:
            xPang_SOLO.prcTime = xCalendar.nowSec;
            break;
        case PANG_SOLO_STATE_GORESULT:
			
			if(xPang_SOLO.anyCnt++ > 33)
			{
				setPang_SoloState(PANG_SOLO_STATE_RESULT);
			}
            break;
        case PANG_SOLO_STATE_RESULT:
            if(++xPang_SOLO.anyCnt > 30)
            {
                
            }
            break;
        default:
            break;
    }
}

int pang_SOLO_X, pang_SOLO_Y, pang_SOLO_W, pang_SOLO_H;

void drawPang_Solo()
{
    int px = cx;
    int py = cy;
    
    int effX,effY;
    
    
    //댄스팡판 배경
    drawImage(&imgPang_SOLO_BG[0], 0, 0, 0, 0, imgPang_SOLO_BG[0].w, imgPang_SOLO_BG[0].h, TL);
    
    drawPang_SoloGear();
    
    drawImage(&imgPang_SOLO_BG[2], 0, lcdH-imgPang_SOLO_BG[2].h, 0, 0, imgPang_SOLO_BG[2].w, imgPang_SOLO_BG[2].h, TL);
    
    
    
    drawImage(&imgPang_SOLO_BG[1], xPang_SOLO.bgX, xPang_SOLO.bgY-5, 0, 0, imgPang_SOLO_BG[1].w, imgPang_SOLO_BG[1].h, VH);
    
    if(getSecurity(&xPang_SOLO.time) == false)
    {
        //해킹처리
    }
    
    
    
    drawPang_SoloUi();
    
    
    
    
    
    //////////20160617 오토팡
    xPang_SOLO.isAutoPang = false;
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
    
    if(xPang_SOLO.state == PANG_SOLO_STATE_PLAY && xPang_SOLO.isAutoPang == true)
    {
        if(xPang_SOLO.totalCheckPangObj >= 3)
        {
            xPang_SOLO.autoPangSpeed += xGame.prcCnt;
            if(xPang_SOLO.autoPangSpeed > 8)
            {
                xPang_SOLO.autoPangSpeed = 0;
                if(xPang_SOLO.totalCheckPangObj >= 4)
                {
                    int tempX[3];
                    int tempY[3];
                    
                    
                    tempX[2] = xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj-1];
                    tempY[2] = xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj-1];
                    
                    tempX[1] = xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj-2];
                    tempY[1] = xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj-2];
                    
                    tempX[0] = xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj-3];
                    tempY[0] = xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj-3];
                    
                    
                    xPang_SOLO.checkPangObjX[0] = tempX[0];
                    xPang_SOLO.checkPangObjY[0] = tempY[0];
                    xPang_SOLO.checkPangObjX[1] = tempX[1];
                    xPang_SOLO.checkPangObjY[1] = tempY[1];
                    xPang_SOLO.checkPangObjX[2] = tempX[2];
                    xPang_SOLO.checkPangObjY[2] = tempY[2];
                    xPang_SOLO.totalCheckPangObj = 3;
                }
                
                xTouch.wPos = 5;
                xTouch.hPos = 5;
                xTouch.xPos = xPang_SOLO.xObj[xPang_SOLO.checkPangObjX[xPang_SOLO.selectCnt]][xPang_SOLO.checkPangObjY[xPang_SOLO.selectCnt]].x-xTouch.wPos/2;
                xTouch.yPos = xPang_SOLO.xObj[xPang_SOLO.checkPangObjX[xPang_SOLO.selectCnt]][xPang_SOLO.checkPangObjY[xPang_SOLO.selectCnt]].y-xTouch.hPos/2;
                
                switch(xPang_SOLO.selectCnt)
                {
                    case 0:
                        touchTypeTemp = MH_KEY_PRESSEVENT;
                        touchType = USER_POINT_PRESS_EVENT;
                        xPang_SOLO.isAutoKey = true;
                        keyPang_Solo(USER_POINT_PRESS_EVENT, xPang_SOLO.xObj[xPang_SOLO.checkPangObjX[xPang_SOLO.selectCnt]][xPang_SOLO.checkPangObjY[xPang_SOLO.selectCnt]].x, xPang_SOLO.xObj[xPang_SOLO.checkPangObjX[xPang_SOLO.selectCnt]][xPang_SOLO.checkPangObjY[xPang_SOLO.selectCnt]].y);
                        xPang_SOLO.isAutoKey = false;
                        break;
                    default:
                        if(xPang_SOLO.selectCnt >= xPang_SOLO.totalCheckPangObj)
                        {
                            touchTypeTemp = MH_KEY_RELEASEEVENT;
                            touchType = USER_POINT_RELEASE_EVENT;
                            xPang_SOLO.isAutoKey = true;
                            keyPang_Solo(USER_POINT_RELEASE_EVENT, cx, cy);
                            xPang_SOLO.isAutoKey = false;
                        }
                        else
                        {
                            touchTypeTemp = MH_KEY_PRESSEVENT;
                            touchType = USER_POINT_MOVE_EVENT;
                            xPang_SOLO.isAutoKey = true;
                            keyPang_Solo(USER_POINT_MOVE_EVENT, xPang_SOLO.xObj[xPang_SOLO.checkPangObjX[xPang_SOLO.selectCnt]][xPang_SOLO.checkPangObjY[xPang_SOLO.selectCnt]].x, xPang_SOLO.xObj[xPang_SOLO.checkPangObjX[xPang_SOLO.selectCnt]][xPang_SOLO.checkPangObjY[xPang_SOLO.selectCnt]].y);
                            xPang_SOLO.isAutoKey = false;
                        }
                        break;
                }
            }
        }
    }
    //////////20160617 오토팡
    
    
    
    
    
    //댄스팡 오브젝트
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        for(int j = 0; j < PANG_SOLO_HEIGHT; j++)
        {
            if(xPang_SOLO.xObj[i][j].state == PANG_SOLO_OBJSTATE_DONT)
                continue;
            if(xPang_SOLO.xObj[i][j].type != PANG_SOLO_OBJTYPE_DONT)
            {
                effX = 0;
                effY = 0;
                if(xPang_SOLO.isSelect == true)
                {
                    for(int k = 0; k < xPang_SOLO.selectCnt; k++)
                    {
                        if(xPang_SOLO.selectOBJ[k].x == i && xPang_SOLO.selectOBJ[k].y == j)
                        {
                            
                            switch (xPang_SOLO.selectOBJ[k].effCnt)
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
                
                if(xPang_SOLO.state != PANG_SOLO_STATE_PAUSE)
                    drawImage(&imgPang_SOLO_Obj, xPang_SOLO.xObj[i][j].x+effX, xPang_SOLO.xObj[i][j].y+effY, 0, imgPang_SOLO_Obj.h/5*xPang_SOLO.xObj[i][j].type, imgPang_SOLO_Obj.w, imgPang_SOLO_Obj.h/5, VH);
            }
            
            if(xPang_SOLO.chargeState[i] == PANG_SOLO_CHARGESTATE_MOVE)
            {
                drawImage(&imgPang_SOLO_Obj, xPang_SOLO.xObjSub[i].x, xPang_SOLO.xObjSub[i].y, 0, imgPang_SOLO_Obj.h/5*xPang_SOLO.xObjSub[i].type, imgPang_SOLO_Obj.w, imgPang_SOLO_Obj.h/5, VH);
            }
            /*
             sprintf(strTemp, "%d/%d", i,j);
             gSetColor(255, 255, 255);
             gDrawString(xPang.xObj[i][j].x, xPang.xObj[i][j].y, strTemp, VH, 30, FONT_XL);
             */
        }
    }
    
    if(xPang_SOLO.isSelect == true)
    {
        xGame.isBlend = true;
        xGame.blendType = BLEND_ADDP;
        for(int i = 0; i < xPang_SOLO.selectCnt; i++)
        {
            if(xPang_SOLO.selectOBJ[i].dir != PANG_SOLO_DIR_DONT)
            {
                switch (xPang_SOLO.selectOBJ[i].dir)
                {
                    case PANG_SOLO_DIR_12:
                        drawImage(&imgPang_SOLO_Dir[12], xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].x, xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].y, 0, 0, imgPang_SOLO_Dir[12].w, imgPang_SOLO_Dir[12].h, VH);
                        break;
                    case PANG_SOLO_DIR_2:
                        drawImage(&imgPang_SOLO_Dir[2], xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].x, xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].y, 0, 0, imgPang_SOLO_Dir[2].w, imgPang_SOLO_Dir[2].h, VH);
                        break;
                    case PANG_SOLO_DIR_4:
                        drawImage(&imgPang_SOLO_Dir[4], xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].x, xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].y, 0, 0, imgPang_SOLO_Dir[4].w, imgPang_SOLO_Dir[4].h, VH);
                        break;
                    case PANG_SOLO_DIR_6:
                        drawImage(&imgPang_SOLO_Dir[6], xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].x, xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].y, 0, 0, imgPang_SOLO_Dir[6].w, imgPang_SOLO_Dir[6].h, VH);
                        break;
                    case PANG_SOLO_DIR_8:
                        drawImage(&imgPang_SOLO_Dir[8], xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].x, xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].y, 0, 0, imgPang_SOLO_Dir[8].w, imgPang_SOLO_Dir[8].h, VH);
                        break;
                    case PANG_DIR_10:
                        drawImage(&imgPang_SOLO_Dir[10], xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].x, xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].y, 0, 0, imgPang_SOLO_Dir[10].w, imgPang_SOLO_Dir[10].h, VH);
                        break;
                }
            }
            
            effX = 0;
            effY = 0;
            switch (xPang_SOLO.selectOBJ[i].effCnt)
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
                xPang_SOLO.selectOBJ[i].effCnt++;
            
            drawImage(&imgPang_SOLO_ObjSelect, xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].x+effX, xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[i].x][xPang_SOLO.selectOBJ[i].y].y+effY, 0, 0, imgPang_SOLO_ObjSelect.w, imgPang_SOLO_ObjSelect.h, VH);
        }
        xGame.isBlend = false;
    }
    
    
    
    if(xPang_SOLO.state == PANG_SOLO_STATE_SORT)
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
    
    drawPang_SoloEff();
    drawPang_SoloCombo();
    drawPang_SoloScoreEff();
    
    subTemp[XPOS] = lcdW-50;
    subTemp[YPOS] = 50;
    drawImage(&imgPang_SOLO_Pause[0], subTemp[XPOS], subTemp[YPOS], 0, 0, imgPang_SOLO_Pause[0].w, imgPang_SOLO_Pause[0].h, VH);
    
    xPang_SOLO.xTouchPause.wPos = imgPang_SOLO_Pause[0].w;
    xPang_SOLO.xTouchPause.hPos = imgPang_SOLO_Pause[0].h;
    xPang_SOLO.xTouchPause.xPos = subTemp[XPOS]-xPang_SOLO.xTouchPause.wPos/2;
    xPang_SOLO.xTouchPause.yPos = subTemp[YPOS]-xPang_SOLO.xTouchPause.hPos/2;
    
    switch(xPang_SOLO.state)
    {
        case PANG_SOLO_STATE_READY:
            drawPang_SoloStart();
            break;
        case PANG_SOLO_STATE_GORESULT:
            drawPang_SoloTimeOver();
            break;
        case PANG_SOLO_STATE_RESULT:
            drawPang_SoloResult();
            break;
        case PANG_SOLO_STATE_CHANGERANK:
            drawRankChange_luluPang();
            break;
        case PANG_SOLO_STATE_PAUSE:
            drawBgFillRect();
            drawImage(&imgPang_SOLO_Pause[1], px, py, 0, 0, imgPang_SOLO_Pause[1].w, imgPang_SOLO_Pause[1].h, VH);
            
            xPang_SOLO.xTouchPauseGoLobby.wPos = 200;
            xPang_SOLO.xTouchPauseGoLobby.hPos = 100;
            xPang_SOLO.xTouchPauseGoLobby.xPos = px-xPang_SOLO.xTouchPauseGoLobby.wPos/2;
            xPang_SOLO.xTouchPauseGoLobby.yPos = py-xPang_SOLO.xTouchPauseGoLobby.hPos/2;
            
            subTemp[XPOS] = px + 200;
            subTemp[YPOS] = py - 100;
            
            xPang_SOLO.xTouchPauseExit.wPos = 80;
            xPang_SOLO.xTouchPauseExit.hPos = 80;
            xPang_SOLO.xTouchPauseExit.xPos = subTemp[XPOS] - xPang_SOLO.xTouchPauseExit.wPos/2;
            xPang_SOLO.xTouchPauseExit.yPos = subTemp[YPOS] - xPang_SOLO.xTouchPauseExit.hPos/2;
            
//            gSetColor(255, 0, 0);
//            setAlpha(100);
//            fillRect(xPang_SOLO.xTouchPauseExit.xPos, xPang_SOLO.xTouchPauseExit.yPos, xPang_SOLO.xTouchPauseExit.wPos, xPang_SOLO.xTouchPauseExit.hPos);
//            setAlpha(ALPHA_MAX);
            /*
             gSetColor(255, 0, 0);
             setAlpha(100);
             fillRect(xPang.xTouchPauseOk.xPos, xPang.xTouchPauseOk.yPos, xPang.xTouchPauseOk.wPos, xPang.xTouchPauseOk.hPos);
             setAlpha(ALPHA_MAX);
             */
            break;
    }
}


void makePang_SoloEff(int x,int y,int objType)
{
    int waitCnt = 0;
    for(int i=0;i<PANGEFFMAX;i++)
    {
        if(xPang_SOLO_Eff.isPlay[i] == true)
            waitCnt++;
    }
    
    for(int i=0;i<PANGEFFMAX;i++)
    {
        if(xPang_SOLO_Eff.isPlay[i] == false)
        {
            xPang_SOLO_Eff.isPlay[i] = true;
            xPang_SOLO_Eff.anyCnt[i] = 0;
            xPang_SOLO_Eff.waitCnt[i] = waitCnt;
            xPang_SOLO_Eff.x[i] = x;
            xPang_SOLO_Eff.y[i] = y;
            xPang_SOLO_Eff.objType[i] = objType;
            
            xPang_SOLO_Eff.rot[i] = 0;
            xPang_SOLO_Eff.rotSpeed[i] = ranDom(-10,10);
            break;
        }
    }
}

void drawPang_SoloEff()
{
    //0~10 각도
    int scale = 100;
    int alpha = ALPHA_MAX;
    
    for(int i=0;i<PANGEFFMAX;i++)
    {
        if(xPang_SOLO_Eff.isPlay[i] == false)
            continue;
        if(xPang_SOLO_Eff.waitCnt[i]-- > 0)
        {
            drawImage(&imgPang_SOLO_Obj, xPang_SOLO.xObj[xPang_SOLO_Eff.x[i]][xPang_SOLO_Eff.y[i]].x, xPang_SOLO.xObj[xPang_SOLO_Eff.x[i]][xPang_SOLO_Eff.y[i]].y, 0, imgPang_SOLO_Obj.h/5*xPang_SOLO_Eff.objType[i], imgPang_SOLO_Obj.w, imgPang_SOLO_Obj.h/5, VH);
            continue;
        }
        
        scale = 100;
        alpha = ALPHA_MAX;
        
        switch(xPang_SOLO_Eff.anyCnt[i])
        {
            case 0:alpha=100;scale=100;
                makeFire(xPang_SOLO.xObj[xPang_SOLO_Eff.x[i]][xPang_SOLO_Eff.y[i]].x, xPang_SOLO.xObj[xPang_SOLO_Eff.x[i]][xPang_SOLO_Eff.y[i]].y, 10);
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
        xGame.rotateNum = xPang_SOLO_Eff.rot[i]%360;
        
        
        drawImage(&imgPang_SOLO_Obj, xPang_SOLO.xObj[xPang_SOLO_Eff.x[i]][xPang_SOLO_Eff.y[i]].x, xPang_SOLO.xObj[xPang_SOLO_Eff.x[i]][xPang_SOLO_Eff.y[i]].y, 0, imgPang_SOLO_Obj.h/5*xPang_SOLO_Eff.objType[i], imgPang_SOLO_Obj.w, imgPang_SOLO_Obj.h/5, VH);
        
        xGame.isRotate = false;
        setAlpha(ALPHA_MAX);
        xGame.isReSizeDraw =false;
        
        for(int prcI=0;prcI<xGame.prcCnt*2;prcI++)
        {
            xPang_SOLO_Eff.rot[i] +=  xPang_SOLO_Eff.rotSpeed[i];
            if(++xPang_SOLO_Eff.anyCnt[i] > 24)
            {
                xPang_SOLO_Eff.isPlay[i] = false;
                
            }
        }
    }
}


bool isPang_SoloObjTouch()
{
    //	XTOUCH xTouch;
    int length = 0;
    int wNum = DONT;
    int hNum = DONT;
    int i = 0;
    int j = 0;
    
    
    
    if(xTouch.xPos < xPang_SOLO.xObjDir[0][0].x - imgPang_SOLO_Obj.w/2 || xTouch.xPos > xPang_SOLO.xObjDir[PANG_SOLO_WIDTH-1][0].x + imgPang_SOLO_Obj.w/2)
        return false;
    if(xTouch.yPos < xPang_SOLO.xObjDir[0][0].y - imgPang_SOLO_Obj.h/5/2 || xTouch.yPos > xPang_SOLO.xObjDir[0][PANG_SOLO_HEIGHT-1].y + imgPang_SOLO_Obj.h/5/2)
        return false;
    
    if(touchType == USER_POINT_PRESS_EVENT || touchType == USER_POINT_MOVE_EVENT)
    {
        for(i = 0; i < PANG_SOLO_WIDTH; i++)
        {
            for(j = 0; j < PANG_SOLO_HEIGHT; j++)
            {
                if(xPang_SOLO.selectCnt == 0)
                {
                    if(length == 0 || getPang_SoloObjLength(xTouch.xPos, xTouch.yPos, xPang_SOLO.xObjDir[i][j].x, xPang_SOLO.xObjDir[i][j].y) < length)
                    {
                        length = (int)getPang_SoloObjLength(xTouch.xPos, xTouch.yPos, xPang_SOLO.xObjDir[i][j].x, xPang_SOLO.xObjDir[i][j].y);
                        wNum = i;
                        hNum = j;
                    }
                }
                else
                {
                    if(length == 0 || (getPang_SoloObjLength(xTouch.xPos, xTouch.yPos, xPang_SOLO.xObjDir[i][j].x, xPang_SOLO.xObjDir[i][j].y) < length
                                       && xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].type == xPang_SOLO.xObjDir[i][j].type))
                    {
                        length = (int)getPang_SoloObjLength(xTouch.xPos, xTouch.yPos, xPang_SOLO.xObjDir[i][j].x, xPang_SOLO.xObjDir[i][j].y);
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
    
    if(xPang_SOLO.xObj[i][j].state == PANG_SOLO_OBJSTATE_DONT)
        return false;
    
    if(i == xPang_SOLO.currentSelectObj.x && j == xPang_SOLO.currentSelectObj.y)
        return false;
    
    if(xPang_SOLO.selectCnt > 1)
    {
        if(i == xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-2].x && j == xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-2].y)
        {
            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].x = DONT;
            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].y = DONT;
            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].type = PANG_SOLO_OBJTYPE_DONT;
            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].effCnt = 0;
            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-2].dir = PANG_SOLO_DIR_DONT;
            xPang_SOLO.selectCnt--;
            xPang_SOLO.currentSelectObj.x = i;
            xPang_SOLO.currentSelectObj.y = j;
            return false;
        }
    }
    
    if(xPang_SOLO.currentSelectObj.x != i || xPang_SOLO.currentSelectObj.y != j)
    {
        if(xPang_SOLO.selectCnt > 0)
        {
            for(int k = 0; k < xPang_SOLO.selectCnt; k++)
            {
                if (xPang_SOLO.xObjDir[i][j].type != xPang_SOLO.selectOBJ[0].type)
                {
                    return false;
                }
            }
            
            if(xPang_SOLO.currentSelectObj.x == 1 || xPang_SOLO.currentSelectObj.x == 3 || xPang_SOLO.currentSelectObj.x == 5)
            {
                if(i > xPang_SOLO.currentSelectObj.x+1 || i < xPang_SOLO.currentSelectObj.x-1 || j > xPang_SOLO.currentSelectObj.y+1 || j < xPang_SOLO.currentSelectObj.y-1)
                    return false;
                
                if(j == xPang_SOLO.currentSelectObj.y)
                {
                    if(i == xPang_SOLO.currentSelectObj.x)
                        return false;
                }
                else if(j < xPang_SOLO.currentSelectObj.y)
                {
                    if(i != xPang_SOLO.currentSelectObj.x)
                        return false;
                }
                else if(j > xPang_SOLO.currentSelectObj.y)
                {
                    if(i > xPang_SOLO.currentSelectObj.x+1 || i < xPang_SOLO.currentSelectObj.x-1)
                        return false;
                }
                else if(xPang_SOLO.xObjDir[i][j].type != xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].type)
                {
                    return false;
                }
            }
            else
            {
                if(i > xPang_SOLO.currentSelectObj.x+1 || i < xPang_SOLO.currentSelectObj.x-1 || j > xPang_SOLO.currentSelectObj.y+1 || j < xPang_SOLO.currentSelectObj.y-1)
                    return false;
                
                if(j == xPang_SOLO.currentSelectObj.y)
                {
                    if(i == xPang_SOLO.currentSelectObj.x)
                        return false;
                }
                else if(j < xPang_SOLO.currentSelectObj.y)
                {
                    if(i > xPang_SOLO.currentSelectObj.x+1 || i < xPang_SOLO.currentSelectObj.x-1)
                        return false;
                }
                else if(j > xPang_SOLO.currentSelectObj.y)
                {
                    if(i != xPang_SOLO.currentSelectObj.x)
                        return false;
                }
                else if(xPang_SOLO.xObjDir[i][j].type != xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].type)
                {
                    return false;
                }
            }
            
        }
        
        if(xPang_SOLO.selectCnt > 1)
        {
            for(int k = 0; k < xPang_SOLO.selectCnt; k++)
            {
                if(i == xPang_SOLO.selectOBJ[k].x && j == xPang_SOLO.selectOBJ[k].y)
                {
                    return false;
                }
            }
        }
        
        xPang_SOLO.currentSelectObj.x = i;
        xPang_SOLO.currentSelectObj.y = j;
        xPang_SOLO.currentSelectObj.type = xPang_SOLO.xObjDir[i][j].type;
        
        return true;
    }
    return false;
}

bool isPang_SoloObjCheck(int touchX, int touchY, int x, int y, int rad)
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
    
    pang_SOLO_X = xTouch.xPos;
    pang_SOLO_Y = xTouch.yPos;
    pang_SOLO_W = xTouch.wPos;
    pang_SOLO_H = xTouch.hPos;
    
    
    return touchCheck(&xTouch);
}


void keyPang_Solo(int type, int param1, int param2)
{
    bool isSame;
    
    if(xPang_SOLO.isNet_pangResult == true)
        return;
    if(touchCheck(&xTouchOk)==true && touchType == USER_POINT_PRESS_EVENT&& xLuluPang.isChangeRankEvent==TRUE)
    {
        xLuluPang.isChangeRankEvent=false;
        playSnd(SND_MENU_OK);
        xWorldMap.isKeyReturn = true;
        setPang_SoloState(PANG_SOLO_STATE_RESULT);
    }

    switch (xPang_SOLO.state)
    {
        case PANG_SOLO_STATE_PAUSE:
            if(touchCheck(&xPang_SOLO.xTouchPauseGoLobby) == true && touchType == USER_POINT_PRESS_EVENT)
            {
                playSnd(SND_MENU_OK);
                xWorldMap.isKeyReturn = true;
                freePang_SoloImg();
                xLuluPangLobby.state=LULUPANG_LOBBY_STATE_MAIN;
				LuluPangLobbyFreeLoad(false);
				xWorldMap.state=WORLDMAP_STATE_PLAY;
            }
            else if(touchCheck(&xPang_SOLO.xTouchPauseExit) == true && touchType == USER_POINT_PRESS_EVENT)
            {
                playSnd(SND_MENU_OK);
                xWorldMap.isKeyReturn = true;
                xPang_SOLO.state = PANG_SOLO_STATE_PLAY;
            }
            break;
        case PANG_SOLO_STATE_RESULT:
            if(touchTypeTemp == MH_KEY_PRESSEVENT)
            {
                if(touchCheck(&xPang_SOLO.xTouchExit) == true && touchType == USER_POINT_PRESS_EVENT)
                {
//                    playSnd(SND_MENU_OK);
//                    xWorldMap.isKeyReturn = true;
//                    
//                    freePang_SoloImg();
//                    initLuluPangLobby();
//                    xLuluPang.state=LULUPANG_STATE_LOBBY;
//                    xLuluPangLobby.state=LULUPANG_LOBBY_STATE_MAIN;
					playSnd(SND_MENU_OK);
					xWorldMap.isKeyReturn = true;
					freePang_SoloImg();
					xLuluPangLobby.state=LULUPANG_LOBBY_STATE_MAIN;
					LuluPangLobbyFreeLoad(false);
					xWorldMap.state=WORLDMAP_STATE_PLAY;
                }
				
                else if(touchCheck(&xPang_SOLO.xTouchReStart)==true && touchType == USER_POINT_PRESS_EVENT)
                {
                    if(xSaveTemp.tired.oriData<xLuluPang.TiredCost)
                    {
                        setPopup(POPUP_TIREDEMPTY, playState, playState, 0, DONT);
                    }
                    else
                    {
                        xLuluPang.state=LULUPANG_STATE_PLAY;
//                        setTired(-10);
                        initPang_Solo();
                    }
                }
            }
            break;
        case PANG_SOLO_STATE_PLAY:
            if(touchCheck(&xPang_SOLO.xTouchPause) == true && touchType == USER_POINT_PRESS_EVENT)
            {
                playSnd(SND_MENU_OK);
                xWorldMap.isKeyReturn = true;
                xPang_SOLO.state = PANG_SOLO_STATE_PAUSE;
            }
            //////////20160617 오토팡
            else if(touchCheck(&xPang_SOLO.xTouchAutoPang) == true && touchType == USER_POINT_PRESS_EVENT)
            {
                playSnd(SND_MENU_OK);
                xWorldMap.isKeyReturn = true;
                if(xPang_SOLO.isAutoPang == true)
                {
                    xPang_SOLO.isAutoPang = false;
                    
                    if(xPang_SOLO.totalCheckPangObj > 0)
                    {
                        touchTypeTemp = MH_KEY_RELEASEEVENT;
                        touchType = USER_POINT_RELEASE_EVENT;
                        
                        xPang_SOLO.isAutoKey = true;
                        keyPang_Solo(USER_POINT_RELEASE_EVENT, cx, cy);
                        xPang_SOLO.isAutoKey = false;
                    }
                    
                    
                }
                else
                    xPang_SOLO.isAutoPang = true;
            }
            else if(xPang_SOLO.isAutoPang == true && xPang_SOLO.isAutoKey == false)
            {
                xWorldMap.isKeyReturn = false;
            }
            //////////20160617 오토팡
            else
            {
                if(touchTypeTemp == MH_KEY_PRESSEVENT)
                {
                    if(xPang_SOLO.selectCnt == 0)
                    {
                        xPang_SOLO.checkTouchX[0] = xTouch.xPos;
                        xPang_SOLO.checkTouchY[0] = xTouch.yPos;
                        xPang_SOLO.checkTouchX[1] = xTouch.xPos;
                        xPang_SOLO.checkTouchY[1] = xTouch.yPos;
                        xPang_SOLO.checkTouchXPang[xPang_SOLO.totalCheckTouchPang] = xPang_SOLO.checkTouchX[0];
                        xPang_SOLO.checkTouchYPang[xPang_SOLO.totalCheckTouchPang] = xPang_SOLO.checkTouchY[0];
                        xPang_SOLO.totalCheckTouchPang++;
                    }
                    else
                    {
                        xPang_SOLO.checkTouchX[1] = xTouch.xPos;
                        xPang_SOLO.checkTouchY[1] = xTouch.yPos;
                    }
                    xPang_SOLO.totalCheckTouchPang = 0;
                    
                    
                    //바로전 터치좌표 저장
                    //현재 터치좌표 저장후
                    //속도별 이동체크
                    while (true)
                    {
                        int targetX = xPang_SOLO.checkTouchX[1];
                        int targetY = xPang_SOLO.checkTouchY[1];
                        int nowX = xPang_SOLO.checkTouchX[0];
                        int nowY = xPang_SOLO.checkTouchY[0];
                        
                        float rad = getArcTan(nowX,nowY,targetX,targetY);
                        float speedMax = getRadiusSpeed(targetX,targetY,nowX,nowY,rad);
                        
                        
                        if(speedMax <= 10)
                        {
                            xPang_SOLO.checkTouchX[0] = xPang_SOLO.checkTouchX[1];
                            xPang_SOLO.checkTouchY[0] = xPang_SOLO.checkTouchY[1];
                            
                            xPang_SOLO.checkTouchXPang[xPang_SOLO.totalCheckTouchPang] = xPang_SOLO.checkTouchX[0];
                            xPang_SOLO.checkTouchYPang[xPang_SOLO.totalCheckTouchPang] = xPang_SOLO.checkTouchY[0];
                            xPang_SOLO.totalCheckTouchPang++;
                            break;
                        }
                        else
                        {
                            getRadiusPos(nowX,nowY,10,rad);
                            xPang_SOLO.checkTouchX[0] = xRadius.pos[XPOS];
                            xPang_SOLO.checkTouchY[0] = xRadius.pos[YPOS];
                            xPang_SOLO.checkTouchXPang[xPang_SOLO.totalCheckTouchPang] = xPang_SOLO.checkTouchX[0];
                            xPang_SOLO.checkTouchYPang[xPang_SOLO.totalCheckTouchPang] = xPang_SOLO.checkTouchY[0];
                            xPang_SOLO.totalCheckTouchPang++;
                        }
                    }
                    
                    for(int reI = 0;reI<xPang_SOLO.totalCheckTouchPang;reI++)
                    {
                        xTouch.xPos = xPang_SOLO.checkTouchXPang[reI];
                        xTouch.yPos = xPang_SOLO.checkTouchYPang[reI];
                        
                        if(isPang_SoloObjTouch() == true)
                        {
                            xPang_SOLO.isSelect = true;
                            isSame = false;
                            
                            if(xPang_SOLO.selectCnt > 0)
                            {
                                if(xPang_SOLO.xObjDir[xPang_SOLO.currentSelectObj.x][xPang_SOLO.currentSelectObj.y].y  < xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].x][xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].y].y)
                                {
                                    if(xPang_SOLO.xObjDir[xPang_SOLO.currentSelectObj.x][xPang_SOLO.currentSelectObj.y].x  < xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].x][xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].y].x)
                                        xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].dir = PANG_SOLO_DIR_10;
                                    else if(xPang_SOLO.xObjDir[xPang_SOLO.currentSelectObj.x][xPang_SOLO.currentSelectObj.y].x  > xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].x][xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].y].x)
                                        xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].dir = PANG_SOLO_DIR_2;
                                    else
                                        xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].dir = PANG_SOLO_DIR_12;
                                }
                                else if(xPang_SOLO.xObjDir[xPang_SOLO.currentSelectObj.x][xPang_SOLO.currentSelectObj.y].y  > xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].x][xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].y].y)
                                {
                                    if(xPang_SOLO.xObjDir[xPang_SOLO.currentSelectObj.x][xPang_SOLO.currentSelectObj.y].x  < xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].x][xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].y].x)
                                        xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].dir = PANG_SOLO_DIR_8;
                                    else if(xPang_SOLO.xObjDir[xPang_SOLO.currentSelectObj.x][xPang_SOLO.currentSelectObj.y].x  > xPang_SOLO.xObjDir[xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].x][xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].y].x)
                                        xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].dir = PANG_SOLO_DIR_4;
                                    else
                                        xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt-1].dir = PANG_SOLO_DIR_6;
                                }
                            }
                            
                            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt].x = xPang_SOLO.currentSelectObj.x;
                            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt].y = xPang_SOLO.currentSelectObj.y;
                            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt].type = xPang_SOLO.currentSelectObj.type;
                            xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt].effCnt = 0;
                            xPang_SOLO.selectCnt++;
                        }
                    }
                }
                else if(touchTypeTemp == MH_KEY_RELEASEEVENT)
                {
                    //댄스팡 터졌을때
                    if(xPang_SOLO.selectCnt >= PANG_SOLO_EFFECT_MIN)
                    {
                        //콤보연산
//                        if(xPang_SOLO.comboCnt == DONT || (xCalendar.nowMilSec - xPang_SOLO.comboTime < 100000))
                        if(xPang_SOLO.comboCnt == DONT || (xCalendar.nowMilSec - xPang_SOLO.comboTime < 2000))
                        {
                            ++xPang_SOLO.comboCnt;
                            if(xPang_SOLO.comboCnt > 0)
                            {
                                makePang_SoloCombo(xPang_SOLO.xObj[xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt/2].x][xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt/2].y].x,xPang_SOLO.xObj[xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt/2].y][xPang_SOLO.selectOBJ[xPang_SOLO.selectCnt/2].y].y,xPang_SOLO.comboCnt);
                                
                                //최대콤보
                                if(xPang_SOLO.comboCnt > xPang_SOLO.totalCombo)
                                    xPang_SOLO.totalCombo = xPang_SOLO.comboCnt;
                                
                            }
                        }
                        else
                        {
                            xPang_SOLO.comboCnt = 0;
                        }
                        xPang_SOLO.comboTime = xCalendar.nowMilSec;
                        
                        
                        for(int i = 0; i < xPang_SOLO.selectCnt; i++)
                        {
                            makePang_SoloEff(xPang_SOLO.selectOBJ[i].x,xPang_SOLO.selectOBJ[i].y,xPang_SOLO.selectOBJ[i].type);
                            delPang_SoloObj(xPang_SOLO.selectOBJ[i].x, xPang_SOLO.selectOBJ[i].y);
                        }
                        xPang_SOLO.state = PANG_SOLO_STATE_EFFECT;
                        xPang_SOLO.beforeState = PANG_SOLO_STATE_EFFECT;
                        checkBlankPang_Solo();
                        //점수계산
                        setPang_SoloScore();
                        
                        
                    }
                    
                    //댄스팡 게임 상태 리셋
                    xPang_SOLO.isSelect = false;
                    xPang_SOLO.autoPangSpeed = 0;
                    xPang_SOLO.selectCnt = 0;
                    xPang_SOLO.currentSelectObj.x = DONT;
                    xPang_SOLO.currentSelectObj.y = DONT;
                    xPang_SOLO.currentSelectObj.type = PANG_SOLO_OBJTYPE_DONT;
                    xPang_SOLO.currentSelectObj.dir = PANG_SOLO_DIR_DONT;
                    for(int i = 0; i < PANG_SOLO_OBJ_MAX; i++)
                    {
                        xPang_SOLO.selectOBJ[i].x = DONT;
                        xPang_SOLO.selectOBJ[i].y = DONT;
                        xPang_SOLO.selectOBJ[i].type = PANG_SOLO_OBJTYPE_DONT;
                        xPang_SOLO.selectOBJ[i].dir = PANG_SOLO_DIR_DONT;
                        xPang_SOLO.selectOBJ[i].effCnt = 0;
                    }
                }
            }
            break;
    }
}

void addPang_SoloScoreCombo(int type,int score)
{
    setSecurity(&xPang_SOLO.comboScore[type], xPang_SOLO.comboScore[type].oriData+score);
}
void addPang_SoloScore(int type,int score)
{
    setSecurity(&xPang_SOLO.score[type], xPang_SOLO.score[type].oriData+score);
}

void addPang_SoloScoreBuff(int type,int score)
{
    setSecurity(&xPang_SOLO.buffScore[type], xPang_SOLO.buffScore[type].oriData+score);
}



void setPang_SoloScore()
{
    int objType = xPang_SOLO.selectOBJ[0].type;
   
    int defaultScore = 0;
    int replyScore = 0;
    float modelbuff = 0.0f;
    float combobuff = 1.0f;
    
    if(xPang_SOLO.selectCnt==3)
    {
        defaultScore = xPang_SOLO.DEFAULTSCORE*(xPang_SOLO.selectCnt-2);
    }
    
    else
    {
        switch (xPang_SOLO.selectCnt-3)
        {
            case 0:
                defaultScore = xPang_SOLO.DEFAULTSCORE;
                break;
            case 1:
                defaultScore = xPang_SOLO.DEFAULTSCORE*3;
                break;
            case 2:
                defaultScore = xPang_SOLO.DEFAULTSCORE*7;
                break;
            case 3:
                defaultScore = xPang_SOLO.DEFAULTSCORE*9;
                break;
            case 4:
                defaultScore = xPang_SOLO.DEFAULTSCORE*11;
                break;
            case 5:
                defaultScore = xPang_SOLO.DEFAULTSCORE*13;
                break;
            case 6:
                defaultScore = xPang_SOLO.DEFAULTSCORE*15;
                break;
            default:
                defaultScore = xPang_SOLO.DEFAULTSCORE*17;
                break;
        }
    }
    
    for(int k=0;k<FASHIONWEEKSETTINGMAX;k++)
    {
        defaultScore = defaultScore + getPangBuffScore_LuluPang(xLuluPangModel[k].modelKey);
    }
    
    xPang_SOLO.effCnt[objType] = 0;
    
    
    if(xPang_SOLO.comboCnt>3)
    {
        if(xPang_SOLO.comboCnt>3&&xPang_SOLO.comboCnt<6)
        {
           combobuff=2.5;
        }
        else if(xPang_SOLO.comboCnt>5&&xPang_SOLO.comboCnt<8)
        {
            combobuff=3.0;
        }
        else if(xPang_SOLO.comboCnt>7&&xPang_SOLO.comboCnt<10)
        {
            combobuff=3.5;
        }
        else if(xPang_SOLO.comboCnt>9&&xPang_SOLO.comboCnt<12)
        {
            combobuff=4.0;
        }
        else if(xPang_SOLO.comboCnt>11&&xPang_SOLO.comboCnt<14)
        {
            combobuff=4.5;
        }
        else if(xPang_SOLO.comboCnt>13&&xPang_SOLO.comboCnt<16)
        {
            combobuff=5.0;
        }
        else if(xPang_SOLO.comboCnt>15&&xPang_SOLO.comboCnt<18)
        {
            combobuff=5.5;
        }
        else if(xPang_SOLO.comboCnt>17&&xPang_SOLO.comboCnt<20)
        {
            combobuff=6.0;
        }
        else if(xPang_SOLO.comboCnt>19&&xPang_SOLO.comboCnt<24)
        {
            combobuff=6.5;
        }
        else if(xPang_SOLO.comboCnt>23&&xPang_SOLO.comboCnt<28)
        {
            combobuff=7.0;
        }
        else if(xPang_SOLO.comboCnt>27&&xPang_SOLO.comboCnt<32)
        {
            combobuff=7.5;
        }
        else if(xPang_SOLO.comboCnt>31&&xPang_SOLO.comboCnt<36)
        {
            combobuff=8.0;
        }
        else if(xPang_SOLO.comboCnt>35&&xPang_SOLO.comboCnt<40)
        {
            combobuff=8.5;
        }
        else if(xPang_SOLO.comboCnt>39&&xPang_SOLO.comboCnt<44)
        {
            combobuff=9.0;
        }
        else if(xPang_SOLO.comboCnt>43&&xPang_SOLO.comboCnt<48)
        {
            combobuff=9.5;
        }
        else if(xPang_SOLO.comboCnt>47&&xPang_SOLO.comboCnt<52)
        {
            combobuff=10.0;
        }
        else if(xPang_SOLO.comboCnt>51&&xPang_SOLO.comboCnt<56)
        {
            combobuff=10.5;
        }
        else if(xPang_SOLO.comboCnt>55&&xPang_SOLO.comboCnt<60)
        {
            combobuff=11.0;
        }
        else if(xPang_SOLO.comboCnt>59&&xPang_SOLO.comboCnt<64)
        {
           combobuff=11.5;
        }
        else if(xPang_SOLO.comboCnt>63&&xPang_SOLO.comboCnt<68)
        {
            combobuff=12.0;
        }
        else if(xPang_SOLO.comboCnt>67&&xPang_SOLO.comboCnt<72)
        {
            combobuff=12.5;
        }
        else if(xPang_SOLO.comboCnt>71&&xPang_SOLO.comboCnt<76)
        {
            combobuff=13.0;
        }
        else if(xPang_SOLO.comboCnt>75&&xPang_SOLO.comboCnt<80)
        {
            combobuff=13.5;
        }
        else if(xPang_SOLO.comboCnt>79&&xPang_SOLO.comboCnt<84)
        {
            combobuff=14.0;
        }
        else if(xPang_SOLO.comboCnt>83&&xPang_SOLO.comboCnt<88)
        {
            combobuff=14.5;
        }
        else if(xPang_SOLO.comboCnt>87&&xPang_SOLO.comboCnt<92)
        {
            combobuff=15.0;
        }
        else if(xPang_SOLO.comboCnt>91&&xPang_SOLO.comboCnt<96)
        {
            combobuff=15.5;
        }
        else if(xPang_SOLO.comboCnt>95&&xPang_SOLO.comboCnt<100)
        {
            combobuff=16.0;
        }
        else
        {
            combobuff=16.5;
        }
    }
    
    modelbuff = getPangBuffmagnification_Lulupang(xLuluPangModel[objType].modelKey);
    
    replyScore = defaultScore*(modelbuff+combobuff);
    //기본점수
    addPang_SoloScore(objType,replyScore);
    
    switch(xPang_SOLO.comboCnt)
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
    initSecurity(&xPang_SOLO.totalScore, (xPang_SOLO.score[0].oriData
                                     +xPang_SOLO.score[1].oriData
                                     +xPang_SOLO.score[2].oriData
                                     +xPang_SOLO.score[3].oriData
                                     +xPang_SOLO.score[4].oriData
                                     ));
    
    setPang_SoloScoreEff(290,cy-60+(objType*80),0,replyScore);
}

void setPang_SoloState(int state)
{
    xPang_SOLO.state = state;
    xPang_SOLO.anyCnt = 0;
    
}

bool checkPang_Solo()
{
    XPANG_SOLO_OBJ obj[PANG_SOLO_OBJ_TYPE_MAX][PANG_SOLO_OBJ_MAX];
    int objType[PANG_SOLO_OBJ_TYPE_MAX];
    int totalNum[PANG_SOLO_OBJ_TYPE_MAX];
    bool isExist = false;
    int num = 0;
    
    objType[PANG_SOLO_OBJTYPE_GOLD] = PANG_SOLO_OBJTYPE_GOLD;
    objType[PANG_SOLO_OBJTYPE_CLOVER] = PANG_SOLO_OBJTYPE_CLOVER;
    objType[PANG_SOLO_OBJTYPE_JUWEL] = PANG_SOLO_OBJTYPE_JUWEL;
    objType[PANG_SOLO_OBJTYPE_MUSIC] = PANG_SOLO_OBJTYPE_MUSIC;
    objType[PANG_SOLO_OBJTYPE_HEART] = PANG_SOLO_OBJTYPE_HEART;
    
    totalNum[PANG_SOLO_OBJTYPE_GOLD] = 0;
    totalNum[PANG_SOLO_OBJTYPE_CLOVER] = 0;
    totalNum[PANG_SOLO_OBJTYPE_JUWEL] = 0;
    totalNum[PANG_SOLO_OBJTYPE_MUSIC] = 0;
    totalNum[PANG_SOLO_OBJTYPE_HEART] = 0;
    
    //각 오브젝트별 총 갯수 및 위치 저장
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        for(int j = 0; j < PANG_SOLO_HEIGHT; j++)
        {
            if(xPang_SOLO.xObjDir[i][j].state == PANG_SOLO_OBJSTATE_PLAY)
            {
                obj[xPang_SOLO.xObjDir[i][j].type][totalNum[xPang_SOLO.xObjDir[i][j].type]].x = i;
                obj[xPang_SOLO.xObjDir[i][j].type][totalNum[xPang_SOLO.xObjDir[i][j].type]].y = j;
                obj[xPang_SOLO.xObjDir[i][j].type][totalNum[xPang_SOLO.xObjDir[i][j].type]].type = xPang_SOLO.xObjDir[i][j].type;
                totalNum[xPang_SOLO.xObjDir[i][j].type]++;
            }
        }
    }
    
    for(int k = 0; k < PANG_SOLO_OBJ_TYPE_MAX; k++)
    {
        num = 0;
        for(int i = 0; i < totalNum[k]; i++)
        {
            xPang_SOLO.totalCheckPangObj = 0;
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
                        xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj] = obj[k][i].x;
                        xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj++] = obj[k][i].y;
                        
                        xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj] = obj[k][j].x;
                        xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj++] = obj[k][j].y;
                        
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
                        xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj] = obj[k][i].x;
                        xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj++] = obj[k][i].y;
                        
                        xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj] = obj[k][j].x;
                        xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj++] = obj[k][j].y;
                        
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
                                xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj] = obj[k][t].x;
                                xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj++] = obj[k][t].y;
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
                                xPang_SOLO.checkPangObjX[xPang_SOLO.totalCheckPangObj] = obj[k][t].x;
                                xPang_SOLO.checkPangObjY[xPang_SOLO.totalCheckPangObj++] = obj[k][t].y;
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

void sortPang_Solo()
{
    XPANG_SOLO_OBJ obj;
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
    
    xPang_SOLO.xObjDir[0][0].state = xPang_SOLO.xObj[0][0].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[0][5].state = xPang_SOLO.xObj[0][5].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[1][5].state = xPang_SOLO.xObj[1][5].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[3][5].state = xPang_SOLO.xObj[3][5].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[5][5].state = xPang_SOLO.xObj[5][5].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[6][0].state = xPang_SOLO.xObj[6][0].state = PANG_SOLO_OBJSTATE_DONT;
    xPang_SOLO.xObjDir[6][5].state = xPang_SOLO.xObj[6][5].state = PANG_SOLO_OBJSTATE_DONT;
    
    
    for(int i = 0; i < PANG_SOLO_WIDTH; i++)
    {
        for(int j = 0; j < PANG_SOLO_HEIGHT; j++)
        {
            if(xPang_SOLO.xObjDir[i][j].state == PANG_SOLO_OBJSTATE_PLAY)
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
        
        obj.type = xPang_SOLO.xObj[dir[ran1][0]][dir[ran1][1]].type;
        xPang_SOLO.xObjDir[dir[ran1][0]][dir[ran1][1]].type = xPang_SOLO.xObj[dir[ran1][0]][dir[ran1][1]].type = xPang_SOLO.xObj[dir[ran2][0]][dir[ran2][1]].type;
        xPang_SOLO.xObjDir[dir[ran2][0]][dir[ran2][1]].type = xPang_SOLO.xObj[dir[ran2][0]][dir[ran2][1]].type = obj.type;
    }
}

double getPang_SoloObjLength(int x1, int y1, int x2, int y2)
{
    double result = 0.f, val=0.f;
    int w,h;
    w = x2 - x1;
    h = y2 - y1;
    val = (w*w) + (h*h);
    result = sqrt(val);
    return result;
}

void loadPang_SoloImg()
{
    
    loadImg("lulupang_bg0.png", &imgPang_SOLO_BG[0]);
    loadImgDocuments("pang_bg1.png",&imgPang_SOLO_BG[1]);
    loadImgDocuments("pang_bg2.png",&imgPang_SOLO_BG[2]);
    loadImgDocuments("pang_bg3.png",&imgPang_SOLO_BG[3]);
    
    
    loadImgDocuments("pangpause0.png",&imgPang_SOLO_Pause[0]);
    loadImg("pangpause1.png",&imgPang_SOLO_Pause[1]);
    //////////20160617 오토팡
    loadImgDocuments("pangauto0.png", &imgPang_SOLO_Auto[0]);
    loadImgDocuments("pangauto1.png", &imgPang_SOLO_Auto[1]);
    loadImgDocuments("pangauto2.png", &imgPang_SOLO_Auto[2]);
    //////////20160617 오토팡
    
    loadImgDocuments("pangobj.png", &imgPang_SOLO_Obj);
    
    
    
    loadImgDocuments("pangnum0.png", &imgPang_SOLO_Num[0]);
    loadImgDocuments("pangnum1.png", &imgPang_SOLO_Num[1]);
    loadImgDocuments("pangnum2.png", &imgPang_SOLO_Num[2]);
    
    loadImgDocuments("pangobjselect.png", &imgPang_SOLO_ObjSelect);
    
    loadImgDocuments("pangstart0.png", &imgPang_SOLO_Start[0]);
    loadImgDocuments("pangstart1.png", &imgPang_SOLO_Start[1]);
    
    loadImgDocuments("pangtimeover.png", &imgPang_SOLO_Timeover);
    
    loadImgDocuments("pangcombo0.png", &imgPang_SOLO_Combo[0]);
    loadImgDocuments("pangcombo1.png", &imgPang_SOLO_Combo[1]);
    loadImgDocuments("pangcombo2.png", &imgPang_SOLO_Combo[2]);
    
    loadImgDocuments("pangdir2.png", &imgPang_SOLO_Dir[2]);
    loadImgDocuments("pangdir4.png", &imgPang_SOLO_Dir[4]);
    loadImgDocuments("pangdir6.png", &imgPang_SOLO_Dir[6]);
    loadImgDocuments("pangdir8.png", &imgPang_SOLO_Dir[8]);
    loadImgDocuments("pangdir10.png", &imgPang_SOLO_Dir[10]);
    loadImgDocuments("pangdir12.png", &imgPang_SOLO_Dir[12]);
    
    
    
    loadImgDocuments("panggear0.png", &imgPang_SOLO_Gear[0]);
    loadImgDocuments("panggear1.png", &imgPang_SOLO_Gear[1]);
    loadImgDocuments("panggear2.png", &imgPang_SOLO_Gear[2]);
    loadImgDocuments("panggear3.png", &imgPang_SOLO_Gear[3]);
    loadImgDocuments("panggear4.png", &imgPang_SOLO_Gear[4]);
    loadImgDocuments("panggear5.png", &imgPang_SOLO_Gear[5]);
    loadImgDocuments("panggear6.png", &imgPang_SOLO_Gear[6]);
    
    
    loadImg("lulupangui0.png", &imgPang_SOLO_Ui[0]);
    loadImg("lulupangui1.png", &imgPang_SOLO_Ui[1]);
    loadImgDocuments("pangui2.png", &imgPang_SOLO_Ui[2]);
    loadImgDocuments("pangui3.png", &imgPang_SOLO_Ui[3]);
    loadImgDocuments("pangui4.png", &imgPang_SOLO_Ui[4]);
    loadImgDocuments("pangui5.png", &imgPang_SOLO_Ui[5]);
    loadImgDocuments("pangui6.png", &imgPang_SOLO_Ui[6]);
    loadImgDocuments("pangui7.png", &imgPang_SOLO_Ui[7]);
    loadImg("pangui8.png", &imgPang_SOLO_Ui[8]);
    loadImg("pangui9.png", &imgPang_SOLO_Ui[9]);
    loadImg("pangui10.png", &imgPang_SOLO_Ui[10]);
    
    
}

void freePang_SoloImg()
{
    
    
    freeImg(&imgPang_SOLO_BG[0]);
    freeImg(&imgPang_SOLO_BG[1]);
    freeImg(&imgPang_SOLO_BG[2]);
    freeImg(&imgPang_SOLO_BG[3]);
    
    
    freeImg(&imgPang_SOLO_Pause[0]);
    freeImg(&imgPang_SOLO_Pause[1]);
    
    //////////20160617 오토팡
    freeImg(&imgPang_SOLO_Auto[0]);
    freeImg(&imgPang_SOLO_Auto[1]);
    freeImg(&imgPang_SOLO_Auto[2]);
    //////////20160617 오토팡
    
    
    
    freeImg(&imgPang_SOLO_Num[0]);
    freeImg(&imgPang_SOLO_Num[1]);
    freeImg(&imgPang_SOLO_Num[2]);
    
    freeImg(&imgPang_SOLO_ObjSelect);
    
    freeImg(&imgPang_SOLO_Start[0]);
    freeImg(&imgPang_SOLO_Start[1]);
    
    freeImg(&imgPang_SOLO_Timeover);
    
    freeImg(&imgPang_SOLO_Combo[0]);
    freeImg(&imgPang_SOLO_Combo[1]);
    freeImg(&imgPang_SOLO_Combo[2]);
    
    freeImg(&imgPang_SOLO_Dir[2]);
    freeImg(&imgPang_SOLO_Dir[4]);
    freeImg(&imgPang_SOLO_Dir[6]);
    freeImg(&imgPang_SOLO_Dir[8]);
    freeImg(&imgPang_SOLO_Dir[10]);
    freeImg(&imgPang_SOLO_Dir[12]);
    
    
    freeImg(&imgPang_SOLO_Gear[0]);
    freeImg(&imgPang_SOLO_Gear[1]);
    freeImg(&imgPang_SOLO_Gear[2]);
    freeImg(&imgPang_SOLO_Gear[3]);
    freeImg(&imgPang_SOLO_Gear[4]);
    freeImg(&imgPang_SOLO_Gear[5]);
    freeImg(&imgPang_SOLO_Gear[6]);
    
    
    freeImg(&imgPang_SOLO_Ui[0]);
    freeImg(&imgPang_SOLO_Ui[1]);
    freeImg(&imgPang_SOLO_Ui[2]);
    freeImg(&imgPang_SOLO_Ui[3]);
    freeImg(&imgPang_SOLO_Ui[4]);
    freeImg(&imgPang_SOLO_Ui[5]);
    freeImg(&imgPang_SOLO_Ui[6]);
    freeImg(&imgPang_SOLO_Ui[7]);
    freeImg(&imgPang_SOLO_Ui[8]);
    freeImg(&imgPang_SOLO_Ui[9]);
    freeImg(&imgPang_SOLO_Ui[10]);
}



void makePang_SoloCombo(int x,int y,int comboNum)
{
    for(int i=0;i<PANGCOMBOMAX;i++)
    {
        if(xPang_SOLO_Combo.isPlay[i] == false)
        {
            xPang_SOLO_Combo.isPlay[i] = true;
            xPang_SOLO_Combo.anyCnt[i] = 0;
            xPang_SOLO_Combo.x[i] = x;
            xPang_SOLO_Combo.y[i] = y;
            xPang_SOLO_Combo.comboNum[i] = comboNum;
            break;
        }
    }
}

void drawPang_SoloCombo()
{
    int alpha;
    int scale;
    int rot;
    
    
    for(int i=0;i<PANGCOMBOMAX;i++)
    {
        if(xPang_SOLO_Combo.isPlay[i] == false)
            continue;
        
        for(int kk=0;kk<2;kk++)
        {
            alpha = 100;
            scale = 100;
            rot = 0;
            
            switch(xPang_SOLO_Combo.anyCnt[i]-(kk*4))
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
                drawImage(&imgPang_SOLO_Combo[0], xPang_SOLO_Combo.x[i], xPang_SOLO_Combo.y[i], 0, 0, imgPang_SOLO_Combo[0].w, imgPang_SOLO_Combo[0].h, VH);
            }
            else
            {
                drawImage(&imgPang_SOLO_Combo[1], xPang_SOLO_Combo.x[i]-25, xPang_SOLO_Combo.y[i]+70, 0, 0, imgPang_SOLO_Combo[1].w, imgPang_SOLO_Combo[1].h, VH);
                drawNum(&imgPang_SOLO_Combo[2], xPang_SOLO_Combo.x[i]-5, xPang_SOLO_Combo.y[i]+70, xPang_SOLO_Combo.comboNum[i], -15,VL);
            }
            
            xGame.isRotate = false;
            xGame.isReSizeDraw = false;
            setAlpha(ALPHA_MAX);
        }
        
        for(int prcI=0;prcI<xGame.prcCnt;prcI++)
            ++xPang_SOLO_Combo.anyCnt[i];
        if(xPang_SOLO_Combo.anyCnt[i] > 40)
        {
            xPang_SOLO_Combo.isPlay[i] = false;
        }
    }
}




void drawPang_SoloStart()
{
    int px = cx;
    int py = cy;
    
    int alpha;
    int scale;
    int yy;
    int rot;
    switch(xPang_SOLO.anyCnt)
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
    
    drawImage(&imgPang_SOLO_Start[1], px, py+52, 0, 0, imgPang_SOLO_Start[1].w, imgPang_SOLO_Start[1].h, VH);
    xGame.isReSizeDraw = false;
    setAlpha(ALPHA_MAX);
    
    
    switch(xPang_SOLO.anyCnt)
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
    drawImage(&imgPang_SOLO_Start[0], px, py-52+yy, 0, 0, imgPang_SOLO_Start[0].w, imgPang_SOLO_Start[0].h, VH);
    
    xGame.isRotate = false;
    xGame.isReSizeDraw = false;
    setAlpha(ALPHA_MAX);
}


void drawPang_SoloTimeOver()
{
    int px = cx;
    int py = cy;
    int yy;
    int rot;
    
    switch(xPang_SOLO.anyCnt)
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
    
    
    
    drawImage(&imgPang_SOLO_Timeover, px, py+yy, 0, 0, imgPang_SOLO_Timeover.w, imgPang_SOLO_Timeover.h, VH);
    xGame.isRotate = false;
}


void drawPang_SoloResult()
{
    int px = cx;
    int py = cy;
    
    drawBgFillRect();
    drawImage(&imgPang_SOLO_Ui[1], px, py, 0, 0, imgPang_SOLO_Ui[1].w, imgPang_SOLO_Ui[1].h, VH);
    
    subTemp[XPOS] = px+255;
    subTemp[YPOS] = py-270;
    
    xPang_SOLO.xTouchExit.wPos = 100;
    xPang_SOLO.xTouchExit.hPos = 100;
    xPang_SOLO.xTouchExit.xPos = subTemp[XPOS]-xPang_SOLO.xTouchExit.wPos/2;
    xPang_SOLO.xTouchExit.yPos = subTemp[YPOS]-xPang_SOLO.xTouchExit.hPos/2;
    
    
    
//     gSetColor(255, 0, 0);
//     setAlpha(100);
//     fillRect(xPang_SOLO.xTouchExit.xPos, xPang_SOLO.xTouchExit.yPos, xPang_SOLO.xTouchExit.wPos, xPang_SOLO.xTouchExit.hPos);
//     setAlpha(ALPHA_MAX);
    

    for(int k=0;k<FASHIONWEEKSETTINGMAX;k++)
    {
        switch (k)
        {
            case 0:
                subTemp[XPOS] = px-147;
                subTemp[YPOS] = py-17;
                break;
            case 1:
                subTemp[XPOS] = px-10;
                subTemp[YPOS] = py-17;
                break;
            case 2:
                subTemp[XPOS] = px+127;
                subTemp[YPOS] = py-17;
                break;
            case 3:
                subTemp[XPOS] = px-78;
                subTemp[YPOS] = py+137;
                break;
            case 4:
                subTemp[XPOS] = px+58;
                subTemp[YPOS] = py+137;
                break;
            default:
                break;
        }
        
        //빈슬롯
        int invenModelSlot = DONT;
        if(xLuluPangModel[k].modelKey == DONT)
            invenModelSlot = DONT;
        else
        {
            invenModelSlot = getModelKeyToSlotNum(xLuluPangModel[k].modelKey);
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
                dy = subTemp[YPOS]+59;
                xGame.fgameScale = 0.6f;
            }
            else
            {
                dx = subTemp[XPOS];
                dy = subTemp[YPOS]+80;
                xGame.fgameScale = 0.7f;
            }
            xGame.fgameScaleCx = dx;
            xGame.fgameScaleCy = lcdH-(dy);
            gSetClip(true, subTemp[XPOS]-50, subTemp[YPOS]-54, 100, 88);
            drawFittingBody(dx, dy,&xFTemp,&xFaceTemp,TRUE,xModelData[code].sex);
            gSetClip(false, subTemp[XPOS]-50, subTemp[YPOS]-54, 100, 88);
//            gSetColor(0, 0, 255);
//            setAlpha(100);
//            fillRect(subTemp[XPOS]-50, subTemp[YPOS]-54, 100, 88);
//            setAlpha(ALPHA_MAX);
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
        int score = xPang_SOLO.score[k].oriData;
        setCommaNum(strTempS, score);
        gDrawString(subTemp[XPOS]+5, subTemp[YPOS]+50, strTempS, VH);
        setFontSize(11);
    }
    
    //베스트
    gSetColor(255, 255, 255);
    setFontSizeORI(20);
    setCommaNum(strTempS, xLuluPang.HighScore);
    gDrawStringBold(px+50, py-160, strTempS, VL, 255, 255, 255, 87, 50, 6);
    setFontSize(11);
    
    gSetColor(255, 255, 255);
    setFontSizeORI(20);
    if(xPang_SOLO.totalCombo<0)
    {
        sprintf(strTempS, "+0");
    }
    else
    {
        sprintf(strTempS, "+%d", xPang_SOLO.totalCombo);
    }
    gDrawStringBold(px+50, py-128, strTempS, VL, 255, 255, 255, 87, 50, 6);
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
    drawNum(&imgPang_SOLO_Ui[6], subTemp[XPOS], subTemp[YPOS], xPang_SOLO.totalScore.oriData, -8, VL);
    xGame.fgameScale = 1.0f;
    xGame.fgameScaleCx =cx;
    xGame.fgameScaleCy =cy;
    
    
    if(xPang_SOLO.totalScore.oriData == xLuluPang.HighScore)
    {
        drawImage(&imgPang_SOLO_Ui[2], subTemp[XPOS]+140, subTemp[YPOS]-35, 0, 0, imgPang_SOLO_Ui[2].w, imgPang_SOLO_Ui[2].h, VH);
    }
    
    subTemp[XPOS] = px;
    subTemp[YPOS] = py+240;
    drawImage(&imgPang_SOLO_Ui[8], subTemp[XPOS], subTemp[YPOS], 0, 0, imgPang_SOLO_Ui[8].w, imgPang_SOLO_Ui[8].h, VH);
    xPang_SOLO.xTouchReStart.wPos = imgPang_SOLO_Ui[8].w;
    xPang_SOLO.xTouchReStart.hPos = imgPang_SOLO_Ui[8].h;
    xPang_SOLO.xTouchReStart.xPos = subTemp[XPOS] - xPang_SOLO.xTouchReStart.wPos/2;
    xPang_SOLO.xTouchReStart.yPos = subTemp[YPOS] - xPang_SOLO.xTouchReStart.hPos/2;
    
    
    if(xPang_SOLO.isNet_pangResult == true)
        drawLoadingIcon(cx, cy);
}



void setPang_SoloScoreEff(int x,int y,int type,int num)
{
    for(int i=0;i<PANGSCOREEFFMAX;i++)
    {
        if(xPang_SOLO_ScoreEff[i].isPlay == false)
        {
            xPang_SOLO_ScoreEff[i].isPlay = true;
            xPang_SOLO_ScoreEff[i].anyCnt = 0;
            xPang_SOLO_ScoreEff[i].type = type;
            xPang_SOLO_ScoreEff[i].num = num;
            xPang_SOLO_ScoreEff[i].x = x;
            xPang_SOLO_ScoreEff[i].y = y;
            break;
        }
    }
}

void drawPang_SoloScoreEff()
{
    int scale;
    int yy;
    
    for(int i=0;i<PANGSCOREEFFMAX;i++)
    {
        if(xPang_SOLO_ScoreEff[i].isPlay == true)
        {
            switch(xPang_SOLO_ScoreEff[i].anyCnt)
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
                xGame.fgameScaleCx =xPang_SOLO_ScoreEff[i].x;
                xGame.fgameScaleCy =lcdH-(xPang_SOLO_ScoreEff[i].y+yy);
                xGame.fgameScale = xDrawObjCenter.reSize*0.01f;
            }
            
            
            drawNum(&imgPang_SOLO_Num[0+xPang_SOLO_ScoreEff[i].type], xPang_SOLO_ScoreEff[i].x, xPang_SOLO_ScoreEff[i].y+yy, xPang_SOLO_ScoreEff[i].num, -10, VH);
            xGame.fgameScale = 1.0f;
            xGame.fgameScaleCx =cx;
            xGame.fgameScaleCy =cy;
            
            for(int prcI=0;prcI<xGame.prcCnt;prcI++)
                ++xPang_SOLO_ScoreEff[i].anyCnt;
            
            if(xPang_SOLO_ScoreEff[i].anyCnt > 28)
            {
                xPang_SOLO_ScoreEff[i].isPlay = false;
            }
        }
    }
}


void drawPang_SoloGear()
{
    
    //왼쪽
    int px = 120;
    int py = lcdH-170;
    xPang_SOLO_Gear[0].type = 0;
    xPang_SOLO_Gear[0].x = px-107;
    xPang_SOLO_Gear[0].y = py-88;
    xPang_SOLO_Gear[0].speed = 10;
    
    
    xPang_SOLO_Gear[1].type = 1;
    xPang_SOLO_Gear[1].x = px;
    xPang_SOLO_Gear[1].y = py;
    xPang_SOLO_Gear[1].speed = 5;
    
    
    xPang_SOLO_Gear[2].type = 6;
    xPang_SOLO_Gear[2].x = px+150;
    xPang_SOLO_Gear[2].y = py+30;
    xPang_SOLO_Gear[2].speed = 13;
    
    
    xPang_SOLO_Gear[3].type = 5;
    xPang_SOLO_Gear[3].x = px+146;
    xPang_SOLO_Gear[3].y = py-69;
    xPang_SOLO_Gear[3].speed = 11;
    
    
    xPang_SOLO_Gear[4].type = 2;
    xPang_SOLO_Gear[4].x = px-73;
    xPang_SOLO_Gear[4].y = py-15;
    xPang_SOLO_Gear[4].speed = 3;
    
    
    
    xPang_SOLO_Gear[5].type = 4;
    xPang_SOLO_Gear[5].x = px+95;
    xPang_SOLO_Gear[5].y = py+32;
    xPang_SOLO_Gear[5].speed = 2;
    
    
    xPang_SOLO_Gear[6].type = 3;
    xPang_SOLO_Gear[6].x = px+56;
    xPang_SOLO_Gear[6].y = py-22;
    xPang_SOLO_Gear[6].speed = 1;
    
    
    //오른쪽
    px = lcdW-250;
    py = lcdH-140;
    
    xPang_SOLO_Gear[7].type = 6;
    xPang_SOLO_Gear[7].x = px+105;
    xPang_SOLO_Gear[7].y = py+25;
    xPang_SOLO_Gear[7].speed = 1;
    
    xPang_SOLO_Gear[8].type = 5;
    xPang_SOLO_Gear[8].x = px;
    xPang_SOLO_Gear[8].y = py;
    xPang_SOLO_Gear[8].speed = 2;
    
    xPang_SOLO_Gear[9].type = 6;
    xPang_SOLO_Gear[9].x = px+175;
    xPang_SOLO_Gear[9].y = py+75;
    xPang_SOLO_Gear[9].speed = 2;
    
    xPang_SOLO_Gear[10].type = 0;
    xPang_SOLO_Gear[10].x = px+213;
    xPang_SOLO_Gear[10].y = py-31;
    xPang_SOLO_Gear[10].speed = 3;
    
    xPang_SOLO_Gear[11].type = 4;
    xPang_SOLO_Gear[11].x = px+62;
    xPang_SOLO_Gear[11].y = py+53;
    xPang_SOLO_Gear[11].speed = 1;
    
    xPang_SOLO_Gear[12].type = 2;
    xPang_SOLO_Gear[12].x = px+175;
    xPang_SOLO_Gear[12].y = py+75;
    xPang_SOLO_Gear[12].speed = 2;
    
    xPang_SOLO_Gear[13].type = 3;
    xPang_SOLO_Gear[13].x = px+109;
    xPang_SOLO_Gear[13].y = py+57;
    xPang_SOLO_Gear[13].speed = 4;
    
    
    xGame.isRotate = true;
    for(int k=0;k<PANGGEARMAX;k++)
    {
        for(int prcI=0;prcI<xGame.prcCnt;prcI++)
            xPang_SOLO_Gear[k].rot += xPang_SOLO_Gear[k].speed;
        
        xPang_SOLO_Gear[k].rot = xPang_SOLO_Gear[k].rot%360;
        xGame.rotateNum = xPang_SOLO_Gear[k].rot;
        drawImage(&imgPang_SOLO_Gear[xPang_SOLO_Gear[k].type], xPang_SOLO_Gear[k].x, xPang_SOLO_Gear[k].y, 0, 0, imgPang_SOLO_Gear[xPang_SOLO_Gear[k].type].w,imgPang_SOLO_Gear[xPang_SOLO_Gear[k].type].h, VH);
    }
    xGame.isRotate = false;
    
}


void drawPang_SoloUi()
{
    
    int px = 0;
    int py = 0;
    //시간
    subTemp[XPOS] = 15;
    subTemp[YPOS] = 57;
    
    int gageW = xPang_SOLO.time.oriData*imgPang_SOLO_BG[3].w/xPang_SOLO.timeMax;
    
    drawImage(&imgPang_SOLO_BG[3], subTemp[XPOS], subTemp[YPOS], 0, 0, imgPang_SOLO_BG[3].w, imgPang_SOLO_BG[3].h/2, VL);
    drawImage(&imgPang_SOLO_BG[3], subTemp[XPOS], subTemp[YPOS], 0, imgPang_SOLO_BG[3].h/2, gageW, imgPang_SOLO_BG[3].h/2, VL);
    
    
    drawImage(&imgPang_SOLO_Ui[4], subTemp[XPOS]+100, subTemp[YPOS]-20, 0, 0, imgPang_SOLO_Ui[4].w, imgPang_SOLO_Ui[4].h, VH);
    
    
    
    xDrawObjCenter.reSize = 60;
    if(xDrawObjCenter.reSize != 100)
    {
        xGame.fgameScaleCx =subTemp[XPOS]+100+28;
        xGame.fgameScaleCy =lcdH-(subTemp[YPOS]-20);
        xGame.fgameScale = xDrawObjCenter.reSize*0.01f;
    }
    drawNum(&imgPang_SOLO_Ui[6], subTemp[XPOS]+100+28, subTemp[YPOS]-20, xPang_SOLO.time.oriData, -8, VH);
    xGame.fgameScale = 1.0f;
    xGame.fgameScaleCx =cx;
    xGame.fgameScaleCy =cy;
    
    px = 190;
    py = cy+30;
    //UI 각각의 의상 관련 점수판
    
    drawImage(&imgPang_SOLO_Ui[0], px, py, 0, 0, imgPang_SOLO_Ui[0].w, imgPang_SOLO_Ui[0].h, VH);
    
    
    for(int k=0;k<FASHIONWEEKSETTINGMAX;k++)
    {
        subTemp[XPOS] = px+3;
        subTemp[YPOS] = py-120+(k*77);
        
        //빈슬롯
        int invenModelSlot = DONT;
        if(xLuluPangModel[k].modelKey == DONT)
            invenModelSlot = DONT;
        else
        {
            invenModelSlot = getModelKeyToSlotNum(xLuluPangModel[k].modelKey);
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
                dx = subTemp[XPOS]-40;
                dy = subTemp[YPOS]+72;
                xGame.fgameScale = 0.6f;
            }
            else
            {
                dx = subTemp[XPOS]-40;
                dy = subTemp[YPOS]+93;
                xGame.fgameScale = 0.7f;
            }
            xGame.fgameScaleCx = dx;
            xGame.fgameScaleCy = lcdH-(dy);
            gSetClip(true, subTemp[XPOS]-88, subTemp[YPOS]-41, 100, 88);
            drawFittingBody(dx, dy,&xFTemp,&xFaceTemp,TRUE,xModelData[code].sex);
            gSetClip(false, subTemp[XPOS]-88, subTemp[YPOS]-41, 100, 88);
//            gSetColor(0, 0, 255);
//            setAlpha(100);
//            fillRect(subTemp[XPOS]-88, subTemp[YPOS]-41, 100, 88);
//            setAlpha(ALPHA_MAX);
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
        //색에 해당하는 점수 표기
        setFontSizeORI(25);
        setCommaNum(strTempS, xPang_SOLO.score[k].oriData);
        gDrawString(subTemp[XPOS]+103, subTemp[YPOS]+13, strTempS, VH);
        setFontSize(11);
        
        xPang_SOLO.effCnt[k]++;
        
        int alpha = 0;
        int scale = 0;
        
        switch(xPang_SOLO.effCnt[k])
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
            drawImage(&imgPang_SOLO_ObjSelect, subTemp[XPOS]-110, subTemp[YPOS]+13, 0, 0, imgPang_SOLO_ObjSelect.w, imgPang_SOLO_ObjSelect.h, VH);
            xGame.isReSizeDraw = false;
            setAlpha(ALPHA_MAX);
        }
        
        
        alpha = 0;
        switch(xPang_SOLO.effCnt[k])
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
            
            drawImage(&imgPang_SOLO_Obj, subTemp[XPOS]-110, subTemp[YPOS]+13, 0, imgPang_SOLO_Obj.h/5*k, imgPang_SOLO_Obj.w, imgPang_SOLO_Obj.h/5, VH);
            drawImage(&imgPang_SOLO_ObjSelect, subTemp[XPOS]-110, subTemp[YPOS]+13, 0, 0, imgPang_SOLO_ObjSelect.w, imgPang_SOLO_ObjSelect.h, VH);
            xGame.isReSizeDraw = false;
            setAlpha(ALPHA_MAX);
        }
    }
    
    //베스트
    gSetColor(255, 255, 255);
    setFontSizeORI(20);
    setCommaNum(strTempS, xLuluPang.HighScore);
    gDrawStringBold(px+40, py-187, strTempS, VL, 255, 255, 255, 87, 50, 6);
    setFontSize(11);
    
    //콤보
    gSetColor(255, 255, 255);
    setFontSizeORI(20);
    if(xPang_SOLO.comboCnt<0)
    {
        sprintf(strTempS, "+0");
    }
    else
    {
        sprintf(strTempS, "+%d",xPang_SOLO.totalCombo);
    }
    gDrawStringBold(px+40, py-160, strTempS, VL, 255, 255, 255, 87, 50, 6);
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
    drawNum(&imgPang_SOLO_Ui[6], subTemp[XPOS], subTemp[YPOS], xPang_SOLO.totalScore.oriData, -8, VH);
    xGame.fgameScale = 1.0f;
    xGame.fgameScaleCx =cx;
    xGame.fgameScaleCy =cy;
}

void drawRankChange_luluPang()
{
    int px = cx;
    int py = cy;
    int startAnyCnt;
    
    startAnyCnt = xLuluPang.rankChangeAnyCnt;
    
    switch (startAnyCnt)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            break;
    }
    
    drawImage(&imgPang_SOLO_Ui[10], px, py, 0, 0, imgPang_SOLO_Ui[10].w, imgPang_SOLO_Ui[10].h, VH);
    
    startAnyCnt = xLuluPang.rankChangeAnyCnt-5;
    int changeX = 0;
    int changeY = -94;
    
    switch (startAnyCnt)
    {
        case 0:changeX=0;changeY=-0;break;
        case 1:changeX=1.849;changeY=-0.605;break;
        case 2:changeX=4;changeY=0;break;
        case 3:changeX=-22.673;changeY=-2.306;break;
        case 4:changeX=-49.339;changeY=-4.617;break;
        case 5:changeX=-76;changeY=-7;break;
        case 6:changeX=-91.975;changeY=-13.409;break;
        case 7:changeX=-107.95;changeY=-19.797;break;
        case 8:changeX=-124;changeY=-26;break;
        case 9:changeX=-127.255;changeY=-35.237;break;
        case 10:changeX=-130.197;changeY=-44.596;break;
        case 11:changeX=-133;changeY=-54;break;
        case 12:changeX=-132.715;changeY=-62.67;break;
        case 13:changeX=-132.403;changeY=-71.336;break;
        case 14:changeX=-132;changeY=-80;break;
        case 15:changeX=-117.688;changeY=-84.732;break;
        case 16:changeX=-103.311;changeY=-89.268;break;
        case 17:changeX=-89;changeY=-94;break;
        case 18:changeX=-71.005;changeY=-94.218;break;
        case 19:changeX=-53.006;changeY=-94.137;break;
        case 20:changeX=-35;changeY=-94;break;
        case 21:changeX=-17.663;changeY=-93.908;break;
        case 22:changeX=-0.333;changeY=-93.854;break;
        case 23:changeX=-17;changeY=-94;break;
        case 24:changeX=-11.362;changeY=-94.095;break;
        case 25:changeX=-5.682;changeY=-94.013;break;
        case 26:changeX=-0;changeY=-94;break;
        default:
            if(startAnyCnt < 0)
            {
                changeX = 0;
                changeY = 0;
            }
            break;
    }
    
    subTemp[XPOS] = px+2;
    subTemp[YPOS] = py-9-47;
    drawFriendProfile(subTemp[XPOS]-65-changeX, subTemp[YPOS]-3-changeY, xLuluPangRank.xRankChangeSlot.usernum, 60);
    setFontSizeORI(22);
    switch (xLuluPangRank.xRankChangeSlot.rank)
    {
        case 0:
            drawPacker(imgRankChange1, subTemp[XPOS]-changeX, subTemp[YPOS]-changeY, 0, 0, imgW(imgRankChange1), imgH(imgRankChange1)/4, VH);
            break;
        case 1:
            drawPacker(imgRankChange1, subTemp[XPOS]-changeX, subTemp[YPOS]-changeY, 0, imgH(imgRankChange1)/4*1, imgW(imgRankChange1), imgH(imgRankChange1)/4, VH);
            break;
        case 2:
            drawPacker(imgRankChange1, subTemp[XPOS]-changeX, subTemp[YPOS]-changeY, 0, imgH(imgRankChange1)/4*2, imgW(imgRankChange1), imgH(imgRankChange1)/4, VH);
            break;
        default:
            drawPacker(imgRankChange1, subTemp[XPOS]-changeX, subTemp[YPOS]-changeY, 0, imgH(imgRankChange1)/4*3, imgW(imgRankChange1), imgH(imgRankChange1)/4, VH);
            sprintf(strTempS, "%d",xLuluPangRank.xRankChangeSlot.rank);
            gDrawStringBold(subTemp[XPOS]-143-changeX, subTemp[YPOS]-5-changeY, strTempS, VH, 86,	255,220 , 33, 20, 20);
            break;
    }

    gDrawStringBold(subTemp[XPOS]+88-changeX, subTemp[YPOS]+13-changeY, xLuluPangRank.xRankChangeSlot.strUserNick, VL, 255, 149, 0, 82, 49, 38);
    sprintf(strTempS, "%d점", xLuluPangRank.xRankChangeSlot.Score);
    gDrawStringBold(subTemp[XPOS]+68-changeX, subTemp[YPOS]+13-changeY, strTempS, VR, 255, 255, 255, 33, 20, 20);
    
    subTemp[XPOS] = px+2;
    subTemp[YPOS] = py-9+47;
    drawFriendProfile(subTemp[XPOS]-65+changeX, subTemp[YPOS]-3+changeY, xNetData.userNum, 60);
    
    switch (xLuluPang.myRank-1)
    {
        case 0:
            drawPacker(imgRankChange1, subTemp[XPOS]+changeX, subTemp[YPOS]+changeY, 0, 0, imgW(imgRankChange1), imgH(imgRankChange1)/4, VH);
            break;
        case 1:
            drawPacker(imgRankChange1, subTemp[XPOS]+changeX, subTemp[YPOS]+changeY, 0, imgH(imgRankChange1)/4*1, imgW(imgRankChange1), imgH(imgRankChange1)/4, VH);
            break;
        case 2:
            drawPacker(imgRankChange1, subTemp[XPOS]+changeX, subTemp[YPOS]+changeY, 0, imgH(imgRankChange1)/4*2, imgW(imgRankChange1), imgH(imgRankChange1)/4, VH);
            break;
        default:
            drawPacker(imgRankChange1, subTemp[XPOS]+changeX, subTemp[YPOS]+changeY, 0, imgH(imgRankChange1)/4*3, imgW(imgRankChange1), imgH(imgRankChange1)/4, VH);
            sprintf(strTempS, "%d",xLuluPang.myRank-1);
            gDrawStringBold(subTemp[XPOS]-143+changeX, subTemp[YPOS]-5+changeY, strTempS, VH, 86,	255,220 , 33, 20, 20);
            break;

    }
    
    sprintf(strTempS, "%s", xSaveTemp.strNickName);
    gDrawStringBold(subTemp[XPOS]+88+changeX, subTemp[YPOS]+13+changeY, strTempS, VL, 255, 149, 0, 82, 49, 38);
    sprintf(strTempS, "%d점", xPang_SOLO.totalScore.oriData);
    gDrawStringBold(subTemp[XPOS]+68+changeX, subTemp[YPOS]+13+changeY, strTempS, VR, 255, 255, 255, 33, 20, 20);
    setFontSize(11);

    switch(startAnyCnt)
    {
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            drawPacker(imgRankChange2, subTemp[XPOS]+changeX, subTemp[YPOS]+changeY, 0, imgH(imgRankChange2)/5*(startAnyCnt-28), imgW(imgRankChange2), imgH(imgRankChange2)/5, VH);
            break;
        case 33:
            makeFire(subTemp[XPOS]+changeX, subTemp[YPOS]+changeY-50, 10);
            makeFire(subTemp[XPOS]+changeX, subTemp[YPOS]+changeY+50, 10);
            makeFire(subTemp[XPOS]+changeX-70, subTemp[YPOS]+changeY, 10);
            makeFire(subTemp[XPOS]+changeX+70, subTemp[YPOS]+changeY, 10);
            makeFire(subTemp[XPOS]+changeX-140, subTemp[YPOS]+changeY, 10);
            makeFire(subTemp[XPOS]+changeX+140, subTemp[YPOS]+changeY, 10);
            break;
    }
    xLuluPang.rankChangeAnyCnt++;
    drawBtn(px, py+135,BTN_OK_CONFIRM);

}

int getPangBuffScore(int modelKey)
{
	int resultNum = 0;
	
	int modelSlot = getModelKeyToSlotNum(modelKey);
	int modelCode = 0;
	
	if(modelSlot != DONT)
	{
		modelCode = xInventoryModel[modelSlot].code;
		resultNum = (xModelData[modelCode].grade+1)*(xModelData[modelCode].grade+1)*10;
	}
	
	return resultNum;
}

int getPangBuffTime(int modelKey)
{
	
	int resultNum = 0;
	
	int modelSlot = getModelKeyToSlotNum(modelKey);
	int modelCode = 0;
	
	if(modelSlot != DONT)
	{
		modelCode = xInventoryModel[modelSlot].code;
		resultNum = xInventoryModel[modelSlot].upGrade+1;
	}
	return resultNum;
}

int getPangBuffScore_LuluPang(int modelKey)
{
	int resultNum = 0;
	
	int modelSlot = getModelKeyToSlotNum(modelKey);
	int modelCode = 0;
	
	if(modelSlot != DONT)
	{
		modelCode = xInventoryModel[modelSlot].code;
		switch(xModelData[modelCode].grade)
		{
			case 0:
				switch(xInventoryModel[modelSlot].upGrade)
			{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					resultNum=5;
					break;
				default:
					break;
			}
				break;
			case 1:
				switch(xInventoryModel[modelSlot].upGrade)
			{
				case 0:
				case 1:
				case 2:
					resultNum=20;
					break;
				case 3:
				case 4:
					resultNum=30;
					break;
				case 5:
					resultNum=40;
					break;
				default:
					break;
			}
				break;
			case 2:
				switch(xInventoryModel[modelSlot].upGrade)
			{
				case 0:
				case 1:
				case 2:
					resultNum=50;
					break;
				case 3:
				case 4:
					resultNum=60;
					break;
				case 5:
					resultNum=70;
					break;
				default:
					break;
			}
				break;
			case 3:
				switch(xInventoryModel[modelSlot].upGrade)
			{
				case 0:
				case 1:
				case 2:
					resultNum=80;
					break;
				case 3:
				case 4:
					resultNum=90;
					break;
				case 5:
					resultNum=100;
					break;
				default:
					break;
			}
				break;
			case 4:
				switch(xInventoryModel[modelSlot].upGrade)
			{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					break;
			}
				break;
			default:
				break;
		}
	}
	return resultNum;
}

float getPangBuffmagnification_Lulupang(int modelKey)
{
	float resultNum = 0.0f;
	
	int modelSlot = getModelKeyToSlotNum(modelKey);
	int modelCode = 0;
	
	if(modelSlot != DONT)
	{
		modelCode = xInventoryModel[modelSlot].code;
		switch(xModelData[modelCode].grade)
		{
			case 0:
				resultNum = 0.02f;
				break;
			case 1:
				resultNum = 0.04f;
				break;
			case 2:
				resultNum = 0.06f;
				break;
			case 3:
				resultNum = 0.08f;
				break;
			case 4:
				break;
			default:
				break;
		}
	}
	return resultNum;
}

int getPangBuffTime_LuluPang(int modelKey)
{
	int resultNum = 0;
	
	int modelSlot = getModelKeyToSlotNum(modelKey);
	int modelCode = 0;
	
	if(modelSlot != DONT)
	{
		modelCode = xInventoryModel[modelSlot].code;
		switch(xModelData[modelCode].grade)
		{
			case 0:
			case 1:
				resultNum=0;
				break;
			case 2:
				resultNum=1;
				break;
			case 3:
				resultNum=2;
				break;
			case 4:
				break;
			default:
				break;
		}
	}
	return resultNum;
}
