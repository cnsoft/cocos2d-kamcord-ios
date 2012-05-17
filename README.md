# cocos2d-kamcord 0.1.0 alpha


## Introduction

Kamcord is a built-in gameplay recording technology for iOS. This repository contains a custom build of <b>Cocos2d-1.0.1</b> modified to include Kamcord technology. It allows you, the game developer, to capture gameplay videos with a very simple API.
Your users can then replay, save, and share these gameplay videos via YouTube, Facebook, Twitter, and email.

In order to use Kamcord, you need an API key. To get one, please email Kevin at <a mailto="kevin@kamcord.com">kevin@kamcord.com</a>.

This is currently an alpha V0.1 build. We will be making lots of improvements over the next few months. We'd love to hear your feedback and thoughts. If you have any questions or comments, please don't hesitate to email Kevin.


## Installation

<ol>
<li style="margin: 0";>Remove libcocos2d.a from your project. The framework you are about to install includes all Cocos2D-1.0.1 features and functionalities.</li>
<li style="margin: 0";>Clone this repository to your local development machine.</li>
<li style="margin: 0";>Drag and drop <code>cocos2d-kamcord.framework</code> into your project.</li>
<li style="margin: 0";">Drag and drop <code>Resources</code> and <code>External-headers</code> to your project. <b>When you do, make sure to check the box next to the target application you want to link this library to (your game, presumably).</b></li>
<li style="margin: 0";>Ensure you have the following frameworks under <code>Build Phases</code> ==> <code>Link Binary With Libraries</code>:
	<p>
	<ul>
        <li style="margin: 0;">AVFoundation</li>
        <li style="margin: 0;">AWSiOSSDK</li>
        <li style="margin: 0;">cocos2d-kamcord</li>
        <li style="margin: 0;">CoreGraphics</li>
        <li style="margin: 0;">CoreMedia</li>
        <li style="margin: 0;">CoreVideo</li>
        <li style="margin: 0;">Foundation</li>
        <li style="margin: 0;">MediaPlayer</li>
        <li style="margin: 0;">MessageUI</li>
        <li style="margin: 0;">OpenGLES</li>
        <li style="margin: 0;">QuartzCore</li>
        <li style="margin: 0;">Security</li>
        <li style="margin: 0;">SystemConfiguration</li>
        <li style="margin: 0;">Twitter</li>
        <li style="margin: 0;">UIKit</li>
        <li style="margin: 0;">libz.dylib</li>
    </ul>
    </p>

<p>
To add <code>cocos2d-kamcord.framework</code> to this list, you cannot use the <code>[+]</code> button at the bottom of the <code>Link Binary With Libraries</code> section. Instead, drag <code>cocos2d-kamcord.framework</code> from your project to this list.
</p>

<p>
<img src="http://dl.dropbox.com/u/6122/Kamcord/xcode%20cocos2d-kamcord.framework.png"/>
</p>

</li>
<li style="margin: 0;">Add the following to <code>Build Settings</code> ==> <code>Other Linker Flags</code>:
	<p>
    <ul style="margin-bottom: 15px;">
        <li style="margin: 0;">-ObjC</li>
        <li style="margin: 0;">-all_load</li>
    </ul>
    </p>
    <p>
    <img src="http://dl.dropbox.com/u/6122/Kamcord/other_linker_flags.png"/>
    </p>
</li>
<li>We will provide you guys with a Kamcord developer key and developer secret. Please be sure to set them when your app initializes or recording won't work:

<p>
<pre><code>[[KCManager sharedManager] setDeveloperKey:@"My_Developer_Key"
							setDeveloperSecret:@"My_Developer_Secret"];</code></pre>
</p>
</li>
<li style="margin: 0;">In your application delegate (or wherever you create the <code>UIWindow</code> and <code>EAGLView</code>), make sure `window.rootViewController` is set to an instance of `KCViewController`. Also set the view of that ViewController to your <code>EAGLView</code>.

