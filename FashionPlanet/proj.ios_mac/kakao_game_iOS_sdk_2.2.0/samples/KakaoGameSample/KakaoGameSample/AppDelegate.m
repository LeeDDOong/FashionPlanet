//
//  AppDelegate.m
//  KakaoGameSample
//
//  Created by Thomas on 2015. 9. 9..
//  Copyright (c) 2015년 Kakao. All rights reserved.
//

#import "AppDelegate.h"
#import <KakaoGameSDK/KakaoGameSDK.h>

@interface AppDelegate ()

@property (nonatomic, strong) UINavigationController *loginViewController;
@property (nonatomic, strong) UINavigationController *mainViewController;

@end

@implementation AppDelegate

- (void)setupEntryController {
    UIStoryboard *storyBoard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    self.loginViewController = [storyBoard instantiateViewControllerWithIdentifier:@"navigator"];
    self.mainViewController = [storyBoard instantiateViewControllerWithIdentifier:@"navigator"];

    UIViewController *viewController = [storyBoard instantiateViewControllerWithIdentifier:@"login"];
    [self.loginViewController pushViewController:viewController animated:YES];

    UIViewController *viewController2 = [storyBoard instantiateViewControllerWithIdentifier:@"main"];
    [self.mainViewController pushViewController:viewController2 animated:YES];
}

- (void)reloadRootViewController {
    BOOL isOpened = [KOSession sharedSession].isOpen;

    if (!isOpened) {
        [self.mainViewController popToRootViewControllerAnimated:YES];
    }

    self.window.rootViewController = isOpened ? self.mainViewController : self.loginViewController;
    [self.window makeKeyAndVisible];
}

- (void)setupPushNotification {
    UIApplication *sharedApplication = [UIApplication sharedApplication];
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0f) {
        [sharedApplication registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:(UIUserNotificationTypeBadge | UIRemoteNotificationTypeSound | UIUserNotificationTypeAlert) categories:nil]];
        [sharedApplication registerForRemoteNotifications];
    } else {
        [sharedApplication registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
    }
}

- (void)setTableViewSelectedBackgroundViewColor {
    UIView *colorView = [[UIView alloc] init];
    colorView.backgroundColor = [UIColor colorWithRed:0xff / 255.0 green:0xcc / 255.0 blue:0x00 / 255.0 alpha:1.0];
    [UITableViewCell appearance].selectedBackgroundView = colorView;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.

    [self setupEntryController];
    [self setupPushNotification];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(kakaoSessionDidChangeWithNotification)
                                                 name:KOSessionDidChangeNotification
                                               object:nil];

    [self reloadRootViewController];
    [self setTableViewSelectedBackgroundViewColor];

    KOSession *session = [KOSession sharedSession];
    session.presentedViewBarTintColor = [UIColor colorWithRed:0x2a / 255.0 green:0x2a / 255.0 blue:0x2a / 255.0 alpha:1.0];
    session.presentedViewBarButtonTintColor = [UIColor colorWithRed:0xe5 / 255.0 green:0xe5 / 255.0 blue:0xe5 / 255.0 alpha:1.0];

    return YES;
}

- (void)kakaoSessionDidChangeWithNotification {
    [self reloadRootViewController];
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    if ([KOSession isKakaoAccountLoginCallback:url]) {
        return [KOSession handleOpenURL:url];
    }
    return NO;
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    if ([KOSession isKakaoAccountLoginCallback:url]) {
        return [KOSession handleOpenURL:url];
    }
    return NO;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.

    [KOSession handleDidEnterBackground];
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.

    [KOSession handleDidBecomeActive];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    NSCharacterSet *characterSet = [NSCharacterSet characterSetWithCharactersInString:@"<>"];
    self.deviceToken = [[deviceToken.description stringByTrimmingCharactersInSet:characterSet] stringByReplacingOccurrencesOfString:@" " withString:@""];

    NSLog(@"[INFO] Device Token for Push Notification: %@", self.deviceToken);
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    NSLog(@"[WARN] Failed to get the device token from APNS: %@", error);
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Push 수신"
                                                    message:[userInfo description]
                                                   delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];

    [alert show];
}

@end
