project(XCanvas)

add_executable(testbed
        main.cpp
)

target_include_directories(testbed PRIVATE ${CODE_DIR})

target_link_libraries(testbed PRIVATE XCanvas)