//
//  KC_iPhoneView.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/21/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KC_BaseView.h"
#import "KCViewController.h"
@interface KC_iPhoneViewLandscape : KCViewController

@property (retain, nonatomic) KC_BaseView *parent;
@property (assign, nonatomic) CGRect myFrame;

-(id)initWithParent:(KC_BaseView *)parent frame:(CGRect)frame;

@end
