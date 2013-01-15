//
//  SettingsTableViewCell.h
//  cocos2d-ios
//
//  Created by Chris Perciballi on 12/22/12.
//
//

#import <UIKit/UIKit.h>

@interface SettingsTableViewCell : UITableViewCell

@property (nonatomic, retain) UIButton * button;
@property (nonatomic, retain) UIImageView * image;

-(void)setupWithBounds:(CGSize)bounds
                 image:(NSString*)imageName
                button:(UIButton*)newButton
               imgSize:(NSInteger)size
                 label:(UILabel*)label;

@end
