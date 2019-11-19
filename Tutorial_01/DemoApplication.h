//
//  DemoApplication.h
//  TuzziApp
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _DEMO_APPLICATION_H_
#define _DEMO_APPLICATION_H_

#include "Application.h"

class DemoApplication : public tuzzi::Application
{
public:
    DemoApplication();
    virtual ~DemoApplication();
    
private:
    virtual void onInit() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
};

#endif /* DemoApplication_h */