<p>
<pre><code>window.rootViewController = [[KCViewController alloc] initWithNibName:nil bundle:nil];
window.rootViewController.view = glView; // Assuming glView is your EAGLView
[[KCManager sharedManager] setParentViewController:window.rootViewController];</code></pre>
<p>

<p>Kamcord uses UIKit autorotation. For all practical purposes in your game, this doesn't affect anything. Set your game orientation as you do normally with <code>[[CCDirector sharedDirector] setDeviceOrientation:…]</code>.<b>You just need to make sure your </b><code>window.rootViewController</code><b> is an instance of </b><code>KCViewController</code><b> or its subclass.</b> If you cannot do this, get in touch with Kevin at <a href="mailto:kevin@kamcord.com"">kevin@kamcord.com</a> or call him at (631) 252-3176 any time of day and we'll help you with a simple workaround.</p>

<p>
This must all be done before:

<pre><code>[window addSubview:glView];
[window makeKeyAndVisible];</code></pre>
	
The full example further below lays this out very clearly.
</p>
</li>
</ol>

Your project should build successfully at this point.

## How to use Kamcord

We've tried to keep the Kamcord API as simple as possible. The only class you will need to interface with is `KCManager`, which is automatically included for you in `cocos2d.h`. To get an instance, call `[KCManager sharedManager]`.

KCManager's public API is broken down by different functionalities.

### Video Recording

The recording interface is built around the concept of one video, which has one or more clips. Most videos will just have one clip, but if your game is interrupted for some reason, you'll have several clips that need to be stitched together into one seamless video. Kamcord handles all of that behind the scenes as long as you start and stop recording your clips at the appropriate places in the app lifecycle.

The API is:

    -(void) beginVideo;
    -(void) endVideo;
    -(void) startRecordingClip;
    -(void) stopRecordingClip;

`beginVideo` is first called to indicate the beginning of a new video. *<b>It does not begin the actual video recording</b>*. After that, `startRecordingClip` and `stopRecordingClip` start and stop the video recording. If you call `startRecording` without calling `beginVideo` first, nothing will happen. When the entire gameplay is over, for example after the user finishes a level, call `endVideo`. An example flow is as follows:

    [[KCManager sharedManager] beginVideo];
    [[KCManager sharedManager] startRecordingClip];
    
    //
    // Gameplay happens
    //
    
    [[KCManager sharedManager] stopRecordingClip];
    
    ///
    // Application interrupted
    // ...
    // Application regains foreground and user resumes gameplay    
    //
    
    [[KCManager sharedManager] startRecordingClip];
    
    // 
    // More gamplay happens until round ends
    //  
    
    [[KCManager sharedManager] stopRecordingClip];
    [[KCManager sharedManager] endVideo];

In this example, the developer recorded two clips that will be contiguously stitched together. He may have stopped the first clip to handle a phone call and started the second clip as soon as the user returned to the app and resumed gameplay. After `endVideo` is called, Kamcord understands that there were two clips and combines them into one video. You can then present the user with more options, which are described in the next section.


### Presenting User Options

Now that that the user has finished his gameplay and you have successfully recorded a video of it, you can present several options to the user with the following API call:

	-(void) showKamcordView;

This presents a modal view with the following options:

<p>
<ul>
    <li style="margin: 0;">Replay video</li>
    <li style="margin: 0;">Share</li>
</ul>
</p>

`Replay video` will show the video of the gameplay that just happened (the result of the last `endVideo` call). 

`Share` will bring the user to a new view that lets them enter a message and select Facebook, Twitter, and/or email. When the user taps the `Share` button on this second view, we upload the video to YouTube and share their message to their selected social networks or email. The first time the user selects Facebook or Twitter, he will be prompted for the relevant credentials and permissions. 

On Facebook, we will share the URL of the video with their typed message. A thumbnail from the video will be automatically generated and shown. On Twitter, if the user types the following message:

`Check out my XYZ gameplay!`

the actual tweeted message will be

`Check out my XYZ gameplay! | http://www.kamcord.com/watch/abcfoobar123`

