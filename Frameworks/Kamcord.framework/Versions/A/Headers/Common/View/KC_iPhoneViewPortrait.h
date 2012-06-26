//
//  KC_iPhoneViewPortrait.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/23/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KC_BaseView.h"
#import "KCViewController.h"
#import "KC_ShareMessageDelegate.h"

@interface KC_iPhoneViewPortrait : KCViewController <KC_ShareMessageDelegate>

@property (retain, nonatomic) KC_BaseView *parent; 
@property (assign, nonatomic) CGRect myFrame;

-(id) initWithParent:(KC_BaseView *)parent frame:(CGRect)frame;

@end
