cmake_minimum_required(VERSION 2.8)
project( DisplayImage )

include_directories(${CMAKE_SOURCE_DIR}/../install/include)
link_directories(${CMAKE_SOURCE_DIR}/../install/lib)

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/ImagePyramid.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/LaplacianPyramid.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/OrientedPyramid.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Exercise6.cpp
)
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/ImagePyramid.h
   ${CMAKE_CURRENT_SOURCE_DIR}/LaplacianPyramid.h
   ${CMAKE_CURRENT_SOURCE_DIR}/OrientedPyramid.h
)

find_package( OpenCV REQUIRED )
add_executable( DisplayImage ${SOURCE} ${HEADERS})

target_link_libraries( DisplayImage ${OpenCV_LIBS} )