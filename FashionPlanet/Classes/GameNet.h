#ifndef __GAME_NET_H__
#define __GAME_NET_H__




//128상용 앱리뷰버전
//131상용 안드로이드

#define NETFASHIONMAX		7
#define NETFLOORMAX			3


#define CMD_AUTHENTICATION			98
#define CMD_AUTHENTICATION_RECV		99

#define CMD_LOGIN					100
#define CMD_LOGIN_RECV				101

#define CMD_IDMAKE					102
#define CMD_IDMAKE_RECV				103

#define CMD_PHOTOUPLOAD_RECV		105

#define CMD_DELPROFILEPHOTO			106
#define CMD_DELPROFILEPHOTO_RECV	107

#define CMD_GETGAMEDATA				108
#define CMD_GETGAMEDATA_RECV		109

#define CMD_SETGAMEDATA				110
#define CMD_SETGAMEDATA_RECV		111

#define CMD_SETFASHION				112
#define CMD_SETFASHION_RECV			113

#define CMD_GETFASHION				114
#define CMD_GETFASHION_RECV			115

#define CMD_SETINTERIOR				116
#define CMD_SETINTERIOR_RECV		117

#define CMD_GETINTERIOR				118
#define CMD_GETINTERIOR_RECV		119

#define CMD_GETMAP					120
#define CMD_GETMAP_RECV				121

#define CMD_SETMAP					122
#define CMD_SETMAP_RECV				123

#define CMD_SETSHOWWINDOW			124
#define CMD_SETSHOWWINDOW_RECV		125

#define CMD_SETSTAFF				126
#define CMD_SETSTAFF_RECV			127

#define CMD_SETSELLTABLE			128
#define CMD_SETSELLTABLE_RECV		129

#define CMD_GETFACE					130
#define CMD_GETFACE_RECV			131

#define CMD_SETFACE					132
#define CMD_SETFACE_RECV			133


#define CMD_INITGAME				134
#define CMD_INITGAME_RECV			135

#define CMD_GETTREND				136
#define CMD_GETTREND_RECV			137

#define CMD_SETTREND				138
#define CMD_SETTREND_RECV			139

#define CMD_GETORDER				140
#define CMD_GETORDER_RECV			141

#define CMD_SETORDER				142
#define CMD_SETORDER_RECV			143


#define CMD_RECVORDER				144
#define CMD_RECVORDER_RECV			145

#define CMD_DELRECVORDER			146
#define CMD_DELRECVORDER_RECV		147


#define CMD_SETCARPARK				148
#define CMD_SETCARPARK_RECV			149

#define CMD_SETCAR					150
#define CMD_SETCAR_RECV				151


#define CMD_ORDEROK					152
#define CMD_ORDEROK_RECV			153

#define CMD_ADDORDER				154
#define CMD_ADDORDER_RECV			155

#define CMD_SETFLOOR				156
#define CMD_SETFLOOR_RECV			157


#define CMD_GETFRIENDLIST			158
#define CMD_GETFRIENDLIST_RECV		159


#define CMD_GETFRIENDSEARCH			160
#define CMD_GETFRIENDSEARCH_RECV	161

#define CMD_ADDFRIEND				162
#define CMD_ADDFRIEND_RECV			163

#define CMD_DELFRIEND				164
#define CMD_DELFRIEND_RECV			165

#define CMD_FRIENDSOCIAL			166
#define CMD_FRIENDSOCIAL_RECV		167

#define CMD_USERSOCIALLIST			168
#define CMD_USERSOCIALLIST_RECV		169

#define CMD_DELCLEAN				170
#define CMD_DELCLEAN_RECV			171

#define CMD_LVUP					172
#define CMD_LVUP_RECV				173

#define CMD_GETMAILLIST				174
#define CMD_GETMAILLIST_RECV		175


#define CMD_SENDMAIL				176
#define CMD_SENDMAIL_RECV			177

#define CMD_DELMAIL					178
#define CMD_DELMAIL_RECV			179


#define CMD_GETGIFTLIST				180
#define CMD_GETGIFTLIST_RECV		181

#define CMD_SENDGIFT				182
#define CMD_SENDGIFT_RECV			183

#define CMD_DELGIFT					184
#define CMD_DELGIFT_RECV			185


#define CMD_TODAY					186
#define CMD_TODAY_RECV				187

#define CMD_MINIPROFILE				188
#define CMD_MINIPROFILE_RECV		189


#define CMD_SETTILE					190
#define CMD_SETTILE_RECV			191


#define CMD_GETQUEST				192
#define CMD_GETQUEST_RECV			193

#define CMD_SETQUEST				194
#define CMD_SETQUEST_RECV			195


#define CMD_GETMODEL				196
#define CMD_GETMODEL_RECV			197


#define CMD_SETMODEL				198
#define CMD_SETMODEL_RECV			199



#define CMD_SETMODELTOTALSLOT		200
#define CMD_SETMODELTOTALSLOT_RECV	201


#define CMD_SELLTABLEUPDATA			202
#define CMD_SELLTABLEUPDATA_RECV	203


#define CMD_MODELGROUPGIFT			206
#define CMD_MODELGROUPGIFT_RECV		207

#define CMD_GETFASHIONSHOWRANK		208
#define CMD_GETFASHIONSHOWRANK_RECV	209

#define CMD_VOTE					210
#define CMD_VOTE_RECV				211

