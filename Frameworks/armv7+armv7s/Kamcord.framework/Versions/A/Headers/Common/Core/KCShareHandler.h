//
//  KCShareHandler.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/29/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SHKSharer.h"
#import "KCYouTubeUploader.h"

// For uploading to S3
#import "S3/AmazonS3Client.h"

@class KCVideoSharingTask;
@class KCVideoProcessingAndShareManager;
@class KCUploadRequestDelegate;


@interface KCShareHandler : NSObject <KCSHKSharerDelegate, AmazonServiceRequestDelegate, NSURLConnectionDelegate, KCYouTubeUploaderDelegate>

// Weak reference b/c the task retains this object, so don't
// want a retain cycle.
@property (nonatomic, readonly, assign) KCVideoSharingTask * sharingTask;
@property (nonatomic, readonly, assign) KCVideoProcessingAndShareManager * delegate;
@property (nonatomic, readonly, assign) KCUploadRequestDelegate * upReqDelegate;

- (id) initWithTask:(KCVideoSharingTask *)task
           delegate:(KCVideoProcessingAndShareManager *)delegate;
- (BOOL) doTask;
- (void) cancel;
- (void) dealloc;

extern NSString * const KCS3UploadDidStartNotification;
extern NSString * const KCS3UploadDidProgressNotification;
extern NSString * const KCS3UploadDidFinishNotification;
@end

@interface KCUploadRequestDelegate : NSObject<AmazonServiceRequestDelegate>

@property (nonatomic, readonly, assign) KCShareHandler *shareHandler;
@property (atomic, assign) BOOL completed;

- (id) initWithShareHandler:(KCShareHandler *)shareHandler;

@end
