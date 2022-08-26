cmake_minimum_required(VERSION 3.5)

project(video_infos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(video_infos main.cpp videoinfo.h videoinfo.cpp)

TARGET_LINK_LIBRARIES(video_infos avformat)
TARGET_LINK_LIBRARIES(video_infos avcodec)
TARGET_LINK_LIBRARIES(video_infos avutil)

install(TARGETS video_infos)

list(APPEND SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	videoinfo.h videoinfo.cpp
)
