//
//  DeviceMac.h
//  Tuzzi
//
//  Created by Lyn Chow on 2019/5/29.
//  Copyright © 2019 Lyn. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "Application.h"

NS_ASSUME_NONNULL_BEGIN

@interface TuzziiOS : NSObject
- (instancetype)initWithFrame:(CGRect)frameRect;
- (UIView *)view;
- (BOOL)loadApplication:(SharedPtr<tuzzi::Application>)application;
- (BOOL)unloadApplication;
- (tuzzi::Application *)currentApplication;
- (void)drawFrame;
@end

NS_ASSUME_NONNULL_END
