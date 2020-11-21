//
//  Map.h
//  Tuzzi
//
//  Created by Lyn on 2020/11/20.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_CONTAINER_MAP_H_
#define _TUZZI_CONTAINER_MAP_H_

#include "Common.h"
#include <unordered_map>

NAMESPACE_TUZZI_ENGINE_BEGIN

template <typename K, typename V>
using Map = std::unordered_map<K, V>;

NAMESPACE_TUZZI_ENGINE_END

#endif /* Map_h */
