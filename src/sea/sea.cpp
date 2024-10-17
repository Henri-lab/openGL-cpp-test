#include "read.h"
#include "shader.h"
#include <string>
using namespace std;


int main() {
  const string frag = "/Users/henrifox/_code_source_/opengl_code/src/sea/.frag";//🤧
  const string vert = "/Users/henrifox/_code_source_/opengl_code/src/sea/.vert";//🤧
  string fragSource = readShaderFile(frag);
  string vertSource = readShaderFile(vert);
  const char *fragmentShaderSource =fragSource.c_str();
  const char *vertexShaderSource = vertSource.c_str();
  // render!
  // #ifdef __EMSCRIPTEN__
  // renderShader_web((char *)vertexShaderSource,(char *)fragmentShaderSource);
  // #else
  // renderShader((char *)vertexShaderSource,(char *)fragmentShaderSource);
  // #endif
  renderShader((char *)vertexShaderSource,(char *)fragmentShaderSource);
  return 0;
}
