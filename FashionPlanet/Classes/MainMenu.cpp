#include "Global.h"

XMAINMENU xMainMenu;
XIDMAKE xIdMake;
XRESCHECK xResCheck;
XETCDOWNLOAD xEtcDownLoad;

XIMG imgLoadingBg;
XIMG imgYoung;
XIMG imgPermissions;
XIMG imgTitleBG;

void initMainMenu()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    startVerCheck();
#else
    xMainMenu.state = MAINMENU_STATE_PERMISSIONCHECK_NET;
    checkBluetoothPermission();
#endif
}

void startVerCheck()
{
    xMainMenu.state = MAINMENU_STATE_VERCHECK;
    xMainMenu.anyCnt = 0;
    
    xIdMake.emailErr = IDMAKEERR_TYPE_DONT;
    xIdMake.passErr = IDMAKEERR_TYPE_DONT;
    xIdMake.nickNameErr = IDMAKEERR_TYPE_DONT;
    
    
    xIdMake.xDragScrollArea.touchXpos = DONT;
    xIdMake.xDragScrollArea.touchYpos = DONT;
    xIdMake.xDragScrollArea.touchXposBefore = DONT;
    xIdMake.xDragScrollArea.touchYposBefore = DONT;
    xIdMake.xDragScrollArea.selectNum = 0;
    xIdMake.xDragScrollArea.pos = 0;
    xIdMake.xDragScrollArea.speed = 0;
    
    xIdMake.xDragScrollAge.touchXpos = DONT;
    xIdMake.xDragScrollAge.touchYpos = DONT;
    xIdMake.xDragScrollAge.touchXposBefore = DONT;
    xIdMake.xDragScrollAge.touchYposBefore = DONT;
    xIdMake.xDragScrollAge.selectNum = 19;
    xIdMake.xDragScrollAge.pos = 0;
    xIdMake.xDragScrollAge.speed = 0;
    
    getDeviceInfo();
    netSend(CMD_AUTHENTICATION,DONT);
    xMainMenu.initCnt = 0;
    
    xIdMake.isClause[0] = FALSE;
    xIdMake.isClause[1] = FALSE;

}


void MainMenuCletEvent(int type, int param1, int param2,int touchId)
{
	if(xWorldMap.isKeyReturn == TRUE)
	{
		if(type == MH_KEY_RELEASEEVENT)
		{
			xWorldMap.isKeyReturn = FALSE;
			return;
		}
	}
	
	switch(playState)
	{
	case PLAY_MSG:
		keyPopup(type,param1,param2);
		return;
		break;
	}
	switch(xMainMenu.state)
	{
    case MAINMENU_STATE_PERMISSIONCHECK:
        if(touchCheck(&xTouchOk) == TRUE && touchType == USER_POINT_PRESS_EVENT)
        {
            freeImg(&imgPermissions);
            startBluetoothPermission();
            xMainMenu.state = MAINMENU_STATE_PERMISSIONCHECK_NET;
        }
        break;
	case MAINMENU_STATE_SERVERNOTICE:
		if(touchCheck(&xTouchOk) == TRUE && touchType == USER_POINT_PRESS_EVENT)
		{
			gameExit();
		}
		break;
	case MAINMENU_STATE_IDMAKE:
		switch(xIdMake.state)
		{
		case IDMAKE_STATE_IDMAKE:
			if(touchType == USER_POINT_PRESS_EVENT)
			{
				if(touchCheck(&xIdMake.xTouchArea) == TRUE)
				{
					xIdMake.isSelectArea = TRUE;
				}
				else
					xIdMake.isSelectArea = FALSE;
				
				if(xIdMake.isSelectArea == FALSE && touchCheck(&xIdMake.xTouchAge) == TRUE)
				{
					xIdMake.isSelectAge = TRUE;
				}
				else
					xIdMake.isSelectAge = FALSE;
			}
			
			if(xIdMake.isSelectArea == TRUE)
			{
				if(type == MH_KEY_PRESSEVENT)
				{
					dragScrollKeyPrc(&xIdMake.xDragScrollArea,2);
				}
				else if(type == MH_KEY_RELEASEEVENT)
				{
					if(xIdMake.xDragScrollArea.touchXposBefore != DONT)
					{
						dragScrollKeyPrc(&xIdMake.xDragScrollArea,3);
					}					
					xIdMake.xDragScrollArea.touchXpos = DONT;
					xIdMake.xDragScrollArea.touchYpos = DONT;
					xIdMake.xDragScrollArea.touchXposBefore = DONT;
					xIdMake.xDragScrollArea.touchYposBefore = DONT;
					xIdMake.isSelectArea = FALSE;
				}
			}
			else if(xIdMake.isSelectAge == TRUE)
			{
				if(type == MH_KEY_PRESSEVENT)
				{
					dragScrollKeyPrc(&xIdMake.xDragScrollAge,2);
				}
				else if(type == MH_KEY_RELEASEEVENT)
				{
					if(xIdMake.xDragScrollAge.touchXposBefore != DONT)
					{
						dragScrollKeyPrc(&xIdMake.xDragScrollAge,3);
					}
					xIdMake.xDragScrollAge.touchXpos = DONT;
					xIdMake.xDragScrollAge.touchYpos = DONT;
					xIdMake.xDragScrollAge.touchXposBefore = DONT;
					xIdMake.xDragScrollAge.touchYposBefore = DONT;
					xIdMake.isSelectAge = FALSE;
				}
			}
			else if(type == MH_KEY_PRESSEVENT)
			{
				if(touchCheck(&xIdMake.xTouchNickName) == TRUE && touchType == USER_POINT_PRESS_EVENT)
				{
					playSnd(SND_MENU_OK);
					xIdMake.nickNameErr = IDMAKEERR_TYPE_DONT;
                    
                    setTextField(TEXTBOX_TYPE_NICKNAME, lcdW/2, lcdH+999, 200, 25);
				}
				else if(touchCheck(&xIdMake.xTouchSex[0]) == TRUE && touchType == USER_POINT_PRESS_EVENT)
				{
					playSnd(SND_MENU_OK);
					xIdMake.sex = 0;
				}
				else if(touchCheck(&xIdMake.xTouchSex[1]) == TRUE && touchType == USER_POINT_PRESS_EVENT)
				{
					playSnd(SND_MENU_OK);
					xIdMake.sex = 1;
				}
				else if(touchCheck(&xTouchOk) == TRUE && touchType == USER_POINT_PRESS_EVENT)
				{
					playSnd(SND_MENU_OK);
					
													
					
					if(strcmp(xIdMake.strNickName, "대표자명 입력") != 0)
					{
						int strByte = getStringByte(xIdMake.strNickName);
						int kor = strByte/1000;
						int eng = strByte%1000;
						int korEng = kor+eng;
						//한글 1자~6자
						//영문 2자~8자
												
						if(kor > 0)
						{
							if(korEng < 1 || korEng > 6)
								xIdMake.nickNameErr = IDMAKEERR_TYPE_NICKNAMEERR;
						}
						else
						{
							if(korEng < 2 || korEng > 8)
								xIdMake.nickNameErr = IDMAKEERR_TYPE_NICKNAMEERR;
						}
						
						if(getCharSpecialCnt(xIdMake.strNickName) > 0)
							xIdMake.nickNameErr = IDMAKEERR_TYPE_NICKNAMEERR3;
						
							
						xIdMake.age = AGESTART-xIdMake.xDragScrollAge.selectNum;
                        xIdMake.area = xIdMake.xDragScrollArea.selectNum;
						
						if(xIdMake.nickNameErr == IDMAKEERR_TYPE_DONT)
						{                            
                            netSend(CMD_IDMAKE,DONT);
						}
					}
				}
			}
			break;
		case IDMAKE_STATE_LOGINKAKAO:				
			if(type == MH_KEY_PRESSEVENT)
			{
				if(touchCheck(&xIdMake.xTouchLoginBtn) == TRUE && touchType == USER_POINT_PRESS_EVENT)
				{
					playSnd(SND_MENU_OK);
                    googleLogin();
				}
				else if(touchCheck(&xIdMake.xTouchLoginIdMakeBtn) == TRUE && touchType == USER_POINT_PRESS_EVENT)
				{
					if(xWorldMap.isAppReview == TRUE)
					{
						playSnd(SND_MENU_OK);
						//게스트로그인 기록이 있다면 저장해둔 아이디와 암호로 로그인
						//게스트로그인 기록이 없다면 아이디생성
						setPopup(POPUP_GUESTLOGINYESNO, playState, playState, 0, DONT);
					}
				}
			}
			break;
		case IDMAKE_STATE_CLAUSE:
			if(type == MH_KEY_PRESSEVENT)
			{
                if(touchCheck(&xIdMake.xTouchClauseLink[0]) == TRUE && touchType == USER_POINT_PRESS_EVENT)
                {
                    playSnd(SND_MENU_OK);
                    startWebView("http://cafe.naver.com/ilovefashionbluefi/3");
                }
                else if(touchCheck(&xIdMake.xTouchClauseLink[1]) == TRUE && touchType == USER_POINT_PRESS_EVENT)
                {
                    playSnd(SND_MENU_OK);
                    startWebView("http://cafe.naver.com/ilovefashionbluefi/4");
                }
				else if(touchCheck(&xIdMake.xTouchClauseBtn[0]) == TRUE && touchType == USER_POINT_PRESS_EVENT)
				{
					playSnd(SND_MENU_OK);
					xIdMake.isClause[0] = TRUE;
				}
				else if(touchCheck(&xIdMake.xTouchClauseBtn[1]) == TRUE && touchType == USER_POINT_PRESS_EVENT)
				{
					playSnd(SND_MENU_OK);
					xIdMake.isClause[1] = TRUE;
				}
                
				
				if(xIdMake.isClause[0] == TRUE && xIdMake.isClause[1] == TRUE)
				{
					xIdMake.state = IDMAKE_STATE_LOGINKAKAO;

				}
			}
			else if(type == MH_KEY_RELEASEEVENT)
			{
				
			}
			break;
		}
		break;
	}
}

