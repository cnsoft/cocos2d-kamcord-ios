//
//  KKVideoWriter.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/2/12.
//  Copyright (c) 2012 KamCord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

// The delegate for when the video is ready to be used
@protocol KCVideoWriterDelegate <NSObject>
@required
- (void) videoCreatedAtURL:(NSURL *) videoURL;
@end

@interface KCVideoWriter : NSObject
{
    // The delegate we will call when the video has been processed
    id <KCVideoWriterDelegate>   delegate_;
    
    // The video dimensions and bitrate
    CGSize                      dimensions_;
    NSNumber *                  bitRate_;
    
    // Video recording objects
    AVAssetWriter *                        videoWriter_;
    AVAssetWriterInput *                   videoWriterInput_;
    AVAssetWriterInputPixelBufferAdaptor * avAdaptor_;
    
    // Video recording status
    NSUInteger                  numFrames_;
    NSURL *                     videoFilePath_;
    
    BOOL                        isWritingVideo_;
    BOOL                        isWritingClip_;
    BOOL                        isVideoEnded_;
    
    // Keep track of how many seperate clips we have that are part
    // of one video. This lets us handle times when the apps are put
    // into the background and we have to finish writing at that point.
    // We then glue the clips together into one video using AVFoundtion.
    NSUInteger                  numClipsStarted_;
    NSMutableArray *            videoClipFilePaths_;
    BOOL                        videoIsMerged_;
    BOOL                        videoIsConverted_;
}

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

//
// A video consists of one or more clips. For example, if there are two clips
// like so:
// 
// [videoCreator beginVideo];
//
// [videoCreater startClip];
// ...
// [videoCreator endClip];
// [videoCreater startClip];
// ...
// [videoCreator endClip];
//
// [videoCreator endVideo];
//
// Then on the call to endVideo, this class will stitch the two clips together
// into one video and return the local file URL of the video.
- (BOOL) beginVideo;
- (BOOL) endVideo;
- (BOOL) requestVideoURLWithConversion:(BOOL) convert;

- (BOOL) startClip;
- (BOOL) endClip;

- (void) dealloc;

@end
