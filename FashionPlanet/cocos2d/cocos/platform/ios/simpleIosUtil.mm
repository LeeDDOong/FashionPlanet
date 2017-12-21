//
//  simpleIosUtil.mm
//  Chef
//
//
#include "platform/ios/simpleIosUtil.h"
#include "Global.h"

@implementation SimpleIosUtil

@synthesize downdelegate;
@synthesize activeDownload;
@synthesize fileConnection;
@synthesize state,totalSize,nowSize,errCnt,errCntMax;

NSString *SaveFileName = nil;
int iDownNum = 0;


static SimpleIosUtil *sharedIosUtil = nil;
 UIImagePickerController *imagePicker;

// Init
+ (SimpleIosUtil *) sharedEngine
{
	if (!sharedIosUtil)
		sharedIosUtil = [SimpleIosUtil alloc];
    
    return sharedIosUtil;
}

- (void)openIosGallery
{

	imagePicker = [[UIImagePickerController alloc] init];
		
	imagePicker.allowsEditing = YES;
	imagePicker.delegate = self;
	
	[imagePicker.view setFrame:CGRectMake(0, 0,orilcdW/2, orilcdH/2)];
		
	imagePicker.sourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
	

	[cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView() addSubview:imagePicker.view];
}

//사진취소
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {

	xWorldMap.state = WORLDMAP_STATE_PLAY;
	[[picker parentViewController] dismissModalViewControllerAnimated:YES];
	[picker.view removeFromSuperview];
	[picker release];
}

//사진성공
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LJW AWS S3 2016.05.24
- (void)imagePickerController:(UIImagePickerController *)picker
didFinishPickingMediaWithInfo:(NSDictionary *)info {
    
    
    UIImage *image = [info objectForKey:UIImagePickerControllerEditedImage];
    NSString *	cachePath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *	pnsFileName	= [ cachePath stringByAppendingPathComponent: @"profileupload.chs" ];
    
    
    
    CGSize cgSize;
    cgSize.width = 100;
    cgSize.height = 100;
    
    UIGraphicsBeginImageContext(cgSize);
    [image drawInRect:CGRectMake(0, 0, cgSize.width, cgSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    NSData *p_data = [NSData dataWithData : UIImagePNGRepresentation(newImage)] ;
    
    
    if(p_data.length>209600)
    {
        
    }
    else
    {
        BOOL flag;
        flag = [p_data writeToFile:pnsFileName options:NSDataWritingFileProtectionComplete error:nil];
        

        
        if (flag)
        {
            NSLog(@"openGallery saving Suceess!!!");
            [p_data getBytes:openGalleryBuf];
            xEventQueueNet.imgBufSize[xEventQueueNet.totalNum] = [p_data length];
            
            for(int i = 0; i < [p_data length]; i++)
                xEventQueueNet.imgBuf[i] = openGalleryBuf[i];
            
            addEventQueueNet(xTouch.xPos, xTouch.yPos, NETQUEUE_TYPE_PROFILEPHOTOUPLOAD, FALSE);
            
            
        }
        else
        {
            NSLog(@"openGallery saving Failed!!!");
        }
    }
    
    [[picker parentViewController] dismissModalViewControllerAnimated:YES];
    [picker.view removeFromSuperview];
    [picker release];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//다운로드 URL과 저장할 파일이름
- (void)startDownload:(NSString *)strFileName:(NSString *)strURL
{
	//NSLog(strURL);
	
	errCnt = 0;
	errCntMax = 3000;
	
	xDownLoader.state = DOWNLOADER_STATE_ING;
	SaveFileName = [[NSString alloc] initWithFormat:strFileName];
    self.activeDownload = [NSMutableData data];
    // alloc+init and start an NSURLConnection; release on completion/failure
    NSURLConnection *conn = [[NSURLConnection alloc] initWithRequest:
                             [NSURLRequest requestWithURL:
                              [NSURL URLWithString:strURL]] delegate:self];
    self.fileConnection = conn;
	
	[conn release];
}

- (void)cancelDownload
{
	
	[self.fileConnection cancel];
	self.fileConnection = nil;
	self.activeDownload = nil;
	
}


#pragma mark -
#pragma mark Download support (NSURLConnectionDelegate)

-(void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
	//파일 총 사이즈
	totalSize = [[NSNumber numberWithLongLong:[response expectedContentLength]]longValue];
	//NSLog(@"Total_Size = %ld bytes",totalSize);
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [self.activeDownload appendData:data];
	
	//다운 받은 파일의 용량을 보여준다.
	NSNumber *ResPoneLength = [NSNumber numberWithUnsignedInteger:[self.activeDownload length]];
	//NSLog(@"DownSize = %ld", [ResPoneLength longValue]);
	
	//다운로드 된 데이터 용량
	nowSize = [ResPoneLength floatValue];
	//NSLog(@"Down : %f",nowSize / totalSize);
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
	
	// Clear the activeDownload property to allow later attempts
    self.activeDownload = nil;
    
    // Release the connection now that it's finished
    self.fileConnection = nil;
	//NSLog(@"다운로드 Err");
	xDownLoader.state = DOWNLOADER_STATE_ERR;
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    
    if(SaveFileName == nil)
    {
        xDownLoader.state = DOWNLOADER_STATE_ERR;
        return;
    }
    
    
	NSString *	cachePath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	NSString *	pnsFileName	= [ NSString stringWithFormat : SaveFileName ];
	NSString *	pnsFilePath	= [ cachePath stringByAppendingPathComponent:pnsFileName ];
    
	
	[self.activeDownload writeToFile:pnsFilePath atomically:NO];
    
    
    self.activeDownload = nil;
	[SaveFileName release];
	SaveFileName = nil;
    
    /*
    if(totalSize < 1300)
        printf("totalSize>>%d\n",totalSize);
    */
    
   
    /*
    if(totalSize < 1300)
        xDownLoader.state = DOWNLOADER_STATE_ERR;
    else
     */
    xDownLoader.state = DOWNLOADER_STATE_SUCCESS;
}








- (void)nativePopup:(NSString*) strText

{
    UIAlertView *alert;
    alert = [[UIAlertView alloc] initWithTitle:@"알림"
                                       message:strText
                                      delegate:self
                             cancelButtonTitle:@"확인"
                             otherButtonTitles:nil, nil];
    
    alert.tag = 0;
    
    
    [alert show];
    [alert release];
}


- (void)nativePopupExit:(NSString*) strText

{
    UIAlertView *alert;
    alert = [[UIAlertView alloc] initWithTitle:@"알림"
                                       message:strText
                                      delegate:self
                             cancelButtonTitle:@"확인"
                             otherButtonTitles:nil, nil];
    
    alert.tag = 1;
    
    
    [alert show];
    [alert release];
}


- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    switch(alertView.tag)
    {
    case 0:
        break;
    case 1:
        exit(0);
        break;
    }
}

@end
