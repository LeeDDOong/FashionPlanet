#include "Global.h"

//***************화면관리***************
M_Int32 lcdW;
M_Int32 lcdH;
M_Int32 cx;
M_Int32 cy;				
//*************************************
//***************인앱관리***************
XBILL xBill;
//*************************************
//***************시스템관리***************
M_Boolean isCall;		


bool isKeyPress[2];


int orilcdW;
int orilcdH;

//*************************************
//***************테스트용***************
M_Int32 pdh[10];
//*************************************
//***************상태관리***************
M_Int32 loadingCnt;			
M_Int32 gameCnt;			
//GAME_STATE
M_Int32 beforState;			
M_Int32 nextState;
M_Int32 nowState;			
M_Int32 playState;			
M_Int32 subState;			
M_Int32 subStateTemp;
//*************************************
M_Boolean isFontLoading;
//***************엔진구조체모음**************
XGAME xGame;
XCONF xConf;

XIOSTREAM xIOStream;
//*********************************************
M_Char strTempS[STRTEMPSMAX];	
M_Char strTempB[STRTEMPBMAX];	
M_Int32 subTemp[SUBTEMPMAX];	
float fsubTemp[SUBTEMPMAX];

M_Int32 isSubTemp[SUBTEMPMAX];	
M_Int32 posTemp[SUBTEMPMAX];	

M_Char saveTemp[2560000];
M_Char strInfo[2][STRTEMPBMAX];
M_Char strTextBox[STRTEMPSMAX];
M_Char strTextBoxSub[STRTEMPSMAX];
M_Boolean isTextBox;
M_Int32 textBoxTypeJava;
XLOOG xLogo;
XHACKING xHacking;

char strRecvTextBox[256];

XDownloader xDownLoader;

XLOCALPUSH xLocalPush;

M_Int32 touchAnyNum;
XTOUCHANY xTouchAny[TOUCHANYMAX];
XTOUCH xTouch;
XTOUCH xTouchS;

XTOUCH xTouchTile;
XTOUCH xTouchTemp;

XTOUCH xTouchBack;

XTOUCH xTouchOk;
XTOUCH xTouchClr;
XTOUCH xTouchArrowUp;
XTOUCH xTouchArrowDown;
XTOUCH xTouchArrowLeft;
XTOUCH xTouchArrowRight;

M_Boolean isTouch;
M_Int32 touchTypeTemp;
M_Int32 touchType;
M_Int32 touchTotal;
M_Int32 touchScaleCnt;
M_Int32 scaleXnow[2];
M_Int32 scaleYnow[2];
M_Int32 scaleXbefore[2];
M_Int32 scaleYbefore[2];

M_Boolean	isResume;
M_Boolean	bResume;
M_Int32		iResumeNum;



Scene* FashionShop::createScene()       //scene생성은 여기에서만
{
    auto scene = Scene::create();
    auto layer = FashionShop::create(); //메인레이어드
    scene->addChild(layer);
    return scene;
}

void FashionShop::onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *unused_event)
{
    std::vector<Touch*>::const_iterator it = touches.begin();
    Touch *touch;
    Point location[2];
    int totalCount = (int)touches.size();
    for(int i=0;i<totalCount;i++)
    {
        touch = (Touch*)(*it);
        
        if(touch->getID() >= 2)
            continue;
        
        location[i] = touch->getLocation();
        it++;
        isKeyPress[touch->getID()] = true;
        keyMainEvent(USER_POINT_PRESS_EVENT, location[i].x, location[i].y,touch->getID(),totalCount);
    }
    
}
void FashionShop::onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *unused_event)
{
    std::vector<Touch*>::const_iterator it = touches.begin();
    Touch *touch;
    Point location[2];
    int totalCount = (int)touches.size();
    for(int i=0;i<totalCount;i++)
    {
        touch = (Touch*)(*it);
        
        if(touch->getID() >= 2)
            continue;
        
        location[i] = touch->getLocation();
        it++;
        
        keyMainEvent(USER_POINT_MOVE_EVENT, location[i].x, location[i].y,touch->getID(),totalCount);
    }
}
void FashionShop::onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *unused_event)
{
    std::vector<Touch*>::const_iterator it = touches.begin();
    Touch *touch;
    Point location[2];
    int totalCount = (int)touches.size();
    for(int i=0;i<totalCount;i++)
    {
        touch = (Touch*)(*it);
        if(touch->getID() >= 2)
            continue;
        
        location[i] = touch->getLocation();
        it++;
        isKeyPress[touch->getID()] = false;
        keyMainEvent(USER_POINT_RELEASE_EVENT, location[i].x, location[i].y,touch->getID(),totalCount);
    }
}
void FashionShop::onTouchesCancelled(const std::vector<Touch*>& touches, Event *event)
{
    std::vector<Touch*>::const_iterator it = touches.begin();
    Touch *touch;
    Point location[2];
    int totalCount = (int)touches.size();
    for(int i=0;i<totalCount;i++)
    {
        touch = (Touch*)(*it);
        location[i] = touch->getLocation();
        it++;
        
        keyMainEvent(USER_POINT_RELEASE_EVENT, location[i].x, location[i].y,touch->getID(),totalCount);
    }
}

void FashionShop::onKeyReleased (EventKeyboard::KeyCode keyCode, Event* event)
{
    //백버튼 터치 업
    
    
    
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
    {
        if(xTextField.state == TEXTFIELD_STATE_PLAY)
        {
            xTextField.textfield->isOpen = false;
        }
        else
        {
            bool isExit = false;
            nativeExitYesNo();
            //상태에 따른 처리형태로
            /*
            isExit = true;
            if(isExit == false)
            {
                xMainMenu.isJniClr = true;
            }
            else if(isExit == true)
            {
                //종료처리
                nativeExitYesNo();
            }
            */
        }
    }
}




void FashionShop::onHttpRequestCompleted(Node *sender,void *data)
{
    
    setRecv((char*)data);
    
}





