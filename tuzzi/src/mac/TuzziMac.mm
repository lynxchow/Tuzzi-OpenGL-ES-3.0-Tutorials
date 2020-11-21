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

NAMESPACE_TUZZI_ENGINE_USING

@interface TuzziMac()
{
    NSView *m_view;
    Tuzzi *m_tuzzi;
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
        
        m_tuzzi = new Tuzzi();
        m_tuzzi->init();
        NSRect realRect = [m_view convertRectToBacking:frameRect];
        m_tuzzi->setSize(realRect.size.width, realRect.size.height);
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
    m_tuzzi->update();
    [m_context flushBuffer];
}

- (BOOL)loadApplication:(SharedPtr<tuzzi::Application>)application
{
    m_tuzzi->loadApplication(application);
    return YES;
}

- (BOOL)unloadApplication
{
    return m_tuzzi->unloadApplication();
}

- (tuzzi::Application *)currentApplication
{
    return m_tuzzi->currentApplication().get();
}

const tuzzi::String& tuzzi::Tuzzi::getResourcePath()
{
    static tuzzi::String s_engine_path;
    if (s_engine_path.empty())
    {
        s_engine_path = [[[NSBundle mainBundle] resourcePath] UTF8String];
        s_engine_path += "/res";
    }
    
    return s_engine_path;
}

- (void)setInputTexture:(SharedPtr<tuzzi::Texture>)texture
{
    m_tuzzi->getTextureManager()->setInputTexture(texture);
}

- (void)dealloc
{
    m_tuzzi->destroy();
    [m_context release];
    [super dealloc];
}

@end
