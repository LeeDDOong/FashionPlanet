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

#import "FriendsViewController.h"
#import "ThumbnailImageViewCell.h"
#import "UIAlertView+Addition.h"
#import "UIImageView+WebCache.h"
#import <KakaoGameSDK/KakaoGameSDK.h>

typedef NS_ENUM (NSInteger, FriendOptionType) {
    FriendOptionTypeTalkRegistered = 1,
    FriendOptionTypeTalkInvitable = 2,
    FriendOptionTypeRecommendedInvitable = 3
};

@interface FriendsViewController() <UITableViewDataSource, UITableViewDelegate, UIAlertViewDelegate, UISearchBarDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet UISearchBar *searchBar;

@end

@implementation FriendsViewController {
    NSInteger _limitCount;

    RegisteredFriendContext *_registeredFriendContext;
    InvitableFriendContext *_invitableFriendContext;
    NSMutableArray *_allFriends;
    NSMutableArray *_filteredFriends;

    BOOL _requesting;
    FriendOptionType _optionType;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    _limitCount = 200;
    _allFriends = [NSMutableArray array];
    _filteredFriends = [NSMutableArray array];
    _optionType = FriendOptionTypeTalkRegistered;

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
        case FriendOptionTypeTalkRegistered:
            _registeredFriendContext = [RegisteredFriendContext contextWithLimit:_limitCount];
            break;
        case FriendOptionTypeTalkInvitable:
            _invitableFriendContext = [InvitableFriendContext contextWithLimit:_limitCount];
            break;
        case FriendOptionTypeRecommendedInvitable:
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
        case FriendOptionTypeTalkRegistered:
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
        case FriendOptionTypeTalkInvitable:
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
        case FriendOptionTypeRecommendedInvitable:
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
    [[[UIAlertView alloc] initWithTitle:@""
                                message:@"Options?"
                               delegate:self
                      cancelButtonTitle:@"Cancel"
                      otherButtonTitles:@"Talk (Registered)", @"Talk (Invitable)", @"Recommended (Invitable)", nil] show];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == alertView.cancelButtonIndex) {
        return;
    }

    _optionType = (FriendOptionType) buttonIndex;
    [_allFriends removeAllObjects];
    [self.tableView reloadData];

    [self setupFriendContext];
    [self requestTalkFriends];
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
    KOFriend *friend = friends[indexPath.row];

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
    [self showFriendInfo:friends[indexPath.row]];
}

- (void)showFriendInfo:(KOFriend *)friend {
    if (!friend) {
        return;
    }

    NSMutableString *message = [NSMutableString stringWithFormat:@"id:%@\nappRegistered:%@\nnickname:%@\nos:%@\nallowedTalkMessaging:%@\nrelations:",
                                                                 friend.ID, (friend.appRegistered ? @"YES" : @"NO"), friend.nickName ,convertOSPropertyTypeString(friend.talkOS),
                                                                 (friend.allowedTalkMessaging ? @"YES" : @"NO")];

    if (friend.talkRelation == KORelationValueFriend) {
        [message appendString:@" talk"];
    }
    if (friend.storyRelation == KORelationValueFriend) {
        [message appendString:@" story"];
    }

    [UIAlertView showMessage:message];
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

@end
