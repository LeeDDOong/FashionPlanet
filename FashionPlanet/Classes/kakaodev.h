#ifndef __KAKAODEV__
#define __KAKAODEV__


typedef struct
{
	//////////////유저정보////////
	char strCountry[64];
	char strNickName[64];
	char strUserId[64];
	char strProfileUrl[128];
	int status;
	int verified;
	
	////////////친구쪽추가정보/////
	int userNum;	//가상코드
	int friendNum;	//가상코드
	char strGameNickName[64];
	char strTalkUserId[64];
	int supported_device;
	int message_blocked;
	
	M_Boolean isInvite;	//카카오초대여부
} XKAKAOUSERINFO;



#define KAKAOFRIENDLISTMAX		1024

#define KAKAOAIP_STATE_DONT			0
#define KAKAOAIP_STATE_LOGIN		1
#define KAKAOAIP_STATE_USERINFO		2
#define KAKAOAIP_STATE_FRIENDINFO	3


#define KAKAOAIP_STATE_SENDMESSAGE		4
#define KAKAOAIP_STATE_SENDMESSAGEAPP	5

#define KAKAOAIP_STATE_LOGOUT			6
#define KAKAOAIP_STATE_UNREG			7

#define KAKAOAIP_STATE_STOP				8
#define KAKAOAIP_STATE_KAKAOSTORY		9









#define KAKAOAIP_RESULT_WAIT		0
#define KAKAOAIP_RESULT_SUCCESS		1
#define KAKAOAIP_RESULT_FAIL		2


typedef struct
{
	XTOUCH xTouchLoginBtn;
	XTOUCH xTouchLogoutBtn;
	XTOUCH xTouchUserInfoBtn;
	XTOUCH xTouchFriendListBtn;
	XTOUCH xTouchSendMessage;
	
	
	int state;
	int resultType;
	int errCode;

	char strAnResult[1024*1024];
	
	
	
	//////////유저정보저장/////
	XKAKAOUSERINFO xUserInfo;
	//////////친구정보저장/////
	int totalFriendInfo;
	XKAKAOUSERINFO xFriendInfo[KAKAOFRIENDLISTMAX];		//앱사용X
	int totalFriendInfoApp;
	XKAKAOUSERINFO xFriendInfoApp[KAKAOFRIENDLISTMAX];	//앱이용
	////////////////////////
	
	int inveiteKeyReturn;
	int inveiteKakaoSlotNum;
	
	
	
	/////////캔디보상관련
	int socialBonusHelp;
	int socialBonusCarStorage;
	int socialBonusOrderSelectItem;

	
	
} XKAKAODATA;
extern XKAKAODATA xKakaoData;





void kakaoDevLogin(void);
void kakaoDevLogout(void);
void kakaoDevUserInfo(void);
void kakaoDevGetFriendList(void);
void kakaoDevSendMessageApp(const char*strUserId, const char*strMessage,const char*strTemplateId);
void kakaoDevSendMessage20_APP(const char*strUserId, const char*strMessage,const char*strImageFileName);
void kakaoDevSendMessage20(const char*strUserId, const char*strMessage);
void prcKakaoApi(void);
void kakaoStoryPost(void);

void kakaoAnRecv(int type);
M_Boolean checkKakaoFriend(char *strId);
void kakaoDevUnRegister(void);
M_Boolean getIsKakaoHelp(char *strId);
void addKakaoHelp(char *strId);
#endif


