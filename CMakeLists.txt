cmake_minimum_required(VERSION 3.10)
project(SpinnakerDemo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 要编译的单个源文件（项目根目录下）
set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/Acquisition.cpp")
if(NOT EXISTS "${SOURCE_FILE}")
    message(FATAL_ERROR "Required source not found: ${SOURCE_FILE}")
endif()

add_executable(${PROJECT_NAME} "${SOURCE_FILE}")

# include 目录
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

# ---------------------------
# OpenCV 配置
# ---------------------------
set(OpenCV_DIR "D:/CppLibrary/opencv/build") # 指向 OpenCVConfig.cmake 所在目录
find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    message(STATUS "Found OpenCV version ${OpenCV_VERSION}")
    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
else()
    message(FATAL_ERROR "OpenCV not found in ${OpenCV_DIR}")
endif()

# ---------------------------
# Windows 下选择 lib 子目录（默认 vs2017）
# ---------------------------
if(WIN32)
    option(MSVC_LIB_DIR "Subfolder in lib64 for MSVC libs (e.g. vs2015 or vs2017)" "vs2017")
    set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib64/${MSVC_LIB_DIR}")   #-DMSVC_LIB_DIR=vs2015
    if(EXISTS "${LIB_DIR}")
        file(GLOB LIB_FILES CONFIGURE_DEPENDS "${LIB_DIR}/*.lib")
        if(LIB_FILES)
            target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_FILES})
        else()
            message(WARNING "No .lib files found in ${LIB_DIR}")
        endif()
    else()
        message(WARNING "Library directory not found: ${LIB_DIR}")
    endif()

    message(STATUS "If needed, run CMake with -DMSVC_LIB_DIR=vs2015 to use vs2015 libs.")
else()
    # Unix: link any static/shared libs placed directly in lib64/
    file(GLOB LIB_FILES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/lib64/*.a"
        "${CMAKE_SOURCE_DIR}/lib64/*.so"
    )
    if(LIB_FILES)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_FILES})
    endif()

    # rpath so executable can find lib64 next to install/build
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH "$ORIGIN/../lib64"
        INSTALL_RPATH "$ORIGIN/../lib64"
    )
endif()

# 默认构建类型（不覆盖 CI/IDE 明确选择）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()
