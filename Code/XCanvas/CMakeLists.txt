project(XCanvas)

include(${CODE_DIR}/Vendor/Vendor.cmake)

add_library(XCanvas STATIC
        # Vendor sources
        ${GLAD_SOURCES}

        # Library sources
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Canvas.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Canvas.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Color.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Macros.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Point.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Shaders.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Typedefs.hpp
)

target_include_directories(XCanvas PUBLIC ${CODE_DIR}/Vendor)

target_link_libraries(XCanvas PUBLIC glfw OpenGL::GL)