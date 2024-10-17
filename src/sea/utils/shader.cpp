#include "shader.h"

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h> // For WebGL 2
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#else
#include <GL/glew.h> // For desktop OpenGL
#endif

#include <GLFW/glfw3.h>
#include <iostream>

GLuint compileShader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);
  // 检查编译错误
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "错误：着色器编译失败\n" << infoLog << std::endl;
  }
  return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  // 检查链接错误
  GLint success;
  GLchar infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    std::cerr << "错误：程序链接失败\n" << infoLog << std::endl;
  }
  return program;
}

int renderShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
  // 初始化 GLFW 库
  if (!glfwInit()) {
    std::cerr << "无法初始化 GLFW" << std::endl;
    return -1;
  }

  // 设置 OpenGL 版本为 3.3 Core Profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 创建一个窗口
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
  if (!window) {
    std::cerr << "无法创建 GLFW 窗口" << std::endl;
    glfwTerminate();
    return -1;
  }

  // 设置当前上下文
  glfwMakeContextCurrent(window);

  // 初始化 GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "无法初始化 GLEW" << std::endl;
    return -1;
  }

  // 编译着色器并创建着色器程序
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  GLuint fragmentShader =
      compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);

  // 删除已编译的着色器
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // 创建一个 VAO
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // 渲染循环
  while (!glfwWindowShouldClose(window)) {
    // 获取当前时间
    float currentTime = glfwGetTime();

    // 设置视口
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // 清空颜色缓冲
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用着色器程序
    glUseProgram(shaderProgram);

    // 设置 Uniform 变量
    glUniform3f(glGetUniformLocation(shaderProgram, "iResolution"), (float)width, (float)height, 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "iTime"), currentTime);
    // 这里可以添加鼠标输入处理，设置 iMouse

    // 绘制全屏四边形
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // 交换缓冲并处理事件
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // 清理资源
  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1, &VAO);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

// In WebGL 2, the following functions are part of the core specification:
// This means you can use these functions directly without needing GLEW when
// targeting WebAssembly.
// ---------------------
// glGenVertexArrays
// glBindVertexArray
// glDeleteVertexArrays

// 全局变量
GLuint shaderProgram;
GLuint VAO;
int canvasWidth = 800, canvasHeight = 600;
float currentTime = 0.0f;

// webassembly
int renderShader_web(const char *vertexShaderSource,const char *fragmentShaderSource) {
  // 创建 WebGL 上下文
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE initWebGL() {
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.antialias = true;
    attrs.majorVersion = 2; // 使用 WebGL 2
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx =
        emscripten_webgl_create_context("#canvas", &attrs);
    if (ctx <= 0) {
      std::cerr << "无法创建 WebGL 上下文！" << std::endl;
      return 0;
    }
    emscripten_webgl_make_context_current(ctx);
    return ctx;
  }

  // 渲染循环
  void renderLoop() {
    // 更新时间
    currentTime += 0.016f; // 模拟帧时间

    // 清屏
    glViewport(0, 0, canvasWidth, canvasHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用着色器程序
    glUseProgram(shaderProgram);

    // 设置 uniform 变量
    glUniform3f(glGetUniformLocation(shaderProgram, "iResolution"),
                (float)canvasWidth, (float)canvasHeight, 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "iTime"), currentTime);

    // 绘制
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // 请求下一帧渲染
    emscripten_webgl_commit_frame();
  }
  // 初始化 WebGL 上下文
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = initWebGL();
  if (!context) {
    return -1;
  }

  // 编译着色器并创建着色器程序
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  GLuint fragmentShader =
      compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  shaderProgram = createShaderProgram(vertexShader, fragmentShader);

  // 删除着色器，因为我们已经不再需要它们了
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // 创建 VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // 启动渲染循环
  emscripten_set_main_loop(renderLoop, 0, 1);

  return 0;
}
