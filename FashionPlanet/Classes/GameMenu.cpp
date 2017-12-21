#include "Global.h"


Xdialog xDialog;

XIMG imgScrollMenu[SCROLLMENUMAX];

XIMG imgPopupNpc[4];

XIMG imgPopupSub[10];

XIMG imgPopupNpcProfile[10];
XIMG imgPopupNpcProfileIcon[10];


XCALENDAR xCalendar;
XMENU xMenu;
XCLR xClr;

void setPopup(M_Int32 type, M_Int32 yes, M_Int32 no,int speakingNpc,M_Int32 setTemp)
{
	int lookNum = 0;
    
    if(xWorldMap.state == WORLDMAP_STATE_EVENTQUEST)
    {
        
    }
    else
    {
        playSnd(SND_POPUP_SHOW);
    }
	playState = PLAY_MSG;
	if(speakingNpc != DONT)
	{
		if(xPopup.speakingNpcNum != speakingNpc)
		{
			xPopup.speakingNpcNum = speakingNpc;
			
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
	}
	xPopup.msgType = type;
	xPopup.yes = yes;
	xPopup.no = no;
	xPopup.select = POPUPYES;
	xPopup.state = MENU_STATE_IN;
	xPopup.anyCnt = 0;
	xPopup.textLine = 0;
	xPopup.num = setTemp;
	
	
	switch(xPopup.msgType)
	{
	case POPUP_USERTEXT:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"유저지정문자");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_AUTOSELLSLEEP:
	case POPUP_AUTOPRODUCTSLEEP:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText, "유저지정문자");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
		case POPUP_KAKAOCARSTORAGE:
		if(xFriendData[xOrder.xSlotListData[xOrder.slotNumList[xOrder.selectSlot]].friendNum].isKakaoMessage == FALSE)
		{
			sprintf(xPopup.strTitle,"주문 받은 의상 보내기");
			sprintf(xPopup.strText,"'%s'님께 카카오톡 메시지와 함께\n의상을 배송하시겠습니까?\n(수신거부 친구로 캔디 %d개를 추가 보상으로\n지급 받지만 메시지는 발송되지 않습니다.)",xFriendData[xOrder.xSlotListData[xOrder.slotNumList[xOrder.selectSlot]].friendNum].strNickName,xKakaoData.socialBonusCarStorage);
		}
		else
		{
			sprintf(xPopup.strTitle,"주문 받은 의상 보내기");
			sprintf(xPopup.strText,"'%s'님께 카카오톡 메시지와 함께\n의상을 배송하시겠습니까?\n(카카오톡 친구는 캔디 %d개를 추가 보상으로 지급 받습니다.)",xFriendData[xOrder.xSlotListData[xOrder.slotNumList[xOrder.selectSlot]].friendNum].strNickName,xKakaoData.socialBonusCarStorage);
		}
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_KAKAOFRIENDMAP:
		if(xFriendData[xFriendMap.selectDataSlotNum].isKakaoMessage == FALSE)
		{
			sprintf(xPopup.strTitle,"헬프 요청 보내기");
			sprintf(xPopup.strText,"'%s'님께 카카오톡 메시지로\n헬프 요청을 하시겠습니까?\n(수신 거부 친구로 헬프 요청 시 캔디 %d개를 지급\n받지만 메시지는 발송되지 않습니다.)",xFriendData[xFriendMap.selectDataSlotNum].strNickName,xKakaoData.socialBonusHelp);
		}
		else
		{
			sprintf(xPopup.strTitle,"헬프 요청 보내기");
			sprintf(xPopup.strText,"'%s'님께 카카오톡 메시지로\n헬프 요청을 하시겠습니까?\n(헬프 요청 시 캔디 %d개를 지급받습니다.)",xFriendData[xFriendMap.selectDataSlotNum].strNickName,xKakaoData.socialBonusHelp);
		}
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_KAKAOORDERITEM:
		if(xFriendData[xFriendMap.selectDataSlotNum].isKakaoMessage == FALSE)
		{
			sprintf(xPopup.strTitle,"주문배송 요청하기");
			sprintf(xPopup.strText,"'%s'님께 카카오톡 메시지와 함께\n주문배송을 요청하시겠습니까?\n(수신거부 친구로 캔디 %d개를 보상으로 지급 받지만\n메시지는 발송되지 않습니다.)",xFriendData[xFriendMap.selectDataSlotNum].strNickName,xKakaoData.socialBonusOrderSelectItem);

		}
		else
		{
			sprintf(xPopup.strTitle,"주문배송 요청하기");
			sprintf(xPopup.strText,"'%s'님께 카카오톡 메시지와 함께\n주문배송을 요청하시겠습니까?\n(카카오톡 친구 주문배송 요청 시 총 획득 캔디 %d개)",xFriendData[xFriendMap.selectDataSlotNum].strNickName,xKakaoData.socialBonusOrderSelectItem);
		}
		xPopup.btnType = BTN_YESNO;
		break;
    case POPUP_FRIENDDEL:
        sprintf(xPopup.strTitle,"친구삭제");
        sprintf(xPopup.strText,"%s님을 친구리스트에서\n삭제하시겠습니까?",xFriendData[xFriendMap.selectDataSlotNum].strNickName);
        xPopup.btnType = BTN_YESNO;
        break;
	case POPUP_GUESTLOGINYESNO:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"게임삭제,디바이스 변경,탈퇴 시\n모든 데이터가 삭제 되며\n복구되지 않습니다\n게스트 로그인 하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_UNREGISTEREDYESNO:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"게임 탈퇴시 모든데이터가 초기화\n되며 복구되지 않습니다\n정말 탈퇴하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_G9_LINK:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"G9앱을 설치하시면 %d룩을 드려요!\n이동하시겠습니까?",G9BONUSCASH);
		xPopup.btnType = BTN_YESNO;
		break;
    case POPUP_SELLFAST:
        sprintf(xPopup.strTitle,"알림");
        sprintf(xPopup.strText,"판매를 즉시완료하시겠습니까?");
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_PRODUCTIONFAST:
    case POPUP_PRODUCTIONFAST2:
        sprintf(xPopup.strTitle,"알림");
        sprintf(xPopup.strText,"제작을 즉시완료하시겠습니까?");
        xPopup.btnType = BTN_YESNO;
        break;
	case POPUP_UNREGISTEREDOK:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"계정이 삭제되었습니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_GUESTMODE:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"게스트모드에서는\n이용하실수 없습니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_RUNWAYSTARTERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"참가하실 모델을 선택해주세요");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_SERVER_TIMEOVER:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"서버와의 연결이 원활하지 않습니다.\n잠시후 다시 시도해 주세요.\n(에러코드:%d)",2000+xPopup.num);
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_KAKAOLOGINERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText, "해당 사용자의 카카오\n계정 정보를 찾을 수 없습니다\n재로그인 바랍니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_KAKAOLOGINERR22:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText, "access_token이 만료\n혹은 유효하지 않은 상태\n재로그인해주세요");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_IDREMAKE:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"등록된 아이디가 있습니다.\n종료후 다시 실행주세요.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
    /*case POPUP_TESTTEST:
            sprintf(xPopup.strTitle,"알림");
            sprintf(xPopup.strText,"ㅁㅁㅁㅁㅁ.종료후 다시 실행주세요.");
            xPopup.btnType = BTN_YESNO;
            break;*/
	case POPUP_SHOP_REVIEWYESNO:
		sprintf(xPopup.strTitle,"더 많은 유저들과\n함께 해요~");
		sprintf(xPopup.strText,"아이러브패션과 함께 즐거운 시간\n보내고 계신가요? 리뷰와 별점을\n남겨주시면 아이러브패션에게\n큰 힘이 됩니다.");
		xPopup.btnType = BTN_LINKNO;
		break;
	case POPUP_LOGOUTYESNO:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"로그아웃 하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_LOGOUT:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"로그아웃되었습니다.\n게임을 종료합니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_TEST_AFTERMAKE:			//구현중입니다.
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"구현중입니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_ADDSELLTABLEERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"해당층에 진열이 불가능합니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
    case POPUP_AMULETBUY:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText,"[%s]를(을)\n구매하시겠습니까?",xAmulet.xData[xAmuletSetting.xEditPage.amuletCode].strName);
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_AMULETPAGEBUY:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText,"저장페이지를\n%d룩을 사용하여\n오픈하시겠습니까?",xAmulet.xAmuletPage[xPopup.num].pagePrice);
        xPopup.btnType = BTN_YESNO;
        break;
	case POPUP_SALESHOPBUYYESNO:
		sprintf(xPopup.strTitle,"구매");
		setMapData(xSaleShop.slotCode[xSaleShop.selectSlot]);
		sprintf(xPopup.strText,"[%s]를(을)\n%d룩을 사용하여\n구매하시겠습니까?\n(상품은 보관함으로 이동됩니다)",xObj.xObjData[xMap.type][xMap.listNum].strName,xSaleShop.slotSalePrice[xSaleShop.selectSlot]);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_TIREDEMPTY:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"캔디가 부족합니다.\n캔디를 구매하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
    case POPUP_RIVALSTOP:
        sprintf(xPopup.strTitle,"알림");
        sprintf(xPopup.strText,"라이벌과의 대결을\n포기하시겠습니까?");
        xPopup.btnType = BTN_YESNO;
        break;
	case POPUP_CARORDER_FASTCASH:
		setMapData(xProductionMenu.slotCode[xProductionMenu.selectType][xProductionMenu.selectSlot]);
		sprintf(xPopup.strTitle,"즉시 완료");
		sprintf(xPopup.strText,"%d룩을 사용하여\n즉시완료 하시겠습니까?",xPopup.num);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_MONEYEMPTY:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"골드가 부족합니다.\n골드를 구매하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_CASHEMPTY:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"룩이 부족합니다.\n룩을 구매하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_FAMEEMPTY:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"명성도가 부족합니다.\n인테리어를 추가 배치해\n명성도를 획득해주세요.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_BUILDMAXERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"설치개수초과");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_PRODUCTIONLINKFASHIONSHOWYESNO:
		sprintf(xPopup.strTitle,"의상오픈");
		sprintf(xPopup.strText,"패션쇼 점수 %d점 이상\n획득해야 획득 가능합니다.\n패션쇼를 이용하시겠습니까?",xPopup.num);
		xPopup.btnType = BTN_LINKNO;
		break;
	case POPUP_FASHIONBUYYESNO:
		setMapData(xCatalog.xSlotS[xCatalog.selectSlot].code);	//xMap.rever,xMap.type,xMap.listNum 구하기
		sprintf(xPopup.strTitle,"구매하기");
		sprintf(xPopup.strText,"<%s>\n해당의상을 오픈하시겠습니까?",xFashionData[xMap.type][xMap.listNum].strName);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_INPUTINVENTORYERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"판매중인 상품이 있습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_SHOP_GUESTLOGINEND:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"게스트플레이가 끝나\n게임이 종료됩니다.\n카카오계정으로 로그인해주세요");

		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_FITTING_LAYEREDERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"레이어드 횟수가\n초과 되었습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_SERVERCHECK:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"서버점검중입니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_MODELUPGRADEFAIL:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"모델 업그레이드에\n실패하였습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_TUTO_LIMIT:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"튜토리얼중 이용하실수 없습니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_MODELVOTEERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"친구당 추천은\n하루에 한번만 가능합니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_SERVERERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"서버와의 연결이 원활하지 않습니다.\n잠시후 다시 시도해 주세요.\n(에러코드:%d)",xPopup.num);
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_APPSTOREUPGRADEYESNO:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"최신버전으로 업데이트 하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_RESUPGRADEYESNO:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"리소스 업데이트를 하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_MAIL_DELYESNO:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"해당글을 삭제하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_LOGINERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"아이디 또는 패스워드가\n불일치합니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_MODELGUESTERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"게스트 지정은 S등급\n모델만 이용가능합니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_LOGINERR2:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"로그인실패");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_VOTEERR0:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"자신에게는 투표하실수 없습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_BESTDESIGNERCLOSE:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"대회시간이 지나 정상\n저장되지 않았습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_BLACKUSER:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"블럭된 유저입니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_LOGINERRRRRRRRR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"중복 로그인입니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_IDMAKEERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"계정생성 실패");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_PAYMENTBUILDERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"계산대는 각층당 1개만\n설치가능합니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_RESDOWNYESNO:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"리소스버전(Ver.%d)을\n업데이트하시겠습니까?",xSave.resVer);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_QUEST_FASTCASHYESNO:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"%d룩을 사용하여\n즉시완료 하시겠습니까?",xPopup.num);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_PROFILEERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"200kb이하로만\n등록하실수 있습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_ORDER_OPENERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"해당의상 오픈후\n제작가능합니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_ORDER_OPENERR_CAR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"차량 선택후 이용가능합니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_MARKETINGMAX:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"상대방의 마케팅친구초과로\n등록에 실패하였습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_TAKEPART_ERR0:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"이미 참가중이십니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_PRODUCTION_FLOORERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"해당층에 설치하실수 없습니다\n(1층:캐쥬얼,2층:명품)");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_TAKEPART_ERR1:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"참가시간이 종료되었습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_MODEL_SLOTMAX:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"더이상 추가하실수 없습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_QUESTDELERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"퀘스트의상은\n버리실수 없습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_ORDERQUESTDELERR:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"QUEST주문장은\n거절하실수 없습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
    case POPUP_SHOP_PACKAGEBUY:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText, "%s를 %d원에\n구매하시겠습니까?",xPackageData[xPackagePopup.selectType].strName,xPackageData[xPackagePopup.selectType].price);
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_SHOP_PREPAYBUY:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText, "정액제를 %d원에\n구매하시겠습니까?",xPrePay.price);
        xPopup.btnType = BTN_YESNO;
        break;
	case POPUP_SHOP_BUYYESNOCASH:
		if(xWorldMap.isCashGift == TRUE)	//선물보내기
		{
			int slotNum = getFriendSlot(xCashGift.friendUserNum);
			
			sprintf(xPopup.strTitle,"선물");
			lookNum = xShop.moneyPoint[xShop.selectSlot].oriData;
			sprintf(xPopup.strText, "%d 룩을 %d원에\n구매 하여 %s님에게\n선물 하시겠습니까?",lookNum,xShop.moneyPrice[xShop.selectSlot].oriData,xFriendData[slotNum].strNickName);
		}
		else
		{
			sprintf(xPopup.strTitle,"구매");
			if(xWorldMap.isFirstIap == TRUE)
				lookNum = xShop.moneyPoint[xShop.selectSlot].oriData+xShop.moneyPriceFirstBonus[xShop.selectSlot];
			else
				lookNum = xShop.moneyPoint[xShop.selectSlot].oriData;
			sprintf(xPopup.strText, "%d 룩을 %d원에\n구매하시겠습니까?",lookNum,xShop.moneyPrice[xShop.selectSlot].oriData);
		}
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_SHOP_BUYYESNOGOLD:
		sprintf(xPopup.strTitle,"구매");
		setCommaNum(strTempB, xShop.moneyPoint[xShop.selectSlot].oriData);
		sprintf(xPopup.strText, "%s 골드를 %d룩을\n사용하여 구매하시겠습니까?",strTempB,xShop.moneyPrice[xShop.selectSlot].oriData);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_SHOP_PREMIUM_BUYYESNO:
		sprintf(xPopup.strTitle,"구매");
		xPopup.btnType = BTN_YESNO;
		
		switch(xShop.premiumPriceType[xShop.selectSlot])
		{
		case 0:		//골드
			setCommaNum(strTempB, xShop.premiumPrice[xShop.selectSlot].oriData);
			sprintf(xPopup.strText, "%s를(을) %s골드\n사용하여 구매하시겠습니까?",xShop.strPremiumName[xShop.selectSlot],strTempB);
			break;
		case 1:		//룩
			sprintf(xPopup.strText, "%s를(을) %d룩을\n사용하여 구매하시겠습니까?",xShop.strPremiumName[xShop.selectSlot],xShop.premiumPrice[xShop.selectSlot].oriData);
			break;
		case 2:		//캔디
			sprintf(xPopup.strText, "%s를(을) %d캔디를\n사용하여 구매하시겠습니까?",xShop.strPremiumName[xShop.selectSlot],xShop.premiumPrice[xShop.selectSlot].oriData);
			break;
		}
		break;
	case POPUP_MODELGIFTFASTCASHYESNO:
		sprintf(xPopup.strTitle,"즉시완료");
		sprintf(xPopup.strText,"%d룩을 사용하여\n즉시완료 하시겠습니까?",getFastTimeCash((xModelMainSlot[xModel.selectMainSlot].endTime - xCalendar.nowTime)));
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_CARQUESTOPEN:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"특정 퀘스트 클리어시 오픈");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_ORDER_SLOTFULL:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"비어있는 생산슬롯이 없습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_PRODUCTION_OPENYESNO:
		sprintf(xPopup.strTitle,"슬롯오픈");
		sprintf(xPopup.strText,"%d룩을 사용하여\n오픈하시겠습니까?",xProductionMenu.openCash[PRODUCTIONMENU_TYPE_PREMIUM][xPopup.num].oriData);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_LOCK_MAINQUEST:
		sprintf(xPopup.strTitle,"이용제한");
		sprintf(xPopup.strText,"%s 클리어후\n이용가능(메인퀘스트Lv.%d)",xQuestDataMain[xPopup.num].strTitle,xQuestDataMain[xPopup.num].lv);
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_CAR_BUYYESNO:
		sprintf(xPopup.strTitle,"구매");
		if(xWorldMap.isCashShop == TRUE)
		{
			subTemp[12] = xShop.carSlot[xShop.selectSlot];
		}
		else
		{
			subTemp[12] = xCar.slotCode[xCar.selectSlot];
		}
		
		switch(xCarData[subTemp[12]].priceType)
		{
		case 0:		//골드
			setCommaNum(strTempB, xCarData[subTemp[12]].price.oriData);
			sprintf(xPopup.strText, "%s를(을) %s골드\n사용하여 구매하시겠습니까?",xCarData[subTemp[12]].strName,strTempB);
			break;
		case 1:		//룩
			sprintf(xPopup.strText, "%s를(을) %d룩을\n사용하여 구매하시겠습니까?",xCarData[subTemp[12]].strName,xCarData[subTemp[12]].price.oriData);
			break;
		}		
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_ORDER_5LIMIT:
		sprintf(xPopup.strTitle,"알림");
	sprintf(xPopup.strText,"하루 신청횟수를\n초과하였습니다(10회)");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_ORDER_1DAY1:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"친구당 하루1번만 가능합니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_HACKINGPACKAGE:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"비정상적인 프로그램이\n감지되어\n게임을 종료합니다.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_ORDER_10LIMIT:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"하루 수락횟수를\n초과하였습니다(10회)");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_FRIEND_100LIMIT:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"150명 이상\n등록하실수 없습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_SOCIALPOINT_3LIMIT:
		sprintf(xPopup.strTitle,"알림");
		sprintf(xPopup.strText,"Social포인트를\n모두사용하셨습니다");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
	case POPUP_MODELMAIN_SLOTOPENGOLD:
	case POPUP_MODELMAIN_SLOTOPENCASH:

		sprintf(xPopup.strTitle,"슬롯 구매");
		sprintf(xPopup.strText,"해당 슬롯을\n구매하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_MODELMAIN_DEL:
		sprintf(xPopup.strTitle,"해제");
		sprintf(xPopup.strText,"해당 모델을\n활동해제 하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_BUILD_PAYMENTERR:
		sprintf(xPopup.strTitle,"구매");
		sprintf(xPopup.strText,"보관함에 이미 보유중인 카운터 입니다.\n구매를 진행하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_MUSIC_BUYYESNO:
		sprintf(xPopup.strTitle,"BGM");
		sprintf(xPopup.strText,"해당 BGM을\n구매하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_ORDERDEL:
		sprintf(xPopup.strTitle,"삭제");
		sprintf(xPopup.strText,"처리하지 않은 주문장입니다.\n삭제 하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_MUSIC_CHANGEYESNO:
		sprintf(xPopup.strTitle,"BGM");
		sprintf(xPopup.strText,"해당 BGM으로\n변경하시겠습니까?");
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_TEST_ALLTILE:
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_MODEL_SELLYESNO:
		sprintf(xPopup.strTitle,"판매");
		switch(xModelData[xInventoryModel[xModel.infoInventoryNum].code].priceType)
		{
		case 0:		//골드
			sprintf(xPopup.strText,"%d골드에\n판매하시겠습니까?",xModelData[xInventoryModel[xModel.infoInventoryNum].code].price*MODELSELLPER/100);
			break;
		case 1:		//룩
			sprintf(xPopup.strText,"%d골드에\n판매하시겠습니까?",xModelData[xInventoryModel[xModel.infoInventoryNum].code].price*MODELSELLCASH);
			break;
		}
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_EXTENSION_BUYYESNO_TILE:
		sprintf(xPopup.strTitle,"확장");
		switch(xExtensionShop.xSlotTile[xExtensionShop.selectSlot].priceType)
		{
		case 0:		//골드
			setCommaNum(strTempB, xExtensionShop.tilePrice[xExtensionShop.xSlotTile[xExtensionShop.selectSlot].tile][xExtensionShop.xSlotTile[xExtensionShop.selectSlot].priceType].oriData);
			sprintf(xPopup.strText, "%s골드를\n사용하여 확장하시겠습니까?",strTempB);
			break;
		case 1:		//룩
			sprintf(xPopup.strText, "%d룩을\n사용하여 확장하시겠습니까?",xExtensionShop.tilePrice[xExtensionShop.xSlotTile[xExtensionShop.selectSlot].tile][xExtensionShop.xSlotTile[xExtensionShop.selectSlot].priceType].oriData);
			break;
		}
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_EXTENSIONWALL_EQUIPYESNO:
		sprintf(xPopup.strTitle,"변경");
		sprintf(xPopup.strText, "%s으로\n변경하시겠습니까?",xExternalWallData.strName[xExternalWall.listSlot[xExtensionShop.selectSlot]]);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_EXTENSIONWALL_BUYYESNO:
		sprintf(xPopup.strTitle,"구매");
		switch(xExternalWallData.priceType[xExternalWall.listSlot[xExtensionShop.selectSlot]])
		{
		case 0:		//골드
			setCommaNum(strTempB, xExternalWallData.price[xExternalWall.listSlot[xExtensionShop.selectSlot]]);
			sprintf(xPopup.strText, "%s를(을) %s골드를\n사용하여 구매하시겠습니까?",xExternalWallData.strName[xExternalWall.listSlot[xExtensionShop.selectSlot]],strTempB);
			break;
		case 1:		//룩
			sprintf(xPopup.strText, "%s를(을) %d룩을\n사용하여 구매하시겠습니까?",xExternalWallData.strName[xExternalWall.listSlot[xExtensionShop.selectSlot]],xExternalWallData.price[xExternalWall.listSlot[xExtensionShop.selectSlot]]);
			break;
		}
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_EXTENSION_BUYYESNO:
		sprintf(xPopup.strTitle,"증축");
		switch(xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].priceType)
		{
		case 0:		//골드
			setCommaNum(strTempB, xExtensionShop.floorPrice[xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].floor][xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].priceType].oriData);
			sprintf(xPopup.strText, "%s골드를 사용하여\n증축하시겠습니까?",strTempB);
			break;
		case 1:		//룩
			sprintf(xPopup.strText, "%d룩을 사용하여\n증축하시겠습니까?",xExtensionShop.floorPrice[xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].floor][xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].priceType].oriData);
			break;
		}
		
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_KAKAOINVEITEYESNO:
		sprintf(xPopup.strTitle,"초대");
		sprintf(xPopup.strText, "%s님에게 카카오톡으로\n초대메시지를 보내시겠습니까?",xKakaoData.xFriendInfo[xKakaoData.inveiteKakaoSlotNum].strNickName);
		xPopup.btnType = BTN_YESNO;
		break;
	case POPUP_EXTENSION_ERR:
		sprintf(xPopup.strTitle,"증축");
		sprintf(xPopup.strText, "증축을 위해 2층으로 올라가기위한\n마지막 벽 공간을 비워주세요.");
		xPopup.btnType = BTN_OK_CONFIRM;
		break;
    case POPUP_SHOP_HOTDEALBUY:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText,"해당 상품을\n구매하시겠습니까?\n(상품은 보관함으로 이동됩니다)");
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_CLUBMAKE:
        sprintf(xPopup.strTitle,"클럽");
        sprintf(xPopup.strText,"클럽을 개설하시겠습니까?\n(개설 후 클럽명 변경불가)");
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_CLUBMAKEOK:
        sprintf(xPopup.strTitle,"클럽");
        sprintf(xPopup.strText, "클럽을 개설하였습니다.");
        xPopup.btnType = BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBJOINOK:
        sprintf(xPopup.strTitle,"클럽");
        sprintf(xPopup.strText, "가입처리되었습니다.");
        xPopup.btnType = BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBMASTERYESNO:
        sprintf(xPopup.strTitle,"위임");
        sprintf(xPopup.strText,"%s님에게\n권한을 위임하시겠습니까?",xFriendData[getFriendSlot(xClub.xMember[xClubLobby.selectSlot].userKey)].strNickName);
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_CLUBFORCEOUTYESNO:
        sprintf(xPopup.strTitle,"추방");
        sprintf(xPopup.strText,"%s님을\n클럽에서 추방하시겠습니까?",xFriendData[getFriendSlot(xClub.xMember[xClubLobby.selectSlot].userKey)].strNickName);
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_CLUBUNREGYESNO:
        sprintf(xPopup.strTitle,"탈퇴");
        sprintf(xPopup.strText,"%s클럽에서\n탈퇴하시겠습니까?",xClub.xMy.strName);
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_CLUBUNREGOK:
        sprintf(xPopup.strTitle,"탈퇴");
        sprintf(xPopup.strText,"탈퇴처리되었습니다.");
        xPopup.btnType = BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBBOOKDEL:
        sprintf(xPopup.strTitle,"삭제");
        sprintf(xPopup.strText,"삭제하시겠습니까?");
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_FASHIONWEEKHAIRBUY:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText,"구매하시겠습니까?");
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_FASHIONWEEKFACEBUY:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText,"구매하시겠습니까?");
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_FASHIONWEEKFASHIONBUY:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText,"구매하시겠습니까?");
        xPopup.btnType = BTN_YESNO;
        break;
    case POPUP_CLUBSHOPITEMBUYCHECK:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText,"%s\n 아이템을 구매하시겠습니까?", xClubShop.xData[xClubShop.selectedNum].strName);
        xPopup.btnType=BTN_YESNO;
        break;
    case POPUP_CLUBSHOPITEMBUYOK:
        sprintf(xPopup.strTitle, "구매");
        sprintf(xPopup.strText, "%s\n 아이템을 구매하였습니다.", xClubShop.xData[xClubShop.selectedNum].strName);
        xPopup.btnType=BTN_OK_CONFIRM;
        break;

    case POPUP_CLUBSHOPTOLACKPOINT:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText, "클럽 포인트가 부족합니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
            
    case POPUP_CLUBSHOPNOTMASTER:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText, "클럽 마스터만 구매 할 수 있습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
            
    case POPUP_CLUBSHOPLOWLV:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText, "클럽 레벨이 낮습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
            
    case POPUP_CLUBITEMTOLACKAMOUNT:
        sprintf(xPopup.strTitle, "선물하기");
        sprintf(xPopup.strText, "아이템 개수가 부족합니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
            
    case POPUP_CLUBGIFTNOTMASTER:
        sprintf(xPopup.strTitle,"선물하기");
        sprintf(xPopup.strText, "클럽 마스터만 선물 할 수 있습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
            
    case POPUP_CLUBGIVEGIFTCHECK:
        sprintf(xPopup.strTitle,"구매");
        sprintf(xPopup.strText,"%s\n 아이템을 선물하시겠습니까?", xClubStorage.xData[xClubStorage.selectedNum].strName);
        xPopup.btnType=BTN_YESNO;
        break;
            
    case POPUP_CLUBGIVEGIFTOK:
        sprintf(xPopup.strTitle,"선물하기");
        sprintf(xPopup.strText, "아이템을 선물하였습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    
    case POPUP_CLUBNAMEMODIFYNOMASTER:
        sprintf(xPopup.strTitle, "클럽명 변경");
        sprintf(xPopup.strText,"클럽 마스터만 변경 할 수 있습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    
    case POPUP_CLUBNAMEMODIFYOK:
        sprintf(xPopup.strTitle, "클럽명 변경");
        sprintf(xPopup.strText, "클럽명 변경에 성공하였습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
            
    case POPUP_CLUBDONATIONGOLDCHECK:
        setCommaNum(strTempS, xSaveTemp.money.oriData);
        sprintf(xPopup.strTitle,"골드로 기부");
        sprintf(xPopup.strText,"골드를 소모하여\n 클럽에 기부하시겠습니까?", strTempS);
        xPopup.btnType=BTN_YESNO;
        break;
    case POPUP_CLUBDONATIONGOLDOK:
        sprintf(xPopup.strTitle,"골드로 기부");
        sprintf(xPopup.strText,"골드를 소모하여\n 클럽에 기부하였습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBDONATIONTOLEAKGOLD:
        sprintf(xPopup.strTitle,"골드로 기부");
        sprintf(xPopup.strText,"골드가 부족합니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBDONATIONTOLEAKGOLDCOUNT:
        sprintf(xPopup.strTitle,"골드로 기부");
        sprintf(xPopup.strText,"하루 기부 횟수를 초과하였습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBDONATIONCANDYCHECK:
        setCommaNum(strTempS, xSaveTemp.tired.oriData);
        sprintf(xPopup.strTitle,"캔디로 기부");
        sprintf(xPopup.strText,"캔디를 소모하여\n 클럽에 기부하시겠습니까?", strTempS);
        xPopup.btnType=BTN_YESNO;
        break;
    case POPUP_CLUBDONATIONCANDYOK:
        sprintf(xPopup.strTitle,"캔디로 기부");
        sprintf(xPopup.strText,"캔디를 소모하여\n 클럽에 기부하였습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBDONATIONTOLEAKCANDY:
        sprintf(xPopup.strTitle,"캔디로 기부");
        sprintf(xPopup.strText,"캔디가 부족합니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBDONATIONTOLEAKCANDYCOUNT:
        sprintf(xPopup.strTitle,"캔디로 기부");
        sprintf(xPopup.strText,"하루 기부 횟수를 초과하였습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBICONBUYCHECK:
        sprintf(xPopup.strTitle,"클럽 아이콘 구매");
        sprintf(xPopup.strText,"해당 아이콘을 구매하시겠습니까?");
        xPopup.btnType=BTN_YESNO;
        break;
    case POPUP_CLUBICONBUYOK:
        sprintf(xPopup.strTitle,"클럽 아이콘 구매");
        sprintf(xPopup.strText,"해당 아이콘을 구매하였습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBICONBUYNOMASTER:
        sprintf(xPopup.strTitle,"클럽 아이콘 구매");
        sprintf(xPopup.strText,"클럽 마스터만 구매할 수 있습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBICONBUYHAVEALREADYICON:
        sprintf(xPopup.strTitle,"클럽 아이콘 구매");
        sprintf(xPopup.strText,"이미 소유 중인 아이콘입니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBICONBUYTOLEAKPOINT:
        sprintf(xPopup.strTitle,"클럽 아이콘 구매");
        sprintf(xPopup.strText,"클럽 포인트가 부족합니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBICONBUYTOLEAKLV:
        sprintf(xPopup.strTitle,"클럽 아이콘 구매");
        sprintf(xPopup.strText,"클럽 레벨이 부족합니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBICONCHANGECHECK:
        sprintf(xPopup.strTitle,"클럽 아이콘 변경");
        sprintf(xPopup.strText,"클럽 아이콘을 선택된 것으로 변경하시겠습니까?");
        xPopup.btnType=BTN_YESNO;
        break;
    case POPUP_CLUBICONCHANGENOMASTER:
        sprintf(xPopup.strTitle,"클럽 아이콘 변경");
        sprintf(xPopup.strText,"클럽 마스터만 변경할 수 있습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_CLUBICONDONTHAVEICON:
        sprintf(xPopup.strTitle,"클럽 아이콘 변경");
        sprintf(xPopup.strText,"소유한 아이콘이 아닙니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_PANGTIMESRESETCHECK:
        sprintf(xPopup.strTitle, "사용 아이템");
        sprintf(xPopup.strText,"허니팡 횟수 추가 아이템을\n 사용하시겠습니까? ");
        xPopup.btnType=BTN_YESNO;
        break;
    case POPUP_PANGTIMESOK:
        sprintf(xPopup.strTitle,"허니팡 횟수 추가");
        sprintf(xPopup.strText, "허니팡 횟수가 추가되었습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_PANGTIMESNOCLUB:
        sprintf(xPopup.strTitle,"허니팡 횟수 추가");
        sprintf(xPopup.strText,"가입된 클럽이 없습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_PANGTIMESMAXTIMESEXCEED:
        sprintf(xPopup.strTitle,"허니팡 횟수 추가");
        sprintf(xPopup.strText,"플레이 최대 횟수를 초과하였습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
            
    case POPUP_INPUTINVENTORYFORMERERR1:
        sprintf(xPopup.strTitle,"알림");
        sprintf(xPopup.strText,"생산기가 작동하고 있습니다.\n 그래도 보관함에 보관하시겠습니까?");
        xPopup.btnType=BTN_YESNO;
        break;
            
    case POPUP_INPUTINVENTORYFORMERERR2:
        sprintf(xPopup.strTitle,"알림");
        sprintf(xPopup.strText,"보상을 수령하지 않았습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
            
        case POPUP_NONFORMER:
        sprintf(xPopup.strTitle,"인테리어 설치");
        sprintf(xPopup.strText,"샵에 인테리어가 존재하지 않습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_NOTFORMER:
        sprintf(xPopup.strTitle,"캔디 제작");
        sprintf(xPopup.strText,"생산 시설이 아닙니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_FORMERCANT:
        sprintf(xPopup.strTitle, "캔디 제작");
        sprintf(xPopup.strText, "생산을 할 수가 없습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;
    case POPUP_FORMERCANTTAKE:
        sprintf(xPopup.strTitle, "캔디 제작");
        sprintf(xPopup.strText, "캔디가 완성되지 않았습니다.");
        xPopup.btnType=BTN_OK_CONFIRM;
        break;

    }
}

void keyPopup(M_Int32 type,M_Int32 param1,M_Int32 param2)
{
    M_Boolean isKeyOk = FALSE;
    M_Boolean isKeyClr = FALSE;
	
	if(xPopup.state != MENU_STATE_WAIT)
		return;
	
	if(isTouch == TRUE)
	{
		if(touchType != USER_POINT_PRESS_EVENT)
			return;
		if(FALSE)//xPopup.btnType == BTN_YESNO)
		{
			if(touchCheck(&xTouchOk))
			{
				if(xPopup.select == POPUPYES)
				{
					playSnd(SND_MENU_OK);
					isKeyOk = TRUE;
				}
				else
				{
					playSnd(SND_MENU_OK);
					xPopup.select = POPUPYES;
				}
			}
			else if(touchCheck(&xTouchClr))
			{
				if(xPopup.select == POPUPNO)
				{
					playSnd(SND_MENU_OK);
					isKeyOk = TRUE;
				}
				else
				{
					playSnd(SND_MENU_OK);
					xPopup.select = POPUPNO;
				}
			}
		}
		else
		{
			if(touchCheck(&xTouchOk))
			{
				playSnd(SND_MENU_OK);
				isKeyOk = TRUE;
			}
			else if(touchCheck(&xTouchClr))
			{
				playSnd(SND_MENU_OK);
				isKeyClr = TRUE;
			}
		}
	}
	
    if(isKeyOk == TRUE)
    {
        switch(xPopup.msgType)
        {
		case DONT:
			break;
		default:
			xPopup.selectNum = POPUPYES;
			xPopup.state = MENU_STATE_OUT;
			xPopup.anyCnt = 0;
			setPopupResult();

			break;
		}
    }
	if(isKeyClr == TRUE)
	{
		switch(xPopup.msgType)
		{
		case DONT:
			break;
		default:
			xPopup.selectNum = POPUPNO;
			xPopup.state = MENU_STATE_OUT;
			xPopup.anyCnt = 0;
			setPopupResult();
			break;   
		}
	}
		
}


void drawPopup()
{
	M_Int32 px = cx;
	M_Int32 py = cy;
	M_Int32 hPos;
	int fontGab = 50;

	drawBgFillRect();

	if(xPopup.state == MENU_STATE_IN)
		xPopup.state = MENU_STATE_WAIT;
	
	switch(xPopup.state)
	{
	case MENU_STATE_IN:
		switch(++xPopup.anyCnt)
		{
		case 1:	hPos = -329;break;
		case 2:	hPos = -233;break;
		case 3:	hPos = -194;break;
		case 4:	hPos = -145;break;
		case 5:	hPos = -81;break;
		case 6:	hPos = -2;break;
		case 7:	hPos = 15;break;
		case 8:	hPos = 12;break;
		case 9:	hPos = -12;break;
		case 10:hPos = -31;break;
		case 11:hPos = -36;break;
		case 12:hPos = -17;break;
		case 13:hPos = -3;break;
		case 14:hPos = -1;break;
		case 15:hPos = 0;break;
		case 16:hPos = 1;break;
		default:
			hPos = 0;
			xPopup.state = MENU_STATE_WAIT;
			break;
		}
		break;
	case MENU_STATE_WAIT:
		hPos = 0;
		break;
	case MENU_STATE_OUT:
			/*
		switch(++xPopup.anyCnt)
		{
		case 1:hPos = -10;break;
		case 2:hPos = -20;break;
		case 3:hPos = -40;break;
		case 4:hPos = -80;break;
		case 5:hPos = -160;break;
		case 6:hPos = -320;
			setPopupResult();
			break;
		default:
			hPos = 0;
			break;
		}
		*/
		break;	
	}
		
	py+=hPos;
	switch(xPopup.msgType)
	{
	case DONT:
		break;
	case POPUP_FASHIONBUYYESNO:
						
		setMapData(xCatalog.xSlotS[xCatalog.selectSlot].code);	//xMap.rever,xMap.type,xMap.listNum 구하기
		drawPacker(imgPopupBg, px, py, 0, 0, imgW(imgPopupBg), imgH(imgPopupBg), VH);
		
			
		subTemp[XPOS] = px+108;
		subTemp[YPOS] = py+30;
		drawPacker(imgInfoBar6, subTemp[XPOS], subTemp[YPOS], 0, 0, imgW(imgInfoBar6), imgH(imgInfoBar6), VH);
		if(xFashionData[xMap.type][xMap.listNum].priceType == 0)
			drawIcon(subTemp[XPOS]-66,subTemp[YPOS], ICON_TYPE_GOLD);
		else
			drawIcon(subTemp[XPOS]-66,subTemp[YPOS], ICON_TYPE_LOOK);
		
		gSetColor(82, 49, 38);
		setCommaNum(strTempS, xFashionData[xMap.type][xMap.listNum].price.oriData);
		setFontSize(14);
		gDrawString(subTemp[XPOS]+66+4,subTemp[YPOS], strTempS, VR);
		setFontSize(11);
			
		
		
		subTemp[XPOS] = px+108;
		subTemp[YPOS] = py-116;
		setFontSize(20);
		gDrawStringBold(subTemp[XPOS], subTemp[YPOS]+4, xPopup.strTitle, VH, 97, ALPHA_MAX, 227, 44, 27, 26);
		gSetColor(82, 49, 38);
		setFontSize(14);
		gDrawString(subTemp[XPOS], subTemp[YPOS]+64, xPopup.strText, VH);
		setFontSize(11);
			
			
		drawImage(&imgLvUp[2], px-160,py-45, 0, 0, imgLvUp[2].w, imgLvUp[2].h, VH);
		drawFittingF(px-160,py-45, (xMap.type*1000)+xMap.listNum, 100);
					
		drawBtn(px, py+158, xPopup.btnType);
			
			
		if(xWorldMap.isTuto == TRUE&&(xQuestTuto.state == QUEST_TUTO_SHOW || xQuestTuto.state == QUEST_TUTO_KEY))
		{
			switch(xQuestTuto.nowNum)
			{
			case TUTO_25_FASHIONOPEN_BUY:
				xTutoInfo.x[xTutoInfo.totalNum] = px+100;
				xTutoInfo.y[xTutoInfo.totalNum] = py+158;
				xTutoInfo.type[xTutoInfo.totalNum++] = TUTOINFO_TYPE_ARROW;
				break;
			case TUTO_25_FASHIONOPEN_ITEM:
				if(xCatalog.xSlotS[xCatalog.selectSlot].code == xQuestDataMain[xQuestInfo.xSlot[0].questNum].checkCode[0])
					xQuestTuto.isTutoClean = TRUE;
				break;
			}
		}
		break;
	case POPUP_TEST_ALLTILE:
		{
			
		setMapData(xInterior.xBuildSlot.codeTeam[0]);
		int totalNum = 0;
		int	sellTotalNum=0;
		int tileNum = 0;
		int interiorNum = 0;
		int sellMoney;
			
		switch(xMap.type)
		{
		case INTERIOR_TYPE_FLOORTILE:
				
			if(xWorldMap.isTuto == TRUE)
			{
				switch(xQuestTuto.nowNum)
				{
				case TUTO_26_INTERIOR_ALL0:
					xQuestTuto.isTutoClean = TRUE;
					break;
				}
			}
				
				
			totalNum = xMap.shopPointW * xMap.shopPointH;
			for(int x=0;x<xMap.shopPointW;x++)
			{
				for(int y=0;y<xMap.shopPointH;y++)
				{
					if(xMap.data[xMap.nowFloor][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y] == (xMap.type*1000)+xMap.listNum)
						tileNum++;
				}
			}
				
			for(int i=0;i<xInventoryInterior.totalNum;i++)
			{
				if(xInventoryInterior.itemCode[i] == (xMap.type*1000)+xMap.listNum)
					interiorNum++;
			}
				
			sellTotalNum = totalNum;
			sellTotalNum -= tileNum;
			sellTotalNum -= interiorNum;
				
			if(sellTotalNum < 0)
			{
				interiorNum += sellTotalNum;
				sellTotalNum = 0;
			}
			
				
							
							
			break;
		case INTERIOR_TYPE_WALLTILE:
				
			if(xWorldMap.isTuto == TRUE)
			{
				switch(xQuestTuto.nowNum)
				{
				case TUTO_26_INTERIOR_ALL1:
					xQuestTuto.isTutoClean = TRUE;
					break;
				}
			}
				
				
				
				
				
				
				
			totalNum = xMap.shopPointW + xMap.shopPointH;
							
			for(int x=0;x<xMap.shopPointW;x++)
			{
				if(xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY-1] == (xMap.type*1000)+xMap.listNum || -xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY-1] == (xMap.type*1000)+xMap.listNum)
					tileNum++;
			}
			for(int y=0;y<xMap.shopPointH;y++)
			{
				if(xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX-1][xMap.shopPointY+y] == (xMap.type*1000)+xMap.listNum || -xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX-1][xMap.shopPointY+y] == (xMap.type*1000)+xMap.listNum)
					tileNum++;
			}
				
			for(int i=0;i<xInventoryInterior.totalNum;i++)
			{
				if(xInventoryInterior.itemCode[i] == (xMap.type*1000)+xMap.listNum)
					interiorNum++;
			}
			
			sellTotalNum = totalNum;
			sellTotalNum -= tileNum;
			sellTotalNum -= interiorNum;
			
			if(sellTotalNum < 0)
			{
				interiorNum += sellTotalNum;
				sellTotalNum = 0;
			}
			break;
		}
			
					
		sellMoney = sellTotalNum * xObj.xObjData[xMap.type][xMap.listNum].price.oriData;
		//구매가격:sellMoney
		//총구매갯수:totalNum
		//인벤토리제외갯수:interiorNum
			
		drawPacker(imgPopupBg, px, py, 0, 0, imgW(imgPopupBg), imgH(imgPopupBg), VH);
		subTemp[XPOS] = px+108;
		subTemp[YPOS] = py+30;
			
		

		drawPacker(imgInfoBar6, subTemp[XPOS], subTemp[YPOS], 0, 0, imgW(imgInfoBar6), imgH(imgInfoBar6), VH);
		switch(xObj.xObjData[xMap.type][xMap.listNum].priceType)
		{
		case 0:		//골드
			drawIcon(subTemp[XPOS]-66,subTemp[YPOS], ICON_TYPE_GOLD);
			break;
		case 1:		//룩
			drawIcon(subTemp[XPOS]-66,subTemp[YPOS], ICON_TYPE_LOOK);
			break;
		}
			
		gSetColor(82, 49, 38);
		setCommaNum(strTempS, sellMoney);
		setFontSize(14);
		gDrawString(subTemp[XPOS]+66+4,subTemp[YPOS], strTempS, VR);
		setFontSize(11);

				
		subTemp[XPOS] = px+108;
		subTemp[YPOS] = py-116;
		
		setFontSize(20);
		gDrawStringBold(subTemp[XPOS], subTemp[YPOS]+4, "전체설치", VH, 97, ALPHA_MAX, 227, 44, 27, 26);
		gSetColor(82, 49, 38);
		setFontSize(14);

		sprintf(strTempB, "<%s>\n로 전체설치 하시겠습니까?\n",xObj.xObjData[xMap.type][xMap.listNum].strName);
		gDrawString(subTemp[XPOS], subTemp[YPOS]+64, strTempB, VH);
		setFontSize(11);
		
		drawImage(&imgLvUp[2], px-160,py-45, 0, 0, imgLvUp[2].w, imgLvUp[2].h, VH);
			
			
		setDrawObjCenter(xMap.type,xMap.listNum);
		if(xDrawObjCenter.reSize != 100)
		{
			xGame.fgameScaleCx =px-160;
			xGame.fgameScaleCy =lcdH-(py-45);
			xGame.fgameScale = xDrawObjCenter.reSize*0.01f;
		}
		drawObj(px-160+xDrawObjCenter.w,py-45+xDrawObjCenter.h, xMap.type,xMap.listNum, 0,TRUE,DONT,DONT);
									
        
		xGame.fgameScale = 1.0f;
		xGame.fgameScaleCx =cx;
		xGame.fgameScaleCy =cy;
					
		drawBtn(px, py+158, xPopup.btnType);
			
			
		if(xWorldMap.isTuto == TRUE&&(xQuestTuto.state == QUEST_TUTO_SHOW || xQuestTuto.state == QUEST_TUTO_KEY))
		{
			switch(xQuestTuto.nowNum)
			{
			case TUTO_26_INTERIOR_OK0:
			case TUTO_26_INTERIOR_OK1:
				xTutoInfo.x[xTutoInfo.totalNum] = px+100;
				xTutoInfo.y[xTutoInfo.totalNum] = py+158;
				xTutoInfo.type[xTutoInfo.totalNum++] = TUTOINFO_TYPE_ARROW;
				break;
			}
		}
			
			
		}
		break;
	case POPUP_MODELMAIN_SLOTOPENGOLD:
	case POPUP_MODELMAIN_SLOTOPENCASH:
		drawPacker(imgPopupBg, px, py, 0, 0, imgW(imgPopupBg), imgH(imgPopupBg), VH);
		setFontSize(20);
		gDrawStringBold(px, py-116, xPopup.strTitle, VH, 97, 255, 227, 44, 27, 26);
		gSetColor(82, 49, 38);
		gDrawString(px, py-16, xPopup.strText, VH);
		setFontSize(11);
		
		drawPacker(imgInfoBar1, px,py+70, 0, 0, imgW(imgInfoBar1), imgH(imgInfoBar1), VH);
		switch(xPopup.msgType)
		{
		case POPUP_MODELMAIN_SLOTOPENGOLD:
			drawIcon(px-82,py+70, ICON_TYPE_GOLD);
			setCommaNum(strTempS, xModelMainSlot[xModel.selectMainSlot].openPrice[0]);
			break;
		case POPUP_MODELMAIN_SLOTOPENCASH:
			drawIcon(px-82,py+70, ICON_TYPE_LOOK);
			setCommaNum(strTempS, xModelMainSlot[xModel.selectMainSlot].openPrice[1]);
			break;
		}
		gSetColor(82, 49, 38);
		setFontSize(14);
		gDrawString(px+82,py+70, strTempS, VR);
		setFontSize(11);

		
		drawBtn(px,py+156,xPopup.btnType);
		break;
	case POPUP_KAKAOCARSTORAGE:
	case POPUP_KAKAOFRIENDMAP:
	case POPUP_KAKAOORDERITEM:
		drawPacker(imgPopupBg, px, py, 0, 0, imgW(imgPopupBg), imgH(imgPopupBg), VH);
		
		gSetColor(82, 49, 38);
		setFontSize(14);

			
		setPopupStringLine(xPopup.strText,lcdW);
		fontGab = 50;
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
			gDrawString(px,py+posTemp[HPOS]+(fontGab*li)-((xPopup.totalLine-1)*(fontGab/2)), xPopup.strTextLine[li], VH);
			
		setFontSize(20);
		gDrawStringBold(px,py-120,xPopup.strTitle,VH,255,255,255,82,49,38);
		setFontSize(11);
			
		drawBtn(px,py+156,xPopup.btnType);
		break;
	default:
		drawPacker(imgPopupBg, px, py, 0, 0, imgW(imgPopupBg), imgH(imgPopupBg), VH);
		gSetColor(82, 49, 38);
		setFontSize(14);
		
				
						
		setPopupStringLine(xPopup.strText,lcdW);
		fontGab = 50;
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
		{
			gDrawString(px-110,py+posTemp[HPOS]+(fontGab*li)-((xPopup.totalLine-1)*(fontGab/2)), xPopup.strTextLine[li], VH);
		}
									
		if(xPopup.speakingNpcNum != DONT)
		{
			drawPacker(imgPopup2, px-16,py-150, 0, 0, imgW(imgPopup2), imgH(imgPopup2), VH);
			gSetColor(138, 117, 111);
			setFontSize(20);
			gDrawString(px-26,py-156,xPopup.strTitle,VH);
			setFontSize(11);
			drawImage(&imgPopupNpc[0], px+180,py+200, 0, 0, imgPopupNpc[0].w, imgPopupNpc[0].h, BH);
			drawImage(&imgPopupNpc[1], px+180,py+200-imgPopupNpc[0].h, 0, 0, imgPopupNpc[1].w, imgPopupNpc[1].h, BH);
		}
		drawBtn(px-110,py+156,xPopup.btnType);
        break;
	}
}

void setPopupResult()
{
	switch(xPopup.msgType)
	{
	case POPUP_G9_LINK:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			char strUrl[256];
			startWebView("https://play.google.com/store/apps/details?id=com.ebay.kr.g9");
			xG9.isCheckInstall = TRUE;
			xG9.checkInstallCnt = 0;
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_KAKAOCARSTORAGE:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			setStateCarSelectMode_Production();
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_KAKAOFRIENDMAP:
		if(xPopup.selectNum == POPUPYES)
		{
			xWorldMap.isKakaoFriendMap_NET = TRUE;
			playState = xPopup.yes;
			////////////////////////////////////////////////////////////
			xEventQueueNet.friendNum[xEventQueueNet.totalNum] = xFriendData[xFriendMap.selectDataSlotNum].userNum;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_KAKAOHELP, TRUE);
			////////////////////////////////////////////////////////////
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_KAKAOORDERITEM:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			orderSelectItemOk();
			if(xFriendData[xFriendMap.selectDataSlotNum].isKakaoMessage == TRUE)
			{
				kakaoDevSendMessageApp(xFriendData[xFriendMap.selectDataSlotNum].strKakaoId, xSaveTemp.strNickName,"1189");
			}
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_GUESTLOGINYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
            /*
			xSave.isGuest = TRUE;
			if(xSave.isGuestIdMake == TRUE)
			{
				sprintf(xKakaoData.xUserInfo.strUserId, "%s",xSave.strIdGuest);
				netSend(CMD_LOGIN, DONT);
			}
			else
			{
				xSave.isGuestIdMake = TRUE;
				xMainMenu.state = MAINMENU_STATE_IDMAKE;
				xIdMake.state = IDMAKE_STATE_IDMAKE;
				sprintf(xIdMake.strNickName, "대표자명 입력");
				xIdMake.sex = 0;
				xIdMake.emailErr = IDMAKEERR_TYPE_DONT;
				xIdMake.passErr = IDMAKEERR_TYPE_DONT;
				xIdMake.nickNameErr = IDMAKEERR_TYPE_DONT;
				xIdMake.ageErr = IDMAKEERR_TYPE_DONT;
			}
             */
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_UNREGISTEREDYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			netSend(CMD_UNREGISTERED, DONT);
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_AUTOSELLSLEEP:
			playState = xPopup.yes;
		break;
	case POPUP_AUTOPRODUCTSLEEP:
		sleepAutoSell();
			playState = xPopup.yes;
		break;
	case POPUP_KAKAOLOGINERR:
	case POPUP_KAKAOLOGINERR22:

		gameExit();
		break;
	case POPUP_IDREMAKE:
		gameExit();
		break;
	case POPUP_HACKINGPACKAGE:
		gameExit();
		break;
	case POPUP_UNREGISTEREDOK:
		gameExit();
		break;
	case POPUP_SERVERCHECK:
		gameExit();
		break;
	case POPUP_SERVERERR:
		gameExit();
		break;
	case POPUP_APPSTOREUPGRADEYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
            startWebView(xNetData.strGameUpDateServerUrl);
		}
		else
		{
			gameExit();
		}
		break;
	case POPUP_SHOP_GUESTLOGINEND:
		gameExit();
		break;
	case POPUP_RESDOWNYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			xResCheck.state = RESCHECK_STATE_FILESCRIPT_DOWNLOAD_START;
			playState = PLAY_PLAY;
		}
		else
		{
			gameExit();
		}
		break;
	case POPUP_MAIL_DELYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			////////////////////////////////////////////////
			xEventQueueNet.key[xEventQueueNet.totalNum] = xMail.xMailSlot[xPopup.num].key;
			xEventQueueNet.friendNum[xEventQueueNet.totalNum] = xNetData.userNum;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_DELMAIL, TRUE);
			///////////////////////////////////////////////
			for(int i=xPopup.num;i<xMail.totalMailSlot-1;i++)
			{
				memcpy(&xMail.xMailSlot[i], &xMail.xMailSlot[i+1], sizeof(xMail.xMailSlot[i]));
			}
			xMail.totalMailSlot--;
			playState = xPopup.yes;
		}
		else
			playState = xPopup.no;
		break;
	case POPUP_RESUPGRADEYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			xMainMenu.state = MAINMENU_STATE_RESCHECK;
			xMainMenu.anyCnt = 0;
		}
		else
		{
			gameExit();
		}
		break;
	case POPUP_SERVER_TIMEOVER:
		gameExit();
		break;
	case POPUP_MODELGIFTFASTCASHYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			
			int endTime = xModelMainSlot[xModel.selectMainSlot].endTime - xCalendar.nowTime;
			int fastCash = getFastTimeCash(endTime);
			
			if(xSaveTemp.cash.oriData < fastCash)
			{
				setPopup(POPUP_CASHEMPTY, playState, playState, 0, DONT);
			}
			else
			{
				xInterior.buildModeTime64 = DONT;
				xWorldMap.state = WORLDMAP_STATE_PLAY;
				
				setCash(-fastCash);
				setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_LOOK, fastCash);
				xModelMainSlot[xModel.selectMainSlot].endTime = xCalendar.nowTime-100;
				////////////////////////////////////////////
				xEventQueueNet.slotNum[xEventQueueNet.totalNum] = xModel.selectMainSlot;
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETMODELMAIN, FALSE);
				///////////////////////////////////////////
				///////////////////////////////////////////
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, FALSE);
				///////////////////////////////////////////
				setFiveRocksCustom("즉시완료","즉시완료횟수","모델즉시완료","NULL",1);
			}
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_SALESHOPBUYYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			setMapData(xSaleShop.slotCode[xSaleShop.selectSlot]);
			setCash(-xSaleShop.slotSalePrice[xSaleShop.selectSlot]);
			setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_LOOK, -xSaleShop.slotSalePrice[xSaleShop.selectSlot]);
			//////////////////////////////////////////////////
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO,TRUE);
			//////////////////////////////////////////////////
			inputInventoryInterior(xSaleShop.slotCode[xSaleShop.selectSlot]);
			//////////////////////////////////////////////////////////////////////////////
			xEventQueueNet.code[xEventQueueNet.totalNum] = xSaleShop.slotCode[xSaleShop.selectSlot];
			xEventQueueNet.code[xEventQueueNet.totalNum] = xEventQueueNet.code[xEventQueueNet.totalNum]<0?-xEventQueueNet.code[xEventQueueNet.totalNum]:xEventQueueNet.code[xEventQueueNet.totalNum];
			xEventQueueNet.haveNum[xEventQueueNet.totalNum] = 0;
			for(int ee=0;ee<xInventoryInterior.totalNum;ee++)
			{
				if(xInventoryInterior.itemCode[ee] == xEventQueueNet.code[xEventQueueNet.totalNum])
					xEventQueueNet.haveNum[xEventQueueNet.totalNum]++;
			}
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_INTERIOR, FALSE);
			//////////////////////////////////////////////////////////////////////////////
			
			///////////////////////////////////////////////////////////////////
			xEventQueueNet.layer[xEventQueueNet.totalNum][0] = 101;//0:골드,1프리미엄,2캔디머쉰,3직원의상,4모델뽑기,100:첫구매이벤트,101:스페션세일이벤트,102:리뷰이벤트
			xEventQueueNet.layer[xEventQueueNet.totalNum][1] = 0;//아이템종류(0~5)직원의상 구매시
			xEventQueueNet.code[xEventQueueNet.totalNum] = xSaleShop.slotCode[xSaleShop.selectSlot];
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_BUYGOLD, TRUE);
			///////////////////////////////////////////////////////////////////
		}
		else
			playState = xPopup.no;
		break;
    case POPUP_SHOP_HOTDEALBUY:
        if(xPopup.selectNum == POPUPYES)
        {
            playState = xPopup.yes;
            
            xEventQueueNet.SLOT[xEventQueueNet.totalNum] = xHotDeal.selectSlot;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_HOTDEALDETAILBUY, TRUE);
            xHotDeal.xSlot[xHotDeal.selectSlot].state = HOTDEAL_STATE_BUY;
            
            xSave.giftLastKey = 999;
            gameSave(SAVE_SLOT_GAME);
            setPopup(POPUP_USERTEXT, xPopup.yes, xPopup.no, 0, DONT);
            sprintf(xPopup.strText, "선물함으로 지급되었습니다.");
                        
            switch(xHotDeal.xSlot[xHotDeal.selectSlot].itemType)
            {
            case HOTDEAL_ITEMTYPE_INTERIOR:
                setMapData(xHotDeal.xSlot[xHotDeal.selectSlot].itemCode);
                sprintf(xRocks.strTemp, "할인률:%d",xHotDeal.xSlot[xHotDeal.selectSlot].salePer);
                setFiveRocksCustom("핫딜","구매",xObj.xObjData[xMap.type][xMap.listNum].strName,xRocks.strTemp,1);
                break;
            case HOTDEAL_ITEMTYPE_CASTING:
                break;
            }
        }
        else
            playState = xPopup.no;
        break;
	case POPUP_TIREDEMPTY:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			setShop(SHOPTAB_TYPE_PREMIUM);
		}
		else
			playState = xPopup.no;
		break;
	case POPUP_CARORDER_FASTCASH:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			setCash(-xPopup.num);

			//주차장 시간만 변경
			xCarPark[xCar.selectCarPark].endTime = xCalendar.nowTime;
			///////////////////////////////////////////////////////////////
			xEventQueueNet.slotNum[xEventQueueNet.totalNum] = xCar.selectCarPark;
			xEventQueueNet.key[xEventQueueNet.totalNum] = xCarPark[xCar.selectCarPark].orderKey;
			xEventQueueNet.code[xEventQueueNet.totalNum] = xCarPark[xCar.selectCarPark].carNum;
			xEventQueueNet.action[xEventQueueNet.totalNum] = xCarPark[xCar.selectCarPark].state;
			xEventQueueNet.time[xEventQueueNet.totalNum] = xCarPark[xCar.selectCarPark].endTime;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CARPARK, FALSE);
			//////////////////////////////////////////////////////////////
			
			xWorldMap.state = WORLDMAP_STATE_PLAY;
			setFiveRocksCustom("즉시완료","즉시완료횟수","배송즉시완료","NULL",1);
		}
		else
			playState = xPopup.no;
		break;
	case POPUP_CASHEMPTY:
	case POPUP_MONEYEMPTY:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			setShop(SHOPTAB_TYPE_MONEY);
		}
		else
			playState = xPopup.no;
		break;
	case POPUP_ORDERDEL:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
						
			//최종 처리
			int orderSlotNum = xOrder.slotNumList[xOrder.selectSlot];
			xOrder.xSlotListData[orderSlotNum].state = ORDERSLOT_STATE_END;
			//////////////////////////////////////////////////////////////
			xEventQueueNet.action[xEventQueueNet.totalNum] = 1;//0:배송1:완료
			xEventQueueNet.key[xEventQueueNet.totalNum] = xOrder.xSlotListData[xOrder.slotNumList[xOrder.selectSlot]].key;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_ORDEROK, FALSE);
			//////////////////////////////////////////////////////////////
			setOrderList();
		}
		else
			playState = xPopup.no;
		break;
	case POPUP_FASHIONBUYYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
									
			int code;
			code = xCatalog.xSlotS[xCatalog.selectSlot].code;
			
			setMapData(code);	//xMap.rever,xMap.type,xMap.listNum 구하기
			
			if(xFashionData[xMap.type][xMap.listNum].priceType == 0)
			{
				setMoney(-xFashionData[xMap.type][xMap.listNum].price.oriData);
				setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_GOLD,-xFashionData[xMap.type][xMap.listNum].price.oriData);
			}
			else
			{
				setCash(-xFashionData[xMap.type][xMap.listNum].price.oriData);
				setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_LOOK,-xFashionData[xMap.type][xMap.listNum].price.oriData);
			}
			xInventoryFashion.isOpen[xMap.type][xMap.listNum] = TRUE;
			
			xSave.fashionNew[xMap.type][xMap.listNum] = 1;	//0:보통 1:new보여주기 2:확인한상태 3:완료
			gameSave(SAVE_SLOT_GAME);
						
			////////////////////////////////////////////////////
			xEventQueueNet.code[xEventQueueNet.totalNum] = (xMap.type*1000)+xMap.listNum;
			xEventQueueNet.haveNum[xEventQueueNet.totalNum] = 0;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_FASHION, TRUE);
			///////////////////////////////////////////////////
			
			sprintf(xRocks.strTemp,"%s",xFashionData[xMap.type][xMap.listNum].strName);
			switch(xMap.type)
			{
			case 0:setFiveRocksCustom("아이템","일반의상","아우터",xRocks.strTemp,1);break;
			case 1:setFiveRocksCustom("아이템","일반의상","상의",xRocks.strTemp,1);break;
			case 2:setFiveRocksCustom("아이템","일반의상","하의",xRocks.strTemp,1);break;
			case 3:setFiveRocksCustom("아이템","일반의상","원피스",xRocks.strTemp,1);break;
			case 4:setFiveRocksCustom("아이템","일반의상","신발",xRocks.strTemp,1);break;
			case 5:setFiveRocksCustom("아이템","일반의상","가방",xRocks.strTemp,1);break;
			case 6:setFiveRocksCustom("아이템","일반의상","악세사리",xRocks.strTemp,1);break;
			}
			

			setCatalogTabChange(xCatalog.selectTabS);
			xCatalog.selectSlot = DONT;
						
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_QUEST_FASTCASHYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			//완료 시키기
			for(int i=0;i<getQuestCheckTotalNum(xQuestInfo.selectSlot);i++)
			{
				switch(xQuestInfo.xSlot[xQuestInfo.selectSlot].type)
				{
				case QUEST_TYPE_MAIN:
					if(xQuestDataMain[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].checkMax[i] == -1)
						xQuestDataMain[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].checkNow[i] = 0;
					else
						xQuestDataMain[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].checkNow[i] = xQuestDataMain[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].checkMax[i];
					
					xQuestDataMain[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].isCheckClean[i] = TRUE;
					break;
				case QUEST_TYPE_NORMAL:
					if(xQuestDataNormal[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].checkMax[i] == -1)
						xQuestDataNormal[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].checkNow[i] = 0;
					else
						xQuestDataNormal[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].checkNow[i] = xQuestDataNormal[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].checkMax[i];
					
					xQuestDataNormal[xQuestInfo.xSlot[xQuestInfo.selectSlot].questNum].isCheckClean[i] = TRUE;
					break;
				}
			}
			
			setCash(-xPopup.num);
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO,TRUE);
			playState = xPopup.yes;
			setFiveRocksCustom("즉시완료","즉시완료횟수","퀘스트즉시완료","NULL",1);
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_LOGINERR:
		playState = xPopup.yes;
		xMainMenu.state = MAINMENU_STATE_IDMAKE;
		xIdMake.state = IDMAKE_STATE_LOGINKAKAO;
		break;
	case POPUP_LOGINERR2:
		playState = xPopup.yes;
		xMainMenu.state = MAINMENU_STATE_IDMAKE;
		xIdMake.state = IDMAKE_STATE_LOGINKAKAO;
		break;
	case POPUP_BLACKUSER:
		gameExit();
		break;
	case POPUP_LOGINERRRRRRRRR:
		gameExit();
		break;
    case POPUP_SHOP_PACKAGEBUY:
        if(xPopup.selectNum == POPUPYES)
        {
            startIap();
            playState = xPopup.yes;
        }
        else
        {
            playState = xPopup.no;
        }
        break;
    case POPUP_SHOP_PREPAYBUY:
        if(xPopup.selectNum == POPUPYES)
        {
            startIap();
            playState = xPopup.yes;
        }
        else
        {
            playState = xPopup.no;
        }
        break;
	case POPUP_SHOP_BUYYESNOCASH:
		if(xPopup.selectNum == POPUPYES)
		{
			startIap();
			playState = xPopup.yes;
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_SHOP_BUYYESNOGOLD:
		if(xPopup.selectNum == POPUPYES)
		{
			setCash(-xShop.moneyPrice[xShop.selectSlot].oriData);
			setMoney(xShop.moneyPoint[xShop.selectSlot].oriData);
									
			sprintf(xRocks.strTemp,"%d골드",xShop.moneyPoint[xShop.selectSlot].oriData);
			setFiveRocksCustom("아이템","골드",xRocks.strTemp,"NULL",1);
			
			/////////////////////////////////////////
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, TRUE);
			/////////////////////////////////////////
			
			///////////////////////////////////////////////////////////////////
			xEventQueueNet.layer[xEventQueueNet.totalNum][0] = 0;//0:골드,1프리미엄,2캔디머쉰,3직원의상,모델뽑기
			xEventQueueNet.layer[xEventQueueNet.totalNum][1] = 0;//아이템종류(0~5)직원의상 구매시
			xEventQueueNet.code[xEventQueueNet.totalNum] = xShop.selectSlot;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_BUYGOLD, TRUE);
			///////////////////////////////////////////////////////////////////
			playState = xPopup.yes;
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_LOGOUTYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			kakaoDevLogout();
			playState = xPopup.yes;
			setPopup(POPUP_LOGOUT, playState, playState, 0, DONT);
						
			subTemp[10] = xSave.resVer;
			initSave();
			xSave.resVer = subTemp[10];
			gameSave(SAVE_SLOT_GAME);
			xSaveKakao.totalInvite = 0;
			xSaveKakaoApp.totalInvite = 0;
			gameSave(SAVE_SLOT_KAKAO);
			gameSave(SAVE_SLOT_KAKAOAPP);
			
		}
		else
			playState = xPopup.no;
		break;
	case POPUP_LOGOUT:
		gameExit();
		break;
	case POPUP_SHOP_PREMIUM_BUYYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			switch(xShop.selectSlot)
			{
			case 0:		//모델 교환권
				if(xModel.totalInventoryModel >= xModel.totalInventoryModelMax)
				{
					setPopup(POPUP_USERTEXT, xPopup.yes, xPopup.no, 0, DONT);
					sprintf(xPopup.strText, "보유 모델 수량이 초과해\n더 이상 획득 하실 수 없습니다.");
				}
				else
				{
					playState = xPopup.yes;
					setNewModel(0);
					
					switch(xShop.premiumPriceType[xShop.selectSlot])
					{
					case 0:
						setMoney(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					case 1:
						setCash(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					case 2:
						setTired(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					}
					////////////////////////////////////////////////////////////
					addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, TRUE);
					////////////////////////////////////////////////////////////
					setFiveRocksCustom("아이템","캐스팅권","일반캐스팅권","NULL",1);

				}
				break;
			case 1:		//모델 교환권
				if(xModel.totalInventoryModel >= xModel.totalInventoryModelMax)
				{
					setPopup(POPUP_USERTEXT, xPopup.yes, xPopup.no, 0, DONT);
					sprintf(xPopup.strText, "보유 모델 수량이 초과해\n더 이상 획득 하실 수 없습니다.");
				}
				else
				{
					playState = xPopup.yes;
					setNewModel(1);
					
					
					switch(xShop.premiumPriceType[xShop.selectSlot])
					{
					case 0:
						setMoney(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					case 1:
						setCash(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					case 2:
						setTired(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					}
					
										
					////////////////////////////////////////////////////////////
					addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, TRUE);
					////////////////////////////////////////////////////////////
					setFiveRocksCustom("아이템","캐스팅권","고급캐스팅권","NULL",1);
				}
				break;
			case 2:		//의상 유행
				switch(xShop.premiumPriceType[xShop.selectSlot])
				{
				case 0:
					setMoney(-xShop.premiumPrice[xShop.selectSlot].oriData);
					break;
				case 1:
					setCash(-xShop.premiumPrice[xShop.selectSlot].oriData);
					break;
				case 2:
					setTired(-xShop.premiumPrice[xShop.selectSlot].oriData);
					break;

				}
				playState = xPopup.yes;
				playSnd(SND_TREND_POPUP);
				setTrendTemp(0,1);
				trendFreeLoad(TRUE);
				xWorldMap.isTrend = TRUE;
				xTrend.state = TREND_STATE_NEW;
				////////////////////////////////////////////////////////////
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, TRUE);
				////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////
				xEventQueueNet.layer[xEventQueueNet.totalNum][0] = 1;//0:골드,1프리미엄,2캔디머쉰,3직원의상,모델뽑기
				xEventQueueNet.layer[xEventQueueNet.totalNum][1] = 0;//아이템종류(0~5)직원의상 구매시
				xEventQueueNet.code[xEventQueueNet.totalNum] = xShop.selectSlot;
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_BUYGOLD, TRUE);
				///////////////////////////////////////////////////////////////////
					
				setFiveRocksCustom("아이템","유행티켓","의상유행티켓","NULL",1);
				setFiveRocksCustom("재화","캔디소모","의상유행","NULL",1);
				break;
			case 3:		//잡화 유행
				playState = xPopup.yes;
	
				setTrendTemp(1,1);
				if(xTrend.isOpen[1] == FALSE)
				{
					setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
					sprintf(xPopup.strText, "잡화 유행티켓은 Lv.%d 부터\n이용가능합니다.",xTrend.lv[1]);
				}
				else if(xTrend.itemCodeTemp == 0)
				{
					setPopup(POPUP_USERTEXT, PLAY_PLAY, PLAY_PLAY, 0, DONT);
					sprintf(xPopup.strText, "잡화 라이선스가 없어\n유행을 발생시킬\n수 없습니다.");
				}
				else
				{
					switch(xShop.premiumPriceType[xShop.selectSlot])
					{
					case 0:
						setMoney(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					case 1:
						setCash(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					case 2:
						setTired(-xShop.premiumPrice[xShop.selectSlot].oriData);
						break;
					}
						
					playSnd(SND_TREND_POPUP);
					trendFreeLoad(TRUE);
					xWorldMap.isTrend = TRUE;
					xTrend.state = TREND_STATE_NEW;
					////////////////////////////////////////////////////////////
					addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, TRUE);
					////////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////////////
					xEventQueueNet.layer[xEventQueueNet.totalNum][0] = 1;//0:골드,1프리미엄,2캔디머쉰,3직원의상,모델뽑기
					xEventQueueNet.layer[xEventQueueNet.totalNum][1] = 0;//아이템종류(0~5)직원의상 구매시
					xEventQueueNet.code[xEventQueueNet.totalNum] = xShop.selectSlot;
					addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_BUYGOLD, TRUE);
					///////////////////////////////////////////////////////////////////
					setFiveRocksCustom("아이템","유행티켓","잡화유행티켓","NULL",1);
					setFiveRocksCustom("재화","캔디소모","잡화유행","NULL",1);
				}
				break;				
			case 4:		//캔디
			case 5:
			case 6:
				setTired(xShop.premiumPoint[xShop.selectSlot].oriData);
				playState = xPopup.yes;
					
				if(xShop.premiumPriceType[xShop.selectSlot] == 0)
					setMoney(-xShop.premiumPrice[xShop.selectSlot].oriData);
				else
					setCash(-xShop.premiumPrice[xShop.selectSlot].oriData);
				/////////////////////////////////////////
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, TRUE);
				/////////////////////////////////////////
				///////////////////////////////////////////////////////////////////
				xEventQueueNet.layer[xEventQueueNet.totalNum][0] = 1;//0:골드,1프리미엄,2캔디머쉰,3직원의상,모델뽑기
				xEventQueueNet.layer[xEventQueueNet.totalNum][1] = 0;//아이템종류(0~5)직원의상 구매시
				xEventQueueNet.code[xEventQueueNet.totalNum] = xShop.selectSlot;
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_BUYGOLD, TRUE);
				///////////////////////////////////////////////////////////////////
					
				sprintf(xRocks.strTemp,"캔디%d개",xShop.premiumPoint[xShop.selectSlot].oriData);
				setFiveRocksCustom("아이템","캔디",xRocks.strTemp,"NULL",1);
				break;
			}
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_MUSIC_BUYYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			
			M_Boolean isCheck = FALSE;
			
			switch(xSongSet.songPriceType[xSongSet.selectSong])
			{
			case 0:
				if(xSaveTemp.money.oriData < xSongSet.songPrice[xSongSet.selectSong])
				{
					isCheck = TRUE;
					xSongSet.selectSong = xSongSet.selectSongTemp;
					setPopup(POPUP_MONEYEMPTY, playState, playState, 0, DONT);
				}
				else
					setMoney(-xSongSet.songPrice[xSongSet.selectSong]);
				break;
			case 1:
				if(xSaveTemp.cash.oriData < xSongSet.songPrice[xSongSet.selectSong])
				{
					isCheck = TRUE;
					xSongSet.selectSong = xSongSet.selectSongTemp;
					setPopup(POPUP_CASHEMPTY, playState, playState, 0, DONT);
				}
				else
					setCash(-xSongSet.songPrice[xSongSet.selectSong]);
				break;
			}
						
			if(isCheck == FALSE)
			{
				///네트워크 음원 저장
				////////////////////////////////////////////
				xEventQueueNet.code[xEventQueueNet.totalNum] = xSongSet.selectSong;
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETSOUND, FALSE);
				///////////////////////////////////////////
				////////////////////////////////////////////
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETETC, FALSE);
				///////////////////////////////////////////
				////////////////////////////////////////////
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, FALSE);
				///////////////////////////////////////////


				xSongSet.isSongOpen[xSongSet.selectSong] = TRUE;
								
				sprintf(xRocks.strTemp,"%s",xSongSet.strSongTitle[xSongSet.selectSong]);
				setFiveRocksCustom("아이템","음악",xRocks.strTemp,"NULL",1);
			}
		}
		else
		{
			playState = xPopup.no;
			xSongSet.selectSong = xSongSet.selectSongTemp;
		}
		break;
	case POPUP_MUSIC_CHANGEYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			///네트워크 음원 저장
			////////////////////////////////////////////
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETETC, FALSE);
			///////////////////////////////////////////
		}
		else
		{
			playState = xPopup.no;
			xSongSet.selectSong = xSongSet.selectSongTemp;
		}
		break;
	case POPUP_KAKAOINVEITEYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			//시작
			xKakaoData.inveiteKeyReturn = TRUE;
			//카톡 초대완료 처리해주자
			addKakaoInvite(xKakaoData.xFriendInfo[xKakaoData.inveiteKakaoSlotNum].strUserId);
			kakaoDevSendMessage20(xKakaoData.xFriendInfo[xKakaoData.inveiteKakaoSlotNum].strUserId, xSaveTemp.strNickName);
		}
		else
		{
			playState = xPopup.no;
			
		}
		break;
	case POPUP_PRODUCTION_OPENYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			xProductionMenu.isOpen[PRODUCTIONMENU_TYPE_PREMIUM][xPopup.num] = TRUE;
			
			setCash(-xProductionMenu.openCash[PRODUCTIONMENU_TYPE_PREMIUM][xPopup.num].oriData);
			setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_LOOK,-xProductionMenu.openCash[PRODUCTIONMENU_TYPE_PREMIUM][xPopup.num].oriData);
			xProductionMenu.pushState[PRODUCTIONMENU_TYPE_PREMIUM][xPopup.num] = 1;	//0:제작1:취소
			if(xSave.isPushOnOff[PUSHONOFF_PRODUCTION] == FALSE)
				xProductionMenu.pushState[PRODUCTIONMENU_TYPE_PREMIUM][xPopup.num] = 1;	//0:제작1:취소
			
			xProductionMenu.pushTime[PRODUCTIONMENU_TYPE_PREMIUM][xPopup.num] = 0;
			xProductionMenu.isUpData[PRODUCTIONMENU_TYPE_PREMIUM][xPopup.num] = TRUE;
			
            ////////////////////////////////////////////////////////////////////////////
            xEventQueueNet.SLOT[xEventQueueNet.totalNum] = (6)+xPopup.num;
            xEventQueueNet.resultCash[xEventQueueNet.totalNum] = xSaveTemp.cash.oriData;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PRODUCTIONOPEN, TRUE);
            ////////////////////////////////////////////////////////////////////////////
			playState = xPopup.yes;
			sprintf(xRocks.strTemp, "%d슬롯오픈",(xPopup.num+1));
			setFiveRocksCustom("프리미엄제작슬롯",xRocks.strTemp,"NULL","NULL",1);
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_CAR_BUYYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			if(xWorldMap.isCashShop == TRUE)
			{
				subTemp[12] = xShop.carSlot[xShop.selectSlot];
			}
			else
			{
				subTemp[12] = xCar.slotCode[xCar.selectSlot];
			}
			
			switch(xCarData[subTemp[12]].priceType)
			{
			case 0:		//골드
				setMoney(-xCarData[subTemp[12]].price.oriData);
				break;
			case 1:		//룩
				setCash(-xCarData[subTemp[12]].price.oriData);
				break;
			}
			xCar.isOpen[subTemp[12]] = TRUE;
			///////////////////////////////////////////////////////////////////
			xEventQueueNet.code[xEventQueueNet.totalNum] = subTemp[12];
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CAR, TRUE);
			///////////////////////////////////////////////////////////////////
			setCarStorage(2);
			playState = xPopup.yes;
			
						
			sprintf(xRocks.strTemp,"%s",xCarData[subTemp[12]].strName);
			setFiveRocksCustom("아이템","자동차",xRocks.strTemp,"NULL",1);
			
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_TEST_ALLTILE:
		if(xPopup.selectNum == POPUPYES)
		{
			setMapData(xInterior.xBuildSlot.codeTeam[0]);
			int totalNum = 0;
			int	sellTotalNum=0;
			int tileNum = 0;
			int interiorNum = 0;
			int sellMoney;
			
			switch(xMap.type)
			{
			case INTERIOR_TYPE_FLOORTILE:
				if(xWorldMap.isTuto == TRUE)
				{
					switch(xQuestTuto.nowNum)
					{
					case TUTO_26_INTERIOR_OK0:
						xQuestTuto.isTutoClean = TRUE;
						break;
					}
				}
					
				totalNum = xMap.shopPointW * xMap.shopPointH;
				for(int x=0;x<xMap.shopPointW;x++)
				{
					for(int y=0;y<xMap.shopPointH;y++)
					{
						if(xMap.data[xMap.nowFloor][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y] == (xMap.type*1000)+xMap.listNum)
							tileNum++;
					}
				}
				
				for(int i=0;i<xInventoryInterior.totalNum;i++)
				{
					if(xInventoryInterior.itemCode[i] == (xMap.type*1000)+xMap.listNum)
						interiorNum++;
				}
				
				sellTotalNum = totalNum;
				sellTotalNum -= tileNum;
				sellTotalNum -= interiorNum;
				
				if(sellTotalNum < 0)
				{
					interiorNum += sellTotalNum;
					sellTotalNum = 0;
				}
				break;
			case INTERIOR_TYPE_WALLTILE:
				if(xWorldMap.isTuto == TRUE)
				{
					switch(xQuestTuto.nowNum)
					{
					case TUTO_26_INTERIOR_OK1:
						xQuestTuto.isTutoClean = TRUE;
						break;
					}
				}
				
				totalNum = xMap.shopPointW + xMap.shopPointH;
				
				for(int x=0;x<xMap.shopPointW;x++)
				{
					if(xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY-1] == (xMap.type*1000)+xMap.listNum || -xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY-1] == (xMap.type*1000)+xMap.listNum)
						tileNum++;
				}
				for(int y=0;y<xMap.shopPointH;y++)
				{
					if(xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX-1][xMap.shopPointY+y] == (xMap.type*1000)+xMap.listNum || -xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX-1][xMap.shopPointY+y] == (xMap.type*1000)+xMap.listNum)
						tileNum++;
				}
				
				for(int i=0;i<xInventoryInterior.totalNum;i++)
				{
					if(xInventoryInterior.itemCode[i] == (xMap.type*1000)+xMap.listNum)
						interiorNum++;
				}
				
				sellTotalNum = totalNum;
				sellTotalNum -= tileNum;
				sellTotalNum -= interiorNum;
				
				if(sellTotalNum < 0)
				{
					interiorNum += sellTotalNum;
					sellTotalNum = 0;
				}
				break;
			}
						
			sellMoney = sellTotalNum * xObj.xObjData[xMap.type][xMap.listNum].price.oriData;
			
			
			switch(xObj.xObjData[xMap.type][xMap.listNum].priceType)
			{
			case 0:		//골드
				if(sellMoney > xSaveTemp.money.oriData)
				{
					setPopup(POPUP_MONEYEMPTY, PLAY_PLAY, PLAY_PLAY, 0, DONT);
					return;
				}
				else
				{
					setMoney(-sellMoney);
					setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_GOLD,-sellMoney);

					switch(xMap.type)
					{
					case INTERIOR_TYPE_FLOORTILE:
						setQuest(24, sellTotalNum, DONT);
						break;
					case INTERIOR_TYPE_WALLTILE:
						setQuest(25, sellTotalNum, DONT);
						break;
					}
				}
				break;
			case 1:		//룩
				if(sellMoney > xSaveTemp.cash.oriData)
				{
					setPopup(POPUP_CASHEMPTY, PLAY_PLAY, PLAY_PLAY, 0, DONT);
					return;
				}
				else
				{
					setCash(-sellMoney);
					setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_LOOK,-sellMoney);
					switch(xMap.type)
					{
					case INTERIOR_TYPE_FLOORTILE:
						setQuest(24, sellTotalNum, DONT);
						break;
					case INTERIOR_TYPE_WALLTILE:
						setQuest(25, sellTotalNum, DONT);
						break;
					}
				}
				break;
			}
			
			//구매가격:sellMoney
			//총구매갯수:totalNum
			//인벤토리제외갯수:interiorNum
			for(int i=0;i<interiorNum;i++)
				outputInventoryInterior(xInterior.xBuildSlot.codeTeam[0]);
			//////////////////////////////////////////////////////////////////////////////
			xEventQueueNet.code[xEventQueueNet.totalNum] = xInterior.xBuildSlot.codeTeam[0];
			xEventQueueNet.code[xEventQueueNet.totalNum] = xEventQueueNet.code[xEventQueueNet.totalNum]<0?-xEventQueueNet.code[xEventQueueNet.totalNum]:xEventQueueNet.code[xEventQueueNet.totalNum];
			xEventQueueNet.haveNum[xEventQueueNet.totalNum] = 0;
			for(int ee=0;ee<xInventoryInterior.totalNum;ee++)
			{
				if(xInventoryInterior.itemCode[ee] == xEventQueueNet.code[xEventQueueNet.totalNum])
					xEventQueueNet.haveNum[xEventQueueNet.totalNum]++;
			}			
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_INTERIOR, TRUE);
			//////////////////////////////////////////////////////////////////////////////
			
			
			M_Boolean isInterior;
			int totalInteriorSlot = 0;;
			int interiorSlot[256];
			int tempCode;
			
			switch(xMap.type)
			{
			case INTERIOR_TYPE_FLOORTILE:
				for(int x=0;x<xMap.shopPointW;x++)
				{
					for(int y=0;y<xMap.shopPointH;y++)
					{
						///////////////기존타일 넣어주기/////////////////
						tempCode = xMap.data[xMap.nowFloor][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y];
						if(tempCode < 0)
							tempCode = -tempCode;
						
						if(tempCode != (xMap.type*1000)+xMap.listNum)
						{
							inputInventoryInterior(tempCode);
							isInterior = FALSE;
							for(int tt=0;tt<totalInteriorSlot;tt++)
							{
								if(interiorSlot[tt] == tempCode)
								{
									isInterior = TRUE;
									break;
								}
							}
							if(isInterior == FALSE)
								interiorSlot[totalInteriorSlot++] = tempCode;
						}
						xMap.data[xMap.nowFloor][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y] = (xMap.type*1000)+xMap.listNum;
						xMap.dataKey[xMap.nowFloor][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y] = 0;
					}
				}
				break;
			case INTERIOR_TYPE_WALLTILE:
				for(int x=0;x<xMap.shopPointW;x++)
				{
					///////////////기존타일 넣어주기/////////////////
					tempCode = xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY-1];
					if(tempCode < 0)
						tempCode = -tempCode;
					
					if(tempCode != (xMap.type*1000)+xMap.listNum)
					{
						inputInventoryInterior(tempCode);
						isInterior = FALSE;
						for(int tt=0;tt<totalInteriorSlot;tt++)
						{
							if(interiorSlot[tt] == tempCode)
							{
								isInterior = TRUE;
								break;
							}
						}
						if(isInterior == FALSE)
							interiorSlot[totalInteriorSlot++] = tempCode;
					}
					
					xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY-1] = -((xMap.type*1000)+xMap.listNum);
					xMap.dataKey[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY-1] = 0;

				}
				for(int y=0;y<xMap.shopPointH;y++)
				{
					///////////////기존타일 넣어주기/////////////////
					tempCode = xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX-1][xMap.shopPointY+y];
					if(tempCode < 0)
						tempCode = -tempCode;
					
					if(tempCode != (xMap.type*1000)+xMap.listNum)
					{
						inputInventoryInterior(tempCode);
						isInterior = FALSE;
						for(int tt=0;tt<totalInteriorSlot;tt++)
						{
							if(interiorSlot[tt] == tempCode)
							{
								isInterior = TRUE;
								break;
							}
						}
						if(isInterior == FALSE)
							interiorSlot[totalInteriorSlot++] = tempCode;
					}
					xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX-1][xMap.shopPointY+y] = (xMap.type*1000)+xMap.listNum;
					xMap.dataKey[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX-1][xMap.shopPointY+y] = 0;
				}
				break;
			}
			
			for(int tt=0;tt<totalInteriorSlot;tt++)
			{
				//////////////////////////////////////////////////////////////////////////////
				xEventQueueNet.code[xEventQueueNet.totalNum] = interiorSlot[tt];
				xEventQueueNet.code[xEventQueueNet.totalNum] = xEventQueueNet.code[xEventQueueNet.totalNum]<0?-xEventQueueNet.code[xEventQueueNet.totalNum]:xEventQueueNet.code[xEventQueueNet.totalNum];
				xEventQueueNet.haveNum[xEventQueueNet.totalNum] = 0;
				for(int ee=0;ee<xInventoryInterior.totalNum;ee++)
				{
					if(xInventoryInterior.itemCode[ee] == xEventQueueNet.code[xEventQueueNet.totalNum])
						xEventQueueNet.haveNum[xEventQueueNet.totalNum]++;
				}
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_INTERIOR, TRUE);
				//////////////////////////////////////////////////////////////////////////////
			}

			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, TRUE);
			///////////////////////////////기본타일 변경////////////////////////////////
			switch(xMap.type)
			{
			case INTERIOR_TYPE_FLOORTILE:
				xMap.floorInitCode[xMap.nowFloor] = (xMap.type*1000)+xMap.listNum;
				xEventQueueNet.action[xEventQueueNet.totalNum] = 0;
				break;
			case INTERIOR_TYPE_WALLTILE:
				xMap.wallInitCode[xMap.nowFloor] = (xMap.type*1000)+xMap.listNum;
				xEventQueueNet.action[xEventQueueNet.totalNum] = 1;
				break;
			}
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_TILE, TRUE);
			////////////////////////////////////////////////////////////////////////
			
			
			switch(xMap.type)
			{
			case INTERIOR_TYPE_FLOORTILE:
				if(xMap.nowFloor == 0)
				{
					////////////////////////////////////////
					xMap.tileInitW = xMap.shopPointW;
					xMap.tileInitH = xMap.shopPointH;
					xEventQueueNet.action[xEventQueueNet.totalNum] = 1;		//0:증축1:확장
					addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_FLOOR, TRUE);
					///////////////////////////////////////
				}
				break;
			}
			
			switch(xMap.type)
			{
			case INTERIOR_TYPE_FLOORTILE:
				for(int x=0;x<15;x++)
				{
					for(int y=0;y<15;y++)
					{
						///////////////기존타일 넣어주기/////////////////
						xMap.data[xMap.nowFloor][MAP_TYPE_FLOORTILE0][xMap.shopPointX+x][xMap.shopPointY+y] = xMap.floorInitCode[xMap.nowFloor];
					}
				}
				break;
			case INTERIOR_TYPE_WALLTILE:
				for(int x=0;x<15;x++)
					xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX+x][xMap.shopPointY-1] = -xMap.wallInitCode[xMap.nowFloor];
					
				for(int y=0;y<15;y++)
					xMap.data[xMap.nowFloor][MAP_TYPE_WALL0][xMap.shopPointX-1][xMap.shopPointY+y] = xMap.wallInitCode[xMap.nowFloor];
				break;
			}
			
			xInterior.xBuildSlot.codeTeam[0] = 0;
			playState = xPopup.yes;
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_EXTENSION_BUYYESNO_TILE:
		if(xPopup.selectNum == POPUPYES)
		{
			switch(xExtensionShop.xSlotTile[xExtensionShop.selectSlot].priceType)
			{
			case 0:		//골드
				setMoney(-xExtensionShop.tilePrice[xExtensionShop.xSlotTile[xExtensionShop.selectSlot].tile][xExtensionShop.xSlotTile[xExtensionShop.selectSlot].priceType].oriData);
				setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_GOLD, -xExtensionShop.tilePrice[xExtensionShop.xSlotTile[xExtensionShop.selectSlot].tile][xExtensionShop.xSlotTile[xExtensionShop.selectSlot].priceType].oriData);
				sprintf(xRocks.strTemp,"%dX%d", xMap.extension+8,xMap.extension+8);
				setFiveRocksCustom("아이템","확장(골드)",xRocks.strTemp,"NULL",1);
				break;
			case 1:		//룩
				setCash(-xExtensionShop.tilePrice[xExtensionShop.xSlotTile[xExtensionShop.selectSlot].tile][xExtensionShop.xSlotTile[xExtensionShop.selectSlot].priceType].oriData);
				setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_LOOK, -xExtensionShop.tilePrice[xExtensionShop.xSlotTile[xExtensionShop.selectSlot].tile][xExtensionShop.xSlotTile[xExtensionShop.selectSlot].priceType].oriData);
				sprintf(xRocks.strTemp,"%dX%d", xMap.extension+8,xMap.extension+8);
				setFiveRocksCustom("아이템","확장(캐시)",xRocks.strTemp,"NULL",1);
				break;
			}
			xMap.extension++;
			////////////////////////////////////////
			xEventQueueNet.action[xEventQueueNet.totalNum] = 1;		//0:증축1:확장
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_FLOOR, TRUE);
			///////////////////////////////////////
			
			
			if(xMap.floorInitCode[xMap.nowFloor] != FLOORTILEINITCODE)
			{
				for(int y=xMap.shopPointY;y<xMap.shopPointY+xMap.shopPointH+1;y++)
				{
					int x = xMap.shopPointX+xMap.shopPointW;
					xMap.data[0][MAP_TYPE_FLOORTILE0][x][y] = FLOORTILEINITCODE;
				}
				
				for(int x=xMap.shopPointX;x<xMap.shopPointX+xMap.shopPointW+1;x++)
				{
					int y = xMap.shopPointY+xMap.shopPointH;
					xMap.data[0][MAP_TYPE_FLOORTILE0][x][y] = FLOORTILEINITCODE;
				}
			}
						
			if(xMap.wallInitCode[xMap.nowFloor] != WALLTILEINITCODE)
			{
				int x = xMap.shopPointX-1;
				int y = xMap.shopPointY+xMap.shopPointH;
				if(xMap.data[0][MAP_TYPE_WALL0][x][y] == 0||xMap.data[0][MAP_TYPE_WALL0][x][y] == xMap.wallInitCode[xMap.nowFloor])
					subTemp[0] = 0;
				else
					subTemp[0] = 1;
								
				
				//////////////////////////////////////////////////////////////////////////////
				xMap.data[0][MAP_TYPE_WALL0][x][y] = WALLTILEINITCODE;
				/////////////////////////////////////////////////////////////////////////////
				xEventQueueNet.floor[xEventQueueNet.totalNum] = 0;
				xEventQueueNet.action[xEventQueueNet.totalNum] = subTemp[0];	//0:신규1:업데이트2:삭제
				xEventQueueNet.code[xEventQueueNet.totalNum] = xMap.data[0][MAP_TYPE_WALL0][x][y];
				xEventQueueNet.key[xEventQueueNet.totalNum] = xMap.dataKey[0][MAP_TYPE_WALL0][x][y];
				xEventQueueNet.mapX[xEventQueueNet.totalNum] = x;
				xEventQueueNet.mapY[xEventQueueNet.totalNum] = y;
				xEventQueueNet.layer[xEventQueueNet.totalNum][0] = 0;	//골드
				xEventQueueNet.layer[xEventQueueNet.totalNum][1] = 0;	//캐쉬
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_MAP, FALSE);
				////////////////////////////////////////////////////////////////////////////
				
				x = xMap.shopPointX+xMap.shopPointW;
				y = xMap.shopPointY-1;
				if(xMap.data[0][MAP_TYPE_WALL0][x][y] == 0||xMap.data[0][MAP_TYPE_WALL0][x][y] == -xMap.wallInitCode[xMap.nowFloor])
					subTemp[0] = 0;
				else
					subTemp[0] = 1;
				
				//////////////////////////////////////////////////////////////////////////////
				xMap.data[0][MAP_TYPE_WALL0][x][y] = -WALLTILEINITCODE;
				/////////////////////////////////////////////////////////////////////////////
				xEventQueueNet.floor[xEventQueueNet.totalNum] = 0;
				xEventQueueNet.action[xEventQueueNet.totalNum] = subTemp[0];	//0:신규1:업데이트2:삭제
				xEventQueueNet.code[xEventQueueNet.totalNum] = xMap.data[0][MAP_TYPE_WALL0][x][y];
				xEventQueueNet.key[xEventQueueNet.totalNum] = xMap.dataKey[0][MAP_TYPE_WALL0][x][y];
				xEventQueueNet.mapX[xEventQueueNet.totalNum] = x;
				xEventQueueNet.mapY[xEventQueueNet.totalNum] = y;
				xEventQueueNet.layer[xEventQueueNet.totalNum][0] = 0;	//골드
				xEventQueueNet.layer[xEventQueueNet.totalNum][1] = 0;	//캐쉬
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_MAP, FALSE);
				////////////////////////////////////////////////////////////////////////////
			}
			
			playState = xPopup.yes;
			
			xWorldMap.state = WORLDMAP_STATE_PLAY;
			xWorldMap.isExtensionEvent = TRUE;
			xWorldMap.extensionEventAnyCnt = 0;
			xWorldMap.isExternal = FALSE;
			xMap.pointX = xMap.pointCx;
			xMap.pointY = xMap.pointCy-150;
			xWorldMap.fscale = 0.8f;			
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_SHOP_REVIEWYESNO:
        if(xPopup.selectNum == POPUPYES)
		{
            if(xEventQueueNet.totalNum == 0)
            {
                playState = xPopup.yes;
                startWebView(xNetData.strReviewUrl);
            }
		}
        else
        {
            playState = xPopup.yes;
        }
		break;
	case POPUP_PRODUCTIONLINKFASHIONSHOWYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			freeFashion();
			setStateFashion();
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_EXTENSION_BUYYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			if(xExtensionShop.isCheckExtension == TRUE)
			{
				playState = xPopup.yes;
				setPopup(POPUP_EXTENSION_ERR, playState, playState, 0, DONT);
			}
			else
			{
				switch(xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].priceType)
				{
				case 0:		//골드
					setMoney(-xExtensionShop.floorPrice[xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].floor][xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].priceType].oriData);
					setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_GOLD, -xExtensionShop.floorPrice[xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].floor][xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].priceType].oriData);
					break;
				case 1:		//룩
					setCash(-xExtensionShop.floorPrice[xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].floor][xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].priceType].oriData);
					setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_LOOK, -xExtensionShop.floorPrice[xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].floor][xExtensionShop.xSlotFloor[xExtensionShop.selectSlot].priceType].oriData);
					break;
				}
				xMap.isOpen[0] = TRUE;
				xMap.totalFloor = 2;
				////////////////////////////////////////
				xEventQueueNet.action[xEventQueueNet.totalNum] = 0;		//0:증축1:확장
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_FLOOR, TRUE);
				///////////////////////////////////////
				playState = xPopup.yes;
				
				sprintf(xRocks.strTemp,"증축");
				setFiveRocksCustom("아이템","확장",xRocks.strTemp,"NULL",1);
				
			}
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_EXTENSIONWALL_BUYYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			switch(xExternalWallData.priceType[xExternalWall.listSlot[xExtensionShop.selectSlot]])
			{
			case 0:		//골드
				setMoney(-xExternalWallData.price[xExternalWall.listSlot[xExtensionShop.selectSlot]]);
				setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_GOLD, -xExternalWallData.price[xExternalWall.listSlot[xExtensionShop.selectSlot]]);
				break;
			case 1:		//룩
				setCash(-xExternalWallData.price[xExternalWall.listSlot[xExtensionShop.selectSlot]]);
				setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_LOOK, -xExternalWallData.price[xExternalWall.listSlot[xExtensionShop.selectSlot]]);
				break;
			}
			
			freeImg(&imgExternalWallS[0]);
			freeImg(&imgExternalWallS[1]);
			freeImg(&imgExternalWallS[2]);
			freeImg(&imgExternalWallS[3]);
			freeImg(&imgExternalWallS[4]);
			freeImg(&imgExternalWallS[5]);
			freeImg(&imgExternalWallS[6]);
			freeImg(&imgExternalWall[0]);
			freeImg(&imgExternalWall[1]);
			xExternalWall.selectWall = xExternalWall.selectWallChange;
			
									
			xExternalWallData.isOpen[xExternalWall.selectWallChange] = TRUE;
			////////////////////////////////////////////
			xEventQueueNet.action[xEventQueueNet.totalNum] = 1;	//0:설정,1:구입
			xEventQueueNet.code[xEventQueueNet.totalNum] = xExternalWall.selectWallChange;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_EXTERNALWALL, FALSE);
			///////////////////////////////////////////
			////////////////////////////////////////////
			xEventQueueNet.action[xEventQueueNet.totalNum] = 0;	//0:설정,1:구입
			xEventQueueNet.code[xEventQueueNet.totalNum] = xExternalWall.selectWallChange;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_EXTERNALWALL, FALSE);
			///////////////////////////////////////////
								
			sprintf(xRocks.strTemp,"%s",xExternalWallData.strName[xExternalWall.selectWallChange]);
			setFiveRocksCustom("아이템","외벽",xRocks.strTemp,"NULL",1);
			
		}
		else
		{
			playState = xPopup.no;
			interiorShopFreeLoad(TRUE);
			xWorldMap.state = WORLDMAP_STATE_INTERIORSHOP;
		}
		freeImg(&imgExternalWallSChange);
		freeImg(&imgExternalWallChange[0]);
		freeImg(&imgExternalWallChange[1]);
		freeImg(&imgExternalWallChange[2]);

		break;
	case POPUP_EXTENSIONWALL_EQUIPYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
						
			freeImg(&imgExternalWallS[0]);
			freeImg(&imgExternalWallS[1]);
			freeImg(&imgExternalWallS[2]);
			freeImg(&imgExternalWallS[3]);
			freeImg(&imgExternalWallS[4]);
			freeImg(&imgExternalWallS[5]);
			freeImg(&imgExternalWallS[6]);
			freeImg(&imgExternalWall[0]);
			freeImg(&imgExternalWall[1]);
			xExternalWall.selectWall = xExternalWall.selectWallChange;
			
			////////////////////////////////////////////
			xEventQueueNet.action[xEventQueueNet.totalNum] = 0;	//0:설정,1:구입
			xEventQueueNet.code[xEventQueueNet.totalNum] = xExternalWall.selectWallChange;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_EXTERNALWALL, FALSE);
			///////////////////////////////////////////
		}
		else
		{
			playState = xPopup.no;
			interiorShopFreeLoad(TRUE);
			xWorldMap.state = WORLDMAP_STATE_INTERIORSHOP;
		}
			
		freeImg(&imgExternalWallSChange);
		freeImg(&imgExternalWallChange[0]);
		freeImg(&imgExternalWallChange[1]);
		freeImg(&imgExternalWallChange[2]);
		break;
	case POPUP_EXTENSION_ERR:
		initMenuOut();
		interiorShopFreeLoad(FALSE);
		xWorldMap.state = WORLDMAP_STATE_PLAY;
		xInterior.buildModeTime64 = DONT;
		xWorldMap.isKeyReturn = TRUE;
			
		xMap.pointX = 826;
		xMap.pointY = -573;
		xWorldMap.fscale = 1.65f;
		playState = PLAY_PLAY;
		xExtensionShop.isExtensionErr = TRUE;
		xExtensionShop.extensionErrTime = xCalendar.nowTime;
		break;
	case POPUP_MODEL_SELLYESNO:
		if(xPopup.selectNum == POPUPYES)
		{
			switch(xModelData[xInventoryModel[xModel.infoInventoryNum].code].priceType)
			{
			case 0:		//골드
				setMoney(xModelData[xInventoryModel[xModel.infoInventoryNum].code].price*MODELSELLPER/100);
				setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_GOLD, xModelData[xInventoryModel[xModel.infoInventoryNum].code].price*MODELSELLPER/100);
				break;
			case 1:		//룩
				setMoney(xModelData[xInventoryModel[xModel.inventoryNum].code].price*MODELSELLCASH);
				setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_GOLD, xModelData[xInventoryModel[xModel.infoInventoryNum].code].price*MODELSELLCASH);
				break;
			}
						
			outPutInventoryModel(xModel.infoInventoryNum);
			setModelList(xModel.listTabNum);
			xModel.inventoryNum = DONT;
			
			switch(xModel.state)
			{
			case MODELCOLLECT_STATE_MAININFO:
				xModel.state = MODELCOLLECT_STATE_MAIN;
				break;
			case MODELCOLLECT_STATE_LISTINFO:
				xModel.state = MODELCOLLECT_STATE_LIST;
				break;
			}
			playState = xPopup.yes;
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_MODELMAIN_SLOTOPENGOLD:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			if(xSaveTemp.money.oriData < xModelMainSlot[xModel.selectMainSlot].openPrice[0])
			{
				setPopup(POPUP_MONEYEMPTY, playState, playState, 0, DONT);
			}
			else
			{
				setMoney(-xModelMainSlot[xModel.selectMainSlot].openPrice[0]);
				xModelMainSlot[xModel.selectMainSlot].state = MODELMAINSLOT_STATE_EMPTY;
				xModelMainSlot[xModel.selectMainSlot].modelKey = 0;
				////////////////////////////////////////////
				xEventQueueNet.slotNum[xEventQueueNet.totalNum] = xModel.selectMainSlot;
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETMODELMAIN, FALSE);
				///////////////////////////////////////////
				
				//////////////////////////////////////////
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, FALSE);
				//////////////////////////////////////////
				
				sprintf(xRocks.strTemp, "%d슬롯",xModel.selectMainSlot+1);
				setFiveRocksCustom("모델","골드슬롯",xRocks.strTemp,"NULL",1);
			}
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_MODELMAIN_SLOTOPENCASH:
		if(xPopup.selectNum == POPUPYES)
		{
			playState = xPopup.yes;
			if(xSaveTemp.cash.oriData < xModelMainSlot[xModel.selectMainSlot].openPrice[1])
			{
				setPopup(POPUP_CASHEMPTY, playState, playState, 0, DONT);
			}
			else
			{
				setCash(-xModelMainSlot[xModel.selectMainSlot].openPrice[1]);
				xModelMainSlot[xModel.selectMainSlot].state = MODELMAINSLOT_STATE_EMPTY;
				xModelMainSlot[xModel.selectMainSlot].modelKey = 0;
				////////////////////////////////////////////
				xEventQueueNet.slotNum[xEventQueueNet.totalNum] = xModel.selectMainSlot;
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETMODELMAIN, FALSE);
				///////////////////////////////////////////
				
				//////////////////////////////////////////
				addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_GAMEINFO, FALSE);
				//////////////////////////////////////////
				sprintf(xRocks.strTemp, "%d슬롯",xModel.selectMainSlot+1);
				setFiveRocksCustom("모델","캐시슬롯",xRocks.strTemp,"NULL",1);

			}
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_BUILD_PAYMENTERR:
		if(xPopup.selectNum == POPUPYES)
		{
			setInteriorBuildMode(xInterior.selectSlotS,xInterior.selectSlotTeam);
			playState = xPopup.yes;
		}
		else
		{
			playState = xPopup.no;
		}
		break;
	case POPUP_MODELMAIN_DEL:
		if(xPopup.selectNum == POPUPYES)
		{
			xModel.state = MODELCOLLECT_STATE_MAIN;
			xModelMainSlot[xModel.selectMainSlot].state = MODELMAINSLOT_STATE_EMPTY;
			xModelMainSlot[xModel.selectMainSlot].modelKey = 0;
			////////////////////////////////////////////
			xEventQueueNet.slotNum[xEventQueueNet.totalNum] = xModel.selectMainSlot;
			addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETMODELMAIN, FALSE);
			///////////////////////////////////////////
			playState = xPopup.yes;
		}
		else
		{
			playState = xPopup.no;
		}
		break;
    case POPUP_FRIENDDEL:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            int kakaoSlot = checkKakaoAppInvite(xFriendData[xFriendMap.selectDataSlotNum].strKakaoId);
            if(kakaoSlot != DONT)
            {
                xSaveKakaoApp.isDel[kakaoSlot] = TRUE;
                gameSave(SAVE_SLOT_KAKAOAPP);
            }
            playSnd(SND_MENU_OK);
            xFriendData[xFriendMap.selectDataSlotNum].isAdd = FALSE;
            xFriendData[xFriendMap.selectDataSlotNum].isFriend = FALSE;
            /////////////////////////////////
            xEventQueueNet.friendNum[xEventQueueNet.totalNum] = xFriendData[xFriendMap.selectDataSlotNum].userNum;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_DELFRIEND, FALSE);
            ////////////////////////////////
        }
        else
        {
            
        }
        break;
    case POPUP_RIVALSTOP:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_RIVALSTOP, TRUE);
            xRival.state = RIVAL_STATE_FAIL;
            xRivalInfo.state = RIVALINFO_STATE_FAILANY;
            xRivalInfo.resultAnyCnt = 0;
        }
        else
        {
            
        }
        break;
    case POPUP_SELLFAST:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            xSell.state = SELL_STATE_MAIN;
            int usePop = getFastSellCash(xSellTableInfo[xMap.nowFloor][xSell.selectSellTable].xSlot[xSell.selectSlot].num);
            setCash(-usePop);
            setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_LOOK,-usePop);
            xSellTableInfo[xMap.nowFloor][xSell.selectSellTable].xSlot[xSell.selectSlot].num = 0;
            
            /////////////////////////
            xEventQueueNet.POP[xEventQueueNet.totalNum] = usePop;
            xEventQueueNet.floor[xEventQueueNet.totalNum] = xMap.nowFloor;
            xEventQueueNet.key[xEventQueueNet.totalNum] = xMap.dataKey[xMap.nowFloor][MAP_TYPE_OBJ][xSellTableInfo[xMap.nowFloor][xSell.selectSellTable].x][xSellTableInfo[xMap.nowFloor][xSell.selectSellTable].y];
            xEventQueueNet.SLOT[xEventQueueNet.totalNum] = xSell.selectSlot;
            xEventQueueNet.resultCash[xEventQueueNet.totalNum] = xSaveTemp.cash.oriData;
            addEventQueueNet(0, 0, NETQUEUE_TYPE_SELLFASTPOP, TRUE);
            /////////////////////////
            setQuest(33, 1, DONT);
            setFiveRocksCustom("즉시완료","즉시완료횟수","판매(단일)즉시완료","NULL",1);
        }
        else
        {
            
        }
        break;
            
    /*case POPUP_TESTTEST:
            playState = xPopup.yes;
            if(xPopup.selectNum == POPUPYES)
            {
                setPopup(POPUP_TEST_AFTERMAKE, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            }
            else
            {
                
            }
            break;*/
            
    case POPUP_PRODUCTIONFAST:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            setMapData(xProductionMenu.slotCode[xProductionMenu.selectType][xProductionMenu.selectSlot]);
            
            int remainTime = xFashionData[xMap.type][xMap.listNum].makeTime.oriData - xProductionMenu.slotFlowTime[xProductionMenu.selectType][xProductionMenu.selectSlot];
            
            xSell.state = SELL_STATE_MAIN;
            xSaveTemp.makeCashNum++;
            
            setCash(-getFastTimeCash(remainTime));
            setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_LOOK,-getFastTimeCash(remainTime));
            
            xProductionMenu.slotFlowTime[xProductionMenu.selectType][xProductionMenu.selectSlot] += xFashionData[xMap.type][xMap.listNum].makeTime.oriData;
            xProductionMenu.pushState[xProductionMenu.selectType][xProductionMenu.selectSlot] = 1;	//0:주문1:취소
            if(xSave.isPushOnOff[PUSHONOFF_PRODUCTION] == FALSE)
                xProductionMenu.pushState[xProductionMenu.selectType][xProductionMenu.selectSlot] = 1;	//0:주문1:취소
            xProductionMenu.pushTime[xProductionMenu.selectType][xProductionMenu.selectSlot] = 0;
            xProductionMenu.useLook[xProductionMenu.selectType][xProductionMenu.selectSlot] = 1;
            xProductionMenu.isUpData[xProductionMenu.selectType][xProductionMenu.selectSlot] = TRUE;
            
            
            ////////////////////////////////////////////////////////////////////////////
            xEventQueueNet.SLOT[xEventQueueNet.totalNum] = (xProductionMenu.selectType*6)+xProductionMenu.selectSlot;
            xEventQueueNet.resultCash[xEventQueueNet.totalNum] = xSaveTemp.cash.oriData;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PRODUCTIONFASTPOP, TRUE);
            ////////////////////////////////////////////////////////////////////////////
            setFiveRocksCustom("즉시완료","즉시완료횟수","제작(단일)즉시완료","NULL",1);
        }
        else
        {
            
        }
        break;
    case POPUP_PRODUCTIONFAST2:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            int remainTime = xFashionData[xMap.type][xMap.listNum].makeTime.oriData - xProductionMenu.slotFlowTime[xProductionMenu.selectType][xProductionMenu.selectSlot];
            xProductionMenu.state2 = PRODUCTIONMENU_STATE_MAIN;
            
            setMapData(xProductionMenu.slotCode[xProductionMenu.selectType][xProductionMenu.selectSlot]);
            playState = xPopup.yes;
            xSaveTemp.makeCashNum++;
            setCash(-getFastTimeCash(remainTime));
            setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_LOOK,-getFastTimeCash(remainTime));
            
            xProductionMenu.slotFlowTime[xProductionMenu.selectType][xProductionMenu.selectSlot] += xFashionData[xMap.type][xMap.listNum].makeTime.oriData;
            xProductionMenu.pushState[xProductionMenu.selectType][xProductionMenu.selectSlot] = 1;	//0:주문1:취소
            if(xSave.isPushOnOff[PUSHONOFF_PRODUCTION] == FALSE)
                xProductionMenu.pushState[xProductionMenu.selectType][xProductionMenu.selectSlot] = 1;	//0:주문1:취소
            xProductionMenu.pushTime[xProductionMenu.selectType][xProductionMenu.selectSlot] = 0;
            xProductionMenu.useLook[xProductionMenu.selectType][xProductionMenu.selectSlot] = 1;
            xProductionMenu.isUpData[xProductionMenu.selectType][xProductionMenu.selectSlot] = TRUE;
            ////////////////////////////////////////////////////////////////////////////
            xEventQueueNet.SLOT[xEventQueueNet.totalNum] = (xProductionMenu.selectType*6)+xProductionMenu.selectSlot;
            xEventQueueNet.resultCash[xEventQueueNet.totalNum] = xSaveTemp.cash.oriData;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PRODUCTIONFASTPOP, TRUE);
            ////////////////////////////////////////////////////////////////////////////
            setFiveRocksCustom("즉시완료","즉시완료횟수","제작(단일)즉시완료","NULL",1);
        }
        break;
    case POPUP_AMULETBUY:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            //골드
            if(xAmulet.xData[xAmuletSetting.xEditPage.amuletCode].priceType == 0)
            {
                setMoney(-xAmulet.xData[xAmuletSetting.xEditPage.amuletCode].priceValue);
                setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_GOLD,-xAmulet.xData[xAmuletSetting.xEditPage.amuletCode].priceValue);

            }
            else if(xAmulet.xData[xAmuletSetting.xEditPage.amuletCode].priceType == 1)
            {
                setCash(-xAmulet.xData[xAmuletSetting.xEditPage.amuletCode].priceValue);
                setBonus(xTouch.xPos,xTouch.yPos,ICON_TYPE_LOOK,-xAmulet.xData[xAmuletSetting.xEditPage.amuletCode].priceValue);
            }
            
            xAmulet.xData[xAmuletSetting.xEditPage.amuletCode].isOpen = true;
            
            ////////////nets
            xEventQueueNet.code[xEventQueueNet.totalNum] = xAmuletSetting.xEditPage.amuletCode;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_AMULETBUY, TRUE);
            ////////////nete
        }
        else
        {
            
        }
        break;
    case POPUP_AMULETPAGEBUY:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            if(xSaveTemp.cash.oriData < xAmulet.xAmuletPage[xPopup.num].pagePrice)
            {
                setPopup(POPUP_CASHEMPTY, PLAY_PLAY, PLAY_PLAY, 0, DONT);
            }
            else
            {
                xAmulet.xAmuletPage[xPopup.num].isOpen = true;
                setCash(-xAmulet.xAmuletPage[xPopup.num].pagePrice);
                setBonus(xTouch.xPos, xTouch.yPos, ICON_TYPE_LOOK, -xAmulet.xAmuletPage[xPopup.num].pagePrice);
                
                ///////////s
                xEventQueueNet.code[xEventQueueNet.totalNum] = xPopup.num;
                addEventQueueNet(0, 0, NETQUEUE_TYPE_AMULETPAGEBUY, TRUE);
                ///////////e
            }
        }
        else
        {
        }
        break;
    case POPUP_CLUBMAKE:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            xClubList.state = CLUBLIST_STATE_MAKENET;
            /////////////////nets
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBMAKE, TRUE);
            /////////////////nets            
        }
        else
        {
            
        }
        break;
    case POPUP_CLUBMAKEOK:
    case POPUP_CLUBJOINOK:
        playState = xPopup.yes;
        
        clubListFreeLoad(false);
        xWorldMap.state = WORLDMAP_STATE_PLAY;
        break;
    case POPUP_CLUBMASTERYESNO:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            xClubLobby.state = CLUBLOBBY_STATE_NET;
            
            ////////////////////////////////////////////////////
            xEventQueueNet.key[xEventQueueNet.totalNum] = xClub.xMember[xClubLobby.selectSlot].userKey;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETCLUBMASTER, TRUE);
            ///////////////////////////////////////////////////
            
            ////////////////////////////////////////////////////
            xEventQueueNet.key[xEventQueueNet.totalNum] = xClub.xMy.clubKey;
            
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBDATA, TRUE);
            ///////////////////////////////////////////////////
            
        }
        else
        {
        }
        break;
    case POPUP_CLUBFORCEOUTYESNO:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            xClubLobby.state = CLUBLOBBY_STATE_NET;
            
            
            ////////////////////////////////////////////////////
            xEventQueueNet.key[xEventQueueNet.totalNum] = xClub.xMember[xClubLobby.selectSlot].userKey;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETCLUBFORCEOUT, TRUE);
            ///////////////////////////////////////////////////
            
            ////////////////////////////////////////////////////
            xEventQueueNet.key[xEventQueueNet.totalNum] = xClub.xMy.clubKey;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBMEMBER, TRUE);
            ///////////////////////////////////////////////////
            
            
            
            
        }
        else
        {
        }
        break;
    case POPUP_CLUBUNREGYESNO:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            xClubLobby.state = CLUBLOBBY_STATE_NET;
            /////////////////////////////////////////
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBUNREG, TRUE);
            /////////////////////////////////////////
        }
        break;
    case POPUP_CLUBUNREGOK:
        playState = xPopup.yes;
            
        xClubLobby.state = CLUBLOBBY_STATE_PLAY;
        xClub.xMy.clubKey = DONT;
        clubLobbyFreeLoad(false);
        xWorldMap.state = WORLDMAP_STATE_PLAY;
        break;
    case POPUP_CLUBBOOKDEL:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            xClubLobby.state = CLUBLOBBY_STATE_NET;
            /////////////////////////////////////////
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBBOOKDEL, TRUE);
            /////////////////////////////////////////
        }
        break;
            
    case POPUP_FASHIONWEEKHAIRBUY:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            
            
            ////////////////////////////////////////////////////
            xEventQueueNet.code[xEventQueueNet.totalNum] = 10000+xPopup.num;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBDRESSBUY, TRUE);
            ////////////////////////////////////////////////////
            
        }
        break;
    case POPUP_FASHIONWEEKFACEBUY:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            //xFaceData[xPopup.num].isClubOpen = true;
            
            ////////////////////////////////////////////////////            
            xEventQueueNet.code[xEventQueueNet.totalNum] = 20000+xPopup.num;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBDRESSBUY, TRUE);
            ////////////////////////////////////////////////////
        }
        break;
    case POPUP_FASHIONWEEKFASHIONBUY:
        playState = xPopup.yes;
        if(xPopup.selectNum == POPUPYES)
        {
            setMapData(xPopup.num);
            //xFashionWeekItem[xMap.type][xMap.listNum].isOpen = true;
            ////////////////////////////////////////////////////
            xEventQueueNet.code[xEventQueueNet.totalNum] = xPopup.num;
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBDRESSBUY, TRUE);
            ////////////////////////////////////////////////////
        }
        break;
    case POPUP_CLUBSHOPITEMBUYCHECK:
        if(xPopup.selectNum==POPUPYES)
        {
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBITEMBUY, TRUE);
            playState = xPopup.yes;
        }
        else
        {
            playState=xPopup.no;
        }
        break;
    case POPUP_CLUBGIVEGIFTCHECK:
        if(xPopup.selectNum==POPUPYES)
        {
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBGIVEGIFT, TRUE);
            playState = xPopup.yes;
        }
        else
        {
            playState=xPopup.no;
        }
        break;
    case POPUP_CLUBDONATIONGOLDCHECK:
        if(xPopup.selectNum==POPUPYES)
        {
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBDONATION, DONT);
            playState = xPopup.yes;
        }
        else
        {
            playState=xPopup.no;
        }
        break;
    case POPUP_CLUBDONATIONCANDYCHECK:
        if(xPopup.selectNum==POPUPYES)
        {
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBDONATION, DONT);
            playState = xPopup.yes;
        }
        else
        {
            playState=xPopup.no;
        }
        break;
    case POPUP_CLUBICONBUYCHECK:
        if(xPopup.selectNum==POPUPYES)
        {
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBICONBUY , DONT);
            playState = xPopup.yes;
        }
        else
        {
            playState=xPopup.no;
        }
        break;
    
    case POPUP_CLUBICONCHANGECHECK:
        if(xPopup.selectNum==POPUPYES)
        {
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBICONUPDATE, DONT);
            playState = xPopup.yes;
        }
        else
        {
            playState=xPopup.no;
        }
        break;
    case POPUP_PANGTIMESRESETCHECK:
        if(xPopup.selectNum==POPUPYES)
        {
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PANGTIMESRESET, TRUE);
            playState = xPopup.yes;
        }
        else
        {
            playState=xPopup.no;
        }
        break;
    case POPUP_INPUTINVENTORYFORMERERR1:
        if(xPopup.selectNum==POPUPYES)
        {
            addEventQueue(xInterior.buildMapTileXpos, xInterior.buildMapTileYpos, EVENTQUEUE_TYPE_INPUTINVEN,xMap.nowFloor,xSelectTileOne.tileNumX,xSelectTileOne.tileNumY);
            xInterior.buildInType = INTERIORBUILD_TYPE_GAME;
            xInterior.xBuildSlot.codeTeam[0] = 0;
            switch(xMap.type)
            {
                case INTERIOR_TYPE_FLOORTILE:
                case INTERIOR_TYPE_WALLTILE:
                    xInterior.buildMode = 1;
                    break;
                default:
                    xInterior.buildMode = 0;
                    break;
            }
        }
        else
        {
            playState=xPopup.no;
        }
	default:
		switch(xPopup.selectNum)
		{
		case POPUPYES:
			playState = xPopup.yes;
			break;
		case POPUPNO :
			playState = xPopup.no;
			break;
		}
		break;
	}
	xWorldMap.isKeyReturn = TRUE;
}