bool FashionShop::init()                //startClet개념
{
    if (!Layer::init() )
    {
        return false;
    }
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(FashionShop::onTouchesBegan,this);
    listener->onTouchesMoved = CC_CALLBACK_2(FashionShop::onTouchesMoved,this);
    listener->onTouchesEnded = CC_CALLBACK_2(FashionShop::onTouchesEnded,this);
    listener->onTouchesCancelled = CC_CALLBACK_2(FashionShop::onTouchesCancelled,this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
    auto keylistener = EventListenerKeyboard::create();
    keylistener->onKeyReleased = CC_CALLBACK_2(FashionShop::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
    
    this->schedule(schedule_selector(FashionShop::run),0.001);
        
    startClet();
    
    return true;
}

void FashionShop::run(float fDelay)
{
    xGame.fDelay += fDelay;
    
    xGame.prcCnt = 0;
    gameCnt++;
    
    if(xCalendar.nowTime != 0)
    {
        if(xGame.delaySec == 0)
            xGame.delaySec = xCalendar.nowTime;
        else if(xCalendar.nowTime-xGame.delaySec > 0)
        {
            xGame.prcSec += xCalendar.nowTime-xGame.delaySec;
            xGame.delaySec = xCalendar.nowTime;
        }
    }
    
    while (true)
    {
        if(xGame.fDelay-0.030f >= 0)
        {
            xGame.fDelay -= 0.030f;
            xGame.prcCnt++;
        }
        else
            break;
    }
    
    if(xGame.prcCnt == 0)
        return;
    
    xGame.layer = this;
    //50:타일그룹
    //타일그룹은 타일이 변경될경우에만 작동
    //100:일반이미지
    for(int i=0;i<40;i++)
        xGame.layer->removeChildByTagPDH(100,true);
        
    
    //200:폰트
    for(int i=0;i<xFontRe.totalNum;i++)
        xFontRe.xSlot[i].isUse = false;
    if(xFontRe.totalNum > FONTRESLOTMAX-64)
    {
        for(int i=0;i<96;i++)
            xGame.layer->removeChildByTagPDH(200,true);
        
        xFontRe.totalNum = 0;
    }
    
    
    xGame.scene = Director::getInstance()->getRunningScene();
    
    xGame.isTextField = false;
    if(xTextField.textfield != NULL)
    {
        if(xTextField.textfield->isVisible() != 0)
            xGame.isTextField = true;
    }
    
    getTime();
    checkSound();
    paintClet(0,0,lcdW,lcdH);
    
    
    if(xWebView.isWebView == true)
        drawWebView();
    
    
    
    if(xGame.isTextField == true)
    {
        drawBgFillRect();
        //drawPacker(imgTextBox, cx, 150, 0, 0, imgW(imgTextBox), imgH(imgTextBox), VH);
        gSetColor(255, 255, 255);
        fillRect(cx-340, 150-40, 680, 80);
        gSetColor(0, 0, 0);
        gSetClip(true, cx-320, 150-50, 640, 100);
        setFontSize(50);
        gDrawString(cx+300, 150, xTextField.textfield->getString().c_str(), VR);
        setFontSize(11);
        gSetClip(false, cx-320, 150-50, 640, 100);
    }
    prcTextField();
    
    xGame.totalPrcSec += xGame.prcSec;
    xGame.prcSec = 0;
}




//*****************이미지*******************
//*********************************************

void pauseClet(){pauseApp();}
void resumeClet(){resumeApp();}
void destroyClet(){}
void pauseApp()
{
}

void resumeApp()
{
	xWorldMap.isLoginInit = TRUE;
	xGame.isResume = TRUE;
	xGame.resumeAnyCnt = 0;
    /*
	xnet.isHeartBit = FALSE;
	xEventQueueNet.isNetOk[0] = TRUE;
	 */
}

void startClet()
{
    //960
    lcdW = 1136;
	lcdH = 640;
	
	cx = lcdW>>1;
	cy = lcdH>>1;
	        
	xmedia.nTrack = DONT;
	xmedia.bgTrack = DONT;
	loadMapData("w1.mpd",0);
	loadMapData("w2.mpd",1);
	loadMapData("w3.mpd",2);
	
	
	if(gameLoad(SAVE_SLOT_GAME) == TRUE)
	{
		gameLoad(SAVE_SLOT_GAME);		
		gameLoad(SAVE_SLOT_KAKAO);
		gameLoad(SAVE_SLOT_KAKAOAPP);
        

		
		xMail.mailLastKey = xSave.mailLastKey;
		xMail.giftLastKey = xSave.giftLastKey;
	}
	else
	{
		initSave();		
		gameSave(SAVE_SLOT_KAKAO);
		gameSave(SAVE_SLOT_KAKAOAPP);
        

	}
    
    
    xSave.tempVol = DONT;
    
    
	
	if(gameLoad(SAVE_SLOT_KAKAOHELP) == TRUE)
	{
		gameLoad(SAVE_SLOT_KAKAOHELP);
	}
	else
	{
		gameSave(SAVE_SLOT_KAKAOHELP);
	}
    
    
    if(gameLoad(SAVE_SLOT_NOTICEPOPUP) == TRUE)
    {
        gameLoad(SAVE_SLOT_NOTICEPOPUP);
    }
    else
    {
        gameSave(SAVE_SLOT_NOTICEPOPUP);
    }
    
    
    
    if(gameLoad(SAVE_SLOT_PRODUCTION) == TRUE)
    {
        gameLoad(SAVE_SLOT_PRODUCTION);
    }
    else
    {
        for(int k=0;k<PRODUCTIONMENULATESTMAX;k++)
            xProductionMenuLatestSave.code[k] = DONT;
        gameSave(SAVE_SLOT_PRODUCTION);
    }
	
	if(gameLoad(SAVE_SLOT_SELLSLOT) == TRUE)
	{
		gameLoad(SAVE_SLOT_SELLSLOT);
	}
	else
	{
		for(int k=0;k<SELLSLOTMAX;k++)
			xSellSlotSave.code[k] = DONT;
		gameSave(SAVE_SLOT_SELLSLOT);
	}
	
	
	

	
	
	
	xGame.isReSizeDraw = FALSE;
	initContext();
	initGame();
	setFontSize(11);
    

    
	nowState = DONT;
	
	xWorldMap.isStartClet = TRUE;
	setState(GAME_LOGO, PLAY_PLAY, DONT);
	
	xWorldMap.isLoginInit = TRUE;
	xGame.isResume = TRUE;
	xGame.resumeAnyCnt = 0;
	xnet.isHeartBit = FALSE;
        
    nativeOnOffPush(xSave.isPushOnOff[2] == FALSE?0:1);
}

void keyMainEvent(int type, int param1, int param2,int touchId,int touchCount)
{
	if(isTextBox == TRUE)
		return;

	if(xBill.isBilling == TRUE)
		return;
		
    param2 = lcdH-param2;
    


    
	touchType = DONT;
	touchTotal = touchCount;
			
	if(type == USER_POINT_MOVE_EVENT)
	{
		if(touchTotal == 2)
		{
			if(touchId == 0 || touchId == 1)
			{
				scaleXbefore[touchId] = scaleXnow[touchId];
				scaleYbefore[touchId] = scaleYnow[touchId];
				scaleXnow[touchId] = param1;
				scaleYnow[touchId] = param2;
			}
		}
		else
		{
			touchScaleCnt = 0;
			scaleXnow[0] = DONT;
			scaleYnow[0] = DONT;
			scaleXbefore[0] = DONT;
			scaleYbefore[0] = DONT;
			scaleXnow[1] = DONT;
			scaleYnow[1] = DONT;
			scaleXbefore[1] = DONT;
			scaleYbefore[1] = DONT;
		}
	}
	
	isTouch = FALSE;
	xTouch.wPos = 20;
	xTouch.hPos = 20;
	xTouchS.wPos = 20;
	xTouchS.hPos = 20;
	initTouchCletEvent(type,param1,param2);
	if(touchTypeTemp == DONT)
		return;
			
	type = touchTypeTemp;
	
    
    if(xWebView.isWebView == true)
    {
        keyWebView(type, param1, param2, touchId, touchCount);
        return;
    }
    
    
			
	switch(type)
	{
	case MH_KEY_PRESSEVENT:
		switch(nowState)
		{
		case GAME_MAINMENU:	MainMenuCletEvent(type,param1,param2,touchId);	break;
		case GAME_WORLDMAP:	WorldMapCletEvent(type,param1,param2,touchId);	break;
		}
		break;
	case MH_KEY_RELEASEEVENT:
		switch(nowState)
		{
		case GAME_MAINMENU:	MainMenuCletEvent(type,param1,param2,touchId);	break;
		case GAME_WORLDMAP:	WorldMapCletEvent(type,param1,param2,touchId);	break;
		}
		break;
	}
}




//XIMG imgTest;

void paintClet(int x, int y, int w, int h)
{
	if(xGame.isResume == TRUE)
	{
		if(xNetData.strGameServerUrl[0] != 0 && xWorldMap.hackingTimeSec != 0)
		{
			getTime();
			xnet.heartBitTime = xCalendar.nowTime;
			xnet.heartBitTime22 = xCalendar.nowTime;
			xGame.isResume = FALSE;
			netSend(CMD_GETTIME, DONT);
		}
	}
    
	prcKakaoApi();
	
	switch(nowState)
	{
	case GAME_LOGO:			drawLogo();				break;
	case GAME_MAINMENU:		paintMainMenu();		break;
	case GAME_WORLDMAP:		paintWorldMap();		break;	
	case GAME_LOADING:		drawLoading();			break;
	}
		
	isSubTemp[11] = FALSE;
	
	switch(nowState)
	{
	case GAME_MAINMENU:
		switch(xMainMenu.state)
		{
		case MAINMENU_STATE_SERVERNOTICE:
			xnet.isHeartBit = FALSE;
			break;
		}
		break;
	}
	
	if(xnet.isHeartBit ==  TRUE)
	{
		if(xCalendar.nowTime - xnet.heartBitTime > 10)
			isSubTemp[11] = TRUE;
		
		if(xCalendar.nowTime - xnet.heartBitTime > 30)
		{
			isSubTemp[11] = FALSE;
			if(playState != PLAY_MSG)
				setPopup(POPUP_SERVER_TIMEOVER, playState, playState, 0, xEventQueueNet.type[0]);
		}
	}
	    
    
	//이벤트가 쌓여있고(이벤트 갯수로 이후로 처리시간으로 판단)
	if(nowState == GAME_WORLDMAP)
	{
		if(xEventQueueNet.totalNum > 0)
		{
            //여기~
			if(xCalendar.nowTime - xnet.heartBitTime22 > 10)
				isSubTemp[11] = TRUE;
			
			if(xCalendar.nowTime - xnet.heartBitTime22 > 50)
			{
				isSubTemp[11] = FALSE;
				if(playState != PLAY_MSG)
					setPopup(POPUP_SERVER_TIMEOVER_EVENTQUEUENET, playState, playState, 0, xEventQueueNet.type[0]);
			}
		}
		else
		{
			xnet.heartBitTime22 = xCalendar.nowTime;
		}
	}
	else
		xnet.heartBitTime22 = xCalendar.nowTime;

	
    
    
    if(nowState == GAME_WORLDMAP && (xEventQuest.isNetLoad == true || xRival.isNetLoad == true))
        isSubTemp[11] = true;
    
    //여기2
	if(isSubTemp[11] == TRUE)
	{
		xGame.isRotate = TRUE;
		xGame.rotateNum = 360-(gameCnt%120)*3;
		drawPacker(imgLoadingIcon0, cx, cy, 0, 0, imgW(imgLoadingIcon0), imgH(imgLoadingIcon0), VH);
		xGame.isRotate = FALSE;
	}
	
	prcIap();
	drawTouchTrace();

	//sprintf(strTempS, "fps:%d",xGame.fpsNow);
	sprintf(strTempS, "11");
	gSetColor(255,0,0);
	//sprintf(strTempS,"%d년%d월%d일   %d:%d:%d>>>%ld\n",xCalendar.nowYear,xCalendar.nowMonth,xCalendar.nowDay,xCalendar.nowHour,xCalendar.nowMinute,xCalendar.nowSec,xCalendar.nowTime);
	gDrawString(cx+1000, lcdH-26, strTempS, VH);
    
    
    
    
    
    /*
    gSetClip(true, cx-200, cy-200, 400, 400);
    
    gSetColor(255, 255, 255);
    fillRect(cx-200, cy-200, 400, 400);
    
    
    loadImg("jewelquesttab0.png", &imgTest);
    
    drawImage(&imgTest, cx, cy-200, 0, 0, imgTest.w, imgTest.h, VR);
    drawImage(&imgTest, cx, cy, 0, 0, imgTest.w, imgTest.h/2, VL);
    drawImage(&imgTest, cx, cy+200, 0, imgTest.h/2, imgTest.w, imgTest.h/2, VH);
    
    gSetColor(255, 0, 0);
    setFontSizeORI(40);
    gDrawString(cx, cy, "VH",  VH);
    setFontSize(11);
    
    gSetClip(false, cx-200, cy-200, 400, 400);
    
    
    freeImg(&imgTest);
    */
	
}

void drawNetBar(int x,int y)
{
	xGame.isBlend = TRUE;
	xGame.blendType = BLEND_ADDP;

	posTemp[XPOS] = x;
	posTemp[YPOS] = y;
	/*
	drawImage(&imgLoadingBar[4], posTemp[XPOS], posTemp[YPOS], 0, imgLoadingBar[4].h/7 * (gameCnt%7), imgLoadingBar[4].w, imgLoadingBar[4].h/7, VH);
	xGame.isBlend = FALSE;
	drawImage(&imgLoadingBar[5], posTemp[XPOS]+25, posTemp[YPOS]+2, 0, 0, imgLoadingBar[5].w, imgLoadingBar[5].h, VL);
	*/
}

//유행
//유행캔디로 구매
//21레벨에 열리고
//구매버튼
void drawLoading()
{	
	int loadingW;
	
	
	if(xInventoryFashion.haveNum[0][13] > 0)
		printf("initWorldMap1 >>>%d\n",xInventoryFashion.haveNum[0][13]);
	
	switch(nextState)
	{
	case GAME_LOGO:
		initLogo();
		nowState = nextState;
		return;
		break;
	case GAME_MAINMENU:
		//LJW 타이틀 이미지 추가
		loadImg("titlebg.png", &imgTitleBG);
		loadImg("all.png", &imgYoung);
	
			
		freeImg(&xLogo.img[0]);
		freeImg(&xLogo.img[1]);
		initMainMenu();
		nowState = nextState;
		return;
		break;
	case GAME_WORLDMAP:
		switch(loadingCnt)
		{
		case 0:
			freeImg(&imgYoung);
			freeImg(&imgTitleBG);
			freeImg(&xPacker[PACKER_STATE_MAINMENU].img);
                
                
            loadImg("clubui0.png", &imgClubUi[0]);
                
                
            loadImg("myshoprefresh0.png", &imgMyShopRefresh[0]);
            loadImg("myshoprefresh1.png", &imgMyShopRefresh[1]);
            loadImg("myshoprefresh2.png", &imgMyShopRefresh[2]);
                
            loadImg("fastscroll.png",&imgFastScroll);
            
            loadImg("helplisticon.png",&imgHelpListIcon);
                
            loadImg("myshop0.png", &imgMyShop[0]);
            loadImg("myshop1.png", &imgMyShop[1]);
                
            loadImg("rivalui0.png", &imgRivalUi[0]);
            loadImg("rivalui1.png", &imgRivalUi[1]);
            loadImg("rivalui2.png", &imgRivalUi[2]);
            loadImg("rivalui3.png", &imgRivalUi[3]);
            loadImg("rivalui4.png", &imgRivalUi[4]);
            loadImg("rivalui5.png", &imgRivalUi[5]);
            loadImg("rivalui6.png", &imgRivalUi[6]);
            loadImg("rivalui7.png", &imgRivalUi[7]);
            loadImg("rivalui8.png", &imgRivalUi[8]);
            loadImg("rivalui9.png", &imgRivalUi[9]);
            loadImg("rivalui10.png", &imgRivalUi[10]);
            loadImg("rivalui11.png", &imgRivalUi[11]);

                
                
            
                
                
                
            loadImg("cafeicon.png", &imgCafeIcon);
                
                
            loadImg("frienddelbtn.png",&imgFriendDelBtn2);
                
                
            loadImg("giftexpicon.png", &imgGiftExpIcon);
            
                
            loadImg("blinkeff.png", &imgBlinkEff2);
            loadImg("logintime.png", &imgLoginTime);
                
            loadImg("dresscodeeff0.png", &imgDressCodeEff[0]);
            loadImg("dresscodeeff1.png", &imgDressCodeEff[1]);
            loadImg("dresscodeeff2.png", &imgDressCodeEff[2]);
            loadImg("dresscodeeff3.png", &imgDressCodeEff[3]);
            
            loadImg("hotdealui0.png", &imgHotDealUi[0]);
            loadImg("hotdealui1.png", &imgHotDealUi[1]);
            loadImg("hotdealui2.png", &imgHotDealUi[2]);
                
                
            loadImg("rivalcomingsoon0.png",&imgRivalComingSoon[0]);
            loadImg("rivalcomingsoon1.png",&imgRivalComingSoon[1]);
                
                
                
            loadImg("webview0.png", &imgWebView[0]);
                
            loadImg("mileageui0.png", &imgMileageUi[0]);
            loadImg("mileageui1.png", &imgMileageUi[1]);
				
			loadImg("lulupang_broochshop.png", &imgLuluPang);

                
            loadImg("eventquestui0.png", &imgEventQuestUi[0]);
            loadImg("eventquestui1.png", &imgEventQuestUi[1]);
            
            loadImg("castingasicon.png", &imgCastingASIcon);
            loadImg("castingaicon.png", &imgCastingAIcon);
            loadImg("castingsicon.png", &imgCastingSIcon);
                
			xCatalog.totalNumB = 8;
			loadImg("mapbg.png", &imgMapBg);
								
			///////////////////////////LVUP/////////////////////
			loadImg("lvup2.png", &imgLvUp[2]);
			////////////////////피팅////////////////////////////
			loadImg("fittingbg0.png", &imgFittingBg[0]);
			loadImg("fittingbg1.png", &imgFittingBg[1]);
			loadImg("fittingbg2.png", &imgFittingBg[2]);
			//////////////////////////////////////////////////
                
                
                
            loadImg("mileageicon0.png", &imgMileageIcon[0]);
            loadImg("mileageicon1.png", &imgMileageIcon[1]);
            loadImg("mileageicon2.png", &imgMileageIcon[2]);
            loadImg("mileageicon3.png", &imgMileageIcon[3]);


            
                
            loadImg("prepayicon0.png", &imgPrePayUi[0]);
            loadImg("prepayicon1.png", &imgPrePayUi[1]);
                
                
			break;
		case 1:
			loadImg("f1.png", &imgFittingBody[0][1]);
			xGame.isUnAnti = TRUE;

			loadImg("f3.png", &imgFittingBody[0][3]);
			loadImg("f5.png", &imgFittingBody[0][5]);
			loadImg("f6.png", &imgFittingBody[0][6]);
			loadImg("f11.png", &imgFittingBody[0][11]);
			loadImg("f12.png", &imgFittingBody[0][12]);
			xGame.isUnAnti = FALSE;

			loadImg("f13.png", &imgFittingBody[0][13]);
			loadImg("f17.png", &imgFittingBody[0][17]);
			loadImg("man_f1.png", &imgFittingBody[1][1]);
			xGame.isUnAnti = TRUE;
			loadImg("man_f3.png", &imgFittingBody[1][3]);
			loadImg("man_f11.png", &imgFittingBody[1][11]);
			xGame.isUnAnti = FALSE;

			loadImg("man_f13.png", &imgFittingBody[1][13]);
			loadImg("man_f17.png", &imgFittingBody[1][17]);
							
			xGame.isUnAnti = TRUE;
			loadImg("fff1.png", &imgFittingBodyStaff[0][1]);
			loadImg("fff3.png", &imgFittingBodyStaff[0][3]);
			loadImg("fff5.png", &imgFittingBodyStaff[0][5]);
			loadImg("fff6.png", &imgFittingBodyStaff[0][6]);
			loadImg("fff11.png", &imgFittingBodyStaff[0][11]);
			loadImg("fff12.png", &imgFittingBodyStaff[0][12]);
			loadImg("fff17.png", &imgFittingBodyStaff[0][17]);
			loadImg("man_fff1.png", &imgFittingBodyStaff[1][1]);
			loadImg("man_fff3.png", &imgFittingBodyStaff[1][3]);
			loadImg("man_fff11.png", &imgFittingBodyStaff[1][11]);
			loadImg("man_fff17.png", &imgFittingBodyStaff[1][17]);
			xGame.isUnAnti = FALSE;
			loadImg("man_fff13.png", &imgFittingBodyStaff[1][13]);
			loadImg("fff13.png", &imgFittingBodyStaff[0][13]);
				
			xGame.isUnAnti = TRUE;
			loadImg("ff1.png", &imgFittingBodyBlack[0][1]);
			loadImg("ff3.png", &imgFittingBodyBlack[0][3]);
			loadImg("ff5.png", &imgFittingBodyBlack[0][5]);
			loadImg("ff6.png", &imgFittingBodyBlack[0][6]);
			loadImg("ff11.png", &imgFittingBodyBlack[0][11]);
			loadImg("ff12.png", &imgFittingBodyBlack[0][12]);
			loadImg("ff17.png", &imgFittingBodyBlack[0][17]);
				
			loadImg("man_ff1.png", &imgFittingBodyBlack[1][1]);
			loadImg("man_ff3.png", &imgFittingBodyBlack[1][3]);
			loadImg("man_ff11.png", &imgFittingBodyBlack[1][11]);
			loadImg("man_ff17.png", &imgFittingBodyBlack[1][17]);
			xGame.isUnAnti = FALSE;
			loadImg("ff13.png", &imgFittingBodyBlack[0][13]);
			loadImg("man_ff13.png", &imgFittingBodyBlack[1][13]);

				
				
			loadImg("ff_3b.png", &imgFittingBodyBlack3Sub[0]);
			loadImg("man_ff_3b.png", &imgFittingBodyBlack3Sub[1]);

			break;
		case 3:
			loadImg("shopoutline0.png", &imgShopOutLine[0]);
			loadImg("shopoutline1.png", &imgShopOutLine[1]);
			loadImg("shopoutline2.png", &imgShopOutLine[2]);
				
			//LJW 월드맵 건물 loadImg 추가
			loadImg("rocket_smoke.png", &imgWorldMapRocketEFF[ROCKET_EFF_SMOKE]);
			loadImg("rocket_flame.png", &imgWorldMapRocketEFF[ROCKET_EFF_FIRE]);
			loadImg("worldmap_rocket0.png", &imgWorldMapRocket[0]);
			loadImg("worldmap_rocketb0.png", &imgWorldMapRocketBottom[0]);
			loadImg("worldmap_vinylhouse0.png", &imgWorldMapVinylHouse[0]);
			loadImg("worldmap_storage0.png", &imgWorldMapStorage[0]);
			loadImg("worldmap_antenna0.png", &imgWorldMapAntenna[0]);
			break;
		case 5:				
			//적용안할껄 TRUE로
//			for(int k=0;k<ACTLAYERMAX;k++)
//			{
//				//팔이랑 다리
//				switch(k)
//				{
//					case 1:
//					case 2:
//					case 3:
//					case 4:
//					case 9:
//					case 10:
//					case 17:
//					case 18:
//					case 5:
//					case 6:
//					case 11:
//					case 12:
//						xGame.isUnAnti = TRUE;
//						break;
//					default:
//						xGame.isUnAnti = FALSE;
//						break;
//				}
//				sprintf(strTempS, "%d.png",k);
//				loadImg(strTempS,&imgActBody[k][ACT_FRONT]);
//				
//				sprintf(strTempS, "%d_200.png",k);
//				loadImg(strTempS,&imgActBodySub[k][ACT_FRONT]);
//				
//				//				xGame.isUnAnti = FALSE;
//				//				sprintf(strTempS, "s%d.png",k);
//				//				loadImg(strTempS,&imgActBodySub[k][ACT_FRONT]);
//				//				xGame.isUnAnti = FALSE;
//				//팔이랑 다리
//				switch(k)
//				{
//					case 0:
//					case 2:
//					case 5:
//					case 6:
//					case 10:
//					case 11:
//					case 16:
//					case 18:
//					case 3:
//					case 4:
//					case 8:
//					case 9:
//						xGame.isUnAnti = TRUE;
//						break;
//					default:
//						xGame.isUnAnti = FALSE;
//						break;
//				}
//				sprintf(strTempS, "b%d.png",k);
//				loadImg(strTempS,&imgActBody[k][ACT_BACK]);
//				
//				sprintf(strTempS, "b%d_200.png",k);
//				loadImg(strTempS,&imgActBodySub[k][ACT_BACK]);
//				
//				//				xGame.isUnAnti = FALSE;
//				//				sprintf(strTempS, "sb%d.png",k);
//				//				loadImg(strTempS,&imgActBodySub[k][ACT_BACK]);
//				//				xGame.isUnAnti = FALSE;
//			}
//			xGame.isUnAnti = FALSE;
			break;
			case 6:
				loadModelShopNpcImg(0);
			break;
		case 8:
			loadModelShopNpcImg(1);
			break;
		case 11:
			loadModelShopNpcImg(2);
			break;
		case 14:
			loadModelShopNpcImg(3);
			break;
		case 17:
			loadModelShopNpcImg(4);
			break;
		case 18:
			initWorldMap();
			break;
		case 20:
			npcSetImgLoad(0);
			break;
		case 22:
			npcSetImgLoad(1);
			break;
		case 24:
			npcSetImgLoad(2);
			break;
		case 25:
			npcSetImgLoad(3);
			break;
		case 26:
			npcSetImgLoad(4);
			break;
		case 27:
			npcSetImgLoad(5);
			break;
		case 28:
			npcSetImgLoad(6);
			break;
		case 30:
			for(int npcI=0;npcI<6;npcI++)
			{
				XFITTINGLAYER xFTemp;
				XFACE xFaceTemp;
				xFaceTemp.hairNum = 2000+npcI;
				xFaceTemp.faceNum = 2000+npcI;
				xFaceTemp.faceType = 0;
								
				for(int f=0;f<16;f++)
					xFTemp.code[f] = DONT;
				
				setMapData((F_TYPE_ONEPIECE*1000)+17+npcI);
				xFTemp.code[xFashionData[xMap.type][xMap.listNum].layer] = (xMap.type*1000)+xMap.listNum;
				setMapData((F_TYPE_SHOES*1000)+40+npcI);
				xFTemp.code[xFashionData[xMap.type][xMap.listNum].layer] = (xMap.type*1000)+xMap.listNum;
				setSpritF(&xSpritNpc[NPC_ACT_STOP][ACT_FRONT],&xFTemp,ACT_FRONT);
								
				drawHair(0,0,xFaceTemp.hairNum,0,0,0);
				drawFace(0,0,&xFaceTemp,0,0);
			}
			break;
		case 32:
			worldMapInitImgLoad(0);
		case 33:
			worldMapInitImgLoad(1);
			break;
		case 34:
			initSongNpc();
			break;
		case 35:
			break;				
		case 36:
			drawWorldMap();
			break;
		case LASTLOADINGNUM:
			nowState = nextState;
			break;
		}
		break;
	}
	
	xGame.fgameScale = 1.f;
	
	drawImage(&imgLoadingBg, cx, cy, 0, 0, imgLoadingBg.w, imgLoadingBg.h, VH);
	loadingW = (loadingCnt)*imgW(imgLoadingGage0)/LASTLOADINGNUM;
	
	drawPacker(imgLoadingGage0, cx-imgW(imgLoadingGage0)/2, lcdH-35, 0, 0, imgW(imgLoadingGage0), imgH(imgLoadingGage0)/2, VL);
	drawPacker(imgLoadingGage0, cx-imgW(imgLoadingGage0)/2, lcdH-35, 0, imgH(imgLoadingGage0)/2, loadingW, imgH(imgLoadingGage0)/2, VL);
	setFontSize(14);
	gDrawStringBold(cx, lcdH-35, "샵을 불러오는 중입니다...", VH, ALPHA_MAX, ALPHA_MAX, ALPHA_MAX, 82, 49, 38);
	setFontSize(11);
	drawPacker(imgLoadingGage1, cx, lcdH-75, 0, imgH(imgLoadingGage1)/4*(gameCnt%4), imgW(imgLoadingGage1), imgH(imgLoadingGage1)/4, VH);
	drawGameTip(cx,42);
			
	++loadingCnt;	
}
void freeLoading(M_Int32 type)
{
	switch(type)
	{
	case GAME_WORLDMAP:
		break;
	}
}

void initGame()
{	
	xGame.fgameScaleCx = cx;
	xGame.fgameScaleCy = cy;
	
	xMap.totalFloor = 3;
	
	//주차장
	xCarPark[0].lv = 0;
	xCarPark[1].lv = 0;
	xCarPark[2].lv = 0;
	
	//샵 시작,끝좌표
	xMap.shopPointX = 25;
	xMap.shopPointY = 25;
	xMap.shopPointW = 15;
	xMap.shopPointH = 15;
		
	/////////모델
	sprintf(xNpc[0].strName, "앤");
	sprintf(xNpc[1].strName, "레베카");
	sprintf(xNpc[2].strName, "안나");
	sprintf(xNpc[3].strName, "멜리사");
	sprintf(xNpc[4].strName, "펠릭스");
	sprintf(xNpc[5].strName, "바니");
	sprintf(xNpc[6].strName, "주인공");
	sprintf(xNpc[7].strName, "엄마");
	sprintf(xNpc[8].strName, "손님");
	sprintf(xNpc[9].strName, "해설");
		
	xPopup.speakingNpcNum = DONT;
	
    loadImg("rect.png", &imgRect);
    
	isCall = FALSE;	
	xGame.fgameScale = 1.0f;
	getTime();	
}

void setShopMoneyData(int code,int type,int price,int point,int bonusPoint,int firstBonusPoint)
{
	xShop.moneyType[code] = type;
	initSecurity(&xShop.moneyPrice[code], price);
	initSecurity(&xShop.moneyPoint[code], point);
	xShop.moneyPriceBonus[code] = bonusPoint;
	xShop.moneyPriceFirstBonus[code] = firstBonusPoint;
}

void setPremiumData(int code,int type,int price,int point,const char* strTitle)
{
	xShop.premiumPriceType[code] = type;
	initSecurity(&xShop.premiumPrice[code],	price);
	initSecurity(&xShop.premiumPoint[code],	point);
	sprintf(xShop.strPremiumName[code], "%s",strTitle);
}


void initSave()
{
	memset(&xSave, 0, sizeof(xSave));
	xSave.resVer = 0;
	xSave.isKakaoLogin = FALSE;
	xSave.is4inch = TRUE;
	xSave.bgmVol = 50;
	xSave.effVol = 100;
	for(int i=0;i<10;i++)
		xSave.isPushOnOff[i] = TRUE;


	gameSave(SAVE_SLOT_GAME);
}


M_Boolean touchCheck(XTOUCH *touch)
{
	
	if(((touch->xPos< xTouch.xPos+xTouch.wPos) && (xTouch.xPos < touch->xPos+touch->wPos))
	   && ((touch->yPos < xTouch.yPos+xTouch.hPos) && (xTouch.yPos < touch->yPos+touch->hPos)))
		return TRUE;
	
	return FALSE;
}

M_Boolean touchCheckS(XTOUCH *touch)
{
	if(((touch->xPos< xTouchS.xPos+xTouchS.wPos) && (xTouchS.xPos < touch->xPos+touch->wPos))
	   && ((touch->yPos < xTouchS.yPos+xTouchS.hPos) && (xTouchS.yPos < touch->yPos+touch->hPos)))
		return TRUE;
	
	return FALSE;
}


M_Boolean rectCheck(M_Int32 x1,M_Int32 y1,M_Int32 w1,M_Int32 h1,M_Int32 x2,M_Int32 y2,M_Int32 w2,M_Int32 h2)
{
	if(((x2 < x1+w1) && (x1 < x2+w2))
	   && ((y2 < y1+h1) && (y1 < y2+h2)))
		return TRUE;
	
	return FALSE;
}

void initTouchCletEvent(int type, int param1, int param2)
{
	
	touchTypeTemp = DONT;
    ScrollCnt = 0;
	touchType = type;
		

	switch(type)
	{
		case USER_POINT_PRESS_EVENT:		
			touchTypeTemp = MH_KEY_PRESSEVENT;
			isTouch = TRUE;
			xTouch.xPos = param1;
			xTouch.yPos = param2;
			
			xTouch.xPosStart = xTouch.xPos;
			xTouch.yPosStart = xTouch.yPos;
			
			break;
		case USER_POINT_RELEASE_EVENT:	
			touchTypeTemp = MH_KEY_RELEASEEVENT;
			isTouch = TRUE;
			xTouch.xPos = param1;
			xTouch.yPos = param2;
			break;
		case USER_POINT_MOVE_EVENT:
			if(touchTotal == 2)
			{
				if(scaleXbefore[0] != DONT && scaleXbefore[1] != DONT)
				{
					if(++touchScaleCnt > 3)
					{
						fsubTemp[0] = getRadiusSpeed(scaleXnow[0],scaleYnow[0],scaleXnow[1],scaleYnow[1],getArcTan(scaleXnow[0],scaleYnow[0],scaleXnow[1],scaleYnow[1]));					
						fsubTemp[1] = getRadiusSpeed(scaleXbefore[0],scaleYbefore[0],scaleXbefore[1],scaleYbefore[1],getArcTan(scaleXbefore[0],scaleYbefore[0],scaleXbefore[1],scaleYbefore[1]));
											
						fsubTemp[2] = fsubTemp[0] - fsubTemp[1];
						
						if(fsubTemp[2]/1000.f < 0.3f && fsubTemp[2]/1000.f > -0.3f)
							xWorldMap.fscale += fsubTemp[2]/1000.f;
						
						if(xWorldMap.fscale < 0.0f)
							xWorldMap.fscale = 0.0f;
						else if(xWorldMap.fscale > 10.0f)
							xWorldMap.fscale = 10.0f;
					}
				}
			}
												
			if(xTouch.xPosStart <= param1+10
			   && xTouch.xPosStart >= param1-10
			   && xTouch.yPosStart <= param2+10
			   && xTouch.yPosStart >= param2-10)
				return;
			
			
			else if(xTouch.xPos == param1 && xTouch.yPos == param2)
				return;
			else if(param1 < 0 || param2 < 0)
				return;

			touchTypeTemp = MH_KEY_PRESSEVENT;
			isTouch = TRUE;
			xTouch.xPos = param1;
			xTouch.yPos = param2;			
			break;
		default:
			touchTypeTemp = type;
			break;
	}
}

void drawTouchTrace()
{
	
}

void reResLoad()
{
	xmedia.bgTrack = 100;
	xmedia.effTrack = 100;
	
}



void setHackingPopup(int type)
{
	if(xGame.isHacking == FALSE)
	{
		xGame.hackingType = type;
		xGame.isHacking = TRUE;
				
		if(xWorldMap.is5RocksHackingLog == TRUE)
		{
			switch(xGame.hackingType)
			{
			case 0:	//메모리
				setFiveRocksCustom("해킹2","메모리해킹",xSaveTemp.strNickName,"NULL",1);
				break;
			case 1:	//시간
				setFiveRocksCustom("해킹2","시간해킹",xSaveTemp.strNickName,"NULL",1);
				break;
			case 2:	//리소스 다운로드 실패
				break;
			case 3:	//서버캐쉬검사해킹으로 판담
				setFiveRocksCustom("해킹2","서버캐쉬",xSaveTemp.strNickName,"NULL",1);
				break;
			}
		}
		
        
    
		switch(type)
		{
		case 0:	//메모리
			nativePopupExit("해킹으로 의심되어 로그저장이 되었습니다. 해킹을 하실경우 계정정지 및 법적제재를 받을 수 있습니다.");
			break;
		case 1:	//시간
			nativePopupExit("휴대폰의 환경설정에서 현재시간을 자동시간대로 설정하거나, 현재시간을 정확하게 맞춰 주세요.");
			break;
		case 2:	//리소스 다운로드 실패
			nativePopupExit("게임데이타 로딩 실패");
			break;
		case 3:	//서버캐쉬검사해킹으로 판담
			nativePopupExit("해킹으로 의심되어 로그저장이 되었습니다. 해킹을 하실경우 계정정지 및 법적제재를 받을 수 있습니다.");
			break;
		}
	}
}




void loadObjData()
{
	int i,z;
	int index;
	
	index = 0;
	//총타입갯수
	//OBJMAX	상수로 지정해놈
	index +=4;
		
	for(i=0;i<OBJMAX;i++)
	{		
		//타입별총갯수
		xObj.totalNum[i] = getByteToInt(bufData, index);
		index += 4;
				
		for (z = 0; z < xObj.totalNum[i]; z++)
		{
			//x,y,w,h
			xObj.xObjData[i][z].x[0] = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].x[1] = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].y[0] = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].y[1] = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].w[0] = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].w[1] = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].h[0] = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].h[1] = getByteToInt(bufData, index);
			index += 4;
            
			/*
			xObj.xObjData[i][z].price = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].priceType = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].slot = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].thema = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].lv = getByteToInt(bufData, index);
			index += 4;
			xObj.xObjData[i][z].fame = getByteToInt(bufData, index);
			index += 4;
			
			xObj.xObjData[i][z].productionType = getByteToInt(bufData, index)%1000;
			
			index += 4;
			
			for (k = 0; k < 64; k++)
			{
				xObj.xObjData[i][z].strName[k] = bufData[index++];
			}

			if(xObj.xObjData[i][z].productionType == 2)
			{
				xObj.xObjData[i][z].isChair = TRUE;				
			}
			*/
		}
	}
}


