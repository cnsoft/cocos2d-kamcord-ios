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

// Audio
+ (void) setAudioResourceName:(NSString *)name
                    extension:(NSString *)extension;
+ (NSString *)audioResourceName;
+ (NSString *)audioResourceExtension;

// Video recording
+ (BOOL) startRecording;
+ (BOOL) stopRecording;
+ (BOOL) resume;
+ (BOOL) pause;

// Video recording settings
enum KC_VIDEO_DIMENSIONS {
    VIDEO_DIMENSIONS_FULL,
    VIDEO_DIMENSIONS_HALF
};

enum KC_VIDEO_QUALITY {
    VIDEO_QUALITY_MEDIUM,
    VIDEO_QUALITY_HIGH
};

// Size refers to the pixel dimensions. 
+ (void) setVideoDimensions:(enum KC_VIDEO_DIMENSIONS)dimensions
                    quality:(enum KC_VIDEO_QUALITY)quality;
+ (enum KC_VIDEO_DIMENSIONS) videoDimensions;
+ (enum KC_VIDEO_QUALITY) videoQuality;


// Displays the Kamcord view inside the previously set parentViewController;
+ (void) showView;

@end
