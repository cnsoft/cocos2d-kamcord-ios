//
//  KCShareView.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/26/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Kamcord.h"
#import "KCViewController.h"
@class KC_BaseView;

@class KCVideo;

@interface KCShareView : KCViewController <KCShareDelegate, UITextViewDelegate>

- (id)initWithVideo:(KCVideo *)video;
- (void)dealloc;
- (void)dismissView;
- (void)setParentTabViewController:(KC_BaseView *)parentViewController;

@end
