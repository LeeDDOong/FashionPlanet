#include "platform/ios/iosUtil.h"
#include "platform/ios/simpleIosUtil.h"

#include "Global.h"

/////////////20170223 IOS
#import <StoreKit/StoreKit.h>
/////////////20170223 IOS





static void static_openIosGallery()
{
    [[SimpleIosUtil sharedEngine] openIosGallery];
}

static void static_startDownLoad(const char *strFileName, const char *strURL)
{
	NSString *fileName = [[NSString alloc] initWithUTF8String:strFileName];
	NSString *URL = [[NSString alloc] initWithUTF8String:strURL];
	
    [[SimpleIosUtil sharedEngine] startDownload:fileName :URL];	
}


static void static_nativePopup(const char *strText)
{
    NSString *text = [[NSString alloc] initWithUTF8String:strText];
    [[SimpleIosUtil sharedEngine] nativePopup:text];
}

static void static_nativePopupExit(const char *strText)
{
    NSString *text = [[NSString alloc] initWithUTF8String:strText];
    [[SimpleIosUtil sharedEngine] nativePopupExit:text];
}







namespace CocosIosUtil {
	
	static IosUtil *s_pEngine;
	
	IosUtil::IosUtil()
	{
		
	}
	
	IosUtil::~IosUtil()
	{
		
	}
	
	IosUtil* IosUtil::getInstance()
	{
		if (! s_pEngine)
		{
			s_pEngine = new IosUtil();
		}
		
		return s_pEngine;
	}

	void IosUtil::openIosGallery()
	{
		static_openIosGallery();
	}
	
	void IosUtil::startDownLoad(const char *strFileName, const char *strURL)
	{
		static_startDownLoad(strFileName, strURL);
	}
    
    
    void IosUtil::nativePopup(char *strText)
    {
        static_nativePopup(strText);
    }
    
    
    void IosUtil::nativePopupExit(char *strText)
    {
        static_nativePopupExit(strText);
    }
    
    
}