//
//  KKVideoWriter.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/2/12.
//  Copyright (c) 2012 KamCord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#import "KCVideoUpdateReceiver.h"

// The delegate for when the video is ready to be used
@protocol KCVideoWriterDelegate <NSObject>
@required
- (void) videoCreatedAtURL:(NSURL *)videoURL
                 thumbnail:(CGImageRef)thumbnail;
@end

@interface KCVideoWriter : NSObject

// Public properties
@property (nonatomic, assign, readonly) BOOL isWritingVideo;
@property (nonatomic, assign, readonly) BOOL isWritingClip;
@property (nonatomic, assign, readonly) BOOL videoIsConverted;


// Only initializer
- (id) initWithDimensions:(CGSize) dimensions
             videoBitRate:(NSUInteger) bitRate
              andDelegate:(id <KCVideoWriterDelegate>) delegate;

// Write a frame to the video
- (BOOL) addFrameToVideo:(CVPixelBufferRef) pixelBuffer
                  atTime:(CMTime) time;

- (BOOL) beginVideo;
- (BOOL) endVideo;
- (BOOL) requestVideoURLWithConversion:(BOOL) convert
                       progressDelgate:(id <KCVideoStatusUpdateReceiver>)delegate;

- (BOOL) startClip;
- (BOOL) endClip;

- (void) dealloc;

@end
