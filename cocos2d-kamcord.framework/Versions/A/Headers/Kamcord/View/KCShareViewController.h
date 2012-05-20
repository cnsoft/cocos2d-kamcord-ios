//
//  KCShareViewController.h
//  KamcordUI
//
//  Created by Kevin Wang on 5/9/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SHKSharer.h"

// For getting updates on video conversion
#import "KCVideoUpdateReceiver.h"

// For uploading to S3
#import <AWSiOSSDK/S3/AmazonS3Client.h>

// For composing email
#import <MessageUI/MFMailComposeViewController.h>

@interface KCShareViewController : UIViewController <UITextViewDelegate, SHKSharerDelegate, KCVideoStatusUpdateReceiver, AmazonServiceRequestDelegate, MFMailComposeViewControllerDelegate, NSURLConnectionDelegate, UITableViewDataSource, UITableViewDelegate>
{    

}

@end
