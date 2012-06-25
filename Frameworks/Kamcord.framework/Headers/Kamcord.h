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

#define KAMCORD_VERSION "0.9.2"

@class KCAudio;
@class KCUI;

@interface Kamcord : NSObject

////////////////////////////////////////////////
// Public methods



// Setup
+ (BOOL) handleOpenURL:(NSURL *)url;

+ (void) setDeveloperKey:(NSString *)key
         developerSecret:(NSString *)secret
                 appName:(NSString *)appName;
+ (NSString *)developerKey;
+ (NSString *)developerSecret;
+ (NSString *)appName;

// View and OpenGL
+ (void) setParentViewController:(UIViewController *)viewController;
+ (UIViewController *)parentViewController;

+ (void) setOpenGLView:(KCGLView *)glView;

+ (void) setDeviceOrientation:(KCDeviceOrientation)orientation;
+ (KCDeviceOrientation) deviceOrientation;

// For Portrait, do we support PortraitUpsideDown also?
+ (void) setSupportPortraitAndPortraitUpsideDown:(BOOL)value;
+ (BOOL) supportPortraitAndPortraitUpsideDown;

// Social media
+ (void) setYouTubeTitle:(NSString *)title
             description:(NSString *)description 
                keywords:(NSString *)keywords;
+ (NSString *) youtubeTitle;
+ (NSString *) youtubeDescription;
+ (NSString *) youtubeKeywords;

+ (void) setFacebookTitle:(NSString *)title
                  caption:(NSString *)caption
              description:(NSString *)description;
+ (NSString *) facebookTitle;
+ (NSString *) facebookCaption;
+ (NSString *) facebookDescription;

+ (void) setLevel:(NSString *)level
            score:(NSNumber *)score;
+ (NSString *) level;
+ (NSNumber *) score;

// Video recording
+ (BOOL) startRecording;
+ (BOOL) stopRecording;
+ (BOOL) resume;
+ (BOOL) pause;

// Displays the Kamcord view inside the previously set parentViewController;
+ (void) showView;

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
+ (KCAudio *) playSound:(NSString *)filename
                   loop:(BOOL)loop;
+ (KCAudio *) playSound:(NSString *)filename;

// Will stop all non-looping sounds. If loop is YES, will also stop
// all looping sounds.
+ (void) stopAllSounds:(BOOL)loop;

// If you have specific sounds you want to overlay at particular times,
// pass in an array populated with KCSound objects.
+ (BOOL) stopRecordingWithSounds:(NSArray *)sounds;

// --------------------------------------------------------
// API for custom UIs

// Authentication
+ (void)presentFacebookLoginView;
+ (void)authenticateTwitter; 
+ (void)presentYoutubeLoginViewInViewController:(UIViewController *)parentViewController;

// One method to share
+ (void)shareOnFacebook:(BOOL)shareFacebook
                onTwitter:(BOOL)shareTwitter
                onYouTube:(BOOL)shareYoutube
            withMessage:(NSString *)message;

// Replay the last video
+ (void)playVideoInViewController:(UIViewController *)parentViewController;

// Let people share a video through an email link
+ (void)presentComposeEmailViewInViewController:(UIViewController *)parentViewController;

// Possible error states as a result of trying to share
typedef enum {
    NO_ERROR,
    FACEBOOK_NOT_AUTHENTICATED,
    FACEBOOK_LOGIN_CANCELLED,
    
    TWITTER_NOT_SETUP,
    TWITTER_NOT_AUTHENTICATED,
    
    YOUTUBE_NOT_AUTHENTICATED,
    YOUTUBE_LOGIN_CANCELLED,
    
    EMAIL_NOT_SETUP,
    EMAIL_CANCELLED,
    EMAIL_FAILED,
    NO_INTERNET,
    NOTHING_TO_SHARE,
    MESSAGE_TOO_LONG
    
} KCUI_SHARE_FAILURE;


// --------------------------------------------------------
// For Kamcord internal use, don't worry about these.

// Returns the singleton Kamcord object. You don't ever really need this, just
// use the static API calls.
+ (Kamcord *) sharedManager;

// Helper to figure calculate the internal scale factor
+ (unsigned int) resolutionScaleFactor;

+ (KCAudio *) audioBackground;

@end

// Delegate for sharing results
@protocol KCShareDelegate 

@optional
- (void)facebookShareFinishedWithStatus:(BOOL)success
                                  error:(KCUI_SHARE_FAILURE)error;
- (void)twitterShareFinishedWithStatus:(BOOL)success
                                 error:(KCUI_SHARE_FAILURE)error;
- (void)youTubeShareFinishedWithStatus:(BOOL)success
                                 error:(KCUI_SHARE_FAILURE)error;
- (void)emailSentWithStatus:(BOOL)success
                      error:(KCUI_SHARE_FAILURE)error;

- (void)generalError:(KCUI_SHARE_FAILURE)error;
- (void)videoIsReadyToShare:(NSURL *)onlineURL
                  thumbnail:(NSURL *)thumbnailURL    // For Facebook wall posts
                      error:(NSError *)error;

@end
