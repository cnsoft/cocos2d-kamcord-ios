# cocos2d-kamcord 0.1.0 alpha


## Introduction

Kamcord is a built-in gameplay recording technology for iOS. This repository contains a Kamcord SDK that works with Cocos2D-1.0.1 and allows you, the game developer, to capture gameplay videos with a very simple API.
Your users can then replay and share these gameplay videos via YouTube, Facebook, Twitter, and email.

In order to use Kamcord, you need a developer key and developer secret. To get these, please email Kevin at <a mailto="kevin@kamcord.com">kevin@kamcord.com</a>.

**Kamcord works on iOS 5 and above**. You can still will run without problems on older versions of iOS, though you will not be able to to record video. Kamcord works on the iPhone 3GS, iPhone 4, iPhone 4S, iPod Touch 3G and 4G, and all iPads.

This is currently an alpha 0.1.0 build. We will be making lots of improvements and adding many features over the next few months. We'd love to hear your feedback and thoughts. If you have any questions or comments, please don't hesitate to <a href="mailto:kevin@kamcord.com"/>contact us</a>.

## A Sample Application

Before we explain how to use Kamcord in your own applications, let's go through a quick example that runs right out the box. Clone this repository to your local machine and open the project located at `Examples/cocos2d-iphone-1.0.1/cocos2d-ios.xcodeproj`.  Select `RotateWorldTest` from the dropdown and build and run that application. You should see the familiar `RotateWorldTest` from the Cocos2D suite of tests. **Make sure to run the application on a physical device with iOS 5+, not the simulator. Video replay is NOT supported by the simulator!**

After 10 seconds, the Kamcord view should appear allowing you to replay a video recording of those first 10 seconds and share that video via Facebook, Twitter, and/or email. `ParticleTest`, `SceneTest`, and `SpriteTest` all work the same way.

`RenderTextureTest` is different in that it allows you to start and stop recording by pressing the two corresponding buttons at the top right of the screen. When you press `Stop Recording`, you will again see the Kamcord view with options to replay and share. Later on in this documentation, we'll walk through all the code needed to add recording and replay functionalities to `RenderTextureTest`.

There is no practical limit on how long you can record for. Everything gets written immediately to disk and old videos are always being erased, so the only real limitation is the device's hard drive size. Since modern iOS devices have 16+ GB of hard disk space, you can safely record one continuous gameplay video for over 24 hours straight, an upper limit your gamers will probably never run into.


## Installation

Let's walk through how to get Kamcord into your games.

### Framework

<ol>
<li style="margin: 0";>From <code>Frameworks</code>, drag and drop <code>Kamcord.framework</code> and <code>AWSiOSSDK.framework</code> into your project.</li>
<li style="margin: 0";>Drag and drop the files under <code>Frameworks/Resources</code> to your project. For both this and the previous step, make sure to check the box next to the target application you want to link these frameworks and resources to (your game, presumably).</li>
<li style="margin: 0";>Ensure you have the following frameworks under <code>Build Phases</code> ==> <code>Link Binary With Libraries</code>:
	<p>
	<ul style="margin-top: 15px; margin-bottom: 15px;">
		<li style="margin: 0;">Accounts</li>
        <li style="margin: 0;">AVFoundation</li>
        <li style="margin: 0;"><b>AWSiOSSDK</b></li>
        <li style="margin: 0;">CoreGraphics</li>
        <li style="margin: 0;">CoreMedia</li>
        <li style="margin: 0;">CoreVideo</li>
        <li style="margin: 0;">Foundation</li>
        <li style="margin: 0;"><b>Kamcord</b></li>
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
    <img src="http://dl.dropbox.com/u/6122/Kamcord/Frameworks.png" />
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
</ol>

### Code

<ol>
<li>
<p>
Import Kamcord into your application delegate:

<pre><code>#import &lt;Kamcord/Kamcord.h&gt;
</code></pre>
</p>
</li>
<li>We will provide you with a per-game Kamcord developer key and developer secret. <b>Please set them when your app initializes or recording won't work</b>:

<p>
<pre><code>[Kamcord setDeveloperKey:@"My_Developer_Key"
         developerSecret:@"My_Developer_Secret"];</code></pre>
