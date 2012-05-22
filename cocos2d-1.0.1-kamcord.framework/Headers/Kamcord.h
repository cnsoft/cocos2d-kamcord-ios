//
//  Kamcord.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/5/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "KCGLView.h"
#import "CCDirectorIOS.h"

// Convenient for game developers
#import "KamcordMacros.h"
#import "View/KCViewController.h"

@interface Kamcord : NSObject

////////////////////////////////////////////////
// Public methods

// Setup
+ (void) setDeveloperKey:(NSString *)key
         developerSecret:(NSString *)secret;
+ (NSString *)developerKey;
+ (NSString *)developerSecret;

// View and OpenGL
+ (void) setParentViewController:(UIViewController *)viewController;
+ (UIViewController *)parentViewController;

+ (void) setOpenGLView:(KCGLView *)glView;

+ (void) setDeviceOrientation:(ccDeviceOrientation)orientation;
+ (ccDeviceOrientation) deviceOrientation;

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

+ (void) setLevel:(NSString *)level
            score:(NSNumber *)score;
+ (NSString *) level;
+ (NSNumber *) score;

// Video recording
+ (BOOL) beginVideo;
+ (BOOL) endVideo;
+ (BOOL) startRecording;
+ (BOOL) stopRecording;

// Displays the Kamcord view inside the previously set parentViewController;
+ (void) showView;

@end