#define CMD_SETFASHIONSHOW			212
#define CMD_SETFASHIONSHOW_RECV		213


#define CMD_GETFASHIONSHOWRANKINFO				214
#define CMD_GETFASHIONSHOWRANKINFO_RECV			215


#define CMD_GETVOTELIST							216
#define CMD_GETVOTELIST_RECV					217



#define CMD_GETMODELFRIEND						218
#define CMD_GETMODELFRIEND_RECV					219

#define CMD_MODELFRIENDVOTE						220
#define CMD_MODELFRIENDVOTE_RECV				221


#define CMD_UNREGISTERED						224
#define CMD_UNREGISTERED_RECV					225






#define CMD_GETWINMODEL							240
#define CMD_GETWINMODEL_RECV					241

#define CMD_RANDOMFRIEND						242
#define CMD_RANDOMFRIEND_RECV					243

#define CMD_NOTICE								244
#define CMD_NOTICE_RECV							245

#define CMD_GETFRIENDMODEL						246
#define CMD_GETFRIENDMODEL_RECV					247


#define CMD_GETTIME								248
#define CMD_GETTIME_RECV						249



#define CMD_SETSOCIALITEM						252
#define CMD_SETSOCIALITEM_RECV					253


#define CMD_SETACCESS							254
#define CMD_SETACCESS_RECV						255


#define CMD_SETEXTERNALWALL						256
#define CMD_SETEXTERNALWALL_RECV				257

#define CMD_GETMODELMAIN						258
#define CMD_GETMODELMAIN_RECV					259

#define CMD_SETMODELMAIN						260
#define CMD_SETMODELMAIN_RECV					261


#define CMD_SETKAKAOINVITE						262
#define CMD_SETKAKAOINVITE_RECV					263

#define CMD_BILL								264
#define CMD_BILL_RECV							265

#define CMD_ADDFRIENDID							266
#define CMD_ADDFRIENDID_RECV					267

#define CMD_GETSOUND							268
#define CMD_GETSOUND_RECV						269
#define CMD_SETSOUND							270
#define CMD_SETSOUND_RECV						271

#define CMD_SETETC								272
#define CMD_SETETC_RECV							273

#define CMD_GETPMDATA							274
#define CMD_GETPMDATA_RECV						275

#define CMD_BUYGOLD								276
#define CMD_BUYGOLD_RECV						277

#define CMD_GETEVENT							278
#define CMD_GETEVENT_RECV						279

#define CMD_SETCOUPON							280
#define CMD_SETCOUPON_RECV						281

#define CMD_HACKINGCHECK						282
#define CMD_HACKINGCHECK_RECV					283

#define CMD_KAKAOHELP							284
#define CMD_KAKAOHELP_RECV						285

#define CMD_SETPUSH								286
#define CMD_SETPUSH_RECV						287


#define CMD_G9EVENT								288
#define CMD_G9EVENT_RECV						289




#define CMD_MILEAGESHOPCOUNT					1000
#define CMD_MILEAGESHOPCOUNT_RECV				-1000

#define CMD_MILEAGESHOPLIST                     1002
#define CMD_MILEAGESHOPLIST_RECV				-1002

#define CMD_MILEAGESHOPBUY                      1004
#define CMD_MILEAGESHOPBUY_RECV                 -1004

#define CMD_MILEAGESHOPUPDATE                   1006
#define CMD_MILEAGESHOPUPDATE_RECV				-1006

#define CMD_MILEAGESHOPCANCLE                   1008
#define CMD_MILEAGESHOPCANCLE_RECV				-1008




#define CMD_PRODUCTIONSTART                   1010
#define CMD_PRODUCTIONSTART_RECV               -1010


#define CMD_PRODUCTIONCANCLE                   1012
#define CMD_PRODUCTIONCANCLE_RECV				-1012


#define CMD_PRODUCTIONFASTPOP                   1014
#define CMD_PRODUCTIONFASTPOP_RECV				-1014


#define CMD_PRODUCTIONCOMPLETE                   1016
#define CMD_PRODUCTIONCOMPLETE_RECV				-1016


#define CMD_PRODUCTIONOPEN               1018
#define CMD_PRODUCTIONOPEN_RECV			-1018



#define CMD_SELLSTART                    1020
#define CMD_SELLSTART_RECV				-1020

#define CMD_SELLCANCLE                   1022
#define CMD_SELLCANCLE_RECV				-1022

#define CMD_SELLFASTPOP                  1024
#define CMD_SELLFASTPOP_RECV			-1024

#define CMD_SELLCOMPLETE                 1026
#define CMD_SELLCOMPLETE_RECV			-1026



#define CMD_PREPAYBUY                 1027
#define CMD_PREPAYBUY_RECV			-1027

#define CMD_PREPAYDAY                 1028
#define CMD_PREPAYDAY_RECV			-1028

#define CMD_PACKAGEBUY                 1029
#define CMD_PACKAGEBUY_RECV              -1029

#define CMD_PACKAGELIST                 1030
#define CMD_PACKAGELIST_RECV              -1030

#define CMD_EVENTQUESTMAINLIST            1031
#define CMD_EVENTQUESTMAINLIST_RECV      -1031

#define CMD_EVENTQUESTMAINCOMPLETE            1032
#define CMD_EVENTQUESTMAINCOMPLETE_RECV      -1032

