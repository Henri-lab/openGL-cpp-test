<h1>sea wave 海洋波浪绘制</h1>

```glsl
float sea_octave(vec2 uv, float choppy) {
    uv += noise(uv);        
    vec2 wv = 1.0-abs(sin(uv));
    vec2 swv = abs(cos(uv));    
    wv = mix(wv, swv, wv);
    return pow(1.0 - pow(wv.x * wv.y, 0.65), choppy);
}
```

<p>uv += noise(uv);</p>
- 首先，通过对 uv 加上一个噪声值来引入随机性。这种噪声是基于 uv 的二维坐标计算的，使得波浪有更多的细节和自然的随机性。noise(uv) 函数通常返回一个在 -1 和 1 之间的值，模拟随机的小波动。

<p>vec2 wv = 1.0 - abs(sin(uv));</p>
- 使用 sin 函数对 uv 进行操作并取绝对值。sin(uv) 返回一个在 -1 到 1 之间的波形，因此取 1.0 - abs(sin(uv)) 使得结果在 0 到 1 之间，这一步生成了一个具有周期性的波形效果。

<p>vec2 swv = abs(cos(uv));</p>
- 同时计算了 cos(uv) 的绝对值，生成了另一个不同周期的波形。

<p>wv = mix(wv, swv, wv);</p>
- 使用 mix 函数在 wv 和 swv 之间进行插值，mix(a, b, factor) 返回的是 a 和 b 的加权混合值，权重由 factor 确定。这里 wv 自身作为 factor，使得波浪更复杂和多变。

<p>return pow(1.0 - pow(wv.x * wv.y, 0.65), choppy);</p>
- 这行代码使用 wv.x *wv.y 来结合两个方向的波形，并使用 pow 函数调整波浪的形状。内部的 pow(wv.x* wv.y, 0.65) 会使波浪的形状更加平滑，而 1.0 - 会将波浪向上移动到正高度。最终的 pow(..., choppy) 再次使用 choppy 来调整波浪的粗糙度（即“波浪的尖锐度”）。choppy 越大，波浪会显得越尖锐。


<br>
这种通过分形噪声和数学函数生成波浪效果的写法在计算机图形学中非常有名，特别是在实时渲染和着色器编程领域。这类波浪效果的实现方式主要依赖于“分形噪声”（fractal noise）和多层次的频率叠加（octaves），这使得海浪看起来更加自然且充满细节。

具体来说，这种波浪效果通常会参考以下几个关键技术和思想：

1. Perlin 噪声和分形噪声：
Perlin Noise（佩林噪声）是 Ken Perlin 在 1980 年代开发的，它广泛用于计算机图形学来生成自然的纹理和形状，包括地形、云朵和海浪等。类似的噪声函数（如 GLSL 中的 noise 函数）也常用于模拟自然现象。
sea_octave 函数通过叠加不同频率和振幅的波形（即分形噪声的思想），生成更加复杂的波浪形状。这种技术被称为“多重频率的分形噪声”（Fractal Brownian Motion, fBm），在很多图形应用中都非常常见。
2. 分形叠加：
octave_m 矩阵用于对波形进行放缩和平移，使得每一层波浪的频率和振幅有所不同，从而模拟出不同尺度的波浪。每一次迭代调整波浪的频率和振幅的技术称为“多尺度噪声”，它通过不断叠加不同层次的波形，来表现海浪在大尺度和小尺度上的复杂性。
3. Procedural Generation（程序化生成）：
这种波浪效果是“程序化生成”的典型示例，它不依赖于预定义的图像或模型，而是通过数学公式和算法动态计算出波浪的形状。这种方式非常适合用于实时渲染，尤其是在 GPU 着色器中进行计算时效率非常高。
程序化生成的海洋效果因其计算灵活性和高效性，被广泛应用于游戏开发、电影特效和虚拟现实等领域。比如经典的海洋效果可以在像《海盗湾》、《风之旅人》这样的游戏中找到类似的实现。
4. 著名参考：
"Shadertoy" 社区：这是一个著名的在线平台，开发者们分享他们使用 GLSL 编写的各种着色器效果，其中也包含了大量海洋和波浪效果的实现。许多波浪效果，如 sea_octave 函数，都是从 Shadertoy 等平台上流传开来的。
Houdini、Blender 等图形软件：在专业的 3D 图形制作软件中，像海洋这样的自然场景通常也会通过程序化生成的方式模拟。其背后的核心思想和 sea_octave 类似，使用分形噪声生成波浪。
5. 著名的应用和案例：
电影与动画：在现代的 3D 动画电影中，波浪效果常常通过类似的技术实现。例如《海洋奇缘》（Moana）中的水体效果就结合了类似的程序化生成方法，并使用物理仿真来增强自然感。
游戏：在很多开放世界游戏如《巫师3》或《黑魂》中，水体和海浪效果都会使用类似的波形叠加和噪声生成技术来模拟自然的波浪形态。




