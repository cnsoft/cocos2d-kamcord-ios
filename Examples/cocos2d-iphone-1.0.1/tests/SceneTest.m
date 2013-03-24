//
// Scene demo
// a cocos2d example
// http://www.cocos2d-iphone.org
//

#import "SceneTest.h"

#import <Kamcord/Kamcord.h>

#pragma mark -
#pragma mark Layer1

@implementation Layer1
-(id) init
{
	if( (self=[super initWithColor: ccc4(0,255,0,255)]) ) {
	
		
		CCMenuItemFont *item1 = [CCMenuItemFont itemFromString: @"Test pushScene" target:self selector:@selector(onPushScene:)];
		CCMenuItemFont *item2 = [CCMenuItemFont itemFromString: @"Test pushScene w/transition" target:self selector:@selector(onPushSceneTran:)];
		CCMenuItemFont *item3 = [CCMenuItemFont itemFromString: @"Quit" target:self selector:@selector(onQuit:)];
		
		CCMenu *menu = [CCMenu menuWithItems: item1, item2, item3, nil];
		[menu alignItemsVertically];
		
		[self addChild: menu];

		CGSize s = [CCDirector sharedDirector].winSize;
		CCSprite *sprite = [CCSprite spriteWithFile:@"grossini.png"];
		[self addChild:sprite];
		sprite.position = ccp(s.width-40, s.height/2);
		id rotate = [CCRotateBy actionWithDuration:2 angle:360];
		id repeat = [CCRepeatForever actionWithAction:rotate];
		[sprite runAction:repeat];
		
		
		[self schedule:@selector(testDealloc:)];
	}

	return self;
}

-(void) onEnter
{
	NSLog(@"Layer1#onEnter");
	[super onEnter];
}

-(void) onEnterTransitionDidFinish
{
	NSLog(@"Layer1#onEnterTransitionDidFinish");
	[super onEnterTransitionDidFinish];
}

-(void) cleanup
{
	NSLog(@"Layer1#cleanup");
	[super cleanup];
}

-(void) testDealloc:(ccTime) dt
{
	NSLog(@"Layer1:testDealloc");
}

-(void) dealloc
{
	NSLog(@"Layer1 - dealloc");
	[super dealloc];
}

-(void) onPushScene: (id) sender
{
	CCScene * scene = [CCScene node];
	[scene addChild: [Layer2 node] z:0];
	[[CCDirector sharedDirector] pushScene: scene];
//	[[Director sharedDirector] replaceScene:scene];
}

-(void) onPushSceneTran: (id) sender
{
	CCScene * scene = [CCScene node];
	[scene addChild: [Layer2 node] z:0];
	[[CCDirector sharedDirector] pushScene: [CCTransitionSlideInT transitionWithDuration:1 scene:scene]];
}


-(void) onQuit: (id) sender
{
	[[CCDirector sharedDirector] popScene];

	// HA HA... no more terminate on sdk v3.0
	// http://developer.apple.com/iphone/library/qa/qa2008/qa1561.html
	if( [[UIApplication sharedApplication] respondsToSelector:@selector(terminate)] )
		[[UIApplication sharedApplication] performSelector:@selector(terminate)];
}

-(void) onVoid: (id) sender
{
}
@end

#pragma mark -
#pragma mark Layer2

@implementation Layer2
-(id) init
{
	if( (self=[super initWithColor: ccc4(255,0,0,255)]) ) {
	
		timeCounter = 0;

		CCMenuItemFont *item1 = [CCMenuItemFont itemFromString: @"replaceScene" target:self selector:@selector(onReplaceScene:)];
		CCMenuItemFont *item2 = [CCMenuItemFont itemFromString: @"replaceScene w/transition" target:self selector:@selector(onReplaceSceneTran:)];
		CCMenuItemFont *item3 = [CCMenuItemFont itemFromString: @"Go Back" target:self selector:@selector(onGoBack:)];
		
		CCMenu *menu = [CCMenu menuWithItems: item1, item2, item3, nil];
		[menu alignItemsVertically];
		
		[self addChild: menu];
		
		[self schedule:@selector(testDealloc:)];
		
		CGSize s = [CCDirector sharedDirector].winSize;
		CCSprite *sprite = [CCSprite spriteWithFile:@"grossini.png"];
		[self addChild:sprite];
		sprite.position = ccp(40, s.height/2);
		id rotate = [CCRotateBy actionWithDuration:2 angle:360];
		id repeat = [CCRepeatForever actionWithAction:rotate];
		[sprite runAction:repeat];		
	}

	return self;
}