void drawBtn(M_Int32 x,M_Int32 y,M_Int32 type)
{
	switch(type)
	{
	case BTN_OK_CONFIRM:
		drawPacker(imgPopupBtn0, x, y, 0, imgH(imgPopupBtn0)/2, imgW(imgPopupBtn0), imgH(imgPopupBtn0)/2, VH);
		setFontSize(20);
		gDrawStringBold(x-2, y-2, "확인", VH, 255, 255, 255, 186, 70, 10);
		setFontSize(11);

		xTouchOk.wPos = imgW(imgPopupBtn0);
		xTouchOk.hPos = imgH(imgPopupBtn0)/2;
		xTouchOk.xPos = x - xTouchOk.wPos/2;
		xTouchOk.yPos = y - xTouchOk.hPos/2;
		break;
	case BTN_OK_LINK:
		drawPacker(imgPopupBtn0, x, y, 0, imgH(imgPopupBtn0)/2, imgW(imgPopupBtn0), imgH(imgPopupBtn0)/2, VH);
		setFontSize(20);
		gDrawStringBold(x-2, y-2, "이동", VH, 255, 255, 255, 186, 70, 10);
		setFontSize(11);
		
		xTouchOk.wPos = imgW(imgPopupBtn0);
		xTouchOk.hPos = imgH(imgPopupBtn0)/2;
		xTouchOk.xPos = x - xTouchOk.wPos/2;
		xTouchOk.yPos = y - xTouchOk.hPos/2;
		break;
	case BTN_CLR_CLEAR:
		drawPacker(imgPopupBtn2, x, y, 0, imgH(imgPopupBtn2)/2, imgW(imgPopupBtn2), imgH(imgPopupBtn2)/2, VH);
		setFontSize(20);
		gDrawStringBold(x-2, y-2, "취소", VH, 255, 255, 255, 77, 77, 77);
		setFontSize(11);

		xTouchClr.wPos = imgW(imgPopupBtn2);
		xTouchClr.hPos = imgW(imgPopupBtn2)/2;
		xTouchClr.xPos = x - xTouchClr.wPos/2;
		xTouchClr.yPos = y - xTouchClr.hPos/2;
		break;
	case BTN_YESNO:
		drawBtn(x+100, y,BTN_OK_CONFIRM);
		drawBtn(x-100, y,BTN_CLR_CLEAR);
		break;
	case BTN_LINKNO:
		drawBtn(x+100, y,BTN_OK_LINK);
		drawBtn(x-100, y,BTN_CLR_CLEAR);
		break;
	}
}