void loadMapData(const char* strFileName,int floor)
{
	int index;
	int v,x,y;
	loadData(strFileName,FALSE);
	
	index = 0;
	
	xMap.totalTileX = getByteToInt(bufData, index);
	index += 4;
	xMap.totalTileY = getByteToInt(bufData, index);
	index += 4;
	//맵테이타타입갯수 MAPMAX
	index += 4;
	
	
	for (v = 0; v < MAPMAX; v++)
	{
		//정보0
		//정보1
		//정보2
		//정보3
		//정보4
		for (x = 0; x < xMap.totalTileX; x++)
		{
			for (y = 0; y < xMap.totalTileY; y++)
			{				
				xMap.data[floor][v][x][y] = getByteToInt(bufData, index);
				index += 4;
			}
		}
	}
}

void drawGameTip(int x,int y)
{
	if(xMainMenu.loadTipCnt < xCalendar.nowTime)
	{
		switch(ranDom(0, 18))
		{
		case 0:sprintf(xNotice.strGameTip,"%s","인테리어를 길게 터치하시면 인테리어 수정 모드가 됩니다.");break;
		case 1:sprintf(xNotice.strGameTip,"%s","유행은 오전 10시, 오후 8시에 발생합니다.");break;
		case 2:sprintf(xNotice.strGameTip,"%s","유행의상을 판매하면 2배 이상의 수익금을 획득할 수 있어요.");break;
		case 3:sprintf(xNotice.strGameTip,"%s","친구샵 방문을 통해 도움을 주고 의상까지 요청해봐요.");break;
		case 4:sprintf(xNotice.strGameTip,"%s","카페트는 다른 가구와 상관없이 바닥에 설치할 수 있어요.");break;
		case 5:sprintf(xNotice.strGameTip,"%s","캔디는 친구샵에서 도움, 모델추천, 주문배송으로 획득할 수 있어요.");break;
		case 6:sprintf(xNotice.strGameTip,"%s","모델은 등급이 높을 수록 레이어드 횟수가 높아 피팅이 자유로워요.");break;
		case 7:sprintf(xNotice.strGameTip,"%s","모델을 피팅하 실 때 넣어입기와 빼입기를 잘 활용해 보세요.");break;
		case 8:sprintf(xNotice.strGameTip,"%s","주문배송은 친구에게 의상을 보내는 즉시 보상을 받을 수 있어요.");break;
		case 9:sprintf(xNotice.strGameTip,"%s","좋은 차량 일수록 배송 시간이 짧아져요.");break;
		case 10:sprintf(xNotice.strGameTip,"%s","캔디머신을 이용하시면 눈의여왕 세트를 얻을 수 있어요.");break;
		case 11:sprintf(xNotice.strGameTip,"%s","활동 보상으로 룩을 제공하는 S급 모델도 있답니다.");break;
		case 12:sprintf(xNotice.strGameTip,"%s","추천 친구를 통해 친구를 추가해보세요.");break;
		case 13:sprintf(xNotice.strGameTip,"%s","증축을 통해 또 다른 컨셉의 샵을 꾸며보세요.");break;
		case 14:sprintf(xNotice.strGameTip,"%s","다양한 외벽으로 나만의 차별화 된 샵을 만들어 보세요.");break;
		case 15:sprintf(xNotice.strGameTip,"%s","모델 업그레이드는 패션쇼 가산점에 크게 기여합니다.");break;
		case 16:sprintf(xNotice.strGameTip,"%s","의상을 제작할 슬롯이 부족하신가요? 확장 슬롯을 이용해보세요.");break;
		case 17:sprintf(xNotice.strGameTip,"%s","매 레벨마다 발생하는 아이러브패션 감성 스토리를 놓치지 마세요!");break;
		case 18:sprintf(xNotice.strGameTip,"%s","유행은 최대 10배까지 수익금을 추가로 획득 할 수 있어요.");break;
		}
		xMainMenu.loadTipCnt = xCalendar.nowTime+3;
	}	
	drawPacker(imgLoadingGage2, x, y-1, 0, 0, imgW(imgLoadingGage2), imgH(imgLoadingGage2), VH);
	gSetColor(255,255,255);
	setFontSize(14);
	gDrawString(x-250, y, "TIP.", VR);
	gDrawString(x-250+10, y, xNotice.strGameTip, VL);
	setFontSize(11);
}


