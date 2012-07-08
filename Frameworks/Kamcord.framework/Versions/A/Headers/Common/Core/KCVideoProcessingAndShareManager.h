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

#import "Kamcord.h"
#import "KCVideo.h"
#import "Reachability.h"

// Forward class declarations
@class KCVideoProcessor;
@class KCShareHandler;

// Handles when a video is merged or converted
@protocol KCVideoProcessDelegate <NSObject>

- (void) mergeFinished:(KCVideo *)video;
- (void) conversionFinished:(KCVideo *)video;

@end

typedef enum
{
    KC_MERGE_VIDEO,
    KC_CONVERT_VIDEO
} KC_VIDEO_PROCESS_TYPE;

// An object needed to merge/convert a video
@interface KCVideoProcessingTask : NSObject

@property (nonatomic, retain) KCVideo * video;
@property (nonatomic, assign) id <KCVideoProcessDelegate> delegate;
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
@property (nonatomic, retain) id <KCShareDelegate> delegate;
@property (nonatomic, retain) KCShareHandler * taskHandler;

- (id) initWithVideo:(KCVideo *)video
                info:(KCVideoShareInfo *)shareInfo
            delegate:(id <KCShareDelegate>)delegate;

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

// Puts a job on the worker queue. Returns immediately and calls
// back to the delegates when finished.
- (void)mergeVideo:(KCVideo *)video
          delegate:(id <KCVideoProcessDelegate>)delegate;
- (void)convertVideo:(KCVideo *)video
            delegate:(id <KCVideoProcessDelegate>)delegate;
- (void)shareVideo:(KCVideo *)video
              info:(KCVideoShareInfo *)info
          delegate:(id <KCShareDelegate>)delegate;

// Try to erase this video
- (BOOL)safelyPerformTaskAndVideoCleanup:(KCVideo *)video;

// Resume and cancel task queues
- (void)resumeTasks;
- (void)cancelAllActiveTasksAndPause;

// Upload status
- (BOOL)isUploadingInBackground;

- (void)dealloc;

+ (NetworkStatus)getNetworkStatus;

@end
