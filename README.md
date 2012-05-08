# cocos2d-kamcord


## Introduction

This is a custom build of cocos2d-1.0.1 with built-in gameplay recording technology.
It allows you, the game developer, to capture gameplay videos with a very simple API.
Your users can then share those video gameplays via YouTube, Facebook, Twitter, and email.


## Installation

Remove libcocos2d.a from your project. This framework includes all cocos features and functionalities.

<ol>
<li style="margin: 0";>Clone this repository to your local development machine.</li>
<li style="margin: 0";>Drag and drop <code>cocos2d-kamcord.framework</code> into your project.</li>
<li style="margin: 0";">Drag and drop <code>Resources</code> and <code>External-headers</code> to your project.</li>
<li style="margin: 0";>Ensure you have following frameworks under <code>Build Phases</code> ==> <code>Link Binary With Libraries</code>:
	<p>
	<ul>
        <li style="margin: 0;">AssetsLibrary</li>
        <li style="margin: 0;">AVFoundation</li>
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
<p>

</li>
<li style="margin: 0;">Add the following to <code>Build Settings</code> ==> <code>Other Linker Flags</code>:
	<p>
    <ul style="margin-bottom: 15px;">
        <li style="margin: 0;">-lxml2</li>
        <li style="margin: 0;">-ObjC</li>
        <li style="margin: 0;">-all_load</li>
    </ul>
    </p>
</li>
<li style="margin: 0;">Add <code>/usr/include/libxml2</code> to <code>Build Settings</code> ==> <code>Header Search Paths</code>.</li>

<li style="margin: 0;">In your application delegate (or wherever you create the <code>UIWindow</code> and <code>EAGLView</code>), make sure you have a rootViewController set and set the view of that ViewController to your <code>EAGLView</code>.

<p>
<pre><code>window.rootViewController = [[UIViewController alloc] initWithNibName:nil bundle:nil];
window.rootViewController.view = glView;
[[KCManager sharedManager] setParentViewController:window.rootViewController];</code></pre>
<p>

If you already have a UIViewController, use that instead. Kamcord assumes that your window's rootViewController is the only active UIViewController in the view hierarchy.
</li>
</ol>

Your project should build successfully at this point.

## How to use Kamcord

We've tried to keep the Kamcord API as simple as possible. The only class you will need to interface with is `KCManager`, which is included by `cocos2d.h`. To get an instance, call `[KCManager sharedManager]`.

KCManager's public API is broken down by different functionalities.

### Video Recording

The recording interface is built around the concept of one video, which has one or more clips. Most videos will just have one clip, but if your game is interrupted for some reason, you'll have several clips that need to be stitched together into one seamless video. Kamcord handles all of that behind the scenes as long as you start and stop recording your clips at the appropriate places in the app lifecycle.

The API is

    -(void) beginVideo;
    -(void) endVideo;
    -(void) startRecordingClip;
    -(void) endRecordingClip;

`beginVideo` is first called to indicate the beginning of a new video. *It does not begin actual video recording*. After that, `startRecordingClip` and `stopRecordingClip` start and stop the video recording. When the entire gameplay is finished (for example, after the user dies and the round ends), call `endVideo`. An example flow is as follows:

    [[KCManager sharedManager] beginVideo];
    [[KCManager sharedManager] startRecordingClip];
    //
    // Gameplay happens
    //
    [[KCManager sharedManager] stopRecordingClip];
    // Application interrupted
    // …
    // Application regains foreground and user resumes gameplay    
    [[KCManager sharedManager] startRecordingClip];
    // 
    // More gamplay happens until round ends
    //  
    [[KCManager sharedManager] stopRecordingClip];
    [[KCManager sharedManager] endVideo];

In this example, the developer recorded two clips that will be contiguously stitched together. He may have stopped the first clip to handle a phone call and started the second clip as soon as the user returned to the app and resumed gameplay. After `endVideo` is called, Kamcord understands that there were two clips and combines them into one video. You can then present the user with more options, which are described in the next section.


### Presenting User Options

Now that that the user has finished his gameplay and you have successfully recorded a video of it, you can present several options to the user with the following API call:

	-(void) showKamcordDialog;

This presents a modal dialog with the following options:

<p>
<ul>
    <li style="margin: 0;">Replay Video</li>
    <li style="margin: 0;">Save Video to Photos</li>
    <li style="margin: 0;">Email Video</li>
    <li style="margin: 0;">Upload to YouTube</li>
    <li style="margin: 0;">Share to Facebook</li>
    <li style="margin: 0;">Share to Twitter</li>
</ul>
</p>

The options are pretty self-explanatory. `Replay Video` will show the video of the gameplay that just happened (the result of the last `endVideo` call). `Save Video to Photos` will save a copy of the video to the device's Photo Album.

`Email Video` will upload the video to YouTube and then present the user with an email dialog that has the video link in the email body.

`Upload to YouTube` lets the user upload the video to YouTube with a title and description.

Lastly, `Share to Facebook` and `Share to Twitter` allow the user to share a link of the uploaded YouTube video on their social networks. If the video has not been uploaded to YouTube yet, it will do that first and then present the user the Facebook/Twitter sharing dialogs.

You as the developer can set default YouTube titles, descriptions, and keywords, and default Tweet messages via the following API calls:

    -(void) setYouTubeUploadDefaultTitle:(NSString *)title
                      defaultDescription:(NSString *)description
                         defaultKeywords:(NSString *)keywords;
    -(void) setDefaultTweet:(NSString *)tweet;

Note that for `setDefaultTweet:`, the video URL will be appended to the message with a space. So for instance, if you set the default Tweet to

`Check out my gameplay!`

the actual tweeted message will be

`Check out my gameplay! http://www.youtube.com/watch?v=abcfoobar123`


## Examples

The `Examples` directory has a fully functional example of how to use Kamcord in your application. It is a slightly modified version of the RenderTextureTest from the cocos2d test suite. When the app launches, it begins a video and starts recording a clip. You can draw on the first screen or switch to two of the other tests. A few seconds later, it stops recording the clip, ends the video, and shows the Kamcord dialog.

Here are all of the code integration points. We bold the lines we added to make Kamcord work. First, we do some initialization:

<pre><code>- (void) applicationDidFinishLaunching:(UIApplication*)application
{
	// Init the window
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	
	// must be called before any othe call to the director
	[CCDirector setDirectorType:kCCDirectorTypeDisplayLink];
	
	// before creating any layer, set the landscape mode
	CCDirector *director = [CCDirector sharedDirector];
	
	// landscape orientation
	[director setDeviceOrientation:kCCDeviceOrientationLandscapeRight];
	
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
    // Create the window's root view controller
    window.rootViewController = [[UIViewController alloc] initWithNibName:nil bundle:nil];
    window.rootViewController.view = glView;
    [[KCManager sharedManager] setParentViewController:window.rootViewController];
    [[KCManager sharedManager] setYouTubeUploadDefaultTitle:@"RenderTexture Test"
                                         defaultDescription:@"Testing Kamcord 0.1"
                                            defaultKeywords:@"cocos2d"];
    </b>
	
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
    
    <b>
    [[KCManager sharedManager] beginVideo];
    [[KCManager sharedManager] startRecordingClip];
	
	// We use a timer for simplicity. You probably want to integrate with your game flow.
    [self performSelector:@selector(stopVideoRecording) withObject:nil afterDelay:5.0];
    </b>
	
	[director runWithScene: scene];
}

<b>
- (void) stopVideoRecording
{
    [[KCManager sharedManager] stopRecordingClip];
    [[KCManager sharedManager] endVideo];
    [[KCManager sharedManager] showKamcordDialog];
}
</b>

</code></pre>

This code sets up the window's root view controller and gives it ownership of the EAGLView. It then begins a new video and starts recording the scene. It also sets a timer for 15 seconds, at which point `stopRecordingVideo` is called. This methods stops recording the current clips, marks the end of the video, and then displays the Kamcord dialog.

For most games, you'll want to defer the call to `startRecordingClip` until appropriate (your user begins the actual round, etc.).

To highlight the handling of the application lifecycle, we've also made minor additions to the following functions:

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

To test this functionality, start up the app, do some stuff, then close it by pressing the home button. Re-open the app and continue doing actions. Once the 15 seconds is up, you should get the Kamcord dialog again. Try pressing `Replay Video`. It should show one seamless video of everything that's happened.