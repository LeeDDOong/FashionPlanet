#include "Global.h"

XROCKS xRocks;
void setFiveRocksUser(char *strId,int lv,int friendsNum,char *strVer,char *strSex,char *strArea,char *strAge)
{
#if(SERVER_TYPE==SEVER_TYPE_DEV)
    return;
#endif
    
    if(xNetData.isQa == true)
        return;
    

    
    
    char strFriendsNum[128];
    sprintf(strFriendsNum, "%d",friendsNum);
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "setTabjoyUserInfo", "(I[B[B[B[B[B[B)V")) {
        
        jbyteArray arg1;
        arg1 = t.env->NewByteArray(strlen(strId));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strId), (jbyte*)strId);
        
        jbyteArray arg2;
        arg2 = t.env->NewByteArray(strlen(strFriendsNum));
        t.env->SetByteArrayRegion(arg2, 0, strlen(strFriendsNum), (jbyte*)strFriendsNum);
        
        jbyteArray arg3;
        arg3 = t.env->NewByteArray(strlen(strVer));
        t.env->SetByteArrayRegion(arg3, 0, strlen(strVer), (jbyte*)strVer);
        
        jbyteArray arg4;
        arg4 = t.env->NewByteArray(strlen(strSex));
        t.env->SetByteArrayRegion(arg4, 0, strlen(strSex), (jbyte*)strSex);
        
        jbyteArray arg5;
        arg5 = t.env->NewByteArray(strlen(strArea));
        t.env->SetByteArrayRegion(arg5, 0, strlen(strArea), (jbyte*)strArea);
        
        jbyteArray arg6;
        arg6 = t.env->NewByteArray(strlen(strAge));
        t.env->SetByteArrayRegion(arg6, 0, strlen(strAge), (jbyte*)strAge);
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID,lv, arg1, arg2, arg3, arg4, arg5, arg6);
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(arg2);
        t.env->DeleteLocalRef(arg3);
        t.env->DeleteLocalRef(arg4);
        t.env->DeleteLocalRef(arg5);
        t.env->DeleteLocalRef(arg6);

        t.env->DeleteLocalRef(t.classID);
    }
#endif

}

void setFiveRocksPurchase(char*strName, int price)
{
    
#if(SERVER_TYPE==SEVER_TYPE_DEV)
    return;
#endif
    
    
    if(xNetData.isQa == true)
        return;
    
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "setTabjoyPurchase", "([BI)V")) {
        
        jbyteArray arg1;
        arg1 = t.env->NewByteArray(strlen(strName));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strName), (jbyte*)strName);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID,arg1, price);
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void setFiveRocksCustom(char*strCategory,char*strName,char*strPar1,char*strPar2,int value)
{
    
    if(xNetData.isQa == true)
        return;
    
    
    
#if(SERVER_TYPE==SEVER_TYPE_DEV)
    return;
#endif
    
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "setTabjoyEventSM", "([B[B[B[BI)V")) {
        
        jbyteArray arg1;
        arg1 = t.env->NewByteArray(strlen(strCategory));
        t.env->SetByteArrayRegion(arg1, 0, strlen(strCategory), (jbyte*)strCategory);
        
        jbyteArray arg2;
        arg2 = t.env->NewByteArray(strlen(strName));
        t.env->SetByteArrayRegion(arg2, 0, strlen(strName), (jbyte*)strName);
        
        jbyteArray arg3;
        arg3 = t.env->NewByteArray(strlen(strPar1));
        t.env->SetByteArrayRegion(arg3, 0, strlen(strPar1), (jbyte*)strPar1);
        
        jbyteArray arg4;
        arg4 = t.env->NewByteArray(strlen(strPar2));
        t.env->SetByteArrayRegion(arg4, 0, strlen(strPar2), (jbyte*)strPar2);
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, arg1, arg2, arg3, arg4, value);
        t.env->DeleteLocalRef(arg1);
        t.env->DeleteLocalRef(arg2);
        t.env->DeleteLocalRef(arg3);
        t.env->DeleteLocalRef(arg4);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

