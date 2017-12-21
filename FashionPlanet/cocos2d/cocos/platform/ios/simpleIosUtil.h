//
//  iosUtil.h
//  Chef
//
//

#ifndef __PARTY_IOSUTIL__
#define __PARTY_IOSUTIL__

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import <UIKit/UIKit.h>

@protocol DownloaderDelegate;

@interface SimpleIosUtil : NSObject <UINavigationControllerDelegate,UIImagePickerControllerDelegate,NSURLConnectionDelegate,NSURLConnectionDownloadDelegate,NSURLConnectionDataDelegate>
{
	int state;
	id <DownloaderDelegate>				downdelegate;
	
	
	
	NSMutableData						*activeDownload;
	NSURLConnection						*fileConnection;
	
	int errCnt;
	int errCntMax;
	int totalSize;
	int nowSize;
}

@property (nonatomic, assign) id <DownloaderDelegate> downdelegate;

@property (nonatomic, retain) NSMutableData *activeDownload;
@property (nonatomic, retain) NSURLConnection *fileConnection;
@property int state;
@property int totalSize;
@property int nowSize;
@property int errCnt,errCntMax;


- (void)startDownload:(NSString *)strFileName:(NSString *)strURL;
- (void)cancelDownload;

+ (SimpleIosUtil*) sharedEngine;
- (void)openIosGallery;



- (void)nativePopup:(NSString*) strText;
- (void)nativePopupExit:(NSString*) strText;


@end

#endif

#endif
