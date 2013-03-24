//
// RotateWorld demo
// a cocos2d example
// http://www.cocos2d-iphone.org
//

// local import
#import "RotateWorldTest.h"

#import <Kamcord/Kamcord.h>

@implementation TextLayer
-(id) init
{
	if( (self=[super init] ) ) {

		float x,y;
		
		CGSize size = [[CCDirector sharedDirector] winSize];
		x = size.width;
		y = size.height;

		NSArray *array = [UIFont familyNames];
		for( NSString *s in array )
			NSLog( @"%@",s );
		CCLabelTTF *label = [CCLabelTTF labelWithString:@"cocos2d" fontName:@"Marker Felt" fontSize:64];

		[label setPosition: ccp(x/2,y/2)];
		
		[self addChild: label];
	}
	return self;
}

- (void) dealloc
{
	[super dealloc];
}

@end

@implementation SpriteLayer
-(id) init
{
	if( (self=[super init] ) ) {
		float x,y;
		
		CGSize size = [[CCDirector sharedDirector] winSize];
		x = size.width;
		y = size.height;
		
		CCSprite *sprite = [CCSprite spriteWithFile: @"grossini.png"];
		CCSprite *spriteSister1 = [CCSprite spriteWithFile: @"grossinis_sister1.png"];
		CCSprite *spriteSister2 = [CCSprite spriteWithFile: @"grossinis_sister2.png"];
		
		[sprite setScale: 1.5f];
		[spriteSister1 setScale: 1.5f];
		[spriteSister2 setScale: 1.5f];
		
		[sprite setPosition: ccp(x/2,y/2)];
		[spriteSister1 setPosition: ccp(40,y/2)];
		[spriteSister2 setPosition: ccp(x-40,y/2)];

		CCAction *rot = [CCRotateBy actionWithDuration:16 angle:-3600];
		
		[self addChild: sprite];
		[self addChild: spriteSister1];
		[self addChild: spriteSister2];
		
		[sprite runAction: rot];

		CCActionInterval *jump1 = [CCJumpBy actionWithDuration:4 position:ccp(-400,0) height:100 jumps:4];
		CCActionInterval *jump2 = [jump1 reverse];
		
		CCActionInterval *rot1 = [CCRotateBy actionWithDuration:4 angle:360*2];
		CCActionInterval *rot2 = [rot1 reverse];
		
		[spriteSister1 runAction: [CCRepeat actionWithAction: [CCSequence actions:jump2, jump1, nil] times:5 ] ];
		[spriteSister2 runAction: [CCRepeat actionWithAction: [CCSequence actions:[[jump1 copy] autorelease], [[jump2 copy] autorelease], nil] times:5 ] ];
		
		[spriteSister1 runAction: [CCRepeat actionWithAction: [CCSequence actions: rot1, rot2, nil] times:5 ] ];
		[spriteSister2 runAction: [CCRepeat actionWithAction: [CCSequence actions: [[rot2 copy] autorelease], [[rot1 copy] autorelease], nil] times:5 ] ];
	}
	
	return self;
}

- (void) dealloc
{
	[super dealloc];
}
@end

@implementation MainLayer
-(id) init
{
	if( (self=[super init] ) ) {
		float x,y;
		
		CGSize size = [[CCDirector sharedDirector] winSize];
		x = size.width;
		y = size.height;
		
		CCNode* blue =  [CCLayerColor layerWithColor:ccc4(0,0,255,255)];
		CCNode* red =   [CCLayerColor layerWithColor:ccc4(255,0,0,255)];
		CCNode* green = [CCLayerColor layerWithColor:ccc4(0,255,0,255)];
		CCNode* white = [CCLayerColor layerWithColor:ccc4(255,255,255,255)];

		[blue setScale: 0.5f];
		[blue setPosition: ccp(-x/4,-y/4)];
		[blue addChild: [SpriteLayer node]];
		
		[red setScale: 0.5f];
		[red setPosition: ccp(x/4,-y/4)];

		[green setScale: 0.5f];
		[green setPosition: ccp(-x/4,y/4)];
		[green addChild: [TextLayer node]];

		[white setScale: 0.5f];
		[white setPosition: ccp(x/4,y/4)];

		[self addChild: blue z:-1];
		[self addChild: white];
		[self addChild: green];
		[self addChild: red];

		CCAction * rot = [CCRotateBy actionWithDuration:8 angle:720];
		
		[blue runAction: rot];
		[red runAction: [[rot copy] autorelease]];
		[green runAction: [[rot copy] autorelease]];
		[white runAction: [[rot copy] autorelease]];
	}
	
	return self;
}
- (void) dealloc
{
	[super dealloc];
}