void dragScrollKeyPrc(XDRAGSCROLL *dragScroll, M_Int32 type)
{
	switch(type)
	{
		case 0:	//누름
			dragScroll->touchXposBefore = dragScroll->touchXpos;
			dragScroll->touchYposBefore = dragScroll->touchYpos;
			dragScroll->touchXpos = xTouch.xPos;
			dragScroll->touchYpos = xTouch.yPos;
									
			if(dragScroll->touchXposBefore != DONT)
			{
				dragScroll->pos += (dragScroll->touchXpos - dragScroll->touchXposBefore);
			}
			
			dragScroll->speed = 0;
			break;
		case 1:	//땜
			//같을경우 버그발생 예외처리
			if(dragScroll->touchXposBefore == dragScroll->touchXpos)
				dragScroll->touchXposBefore = DONT;
			
			if(dragScroll->touchXposBefore == DONT)
			{
				dragScroll->touchXpos = DONT;
				dragScroll->touchYpos = DONT;
				dragScroll->touchXposBefore = DONT;
				dragScroll->touchYposBefore = DONT;
				return;
			}
		 	
			dragScroll->speed = dragScroll->touchXpos - dragScroll->touchXposBefore;
			dragScroll->speed = dragScroll->speed*3;
			
			if(dragScroll->speed > 100)
				dragScroll->speed = 100;
			else if(dragScroll->speed < -100)
				dragScroll->speed = -100;
			
			
			
			
			if(dragScroll->speed == 0 && dragScroll->pos != 0)
			{
				if(dragScroll->pos > 0)
				{
					dragScroll->speed = -((dragScroll->pos/2)+1);
				}
				else
				{
					dragScroll->speed = ((-(dragScroll->pos/2))+1);
				}
			}
			
			
			
			dragScroll->touchXpos = DONT;
			dragScroll->touchYpos = DONT;
			dragScroll->touchXposBefore = DONT;
			dragScroll->touchYposBefore = DONT;
			
			
			break;
		case 2:
			if(dragScroll->touchXposBefore == DONT || dragScroll->touchXposBefore != dragScroll->touchXpos)
			{
				dragScroll->touchXposBefore = dragScroll->touchXpos;
				dragScroll->touchYposBefore = dragScroll->touchYpos;
				dragScroll->touchXpos = xTouch.yPos;
				dragScroll->touchYpos = xTouch.xPos;
				
				if(dragScroll->touchXposBefore != DONT)
					dragScroll->pos += (dragScroll->touchXpos - dragScroll->touchXposBefore);
			}
			dragScroll->speed = 0;
			break;
		case 3:
			
			
			//같을경우 버그발생 예외처리
			if(dragScroll->touchXposBefore == dragScroll->touchXpos)
				dragScroll->touchXposBefore = DONT;
						
			if(dragScroll->touchXposBefore == DONT)
			{
				dragScroll->touchXpos = DONT;
				dragScroll->touchYpos = DONT;
				dragScroll->touchXposBefore = DONT;
				dragScroll->touchYposBefore = DONT;
				return;
			}
			
			dragScroll->speed = dragScroll->touchXpos - dragScroll->touchXposBefore;
			dragScroll->speed = dragScroll->speed*3;
			
			if(dragScroll->speed > 100)
				dragScroll->speed = 100;
			else if(dragScroll->speed < -100)
				dragScroll->speed = -100;
			
			
									
			
			if(dragScroll->speed == 0 && dragScroll->pos != 0)
			{
				if(dragScroll->pos > 0)
				{
					dragScroll->speed = -((dragScroll->pos/2)+1);
				}
				else
				{
					dragScroll->speed = ((-(dragScroll->pos/2))+1);
				}
			}
			
			
			
			dragScroll->touchXpos = DONT;
			dragScroll->touchYpos = DONT;
			dragScroll->touchXposBefore = DONT;
			dragScroll->touchYposBefore = DONT;
			break;
	}
}

