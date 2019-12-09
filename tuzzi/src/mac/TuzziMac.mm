//
//  Tuzzi.m
//  Tuzzi
//
//  Created by Lyn Chow on 2019/5/29.
//  Copyright © 2019 Lyn. All rights reserved.
//

#import "TuzziMac.h"
#include "Tuzzi.h"
#include "gl/gl.h"

@interface TuzziMac()
{
    NSView *m_view;
    NSOpenGLContext *m_context;
}
@end

@implementation TuzziMac

- (instancetype)initWithFrame:(NSRect)frameRect
{
    self = [super init];
    if (self)
    {
        const uint32_t attrs[] =
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFADepthSize, 24,
            0
        };
        
        m_view = [[NSView alloc] initWithFrame:frameRect];
        m_context = [[NSOpenGLContext alloc] initWithFormat:[[NSOpenGLPixelFormat alloc] initWithAttributes:attrs] shareContext:nil];
        [m_context setView:m_view];
        [m_context makeCurrentContext];
        
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
    [m_context makeCurrentContext];
    tuzzi::Tuzzi::instance()->update();
    [m_context flushBuffer];
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
    [m_context release];
    [super dealloc];
}

@end
