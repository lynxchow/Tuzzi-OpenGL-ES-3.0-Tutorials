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
        
        
        tuzzi::Tuzzi::instance()->init();
    }
    
    return self;
}

- (void)drawFrame {
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_color_buffer);
    tuzzi::Tuzzi::instance()->update();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
    
- (UIView *)view
{
    return m_view;
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
    glDeleteRenderbuffers(1, &m_color_buffer);
    glDeleteRenderbuffers(1, &m_depth_buffer);
    glDeleteFramebuffers(1, &m_frame_buffer);
    
    tuzzi::Tuzzi::instance()->destroy();
}

- (void)dealloc
{
    [self destroy];
    [super dealloc];
}
@end
