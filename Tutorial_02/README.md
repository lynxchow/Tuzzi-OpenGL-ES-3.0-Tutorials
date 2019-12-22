## 图志OpenGL ES 3.0教程(二): 画一个劝退三角形

一、小志的瞎BB

自从OpenGL从固定管线走向可编程管线的道路之后，我猜大多数人刚开始学习如何用OpenGL绘制一个三角形，内心肯定是有疑问：画个三角形竟然要这么麻烦？

使用OpenGL绘制一个图形，需要经过shader的编写，编译，链接，顶点装配，绘制。其中涉及一些图形学原理（如：图元装配，裁剪，光栅化），代码里穿插各种状态检查，出了问题除非能抓帧，否则就是各种猜想，小志当年光是学习绘制三角形差点吓到劝退。

为什么看似如此简单的图形，却要大费周章学习？那是因为你所看到的很多三维游戏的场景，模型，包括二维的应用，美妆，视频特效，其实都是由一个一个的三角形绘制而成的。例如下图业界知名的OpenGL ES 3.0编程指南，和D3D的红龙书。

![OpenGL ES 3.0编程指南和红龙书](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_02/res/1.png)

也就是说，掌握如何绘制像三角形这种基本图元，是入门图形学必不可少的第一步，以后做的所有特效，几乎都在和三角形打交道。

但是还是好麻烦哦。。。其实，现在一般的渲染引擎和游戏引擎几乎都把这些繁琐的shader操作封装好了，模型的加载都有便捷的api或者工具可以导入（例如Unity，开发者只需拖拽模型，配置模型渲染的材质就可以实现自己想要的特效）。

而对于只想做一些基础特效的移动端应用来说，可能就需要自己编写渲染功能，或者使用一些成熟的渲染器sdk。

二、我可以学到些什么？

1. 渲染管线原理

在OpenGL里面，任何图形都是在三维空间的（就算是一个二维的OpenGL应用，其渲染的图形也是三维空间的面片）。

但是屏幕空间又是二维像素点。所以渲染管线的工作就是要把三维空间的点转成二维点，再经过上色输出成屏幕空间的像素点。

一组3D坐标在渲染管线处理完成输出到屏幕上，是需要经过几个阶段的。如下图：

![渲染管线](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_02/res/2.png)

这上图中每个阶段的任务都是简单且重复的，就是拿到上一个阶段的结果，处理完之后，然后送到下一个阶段作为输入，就像车间的流水线一样。现在市面上大多数的显卡都有成千上万的小处理核心，这些核心各自跑着渲染管线阶段上的小程序，而这些小程序叫做着色器，也就是Shader。

所以GPU的渲染管线的每个阶段都是可以并行的，效率当然是比CPU高。

上图中的顶点着色器和片元着色器是我们可以定义的，通过GLSL（OpenGL Shader Language）编写着色器程序在GPU上运行。

其他的阶段虽然不能定义，但是开发者可以配置这些阶段的属性，例如混合的阶段，是否打开混合，混合的方式是怎样的。

2. 状态机

一直说OpenGL是个状态机，听着好像好难的样子。其实就是一个记录OpenGL的当前的运行状态的超大结构体，例如当前要绘制的是那些顶点数据，用的哪个shader绘制，画的是三角形还是点。这个状态机的结构体通常被称为OpenGL的上下文，Context。

由于OpenGL的实现是面向过程的C语言写的，也为了能够在别的语言上更好的支持，所以OpenGL的很多操作都是很抽象的。例如创建对象，但并不是真的给你对象，而是返回一个对象的句柄（handle），然后对这个对象的操作，首先先要通过绑定去锁定的当前操作的目标，然后你后续所以的操作都会作用在这个目标上面，操作完之后，需要解除绑定，否则后面的代码误操作这个目标就会发生一些莫名其妙的问题。

3. 着色器