@end

// CLASS IMPLEMENTATIONS
@implementation AppController

@synthesize window;

- (void) applicationDidFinishLaunching:(UIApplication*)application
{
    // Init the window
    window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    // Must be called before any other call to the director
    [CCDirector setDirectorType:kCCDirectorTypeDisplayLink];
    
    // Before creating any layer, set the landscape mode
    CCDirector *director = [CCDirector sharedDirector];
    
    // Set FPS at 60k
    [director setAnimationInterval:1.0/60];
    
    // Display FPS: yes
    [director setDisplayFPS:YES];
    
    // Instantiate a KCGLView, which is a subclass with EAGLView with
    // special recording functionality.
    KCGLView * glView = [KCGLView viewWithFrame:[window bounds]
                                    pixelFormat:kEAGLColorFormatRGB565
                                    depthFormat:0];
    
    // Kamcord uses UIKit for autorotation, which requires special logic to handle rotations.
    window.rootViewController = [[KCViewController alloc] initWithNibName:nil bundle:nil];
    window.rootViewController.view = glView;
    
    // Tell Kamcord about the root view controller and the KCGLView
    [Kamcord setParentViewController:window.rootViewController];
    [Kamcord setOpenGLView:glView];
    
    // Set the device orientation. Must use Kamcord, not CCDirector!
    [Kamcord setDeviceOrientation:KCDeviceOrientationPortrait];
    
    // Kamcord setup
    [Kamcord setDeveloperKey:@"f9014ff0b3d5a44db2468a0e16bfcf8c"
             developerSecret:@"SDqGQY8I2JtmXmk4rJZhS5qtr5witt7YmRhVODhu8Yw"
                     appName:@"RotateWorldTest"];
    
    // Social media settings
    [Kamcord setYouTubeDescription:@"This is a Cocos2D test app that was recorded with Kamcord."
                              tags:@"Cocos2D RotateWorldTest"];
    
    [Kamcord setFacebookTitle:@"RotateWorldTest"
                      caption:@"Kamcord recording"
                  description:@"This is a Cocos2D test app that was recorded with Kamcord."];
	
	// Turn on display FPS
	[director setDisplayFPS:YES];
    
    [Kamcord setVideoResolution:MEDIUM_VIDEO_RESOLUTION];
	
	// Enables High Res mode (Retina Display) on iPhone 4 and maintains low res on all other devices
	if( ! [director enableRetinaDisplay:YES] )
		CCLOG(@"Retina Display Not supported");
	
	// Default texture format for PNG/BMP/TIFF/JPEG/GIF images
	// It can be RGBA8888, RGBA4444, RGB5_A1, RGB565
	// You can change anytime.
	[CCTexture2D setDefaultAlphaPixelFormat:kCCTexture2DPixelFormat_RGBA8888];
	
    // Do this after [Kamcord setDeviceOrientation:...];
    [window addSubview:[director openGLView]];
    [window makeKeyAndVisible];

	CCScene *scene = [CCScene node];

	MainLayer * mainLayer =[MainLayer node];
	
	[scene addChild: mainLayer];
	
	[scene runAction: [CCRotateBy actionWithDuration: 4 angle:-360]];
    
    [Kamcord startRecording];
    double delayInSeconds = 10.0;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [Kamcord stopRecording];
        [Kamcord showView];
    });
	
    [director runWithScene: scene];
}

// getting a call, pause the game
-(void) applicationWillResignActive:(UIApplication *)application
{
	[[CCDirector sharedDirector] pause];
    [Kamcord pause];
}

// call got rejected
-(void) applicationDidBecomeActive:(UIApplication *)application
{
    [Kamcord resume];
	[[CCDirector sharedDirector] resume];
}

-(void) applicationDidEnterBackground:(UIApplication*)application
{
	[[CCDirector sharedDirector] stopAnimation];
}

-(void) applicationWillEnterForeground:(UIApplication*)application
{
	[[CCDirector sharedDirector] startAnimation];
}

// application will be killed
- (void)applicationWillTerminate:(UIApplication *)application
{	
	CC_DIRECTOR_END();
}

// purge memory
- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application
{
	[[CCDirector sharedDirector] purgeCachedData];
}

// next delta time will be zero
-(void) applicationSignificantTimeChange:(UIApplication *)application
{
	[[CCDirector sharedDirector] setNextDeltaTimeZero:YES];
}

- (void) dealloc
{
	[window release];
	[super dealloc];
}

@end
