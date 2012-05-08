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
    <ul>
        <li style="margin: 0;">-lxml2</li>
        <li style="margin: 0;">-ObjC</li>
        <li style="margin: 0;">-all_load</li>
    </ul>
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

