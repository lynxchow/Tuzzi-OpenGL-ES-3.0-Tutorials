//
//  SharedPtr.h
//  Tuzzi
//
//  Created by Lyn on 2019/7/10.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_SHARED_PTR_H_
#define _TUZZI_SHARED_PTR_H_

#include <memory>

#define WeakPtr std::weak_ptr
#define SharedPtr std::shared_ptr
#define MakeShared std::make_shared
#define DynamicCast std::dynamic_pointer_cast

#endif /* SharedPtr_h */