void loadImgDocuments(const char* strFileName, XIMG* pImg)
{
    loadImgCash(strFileName, pImg);
}

void addLocalPush(int sec,const char *strText,int pushCode)
{
    sendPush(pushCode, sec, strText,"DONT");
}
void delLocalPush(int pushCode)
{
    canclePush(pushCode);
}

void startIap()
{
	/*
	#define IAP_STATE_DONT		0//사용안함(평상시)
	#define IAP_STATE_ING		1//결제중(키만 막아주자)
	#define IAP_STATE_SUCCED 	2//성공
	#define IAP_STATE_FAIL		3//실패
	#define IAP_STATE_INGRESTORE		4//리스토어
	 */

	xBill.isBilling = TRUE;
	xnet.iapState = IAP_STATE_ING_TP;
        
    char strTempRocks[128];
    memset(strTempRocks, 0, sizeof(strTempRocks));
    
    
    if(xPackagePopup.isPlay == true)
    {
        
#if(MARKET_TYPE == MARKET_TYPE_GOOGLE)
        sprintf(xnet.strIapPid, "package%d",xPackagePopup.selectType);
#else
        sprintf(xnet.strIapPid, "%s",xPackageData[xPackagePopup.selectType].strOneStoreIapId);
#endif
    }
    else
    {
        switch (xWorldMap.state)
        {
        case WORLDMAP_STATE_PREPAY:
                
#if(MARKET_TYPE == MARKET_TYPE_GOOGLE)
                sprintf(xnet.strIapPid, "fixedcharge");
#else
                sprintf(xnet.strIapPid, "0910079136");
#endif
            break;
        default:
            sprintf(strTempRocks, "%d원시도",xShop.moneyPrice[xShop.selectSlot].oriData);
            sprintf(xRocks.strTemp, "%s",xSaveTemp.strNickName);
            setFiveRocksCustom("인앱",strTempRocks,xRocks.strTemp,"NULL",1);
            
            
            sprintf(xRocks.strTemp, "%d원",xShop.moneyPrice[xShop.selectSlot].oriData);
            setFiveRocksCustom("인앱","인앱시도",xRocks.strTemp,"NULL",1);
                
               
#if(MARKET_TYPE == MARKET_TYPE_GOOGLE)
                switch(xShop.selectSlot)
            {
                case 0:sprintf(xnet.strIapPid, "shop_cash_0");break;
                case 1:sprintf(xnet.strIapPid, "shop_cash_1");break;
                case 2:sprintf(xnet.strIapPid, "shop_cash_2");break;
                case 3:sprintf(xnet.strIapPid, "shop_cash_3");break;
                case 4:sprintf(xnet.strIapPid, "shop_cash_4");break;
                case 5:sprintf(xnet.strIapPid, "shop_cash_5");break;
                case 6:sprintf(xnet.strIapPid, "shop_cash_6");break;
            }
#else
                switch(xShop.selectSlot)
            {
                case 0:sprintf(xnet.strIapPid, "0910079130");break;
                case 1:sprintf(xnet.strIapPid, "0910079131");break;
                case 2:sprintf(xnet.strIapPid, "0910079132");break;
                case 3:sprintf(xnet.strIapPid, "0910079133");break;
                case 4:sprintf(xnet.strIapPid, "0910079134");break;
                case 5:sprintf(xnet.strIapPid, "0910079135");break;
            }
#endif
            break;
        }
    }
    
#if(MARKET_TYPE == MARKET_TYPE_GOOGLE)
    googleInApp(xnet.strIapPid);
#else
    oneStoreInApp(xnet.strIapPid);
#endif
}

