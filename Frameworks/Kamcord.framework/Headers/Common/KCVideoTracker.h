//
//  KCVideoTracker.h
//  cocos2d-ios
//
//  Created by Aditya Rathnam on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface KCVideoTracker : NSManagedObject

@property (nonatomic, retain) NSDate * addedAt;
@property (nonatomic, retain) NSString * localVideoId;
@property (nonatomic, retain) NSNumber * s3UploadAttempt;
@property (nonatomic, retain) NSString * s3VideoId;
@property (nonatomic, retain) NSString * sharedOn;
@property (nonatomic, retain) NSString * videoPath;
@property (nonatomic, retain) NSString * videoStatus;
@property (nonatomic, retain) NSNumber * youtubeUploadAttempt;

@end
