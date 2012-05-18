//
//  KCVideoReplayCreator.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/2/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import "KCVideoWriter.h"

@protocol KCPixelBufferHandler <NSObject>

- (void) handlePixelBuffer:(CVPixelBufferRef) pixelBuffer
                    atTime:(CFAbsoluteTime) time;

@end

@interface KCVideoReplayCreator : NSObject <KCPixelBufferHandler>
{
    // Recording properties
    double targetFPS_;
    double recordingInterval_;
    
    // The video writer
    KCVideoWriter * videoWriter_;
    
    // Our current recording state
    CFAbsoluteTime startTime_;
    CFAbsoluteTime timeOfLastRecordedFrame_;
    BOOL           isWritingVideo_;
    BOOL           isWritingClip_;
    
}

// Public properties
@property (nonatomic, assign, readonly) BOOL isWritingVideo;
@property (nonatomic, assign, readonly) BOOL isWritingClip;

// Public methods

- (id) initWithDimensions:(CGSize) dimensions
             videoBitRate:(NSUInteger) bitRate
                targetFPS:(double) targetFPS
              andDelegate:(id <KCVideoWriterDelegate>) delegate;

- (void) handlePixelBuffer:(CVPixelBufferRef) pixelBuffer
                    atTime:(CFAbsoluteTime) time;

- (BOOL) beginVideo;
- (BOOL) endVideo;
- (BOOL) startRecording;
- (BOOL) stopRecording;
- (BOOL) requestVideoURLWithConversion:(BOOL) convert
                       progressDelgate:(id <KCVideoStatusUpdateReceiver>)delegate;

- (BOOL) videoIsConverted;

- (void) dealloc;

@end