where the kamcord.com URL will instantly <a href="http://en.wikipedia.org/wiki/HTTP_302">HTTP 302</a> redirect to the corresponding YouTube video.

### Differences from Cocos2D

If your application's setup code calls `CC_DIRECTOR_INIT()` right now, you'll need to replace it with `CC_DIRECTOR_INIT_KAMCORD_SAFE()` and add the following two lines later in your app delegate's `applicationDidFinishLaunching`:

	[window addSubview:[[CCDirector sharedDirector] openGLView]];
	[window makeKeyAndVisible];

A simple example illustrating this is in `Examples/SceneTest.m:applicationDidFinishLaunching`.

### Developer Goodies

You as the developer can set defaults for when the user uploads to YouTube and shares to Facebook. A YouTube video looks like this:

<img src="http://dl.dropbox.com/u/6122/Kamcord/youtube_video2.png"/>

You can set the title, description, and tags (highlighted in the orange boxes) with the following API call:

	-(void) setYouTubeUploadDefaultTitle:(NSString *)title
	                  defaultDescription:(NSString *)description
	                            keywords:(NSString *)keywords;

A Facebook wall post looks like the following:

<img src="http://dl.dropbox.com/u/6122/Kamcord/facebook_share.png"/>

The `Message` is the text the user will enter. You can set the title, caption, and description with the following API call:

	-(void) setFacebookShareTitle:(NSString *)title
	                      caption:(NSString *)caption
	                  description:(NSString *)description;


When the user shares to Facebook, their video is first uploaded to YouTube. These strings will be used to pre-populate the corresponding fields on YouTube and Facebook. Needless to say, this is a great way to advertise your game by putting links to your website or your game's page on the Apple app store.


## Examples

The `Examples` directory has a fully functional example of how to use Kamcord in your application. It is a slightly modified version of `RenderTextureTest` from the cocos2d test suite. When the app launches, there are two buttons on the top right of the screen you can press to start and stop video recording.

Below are all of the code integration points. We bold the lines we added to make Kamcord work. First, we do some initialization:

<pre><code>- (void) applicationDidFinishLaunching:(UIApplication*)application
{
	// Init the window
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	
	// must be called before any othe call to the director
	[CCDirector setDirectorType:kCCDirectorTypeDisplayLink];
	
	// before creating any layer, set the landscape mode
	CCDirector *director = [CCDirector sharedDirector];
	
	// Landscape orientation
	<b>// Set as you normally do</b>
	[director setDeviceOrientation:CCDeviceOrientationLandscapeRight];
	
	// set FPS at 60
	[director setAnimationInterval:1.0/60];
	
	// Display FPS: yes
	[director setDisplayFPS:YES];
	
	// Create an EAGLView with a RGB8 color buffer, and a depth buffer of 24-bits
	EAGLView *glView = [EAGLView viewWithFrame:[window bounds]
								   pixelFormat:kEAGLColorFormatRGB565
								   depthFormat:0];
	
	// attach the openglView to the director
	[director setOpenGLView:glView];
	
	// Enables High Res mode (Retina Display) on iPhone 4 and maintains low res on all other devices
	if( ! [director enableRetinaDisplay:YES] )
		CCLOG(@"Retina Display Not supported");
    <b>
    // Set the window's root view controller to an instance or subclass
    // of KCViewController
    window.rootViewController = [[KCViewController alloc] initWithNibName:nil bundle:nil];
    window.rootViewController.view = glView;
    [[KCManager sharedManager] setParentViewController:window.rootViewController];
    [[KCManager sharedManager] setYouTubeUploadDefaultTitle:@"RenderTexture Test"
                                         defaultDescription:@"Testing Kamcord 0.1"
                                                   keywords:@"cocos2d"];
    
    [[KCManager sharedManager] setFacebookShareTitle:@"RenderTexture Test"
                                             caption:@"Testing Kamcord"
                                         description:@"It's a test!"];
    
    [[KCManager sharedManager] setDeveloperKey:@"Key123"
                               developerSecret:@"Secret123"];
    </b>
	// Make the OpenGLView a child of the main window and make the main window visible.
	<b>// Must do this AFTER setting the window's rootViewController.</b>
	[window addSubview:glView];
	[window makeKeyAndVisible];		
	
	// Default texture format for PNG/BMP/TIFF/JPEG/GIF images
	// It can be RGBA8888, RGBA4444, RGB5_A1, RGB565
	// You can change anytime.
	[CCTexture2D setDefaultAlphaPixelFormat:kCCTexture2DPixelFormat_RGBA8888];
	
	CCScene *scene = [CCScene node];
	[scene addChild: [nextAction() node]];

	[director runWithScene: scene];
}</code></pre>

