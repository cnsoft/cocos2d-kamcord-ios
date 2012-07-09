//
//  Kamcord.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/5/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

#import "CCDirectorIOS.h"
#import "KCGLView.h"

// Convenient for game developers
#import "KamcordMacros.h"
#import "Common/View/KCViewController.h"
#import "Common/Core/Audio/KCAudio.h"
#import "Common/Core/Audio/KCSound.h"

#define KAMCORD_VERSION "0.9.4"


// --------------------------------------------------------
// The following enum and protocol are only relevant
// if you're implementing your own custom UI.
// If you're using the default Kamcord UI, please
// ignore the following as it is irrelevant for you.

@class GTMOAuth2Authentication;

// --------------------------------------------------------
// API elements for custom sharing UI.
// Will be documented soon as we roll out complete
// support for custom UIs.
typedef enum
{
    NO_ERROR,
    FACEBOOK_NOT_AUTHENTICATED,
    FACEBOOK_LOGIN_CANCELLED,
    FACEBOOK_DAILY_SHARE_EXCEEDED,
    FACEBOOK_SERVER_ERROR,
    
    TWITTER_NOT_SETUP,
    TWITTER_NOT_AUTHENTICATED,
    TWITTER_SERVER_ERROR,
    
    YOUTUBE_NOT_AUTHENTICATED,
    YOUTUBE_LOGIN_CANCELLED,
    YOUTUBE_SERVER_ERROR,
    
    EMAIL_NOT_SETUP,
    EMAIL_CANCELLED,
    EMAIL_FAILED,
    NO_INTERNET,
    
    KAMCORD_SERVER_ERROR,
    
    NOTHING_TO_SHARE,
    MESSAGE_TOO_LONG,
    
    VIDEO_PROCESSING_ERROR,
} KCShareStatus;


@protocol KCShareDelegate <NSObject>

@required
// Only after this callback (or a generalError below) is it safe
// make a new share request.
- (void)shareStartedWithSuccess:(BOOL)success error:(KCShareStatus)error;

// Errors that happen along the way
- (void)generalError:(KCShareStatus)error;



@optional
// --------------------------------------------------------
// Callbacks for sharing

// Updates on video conversion.
// You should only try to show the video replay after
// the merge is finished. When the conversion is finished,
// the sound will have been added in.
//
// Don't worry about deferring on sharing until these are
// called. Our internal system will wait until conversion
// is finished before your share request is executed.
//
// 
- (void)videoMergeFinishedWithSuccess:(BOOL)success error:(NSError *)error;
- (void)videoConversionFinishedWithSuccess:(BOOL)success error:(NSError *)error;

// The following are only relevant for Option 1:
// Auth requests
- (void)facebookAuthFinishedWithSuccess:(BOOL)success;
- (void)twitterAuthFinishedWithSuccess:(BOOL)success;
- (void)youTubeAuthFinishedWithSuccess:(BOOL)success;

// Beginning of share process
//
// First: auth verification
- (void)facebookShareStartedWithSuccess:(BOOL)success error:(KCShareStatus)error;
- (void)twitterShareStartedWithSuccess:(BOOL)success error:(KCShareStatus)error;
- (void)youTubeUploadStartedWithSuccess:(BOOL)success error:(KCShareStatus)error;
- (void)emailSentWithSuccess:(BOOL)success error:(KCShareStatus)error;
//
// End of share process
- (void)facebookShareFinishedWithSuccess:(BOOL)success error:(KCShareStatus)error;
- (void)twitterShareFinishedWithSuccess:(BOOL)success error:(KCShareStatus)error;
- (void)youTubeUploadFinishedWithSuccess:(BOOL)success error:(KCShareStatus)error;


// The following callback will be made for both Option 1 and Option 2:

// If the error object is nil, then the video and thumbnail
// URLs are valid. Otherwise, the video and thumbnail URLs
// should not be considered valid, even if they are non-nil.
// The data is the original object that was passed in with the share request.
- (void)videoIsReadyToShare:(NSURL *)onlineVideoURL
                  thumbnail:(NSURL *)onlineThumbnailURL
                    message:(NSString *)message
                       data:(NSDictionary *)data
                      error:(NSError *)error;
@end


@interface Kamcord : NSObject

////////////////////////////////////////////////
// Public methods

