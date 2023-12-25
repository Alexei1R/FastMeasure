cmake_minimum_required(VERSION 3.5)
project(FastMeasure)
find_package(OpenCV REQUIRED )
find_package(PCL REQUIRED)


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
        FastMeasure/UI/UI.cpp
        FastMeasure/UI/UI.h
        FastMeasure/UI/logo.h
        FastMeasure/UI/widgets.h
        FastMeasure/Algorithm/FindLines.cpp
        FastMeasure/Algorithm/FindLines.h

)

file(GLOB COMMUNICATION_SOURCES
        "Communication/*.cpp"
        "Communication/*.h"
)

list(APPEND SOURCES ${COMMUNICATION_SOURCES})


add_executable(executable ${SOURCES} )

target_link_libraries(executable
        ${OpenCV_LIBS}
        ${PCL_LIBRARIES}
        glm
        sfml-graphics
        sfml-audio
        imgui
)



target_include_directories(executable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)


