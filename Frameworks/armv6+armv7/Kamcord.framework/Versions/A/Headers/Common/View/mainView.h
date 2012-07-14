//
//  KC_iPhoneView.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/26/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Kamcord.h"
#import "KCViewController.h"
#import "KC_BaseView.h"
#import "KC_ShareMessageDelegate.h"

@interface MainView : KCViewController <KC_ShareMessageDelegate, KCShareDelegate>

@property (retain, nonatomic) KC_BaseView *parent;
@property (assign, nonatomic) CGRect myFrame;

- (id)initWithParent:(KC_BaseView *)parent frame:(CGRect)frame;
- (void)dealloc;

@end