#define CMD_EVENTQUESTDETAILLIST            1033
#define CMD_EVENTQUESTDETAILLIST_RECV      -1033

#define CMD_EVENTQUESTDETAILUPDATE            1034
#define CMD_EVENTQUESTDETAILUPDATE_RECV      -1034

#define CMD_EVENTQUESTDETAILCOMPLETE            1035
#define CMD_EVENTQUESTDETAILCOMPLETE_RECV      -1035

#define CMD_HOTDEALMAINLIST                     1036
#define CMD_HOTDEALMAINLIST_RECV                -1036

#define CMD_HOTDEALDETAILLIST                     1037
#define CMD_HOTDEALDETAILLIST_RECV                -1037

#define CMD_HOTDEALMAINOPEN                     1038
#define CMD_HOTDEALMAINOPEN_RECV                -1038

#define CMD_HOTDEALDETAILOPEN                     1039
#define CMD_HOTDEALDETAILOPEN_RECV                -1039

#define CMD_HOTDEALDETAILBUY                     1040
#define CMD_HOTDEALDETAILBUY_RECV                -1040

#define CMD_RIVALLIST                     1041
#define CMD_RIVALLIST_RECV                -1041

#define CMD_RIVALSTART                     1042
#define CMD_RIVALSTART_RECV                -1042

#define CMD_RIVALSTOP                     1043
#define CMD_RIVALSTOP_RECV                -1043

#define CMD_RIVALUPDATE                     1044
#define CMD_RIVALUPDATE_RECV                -1044

#define CMD_RIVALCOMPLETE                     1045
#define CMD_RIVALCOMPLETE_RECV                -1045



#define CMD_SETDEVICEID                     1046
#define CMD_SETDEVICEID_RECV                -1046

#define CMD_BOOKMARK                     1047
#define CMD_BOOKMARK_RECV                -1047



#define CMD_JEWELQUESTLIST                     1048
#define CMD_JEWELQUESTLIST_RECV                -1048

#define CMD_JEWELQUESTUPDATE                     1049
#define CMD_JEWELQUESTUPDATE_RECV                -1049

#define CMD_JEWELQUESTCOMPLETE                     1050
#define CMD_JEWELQUESTCOMPLETE_RECV                -1050

#define CMD_AMULETBUYLIST                     1051
#define CMD_AMULETBUYLIST_RECV                -1051

#define CMD_AMULETBUY                     1052
#define CMD_AMULETBUY_RECV                -1052

#define CMD_AMULETLIST                     1053
#define CMD_AMULETLIST_RECV                -1053

#define CMD_AMULETUPDATE                     1054
#define CMD_AMULETUPDATE_RECV                     -1054



#define CMD_AMULETPAGEBUY                     1055
#define CMD_AMULETPAGEBUY_RECV                     -1055


#define CMD_CLUBLIST                     1056
#define CMD_CLUBLIST_RECV                     -1056
#define CMD_CLUBMAKE                     1057
#define CMD_CLUBMAKE_RECV                     -1057
#define CMD_CLUBJOIN                     1059
#define CMD_CLUBJOIN_RECV                     -1059
#define CMD_CLUBUNREG                     1060
#define CMD_CLUBUNREG_RECV                     -1060
#define CMD_CLUBSEARCH                     1061
#define CMD_CLUBSEARCH_RECV                     -1061



#define CMD_CLUBDATA                     1062
#define CMD_CLUBDATA_RECV                     -1062

#define CMD_CLUBMEMBER                     1063
#define CMD_CLUBMEMBER_RECV                     -1063


#define CMD_SETCLUBJOINTYPE                     1064
#define CMD_SETCLUBJOINTYPE_RECV                     -1064

#define CMD_SETCLUBNOTICE                     1065
#define CMD_SETCLUBNOTICE_RECV                     -1065

#define CMD_SETCLUBJOININFO                     1066
#define CMD_SETCLUBJOININFO_RECV                     -1066

#define CMD_SETCLUBFORCEOUT                     1067
#define CMD_SETCLUBFORCEOUT_RECV                     -1067

#define CMD_SETCLUBMASTER                     1068
#define CMD_SETCLUBMASTER_RECV                     -1068




#define CMD_CLUBJOINLIST                     1070
#define CMD_CLUBJOINLIST_RECV                     -1070

#define CMD_CLUBJOINAPPLY                     1071
#define CMD_CLUBJOINAPPLY_RECV                     -1071


#define CMD_CLUBJOINACCEPT                     1072
#define CMD_CLUBJOINACCEPT_RECV                     -1072

#define CMD_CLUBJOINDEL                     1073
#define CMD_CLUBJOINDEL_RECV                     -1073



#define CMD_CLUBHISTORYLIST                     1074
#define CMD_CLUBHISTORYLIST_RECV                     -1074
#define CMD_CLUBBOOKLIST                     1075
#define CMD_CLUBBOOKLIST_RECV                     -1075
#define CMD_CLUBBOOKADD                     1076
#define CMD_CLUBBOOKADD_RECV                     -1076
#define CMD_CLUBBOOKDEL                     1077
#define CMD_CLUBBOOKDEL_RECV                     -1077

#define CMD_FASHIONWEEKDRESSLIST                     1078
#define CMD_FASHIONWEEKDRESSLIST_RECV                     -1078



#define CMD_FASHIONWEEKEXP                     1082
#define CMD_FASHIONWEEKEXP_RECV                     -1082

