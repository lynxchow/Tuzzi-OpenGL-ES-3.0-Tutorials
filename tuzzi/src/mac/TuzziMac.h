//
//  TuzziMac.h
//  Tuzzi
//
//  Created by Lyn Chow on 2019/5/29.
//  Copyright © 2019 Lyn. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "Application.h"
#include "graphics/Texture.h"

NS_ASSUME_NONNULL_BEGIN

@interface TuzziMac : NSObject
- (instancetype)initWithFrame:(NSRect)frameRect;
- (NSView *)view;
- (BOOL)loadApplication:(SharedPtr<tuzzi::Application>)application;
- (BOOL)unloadApplication;
- (tuzzi::Application *)currentApplication;
- (void)drawFrame;
- (void)setInputTexture:(SharedPtr<tuzzi::Texture>)texture;
@end

NS_ASSUME_NONNULL_END
