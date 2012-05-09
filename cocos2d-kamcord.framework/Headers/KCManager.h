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

// For sharing to Facebook
#import "FBConnect.h"

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

@interface KCManager : NSObject <KCVideoWriterDelegate, KCYouTubeUploaderDelegate, UIActionSheetDelegate, MFMailComposeViewControllerDelegate, FBSessionDelegate, FBDialogDelegate, FBRequestDelegate>
{    
    // The developer key
    NSString * developerKey_;
    
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
    id <KCYouTubeUploaderDelegate> youtubeDelegate_;
    UIProgressView * uploadProgressView_;
    NSString * defaultYouTubeTitle_;
    NSString * defaultYouTubeDescription_;
    NSString * defaultYouTubeKeywords_;
    NSURL * uploadedYouTubeVideoURL_;   // The online YouTube URL of the video
    
    // Facebook sharing
    Facebook * facebook_;
    NSString * defaultFacebookTitle_;
    NSString * defaultFacebookCaption_;
    NSString * defaultFacebookDescription_;
    
    // Twitter
    NSString * defaultTweet_;
    
    // The custom developer message to add to all YouTube/Facebook descriptions
    NSString * developerMessage_;
}

////////////////////////////////////////////////
// Public properties
@property (nonatomic, assign) UIViewController * parentViewController;
@property (nonatomic, assign) CC_GLVIEW * openGLView;

////////////////////////////////////////////////
// Public methods

+ (KCManager *)sharedManager;

- (void) setDeveloperKey:(NSString *)developerKey;

- (BOOL) beginVideo;
- (BOOL) endVideo;
- (BOOL) startRecordingClip;
- (BOOL) stopRecordingClip;

// Set defaults for YouTube/Facebook/Twitter user dialogs
- (void) setYouTubeUploadDefaultTitle:(NSString *)title
                   defaultDescription:(NSString *)description
                      defaultKeywords:(NSString *)keywords;

- (void) setFacebookShareDefaultTitle:(NSString *)title
                       defaultCaption:(NSString *)caption
                   defaultDescription:(NSString *)description;


// The tweeted message will be: tweet + " videoURL" where videoURL is the
// YouTube URL of the uploaded video.
- (void) setDefaultTweet:(NSString *)tweet;

// This string is appended to every YouTube and Facebook description.
// Use it to advertise your game (for example: "Get this game at http://www.mycoolgame.com/").
- (void) setDeveloperMessage:(NSString *)message;

// Displays the Kamcord view inside the previously set parentViewController;
- (void) showKamcordView;


@end
