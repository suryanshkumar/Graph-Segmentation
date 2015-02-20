# Make sure the compiler can find include files from our src library.
cmake_minimum_required(VERSION 2.6)
#cmake_policy(SET CMP0012 NEW)
SET(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -O3 -ffast-math -fomit-frame-pointer -funroll-loops -fopenmp -msse2")
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
SET(CMAKE_BUILD_TYPE RELEASE)
INCLUDE_DIRECTORIES(/usr/local/include )

find_package( OpenCV REQUIRED )
set(CORELIBS GraphSegmentation ${OpenCV_LIBS})
#set(CORELIBS VisionMachinelib /usr/lib/libgdal.so)
#...............

ADD_EXECUTABLE(graph_segmentation graph-segmentation)
TARGET_LINK_LIBRARIES(graph_segmentation ${CORELIBS})