// Returns YES if and only if Kamcord is supported by 
// this device's version of iOS.
// Note: You do NOT need to wrap your Kamcord calls
//       with this function. Kamcord will turn itself
//       off if this is NO.
+ (BOOL)isEnabled;

// Setup
+ (void) setDeveloperKey:(NSString *)key
         developerSecret:(NSString *)secret
                 appName:(NSString *)appName;
+ (NSString *)developerKey;
+ (NSString *)developerSecret;
+ (NSString *)appName;

// View and OpenGL
+ (void)setParentViewController:(UIViewController *)viewController;
+ (UIViewController *)parentViewController;

+ (void)setOpenGLView:(KCGLView *)glView;
+ (KCGLView *)openGLView;

+ (void)setDeviceOrientation:(KCDeviceOrientation)orientation;
+ (KCDeviceOrientation) deviceOrientation;

// For Portrait, do we support PortraitUpsideDown also?
+ (void)setSupportPortraitAndPortraitUpsideDown:(BOOL)value;
+ (BOOL)supportPortraitAndPortraitUpsideDown;

// Social media
+ (void) setYouTubeTitle:(NSString *)title
             description:(NSString *)description 
                keywords:(NSString *)keywords;
+ (NSString *)youtubeTitle;
+ (NSString *)youtubeDescription;
+ (NSString *)youtubeKeywords;

+ (void) setFacebookTitle:(NSString *)title
                  caption:(NSString *)caption
              description:(NSString *)description;
+ (NSString *)facebookTitle;
+ (NSString *)facebookCaption;
+ (NSString *)facebookDescription;

// Achievements is an NSArray of KCAchievement objects
+ (void)setLevel:(NSString *)level
           score:(NSNumber *)score
    achievements:(NSArray *)achievements;

+ (NSString *)level;
+ (NSNumber *)score;

////////////////////
// Video recording
//

// Not necessary to call. However, if you want to avoid
// the slight FPS drop when calling startRecording,
// call this method earlier when there's very little
// processing and a slight drop in FPS won't be noticed
// (for example, on startup, or an end of level screen).
+ (BOOL)prepareNextVideo;     // Same as [Kamcord beginVideoAsync:NO];
+ (BOOL)prepareNextVideo:(BOOL)async;

+ (BOOL)startRecording;
+ (BOOL)stopRecording;
+ (BOOL)resume;
+ (BOOL)pause;

// Displays the Kamcord view inside the previously set parentViewController;
+ (void)showView;

// Video recording settings
// For release, use SMART_VIDEO_DIMENSIONS:
//   iPad 1 and 2: 512x384
//   iPad 3: 1024x768
//   All iPhone and iPods: 480x320
//
// For trailers, use TRAILER_VIDEO_RESOLUTION
//   All iPads: 1024x768
//   iPhone/iPod non-retina: 480x320
//   iPhone/iPad retina: 960x640
typedef enum {
    SMART_VIDEO_RESOLUTION,
    TRAILER_VIDEO_RESOLUTION,
} KC_VIDEO_RESOLUTION;

// Size refers to the pixel dimensions. 
+ (void) setVideoResolution:(KC_VIDEO_RESOLUTION)resolution;
+ (KC_VIDEO_RESOLUTION) videoResolution;

// Audio recording
+ (KCAudio *)playSound:(NSString *)filename
                  loop:(BOOL)loop;
+ (KCAudio *)playSound:(NSString *)filename;

// Will stop all non-looping sounds. If loop is YES, will also stop
// all looping sounds.
+ (void)stopAllSounds:(BOOL)loop;

// If you have specific sounds you want to overlay at particular times,
// pass in an array populated with KCSound objects.
+ (BOOL)stopRecordingWithSounds:(NSArray *)sounds;

// Every time you call startRecording, Kamcord will delete
// the previous video if it is not currently being shared.
// If you want to erase the video before then, you can call
// this method. If the video is currently being shared, it
// it will be erased after the next share is complete.
//
// Please be careful with this call. If there are no pending shares,
// the video WILL be erased. If, for instance, you call
// [Kamcord presentVideoPlayerInViewController:] and
// then [Kamcord deleteLatestVideo] while the video is
// being shown, you may get EXC_BAD_ACCESS. 
//
// Returns YES if the latest video was deleted NOW.
// Returns NO if the latest video will be deleted after
// all sharing has been completed.
+ (BOOL)deleteLatestVideo;

