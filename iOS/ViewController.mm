//
//  ViewController.m
//  TuzziApp
//
//  Created by Lyn Chow on 2019/11/10.
//  Copyright © 2019 Lyn Chow. All rights reserved.
//

#import "ViewController.h"
#include "ios/TuzziiOS.h"
#include "Tutorial_01/DemoApplication.h"
#include "Tutorial_02/ColorApplication.h"
#include "Tutorial_03/TextureApplication.h"

@interface FrameHandler : NSObject
{
    TuzziiOS *m_engine;
}
- (void)setEngine:(TuzziiOS *)engine;
@end

@implementation FrameHandler

- (void)setEngine:(TuzziiOS *)engine
{
    m_engine = engine;
}

- (void)updateFrame
{
    [m_engine drawFrame];
}

@end

@interface ViewController ()
{
    TuzziiOS *m_engine;
    FrameHandler *m_frame_handler;
    CADisplayLink *m_display_link;
}
@end

@implementation ViewController

NAMESPACE_TUZZI_ENGINE_USING

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    CGSize size = UIScreen.mainScreen.bounds.size;
    m_engine = [[TuzziiOS alloc] initWithFrame:CGRectMake(0, 0, size.width, size.height)];
    self.view = m_engine.view;
    
    m_frame_handler = [[FrameHandler alloc] init];
    [m_frame_handler setEngine:m_engine];
    
    m_display_link = [CADisplayLink displayLinkWithTarget:m_frame_handler selector:@selector(updateFrame)];
    [m_display_link setPreferredFramesPerSecond:60];
    [m_display_link addToRunLoop: NSRunLoop.currentRunLoop forMode:NSDefaultRunLoopMode];
    
    SharedPtr<Application> app = MakeShared<TextureApplication>();
    [m_engine loadApplication:app];
}

- (void)dealloc
{
    [super dealloc];
    [m_display_link invalidate];
    m_display_link = nil;
}


@end
