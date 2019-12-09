### 跨平台开发真好玩

一、教程介绍

1. 行业需要

最近有好几个朋友问我，这种涂抹效果是怎么做的，这种转场的特效真酷，是如何实现的？我每次都结合OpenGL ES，把每个绘制流程的实现讲一遍。

小伙伴听完之后，他们的反应是这样的...

![img](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_01/res/1.jpg)

于是，小志打算搞个OpenGL ES 3.0的教程，写一些好看的特效是怎么实现的。

在工作的这些年，小志参与多款知名相机产品的研发，深深感受到图形学的魅力。相比后台开发，图形工程师的工作更富有艺术性。同样是各种看似复杂，枯燥乏味的代码，数据结构和算法，但图形学可以将数字呈现出一个“精美世界”，例如下图的glfw的粒子系统Demo。

![img](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_01/res/2.gif)

2. 特色

这个教程收集了小伙伴们想实现的特效需求，并不是简单介绍功能和API，还会提到一些常见问题的解决以及性能的优化方案。希望读者不仅能通过教程学会OpenGL ES的技术，还可以解决实际项目中所遇到的问题。

为了我们的特效可以一处编写，随处编译。我们要把整套教程搞成跨平台的OpenGL ES应用，教程分为两部分。

一部分是Tuzzi渲染引擎，该引擎封装了平台相关的窗口处理，OpenGL API的封装，以及一些渲染引擎常用的功能，例如，渲染，资源加载，Debugger。这个引擎不仅仅是服务于教程，还可以实现个人的图形应用，引擎的功能会根据每一篇教程的需要逐渐完善。

另一部分是基于Tuzzi引擎实现的教程Demo，每一篇教程都是继承Tuzzi的Application类实现。

教程的例子可在Android、iOS跨平台上运行。同时，例子还可以在PC(目前仅支持macOS，Windows待完善)上快速测试。

二、前提知识

1. C++

因为是跨平台OpenGL ES教程，所以需要你有一定的C++基础。

2. 了解几何意义的线性代数

