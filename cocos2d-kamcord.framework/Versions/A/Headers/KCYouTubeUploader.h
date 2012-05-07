//
//  YouTubeUploader.h
//
//  Created by Kevin Wang on 3/23/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "GData.h"

// Upload status callbacks
@protocol YouTubeUploaderDelegate <NSObject>

@optional
- (void) loginIsSuccessful:(BOOL) success;

- (void) bytesSent:(unsigned long long) bytesSent
  ofTotalByteCount:(unsigned long long) dataLength;

- (void) uploadFinishedWithURL:(NSURL *) videoURL
                         error:(NSError *) error;
@end


@interface KCYouTubeUploader : NSObject <UIWebViewDelegate>
{
    NSString * developerKey_;
    NSURL * uploadLocationURL_;
    GDataServiceTicket * uploadTicket_;
    
    id <YouTubeUploaderDelegate> delegate_;
    
    UIViewController * parentViewController_;
}

// Public properties
@property (nonatomic, retain) NSString * developerKey;
@property (nonatomic, retain) id <YouTubeUploaderDelegate> delegate;

// Public methods
- (BOOL)isAuthenticated;

- (id) initWithDelegate:(id <YouTubeUploaderDelegate>)delegate
        andDeveloperKey:(NSString *)developerKey;
- (void) showUserLoginViewInViewController:(UIViewController *)parentViewController;

// Returns NO if the user is not logged in or not delegate is set.
// The upload is not attempted (obviously).
//
// Returns YES if the user is logged in and the upload was attempted. Does NOT
// mean that the upload was successful. Must wait for the delegate callback
// uploadFinishedWithUrl:error: to verify that.
- (BOOL) uploadVideoFile:(NSURL *)path
               withTitle:(NSString *)title
             description:(NSString *)description
                keywords:(NSString *)keywords;

// TODO: test somehow
- (void) restartUpload:(NSString *)path;

- (void) signOut;


@end