</p>
</li>
<li style="margin: 0;">
<p>
In your application delegate (or wherever you create the <code>UIWindow</code> and initialize <code>CCDirector</code>), instantiate a <code>KCGLView</code>. This is our special sublcass of <code>EAGLView</code> that aids in video recording. Then set <code>window.rootViewController</code> to an instance of <code>KCViewController</code> and set <code>window.rootViewController.view</code> to your <code>KCGLView</code>
</p>
<p>
<b>Also be sure to use </b><code>[Kamcord setDeviceOrientation:...]</code> <b>instead of</b> <code>[director setDeviceOrientation:...]</code>:
</p>

<p>
<pre><code>// Instantiate a KCGLView, which is a subclass with EAGLView with
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

// Set the device orientation. <b>Must use Kamcord, not CCDirector!</b>
[Kamcord setDeviceOrientation:CCDeviceOrientationLandscapeLeft];
</code></pre>
</p>
<p>
This must all be done before:

<pre><code>[window addSubview:glView];
[window makeKeyAndVisible];
</code></pre>
</p>
<p>
The full examples further below lay this out very clearly.
</p>
</li>
</ol>

Your project should build successfully at this point.

## How to use Kamcord

We've tried to keep the Kamcord API as simple as possible. The only class you will need to interface with is `Kamcord`, which you can get by including `<Kamcord/Kamcord.h>`.

Kamcord's public API is broken down by different functionalities.

### Video Recording

The recording interface is built around the concept of one video, which has one or more clips. Most videos will just have one clip, but if your game is interrupted (for example, if the user gets a phone call), you'll have several clips that need to be stitched together into one seamless video. Kamcord handles all of that behind the scenes as long as you pause and resume your recording at the appropriate places in the app lifecycle.

The API is:

    +(void) startRecording;
    +(void) stopRecording;
    +(void) pause;
    +(void) resume;

`startRecording` starts the video recording, which you can pause and resume with `pause` and `resume`. Once you're done with the entire video, call `stopRecording`.

**Please be aware that video replay will NOT work in the simulator! The video will be recorded and it will be the right length, but it will be all black. You must test on a device to see the video replay actually work.**

### Video Quality

You can also set the dimensions and quality of the recorded video:

	+(void) setVideoDimensions:(enum KC_VIDEO_DIMENSIONS)dimensions
	    	           quality:(enum KC_VIDEO_QUALITY)quality;

There are two video dimension settings: `VIDEO_DIMENSIONS_FULL` and `VIDEO_DIMENSIONS_HALF`. The first keeps the original rendered pixel dimensions while the second reduces the width and height by two, effectively reducing the video size by 4. The two video quality settings are `VIDEO_QUALITY_HIGH` and `VIDEO_QUALITY_MEDIUM`.

Keep in mind that videos that are larger and have higher quality will take much longer to process and upload, potentially making for a worse user experience. We recommend running with either `VIDEO_DIMENSIONS_FULL` and `VIDEO_QUALITY_MEDIUM` (the default) or `VIDEO_DIMENSIONS_HALF` and `VIDEO_QUALITY_HIGH`. You should experiment with different combinations to see what works best for your games.


### Presenting User Options

Now that the user has finished his gameplay and you have successfully recorded a video of it, you can present several options to the user with the following API call:

	+(void) showView;

This presents a modal view with the following options:

<p>
<ul>
    <li style="margin: 0;">Replay video</li>
    <li style="margin: 0;">Share</li>
</ul>
</p>

`Replay video` will show the video of the gameplay that just happened (the result of the last `stopRecording` call). 

