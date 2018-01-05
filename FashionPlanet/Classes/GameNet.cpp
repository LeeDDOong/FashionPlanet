#include "Global.h"

#include "network/HttpRequest.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;

XNETAUTOSELL xNetAutoSell;
XNETAUTOPRODUCT xNetAutoProduct;
XNet xnet;
XNETEVENTQUEST xNetEventQuest;
XNETHOTDEAL xNetHotDeal;
XNETDATA xNetData;
XNETAMULETBUY xNetAmuletBuy;
XNETFASHION xNetFashion;
XNETINTERIOR xNetInterior;
XNETMAP xNetMap;
XNETFORMER xNetFormer;

XNETSELLTABLE xNetSellTable;
XNETSHOWWINDOW xNetShowWindow;
XNETINITGAME xNetInitGame;
XNETSTAFF xNetStaff;
XNETFACE xNetFace;
XNETG9EVENT xNetG9Event;
XNETTREND xNetTrend;
XNETCAR xNetCar;
XNETADDORDER xNetAddOrder;
XNETORDER xNetOrder;
XNETCARPARK xNetCarPark;
XNETSETSOUND xNetSetSound;
XNETORDEROK xNetOrderOk;
XNETDELRECVORDER xNetDelRecvOrder;
XNETGETMAP xNetGetMap;
XNETGETFASHIONSHOWRANK xNetFashionShowRank;
XNETGETFASHIONSHOWRANKINFO xNetFashionShowRankInfo;
XNEGETMODELLISTFRIEND xNetGetModelListFriend;
XNEMODELVOTE xNetModelVote;
XNETEXTERNALWALL xNetExternalWall;
XNETGETMODELMAIN xNetGetModelMain;
XNETSETMODELMAIN xNetSetModelMain;
XNETGETFRIENDLIST xNetFriendList;
XNETGETFRIENDSEARCH xNetFriendSearch;
XNETADDFRIEND xNetAddFriend;
XNETDELFRIEND xNetDelFriend;
XNETGETGAMEINFO xNetGetGameInfo;
XNETFRIENDSOCIAL xNetFriendSocial;
XNETMYSOCIALLIST xNetMySocialList;
XNETDELCLEAN xNetDelClean;
XNETGETGAMEINFO xNetGetOrder;
XNETGETFASHION xNetGetFashion;
XNETSENDMAIL xNetSendMail;
XNETGETMAILLIST xNetGetMailList;
XNETDELMAIL xNetDelMail;
XNETMINIPROFILE xNetMiniProfile;
XNETSENDGIFT xNetSendGift;
XNETGETGIFTLIST xNetGetGiftList;
XNETDELGIFT xNetDelGift;
XNETQUEST xNetQuest;
XNETTILE xNetTile;
XNETSETMODEL xNetSetModel;
XNETOPENMODEL xNetOpenModel;
XNETMODELGROUPGFIT xNetModelGroupGift;
XNETBESTDESIGNERRESULT xNetBestDesignerResult;
XNETTAKEPART xNetTakePart;
XNETTRENDMAKERINFO xNetTrendMakerInfo;
XNETTRENDMAKERVOTELIST xNetTrendMakerVoteList;
XNETVOTE xNetVote;
XNETBOOKMARK xNetBookMark;
XNETMARKETINGRECVYESNO xNetMarketingRecvYesNo;
XNETSENDMARKTING xNetSendMarketing;
XNETPRODUCTIONINFO xNetProductionInfo;
XNETSETFLOOR xNetSetFloor;
XNETBUYGOLD xNetBuyGold;
XNETCOUPON xNetCoupon;
XNETKAKAOHELP xNetKakaoHelp;
XNETSETPUSH xNetSetPush;
XNETPROFILEUPLOAD xNetProfileUpLoad;
XNETMILEAGESHOPBUY xNetMileageShopBuy;
XNETMILEAGESHOPUPDATE xNetMileageShopUpdate;
XNETPRODUCTIONNET xNetProductionNet;
XNETSELLNET xNetSellNet;
XNETJEWELQUEST xNetJewelQuest;
XNETAMULETUPDATE xNetAmuletUpdate;
XNETAMULETPAGEBUY xNetAmuletPageBuy;
XNETCLUBJOIN xNetClubJoin;
XNETCLUBDATA xNetClubData;
XNETCLUBMEMBER xNetClubMember;
XNETSETCLUBMASTER xNetSetClubMaster;
XNETSETCLUBFORCEOUT xNetSetClubForceOut;
XNETCLUBHISTORYLIST xNetClubHistoryList;
XNETCLUBBOOKLIST xNetClubBookList;
XNETCLUBJOINAPPLY xNetClubJoinApply;
XNETCLUBDRESSBUY xNetClubDressBuy;



int fashionNum;	//패션카테고리넘버
int floorNum;	//로딩층

