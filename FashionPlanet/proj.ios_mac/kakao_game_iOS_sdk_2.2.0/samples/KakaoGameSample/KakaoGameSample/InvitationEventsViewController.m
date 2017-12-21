//
// Created by house.dr on 2016. 3. 15..
// Copyright (c) 2016 Kakao. All rights reserved.
//

#import <KakaoGameSDK/KakaoGameSDK.h>
#import <KakaoGameSDK/KGInvitationEvent.h>
#import <KakaoGameSDK/KGInvitationState.h>
#import <KakaoGameSDK/KGInvitationSender.h>
#import "InvitationEventsViewController.h"
#import "UIAlertView+Addition.h"

@class KGInvitationEvent;

@interface InvitationEventsViewController () <UITableViewDataSource, UITableViewDelegate, UIAlertViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@end

@implementation InvitationEventsViewController {
    NSMutableArray *_invitationEvents;

    NSString *eventInfoString;
    NSString *statesString;
    NSString *senderString;

    KGInvitationEvent *selectedEvent;
}

- (void)requestInvitationEvents {
    [KakaoGameAPI invitationEventsWithCompletionHandler:^(NSArray *events, NSError *error) {
        _invitationEvents = [events mutableCopy];
        [_tableView reloadData];
    }];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    eventInfoString = @"Event Info";
    statesString = @"States";
    senderString = @"Sender";
}


- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];

    [self requestInvitationEvents];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _invitationEvents.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *normalCell = [tableView dequeueReusableCellWithIdentifier:@"InvitationRewardViewCell"];
    if (normalCell == nil) {
        normalCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"InvitationRewardViewCell"];
    }

    KGInvitationEvent *event = _invitationEvents[(NSUInteger) indexPath.row];
    normalCell.textLabel.text = [NSString stringWithFormat:@"%@ %@", event.eventId, event.startsAt];
    return normalCell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];

    selectedEvent = _invitationEvents[(NSUInteger) indexPath.row];
    UIAlertView *alertView;
    alertView = [[UIAlertView alloc] initWithTitle:@"" message:@"Choice" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:eventInfoString, statesString, senderString, nil];
    [alertView show];
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (buttonIndex == alertView.cancelButtonIndex) {
        return;
    }

    NSString *choice = [alertView buttonTitleAtIndex:buttonIndex];
    if ([choice isEqualToString:eventInfoString]) {
        [KakaoGameAPI invitationEventInfoWithId:selectedEvent.eventId CompletionHandler:^(KGInvitationEvent *eventInfo, NSError *error) {
            [UIAlertView showMessage:eventInfo.invitationUrl];
        }];

    } else if ([choice isEqualToString:statesString]) {
        [KakaoGameAPI invitationStatesWithId:selectedEvent.eventId CompletionHandler:^(NSArray *states, NSError *error) {
            for (KGInvitationState *state in states) {
                [UIAlertView showMessage:state.receiverRewardState];
            }
        }];

    } else if ([choice isEqualToString:senderString]) {
        [KakaoGameAPI invitationSenderWithId:selectedEvent.eventId CompletionHandler:^(KGInvitationSender *sender, NSError *error) {
            if (sender == nil) {
                [UIAlertView showMessage:@"sender is nil"];
            } else {
                [UIAlertView showMessage:[sender.totalReceiversCount stringValue]];
            }
        }];
    }
}

@end