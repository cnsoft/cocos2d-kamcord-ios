//
//  KCVideo.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/30/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreMedia/CMTime.h>

#import "DataStructures/NSMutableArray+QueueAdditions.h"

//////////////////////////////////////////////////////
// Begin KCVideoSharingState
@interface KCVideoShareInfo : NSObject

@property (readonly, nonatomic, copy)   NSString * message;
@property (readonly, nonatomic, assign) BOOL shareOnFacebook;
@property (readonly, nonatomic, assign) BOOL shareOnTwitter;
@property (readonly, nonatomic, assign) BOOL shareOnYouTube;
@property (readonly, nonatomic, assign) BOOL alreadySharedWithEmail;

- (id) initWithMessage:(NSString *)message
       shareOnFacebook:(BOOL)shareOnFacebook
        shareOnTwitter:(BOOL)shareOnTwitter
        shareOnYouTube:(BOOL)shareOnYouTube
alreadySharedWithEmail:(BOOL)alreadySharedWithEmail;

- (void) dealloc;

@end
// End KCVideoSharingState
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
// Begin KCVideo
@class KCAudioCollection;

@interface KCVideo : NSObject

typedef enum
{
    KC_VIDEO_STATUS_NONE,       // Just instantiated
    
    KC_VIDEO_BEGUN,             // beginVideo
    KC_VIDEO_RECORDING,         // startRecording
    KC_VIDEO_DONE_RECORDING,    // stopRecording
    KC_VIDEO_ENDED,             // endVideo
    
    KC_VIDEO_QUEUED_FOR_MERGE,
    KC_VIDEO_MERGING,
    KC_VIDEO_DONE_MERGING,    
    
    KC_VIDEO_QUEUED_FOR_CONVERSION,
    KC_VIDEO_CONVERTING,
    KC_VIDEO_DONE_CONVERTING,
    
    KC_VIDEO_UPLOADING_TO_KAMCORD,
    KC_VIDEO_DONE_UPLOADING_TO_KAMCORD,
    
    KC_VIDEO_SHARING,
    KC_VIDEO_DONE_SHARING
} KC_VIDEO_STATUS;

// The unique video ID
@property (readonly, nonatomic, copy) NSString * localVideoID;

// Video state variable
@property (nonatomic, assign) KC_VIDEO_STATUS videoStatus;

@property (nonatomic, readonly, assign) BOOL hasEnded;
@property (nonatomic, readonly, assign) BOOL isMerged;
@property (nonatomic, readonly, assign) BOOL isConverted;

// Information about the currently recorded clip
@property (nonatomic, assign) CFAbsoluteTime startTime;
@property (nonatomic, assign) CFAbsoluteTime timeOfLastRecordedFrame;

// The total duration of all previous clips (before the current clip)
@property (nonatomic, assign) CMTime durationOfAllPreviousClips;

// Local video URLs
@property (nonatomic, readonly, retain) NSURL * videoDirectory;

@property (nonatomic, retain) NSMutableArray * videoClipLocalURLs;
@property (nonatomic, retain) NSURL * mergedVideoLocalURL;
@property (nonatomic, retain) NSURL * convertedVideoLocalURL;
@property (nonatomic, retain) CGImageRef thumbnail __attribute__((NSObject));

// Online URLs and IDs
@property (nonatomic, copy) NSString * onlineVideoID;
@property (nonatomic, copy) NSString * onlineThumbnailID;

@property (nonatomic, copy) NSString * onlineVideoBucketName;
@property (nonatomic, copy) NSString * onlineThumbnailBucketName;

@property (nonatomic, retain) NSURL * onlineKamcordVideoURL;
@property (nonatomic, retain) NSURL * onlineKamcordThumbnailURL;
@property (nonatomic, retain) NSURL * onlineYouTubeVideoURL;

@property (nonatomic, assign) BOOL uploadedToKamcord;

// Audio
@property (nonatomic, retain) KCAudioCollection * audioCollection;

// Has everything that we need to do with this video been done?
// If so, we can just go ahead and erase it to save space.
@property (nonatomic, assign) BOOL markForDeletion;
@property (nonatomic, assign) BOOL deleted;


// Public methods

// Initializes a video with an ID
- (id)initWithID:(NSString *)videoID;

// Returns the URL of the current video being recorded
- (NSURL *)currentVideoClipLocalURL;

// Creates a new local file and sets the current video clip
// local URL to that file path. Returns YES on success.
- (BOOL)addNewVideoClip;


// Erases all video files associated with this video
- (void)dealloc;

@end
// End KCVideo
//////////////////////////////////////////////////////
