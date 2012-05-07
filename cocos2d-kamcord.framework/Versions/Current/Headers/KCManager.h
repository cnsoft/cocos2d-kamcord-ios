//
//  KCManager.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/5/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Platforms/CCGL.h"

// For recording video
#import "Platforms/iOS/KCVideoReplayCreator.h"

// For replaying video
#import <MediaPlayer/MPMoviePlayerViewController.h>

// For uploading to YouTube
#import "Platforms/iOS/KCYouTubeUploader.h"

// For composing email
#import <MessageUI/MFMailComposeViewController.h>

// For sharing to Faccebook
// TODO: Fix this relative path crap?
#import "../external/facebook-ios-sdk-kamcord/src/FBConnect.h"

// Kamcord dialog state
enum KamcordDialogState {
    OK,
    SAVING_TO_PHOTO_ALBUM,
    UPLOADING_TO_YOUTUBE,
    SENDING_VIDEO_EMAIL,
    SHARING_TO_FACEBOOK,
    SHARING_TO_TWITTER
};

enum LastVideoStatus
{
    NOT_READY,
    READY_FOR_SHOWING,
    VIDEO_IS_ON_YOUTUBE,
};

@interface KCManager : NSObject <KCVideoWriterDelegate, YouTubeUploaderDelegate, UIActionSheetDelegate, MFMailComposeViewControllerDelegate, FBSessionDelegate, FBDialogDelegate, FBRequestDelegate>
{    
    // Where to display our dialog
    UIViewController * parentViewController_;
    
    // Get the dimensions from the OpenGL view
    CC_GLVIEW * openGLView_;

    // Does our actual recording
    KCVideoReplayCreator * videoReplayCreator_;
    UIActivityIndicatorView * _exportActivityView;
    
    // Last video local URL and status
    NSURL * lastVideoURL_;
    enum LastVideoStatus lastVideoStatus_;
    
    // Kamcord dialog state
    BOOL kamcordDialogShowing_;
    enum KamcordDialogState dialogState_;
    
    // For replaying the recorded video
    MPMoviePlayerViewController * moviePlayerViewController_;
    
    // YouTube uploading
    KCYouTubeUploader * youtubeUploader_;
    id <YouTubeUploaderDelegate> youtubeDelegate_;
    UIProgressView * uploadProgressView_;
    NSString * defaultTitle_;
    NSString * defaultDescription_;
    NSString * defaultKeywords_;
    NSURL * uploadedYouTubeVideoURL_;   // The online YouTube URL of the video
    
    // Facebook sharing
    Facebook * facebook_;
    
    // Twitter
    NSString * defaultTweet_;
}

////////////////////////////////////////////////
// Public properties
@property (nonatomic, assign) UIViewController * parentViewController;
@property (nonatomic, assign) CC_GLVIEW * openGLView;

////////////////////////////////////////////////
// Public methods

+ (KCManager *)sharedManager;

- (BOOL) beginVideo;
- (BOOL) endVideo;
- (BOOL) startRecordingClip;
- (BOOL) stopRecordingClip;

- (void) setYouTubeUploadDefaultTitle:(NSString *)title
                   defaultDescription:(NSString *)description
                      defaultKeywords:(NSString *)keywords;

// The tweeted message will be: tweet + " videoURL" where videoURL is the
// YouTube URL of the uploaded video.
- (void) setDefaultTweet:(NSString *)tweet;

// Displays the Kamcord options inside the previously set parentViewController;
- (void) showKamcordDialog;


@end