void prcIap()
{
	int h = 0;
	int alpha;
		
	char strTempRocks[128];
	memset(strTempRocks, 0, sizeof(strTempRocks));
		
	switch(gameCnt%24)
	{
	case 0:h=	0;alpha=	100;break;
	case 1:h=	0;alpha=	91;break;
	case 2:h=	0;alpha=	82;break;
	case 3:h=	1;alpha=	73;break;
	case 4:h=	1;alpha=	64;break;
	case 5:h=	1;alpha=	55;break;
	case 6:h=	2;alpha=	46;break;
	case 7:h=	2;alpha=	37;break;
	case 8:h=	2;alpha=	28;break;
	case 9:h=	2;alpha=	19;break;
	case 10:h=	3;alpha=	10;break;
	case 11:h=	2;alpha=	20;break;
	case 12:h=	2;alpha=	30;break;
	case 13:h=	2;alpha=	40;break;
	case 14:h=	1;alpha=	50;break;
	case 15:h=	1;alpha=	60;break;
	case 16:h=	1;alpha=	70;break;
	case 17:h=	1;alpha=	80;break;
	case 18:h=	0;alpha=	90;break;
	case 19:h=	0;alpha=	100;break;
	case 20:h=	0;alpha=	100;break;
	case 21:h=	0;alpha=	100;break;
	case 22:h=	0;alpha=	100;break;
	case 23:h=	0;alpha=	100;break;
	}
	///////인앱설계/////////
	//인앱요청(인앱 실행중에는 게임키 정지)
	//인앱실패시(실패팝업과 게임키 풀어주기)
	//인앱성공시(네트워크 검증키 발송후 최종 성공처리 해주기)
	if(xBill.isBilling == TRUE)
	{
		xnet.heartBitTime = xCalendar.nowTime;
		xnet.heartBitTime22 = xCalendar.nowTime;				
		if(alpha != 100)
			setAlpha(alpha*ALPHA_MAX/100);
		drawPacker(imgIapIng, cx, cy, 0, 0, imgW(imgIapIng), imgH(imgIapIng), VH);
		setAlpha(ALPHA_MAX);
	}
}


