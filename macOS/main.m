//
//  main.m
//  TuzziApp
//
//  Created by Lyn Chow on 2019/11/5.
//  Copyright © 2019 Lyn Chow. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"

int main(int argc, const char * argv[]) {
    NSApplication* app = [NSApplication sharedApplication];
    AppDelegate* delegate = [[AppDelegate alloc] init];
    app.delegate = delegate;
    [app run];
    return 0;
}
