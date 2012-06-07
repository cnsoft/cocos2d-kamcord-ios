//
//  KCViewController.h
//  KamcordUI
//
//  Created by Kevin Wang on 5/9/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KCViewController.h"

@class KCVideo;
@class KCVideoProcessingAndShareManager;

@interface KCMainMenuViewController : KCViewController

@property (nonatomic, retain) KCVideo * latestVideo;
@property (nonatomic, retain) KCVideoProcessingAndShareManager * shareManager;

- (void) dealloc;

@end
