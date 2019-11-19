//
//  Tuzzi.m
//  Tuzzi
//
//  Created by Lyn Chow on 2019/5/29.
//  Copyright © 2019 Lyn. All rights reserved.
//

#import "TuzziMac.h"
#include "Tuzzi.h"

@interface TuzziMac()
{
    NSView *m_view;
}
@end

@implementation TuzziMac

- (instancetype)initWithFrame:(NSRect)frameRect
{
    self = [super init];
    if (self)
    {
        m_view = [[NSView alloc] initWithFrame:frameRect];
        
        tuzzi::Tuzzi::instance()->init();
    }
    
    return self;
}

- (NSView *)view
{
    return m_view;
}

- (void)drawFrame
{
    tuzzi::Tuzzi::instance()->update();
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

- (void)dealloc
{
    tuzzi::Tuzzi::instance()->destroy();
}

@end