#define CMD_FASHIONWEEKSCOREUPDATE                     1083
#define CMD_FASHIONWEEKSCOREUPDATE_RECV                     -1083





#define CMD_FASHIONWEEKFITTINGLIST                     1084
#define CMD_FASHIONWEEKFITTINGLIST_RECV                     -1084





#define CMD_FASHIONWEEKFITTINGUPDATE                     1085
#define CMD_FASHIONWEEKFITTINGUPDATE_RECV                     -1085


#define CMD_CLUBRANKLIST                     1086
#define CMD_CLUBRANKLIST_RECV                     -1086

#define CMD_PANGRESULT                        1087
#define CMD_PANGRESULT_RECV                        -1087



#define CMD_CLUBDRESSBUY                        1088
#define CMD_CLUBDRESSBUY_RECV                        -1088


#define CMD_PANGSTART                        1089
#define CMD_PANGSTART_RECV                        -1089

#define CMD_CLUBSTORAGYLIST                  1090
#define CMD_CLUBSTORAGYLIST_RECV                  -1090

#define CMD_CLUBITEMBUY                      1091
#define CMD_CLUBITEMBUY_RECV                      -1091

#define CMD_CLUBGIVEGIFT                     1092
#define CMD_CLUBGIVEGIFT_RECV                     -1092

#define CMD_CLUBDONATION                     1093
#define CMD_CLUBDONATION_RECV                     -1093

#define CMD_PANGTIMESRESET                   1094
#define CMD_PANGTIMESRESET_RECV                   -1094

#define CMD_CLUBITEMDELETE                   1095
#define CMD_CLUBITEMDELETE_RECV                   -1095

#define CMD_CLUBICONLISTUPDATE               1096
#define CMD_CLUBICONLISTUPDATE_RECV               -1096

#define CMD_CLUBICONBUY                      1097
#define CMD_CLUBICONBUY_RECV                      -1097

#define CMD_CLUBICONUPDATE                   1098
#define CMD_CLUBICONUPDATE_RECV                   -1098

#define CMD_CLUBDONATIONCOUNT                1099
#define CMD_CLUBDONATIONCOUNT_RECV                -1099

#define CMD_CLUBNAMEMODIFY                   1100
#define CMD_CLUBNAMEMODIFY_RECV                   -1100

#define CMD_PANGCOUNTCHECK                   1101
#define CMD_PANGCOUNTCHECK_RECV                   -1101

#define CMD_FORMERLISTUPDATE                 1102
#define CMD_FORMERLISTUPDATE_RECV                 -1102

#define CMD_FORMERSTART                      1103
#define CMD_FORMERSTART_RECV                      -1103

#define CMD_FORMERTAKEWEALTH                 1104
#define CMD_FORMERTAKEWEALTH_RECV                 -1104

#define CMD_AUTOSELL						2000
#define CMD_AUTOSELL_RECV							-2000

#define CMD_PRODUCTIONSLOTUPDATE            10000
#define CMD_PRODUCTIONSLOTUPDATE_RECV               -10000

#define CMD_PRODUCTIONSLOTOPEN              10001
#define CMD_PRODUCTIONSLOTOPEN_RECV                 -10001

#define CMD_PRODUCTIONINFOUPDATE            10002
#define CMD_PRODUCTIONINFOUPDATE_RECV               -10002

#define CMD_PRODUCTIONSLOTINFOUPDATE        10003
#define CMD_PRODUCTIONSLOTINFOUPDATE_RECV           -10003

//#define CMD_PRODUCTIONREGIST                10004
//#define CMD_PRODUCTIONREGIST_RECV                   -10004
//
//#define CMD_PRODUCTIONDELETE                10005
//#define CMD_PRODUCTIONDELETE_RECV                   -10005

#define CMD_SENDMACHINEINFO                 10004
#define CMD_SENDMACHINEINFO_RECV                    -10004

#define CMD_SENDMACHINESLOTINFO             10005
#define CMD_SENDMACHINESLOTINFO_RECV                -10005

#define CMD_SENDMACHINESLOTOPEN             10006
#define CMD_SENDMACHINESLOTOPEN_RECV                -10006

#define CMD_SENDMACHINESLOTUPDATE           10007
#define CMD_SENDMACHINESLOTUPDATE_RECV              -10007

#define CMD_GETDRESSINFO                    10008
#define CMD_GETDRESSINFO_RECV                       -10008

#define CMD_GREENHOUSEINFOUPDATE            10009
#define CMD_GREENHOUSEINFOUPDATE_RECV               -10009

#define CMD_GREENHOUSESLOTUPDATE            10010
#define CMD_GREENHOUSESLOTUPDATE_RECV               -10010

#define CMD_SPINNINGWHEELINFOUPDATE         10011
#define CMD_SPINNINGWHEELINFOUPDATE_RECV            -10011

#define CMD_SPINNINGWHEELSLOTUPDATE         10012
#define CMD_SPINNINGWHEELSLOTUPDATE_RECV            -10012

#define CMD_GETCARROT                       10013
#define CMD_GETCARROT_RECV                          -10013

/////////////////////////////////////////////////////////////
//10014번 들어올 자리

#define CMD_GETDRESSROOMINFO                10014
#define CMD_GETDRESSROOMINFO_RECV						-10014

/////////////////////////////////////////////////////////////

