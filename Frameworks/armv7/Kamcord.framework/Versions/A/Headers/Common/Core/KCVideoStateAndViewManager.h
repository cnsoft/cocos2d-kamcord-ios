//
//  KCVideoStateAndViewManager.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 7/13/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "KCVideoProcessingAndShareManager.h"

@class KCUI;

@interface KCVideoStateAndViewManager : NSObject<KCVideoProcessDelegate>

// Everything we need before we put the job on the share queues
@property (nonatomic, retain) KCUI * preUploadManager;

@property (nonatomic, assign) UIViewController * parentViewController;

// Audio background
@property (nonatomic, retain) KCAudio * audioBackground;

// Video properties
@property (nonatomic, assign) CGSize        dimensions;
@property (nonatomic, assign) NSUInteger    bitrate;
@property (nonatomic, assign) float         targetFPS;

- (id)init;

- (void)showView;
- (BOOL)safelyCleanupLatestVideo;

// Video
- (BOOL)beginVideoForce:(BOOL)force;
- (BOOL)endVideo;

- (BOOL)endVideoAndDiscardVideo;
- (BOOL)endVideoWithSounds:(NSArray *)sounds;

- (BOOL)startRecording;
- (BOOL)stopRecording;
- (BOOL)pause;
- (BOOL)resume;

// Sound
- (KCAudio *)playAudioWithName:(NSString *)name
                     extension:(NSString *)extension
                          loop:(BOOL)loop;

- (void)stopAllSounds:(BOOL)loop;

// Uploading status
- (BOOL)isUploadingInBackground;

- (void)dealloc;


@end
