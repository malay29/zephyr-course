cmake_minimum_required(VERSION 3.20.0)

#list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE}) # we tell cmake to look for zephyr 
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp) # the app target is created, and we can add the src files, app name is always app, we can make changes in the project name but here it needs to be app
add_subdirectory(drivers/our_driver)
