//
//  AppDelegate.mm
//  TuzziApp
//
//  Created by Lyn on 2019/5/24.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()<NSApplicationDelegate, NSWindowDelegate>
@property (strong, nonatomic) NSWindow* window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    auto style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
    auto frame = [NSWindow frameRectForContentRect:NSMakeRect(0, 0, 1280, 720) styleMask:style];
    
    self.window = [[NSWindow alloc] initWithContentRect:frame styleMask:style backing:NSBackingStoreBuffered defer:YES];
    self.window.title = @"Tuzzi Demo";
    [self.window center];
    [self.window makeKeyAndOrderFront:self.window];
    
    self.window.contentViewController = [[ViewController alloc] init];
    self.window.delegate = self;
}


- (void)applicationWillTerminate:(NSNotification *)notification {
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end
