//
//  KC_BaseView.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/18/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Kamcord.h"
#import "KCVideo.h"
#import "KCVideoProcessingAndShareManager.h"

@interface KC_BaseView : UINavigationController {
    CGRect frame_;
}

- (id)initMainViewWithFrame:(CGRect)frame isDark:(BOOL)isDark;

@property (nonatomic, readonly) BOOL isDark; 

@property (nonatomic, retain) KCVideo *latestVideo;
@property (nonatomic, retain) KCVideoProcessingAndShareManager *shareManager;
@end
