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

#import "UserMgmtTableViewCell.h"
#import "InsetableTextField.h"
#import "UIImageView+WebCache.h"

@interface UserMgmtTableViewCell ()

@property (weak, nonatomic) IBOutlet InsetableTextField *name;
@property (weak, nonatomic) IBOutlet InsetableTextField *nickName;
@property (weak, nonatomic) IBOutlet InsetableTextField *level;
@property (weak, nonatomic) IBOutlet InsetableTextField *exp;

@end

@implementation UserMgmtTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    self.name.inset = self.nickName.inset = self.level.inset = self.exp.inset = 10;
}

- (void)setUser:(KOUser *)user {
    if (user == nil) {
        return;
    }
    
    NSString *imageURL = nil;
    if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPhone) {
        imageURL = user.properties[@"thumbnail_image"];
    } else {
        imageURL = user.properties[@"profile_image"];
    }

    if (!imageURL) {
        [self.thumbnail sd_setImageWithURL:[NSURL URLWithString:imageURL] placeholderImage:[UIImage imageNamed:@"PlaceHolder"]];
    }
    self.name.text = user.properties[@"unique_nickname"];
    self.nickName.text = user.properties[@"nickname"];
    self.level.text = user.properties[@"level"];
    self.exp.text = user.properties[@"exp"];
}

- (NSDictionary *)userDictionary {
    NSMutableDictionary *dictionary = [NSMutableDictionary dictionaryWithCapacity:4];
    if (self.name.text) {
        dictionary[@"unique_nickname"] = self.name.text;
    }
    if (self.nickName.text) {
        dictionary[@"nickname"] = self.nickName.text;
    }
    if (self.level.text) {
        dictionary[@"level"] = self.level.text;
    }
    if (self.exp.text) {
        dictionary[@"exp"] = self.exp.text;
    }
    return dictionary;
}

@end