This code sets up the window's root view controller and gives it ownership of the `EAGLView`. It then begins a new video and starts recording the scene. The `Start Recording` and `Stop Recording` buttons in the app are hooked in as follows:

<pre><code>@implementation KamcordRecording
-(id) init
{
	if( (self = [super init]) ) {
		
		CGSize s = [[CCDirector sharedDirector] winSize];	
		
		// create a render texture, this is what we're going to draw into
		target = [[CCRenderTexture renderTextureWithWidth:s.width height:s.height] retain];
		[target setPosition:ccp(s.width/2, s.height/2)];
		
		
		// It's possible to modify the RenderTexture blending function by
		// [[target sprite] setBlendFunc:(ccBlendFunc) {GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];
		
		// note that the render texture is a CCNode, and contains a sprite of its texture for convience,
		// so we can just parent it to the scene like any other CCNode
		[self addChild:target z:-1];
		
		// create a brush image to draw into the texture with
		brush = [[CCSprite spriteWithFile:@"fire.png"] retain];
		[brush setOpacity:20];
#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
		self.isTouchEnabled = YES;
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)
		self.isMouseEnabled = YES;
		lastLocation = CGPointMake( s.width/2, s.height/2);
#endif
		
		[CCMenuItemFont setFontSize:16];
		<b>CCMenuItem *item1 = [CCMenuItemFont itemFromString:@"Start Recording" target:self selector:@selector(startRecording:)];
		CCMenuItem *item2 = [CCMenuItemFont itemFromString:@"Stop Recording" target:self selector:@selector(stopRecordingAndShowDialog:)];</b>
		CCMenu *menu = [CCMenu menuWithItems:item1, item2, nil];
		[self addChild:menu];
		[menu alignItemsVertically];
		[menu setPosition:ccp(s.width-80, s.height-30)];
	}
	return self;
}

<b>-(void) startRecording:(id)sender
{
	[[KCManager sharedManager] beginVideo];
    [[KCManager sharedManager] startRecordingClip];
}

-(void) stopRecordingAndShowDialog:(id)sender
{
	[[KCManager sharedManager] stopRecordingClip];
    [[KCManager sharedManager] endVideo];
    [[KCManager sharedManager] showKamcordView];
}</b></code></pre>

For most games, you'll want to defer the calls to `beginVideo` and `startRecordingClip` until appropriate (your user begins the actual round, etc.).

To highlight the handling of the application lifecycle, we've made additions to the following functions:

<pre><code>-(void) applicationDidBecomeActive:(UIApplication *)application
{
    <b>[[KCManager sharedManager] startRecordingClip];</b>
	[[CCDirector sharedDirector] resume];
}

-(void) applicationDidEnterBackground:(UIApplication*)application
{
	[[CCDirector sharedDirector] stopAnimation];
    <b>[[KCManager sharedManager] stopRecordingClip];</b>
}</code></pre>

That's all you have to do to manage the applicaton lifecycle. If no video is currently being recorded (i.e. `beginVideo` has not been called), the calls to `startRecordingClip` and `stopRecordingClip` do nothing.

To test this functionality, press `Start Recording`, play with the app, then close it by pressing the home button. Re-open the app, do some more actions, then press `Stop Recording`. When the Kamcord dialog appears, select `Replay Video`. It should show one seamless video of everything that's happened.