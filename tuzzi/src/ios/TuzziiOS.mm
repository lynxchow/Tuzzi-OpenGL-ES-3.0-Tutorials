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
#include "gl/gl.h"

NAMESPACE_TUZZI_ENGINE_USING

@interface GLView : UIView

@end

@implementation GLView

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        CAEAGLLayer* aglLayer       = (CAEAGLLayer*)self.layer;
        aglLayer.drawableProperties = @{
            kEAGLDrawablePropertyRetainedBacking : [NSNumber numberWithBool:NO],
            kEAGLDrawablePropertyColorFormat : kEAGLColorFormatRGBA8,
        };
        aglLayer.opaque        = YES;
        aglLayer.contentsScale = [[UIScreen mainScreen] scale];
    }

    return self;
}

@end
@interface TuzziiOS()
{
    Tuzzi *m_tuzzi;
    GLView *m_view;
    EAGLContext *m_context;
    
    GLuint m_color_buffer;
    GLuint m_depth_buffer;
    GLuint m_frame_buffer;
}
@end

@implementation TuzziiOS

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super init];
    if (self)
    {
        m_view = [[GLView alloc] initWithFrame:frame];
        m_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    
        [EAGLContext setCurrentContext:m_context];
        
        glGenFramebuffers(1, &m_frame_buffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);

        glGenRenderbuffers(1, &m_color_buffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_color_buffer);

        CAEAGLLayer* aglLayer = (CAEAGLLayer*)m_view.layer;
        if ([m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:aglLayer])
        {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_color_buffer);

            GLint width  = 0;
            GLint height = 0;
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);

            glGenRenderbuffers(1, &m_depth_buffer);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depth_buffer);
            
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_buffer);

            glCheckFramebufferStatus(GL_FRAMEBUFFER);
        }
        else
        {
            glDeleteBuffers(1, &m_color_buffer);
            m_color_buffer = -1;
        }
        
        
        m_tuzzi = new Tuzzi();
        m_tuzzi->init();
        CGFloat scale = [UIScreen mainScreen].scale;
        m_tuzzi->setSize(frame.size.width * scale, frame.size.height * scale);
    }
    
    return self;
}

- (void)drawFrame {
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_color_buffer);
    m_tuzzi->update();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
    
- (UIView *)view
{
    return m_view;
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

- (void)destroy
{
    m_tuzzi->destroy();
    
    glDeleteRenderbuffers(1, &m_color_buffer);
    glDeleteRenderbuffers(1, &m_depth_buffer);
    glDeleteFramebuffers(1, &m_frame_buffer);
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

- (void)dealloc
{
    [self destroy];
    [super dealloc];
}
@end
