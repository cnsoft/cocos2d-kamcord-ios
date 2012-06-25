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


@interface KCUI : NSObject <KCSHKSharerDelegate, MFMailComposeViewControllerDelegate, NSURLConnectionDelegate,KCYouTubeUploaderDelegate,KC_FBSessionDelegate, KC_FBDialogDelegate, KCLoginDismissedDelegate, KCShareFinishedDelegate>



@property (assign, nonatomic) id<KCShareDelegate> delegate;
@property (retain, nonatomic) KCVideoProcessingAndShareManager *shareManager; 
@property (assign, nonatomic) KCVideo *latestVideo;
@property (assign, nonatomic) UIViewController *parentView;
-(void) presentFacebookLoginView;
-(void) authenticateTwitter;
-(void) presentComposeEmailViewInViewController:(UIViewController *)parentViewController;
-(void) presentYoutubeLoginViewInViewController:(UIViewController *)parentViewController;
-(void) presentVideoPlayerToViewController:(UIViewController *)parentViewController;
//general 

-(void) setVideo:(KCVideo *)video;

-(void) shareToFacebook:(BOOL)shareFacebook 
                Twitter:(BOOL)shareTwitter 
                Youtube:(BOOL)shareYoutube 
            withMessage:(NSString *)message;


@end
