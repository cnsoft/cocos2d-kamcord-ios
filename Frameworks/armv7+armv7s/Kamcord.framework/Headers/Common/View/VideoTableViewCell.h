//
//  VideoTableViewCell.h
//  cocos2d-ios
//
//  Created by Chris Perciballi on 12/20/12.
//
//

#import <UIKit/UIKit.h>

@interface VideoTableViewCell : UITableViewCell

@property (nonatomic, retain) UIImageView * thumbnail;
@property (nonatomic, retain) UIImageView * playButton;
@property (nonatomic, retain) UILabel *     title;
@property (nonatomic, retain) UILabel *     timestampLabel;
@property (nonatomic, retain) UILabel *     appNameLabel;
@property (nonatomic, retain) UIImageView * background;
//@property (nonatomic, retain) UIImageView * commentIcon;
//@property (nonatomic, retain) UIButton *    commentButton;
//@property (nonatomic, retain) UIImageView * likeIcon;
//@property (nonatomic, retain) UIButton *    likeButton;	

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier xOffset:(NSInteger)xOffset thumbnailHeight:(NSInteger)thumbnailHeight;

@end
