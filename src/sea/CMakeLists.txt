cmake_minimum_required(VERSION 3.5.0)
project(opengl_cpp VERSION 0.1.0 LANGUAGES CXX)
message("System name: ${CMAKE_SYSTEM_NAME}")


# C++ standard settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# General include directories
include_directories(/opt/homebrew/include)
include_directories(${CMAKE_SOURCE_DIR}/utils)


# Conditionally handle Emscripten-specific settings
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    # Use Emscripten's em++ compiler
    message("Building for WebAssembly")
    set(CMAKE_CXX_COMPILER em++)

    # Emscripten-specific executable suffix and flags
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_WEBGL2=1 -s FULL_ES3=1")#开启对webgl2 、OpenGL ES 3.0 API的支持


    # Set output directories
    # For executables
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build_web")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build_web")

    # For shared libraries
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build_web")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build_web")

    # For static libraries
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build_web")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build_web")
   
    # Emscripten WebAssembly target
    file(GLOB UTILS ${CMAKE_SOURCE_DIR}/utils/*.cpp)
    add_executable(out_web ./sea.cpp ${UTILS})

    # Link against WebGL (no need for GLEW or native OpenGL)
    link_directories(/opt/homebrew/opt/glfw/lib)
    target_link_libraries(out_web glfw "-s USE_WEBGL2=1 -s USE_GLFW=3 -s FULL_ES3=1 -s WASM=1")

    # Set output directories for the Emscripten target
    set_target_properties(out_web PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build_web"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build_web"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build_web")

    

else()
    # Native macOS build configuration
    message("Building for macOS-clang++")
    # Use native clang++ compiler
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    
    # macOS architecture (for Apple Silicon)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
   
    # Native macOS target
    file(GLOB UTILS ${CMAKE_SOURCE_DIR}/utils/*.cpp)
    add_executable(out ./sea.cpp ${UTILS})
   
    # Link against native GLFW and OpenGL for macOS
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
    target_link_libraries(out PRIVATE glfw GLEW::GLEW "-framework OpenGL")

endif()
