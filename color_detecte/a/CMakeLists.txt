cmake_minimum_required(VERSION 3.15)
project(detector)
file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/src/detector/include/detector)
include_directories(${PROJECT_SOURCE_DIR}/src/google_logger/include/google_logger)
add_executable(${PROJECT_NAME} ${SRC})
find_package(OpenCV REQUIRED)
find_package(glog REQUIRED)
find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC 
        ${OpenCV_LIBS} 
        glog::glog
        fmt::fmt)
