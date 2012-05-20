//
//  KCManager.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/5/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "../Platforms/CCGL.h"

// For recording video
#import "KCVideoReplayCreator.h"

enum LastVideoStatus
{
    NOT_READY,
    READY_FOR_SHOWING,
    VIDEO_IS_ON_YOUTUBE,
};

@interface KCManager : NSObject <KCVideoWriterDelegate>

////////////////////////////////////////////////
// Public properties
@property (nonatomic, assign) UIViewController * parentViewController;
@property (nonatomic, assign) CC_GLVIEW * openGLView;

// Kamcord developer key and secret
@property (nonatomic, retain) NSString * developerKey;
@property (nonatomic, retain) NSString * developerSecret;

// Game properties
@property (nonatomic, retain) NSString * level;
@property (nonatomic, retain) NSNumber * score;

// YouTube
@property (nonatomic, retain) NSString * youtubeTitle;
@property (nonatomic, retain) NSString * youtubeDescription;
@property (nonatomic, retain) NSString * youtubeKeywords;

// Facebook
@property (nonatomic, retain) NSString * facebookTitle;
@property (nonatomic, retain) NSString * facebookCaption;
@property (nonatomic, retain) NSString * facebookDescription;


////////////////////////////////////////////////
// Public methods

+ (KCManager *)sharedManager;

- (BOOL) beginVideo;
- (BOOL) endVideo;
- (BOOL) startRecordingClip;
- (BOOL) stopRecordingClip;

// Displays the Kamcord view inside the previously set parentViewController;
- (void) showKamcordView;

@end