void initLogo()
{
	xLogo.state = LOGO_STATE_COMPANY;
	loadImg("logo1.png", &xLogo.img[1]);
	xLogo.anyCnt = 0;
}

void drawLogo()
{
	switch(xLogo.state)
	{
	case LOGO_STATE_KAKAOGAME:
		drawImage(&xLogo.img[0], cx, cy, 0, 0, xLogo.img[0].w, xLogo.img[0].h, VH);
		switch(xLogo.anyCnt++)
		{
		case 0:
			xLogo.endTime = xCalendar.nowTime;
			break;
		case 1:	//이미지 로딩
			break;
		default:
			if(xCalendar.nowTime - xLogo.endTime > 1)
			{
				xLogo.state = LOGO_STATE_COMPANY;
				xLogo.anyCnt = 0;
			}
			break;
		}
		break;
	case LOGO_STATE_COMPANY:
		drawImage(&xLogo.img[1], cx, cy, 0, 0, xLogo.img[1].w, xLogo.img[1].h, VH);
		switch(xLogo.anyCnt++)
		{
		case 0:
			xLogo.endTime = xCalendar.nowTime;
			break;
		case 1:	//이미지 로딩
			setPacker(PACKER_STATE_WORLDMAP);
			setPacker(PACKER_STATE_WORLDMAP2);
			setPacker(PACKER_STATE_PRODUCTION);
			setPacker(PACKER_STATE_SELL);
			setPacker(PACKER_STATE_INTERIOR);
			setPacker(PACKER_STATE_MAINMENU);
			setPacker(PACKER_STATE_SKILL);
            /////////////////////////////////////////////////
            ////메인 UI 이미지 로딩 KBY
            loadImg("wealth.png", &imgWealth);
            loadImg("main_btn_menu.png", &imgMenu);
            loadImg("main_btn_menuicon1.png", &imgMenuIcon1);
            loadImg("main_btn_menuicon2.png", &imgMenuIcon2);
            loadImg("main_frame_profile.png", &imgProfile);
            loadImg("non_profile_image.png", &imgNonProfile);
            loadImg("main_bar_exp.png", &imgBarExp);
            loadImg("main_bar_warmth.png", &imgBarWarmth);
            loadImg("main_icon_exp_warmth.png", &imgMainExpWarmth);
            loadImg("main_bar_empty.png", &imgBarEmpty);
            /////////////////////////////////////////////////
                
           
			break;
		default:
			if(xCalendar.nowTime - xLogo.endTime > 1)
			{
				setState(GAME_MAINMENU, PLAY_PLAY, DONT);
			}
			break;
		}
		break;
	}
}

