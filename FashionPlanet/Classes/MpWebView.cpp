//
//  MpTextField.cpp
//  FridayNight
//
//  Created by DaeHo on 2014. 8. 20..
//
//
#include "Global.h"


XWEBVIEW xWebView;


MpWebView::MpWebView()
{
    
}


MpWebView::~MpWebView()
{
    
}

Scene* MpWebView::createScene()
{
    auto scene = Scene::create();
    auto layer = MpWebView::create();
    scene->addChild(layer);
    return scene;
}

bool MpWebView::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
    xGame.webView = cocos2d::experimental::ui::WebView::create();
    
    xGame.webView->setAnchorPoint(Point(0.5f, 0.5f));
    xGame.webView->setContentSize(Size(visibleSize.width, visibleSize.height-100));
    xGame.webView->setPosition(Vec2(origin.x + visibleSize.width * 0.5f,
                              origin.y-50 + visibleSize.height * 0.5f));
    xGame.webView->setScalesPageToFit(true);
    xGame.webView->loadURL(xWebView.strWebViewUrl);
    
    
    xGame.webView->setOnShouldStartLoading(CC_CALLBACK_2(MpWebView::onWebViewShouldStartLoading, this));
    xGame.webView->setOnDidFinishLoading(CC_CALLBACK_2(MpWebView::onWebViewDidFinishLoading, this));
    xGame.webView->setOnDidFailLoading(CC_CALLBACK_2(MpWebView::onWebViewDidFailLoading, this));
    
    this->addChild(xGame.webView, 0,100);
    
    
    
    return true;
}


bool MpWebView::onWebViewShouldStartLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewShouldStartLoading, url is %s", url.c_str());
    
    return true;
}

void MpWebView::onWebViewDidFinishLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewDidFinishLoading, url is %s", url.c_str());
}

void MpWebView::onWebViewDidFailLoading(experimental::ui::WebView *sender, const std::string &url)
{
    CCLOG("onWebViewDidFailLoading, url is %s", url.c_str());
}



void openWebView(int type)
{
    xWebView.type = type;
    switch(xWebView.type)
    {
    case WEBVIEW_TYPE_MILEAGESHOP:
        sprintf(xWebView.strWebViewUrl,"%s",xMileageData.xSlot[xMileageShop.listCode[xMileageShop.selectSlot]/10000][xMileageShop.listCode[xMileageShop.selectSlot]%10000].strUrl);
        break;
    }
    
    printf("xWebView.strWebViewUrl>>%s\n",xWebView.strWebViewUrl);
    
    xWebView.layerWebView = MpWebView::create();
    xWebView.layerWebView->setTag(100);
    xGame.scene->addChild(xWebView.layerWebView);//메인레이어드
    xWebView.isWebView = true;
}

void closeWebView()
{
    xGame.scene->removeChild(xWebView.layerWebView);
    xWebView.isWebView = false;
}

void prcWebView()
{
    //웹뷰체크
    if(xGame.scene->getChildByTag(100) == 0)
        xWebView.isWebView = false;
    else
        xWebView.isWebView = true;
}

void drawWebView()
{
    int px = cx;
    gSetColor(255, 255, 255);
    fillRect(0, 0, lcdW, lcdH);
    drawImage(&imgWebView[0], px, 50, 0, 0, imgWebView[0].w, imgWebView[0].h, VH);
    
    switch(xWebView.type)
    {
    case WEBVIEW_TYPE_MILEAGESHOP:
        sprintf(strTempS, "마일리지샵");
        break;
    }
    
    gSetColor(255, 255, 255);
    setFontSize(40);
    gDrawString(px, 50, strTempS, VH);
    setFontSize(11);
    
    subTemp[XPOS] = lcdW-50;
    subTemp[YPOS] = 50;
    xWebView.xTouchExit.wPos = 100;
    xWebView.xTouchExit.hPos = 100;
    xWebView.xTouchExit.xPos = subTemp[XPOS]-xWebView.xTouchExit.wPos/2;
    xWebView.xTouchExit.yPos = subTemp[YPOS]-xWebView.xTouchExit.hPos/2;
    
    
    subTemp[XPOS] = 50;
    subTemp[YPOS] = 50;
    xWebView.xTouchBack.wPos = 100;
    xWebView.xTouchBack.hPos = 100;
    xWebView.xTouchBack.xPos = subTemp[XPOS]-xWebView.xTouchBack.wPos/2;
    xWebView.xTouchBack.yPos = subTemp
    [YPOS]-xWebView.xTouchBack.hPos/2;
}

void keyWebView(int type, int param1, int param2,int touchId,int touchCount)
{
    //터치 및 트레그
    if(touchTypeTemp == MH_KEY_PRESSEVENT)
    {
        if(touchCheck(&xWebView.xTouchBack) && touchType == USER_POINT_PRESS_EVENT)
        {
            playSnd(SND_MENU_OK);
            xWorldMap.isKeyReturn = true;
            xGame.webView->goBack();
        }
        else if(touchCheck(&xWebView.xTouchExit) && touchType == USER_POINT_PRESS_EVENT)
        {
            playSnd(SND_MENU_OK);
            xWorldMap.isKeyReturn = true;
            closeWebView();
        }
    }
}


