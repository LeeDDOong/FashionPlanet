#include "Global.h"


XKAKAODATA xKakaoData;
//로그인
void kakaoDevLogin()
{
	xKakaoData.state = KAKAOAIP_STATE_LOGIN;
	xKakaoData.resultType = KAKAOAIP_RESULT_WAIT;
}
//로그아웃
void kakaoDevLogout()
{
	xKakaoData.state = KAKAOAIP_STATE_LOGOUT;
	xKakaoData.resultType = KAKAOAIP_RESULT_WAIT;
	
}

//계정삭제
void kakaoDevUnRegister()
{
	xKakaoData.state = KAKAOAIP_STATE_UNREG;
	xKakaoData.resultType = KAKAOAIP_RESULT_WAIT;

}

//유저정보
void kakaoDevUserInfo()
{
	xKakaoData.state = KAKAOAIP_STATE_USERINFO;
	xKakaoData.resultType = KAKAOAIP_RESULT_WAIT;

}
//친구리스트
void kakaoDevGetFriendList()
{
	xKakaoData.state = KAKAOAIP_STATE_FRIENDINFO;
	xKakaoData.resultType = KAKAOAIP_RESULT_WAIT;

}
//메시지보내기
void kakaoDevSendMessageApp(const char*strUserId, const char*strMessage,const char*strTemplateId)
{
	xKakaoData.state = KAKAOAIP_STATE_SENDMESSAGE;
}

//메시지보내기2.0초대메시지
void kakaoDevSendMessage20(const char*strUserId, const char*strMessage)
{
	xKakaoData.state = KAKAOAIP_STATE_SENDMESSAGE;
	
}
//메시지보내기2.0게임메시지
void kakaoDevSendMessage20_APP(const char*strUserId, const char*strMessage,const char*strImageFileName)
{
	xKakaoData.state = KAKAOAIP_STATE_SENDMESSAGEAPP;
}


void kakaoStoryPost()
{
/*	
	xKakaoData.state = KAKAOAIP_STATE_KAKAOSTORY;
	
	NSDictionary *androidMetaInfo = [NSDictionary dictionaryWithObjectsAndKeys:@"android",@"os", @"custum_var=1",@"executeurl", nil];
	NSDictionary *iOSMetaInfo = [NSDictionary dictionaryWithObjectsAndKeys:@"ios",@"os", @"custum_var=2",@"executeurl", nil];

	[[KakaoSDKViewController controller] showStoryViewWithImage:[UIImage imageNamed:@"logo0.png"] postString:@"내 친구들과 나누는 이야기!\nhttp://www.kakao.com/story"
												  metaInfoArray:[NSArray arrayWithObjects:androidMetaInfo,iOSMetaInfo, nil]
											  completionHandler:^(BOOL success, NSError *error) { dispatch_async(dispatch_get_main_queue(), ^{
		if ( success ) {
			UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"포스팅 성공"
																message:@"성공"
															   delegate:nil
													  cancelButtonTitle:@"OK"
													  otherButtonTitles:nil];
			[alertView show];
			[alertView release];
		} else {
			UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"포스팅 실패"
																message:@"실패"
															   delegate:nil
													  cancelButtonTitle:@"OK"
													  otherButtonTitles:nil];
			[alertView show];
			[alertView release];
		}
			  [[KakaoSDKViewController controller] closeStoryView]; });
			  }];
*/
}


