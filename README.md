cmake_minimum_required(VERSION 3.17)   
project(Ejm8)   
set(CMAKE_CXX_STANDARD 14)   
#inicio   
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")   
set(OpenCV_DIR "C:\\openCV\\mingw-build\\install")   
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")   
find_package(OpenCV REQUIRED)   
include_directories(${OpenCV_INCLUDE_DIRS})   
#Fin   
#Proyecto y archivos   
add_executable(Ejm8 main.cpp)  
   
#Inico 2| cambiar nombre   
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)    
target_link_libraries(Ejm8 ${OpenCV_LIBS})   
#fin 2  
