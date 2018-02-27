//
//  MpTextField.cpp
//  FridayNight
//
//  Created by DaeHo on 2014. 8. 20..
//
//
#include "Global.h"


XTEXTFIELD xTextField;
XSWEARWORD xSwearWord;


bool MpTextField::init()
{
    if (!Layer::init() )
    {
        return false;
    }
    
    xGame.layerTextField = this;
    
    if(xTextField.textfield == NULL)
    {
        xTextField.textfield = TextFieldTTF::textFieldWithPlaceHolder("", Size(300,40), TextHAlignment::RIGHT, "Arial", 50);
        xTextField.textfield->setColor(Color3B(ALPHA_MAX, ALPHA_MAX, ALPHA_MAX));
        xTextField.textfield->setAnchorPoint(Vec2(0.5, 0.5));
        xTextField.textfield->setPosition(Vec2(lcdW/2-150, lcdH/2+100));
        xTextField.textfield->setTag(200);
        xTextField.textfield->setVisible(false);
        
        this->addChild(xTextField.textfield,0,100);
        this->setTag(200);
    }
    return true;
}

void MpTextField::keyboardWillShow(IMEKeyboardNotificationInfo &info)
{
    //안드로이드는 적용이 안되서 따로 처리
}

void MpTextField::keyboardWillHide(IMEKeyboardNotificationInfo &info)
{
    //안드로이드는 적용이 안되서 따로 처리
}

void setTextField(int type, int x, int y, int w, int h)
{
    x = cx;
    y = lcdH+150;
    w = 600;
    
    xTextField.layer = MpTextField::create();
    xTextField.layer->setTag(200);
    xGame.scene->addChild(xTextField.layer);
    xTextField.textfield->attachWithIME();
    
    switch(type)
    {
    case TEXTBOX_TYPE_EMAIL:   setTextLength(16);break;
    case TEXTBOX_TYPE_PASS:   setTextLength(12);break;
    case TEXTBOX_TYPE_PASS2:   setTextLength(12);break;
    case TEXTBOX_TYPE_NICKNAME:   setTextLength(16);break;
    case TEXTBOX_TYPE_FRIENDID:   setTextLength(32);break;
    case TEXTBOX_TYPE_MAILTODAY:   setTextLength(32);break;
    case TEXTBOX_TYPE_MAIL:                 setTextLength(85);break;
    case TEXTBOX_TYPE_COUPON:               setTextLength(20);break;
    case TEXTBOX_TYPE_STAFFNAME:            setTextLength(32);break;
    case TEXTBOX_TYPE_MILEAGESHOP_NAME:     setTextLength(8);break;
    case TEXTBOX_TYPE_MILEAGESHOP_PHONE:    setTextLength(16);break;
    case TEXTBOX_TYPE_MILEAGESHOP_ADDRESS:  setTextLength(50);break;
    case TEXTBOX_TYPE_CLUBSEARCH:           setTextLength(6);break;
    case TEXTBOX_TYPE_CLUBMAKENAME:         setTextLength(6);break;
    case TEXTBOX_TYPE_CLUBMAKEJOININFO:     setTextLength(30);break;
    case TEXTBOX_TYPE_CLUBLOBBYJOININFO:    setTextLength(30);break;
    case TEXTBOX_TYPE_CLUBLOBBYNOTICE:      setTextLength(80);break;
    case TEXTBOX_TYPE_CLUBBOOK:             setTextLength(50);break;
    case TEXTBOX_TYPE_CLUBNAMEMODIFY:       setTextLength(6);break;
    case TEXTBOX_TYPE_FRIENDID_FP:          setTextLength(32);break;
    default: setTextLength(32);break;
    }
    
    
    xTextField.textfield->setVisible(true);
    xTextField.textfield->setString("");
	xTextField.textfield->setPosition(x, y);
	xTextField.textfield->setWidth(w);
	xTextField.textfield->setHeight(h);
    xTextField.state = TEXTFIELD_STATE_PLAY;
    xTextField.type = type;
}

