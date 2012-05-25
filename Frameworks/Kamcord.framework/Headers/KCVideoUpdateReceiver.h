//
//  KCVideoUpdateReceiver.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/13/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@protocol KCVideoStatusUpdateReceiver <NSObject>

// Export status
- (void)setActiveExporter:(AVAssetExportSession *)exporter;
- (void)setExportProgress:(float)progress;

// By the time these two methods are called, the active exporter
// may already have been dealloc'ed.
- (void)exportDoneWithVideoURL:(NSURL *)videoURL
                     thumbnail:(CGImageRef)thumbnail
             isReadyForSharing:(BOOL)isReadyForSharing;
- (void)exportCancelled;

- (void)videoUploadedOnlineToURL:(NSURL *)videoURL
                    thumbnailURL:(NSURL *)thumbnailURL;


@end