void paintMainMenu()
{
	int initType;
		
	if(xDownLoader.totalSize == 0)
		xDownLoader.totalSize = 1;
	
//	drawPacker(IMG_MainMenuBg, 0, 0, 0, 0, imgW(IMG_MainMenuBg), imgH(IMG_MainMenuBg), TL);
	drawImage(&imgTitleBG, 0, 0, 0, 0, imgTitleBG.w, imgTitleBG.h, TL);
		
    //drawImage(&imgYoung, lcdW-58, 100, 0, 0, imgYoung.w, imgYoung.h, VH);
	
	if(xMainMenu.state == MAINMENU_STATE_RESCHECK && xSave.resVer < xResCheck.totalVer)//버전 체크 이후, 업데이트
	{
		switch(xResCheck.state)
		{
		case RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_ING:
		case RESCHECK_STATE_FILE_DOWNLOAD_START:
		case RESCHECK_STATE_FILE_DOWNLOAD_ING:
		case RESCHECK_STATE_FILESCRIPT_DOWNLOAD_START:
		case RESCHECK_STATE_FILESCRIPT_DOWNLOAD_ING:
		case RESCHECK_STATE_FILE_DOWNLOAD_UNZIP:
			if(xResCheck.isZip[xSave.resVer] == TRUE)
			{
				int nS = xDownLoader.nowSize/100;
				int tS = xDownLoader.totalSize/100;
                
                nS = 1;
                tS = 1;
                
				
				int loadingW = nS*imgW(imgLoadingGage0)/tS;
				switch(xDownLoader.state)
				{
				case DOWNLOADER_STATE_SUCCESS:
					//압축해제중
					loadingW = tS*imgW(imgLoadingGage0)/tS;
					sprintf(strTempS, "압축해제 중(%d/%d)",xSave.resVer+1,xResCheck.totalVer);
					break;
				default:
					sprintf(strTempS, "리소스 다운로드 중(%d/%d)",xSave.resVer+1,xResCheck.totalVer);
					break;
				}
				drawPacker(imgLoadingGage0, cx-imgW(imgLoadingGage0)/2, lcdH-35, 0, 0, imgW(imgLoadingGage0), imgH(imgLoadingGage0)/2, VL);
				drawPacker(imgLoadingGage0, cx-imgW(imgLoadingGage0)/2, lcdH-35, 0, imgH(imgLoadingGage0)/2, loadingW, imgH(imgLoadingGage0)/2, VL);
				gSetColor(255,255,255);
				gDrawString(cx, lcdH-35, strTempS, VH);
				drawGameTip(cx,lcdH-75);
			}
			else
			{
				sprintf(strTempS, "리소스 업데이트 중(%d/%d)",xSave.resVer+1,xResCheck.totalVer);
				int loadingW = xResCheck.nowFileList*imgW(imgLoadingGage0)/xResCheck.totalFileList;
				
				drawPacker(imgLoadingGage0, cx-imgW(imgLoadingGage0)/2, lcdH-35, 0, 0, imgW(imgLoadingGage0), imgH(imgLoadingGage0)/2, VL);
				drawPacker(imgLoadingGage0, cx-imgW(imgLoadingGage0)/2, lcdH-35, 0, imgH(imgLoadingGage0)/2, loadingW, imgH(imgLoadingGage0)/2, VL);
				gSetColor(255,255,255);
				gDrawString(cx, lcdH-35, strTempS, VH);
				drawGameTip(cx,lcdH-75);
			}
			break;
		}
	}
	else
	{
		if(playState != PLAY_MSG)
		{
			switch(xMainMenu.state)
			{
			case MAINMENU_STATE_VERCHECK:
			case MAINMENU_STATE_INITFILEDOWN:
			case MAINMENU_STATE_HACKINGCHECK:
			case MAINMENU_STATE_RESCHECK:
			case MAINMENU_STATE_LOGIN:
			case MAINMENU_STATE_INITCHECK:
				drawLodingText();
				break;
			}
		}
	}
	
	switch(xMainMenu.state)
	{
    case MAINMENU_STATE_PERMISSIONCHECK:
        if(imgPermissions.texture == NULL)
        {
            loadImg("permission.png", &imgPermissions);
        }
            
        drawImage(&imgPermissions, cx, cy, 0, 0, imgPermissions.w, imgPermissions.h, VH);
            
        xTouchOk.wPos = 230;
        xTouchOk.hPos = 100;
        xTouchOk.xPos = cx-xTouchOk.wPos/2;
        xTouchOk.yPos = cy+220-xTouchOk.hPos/2;
            
        /*
        gSetColor(255, 0, 0);
        setAlpha(100);
        fillRect(xTouchOk.xPos, xTouchOk.yPos, xTouchOk.wPos, xTouchOk.hPos);
        setAlpha(ALPHA_MAX);
        */
        break;
	case MAINMENU_STATE_SERVERNOTICE:
		drawServerNotice();
		break;
	case MAINMENU_STATE_VERCHECK:
		//버전체크
		break;
	case MAINMENU_STATE_INITFILEDOWN:
		switch(xResCheck.state)
		{
		case RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_START:
            sprintf(xDownLoader.strTempUrl,"%s/%d/Data/initfile.dat", xNetData.strCdnUrl,DATAVER);
            dataDownLoad(xDownLoader.strTempUrl,"initfile.dat",DATADOWNLOAD_TYPE_BUFF);
			xResCheck.state = RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_ING;
			break;
		case RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_ING:
			switch(xDownLoader.state)
			{
			case DOWNLOADER_STATE_ING:						
				break;
			case DOWNLOADER_STATE_ERR:
				if(playState == PLAY_PLAY)
					setPopup(POPUP_SERVERERR, playState, playState, 0, DONT);
				break;
			case DOWNLOADER_STATE_SUCCESS:
				//메인스크립트파일체크
                loadNativeFileData("buffer.dat", bufData, &bufDataSize);
					
				int index = 0;
				int urlSize = 0;
			
				xResCheck.totalFileList = getByteToInt(bufData,index);
				index +=4;
				for(int i=0;i<xResCheck.totalFileList;i++)
				{
					urlSize = getByteToInt(bufData,index);
					index +=4;
					memset(xResCheck.strFileList[i],0x00,sizeof(xResCheck.strFileList[i]));
					for(int f=0;f<urlSize;f++)
						xResCheck.strFileList[i][f] = bufData[index++];
				}
				xResCheck.state = RESCHECK_STATE_FILE_DOWNLOAD_START;
				xResCheck.nowFileList = 0;
				break;
			}
			break;
		case RESCHECK_STATE_FILE_DOWNLOAD_START:
			if(xResCheck.nowFileList < xResCheck.totalFileList)
			{
                sprintf(xDownLoader.strTempUrl,"%s/%d/Data/%s", xNetData.strCdnUrl,DATAVER,xResCheck.strFileList[xResCheck.nowFileList]);

                dataDownLoad(xDownLoader.strTempUrl,xResCheck.strFileList[xResCheck.nowFileList],DATADOWNLOAD_TYPE_BUFF);
				xResCheck.state = RESCHECK_STATE_FILE_DOWNLOAD_ING;
                
			}
			else	//전부다 받았다면
			{
				xMainMenu.state = MAINMENU_STATE_HACKINGCHECK;
			}
			break;
		case RESCHECK_STATE_FILE_DOWNLOAD_ING:
			switch(xDownLoader.state)
			{
			case DOWNLOADER_STATE_ING:
				break;
			case DOWNLOADER_STATE_ERR:
				if(playState == PLAY_PLAY)
					setPopup(POPUP_SERVERERR, playState, playState, 0, DONT);
				break;
			case DOWNLOADER_STATE_SUCCESS:
                    
                loadNativeFileData("buffer.dat", bufData, &bufDataSize);
                    
				initType = getExcelTypeNum(xResCheck.strFileList[xResCheck.nowFileList]);
				switch(initType)
				{
				case EXCEL_PS_WOBD:
					loadObjData();
					break;
				default:
					loadExcelParserByte(initType);
					break;
				}
				++xResCheck.nowFileList;
				xResCheck.state = RESCHECK_STATE_FILE_DOWNLOAD_START;
				break;
			}
			break;
		}
		break;
	case MAINMENU_STATE_HACKINGCHECK:
		if(playState != PLAY_MSG)
			checkHackingPackage();
			
		if(xHacking.resultNum != DONT)
		{
			if(playState != PLAY_MSG)
				setPopup(POPUP_HACKINGPACKAGE, playState, playState, 0, DONT);
		}
		else
		{
			xMainMenu.state = MAINMENU_STATE_RESCHECK;
			xResCheck.state = RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_START;
			xMainMenu.anyCnt = 0;
		}
		break;
	case MAINMENU_STATE_RESCHECK:
		switch(xResCheck.state)
		{
		case RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_START:
            sprintf(xDownLoader.strTempUrl,"%s/%d/Resource/resource.dat", xNetData.strCdnUrl,DATAVER);
            dataDownLoad(xDownLoader.strTempUrl,"resdownload.dat",DATADOWNLOAD_TYPE_SDCARD);
            xResCheck.state = RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_ING;
			break;
		case RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_ING:
			switch(xDownLoader.state)
			{
			case DOWNLOADER_STATE_ING:				
				break;
			case DOWNLOADER_STATE_ERR:
				if(playState == PLAY_PLAY)
					setPopup(POPUP_SERVERERR, playState, playState, 0, DONT);
				break;
			case DOWNLOADER_STATE_SUCCESS:
				//메인스크립트파일체크
				loadExcelParser(EXCEL_PS_RESDOWN_FILE,TRUE);
				if(xSave.resVer <xResCheck.totalVer)
				{
					if(xResCheck.resInit++ == 0)
					{
                        if(xSave.resVer == 0)
                            setFiveRocksCustom("퍼널분석","1.게임실행","NULL","NULL",1);
                        
						setPopup(POPUP_RESDOWNYESNO, playState, playState, 0, DONT);
						xResCheck.state = RESCHECK_STATE_FILESCRIPT_DOWNLOAD_POPUP;
					}
					else
					{
						xResCheck.state = RESCHECK_STATE_FILESCRIPT_DOWNLOAD_START;
					}
				}
				else
				{
                    freeImg(&imgLoadingBg);
					int loadImgNum = 0;
					if(xMainMenu.totalLoadingImg > 0)
						loadImgNum = ranDom(0, xMainMenu.totalLoadingImg-1);
					
					sprintf(strTempS,"loadingbg%d.png", xMainMenu.loadingImgSlot[loadImgNum]);
					loadImgDocuments(strTempS, &imgLoadingBg);
                    
                    if(xSave.isKakaoLogin == FALSE)
					{
						xMainMenu.state = MAINMENU_STATE_IDMAKE;
						xIdMake.state = IDMAKE_STATE_CLAUSE;
					}
					else
					{
						xMainMenu.state = MAINMENU_STATE_LOGIN;
						xMainMenu.anyCnt = 0;
                        googleLogin();
					}
				}
				break;
			}
			break;
		case RESCHECK_STATE_FILESCRIPT_DOWNLOAD_START:
			if(xResCheck.isZip[xSave.resVer] == TRUE)
			{
                if(xSave.resVer == 0)
                    setFiveRocksCustom("퍼널분석","2.리소스 다운로드 시작","NULL","NULL",1);
                
                sprintf(xDownLoader.strTempUrl,"%s/%d/Resource/%s", xNetData.strCdnUrl,DATAVER,xResCheck.strUrlDir[xSave.resVer]);
				dataDownLoad(xDownLoader.strTempUrl,"res.zip",DATADOWNLOAD_TYPE_SDCARD);
				xResCheck.state = RESCHECK_STATE_FILESCRIPT_DOWNLOAD_ING;
			}
			else
			{
                sprintf(xDownLoader.strTempUrl,"%s/%d/Resource/%s", xNetData.strCdnUrl,DATAVER,xResCheck.strUrlDir[xSave.resVer]);
				dataDownLoad(xDownLoader.strTempUrl,"resscript.dat",DATADOWNLOAD_TYPE_SDCARD);
				xResCheck.state = RESCHECK_STATE_FILESCRIPT_DOWNLOAD_ING;
			}
			break;
		case RESCHECK_STATE_FILESCRIPT_DOWNLOAD_ING:
			switch(xDownLoader.state)
			{
			case DOWNLOADER_STATE_ING:				
				break;
			case DOWNLOADER_STATE_ERR:
				if(playState == PLAY_PLAY)
					setPopup(POPUP_SERVERERR, playState, playState, 0, DONT);
				break;
			case DOWNLOADER_STATE_SUCCESS:
				if(xResCheck.isZip[xSave.resVer] == TRUE)
				{
					//압축해제하기
					xResCheck.state = RESCHECK_STATE_FILE_DOWNLOAD_UNZIP;
				}
				else
				{
					//리소스리스트스크립트 분석후 다운로드 받기
					loadData("resscript.dat",TRUE);
					{
						int index = 0;
						int urlSize = 0;

						xResCheck.totalFileList = getByteToInt(bufData,index);
						
						index +=4;
						for(int i=0;i<xResCheck.totalFileList;i++)
						{
							urlSize = getByteToInt(bufData,index);
													
							index +=4;
							memset(xResCheck.strFileList[i],0x00,sizeof(xResCheck.strFileList[i]));
							for(int f=0;f<urlSize;f++)
								xResCheck.strFileList[i][f] = bufData[index++];
						}
					}
					xResCheck.state = RESCHECK_STATE_FILE_DOWNLOAD_START;
					xResCheck.nowFileList = 0;
				}
				break;
			}
			break;
		case RESCHECK_STATE_FILE_DOWNLOAD_START:
			if(xResCheck.nowFileList < xResCheck.totalFileList)
			{
				sprintf(strTempS,"%s%s",xResCheck.strUrlDir[xSave.resVer],xResCheck.strFileList[xResCheck.nowFileList]);
				
				
				xResCheck.strFileList[xResCheck.nowFileList][strlen(xResCheck.strFileList[xResCheck.nowFileList])-1] = 'p';
				xResCheck.strFileList[xResCheck.nowFileList][strlen(xResCheck.strFileList[xResCheck.nowFileList])-2] = 'p';
				xResCheck.strFileList[xResCheck.nowFileList][strlen(xResCheck.strFileList[xResCheck.nowFileList])-3] = 'p';
				dataDownLoad(strTempS,xResCheck.strFileList[xResCheck.nowFileList],DATADOWNLOAD_TYPE_SDCARD);
				xResCheck.state = RESCHECK_STATE_FILE_DOWNLOAD_ING;
			}
			else	//전부다 받았다면
			{
				xResCheck.state = RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_ING;
				xDownLoader.state = DOWNLOADER_STATE_SUCCESS;
				
				xSave.resVer++;
				gameSave(SAVE_SLOT_GAME);
			}
			break;
		case RESCHECK_STATE_FILE_DOWNLOAD_ING:
			switch(xDownLoader.state)
			{
			case DOWNLOADER_STATE_ING:				
				break;
			case DOWNLOADER_STATE_ERR:
				if(playState == PLAY_PLAY)
					setPopup(POPUP_SERVERERR, playState, playState, 0, DONT);
				break;
			case DOWNLOADER_STATE_SUCCESS:
				++xResCheck.nowFileList;
				xResCheck.state = RESCHECK_STATE_FILE_DOWNLOAD_START;
				break;
			}
			break;
		case RESCHECK_STATE_FILE_DOWNLOAD_UNZIP:
			unZip("res.zip");
			xResCheck.state = RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_ING;
			xDownLoader.state = DOWNLOADER_STATE_SUCCESS;
			
            if(xSave.resVer == 0)
                setFiveRocksCustom("퍼널분석","3.리소스 다운로드 완료","NULL","NULL",1);
                
                
			xSave.resVer++;
			gameSave(SAVE_SLOT_GAME);
			break;
		}
		break;
	case MAINMENU_STATE_IDMAKE:
		drawIdMake();
		break;
	case MAINMENU_STATE_LOGIN:
	case MAINMENU_STATE_INITCHECK:
		
		if(xMainMenu.state == MAINMENU_STATE_INITCHECK)
		{
			switch(xMainMenu.initCnt)
			{
			case 0:
				xMainMenu.isInitNet = FALSE;
				xMainMenu.initCnt++;
				/////////////////////////////////////////////////////////////////////////////
				//서버 초기화 정보 가져오기
				netSend(CMD_GETGAMEDATA, DONT);
				////////////////////////////////////////////////////////////////////////////
				break;
			case 1:		//헹거
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetMap.floor = 0;
					xNetMap.action = 0;
					xNetMap.code = 2000;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX+6;
					xNetMap.mapY = xMap.shopPointY+4;
					xMap.data[xNetMap.floor][MAP_TYPE_OBJ][xNetMap.mapX][xNetMap.mapY] = xNetMap.code;
					netSend(CMD_SETMAP, DONT);
				}
				break;
			case 2:		//카운터
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetMap.floor = 0;
					xNetMap.action = 0;
					xNetMap.code = 1;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX+2;
					xNetMap.mapY = xMap.shopPointY+2;
					netSend(CMD_SETMAP, DONT);
				}
				break;
			case 3:		//피팅룸
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetMap.floor = 0;
					xNetMap.action = 0;
					xNetMap.code = 1000;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX;
					xNetMap.mapY = xMap.shopPointY+6;
					netSend(CMD_SETMAP, DONT);
				}
				break;
			case 4:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					/////////////////////////////////////////////////////////////////////////////
					//문
					xNetMap.floor = 0;
					xNetMap.action = 0;	//0:신규1:업데이트2:삭제
					xNetMap.code = -8000;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX+5;
					xNetMap.mapY = xMap.shopPointY-1;
					netSend(CMD_SETMAP, DONT);
					////////////////////////////////////////////////////////////////////////////
				}
				break;
			case 5:		//거울
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetMap.floor = 0;
					xNetMap.action = 0;
					xNetMap.code = 6007;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX+6;
					xNetMap.mapY = xMap.shopPointY+6;
					netSend(CMD_SETMAP, DONT);
				}
				break;
			case 6:		//데코나무
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetMap.floor = 0;
					xNetMap.action = 0;
					xNetMap.code = 6002;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX+4;
					xNetMap.mapY = xMap.shopPointY;
					netSend(CMD_SETMAP, DONT);
				}
				break;
			case 7:		//책장
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetMap.floor = 0;
					xNetMap.action = 0;
					xNetMap.code = 6005;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX;
					xNetMap.mapY = xMap.shopPointY+4;
					netSend(CMD_SETMAP, DONT);
				}
				break;
			case 8:		//창문
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					/////////////////////////////////////////////////////////////////////////////
					//문
					xNetMap.floor = 0;
					xNetMap.action = 0;	//0:신규1:업데이트2:삭제
					xNetMap.code = -7000;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX+1;
					xNetMap.mapY = xMap.shopPointY-1;
					netSend(CMD_SETMAP, DONT);
					////////////////////////////////////////////////////////////////////////////
				}
				break;
			case 9:		//창문
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					/////////////////////////////////////////////////////////////////////////////
					//문
					xNetMap.floor = 0;
					xNetMap.action = 0;	//0:신규1:업데이트2:삭제
					xNetMap.code = 7001;
					xNetMap.key = 0;
					xNetMap.mapX = xMap.shopPointX-1;
					xNetMap.mapY = xMap.shopPointY+1;
					netSend(CMD_SETMAP, DONT);
					////////////////////////////////////////////////////////////////////////////
				}
				break;
			case 10:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;

					////////////////////////////////////////////////////////////////////////////////
					xNetStaff.floor = 0;
					xNetStaff.type = 0;		//0판매 1응대
					sprintf(xNetStaff.strNickName, "%s","1층 판매원");
					xNetStaff.sex = 0;
					xNetStaff.layer[0] = STAFF0_HAIRCODE;	//헤어
					xNetStaff.layer[1] = STAFF0_FACECODE;		//표정
					xNetStaff.layer[2] = STAFF0_FASHIONCODE0;//상의
					xNetStaff.layer[3] = STAFF0_FASHIONCODE1;//하의
					xNetStaff.layer[4] = STAFF0_FASHIONCODE2;//원피스
					xNetStaff.layer[5] = STAFF0_FASHIONCODE3;//구두
					xNetStaff.inFitting = 0;
										
					
					sprintf(xPaymentAssistant[xNetStaff.floor].strName, "%s",xNetStaff.strNickName);
					
					for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
						xPaymentAssistant[xNetStaff.floor].xF.code[ff] = DONT;
					
					for(int f=2;f<6;f++)
					{
						if(xNetStaff.layer[f] != DONT)
						{
							setMapData(xNetStaff.layer[f]);//xMap.rever,xMap.type,xMap.listNum 구하기
							xPaymentAssistant[xNetStaff.floor].xF.code[xFashionData[xMap.type][xMap.listNum].layer] = xMap.type*1000+xMap.listNum;
						}
					}					
					xPaymentAssistant[xNetStaff.floor].xFace.hairNum = xNetStaff.layer[0];
					xPaymentAssistant[xNetStaff.floor].xFace.faceNum = xNetStaff.layer[1];
					netSend(CMD_SETSTAFF, DONT);
					///////////////////////////////////////////////////////////////////////////////////
				}					
				break;
			case 11:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					///////////////////////////////////////////////////////////////////////////////
					xNetStaff.floor = 1;
					xNetStaff.type = 0;		//0판매 1응대
					sprintf(xNetStaff.strNickName, "%s","2층 판매원");
					xNetStaff.sex = 0;
					xNetStaff.layer[0] = STAFF0_HAIRCODE;	//헤어
					xNetStaff.layer[1] = STAFF0_FACECODE;		//표정
					xNetStaff.layer[2] = STAFF0_FASHIONCODE0;//상의
					xNetStaff.layer[3] = STAFF0_FASHIONCODE1;//하의
					xNetStaff.layer[4] = STAFF0_FASHIONCODE2;//원피스
					xNetStaff.layer[5] = STAFF0_FASHIONCODE3;//구두
					xNetStaff.inFitting = 0;

					
					sprintf(xPaymentAssistant[xNetStaff.floor].strName, "%s",xNetStaff.strNickName);
					
					for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
						xPaymentAssistant[xNetStaff.floor].xF.code[ff] = DONT;
					
					for(int f=2;f<6;f++)
					{
						if(xNetStaff.layer[f] != DONT)
						{
							setMapData(xNetStaff.layer[f]);//xMap.rever,xMap.type,xMap.listNum 구하기
							xPaymentAssistant[xNetStaff.floor].xF.code[xFashionData[xMap.type][xMap.listNum].layer] = xMap.type*1000+xMap.listNum;
						}
					}
					xPaymentAssistant[xNetStaff.floor].xFace.hairNum = xNetStaff.layer[0];
					xPaymentAssistant[xNetStaff.floor].xFace.faceNum = xNetStaff.layer[1];
					netSend(CMD_SETSTAFF, DONT);
					///////////////////////////////////////////////////////////////////////////////////
				}					
				break;
			case 12:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					////////////////////////////////////////////////////////////////////////////////
					xNetStaff.floor = 2;
					xNetStaff.type = 0;		//0판매 1응대
					sprintf(xNetStaff.strNickName, "%s","3층 판매원");
					xNetStaff.sex = 0;
					xNetStaff.layer[0] = STAFF0_HAIRCODE;	//헤어
					xNetStaff.layer[1] = STAFF0_FACECODE;		//표정
					xNetStaff.layer[2] = STAFF0_FASHIONCODE0;//상의
					xNetStaff.layer[3] = STAFF0_FASHIONCODE1;//하의
					xNetStaff.layer[4] = STAFF0_FASHIONCODE2;//원피스
					xNetStaff.layer[5] = STAFF0_FASHIONCODE3;//구두
					xNetStaff.inFitting = 0;

					
					sprintf(xPaymentAssistant[xNetStaff.floor].strName, "%s",xNetStaff.strNickName);
					
					for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
						xPaymentAssistant[xNetStaff.floor].xF.code[ff] = DONT;
					
					for(int f=2;f<6;f++)
					{
						if(xNetStaff.layer[f] != DONT)
						{
							setMapData(xNetStaff.layer[f]);//xMap.rever,xMap.type,xMap.listNum 구하기
							xPaymentAssistant[xNetStaff.floor].xF.code[xFashionData[xMap.type][xMap.listNum].layer] = xMap.type*1000+xMap.listNum;
						}
					}
					xPaymentAssistant[xNetStaff.floor].xFace.hairNum = xNetStaff.layer[0];
					xPaymentAssistant[xNetStaff.floor].xFace.faceNum = xNetStaff.layer[1];
					netSend(CMD_SETSTAFF, DONT);
					///////////////////////////////////////////////////////////////////////////////////
				}					
				break;
			case 13:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					////////////////////////////////////////////////////////////////////////////////
					xNetStaff.floor = 0;
					xNetStaff.type = 1;		//0판매 1응대
					sprintf(xNetStaff.strNickName, "%s","1층 응대");
					xNetStaff.sex = 1;
					xNetStaff.layer[0] = STAFF1_HAIRCODE;	//헤어
					xNetStaff.layer[1] = STAFF1_FACECODE;		//표정
					xNetStaff.layer[2] = STAFF1_FASHIONCODE0;//상의
					xNetStaff.layer[3] = STAFF1_FASHIONCODE1;//하의
					xNetStaff.layer[4] = STAFF1_FASHIONCODE2;//원피스
					xNetStaff.layer[5] = STAFF1_FASHIONCODE3;//구두
					xNetStaff.inFitting = 0;

					
					sprintf(xShopAssistant[xNetStaff.floor][0].strName, "%s",xNetStaff.strNickName);
					
					for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
						xShopAssistant[xNetStaff.floor][0].xF.code[ff] = DONT;
					
					for(int f=2;f<6;f++)
					{
						if(xNetStaff.layer[f] != DONT)
						{
							setMapData(xNetStaff.layer[f]);//xMap.rever,xMap.type,xMap.listNum 구하기
							xShopAssistant[xNetStaff.floor][0].xF.code[xFashionData[xMap.type][xMap.listNum].layer] = xMap.type*1000+xMap.listNum;
						}
					}
					xShopAssistant[xNetStaff.floor][0].xFace.hairNum = xNetStaff.layer[0];
					xShopAssistant[xNetStaff.floor][0].xFace.faceNum = xNetStaff.layer[1];
					netSend(CMD_SETSTAFF, DONT);
					///////////////////////////////////////////////////////////////////////////////////
				}					
				break;
			case 14:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					////////////////////////////////////////////////////////////////////////////////
					xNetStaff.floor = 1;
					xNetStaff.type = 1;		//0판매 1응대
					sprintf(xNetStaff.strNickName, "%s","2층 응대");
					xNetStaff.sex = 1;
					xNetStaff.layer[0] = STAFF1_HAIRCODE;	//헤어
					xNetStaff.layer[1] = STAFF1_FACECODE;		//표정
					xNetStaff.layer[2] = STAFF1_FASHIONCODE0;//상의
					xNetStaff.layer[3] = STAFF1_FASHIONCODE1;//하의
					xNetStaff.layer[4] = STAFF1_FASHIONCODE2;//원피스
					xNetStaff.layer[5] = STAFF1_FASHIONCODE3;//구두
					xNetStaff.inFitting = 0;

					
					sprintf(xShopAssistant[xNetStaff.floor][0].strName, "%s",xNetStaff.strNickName);
					
					for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
						xShopAssistant[xNetStaff.floor][0].xF.code[ff] = DONT;
					
					for(int f=2;f<6;f++)
					{
						if(xNetStaff.layer[f] != DONT)
						{
							setMapData(xNetStaff.layer[f]);//xMap.rever,xMap.type,xMap.listNum 구하기
							xShopAssistant[xNetStaff.floor][0].xF.code[xFashionData[xMap.type][xMap.listNum].layer] = xMap.type*1000+xMap.listNum;
						}
					}
					xShopAssistant[xNetStaff.floor][0].xFace.hairNum = xNetStaff.layer[0];
					xShopAssistant[xNetStaff.floor][0].xFace.faceNum = xNetStaff.layer[1];
					netSend(CMD_SETSTAFF, DONT);
					///////////////////////////////////////////////////////////////////////////////////
				}					
				break;
			case 15:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					////////////////////////////////////////////////////////////////////////////////
					xNetStaff.floor = 2;
					xNetStaff.type = 1;		//0판매 1응대
					sprintf(xNetStaff.strNickName, "%s","3층 응대");
					xNetStaff.sex = 1;
					xNetStaff.layer[0] = STAFF1_HAIRCODE;	//헤어
					xNetStaff.layer[1] = STAFF1_FACECODE;		//표정
					xNetStaff.layer[2] = STAFF1_FASHIONCODE0;//상의
					xNetStaff.layer[3] = STAFF1_FASHIONCODE1;//하의
					xNetStaff.layer[4] = STAFF1_FASHIONCODE2;//원피스
					xNetStaff.layer[5] = STAFF1_FASHIONCODE3;//구두
					xNetStaff.inFitting = 0;

					
					sprintf(xShopAssistant[xNetStaff.floor][0].strName, "%s",xNetStaff.strNickName);					
					
					for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
						xShopAssistant[xNetStaff.floor][0].xF.code[ff] = DONT;
					for(int f=2;f<6;f++)
					{
						if(xNetStaff.layer[f] != DONT)
						{
							setMapData(xNetStaff.layer[f]);//xMap.rever,xMap.type,xMap.listNum 구하기
							xShopAssistant[xNetStaff.floor][0].xF.code[xFashionData[xMap.type][xMap.listNum].layer] = xMap.type*1000+xMap.listNum;
						}
					}
					xShopAssistant[xNetStaff.floor][0].xFace.hairNum = xNetStaff.layer[0];
					xShopAssistant[xNetStaff.floor][0].xFace.faceNum = xNetStaff.layer[1];
					netSend(CMD_SETSTAFF, DONT);
					///////////////////////////////////////////////////////////////////////////////////
				}					
				break;
			case 16:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;

					xNetTile.type = 0;
					xNetTile.tileCode = FLOORTILEINITCODE;
					xNetTile.wallCode = WALLTILEINITCODE;
					xNetTile.floor = 0;
					netSend(CMD_SETTILE, DONT);
				}
				break;
			case 17:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetTile.type = 1;
					xNetTile.tileCode = FLOORTILEINITCODE;
					xNetTile.wallCode = WALLTILEINITCODE;
					xNetTile.floor = 0;
					netSend(CMD_SETTILE, DONT);
				}
				break;
			case 18:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetTile.type = 0;
					xNetTile.tileCode = FLOORTILEINITCODE;
					xNetTile.wallCode = WALLTILEINITCODE;
					xNetTile.floor = 1;
					netSend(CMD_SETTILE, DONT);
				}
				break;
			case 19:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetTile.type = 1;
					xNetTile.tileCode = FLOORTILEINITCODE;
					xNetTile.wallCode = WALLTILEINITCODE;
					xNetTile.floor = 1;
					netSend(CMD_SETTILE, DONT);
				}
				break;
			case 20:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetTile.type = 0;
					xNetTile.tileCode = FLOORTILEINITCODE;
					xNetTile.wallCode = WALLTILEINITCODE;
					xNetTile.floor = 2;
					netSend(CMD_SETTILE, DONT);
				}
				break;
			case 21:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					
					xNetTile.type = 1;
					xNetTile.tileCode = FLOORTILEINITCODE;
					xNetTile.wallCode = WALLTILEINITCODE;
					xNetTile.floor = 2;
					netSend(CMD_SETTILE, DONT);
				}
				break;
			case 22:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;

					xModel.totalInventoryModelMax = 100;
					netSend(CMD_SETMODELTOTALSLOT,	DONT);
				}
				break;
			case 23:
				if(xMainMenu.isInitNet == TRUE)
				{
					xMainMenu.isInitNet = FALSE;
					xMainMenu.initCnt++;
					/////////////////////////////////////////////////////////////////////////////
					//초기화 완료
					xNetInitGame.action = 1;
					netSend(CMD_INITGAME, DONT);
					////////////////////////////////////////////////////////////////////////////
				}
				break;
			}
		}
					
		++xMainMenu.anyCnt;
		break;
	}
				
	
	
	
	switch(playState)
	{
	case PLAY_MSG:
		drawPopup();
		break;
	}
	
	setFontSize(14);
	gDrawStringBold(lcdW-10,18, VER, VR, ALPHA_MAX, ALPHA_MAX, ALPHA_MAX, 82, 49, 38);
	setFontSize(11);
}

