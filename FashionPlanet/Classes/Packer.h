#ifndef IMGPACKER_
#define IMGPACKER_


#define imgW(a)	xPacker[a/1000].w[a%1000]
#define imgH(a)	xPacker[a/1000].h[a%1000]

#define PACKERMAX	18

#define PACKERDATAMAX	250
typedef struct
{
	XIMG img;
		
	int x[PACKERDATAMAX];
	int y[PACKERDATAMAX];
	int w[PACKERDATAMAX];
	int h[PACKERDATAMAX];
	
} XPACKER;
extern XPACKER xPacker[PACKERMAX];
//////////////////////////////////////////
#define PACKER_STATE_MAINMENU		0

#define IMG_IdMakeBg		0
#define IMG_MainMenu0		1
#define IMG_MainMenu1		2
#define IMG_MainMenu2		3
#define IMG_MainMenu3		4
#define IMG_MainMenu4		5
#define IMG_MainMenu5		6
#define IMG_MainMenu6		7
#define IMG_MainMenu7		8
#define IMG_MainMenu8		9
#define IMG_MainMenu9		10
#define IMG_MainMenu10		11
#define IMG_MainMenu11		12
#define IMG_MainMenuBg		13
//////////////////////////////////////////
#define PACKER_STATE_PRODUCTION		1
enum
{
imgNewModelInfo0 = 1000,
imgProductionFastBtn,
imgProductionMenuBg,
imgProductionMenuBtn0,
imgProductionMenuBtn1,
imgProductionMenuBtn2,
imgProductionMenuBtn3,
imgProductionMenuBtn4,
imgProductionMenuBtn5,
imgProductionMenuGage,
imgProductionMenuListTab,
imgProductionMenuLock0,
imgProductionMenuLock1,
imgProductionMenuLock2,
imgProductionMenuObj0,
imgProductionMenuObj1,
imgProductionMenuObj2,
imgProductionMenuObj3,
imgProductionMenuObj4,
imgProductionMenuObj5,
imgProductionMenuObj6,
imgProductionMenuObj7,
imgProductionMenuObj8,
imgProductionMenuObj9,
imgProductionMenuObj10,
imgProductionMenuObj11,
imgProductionMenuObj12,
imgProductionMenuObj13,
imgProductionSlotSaleIcon
};

//////////////////////////////////////////
#define PACKER_STATE_SELL			2
enum
{
imgProductionMenuSlot0 = 2000,
imgProductionMenuSlot1,
imgProductionMenuSlot2,
imgProductionMenuSlot3,
imgProductionMenuSlot4,
imgProductionMenuSlot5,
imgProductionMenuSlot6,
imgProductionMenuSlot7,
imgProductionMenuSlot8,
imgSellBg0,
imgSellBg1,
imgSellBg2,
imgSellBg3,
imgSellBg4,
imgSellBg5,
imgSellBg6,
imgSellBg7,
imgSellBg8,
imgSellBg9,
imgSellScroll,
imgSellSelectBg,
imgSellSelectSlot,
imgStorageTitle
};


//////////////////////////////////////////
#define PACKER_STATE_FRIENDLIST			3
#define imgAddFriendBg					3000
#define imgAddFriendBtn					3001
#define imgAddFriendSlot				3002
#define imgAddFriendTab0				3003
#define imgAddFriendTab2				3004
#define imgAddFriendTextBox				3005
#define imgAddKakao0					3006
#define imgAddKakao1					3007
#define imgAddKakao2					3008
#define imgAddKakao3					3009
#define imgAddKakao4					3010
#define imgFriendAdd0					3011
#define imgFriendAdd1					3012
#define imgFriendAdd2					3013
#define imgFriendBg						3014
#define imgFriendEditBtn				3015
#define imgFriendInfoIcon0				3016
#define imgFriendInfoIcon1				3017
#define imgFriendInfoIcon2				3018
#define imgFriendKakaoIcon				3019
#define imgFriendRandomBtn				3020
#define imgFriendSlot0					3021
#define imgFriendSlot1					3022
#define imgFriendSlot2					3023
#define imgFriendTab					3024
#define imgFriendTabIcon0				3025
#define imgFriendTabIcon1				3026
#define imgFriendTabIcon2				3027
#define imgFriendVisitIcon				3028