void checkHackingPackage()
{
	xHacking.resultNum = DONT;
	
	for(int i=0;i<xHacking.totalNum;i++)
	{
		switch(xHacking.type[i])
		{
		case HACKINGPACKAGE_TYPE_IOS:
			break;
		case HACKINGPACKAGE_TYPE_ANDROID:
			break;
		}
        
        //xHacking.strPackage[i]
        
		if(xHacking.resultNum != DONT)
		{
			return;
		}
	}
}

//유저기본정보(돈,룩,명성,경험치,레벨,캔디)
void checkUserInfoHacking()
{
	setSecurity(&xSaveTemp.money, xSaveTemp.money.oriData);
	setSecurity(&xSaveTemp.cash, xSaveTemp.cash.oriData);
	setSecurity(&xSaveTemp.fame, xSaveTemp.fame.oriData);
	setSecurity(&xSaveTemp.exp, xSaveTemp.exp.oriData);
	setSecurity(&xSaveTemp.lv, xSaveTemp.lv.oriData);
	setSecurity(&xSaveTemp.tired, xSaveTemp.tired.oriData);
}

//룩골드 구매(가격)
//프리미엄 구매(가격)
void checkShopHacking()
{
	for(int i=0;i<20;i++)
	{
		setSecurity(&xShop.moneyPrice[i], xShop.moneyPrice[i].oriData);
		setSecurity(&xShop.moneyPoint[i], xShop.moneyPoint[i].oriData);
	}
	
	for(int i=0;i<SHOPTABPREMIUMMAX;i++)
	{
		setSecurity(&xShop.premiumPrice[i],xShop.premiumPrice[i].oriData);
		setSecurity(&xShop.premiumPoint[i],xShop.premiumPoint[i].oriData);
	}
}

