//
//  KCShareViewController.h
//  KamcordUI
//
//  Created by Kevin Wang on 5/9/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KCViewController.h"

// Sharing
#import "SHKSharer.h"
#import "KCYouTubeUploader.h"

// For composing email
#import <MessageUI/MFMailComposeViewController.h>

@class KCVideo;
@class KCVideoProcessingAndShareManager;

@interface KCShareViewController : KCViewController <UITextViewDelegate, UITableViewDataSource, UITableViewDelegate, SHKSharerDelegate, MFMailComposeViewControllerDelegate, NSURLConnectionDelegate,KCYouTubeUploaderDelegate>

@property (nonatomic, retain) KCVideo * latestVideo;
@property (nonatomic, retain) KCVideoProcessingAndShareManager * shareManager;

- (void) dealloc;

@end