void netSend(M_Int32 cmd,M_Int32 subIndex)
{
	int sellEndTime;
	int sellState;
    
	if(nowState == GAME_WORLDMAP)
	{	
		checkUserInfoHacking();		//기본 항상돌리자
		checkShopHacking();			//캐쉬샵
		checkProductionHacking();	//생산
		checkInteriorHacking();		//인테리어
		checkCarHacking();			//자동차
		checkQuestHacking();		//퀘스트
		checkExtensionHacking();	//확장
		checkStaffHacking();		//스테프
		checkGiftHacking();			//선물함
		checkMinigameHacking();		//미니게임
		checkModelHacking();		//모델해킹
		checkEtcHacking();			//기타
	}
				
	if(xGame.isHacking == TRUE && cmd != CMD_BUYGOLD)
	{
		//cmd = 해킹시도
		if(++xGame.hackingNetCnt <= 1)
		{
			xNetBuyGold.index = xGame.hackingType;
			xNetBuyGold.typeB = 200;//0:골드,1프리미엄,2캔디머쉰,3직원의상,모델뽑기
			xNetBuyGold.typeS = 0;//아이템종류(0~5)직원의상 구매시
			netSend(CMD_BUYGOLD, DONT);						
		}
		return;
	}
	
	if(cmd == CMD_GETTIME)
		xnet.isGetTime = TRUE;
				
	if(xnet.isHeartBit == FALSE)
	{
		xnet.isHeartBit =  TRUE;
	}
	xnet.heartBitTime = xCalendar.nowTime;
				
	//연결
	xnet.cmd = (M_Int16)cmd;
	xnet.state = NET_SEND;
	int client;
	
	//클라이언트종류(2:원스토어:,3:구글마켓)
#if(MARKET_TYPE==MARKET_TYPE_GOOGLE)
    client = 3;
#else
    client = 2;
#endif
    
    Json::Value root;
    int arrayIndex = 0;
    Json::Value arrayRoot;
    Json::Value array[30];
    
	switch(xnet.cmd)
	{
    case CMD_AUTHENTICATION:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]="0";
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#else
        sprintf(xGame.strDeviceID, "352461072873753");    //대호
            
        //sprintf(xGame.strDeviceID, "");    //대호

            
#endif
        root["ID"]=xGame.strDeviceID;
        root["APP_VERSION"]=NETVER;
        root["REC_VERSION"]=xSave.resVer;
        root["CLIENT"]=client;			
        break;
    case CMD_LOGIN:            
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]="0";
//        root["ID"]="102500557792235657915";
//        root["PASSWORD"]="102500557792235657915";//과장님 계정
//        root["ID"]="112274298363860004060";
//        root["PASSWORD"]="112274298363860004060";//하영씨 계정
//        root["ID"]="106403318778630873593";
//        root["PASSWORD"]="106403318778630873593";//다솜씨 계정
//        root["ID"]="116455304159778020587";
//        root["PASSWORD"]="116455304159778020587";//내 계정
        root["ID"]=xKakaoData.xUserInfo.strUserId;
        root["PASSWORD"]=xKakaoData.xUserInfo.strUserId;
        root["CLIENT"]=client;
        root["TOKEN"]=xNetData.strUid;
        break;
    case CMD_SETPUSH:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetSetPush.userNum;
        root["STATE"]=xNetSetPush.state;
        root["PUSH_1"]=(xSave.isPushOnOff[2] == FALSE?1:0);
        break;
    case CMD_SETKAKAOINVITE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["VISIT_COUNT"]=xKakao.totalKakaoInvite.oriData;
        break;
    case CMD_G9EVENT:
        //state0셀렉트     recv0:보상지급안한거		1:보상지급완료
        //보상지급안한유저는 1번보상지급요청
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["STATE"]=xNetG9Event.state;
        break;
    case CMD_UNREGISTERED:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_SETEXTERNALWALL:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["STATE"]=xNetExternalWall.state;
        root["SIDE_INDEX"]=xNetExternalWall.side_index;
        root["CASH"]=xSaveTemp.cash.oriData;
        root["GOLD"]=xSaveTemp.money.oriData;
        break;
    case CMD_IDMAKE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]="0";
        root["ID"]=xKakaoData.xUserInfo.strUserId;
        root["PASSWORD"]=xKakaoData.xUserInfo.strUserId;
        root["NICKNAME"]=xIdMake.strNickName;
        root["CLIENT"]=client;
        root["SEX"]=xIdMake.sex;
        root["AGE"]=xIdMake.age;
        root["ZONE"]=xIdMake.area;
        root["UID"]=xNetData.strUid;
        break;
    case CMD_DELPROFILEPHOTO:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_GETTIME:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]="0";
        root["USERNUM"]=xNetData.userNum;
        root["CLIENT"]=client;
        root["ID"]=xGame.strDeviceID;
        root["APP_VERSION"]=NETVER;
        root["DATA_VERSION"]=dataVer;
        break;
    case CMD_NOTICE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_SETETC:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CANDY_COUNT"]=xMiniGame.playCount;
        root["MODEL_COUNT"]=xModel.newModelCountNum;
        root["SOUND_INDEX"]=xSongSet.selectSong;
        break;
    case CMD_SETSOUND:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["INDEX"]=xNetSetSound.index;
        break;
    case CMD_BUYGOLD:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["BUY_INDEX"]=xNetBuyGold.index;
        root["LOG_TYPE"]=xNetBuyGold.typeB;
        root["ITEM_TYPE"]=xNetBuyGold.typeS;
        root["CLIENT"]=client;
        break;
    case CMD_GETSOUND:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_GETFRIENDMODEL:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_GETMODEL:
            root["PROTOCOL"]=xnet.cmd;
            root["AUTHENTICODE"]=xNetData.strAuthentiCode;
            root["USERNUM"]=xNetData.userNum;
    break;
	case CMD_MODELFRIENDVOTE:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		root["FRIEND_USERNUM"]=xNetModelVote.friendUserNum;
		root["KEY"]=xNetModelVote.key;
		root["CASH"]=xSaveTemp.cash.oriData;
		break;
	case CMD_KAKAOHELP:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		root["FRIEND_USERNUM"]=xNetKakaoHelp.friendUserNum;
		break;
	case CMD_GETMODELFRIEND:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		root["FRIEND_USERNUM"]=xNetGetModelListFriend.friendUserNum;
		break;
	case CMD_GETWINMODEL:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		break;
	case CMD_RANDOMFRIEND:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		break;
	case CMD_SETACCESS:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		root["COME_TIME"]=xAccessBonus.accessDay;
		root["COME_DAY"]=xAccessBonus.accessCount;
		break;
	case CMD_MODELGROUPGIFT:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		root["GROUP"]=xNetModelGroupGift.code;
		root["EXP"]=xSaveTemp.exp.oriData;
		root["GOLD"]=xSaveTemp.money.oriData;
		break;
	case CMD_SETMODEL:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		root["GOLD"]=xSaveTemp.money.oriData;
		root["CASH"]=xSaveTemp.cash.oriData;
		root["STATE"]=xNetSetModel.state;
		root["KEY"]=xNetSetModel.key;
		root["M_INDEX"]=xNetSetModel.code;
		root["UPGLADE"]=xNetSetModel.upgrade;
		root["LAYED1"]=xNetSetModel.layer[0];
		root["LAYED2"]=xNetSetModel.layer[1];
		root["LAYED3"]=xNetSetModel.layer[2];
		root["LAYED4"]=xNetSetModel.layer[3];
		root["LAYED5"]=xNetSetModel.layer[4];
		root["LAYED6"]=xNetSetModel.layer[5];
		root["LAYED7"]=xNetSetModel.layer[6];
		root["LAYED8"]=xNetSetModel.layer[7];
		root["LAYED9"]=xNetSetModel.layer[8];
		root["LAYED10"]=xNetSetModel.layer[9];
		root["LAYED11"]=xNetSetModel.layer[10];
		root["LAYED12"]=xNetSetModel.layer[11];
		root["LAYED13"]=xNetSetModel.layer[12];
		root["LAYED14"]=xNetSetModel.layer[13];
		root["LAYED15"]=xNetSetModel.layer[14];
		root["LAYED16"]=xNetSetModel.layer[15];
		root["LOAD"]=xNetSetModel.load;
		root["OUT"]=xNetSetModel.inFitting;
		break;
	case CMD_SETMODELTOTALSLOT:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		root["COUNT"]=xModel.totalInventoryModelMax;
		root["CASH"]=xSaveTemp.cash.oriData;
		break;

		case CMD_GETGAMEDATA:			
			if(xWorldMap.isFriendMap == TRUE)
            {
				xNetGetGameInfo.userNum = xFriendData[xFriendMap.selectDataSlotNum].userNum;
             
                root["UPDATE"]=0;
                
            }
			else
			{
				xNetGetGameInfo.userNum = xNetData.userNum;
                root["UPDATE"]=1;

			}
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetGetGameInfo.userNum;
			break;
		case CMD_MINIPROFILE:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["FRIEND_USERNUM"]=xNetMiniProfile.userNum;
			break;
		case CMD_GETGIFTLIST:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["ROWNUM"]=xNetGetGiftList.rowNum;
			root["PAGENUM"]=xNetGetGiftList.pageNum;
			break;
		case CMD_GETVOTELIST:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			break;
		case CMD_GETPMDATA:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			break;
		case CMD_VOTE:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["VOTE_USERNUM"]=xNetVote.friendNum;
			break;
		case CMD_GETFASHIONSHOWRANK:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["PAGENUM"]=xNetFashionShowRank.pageNum;
			root["RANK_TYPE"]=xNetFashionShowRank.action;
			root["REQUEST_TYPE"]=xNetFashionShowRank.request;
			break;
		case CMD_GETFRIENDLIST:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["ROWNUM"]=xNetFriendList.rowNum;
			root["PAGENUM"]=xNetFriendList.pageNum;
			root["TYPE"]=xNetFriendList.action;
			break;
		case CMD_GETMAILLIST:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetGetMailList.userNum;
			root["ROWNUM"]=xNetGetMailList.rowNum;
			root["PAGENUM"]=xNetGetMailList.pageNum;
			root["VISIT_USERNUM"]=xNetData.userNum;
			break;
		case CMD_SETMODELMAIN:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["SLOT"]=xNetSetModelMain.slot;
			root["MKEY"]=xNetSetModelMain.modelKey;
			root["MTIME"]=xNetSetModelMain.endTime;
			root["MSTATE"]=xNetSetModelMain.state;
			break;
		case CMD_GETMODELMAIN:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetGetModelMain.friendNum;
			break;
		case CMD_GETFACE:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			break;
		case CMD_DELGIFT:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["KEY"]=xNetDelGift.key;
			root["CASH"]=xSaveTemp.cash.oriData;
			root["GOLD"]=xSaveTemp.money.oriData;
            break;
		case CMD_GETFASHION:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetGetFashion.userNum;
			root["CARTEGORY"]=subIndex;
			break;
		case CMD_GETFRIENDSEARCH:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["TYPE"]=xNetFriendSearch.action;
			root["NICKNAME"]=xNetFriendSearch.strNickName;
			break;
		case CMD_FRIENDSOCIAL:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["FRIEND_USERNUM"]=xNetFriendSocial.friendNum;
			root["KEY"]=xNetFriendSocial.key;
			root["FLOOR"]=xNetFriendSocial.floor+1;
			root["EXP"]=xSaveTemp.exp.oriData;
			root["GOLD"]=xSaveTemp.money.oriData;
			root["FAME"]=xSaveTemp.fame.oriData;
			root["CANDY"]=xSaveTemp.tired.oriData;
			break;
		case CMD_USERSOCIALLIST:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetMySocialList.userNum;
			root["FLOOR"]=xNetMySocialList.floor+1;
			break;
		case CMD_DELCLEAN:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["CKEY"]=xNetDelClean.cKey;
			root["BKEY"]=xNetDelClean.bKey;
			root["FLOOR"]=xNetDelClean.floor+1;
			root["EXP"]=xSaveTemp.exp.oriData;
			root["GOLD"]=xSaveTemp.money.oriData;
			root["FAME"]=xSaveTemp.fame.oriData;
			root["CANDY"]=xSaveTemp.tired.oriData;
			break;
		case CMD_LVUP:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["LEVEL"]=xSaveTemp.lv.oriData;
			root["EXP"]=xSaveTemp.exp.oriData;
			break;
		case CMD_SENDMAIL:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetSendMail.friendNum;
			root["FRIEND_USERNUM"]=xNetSendMail.userNum;
			root["CONTENT"]=xMail.strTextBox;
			root["SECRET"]=xNetSendMail.action;
			break;
		case CMD_SETFLOOR:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["GOLD"]=xSaveTemp.money.oriData;
			root["CASH"]=xSaveTemp.cash.oriData;
			root["TYPE"]=xNetSetFloor.action;
			root["FLOOR"]=(xMap.totalFloor == 2?0:1);
			root["EXTEND"]=xMap.extension;
			root["EXTEND_WIDTH"]=xMap.tileInitW;
			root["EXTEND_HEIGHT"]=xMap.tileInitH;
			break;
		case CMD_SETORDER:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["KEY"]=xNetOrder.key;
			root["STATE"]=xNetOrder.state;
			root["TIME"]=xNetOrder.endTime;
			break;
		case CMD_SENDGIFT:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["CASH"]=xNetSendGift.cash;
			break;
		case CMD_SETTREND:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["GOLD"]=xSaveTemp.money.oriData;
			root["CASH"]=xSaveTemp.cash.oriData;
			root["SLOT"]=xNetTrend.slotNum;
			root["OPEN"]=xNetTrend.open;
			root["ITEM_INDEX"]=xNetTrend.code;
			root["TYPE_INDEX"]=xNetTrend.type;
			root["VALUE"]=xNetTrend.haveNum;
			root["TIME"]=xNetTrend.time;
			root["DATA1"]=xNetTrend.per;
			break;
		case CMD_SETFASHION:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["CARTEGORY"]=xNetFashion.code/1000;
			root["ITEM_INDEX"]=xNetFashion.code;
			root["ITEM_COUNT"]=xNetFashion.haveNum;
			root["GOLD"]=xSaveTemp.money.oriData;
			root["CASH"]=xSaveTemp.cash.oriData;
			break;
		case CMD_SETINTERIOR:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["CARTEGORY"]=xNetInterior.code/1000;
			root["ITEM_INDEX"]=xNetInterior.code;
			root["ITEM_COUNT"]=xNetInterior.haveNum;
			root["GOLD"]=xSaveTemp.money.oriData;
			root["CASH"]=xSaveTemp.cash.oriData;
			break;
		case CMD_GETINTERIOR:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			break;
		case CMD_SETCOUPON:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["COUPON"]=xNetCoupon.strText;
			break;
		case CMD_GETMAP:
			floorNum=subIndex;
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetGetMap.userNum;
			root["FLOOR"]=floorNum+1;
			root["TYPE"]=xNetGetMap.action;
			root["VISIT_USERNUM"]=xNetGetMap.friendNum;
			break;
		case CMD_DELMAIL:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetDelMail.userNum;
			root["KEY"]=xNetDelMail.key;
			break;
		case CMD_SETMAP:
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["GOLD"]=xSaveTemp.money.oriData;
			root["CASH"]=xSaveTemp.cash.oriData;
			root["EXP"]=xSaveTemp.exp.oriData;
			root["FLOOR"]=xNetMap.floor+1;
			root["ACTION"]=xNetMap.action;
			root["KEY"]=xNetMap.key;
			root["B_ITEM_INDEX"]=xNetMap.code;
			root["X"]=xNetMap.mapX;
			root["Y"]=xNetMap.mapY;
			root["SELL_GOLD"]=xNetMap.gold;
			root["SELL_CASH"]=xNetMap.cash;
			break;
		case CMD_SETSHOWWINDOW:
			char strKeySetShowWindow[32];
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["FLOOR"]=xNetShowWindow.floor+1;
			root["KEY"]=xNetShowWindow.key;
			root["SEX"]=xNetShowWindow.sex;
            
			for(int k=0;k<16;k++)
			{					
				sprintf(strKeySetShowWindow, "LAYER%d", k);
				root[strKeySetShowWindow] = xNetShowWindow.layer[k];
			}
			root["OUT"]= xNetShowWindow.inFitting;
			break;
		case CMD_SETSTAFF:
			char strKeySetStaff[32];
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["FLOOR"]=xNetStaff.floor+1;
			root["TYPE"]=xNetStaff.type;
			root["NICKNAME"]=xNetStaff.strNickName;
			root["SEX"]=xNetStaff.sex;
			
			for(int k=0;k<6;k++)
			{					
				sprintf(strKeySetStaff, "LAYER%d", k);
				root[strKeySetStaff] = xNetStaff.layer[k];
			}
			root["OUT"]= xNetStaff.inFitting;
			break;
		case CMD_SELLTABLEUPDATA:
            sellEndTime = getSellEndTime();
			sellState = (xSave.isPushOnOff[PUSHONOFF_SELLTABLE]==FALSE?1:0);
			if(sellEndTime <= 0)
				sellState = 1;
			else
				sellEndTime = sellEndTime*105/100;
			
            /*
			if(sellState == 0)
				addLocalPush(sellEndTime, "진열 중인 의상이 전부 완판됐네요.판매 보상 받으러 빨리오세요~", 1);
			else
				delLocalPush(1);
             */
				

			char strSellTableUpdata[32];
			
			
			root["PROTOCOL"]=xnet.cmd;
			root["AUTHENTICODE"]=xNetData.strAuthentiCode;
			root["USERNUM"]=xNetData.userNum;
			root["TOKEN"]=xNetData.strUid;
			root["CLIENT"]=client;
			root["PUSH_TIME"]=sellEndTime;
			root["PUSH_STATE"]=sellState;
			
            


            arrayIndex = 0;
			for(int i=0;i<xSellTableUpdata.total;i++)
			{
                array[arrayIndex]["FLOOR"]=xSellTableUpdata.floor[i]+1;
				array[arrayIndex]["KEY"]=xMap.dataKey[xSellTableUpdata.floor[i]][MAP_TYPE_OBJ][xSellTableInfo[xSellTableUpdata.floor[i]][xSellTableUpdata.sellTableNum[i]].x][xSellTableInfo[xSellTableUpdata.floor[i]][xSellTableUpdata.sellTableNum[i]].y];
				
				for(int k=0;k<6;k++)
				{
					sprintf(strSellTableUpdata, "D_ITEM_INDEX_%d", k);
                    array[arrayIndex][strSellTableUpdata] = xSellTableInfo[xSellTableUpdata.floor[i]][xSellTableUpdata.sellTableNum[i]].xSlot[k].code;

					sprintf(strSellTableUpdata, "COUNT_%d",k);
                    array[arrayIndex][strSellTableUpdata] = xSellTableInfo[xSellTableUpdata.floor[i]][xSellTableUpdata.sellTableNum[i]].xSlot[k].maxNum;

					sprintf(strSellTableUpdata, "SELL_COUNT_%d", k);
                    array[arrayIndex][strSellTableUpdata] = xSellTableInfo[xSellTableUpdata.floor[i]][xSellTableUpdata.sellTableNum[i]].xSlot[k].num;
					
					sprintf(strSellTableUpdata, "START_TIME_%d", k);
                    array[arrayIndex][strSellTableUpdata] = (int)xSellTableInfo[xSellTableUpdata.floor[i]][xSellTableUpdata.sellTableNum[i]].xSlot[k].flowTime;
				}
                
                arrayRoot.append(array[arrayIndex]);
                arrayIndex++;
			}
            root["SHOP"] = arrayRoot;
		break;
    case CMD_SETSELLTABLE:
        sellEndTime = getSellEndTime();
        sellState = (xSave.isPushOnOff[PUSHONOFF_SELLTABLE]==FALSE?1:0);
        if(sellEndTime <= 0)
            sellState = 1;
        else
            sellEndTime = sellEndTime*105/100;
        
        /*
        if(sellState == 0)
            addLocalPush(sellEndTime, "진열 중인 의상이 전부 완판됐네요.판매 보상 받으러 빨리오세요~", 1);
        else
            delLocalPush(1);
         */

        char strKeySetSellTable[32];
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["GOLD"]=xSaveTemp.money.oriData;
        root["CASH"]=xSaveTemp.cash.oriData;
        root["EXP"]=xSaveTemp.exp.oriData;
        root["FLOOR"]=xNetSellTable.floor+1;			
        root["KEY"]=xNetSellTable.key;
        
        for(int k=0;k<6;k++)
        {					
            sprintf(strKeySetSellTable, "D_ITEM_INDEX_%d", k);
            root[strKeySetSellTable] = xNetSellTable.xSellSlot[k].code;

            sprintf(strKeySetSellTable, "COUNT_%d", k);
            root[strKeySetSellTable]= xNetSellTable.xSellSlot[k].maxNum;

            sprintf(strKeySetSellTable, "SELL_COUNT_%d", k);
            root[strKeySetSellTable] = xNetSellTable.xSellSlot[k].num;

            sprintf(strKeySetSellTable, "START_TIME_%d", k);
            root[strKeySetSellTable] = (int)xNetSellTable.xSellSlot[k].flowTime;
                            
            sprintf(strKeySetSellTable, "COOK_%d", k);
            root[strKeySetSellTable] = xNetSellTable.xSellSlot[k].useCook;
                            
            xNetSellTable.xSellSlot[k].useCook = 0;
        }
        
        root["TOKEN"]=xNetData.strUid;
        root["CLIENT"]=client;
        root["PUSH_TIME"]=sellEndTime;
        root["PUSH_STATE"]=sellState;
        break;
    case CMD_BILL:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["BUY_INDEX"]=xShop.selectSlot;
        root["CLIENT"]=client;
        root["ID"]=xKakaoData.xUserInfo.strUserId;
        root["FRIEND_USERNUM"]=xCashGift.friendUserNum;
        root["REQUEST_INFO"]=(xWorldMap.isCashGift == TRUE?1:0);
        
        root["INAPP_PURCHASE_DATA"]=xBill.strReceipt;
        root["INAPP_DATA_SIGNATURE"]=xBill.strSignature;
        root["FIRST_INAPP"]=(xWorldMap.isFirstIap == TRUE?1:0);
        break;
    case CMD_TODAY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CONTENT"]=xMail.strToday;
        break;
    case CMD_GETEVENT:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_SETFACE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["ITEM_INDEX"]=xNetFace.code;
        root["ITEM_COUNT"]=xNetFace.haveNum;
        root["GOLD"]=xSaveTemp.money.oriData;
        root["CASH"]=xSaveTemp.cash.oriData;
        break;
    case CMD_INITGAME:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["ACTION"]=xNetInitGame.action;
        break;
    case CMD_GETTREND:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;

    case CMD_GETORDER:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetGetOrder.userNum;
        break;
    case CMD_DELRECVORDER:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["KEY"]=xNetDelRecvOrder.key;
        break;
    case CMD_SETCAR:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["GOLD"]=xSaveTemp.money.oriData;
        root["CASH"]=xSaveTemp.cash.oriData;
        root["CAR_INDEX"]=xNetCar.code;
        break;
    case CMD_SETCARPARK:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SLOT"]=xNetCarPark.slot;
        root["KEY"]=xNetCarPark.key;
        root["CAR_INDEX"]=xNetCarPark.carNum;
        root["STATE"]=xNetCarPark.state;
        root["START_TIME"]=xNetCarPark.time;
        break;
    case CMD_ADDFRIEND:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["FRIEND_USERNUM"]=xNetAddFriend.friendNum;
        break;
    case CMD_ADDFRIENDID:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["ID"]=xNetAddFriend.strKakaoid;
        break;
    case CMD_DELFRIEND:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["FRIEND_USERNUM"]=xNetDelFriend.friendNum;
        break;
    case CMD_ADDORDER:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetAddOrder.userNum;
        root["STATE"]=xNetAddOrder.state;
        root["FRIEND_USERNUM"]=xNetAddOrder.friendNum;
        root["ITEM_INDEX"]=xNetAddOrder.code;
        break;
    case CMD_HACKINGCHECK:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CASH"]=xSaveTemp.cash.oriData;
        break;
    case CMD_ORDEROK:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["KEY"]=xNetOrderOk.key;
        root["EXP"]=xSaveTemp.exp.oriData;
        root["GOLD"]=xSaveTemp.money.oriData;
        root["STATE"]=xNetOrderOk.action;
        break;
    case CMD_SETTILE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["TYPE"]=xNetTile.type;
        root["BOTTOM"]=xNetTile.tileCode;
        root["WALL"]=xNetTile.wallCode;
        root["FLOOR"]=xNetTile.floor+1;
        break;
    case CMD_GETFASHIONSHOWRANKINFO:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetFashionShowRankInfo.userNum;
        root["RANK_TYPE"]=xNetFashionShowRankInfo.action;
        break;
    case CMD_SETSOCIALITEM:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["ITEM_INDEX1"]=xSaveTemp.socialItem[0];
        root["ITEM_INDEX2"]=xSaveTemp.socialItem[1];
        root["TIME"]=xSaveTemp.socialDay;
        break;
    case CMD_GETQUEST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_SETQUEST:			
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["TYPE"]=xNetQuest.type;
        root["T_INDEX"]=xQuestTuto.nowNum;
        root["T_STATE"]=xQuestTuto.state;
        root["M_INDEX"]=xQuestMain.nowNum;
        root["M_STATE"]=xQuestMain.state;			
        root["M_VALUE1"]=xQuestDataMain[xQuestMain.nowNum].checkNow[0];
        root["M_VALUE2"]=xQuestDataMain[xQuestMain.nowNum].checkNow[1];
        root["M_VALUE3"]=xQuestDataMain[xQuestMain.nowNum].checkNow[2];
        root["QUEST_INDEX"]=xNetQuest.slot;
        root["STATE"]=xQuestDataNormal[xNetQuest.slot].state;
        root["VALUE1"]=xQuestDataNormal[xNetQuest.slot].checkNow[0];
        root["VALUE2"]=xQuestDataNormal[xNetQuest.slot].checkNow[1];
        root["VALUE3"]=xQuestDataNormal[xNetQuest.slot].checkNow[2];
        root["END_QUEST"]=xQuestInfo.cleanNormal;
        root["REWARD_GOLD"]=xNetQuest.gold;
        root["REWARD_CASH"]=xNetQuest.cash;
        root["REWARD_EXP"]=xNetQuest.exp;
        break;
    case CMD_RECVORDER:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTlCODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;			
        break;
    case CMD_SETFASHIONSHOW:
        
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SCORE"]=xRunWay.totalFashionShowScore;
            
        arrayIndex = 0;
        for(int m=0; m<xRunWay.maxModel; m++)
        {
            array[arrayIndex]["M_INDEX"]=xRunWay.modelCode[m];
            array[arrayIndex]["UPGLADE"]=xRunWay.modelUpgrade[m];
            array[arrayIndex]["LAYED1"]=xRunWay.xF_Model[m].code[0];
            array[arrayIndex]["LAYED2"]=xRunWay.xF_Model[m].code[1];
            array[arrayIndex]["LAYED3"]=xRunWay.xF_Model[m].code[2];
            array[arrayIndex]["LAYED4"]=xRunWay.xF_Model[m].code[3];
            array[arrayIndex]["LAYED5"]=xRunWay.xF_Model[m].code[4];
            array[arrayIndex]["LAYED6"]=xRunWay.xF_Model[m].code[5];
            array[arrayIndex]["LAYED7"]=xRunWay.xF_Model[m].code[6];
            array[arrayIndex]["LAYED8"]=xRunWay.xF_Model[m].code[7];
            array[arrayIndex]["LAYED9"]=xRunWay.xF_Model[m].code[8];
            array[arrayIndex]["LAYED10"]=xRunWay.xF_Model[m].code[9];
            array[arrayIndex]["LAYED11"]=xRunWay.xF_Model[m].code[10];
            array[arrayIndex]["LAYED12"]=xRunWay.xF_Model[m].code[11];
            array[arrayIndex]["LAYED13"]=xRunWay.xF_Model[m].code[12];
            array[arrayIndex]["LAYED14"]=xRunWay.xF_Model[m].code[13];
            array[arrayIndex]["LAYED15"]=xRunWay.xF_Model[m].code[14];
            array[arrayIndex]["LAYED16"]=xRunWay.xF_Model[m].code[15];
            array[arrayIndex]["OUT"]=xRunWay.xF_Model[m].isInFitting==FALSE?0:1;
            
            arrayRoot.append(array[arrayIndex]);
            arrayIndex++;

        }
        root["MODEL"] = arrayRoot;
        break;
    case CMD_SETGAMEDATA:
        {
        int requestType = 0;//0내정보,1제작슬롯;
        for(int i=0;i<12;i++)
        {
            int type = i/6;
            int slot = i%6;
            if(xProductionMenu.isUpData[type][slot] == TRUE)
            {
                xProductionMenu.isUpData[type][slot] = FALSE;
                //requestType = 1;
                if(xProductionMenu.pushState[type][slot] == 0)	//등록
                {
                                        }
                else	//취소
                {
                                        }
            }
        }
                        
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;	
        root["USERNUM"]=xNetData.userNum;
        root["LEVEL"]=xSaveTemp.lv.oriData;
        root["GOLD"]=xSaveTemp.money.oriData;
        root["CASH"]=xSaveTemp.cash.oriData;
        root["EXP"]=xSaveTemp.exp.oriData;
        root["CANDY"]=xSaveTemp.tired.oriData;
        root["CANDY_TIME"]=(int)xSaveTemp.tiredTime;
        root["FAME"]=xSaveTemp.fame.oriData;
        root["NPC_AM"]=xSaveTemp.orderAmDay;
        root["NPC_PM"]=xSaveTemp.orderPmDay;
        root["TRAND_AM"]=xSaveTemp.trendAmDay;
        root["TRAND_PM"]=xSaveTemp.trendPmDay;
        root["REQUEST_TYPE"]=requestType;
        }
        break;
    case CMD_MILEAGESHOPCOUNT:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_MILEAGESHOPLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_MILEAGESHOPBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        
        root["ITEM_INDEX"]=xNetMileageShopBuy.ITEM_INDEX;
        root["ADDRESS"]=xNetMileageShopBuy.ADDRESS;
        root["BUYER_NAME"]=xNetMileageShopBuy.BUYER_NAME;
        root["PHONENUM"]=xNetMileageShopBuy.PHONENUM;
        break;
    case CMD_MILEAGESHOPUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["ITEM_KEY"]=xNetMileageShopUpdate.ITEM_KEY;
        root["ADDRESS"]=xNetMileageShopUpdate.ADDRESS;
        root["BUYER_NAME"]=xNetMileageShopUpdate.BUYER_NAME;
        root["PHONENUM"]=xNetMileageShopUpdate.PHONENUM;
        break;
    case CMD_MILEAGESHOPCANCLE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
        
        
        
    case CMD_PRODUCTIONSTART:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SLOT"]=xNetProductionNet.SLOT;
        root["ITEM_INDEX"]=xNetProductionNet.ITEM_INDEX;
        break;
    case CMD_PRODUCTIONCANCLE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SLOT"]=xNetProductionNet.SLOT;
        break;
    case CMD_PRODUCTIONFASTPOP:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SLOT"]=xNetProductionNet.SLOT;
        break;
    case CMD_PRODUCTIONCOMPLETE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SLOT"]=xNetProductionNet.SLOT;
        break;
    case CMD_PRODUCTIONOPEN:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SLOT"]=xNetProductionNet.SLOT;
        break;
    case CMD_SELLSTART:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["FLOOR"]=xNetSellNet.FLOOR+1;
        root["KEY"]=xNetSellNet.KEY;
        root["SLOT"]=xNetSellNet.SLOT;
        root["ITEM_INDEX"]=xNetSellNet.ITEM_INDEX;
        root["COUNT"]=xNetSellNet.COUNT;
        root["SELL_COUNT"]=xNetSellNet.SELL_COUNT;
        break;
    case CMD_SELLCANCLE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["FLOOR"]=xNetSellNet.FLOOR+1;
        root["KEY"]=xNetSellNet.KEY;
        root["SLOT"]=xNetSellNet.SLOT;
        break;
    case CMD_SELLFASTPOP:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["FLOOR"]=xNetSellNet.FLOOR+1;
        root["KEY"]=xNetSellNet.KEY;
        root["SLOT"]=xNetSellNet.SLOT;
        root["CASH"]=xNetSellNet.POP;
        break;
    case CMD_SELLCOMPLETE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["FLOOR"]=xNetSellNet.FLOOR+1;
        root["KEY"]=xNetSellNet.KEY;
        root["SLOT"]=xNetSellNet.SLOT;
        root["GOLD"]=xNetSellNet.GOLD;
        root["EXP"]=xNetSellNet.EXP;
        break;
    case CMD_PREPAYBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLIENT"]=client;
        root["ID"]=xKakaoData.xUserInfo.strUserId;
        root["INAPP_PURCHASE_DATA"]=xBill.strReceipt;
        root["INAPP_DATA_SIGNATURE"]=xBill.strSignature;
        break;
    case CMD_PREPAYDAY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_PACKAGEBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["BUY_INDEX"]=xPackagePopup.selectType;
        root["CLIENT"]=client;
        root["INAPP_PURCHASE_DATA"]=xBill.strReceipt;
        root["INAPP_DATA_SIGNATURE"]=xBill.strSignature;
        break;
    case CMD_PACKAGELIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_EVENTQUESTMAINLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_EVENTQUESTMAINCOMPLETE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["MAIN_TYPE"]=xNetEventQuest.DETAIL_TYPE;
        break;
    case CMD_EVENTQUESTDETAILLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["DETAIL_TYPE"]=xNetEventQuest.DETAIL_TYPE;
        break;
    case CMD_EVENTQUESTDETAILUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["DETAIL_TYPE"]=xNetEventQuest.DETAIL_TYPE;
        root["DETAIL_INDEX"]=xNetEventQuest.DETAIL_INDEX;
        root["VALUE"]=xNetEventQuest.VALUE;
        break;
    case CMD_EVENTQUESTDETAILCOMPLETE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["DETAIL_TYPE"]=xNetEventQuest.DETAIL_TYPE;
        root["DETAIL_INDEX"]=xNetEventQuest.DETAIL_INDEX;
        break;
    case CMD_HOTDEALMAINLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLIENT"]=client;
        break;
    case CMD_HOTDEALDETAILLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLIENT"]=client;
        break;
    case CMD_HOTDEALMAINOPEN:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_HOTDEALDETAILOPEN:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SLOT"] = xNetHotDeal.slot;
        root["CATE"] = xHotDeal.xSlot[xNetHotDeal.slot].itemType;
        root["INDEX"] = xHotDeal.xSlot[xNetHotDeal.slot].itemCode;
        root["DC"] = xHotDeal.xSlot[xNetHotDeal.slot].salePer;
        break;
    case CMD_HOTDEALDETAILBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["SLOT"] = xNetHotDeal.slot;
        break;
    case CMD_RIVALLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_RIVALSTART:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["MAINNUM_NOW"]= xRival.nowMain;
        root["SUBNUM_NOW"]= xRival.nowDetail;
        break;
    case CMD_RIVALSTOP:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_RIVALUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["QUEST_0"]= xRival.checkNow[0];
        root["QUEST_1"]= xRival.checkNow[1];
        root["QUEST_2"]= xRival.checkNow[2];
        root["QUEST_3"]= xRival.checkNow[3];
        root["QUEST_4"]= xRival.checkNow[4];
        root["QUEST_5"]= xRival.checkNow[5];
        root["QUEST_6"]= xRival.checkNow[6];
        root["QUEST_7"]= xRival.checkNow[7];
        root["QUEST_8"]= xRival.checkNow[8];
        root["QUEST_9"]= xRival.checkNow[9];
        break;
    case CMD_RIVALCOMPLETE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_SETDEVICEID:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["DEVICE_ID"]=xGame.strDeviceID;
        break;
    case CMD_BOOKMARK:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["FRIENDNUM"]=xNetBookMark.FRIENDNUM;
        root["BOOKMARK"]=xNetBookMark.BOOKMARK;
        break;
    case CMD_JEWELQUESTLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_JEWELQUESTUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["INDEX"]=xNetJewelQuest.INDEX;
        root["VALUE"]=xNetJewelQuest.VALUE;
        break;
    case CMD_JEWELQUESTCOMPLETE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["INDEX"]=xNetJewelQuest.INDEX;
        break;
    case CMD_AMULETBUYLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_AMULETBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["AMULET"]=xNetAmuletBuy.AMULET;
        break;
    case CMD_AMULETLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
            
        if(xWorldMap.isFriendMap == FALSE)
            root["USERNUM"]=xNetData.userNum;
        else
            root["USERNUM"]=xFriendData[xFriendMap.selectDataSlotNum].userNum;
            
        break;
    case CMD_AMULETUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        
        root["STATE"]=xNetAmuletUpdate.pageUpdate;
        root["DECK"]=xNetAmuletUpdate.selectPage;
        root["AMULET"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].amuletCode;
        root["SLOT0"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[0];
        root["SLOT1"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[1];
        root["SLOT2"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[2];
        root["SLOT3"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[3];
        root["SLOT4"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[4];
        root["SLOT5"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[5];
        root["SLOT6"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[6];
        root["SLOT7"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[7];
        root["SLOT8"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[8];
        root["SLOT9"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[9];
        root["SLOT10"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[10];
        root["SLOT11"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[11];
        root["SLOT12"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[12];
        root["SLOT13"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[13];
        root["SLOT14"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[14];
        root["SLOT15"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[15];
        root["SLOT16"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[16];
        root["SLOT17"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[17];
        root["SLOT18"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[18];
        root["SLOT19"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[19];
        root["SLOT20"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[20];
        root["SLOT21"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[21];
        root["SLOT22"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[22];
        root["SLOT23"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[23];
        root["SLOT24"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[24];
        root["SLOT25"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[25];
        root["SLOT26"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[26];
        root["SLOT27"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[27];
        root["SLOT28"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[28];
        root["SLOT29"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[29];
        root["SLOT30"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[30];
        root["SLOT31"]=xAmulet.xAmuletPage[xNetAmuletUpdate.selectPage].socketJewelCode[31];
        break;
    case CMD_AMULETPAGEBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["DECK"]=xNetAmuletPageBuy.DECK;
        break;
    case CMD_CLUBLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_CLUBMAKE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["NICKNAME"]=xSaveTemp.strNickName;
        root["CLUB_NAME"]=xClubMake.strName;
        root["ICON"]=xClubMake.iconListCode[xClubMake.selectIconSlot];
        root["JOIN"]=xClubMake.selectJoinType;
        root["CONTENT"]=xClubMake.strJoinInfo;
        break;
    case CMD_CLUBJOIN:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xNetClubJoin.CLUB_NUM;
        root["NICKNAME"]=xSaveTemp.strNickName;
        break;
    case CMD_CLUBUNREG:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;

        break;
    case CMD_CLUBSEARCH:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NAME"]=xClubSearch.strName;
        break;
    case CMD_CLUBDATA:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xNetClubData.CLUB_NUM;
        break;
    case CMD_CLUBMEMBER:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xNetClubMember.CLUB_NUM;
        break;
    case CMD_SETCLUBJOINTYPE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["TYPE"]=xClub.xMy.joinType;
        break;
    case CMD_SETCLUBNOTICE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["NOTICE"]=xClub.xMy.strNotice;
        break;
    case CMD_SETCLUBJOININFO:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["CONTENT"]=xClub.xMy.strJoinInfo;
        break;
    case CMD_SETCLUBFORCEOUT:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["MEMBER_NUM"]=xNetSetClubForceOut.MEMBER_NUM;
        break;
    case CMD_SETCLUBMASTER:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["MEMBER_NUM"]=xNetSetClubMaster.MEMBER_NUM;
        break;
    case CMD_CLUBJOINLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        break;
    case CMD_CLUBJOINAPPLY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]= xNetClubJoinApply.CLUB_NUM;
        break;
    case CMD_CLUBJOINACCEPT:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["MEMBER_NUM"]=xClubJoinMember.xJoinMember[xClubLobby.selectSlot].userKey;
            
        break;
    case CMD_CLUBJOINDEL:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["MEMBER_NUM"]=xClubJoinMember.xJoinMember[xClubLobby.selectSlot].userKey;
        break;
    case CMD_CLUBHISTORYLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["ROWNUM"]=xNetClubHistoryList.rowNum;
        root["PAGENUM"]=xNetClubHistoryList.pageNum;
        break;
    case CMD_CLUBBOOKLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["ROWNUM"]=xNetClubBookList.rowNum;
        root["PAGENUM"]=xNetClubBookList.pageNum;
        break;
    case CMD_CLUBBOOKADD:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["CONTENT"]=xClubBook.strText;
        break;
    case CMD_CLUBBOOKDEL:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["KEY"]=xClubBook.xSlot[xClubBook.selectSlot].key;
        break;
    case CMD_CLUBRANKLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        break;
    case CMD_CLUBSTORAGYLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        break;
    case CMD_CLUBITEMBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        root["ITEM_INDEX"]=xClubShop.selectedNum;
        break;
    case CMD_CLUBGIVEGIFT:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        root["ITEM_INDEX"]=xClubStorage.xData[xClubStorage.selectedNum].num;
        root["TOTAL"]=xClubShopGift.giftCount;
        arrayIndex=0;
        for(int i=0;i<xClubShopGift.totalData;i++)
        {
            if(xClubShopGift.touched[i] == true)
            {
                int memberCode = xClubShopGift.memberCode[i];
                array[arrayIndex]["MEMBER_NUM"]=xClub.xMember[memberCode].userKey;
                arrayRoot.append(array[arrayIndex]);
                arrayIndex++;
            }
            
        }
        root["MEMBER"] = arrayRoot;
        break;
    case CMD_CLUBDONATIONCOUNT:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        break;
    case CMD_CLUBDONATION:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        root["TYPE"]=xClub.donationType;
        break;
    case CMD_PANGCOUNTCHECK:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_PANGTIMESRESET:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        break;
    case CMD_CLUBNAMEMODIFY:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        root["CLUBNAME"]=xClubNameModify.strName;
        break;
    case CMD_CLUBITEMDELETE:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        root["ITEM_INDEX"]=xClubStorage.xData[xClubStorage.selectedNum].num;
        break;
    case CMD_CLUBICONLISTUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        break;
    case CMD_CLUBICONBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
//        root["ICONNUM"]=xClub.xIcon[xClubIconShop.selectedNum].index;
        root["ICONNUM"]=xClubIconShop.selectedNum;
        break;
    case CMD_CLUBICONUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        root["ICONNUM"]=xClub.xIcon[xChangeClubIcon.selectedNum].index;
        break;
    case CMD_FASHIONWEEKDRESSLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        break;
    case CMD_FASHIONWEEKFITTINGLIST:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        break;
    case CMD_CLUBDRESSBUY:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["DRESS_NUM"]=xNetClubDressBuy.DRESS_NUM;
        break;
    case CMD_FASHIONWEEKFITTINGUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["SEX"]=xClub.xMy.gender;
        root["FACE"]=xClub.xMy.xFace.faceNum;
        root["HAIR"]=xClub.xMy.xFace.hairNum;
        root["LAYER0"]=xClub.xMy.xF.code[0];
        root["LAYER1"]=xClub.xMy.xF.code[1];
        root["LAYER2"]=xClub.xMy.xF.code[2];
        root["LAYER3"]=xClub.xMy.xF.code[3];
        root["LAYER4"]=xClub.xMy.xF.code[4];
        root["LAYER5"]=xClub.xMy.xF.code[5];
        root["LAYER6"]=xClub.xMy.xF.code[6];
        root["LAYER7"]=xClub.xMy.xF.code[7];
        root["LAYER8"]=xClub.xMy.xF.code[8];
        root["LAYER9"]=xClub.xMy.xF.code[9];
        root["LAYER10"]=xClub.xMy.xF.code[10];
        root["LAYER11"]=xClub.xMy.xF.code[11];
        root["LAYER12"]=xClub.xMy.xF.code[12];
        root["LAYER13"]=xClub.xMy.xF.code[13];
        root["LAYER14"]=xClub.xMy.xF.code[14];
        root["LAYER15"]=xClub.xMy.xF.code[15];
        root["PUTIN"]=xClub.xMy.xF.isInFitting ==false?0:1;
        break;
    case CMD_PANGSTART:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUBNUM"]=xClub.xMy.clubKey;
        break;
    case CMD_PANGRESULT:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["SCORE"]=xPang.totalScore.oriData;
            
        {
            
        int totalDress = 0;
        int dressCode[10];
        int dressScore[10];
        bool isCheck = false;
        for(int k=0;k<10;k++)
            dressScore[k] = 0;
            
            
            for(int k=0; k<FASHIONWEEKSETTINGMAX; k++)
            {
                if(xFashionWeekModel[k].studioSlotNum != DONT)
                {
                    if(xFashionStudio.itemCode[xFashionWeekModel[k].studioSlotNum] != DONT)
                    {
                        isCheck = false;
                        for(int z=0;z<totalDress;z++)
                        {
                            if(dressCode[z] == xFashionStudio.itemCode[xFashionWeekModel[k].studioSlotNum])
                            {
                                isCheck = true;
                                dressScore[z] += xPang.score[k].oriData+xPang.buffScore[k].oriData+xPang.comboScore[k].oriData;
                                break;
                            }
                        }
                        
                        if(isCheck == false)
                        {
                            dressCode[totalDress] = xFashionStudio.itemCode[xFashionWeekModel[k].studioSlotNum];
                            dressScore[totalDress] = xPang.score[k].oriData+xPang.buffScore[k].oriData+xPang.comboScore[k].oriData;
                            totalDress++;
                        }
                    }
                }
            }
            
            arrayIndex = 0;
            for(int k=0; k<totalDress; k++)
            {
                array[arrayIndex]["DRESS_NUM"]=dressCode[k];
                array[arrayIndex]["VALUE"]=dressScore[k];
                arrayRoot.append(array[arrayIndex]);
                arrayIndex++;
            }
        }
        root["DRESS"] = arrayRoot;
        break;
    case CMD_FASHIONWEEKEXP:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["DRESS_NUM"]=xFashionStudio.itemCode[xFashionStudio.selectInfoSlot];
        break;
    case CMD_FASHIONWEEKSCOREUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["CLUB_NUM"]=xClub.xMy.clubKey;
        root["SCORE"]=xFashionWeek.totalScore;
        break;
    case CMD_FORMERLISTUPDATE:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        break;
            
    case CMD_FORMERSTART:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["KEY"]=xNetFormer.key;
        root["TIME"]=xNetFormer.startTime;
        break;
            
    case CMD_FORMERTAKEWEALTH:
        root["PROTOCOL"]=xnet.cmd;
        root["AUTHENTICODE"]=xNetData.strAuthentiCode;
        root["USERNUM"]=xNetData.userNum;
        root["KEY"]=xNetFormer.key;
        root["TYPE"]=xNetFormer.type;
        root["VALUE"]=xNetFormer.wealth;
        break;
	case CMD_AUTOSELL:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		root["GOLD"]=xNetAutoSell.gold;
		break;
	case CMD_AUTOPRODUCT:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		arrayIndex = 0;
		for(int i=0;i<xEventQueueNet.item_total[0];i++)
		{
			array[arrayIndex]["CATEGORY"] = xEventQueueNet.item_category[0][i];
			array[arrayIndex]["ITEM_INDEX"] = xEventQueueNet.item_index[0][i];
			array[arrayIndex]["ITEM_COUNT"] = xEventQueueNet.item_count[0][i];
			arrayRoot.append(array[arrayIndex]);
			arrayIndex++;
		}
		root["DRESS"] = arrayRoot;
		break;
	case CMD_AUTOPRODUCTSLOTUPDATE:
		root["PROTOCOL"]=xnet.cmd;
		root["AUTHENTICODE"]=xNetData.strAuthentiCode;
		root["USERNUM"]=xNetData.userNum;
		arrayIndex = 0;
			
		for(int i=0;i<12;i++)
		{
			int type = i/6;
			int slot = i%6;
			
			array[arrayIndex]["SLOT"]=i;
			array[arrayIndex]["OPEN"]=xProductionMenu.isOpen[type][slot];
			array[arrayIndex]["TYPE"]=xProductionMenu.isFriend[type][slot];
			array[arrayIndex]["KEY"]=xProductionMenu.orderKey[type][slot];
			array[arrayIndex]["STATE"]=xProductionMenu.state[type][slot];
			array[arrayIndex]["ITEM_INDEX"]=xProductionMenu.slotCode[type][slot];
			array[arrayIndex]["START_TIME"]=0;
			array[arrayIndex]["BONUS"]=xProductionMenu.minigameBonus[type][slot];
			array[arrayIndex]["TOKEN"]=xNetData.strUid;
			array[arrayIndex]["PUSH_STATE"]=xProductionMenu.pushState[type][slot];
			array[arrayIndex]["CLIENT"]=client;
			array[arrayIndex]["PUSH_TIME"]=xProductionMenu.pushTime[type][slot];
			array[arrayIndex]["COOK"]=xProductionMenu.useLook[type][slot];
			
			arrayRoot.append(array[arrayIndex]);
			arrayIndex++;

		}
		root["SLOT"] = arrayRoot;
		
		break;
	}
	
	
	
	
	
	
	char strUrl[256];
    Json::StyledWriter writer;
    std::string strJson = writer.write(root);
    HttpRequest *request = new HttpRequest();
    std::vector<std::string> headers;
    
    //지연씨서버
    switch(xnet.cmd)
    {
    case CMD_AUTHENTICATION:		//인증서버
#if(SERVER_TYPE == SEVER_TYPE_RELEASE)
    sprintf(strUrl, "%s","http://14.63.223.48:2010/Contact.aspx"); //마이부띠크
#else
    sprintf(strUrl, "%s","http://125.129.247.61:6071/Contact.aspx"); //DEV
        headers.push_back("Content-Type: application/json");
        request->setHeaders(headers);
#endif
        break;
    case CMD_DELPROFILEPHOTO:
        sprintf(strUrl, "%s%s",xNetData.strImgServerUrl,"/Contact.aspx");
        break;
    default:						//게임서버
        sprintf(strUrl, "%s%s",xNetData.strGameServerUrl,"/Contact.aspx");
        break;
    }
    
    request->setUrl(strUrl);
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback(xGame.layer,callfuncND_selector(FashionShop::onHttpRequestCompleted));
    request->setRequestData(strJson.c_str(), strlen(strJson.c_str()));
    HttpClient::getInstance()->send(request);
    request->release();

    
    //if(xnet.cmd >= CMD_RIVALLIST)
    {
        CCLOG("보낸패킷>>>%s\n",strJson.c_str());
//        log("KBY_Send Packet(%d)>>>%s\n",xnet.cmd,strJson.c_str());
    }
}

void setRecv(char* strJson)
{
	
	if(xInventoryFashion.haveNum[0][13] > 0)
		printf("setRecv1 >>>%d\n",xInventoryFashion.haveNum[0][13]);
	
    HttpResponse *response = (HttpResponse *)strJson;
    std::vector<char> *buffer = response->getResponseData();
    
    char strRecv[409600];
    memset(strRecv, 0, sizeof(strRecv));
    
    for(unsigned int i=0;i<buffer->size();i++)
        strRecv[i] = (*buffer)[i];
    Json::Value root;
    Json::Value array;
    Json::Reader reader;
    reader.parse(strRecv, root);
    
    //if(root["PROTOCOL"].asInt() <= -CMD_RIVALLIST)
    {
        CCLOG("받은패킷>>%s\n",strRecv);
//        log("KBY_RECV Packet>>>%s\n",strRecv);
    }
    
	xEventQueueNet.isNetOk[0] = TRUE;
	xMainMenu.isInitNet = TRUE;
	xnet.isHeartBit =  FALSE;
    
    if(!response)
    {
        setPopup(POPUP_SERVERERR, playState, playState, 0,xnet.cmd);
        sprintf(xPopup.strText, "네트워크가 불안정합니다.\n(%d=responseErr)",xnet.cmd);
        return;
    }
    
    if(buffer->size() == 0)
    {
        setPopup(POPUP_SERVERERR, playState, playState, 0,xnet.cmd);
        sprintf(xPopup.strText, "네트워크가 불안정합니다.\n(%d=size0)",xnet.cmd);
        return;
    }
    
	switch(root["STATUS"].asInt())
	{
	case 0:
		break;
	default:
		setPopup(POPUP_SERVERERR, playState, playState, 0, 1000+xnet.cmd);
		return;
		break;
	}	
	
	switch(root["PROTOCOL"].asInt())
	{
    case CMD_MILEAGESHOPLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            array = root["ORDER"];
            for(int i=0;i<array.size();i++)
            {
                
                
                
                xMileageShopInfo.xSlot[xMileageShopInfo.totalNum].key = array[i]["ITEM_KEY"].asInt();
                xMileageShopInfo.xSlot[xMileageShopInfo.totalNum].code = array[i]["ITEM_INDEX"].asInt();
                xMileageShopInfo.xSlot[xMileageShopInfo.totalNum].state = array[i]["ITEM_STATE"].asInt();
                
                sprintf(xMileageShopInfo.xSlot[xMileageShopInfo.totalNum].strAddress, "%s",array[i]["ADDRESS"].asCString());
                sprintf(xMileageShopInfo.xSlot[xMileageShopInfo.totalNum].strName, "%s",array[i]["BUYER_NAME"].asCString());
                sprintf(xMileageShopInfo.xSlot[xMileageShopInfo.totalNum].strPhone, "%s",array[i]["PHONENUM"].asCString());
                
                sprintf(xMileageShopInfo.xSlot[xMileageShopInfo.totalNum].strDate, "%s",array[i]["DATE"].asCString());
                
                
                
                
                xMileageShopInfo.totalNum++;
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_MILEAGESHOPUPDATE_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            //root["MILEAGE"].asInt();
            xMileageShop.state = MILEAGESHOP_STATE_INFO_POPUP;
            sprintf(xMileageShop.strPopupTitle, "변경완료");
            sprintf(xMileageShop.strPopupText, "배송정보가 변경되었습니다.");
                
                
            sprintf(xMileageShopInfo.xSlot[xMileageShopInfo.selectSlot].strName, "%s",xMileageShop.strName);
            sprintf(xMileageShopInfo.xSlot[xMileageShopInfo.selectSlot].strAddress, "%s",xMileageShop.strAddress);
            sprintf(xMileageShopInfo.xSlot[xMileageShopInfo.selectSlot].strPhone, "%s",xMileageShop.strPhone);
                
                
                
            break;
        case 2:	//재고없음
        case 1:	//실패
        case 4:	//실패
        case 3:	//마일리지부족
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        
        }
        break;
    case CMD_MILEAGESHOPBUY_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            initSecurity(&xSaveTemp.mileage, root["MILEAGE"].asInt());
            xMileageShop.state = MILEAGESHOP_STATE_POPUP;
            sprintf(xMileageShop.strPopupTitle, "신청완료");
            sprintf(xMileageShop.strPopupText, "상품신청이 완료되었습니다.\n감사합니다.");
            break;
        case 2:	//재고없음
            xMileageShop.state = MILEAGESHOP_STATE_POPUP;
            sprintf(xMileageShop.strPopupTitle, "재고부족");
            sprintf(xMileageShop.strPopupText, "죄송합니다.\n신청하신 상품의 재고가 부족합니다.\n다른 상품을 신청해주세요.");
            break;
        case 1:	//실패
        case 3:	//마일리지부족
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_MILEAGESHOPCOUNT_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            array = root["ITEM"];
            for(int i=0;i<array.size();i++)
            {
                int type = array[i]["ITEM_INDEX"].asInt()/10000;
                int listNum = array[i]["ITEM_INDEX"].asInt()%10000;
                xMileageData.xSlot[type][listNum].nowCount = array[i]["ITEM_COUNT"].asInt();
            }
            xMileageShop.state = MILEAGESHOP_STATE_PLAY;
            setMileageShopCategory();
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
	case CMD_G9EVENT_RECV:
		if(xNetG9Event.state == 0)
		{
			switch(root["RESULT"].asInt())
			{
			case 0:	//보상지급안함놈은 g9패키지설치여부 확인
				xG9.isNet = TRUE;
				break;
			case 1:	//보상지급된놈은 이벤트 잠금
				xG9.isOpen = FALSE;
				break;
			}
		}
		else
		{
			switch(root["RESULT"].asInt())
			{
			case 0:	//성공
				xG9.isOpen = FALSE;
				setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
				sprintf(xPopup.strText,"%d룩이 선물함으로\n지급되었습니다.",G9BONUSCASH);
				break;
			case 1:	//이미 보상 지급된 유저임
				xG9.isOpen = FALSE;
				break;
			case 2:	//실패
				xG9.isOpen = FALSE;
				setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
				break;
			}
		}
		break;
    case CMD_PACKAGEBUY_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xnet.iapState = IAP_STATE_SUCCED_CP;
            
            xPackageData[xPackagePopup.selectType].cnt++;
            //최종성공
            xBill.isBilling = FALSE;
            xnet.iapState = IAP_STATE_DONT;
                
            xSave.giftLastKey = 999;
            gameSave(SAVE_SLOT_GAME);

                
            
            //보상처리
            setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
            sprintf(xPopup.strText, "구매완료\n선물함을 확인해주세요");
            xWorldMap.isKeyReturn = FALSE;
                
            initSecurity(&xSaveTemp.mileage,root["MILEAGE"].asInt());
                
            sprintf(xRocks.strTemp, "%d원",xPackageData[xPackagePopup.selectType].price);
                setFiveRocksPurchase(xRocks.strTemp,xPackageData[xPackagePopup.selectType].price);
            
                sprintf(strTempS, "%d원과금성공",xPackageData[xPackagePopup.selectType].price);
            sprintf(xRocks.strTemp, "%s",xSaveTemp.strNickName);
            setFiveRocksCustom("인앱",strTempS,xRocks.strTemp,"NULL",1);
            
                sprintf(xRocks.strTemp, "%d원",xPackageData[xPackagePopup.selectType].price);
            setFiveRocksCustom("인앱","과금성공",xRocks.strTemp,"NULL",1);
            break;
        case 1:	//실패
            xnet.iapState = IAP_STATE_FAIL_CP;
            break;
        }
        break;
    case CMD_PACKAGELIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            array = root["GOODS"];
            for(int i=0;i<array.size();i++)
            {
                int index = array[i]["BUY_INDEX"].asInt();
                xPackageData[index].cnt = array[i]["COUNT"].asInt();
            }
            setState(GAME_WORLDMAP, PLAY_PLAY, DONT);
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
            
        break;
    case CMD_PREPAYBUY_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xnet.iapState = IAP_STATE_SUCCED_CP;
            
            //최종성공
            xBill.isBilling = FALSE;
            xnet.iapState = IAP_STATE_DONT;
                
            //보상처리
            xSave.giftLastKey = 999;
            gameSave(SAVE_SLOT_GAME);

            setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
            sprintf(xPopup.strText, "구매완료\n선물함을 확인해주세요");
            xWorldMap.isKeyReturn = FALSE;
            xPrePay.remainDay = 30;
            xPrePay.isRecv = false;
                
                
            initSecurity(&xSaveTemp.mileage,root["MILEAGE"].asInt());
                
                
                
            sprintf(xRocks.strTemp, "%d원",xPrePay.price);
            setFiveRocksPurchase(xRocks.strTemp,xPrePay.price);
            
            sprintf(strTempS, "%d원과금성공",xPrePay.price);
            sprintf(xRocks.strTemp, "%s",xSaveTemp.strNickName);
            setFiveRocksCustom("인앱",strTempS,xRocks.strTemp,"NULL",1);
            
            sprintf(xRocks.strTemp, "%d원",xPrePay.price);
            setFiveRocksCustom("인앱","과금성공",xRocks.strTemp,"NULL",1);
            break;
        case 1:	//실패
            xnet.iapState = IAP_STATE_FAIL_CP;
            break;
        }
        break;
	case CMD_BILL_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			xnet.iapState = IAP_STATE_SUCCED_CP;
                
            //최종성공
            xBill.isBilling = FALSE;
            xnet.iapState = IAP_STATE_DONT;
            //보상처리
            int lookNum;
                
            if(xWorldMap.isCashGift == TRUE)	//선물보내기
            {
                lookNum = xShop.moneyPoint[xShop.selectSlot].oriData;
                setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
                sprintf(xPopup.strText, "선물보내기완료");
                xWorldMap.isKeyReturn = FALSE;
                
                setMileage(xMileageShop.cashBonus[xShop.selectSlot]);
            }
            else
            {
                if(xWorldMap.isFirstIap == TRUE)
                    lookNum = xShop.moneyPoint[xShop.selectSlot].oriData+xShop.moneyPriceFirstBonus[xShop.selectSlot];
                else
                    lookNum = xShop.moneyPoint[xShop.selectSlot].oriData;
                
                setMileage(xMileageShop.cashBonus[xShop.selectSlot]);
                setCash(lookNum);
                
                
                addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, FALSE);
                
                setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
                sprintf(xPopup.strText, "구매완료");
                
                if(xWorldMap.isFirstIap == TRUE)
                {
                    ///////////////////////////////////////////////////////////////////
                    xEventQueueNet.layer[xEventQueueNet.totalNum][0] = 100;//0:골드,1프리미엄,2캔디머쉰,3직원의상,4모델뽑기,100:첫구매이벤트,101:스페션세일이벤트,102:리뷰이벤트
                    xEventQueueNet.layer[xEventQueueNet.totalNum][1] = 0;//아이템종류(0~5)직원의상 구매시
                    xEventQueueNet.code[xEventQueueNet.totalNum] = xShop.selectSlot;
                    addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_BUYGOLD, TRUE);
                    ///////////////////////////////////////////////////////////////////
                }
                xWorldMap.isFirstIap = FALSE;
                xWorldMap.isKeyReturn = FALSE;
            }
            
            if(xWorldMap.isOpen_CASH10000 == TRUE)
            {
                ///////////////////////////////////////////////////////////////////
                xEventQueueNet.action[xEventQueueNet.totalNum] = 0;		//셀렉트(만원이벤트 지급과 g9이벤트 참여여부얻어오기)
                addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_G9EVENT, TRUE);
                ///////////////////////////////////////////////////////////////////
            }
                
                
            sprintf(xRocks.strTemp, "%d원",xShop.moneyPrice[xShop.selectSlot].oriData);
            setFiveRocksPurchase(xRocks.strTemp,xShop.moneyPrice[xShop.selectSlot].oriData);

            
            sprintf(strTempS, "%d원과금성공",xShop.moneyPrice[xShop.selectSlot].oriData);
            sprintf(xRocks.strTemp, "%s",xSaveTemp.strNickName);
            setFiveRocksCustom("인앱",strTempS,xRocks.strTemp,"NULL",1);
            
            sprintf(xRocks.strTemp, "%d원",xShop.moneyPrice[xShop.selectSlot].oriData);
            setFiveRocksCustom("인앱","과금성공",xRocks.strTemp,"NULL",1);                
			break;
		case 1:	//실패
			xnet.iapState = IAP_STATE_FAIL_CP;
			break;
		}
		break;
	case CMD_GETEVENT_RECV:
		xWorldMap.isFirstIap = root["CHARGE_INFO"].asInt() == 0?TRUE:FALSE;
		xSaleShop.isOpen = root["SPACIAL_EVENT"].asInt() == 0?FALSE:TRUE;
		sprintf(xSaleShop.strDay,"%s",root["SPACIAL_TEXT"].asCString());
			
		xNetGetFashion.userNum = xNetData.userNum;
		netSend(CMD_GETFASHION, 0);
		break;
    case CMD_SETDEVICEID_RECV:
        xWorldMap.isSetDeviceId = true;
        break;
	case CMD_GETTIME_RECV:
		xnet.isGetTime = FALSE;
			
		xCalendar.nowYear_Hacking = root["YEAR"].asInt();
		xCalendar.nowMonth_Hacking = root["MONTH"].asInt();
		xCalendar.nowDay_Hacking =root["DAY"].asInt();
		xCalendar.nowHour_Hacking =root["HOUR"].asInt();
		xCalendar.nowMinute_Hacking =root["MINUTE"].asInt();
		xCalendar.nowSec_Hacking =root["SECOND"].asInt();
		checkTimeHacking();
        
        if(nowState == GAME_WORLDMAP)
        {
            switch(root["RESULT"].asInt())
            {
            case 2:	//점검중
                nativePopupExit("서버점검상태입니다.");
                break;
            case 3:	//앱버전
                nativePopupExit("새버전 업데이트후 이용가능합니다.");
                break;
            case 4:	//데이타
                nativePopupExit("새로운 패치적용을 위해 재실행합니다.");
                break;
            case 5:	//디바이스중복
                //내디바이스 등록완료후에 체크하자
                if(xWorldMap.isSetDeviceId == true)
                    nativePopupExit("다른 디바이스에서 접속하였습니다.");
                break;
            }
        }
		break;
	case CMD_AUTHENTICATION_RECV:
            
		sprintf(xNetData.strNotice				,"%s",root["NOTICE"] .asCString());
		sprintf(xNetData.strGameServerUrl		,"%s",root["GAME_SERVER_URL"] .asCString());
		sprintf(xNetData.strImgServerUrl		,"%s",root["IMG_SERVER_URL"] .asCString());
		sprintf(xNetData.strGameUpDateServerUrl,"%s",root["GAME_UPDATE_URL"] .asCString());
        sprintf(xNetData.strCdnUrl,"%s",root["DATA_SERVER_URL"] .asCString());
        sprintf(xNetData.strReviewUrl,"%s",root["GAME_REVIEW_URL"] .asCString());            
            
        xNetData.isQa = root["QA"].asInt() == 0?false:true;
		xWorldMap.isAppReview = root["INFO"].asInt() == 0?TRUE:FALSE;
        
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			xMainMenu.state = MAINMENU_STATE_INITFILEDOWN;
			xResCheck.state = RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_START;
			xMainMenu.anyCnt = 0;
			/*
			안드로이드 파일 다운로드 미구현시 이걸로
			xMainMenu.state = MAINMENU_STATE_RESCHECK;
			xResCheck.state = RESCHECK_STATE_MAINSCRIPT_DOWNLOAD_START;
			xMainMenu.anyCnt = 0;
			*/
			break;
		case 1:	//최신 어플로 업데이트 바람
			setPopup(POPUP_APPSTOREUPGRADEYESNO, playState, playState, 0, DONT);
			break;
		case 2:	//리소스로 업데이트 바람
			setPopup(POPUP_RESUPGRADEYESNO, playState, playState, 0, DONT);
			break;
		case 3:	//서버점검중
			xMainMenu.state = MAINMENU_STATE_SERVERNOTICE;
			break;
		case 4:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}						
		break;
	case CMD_SETPUSH_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			//TRUE:수신가능 FALSE:수신불가능
			if(xNetSetPush.state == 0)
			{
				int pushNum = root["PUSH_1"].asInt();
				if(xWorldMap.isFriendMap == TRUE)
				{
					xFriendMap.isLoadingOk = TRUE;
					xFriendData[xFriendMap.selectDataSlotNum].isKakaoMessage = pushNum== 0?TRUE:FALSE;
					
					if(xFriendData[xFriendMap.selectDataSlotNum].isKakaoMessage == TRUE)
					{
						//카카오톡수신거부일경우
						int message_blocked = 0;
						for(int k=0;k<xKakaoData.totalFriendInfoApp;k++)
						{
							if(strcmp(xFriendData[xFriendMap.selectDataSlotNum].strKakaoId, xKakaoData.xFriendInfoApp[k].strUserId) == 0)
							{
								message_blocked = xKakaoData.xFriendInfoApp[k].message_blocked;
								break;
							}
						}
						if(message_blocked == 1)
							xFriendData[xFriendMap.selectDataSlotNum].isKakaoMessage = FALSE;
					}
				}
				else
				{
					//내정보 얻어올때와
					if(xNetSetPush.userNum == xNetData.userNum)
					{
						xSave.isPushOnOff[2] = (pushNum == 0?TRUE:FALSE);
					}
					//주문장 리스트친구정보 얻어올때
					else
					{
						xFriendData[xOrder.xSlotListData[xOrder.slotNumList[xOrder.selectSlot]].friendNum].isKakaoMessage = pushNum== 0?TRUE:FALSE;
						
						if(xFriendData[xOrder.xSlotListData[xOrder.slotNumList[xOrder.selectSlot]].friendNum].isKakaoMessage == TRUE)
						{
							//카카오톡수신거부일경우
							int message_blocked = 0;
							for(int k=0;k<xKakaoData.totalFriendInfoApp;k++)
							{
								if(strcmp(xFriendData[xOrder.xSlotListData[xOrder.slotNumList[xOrder.selectSlot]].friendNum].strKakaoId, xKakaoData.xFriendInfoApp[k].strUserId) == 0)
								{
									message_blocked = xKakaoData.xFriendInfoApp[k].message_blocked;
									break;
								}
							}
							if(message_blocked == 1)
								xFriendData[xOrder.xSlotListData[xOrder.slotNumList[xOrder.selectSlot]].friendNum].isKakaoMessage = FALSE;
						}
						
						setPopup(POPUP_KAKAOCARSTORAGE, playState, playState, 0, DONT);
						xOrder.isKakaoMessage_Net = FALSE;
					}
				}
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_SETCOUPON_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
			sprintf(xPopup.strText, "선물함으로 정상\n지급되었습니다.");
			break;
		case 1:	//쿠폰등록기간이 아님
			setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
			sprintf(xPopup.strText, "쿠폰등록기간이 아닙니다.");
			break;
		case 2:	//이미 사용이 완료된 쿠폰
			setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
			sprintf(xPopup.strText, "사용이 완료된 쿠폰입니다.");
			break;
		case 3:	//등록기간이 지남
			setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
			sprintf(xPopup.strText, "등록기간이 지난 쿠폰입니다.");
			break;
		case 4:	//해당쿠폰없음
			setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
			sprintf(xPopup.strText, "잘못된 쿠폰번호 입니다.");
			break;
		case 5:	//
			setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
			sprintf(xPopup.strText, "해당쿠폰은 한번만 사용가능합니다.");
			break;
		}
		break;
	case CMD_ADDFRIENDID_RECV:
		int kakaoSlot;
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
		case 1:	//이미등록완료
			kakaoSlot = checkKakaoAppInvite(xNetAddFriend.strKakaoid);
			if(kakaoSlot == DONT)
				addKakaoAppInvite(xNetAddFriend.strKakaoid,FALSE);
			
			kakaoSlot = checkKakaoAppInvite(xNetAddFriend.strKakaoid);
			xSaveKakaoApp.isDel[kakaoSlot] = FALSE;
			
			sprintf(xSaveKakaoApp.strNickName[kakaoSlot], "%s",root["NICKNAME"] .asCString());
			gameSave(SAVE_SLOT_KAKAOAPP);
			break;
		case 2:	//실패
			kakaoSlot = checkKakaoAppInvite(xNetAddFriend.strKakaoid);
			if(kakaoSlot == DONT)
				addKakaoAppInvite(xNetAddFriend.strKakaoid,TRUE);
			
			kakaoSlot = checkKakaoAppInvite(xNetAddFriend.strKakaoid);
			xSaveKakaoApp.isDel[kakaoSlot] = TRUE;
			if(xWorldMap.state == WORLDMAP_STATE_FRIENDLIST && xFriend.state == FRIEND_STATE_ADD)
			{
				setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
				sprintf(xPopup.strText, "계정 생성중 또는\n탈퇴한 아이디입니다");
			}
				
			memset(xSaveKakaoApp.strNickName[kakaoSlot], 0, sizeof(xSaveKakaoApp.strNickName[kakaoSlot]));
			gameSave(SAVE_SLOT_KAKAOAPP);
			break;
		}
		break;
	case CMD_PHOTOUPLOAD_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
            xWorldMap.state = WORLDMAP_STATE_PLAY;
			//유저넘버 슬롯번호 찾기
			int userNum = xNetData.userNum;
			int slotNum = getFriendSlot(userNum);
			
			if(slotNum == DONT)
			{
				slotNum = addFriendData(userNum);
			}
							
			if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
				sprintf(xFriendData[slotNum].strUrl, "%s",root["URL"] .asCString());

                
            xFriendData[slotNum].waitCnt = 0;
			xFriendData[slotNum].downLoadImgState = FRIENDDOWNLOADIMG_STATE_DONT;
			freeImg(&imgFriend[slotNum]);
			gameSave(SAVE_SLOT_GAME);
			}
			break;
		default:
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;				
		}
		break;
	case CMD_GETPMDATA_RECV:
		{
			//유저넘버 슬롯번호 찾기
			xMail.pmUserId = root["FRIEND_USERNUM"].asInt();
			int userNum = xMail.pmUserId;
			int slotNum = getFriendSlot(userNum);
			
			if(slotNum == DONT)
			{
				slotNum = addFriendData(userNum);
			}
			
			xFriendData[slotNum].lv = root["LEVEL"].asInt();
			xFriendData[slotNum].sex = root["SEX"].asInt();
			xFriendData[slotNum].age = root["AGE"].asInt();
			if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
				sprintf(xFriendData[slotNum].strUrl, "%s",root["PRO_URL"] .asCString());
			
			sprintf(xFriendData[slotNum].strNickName, "%s",root["NICKNAME"] .asCString());
			sprintf(xMail.strTodayPm, "%s",root["TODAY"] .asCString());
		}
		break;
	case CMD_UNREGISTERED_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			subTemp[10] = xSave.resVer;
			initSave();
			xSave.resVer = subTemp[10];
			gameSave(SAVE_SLOT_GAME);
			xSaveKakao.totalInvite = 0;
			xSaveKakaoApp.totalInvite = 0;
			gameSave(SAVE_SLOT_KAKAO);
			gameSave(SAVE_SLOT_KAKAOAPP);
								
			setPopup(POPUP_UNREGISTEREDOK, playState, playState, 0, DONT);
			break;
		case 1:	//실패
			setPopup(POPUP_LOGINERR2, playState, playState, 0, DONT);
			break;
		}
		break;
	case CMD_LOGIN_RECV:
            
        //해당계정이 있나 확인해야함 바로 로그인 만약에 계정기록이 있다면 idmake = TRUE 없다면 IDMAKE로
        switch(root["RESULT"].asInt())

        {
		case 0:	//성공
        

			sprintf(xNetData.strAuthentiCode		,"%s",root["AUTHENTICODE"] .asCString());
			xNetData.userNum = root["USERNUM"].asInt();
			xNetData.eventNum = root["EVENT"].asInt();
			xNetData.serverTime = root["SERVER_TIME"].asInt();
			initSecurity(&xKakao.totalKakaoInvite, root["VISIT_COUNT"].asInt());
								
			if(xKakao.totalKakaoInvite.oriData == 0)
			{
				xSaveKakao.totalInvite = 0;
				gameSave(SAVE_SLOT_KAKAO);
			}
				

            xSave.isKakaoLogin = TRUE;
			sprintf(xSave.strId,"%s",xKakaoData.xUserInfo.strUserId);
			gameSave(SAVE_SLOT_GAME);	
			xNetInitGame.action = 0; //(0:완료여부확인 1:완료후 저장)
			netSend(CMD_INITGAME, DONT);
            
			break;
		case 1:	//아이디,패스 불일친
            xSave.isKakaoLogin = FALSE;
			 xMainMenu.state = MAINMENU_STATE_IDMAKE;
			 xIdMake.state = IDMAKE_STATE_IDMAKE;
			 sprintf(xIdMake.strNickName, "대표자명 입력");
			 
			 xIdMake.sex = 0;
			 xIdMake.emailErr = IDMAKEERR_TYPE_DONT;
			 xIdMake.passErr = IDMAKEERR_TYPE_DONT;
			 xIdMake.nickNameErr = IDMAKEERR_TYPE_DONT;
			 xIdMake.ageErr = IDMAKEERR_TYPE_DONT;
			break;
		case 2:	//블럭유저
			setPopup(POPUP_BLACKUSER, playState, playState, 0, DONT);
			break;
		case 3:	//중복로그인
			setPopup(POPUP_LOGINERRRRRRRRR, playState, playState, 0, DONT);
			break;
		case 4:	//실패
			setPopup(POPUP_LOGINERR2, playState, playState, 0, DONT);
			break;
		}			
		break;
	case CMD_IDMAKE_RECV:
		//88106339744539473
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
            setFiveRocksCustom("퍼널분석","4.계정생성","NULL","NULL",1);
                
			xIdMake.state = IDMAKE_STATE_STAMP;
			xIdMake.anyCnt = 0;
				
			sprintf(xSave.strId, "%s",xKakaoData.xUserInfo.strUserId);
			sprintf(xSaveTemp.strNickName, "%s",xIdMake.strNickName);
			gameSave(SAVE_SLOT_GAME);
			break;
		case 1:	//존재하는아이디
			subTemp[10] = xSave.resVer;
			initSave();
			xSave.resVer = subTemp[10];
			gameSave(SAVE_SLOT_GAME);
			xKakaoData.state = KAKAOAIP_STATE_LOGOUT;
			

			setPopup(POPUP_IDREMAKE, playState, playState, 0, DONT);
			break;
		case 2:	//존재하는 닉네임
			xIdMake.nickNameErr = IDMAKEERR_TYPE_NICKNAMEERR2;
			break;
		case 3:	//실패
			setPopup(POPUP_IDMAKEERR, playState, playState, 0, DONT);
			break;
		}
		break;
	case CMD_SENDMAIL_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			memset(xMail.strTextBox, 0, sizeof(xMail.strTextBox));
			xMail.totalMailSlot = 0;
			xMail.rowNum = 0;
			xMail.pageNum = 0;
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETFRIENDSEARCH_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
                array = root["FRIEND"];
				xFriend.totalNumListRanDom = 0;
				for(int i=0;i<array.size();i++)
				{
					//유저넘버 슬롯번호 찾기
					int userNum = array[i]["USERNUM"].asInt();
					int slotNum = getFriendSlot(userNum);

					if(slotNum == DONT)
					{
						slotNum = addFriendData(userNum);
					}

					if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
						sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());
					sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
					xFriendData[slotNum].lv = array[i]["LEVEL"].asInt();
					xFriendData[slotNum].sex = array[i]["SEX"].asInt();
					xFriendData[slotNum].age = array[i]["AGE"].asInt();
                    xFriendData[slotNum].area = array[i]["ZONE"].asInt();
                    
					xFriend.dataSlotNumListRanDom[xFriend.totalNumListRanDom++] = slotNum;
				}

				if(xFriend.totalNumListRanDom == 0)
					xFriend.addState = FRIENDADD_STATE_NOTUSER;
				else
					xFriend.addState = FRIENDADD_STATE_RESULT;

			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}

		break;
	case CMD_MINIPROFILE_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
				//유저넘버 슬롯번호 찾기
				int slotNum = xMiniProfile.friendDataSlotNum;

				xFriendData[slotNum].lv = root["LEVEL"].asInt();
				xFriendData[slotNum].sex = root["SEX"].asInt();
				xFriendData[slotNum].age = root["AGE"].asInt();

				xFriendData[slotNum].isFriend = root["FRIEND"].asInt();	//0:아님1:맞음
				xFriendData[slotNum].area = root["ZONE"].asInt();
                
                
                
                xFriendData[slotNum].todayVisit = root["TODAY_VISIT"].asInt();
                xFriendData[slotNum].todayOrder = root["TODAY_ORDER"].asInt();
                xFriendData[slotNum].friendState = root["FRIEND_STATE"].asInt();
                xFriendData[slotNum].socialCount = root["SOCIAL_COUNT"].asInt();
                xFriendData[slotNum].isVote = (root["TODAY_VOTE"].asInt()==0?FALSE:TRUE);
                
                if(xFriendData[slotNum].isFriend == false)
                {
                    xFriendData[slotNum].socialCount = 3;
                
                }

                
                
                
                


				sprintf(xMiniProfile.strToday, "%s",root["TODAY"] .asCString());
				if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
					sprintf(xFriendData[slotNum].strUrl, "%s",root["PRO_URL"] .asCString());
				sprintf(xFriendData[slotNum].strNickName, "%s",root["NICKNAME"] .asCString());
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETWINMODEL_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
                
                
				xWinnerModel.totalNum = 0;
                array = root["WINNER"];
				for(int i=0;i<array.size();i++)
				{
					//array[i]["TYPE"].asInt()		//0심사모드1투표모드
					//유저넘버 슬롯번호 찾기
					int userNum = array[i]["USERNUM"].asInt();
					int slotNum = getFriendSlot(userNum);

					if(slotNum == DONT)
					{
						slotNum = addFriendData(userNum);
					}
					sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());

					xWinnerModel.friendDataNum[xWinnerModel.totalNum] = slotNum;
					xWinnerModel.type[xWinnerModel.totalNum] = array[i]["TYPE"].asInt();
					xWinnerModel.modelNum[xWinnerModel.totalNum] = array[i]["M_INDEX"].asInt();

					xWinnerModel.xF[xWinnerModel.totalNum].code[0] = array[i]["LAYED1"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[1] = array[i]["LAYED2"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[2] = array[i]["LAYED3"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[3] = array[i]["LAYED4"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[4] = array[i]["LAYED5"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[5] = array[i]["LAYED6"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[6] = array[i]["LAYED7"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[7] = array[i]["LAYED8"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[8] = array[i]["LAYED9"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[9] = array[i]["LAYED10"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[10] = array[i]["LAYED11"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[11] = array[i]["LAYED12"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[12] = array[i]["LAYED13"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[13] = array[i]["LAYED14"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[14] = array[i]["LAYED15"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].code[15] = array[i]["LAYED16"].asInt();
					xWinnerModel.xF[xWinnerModel.totalNum].isInFitting = array[i]["OUT"].asInt()==0?FALSE:TRUE;

					xWinnerModel.totalNum++;
				}
			}
			netSend(CMD_GETVOTELIST, DONT);
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETGIFTLIST_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
            if(xNetGetGiftList.pageNum == 0)
                xMail.totalMailSlot = 0;
			{
				xMail.rowNum = root["ROWNUM"].asInt();
                array = root["BOOK"];
				xMail.giftLastKey = xSave.giftLastKey;
								
				for(int i=0;i<array.size();i++)
				{
                    
                    if(xMail.totalMailSlot > MAILSLOTMAX-10)
                        continue;
                                        
					xMail.xMailSlot[xMail.totalMailSlot].key = array[i]["KEY"].asInt();
					
					if(xMail.totalMailSlot == 0)
					{
						if(xWorldMap.isFriendMap == FALSE)
							xMail.giftLastKey = xMail.xMailSlot[xMail.totalMailSlot].key;
					}

					//유저넘버 슬롯번호 찾기
					int userNum = array[i]["USERNUM"].asInt();
					int slotNum = getFriendSlot(userNum);

					if(slotNum == DONT)
					{
						slotNum = addFriendData(userNum);
					}

					xMail.xMailSlot[xMail.totalMailSlot].isRecvOk = FALSE;
					xMail.xMailSlot[xMail.totalMailSlot].friendDataSlotNum = slotNum;

					xMail.xMailSlot[xMail.totalMailSlot].type = array[i]["TYPE"].asInt();
					
					xMail.xMailSlot[xMail.totalMailSlot].giftType = array[i]["PRESENT_TYPE"].asInt();
					
					initSecurity(&xMail.xMailSlot[xMail.totalMailSlot].giftValue, array[i]["VALUE"].asInt());
					

					sprintf(xMail.xMailSlot[xMail.totalMailSlot].strText, "%s",array[i]["TEXT"] .asCString());

					sprintf(xMail.xMailSlot[xMail.totalMailSlot].strTime, "%s",array[i]["TIME"] .asCString());
					if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
						sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());
					sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
					xFriendData[slotNum].lv = array[i]["LEVEL"].asInt();
					xMail.totalMailSlot++;
				}												
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETSOUND_RECV:
		{
        array = root["SOUND"];
		for(int i=0;i<array.size();i++)
		{
			xSongSet.isSongOpen[array[i]["INDEX"].asInt()] = TRUE;
		}
			netSend(CMD_NOTICE, DONT);
		}
		break;
	case CMD_GETMAILLIST_RECV:			
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
				xMail.rowNum = root["ROWNUM"].asInt();
				if(xWorldMap.isFriendMap == FALSE)
				{
					if(xMail.selectTab == 0)
						xMail.mailLastKey = xSave.mailLastKey;
				}
				
                array = root["BOOK"];
				for(int i=0;i<array.size();i++)
				{
					xMail.xMailSlot[xMail.totalMailSlot].key = array[i]["KEY"].asInt();
					
					if(xWorldMap.isFriendMap == FALSE)
					{
						if(xMail.totalMailSlot == 0)
							if(xMail.selectTab == 0)
								xMail.mailLastKey = xMail.xMailSlot[xMail.totalMailSlot].key;
					}
					


					//유저넘버 슬롯번호 찾기
					int userNum = array[i]["USERNUM"].asInt();
					int slotNum = getFriendSlot(userNum);

					if(slotNum == DONT)
					{
						slotNum = addFriendData(userNum);
					}

					xMail.xMailSlot[xMail.totalMailSlot].friendDataSlotNum = slotNum;
					sprintf(xMail.xMailSlot[xMail.totalMailSlot].strText, "%s",array[i]["CONTENT"] .asCString());

					sprintf(xMail.xMailSlot[xMail.totalMailSlot].strTime, "%s",array[i]["TIME"] .asCString());

					if(xFriendData[slotNum].strUrl[0] == '0' || xFriendData[slotNum].strUrl[0] == 0)
						sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());
					sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
					if(xFriendData[slotNum].lv == 0)
						xFriendData[slotNum].lv = array[i]["LEVEL"].asInt();
					xMail.xMailSlot[xMail.totalMailSlot].isSecret = (array[i]["SECRET"].asInt() == 0?FALSE:TRUE);
					xMail.totalMailSlot++;								
				}
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETVOTELIST_RECV:
		{
        array = root["VOTE"];
		for(int i=0;i<array.size();i++)
		{
			addIsVote(array[i]["USERNUM"].asInt());
		}
		xNetGetModelMain.friendNum = xNetData.userNum;
		netSend(CMD_GETMODELMAIN, DONT);
		}
		break;
	case CMD_VOTE_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
		case 1:	//이미추천함
			break;
		case 2:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETFASHIONSHOWRANKINFO_RECV:
		{
		xFashionShowInfo.xRankSlot.rank = root["RANK"].asInt();
		xFashionShowInfo.xRankSlot.score = root["SCORE"].asInt();
		xFashionShowInfo.xRankSlot.vote = root["VOTE"].asInt();
					
		xFashionShowInfo.xRankSlot.totalModel = 0;
        array = root["MODEL"];
            
		for(int i=0;i<array.size();i++)
		{
			xFashionShowInfo.xRankSlot.modelCode[xFashionShowInfo.xRankSlot.totalModel] = array[i]["M_INDEX"].asInt();
			xFashionShowInfo.xRankSlot.modelUpgrade[xFashionShowInfo.xRankSlot.totalModel] = array[i]["UPGLADE"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[0] = array[i]["LAYED1"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[1] = array[i]["LAYED2"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[2] = array[i]["LAYED3"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[3] = array[i]["LAYED4"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[4] = array[i]["LAYED5"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[5] = array[i]["LAYED6"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[6] = array[i]["LAYED7"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[7] = array[i]["LAYED8"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[8] = array[i]["LAYED9"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[9] = array[i]["LAYED10"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[10] = array[i]["LAYED11"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[11] = array[i]["LAYED12"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[12] = array[i]["LAYED13"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[13] = array[i]["LAYED14"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[14] = array[i]["LAYED15"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].code[15] = array[i]["LAYED16"].asInt();
			xFashionShowInfo.xRankSlot.xF[xFashionShowInfo.xRankSlot.totalModel].isInFitting = array[i]["OUT"].asInt()==0?FALSE:TRUE;
			xFashionShowInfo.xRankSlot.totalModel++;
		}
		}
		break;
	case CMD_SETFASHIONSHOW_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xFashionShow.xMyRankSlot[1].rank = root["RANK"].asInt();
            xFashionShow.remainCount = root["COUNT"].asInt();
            
            if(xFashionShow.xMyRankSlot[1].rank < xFashionShow.bestRank)
            {
                xFashionShow.isRankChangeEvent = TRUE;
                xFashionShow.rankChangeAnyCnt = 0;
                //상대방 위치 찾기
                xEventQueueNet.slotNum[xEventQueueNet.totalNum] = (xFashionShow.xMyRankSlot[1].rank+1)/10;
                xEventQueueNet.action[xEventQueueNet.totalNum] = 1;
                addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GETFASHIONSHOWRANK, TRUE);
            }
            else
            {
                xFashionShow.state = FASHIONSHOW_STATE_RUNWAYRESULT;
            }
            break;
        default:
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
		break;
	case CMD_GETFASHIONSHOWRANK_RECV:
		{
			
		//0모든정보 1:랭킹정보(추가되는 랭킹페이지 전용)
		if(xNetFashionShowRank.request == 0)
		{
			sprintf(xFashionShow.strNoticeBar, "%s",root["TOP_STR"] .asCString());
			sprintf(xFashionShow.strNotice, "%s",root["NOTICE"] .asCString());
				
			xFashionShow.xMyRankSlot[xNetFashionShowRank.action].rank = root["RANK"].asInt();
			xFashionShow.xMyRankSlot[xNetFashionShowRank.action].score = root["SCORE"].asInt();
			xFashionShow.xMyRankSlot[xNetFashionShowRank.action].vote = root["VOTE"].asInt();
			xFashionShow.severNum = root["CAL_INDEX"].asInt();
			xFashionShow.xMyRankSlot[1].totalPeople = root["TOTAL_COUNT"].asInt();
			xFashionShow.isTodayFree = root["ADD_SHOW"].asInt() == 0?TRUE:FALSE;
            xFashionShow.remainCount = root["COUNT"].asInt();
            
            
				
			setFashionShow(xFashionShow.severNum);
			
            array = root["MODEL"];
			xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel = 0;
			for(int i=0;i<array.size();i++)
			{
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].modelCode[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel] = array[i]["M_INDEX"].asInt();
				
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].modelUpgrade[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel] = array[i]["UPGLADE"].asInt();
				
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[0] = array[i]["LAYED1"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[1] = array[i]["LAYED2"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[2] = array[i]["LAYED3"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[3] = array[i]["LAYED4"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[4] = array[i]["LAYED5"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[5] = array[i]["LAYED6"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[6] = array[i]["LAYED7"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[7] = array[i]["LAYED8"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[8] = array[i]["LAYED9"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[9] = array[i]["LAYED10"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[10] = array[i]["LAYED11"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[11] = array[i]["LAYED12"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[12] = array[i]["LAYED13"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[13] = array[i]["LAYED14"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[14] = array[i]["LAYED15"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].code[15] = array[i]["LAYED16"].asInt();
				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].xF[xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel].isInFitting = array[i]["OUT"].asInt()==0?FALSE:TRUE;

				xFashionShow.xMyRankSlot[xNetFashionShowRank.action].totalModel++;
			}
		}

		
        array = root["RANKING"];
            
		for(int i=0;i<array.size();i++)
		{
			if(xFashionShow.totalRankList[xNetFashionShowRank.action] < FASHIONSHOWRANKMAX-1)
			{
				//유저넘버 슬롯번호 찾기
				int userNum = array[i]["USERNUM"].asInt();
				int slotNum = getFriendSlot(userNum);
				
				if(slotNum == DONT)
				{
					slotNum = addFriendData(userNum);
				}
				
				if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
					sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());
				sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
				
				xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].userCode = userNum;
				xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].friendDataNum = slotNum;				
				xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].rank = xFashionShow.totalRankList[xNetFashionShowRank.action]+1;
				xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].score = array[i]["SCORE"].asInt();
				xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].vote = array[i]["VOTE"].asInt();
				xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].isVote = getIsVote(userNum);
								
				if(xFashionShow.isRankChangeEvent == TRUE)
				{
					if((xFashionShow.xMyRankSlot[1].rank+1)%10)
					{
						xFashionShow.xRankChangeSlot.rank = xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].rank;
						xFashionShow.xRankChangeSlot.score = xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].score;
						xFashionShow.xRankChangeSlot.vote = xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].vote;
						xFashionShow.xRankChangeSlot.userCode = xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].userCode;
						xFashionShow.xRankChangeSlot.friendDataNum = xFashionShow.xRankSlot[xNetFashionShowRank.action][xFashionShow.totalRankList[xNetFashionShowRank.action]].friendDataNum;
						xFashionShow.totalRankList[xNetFashionShowRank.action] = 0;
					}
					xFashionShow.state = FASHIONSHOW_STATE_RUNWAYRESULT;
				}
				xFashionShow.totalRankList[xNetFashionShowRank.action]++;
			}
		}
		}
		break;
	case CMD_GETFRIENDLIST_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
				switch(xNetFriendList.action)
				{
				case 0:	//친구리스트
					xFriend.nowRowNumList = root["ROWNUM"].asInt();
                    xFriend.totalFriend = root["FRIEND_MAX"].asInt();
					break;
				case 1:	//팔로잉
					xFriend.nowRowNumListFollow = root["ROWNUM"].asInt();
					break;
				}
                               
                array = root["FRIEND"];
				for(int i=0;i<array.size();i++)
				{
					//유저넘버 슬롯번호 찾기
					int userNum = array[i]["USERNUM"].asInt();
					int slotNum = getFriendSlot(userNum);

					if(slotNum == DONT)
					{
						slotNum = addFriendData(userNum);
					}
					if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
						sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());
					sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
					xFriendData[slotNum].lv = array[i]["LEVEL"].asInt();
					xFriendData[slotNum].todayVisit = array[i]["TODAY_VISIT"].asInt();
					xFriendData[slotNum].todayOrder = array[i]["TODAY_ORDER"].asInt();
					xFriendData[slotNum].friendState = array[i]["FRIEND_STATE"].asInt();
					xFriendData[slotNum].socialCount = array[i]["SOCIAL_COUNT"].asInt();
                    xFriendData[slotNum].loginDay = array[i]["LDATE"].asInt();
                    xFriendData[slotNum].isBookMark = array[i]["BOOKMARK"].asInt() == 0?false:true;
                    
                    
					switch(array[i]["TYPE"].asInt())
					{
					case 0:
						break;
					case 1:
						xFriendData[slotNum].isAlliance = TRUE;
						break;
					case 2:
						xFriendData[slotNum].isPM = TRUE;
						break;
					}
					
					xFriendData[slotNum].isVote = (array[i]["TODAY_VOTE"].asInt()==0?FALSE:TRUE);
					
					if(xFriendData[slotNum].strKakaoId[0] == 0 || xFriendData[slotNum].strKakaoId[0] == '0')
					{
						sprintf(xFriendData[slotNum].strKakaoId, "%s",array[i]["SID"] .asCString());
						xFriendData[slotNum].isKakao = checkKakaoFriend(xFriendData[slotNum].strKakaoId);
					}
					
					xFriendData[slotNum].sex = array[i]["SEX"].asInt();
							
                    
					switch(xNetFriendList.action)
					{
					case 0:	//친구리스트
                        xFriendData[slotNum].isAdd = TRUE;
                        if(xFriend.selectTabB == 0)
                        {
                            xFriend.dataSlotNumList[xFriend.totalNumList++] = slotNum;
                            //친구추가 버튼으로 사용하자
                            if(xFriend.totalNumList == 1)
                            {
                                xFriend.dataSlotNumList[xFriend.totalNumList++] = DONT;
                            }

                        }
                        else if(xFriend.selectTabB == 2)
                        {
                            if(xFriendData[slotNum].isBookMark == true)
                            {
                                xFriend.dataSlotNumList[xFriend.totalNumList++] = slotNum;
                            }
                        }
                        break;
					case 1:	//팔로잉
						xFriend.dataSlotNumListFollow[xFriend.totalNumListFollow++] = slotNum;
						break;
					}
				}
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_USERSOCIALLIST_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
                array = root["CLEAN"];
				for(int i=0;i<array.size();i++)
				{
					int bKey = array[i]["BKEY"].asInt();
					int sellTableNum = getSellTableInfo(bKey,xNetMySocialList.floor);
					int showWinDowNum = getShowWindowInfo(bKey,xNetMySocialList.floor);				

					if(sellTableNum != DONT)
					{
						if(xSellTableInfo[xNetMySocialList.floor][sellTableNum].totalSocialSlot < 3)
						{
							//유저넘버 슬롯번호 찾기
							int userNum = array[i]["FRIEND_USERNUM"].asInt();
							int slotNum = getFriendSlot(userNum);

							if(slotNum == DONT)
							{
								slotNum = addFriendData(userNum);
							}

							if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
								sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());

							sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
                            
                            
                            if(xWorldMap.isFriendMap == false)
                                addHelpList(userNum);
                            
                            

							xSellTableInfo[xNetMySocialList.floor][sellTableNum].xSocialSlot[xSellTableInfo[xNetMySocialList.floor][sellTableNum].totalSocialSlot].friendDataSlotNum = slotNum;
							xSellTableInfo[xNetMySocialList.floor][sellTableNum].xSocialSlot[xSellTableInfo[xNetMySocialList.floor][sellTableNum].totalSocialSlot].cleanKey = array[i]["CKEY"].asInt();
							xSellTableInfo[xNetMySocialList.floor][sellTableNum].xSocialSlot[xSellTableInfo[xNetMySocialList.floor][sellTableNum].totalSocialSlot].interiorKey = bKey;
							xSellTableInfo[xNetMySocialList.floor][sellTableNum].totalSocialSlot++;
							
						}
					}
					else if(showWinDowNum != DONT)
					{
						if(xShowWindowInfo[xNetMySocialList.floor][showWinDowNum].totalSocialSlot < 1)
						{
							//유저넘버 슬롯번호 찾기
							int userNum = array[i]["FRIEND_USERNUM"].asInt();
							int slotNum = getFriendSlot(userNum);

							if(slotNum == DONT)
							{
								slotNum = addFriendData(userNum);
							}
														
							if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
								sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());

							sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
							
                            if(xWorldMap.isFriendMap == false)
                                addHelpList(userNum);

							xShowWindowInfo[xNetMySocialList.floor][showWinDowNum].xSocialSlot[xShowWindowInfo[xNetMySocialList.floor][showWinDowNum].totalSocialSlot].friendDataSlotNum = slotNum;
							xShowWindowInfo[xNetMySocialList.floor][showWinDowNum].xSocialSlot[xShowWindowInfo[xNetMySocialList.floor][showWinDowNum].totalSocialSlot].cleanKey = array[i]["CKEY"].asInt();
							xShowWindowInfo[xNetMySocialList.floor][showWinDowNum].xSocialSlot[xShowWindowInfo[xNetMySocialList.floor][showWinDowNum].totalSocialSlot].interiorKey = bKey;
							xShowWindowInfo[xNetMySocialList.floor][showWinDowNum].totalSocialSlot++;
						}
					}
				}
			}
                
            xNetMySocialList.isEventQueue = false;
            for(int k=0;k<xEventQueueNet.totalNum;k++)
            {
                if(xEventQueueNet.type[k] == NETQUEUE_TYPE_SOCIALLIST)
                {
                    xNetMySocialList.isEventQueue = true;
                    break;
                }
            }
                
            if(xWorldMap.isMyShopRefreshNet == true)
            {
                if(xNetMySocialList.floor >= 1)
                    xWorldMap.isMyShopRefreshNet = false;
            }
            else
            {
                if(xNetMySocialList.floor >= 2)
                {
                    if(xWorldMap.isFriendMap == TRUE)
                        xFriendMap.isLoadingOk = TRUE;
                    else
                        netSend(CMD_GETQUEST, DONT);
                }
                else
                {
                    ++xNetMySocialList.floor;
                    if(xWorldMap.isFriendMap == FALSE)
                        xNetMySocialList.userNum = xNetData.userNum;
                    else
                        xNetMySocialList.userNum = xFriendData[xFriendMap.selectDataSlotNum].userNum;
                    
                    netSend(CMD_USERSOCIALLIST, DONT);
                }
            }
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETORDER_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
				xOrder.isNetLoad = TRUE;
				
                array = root["ORDER"];
				xOrder.totalNumListDataFriend = 0;
				xOrder.totalNumListData = 0;
				
				
				
				for(int i=0;i<array.size();i++)
				{
					if(xWorldMap.isFriendMap == TRUE)
					{
						xOrder.xSlotListDataFriend[xOrder.totalNumListDataFriend].state = array[i]["STATE"].asInt();
						xOrder.xSlotListDataFriend[xOrder.totalNumListDataFriend].code = array[i]["ITEM_INDEX"].asInt();
						xOrder.xSlotListDataFriend[xOrder.totalNumListDataFriend].key = array[i]["KEY"].asInt();
						xOrder.xSlotListDataFriend[xOrder.totalNumListDataFriend].friendType = array[i]["TYPE"].asInt();
						
						int userNum = array[i]["USERNUM"].asInt();
						int slotNum = getFriendSlot(userNum);

						if(slotNum == DONT)
						{
							slotNum = addFriendData(userNum);
						}

						if(xOrder.xSlotListDataFriend[xOrder.totalNumListDataFriend].friendType == 0)
						{
							if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
								sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["URL"] .asCString());
							
							
							sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
						}


						xOrder.xSlotListDataFriend[xOrder.totalNumListDataFriend].friendNum = slotNum;
						xOrder.xSlotListDataFriend[xOrder.totalNumListDataFriend++].endTime = array[i]["TIME"].asInt();

					}
					else
					{
						xOrder.xSlotListData[xOrder.totalNumListData].state = array[i]["STATE"].asInt();
						xOrder.xSlotListData[xOrder.totalNumListData].code = array[i]["ITEM_INDEX"].asInt();
						xOrder.xSlotListData[xOrder.totalNumListData].key = array[i]["KEY"].asInt();
						xOrder.xSlotListData[xOrder.totalNumListData].friendType = array[i]["TYPE"].asInt();

						int userNum = array[i]["USERNUM"].asInt();
                        
                        
						int slotNum = getFriendSlot(userNum);

						if(slotNum == DONT)
						{
							slotNum = addFriendData(userNum);
						}

						if(xOrder.xSlotListData[xOrder.totalNumListData].friendType == 0)
						{
							if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
								sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["URL"] .asCString());
							sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
						}

						xOrder.xSlotListData[xOrder.totalNumListData].friendNum = slotNum;					
						xOrder.xSlotListData[xOrder.totalNumListData++].endTime = array[i]["TIME"].asInt();
					}

					//유저넘버 등록
					if(array[i]["TYPE"].asInt() == 0)
					{
						int userNum = array[i]["USERNUM"].asInt();
						int slotNum = getFriendSlot(userNum);

						if(slotNum == DONT)
						{
							slotNum = addFriendData(userNum);
						}
						if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
							sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["URL"] .asCString());
						sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
						sprintf(xFriendData[slotNum].strKakaoId, "%s",array[i]["SID"] .asCString());
					}
				}
				setOrderList();
			}				
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETGAMEDATA_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			for(int carNum=0;carNum<3;carNum++)
			{
				xCarPark[carNum].state = 0;
				xCarPark[carNum].carNum = DONT;
				xCarPark[carNum].endTime = 0;
				xCarPark[carNum].orderKey = 0;
			}

			if(xWorldMap.isFriendMap == FALSE)
			{                
                xPrePay.isRecv = root["FIXEDCHARGE_STATE"].asInt()==0?true:false;
                xPrePay.remainDay = root["FIXEDCHARGE_DAY"].asInt();
                
				xSaveTemp.sex = root["SEX"].asInt();
				xSaveTemp.age = root["AGE"].asInt();
				xSaveTemp.friendNum = root["FRIENDS"].asInt();
				xSaveTemp.area = root["ZONE"].asInt();
                
                
                xClub.xMy.clubKey = root["CLUB_NUM"].asInt();

                
                

				//xModel.totalInventoryModelMax = root["MODEL_SLOT"].asInt();
                xModel.totalInventoryModelMax = 100;

				sprintf(xSaveTemp.strNickName		,"%s",root["NICKNAME"] .asCString());

				initSecurity(&xSaveTemp.lv,root["LEVEL"].asInt());
				initSecurity(&xSaveTemp.money,root["GOLD"].asInt());
				initSecurity(&xSaveTemp.cash,root["CASH"].asInt());				
				initSecurity(&xSaveTemp.exp,root["EXP"].asInt());				
				initSecurity(&xSaveTemp.tired,root["CANDY"].asInt());
				xSaveTemp.tiredTime = root["CANDY_TIME"].asInt();
				initSecurity(&xSaveTemp.fame,root["FAME"].asInt());
                
                initSecurity(&xSaveTemp.mileage,root["MILEAGE"].asInt());
                
                

				sprintf(xSaveTemp.profileUrl	,"%s",root["PROFILE_URL"] .asCString());	//닉네임
				if(xSaveTemp.profileUrl[0] == '0')
					xProfile.isPhoto = FALSE;
				else
					xProfile.isPhoto = TRUE;
				
				//유저넘버 슬롯번호 찾기
				int userNum = xNetData.userNum;
				int slotNum = getFriendSlot(userNum);
				
				if(slotNum == DONT)
				{
					slotNum = addFriendData(userNum);
				}
				
				if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
					sprintf(xFriendData[slotNum].strUrl, "%s",xSaveTemp.profileUrl);
				xFriendData[slotNum].sex = xSaveTemp.sex;
				xFriendData[slotNum].age = xSaveTemp.age;
				
				
				xSaveTemp.orderAmDay = root["NPC_AM"].asInt();
				xSaveTemp.orderPmDay = root["NPC_PM"].asInt();
				xSaveTemp.trendAmDay = root["TRAND_AM"].asInt();
				xSaveTemp.trendPmDay = root["TRAND_PM"].asInt();
				
				
				xSaveTemp.socialDay = root["ITEM_TIME"].asInt();
				xSaveTemp.socialItem[0] = root["ITEM_INDEX1"].asInt();
				xSaveTemp.socialItem[1] = root["ITEM_INDEX2"].asInt();
				
				
				xAccessBonus.accessDay = root["COME_TIME"].asInt();
				xAccessBonus.accessCount = root["COME_DAY"].asInt();
				
				xSaveTemp.socialHelpCnt = (49+xSaveTemp.lv.oriData)-root["TODAY_HELP"].asInt();
                
                
                
                
                
                
                

                
                
								
				xSaveTemp.friendOrderNum = root["ORDER_COUNT"].asInt();
				
				
				for(int i=0;i<CARDATAMAX;i++)
					xCar.isOpen[i] = FALSE;
				{
                    array = root["CAR"];
					for(int i=0;i<array.size();i++)
						xCar.isOpen[array[i]["CAR_INDEX"].asInt()] = TRUE;
				}
				
				
							
				
				{
					for(int i=0;i<12;i++)
					{
						int type = i/6;
						int slot = i%6;
						xProductionMenu.isOpen[type][slot] = FALSE;
						xProductionMenu.state[type][slot] = PRODUCTIONMENUSLOT_STATE_WAIT;
						xProductionMenu.slotCode[type][slot] = DONT;
					}
                    
                    array = root["SLOT"];

										
					for(int i=0;i<array.size();i++)
					{
						int slotTemp = array[i]["SLOT"].asInt();
						int type = slotTemp/ 6;
						int slot = slotTemp%6;
						
						xProductionMenu.isOpen[type][slot] = array[i]["OPEN"].asInt()==0?FALSE:TRUE;
						xProductionMenu.isFriend[type][slot] = array[i]["TYPE"].asInt()==0?FALSE:TRUE;
						xProductionMenu.orderKey[type][slot] = array[i]["KEY"].asInt();
						
//						switch(array[i]["STATE"].asInt())
//						{
//							case 0:		//비생산중
//								xProductionMenu.slotCode[type][slot] = DONT;
//								xProductionMenu.state[type][slot] = PRODUCTIONMENUSLOT_STATE_WAIT;
//								break;
//							case 1:		//생산중
//								xProductionMenu.slotCode[type][slot] = array[i]["ITEM_INDEX"].asInt();
//								xProductionMenu.state[type][slot] = PRODUCTIONMENUSLOT_STATE_WAIT;
//								break;
//						}
						xProductionMenu.slotCode[type][slot] = array[i]["ITEM_INDEX"].asInt();
						xProductionMenu.state[type][slot] = PRODUCTIONMENUSLOT_STATE_WAIT;
						
						xProductionMenu.slotFlowTime[type][slot] = array[i]["START_TIME"].asInt();
						xProductionMenu.minigameBonus[type][slot] = array[i]["BONUS"].asInt();
					}
				}
				
				{
                    array = root["SIDE"];
					for(int i=0;i<array.size();i++)
						xExternalWallData.isOpen[array[i]["SIDE_INDEX"].asInt()] = TRUE;
				}
				
				xSaveTemp.socialModelVoteCnt = 10-root["TODAY_VOTE"].asInt();
				xMiniGame.playCount = root["CANDY_COUNT"].asInt();
				xModel.newModelCountNum = root["MODEL_COUNT"].asInt();
			}
			else
			{
				xFriendMap.fame = root["FAME"].asInt();
				xFriendMap.lv = root["LEVEL"].asInt();
				xFriendData[xFriendMap.selectDataSlotNum].lv = xFriendMap.lv;
                xFriendData[xFriendMap.selectDataSlotNum].loginFlowTime = root["UPDATETIME"].asInt();
				
				sprintf(xFriendData[xFriendMap.selectDataSlotNum].strNickName	,"%s",root["NICKNAME"] .asCString());
				if(xFriendData[xFriendMap.selectDataSlotNum].strUrl[0] == 0 || xFriendData[xFriendMap.selectDataSlotNum].strUrl[0] == '0')
					sprintf(xFriendData[xFriendMap.selectDataSlotNum].strUrl, "%s",root["PROFILE_URL"] .asCString());
				
				xFriendData[xFriendMap.selectDataSlotNum].age = root["AGE"].asInt();
			}
								
			sprintf(xMail.strToday		,"%s",root["TODAY"] .asCString());

			xMap.isOpen[0] = root["FLOOR2"].asInt() == 0?FALSE:TRUE;
			xMap.isOpen[1] = root["FLOOR3"].asInt() == 0?FALSE:TRUE;
			xMap.extension = root["EXTEND"].asInt();
			xMap.tileInitW = root["EXTEND_WIDTH"].asInt();
			xMap.tileInitH = root["EXTEND_HEIGHT"].asInt();

				
			xExternalWall.selectWall = root["SIDE_INDEX"].asInt();
			xSongSet.selectSong = root["SOUND"].asInt();
			

			{
                array = root["PARKING"];
				for(int i=0;i<array.size();i++)
				{
					int slot = array[i]["SLOT"].asInt();
					xCarPark[slot].state = array[i]["STATE"].asInt();
					xCarPark[slot].carNum = array[i]["CAR_INDEX"].asInt();
					xCarPark[slot].endTime = array[i]["START_TIME"].asInt();
					xCarPark[slot].orderKey = array[i]["KEY"].asInt();
				}
			}


				
			if(xWorldMap.isFriendMap == TRUE)
				xFriendMap.isLoadingOk = TRUE;
			else
			{
				if(xMainMenu.initCnt >= 2)
				{
					netSend(CMD_GETEVENT, DONT);
				}
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETFASHION_RECV:
			
		if(xInventoryFashion.haveNum[0][13] > 0)
			printf(">>>%d\n",xInventoryFashion.haveNum[0][13]);
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{

                array = root["ITEM"];

				for(int i=0;i<array.size();i++)
				{
					int code = array[i]["ITEM_INDEX"].asInt();
					int rever = code < 0?1:0;
					int type = code/1000;
					int list = code%1000;
					type = rever==0?type:-type;
					list = rever==0?list:-list;

					if(xWorldMap.isFriendMap == TRUE)
					{
						int minLv = xSaveTemp.lv.oriData <= xFriendData[xFriendMap.selectDataSlotNum].lv?xSaveTemp.lv.oriData:xFriendData[xFriendMap.selectDataSlotNum].lv;

						if(xInventoryFashion.isOpen[type][list] == TRUE && minLv >= xFashionData[type][list].lv && xFashionData[type][list].isStaff == 0)
						{							
							xCatalog.xSlotFriendOrder[type][xCatalog.totalSlotFriendOrder[type]++].code = code;
						}
						
					}
					else
					{
						xInventoryFashion.isOpen[type][list] = TRUE;
						xInventoryFashion.haveNum[type][list] = array[i]["ITEM_COUNT"].asInt();
					}
				}

				if(xWorldMap.isFriendMap == TRUE)
				{
					for(int t=0;t<CATALOGSLOTBMAX;t++)
					{
						xCatalog.totalSlotFriendOrderTemp[t] = 0;
						for(int s=xCatalog.totalSlotFriendOrder[t]-1;s>=0;s--)
						{
							xCatalog.xSlotFriendOrderTemp[t][xCatalog.totalSlotFriendOrderTemp[t]++] = xCatalog.xSlotFriendOrder[t][s];
						}
					}
					
					for(int t=0;t<CATALOGSLOTBMAX;t++)
					{
						for(int s=xCatalog.totalSlotFriendOrder[t]-1;s>=0;s--)
						{
							xCatalog.xSlotFriendOrder[t][s] = xCatalog.xSlotFriendOrderTemp[t][s];
						}
					}
				}
			}

			if(fashionNum < NETFASHIONMAX-1)
			{
                fashionNum += 1;
				netSend(CMD_GETFASHION, fashionNum);
			}
			else
			{
				if(xWorldMap.isFriendMap == TRUE)
				{
					setFriendOrderTab();
				}
				else
				{
					netSend(CMD_GETINTERIOR, DONT);
				}
			}
			
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;

	case CMD_GETINTERIOR_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
                array = root["ITEM"];


				xInventoryInterior.totalNum = 0;
				for(int i=0;i<array.size();i++)
				{
					int code = array[i]["ITEM_INDEX"].asInt();
					int count = array[i]["ITEM_COUNT"].asInt();

					int rever = code < 0?1:0;
					int type = code/1000;
					int list = code%1000;
					type = rever==0?type:-type;
					list = rever==0?list:-list;

					for(int c=0;c<count;c++)
						inputInventoryInterior(code);
				}
								

				////////////////////////////////////////////
				xNetGetMap.userNum = xNetData.userNum;
				xNetGetMap.action = 0;	//0:내매장1:친구매장
				xNetGetMap.friendNum = 0;
				netSend(CMD_GETMAP, 0);
                netSend(CMD_FORMERLISTUPDATE,0);
				///////////////////////////////////////////
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETMAP_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			if(xMap.tileInitW < 8)
				xMap.tileInitW = 8;
			if(xMap.tileInitH < 8)
				xMap.tileInitH = 8;
				
			xMap.wallInitCode[floorNum] = root["WALL"].asInt();
			xMap.floorInitCode[floorNum] = root["BOTTOM"].asInt();
				
			for(int x=-1;x<15;x++)
			{
				for(int y=-1;y<15;y++)
				{
					if(x>=0 && y>=0)
					{
						if(floorNum != 0 || (x < xMap.tileInitW && y < xMap.tileInitH))
							xMap.data[floorNum][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y] = xMap.floorInitCode[floorNum];
						else
							xMap.data[floorNum][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y] = FLOORTILEINITCODE;
					}
					xMap.data[floorNum][MAP_TYPE_FLOORTILE1][xMap.shopPointX+x][xMap.shopPointY+y] = 0;
					
					if(x==-1 || y==-1)
					{
						if(x==-1)
						{
							xMap.data[floorNum][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY+y] = xMap.wallInitCode[floorNum];
						}
						else
						{
							xMap.data[floorNum][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY+y] = -xMap.wallInitCode[floorNum];
						}
					}
					xMap.data[floorNum][MAP_TYPE_WALL1][xMap.shopPointX+x][xMap.shopPointY+y] = 0;
					xMap.data[floorNum][MAP_TYPE_OBJ][xMap.shopPointX+x][xMap.shopPointY+y] = 0;

					xMap.dataKey[floorNum][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y] = 0;
					xMap.dataKey[floorNum][MAP_TYPE_FLOORTILE1][xMap.shopPointX+x][xMap.shopPointY+y] = 0;
					xMap.dataKey[floorNum][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY+y] = 0;
					xMap.dataKey[floorNum][MAP_TYPE_WALL1][xMap.shopPointX+x][xMap.shopPointY+y] = 0;
					xMap.dataKey[floorNum][MAP_TYPE_OBJ][xMap.shopPointX+x][xMap.shopPointY+y] = 0;
				}
			}
			
			{
                array = root["BATCH"];
				for(int i=0;i<array.size();i++)
				{
					int code = array[i]["B_ITEM_INDEX"].asInt();
					int key = array[i]["KEY"].asInt();
					int x = array[i]["X"].asInt();
					int y = array[i]["Y"].asInt();

					int rever = code < 0?1:0;
					int type = code/1000;
					int list = code%1000;
					type = rever==0?type:-type;
					list = rever==0?list:-list;

					if(xFloorWallTileErrQueue.isOneLoop == FALSE)
					{
						switch(type)
						{
						case INTERIOR_TYPE_FLOORTILE:			//타일
							//바닥지,또는 벽지인데 중복되는 위치에 값이 있다면 큐를 만들어 나중에 인벤에 넣어주고 해당 key는 삭제해주자
							if(xMap.data[floorNum][MAP_TYPE_FLOORTILE0][x][y] != 0 && xMap.dataKey[floorNum][MAP_TYPE_FLOORTILE0][x][y] != 0)
							{
								if(xFloorWallTileErrQueue.totalNum < FLOORWALLTILEERRQUEUEMAX-10)
								{
									xFloorWallTileErrQueue.code[xFloorWallTileErrQueue.totalNum] = xMap.data[floorNum][MAP_TYPE_FLOORTILE0][x][y];
									xFloorWallTileErrQueue.key[xFloorWallTileErrQueue.totalNum] = xMap.dataKey[floorNum][MAP_TYPE_FLOORTILE0][x][y];
									xFloorWallTileErrQueue.floor[xFloorWallTileErrQueue.totalNum] = floorNum;
									xFloorWallTileErrQueue.x[xFloorWallTileErrQueue.totalNum] = x;
									xFloorWallTileErrQueue.y[xFloorWallTileErrQueue.totalNum] = y;
									xFloorWallTileErrQueue.totalNum++;
								}
							}
							break;
						case INTERIOR_TYPE_WALLTILE:			//벽타일
							if(xMap.data[floorNum][MAP_TYPE_WALL0][x][y] != 0 && xMap.dataKey[floorNum][MAP_TYPE_WALL0][x][y] != 0)
							{
								if(xFloorWallTileErrQueue.totalNum < FLOORWALLTILEERRQUEUEMAX-10)
								{
									xFloorWallTileErrQueue.code[xFloorWallTileErrQueue.totalNum] = xMap.data[floorNum][MAP_TYPE_WALL0][x][y];
									xFloorWallTileErrQueue.key[xFloorWallTileErrQueue.totalNum] = xMap.dataKey[floorNum][MAP_TYPE_WALL0][x][y];
									xFloorWallTileErrQueue.floor[xFloorWallTileErrQueue.totalNum] = floorNum;
									xFloorWallTileErrQueue.x[xFloorWallTileErrQueue.totalNum] = x;
									xFloorWallTileErrQueue.y[xFloorWallTileErrQueue.totalNum] = y;
									xFloorWallTileErrQueue.totalNum++;
								}
							}
							break;
						}
					}
					
					switch(type)
					{
					case INTERIOR_TYPE_FLOORTILE:			//타일
						xMap.data[floorNum][MAP_TYPE_FLOORTILE0][x][y] = code;
						xMap.dataKey[floorNum][MAP_TYPE_FLOORTILE0][x][y] = key;
						break;
					case INTERIOR_TYPE_OBJFLOOR:			//타일
						xMap.data[floorNum][MAP_TYPE_FLOORTILE1][x][y] = code;
						xMap.dataKey[floorNum][MAP_TYPE_FLOORTILE1][x][y] = key;
						break;
					case INTERIOR_TYPE_WALLTILE:			//벽타일
						xMap.data[floorNum][MAP_TYPE_WALL0][x][y] = code;
						xMap.dataKey[floorNum][MAP_TYPE_WALL0][x][y] = key;
						break;
					case INTERIOR_TYPE_WALLITEM:			//벽장식
					case INTERIOR_TYPE_DOOR:				//문
					case INTERIOR_TYPE_SHOWWINDOW:			//쇼윈도
						xMap.data[floorNum][MAP_TYPE_WALL1][x][y] = code;
						xMap.dataKey[floorNum][MAP_TYPE_WALL1][x][y] = key;
							
						break;
					default:
						xMap.data[floorNum][MAP_TYPE_OBJ][x][y] = code;
						xMap.dataKey[floorNum][MAP_TYPE_OBJ][x][y] = key;
                            
                        
                            
						break;
					}
				}
			}
			
				
			xFloorWallTileErrQueue.isOneLoop = TRUE;
							
				
				
				
				
			for(int z=0;z<SELLTABLEINFOMAX;z++)
			{
				xSellTableInfo[floorNum][z].isUse = FALSE;
				xSellTableInfo[floorNum][z].totalSocialSlot = 0;
				for(int i=0;i<SELLSLOTMAX;i++)
					xSellTableInfo[floorNum][z].xSlot[i].code = DONT;
			}

			//진열대 정보
			{
                array = root["DP"];

				for(int i=0;i<array.size();i++)
				{
					int resetCode = addSellTableInfo(array[i]["KEY"].asInt(),floorNum);	//배치키

					for(int k=0;k<6;k++)
					{
                        char strTempKey[128];
                        sprintf(strTempKey,"D_ITEM_INDEX_%d",k);
						xSellTableInfo[floorNum][resetCode].xSlot[k].code =	array[i][strTempKey].asInt();		//아이템인텍스
                        
                        sprintf(strTempKey,"COUNT_%d",k);
						xSellTableInfo[floorNum][resetCode].xSlot[k].maxNum =array[i][strTempKey].asInt();				//진열수량
                        
                        sprintf(strTempKey,"SELL_COUNT_%d",k);
						xSellTableInfo[floorNum][resetCode].xSlot[k].num =array[i][strTempKey].asInt();		//판매완료수량
                        
                        sprintf(strTempKey,"START_TIME_%d",k);
						xSellTableInfo[floorNum][resetCode].xSlot[k].flowTime =	array[i][strTempKey].asInt();
                        //판매시작시간(판매수량이 생길떄마다 갱신해주자)
                        
                        xSellTableInfo[floorNum][resetCode].isSocial = array[i]["CLEAN"].asInt()==0?FALSE:TRUE;
					}

					//array[i]["CLEAN"].asInt();			//친구
					//array[i]["PROFILE_URL"].asInt();		//친구
				}
			}

			//피팅 정보
			if(xWorldMap.isInitLoading == FALSE)
			{
				for(int ss=0;ss<SHOWWINDOWINFOMAX;ss++)
				{
					xShowWindowInfo[floorNum][ss].isUse = FALSE;
					xShowWindowInfo[floorNum][ss].totalSocialSlot = 0;
				}
			}
                
			xWorldMap.isInitLoading = FALSE;
			{
                
                array = root["FITING_1"];
                
				for(int i=0;i<array.size();i++)
				{
					int resetCode =  addShowWindowInfo(array[i]["KEY"].asInt(), floorNum);	//배치키

					xShowWindowInfo[floorNum][resetCode].gender = array[i]["SEX"].asInt();
					xShowWindowInfo[floorNum][resetCode].isSocial = array[i]["CLEAN"].asInt()==0?FALSE:TRUE;

					for(int k=0;k<16;k++)
                    {
                        char strArrTemp[128];
                        sprintf(strArrTemp,"LAYER%d",k);
						xShowWindowInfo[floorNum][resetCode].xF.code[k] = array[i][strArrTemp].asInt();
                    }
					
					xShowWindowInfo[floorNum][resetCode].xF.isInFitting = array[i]["OUT"].asInt()==0?FALSE:TRUE;
				}
			}

			//스태프 정보
			{
                array = root["FITING_2"];

				for(int i=0;i<array.size();i++)
				{
					switch(array[i]["TYPE"].asInt())
					{
					case 0:	//판매
						sprintf(xPaymentAssistant[floorNum].strName		,"%s",array[i]["NICKNAME"] .asCString());	//닉네임
						xPaymentAssistant[floorNum].gender = array[i]["SEX"].asInt();

						for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
							xPaymentAssistant[floorNum].xF.code[ff] = DONT;

						for(int k=0;k<6;k++)
						{
                            char strArrTemp[128];
                            sprintf(strArrTemp,"LAYER%d",k);
                            
							if(array[i][strArrTemp].asInt() != DONT)
							{
								switch(k)
								{
								case 0:	//머리
									xPaymentAssistant[floorNum].xFace.hairNum = array[i][strArrTemp].asInt();
									break;
								case 1:	//표정
									xPaymentAssistant[floorNum].xFace.faceNum = array[i][strArrTemp].asInt();
									break;
								case 2:	//상의
								case 3:	//하의
								case 4:	//원피스
								case 5:	//신발
									setMapData(array[i][strArrTemp].asInt());
									xPaymentAssistant[floorNum].xF.code[xFashionData[xMap.type][xMap.listNum].layer] = xMap.type*1000+xMap.listNum;
									break;
								}
							}
						}
						xPaymentAssistant[floorNum].xF.isInFitting = array[i]["OUT"].asInt()==0?FALSE:TRUE;

						break;
					case 1:	//응대
						sprintf(xShopAssistant[floorNum][0].strName		,"%s",array[i]["NICKNAME"] .asCString());	//닉네임
						xShopAssistant[floorNum][0].gender = array[i]["SEX"].asInt();

						for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
							xShopAssistant[floorNum][0].xF.code[ff] = DONT;

						for(int k=0;k<6;k++)
						{
                            char strArrTemp[128];
                            sprintf(strArrTemp,"LAYER%d",k);
                            
							if(array[i][strArrTemp].asInt() != DONT)
							{
								switch(k)
								{
								case 0:	//머리
									xShopAssistant[floorNum][0].xFace.hairNum = array[i][strArrTemp].asInt();
									break;
								case 1:	//표정
									xShopAssistant[floorNum][0].xFace.faceNum = array[i][strArrTemp].asInt();
									break;
								case 2:	//상의
								case 3:	//하의
								case 4:	//원피스
								case 5:	//신발
									setMapData(array[i][strArrTemp].asInt());
									xShopAssistant[floorNum][0].xF.code[xFashionData[xMap.type][xMap.listNum].layer] = xMap.type*1000+xMap.listNum;
									break;
								}								
							}
						}
						xShopAssistant[floorNum][0].xF.isInFitting = array[i]["OUT"].asInt()==0?FALSE:TRUE;
						break;
					}
				}
			}

			if(floorNum < NETFLOORMAX-1)
			{
				netSend(CMD_GETMAP, floorNum+1);
			}
			else
			{
				if(xWorldMap.isFriendMap == TRUE)
					xFriendMap.isLoadingOk = TRUE;
				else
					netSend(CMD_GETFACE, DONT);
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}		
		break;
	case CMD_SETMODEL_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			if(xNetSetModel.state == 0)		//신규일때
			{
				xInventoryModel[xNetSetModel.slotNum].key = root["KEY"].asInt();
			}
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_SETMAP_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
				int key =root["KEY"].asInt();
				setMapData(xNetMap.code);
                isSubTemp[1]=FALSE;
				if(xNetMap.action != 1)
				{
					switch(xMap.type)
					{
					case INTERIOR_TYPE_FLOORTILE:			//타일
						xMap.dataKey[xNetMap.floor][MAP_TYPE_FLOORTILE0][xNetMap.mapX][xNetMap.mapY] = key;
						break;
					case INTERIOR_TYPE_OBJFLOOR:
						xMap.dataKey[xNetMap.floor][MAP_TYPE_FLOORTILE1][xNetMap.mapX][xNetMap.mapY] = key;
						break;
					case INTERIOR_TYPE_WALLTILE:			//벽타일
						xMap.dataKey[xNetMap.floor][MAP_TYPE_WALL0][xNetMap.mapX][xNetMap.mapY] = key;
						break;
					case INTERIOR_TYPE_WALLITEM:			//벽장식
					case INTERIOR_TYPE_DOOR:				//문
					case INTERIOR_TYPE_SHOWWINDOW:			//쇼윈도
						xMap.dataKey[xNetMap.floor][MAP_TYPE_WALL1][xNetMap.mapX][xNetMap.mapY] = key;
						break;
					default:
						xMap.dataKey[xNetMap.floor][MAP_TYPE_OBJ][xNetMap.mapX][xNetMap.mapY] = key;
						break;
					}
				}			

				//0:신규1:업데이트2:삭제
				if(xNetMap.action == 0)
				{
					switch(xMap.type)
					{
					case INTERIOR_TYPE_SHOWWINDOW:		//쇼윈도
						addShowWindowInfo(key,xNetMap.floor);
						/////////////////////////////////////////////////////////////////////////////
						xEventQueueNet.floor[xEventQueueNet.totalNum] = xNetMap.floor;
						xEventQueueNet.key[xEventQueueNet.totalNum] = key;
						for(int k=0;k<16;k++)
							xEventQueueNet.layer[xEventQueueNet.totalNum][k] = DONT;
						
						
						xEventQueueNet.open[xEventQueueNet.totalNum] = 0;

							
						if(xMainMenu.initCnt < 99)
						{
							xNetShowWindow.floor = xEventQueueNet.floor[xEventQueueNet.totalNum];
							xNetShowWindow.key = xEventQueueNet.key[xEventQueueNet.totalNum];
							xNetShowWindow.sex = xEventQueueNet.sex[xEventQueueNet.totalNum];
							xNetShowWindow.inFitting = xEventQueueNet.open[xEventQueueNet.totalNum];
							for(int k=0;k<16;k++)
								xNetShowWindow.layer[k] = xEventQueueNet.layer[xEventQueueNet.totalNum][k];
							netSend(CMD_SETSHOWWINDOW, DONT);
							xMainMenu.isInitNet = FALSE;
						}
						else
						{
							addEventQueueNet(0, 0, NETQUEUE_TYPE_SHOWWINDOW, TRUE);
							/////////////////////////////////////////////////////////////////////////////
						}
						break;
					case INTERIOR_TYPE_HANGER:
					case INTERIOR_TYPE_ACCESSORY:

						addSellTableInfo(key,xNetMap.floor);

						////////////////////////////////////////////////////////////////////////////
						xEventQueueNet.floor[xEventQueueNet.totalNum] = xNetMap.floor;
						xEventQueueNet.key[xEventQueueNet.totalNum] =  key;
						for(int k=0;k<9;k++)
						{
							xEventQueueNet.xSellSlot[xEventQueueNet.totalNum][k].code = DONT;
							xEventQueueNet.xSellSlot[xEventQueueNet.totalNum][k].num = 0;
							xEventQueueNet.xSellSlot[xEventQueueNet.totalNum][k].maxNum = 0;
							xEventQueueNet.xSellSlot[xEventQueueNet.totalNum][k].flowTime = 0;
						}
														
						if(xMainMenu.initCnt < 99)
						{
							xNetSellTable.floor = xEventQueueNet.floor[xEventQueueNet.totalNum];
							xNetSellTable.key = xEventQueueNet.key[xEventQueueNet.totalNum];
							memcpy(&xNetSellTable.xSellSlot, &xEventQueueNet.xSellSlot[xEventQueueNet.totalNum], sizeof(xNetSellTable.xSellSlot));
							netSend(CMD_SETSELLTABLE, DONT);
							xMainMenu.isInitNet = FALSE;
						}
						else
						{
							addEventQueueNet(0, 0, NETQUEUE_TYPE_SELLTABLE, TRUE);
							/////////////////////////////////////////////////////////////////////////////
						}
						break;
					}
				}
			}
            netSend(CMD_FORMERLISTUPDATE,DONT);
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
        case 2:
            netSend(CMD_FORMERLISTUPDATE,DONT);
            break;
        case 3:
            setPopup(POPUP_NONFORMER, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            netSend(CMD_FORMERLISTUPDATE,DONT);
            break;
		}
		break;
	case CMD_ADDFRIEND_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
		case 1:	//이미등록된친구성공
			break;
		case 2:	//친구등록 100개 초과
			{
			int slotNum = getFriendSlot(xNetAddFriend.friendNum);
			
			if(slotNum != DONT)
			{
				xFriendData[slotNum].isAdd = FALSE;
			}
				
			playState = PLAY_PLAY;
			setPopup(POPUP_FRIEND_100LIMIT, playState, playState, 0, DONT);
			}
			break;
		case 3:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETQUEST_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			if(xFriendMap.isPlay == FALSE)
			{
				xQuestInfo.totalNum = 0;
				
				xQuestMain.nowNum = root["M_INDEX"].asInt();
                
                

                
				xQuestDataMain[xQuestMain.nowNum].checkNow[0] = root["M_VALUE1"].asInt();
				xQuestDataMain[xQuestMain.nowNum].checkNow[1] = root["M_VALUE2"].asInt();
				xQuestDataMain[xQuestMain.nowNum].checkNow[2] = root["M_VALUE3"].asInt();

				for(int k=0;k<3;k++)
				{
					if(xQuestDataMain[xQuestMain.nowNum].checkNow[k] >= xQuestDataMain[xQuestMain.nowNum].checkMax[k])
						xQuestDataMain[xQuestMain.nowNum].isCheckClean[k] = TRUE;
				}
				
				xQuestMain.state = root["M_STATE"].asInt();
				if(xQuestMain.state == QUEST_STATE_PLAY || xQuestMain.state == QUEST_STATE_NEW)
				{
					xQuestInfo.xSlot[xQuestInfo.totalNum].type = QUEST_TYPE_MAIN;
					xQuestInfo.xSlot[xQuestInfo.totalNum].questNum = xQuestMain.nowNum;
					xQuestInfo.totalNum++;
				}

				
#if(FALSE)
                /*
				 xQuestInfo.totalNum--;
				 xQuestMain.state = QUEST_STATE_WAIT;
				 xQuestMain.nowNum = 90;
				 xQuestInfo.xSlot[xQuestInfo.totalNum].type = QUEST_TYPE_MAIN;
				 xQuestInfo.xSlot[xQuestInfo.totalNum].questNum = xQuestMain.nowNum;
				 xQuestInfo.totalNum++;
                 */

#endif

				
				xQuestTuto.nowNum = root["T_INDEX"].asInt();
				xQuestTuto.state = root["T_STATE"].asInt();

				xQuestInfo.cleanNormal = root["END_QUEST"].asInt();

				
				for(int i=0;i<QUESTNORMALMAX;i++)
					xQuestDataNormal[i].state = QUEST_STATE_WAIT;
				
				if(xQuestInfo.cleanNormal != 0)
				{
					for(int i=0; i<= xQuestInfo.cleanNormal;i++ )
					{
						xQuestDataNormal[i].state = QUEST_STATE_RESULT;
						xQuestDataNormal[i].isClear = TRUE;
					}
				}

				
                array = root["QUEST"];

				int questNum;
				for(int i=0;i<array.size();i++)
				{
					questNum = array[i]["QUEST_INDEX"].asInt();
					xQuestDataNormal[questNum].state = array[i]["STATE"].asInt();
										

					if(xQuestDataNormal[questNum].state == QUEST_STATE_PLAY || xQuestDataNormal[questNum].state == QUEST_STATE_NEW)
					{
						xQuestInfo.xSlot[xQuestInfo.totalNum].type = QUEST_TYPE_NORMAL;
						xQuestInfo.xSlot[xQuestInfo.totalNum].questNum = questNum;
						xQuestInfo.totalNum++;
					}
					else if(xQuestDataNormal[questNum].state == QUEST_STATE_RESULT)
					{
						xQuestDataNormal[questNum].isClear = TRUE;
					}

					xQuestDataNormal[questNum].checkNow[0] = array[i]["VALUE1"].asInt();
					xQuestDataNormal[questNum].checkNow[1] = array[i]["VALUE2"].asInt();
					xQuestDataNormal[questNum].checkNow[2] = array[i]["VALUE3"].asInt();

					for(int k=0;k<3;k++)
					{
						if(xQuestDataNormal[questNum].checkNow[k] >= xQuestDataNormal[questNum].checkMax[k])
							xQuestDataNormal[questNum].isCheckClean[k] = TRUE;
					}				
				}				
			}
			netSend(CMD_GETMODEL, DONT);
			break;
		case 1:	//실패 
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_RECVORDER_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
                array = root["ORDER"];
                
				xOrder.totalNumRecv = 0;
				for(int i=0;i<array.size();i++)
				{
					xOrder.xSlotNumRecv[xOrder.totalNumRecv].key = array[i]["KEY"].asInt();
					xOrder.xSlotNumRecv[xOrder.totalNumRecv].code = array[i]["ITEM_INDEX"].asInt();




					int userNum = array[i]["USERNUM"].asInt();
					int slotNum = getFriendSlot(userNum);

					if(slotNum == DONT)
					{
						slotNum = addFriendData(userNum);
					}

					if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
						sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["URL"] .asCString());

					sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
					xOrder.xSlotNumRecv[xOrder.totalNumRecv].friendNum = slotNum;

					xOrder.totalNumRecv++;
				}
			}			
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_HACKINGCHECK_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//일반유저
			//아무처리 안함
			break;
		case 1:	//해킹유저
			//해킹유저 처리
			setHackingPopup(3);
			break;
		}
		break;
	case CMD_ADDORDER_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			xOrder.xSlotListData[xNetAddOrder.slotNum].key = root["KEY"].asInt();			
			//	친구에게 주문배송 요청하기
			setQuest(43, 1, DONT);
			break;
		case 1:	//신청횟수 초과
			xOrder.totalNumListDataFriend--;
			setPopup(POPUP_ORDER_5LIMIT, playState, playState, 0, DONT);
			break;
		case 2:	//신청횟수 초과
			xOrder.totalNumListDataFriend--;
			setPopup(POPUP_ORDER_1DAY1, playState, playState, 0, DONT);
			break;
		case 3:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_SETORDER_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			break;
		case 1:	//신청횟수 초과
			setPopup(POPUP_ORDER_10LIMIT, playState, playState, 0, DONT);
			break;
		case 2:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}		
		break;
	case CMD_GETTREND_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
				
			for(int trendNum=0;trendNum<TRENDMAX;trendNum++)
			{
				xTrend.isOpen[trendNum] = 0;
				xTrend.itemCode[trendNum] = DONT;
				xTrend.per[trendNum] = 0;
				xTrend.endTime[trendNum] = 0;

			}
				
			{
                array = root["TRAND"];

				int slot;
				for(int i=0;i<array.size();i++)
				{
					if(i >= 2)
						continue;
					slot = array[i]["SLOT"].asInt();
					xTrend.isOpen[slot] = array[i]["OPEN"].asInt() == 0?FALSE:TRUE;
					xTrend.itemCode[slot] = array[i]["ITEM_INDEX"].asInt();
					xTrend.per[slot] = array[i]["VALUE"].asInt();
					xTrend.endTime[slot] = array[i]["TIME"].asInt();
					xTrend.per[slot] = array[i]["DATA1"].asInt();
					
					
				}
			}
			xNetMySocialList.floor = 0;
			if(xWorldMap.isFriendMap == FALSE)
				xNetMySocialList.userNum = xNetData.userNum;
			else
				xNetMySocialList.userNum = xFriendData[xFriendMap.selectDataSlotNum].userNum;
			netSend(CMD_USERSOCIALLIST, DONT);
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_NOTICE_RECV:
		{
            array = root["NOTICE"];
			xNoticeWorldMap.totalNum = array.size();
			for(int i=0;i<array.size();i++)
			{
                xNoticeWorldMap.code[i] = array[i]["CODE"].asInt();
				sprintf(xNoticeWorldMap.strImgUrl[i], "%s",array[i]["IMG_URL"] .asCString());
				sprintf(xNoticeWorldMap.strRinkUrl[i], "%s",array[i]["MOVE_URL"] .asCString());
			}
            netSend(CMD_PACKAGELIST, DONT);
        }
		break;
	case CMD_GETFRIENDMODEL_RECV:
		{
            array = root["MODEL"];

			
			xRunWay.totalFriendModel = 0;
			for(int i=0;i<array.size();i++)
			{				
				//유저넘버 슬롯번호 찾기
				int userNum = array[i]["USERNUM"].asInt();
				int slotNum = getFriendSlot(userNum);
												
				if(slotNum == DONT)
				{
					slotNum = addFriendData(userNum);
				}
				xRunWay.friendDataSlot[xRunWay.totalFriendModel] = slotNum;
				
				sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
												
				xRunWay.modelCode_Friend[xRunWay.totalFriendModel] = array[i]["M_INDEX"].asInt();												
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[0] = array[i]["LAYED1"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[1] = array[i]["LAYED2"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[2] = array[i]["LAYED3"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[3] = array[i]["LAYED4"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[4] = array[i]["LAYED5"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[5] = array[i]["LAYED6"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[6] = array[i]["LAYED7"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[7] = array[i]["LAYED8"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[8] = array[i]["LAYED9"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[9] = array[i]["LAYED10"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[10] = array[i]["LAYED11"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[11] = array[i]["LAYED12"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[12] = array[i]["LAYED13"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[13] = array[i]["LAYED14"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[14] = array[i]["LAYED15"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].code[15] = array[i]["LAYED16"].asInt();
				xRunWay.xF_Friend[xRunWay.totalFriendModel].isInFitting = array[i]["OUT"].asInt()==0?FALSE:TRUE;

				xRunWay.totalFriendModel++;
			}
		}
		break;
	case CMD_MODELFRIENDVOTE_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			break;
		case 1:	//친구당 한번만 가능
			setPopup(POPUP_MODELVOTEERR, playState, playState, 0, DONT);
			break;
		case 2:
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_KAKAOHELP_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			if(xFriendData[xFriendMap.selectDataSlotNum].isKakaoMessage == TRUE)
				kakaoDevSendMessageApp(xFriendData[xFriendMap.selectDataSlotNum].strKakaoId, xSaveTemp.strNickName,"1473");
								
			setTired(xKakaoData.socialBonusHelp);
			setBonus(400, 110, ICON_TYPE_CANDY, xKakaoData.socialBonusHelp);
			setDropIcon(400, 110, ICON_TYPE_CANDY, xKakaoData.socialBonusHelp, ICON_TYPE_CANDY, 0, ICON_TYPE_CANDY, 0);
			//////////////////////////////////////////////////
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO,TRUE);
			//////////////////////////////////////////////////
			break;
		case 1:	//오늘했음
			setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
			sprintf(xPopup.strText, "오늘 도움요청이 완료된 친구입니다.");
			break;
		}
		xWorldMap.isKakaoFriendMap_NET = FALSE;
		addKakaoHelp(xFriendData[xFriendMap.selectDataSlotNum].strKakaoId);
		xFriendData[xFriendMap.selectDataSlotNum].isKakaoHelp = TRUE;
		break;
	case CMD_GETMODELFRIEND_RECV:
		{
			int userNum = xNetGetModelListFriend.friendUserNum;
			int slotNum = getFriendSlot(userNum);
			
			if(slotNum == DONT)
			{
				slotNum = addFriendData(userNum);
			}
			xFriendData[slotNum].age = root["AGE"].asInt();
			xFriendData[slotNum].sex = root["SEX"].asInt();
			xFriendData[slotNum].isVote = root["VOTE_STATE"].asInt() == 0?FALSE:TRUE;
			
            array = root["MODEL"];

			
			xModel.totalInventoryModel_FRIEND = 0;
			
			int slot;
			for(int i=0;i<array.size();i++)
			{
//				slot = addInventoryModel_FRIEND(array[i]["M_INDEX"].asInt());
				xInventoryModel_FRIEND[slot].key = array[i]["KEY"].asInt();
				xInventoryModel_FRIEND[slot].upGrade = array[i]["UPGLADE"].asInt();
				
				xInventoryModel_FRIEND[slot].xF.code[0] = array[i]["LAYED1"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[1] = array[i]["LAYED2"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[2] = array[i]["LAYED3"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[3] = array[i]["LAYED4"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[4] = array[i]["LAYED5"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[5] = array[i]["LAYED6"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[6] = array[i]["LAYED7"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[7] = array[i]["LAYED8"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[8] = array[i]["LAYED9"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[9] = array[i]["LAYED10"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[10] = array[i]["LAYED11"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[11] = array[i]["LAYED12"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[12] = array[i]["LAYED13"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[13] = array[i]["LAYED14"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[14] = array[i]["LAYED15"].asInt();
				xInventoryModel_FRIEND[slot].xF.code[15] = array[i]["LAYED16"].asInt();
				xInventoryModel_FRIEND[slot].vote = array[i]["VOTE"].asInt();
				xInventoryModel_FRIEND[slot].xF.isInFitting = array[i]["OUT"].asInt()==0?FALSE:TRUE;
			}
			
//			sortModelListFriend();
			
			xNetGetModelMain.friendNum = xNetGetModelListFriend.friendUserNum;
			netSend(CMD_GETMODELMAIN, DONT);
		}
		break;
	case CMD_GETMODELMAIN_RECV:
		if(xNetGetModelMain.friendNum == xNetData.userNum)
		{

            
            array = root["SLOT"];
            
			int slot;
			for(int i=0;i<array.size();i++)
			{
				slot = array[i]["NUM"].asInt();
				xModelMainSlot[slot].modelKey = array[i]["MKEY"].asInt();
				xModelMainSlot[slot].endTime = array[i]["MTIME"].asInt();
				xModelMainSlot[slot].state = array[i]["MSTATE"].asInt();
				
				if(xModelMainSlot[slot].modelKey == -1)
				{
					xModelMainSlot[slot].modelKey = 0;
					xModelMainSlot[slot].state = 0;
				}
			}
			netSend(CMD_GETSOUND, DONT);
		}
		else
		{
            array = root["SLOT"];
			int slot;
			for(int i=0;i<array.size();i++)
			{
				slot = array[i]["NUM"].asInt();
				xModelMainSlotFRIEND[slot].modelKey = array[i]["MKEY"].asInt();
				xModelMainSlotFRIEND[slot].endTime = array[i]["MTIME"].asInt();
				xModelMainSlotFRIEND[slot].state = array[i]["MSTATE"].asInt();
			}
		}
		break;
	case CMD_GETMODEL_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
				
                array = root["MODEL"];
									
				xModel.totalInventoryModel = 0;
				
				int slot;
                

                
				for(int i=0;i<array.size();i++)
				{
					
					xModelData[array[i]["M_INDEX"].asInt()].isOpen = TRUE;
//					slot = addInventoryModel(array[i]["M_INDEX"].asInt());
					xInventoryModel[slot].key = array[i]["KEY"].asInt();
					xInventoryModel[slot].upGrade = array[i]["UPGLADE"].asInt();
					
					xInventoryModel[slot].xF.code[0] = array[i]["LAYED1"].asInt();
					xInventoryModel[slot].xF.code[1] = array[i]["LAYED2"].asInt();
					xInventoryModel[slot].xF.code[2] = array[i]["LAYED3"].asInt();
					xInventoryModel[slot].xF.code[3] = array[i]["LAYED4"].asInt();
					xInventoryModel[slot].xF.code[4] = array[i]["LAYED5"].asInt();
					xInventoryModel[slot].xF.code[5] = array[i]["LAYED6"].asInt();
					xInventoryModel[slot].xF.code[6] = array[i]["LAYED7"].asInt();
					xInventoryModel[slot].xF.code[7] = array[i]["LAYED8"].asInt();
					xInventoryModel[slot].xF.code[8] = array[i]["LAYED9"].asInt();
					xInventoryModel[slot].xF.code[9] = array[i]["LAYED10"].asInt();
					xInventoryModel[slot].xF.code[10] = array[i]["LAYED11"].asInt();
					xInventoryModel[slot].xF.code[11] = array[i]["LAYED12"].asInt();
					xInventoryModel[slot].xF.code[12] = array[i]["LAYED13"].asInt();
					xInventoryModel[slot].xF.code[13] = array[i]["LAYED14"].asInt();
					xInventoryModel[slot].xF.code[14] = array[i]["LAYED15"].asInt();
					xInventoryModel[slot].xF.code[15] = array[i]["LAYED16"].asInt();
					xInventoryModel[slot].vote = array[i]["VOTE"].asInt();
					xInventoryModel[slot].xF.isInFitting = array[i]["OUT"].asInt() == 0?FALSE:TRUE;
				}
			}
			netSend(CMD_GETWINMODEL, DONT);
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_GETFACE_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			{
                array = root["ITEM"];

				for(int i=0;i<array.size();i++)
				{
					switch(array[i]["ITEM_INDEX"].asInt()/1000)
					{
					case 0:
						xHairData[array[i]["ITEM_INDEX"].asInt()%1000].haveNum = array[i]["ITEM_COUNT"].asInt();
						break;
					case 1:
						xFaceData[array[i]["ITEM_INDEX"].asInt()%1000].haveNum = array[i]["ITEM_COUNT"].asInt();
						break;
					}
				}
			}				
			netSend(CMD_GETTREND, DONT);
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	case CMD_RANDOMFRIEND_RECV:
		xWorldMap.ranDomUserCode = root["USERNUM"].asInt();
		{
		//유저넘버 슬롯번호 찾기
		int userNum = xWorldMap.ranDomUserCode;
		int slotNum = getFriendSlot(userNum);
		
		if(slotNum == DONT)
		{
			slotNum = addFriendData(userNum);
		}

		xFriendMap.selectDataSlotNum = slotNum;
		xWorldMap.isFriendMap = TRUE;
		xFriendMap.isPlay = TRUE;
		xFriendMap.state = FRIENDMAP_STATE_LOADING0_START;
		xFriendMap.anyCnt = 0;
			
            
        
        
            
		xFriendMap.type = 1;//0:리스트1:랜덤2:메일
        if(xFriendData[xFriendMap.selectDataSlotNum].isFriend == false)
            xFriendData[xFriendMap.selectDataSlotNum].todayOrder = TRUE;
			
			
		}
		break;
    case CMD_SELLCOMPLETE_RECV:
        initSecurity(&xSaveTemp.mileage, root["MILEAGE"].asInt());
        break;
    case CMD_EVENTQUESTMAINLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
                
            for(int type=0;type<EVENTQUESTMAX;type++)
                xEventQuest.xMain[type].state = EVENTQUESTMAIN_STATE_PLAY;
                
            array = root["MAINLIST"];
            for(int i=0;i<array.size();i++)
            {
                int mainType = array[i]["MAIN_TYPE"].asInt();                
                xEventQuest.xMain[mainType].state = array[i]["STATE"].asInt();
                
                
                if(xEventQuest.xMain[mainType].state == EVENTQUESTMAIN_STATE_END)
                {
                    for(int list=0;list<xEventQuest.totalNum[mainType];list++)
                    {
                        xEventQuest.xData[mainType][list].state = EVENTQUESTDETAIL_STATE_END;
                        xEventQuest.xData[mainType][list].checkNow = xEventQuest.xData[mainType][list].checkMax;
                    }
                }
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_EVENTQUESTDETAILLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xEventQuest.isNetLoad = false;
            
            array = root["DETAILLIST"];
            for(int i=0;i<array.size();i++)
            {
                int mainType = array[i]["DETAIL_TYPE"].asInt();
                int list = array[i]["INDEX"].asInt();
                
                xEventQuest.xData[mainType][list].state = array[i]["STATE"].asInt();
                xEventQuest.xData[mainType][list].checkNow = array[i]["VALUE"].asInt();
                
                if(xEventQuest.xMain[mainType].state == EVENTQUESTMAIN_STATE_END)
                {
                    xEventQuest.xData[mainType][list].state = EVENTQUESTDETAIL_STATE_END;
                    xEventQuest.xData[mainType][list].checkNow = xEventQuest.xData[mainType][list].checkMax;
                }
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_HOTDEALMAINLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xHotDeal.isReset = root["RESET"].asInt()==0?true:false;
            xHotDeal.remainTime= root["TIME"].asInt();
            xHotDeal.hotDealCode = root["DATANUM"].asInt();
                
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_HOTDEALDETAILLIST, TRUE);
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_HOTDEALDETAILLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xHotDeal.state = HOTDEAL_MAINSTATE_PLAY;
            if(xHotDeal.isReset == true)
            {
                for(int k=0;k<HOTDEALSLOTMAX;k++)
                {
                    xHotDeal.xSlot[k].state = HOTDEAL_STATE_CLOSE;
                    xHotDeal.xSlot[k].isCardOpen = false;
                    xHotDeal.xSlot[k].anyCnt = 0;
                    xHotDeal.xSlot[k].actFlow = 0;
                }
            }
            else
            {
                array = root["SLOT"];
                for(int i=0;i<array.size();i++)
                {
                    xHotDeal.xSlot[i].state = array[i]["STATE"].asInt();
                    xHotDeal.xSlot[i].itemType = array[i]["CATE"].asInt();
                    xHotDeal.xSlot[i].itemCode = array[i]["INDEX"].asInt();
                    xHotDeal.xSlot[i].salePer = array[i]["DC"].asInt();
                }
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_HOTDEALDETAILBUY_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            initSecurity(&xSaveTemp.cash, root["CASH"].asInt());
            break;
        default:
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
	case CMD_INITGAME_RECV:
		switch(root["RESULT"].asInt())
		{
		case 0:	//미완료
			xMainMenu.state = MAINMENU_STATE_INITCHECK;
			xWorldMap.isInitLoading = TRUE;
			break;
		case 1:	//완료
			xMainMenu.initCnt = 99;
				
			loadSpriteData("sptnpc0.spt",&xSpritNpc[NPC_ACT_WALKING][ACT_FRONT]);
			loadSpriteData("sptnpc0b.spt",&xSpritNpc[NPC_ACT_WALKING][ACT_BACK]);
			loadSpriteData("sptnpc1.spt",&xSpritNpc[NPC_ACT_WALKINGBAG][ACT_FRONT]);
			loadSpriteData("sptnpc1b.spt",&xSpritNpc[NPC_ACT_WALKINGBAG][ACT_BACK]);
			loadSpriteData("sptnpc2.spt",&xSpritNpc[NPC_ACT_PORTER_FITTING][ACT_FRONT]);
			loadSpriteData("sptnpc2b.spt",&xSpritNpc[NPC_ACT_PORTER_FITTING][ACT_BACK]);
			loadSpriteData("sptnpc3.spt",&xSpritNpc[NPC_ACT_POSE1][ACT_FRONT]);
			loadSpriteData("sptnpc3b.spt",&xSpritNpc[NPC_ACT_POSE1][ACT_BACK]);
			loadSpriteData("sptnpc4.spt",&xSpritNpc[NPC_ACT_POSE2][ACT_FRONT]);
			loadSpriteData("sptnpc4b.spt",&xSpritNpc[NPC_ACT_POSE2][ACT_BACK]);
			loadSpriteData("sptnpc5.spt",&xSpritNpc[NPC_ACT_GOMIN][ACT_FRONT]);
			loadSpriteData("sptnpc5b.spt",&xSpritNpc[NPC_ACT_GOMIN][ACT_BACK]);
			loadSpriteData("sptnpc6.spt",&xSpritNpc[NPC_ACT_GREETING][ACT_FRONT]);
			loadSpriteData("sptnpc6b.spt",&xSpritNpc[NPC_ACT_GREETING][ACT_BACK]);
			loadSpriteData("sptnpc7.spt",&xSpritNpc[NPC_ACT_TALKING][ACT_FRONT]);
			loadSpriteData("sptnpc7b.spt",&xSpritNpc[NPC_ACT_TALKING][ACT_BACK]);
			loadSpriteData("sptnpc8.spt",&xSpritNpc[NPC_ACT_LOOKINGAROUND][ACT_FRONT]);
			loadSpriteData("sptnpc8b.spt",&xSpritNpc[NPC_ACT_LOOKINGAROUND][ACT_BACK]);
			loadSpriteData("sptnpc9.spt",&xSpritNpc[NPC_ACT_STOP][ACT_FRONT]);
			loadSpriteData("sptnpc9b.spt",&xSpritNpc[NPC_ACT_STOP][ACT_BACK]);
			loadSpriteData("sptnpc12.spt",&xSpritNpc[NPC_ACT_ANGRY][ACT_FRONT]);
			loadSpriteData("sptnpc12b.spt",&xSpritNpc[NPC_ACT_ANGRY][ACT_BACK]);
			loadSpriteData("sptnpc13.spt",&xSpritNpc[NPC_ACT_PORTER_MAN_YES][ACT_FRONT]);
			loadSpriteData("sptnpc13b.spt",&xSpritNpc[NPC_ACT_PORTER_MAN_YES][ACT_BACK]);
			loadSpriteData("sptnpc14.spt",&xSpritNpc[NPC_ACT_PORTER_MAN_TIRED][ACT_FRONT]);
			loadSpriteData("sptnpc14b.spt",&xSpritNpc[NPC_ACT_PORTER_MAN_TIRED][ACT_BACK]);
			loadSpriteData("sptnpc15.spt",&xSpritNpc[NPC_ACT_PORTER_MAN_APPLAUD][ACT_FRONT]);
			loadSpriteData("sptnpc15b.spt",&xSpritNpc[NPC_ACT_PORTER_MAN_APPLAUD][ACT_BACK]);
			loadSpriteData("sptnpc16.spt",&xSpritNpc[NPC_ACT_APPLAUD][ACT_FRONT]);
			loadSpriteData("sptnpc16b.spt",&xSpritNpc[NPC_ACT_APPLAUD][ACT_BACK]);
			loadSpriteData("sptnpc17.spt",&xSpritNpc[NPC_ACT_WATCH][ACT_FRONT]);
			loadSpriteData("sptnpc17b.spt",&xSpritNpc[NPC_ACT_WATCH][ACT_BACK]);
			loadSpriteData("sptnpc18.spt",&xSpritNpc[NPC_ACT_WORLDMAPPHONE][ACT_FRONT]);
			loadSpriteData("sptnpc18b.spt",&xSpritNpc[NPC_ACT_WORLDMAPPHONE][ACT_BACK]);
			loadSpriteData("sptnpc19.spt",&xSpritNpc[NPC_ACT_PORTER_ANGRY][ACT_FRONT]);
			loadSpriteData("sptnpc19b.spt",&xSpritNpc[NPC_ACT_PORTER_ANGRY][ACT_BACK]);
			loadSpriteData("sptnpc20.spt",&xSpritNpc[NPC_ACT_PORTER_MAN_WALKING][ACT_FRONT]);
			loadSpriteData("sptnpc20b.spt",&xSpritNpc[NPC_ACT_PORTER_MAN_WALKING][ACT_BACK]);
			loadSpriteData("sptnpc21.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_STOP][ACT_FRONT]);
			loadSpriteData("sptnpc21b.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_STOP][ACT_BACK]);
			loadSpriteData("sptnpc22.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_APPLAUD][ACT_FRONT]);
			loadSpriteData("sptnpc22b.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_APPLAUD][ACT_BACK]);
			loadSpriteData("sptnpc23.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION0][ACT_FRONT]);
			loadSpriteData("sptnpc23b.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION0][ACT_BACK]);
			loadSpriteData("sptnpc24.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION1][ACT_FRONT]);
			loadSpriteData("sptnpc24b.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION1][ACT_BACK]);
			loadSpriteData("sptnpc25.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION2][ACT_FRONT]);
			loadSpriteData("sptnpc25b.spt",&xSpritNpc[NPC_ACT_RUNWAY_CHAIR_ACTION2][ACT_BACK]);
				
			loadSpriteData("sptnpc26.spt",&xSpritNpc[NPC_ACT_PORTER_MM_MAN_YES][ACT_FRONT]);
			loadSpriteData("sptnpc26b.spt",&xSpritNpc[NPC_ACT_PORTER_MM_MAN_YES][ACT_BACK]);
			loadSpriteData("sptnpc27.spt",&xSpritNpc[NPC_ACT_PORTER_MM_MAN_TIRED][ACT_FRONT]);
			loadSpriteData("sptnpc27b.spt",&xSpritNpc[NPC_ACT_PORTER_MM_MAN_TIRED][ACT_BACK]);
			loadSpriteData("sptnpc28.spt",&xSpritNpc[NPC_ACT_PORTER_WW_MAN_YES][ACT_FRONT]);
			loadSpriteData("sptnpc28b.spt",&xSpritNpc[NPC_ACT_PORTER_WW_MAN_YES][ACT_BACK]);
			loadSpriteData("sptnpc29.spt",&xSpritNpc[NPC_ACT_PORTER_WW_MAN_TIRED][ACT_FRONT]);
			loadSpriteData("sptnpc29b.spt",&xSpritNpc[NPC_ACT_PORTER_WW_MAN_TIRED][ACT_BACK]);
				
							
			loadSpriteData("sptnpc40.spt",&xSpritNpc[NPC_ACT_SMILE][ACT_FRONT]);
			loadSpriteData("sptnpc41.spt",&xSpritNpc[NPC_ACT_PAYMENT][ACT_FRONT]);
			loadSpriteData("sptnpc42.spt",&xSpritNpc[NPC_ACT_ASSISTANTCALL][ACT_FRONT]);
			loadSpriteData("sptnpc43.spt",&xSpritNpc[NPC_ACT_CROSSARMS][ACT_FRONT]);
			loadSpriteData("sptnpc44.spt",&xSpritNpc[NPC_ACT_WAVINGHAND][ACT_FRONT]);
			loadSpriteData("sptnpc45.spt",&xSpritNpc[NPC_ACT_GUITAR][ACT_FRONT]);
			loadSpriteData("sptnpc46.spt",&xSpritNpc[NPC_ACT_SONG][ACT_FRONT]);
			loadSpriteData("sptnpc47.spt",&xSpritNpc[NPC_ACT_DANCE][ACT_FRONT]);
			loadSpriteData("sptnpc48.spt",&xSpritNpc[NPC_ACT_PHONE][ACT_FRONT]);
			loadSpriteData("sptnpc49.spt",&xSpritNpc[NPC_ACT_FASHIONCHECK][ACT_FRONT]);
			loadSpriteData("sptnpc50.spt",&xSpritNpc[NPC_ACT_POWERMAN][ACT_FRONT]);
			loadSpriteData("sptnpc51.spt",&xSpritNpc[NPC_ACT_TOUCH0_MAN][ACT_FRONT]);
			loadSpriteData("sptnpc52.spt",&xSpritNpc[NPC_ACT_TOUCH1_MAN][ACT_FRONT]);
			loadSpriteData("sptnpc53.spt",&xSpritNpc[NPC_ACT_TOUCH0_WOMAN][ACT_FRONT]);
			loadSpriteData("sptnpc54.spt",&xSpritNpc[NPC_ACT_TOUCH1_WOMAN][ACT_FRONT]);
			loadSpriteData("sptnpc55.spt",&xSpritNpc[NPC_ACT_CHAIR_SIT][ACT_FRONT]);
			loadSpriteData("sptnpc56.spt",&xSpritNpc[NPC_ACT_CHAIR_BOOK][ACT_FRONT]);
			loadSpriteData("sptnpc57.spt",&xSpritNpc[NPC_ACT_CHAIR_COFFEE][ACT_FRONT]);
			loadSpriteData("sptnpc58.spt",&xSpritNpc[NPC_ACT_CHAIR_IPAD][ACT_FRONT]);
			loadSpriteData("sptnpc59.spt",&xSpritNpc[NPC_ACT_CHAIR_STANDUP][ACT_FRONT]);
			loadSpriteData("sptnpc60.spt",&xSpritNpc[NPC_ACT_CHAIR_EVENT][ACT_FRONT]);
			loadSpriteData("sptnpc61.spt",&xSpritNpc[NPC_ACT_CHAIR_PHONE][ACT_FRONT]);

			loadSpriteData("sptnpc80b.spt",&xSpritNpc[NPC_ACT_SELECT][ACT_BACK]);
			loadSpriteData("sptnpc81b.spt",&xSpritNpc[NPC_ACT_NPC1][ACT_BACK]);
			loadSpriteData("sptnpc82b.spt",&xSpritNpc[NPC_ACT_NPC2][ACT_BACK]);
			loadSpriteData("sptnpc83b.spt",&xSpritNpc[NPC_ACT_ORDERING][ACT_BACK]);
			loadSpriteData("sptnpc84b.spt",&xSpritNpc[NPC_ACT_CLEAN][ACT_BACK]);
			loadSpriteData("sptnpc85b.spt",&xSpritNpc[NPC_ACT_POSE3][ACT_BACK]);
				
			loadSpriteData("sptnpc86b.spt",&xSpritNpc[NPC_ACT_PORTER_MM_W_FITTING][ACT_BACK]);
			loadSpriteData("sptnpc87b.spt",&xSpritNpc[NPC_ACT_PORTER_MM_W_ANGRY][ACT_BACK]);
			loadSpriteData("sptnpc88b.spt",&xSpritNpc[NPC_ACT_PORTER_WW_W_FITTING][ACT_BACK]);
			loadSpriteData("sptnpc89b.spt",&xSpritNpc[NPC_ACT_PORTER_WW_W_ANGRY][ACT_BACK]);
								
							
			netSend(CMD_GETGAMEDATA, DONT);
			break;
		}
		break;
    case CMD_RIVALLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xRival.isNetLoad = false;
                
            xRival.nowCount = root["COUNT"].asInt();
            xRival.state = root["STATE"].asInt();
            xRival.remainTime = root["TIME"].asInt();
            xRival.completeMain = root["MAINNUM"].asInt();
            xRival.completeDetail = root["SUBNUM"].asInt();
            xRival.nowMain = root["MAINNUM_NOW"].asInt();
            xRival.nowDetail = root["SUBNUM_NOW"].asInt();
                
            xRival.checkNow[0] = root["QUEST_0"].asInt();
            xRival.checkNow[1] = root["QUEST_1"].asInt();
            xRival.checkNow[2] = root["QUEST_2"].asInt();
            xRival.checkNow[3] = root["QUEST_3"].asInt();
            xRival.checkNow[4] = root["QUEST_4"].asInt();
            xRival.checkNow[5] = root["QUEST_5"].asInt();
            xRival.checkNow[6] = root["QUEST_6"].asInt();
            xRival.checkNow[7] = root["QUEST_7"].asInt();
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_RIVALCOMPLETE_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xRival.completeMain = root["MAINNUM"].asInt();
            xRival.completeDetail = root["SUBNUM"].asInt();
                
            xSave.giftLastKey = 999;
            gameSave(SAVE_SLOT_GAME);
                
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_JEWELQUESTLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            
            xJewelQuest.isNetLoad = true;
            for(int k=0;k<xJewelQuest.totalData;k++)
            {
                xJewelQuest.xData[k].state = JEWELQUEST_STATE_PLAY;
                xJewelQuest.xData[k].checkNow = 0;
            }
            
            array = root["COLLECTIONLIST"];
            for(int i=0;i<array.size();i++)
            {
                int listNum = array[i]["INDEX"].asInt();
                xJewelQuest.xData[listNum].state = array[i]["STATE"].asInt();
                xJewelQuest.xData[listNum].checkNow = array[i]["VALUE"].asInt();
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_JEWELQUESTCOMPLETE_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xSave.giftLastKey = 999;
            gameSave(SAVE_SLOT_GAME);
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_AMULETLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xAmulet.isNetLoad = true;
            
            
            if(xWorldMap.isFriendMap == false)
            {
                for(int k=0;k<AMULETPAGEMAX;k++)
                {
                    xAmulet.xAmuletPage[k].isOpen = false;
                    xAmulet.xAmuletPage[k].amuletCode = 0;
                    
                    for(int z=0;z<AMULETSOCKETMAX;z++)
                        xAmulet.xAmuletPage[k].socketJewelCode[z] = DONT;
                }
                xAmulet.selectAmuletPage = root["STATE"].asInt();
                
                for(int k=0;k<root["BUYDECK"].asInt()+1;k++)
                {
                    xAmulet.xAmuletPage[k].isOpen = true;
                }
                array = root["AMULETINFO"];
                for(int i=0;i<array.size();i++)
                {
                    int deck = array[i]["DECK"].asInt();
                    xAmulet.xAmuletPage[deck].amuletCode = array[i]["AMULET"].asInt();
                    
                    xAmulet.xAmuletPage[deck].socketJewelCode[0] = array[i]["SLOT0"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[1] = array[i]["SLOT1"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[2] = array[i]["SLOT2"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[3] = array[i]["SLOT3"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[4] = array[i]["SLOT4"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[5] = array[i]["SLOT5"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[6] = array[i]["SLOT6"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[7] = array[i]["SLOT7"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[8] = array[i]["SLOT8"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[9] = array[i]["SLOT9"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[10] = array[i]["SLOT10"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[11] = array[i]["SLOT11"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[12] = array[i]["SLOT12"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[13] = array[i]["SLOT13"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[14] = array[i]["SLOT14"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[15] = array[i]["SLOT15"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[16] = array[i]["SLOT16"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[17] = array[i]["SLOT17"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[18] = array[i]["SLOT18"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[19] = array[i]["SLOT19"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[20] = array[i]["SLOT20"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[21] = array[i]["SLOT21"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[22] = array[i]["SLOT22"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[23] = array[i]["SLOT23"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[24] = array[i]["SLOT24"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[25] = array[i]["SLOT25"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[26] = array[i]["SLOT26"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[27] = array[i]["SLOT27"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[28] = array[i]["SLOT28"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[29] = array[i]["SLOT29"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[30] = array[i]["SLOT30"].asInt();
                    xAmulet.xAmuletPage[deck].socketJewelCode[31] = array[i]["SLOT31"].asInt();

                }
            }
            else
            {
                
                xAmulet.xAmuletFriend.amuletCode = 0;
                for(int z=0;z<AMULETSOCKETMAX;z++)
                    xAmulet.xAmuletFriend.socketJewelCode[z] = DONT;
                
                array = root["AMULETINFO"];
                for(int i=0;i<array.size();i++)
                {
                    int deck = array[i]["DECK"].asInt();
                    
                    if(deck == root["STATE"].asInt())
                    {
                        xAmulet.xAmuletFriend.amuletCode = array[i]["AMULET"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[0] = array[i]["SLOT0"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[1] = array[i]["SLOT1"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[2] = array[i]["SLOT2"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[3] = array[i]["SLOT3"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[4] = array[i]["SLOT4"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[5] = array[i]["SLOT5"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[6] = array[i]["SLOT6"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[7] = array[i]["SLOT7"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[8] = array[i]["SLOT8"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[9] = array[i]["SLOT9"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[10] = array[i]["SLOT10"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[11] = array[i]["SLOT11"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[12] = array[i]["SLOT12"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[13] = array[i]["SLOT13"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[14] = array[i]["SLOT14"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[15] = array[i]["SLOT15"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[16] = array[i]["SLOT16"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[17] = array[i]["SLOT17"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[18] = array[i]["SLOT18"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[19] = array[i]["SLOT19"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[20] = array[i]["SLOT20"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[21] = array[i]["SLOT21"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[22] = array[i]["SLOT22"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[23] = array[i]["SLOT23"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[24] = array[i]["SLOT24"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[25] = array[i]["SLOT25"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[26] = array[i]["SLOT26"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[27] = array[i]["SLOT27"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[28] = array[i]["SLOT28"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[29] = array[i]["SLOT29"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[30] = array[i]["SLOT30"].asInt();
                        xAmulet.xAmuletFriend.socketJewelCode[31] = array[i]["SLOT31"].asInt();
                    }
                }
            }
                
            
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_AMULETBUYLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            array = root["AMULETLIST"];
            xAmulet.xData[0].isOpen = true;
            for(int i=0;i<array.size();i++)
            {
                xAmulet.xData[array[i]["AMULET"].asInt()].isOpen = true;
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
                
            xClubList.totalList = 0;
                
            array = root["CLUBLIST"];
            for(int i=0;i<array.size();i++)
            {
                xClubList.xListSlot[xClubList.totalList].clubKey = array[i]["CLUB_NUM"].asInt();
                sprintf(xClubList.xListSlot[xClubList.totalList].strName, "%s",array[i]["CLUB_NAME"].asCString());
                sprintf(xClubList.xListSlot[xClubList.totalList].strNickName, "%s",array[i]["MASTER_NAME"].asCString());
                xClubList.xListSlot[xClubList.totalList].clubLv = array[i]["LV"].asInt();
                xClubList.xListSlot[xClubList.totalList].clubExp = array[i]["EXP"].asInt();
                xClubList.xListSlot[xClubList.totalList].clubIcon = array[i]["ICON"].asInt();
                xClubList.xListSlot[xClubList.totalList].memberNow = array[i]["MEMBER_COUNT"].asInt();
                xClubList.xListSlot[xClubList.totalList].joinType = array[i]["JOIN"].asInt();
                sprintf(xClubList.xListSlot[xClubList.totalList].strJoinInfo, "%s",array[i]["CONTENT"].asCString());
                xClubList.totalList++;
            }                                
            xClubList.state = CLUBLIST_STATE_PLAY;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBSEARCH_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공        
            xClubSearch.xSearchSlot.clubKey = root["CLUB_NUM"].asInt();
            sprintf(xClubSearch.xSearchSlot.strName, "%s",root["CLUB_NAME"].asCString());
            sprintf(xClubSearch.xSearchSlot.strNickName, "%s",root["MASTER_NAME"].asCString());
            xClubSearch.xSearchSlot.clubLv = root["LV"].asInt();
            xClubSearch.xSearchSlot.clubExp = root["EXP"].asInt();
            xClubSearch.xSearchSlot.clubIcon = root["ICON"].asInt();
            xClubSearch.xSearchSlot.memberNow = root["MEMBER_COUNT"].asInt();
            xClubSearch.xSearchSlot.joinType = root["JOIN"].asInt();
            sprintf(xClubSearch.xSearchSlot.strJoinInfo, "%s",root["CONTENT"].asCString());
            break;
        case 2:	//검색실패
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "해당 클럽이 존재하지 않습니다.");
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBMAKE_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClub.xMy.clubKey = root["CLUB_NUM"].asInt();
                
            setMoney(-xClub.makePrice);
            setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_GOLD,-xClub.makePrice);
            ////////////////////////////////////////////////////////////
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, FALSE);
            ////////////////////////////////////////////////////////////
            
            setPopup(POPUP_CLUBMAKEOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            break;
        case 2:	//중복
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "이미 사용중인 클럽명입니다.");
            xClubList.state = CLUBLIST_STATE_MAKE;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBJOINAPPLY_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClubList.state = CLUBLIST_STATE_PLAY;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "가입 신청 되었습니다.");
            break;
        case 2:	//가입된상태
                
            clubListFreeLoad(false);
            xWorldMap.state = WORLDMAP_STATE_PLAY;
            xClub.xMy.clubKey = root["CLUB_NUM"].asInt();
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "이미 클럽에 가입된 상태됩니다.");
            break;
        case 3:	//중복
            xClubList.state = CLUBLIST_STATE_PLAY;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "이미 신청한 클럽입니다.");
            break;
        case 4:
            xClubList.state = CLUBLIST_STATE_PLAY;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "해당클럽의 가입신청수가\n초과되었습니다.");
            break;

        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBJOIN_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClub.xMy.clubKey = xNetClubJoin.CLUB_NUM;
            setPopup(POPUP_CLUBJOINOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            break;
        case 2:	//가입된상태
            clubListFreeLoad(false);
            xWorldMap.state = WORLDMAP_STATE_PLAY;
            xClub.xMy.clubKey = root["CLUB_NUM"].asInt();
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "이미 클럽에 가입된 상태됩니다.");
            break;
        case 3:	//클럽인원제한을 초과
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "클럽 인원 제한이 초과 되었습니다.");
            xClubList.state = CLUBLIST_STATE_PLAY;
            break;
        case 4:	//
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "폐쇄된 클럽입니다.");
            xClubList.state = CLUBLIST_STATE_PLAY;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBDATA_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            sprintf(xClub.xMy.strName, "%s",root["CLUB_NAME"].asCString());
                
            xClub.xMy.masterKey = root["MASTER_NUM"].asInt();
            sprintf(xClub.xMy.strNickName, "%s",root["MASTER_NAME"].asCString());
            xClub.xMy.clubLv = root["LV"].asInt();
            
            
            xClub.bestPangScore = root["BESTSCORE"].asInt();
            
                
            xClub.xMy.fashionWeekRank = root["MYRANK"].asInt();
            xClub.xMy.fashionWeekRankPer = root["MYRANKPER"].asDouble();
                
                
            xClub.xMy.fashionWeekScore_LASTWEEK = root["LASTMYSCORE"].asInt();
            xClub.xMy.fashionWeekRank_LASTWEEK = root["LASTMYRANK"].asInt();
            xClub.xMy.fashionWeekRankPer_LASTWEEK = root["LASTMYRANKPER"].asDouble();
            

            
            xClub.money = root["MONEY"].asInt();
            xClub.xMy.clubExp = root["EXP"].asInt();
            xClub.xMy.clubIcon = root["ICON"].asInt();
            xClub.xMy.memberNow = root["MEMBER_COUNT"].asInt();
            xClub.xMy.joinType = root["JOIN"].asInt();
            sprintf(xClub.xMy.strJoinInfo, "%s",root["CONTENT"].asCString());
            sprintf(xClub.xMy.strNotice, "%s",root["NOTICE"].asCString());
            xClub.fashionWeekPlayCount = root["PLAYCOUNT"].asInt();
            break;
        case 1:	//실패
        case 2:	//존재하지 않는 길드
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_SETCLUBFORCEOUT_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClub.xMy.memberNow--;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBMEMBER_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            if(xClubLobby.state == CLUBLOBBY_STATE_NET)
                xClubLobby.state = CLUBLOBBY_STATE_PLAY;
                
            {
            bool isMyData = false;
                
            xClub.totalMember = 0;
            array = root["CLUBMEMBER"];
            for(int i=0;i<array.size();i++)
            {
                xClub.xMember[xClub.totalMember].userKey = array[i]["USERNUM"].asInt();
                xClub.xMember[xClub.totalMember].totalContribution = array[i]["CONTRIBUTION"].asInt();
                
                
                int userNum = xClub.xMember[xClub.totalMember].userKey;
                int slotNum = getFriendSlot(userNum);
                
                if(slotNum == DONT)
                {
                    slotNum = addFriendData(userNum);
                }
                xFriendData[slotNum].userNum = userNum;
                sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"].asCString());
                
                xFriendData[slotNum].lv = array[i]["LEVEL"].asInt();
                if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
                    sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());
                
                xClub.xMember[xClub.totalMember].loginTime = array[i]["LOGIN"].asInt();
                
                if(userNum == xNetData.userNum)
                    isMyData = true;
                
                xClub.totalMember++;
            }
            
            if(isMyData == false)
            {
                setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                sprintf(xPopup.strText, "강퇴된 회원입니다.");
                xClub.xMy.clubKey = DONT;
                clubLobbyFreeLoad(false);
                xWorldMap.state = WORLDMAP_STATE_PLAY;
            }
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBJOINLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClubJoinMember.totalNum = 0;
            array = root["REQUESTLIST"];
            for(int i=0;i<array.size();i++)
            {
                
                xClubJoinMember.xJoinMember[xClubJoinMember.totalNum].userKey = array[i]["USERNUM"].asInt();
                int userNum = xClubJoinMember.xJoinMember[xClubJoinMember.totalNum].userKey;
                int slotNum = getFriendSlot(userNum);
                
                if(slotNum == DONT)
                {
                    slotNum = addFriendData(userNum);
                }
                xFriendData[slotNum].userNum = userNum;
                sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"].asCString());
                xFriendData[slotNum].lv = array[i]["LV"].asInt();
                if(xFriendData[slotNum].strUrl[0] == 0 || xFriendData[slotNum].strUrl[0] == '0')
                    sprintf(xFriendData[slotNum].strUrl, "%s",array[i]["PRO_URL"] .asCString());

                sprintf(xClubJoinMember.xJoinMember[xClubJoinMember.totalNum].strJoinApplyTime, "%s",array[i]["CDATE"].asCString());
                xClubJoinMember.totalNum++;
                
               
                
            }
            break;
        default:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBUNREG_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            setPopup(POPUP_CLUBUNREGOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);                
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            break;
        case 3:
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "클럽마스터는 탈퇴하실수 없습니다.");
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            break;
        case 1:	//실패
        case 2:
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
            
    case CMD_CLUBJOINDEL_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            for(int k=xClubLobby.selectSlot;k<xClubJoinMember.totalNum;k++)
            {
                memcpy(&xClubJoinMember.xJoinMember[k], &xClubJoinMember.xJoinMember[k+1], sizeof(xClubJoinMember.xJoinMember[k]));
            }
            xClubJoinMember.totalNum--;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBJOINACCEPT_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            for(int k=xClubLobby.selectSlot;k<xClubJoinMember.totalNum;k++)
            {
                memcpy(&xClubJoinMember.xJoinMember[k], &xClubJoinMember.xJoinMember[k+1], sizeof(xClubJoinMember.xJoinMember[k]));
            }
            xClubJoinMember.totalNum--;
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "승인되었습니다.");
                
                
            xClub.xMy.memberNow++;
                
            ////////////////////////////////////////////////////
            xEventQueueNet.key[xEventQueueNet.totalNum] = xClub.xMy.clubKey;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBMEMBER, TRUE);
            ///////////////////////////////////////////////////
            break;
        case 2:
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "다른 클럽에 가입된 상태입니다.");
            break;
        case 3:
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "잘못된 신청정보입니다.");
            break;
        case 4:
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "승인권한이 없습니다.");
            break;
        case 5:
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "클럽인원 제한을 초과하였습니다.");
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBHISTORYLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
        {
            xClubHistory.rowNum = root["ROWNUM"].asInt();
            
            array = root["CLUBHISTORY"];
            for(int i=0;i<array.size();i++)
            {
                //유저넘버 슬롯번호 찾기
                int userNum = array[i]["USERNUM"].asInt();
                int ToUserNum = array[i]["USERNUM2"].asInt();
                int slotNum = getFriendSlot(userNum);
                int ToNum=getFriendSlot(ToUserNum);
                if(slotNum == DONT)
                {
                    slotNum = addFriendData(userNum);
                }
                
                if(ToNum==DONT)
                {
                    ToNum=addFriendData(ToUserNum);
                }
                
                xClubHistory.xSlot[xClubHistory.totalNum].userKey = userNum;
                xClubHistory.xSlot[xClubHistory.totalNum].ToUserKey= ToUserNum;
                xClubHistory.xSlot[xClubHistory.totalNum].type = array[i]["TYPE"].asInt();
                xClubHistory.xSlot[xClubHistory.totalNum].value = array[i]["VALUE"].asInt();

                xClubHistory.xSlot[xClubHistory.totalNum].writeTime = array[i]["CDATE"].asInt();                
                sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"].asCString());
                sprintf(xFriendData[ToNum].strNickName, "%s",array[i]["NICKNAME2"].asCString());
                xClubHistory.totalNum++;
            }
        }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBBOOKLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            {
            xClubBook.rowNum = root["ROWNUM"].asInt();
            array = root["CLUBBOOKINFO"];
            for(int i=0;i<array.size();i++)
            {
                //유저넘버 슬롯번호 찾기
                int userNum = array[i]["USERNUM"].asInt();
                int slotNum = getFriendSlot(userNum);
                
                if(slotNum == DONT)
                {
                    slotNum = addFriendData(userNum);
                }
                sprintf(xFriendData[slotNum].strNickName, "%s",array[i]["NICKNAME"] .asCString());
                
                xClubBook.xSlot[xClubBook.totalNum].key = array[i]["KEY"].asInt();
                xClubBook.xSlot[xClubBook.totalNum].userKey = userNum;
                sprintf(xClubBook.xSlot[xClubBook.totalNum].strText, "%s",array[i]["CONTENT"] .asCString());
                sprintf(xClubBook.xSlot[xClubBook.totalNum].strDate, "%s",array[i]["CDATE"] .asCString());
                xClubBook.totalNum++;
            }
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBBOOKADD_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            break;
        case 2:	//없는 맴버
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "탈퇴된 회원입니다.");
            xClub.xMy.clubKey = DONT;

            clubLobbyFreeLoad(false);
            xWorldMap.state = WORLDMAP_STATE_PLAY;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBBOOKDEL_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xClubLobby.state = CLUBLOBBY_STATE_PLAY;
            for(int k=xClubBook.selectSlot;k<xClubBook.totalNum;k++)
            {
                memcpy(&xClubBook.xSlot[k], &xClubBook.xSlot[k+1], sizeof(xClubBook.xSlot[k]));
            }
            xClubBook.totalNum--;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_SETCLUBMASTER_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            break;
        case 2:	//없는 맴버
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "탈퇴된 회원입니다.");
            
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBRANKLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
                
            xFashionWeek.isNet_Ranking = false;
            xFashionWeekRank.totalNum = 0;
            xClub.xMy.fashionWeekRank = root["MYRANK"].asInt();
            xClub.xMy.fashionWeekRankPer = root["MYRANKPER"].asDouble();
            xClub.xMy.fashionWeekScore = root["MYSCORE"].asInt();
                
                
            xClub.xMy.fashionWeekScore_LASTWEEK = root["LASTMYSCORE"].asInt();
            xClub.xMy.fashionWeekRank_LASTWEEK = root["LASTMYRANK"].asInt();
            xClub.xMy.fashionWeekRankPer_LASTWEEK = root["LASTMYRANKPER"].asDouble();
                
                
                
            array = root["CLUBRANKLIST"];
            for(int i=0;i<array.size();i++)
            {
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].fashionWeekRank = array[i]["RANK"].asInt();
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].fashionWeekScore = array[i]["SCORE"].asInt();
                
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].clubKey = array[i]["CLUB_NUM"].asInt();
                sprintf(xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].strName, "%s",array[i]["CLUB_NAME"].asCString());
                
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].masterKey = array[i]["MASTER_NUM"].asInt();
                sprintf(xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].strNickName, "%s",array[i]["MASTER_NAME"].asCString());
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].clubLv = array[i]["LV"].asInt();
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].clubExp = array[i]["EXP"].asInt();
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].clubIcon = array[i]["ICON"].asInt();
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].joinType = array[i]["JOIN"].asInt();
                xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].memberNow = array[i]["MEMBER_COUNT"].asInt();
                
                sprintf(xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].strJoinInfo, "%s",array[i]["CONTENT"].asCString());
                sprintf(xFashionWeekRank.xSlot[xFashionWeekRank.totalNum].strNotice, "%s",array[i]["NOTICE"].asCString());
                
                xFashionWeekRank.totalNum++;
            }                
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_FASHIONWEEKDRESSLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공                                
            xFashionWeek.isNet_Dress = false;
                
            for(int tt=0;tt<FASHIONDATATYPEMAX;tt++)
            {
                for(int ll=0;ll<FASHIONDATAMAX;ll++)
                {
                    xFashionWeekItem[tt][ll].nowCost = 0;
                    xFashionWeekItem[tt][ll].isExp = false;
                    xFashionWeekItem[tt][ll].isOpen = false;
                }
            }
                
            for(int k=0;k<HAIRDATAMAX;k++)
                xHairData[k].isClubOpen = false;
                
            for(int k=0;k<FACEDATAMAX;k++)
                xFaceData[k].isClubOpen = false;
                
                
            xHairData[STAFF0_HAIRCODE].isClubOpen = true;
            xFaceData[STAFF0_FACECODE].isClubOpen = true;
            xHairData[STAFF1_HAIRCODE].isClubOpen = true;
            xFaceData[STAFF1_FACECODE].isClubOpen = true;
                
            array = root["DRESSLIST"];
            for(int i=0;i<array.size();i++)
            {
                int code = array[i]["DRESS_NUM"].asInt();
                int list = code%10000;
                
                switch(code/10000)
                {
                case 0:
                    setMapData(code);
                    xFashionWeekItem[xMap.type][xMap.listNum].isOpen = true;
                    xFashionWeekItem[xMap.type][xMap.listNum].key = array[i]["DRESS_KEY"].asInt();
                    xFashionWeekItem[xMap.type][xMap.listNum].nowCost = array[i]["VALUE"].asInt();
                    xFashionWeekItem[xMap.type][xMap.listNum].isExp = array[i]["STATE"].asInt()==0?false:true;
                    break;
                case 1:
                    xHairData[list].isClubOpen = true;
                    break;
                case 2:
                    xFaceData[list].isClubOpen = true;
                    break;
                }
            }
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_FASHIONWEEKFITTINGLIST_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xFashionWeek.isNet_FittingList = false;
            for(int ff=0;ff<SPRIT_IMGLAYERMAX;ff++)
                xClub.xMy.xF.code[ff] = DONT;
            
            xClub.xMy.gender = root["SEX"].asInt();
            xClub.xMy.xF.isInFitting = root["PUTIN"].asInt()==0?false:true;
            xClub.xMy.xFace.hairNum = root["HAIR"].asInt();
            xClub.xMy.xFace.faceNum = root["FACE"].asInt();
                
                
            xClub.xMy.xF.code[0] = root["LAYER0"].asInt();
            xClub.xMy.xF.code[1] = root["LAYER1"].asInt();
            xClub.xMy.xF.code[2] = root["LAYER2"].asInt();
            xClub.xMy.xF.code[3] = root["LAYER3"].asInt();
            xClub.xMy.xF.code[4] = root["LAYER4"].asInt();
            xClub.xMy.xF.code[5] = root["LAYER5"].asInt();
            xClub.xMy.xF.code[6] = root["LAYER6"].asInt();
            xClub.xMy.xF.code[7] = root["LAYER7"].asInt();
            xClub.xMy.xF.code[8] = root["LAYER8"].asInt();
            xClub.xMy.xF.code[9] = root["LAYER9"].asInt();
            xClub.xMy.xF.code[10] = root["LAYER10"].asInt();
            xClub.xMy.xF.code[11] = root["LAYER11"].asInt();
            xClub.xMy.xF.code[12] = root["LAYER12"].asInt();
            xClub.xMy.xF.code[13] = root["LAYER13"].asInt();
            xClub.xMy.xF.code[14] = root["LAYER14"].asInt();
            xClub.xMy.xF.code[15] = root["LAYER15"].asInt();
                
            setFashionStudioSlot();                
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_FASHIONWEEKFITTINGUPDATE_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xFashionWeek.isNet_FittingUpdate = false;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_PANGSTART_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xFashionWeek.isNet_PangStart = false;
            xClub.fashionWeekPlayCount = root["PLAYCOUNT"].asInt();
                
            xWorldMap.state = WORLDMAP_STATE_PANG;
            initPang();
            loadPangImg();
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        case 2:
            xFashionWeek.isNet_PangStart = false;
            xClub.fashionWeekPlayCount = 0;
            setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            sprintf(xPopup.strText, "하루 가능한 횟수를 초과하였습니다.");
            break;
        }
        break;
    case CMD_PANGRESULT_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xPang.isNet_pangResult = false;
            xClub.bestPangScore = root["SCORE"].asInt();      //내팡게임 최고점수                
            //root["VALUE"].asInt();      //내클럽기여도
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_FASHIONWEEKEXP_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xFashionWeek.isNet_Exp = false;
            xClub.xMy.clubLv = root["LEVEL"].asInt();
            xClub.xMy.clubExp = root["EXP"].asInt();
            break;
        case 1:	//실패
        case 2:	//중복완료
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_FASHIONWEEKSCOREUPDATE_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            xFashionWeek.isNet_Score = false;
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        }
        break;
    case CMD_CLUBDRESSBUY_RECV:
        switch(root["RESULT"].asInt())
        {
        case 0:	//성공
            if(root["DRESS_NUM"].asInt()<10000)
            {
                setMapData(xPopup.num);
                xFashionWeekItem[xMap.type][xMap.listNum].isOpen=true;
            }
            else if(root["DRESS_NUM"].asInt()>=10000&&root["DRESS_NUM"].asInt()<20000)
            {
                xHairData[xPopup.num].isClubOpen=true;
            }
            else
            {
                xFaceData[xPopup.num].isClubOpen=true;
            }
            xClub.money=root["MONEY"].asInt();
            break;
        case 1:	//실패
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        case 2:
            setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
            sprintf(xPopup.strText, "이미 소유 중인 의상입니다.");
            break;
        case 3:
            setPopup(POPUP_USERTEXT, playState, playState, 0, DONT);
            sprintf(xPopup.strText, "클럽 포인트가 부족합니다.");
            break;
        }
        break;
    case CMD_CLUBSTORAGYLIST_RECV:
        switch (root["RESULT"].asInt())
        {
        case 0:
            array = root["STORAGE"];
                memset(&xClubStorage.xData, 0x00, sizeof(xClubStorage.xData));
                
            xClubStorage.totalData=array.size();
            for(int i=0;i<array.size();i++)
            {
                xClubStorage.xData[i].count=array[i]["ITEM_COUNT"].asInt();
                xClubStorage.xData[i].num = array[i]["ITEM_INDEX"].asInt();
                sprintf(xClubStorage.xData[i].strName, "%s",xClubShop.xData[array[i]["ITEM_INDEX"].asInt()].strName);
            }
            break;
        case 1:
            setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
            break;
        default:
            break;
        }
        break;
            
    case CMD_CLUBITEMBUY_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                xClubStorage.xData[xClubShop.selectedNum].count=root["ITEM_COUNT"].asInt();
                setPopup(POPUP_CLUBSHOPITEMBUYOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                xClub.money=root["TOTAL_MONEY"].asInt();
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_CLUBSHOPTOLACKPOINT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 3:
                setPopup(POPUP_CLUBSHOPNOTMASTER, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 4:
                setPopup(POPUP_CLUBSHOPLOWLV, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            default:
                break;
            }
        break;
    case CMD_CLUBGIVEGIFT_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                xClubStorage.xData[xClubStorage.selectedNum].count=root["ITEM_COUNT"].asInt();
                setPopup(POPUP_CLUBGIVEGIFTOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBSTORAGEUPDATE, TRUE);
                xClubShop.selectMenu=CLUBSTORAGE;
                xClubStorage.state=CLUBSTORAGE_STATE_PLAY;
                
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_CLUBITEMTOLACKAMOUNT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 3:
                setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                sprintf(xPopup.strText, " 클라이언트 오류 Err: %d",root["RESULT"].asInt());
                break;
            case 4:
                setPopup(POPUP_CLUBGIFTNOTMASTER, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
                
        default:
            break;
        }
        break;
    case CMD_PANGCOUNTCHECK_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                xClub.fashionWeekPlayCount=root["COUNT"].asInt();
                
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            default:
                break;
        }
        break;
    case CMD_PANGTIMESRESET_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                if(xWorldMap.state == WORLDMAP_STATE_CLUBLOBBY&&xClubLobby.selectMenu==CLUBLOBBY_MENU_SHOP&&xClubShop.state==CLUBSTORAGE&&xClubStorage.state==CLUBSTORAGE_STATE_PLAY)
                {
                    addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CMD_CLUBITEMDELETE, TRUE);
                }
                setPopup(POPUP_PANGTIMESOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                xClub.fashionWeekPlayCount=root["COUNT"].asInt();
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_PANGTIMESNOCLUB, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 3:
                xMail.bTemp=true;
                setPopup(POPUP_PANGTIMESMAXTIMESEXCEED, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            default:
                break;
        }
        break;
    case CMD_CLUBNAMEMODIFY_RECV:
        switch(root["RESULT"].asInt())
        {
            case 0:
                sprintf(xClub.xMy.strName, "%s",root["CLUBNAME"].asCString());
                xClub.money=root["CLUBPOINT"].asInt();
                setPopup(POPUP_CLUBNAMEMODIFYOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                xClubShop.state=CLUBSHOP_STATE_PLAY;
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_CLUBNAMEMODIFYNOMASTER, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 3:
                xClubNameModify.bTemp=true;
                xClubNameModify.state=CLUBNAME_STATE_OVERLAPWORD;
                break;
            case 4:
                xClubNameModify.bTemp=true;
                xClubNameModify.state=CLUBNAME_STATE_TOLEAKWORD;
                break;
            case 5:
                setPopup(POPUP_CLUBSHOPTOLACKPOINT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
        }
    case CMD_CLUBITEMDELETE_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                xClubStorage.xData[xClubStorage.selectedNum].count=root["ITEM_COUNT"].asInt();
                if(xClubStorage.xData[xClubStorage.selectedNum].num==1)
                {
//                    setNewModel(1);
                }
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_USERTEXT, PLAY_PLAY,PLAY_PLAY,0,DONT);
                sprintf(xPopup.strText,"아이템 수량 없음");
                break;
            default:
                break;
        }
        break;
    case CMD_CLUBDONATIONCOUNT_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                xClub.xDonation[0].donationCount=root["GOLD_COUNT"].asInt();
                xClub.xDonation[1].donationCount=root["CANDY_COUNT"].asInt();
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            default:
                break;
            }
        break;
    case CMD_CLUBDONATION_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                initSecurity(&xSaveTemp.money, root["GOLD"].asInt());
                initSecurity(&xSaveTemp.tired, root["CANDY"].asInt());
                xClub.money=root["CLUB_MONEY"].asInt();
                xClub.xDonation[0].donationCount=root["GOLD_COUNT"].asInt();
                xClub.xDonation[1].donationCount=root["CANDY_COUNT"].asInt();
                
                //xClub.xMember[0].userKey == player,userkey
                xClub.xMember[xNetData.userNum].totalContribution=root["CONTRIBUTION"].asInt();
                
                switch (xClub.donationType)
                {
                    case 0:
                        setPopup(POPUP_CLUBDONATIONGOLDOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                        break;
                    case 1:
                        setPopup(POPUP_CLUBDONATIONCANDYOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                        break;
                    default:
                        break;
                }
                xEventQueueNet.key[xEventQueueNet.totalNum] = xClub.xMy.clubKey;
                addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBMEMBER, TRUE);
                xClubLobby.selectMenu=CLUBLOBBY_MENU_MAIN;
                clubLobbyFreeLoad(true);
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_CLUBDONATIONTOLEAKGOLD, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 3:
                setPopup(POPUP_CLUBDONATIONTOLEAKCANDY, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 4:
                switch (xClub.donationType)
                {
                    case 0:
                        setPopup(POPUP_CLUBDONATIONTOLEAKGOLDCOUNT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                        break;
                    case 1:
                        setPopup(POPUP_CLUBDONATIONTOLEAKCANDYCOUNT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        break;
    case CMD_CLUBICONLISTUPDATE_RECV:
        switch(root["RESULT"].asInt())
        {
            case 0:
                for(int k=0;k<CLUBICONMAX;k++)
                {
                    xClub.xIcon[k].isOpen=false;
                }
                xClub.xMy.clubIcon=root["NOWICON"].asInt();
                array = root["ICONLIST"];
                for(int i=0;i<array.size();i++)
                {
                    xClub.xIcon[i].index=array[i]["ICONNUM"].asInt();
                    xClub.xIcon[array[i]["ICONNUM"].asInt()].isOpen=true;
                    log("KBY2_%d",array[i]["ICONNUM"].asInt());
                }
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            default:
                break;
        }
        break;
    case CMD_CLUBICONBUY_RECV:
        switch(root["RESULT"].asInt())
        {
            case 0:
                xClub.xIcon[xClubIconShop.selectedNum].isOpen=true;
                xClub.money=root["CLUBPOINT"].asInt();
                setPopup(POPUP_CLUBICONBUYOK, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_CLUBICONBUYNOMASTER, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 3:
                setPopup(POPUP_CLUBICONBUYHAVEALREADYICON, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 4:
                setPopup(POPUP_CLUBICONBUYTOLEAKPOINT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 5:
                setPopup(POPUP_CLUBICONBUYTOLEAKLV, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
        }
        break;
    case CMD_CLUBICONUPDATE_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                xClub.xMy.clubIcon=root["NOWICON"].asInt();
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_CLUBICONCHANGENOMASTER, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 3:
                setPopup(POPUP_CLUBICONDONTHAVEICON, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            default:
                break;
        }
        break;
    case CMD_FORMERLISTUPDATE_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:                
                xFormer.totalData = 0;
                for(int i = 0; i < FORMERMAX; i++)
                    xFormer.itemCnt[i] = 0;
                array=root["INTERIORLIST"];
                for(int i=0;i<array.size();i++)
                {
                    
                    xFormer.xData[xFormer.totalData].key=array[i]["KEY"].asInt();
                    xFormer.xData[xFormer.totalData].index=array[i]["ITEM_INDEX"].asInt();
                    xFormer.xData[xFormer.totalData].state=array[i]["STATE"].asInt();
                    xFormer.xData[xFormer.totalData].endTime=array[i]["TIME"].asInt();
                    if( xFormer.xData[xFormer.totalData].index>0)
                    {
                        xFormer.itemCnt[xFormer.xData[xFormer.totalData].index%1000]++;
                        xFormer.count[xFormer.xData[xFormer.totalData].index%1000]=xFormer.itemCnt[xFormer.xData[xFormer.totalData].index%1000];
                    }
                    else
                    {
                        xFormer.itemCnt[(-xFormer.xData[xFormer.totalData].index)%1000]++;
                        xFormer.count[(-xFormer.xData[xFormer.totalData].index)%1000]=xFormer.itemCnt[(-xFormer.xData[xFormer.totalData].index)%1000];
                    }
                    xFormer.totalData++;
                }
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            default:
                break;
        }
        break;
    case CMD_FORMERSTART_RECV:
        switch (root["RESULT"].asInt())
        {
            case 0:
                xFormer.index=getFormerIndex(xNetFormer.key);
                xFormer.xData[xFormer.index].state=root["STATE"].asInt();
                //xFormer.xData[xFormer.index].endTime=root["TIME"].asInt();
                break;
            case 1:
                setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                break;
            case 2:
                setPopup(POPUP_NOTFORMER, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            case 3:
                setPopup(POPUP_FORMERCANT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                break;
            default:
                break;
        }
        break;
    case CMD_FORMERTAKEWEALTH_RECV:
        {
            switch (root["RESULT"].asInt())
            {
                case 0:
                    {
                        int Type=root["TYPE"].asInt();
                        int giftNum=root["VALUE"].asInt();
                        xFormer.index=getFormerIndex(xNetFormer.key);
                        switch (Type)
                        {
                            case 2:
                                {
                                    xFormer.xData[xFormer.index].state=root["STATE"].asInt();
                                    xFormer.xData[xFormer.index].endTime=root["TIME"].asInt();
                                    setMoney(giftNum);
                                }
                                break;
                            case 3:
                                {
                                    xFormer.xData[xFormer.index].state=root["STATE"].asInt();
                                    xFormer.xData[xFormer.index].endTime=root["TIME"].asInt();
                                    setCash(giftNum);
                                }
                                break;
                            case 4:
                                {
                                    xFormer.xData[xFormer.index].state=root["STATE"].asInt();
                                    xFormer.xData[xFormer.index].endTime=root["TIME"].asInt();
                                    setTired(giftNum);
                                }
                                break;
                            default:
                                break;
                        }
                        
                    }
                    break;
                case 1:
                    setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
                    break;
                case 2:
                    setPopup(POPUP_FORMERCANTTAKE, PLAY_PLAY, PLAY_PLAY, 0, DONT);
                    break;
                default:
                    break;
            }
        }
        break;
	case CMD_AUTOSELL_RECV:
		{
			switch (root["RESULT"].asInt())
			{
				case 0:
				{
//					int GOLD  = root["GOLD"].asInt();
//					setMoney(GOLD);
				}
					break;
				case 1:
					setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
					break;
				case 2:
					setPopup(POPUP_FORMERCANTTAKE, PLAY_PLAY, PLAY_PLAY, 0, DONT);
					break;
				default:
					break;
			}
		}
		break;
	case CMD_AUTOPRODUCT_RECV:
		{
			switch (root["RESULT"].asInt())
			{
				case 0:
				{
					array = root["DRESS"];
					
					for(int i=0;i<array.size();i++)
					{
						int code = array[i]["ITEM_INDEX"].asInt();
						int rever = code < 0?1:0;
						int type = code/1000;
						int list = code%1000;
						type = rever==0?type:-type;
						list = rever==0?list:-list;
						
						if(xWorldMap.isFriendMap == TRUE)
						{
							int minLv = xSaveTemp.lv.oriData <= xFriendData[xFriendMap.selectDataSlotNum].lv?xSaveTemp.lv.oriData:xFriendData[xFriendMap.selectDataSlotNum].lv;
							
							if(xInventoryFashion.isOpen[type][list] == TRUE && minLv >= xFashionData[type][list].lv && xFashionData[type][list].isStaff == 0)
							{
								xCatalog.xSlotFriendOrder[type][xCatalog.totalSlotFriendOrder[type]++].code = code;
							}
							
						}
						else
						{
							xInventoryFashion.isOpen[type][list] = TRUE;
							xInventoryFashion.haveNum[type][list] = array[i]["ITEM_COUNT"].asInt();
						}
					}
					
					//setSellSelectItemSlot();
					xSell.totalSlot = 0;
					
					for(int z=0;z<7;z++)
					{
						for(int t=0;t<FASHIONDATAMAX;t++)
						{
							if(xSell.totalSlot>256)
								break;
							
							if(z <= 3 && xInventoryFashion.haveNum[z][t] > 0 && xFashionData[z][t].isStaff == 0)
							{
								xSell.xSlot[xSell.totalSlot++].maxNum = xInventoryFashion.haveNum[z][t];
							}
							else if(z >= 4 && xInventoryFashion.haveNum[z][t] > 0 && (xFashionData[z][t].isStaff == 0 || xFashionData[z][t].isStaff == 3))
							{
								xSell.xSlot[xSell.totalSlot++].maxNum = xInventoryFashion.haveNum[z][t]%xFashionData[z][t].makeNum.oriData;
							}
						}
					}
					
					if(xAutoProduct.isSleep == TRUE)
					{
						setPopup(POPUP_AUTOPRODUCTSLEEP, xPopup.yes, xPopup.no, 0, DONT);
						sprintf(xPopup.strText, "의상 %d벌을 획득했습니다.", xAutoProduct.sleepCount);
						xAutoProduct.isSleep = FALSE;
					}
					
					
					if(xAutoSell.isSleep == TRUE)
					{
						setPopup(POPUP_AUTOSELLSLEEP, xPopup.yes, xPopup.no, 0, DONT);
						sprintf(xPopup.strText, "의상판매로 %d골드를 획득했습니다.", xAutoSell.gold);
						xAutoSell.isSleep = FALSE;
						xAutoSell.gold = 0;
					}
					
				}
					break;
				case 1:
					setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
					break;
				case 2:
					setPopup(POPUP_FORMERCANTTAKE, PLAY_PLAY, PLAY_PLAY, 0, DONT);
					break;
				default:
					break;
			}
		}
			break;
	case CMD_AUTOPRODUCTSLOTUPDATE_RECV:
		{
			switch (root["RESULT"].asInt())
			{
			case 0:
				break;
			case 1:
				setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
				break;
			case 2:
				setPopup(POPUP_FORMERCANTTAKE, PLAY_PLAY, PLAY_PLAY, 0, DONT);
				break;
			default:
				break;
			}
		}
		break;
			
		default:
			switch(root["RESULT"].asInt())
		{
		case 0:	//성공
			break;
		case 1:	//실패
			setPopup(POPUP_SERVERERR, playState, playState, 0, root["PROTOCOL"].asInt());
			break;
		}
		break;
	}
	
	if(xInventoryFashion.haveNum[0][13] > 0)
		printf("setRecv2 >>>%d\n",xInventoryFashion.haveNum[0][13]);
}



void urlBuffUpLoad(char *buff, int userkey, int fileSize)
{
    char url[128];
    sprintf(url, "%s/ImageUpload.aspx",xNetData.strImgServerUrl);
	
    HttpRequest *request = new HttpRequest();
    char strTemp[32];
	
    request->setUrl(url);
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback(xGame.layer,callfuncND_selector(FashionShop::onHttpRequestCompleted));
	
    std::vector<std::string> headers;
    headers.push_back("Content-Type: image/png");
    sprintf(strTemp, "usernum: %d",userkey);
    headers.push_back(strTemp);
    sprintf(strTemp, "filesize: %d",fileSize);
    headers.push_back(strTemp);
	
    printf("url>>%s\n",url);
    printf("headers>>%s\n",headers[0].c_str());
    printf("headers>>%s\n",headers[1].c_str());
    printf("headers>>%s\n",headers[2].c_str());
    
    request->setHeaders(headers);
    request->setRequestData(buff, fileSize);
    
    HttpClient::getInstance()->send(request);
    request->release();
}

void parserJson(char *str)
{
	if(str[0] == '"')
	{
		for(int j = 0; j < strlen(str); j++)
		{
			str[j] = str[j+1];

			if(str[j] == '"')			
				str[j] = NULL;			
		}
	}
}


