#version 330 core
out vec2 fragCoord;

void main() {
    vec2 positions[4] = vec2[](vec2(-1.0, -1.0), // 左下
    vec2(1.0, -1.0),  // 右下
    vec2(-1.0, 1.0),  // 左上
    vec2(1.0, 1.0)    // 右上
    );

    fragCoord = positions[gl_VertexID].xy * 0.5 + 0.5;
    gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
}