void drawIdMake()
{
	int px = cx;
	int py = cy;
	int line;
    

    
	switch(xIdMake.state)
	{
	case IDMAKE_STATE_CLAUSE:
		drawPacker(IMG_MainMenu1, px, py, 0, 0, imgW(IMG_MainMenu1), imgH(IMG_MainMenu1), VH);
		subTemp[XPOS] = px-156;
		subTemp[YPOS] = py-40;
		
            
		if(xIdMake.isClause[0] == TRUE)
			drawPacker(IMG_MainMenu5, subTemp[XPOS]-3, subTemp[YPOS]+40, 0, 0, imgW(IMG_MainMenu5), imgH(IMG_MainMenu5), VH);
		
		subTemp[XPOS] = px-160;
		subTemp[YPOS] = py+210;
		
		if(xIdMake.isClause[0] == TRUE)
		{
			drawPacker(imgQuestV, subTemp[XPOS]-115, subTemp[YPOS]-20, 0, 0, imgW(imgQuestV), imgH(imgQuestV), VH);
		}
				
		xIdMake.xTouchClauseBtn[0].wPos = imgW(IMG_MainMenu7)+60;
		xIdMake.xTouchClauseBtn[0].hPos = imgH(IMG_MainMenu7)/2;
		xIdMake.xTouchClauseBtn[0].xPos = subTemp[XPOS] - xIdMake.xTouchClauseBtn[0].wPos/2;
		xIdMake.xTouchClauseBtn[0].yPos = subTemp[YPOS] - xIdMake.xTouchClauseBtn[0].hPos/2;
        
            
        xIdMake.xTouchClauseLink[0].wPos = 120;
        xIdMake.xTouchClauseLink[0].hPos = 40;
        xIdMake.xTouchClauseLink[0].xPos = subTemp[XPOS]+90 - xIdMake.xTouchClauseLink[0].wPos/2;
        xIdMake.xTouchClauseLink[0].yPos = subTemp[YPOS]-80 - xIdMake.xTouchClauseLink[0].hPos/2;
        
    
        /*
        gSetColor(255, 0, 0);
        setAlpha(100);
        fillRect(xIdMake.xTouchClauseLink[0].xPos, xIdMake.xTouchClauseLink[0].yPos, xIdMake.xTouchClauseLink[0].wPos, xIdMake.xTouchClauseLink[0].hPos);
        setAlpha(ALPHA_MAX);
        */
        
		
		//약관2
		subTemp[XPOS] = px+160;
		subTemp[YPOS] = py-40;

		
            
		if(xIdMake.isClause[1] == TRUE)
			drawPacker(IMG_MainMenu5, subTemp[XPOS]-3, subTemp[YPOS]+40, 0, 0, imgW(IMG_MainMenu5), imgH(IMG_MainMenu5), VH);
		
		subTemp[XPOS] = px+160;
		subTemp[YPOS] = py+210;
		
		if(xIdMake.isClause[1] == TRUE)
			drawPacker(imgQuestV, subTemp[XPOS]-115, subTemp[YPOS]-20, 0, 0, imgW(imgQuestV), imgH(imgQuestV), VH);
				
		xIdMake.xTouchClauseBtn[1].wPos = imgW(IMG_MainMenu7)+60;
		xIdMake.xTouchClauseBtn[1].hPos = imgH(IMG_MainMenu7)/2;
		xIdMake.xTouchClauseBtn[1].xPos = subTemp[XPOS] - xIdMake.xTouchClauseBtn[1].wPos/2;
		xIdMake.xTouchClauseBtn[1].yPos = subTemp[YPOS] - xIdMake.xTouchClauseBtn[1].hPos/2;
            
            
        xIdMake.xTouchClauseLink[1].wPos = 120;
        xIdMake.xTouchClauseLink[1].hPos = 40;
        xIdMake.xTouchClauseLink[1].xPos = subTemp[XPOS]-90 - xIdMake.xTouchClauseLink[0].wPos/2;
        xIdMake.xTouchClauseLink[1].yPos = subTemp[YPOS]-80 - xIdMake.xTouchClauseLink[0].hPos/2;
            
        /*
		gSetColor(255, 0, 0);
		setAlpha(100);
		fillRect(xIdMake.xTouchClauseBtn[1].xPos, xIdMake.xTouchClauseBtn[1].yPos, xIdMake.xTouchClauseBtn[1].wPos, xIdMake.xTouchClauseBtn[1].hPos);
		setAlpha(ALPHA_MAX);
        */
		
		
		break;
	case IDMAKE_STATE_LOGINKAKAO:
	case IDMAKE_STATE_LOGINKAKAOING:
								
		subTemp[XPOS] = px;
		subTemp[YPOS] = py+200;
		drawPacker(IMG_MainMenu11, subTemp[XPOS], subTemp[YPOS], 0, 0, imgW(IMG_MainMenu11), imgH(IMG_MainMenu11), VH);
			
		xIdMake.xTouchLoginBtn.wPos = imgW(IMG_MainMenu11);
		xIdMake.xTouchLoginBtn.hPos = imgH(IMG_MainMenu11);
		xIdMake.xTouchLoginBtn.xPos = subTemp[XPOS] - xIdMake.xTouchLoginBtn.wPos/2;
		xIdMake.xTouchLoginBtn.yPos = subTemp[YPOS] - xIdMake.xTouchLoginBtn.hPos/2;
		/*
		setAlpha(100);
		gSetColor(255, 0, 0);
		fillRect(xIdMake.xTouchLoginBtn.xPos, xIdMake.xTouchLoginBtn.yPos, xIdMake.xTouchLoginBtn.wPos, xIdMake.xTouchLoginBtn.hPos);
		setAlpha(ALPHA_MAX);
		*/
		if(xWorldMap.isAppReview == TRUE)
		{
			subTemp[XPOS] = px;
			subTemp[YPOS] = py+270;
				
			drawPacker(IMG_MainMenu6, subTemp[XPOS], subTemp[YPOS], 0, 0, imgW(IMG_MainMenu6), imgH(IMG_MainMenu6), VH);
						
			xIdMake.xTouchLoginIdMakeBtn.wPos = imgW(IMG_MainMenu6);
			xIdMake.xTouchLoginIdMakeBtn.hPos = imgH(IMG_MainMenu6);
			xIdMake.xTouchLoginIdMakeBtn.xPos = subTemp[XPOS] - xIdMake.xTouchLoginIdMakeBtn.wPos/2;
			xIdMake.xTouchLoginIdMakeBtn.yPos = subTemp[YPOS] - xIdMake.xTouchLoginIdMakeBtn.hPos/2;
			/*
			setAlpha(100);
			gSetColor(255, 0, 0);
			fillRect(xIdMake.xTouchLoginIdMakeBtn.xPos, xIdMake.xTouchLoginIdMakeBtn.yPos, xIdMake.xTouchLoginIdMakeBtn.wPos, xIdMake.xTouchLoginIdMakeBtn.hPos);
			setAlpha(ALPHA_MAX);
			 */
		}
		break;
	case IDMAKE_STATE_IDMAKE:
	case IDMAKE_STATE_STAMP:
		drawPacker(IMG_IdMakeBg, px, py, 0, 0, imgW(IMG_IdMakeBg), imgH(IMG_IdMakeBg), VH);
		subTemp[XPOS] = px-160;
		subTemp[YPOS] = py-42;
		gSetColor(109, 108, 121);
		switch(xIdMake.nickNameErr)
		{
		case IDMAKEERR_TYPE_DONT:
			gSetColor(109, 108, 121);
			gDrawString(subTemp[XPOS], subTemp[YPOS], xIdMake.strNickName, VH);
			break;
		case IDMAKEERR_TYPE_NICKNAMEERR:
			drawPacker(IMG_MainMenu3, subTemp[XPOS]+131, subTemp[YPOS], 0, 0, imgW(IMG_MainMenu3), imgH(IMG_MainMenu3), VH);
			gSetColor(255, 0, 0);
			gDrawString(subTemp[XPOS], subTemp[YPOS],"한글(1~6),영문(2~8)제한", VH);
			break;
		case IDMAKEERR_TYPE_NICKNAMEERR2:
			drawPacker(IMG_MainMenu3, subTemp[XPOS]+131, subTemp[YPOS], 0, 0, imgW(IMG_MainMenu3), imgH(IMG_MainMenu3), VH);
			gSetColor(255, 0, 0);
			gDrawString(subTemp[XPOS], subTemp[YPOS],"대표자명 중복", VH);
			break;
		case IDMAKEERR_TYPE_NICKNAMEERR3:
			drawPacker(IMG_MainMenu3, subTemp[XPOS]+131, subTemp[YPOS], 0, 0, imgW(IMG_MainMenu3), imgH(IMG_MainMenu3), VH);
			gSetColor(255, 0, 0);
			gDrawString(subTemp[XPOS], subTemp[YPOS],"특수문자 사용 금지", VH);
			break;
		}
			
			
		xIdMake.xTouchNickName.wPos = imgW(IMG_MainMenu2);
		xIdMake.xTouchNickName.hPos = imgH(IMG_MainMenu2);
		xIdMake.xTouchNickName.xPos = subTemp[XPOS] - xIdMake.xTouchNickName.wPos/2;
		xIdMake.xTouchNickName.yPos = subTemp[YPOS] - xIdMake.xTouchNickName.hPos/2;
		
		/*
		setAlpha(100);
		gSetColor(255, 0, 0);
		fillRect(xIdMake.xTouchNickName.xPos, xIdMake.xTouchNickName.yPos, xIdMake.xTouchNickName.wPos, xIdMake.xTouchNickName.hPos);
		setAlpha(ALPHA_MAX);
		*/
			
			
		subTemp[XPOS] = px-170-83;
		subTemp[YPOS] = py+97;
			
		drawPacker(IMG_MainMenu8, subTemp[XPOS], subTemp[YPOS], 0, imgH(IMG_MainMenu8)/2*(xIdMake.sex==0?0:1), imgW(IMG_MainMenu8)/2, imgH(IMG_MainMenu8)/2, VH);
		xIdMake.xTouchSex[0].wPos = imgW(IMG_MainMenu8)/2;
		xIdMake.xTouchSex[0].hPos = imgH(IMG_MainMenu8)/2;
		xIdMake.xTouchSex[0].xPos = subTemp[XPOS]-xIdMake.xTouchSex[0].wPos/2;
		xIdMake.xTouchSex[0].yPos = subTemp[YPOS]-xIdMake.xTouchSex[0].hPos/2;
						
		subTemp[XPOS] = px-170+83;
		subTemp[YPOS] = py+97;
		drawPacker(IMG_MainMenu8, subTemp[XPOS], subTemp[YPOS], imgW(IMG_MainMenu8)/2, imgH(IMG_MainMenu8)/2*(xIdMake.sex==1?0:1), imgW(IMG_MainMenu8)/2, imgH(IMG_MainMenu8)/2, VH);
		xIdMake.xTouchSex[1].wPos = imgW(IMG_MainMenu8)/2;
		xIdMake.xTouchSex[1].hPos = imgW(IMG_MainMenu8)/2;
		xIdMake.xTouchSex[1].xPos = subTemp[XPOS]-xIdMake.xTouchSex[0].wPos/2;
		xIdMake.xTouchSex[1].yPos = subTemp[YPOS]-xIdMake.xTouchSex[0].hPos/2;
					
		//나이
		subTemp[XPOS] = px+112;
		subTemp[YPOS] = py+47;		
		
		//거리별 스크롤 방식에서 셀럭트넘은 첫 시작 값으로 취급한다
		xIdMake.xTouchAge.wPos = 140;
		xIdMake.xTouchAge.hPos = 221;
		xIdMake.xTouchAge.xPos = subTemp[XPOS]-xIdMake.xTouchAge.wPos/2;
		xIdMake.xTouchAge.yPos = subTemp[YPOS]-xIdMake.xTouchAge.hPos/2;
		/*
		gSetColor(255, 0, 0);
		setAlpha(100);
		fillRect(xIdMake.xTouchAge.xPos, xIdMake.xTouchAge.yPos, xIdMake.xTouchAge.wPos, xIdMake.xTouchAge.hPos);
		setAlpha(ALPHA_MAX);
		*/
		
		xIdMake.xDragScrollAge.totalNum = AGEMAX;
		xIdMake.xDragScrollAge.posGab = 48;
		
		dragScrollPrc(&xIdMake.xDragScrollAge,0,FALSE);
			
		
		
		gSetClip(true,xIdMake.xTouchAge.xPos, xIdMake.xTouchAge.yPos, xIdMake.xTouchAge.wPos, xIdMake.xTouchAge.hPos);
		for(int i=-2;i<=2;i++)
		{
			if(xIdMake.xDragScrollAge.selectNum+i >= 0 && xIdMake.xDragScrollAge.selectNum+i < xIdMake.xDragScrollAge.totalNum)
			{
				int pos = xIdMake.xDragScrollAge.pos+(xIdMake.xDragScrollAge.posGab*i);
				
				getSprintfAge(strTempS,xIdMake.xDragScrollAge.selectNum+i);
				gSetColor(109, 108, 121);
				
				gDrawString(subTemp[XPOS], subTemp[YPOS]+pos, strTempS, VH);
				drawPacker(IMG_MainMenu4, subTemp[XPOS], subTemp[YPOS]+20+pos, 0, 0, imgW(IMG_MainMenu4), imgH(IMG_MainMenu4), VH);
			}
		}
		gSetClip(false,0, 0, lcdW, lcdH);
		drawPacker(IMG_MainMenu9, subTemp[XPOS], subTemp[YPOS], 0, 0, imgW(IMG_MainMenu9), imgH(IMG_MainMenu9), VH);
		//지역
		subTemp[XPOS] = px+263;
		subTemp[YPOS] = py+47;

		
		//거리별 스크롤 방식에서 셀럭트넘은 첫 시작 값으로 취급한다
		xIdMake.xTouchArea.wPos = 146;
		xIdMake.xTouchArea.hPos = 221;
		xIdMake.xTouchArea.xPos = subTemp[XPOS]-xIdMake.xTouchArea.wPos/2;
		xIdMake.xTouchArea.yPos = subTemp[YPOS]-xIdMake.xTouchArea.hPos/2;
		/*
		 gSetColor(255, 0, 0);
		 setAlpha(100);
		 fillRect(xIdMake.xTouchArea.xPos, xIdMake.xTouchArea.yPos, xIdMake.xTouchArea.wPos, xIdMake.xTouchArea.hPos);
		 setAlpha(ALPHA_MAX);
		 */

		xIdMake.xDragScrollArea.totalNum = AREAMAX;
		xIdMake.xDragScrollArea.posGab = 48;

		dragScrollPrc(&xIdMake.xDragScrollArea,0,FALSE);
		
		gSetClip(true,xIdMake.xTouchArea.xPos, xIdMake.xTouchArea.yPos, xIdMake.xTouchArea.wPos, xIdMake.xTouchArea.hPos);
		for(int i=-2;i<=2;i++)
		{
			if(xIdMake.xDragScrollArea.selectNum+i >= 0 && xIdMake.xDragScrollArea.selectNum+i < xIdMake.xDragScrollArea.totalNum)
			{
				int pos = xIdMake.xDragScrollArea.pos+(xIdMake.xDragScrollArea.posGab*i);
								
				getSprintfArea(strTempS,xIdMake.xDragScrollArea.selectNum+i);
				gSetColor(109, 108, 121);
				
				gDrawString(subTemp[XPOS], subTemp[YPOS]+pos, strTempS, VH);
				drawPacker(IMG_MainMenu4, subTemp[XPOS], subTemp[YPOS]+20+pos, 0, 0, imgW(IMG_MainMenu4), imgH(IMG_MainMenu4), VH);
			}
		}			
		gSetClip(false,0, 0, lcdW, lcdH);
		drawPacker(IMG_MainMenu10, subTemp[XPOS], subTemp[YPOS], 0, 0, imgW(IMG_MainMenu10), imgH(IMG_MainMenu10), VH);
		
		subTemp[XPOS] = px;
		subTemp[YPOS] = py+210;
		drawPacker(imgPopupBtn0, subTemp[XPOS], subTemp[YPOS], 0, imgH(imgPopupBtn0)/2, imgW(imgPopupBtn0), imgH(imgPopupBtn0)/2, VH);
		gDrawStringBold(subTemp[XPOS], subTemp[YPOS], "등록", VH, ALPHA_MAX, ALPHA_MAX, ALPHA_MAX, 186, 70, 10);
						
		xTouchOk.wPos = imgW(imgPopupBtn0);
		xTouchOk.hPos = imgH(imgPopupBtn0)/2;
		xTouchOk.xPos = subTemp[XPOS] - xTouchOk.wPos/2;
		xTouchOk.yPos = subTemp[YPOS] - xTouchOk.hPos/2;
		
		if(xIdMake.state == IDMAKE_STATE_STAMP)
		{
			if(drawStamp(cx, cy, xIdMake.anyCnt++,0) == TRUE)
			{
				playSnd(SND_MENU_OK);
				xMainMenu.state = MAINMENU_STATE_LOGIN;
				xMainMenu.anyCnt = 0;
				
                netSend(CMD_LOGIN,DONT);
            }
		}
		break;
	}
}

