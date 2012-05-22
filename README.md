# cocos2d-kamcord 0.1.0 alpha


## Introduction

Kamcord is a built-in gameplay recording technology for iOS. This repository contains an SDK that works with Cocos2D-1.0.1. It allows you, the game developer, to capture gameplay videos with a very simple API.
Your users can then replay and share these gameplay videos via YouTube, Facebook, Twitter, and email.

In order to use Kamcord, you need a developer key and developer secret. To get a pair, please email Kevin at <a mailto="kevin@kamcord.com">kevin@kamcord.com</a>.

This is currently an alpha V0.1 build. We will be making lots of improvements over the next few months. We'd love to hear your feedback and thoughts. If you have any questions or comments, please don't hesitate to email Kevin.


## Installation

<ol>
<li style="margin: 0";>Clone this repository to your local development machine.</li>
<li style="margin: 0";>Drag and drop <code>cocos2d-kamcord.framework</code> into your project.</li>
<li style="margin: 0";>Under <code>Other Frameworks</code>, drag and drop <code>AWSiOSSDK.framework</code> into your project.</li>
<li style="margin: 0";">Drag and drop <code>Resources</code> to your project. <b>For steps 3-5, make sure to check the box next to the target application you want to link this library to (your game, presumably).</b></li>
<li style="margin: 0";>Ensure you have the following frameworks under <code>Build Phases</code> ==> <code>Link Binary With Libraries</code>:
	<p>
	<ul>
        <li style="margin: 0;">AVFoundation</li>
        <li style="margin: 0;"><b>AWSiOSSDK</b></li>
        <li style="margin: 0;"><b><i>cocos2d-kamcord</i></b></li>
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
    </ul>
    </p>

<p>
To add <code>cocos2d-kamcord.framework</code> and <code>AWSiOSSDK.framework</code> to this list, you cannot use the <code>[+]</code> button at the bottom of the <code>Link Binary With Libraries</code> section. Instead, drag <code>cocos2d-kamcord.framework</code> from your project to this list.
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
<li>We will provide you with a per-game Kamcord developer key and developer secret. Please be sure to set them when your app initializes or recording won't work:

<p>
<pre><code>[Kamcord setDeveloperKey:@"My_Developer_Key"];
[Kamcord setDeveloperSecret:@"My_Developer_Secret"];</code></pre>
</p>
</li>
<li style="margin: 0;">In your application delegate (or wherever you create the <code>UIWindow</code> and <code>EAGLView</code>), make sure <code>window.rootViewController</code> is set to an instance of <code>KCViewController</code>. Also set the view of that ViewController to your <code>EAGLView</code>.

<p>
<pre><code>window.rootViewController = [[KCViewController alloc] initWithNibName:nil bundle:nil];
window.rootViewController.view = glView; // Assuming glView is your EAGLView
[Kamcord setParentViewController:window.rootViewController];</code></pre>
<p>

<p>Kamcord uses UIKit for autorotation. For all practical purposes in your game, this doesn't affect anything. The one minor setup difference is, instead of using <code>[[CCDirector sharedDirector] setDeviceOrientation:...]</code> to set your device orientation, call <code>[Kamcord setDeviceOrientation:...]</code>. <b>Please make sure your </b><code>window.rootViewController</code><b> is an instance of </b><code>KCViewController</code><b> or its subclass.</b> If you can't do this, get in touch with Kevin at <a href="mailto:kevin@kamcord.com"">kevin@kamcord.com</a> and we'll help you with a simple workaround (a short chunk of code you can copy and paste into your own custom <code>UIViewController</code>).</p>

<p>
This must all be done before:

<pre><code>[window addSubview:glView];
[window makeKeyAndVisible];
</code></pre>
</p>
<p>
The full example further below lays this out very clearly.
</p>
</li>
</ol>

Your project should build successfully at this point.

## How to use Kamcord

We've tried to keep the Kamcord API as simple as possible. The only class you will need to interface with is `Kamcord`, which you can get by including `<cocos2d-1.0.1-kamcord/Kamcord.h>`.

Kamcord's public API is broken down by different functionalities.

### Video Recording

The recording interface is built around the concept of one video, which has one or more clips. Most videos will just have one clip, but if your game is interrupted for some reason, you'll have several clips that need to be stitched together into one seamless video. Kamcord handles all of that behind the scenes as long as you start and stop recording your clips at the appropriate places in the app lifecycle.