#define CMD_BUYDRESSCHAR                    10015
#define CMD_BUYDRESSCHAR_RECV                       -10015

#define CMD_UPDATEMYDRESS                10016
#define CMD_UPDATEMYDRESS_RECV						-10016

#define NET_CONN			0
#define NET_SEND			1
#define NET_RECV			2
#define NET_WAIT			3

#define SALEEVENT_FALSE			0
#define SALEEVENT_TRUE			1
#define SALEEVENT_TEST			2

typedef struct _XNet
{
	M_Int32 iapState;
	M_Char strIapPid[20];		//과금코드

	M_Boolean isFriendMode;		//친구모드

	M_Int32 friendRecvYesNo;
	M_Int32 netModeType;
	M_Int32 roomNum;

	M_Int32 rankCnt;
	M_Int32 bPlayState;
	M_Int32 bState;

	M_Boolean isConnt;
	M_Int8 state;
	M_Int32 socket;
	M_Int32 code;
	M_Int16 cmd;
	M_Int16 nSendLenth;
	M_Int16 nRecvLenth;
	M_Int16 nSendLenthMax;
	M_Int16 nRecvLenthMax;
	M_Char czSendBuf[3000];		
	M_Char czRecvBuf[3000];		
	M_Int32 addr;
	M_Int16 port;
	
	M_Int32 connectTime;
	M_Int32 winlosedraw;
	M_Boolean isHeartBit;
	M_Int64 heartBitTime;
	
	
	M_Int64 heartBitTime22;
	M_Boolean isAndroidClose;
	
	M_Boolean isGetTime;
	
	
	
} XNet;
extern XNet xnet;
//*************************************


extern int fashionNum;	//패션카테고리넘버


typedef struct _PRODUCTIONINFO
{
	int bkey;
	int type;
	int ckey;
	int state;
	int itemIndex;
	M_Int64 time;
	int bonus;
	int floor;
} XNETPRODUCTIONINFO;
extern XNETPRODUCTIONINFO xNetProductionInfo;

typedef struct _XNETFASHION
{
	int code;
	int haveNum;
} XNETFASHION;
extern XNETFASHION xNetFashion;


typedef struct _XNETEVENTQUEST
{
    int DETAIL_TYPE;
    int DETAIL_INDEX;
    int VALUE;
} XNETEVENTQUEST;
extern XNETEVENTQUEST xNetEventQuest;




typedef struct _XNETEXTERNALWALL
{
	int state;
	int side_index;
} XNETEXTERNALWALL;
extern XNETEXTERNALWALL xNetExternalWall;


typedef struct _XNETSETPUSH
{
	int userNum;
	int state;
} XNETSETPUSH;
extern XNETSETPUSH xNetSetPush;



typedef struct _XNETHOTDEAL
{
    int slot;
} XNETHOTDEAL;
extern XNETHOTDEAL xNetHotDeal;




typedef struct _XNETSENDMARKTING
{
	int friendNum;
} XNETSENDMARKTING;
extern XNETSENDMARKTING xNetSendMarketing;


typedef struct _XNETCOUPON
{
	char strText[64];
} XNETCOUPON;
extern XNETCOUPON xNetCoupon;


typedef struct _XNETGETMODELMAIN
{
	int friendNum;
} XNETGETMODELMAIN;
extern XNETGETMODELMAIN xNetGetModelMain;


typedef struct _XNETSETSOUND
{
	int index;
} XNETSETSOUND;
extern XNETSETSOUND xNetSetSound;

typedef struct _XNETG9EVENT
{
	int state;
} XNETG9EVENT;
extern XNETG9EVENT xNetG9Event;


typedef struct _XNETBOOKMARK
{
    int FRIENDNUM;
    int BOOKMARK;
} XNETBOOKMARK;
extern XNETBOOKMARK xNetBookMark;




typedef struct _XNETBUYGOLD
{
	int index;
	int typeB;
	int typeS;
} XNETBUYGOLD;
extern XNETBUYGOLD xNetBuyGold;



typedef struct _XNETSETMODELMAIN
{
	int slot;
	int modelKey;
	int endTime;
	int state;
} XNETSETMODELMAIN;
extern XNETSETMODELMAIN xNetSetModelMain;



typedef struct _XNETTRENDMAKERVOTELIST
{
	int type;
} XNETTRENDMAKERVOTELIST;
extern XNETTRENDMAKERVOTELIST xNetTrendMakerVoteList;


typedef struct _XNETTAKEPART
{
	int key;
} XNETTAKEPART;
extern XNETTAKEPART xNetTakePart;


typedef struct _XNETMARKETINGRECVYESNO
{
	int key;
	int type;
	int userNum;	
} XNETMARKETINGRECVYESNO;
extern XNETMARKETINGRECVYESNO xNetMarketingRecvYesNo;


typedef struct _XNEGETMODELLISTFRIEND
{
	int friendUserNum;
} XNEGETMODELLISTFRIEND;
extern XNEGETMODELLISTFRIEND xNetGetModelListFriend;


typedef struct _XNETKAKAOHELP
{
	int friendUserNum;
} XNETKAKAOHELP;
extern XNETKAKAOHELP xNetKakaoHelp;



typedef struct _XNEMODELVOTE
{
	int friendUserNum;
	int key;
} XNEMODELVOTE;
extern XNEMODELVOTE xNetModelVote;





