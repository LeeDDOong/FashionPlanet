//
//  MpTextField.h
//  FridayNight
//
//  Created by DaeHo on 2014. 8. 20..
//
//

#ifndef __WebView__WebTopView__
#define __WebView__WebTopView__



class MpWebView :public cocos2d::Layer
{
protected:

    MpWebView();
    virtual ~MpWebView();
    bool init() override;
    
    
    bool onWebViewShouldStartLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
    void onWebViewDidFinishLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
    void onWebViewDidFailLoading(cocos2d::experimental::ui::WebView *sender, const std::string &url);
    
    
public:
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MpWebView);
};




#define WEBVIEW_TYPE_MILEAGESHOP  0





typedef struct
{
    cocos2d::Layer *layerWebView;
    bool isWebView;
    
    XTOUCH xTouchBack;
    XTOUCH xTouchExit;
    char strWebViewUrl[256];    
    int type;
} XWEBVIEW;
extern XWEBVIEW xWebView;


void prcWebView();
void openWebView(int type);
void closeWebView();
void keyWebView(int type, int param1, int param2,int touchId,int touchCount);
void drawWebView();

#endif /* defined(__WebView__WebTopView__) */