The API is:

    +(void) beginVideo;
    +(void) endVideo;
    +(void) startRecording;
    +(void) stopRecording;

`beginVideo` is first called to indicate the beginning of a new video. *<b>It does not begin the actual video recording</b>*. After that, `startRecording` and `stopRecording` start and stop the video recording. If you call `startRecording` without calling `beginVideo` first, nothing will happen. When the entire gameplay is over, for example after the user finishes a level, call `endVideo`.

### Presenting User Options

Now that that the user has finished his gameplay and you have successfully recorded a video of it, you can present several options to the user with the following API call:

	+(void) showView;

This presents a modal view with the following options:

<p>
<ul>
    <li style="margin: 0;">Replay video</li>
    <li style="margin: 0;">Share</li>
</ul>
</p>

`Replay video` will show the video of the gameplay that just happened (the result of the last `endVideo` call). 

`Share` will bring the user to a new view that lets them enter a message and select Facebook, Twitter, and/or email. When the user taps the `Share` button on this second view, we upload the video to our (Kamcord's) YouTube channel and share their message to their selected social networks or via email. The first time the user selects Facebook or Twitter, he will be prompted for the relevant credentials and permissions. 

On Facebook, we will share the URL of the video with their typed message. A thumbnail from the video will be automatically generated and shown. On Twitter, if the user types the following message:

`Check out my gameplay!`

the actual tweeted message will be

`Check out my gameplay! | http://www.kamcord.com/watch/abcfoobar123`

where the kamcord.com URL will instantly <a href="http://en.wikipedia.org/wiki/HTTP_302">HTTP 302</a> redirect to the corresponding YouTube video.

### Differences from Cocos2D

If your application's setup code calls `CC_DIRECTOR_INIT()` right now, replace it with `CC_DIRECTOR_INIT_KAMCORD()`.

### Developer Goodies

You as the developer can set defaults for when the user uploads to YouTube and shares to Facebook. A YouTube video looks like this:

<img src="http://dl.dropbox.com/u/6122/Kamcord/youtube_video2.png"/>

You can set the title, description, and keywords (highlighted in the orange boxes) with the following fybctuib:

	+(void) setYouTubeTitle:(NSString *)title
     	        description:(NSString *)description 
                   keywords:(NSString *)keywords;

`youtubeKeywords` is one string of word tokens delimited by spaces. A Facebook wall post looks like the following:

<img src="http://dl.dropbox.com/u/6122/Kamcord/facebook_share.png"/>

The `Message` is the text the user will enter. You can set the title, caption, and description with the following fybctuib:

	+(void) setFacebookTitle:(NSString *)title
   	                 caption:(NSString *)caption
                 description:(NSString *)description;

When the user shares to Facebook, their video is first uploaded to YouTube. We will then use your settings to populate the corresponding fields on YouTube and Facebook. Needless to say, this is a great way to advertise your game by putting links to your website or your game's page on the Apple App Store.

It's worth noting that every time we upload a video to YouTube and post to Facebook, we use the currently set values of these fields. Therefore, you may want to change the title, caption, and or description to match the results of the most recent gameplay (to add the score, for instance).

Lastly, we another function you should set after you call `endVideo`:

	+(void) setLevel:(NSString *)level
     	       score:(NSNumber *)score;
	
These values should be set per video. This metadata will be uploaded along with the video and in the future, we will offer a way to access this data to provide a better quality video viewing experience for your users.

### Developer Key and Secret

As we've mentioned before in the installation section, don't forget to set your Kamcord developer key and secret using this function:

	+(void) setDeveloperKey:(NSString *)key
	        developerSecret:(NSString *)secret;

We will give you a key and secret per game you build. We'll give you as many key/secret pairs you need, just don't tell them to anyone else.

## Examples

The `Examples` directory has some fully functional examples of how to use Kamcord in your application. You will recognize these as test apps that come bundled with Cocos2D. Right now, there are four tests that have been ported over to `cocos2d-kamcord`:

<ul>
    <li style="margin: 0;">ParticleTest</li>
    <li style="margin: 0;">RenderTextureTest</li>
    <li style="margin: 0;">RotateWorldTest</li>
    <li style="margin: 0;">SceneTest</li>
</ul>

### RenderTextureTest

When this app launches, there are two buttons on the top right of the screen you can press to start and stop video recording. Play around by pressing `Start Recording`, doing some drawing or flipping between different tests, and then pressing `Stop Recording`. The Kamcord dialog should pop up and you'll be able to replay your previous actions as well as share it online.

Below are all of the code integration points. We bold the lines we added to make Kamcord work. First, we do some initialization:

<pre><code>- (void) applicationDidFinishLaunching:(UIApplication*)application
{
	// Init the window
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	
	// must be called before any othe call to the director
	[CCDirector setDirectorType:kCCDirectorTypeDisplayLink];
	
	// before creating any layer, set the landscape mode
	CCDirector *director = [CCDirector sharedDirector];
	
	// set FPS at 60
	[director setAnimationInterval:1.0/60];
	
	// Display FPS: yes
	[director setDisplayFPS:YES];
	
	// Create an EAGLView with a RGB8 color buffer, and a depth buffer of 24-bits
	KCGLView *glView = [KCGLView viewWithFrame:[window bounds]
								   pixelFormat:kEAGLColorFormatRGB565
								   depthFormat:0];
    
    // Create root view controller
    window.rootViewController = [[KCViewController alloc] initWithNibName:nil bundle:nil];
    window.rootViewController.view = glView;
	
	// Tell Kamcord the root view controller and the OpenGL View.
    // It will pass on the OpenGL View to CCDirector, so you don't need to 
    // call [[CCDirector sharedDirector] setOpenGLView:glView];
    [Kamcord setParentViewController:window.rootViewController];
	[Kamcord setOpenGLView:glView];
    
    // Developer settings
    [Kamcord setDeveloperKey:@"kamcord-test"
             developerSecret:@"kamcord-test"];
    
    // Game orientation
    [Kamcord setDeviceOrientation:CCDeviceOrientationLandscapeRight];

    // Social media settings
    [Kamcord setYouTubeTitle:@"RenderTextureTest"
                 description:@"This is a Cocos2D test app that was recorded with Kamcord."
                    keywords:@"Cocos2D RenderTextureTest"];
    
    [Kamcord setFacebookTitle:@"RenderTextureTest"
                      caption:@"Kamcord recording"
                  description:@"This is a Cocos2D test app that was recorded with Kamcord."];
	
	// Enables High Res mode (Retina Display) on iPhone 4 and maintains low res on all other devices
	if( ![director enableRetinaDisplay:YES] )
		CCLOG(@"Retina Display Not supported");
	
	// make the OpenGLView a child of the main window
	[window addSubview:glView];
	
	// make main window visible
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
	[Kamcord beginVideo];
    [Kamcord startRecording];
}

-(void) stopRecordingAndShowDialog:(id)sender
{
	[Kamcord stopRecording];
    [Kamcord endVideo];
    [Kamcord showView];
}</b></code></pre>

For most games, you'll want to defer the calls to `beginVideo` and `startRecording` until appropriate (your user begins the actual level, etc.).

To highlight the handling of the application lifecycle, we've made additions to the following functions:

<pre><code>-(void) applicationWillResignActive:(UIApplication *)application
{
	[[CCDirector sharedDirector] pause];
    <b>[Kamcord stopRecording];</b>
}

-(void) applicationDidBecomeActive:(UIApplication *)application
{
    <b>[Kamcord startRecording];</b>
	[[CCDirector sharedDirector] resume];
}
</code></pre>

That's all you have to do to manage the applicaton lifecycle. If no video is currently being recorded (i.e. `beginVideo` has not been called), the calls to `startRecording` and `stopRecording` do nothing.

To test this functionality, press `Start Recording`, play with the app, then close it by pressing the home button. Re-open the app, do some more actions, then press `Stop Recording`. When the Kamcord dialog appears, select `Replay Video`. It should show one seamless video of everything that's happened.

<b>Note: in your game, you should defer calling</b> `startRecording` <b>until your user resumes gameplay. Calling it in</b> `applicationDidBecomeActive:` <b>like in this example will capture the pause screen of your game, which is probably not what you or your user wants.</b>

## Contact Us

If you have any questions or comments, don't hesitate to email Kevin at <a href="mailto:kevin@kamcord.com">kevin@kamcord.com</a>. We reply to every email usually within a couple of hours, if not sooner.