这里提到的线性代数不是指应付考试的线性代数，而是知其几何意义的线性代数。其实线性代数的几何意义并不难理解，一般图形开发中常用的也就是4x4的矩阵。如果不了解线性代数的几何意义，这里可以推荐一下网易公开课上的[麻省理工的线性代数公开课](http://open.163.com/newview/movie/courseintro?newurl=%2Fspecial%2Fopencourse%2Fdaishu.html)，还有B站上的[线性代数本质](https://www.bilibili.com/video/av5987715)。

3. cmake

该教程用构建工具CMake生成不同平台的工程，需要你了解一点CMake。不过教程已经写好构建Android、iOS、Mac这些平台工程的CMakeLists.txt，同时通过gen_build_xxx.sh的脚本生成目标平台的工程目录文件。

三、平台搭建

引擎的最主要的类是Tuzzi，它是一个单例。该类封装了一个跨平台渲染引擎该有的生命周期，同时该类负责管理图形应用Application的加载，更新和卸载。下图为Tuzzi的UML类图。

![img](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_01/res/5.png)

引擎的应用类是Application，我们只需继承Application类，实现图形特效的逻辑，再使用Tuzzi引擎实例加载出来就可以渲染出效果。

在Tuzzi和Application都可以调用OpenGL ES的API，但并没有和平台相关的窗口处理。

OpenGL ES是平台通用的绘图API，并没有定义窗口系统。在特定设备上使用需要一个中间层做适配，这个中间层在Android平台上就是EGL，而iOS是EAGL。

为了处理不同平台的窗口系统的问题，Tuzzi渲染引擎在每个平台都有自己实现的引擎类，Android平台的是TuzziAndroid类，iOS对应的是TuzziiOS类，macOS对应的是TuzziMac类。这些平台相关的引擎类封装了和OpenGL ES通信的窗口系统，应用的生命周期以及一些事件的处理。

1. Android平台搭建

用于Android的库称为EGL。如果要绘制纹理多边形，应使用GLES调用；如果要在屏幕上进行渲染，应使用EGL调用。关于Android EGL的native配置有一个篇不错的文章，感兴趣的可以看一下：[OpenGL ES 3.0 EGL概述](https://www.jianshu.com/p/397cc3c23b75)

Android Java层是一个Activity+自定义的SurfaceView。SurfaceView负责显示OpenGL的渲染结果。由于考虑到跨平台的使用，所以我们要通过jni调用Native层的引擎接口。

Native层的TuzziAndroid平台相关引擎类，负责调用EGL，将我们OpenGL ES的绘制结果更新到SurfaceView。

代码参考: [TuzziAndroid.cpp](https://github.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/blob/master/tuzzi/src/android/TuzziAndroid.cpp)。

2. iOS搭建

iOS平台为OpenGL提供的实现是EAGL，OpenGL ES系统与本地窗口（UIKit）桥接由EAGL上下文系统实现。关于iOS的EAGL配置可以参考：[OpenGL ES在iOS中的上下文环境搭建](https://www.jianshu.com/p/c34c14589e0c)

同样的，引擎的TuzziiOS负责管理EAGL的调用，帮我们初始化OpenGL ES的环境。

代码参考：[TuzziiOS.mm](https://github.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/blob/master/tuzzi/src/ios/TuzziiOS.mm)

3. macOS搭建

mac平台的搭建相对要简单一点，只需要初始化OpenGL的Context即可。可以直接参考TuzziMac的代码：[TuzziMac.mm](https://github.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/blob/master/tuzzi/src/mac/TuzziMac.mm)。

四、写下第一个类

废了那么大功夫，平台都搭建好了，我们可以愉快的玩耍啦。因为这次教程篇幅的原因，所以第一篇的教程只有两个功能，此处贴出链接：[Tutorial_01](https://github.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/tree/master/Tutorial_01)

- 使用OpenGL ES的glClear函数给窗口清一个背景色
- 使用Log宏，把Application的生命周期打出来

这样就可以验证我们的每个平台和OpenGL ES环境是否都搭建好啦。

```cpp
#include "DemoApplication.h"

#include "Tuzzi.h"

#include "gl/gl.h"


NAMESPACE_TUZZI_ENGINE_USING

DemoApplication::DemoApplication() : tuzzi::Application()
{
    
}

DemoApplication::~DemoApplication()
{
    
}

void DemoApplication::onInit()
{
    TZ_LOGD("DemoApplication", "onInit");
}

void DemoApplication::onUpdate()
{
    TZ_LOGD("DemoApplication", "onUpdate");
    // 设置清屏的颜色
    glClearColor(0.0, 0.5, 0.5, 1.0);
    // 执行清屏
    glClear(GL_COLOR_BUFFER_BIT);
}

void DemoApplication::onDestroy()
{
    TZ_LOGD("DemoApplication", "onDestroy");
}
```

然后，我们只需要在平台的工程代码里load这个DemoApplication就好了，例如mac工程的ViewController.mm

```
SharedPtr<Application> app = MakeShared<DemoApplication>();

[m_engine loadApplication:app];
```

OpenGL的头文件在不同平台上路径和文件不一样，在gl.h的头文件中，我们根据平台的宏指定include正确的OpenGL头文件

```cpp
#ifndef _TUZZI_GL_H_
#define _TUZZI_GL_H_

#if defined(__APPLE__)

#include "TargetConditionals.h"
    
#if TARGET_OS_IPHONE
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#elif TARGET_OS_MAC
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#   error "Unknown Apple platform"
#endif

#elif __ANDROID__

#include <GLES3/gl3.h>

#elif _WIN32

#endif

#endif /* gl_h */
```

DemoApplication的TZ_LOG这些宏是Tuzzi的Log输出方法，具体实现在Log.h。

五、测试

接下来我们测试一下DemoApplication的效果。看到这个浅绿色的背景窗口，还有控制台的log输出，就意味着我们成功啦。

![img](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_01/res/3.png)

![img](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_01/res/4.png)