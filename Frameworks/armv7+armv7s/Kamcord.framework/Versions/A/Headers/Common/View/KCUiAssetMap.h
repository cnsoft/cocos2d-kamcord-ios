//
//  KCUiAssetMap.h
//  cocos2d-ios
//
//  Created by Chris Perciballi on 2/15/13.
//
//

#import <Foundation/Foundation.h>

@interface KCUiAssetMap : NSObject

@property (nonatomic, retain) NSDictionary * uiComponentMap;
@property (nonatomic, retain) NSDictionary * uiStyleMap;

-(void) loadComponentNamesFromJson:(NSString *)jsonFileName;
-(void) setFileName:(NSString *)fileName forUiComponent:(NSString *)uiComponent;
-(NSString *) getFileNameForUiComponent:(NSString *)uiComponent;
-(NSString *) getStyleForUiComponent:(NSString *)uiComponent;

-(id) initForDebug;
-(id) initWithDefaults;
-(id) initForAutoPop;

@end
