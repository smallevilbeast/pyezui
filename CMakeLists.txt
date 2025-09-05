cmake_minimum_required(VERSION 3.12...3.26)

# 设置项目名称和版本
project(ezui_python VERSION 0.1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
if(UNIX)
    add_compile_options(-finput-charset=UTF-8)
    add_compile_options(-fexec-charset=UTF-8)
elseif(WIN32)
    add_compile_options(/utf-8)
endif()

# 让所有项目都使用UNICODE
add_definitions(-D_UNICODE -DUNICODE)

# 查找Python和pybind11
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# 添加EzUI库路径
set(EZUI_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/EzUI)
set(EZUI_INCLUDE_DIR ${EZUI_ROOT_DIR}/include)
set(EZUI_SOURCE_DIR ${EZUI_ROOT_DIR}/sources)

# 收集EzUI源文件
file(GLOB EZUI_SOURCES 
    ${EZUI_SOURCE_DIR}/*.cpp
    ${EZUI_INCLUDE_DIR}/EzUI/*.h
)

# 收集Python绑定源文件
file(GLOB BINDING_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/controls/*.cpp
)

# 创建pybind11模块
pybind11_add_module(ezui 
    ${BINDING_SOURCES}
    ${EZUI_SOURCES}
)

# 设置包含目录
target_include_directories(ezui PRIVATE 
    ${EZUI_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Windows特定设置
if(WIN32)
    # Direct2D和相关库
    target_link_libraries(ezui PRIVATE
        d2d1
        dwrite
        windowscodecs
        user32
        gdi32
        ole32
        oleaut32
        uuid
        kernel32
        shell32
        advapi32
        comdlg32
        comctl32
    )
    
    # 定义宏
    target_compile_definitions(ezui PRIVATE
        WIN32
        _WINDOWS
        USED_DIRECT2D=1
        NOMINMAX
        WIN32_LEAN_AND_MEAN
        _CRT_SECURE_NO_WARNINGS
    )
    
    # 设置运行时库
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set_property(TARGET ezui PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    else()
        set_property(TARGET ezui PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif()
endif()

# 设置输出属性
set_target_properties(ezui PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN TRUE
)

# 编译定义
target_compile_definitions(ezui PRIVATE VERSION_INFO=${PROJECT_VERSION})

# 设置链接器语言
set_target_properties(ezui PROPERTIES LINKER_LANGUAGE CXX)

# 安装规则
install(TARGETS ezui
    DESTINATION .
)

# 生成编译命令数据库
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 调试信息
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
    target_compile_definitions(ezui PRIVATE _DEBUG)
else()
    message(STATUS "Building in Release mode")
    target_compile_definitions(ezui PRIVATE NDEBUG)
endif()

# 显示配置信息
message(STATUS "Python version: ${Python_VERSION}")
message(STATUS "Python include dirs: ${Python_INCLUDE_DIRS}")
message(STATUS "Python libraries: ${Python_LIBRARIES}")
message(STATUS "pybind11 version: ${pybind11_VERSION}")
message(STATUS "EzUI root directory: ${EZUI_ROOT_DIR}")
message(STATUS "EzUI include directory: ${EZUI_INCLUDE_DIR}")
message(STATUS "EzUI source directory: ${EZUI_SOURCE_DIR}")