//옷 수익금
//옷 경험치
//옷 시간
//옷 생산갯수
//옷 오픈비용
//옷 명성도
void checkProductionHacking()
{
	for(int type=0;type<FASHIONDATATYPEMAX;type++)
	{
		for(int list=0;list<FASHIONDATAMAX;list++)
		{
			setSecurity(&xFashionData[type][list].price,xFashionData[type][list].price.oriData);
			setSecurity(&xFashionData[type][list].exp,xFashionData[type][list].exp.oriData);
			setSecurity(&xFashionData[type][list].fame,xFashionData[type][list].fame.oriData);
			setSecurity(&xFashionData[type][list].makeTime,xFashionData[type][list].makeTime.oriData);
			setSecurity(&xFashionData[type][list].makeNum,xFashionData[type][list].makeNum.oriData);
			setSecurity(&xFashionData[type][list].sellPrice,xFashionData[type][list].sellPrice.oriData);
		}
	}
}

//인테리어 가격
void checkInteriorHacking()
{
	for(int type=0;type<FASHIONDATATYPEMAX;type++)
	{
		for(int list=0;list<FASHIONDATAMAX;list++)
		{
			setSecurity(&xObj.xObjData[type][list].price,xObj.xObjData[type][list].price.oriData);
		}
	}
}

//자동차가격
void checkCarHacking()
{
	for(int i=0;i<CARDATAMAX;i++)
	{
		setSecurity(&xCarData[i].price, xCarData[i].price.oriData);
		setSecurity(&xCarData[i].timePer, xCarData[i].timePer.oriData);
	}
}

//퀘스트완료보상
void checkQuestHacking()
{
	for(int i=0;i<QUESTMAINMAX;i++)
	{
		setSecurity(&xQuestDataMain[i].giftMax[0],xQuestDataMain[i].giftMax[0].oriData);
		setSecurity(&xQuestDataMain[i].giftMax[1],xQuestDataMain[i].giftMax[1].oriData);
		setSecurity(&xQuestDataMain[i].giftMax[2],xQuestDataMain[i].giftMax[2].oriData);
	}
	
	for(int i=0;i<QUESTNORMALMAX;i++)
	{
		setSecurity(&xQuestDataNormal[i].giftMax[0],xQuestDataNormal[i].giftMax[0].oriData);
		setSecurity(&xQuestDataNormal[i].giftMax[1],xQuestDataNormal[i].giftMax[1].oriData);
		setSecurity(&xQuestDataNormal[i].giftMax[2],xQuestDataNormal[i].giftMax[2].oriData);
	}
}

//확장증축
void checkExtensionHacking()
{
	for(int i=0;i<EXTENSIONSHOPTILEMAX;i++)
	{
		setSecurity(&xExtensionShop.tilePrice[i][0], xExtensionShop.tilePrice[i][0].oriData);
		setSecurity(&xExtensionShop.tilePrice[i][1], xExtensionShop.tilePrice[i][1].oriData);
	}
	
	for(int i=0;i<EXTENSIONSHOPFLOORMAX;i++)
	{
		setSecurity(&xExtensionShop.floorPrice[i][0],xExtensionShop.floorPrice[i][0].oriData);
		setSecurity(&xExtensionShop.floorPrice[i][1],xExtensionShop.floorPrice[i][1].oriData);
	}
}

//직원헤어
//직원얼굴
void checkStaffHacking()
{
	for(int i=0;i<HAIRDATAMAX;i++)
		setSecurity(&xHairData[i].price, xHairData[i].price.oriData);
		
	for(int i=0;i<FACEDATAMAX;i++)
		setSecurity(&xFaceData[i].price, xFaceData[i].price.oriData);
}

//선물함 해킹
void checkGiftHacking()
{
	for(int i=0;i<MAILSLOTMAX;i++)
	{
		setSecurity(&xMail.xMailSlot[i].giftValue, xMail.xMailSlot[i].giftValue.oriData);
	}
}

//미니게임해킹
void checkMinigameHacking()
{
	for(int i=0;i<MINIGAMESLOTMAX;i++)
	{
		setSecurity(&xMiniGame.xMiniGameSlot[i].slotCode, xMiniGame.xMiniGameSlot[i].slotCode.oriData);
	}
	
	setSecurity(&xMiniGame.userTired, xMiniGame.userTired.oriData);
	
}

//모델해킹
void checkModelHacking()
{
	for(int i=0;i<MODELDATAMAX;i++)
	{
		setSecurity(&xModelData[i].giftTime, xModelData[i].giftTime.oriData);
		setSecurity(&xModelData[i].giftNum, xModelData[i].giftNum.oriData);
	}
}

//카톡친구
//패션쇼 캔디사용
void checkEtcHacking()
{
	for(int i=0;i<5;i++)
		setSecurity(&xKakao.inviteNum[i], xKakao.inviteNum[i].oriData);
		
	setSecurity(&xKakao.totalKakaoInvite, xKakao.totalKakaoInvite.oriData);		
	setSecurity(&xFashionShow.userTired, xFashionShow.userTired.oriData);
}