那么我们要学习的第一个OpenGL对象就是着色器，这个着色器其实就是一个运行在GPU上的一个小程序，功能是实现我们的特效，顶点着色器负责控制图形的顶点应该如何显示在窗口上（例如，是否近大远小，位置，大还是小，是否旋转），片元着色器负责给我们的图形的片元上色（例如我要给三角形上个五彩斑斓的黑）。

在我们的应用在运行过程中，需要对着色器进行编译，链接，检查错误，使用。小志第一次学着色器就觉得这个操作很牛逼，一个应用内部竟然可以编译代码，不过着色器的编译和链接过程都是通过OpenGL的图形驱动在GPU上执行的。

这里我们写下第一个shader，用于绘制我们的三角形，并且给这个三角形上彩色。

我们的顶点着色器的功能非常简单，直接把CPU传过来的顶点的位置，颜色，不做任何变换直接输出，同时把cpu传过来的颜色值传到片元着色器，由于片元着色器可以对我们顶点的颜色进行线性插值的，所以如果给三角形的每个顶点分别指定红绿蓝三种颜色，三角形内部的颜色会被插值成彩色。

```cpp
#version 300 es
// OpenGL ES 3.0版本信息声明，不写的话shader编译不通过

// 这里写顶点布局，location = 0，要求cpu传递的顶点时，position数据要放在最前面
layout (location = 0) in vec3 position;
// location = 1为color数据
layout (location = 1) in vec3 color;

// 定义输出类型的颜色值，传输到片元着色器上
out vec3 outColor;

void main()
{
    // 给gl_Position关键字赋值，就相当于把顶点数据传到渲染管线的下一个阶段
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    // 把颜色值传到渲染管线的下一个阶段
    outColor = color;
}

```

我们在片元着色器给我们的三角形上个颜色，颜色值由顶点着色器传过来。

```cpp
#version 300 es
// 和顶点着色器一样需要

// 精度声明，不写编译不通过
precision mediump float;

// 接收从顶点着色器传过来的颜色值
// 需要用关键字in修饰
// 名字要和顶点着色器的命名一样
in vec3 outColor;

// 只需定义一个vec4类型的输出变量作为颜色的输出，输出变量用out标示
out vec4 FragColor;

void main()
{
    vec3 result = outColor;
    FragColor = vec4(result, 1.0f);
}

```

这个shader的代码写好了，可以写在代码里，作为const字符串存起来，又或者说写成外部的vsh，fsh文件，然后用文件流运行时读出来。如果只涉及到shader反复修改，建议是设计成外部文件读取的方式比较合理，这样可以省掉程序的编译。

shader写好啦，接下来我们需要编译这个shader，并且链接成一个shader程序。

```cpp
unsigned int vertex, fragment;
// 创建一个顶点着色器对象
vertex = glCreateShader(GL_VERTEX_SHADER);
// 指定顶点着色器的代码
glShaderSource(vertex, 1, &vertexSource, NULL);
// 编译顶点着色器
glCompileShader(vertex);
// 检查是否有编译错误
result = checkCompileErrors(vertex, "VERTEX");

// 创建一个顶点着色器对象
fragment = glCreateShader(GL_FRAGMENT_SHADER);
// 指定片元着色器的代码
glShaderSource(fragment, 1, &fragmentSource, NULL);
// 编译片元着色器
glCompileShader(fragment);
// 检查是否有编译错误
result = result && checkCompileErrors(fragment, "FRAGMENT");

// 创建一个着色器程序
m_id = glCreateProgram();
// 依附前面两个创建好的着色器
glAttachShader(m_id, vertex);
glAttachShader(m_id, fragment);
// 链接
glLinkProgram(m_id);
// 检查链接错误
result = result && checkCompileErrors(m_id, "PROGRAM");

// 着色器程序链接ok之后，是可以删掉两个着色器的
// 但是着色器程序不能删除，因为我们绘制图形的时候要用到
glDeleteShader(vertex);
glDeleteShader(fragment);
```

是不是很麻烦？我们把这些繁琐的操作封装成一个Shader类，这样以后编译shader就很方便啦！