M_Boolean checkEmail(const char*strText)
{
	M_Boolean isCheck[2];
	isCheck[0] = FALSE;
	isCheck[1] = FALSE;
	
	/*
	for(int i=0;i<strlen(strText);i++)
	{
		if(strText[i] == '@')
			isCheck[0] = TRUE;
		else if(strText[i] == '.')
			isCheck[1] = TRUE;
	}
	
	if(isCheck[0] == TRUE && isCheck[1] == TRUE)
		return TRUE;
	
	return FALSE;
	 */
	return TRUE;
}

M_Boolean checkAge(const char*strText)
{
	for(int i=0;i<strlen(strText);i++)
	{
		if(strText[i] < '0' || strText[i] > '9')
			return FALSE;
	}
		
	return TRUE;
}

void getSprintfArea(char*strText,int code)
{	
	switch(code)
	{
	case 0:sprintf(strText,"서울");	break;
	case 1:sprintf(strText,"부산");	break;
	case 2:sprintf(strText,"인천");	break;
	case 3:sprintf(strText,"대전");	break;
	case 4:sprintf(strText,"대구");	break;
	case 5:sprintf(strText,"광주");	break;
	case 6:sprintf(strText,"울산");	break;
	case 7:sprintf(strText,"경기");	break;
	case 8:sprintf(strText,"강원");	break;
	case 9:sprintf(strText,"충남");	break;
	case 10:sprintf(strText,"충북");	break;
	case 11:sprintf(strText,"경남");	break;
	case 12:sprintf(strText,"경북");	break;
	case 13:sprintf(strText,"전남");	break;
	case 14:sprintf(strText,"전북");	break;
	case 15:sprintf(strText,"제주");	break;
	}
}

