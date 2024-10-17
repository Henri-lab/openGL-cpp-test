cmake_minimum_required(VERSION 3.5.0)
project(opengl_cpp VERSION 0.1.0 LANGUAGES CXX)

# C++ standard settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# General include directories
include_directories(${CMAKE_SOURCE_DIR}/utils)

# Conditionally handle Emscripten-specific settings
if (EMSCRIPTEN)
    # Use Emscripten's em++ compiler
    message("Building for WebAssembly")
    set(CMAKE_CXX_COMPILER em++)

    # Emscripten-specific executable suffix and flags
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FETCH=1 -O3")

    # Emscripten WebAssembly target
    file(GLOB UTILS ${CMAKE_SOURCE_DIR}/utils/*.cpp)
    add_executable(out_web ./sea.cpp ${UTILS})

    # Link against WebGL (no need for GLEW or native OpenGL)
    target_link_libraries(out_web glfw "-s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1")

else()
    # Native macOS build configuration
     message("Building for macOS")
    # Use native clang++ compiler
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    
    # macOS architecture (for Apple Silicon)
    set(CMAKE_OSX_ARCHITECTURES "arm64")

    # Include directories
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/opt/glew/lib)
    link_directories(/opt/homebrew/opt/glfw/lib)

    # Native macOS target
    file(GLOB UTILS ${CMAKE_SOURCE_DIR}/utils/*.cpp)
    add_executable(out ./sea.cpp ${UTILS})

    # Link against native GLFW and OpenGL for macOS
    target_link_libraries(out glfw glew "-framework OpenGL")

endif()
