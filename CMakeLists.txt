cmake_minimum_required(VERSION 3.10)
project(SpinnakerAcquisition VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------
# 源文件
# ---------------------------
set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/Acquisition.cpp")
if(NOT EXISTS "${SOURCE_FILE}")
    message(FATAL_ERROR "Required source not found: ${SOURCE_FILE}")
endif()
add_executable(${PROJECT_NAME} 
    "${SOURCE_FILE}"
    "app.rc"           # 图标资源
)


# ---------------------------
# OpenCV
# ---------------------------
# Windows 默认路径，可根据实际修改
if(WIN32)
    set(OpenCV_DIR "D:/CppLibrary/opencv/build")  # 指向 OpenCVConfig.cmake 所在目录
endif()

find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    message(STATUS "Found OpenCV version ${OpenCV_VERSION}")
    target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
else()
    message(FATAL_ERROR "OpenCV not found!")
endif()

# ---------------------------
# Spinnaker SDK
# ---------------------------
if(WIN32)
    # Windows 路径
    set(SPINNAKER_DIR "${CMAKE_SOURCE_DIR}/lib64/vs2015")  # 放置 .lib 文件
    target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/include/Spinnaker"
        "${CMAKE_SOURCE_DIR}/include/SpinGenApi"
    )
    file(GLOB SPINNAKER_LIBS "${SPINNAKER_DIR}/*.lib")
    if(SPINNAKER_LIBS)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${SPINNAKER_LIBS})
    else()
        message(WARNING "No Spinnaker .lib files found in ${SPINNAKER_DIR}")
    endif()
else()
    # Linux 路径
    set(SPINNAKER_DIR "/opt/spinnaker")   # 根据实际安装修改
    target_include_directories(${PROJECT_NAME} PRIVATE
        "${SPINNAKER_DIR}/include"
        "${SPINNAKER_DIR}/include/Spinnaker"
        "${SPINNAKER_DIR}/include/SpinGenApi"
    )
    link_directories("${SPINNAKER_DIR}/lib")
    file(GLOB SPINNAKER_LIBS
        "${SPINNAKER_DIR}/lib/libSpinnaker.so*"
        "${SPINNAKER_DIR}/lib/libGenApi*.so*"
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SPINNAKER_LIBS} pthread)
endif()

# ---------------------------
# Windows 特有选项
# ---------------------------
if(MSVC)
    add_compile_options("/utf-8")
endif()

# ---------------------------
# 输出路径
# ---------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
message("***************************")
message("******Done!!!!!!!!!!!******")
message("***************************")