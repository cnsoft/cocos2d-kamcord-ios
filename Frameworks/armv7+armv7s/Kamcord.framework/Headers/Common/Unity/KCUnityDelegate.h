//
//  KCUnityVideoDelegate.h
//  Unity-iPhone
//
//  Created by Kevin Wang on 10/3/12.
//
//

#import "Kamcord.h"

@interface KCUnityDelegate : NSObject<KamcordDelegate>

- (id)init;
- (void)dealloc;

////////////////////////////////////////////////////////////////
// KCVideoDelegate protocol

// Called when the Kamcord share view is dismissed
- (void)kamcordViewDidDisappear;

// Called when the movie player is presented
- (void)moviePlayerDidAppear;

// Called when the movie player is dismissed
- (void)moviePlayerDidDisappear;

// Called when the thumbnail image for the video is ready
- (void)thumbnailReadyAtFilePath:(NSString *)thumbnailFilePath;

// Called when the video upload begins
- (void)videoWillUploadToURL:(NSString *)kamcordURLString;

// Called when the video upload finishes
- (void)videoFinishedUploadingWithSuccess:(BOOL)success;

@end