typedef struct _XNETVOTE
{
	int friendNum;
} XNETVOTE;
extern XNETVOTE xNetVote;


typedef struct _XNETTRENDMAKERINFO
{
	int userNum;
} XNETTRENDMAKERINFO;
extern XNETTRENDMAKERINFO xNetTrendMakerInfo;

typedef struct _XNETBESTDESIGNERRESULT
{
	int key;
	int score;
} XNETBESTDESIGNERRESULT;
extern XNETBESTDESIGNERRESULT xNetBestDesignerResult;

typedef struct _XNETOPENMODEL
{
	int code;
} XNETOPENMODEL;
extern XNETOPENMODEL xNetOpenModel;

typedef struct _XNETMODELGROUPGFIT
{
	int code;
} XNETMODELGROUPGFIT;
extern XNETMODELGROUPGFIT xNetModelGroupGift;


typedef struct _XNETQUEST
{
	int type;	
	int slot;
	int gold;
	int cash;
	int exp;

} XNETQUEST;
extern XNETQUEST xNetQuest;


typedef struct _XNETSETMODEL
{
	int state;
	int code;
	int upgrade;
	int slotNum;
	int key;
	int layer[16];
	int load;
	int inFitting;
	

} XNETSETMODEL;
extern XNETSETMODEL xNetSetModel;




typedef struct _XNETTILE
{
	int tileCode;
	int wallCode;
	int floor;
	int type;

	

} XNETTILE;
extern XNETTILE xNetTile;




typedef struct _XNETGETMAP
{
	int action;
	int userNum;
	int friendNum;
} XNETGETMAP;
extern XNETGETMAP xNetGetMap;


typedef struct _XNETDELMAIL
{
	int userNum;
	int key;
} XNETDELMAIL;
extern XNETDELMAIL xNetDelMail;


typedef struct _XNETDELGIFT
{
	int key;
} XNETDELGIFT;
extern XNETDELGIFT xNetDelGift;


typedef struct _XNETSENDGIFT
{
	int friendNum;
	int cash;
} XNETSENDGIFT;
extern XNETSENDGIFT xNetSendGift;




typedef struct _XNETFRIENDSOCIAL
{
	int floor;
	int key;
	int friendNum;
} XNETFRIENDSOCIAL;
extern XNETFRIENDSOCIAL xNetFriendSocial;

typedef struct _XNETMYSOCIALLIST
{
	int userNum;
	int floor;

    
    bool isEventQueue;
    
    
} XNETMYSOCIALLIST;
extern XNETMYSOCIALLIST xNetMySocialList;


typedef struct _XNETGETGAMEINFO
{
	int userNum;
} XNETGETGAMEINFO;
extern XNETGETGAMEINFO xNetGetGameInfo;

typedef struct _XNETMINIPROFILE
{
	int userNum;
} XNETMINIPROFILE;
extern XNETMINIPROFILE xNetMiniProfile;


typedef struct _XNETGETORDER
{
	int userNum;
} XNETGETORDER;
extern XNETGETGAMEINFO xNetGetOrder;

typedef struct _XNETGETFASHION
{
	int userNum;
} XNETGETFASHION;
extern XNETGETFASHION xNetGetFashion;



typedef struct _XNETGETFASHIONSHOWRANK
{
	int pageNum;
	int action;
	int request;
} XNETGETFASHIONSHOWRANK;
extern XNETGETFASHIONSHOWRANK xNetFashionShowRank;


typedef struct _XNETGETFASHIONSHOWRANKINFO
{
	int userNum;
	int action;
} XNETGETFASHIONSHOWRANKINFO;
extern XNETGETFASHIONSHOWRANKINFO xNetFashionShowRankInfo;


typedef struct _XNETGETFRIENDLIST
{
	int rowNum;
	int pageNum;
	int action;
} XNETGETFRIENDLIST;
extern XNETGETFRIENDLIST xNetFriendList;

typedef struct _XNETGETGIFTLIST
{
	int rowNum;
	int pageNum;
} XNETGETGIFTLIST;
extern XNETGETGIFTLIST xNetGetGiftList;



typedef struct _XNETGETMAILLIST
{
	int rowNum;
	int pageNum;
	int userNum;
} XNETGETMAILLIST;
extern XNETGETMAILLIST xNetGetMailList;

typedef struct _XNETDELCLEAN
{
	int cKey;
	int bKey;
	int floor;
} XNETDELCLEAN;
extern XNETDELCLEAN xNetDelClean;

typedef struct _XNETGETFRIENDSEARCH
{
	int action;
	char strNickName[64];
} XNETGETFRIENDSEARCH;
extern XNETGETFRIENDSEARCH xNetFriendSearch;



typedef struct _XNETDELRECVORDER
{
	int key;	
} XNETDELRECVORDER;
extern XNETDELRECVORDER xNetDelRecvOrder;




typedef struct _XNETTREND
{
	int slotNum;
	int open;
	int code;
	int type;
	int haveNum;
	int time;
	int per;

} XNETTREND;
extern XNETTREND xNetTrend;


typedef struct _XNETFACE
{
	int code;
	int haveNum;
} XNETFACE;
extern XNETFACE xNetFace;


typedef struct _XNETSETFLOOR
{
	int action;
} XNETSETFLOOR;
extern XNETSETFLOOR xNetSetFloor;


typedef struct _XNETINTERIOR
{
	int code;
	int haveNum;
} XNETINTERIOR;
extern XNETINTERIOR xNetInterior;

