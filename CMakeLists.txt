cmake_minimum_required( VERSION 2.8 )
project( Segmentation )

# Set C++ Version
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" HAS_CXX1Y)
CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" HAS_CXX0x)
if(HAS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(HAS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
elseif(HAS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(HAS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

# Required packages
find_package( OpenCV REQUIRED )

# Add Executables
add_executable( segmentation main.cpp
    centroid.cpp
    histogram_group.cpp
    histogram_knn.cpp
    histogram.cpp
    kmeans.cpp )

# Link libraries
target_link_libraries( segmentation ${OpenCV_LIBS} )
