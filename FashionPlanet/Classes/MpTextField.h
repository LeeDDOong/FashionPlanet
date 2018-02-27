//
//  MpTextField.h
//  FridayNight
//
//  Created by DaeHo on 2014. 8. 20..
//
//

#ifndef __FridayNight__MpTextField__
#define __FridayNight__MpTextField__

class MpTextField : public cocos2d::Layer, public cocos2d::IMEDelegate
{
public:
    
    virtual bool init();
    CREATE_FUNC(MpTextField);
    
    virtual void keyboardWillShow(cocos2d::IMEKeyboardNotificationInfo &info);
    virtual void keyboardWillHide(cocos2d::IMEKeyboardNotificationInfo &info);
};


#define TEXTFIELD_STATE_DONT        0
#define TEXTFIELD_STATE_PLAY        1


#define TEXTBOX_TYPE_EMAIL		1
#define TEXTBOX_TYPE_PASS		2
#define TEXTBOX_TYPE_PASS2		3
#define TEXTBOX_TYPE_NICKNAME	4
#define TEXTBOX_TYPE_FRIENDID	5
#define TEXTBOX_TYPE_MAILTODAY	6
#define TEXTBOX_TYPE_MAIL		7
#define TEXTBOX_TYPE_COUPON		8
#define TEXTBOX_TYPE_STAFFNAME	9


#define TEXTBOX_TYPE_MILEAGESHOP_NAME       10
#define TEXTBOX_TYPE_MILEAGESHOP_PHONE      11
#define TEXTBOX_TYPE_MILEAGESHOP_ADDRESS	12

#define TEXTBOX_TYPE_CLUBSEARCH             13


#define TEXTBOX_TYPE_CLUBMAKENAME           14
#define TEXTBOX_TYPE_CLUBMAKEJOININFO       15



#define TEXTBOX_TYPE_CLUBLOBBYJOININFO      16
#define TEXTBOX_TYPE_CLUBLOBBYNOTICE        17

#define TEXTBOX_TYPE_CLUBBOOK               18
#define TEXTBOX_TYPE_CLUBNAMEMODIFY         19

#define TEXTBOX_TYPE_FRIENDID_FP            20




typedef struct{
    int state;
    int type;
    cocos2d::TextFieldTTF *textfield;
    cocos2d::Layer *layer;
}XTEXTFIELD;
extern XTEXTFIELD xTextField;



typedef struct
{
    int totalNum;
    char strText[10240][128];
}XSWEARWORD;
extern XSWEARWORD xSwearWord;





void setTextField(int type, int x, int y, int w, int h);
void prcTextField();
void setTextLength(int length);
bool checkSwearWord(char *strText);

#endif /* defined(__FridayNight__MpTextField__) */
