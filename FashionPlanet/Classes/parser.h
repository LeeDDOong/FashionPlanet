#ifndef IMGPARSER_
#define IMGPARSER_


extern int dataVer;

extern char bufData[15240000];
extern long bufDataSize;


void loadData(const char* strFileName,M_Boolean isSdCard);
void loadExcelParser(const char* strFileName,M_Boolean isSdCard);
int getByteToIntPar(unsigned char data[], int idx);

typedef struct 
{
	int imgNum;
	int imgX;
	int imgY;
	int imgW;
	int imgH;
	int drawX;
	int drawY;
	int imgRot;
	int imgScale;
	M_Boolean isReverse;
} XSPRITLAYER;

typedef struct 
{
	int delay;
	int snd;
	int totalLayer;
	XSPRITLAYER xLayer[20];
} XSPRITFRAME;

#define SPRIT_IMGLAYERMAX	16
#define SPRIT_IMGLAYER_BACKLAYER	16		//백레이어
extern int sortSlot[2][20];

typedef struct 
{
	XIMG *img[64][20];
	XIMG *imgLayer[40][2];
	int totalImg;
	int endAction;
	int totalFrame;
	XSPRITFRAME xFrame[200];
	///////////////운영부분/////////////////
	int nowFrame;
	int nowDelay;
	
	int buyItemCode;
	
	M_Boolean isHighHeeled;
	
	int hairResize;
	int hairResizeY;
	
	
	/////////////추가이미지부분////////////
	M_Boolean isGuitar;
	M_Boolean isPhone_Left;
	M_Boolean isPhone_Right;
	M_Boolean isMike;
	
	M_Boolean isCleaning;
	M_Boolean isPorterMan_LEFT;
	M_Boolean isPorterMan_RIGHT;
	
	M_Boolean isChairBook;
	M_Boolean isChairCoffee;
	M_Boolean isFitting;
	M_Boolean isIpad;
	
	M_Boolean isPen;
	M_Boolean isNote;
	
	
} XSPRIT;

//////////////얼굴/////////////////////
#define FACELAYER		7
typedef struct
{
	int faceNum;
	int faceType;
	int faceAnyCnt;
	int hairNum;
} XFACE;


//////////////말풍선관리/////////////////////
#define SPEAKFRAMEMAX			40

#define SPEAK_STATE_DONT		0
#define SPEAK_STATE_PLAY		1
typedef struct
{
	int state;
	int anyCnt;
	int anyCntMax;
	char strText[128];
} XSPEAK;



//////////////////////////////////캐릭터액팅///////////////////////
#define SPRITNPCMAX		128
#define ACT_FRONT		0
#define ACT_BACK		1


//앞쪽 고정은 20이후로
#define NPC_ACT_FRONTNUM		40
#define NPC_ACT_BACKNUM			80

#define NPC_ACT_WALKING				0
#define NPC_ACT_WALKINGBAG			1
#define NPC_ACT_PORTER_FITTING		2	
#define NPC_ACT_POSE1				3
#define NPC_ACT_POSE2				4
#define NPC_ACT_GOMIN				5
#define NPC_ACT_GREETING			6
#define NPC_ACT_TALKING				7
#define NPC_ACT_LOOKINGAROUND		8
#define NPC_ACT_STOP				9
#define NPC_ACT_ANGRY				12
#define NPC_ACT_PORTER_MAN_YES		13	
#define NPC_ACT_PORTER_MAN_TIRED	14
#define NPC_ACT_PORTER_MAN_APPLAUD	15
#define NPC_ACT_APPLAUD				16
#define NPC_ACT_WATCH				17
#define NPC_ACT_WORLDMAPPHONE		18
#define NPC_ACT_PORTER_ANGRY		19	
#define NPC_ACT_PORTER_MAN_WALKING	20



#define NPC_ACT_RUNWAY_CHAIR_STOP		21	//패션쇼앉아대기
#define NPC_ACT_RUNWAY_CHAIR_APPLAUD	22	//패션쇼앉아박수
#define NPC_ACT_RUNWAY_CHAIR_ACTION0	23	//패션쇼앉아메모
#define NPC_ACT_RUNWAY_CHAIR_ACTION1	24	//패션쇼앉아아이패드
#define NPC_ACT_RUNWAY_CHAIR_ACTION2	25	//패션쇼앉아휴패폰

