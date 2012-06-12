//
//  KCShareManager.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/29/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

#import "KCVideo.h"

// Forward class declarations
@class KCVideoProcessor;
@class KCShareHandler;

// Handles when a video is merged or convered
@protocol KCVideoProcessDelegate <NSObject>

- (void) mergeFinished:(KCVideo *)video;
- (void) conversionFinished:(KCVideo *)video;

@end


// Handles when a video is finished uploading and sharing
@protocol KCShareFinishedDelegate <NSObject>

- (void) shareFinished:(KCVideo *)video
                 error:(NSError *)error;

@end

typedef enum
{
    KC_MERGE_VIDEO,
    KC_CONVERT_VIDEO
} KC_VIDEO_PROCESS_TYPE;

// An object needed to merge/convert a video
@interface KCVideoProcessingTask : NSObject

@property (nonatomic, retain) KCVideo * video;
@property (nonatomic, retain) id <KCVideoProcessDelegate> delegate;
@property (nonatomic, retain) KCVideoProcessor * taskHandler;
@property (nonatomic, assign) KC_VIDEO_PROCESS_TYPE type;

- (id) initWithVideo:(KCVideo *)video
            delegate:(id <KCVideoProcessDelegate>)delegate
                type:(KC_VIDEO_PROCESS_TYPE)processType;
- (void) dealloc;

@end

// An object needed to upload and share a video
@interface KCVideoSharingTask : NSObject

@property (nonatomic, retain) KCVideo * video;
@property (nonatomic, retain) KCVideoShareInfo * info;
@property (nonatomic, retain) id <KCShareFinishedDelegate> delegate;
@property (nonatomic, retain) KCShareHandler * taskHandler;

- (id) initWithVideo:(KCVideo *)video
                info:(KCVideoShareInfo *)shareInfo
            delegate:(id <KCShareFinishedDelegate>)delegate;

- (void) dealloc;

@end


///////////////////////////////////////////////////////////////
// Handles video conversion and merging
@interface KCVideoProcessingAndShareManager : NSObject

// Are we currently merging, converting, or uploading/sharing?
@property (nonatomic, readonly) BOOL isActive;

-(id) init;

// Own custom video process callback
- (void)mergeFinished:(KCVideoProcessingTask *)obj;
- (void)conversionFinished:(KCVideoProcessingTask *)obj;
- (void)shareFinished:(KCVideoSharingTask *)task
                error:(NSError *)error;

- (void)resumeTasks;

// Puts a job on the worker queue. Returns immediately and calls
// back to the delegates when finished.
- (void)mergeVideo:(KCVideo *)video
          delegate:(id <KCVideoProcessDelegate>)delegate;
- (void)convertVideo:(KCVideo *)video
            delegate:(id <KCVideoProcessDelegate>)delegate;
- (void)shareVideo:(KCVideo *)video
              info:(KCVideoShareInfo *)info
          delegate:(id <KCShareFinishedDelegate>)delegate;

// Some ways to cancel tasks
- (void)safelyPerformTaskAndVideoCleanup:(KCVideo *)video;
- (void)cancelAllActiveTasksAndPause;

- (void)dealloc;

@end