//////////////////////////////////////////
#define PACKER_STATE_MINIGAME			4
#define imgMiniGameBg					4000
#define imgMiniGameBtn					4001
#define imgMiniGameObj0					4002
#define imgMiniGameObj1					4003
#define imgMiniGameObj2					4004
#define imgMiniGameObj3					4005
#define imgMiniGameObj4					4006
#define imgMiniGameObj5					4007
#define imgMiniGameObj6					4008
#define imgMiniGameObj7					4009

//////////////////////////////////////////
#define PACKER_STATE_OPTION				5
#define imgOptionBar0					5000
#define imgOptionBar1					5001
#define imgOptionBg						5002
#define imgOptionOnOff					5003
#define imgOptionSubBg0					5004
#define imgOptionSubBg1					5005
#define imgOptionTab					5006
#define imgOptionTabIcon				5007
#define imgOptionV						5008
//////////////////////////////////////////
#define PACKER_STATE_MODEL				6
#define imgModelBg0						6000
#define imgModelBg1						6001
#define imgModelCastingBtn0				6002
#define imgModelCastingBtn1				6003
#define imgModelCastingBtn2				6004
#define imgModelCastingBtn4				6005
#define imgModelCastingBtn5				6006
#define imgModelCastingBtn6				6007
#define imgModelEditBtn					6008
#define imgModelFriendBg0				6009
#define imgModelFriendBg1				6010
#define imgModelFriendBg2				6011
#define imgModelFriendBg3				6012
#define imgModelFriendBg4				6013
#define imgModelFriendBg6				6014
#define imgModelFriendBtn0				6015
#define imgModelGuestSlot				6016
#define imgModelMainInfo0				6017
#define imgModelMainInfo1				6018
#define imgModelMainInfo2				6019
#define imgModelMainInfo3				6020
#define imgModelMainInfo4				6021
#define imgModelListBtn					6022
#define imgModelMainBg0					6023
#define imgModelMainBg1					6024
#define imgModelMainBg2					6025
#define imgModelMainBg3					6026
#define imgModelMainBg4					6027
#define imgModelMainEmpty				6028
#define imgModelMainGage0				6029
#define imgModelMainGage1				6030
#define imgModelMainGage2				6031
#define imgModelUpGradeBg				6032
#define imgModelUpGradeSlot0			6033
#define imgModelUpGradeSlot1			6034
#define imgModelUpGradeSlot2			6035
#define imgUpGrageBtn					6036
//////////////////////////////////////////
#define PACKER_STATE_MAIL				7
#define imgGiftShopBg					7000
#define imgGiftShopSlotBg				7001
#define imgMailBg0						7002
#define imgMailBg1						7003
#define imgMailBtn0						7004
#define imgMailGiftBtn					7005
#define imgMailGiftIcon					7006
#define imgMailSlotBg0					7007
#define imgMailSlotBg1					7008
#define imgMailTab2						7009
#define imgMailTextBox					7010
#define imgMiniProFileBg				7011
#define imgSecret0						7012
#define imgSecret1						7013
//////////////////////////////////////////
#define PACKER_STATE_INTERIOR			8
#define imgBuildFrame0					8000
#define imgBuildFrame1					8001
#define imgBuildIconAll					8002
#define imgBuildIconClr					8003
#define imgBuildIconExit				8004
#define imgBuildIconInven				8005
#define imgBuildIconMove				8006
#define imgBuildIconOk					8007
#define imgBuildIconRot					8008
#define imgBuildIconShop				8009
#define imgBuildMode0					8010
#define imgBuildMode1					8011
#define imgBuildTileErr0				8012
#define imgBuildTileErr1				8013
#define imgBuildTileOk0					8014
#define imgBuildTileOk1					8015
#define imgExtensionFloorIcon			8016
#define imgExtensionTileIcon			8017
#define imgInteriorSelectSlot0			8018
#define imgInteriorSelectSlot1			8019
#define imginteriorShopBg				8020
#define imgInteriorTabB0				8021
#define imgInteriorTeamBg				8022
//////////////////////////////////////////
#define PACKER_STATE_FASHIONSHOW		9
enum
{
imgColorIcon0 = 9000,
imgColorIcon1,
imgColorIcon2,
imgColorIcon3,
imgColorIcon4,
imgColorIcon5,
imgColorIcon6,
imgColorIcon7,
imgColorIcon8,
imgColorIcon9,
imgColorIcon10,
imgColorIcon11,
imgConceptionIcon,
imgDressCodeBg,
imgDressCodeIcon0,
imgDressCodeIcon1,
imgDressCodeInOut,
imgDressCodeLayered0,
imgDressCodeLayered1,
imgDressCodeLayered2,
imgDressCodeLayered3,
imgDressCodeSex,
imgDressCodeSlot,
imgFashionShowFree,
imgFsBackBtn,
imgFsBg,
imgFsBtn0,
imgFsBtn1,
imgFsBtn2,
imgFsBtn3,
imgFsInfo0,
imgFsModelSlot0,
imgFsModelSlot1,
imgFsNoticeBg0,
imgFsNoticeBg1,
imgFsNoticeBg2,
imgFsObj0,
imgFsObj1,
imgFsObj2,
imgFsObj3,
imgFsObj4,
imgFsRankBg,
imgFsRankBtn0,
imgFsRankBtn1,
imgFsRankNum,
imgFsRankSlot0,
imgFsRankSlot1,
imgFsRankSlot2,
imgFsRankSlot3,
imgFsRankSlot4,
imgFsRankTab,
imgFsRankTabIcon0,
imgFsRankTabIcon1,
imgFsRankTabIcon2,
imgFsSelectInfo,
imgRankChange0,
imgRankChange1,
imgRankChange2,
};
//////////////////////////////////////////
#define PACKER_STATE_RUNWAY				10
enum
{
imgFashionShowEff0 = 10000,
imgFashionShowEff1,
imgFashionShowEff2,
imgFashionShowEff3,
imgFashionShowEff4,
imgFashionShowEff5,
imgFashionShowEff6,
imgOrderBg,
imgOrderNum0,
imgOrderNum1,
imgRunWayBg0,
imgRunWayBg3,
imgRunWayBg4,
imgRunWayBg5,
imgRunWayBg6,
imgRunWayResultBg0,
imgRunWayResultBg1,
imgRunWayResultBg2,
imgRunWayResultBonus0,
imgRunWayResultBonus1,
imgRunWaySkipBtn
};
//////////////////////////////////////////
#define PACKER_STATE_TREND				11
#define imgTrendArrow					11000
#define imgTrendBg						11001
#define imgTrendLv0						11002
#define imgTrendLv1						11003
#define imgTrendSlot0					11004
#define imgTrendSlot1					11005
#define imgTrendSlot2					11006
#define imgTrendTitle					11007
//////////////////////////////////////////
#define PACKER_STATE_CARSTORAGE			12
#define imgCarStorageBg					12000
#define imgCarStorageSlot0				12001
#define imgCarStorageSlot1				12002
#define imgCarStorageSlotInfo			12003
#define imgCarStorageTabB				12004
#define imgCarStorageTabIcon			12005
//////////////////////////////////////////
#define PACKER_STATE_WORLDMAP			13
enum
{
imgActObj0 = 13000,
imgActObj1,
imgActObj2,
imgActObj3,
imgActObj4,
imgActObj5,
imgActObj6,
imgActObj7,
imgActObj8,
imgActObj9,
imgActObj10,
imgActObj11,
imgActObj12,
imgActObj13,
imgActObj14,
imgActObj15,
imgAddSlot,
imgAstarErrIcon,
imgBlinkEff0,
imgBlinkEff1,
imgBonus0,
imgBonus1,
imgBookIcon,
imgBtn0,
imgBtn1,
imgBtn2,
imgBuildIconBg,
imgCandyIcon,
imgCarOrderFailIcon,
imgCarOrderIcon,
imgCarParkIng,
imgCarParkLv,
imgCarProductionFailIcon,
imgCarProductionIcon,
imgCarProductionOkIcon,
imgCatalogSex,
imgCoffeeIcon,
imgColorPaper,
imgCompletionIcon,
imgEff0,
imgEff1,
imgEff2,
imgEff3,
imgEmoticon,
imgEmptyIcon,
imgEmptyIconModel,
imgEmptySlot0,
imgEmptySlot1,
imgExtensiontile,
imgExternalInfo,
imgFire0,
imgFire1,
imgFire2,
imgFire3,
imgFire4,
imgFire5,
imgFire6,
imgFire7,
imgFire8,
imgFire9,
imgFriendDelBtn,
imgFriendMapAddBtn,
imgFriendMapBackBtn,
imgFriendMapIcon,
imgFriendMapInfo0,
imgFriendMapInfo1,
imgFriendMapNextBtn,
imgFriendMapRandomBtn,
imgGiftIcon,
imgGiftShopPage,
imgGlitterEff,
imgHelpIcon,
imgHelpInfoBar0,
imgHelpInfoBar1,
imgHiPing0,
imgHiPing1,
imgHiPing2,
imgIconGage,
imgIcon,
imgInfoBar0,
imgInfoBar1,
imgInfoBar2,
imgInfoBar3,
imgInfoBar4,
imgInfoBar5,
imgInfoBar6,
imgIngIcon,
imgInShopPerIcon0,
imgInShopPerIcon1,
imgInShopPerIcon2,
imgInShopPerIcon3,
imgInteriorGage,
imgIpadIcon,
imgLinkInfoIcon,
imgLoadingIcon0,
imgMailIcon,
imgMailSex,
imgMenu8,
imgMenu10,
imgMenu11,
imgMenu12,
imgMenu13,
imgModelMainOkIcon0,
imgModelMainOkIcon1,
imgModelMainOkIcon2,
imgModelMainOkIcon3,
imgNpcName,
imgNpcSpeakBox,
imgPaymentIcon,
imgPhoneIcon,
imgPhotoBg,
imgPopup2,
imgPopupBg,
imgPopupBtn0,
imgPopupBtn1,
imgPopupBtn2,
imgPopupBtn3,
imgPopupBtn4,
imgPopupBtn5,
imgPopupBtnB0,
imgPopupBtnB1,
imgPopupBtnB2,
imgPopupBtnS0,
imgPopupBtnS1,
imgPopupBtnS2,
imgProductionArrow,
imgProductionClrBtn,
imgProductionIcon,
imgProductionInfoIcon,
imgProfile0,
imgProfile3,
imgQuestBar,
imgQuestBtn0,
imgQuestBtn1,
imgQuestGiftIcon,
imgQuestInfo,
imgQuestMainIcon,
imgQuestResult0,
imgQuestResult1,
imgQuestResult2,
imgQuestV,
imgSaleIcon,
imgShoppingBag0,
imgShoppingBag1,
imgShowwindowIcon,
imgSlotEvent,
imgSocialIcon,
imgSongIcon,
imgSwitchWorldMapUi0,
imgSwitchWorldMapUi1,
imgSwitchWorldMapUi2,
imgSwitchWorldMapUi3,
imgSwitchWorldMapUi4,
imgTileFrame0,
imgTileFrame1,
imgTire,
imgTrendBonusIcon0,
imgTrendBonusIcon1,
imgTrendBonusIcon2,
imgTrendBonusIcon3,
imgTrendEff0,
imgTrendEff1,
imgTrendEff2,
imgTrendInfoIcon,
imgTrendInfoSlot,
imgTrendNpcIcon,
imgTrendText,
imgTutoInfo0,
imgTutoInfo1,
imgTutoInfo2,
imgTutoInfo3,
imgTutoInfo4,
imgTutoInfo5,
imgTutoInfo6,
imgTutoInfo7,
imgUserPhoto0,
imgUserPhoto1,
imgWaste0,
imgWaste1,
imgWaste2,
imgWorldMapCar00,
imgWorldMapCar01,
imgWorldMapCar10,
imgWorldMapCar11,
imgWorldMapCarShadow,
imgWorldMapCash0,
imgWorldMapCash1,
imgWorldMapCash2,
imgWorldMapCash3,
imgWorldMapFsInof,
imgWorldMapLv0,
imgWorldMapLv1,
imgWorldMapLv2,
imgWorldMapLv3,
imgWorldMapLv4,
imgWorldMapLv5,
imgWorldMapLv6,
imgWorldMapLv7,
imgWorldMapLv8,
imgWorldMapMailIcon0,
imgWorldMapObj0,
imgWorldMapObj1,
imgWorldMapObj2,
imgWorldMapObj3,
imgWorldMapObj4,
imgWorldMapOrderIcon0,
imgWorldMapOrderIcon1,
imgWorldMapOrderIcon2,
imgWorldMapRunWay,
imgWorldMapTrendIcon0,
imgWorldMapTrendIcon1
};
//////////////////////////////////////////
#define PACKER_STATE_WORLDMAP2			14
enum
{
imgBonusNum = 14000,
imgCarBox0,
imgCarBox1,
imgCashGiftIcon,
imgCashShop0,
imgDialogBg0,
imgDialogBg1,
imgDialogBg2,
imgDialogBg3,
imgDialogSkipBtn,
imgFittingMenu0,
imgFittingMenu1,
imgFittingMenu2,
imgFittingMenu3,
imgFittingMenu4,
imgFittingMenu5,
imgFittingSelectSlot,
imgFittingTabB,
imgIapIng,
imgKakaoHelpBtn,
imgKakaoIcon,
imgLoadingGage0,
imgLoadingGage1,
imgLoadingGage2,
imgLoadingGage3,
imgLock2,
imgModelLv,
imgModelMainGift0,
imgModelSlot1,
imgModelSlot2,
imgModelSlot3,
imgNewModel0,
imgNewModel1,
imgNewModel2,
imgNewModel3,
imgNewModel4,
imgNewModel5,
imgNewModel6,
imgNewModel7,
imgNewModelRank0,
imgNewModelRank1,
imgNewModelRank2,
imgNewModelRank3,
imgOrderNumBox,
imgOrderObj0,
imgOrderObj1,
imgOrderObj2,
imgOrderObj3,
imgOrderSlot0,
imgOrderSlot1,
imgOrderSlot2,
imgOrderSlot3,
imgOrderSlot4,
imgOrderSlot5,
imgOrderTitle,
imgQuestArrow,
imgQuestBg,
imgQuestInfoArrow,
imgSlotBonus0,
imgSlotSale0,
imgSlotSale1,
imgSlotSale2,
imgSlotSale3,
imgStaffEditBtn,
imgStamp0,
imgStamp1,
imgStamp2,
imgTextHave,
imgTextQuest,
imgUW0,
imgUW1,
imgUW2,
imgWorldMapCashNum,
imgWorldMapModelSkillIcon,
imgWorldMapModelSkillInfoBox,
imgWorldMapNotice0,
imgWorldMapNotice1,
imgWorldMapNotice2,
imgWorldMapNotice3,
imgWorldMapNoticeNum,
imgWorldMapNum0,
imgWorldMapNum1,
imgWorldMapNum2,
imgWorldMapNum3,
imgWorldMapNum4,
imgWorldMapSub5,
imgWorldMapTired2
	
};
#define PACKER_STATE_MODEL2			15
enum
{
	imgModelHelp0 = 15000,
imgModelHelp1,
imgModelHelp2,
imgModelHelp3,
imgModelHelp4,
imgModelHelp5,
imgModelHelpCandyIcon0,
imgModelHelpExpIcon0,
imgModelHelpExpIcon1,
imgModelHelpExpIcon2,
imgModelHelpGoldIcon0,
imgModelHelpGoldIcon1,
imgModelHelpGoldIcon2,
imgModelHelpLookIcon0,
imgModelHelpLookIcon1,
imgModelMainSlotLv0,
imgModelUpGrade0,
imgModelUpGrade1
};


