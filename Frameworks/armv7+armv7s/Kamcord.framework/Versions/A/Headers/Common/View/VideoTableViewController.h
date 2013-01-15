//
//  VideoTableViewController.h
//  KamcordApp
//
//  Created by Matthew Zitzmann on 10/7/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

//
//  Based On:
//  PullRefreshTableViewController.h
//  Plancast
//
//  Created by Leah Culver on 7/2/10.
//  Copyright (c) 2010 Leah Culver
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without
//  restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following
//  conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import <StoreKit/StoreKit.h>

@interface VideoEntity : NSObject

@property (nonatomic, copy) NSString * title;
@property (nonatomic, copy) NSString * thumbnailURL;
@property (nonatomic, copy) NSString * videoURL;
@property (nonatomic, assign) int appId;
@property (nonatomic, copy) NSString * appName;
@property (nonatomic, copy) NSString * videoId;
@property (nonatomic, copy) NSString * appStoreIdentifier;
@property (nonatomic, copy) NSString * appStoreLink;
@property (nonatomic, assign) long addedAt;

@end

@interface KCMPMoviePlayerViewController : MPMoviePlayerViewController

@property (nonatomic, assign) int appId;
@property (nonatomic, copy) NSString * videoId;
@property (nonatomic, assign) int feedPosition;

- (id)initWithContentURL:(NSURL *)contentUrl
                   appId:(int)appId
                 videoId:(NSString *)videoId
            feedPosition:(int)feedPosition;

@end

@interface VideoTableViewController : UITableViewController<SKStoreProductViewControllerDelegate, NSURLConnectionDelegate> {
    UIView * refreshHeaderView;
    UILabel * refreshLabel;
    UIImageView * refreshArrow;
    UIActivityIndicatorView * refreshSpinner;
    BOOL isDragging;
    BOOL isLoading;
}

@property (nonatomic, strong) UIView * refreshHeaderView;
@property (nonatomic, strong) UILabel * refreshLabel;
@property (nonatomic, strong) UIImageView * refreshArrow;
@property (nonatomic, strong) UIActivityIndicatorView * refreshSpinner;

@property (nonatomic, strong) NSMutableArray * videoEntities;
@property (nonatomic, strong) NSMutableData * httpResponseData;
@property (nonatomic, strong) KCMPMoviePlayerViewController * player;
@property (nonatomic, strong) NSDateFormatter * dateFormatter;
@property (nonatomic, strong) NSDate * lastUpdatedAt;
@property (nonatomic, strong) UILabel * noInternetLabel;

- (void)addPullToRefreshHeader;
- (void)startLoading;
- (void)stopLoading;

@end