```cpp
m_shader = new tuzzi::Shader();
m_shader->initWithSource(s_vertex_shader, s_fragment_shader);
```

4. OpenGL坐标系

在传输顶点数据之前，首先要了解一下OpenGL的坐标，这样我们才能确定如何传什么样的顶点数据才能输出我们想要的图形。

3D坐标系有两种坐标系，一种是左手坐标系和右手坐标系，如下图。

![左手坐标系与右手坐标系](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_02/res/3.jpg)

两套坐标系的X，Y，Z轴都是互相垂直的，区别是Z的方向是相反的。OpenGL是使用的右手坐标系，和我们数学课上讲的坐标系是同一套，而DirectX，Unity用的是左手坐标系。

对于我们只需要绘制一个三角形面片而言，我们首先要知道窗口的坐标系的大小，否则我们不能确定三角形每个顶点的值是多少。这里就需要引入另外一个坐标系统，标准化设备坐标(Normalized Device Coordinates, NDC)。

![NDC坐标系](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_02/res/4.png)

NDC是一个x、y、z轴在-1.0到1.0的一小段空间，(0.0, 0.0, 0.0)就是屏幕的中心点。经过顶点着色器处理过的顶点，最终赋值到gl_Position的顶点要在这个范围内才能正常显示到窗口上，否则会被裁剪。

5. 传输顶点

我们可以先设置三角形的z轴为0，因为我希望这个三角形能显示在NDC坐标的正中心的平面上，然后x，y设置成-0.5～0.5。然后用一个float的数组把顶点按x,y,z的顺序存下来。

```cpp
// 设置3个顶点，每个顶点有1个vec3的位置信息和1个vec3的颜色信息
float vertices[] =
{
    -0.5f, -0.5f,  0.0f, // 左边点的位置
     1.0f,  0.0f,  0.0f, // 左边点的颜色
     0.5f, -0.5f,  0.0f, // 右边点的位置
     0.0f,  1.0f,  0.0f, // 右边点的颜色
     0.0f,  0.5f,  0.0f, // 上方点的位置
     0.0f,  0.0f,  1.0f  // 上方点的颜色
};

// 三角形面片的顶点序号，从0开始的
unsigned int indices[] =
{
    0, 1, 2
};
```

由于本地的应用和GPU的通信是CS架构的，即我们分配的对象，封装好的数据，需要从客户端上提交到GPU上，由GPU来处理。

既然涉及到通信，那肯定是存在通信的协议。我们要通过以下的一些API，将顶点数据提交到GPU，并告诉GPU应该要如何解析这些顶点数据。

这里要先介绍几个对象存储数据的对象：
VAO(顶点数组对象): 存储顶点配置用
VBO(顶点缓冲对象): 存储顶点数据用
EBO(索引缓冲对象): 存储顶点索引数据用

下面是绑定的方法

