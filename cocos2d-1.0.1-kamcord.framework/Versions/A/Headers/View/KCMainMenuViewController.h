//
//  KCViewController.h
//  KamcordUI
//
//  Created by Kevin Wang on 5/9/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KCViewController.h"
#import "../KCVideoUpdateReceiver.h"

@interface KCMainMenuViewController : KCViewController <KCVideoStatusUpdateReceiver>

@end
