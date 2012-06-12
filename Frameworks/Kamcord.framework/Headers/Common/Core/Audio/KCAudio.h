//
//  KCAudio.h
//  cocos2d-ios
//
//  Created by Matthew Zitzmann on 6/4/12.
//  Copyright (c) 2012 Kamcord Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>

@class KCVideo;

@interface KCAudio : NSObject

// File name, extension, and loop
@property (nonatomic, copy) NSString * name;
@property (nonatomic, copy) NSString * extension;
@property (nonatomic, assign) BOOL loop;

// Start and end times
@property (nonatomic, assign) KCVideo * video;
@property (nonatomic, readonly, assign) CMTime startTime;
@property (nonatomic, readonly, assign) CMTime endTime;

// Resource URL
@property (nonatomic, retain) NSURL * url;

- (id)  initWithName:(NSString *)name
            extension:(NSString *)extension
                loop:(BOOL) loop
            forVideo:(KCVideo *)video;

- (void)start;
- (void)stop;

@end