#define NPC_ACT_PORTER_MM_MAN_YES		26
#define NPC_ACT_PORTER_MM_MAN_TIRED		27
#define NPC_ACT_PORTER_WW_MAN_YES		28
#define NPC_ACT_PORTER_WW_MAN_TIRED		29


#define NPC_ACT_SMILE			40
#define NPC_ACT_PAYMENT			41
#define NPC_ACT_ASSISTANTCALL	42
#define NPC_ACT_CROSSARMS		43
#define NPC_ACT_WAVINGHAND		44
#define NPC_ACT_GUITAR			45
#define NPC_ACT_SONG			46
#define NPC_ACT_DANCE			47
#define NPC_ACT_PHONE			48
#define NPC_ACT_FASHIONCHECK	49
#define NPC_ACT_POWERMAN		50
#define NPC_ACT_TOUCH0_MAN		51
#define NPC_ACT_TOUCH1_MAN		52
#define NPC_ACT_TOUCH0_WOMAN	53
#define NPC_ACT_TOUCH1_WOMAN	54
#define NPC_ACT_CHAIR_SIT		55
#define NPC_ACT_CHAIR_BOOK		56
#define NPC_ACT_CHAIR_COFFEE	57
#define NPC_ACT_CHAIR_IPAD		58
#define NPC_ACT_CHAIR_STANDUP	59
#define NPC_ACT_CHAIR_EVENT		60
#define NPC_ACT_CHAIR_PHONE		61



#define NPC_ACT_SELECT			80
#define NPC_ACT_NPC1			81
#define NPC_ACT_NPC2			82
#define NPC_ACT_ORDERING		83
#define NPC_ACT_CLEAN			84
#define NPC_ACT_POSE3			85


#define NPC_ACT_PORTER_MM_W_FITTING	86
#define NPC_ACT_PORTER_MM_W_ANGRY	87


#define NPC_ACT_PORTER_WW_W_FITTING	88
#define NPC_ACT_PORTER_WW_W_ANGRY	89
#define NPC_ACT_FITTINGROOM	NPC_ACT_PORTER_WW_W_ANGRY + 1

extern XSPRIT xSpritNpc[SPRITNPCMAX][2];		//[액팅번호][앞뒤구분]
extern XSPRIT xSpritDrawSub;
extern XSPRIT xSpritShowWindow[2];
extern char strFileNameTemp[64];
///////////////////////////////////////////////////////////////


/////////////////////////////////////엑셀파싱///////////////////////////////
#define EXCEL_PS_INTERIOR_DATA			0
#define EXCEL_PS_INTERIOR_DATA_FILE		"interior_data.dat"

#define EXCEL_PS_INTERIOR_LIST			1
#define EXCEL_PS_INTERIOR_LIST_FILE		"interior_list.dat"

#define EXCEL_PS_THEME					2
#define EXCEL_PS_THEME_FILE				"interior_theme.dat"

#define EXCEL_PS_DRESS_DATA				3
#define EXCEL_PS_DRESS_DATA_FILE		"dress_data.dat"

#define EXCEL_PS_DRESS_LIST				4
#define EXCEL_PS_DRESS_LIST_FILE		"dress_list.dat"

#define EXCEL_PS_STAFF_DATA				5
#define EXCEL_PS_STAFF_DATA_FILE		"staff_data.dat"

#define EXCEL_PS_STAFF_LIST				6
#define EXCEL_PS_STAFF_LIST_FILE		"staff_list.dat"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Level Data KBY
#define EXCEL_PS_LVTABLE				7
#define EXCEL_PS_LVTABLE_FILE			"level.dat"

//#define EXCEL_PS_LVTABLE				7
//#define EXCEL_PS_LVTABLE_FILE			"LevelTable.dat"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define EXCEL_PS_RESDOWN				8
#define EXCEL_PS_RESDOWN_FILE			"resdownload.dat"

#define EXCEL_PS_MINIGAME				9
#define EXCEL_PS_MINIGAME_FILE			"minigame.dat"