// Optional: Set the maximum video time in seconds. If the recorded video goes over that time,
//           then only the last N seconds are taken.
//           To not have a maximum video time, set this value to 0 (the default).
+ (void)setMaximumVideoTime:(NSUInteger)seconds;
+ (NSUInteger)maximumVideoTime;

// --------------------------------------------------------
// Custom sharing API


// Used for both Case 1 and Case 2

// Replay the latest video in the parent view controller.
// The "latest video" is defined as the last one for which
// you called [Kamcord stopRecording].
+ (void)presentVideoPlayerInViewController:(UIViewController *)parentViewController;

// The object that will receive callbacks about sharing state.
// You must make sure that this object is retained until
// all the callbacks are done. This delegate is retained
// until all the callbacks are complete, after which it
// is released by Kamcord.
//
// When you release the object, you MUST set this delegate to nil.
+ (void)setShareDelegate:(id <KCShareDelegate>)delegate;
+ (id <KCShareDelegate>)shareDelegate;


// Case 1: Use the following API for sharing if you want
//         your own custom UI but would like Kamcord to handle
//         all of the Facebook/Twitter/YouTube authentication for you.

// Authenticate to the three social media services
+ (void)showFacebookLoginView;
+ (void)authenticateTwitter; 
+ (void)presentYouTubeLoginViewInViewController:(UIViewController *)parentViewController;

// Status of authentication
+ (BOOL)facebookIsAuthenticated;
+ (BOOL)twitterIsAuthenticated;
+ (BOOL)youTubeIsAuthenticated;

+ (void)performFacebookLogout;
+ (void)performYouTubeLogout;

// The method to share a message on these services.
// You can also use this if you want to mix different
// authentications. For instance, you can handle
// Facebook and Twitter auth and let Kamcord upload
// to YouTube with its own auth (which it got via
// presentYouTubeLoginViewInViewController: above.
// Simply call this with shareFacebook and shareTwitter set to NO
// and shareYouTube set to YES.
//
// Once the video uploads are done, we will call back
// to videoIsReadyToShare.
//
// Returns YES if the share was accepted for processing.
// Returns NO if there was a previous share that is still
// in its early stages (specifically, before a generalError:
// or shareshareStartedWithSuccess:error: callback).
+ (BOOL)shareVideoOnFacebook:(BOOL)shareFacebook
                     Twitter:(BOOL)shareTwitter
                     YouTube:(BOOL)shareYouTube
                 withMessage:(NSString *)message;

// Show the send email dialog with the Kamcord URL in the message.
// Any additional body text you'd like to add should be passed in the
// second argument.
+ (void)presentComposeEmailViewInViewController:(UIViewController *)parentViewController
                                       withBody:(NSString *)bodyText;


// Case 2: Use the following API for sharing if you want to use
//         your own custom UI and will also perform all of the 
//         Facebook/Twitter/YouTube authentication yourself.
//         Simply call this one function that will upload the video
//         to Kamcord (and optionally YouTube). Once the video is successfully
//         uploaded, you'll get a callback to 
//
//         - (void)videoIsReadyToShare:(NSURL *)onlineVideoURL
//                           thumbnail:(NSURL *)onlineThumbnailURL
//                             message:(NSString *)message
//                                data:(NSDictionary *)data
//                               error:(NSError *)error;
//
//         (defined above in KCShareDelegate).
//         If you don't want to upload to YouTube, simply pass
//         in nil for the youTubeAuth object.
//
//         The data object you pass in will be passed back to you
//         in videoIsReadyToShare.
//
//         Returns YES if the share was accepted for processing.
//         Returns NO if there was a previous share that is still
//         in its early stages (specifically, before a generalError:
//         or shareshareStartedWithSuccess:error: callback).
+ (BOOL)shareVideoWithMessage:(NSString *)message
              withYouTubeAuth:(GTMOAuth2Authentication *)youTubeAuth
                         data:(NSDictionary *)data;


// --------------------------------------------------------
// For Facebook SSO
+ (BOOL)handleOpenURL:(NSURL *)url;

// --------------------------------------------------------
// For Kamcord internal use, don't worry about these.

// Returns the singleton Kamcord object. You don't ever really need this, just
// use the static API calls.
 
+ (Kamcord *)sharedManager;

// Helper to figure calculate the internal scale factor
+ (unsigned int)resolutionScaleFactor;

+ (KCAudio *)audioBackground;

@end
