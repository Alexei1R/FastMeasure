cmake_minimum_required(VERSION 3.0)
project(FastMeasure)
find_package(OpenCV REQUIRED )


set(SOURCES
        main.cpp
        FastMeasure/Application.cpp
        FastMeasure/Application.h
        FastMeasure/Core/Layers/Layer.cpp
        FastMeasure/Core/Layers/Layer.h
        FastMeasure/Core/Layers/LayerStack.cpp
        FastMeasure/Core/Layers/LayerStack.h
        FastMeasure/fastmeasurepch.h
        FastMeasure/EmbededPlatform/LidarReadLayer.cpp
        FastMeasure/EmbededPlatform/LidarReadLayer.h
        FastMeasure/Display/DisplayData.cpp
        FastMeasure/Display/DisplayData.h

)

file(GLOB COMMUNICATION_SOURCES
        "Communication/*.cpp"
        "Communication/*.h"
)

list(APPEND SOURCES ${COMMUNICATION_SOURCES})


add_executable(executable ${SOURCES} )

target_link_libraries(executable
        ${OpenCV_LIBS}
        glm
        sfml-graphics
        sfml-audio
)



target_include_directories(executable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)


