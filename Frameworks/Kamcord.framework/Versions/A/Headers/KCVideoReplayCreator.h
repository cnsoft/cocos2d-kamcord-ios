//
//  KCVideoReplayCreator.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/2/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import "KCVideoWriter.h"

@protocol KCPixelBufferHandler <NSObject>

- (void) handlePixelBuffer:(CVPixelBufferRef) pixelBuffer
                    atTime:(CFAbsoluteTime) time;

@end

@interface KCVideoReplayCreator : NSObject <KCPixelBufferHandler>

// Public properties
@property (nonatomic, assign, readonly) BOOL isWritingVideo;
@property (nonatomic, assign, readonly) BOOL isWritingClip;

// Public methods

- (id) initWithDimensions:(CGSize) dimensions
             videoBitRate:(NSUInteger) bitRate
                targetFPS:(double) targetFPS;

- (void) handlePixelBuffer:(CVPixelBufferRef) pixelBuffer
                    atTime:(CFAbsoluteTime) time;

- (BOOL) beginVideoWithId:(NSString *)videoID;
- (BOOL) endVideo;
- (BOOL) startRecording;
- (BOOL) stopRecording;
- (BOOL) requestVideoURLWithConversion:(BOOL) convert
                       progressDelgate:(id <KCVideoStatusUpdateReceiver>)delegate;

- (BOOL) videoIsConverted;

- (void) dealloc;

@end