typedef struct _XNETMAP
{
	int code;
	int floor;
	int action;
	int key;
	int mapX;
	int mapY;
	
	
	int gold;
	int cash;

	
} XNETMAP;
extern XNETMAP xNetMap;

typedef struct _XNETPRODUCTIONSLOT
{
    int type;
    int slot;
    int itemcode;
    int time;
}XNETPRODUCTIONSLOT;
extern XNETPRODUCTIONSLOT xNetProductionSlot;

typedef struct _XNETGREENHOUSESLOT
{
    int type;
    int slot;
    int ItemIndex;
    int ItemCnt;
    int time;
}XNETGREENHOUSESLOT;

extern XNETGREENHOUSESLOT xNetGreenHouseSlot;

typedef struct _XNETSPINNINGWHEELSLOT
{
    int type;
    int slot;
    int ItemIndex;
    int ItemCnt;
    int time;
}XNETSPINNINGWHEELSLOT;

extern XNETSPINNINGWHEELSLOT xNetSpinningWheelSlot;

typedef struct _XNETFORMER
{
    int key;
    int type;
    int wealth;
    int startTime;
    
}XNETFORMER;
extern XNETFORMER xNetFormer;

typedef struct _XNETSELLTABLE
{
	int floor;
	int key;
	XSELLSLOT xSellSlot[9];
	
} XNETSELLTABLE;
extern XNETSELLTABLE xNetSellTable;

typedef struct _XNETSHOWWINDOW
{
	int floor;
	int key;
	int sex;
	int inFitting;


	int layer[16];	
} XNETSHOWWINDOW;
extern XNETSHOWWINDOW xNetShowWindow;


typedef struct _XNETSTAFF
{
	int floor;
	int type;
	char strNickName[64];
	int sex;
	int inFitting;
	int layer[6];
} XNETSTAFF;
extern XNETSTAFF xNetStaff;


typedef struct _XNETINITGAME
{
	int action;
	int result;

} XNETINITGAME;
extern XNETINITGAME xNetInitGame;

typedef struct _XNETCAR
{
	int code;
} XNETCAR;
extern XNETCAR xNetCar;

typedef struct _XNETCARPARK
{
	int slot;
	int key;
	int carNum;
	int state;
	int time;
} XNETCARPARK;
extern XNETCARPARK xNetCarPark;


typedef struct _XNETADDORDER
{
	int state;
	int code;
	int userNum;
	int friendNum;
	int slotNum;

} XNETADDORDER;
extern XNETADDORDER xNetAddOrder;

typedef struct _XNETSENDMAIL
{
	int userNum;
	int friendNum;
	int action;

} XNETSENDMAIL;
extern XNETSENDMAIL xNetSendMail;


typedef struct _XNETADDFRIEND
{
	int friendNum;
	char strKakaoid[128];
} XNETADDFRIEND;
extern XNETADDFRIEND xNetAddFriend;

typedef struct _XNETDELFRIEND
{
	int friendNum;
} XNETDELFRIEND;
extern XNETDELFRIEND xNetDelFriend;


typedef struct _XNETORDER
{
	int state;
	int key;
	int endTime;
} XNETORDER;
extern XNETORDER xNetOrder;

typedef struct _XNETORDEROK
{
	int action;
	int key;
} XNETORDEROK;
extern XNETORDEROK xNetOrderOk;



typedef struct _XNETPROFILEUPLOAD
{
    int imgBufSize;
    char imgBuf[209600];
} XNETPROFILEUPLOAD;
extern XNETPROFILEUPLOAD xNetProfileUpLoad;


typedef struct
{
	int item_index[16];
	int item_count[16];
	int item_category[16];
	int totalNum;
} XNETAUTOPRODUCT;
extern XNETAUTOPRODUCT xNetAutoProduct;

typedef struct
{
	int gold;
} XNETAUTOSELL;
extern XNETAUTOSELL xNetAutoSell;


typedef struct _XNETDATA
{
	
    char strCdnUrl[128];

	char strGameServerUrl[128];
	char strImgServerUrl[128];
	char strGameUpDateServerUrl[128];
    
    
    char strReviewUrl[128];
    
    
    
    
    
	char strNotice[1024];
	char strAuthentiCode[128];
	char strUid[256];
	int userNum;
	int eventNum;
    
    
    bool isQa;
	
	
	M_Int64	serverTime;
		
	
} XNETDATA;
extern XNETDATA xNetData;







typedef struct _XHeader
{
	M_Byte header[2];		//KTFN, SKTW											//4
	M_Byte len[2];													//4
	///////////////////////////////////////////////////////
} XHeader;



typedef struct _XNETHEARTBIT
{
	XHeader xHeader;
	M_Byte type[2];			
	///////////////////////////////////////////////////////
} XNETHEARTBIT;
extern XNETHEARTBIT xNetHeartBit;



typedef struct _XNETMILEAGESHOPBUY
{
    int ITEM_INDEX;
    char ADDRESS[256];
    char BUYER_NAME[128];
    char PHONENUM[128];
    
} XNETMILEAGESHOPBUY;
extern XNETMILEAGESHOPBUY xNetMileageShopBuy;