<br>
<h2>应用</h2>
map 和 map_detailed 函数的作用：<br>
map 函数

map 函数是用来计算一个给定的三维点 p 在海洋表面的高度（波浪高度）。它的主要工作是通过调用 sea_octave 函数来累加多个波浪的高度值，从而创建出复杂的波浪形状。
map 通过迭代 ITER_GEOMETRY 次来叠加不同频率和振幅的波浪细节，模拟波浪在大尺度上的变化。每一次迭代都会使波浪的频率更高，振幅更小，形成多层次的波形叠加，产生更自然的海洋表面效果。
函数实现：

```glsl
float map(vec3 p) {
    float freq = SEA_FREQ;
    float amp = SEA_HEIGHT;
    float choppy = SEA_CHOPPY;
    vec2 uv = p.xz; uv.x *= 0.75;

    float d, h = 0.0;    
    for (int i = 0; i < ITER_GEOMETRY; i++) {        
        d = sea_octave((uv + SEA_TIME) * freq, choppy);
        d += sea_octave((uv - SEA_TIME) * freq, choppy);
        h += d * amp;        
        uv *= octave_m; freq *= 1.9; amp *= 0.22;
        choppy = mix(choppy, 1.0, 0.2);
    }
    return p.y - h;
}
```

uv = p.xz: 提取 p 的 x 和 z 分量，用于计算波浪在水平面的变化（y 是高度，x 和 z 是水平坐标）。
d = sea_octave(...)：调用 sea_octave 计算波浪的基本形状，将其结果累加到 h 上。
uv *= octave_m: 在每次迭代中，对 uv 进行缩放和平移，以改变波浪的频率和形状。
每次迭代都会改变波浪的频率 freq 和振幅 amp，以及 choppy，形成多层次的波形叠加。
最后返回 p.y - h，它表示给定位置 p 的实际高度与波浪高度的差值。
作用：

map 用于给定一个三维位置 p，计算出它在波浪上的垂直高度差（波浪表面相对于原始平面的位置）。这个高度差用于后续的光照计算和波浪的形状生成。
它适用于大尺度波浪的生成，模拟出宽广的海洋表面。
<br>
map_detailed 函数：
map_detailed 与 map 非常相似，仅仅迭代次数不同，使得它在波浪表面的细节上有更高的精度。map_detailed 用来计算更高频率的细节波浪，尤其是小波浪的高度变化。
并且它主要用于在光照计算中提高表面法线的精度。
函数实现：

```glsl
float map_detailed(vec3 p) {
    float freq = SEA_FREQ;
    float amp = SEA_HEIGHT;
    float choppy = SEA_CHOPPY;
    vec2 uv = p.xz; uv.x *= 0.75;

    float d, h = 0.0;    
    for (int i = 0; i < ITER_FRAGMENT; i++) {        
        d = sea_octave((uv + SEA_TIME) * freq, choppy);
        d += sea_octave((uv - SEA_TIME) * freq, choppy);
        h += d * amp;        
        uv *= octave_m; freq *= 1.9; amp *= 0.22;
        choppy = mix(choppy, 1.0, 0.2);
    }
    return p.y - h;
}
```
主要区别：

ITER_FRAGMENT 比 ITER_GEOMETRY 的值更大，因此 map_detailed 会生成更多的细节层次。它生成的波浪更细致，更适合局部表面效果（例如光照、反射和法线计算）。
map 和 map_detailed 的具体用途：
map：用于大范围的波浪高度计算，主要用于确定波浪的整体形状和高度。它生成了海洋的基础结构。
map_detailed：用于局部细节处理，尤其是在计算表面法线时，用更高精度的波浪形状来得到更准确的法线，进而提高光照和反射的效果。
为什么需要两者？
map 提供了海洋波浪的宏观形状，但它不够精细。如果我们只使用 map，那么在近处观察海浪时，细节会不够丰富，表面法线的计算也会不准确。
map_detailed 则通过更多的迭代，生成更高频率的小波浪细节，使得波浪的表面看起来更加精细，光照效果也会更加真实。
