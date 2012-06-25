//
//  KCExperimentalView1.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/18/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MPMoviePlayerController.h>
#import "KC_BaseView.h"
@class MPMoviePlayerController, KC_BaseView;

@interface KC_iPadView : KCViewController 
@property (retain, nonatomic) KC_BaseView *parent;
@property (assign, nonatomic) CGRect myFrame;
- (id)initWithParent:(KC_BaseView *)parent frame: (CGRect)Frame;

@end
