//
//  KamcordMacros.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/21/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#ifndef cocos2d_ios_KamcordMacros_h
#define cocos2d_ios_KamcordMacros_h

#define CC_DIRECTOR_INIT_KAMCORD()                                                              \
do	{																							\
    window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];					\
    if( ! [CCDirector setDirectorType:kCCDirectorTypeDisplayLink] )								\
        [CCDirector setDirectorType:kCCDirectorTypeNSTimer];									\
    CCDirector *__director = [CCDirector sharedDirector];										\
    [__director setDisplayFPS:NO];																\
    [__director setAnimationInterval:1.0/60];													\
    KCGLView *__glView = [KCGLView viewWithFrame:[window bounds]								\
                                     pixelFormat:kEAGLColorFormatRGB565							\
                                     depthFormat:0 /* GL_DEPTH_COMPONENT24_OES */				\
                              preserveBackbuffer:NO												\
                                      sharegroup:nil											\
                                   multiSampling:NO                                             \
                                numberOfSamples:0												\
                                                    ];                                          \
    window.rootViewController = [[KCViewController alloc] initWithNibName:nil bundle:nil];      \
    window.rootViewController.view = __glView;                                                  \
    [Kamcord setParentViewController:window.rootViewController];                                \
    [Kamcord setOpenGLView:__glView];                                                           \
} while(0)


#endif
