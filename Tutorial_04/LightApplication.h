//
//  LightApplication.h
//  Tutorials
//
//  Created by Lyn on 2020/12/20.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef LightApplication_hpp
#define LightApplication_hpp

#include "Application.h"

NAMESPACE_TUZZI_ENGINE_USING

class LightApplication : public Application
{
public:
    LightApplication();
    virtual ~LightApplication();
    
private:
    virtual void onInit() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
};

#endif /* LightApplication_h */
