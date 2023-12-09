cmake_minimum_required(VERSION 3.0)
project(FastMeasure)
find_package(OpenCV REQUIRED )


set(SOURCES
        main.cpp
        
)

file(GLOB COMMUNICATION_SOURCES
        "Communication/*.cpp"
        "Communication/*.h"
)

list(APPEND SOURCES ${COMMUNICATION_SOURCES})


add_executable(executable ${SOURCES} )

target_link_libraries(executable
        ${OpenCV_LIBS}
)



target_include_directories(executable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)


