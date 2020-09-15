cmake_minimum_required(VERSION 2.8)

project( cvThresh )
find_package( OpenCV REQUIRED )

add_executable( cvThresh cvThresh.cpp )
target_link_libraries( cvThresh ${OpenCV_LIBS} )