void getSprintfAge(char*strText,int code)
{
	sprintf(strText,"%d년생",AGESTART-code);
}

int getScrollW(XDRAGSCROLL *xDragScroll,int fullWidth,int imgWidth)
{
	int pos = xDragScroll->pos;
	
	if(pos>0)
		pos = 0;
	else if(pos < xDragScroll->endPos)
		pos = xDragScroll->endPos;
	
	
	if(xDragScroll->endPos == 0)
		return 0;
	
	return pos*(fullWidth-imgWidth)/xDragScroll->endPos;
}


void drawServerNotice()
{	
	int px = cx;
	int py = cy;
	drawPacker(imgPopupBg, px, py, 0, 0, imgW(imgPopupBg), imgH(imgPopupBg), VH);
	
	gSetColor(44, 26, 26);
	setPopupStringLine(xNetData.strNotice,lcdW);
	
		
	int fontGab = 50;
	switch(xPopup.totalLine)
	{
		case 1:	fontGab = 50;break;
		case 2:	fontGab = 45;break;
		case 3:	fontGab = 40;break;
		case 4:	fontGab = 35;break;
		case 5:	fontGab = 30;break;
		default:fontGab = 25;break;
	}
	for(int li=0;li<xPopup.totalLine;li++)
		gDrawString(px-110,py+posTemp[HPOS]+(fontGab*li)-((xPopup.totalLine-1)*(fontGab/2)), xPopup.strTextLine[li], VH);
		
				
	if(xPopup.speakingNpcNum != 0)
	{
		xPopup.speakingNpcNum = 0;
		
		freeImg(&imgPopupNpc[0]);
		freeImg(&imgPopupNpc[1]);
		freeImg(&imgPopupNpc[2]);
		freeImg(&imgPopupNpc[3]);
		
		sprintf(strTempS, "popupnpc%d.png",xPopup.speakingNpcNum);
		loadImg(strTempS, &imgPopupNpc[0]);
		sprintf(strTempS, "popupnpc%da.png",xPopup.speakingNpcNum);
		loadImg(strTempS, &imgPopupNpc[1]);
		sprintf(strTempS, "popupnpc%db.png",xPopup.speakingNpcNum);
		loadImg(strTempS, &imgPopupNpc[2]);
		sprintf(strTempS, "popupnpc%dc.png",xPopup.speakingNpcNum);
		loadImg(strTempS, &imgPopupNpc[3]);
	}

	if(xPopup.speakingNpcNum != DONT)
	{
		drawPacker(imgPopup2, px-16,py-150, 0, 0, imgW(imgPopup2), imgH(imgPopup2), VH);
		gSetColor(138, 117, 111);
		setFontSize(14);
		gDrawString(px-16,py-156,"서버공지",VH);
		setFontSize(11);
		drawImage(&imgPopupNpc[0], px+180,py+200, 0, 0, imgPopupNpc[0].w, imgPopupNpc[0].h, BH);
		drawImage(&imgPopupNpc[1], px+180,py+200-imgPopupNpc[0].h, 0, 0, imgPopupNpc[1].w, imgPopupNpc[1].h, BH);

	}
	drawBtn(px-110,py+156,xPopup.btnType);
}

