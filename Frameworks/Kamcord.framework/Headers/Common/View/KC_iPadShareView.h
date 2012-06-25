//
//  KCExperimentalView2.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/18/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KCViewController.h"

@class KC_BaseView, HintTextView;

@interface KC_iPadShareView : KCViewController <UITextViewDelegate> {
    KC_BaseView *parent_; 
}
@property (retain, nonatomic) UITapGestureRecognizer *rec;
@property (retain, nonatomic) HintTextView *message;
- (id) initWithTitle:(NSString *)title parent:(KC_BaseView *)parent;

@end
