/**
 * Copyright 2015 Daum Kakao Corp.
 *
 * Redistribution and modification in source or binary forms are not permitted without specific prior written permission.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "MessageViewController.h"
#import "ThumbnailImageViewCell.h"
#import "UIAlertView+Addition.h"
#import "UIImageView+WebCache.h"
#import <KakaoGameSDK/KakaoGameSDK.h>
#import <KakaoGameSDK/KGExtendedFriend.h>

typedef NS_ENUM (NSInteger, TalkFriendOptionType) {
    TalkFriendOptionTypeRegistered = 1,
    TalkFriendOptionTypeInvitable = 2,
    RecommendedFriendOptionTypeInvitable = 3
};

@interface MessageViewController () <UITableViewDataSource, UITableViewDelegate, UIAlertViewDelegate, UISearchBarDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet UISearchBar *searchBar;

@end

@implementation MessageViewController {
    NSInteger _limitCount;

    RegisteredFriendContext *_registeredFriendContext;
    InvitableFriendContext *_invitableFriendContext;
    NSMutableArray *_allFriends;
    NSMutableArray *_filteredFriends;
    
    BOOL _requesting;
    TalkFriendOptionType _optionType;
    KGExtendedFriend *_selectedFriend;

    NSString *templateMessage;
    NSString *ImageMessage;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _limitCount = 200;
    _allFriends = [NSMutableArray array];
    _filteredFriends = [NSMutableArray array];
    _optionType = TalkFriendOptionTypeRegistered;

    templateMessage = @"Template Message";
    ImageMessage = @"Image Message";
    
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    self.tableView.tableFooterView = [[UIView alloc] init];
    self.tableView.tableHeaderView = self.searchBar;
    
    self.searchBar.delegate = self;
    self.searchDisplayController.searchResultsTableView.tableFooterView = [[UIView alloc] init];
    
    [self setupFriendContext];
    [self requestTalkFriends];
}

- (void)setupFriendContext {
    switch (_optionType) {
        case TalkFriendOptionTypeRegistered:
            _registeredFriendContext = [RegisteredFriendContext contextWithLimit:_limitCount];
            break;
        case TalkFriendOptionTypeInvitable:
            _invitableFriendContext = [InvitableFriendContext contextWithLimit:_limitCount];
            break;
        case RecommendedFriendOptionTypeInvitable:
            _invitableFriendContext = [InvitableFriendContext contextWithLimit:_limitCount];
            break;
        default:
            _registeredFriendContext = nil;
            _invitableFriendContext = nil;
            break;
    }
}

- (void)requestTalkFriends {
    if (_requesting) {
        return;
    }

    switch (_optionType) {
        case TalkFriendOptionTypeRegistered:
            if (_registeredFriendContext.hasMoreItems) {
                _requesting = YES;

                [KakaoGameAPI registeredFriendsWithContext:_registeredFriendContext completionHandler:^(NSArray *friends, NSError *error) {
                    if (error) {
                        NSLog(@"friends error = %@", error);
                        if (error.code == KOErrorCancelled) {
                            [self.navigationController popViewControllerAnimated:YES];
                        }
                    } else {
                        self.title = [NSString stringWithFormat:@"Friends (%@)", _registeredFriendContext.totalCount];
                        [_allFriends addObjectsFromArray:friends];
                        [self.tableView reloadData];
                    }

                    _requesting = NO;
                }];
            }
            break;
        case TalkFriendOptionTypeInvitable:
            if (_invitableFriendContext.hasMoreItems) {
                _requesting = YES;

                [KakaoGameAPI invitableFriendsWithLimit:_invitableFriendContext completionHandler:^(NSArray *friends, NSError *error) {
                    if (error) {
                        NSLog(@"friends error = %@", error);
                        if (error.code == KOErrorCancelled) {
                            [self.navigationController popViewControllerAnimated:YES];
                        }
                    } else {
                        self.title = [NSString stringWithFormat:@"Friends (%@)", _invitableFriendContext.totalCount];
                        [_allFriends addObjectsFromArray:friends];
                        [self.tableView reloadData];
                    }

                    _requesting = NO;
                }];
            }
            break;
        case RecommendedFriendOptionTypeInvitable:
            if (_invitableFriendContext.hasMoreItems) {
                _requesting = YES;

                [KakaoGameAPI recommendedInvitableFriendsWithLimit:_invitableFriendContext completionHandler:^(NSArray *friends, NSError *error) {
                    if (error) {
                        NSLog(@"friends error = %@", error);
                        if (error.code == KOErrorCancelled) {
                            [self.navigationController popViewControllerAnimated:YES];
                        }
                    } else {
                        self.title = [NSString stringWithFormat:@"Friends (%@)", _invitableFriendContext.totalCount];
                        [_allFriends addObjectsFromArray:friends];
                        [self.tableView reloadData];
                    }

                    _requesting = NO;
                }];
            }
            break;
        default:
            break;
    }
}

- (IBAction)selectOptions:(id)sender {
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@""
                                                        message:@"Options?"
                                                       delegate:self
                                              cancelButtonTitle:@"Cancel"
                                              otherButtonTitles:@"App Registered",@"Invitable, Not App Registered", @"Recommended (Invitable)", nil];
    alertView.tag = 1;
    [alertView show];
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (buttonIndex == alertView.cancelButtonIndex) {
        return;
    }
    if (alertView.tag == 1) {
        _optionType = (TalkFriendOptionType) buttonIndex;
        [_allFriends removeAllObjects];
        [self.tableView reloadData];

        [self setupFriendContext];
        [self requestTalkFriends];
    } else if (alertView.tag == 2) {
        NSString *title = [alertView buttonTitleAtIndex:buttonIndex];
        if ([title isEqualToString:ImageMessage]) {
            [self sendImageMessage];
        } else {
            [self sendTemplateMessage];
        }
    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 52;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (tableView == self.searchDisplayController.searchResultsTableView) {
        return _filteredFriends.count;
    }
    
    return _allFriends.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    ThumbnailImageViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell"];
    if (cell == nil) {
        cell = [[ThumbnailImageViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"Cell"];
    }
    
    NSArray *friends = (tableView == self.searchDisplayController.searchResultsTableView ? _filteredFriends : _allFriends);
    KOFriend *friend = friends[(NSUInteger) indexPath.row];
    
    cell.textLabel.text = friend.nickName;
    [cell.imageView sd_setImageWithURL:[NSURL URLWithString:friend.thumbnailURL]
                      placeholderImage:[UIImage imageNamed:@"PlaceHolder"]];
    
    if (tableView == self.tableView) {
        NSInteger count = friends.count;
        if (indexPath.row > (count - count / 3)) {
            [self requestTalkFriends];
        }
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    NSArray *friends = (tableView == self.searchDisplayController.searchResultsTableView ? _filteredFriends : _allFriends);
    _selectedFriend = friends[(NSUInteger) indexPath.row];

    UIAlertView *alertView;
    if(_selectedFriend.appRegistered) {
        alertView = [[UIAlertView alloc] initWithTitle:@"" message:@"Send Message?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:templateMessage, ImageMessage, nil];
    } else {
        alertView = [[UIAlertView alloc] initWithTitle:@"" message:@"Send Message?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
    }
    alertView.tag = 2;
    [alertView show];
}

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText {
    [_filteredFriends removeAllObjects];
    
    if (searchText.length == 0) {
        return;
    }
    
    for (KOFriend *friend in _allFriends) {
        if ([friend.nickName rangeOfString:searchText options:NSCaseInsensitiveSearch].location != NSNotFound) {
            [_filteredFriends addObject:friend];
        }
    }
    
    [self.tableView reloadData];
}

- (void)sendTemplateMessage {
    if (_selectedFriend == nil) {
        return;
    }
    
    KGExtendedFriend *friend = _selectedFriend;
    _selectedFriend = nil;
    
    if (!friend.allowedTalkMessaging) {
        [UIAlertView showMessage:@"friend set message blocked."];
        return;
    }
    if (_optionType == TalkFriendOptionTypeRegistered) {
        NSString *templateID = @"4";  // feed template message id
        [KakaoGameAPI sendGameMessageTaskWithTemplateID:templateID
                                         receiverFriend:friend
                                       messageArguments:@{@"name" : friend.nickName, @"iphoneMarketParam" : @"test", @"iphoneExecParam" : @"test", @"sender_name" : @"iOS tester"}
                                      completionHandler:^(NSError *error) {
                                          if (error) {
                                              if (error.code != KOErrorOperationInProgress) {
                                                  [UIAlertView showMessage:[NSString stringWithFormat:@"message send failed = %@", error]];
                                              }
                                          } else {
                                              [UIAlertView showMessage:@"message send succeed."];
                                          }
                                      }];
    } else if (_optionType == TalkFriendOptionTypeInvitable) {
        NSString *templateID = @"6";  // invite template message id
        [KakaoGameAPI sendInviteMessageTaskWithTemplateID:templateID
                                           receiverFriend:friend
                                         messageArguments:@{@"msg" : @"새로운 연결, 새로운 세상.", @"iphoneMarketParam" : @"test", @"iphoneExecParam" : @"test", @"sender_name" : @"iOS tester"}
                                        completionHandler:^(NSError *error) {
                                            if (error) {
                                                if (error.code != KOErrorOperationInProgress) {
                                                    [UIAlertView showMessage:[NSString stringWithFormat:@"message send failed = %@", error]];
                                                }
                                            } else {
                                                [UIAlertView showMessage:@"message send succeed."];
                                            }
                                        }];
    } else if (_optionType == RecommendedFriendOptionTypeInvitable) {
        NSString *templateID = @"6";  // invite template message id
        [KakaoGameAPI sendRecommendedInviteMessageTaskWithTemplateID:templateID
                                                      receiverFriend:friend
                                                    messageArguments:@{@"msg" : @"새로운 연결, 새로운 세상.", @"iphoneMarketParam" : @"test", @"iphoneExecParam" : @"test", @"sender_name" : @"iOS tester"}
                                                   completionHandler:^(NSError *error) {
                                                       if (error) {
                                                           if (error.code != KOErrorOperationInProgress) {
                                                               [UIAlertView showMessage:[NSString stringWithFormat:@"message send failed = %@", error]];
                                                           }
                                                       } else {
                                                           [UIAlertView showMessage:@"message send succeed."];
                                                       }
                                                   }];
    }
}

- (void)sendImageMessage {
    if (_selectedFriend == nil) {
        return;
    }

    KOFriend *friend = _selectedFriend;
    _selectedFriend = nil;

    if (!friend.allowedTalkMessaging) {
        [UIAlertView showMessage:@"friend set message blocked."];
        return;
    }

    if (_optionType == TalkFriendOptionTypeRegistered) {
        NSString *templateID = @"7";
        [KakaoGameAPI sendImageMessageTaskWithTemplateID:templateID
                                          receiverFriend:friend
                                        messageArguments:@{@"name" : friend.nickName, @"iphoneMarketParam" : @"test", @"iphoneExecParam" : @"test", @"sender_name" : @"iOS tester"}
                                                   image:[self getScreenShot]
                                       completionHandler:^(NSError *error) {
                                           if (error) {
                                               if (error.code != KOErrorOperationInProgress) {
                                                   [UIAlertView showMessage:[NSString stringWithFormat:@"message send failed = %@", error]];
                                               }
                                           } else {
                                               [UIAlertView showMessage:@"message send succeed."];
                                           }
                                       }];
    }
}

-(UIImage*)getScreenShot {
    UIWindow *keyWindow = [[UIApplication sharedApplication] keyWindow];
    CGRect rect = [keyWindow bounds];
    UIGraphicsBeginImageContextWithOptions(rect.size,YES,0.0f);
    CGContextRef context = UIGraphicsGetCurrentContext();
    [keyWindow.layer renderInContext:context];
    UIImage *capturedScreen = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return capturedScreen;
}

@end
