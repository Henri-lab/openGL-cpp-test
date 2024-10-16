<h1>抗锯齿实现</h1>

```glsl
    vec3 color = vec3(0.0);
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            vec2 uv = gl_FragCoord.xy + vec2(i,j)/3.0;
            color += getPixel(uv, time);
        }
    }
    color /= 9.0;
```

原理：
它通过偏移像素坐标 gl_FragCoord.xy 进行 3x3 网格的采样，也就是从原始像素的周围共采样 9 次（i 和 j 迭代 -1 到 1 的范围）。
然后将所有采样的颜色值加起来，取平均值。
这个过程被称为 超采样抗锯齿（Supersampling Anti-Aliasing, SSAA）。