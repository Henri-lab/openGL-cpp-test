#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 顶点着色器的源代码
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform float xOffset;  // x轴上的偏移量
void main()
{
    // 在 x 轴上偏移三角形的位置
    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);
}
)";

// 片段着色器的源代码
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.5, 0.8, 0.2, 1.0);  // 绿色
}
)";

int main() {
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Moving Triangle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // 初始化 GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // 定义三角形的顶点数据
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // 左下角
         0.5f, -0.5f, 0.0f,  // 右下角
         0.0f,  0.5f, 0.0f   // 顶部
    };

    // 创建 VBO 和 VAO
    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // 绑定 VAO
    glBindVertexArray(VAO);

    // 绑定 VBO 并传输数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // 检查编译是否成功
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 检查编译是否成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建着色器程序并链接
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检查链接是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 删除着色器，因为它们已经链接到程序中了，不再需要
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 使用着色器程序
    glUseProgram(shaderProgram);

    // 获取着色器中偏移量的 uniform 位置
    int xOffsetLocation = glGetUniformLocation(shaderProgram, "xOffset");

    // 定义初始的偏移量和速度
    float xOffset = 0.0f;
    float speed = 0.01f;

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 清除颜色缓冲区
        glClear(GL_COLOR_BUFFER_BIT);

        // 动态改变三角形的 X 轴位置（使它来回移动）
        xOffset += speed;
        if (xOffset > 1.0f || xOffset < -1.0f) {
            speed = -speed;  // 当到达边界时反向移动
        }

        // 传递偏移量给着色器
        glUniform1f(xOffsetLocation, xOffset);

        // 绑定 VAO 并绘制三角形
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换缓冲区并处理事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // 销毁窗口并终止 GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}