//////////////카톡결과관리/////////////
void prcKakaoApi()
{
    
	if(xKakaoData.state != KAKAOAIP_STATE_DONT)
	{
		switch(xKakaoData.resultType)
		{
		case KAKAOAIP_RESULT_SUCCESS:

			switch(xKakaoData.state)
			{
			case KAKAOAIP_STATE_USERINFO:
				kakaoAnRecv(KAKAOAIP_STATE_USERINFO);
				break;
			case KAKAOAIP_STATE_FRIENDINFO:
				kakaoAnRecv(KAKAOAIP_STATE_FRIENDINFO);
				break;
			}
			//printf("xKakaoData.state????????????????%d\n",xKakaoData.state);
				
			xKakaoData.resultType = KAKAOAIP_RESULT_WAIT;
			switch(xKakaoData.state)
			{
			case KAKAOAIP_STATE_SENDMESSAGE:
			case KAKAOAIP_STATE_SENDMESSAGEAPP:
				if(xWorldMap.state == WORLDMAP_STATE_FRIENDLIST)
					setKakaoinviteOk();
				break;
			case KAKAOAIP_STATE_LOGIN:
				xIdMake.state = IDMAKE_STATE_LOGINKAKAOING;
				xSave.isKakaoLogin = TRUE;
				gameSave(SAVE_SLOT_GAME);
				//만들어진 계정이 있나 확인필요
				kakaoDevUserInfo();
				break;
			case KAKAOAIP_STATE_USERINFO:
				kakaoDevGetFriendList();
				break;
			case KAKAOAIP_STATE_FRIENDINFO:
				for(int i=0;i<xKakaoData.totalFriendInfo;i++)
				{
					int userNum = xKakaoData.xFriendInfo[i].userNum;
					int slotNum = getFriendSlot(userNum);
					
					
					if(slotNum == DONT)
					{
						slotNum = addFriendData(userNum);
					}
					
					
					if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
						sprintf(xFriendData[slotNum].strUrl, "%s",xKakaoData.xFriendInfo[i].strProfileUrl);
					
									
					sprintf(xFriendData[slotNum].strNickName, "%s",xKakaoData.xFriendInfo[i].strNickName);					

					xKakaoData.xFriendInfo[i].friendNum = slotNum;
					xKakaoData.xFriendInfo[i].isInvite = checkKakaoInvite(xKakaoData.xFriendInfo[i].strUserId) == DONT?FALSE:TRUE;
					
				}
					
				for(int i=0;i<xKakaoData.totalFriendInfoApp;i++)
				{
					int userNum = xKakaoData.xFriendInfoApp[i].userNum;
					int slotNum = getFriendSlot(userNum);
					
					
					
					if(slotNum == DONT)
					{
						slotNum = addFriendData(userNum);
					}
					
					if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
						sprintf(xFriendData[slotNum].strUrl, "%s",xKakaoData.xFriendInfoApp[i].strProfileUrl);
					
					sprintf(xFriendData[slotNum].strNickName, "%s",xKakaoData.xFriendInfoApp[i].strNickName);
					
					xKakaoData.xFriendInfoApp[i].friendNum = slotNum;
					int kakaoSlot = checkKakaoAppInvite(xKakaoData.xFriendInfoApp[i].strUserId);
					xKakaoData.xFriendInfoApp[i].isInvite = kakaoSlot==DONT?FALSE:TRUE;

					xFriendData[slotNum].isAdd = FALSE;
					if(kakaoSlot != DONT && xSaveKakaoApp.isDel[kakaoSlot] == FALSE)
					xFriendData[slotNum].isAdd = TRUE;
					
					sprintf(xFriendData[slotNum].strKakaoId, "%s",xKakaoData.xFriendInfoApp[i].strUserId);
										
				}


				switch(xMainMenu.state)
				{
					case MAINMENU_STATE_IDMAKE:
						switch(xIdMake.state)
						{
						case IDMAKE_STATE_LOGINKAKAOING:
						case IDMAKE_STATE_LOGINKAKAO:	//해당계정이 있나 확인해야함 바로 로그인 만약에 계정기록이 있다면 idmake = TRUE 없다면 IDMAKE로
							netSend(CMD_LOGIN, DONT);
							break;
						case IDMAKE_STATE_IDMAKE:
							netSend(CMD_IDMAKE,DONT);
							break;
						}
						break;
					case MAINMENU_STATE_LOGIN:
						netSend(CMD_LOGIN, DONT);
						break;
					default:
						break;
				}
				break;
			}
			break;
		case KAKAOAIP_RESULT_FAIL:
			xKakaoData.resultType = KAKAOAIP_RESULT_WAIT;
			xKakaoData.inveiteKeyReturn = FALSE;
			printf("xKakaoData.state>>%d\n",xKakaoData.state);
				
			//아무처리 안함
			switch(xKakaoData.errCode)
			{
			case 8:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "Guest Login상태에서는\n지원하지 않는 기능입니다.");
				break;
			case 10:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "계정 연결에는 성공하였으나\n해당 사용자의 카카오계정은\n아직 이메일 인증을 받지 않았습니다.");
				break;
			case -9798:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "인증서버 또는 API 서버 점검중입니다.");
				break;
			case -1000:
				setPopup(POPUP_KAKAOLOGINERR22, playState, playState, 0, DONT);
				subTemp[10] = xSave.resVer;
				initSave();
				xSave.resVer = subTemp[10];
				gameSave(SAVE_SLOT_GAME);
				break;
			case -500:
				break;
			case -451:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "해당 앱의 이용가능\n연령에 미달하는 사용자입니다");
				break;
			case -400:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "refresh_token이\n만료 혹은 유효하지 않은 상태");
				break;
			case -200:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "올바르지 않은\n푸시 토큰입니다");
				break;
			case -100:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "권한이 없습니다.\n권한이 부여되지 않은 정보를 요청한 경우");
				break;
			case -32:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "1일 초대 횟수 30회를 초과하였습니다.");
				break;
			case -31:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "초대메시지를 보낼 수 없는 사용자입니다.\n초대메시지는 같은 수신자에게는\n30일에 1번만 보낼 수 있습니다.");
				break;
			case -17:
			case -16:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "메시지 수신을 차단한 사용자입니다.");
				break;
			case -15:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "CHAT_NOT_FOUND\n채팅방 정보를 찾을 수 없습니다.");
				break;
			case -14:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "메시지 수신을 차단한 사용자입니다.");
				break;
			case -13:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "등록되지 않은 사용자입니다.");
				break;
			case -12:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "해당 request에 필요한\nparameter가 누락되었거나\nparameter 형식이\n지정된 것과 다른 경우 등");
				break;
			case -11:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "탈퇴한 사용자입니다.");
				break;
			case -10:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "해당 사용자의 카카오\n계정 정보를 찾을 수 없습니다");
				break;
			case 4:
				setPopup(POPUP_KAKAOLOGINERR, playState, playState, 0, DONT);
				subTemp[10] = xSave.resVer;
				initSave();
				xSave.resVer = subTemp[10];
				gameSave(SAVE_SLOT_GAME);
				break;
			case 2:
				//카카오톡 로그인 취소키
				break;
			default:
				setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
				sprintf(xPopup.strText, "에러코드:%d",xKakaoData.errCode);
				break;
			}
			break;
		}
	}	
}