`Share` will bring the user to a new view that lets them enter a message and select Facebook, Twitter, and/or email. When the user taps the `Share` button on this second view, we upload the video to our (Kamcord's) YouTube channel and share their message to their selected social networks or via email. The first time the user selects Facebook or Twitter, he will be prompted for the relevant credentials and permissions. 

On Facebook, we will share the URL of the video with their typed message. A thumbnail from the video will be automatically generated and shown. On Twitter, if the user types the following message:

`Check out my gameplay!`

the actual tweeted message will be

`Check out my gameplay! | kamcord.com/v/abcfoobar123`

where the kamcord.com URL will instantly <a href="http://en.wikipedia.org/wiki/HTTP_302">HTTP 302</a> redirect to the corresponding YouTube video.

### Differences from Cocos2D

If your application's setup code calls `CC_DIRECTOR_INIT()`, replace it with `CC_DIRECTOR_INIT_KAMCORD()` and add the following two lines after `[Kamcord setDeviceOrientation:...]` is called:

	[window addSubview:[[CCDirector sharedDirector] openGLView];
    [window makeKeyAndVisible];
    
`ParticleTest`, `RotateWorldTest`, `SceneTest`, and `SpriteTest` all show how to use `CC_DIRECTOR_INIT_KAMCORD()`. Their source code can be found in `Examples/cocos2d-iphone-1.0.1/tests`.

Kamcord uses <a href="http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:autorotation#the_uikit_autorotation"/>UIKit for autorotation</a>. <b>To ensure everything works as advertised, please make your </b>`window.rootViewController` <b>an instance of </b>`KCViewController` and use

	[Kamcord setDeviceOrientation:...]

instead of `[[CCDirector sharedDirector] setDeviceOrientation:...]`. If you cannot make ur `window.rootViewController` an instance of `KCViewController`, <a href="mailto:kevin@kamcord.com" />let us know</a> and we'll give you a simple patch for your View Controller code.

### Developer Settings

A YouTube video looks like this:

<img src="http://dl.dropbox.com/u/6122/Kamcord/youtube_video2.png"/>

You can set the title, description, and keywords (highlighted in the orange boxes) with the following function:

	+(void) setYouTubeTitle:(NSString *)title
     	        description:(NSString *)description 
                   keywords:(NSString *)keywords;

`youtubeKeywords` is one string of word tokens delimited by commas (e.g. `"multi-word keyword, another multiword keyword, keyword3, keyword4"`).

A Facebook wall post looks like the following:

<img src="http://dl.dropbox.com/u/6122/Kamcord/facebook_share.png"/>

The `Message` is the text the user will enter. You can set the title, caption, and description with the following function:

	+(void) setFacebookTitle:(NSString *)title
   	                 caption:(NSString *)caption
                 description:(NSString *)description;

When the user shares to Facebook, their video is first uploaded to YouTube. We will then use your settings to populate the corresponding fields on YouTube and Facebook. Needless to say, this is a great way to advertise your game by putting links to your website or your game's page on the Apple App Store.

It's worth noting that every time we upload a video to YouTube and post to Facebook, we use the currently set values of these fields. Therefore, you may want to change the title, caption, and or description to match the results of the most recent gameplay. We recommend you do this so that the message looks more customized which should result in more clicks on the video.

Another function you need to set after you call `stopRecording` is:

	+(void) setLevel:(NSString *)level
     	       score:(NSNumber *)score;
	
These values should be set per video. This metadata will be uploaded along with the video and be used to better organize videos for viewers.

### Developer Key and Secret

As we've mentioned before in the installation section, don't forget to set your Kamcord developer key and secret using this function:

	+(void) setDeveloperKey:(NSString *)key
	        developerSecret:(NSString *)secret;

We will give you a key and secret per game you build. We'll give you as many key/secret pairs you need, just don't tell them to anyone else.

## Examples

The `Examples` directory has some fully functional examples of how to use Kamcord in your application. You will recognize these as test apps that come bundled with Cocos2D. The following test apps have been ported over to `Kamcord`:

<ul>
    <li style="margin: 0;">ParticleTest</li>
    <li style="margin: 0;">RenderTextureTest</li>
    <li style="margin: 0;">RotateWorldTest</li>
    <li style="margin: 0;">SceneTest</li>
    <li style="margin: 0;">SpriteTest</li>
</ul>

### RenderTextureTest

When this app launches, there are two buttons on the top right of the screen you can press to start and stop video recording. Play around by pressing `Start Recording`, doing some drawing or flipping between different tests, and then pressing `Stop Recording`. The Kamcord dialog should pop up and you'll be able to replay a video recording of your actions as well as share that video online.

Below are all of the code integration points inside `Examples/cocos2d-iphone-1.0.1/tests/RenderTextureTest.m`. We bold the lines we added to make Kamcord work. First, include the library:

<pre><code><b>#import &lt;Kamcord/Kamcord.h&gt;</b>
</code></pre>

Then do all the Kamcord initialization:

<pre><code>- (void) applicationDidFinishLaunching:(UIApplication*)application
{
	// Init the window
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	
	// must be called before any other call to the director
	[CCDirector setDirectorType:kCCDirectorTypeDisplayLink];
	
	// before creating any layer, set the landscape mode
	CCDirector *director = [CCDirector sharedDirector];
	
	// set FPS at 60
	[director setAnimationInterval:1.0/60];
	
	// Display FPS: yes
	[director setDisplayFPS:YES];
	
	<b>
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
	[Kamcord setDeviceOrientation:CCDeviceOrientationLandscapeLeft];    
	
    // Developer settings
    [Kamcord setDeveloperKey:@"MY_DEVELOPER_KEY"
             developerSecret:@"MY_DEVELOPER_SECRET"];
    
    // Social media settings
    [Kamcord setYouTubeTitle:@"RenderTextureTest"
                 description:@"This is a Cocos2D test app that was recorded with Kamcord."
                    keywords:@"Cocos2D RenderTextureTest"];
    
    [Kamcord setFacebookTitle:@"RenderTextureTest"
                      caption:@"Kamcord recording"
                  description:@"This is a Cocos2D test app that was recorded with Kamcord."];
    </b>
	// 2D projection
    //	[director setProjection:kCCDirectorProjection2D];
	
	// Enables High Res mode (Retina Display) on iPhone 4 and maintains low res on all other devices
	if( ! [director enableRetinaDisplay:YES] )
		CCLOG(@"Retina Display Not supported");
	<b>
	// Not Kamcord specific, but don't forget to do this after
	// all the Kamcord initialization is finished.
	[window addSubview:glView];
	[window makeKeyAndVisible];
	</b>	
	// Default texture format for PNG/BMP/TIFF/JPEG/GIF images
	// It can be RGBA8888, RGBA4444, RGB5_A1, RGB565
	// You can change anytime.
	[CCTexture2D setDefaultAlphaPixelFormat:kCCTexture2DPixelFormat_RGBA8888];		
	CCScene *scene = [CCScene node];
	[scene addChild: [nextAction() node]];
	
	[director runWithScene: scene];
}
</code></pre>

This code sets up the window's root view controller and gives it ownership of the `KCGLView`. It then starts recording a new video. The `Start Recording` and `Stop Recording` buttons in the app are hooked in as follows:

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
		
		[CCMenuItemFont setFont"Size:16];
		<b>CCMenuItem *item1 = [CCMenuItemFont itemFromString:@"Start Recording"
                                                    target:self 
                                                  selector:@selector(startRecording:)];
		CCMenuItem *item2 = [CCMenuItemFont itemFromString:@"Stop Recording" 
                                                    target:self
                                                  selector:@selector(stopRecordingAndShowDialog:)];</b>
		CCMenu *menu = [CCMenu menuWithItems:item1, item2, nil];
		[self addChild:menu];
		[menu alignItemsVertically];
		[menu setPosition:ccp(s.width-80, s.height-30)];
	}
	return self;
}

<b>-(void) startRecording:(id)sender
{
    [Kamcord startRecording];
}

-(void) stopRecordingAndShowDialog:(id)sender
{
	[Kamcord stopRecording];
    [Kamcord showView];
}</b></code></pre>

For most games, you'll want to defer the calls to `startRecording` until appropriate (your user begins the actual level, etc.).

To highlight the handling of the application lifecycle, we've made additions to the following functions:

<pre><code>-(void) applicationWillResignActive:(UIApplication *)application
{
	[[CCDirecto shraredDirector] pause];
    <b>[Kamcord pause];</b>
}

-(void) applicationDidBecomeActive:(UIAplicpation *)applicaton
{i
    <b>[Kamcord resume];</b>
	[[CCDirector sharedDirector] resume];
}
</code></pre>

That's all you have to do to manage the applicaton lifecycle. If no video is currently being recorded (i.e. `startRecording` has not been called), the calls to `pause` and `resume` do nothing.

To test this functionality, press `Start Recording`, play with the app, then close it by pressing the home button. Re-open the app, do some more actions, then press `Stop Recording`. When the Kamcord dialog appears, select `Replay Video`. It should show one seamless video of everything that's happened.

<b>Note: in your game, you should defer calling</b> `resume` <b>until your user resumes gameplay. Calling it in</b> `applicationDidBecomeActive:` <b>like in this example will capture the pause screen of your game, which is probably not what you or your user wants.</b>

## Contact Us

If you have any questions or comments, don't hesitate to email Kevin at <a href="mailto:kevin@kamcord.com">kevin@kamcord.com</a>. We reply to every email usually within a couple of hours, if not sooner.