#define EXCEL_PS_NPCSET					10
#define EXCEL_PS_NPCSET_FILE			"npcset.dat"
#define EXCEL_PS_CAR					11
#define EXCEL_PS_CAR_FILE				"car.dat"
#define EXCEL_PS_CARSLOT				12
#define EXCEL_PS_CARSLOT_FILE			"carc.dat"
#define EXCEL_PS_QUESTMAIN				13
#define EXCEL_PS_QUESTMAIN_FILE			"main.dat"
#define EXCEL_PS_QUESTNORMAL			14
#define EXCEL_PS_QUESTNORMAL_FILE		"normal.dat"
#define EXCEL_PS_MODEL					15
#define EXCEL_PS_MODEL_FILE				"model.dat"
#define EXCEL_PS_SONG					16
#define EXCEL_PS_SONG_FILE				"world.dat"

#define EXCEL_PS_WOBD					17
#define EXCEL_PS_WOBD_FILE				"w.obd"

#define EXCEL_PS_BALANCE				18
#define EXCEL_PS_BALANCE_FILE			"balance.dat"

#define EXCEL_PS_DRESSCOLOR				19
#define EXCEL_PS_DRESSCOLOR_FILE		"dress_color.dat"

#define EXCEL_PS_DRESSCONCEPT			20
#define EXCEL_PS_DRESSCONCEPT_FILE		"dress_concept.dat"

#define EXCEL_PS_FASHIONSHOW			21
#define EXCEL_PS_FASHIONSHOW_FILE		"fashionshow.dat"

#define EXCEL_PS_DRESSSECTION			22
#define EXCEL_PS_DRESSSECTION_FILE		"dress_section.dat"

#define EXCEL_PS_ACCESSBONUS			23
#define EXCEL_PS_ACCESSBONUS_FILE		"dailybonus.dat"

#define EXCEL_PS_EXPANDDATA			24
#define EXCEL_PS_EXPANDDATA_FILE		"expand_data.dat"

#define EXCEL_PS_EXPANDLIST			25
#define EXCEL_PS_EXPANDLIST_FILE		"expand_list.dat"


#define EXCEL_PS_DRESS_IMG				26
#define EXCEL_PS_DRESS_IMG_FILE		"dress_image.dat"

#define EXCEL_PS_HACK				27
#define EXCEL_PS_HACK_FILE		"hack_tool.dat"


#define EXCEL_PS_GOODSLIST				28
#define EXCEL_PS_GOODSLIST_FILE		"goods_list.dat"

#define EXCEL_PS_SPECIALSALE				29
#define EXCEL_PS_SPECIALSALE_FILE		"special_sale.dat"

#define EXCEL_PS_MODELCASTING				30
#define EXCEL_PS_MODELCASTING_FILE		"model_casting.dat"


#define EXCEL_PS_STYLEBOOK				31
#define EXCEL_PS_STYLEBOOK_FILE		"stylebook_model.dat"



#define EXCEL_PS_MILEAGE				32
#define EXCEL_PS_MILEAGE_FILE		"mileage.dat"




#define EXCEL_PS_STYLEDRESS				33
#define EXCEL_PS_STYLEDRESS_FILE		"stylebook_dress.dat"


#define EXCEL_PS_PACKAGE				34
#define EXCEL_PS_PACKAGE_FILE		"Product.dat"



#define EXCEL_PS_EVENTQUEST				35
#define EXCEL_PS_EVENTQUEST_FILE		"EventQuest.dat"


#define EXCEL_PS_EVENTTYPE				36
#define EXCEL_PS_EVENTTYPE_FILE		"EventType.dat"



#define EXCEL_PS_HOTDEAL				37
#define EXCEL_PS_HOTDEAL_FILE		"HotDealProduct.dat"



#define EXCEL_PS_RIVAL				38
#define EXCEL_PS_RIVAL_FILE		"RivalStage.dat"


#define EXCEL_PS_COLLECTION				39
#define EXCEL_PS_COLLECTION_FILE		"Collection.dat"

#define EXCEL_PS_JEWEL				40
#define EXCEL_PS_JEWEL_FILE		"Jewel.dat"

#define EXCEL_PS_AMULET				41
#define EXCEL_PS_AMULET_FILE		"Amulet.dat"