void dragScrollPrc(XDRAGSCROLL *dragScroll,M_Int32 type,M_Boolean isRolling)
{
	
	if(dragScroll->speed < 0)
	{
		dragScroll->pos += dragScroll->speed;
		dragScroll->speed += -(dragScroll->speed/2);
		
		if(dragScroll->speed >= -2)
			dragScroll->speed = 0;
		
	}
	else if(dragScroll->speed > 0)
	{
		dragScroll->pos += dragScroll->speed;
		dragScroll->speed -= (dragScroll->speed/2);
		
		if(dragScroll->speed <= 2)
			dragScroll->speed = 0;
	}
	
	
	switch(type)
	{
	case 0:
			
		while(TRUE)
		{
			if(dragScroll->pos >= dragScroll->posGab/2)
			{
				dragScroll->selectNum--;
				dragScroll->pos -= dragScroll->posGab;
				
			}
			else if(dragScroll->pos < -(dragScroll->posGab/2))
			{
				dragScroll->selectNum++;
				dragScroll->pos += dragScroll->posGab;
			}
			else
			{
				break;
			}
		
		}
	
		if(isRolling == TRUE)
		{
			while (TRUE)
			{
				if(dragScroll->selectNum < 0)
					dragScroll->selectNum = dragScroll->totalNum+dragScroll->selectNum;
				else if(dragScroll->selectNum >= dragScroll->totalNum)
					dragScroll->selectNum = dragScroll->totalNum-dragScroll->selectNum;
				else
					break;
			}
		}		
		
		if(dragScroll->selectNum < 0)
		{
			dragScroll->selectNum = 0;
			dragScroll->pos = dragScroll->posGab/3;
			dragScroll->speed = 0;
		}
		else if(dragScroll->selectNum == 0 && dragScroll->pos > 0)
		{
			if(isRolling == FALSE)
			{
				if(dragScroll->pos <=2)
					dragScroll->pos --;
				else
					dragScroll->pos -= dragScroll->pos/3;
				dragScroll->speed = 0;
			}
		}
		
		if(dragScroll->selectNum > dragScroll->totalNum-1)
		{
			dragScroll->selectNum = dragScroll->totalNum-1;
			dragScroll->pos = -dragScroll->posGab/3;
			dragScroll->speed = 0;
		}
		else if(dragScroll->selectNum == dragScroll->totalNum-1 && dragScroll->pos < 0)
		{
			if(isRolling == FALSE)
			{
				if(dragScroll->pos >=-2)
				{
					dragScroll->pos ++;
				}
				else
				{
					dragScroll->pos -= dragScroll->pos/3;
				}
				
				dragScroll->speed = 0;
			}
		}
			
		//위치 보정
		if(dragScroll->touchXpos == DONT)
		{
			if(dragScroll->speed == 0)
			{
				if(dragScroll->pos != 0)
				{
					if(dragScroll->pos > 0)
					{
						dragScroll->speed = -((dragScroll->pos/2)+1);
					}
					else
					{
						dragScroll->speed = ((-(dragScroll->pos/2))+1);
					}
				}
			}
		}
		break;
	case 1:
		if(dragScroll->pos > 0)
		{
			if(dragScroll->pos <=2)
				dragScroll->pos --;
			else
				dragScroll->pos -= dragScroll->pos/3;
		}
		 
	
		if(dragScroll->pos < dragScroll->endPos)
		{
			if(((-dragScroll->pos) - (-dragScroll->endPos)) <=2)
				dragScroll->pos ++;
			else
				dragScroll->pos += ((-dragScroll->pos) - (-dragScroll->endPos))/3;
		}
		break;
	}
}

