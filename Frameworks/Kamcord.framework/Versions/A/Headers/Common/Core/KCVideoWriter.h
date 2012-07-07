//
//  KKVideoWriter.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/2/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@class KCVideo;

@interface KCVideoWriter : NSObject

// Public properties
@property (nonatomic, copy, readonly) KCVideo * currentVideo;

// Only initializer
- (id) initWithDimensions:(CGSize) dimensions
             videoBitRate:(NSUInteger) bitRate
                targetFPS:(double) targetFPS;


// Write a frame to the video
- (BOOL) addFrameToVideo:(CVPixelBufferRef) pixelBuffer
                  atTime:(CFAbsoluteTime) time;

- (BOOL) beginVideo:(KCVideo *)video;
- (BOOL) endVideo;
- (BOOL) startRecording;
- (BOOL) pause;
- (BOOL) resume;
- (BOOL) stopRecording;

// Useful to know if we're currently writing frames or not
- (BOOL) isWriting;

- (void) dealloc;

@end