-(void) dealloc
{
	NSLog(@"Layer2 - dealloc");
	[super dealloc];
}

-(void) testDealloc:(ccTime) dt
{
	NSLog(@"Layer2:testDealloc");

	timeCounter += dt;
	if( timeCounter > 10 )
		[self onReplaceScene:self];
}

-(void) onGoBack:(id) sender
{
	[[CCDirector sharedDirector] popScene];
}

-(void) onReplaceScene:(id) sender
{
	CCScene *scene = [CCScene node];
	[scene addChild: [Layer3 node] z:0];
	[[CCDirector sharedDirector] replaceScene: scene];
}
-(void) onReplaceSceneTran:(id) sender
{
	CCScene *s = [CCScene node];
	[s addChild: [Layer3 node] z:0];
	[[CCDirector sharedDirector] replaceScene: [CCTransitionFlipX transitionWithDuration:2 scene:s]];
}
@end

#pragma mark -
#pragma mark Layer3

@implementation Layer3
-(id) init
{
	if( (self=[super initWithColor: ccc4(0,0,255,255)]) ) {
		self.isTouchEnabled = YES;
		id label = [CCLabelTTF labelWithString:@"Touch to popScene" fontName:@"Marker Felt" fontSize:32];
		[self addChild:label];
		CGSize s = [[CCDirector sharedDirector] winSize];
		[label setPosition:ccp(s.width/2, s.height/2)];
		
		[self schedule:@selector(testDealloc:)];
		
		CCSprite *sprite = [CCSprite spriteWithFile:@"grossini.png"];
		[self addChild:sprite];
		sprite.position = ccp(s.width/2, 40);
		id rotate = [CCRotateBy actionWithDuration:2 angle:360];
		id repeat = [CCRepeatForever actionWithAction:rotate];
		[sprite runAction:repeat];		
		
	}
	return self;
}

- (void) dealloc
{
	NSLog(@"Layer3 - dealloc");
	[super dealloc];
}

-(void) testDealloc:(ccTime)dt
{
	NSLog(@"Layer3:testDealloc");
}
- (void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	[[CCDirector sharedDirector] popScene];
}
@end


#pragma mark -
#pragma mark AppController

// CLASS IMPLEMENTATIONS
@implementation AppController

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
                     appName:@"SceneTest"];
    
    // Social media settings
    [Kamcord setYouTubeDescription:@"This is a Cocos2D test app that was recorded with Kamcord."
                              tags:@"Cocos2D RotateWorldTest"];
    
    [Kamcord setFacebookTitle:@"SceneTest"
                      caption:@"Kamcord recording"
                  description:@"This is a Cocos2D test app that was recorded with Kamcord."];

    [Kamcord setVideoResolution:MEDIUM_VIDEO_RESOLUTION];
	
	// Enables High Res mode (Retina Display) on iPhone 4 and maintains low res on all other devices
	if( ! [director enableRetinaDisplay:YES] )
		CCLOG(@"Retina Display Not supported");
	
	// Turn on display FPS
	[director setDisplayFPS:YES];
	
	// Default texture format for PNG/BMP/TIFF/JPEG/GIF images
	// It can be RGBA8888, RGBA4444, RGB5_A1, RGB565
	// You can change anytime.
	[CCTexture2D setDefaultAlphaPixelFormat:kCCTexture2DPixelFormat_RGBA8888];
    
    // Do this after [Kamcord setDeviceOrientation:...];
    [window addSubview:[director openGLView]];
    [window makeKeyAndVisible];
	
	CCScene *scene = [CCScene node];

	[scene addChild: [Layer1 node] z:0];
	
	[director runWithScene: scene];
    
    [Kamcord startRecording];
    double delayInSeconds = 10.0;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [Kamcord stopRecording];
        [Kamcord showView];
    });
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