void setPopupStringLine(M_Char *pChar,M_Int32 w)
{
    xPopup.totalLine = 0;
    memset(xPopup.strTextLine, 0, sizeof(xPopup.strTextLine));
    
    int index = 0;
    int kor = 0;
    int eng = 0;
    
    
    for(int i=0; i<strlen(pChar); i++)
    {
        if((unsigned char)pChar[i] >= 0xA4)
        {
            //한글
            xPopup.strTextLine[xPopup.totalLine][index++] = pChar[i++];
            xPopup.strTextLine[xPopup.totalLine][index++] = pChar[i++];
            xPopup.strTextLine[xPopup.totalLine][index++] = pChar[i];
            kor++;
        }
        else if(pChar[i] == '\n')
        {
            index = 0;
            kor = 0;
            eng = 0;
            xPopup.totalLine++;
        }
        else if(pChar[i] == 0x5c)
        {
            i++;
            if(pChar[i] == 'r')
            {
                continue;
            }
            index = 0;
            kor = 0;
            eng = 0;
            xPopup.totalLine++;
            continue;
        }
        else
        {
            xPopup.strTextLine[xPopup.totalLine][index++] = pChar[i];
            eng++;
        }
        
        if(kor+(eng*0.8) > w)
        {
            index = 0;
            kor = 0;
            eng = 0;
            xPopup.totalLine++;
        }
    }
    xPopup.totalLine++;
}