```cpp
// 分配VAO对象
glGenVertexArrays(1, &VAO);
// 分配VBO对象，专门存储顶点数据
glGenBuffers(1, &VBO);
// 分配EBO对象，专门存储顶点的索引值
glGenBuffers(1, &EBO);

// 先绑定VAO对象，由这个VAO对象来记录VBO操作
glBindVertexArray(VAO);

// 先绑定VBO对象到GL_ARRAY_BUFFER这个target上，后续对GL_ARRAY_BUFFER的操作都会修改VBO这个对象
glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 绑定具体的顶点内存数据到GL_ARRAY_BUFFER
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 绑定EBO对象到GL_ELEMENT_ARRAY_BUFFER这个target上，后续对GL_ELEMENT_ARRAY_BUFFER的操作都会修改EBO
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
// 绑定顶点索引数据到GL_ELEMENT_ARRAY_BUFFER
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// 通过下面的方法告诉OpenGL如何解析顶点数据的postion信息
// 第一个参数，0，数据解析对应到顶点着色器中的layout(location = 0)
// 第二个参数，3，表示顶点数据的大小，因为顶点是vec3，所以这里是3
// 第三个参数，GL_FLOAT，表示我们的数据是float类型的
// 第四个参数，GL_FALSE，表示是否需要归一化
// 第五个参数，一个顶点数据的是多少，我们一个顶点包含3个float的position，3个float的color，所以这里是6 * sizeof(float)
// 第六个参数，(void*)0，表示位置信息在一个顶点数据的偏移值是多少。因为每组数据开头就是position信息，所以这里填0
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    
// 解析顶点数据的color信息，因为color在顶点布局的1号位置，所以第一个参数是0
// 第六个参数是sizeof(float) * 3，因为一组顶点数据开头要偏移3个float数据才是color值
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

// 启动传输layout 0
glEnableVertexAttribArray(0);
// 启动传输layout 1
glEnableVertexAttribArray(1);

// 因为之前需要绑定VBO来绑定顶点数据，那么处理完之后解绑GL_ARRAY_BUFFER
// 免得后面误操作了VBO，毕竟OpenGL是个状态机。
glBindBuffer(GL_ARRAY_BUFFER, 0);

// 但是却不能在VAO绑定的过程中解绑EBO，因为EBO需要存储在VAO的，很怪的规定，反正别解绑EBO就是了- -

// 终于处理完VAO的配置了，这个时候就可以解除绑定VAO啦，免得后面又不小心误操作了VAO
glBindVertexArray(0);
```

6. 绘制

```cpp
// 需要设置窗口的位置和大小，如果错误设置将会导致位置不对，或者图形的比例不对
glViewport(0, 0, getWidth(), getHeight());
    
// 先设置窗口的清屏颜色
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 参数传GL_COLOR_BUFFER_BIT，代表glClear清除的是颜色缓冲区
glClear(GL_COLOR_BUFFER_BIT);

// 使用我们的shader
m_shader->use();
// 因为我们的三角形的顶点数据绑定解析已经全部配置到VAO啦
// glBindVertexArray绑定可以将下面的绘制操作制定之前设置的三角形
glBindVertexArray(VAO);
// 调用glDrawElements绘制方法，
// 第一个参数代表，绘制图元是三角形，还有点，线，扇形可选择
// 第二个参数代表需要绘制的顶点，因为我们的三角形只有3个顶点，所以就填3好了
glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

```

这个时候，我们可以运行我们的程序啦。

![彩色三角形绘制](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_02/res/5.png)

但是产品经理就是想要五彩斑斓的黑，怎么办？

对于这种无理的需求，我们当然是...满足他，哈哈哈。

这么简单的事情改改片元着色器就可以实现啦。

```cpp
void main()
{
    // 将顶点的颜色乘以一个很小的系数，让三角形的原有的颜色接近黑色
    vec3 result = outColor * 0.1;
    FragColor = vec4(result, 1.0f);
}
```

看，五彩斑斓的黑！

![彩色三角形绘制](https://raw.githubusercontent.com/LittleLyn/Tuzzi-OpenGL-ES-3.0-Tutorials/master/Tutorial_02/res/6.png)

三、Q&A

1. 我的屏幕是黑的，什么都没有，怎么回事
A: OpenGL的渲染出错有很多原因导致的，有可能GL的环境根本就没有配置对，也有可能shader编译出错，或者顶点数据传输有误（顶点数据不对，VAO和VBO配置错误），glViewport设置不对，或者相机根本就没有看着渲染的模型。

这么多可能性，就要用排除法定位问题，如果屏幕是黑的，最简单的判断方式就是glClear清屏你设置的颜色，如果清屏不是你想要的颜色，那就需要检查OpenGL和本地窗口的配置。

如果清屏是成功的，说明OpenGL环境正常，但是什么都没有绘制，就要检查一下shader编译和链接是否报错，一般有错误是会输出错误并定位到shader的指定行。这些都正确就需要看顶点数据是否配置正确，以及是否正确执行了draw函数。

2. 我绘制出图形，但是图形为什么会被压扁？
A: 这种情况极有可能是viewport不对，或者顶点数据有误，检查一下这两项吧。

