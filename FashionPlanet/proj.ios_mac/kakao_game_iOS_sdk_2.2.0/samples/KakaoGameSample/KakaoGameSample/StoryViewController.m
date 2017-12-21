//
// Created by house.dr on 2015. 10. 20..
// Copyright (c) 2015 Kakao. All rights reserved.
//

#import <KakaoGameSDK/KakaoGameSDK.h>
#import "StoryViewController.h"
#import "UIAlertView+Addition.h"


@interface StoryViewController() <UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@end

@implementation StoryViewController {

}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.tableView.delegate = self;
    self.tableView.dataSource = self;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *normalCell = [tableView dequeueReusableCellWithIdentifier:@"StoryViewCell"];
    if (normalCell == nil) {
        normalCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"StoryViewCell"];
    }

    normalCell.textLabel.textAlignment = NSTextAlignmentCenter;
    normalCell.textLabel.text = @"스토리 포스팅";
    return normalCell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];

    [KakaoGameAPI postStoryWithTemplateId:@"6" content:@"" completionHandler:^(BOOL success, NSError *error) {
        if (error) {
            [UIAlertView showMessage:[error description]];
        } else {
            [UIAlertView showMessage:[NSString stringWithFormat:@"Success post story"]];
        }
    }];
}


@end