#include "read.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
using namespace std;

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

int main() {
  const string frag = "/Users/henrifox/_code_source_/opengl_code/src/sea/.frag";
  const string vert = "/Users/henrifox/_code_source_/opengl_code/src/sea/.vert";
  string fragSource = readShaderFile(frag);
  string vertSource = readShaderFile(vert);
  const char *fragmentShaderSource =fragSource.c_str();//C风格str ，便与 OpenGL 等 API 兼容
  const char *vertexShaderSource = vertSource.c_str();

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
    glUniform3f(glGetUniformLocation(shaderProgram, "iResolution"),
                (float)width, (float)height, 1.0f);
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
