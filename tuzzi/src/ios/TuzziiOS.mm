//
//  Tuzzi.m
//  Tuzzi
//
//  Created by Lyn Chow on 2019/5/29.
//  Copyright © 2019 Lyn. All rights reserved.
//

#import "TuzziiOS.h"
#include <iostream>
#include "Tuzzi.h"

@interface TuzziiOS()
{
    UIView *_view;
}
@end

@implementation TuzziiOS

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super init];
    if (self)
    {
        _view = [[UIView alloc] initWithFrame:frame];
        
        tuzzi::Tuzzi::instance()->init();
    }
    
    return self;
}

- (void)drawFrame {
    tuzzi::Tuzzi::instance()->update();
}
    
- (UIView *)view
{
    return _view;
}

- (BOOL)loadApplication:(SharedPtr<tuzzi::Application>)application
{
    tuzzi::Tuzzi::instance()->loadApplication(application);
    return YES;
}

- (BOOL)unloadApplication
{
    return tuzzi::Tuzzi::instance()->unloadApplication();
}

- (tuzzi::Application *)currentApplication
{
    return tuzzi::Tuzzi::instance()->currentApplication().get();
}

- (void)destroy
{
    tuzzi::Tuzzi::instance()->destroy();
}

- (void)dealloc
{
    [self destroy];
    [super dealloc];
}
@end