#define EXCEL_PS_AMULETXY				42
#define EXCEL_PS_AMULETXY_FILE		"Amulet_XY.dat"

#define EXCEL_PS_CLUB                   43
#define EXCEL_PS_CLUB_FILE              "Club.dat"

#define EXCEL_PS_CLUBICON				44
#define EXCEL_PS_CLUBICON_FILE          "ClubIcon.dat"



#define EXCEL_PS_FASHIONWEEKMAKEUP				45
#define EXCEL_PS_FASHIONWEEKMAKEUP_FILE          "FashionWeek_Makeup.dat"

#define EXCEL_PS_FASHIONWEEKDRESS				46
#define EXCEL_PS_FASHIONWEEKDRESS_FILE          "FashionWeek_Dress.dat"

#define EXCEL_PS_CLUBSTORE                      47
#define EXCEL_PS_CLUBSTORE_FILE                 "Club_store.dat"


#define EXCEL_PS_BROOCHSHOP                     48
#define EXCEL_PS_BROOCHSHOP_FILE                "b_shop.dat"

#define EXCEL_PS_R_STYLEBOOK                    49
#define EXCEL_PS_R_STYLEBOOK_FILE               "R_stylebook_model.dat"

#define EXCEL_PS_R_UPGRADE                      50
#define EXCEL_PS_R_UPGRADE_FILE                 "R_Upgrade.dat"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////패션플래닛 추가 Data KBY
#define EXCEL_PS_PDRESS_DATA                    EXCEL_PS_R_UPGRADE+1
#define EXCEL_PS_PDRESS_DATA_FILE               "pdress_data.dat"

#define EXCEL_PS_PDRESS_LIST                    EXCEL_PS_PDRESS_DATA+1
#define EXCEL_PS_PDRESS_LIST_FILE               "pdress_list.dat"

#define EXCEL_PS_CLOTHES_DATA                   EXCEL_PS_PDRESS_LIST+1
#define EXCEL_PS_CLOTHES_DATA_FILE              "Clothes_Data.dat"

#define EXCEL_PS_HAIRMAKEUP_DATA                EXCEL_PS_CLOTHES_DATA+1
#define EXCEL_PS_HAIRMAKEUP_DATA_FILE           "HairMakeup.dat"

#define EXCEL_PS_LAYERTYPE_DATA                 EXCEL_PS_HAIRMAKEUP_DATA+1
#define EXCEL_PS_LAYERTYPE_DATA_FILE            "LayerType.dat"

#define EXCEL_PS_MATERIAL_DATA                  EXCEL_PS_LAYERTYPE_DATA+1
#define EXCEL_PS_MATERIAL_DATA_FILE             "Material.dat"

#define EXCEL_PS_VARIABLE                       EXCEL_PS_MATERIAL_DATA+1
#define EXCEL_PS_VARIABLE_FILE                  "Variable.dat"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int prcSprit(XSPRIT *Xsprit ,int *nowDelay,int *nowFrame);
void initSprit(XSPRIT *Xsprit);
void loadSpriteData(const char* strFileName,XSPRIT* Xsprit);
void drawSprit(XSPRIT *Xsprit,int x,int y,int pos,XFACE *xFace);
void reverseSprit(XSPRIT *Xsprit,int x,int y,int pos,XFACE *xFace);
void loadExcelParserByte(int type);
void drawSpritcharacter(XIMG* img, float x, float y, float imgX, float imgY, float imgW, float imgH, int ank, float fGameScale);
int getExcelTypeNum(const char* strFileName);

////////////////////////////////////////////////////////////////////////////
//LJW 추가
void drawSprit_FP(XSPRIT *Xsprit,int x,int y,int pos,XFACE *xFace);
void reverseSprit_FP(XSPRIT *Xsprit,int x,int y,int pos,XFACE *xFace);
void drawSpritBig_FP(XSPRIT *Xsprit,int x,int y,int pos,XFACE *xFace);
void reverseSpritBig_FP(XSPRIT *Xsprit,int x,int y,int pos,XFACE *xFace);

void delSprit_FP(XSPRIT *xSprit);
int prcSpritBig_FP(XSPRIT *Xsprit ,int *nowDelay,int *nowFrame);
////////////////////////////////////////////////////////////////////////////

#endif



