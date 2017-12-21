//
// Created by house.dr on 2015. 9. 22..
// Copyright (c) 2015 Kakao. All rights reserved.
//

#import <KakaoGameSDK/KakaoGameSDK.h>
#import "GuildMainViewController.h"
#import "UIAlertView+Addition.h"


@interface GuildMainViewController () <UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@end


@implementation GuildMainViewController {
    NSArray *_apiMenus;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];

    self.title = @"Guild";

    _apiMenus = @[@"Send Guild Message", @"Join Guild Chat"];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _apiMenus.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *guildMenuCell = [tableView dequeueReusableCellWithIdentifier:@"GuildTableViewCell"];
    if (guildMenuCell == nil) {
        guildMenuCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"GuildTableViewCell"];
    }

    guildMenuCell.textLabel.text = _apiMenus[(NSUInteger) indexPath.row];
    return guildMenuCell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    switch (indexPath.row) {
        case 0: {

            [KakaoGameAPI sendGuildMessageWithWorldId:@"1lG" guildId:@"150" templateId:@"4" messageArguments:@{@"sender_name" : @"iOS tester"} completionHandler:^(BOOL success, NSError *error) {
                if (error) {
                    [UIAlertView showMessage:[NSString stringWithFormat:@"message send failed = %@", error]];
                } else {
                    [UIAlertView showMessage:@"Success Send Guild Message"];
                }
            }];
        }
            break;
        case 1: {
            [KakaoGameAPI joinGuildChatWithWorldId:@"1YX" guildId:@"1P6"];
        }
            break;
        default:break;
    }
}

@end