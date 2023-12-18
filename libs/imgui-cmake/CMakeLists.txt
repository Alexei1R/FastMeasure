cmake_minimum_required(VERSION 3.20)
project(imgui)


# print curent directory
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")



#message curent cmake dir
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")


set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/libs/imgui-cmake)


set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)


set(ROOT ${IMGUI_DIR})

add_library(imgui STATIC

	${ROOT}/imgui/imgui.cpp
	${ROOT}/imgui/imgui.h
	${ROOT}/imgui/imstb_rectpack.h
	${ROOT}/imgui/imstb_textedit.h
	${ROOT}/imgui/imstb_truetype.h
    ${ROOT}/imgui/imgui_demo.cpp
    ${ROOT}/imgui/imgui_draw.cpp
    ${ROOT}/imgui/imgui_internal.h
    ${ROOT}/imgui/imgui_tables.cpp
    ${ROOT}/imgui/imgui_widgets.cpp


	${ROOT}/imconfig-SFML.h
	${ROOT}/imgui-SFML.cpp
	${ROOT}/imgui-SFML.h
	${ROOT}/imgui-SFML_export.h

)

target_include_directories(imgui
  PUBLIC ${IMGUI_DIR}
  PUBLIC ${IMGUI_DIR}/backends
)



# Link against the OpenGL and GLEW libraries
target_link_libraries(imgui
		sfml-graphics
		sfml-audio
)