void dataDownLoad(const char*strUrl,const char*strFileName,int type)
{
    CCLOG("strUrl>>%s\n",strUrl);
    xDownLoader.state = DOWNLOADER_STATE_ING;
    switch(type)
    {
    case DATADOWNLOAD_TYPE_SDCARD:
        urlFileDownLoad((char*)strFileName, (char*)strUrl);
        break;
    case DATADOWNLOAD_TYPE_BUFF:
        urlFileDownLoad("buffer.dat", (char*)strUrl);
        break;
    }
}
void gameExit()
{
	exit(0);
}
void drawLodingText()
{
	drawPacker(imgLoadingGage1, cx, lcdH-75, 0, imgH(imgLoadingGage1)/4*(gameCnt%4), imgW(imgLoadingGage1), imgH(imgLoadingGage1)/4, VH);
	
	if(isResume == FALSE)
		drawPacker(imgLoadingGage2, cx, lcdH-35, 0, 0, imgW(imgLoadingGage2), imgH(imgLoadingGage2), VH);
	
	if(xMainMenu.loadTextCnt < xCalendar.nowTime)
	{
		xMainMenu.loadTextCnt = xCalendar.nowTime+3;
		xMainMenu.textType = ranDom(0,7);
	}
	
	switch(xMainMenu.textType)
	{
	case 0:sprintf(strTempS, "패션 정보를 받아오는 중...");break;
	case 1:sprintf(strTempS, "이번 주 하이라이트 유행 정보 수신 중...");break;
	case 2:sprintf(strTempS, "S급 모델 근황 추적 중...");break;
	case 3:sprintf(strTempS, "캔디 머신 정비 중...");break;
	case 4:sprintf(strTempS, "쇼윈도 설치중...");break;
	case 5:sprintf(strTempS, "쇼핑 카트 가져오는중...");break;
	case 6:sprintf(strTempS, "직원 복장 점검 중...");break;
	case 7:sprintf(strTempS, "연예인 패션 리스트 불러오는 중...");break;
	}
    
	if(isResume == FALSE)
	{
		gSetColor(255,255,255);
		setFontSize(14);
		gDrawString(cx, lcdH-35, strTempS, VH);
		setFontSize(11);
	}
}

void googleLogin()
{
    xIdMake.state = IDMAKE_STATE_LOGINKAKAOING;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sprintf(xKakaoData.xUserInfo.strUserId, "112568368855147217704"); //나
    
    /*
    test5   116722146348515101027     
    카벨류사   104961141565134770510
    호호호   108216939925142011096
    카링   106119835205761795078
        레오나   102500557792235657915
    jjj   104511034655147700437
    대호   7608
    레베카   102500557792235657915
    덜덜   104800908542216173574
    소름경석   100242588841125604612
    점이용이   109347216825434270298
    ㅋㅋ   111564125981557772305
    튜튜토링   7777
    럴   117358579338749608513
    지역   0000
    ddd   0001
    드레이븐   104511034655147700437
    */
    
    
    
    netSend(CMD_LOGIN,DONT);
#else
    googleSignIn();
#endif
    
}


