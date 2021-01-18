cmake_minimum_required(VERSION 3.17)
project(Image)

#inicio 1
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "C:\\openCV\\mingw-build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#Fin 1
#Achivos del proyecto
add_executable(Image main.cpp)
#Inico 2
# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(Image ${OpenCV_LIBS})
#fin 2