void kakaoAnRecv(int type)
{

}

M_Boolean checkKakaoFriend(char *strId)
{
	for(int i=0;i<xKakaoData.totalFriendInfoApp;i++)
	{
		if(strcmp(xKakaoData.xFriendInfoApp[i].strUserId, strId) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

M_Boolean getIsKakaoHelp(char *strId)
{
	for(int i=0;i<xSaveKakaoHelp.totalNum;i++)
	{
		if(xSaveKakaoHelp.helpDay[i] == xCalendar.nowDay)
		{
			if(strcmp(xSaveKakaoHelp.strHelpId[i], strId) == 0)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

void addKakaoHelp(char *strId)
{
	int checkNum = DONT;
	
	for(int i=0;i<xSaveKakaoHelp.totalNum;i++)
	{
		if(strcmp(xSaveKakaoHelp.strHelpId[i], strId) == 0)
		{
			checkNum = i;
		}
	}
	
	if(checkNum != DONT)
	{
		xSaveKakaoHelp.helpDay[checkNum] = xCalendar.nowDay;
	}
	else
	{
		sprintf(xSaveKakaoHelp.strHelpId[xSaveKakaoHelp.totalNum], "%s",strId);
		xSaveKakaoHelp.helpDay[xSaveKakaoHelp.totalNum] = xCalendar.nowDay;
		xSaveKakaoHelp.totalNum++;
	}
	gameSave(SAVE_SLOT_KAKAOHELP);
}