#define PACKER_STATE_COLLECTION			16
enum
{
imgCollectionBg = 16000,
imgCollectionBody0,
imgCollectionBody1,
imgCollectionIcon,
imgCollectionInfo0,
imgCollectionSelect,
imgCollectionSlot0,
imgCollectionSlot1,
imgCollectionSlot2,
imgCollectionSlot3,
imgCollectionSlot4,
imgCollectionTab,
imgCollectionTabBar,
imgCollectionColorIcon0,
imgCollectionColorIcon1,
imgCollectionColorIcon2,
imgCollectionColorIcon3,
imgCollectionColorIcon4,
imgCollectionColorIcon5,
imgCollectionColorIcon6,
imgCollectionColorIcon7,
imgCollectionColorIcon8,
imgCollectionColorIcon9,
imgCollectionColorIcon10,
imgCollectionColorIcon11,
imgCollectionConceptionIcon,
imgSkillInfoBox
};

#define PACKER_STATE_SKILL			17
enum
{
	imgSkillIcon0 = 17000,
	imgSkillIcon1,
	imgSkillIcon2,
	imgSkillIcon3,
	imgSkillIcon4,
	imgSkillIcon5,
	imgSkillIcon6,
	imgSkillIcon7,
	imgSkillIcon8,
	imgSkillIcon9,
	imgSkillIcon10,
	imgSkillIcon11,
	imgSkillIcon12,
	imgSkillIcon13,
	imgSkillIcon14,
	imgSkillIcon15,
	imgSkillIcon16,
	imgSkillIcon17,
	imgSkillIcon18,
	imgSkillIcon19,
	imgSkillIcon20,
	imgSkillIcon21,
	imgSkillIcon22,
	imgSkillIcon23,
	imgSkillIcon24,
	imgSkillIcon25,
	imgSkillIcon26,
	imgSkillIcon27,
	imgSkillIcon28,
	imgSkillIcon29,
	imgSkillIcon30,
	imgSkillIcon31,
	imgSkillIcon32,
	imgSkillIcon33,
	imgSkillIcon34,
	imgSkillIcon35,
	imgSkillIcon36,
	imgSkillIcon37,
	imgSkillIcon38,
	imgSkillIcon39,
	imgSkillIcon40,
	imgSkillIcon41,
	imgSkillIcon42,
	imgSkillIcon43,
	imgSkillIcon44,
	imgSkillIcon45,
	imgSkillIcon46,
	imgSkillIcon47,
	imgSkillIcon48,
	imgSkillIcon49,
	imgSkillIcon50,
	imgSkillIcon51,
	imgSkillIcon52,
	imgSkillIcon53,
	imgSkillIcon54,
	imgSkillIcon55,
	imgSkillIcon56,
	imgSkillSelect,
	imgSkillSlot,
	imgSkillSlotEmpty,
	imgSkillTextBox
};



void setPacker(int packerNum);
void drawPacker(int packerCode,int x,int y,int rx,int ry,int rw,int rh,int ank);
#endif


