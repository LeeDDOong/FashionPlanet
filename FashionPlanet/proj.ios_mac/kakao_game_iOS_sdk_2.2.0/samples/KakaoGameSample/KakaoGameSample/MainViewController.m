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

#import "MainViewController.h"
#import "IconTableViewCell.h"
#import "MainViewTableViewCell.h"
#import "UIAlertView+Addition.h"
#import <KakaoGameSDK/KakaoGameSDK.h>

@interface MainViewController () <UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@end

@implementation MainViewController {
    NSArray *_apiMenus;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    _apiMenus = @[@"User API", @"Friend API", @"Friend Message API", @"Chat Message API", @"Guild API", @"Story API", @"Invitation Reward"];

    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    self.navigationItem.titleView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"img_logotitle.png"]];

    self.navigationController.navigationBar.layer.shadowColor = [[UIColor blackColor] CGColor];
    self.navigationController.navigationBar.layer.shadowOffset = CGSizeMake(0.0f,0.0f);
    self.navigationController.navigationBar.layer.shadowOpacity = 0.24f;
    self.navigationController.navigationBar.layer.shadowRadius = 12.0f;

    [self requestMe:NO];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)logoutClicked:(id)sender {
    __weak MainViewController *wself = self;
    [KakaoGameAPI logoutAndCloseWithCompletionHandler:^(BOOL success, NSError *error) {
        [wself.navigationController popViewControllerAnimated:YES];
    }];

}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _apiMenus.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    MainViewTableViewCell *cell = (MainViewTableViewCell *) [tableView dequeueReusableCellWithIdentifier:@"MainViewTableViewCell"];
    if (cell == nil) {
        [tableView registerNib:[UINib nibWithNibName:@"MainViewTableViewCell" bundle:nil] forCellReuseIdentifier:@"mainCell"];
        cell = (MainViewTableViewCell *) [tableView dequeueReusableCellWithIdentifier:@"mainCell"];
    }
    
    cell.thumbnailImageView.image = [UIImage imageNamed:[NSString stringWithFormat:@"ic_0%d", (int) indexPath.row]];
    cell.menuLabelView.text = _apiMenus[(NSUInteger) indexPath.row];

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self performSegueWithIdentifier:[NSString stringWithFormat:@"%@", _apiMenus[(NSUInteger) indexPath.row]]
                              sender:nil];
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    UIViewController *viewController = segue.destinationViewController;
    viewController.title = sender;
}

- (void)requestMe:(BOOL)displayResult {
    [KakaoGameAPI meTaskWithCompletionHandler:^(id result, NSError *error) {
        if (error) {
            [KakaoGameAPI signUpTaskWithProperties:nil completionHandler:^(BOOL success, NSError *error) {
                if (error) {
                    [self.navigationController popViewControllerAnimated:YES];
                } else {
                    [self requestMe:NO];
                }
            }];
        } else {
            if (displayResult) {
                [UIAlertView showMessage:[result description]];
            }
        }
    }];
}

@end
