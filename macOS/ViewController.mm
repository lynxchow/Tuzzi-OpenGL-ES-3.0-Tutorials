//
//  ViewController.mm
//  TuzziApp
//
//  Created by Lyn on 2019/5/29.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#import "ViewController.h"
#import "TuzziMac.h"
#include "DemoApplication.h"
#include "ColorApplication.h"
#include "TextureApplication.h"

@interface FrameHandler : NSObject
{
    TuzziMac *m_engine;
}
- (void)setEngine:(TuzziMac *)engine;
@end

@implementation FrameHandler

- (void)setEngine:(TuzziMac *)engine
{
    m_engine = engine;
}

- (void)updateFrame
{
    [m_engine drawFrame];
}

@end

@interface ViewController()
{
    FrameHandler *m_frame_handler;
    TuzziMac *m_engine;
    NSTimer *m_timer;
}
@end

@implementation ViewController

NAMESPACE_TUZZI_ENGINE_USING

- (void)loadView
{
    NSWindow *window = [[NSApplication sharedApplication] keyWindow];
    CGSize size = [window contentRectForFrameRect:window.contentLayoutRect].size;
    
    m_engine = [[TuzziMac alloc] initWithFrame:NSMakeRect(0, 0, size.width, size.height)];
    self.view = m_engine.view;
    
    m_frame_handler = [[FrameHandler alloc] init];
    [m_frame_handler setEngine:m_engine];
    
    m_timer = [NSTimer timerWithTimeInterval:1.0f / 60.0 target:m_frame_handler selector:@selector(updateFrame) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:m_timer forMode:NSDefaultRunLoopMode];
    
    SharedPtr<Application> app = MakeShared<TextureApplication>();
    [m_engine loadApplication:app];
}

- (void)dealloc
{
    [m_timer invalidate];
    m_timer = nil;
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}


@end
