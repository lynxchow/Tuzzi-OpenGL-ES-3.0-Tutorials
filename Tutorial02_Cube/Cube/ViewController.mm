//
//  ViewController.m
//  Cube
//
//  Created by Pocoyo Chow on 24/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#import "ViewController.h"
#include "CubeApplication.hpp"

@interface ViewController ()<GLKViewDelegate>
{
    EAGLContext *_context;
    GLApplication *_application;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!_context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = _context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [EAGLContext setCurrentContext:_context];
    
    CAEAGLLayer *eaglLayer = (CAEAGLLayer *)view.layer;
    
    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
    
    _application = new CubeApplication();
    _application->init();
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    _application->render(rect.origin.x * 2, rect.origin.y * 2, rect.size.width * 2, rect.size.height * 2);
}

@end
