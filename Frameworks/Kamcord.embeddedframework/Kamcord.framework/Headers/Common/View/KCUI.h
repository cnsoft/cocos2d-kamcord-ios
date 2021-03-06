//
//  KCGUI.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/14/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MessageUI/MFMailComposeViewController.h>
#import "SHKFacebook.h"
#import "KCYouTubeUploader.h"
#import "KCVideo.h"
#import "KCVideoProcessingAndShareManager.h"
#import "Kamcord.h"

@class KCSHKConfigurator;

@interface KCUI : NSObject <KCSHKSharerDelegate, MFMailComposeViewControllerDelegate, NSURLConnectionDelegate,KCYouTubeUploaderDelegate,KC_FBSessionDelegate, KC_FBDialogDelegate, KCLoginDismissedDelegate>


// The share delegate
@property (assign, nonatomic) id <KamcordDelegate> delegate;
@property (assign, nonatomic) id <KCShareDelegate> shareDelegate;

@property (retain, nonatomic) KCVideoProcessingAndShareManager * shareManager; 
@property (assign, nonatomic) KCVideo * latestVideo;

// Replay
- (void)presentVideoPlayerInViewController:(UIViewController *)parentViewController
                                  forVideo:(KCVideo *)video;

// Authentication
- (void)presentFacebookLoginView;
- (void)authenticateTwitter;
- (void)presentYouTubeLoginViewInViewController:(UIViewController *)parentViewController;

- (void)performFacebookLogout; 
- (void)performYoutubeLogout;

- (BOOL)facebookIsAuthenticated;
- (BOOL)twitterIsAuthenticated;
- (BOOL)youTubeIsAuthenticated;

// TODO: Find a cleaner way to do this.
- (void)videoConversionToBeScheduled;
- (void)videoConversionFinished:(NSError *)error;

// Sharing
- (BOOL)shareVideoOnFacebook:(BOOL)shareOnFacebook
                     Twitter:(BOOL)shareOnTwitter
                     YouTube:(BOOL)shareOnYoutube
                       Email:(BOOL)shareEmail
                 withMessage:(NSString *)message
        parentViewController:(UIViewController *)parentViewController
                    delegate:(id <KCShareDelegate>)delegate;

- (BOOL)shareVideo:(KCVideo *)video
        onFacebook:(BOOL)shareFacebook
           Twitter:(BOOL)shareTwitter
           YouTube:(BOOL)shareYoutube
             Email:(BOOL)shareEmail
       withMessage:(NSString *)message
parentViewController:(UIViewController *)parentViewController
           delegate:(id <KCShareDelegate>)delegate;

- (BOOL)presentComposeEmailViewInViewController:(UIViewController *)parentViewController
                                       withBody:(NSString *)bodyText;

// Used for Case 2 where they just want to upload the video
- (BOOL)uploadVideoToKamcordAndAlsoYouTubeWithAuth:(GTMOAuth2Authentication *)youTubeAuth
                                       withMessage:(NSString *)message
                                              data:(NSDictionary *)data;

@end