typedef struct _XNETMILEAGESHOPUPDATE
{
    int ITEM_KEY;
    char ADDRESS[256];
    char BUYER_NAME[128];
    char PHONENUM[128];
    
} XNETMILEAGESHOPUPDATE;
extern XNETMILEAGESHOPUPDATE xNetMileageShopUpdate;


typedef struct _XNETPRODUCTIONNET
{
    int SLOT;
    int ITEM_INDEX;
    
    int resultGold;
    int resultCash;
    int resultCount;
    
} XNETPRODUCTIONNET;
extern XNETPRODUCTIONNET xNetProductionNet;



typedef struct _XNETJEWELQUEST
{
    int INDEX;
    int VALUE;
    
} XNETJEWELQUEST;
extern XNETJEWELQUEST xNetJewelQuest;


typedef struct _XNETAMULETUPDATE
{
    int pageUpdate;
    int selectPage;
} XNETAMULETUPDATE;
extern XNETAMULETUPDATE xNetAmuletUpdate;


typedef struct _XNETAMULETBUY
{
    int AMULET;
} XNETAMULETBUY;
extern XNETAMULETBUY xNetAmuletBuy;


typedef struct _XNETAMULETPAGEBUY
{
    int DECK;
} XNETAMULETPAGEBUY;
extern XNETAMULETPAGEBUY xNetAmuletPageBuy;



typedef struct _XNETCLUBJOIN
{
    int CLUB_NUM;
} XNETCLUBJOIN;
extern XNETCLUBJOIN xNetClubJoin;








typedef struct _XNETSELLNET
{
    int FLOOR;
    int KEY;
    int SLOT;
    int ITEM_INDEX;
    int COUNT;
    int SELL_COUNT;
    
    int EXP;
    int GOLD;
    int POP;
    
    
    int resultGold;
    int resultExp;
    int resultCash;
    int resultCount;
} XNETSELLNET;
extern XNETSELLNET xNetSellNet;




typedef struct _XNETCLUBDATA
{
    int CLUB_NUM;
} XNETCLUBDATA;
extern XNETCLUBDATA xNetClubData;


typedef struct _XNETCLUBMEMBER
{
    int CLUB_NUM;
} XNETCLUBMEMBER;
extern XNETCLUBMEMBER xNetClubMember;




typedef struct
{
    int MEMBER_NUM;
} XNETSETCLUBFORCEOUT;
extern XNETSETCLUBFORCEOUT xNetSetClubForceOut;



typedef struct
{
    int MEMBER_NUM;
} XNETSETCLUBMASTER;
extern XNETSETCLUBMASTER xNetSetClubMaster;



typedef struct
{
    int rowNum;
    int pageNum;
} XNETCLUBHISTORYLIST;
extern XNETCLUBHISTORYLIST xNetClubHistoryList;


typedef struct
{
    int rowNum;
    int pageNum;
} XNETCLUBBOOKLIST;
extern XNETCLUBBOOKLIST xNetClubBookList;


typedef struct
{
    int CLUB_NUM;
} XNETCLUBJOINAPPLY;
extern XNETCLUBJOINAPPLY xNetClubJoinApply;


typedef struct
{
    int DRESS_NUM;
} XNETCLUBDRESSBUY;
extern XNETCLUBDRESSBUY xNetClubDressBuy;

/////////////////////////////////////////////////////////////////////
//전송기 이벤트큐 추가 LJW 2018.01.22
typedef struct
{
	int bkey;
}XNETSENDMACHINESLOTINFO;
extern XNETSENDMACHINESLOTINFO xNetSendMachineSlotInfo;

typedef struct
{
	int slot;
	int bkey;
}XNETSENDMACHINESLOTOPEN;
extern XNETSENDMACHINESLOTOPEN xNetSendMachineSlotOpen;

typedef struct
{
	int type;
	int bkey;
	int idx;
	int item_index;
	int item_count;
	int start_time;
	int end_time;
}XNETSENDMACHINESLOTUPDATE;
extern XNETSENDMACHINESLOTUPDATE xNetSendMachineSlotUpdate;
/////////////////////////////////////////////////////////////////////
//당근 KBY
typedef struct
{
    int endTime;
}XNETCARROT;
extern XNETCARROT xNetCarrot;
/////////////////////////////////////////////////////////////////////
//의상 구매 KBY
typedef struct
{
    int DressCode;
}XNETBUYDRESS;
extern XNETBUYDRESS xNetBuyDress;

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//옷장 이벤트큐 추가 LJW 2018.02.12
typedef struct
{
    int type;
}XNETGETDRESSROOMINFO;
extern XNETGETDRESSROOMINFO xNetGetDressRoomInfo;
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//내 캐릭터 의상 입히기 이벤트큐 추가 LJW 2018.02.12
typedef struct
{
    int DRESS0;
    int DRESS1;
    int DRESS2;
    int DRESS3;
    int DRESS4;
    int DRESS5;
    int DRESS6;
    int DRESS7;
    int DRESS8;
    int DRESS9;
}XNETUPDATEMYDRESS;
extern XNETUPDATEMYDRESS xNetUpdateMyDress;
/////////////////////////////////////////////////////////////////////


void netSend(M_Int32 cmd,M_Int32 subIndex);
void SockRecvCB(M_Int32 fd, M_Int32 error, void *param);

void setRecv(char *strJson);

void urlBuffUpLoad(char *buff, int userkey, int fileSize);
void downloadImage(const char *strFileName,const char *strFileUrl);

void parserJson(char *str);


#endif


