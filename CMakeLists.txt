cmake_minimum_required(VERSION 3.5.0)

project(opengl_cpp VERSION 0.1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

# 添加包含路径(include_directories无法使用‘folder/**’进行递归)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/graphics)
include_directories(${CMAKE_SOURCE_DIR}/include/utils)
include_directories(/opt/homebrew/include)

# 添加链接库路径
link_directories(/opt/homebrew/opt/glew/lib)
link_directories(/opt/homebrew/opt/glfw/lib)

# 添加可执行文件
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)  # 自动找到 src 目录下的所有 .cpp 文件
file(GLOB UTILS ${CMAKE_SOURCE_DIR}/src/utils/*.cpp)
# message(STATUS "SOURCES: ${SOURCES}")


add_executable(opengl_cpp ${SOURCES} ${UTILS}) 
# add_executable(opengl_cpp src/main.cpp)

# 指定生成的可执行文件放在项目根目录
# set_target_properties(opengl_cpp PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
# )    

# 链接库
target_link_libraries(opengl_cpp glfw glew "-framework OpenGL")

# 启用测试
# include(CTest)
# enable_testing()

# 打包设置
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)


# --- default config ---
# cmake_minimum_required(VERSION 3.5.0)
# project(openGL_cpp VERSION 0.1.0 LANGUAGES C CXX)

# add_executable(openGL_cpp main.cpp)

# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)



# ---头文件批量引入---
# # 查找 include 目录下所有头文件
# file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h)

# # 遍历、提取包含头文件的目录。
# foreach(HEADER_FILE ${HEADER_FILES})
#     get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)
#     list(APPEND HEADER_DIRS ${HEADER_DIR})
# endforeach()

# # 去除重复的目录
# list(REMOVE_DUPLICATES HEADER_DIRS)

# # 添加头文件目录到 include path
# include_directories(${HEADER_DIRS})




# 生成clangd需要的compile_command JSON
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .

