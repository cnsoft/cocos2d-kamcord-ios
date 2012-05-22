//
//  KCVideoUpdateReceiver.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/13/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol KCVideoStatusUpdateReceiver <NSObject>

- (void)setLocalVideoURL:(NSURL *)videoURL
               thumbnail:(CGImageRef)thumbnail
       isReadyForSharing:(BOOL)isReadyForSharing;

- (void)setExportProgress:(float)progress;

@end