void prcTextField()
{    
    if(xTextField.state == TEXTFIELD_STATE_PLAY)
    {
        /*
		switch(xTextField.type)
		{
            case TEXTFIELD_TYPE_IDMAKE:
                sprintf(xGameMake.strId, "%s",xTextField.textfield->getString().c_str());
                break;
			case TEXTFIELD_TYPE_CHATTING:
                sprintf(xChatting.strText, "%s",xTextField.textfield->getString().c_str());
                break;
		}
        */
		///////////////////////////////////////////////////////////////////////////////////////////
        char strTemp[512];
        sprintf(strTemp, "%s",xTextField.textfield->getString().c_str());
        int korEngTemp = getStringByte(strTemp);
        int kor = korEngTemp/1000;
        int eng = korEngTemp%1000;
        int korEngByte = (kor*3)+eng;
        
        if(xTextField.textfield->isOpen == false)
        {
            xTextField.state = TEXTFIELD_STATE_DONT;
            xTextField.textfield->setVisible(false);
            
            switch(xTextField.type)
            {
            case TEXTBOX_TYPE_CLUBNAMEMODIFY:
                if(korEngByte==0)
                {
                    
                }
                else
                {
                    if(xClubNameModify.state==CLUBNAME_STATE_OK)
                    {
                        sprintf(xClubNameModify.strName, "%s",xTextField.textfield->getString().c_str());
                    }
                    

                    //sprintf(xClubNameModify.strName, "%s",xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_CLUBBOOK:
                if(korEngByte == 0)
                {
                }
                else
                {
                    sprintf(xClubBook.strText,"%s", xTextField.textfield->getString().c_str());
                    
                    
                    xClubLobby.state = CLUBLOBBY_STATE_NET;
                    /////////////////////////////////////////
                    addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_CLUBBOOKADD, TRUE);
                    /////////////////////////////////////////
                    
                    xClubBook.totalNum = 0;
                    xClubBook.rowNum = 0;
                    xClubBook.pageNum = 0;
                }
                break;
            case TEXTBOX_TYPE_CLUBLOBBYJOININFO:
                if(korEngByte == 0)
                {
                }
                else
                {
                    sprintf(xClub.xMy.strJoinInfo,"%s", xTextField.textfield->getString().c_str());
                    xClubLobby.state=CLUBLOBBY_STATE_PLAY;
                    /////////////////////////////////////////
                    addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETCLUBJOININFO, TRUE);
                    /////////////////////////////////////////
                    
                }
                break;
            case TEXTBOX_TYPE_CLUBLOBBYNOTICE:
                if(korEngByte == 0)
                {
                    
                }
                else
                {
                    sprintf(xClub.xMy.strNotice,"%s", xTextField.textfield->getString().c_str());
                    xClubLobby.state=CLUBLOBBY_STATE_PLAY;
                    /////////////////////////////////////////
                    addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_SETCLUBNOTICE, TRUE);
                    /////////////////////////////////////////
                }
                break;
            case TEXTBOX_TYPE_CLUBMAKENAME:
                if(korEngByte == 0)
                {
                }
                else
                {
                    sprintf(xClubMake.strName,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_CLUBMAKEJOININFO:
                if(korEngByte == 0)
                {
                }
                else
                {
                    sprintf(xClubMake.strJoinInfo,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_CLUBSEARCH:
                if(korEngByte == 0)
                {
                }
                else
                {
                    sprintf(xClubSearch.strName,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_MILEAGESHOP_NAME:
                if(korEngByte == 0)
                {
                }
                else
                {
                    sprintf(xMileageShop.strName,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_MILEAGESHOP_PHONE:
                if(korEngByte == 0)
                {
                }
                else
                {
                    sprintf(xMileageShop.strPhone,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_MILEAGESHOP_ADDRESS:
                if(korEngByte == 0)
                {
                }
                else
                {
                    sprintf(xMileageShop.strAddress,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_EMAIL:
                break;
            case TEXTBOX_TYPE_PASS:
                break;
            case TEXTBOX_TYPE_PASS2:
                break;
            case TEXTBOX_TYPE_COUPON:
                if(korEngByte == 0)
                {
                    
                }
                else
                {
                    sprintf(xShop.strCoupon,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_NICKNAME:
                if(korEngByte == 0)
                {
                    
                }
                else
                {
                    sprintf(xIdMake.strNickName,"%s", xTextField.textfield->getString().c_str());
                    xIdMake.state=IDMAKE_STATE_IDMAKE;
                }
                break;
            case TEXTBOX_TYPE_FRIENDID:
                if(korEngByte == 0)
                {
                    
                }
                else
                {
                    sprintf(xFriend.strUserName,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            case TEXTBOX_TYPE_FRIENDID_FP:
                if(korEngByte == 0)
                {
                        
                }
                else
                {
                    if(xFriend_FP.SearchState==FRIENDSEARCH_FP_STATE_OK)
                    {
                        sprintf(xFriend_FP.strName,"%s", xTextField.textfield->getString().c_str());
                    }
                }
                break;
            case TEXTBOX_TYPE_MAILTODAY:
                if(korEngByte == 0)
                {
                    
                }
                else
                {
                    sprintf(xMail.strToday,"%s", xTextField.textfield->getString().c_str());
                    addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_TODAY, FALSE);
                    setQuest(26, 1, DONT);
                }
                break;
            case TEXTBOX_TYPE_STAFFNAME:
                if(korEngByte == 0)
                {
                    
                }
                else
                {
                    sprintf(xStaffMake.strName,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            /*
            case TEXTBOX_TYPE_AGE:
                if(korEngByte == 0)
                {
                    
                }
                else
                {
                    xIdMake.age = atoi(xTextField.textfield->getString().c_str());
                    if(xIdMake.age < 0)
                        xIdMake.age = 0;
                    if(xIdMake.age > 99)
                        xIdMake.age = 99;
                }
             
                break;
            */
            case TEXTBOX_TYPE_MAIL:
                if(korEngByte == 0)
                {
                    
                }
                else
                {
                    sprintf(xMail.strTextBox,"%s", xTextField.textfield->getString().c_str());
                }
                break;
            }
            xGame.scene->removeChild(xTextField.layer);
            xTextField.textfield = NULL;
        }
    }
}


void setTextLength(int length)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxTextInputWraper", "nativeSetTextLength", "(I)V")) {
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, length);
        
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}


bool checkSwearWord(char *strText)
{
    
    
    xSwearWord.totalNum = 0;
    
    for(int k=0; k< 6000; k++)
    {
        sprintf(xSwearWord.strText[xSwearWord.totalNum], "이건 아녀");
        xSwearWord.totalNum++;
    }
    
    
    sprintf(xSwearWord.strText[xSwearWord.totalNum], "지연이");
    xSwearWord.totalNum++;
    
    sprintf(xSwearWord.strText[xSwearWord.totalNum], "소영이");
    xSwearWord.totalNum++;
    
    sprintf(xSwearWord.strText[xSwearWord.totalNum], "바보");
    xSwearWord.totalNum++;
    
    
    
    
    
    
    int lenOri = strlen(strText);
    
    for(int z=0;z<lenOri;z++)
    {
        for(int k=0;k<xSwearWord.totalNum;k++)
        {
            if(strText[z] == xSwearWord.strText[k][0])
            {
                int lenData = strlen(xSwearWord.strText[k]);
                
                //데이타값이 원본값의 총값을 넘지 않을경우만 체크
                if(z+lenData <= lenOri)
                {
                    //동일 하지 않는값이 있는지 체크
                    bool isCheckSub = false;
                    for(int i=0;i<lenData;i++)
                    {
                        if(xSwearWord.strText[k][i] != strText[z+i])
                        {
                            
                            isCheckSub = true;
                            break;
                        }
                    }
                    
                    //동일한 값이 존재함
                    if(lenData > 0 && isCheckSub == false)
                    {
                        printf("KK>>%d\n",k);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}






