# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(
	Keyboard_Firmware
	VERSION 1.0
	LANGUAGES C CXX ASM
)

# Include the definition of the slc_Keyboard_Firmware target,
# which contains the content of the SLC project
include(Keyboard_Firmware.cmake)

add_executable(Keyboard_Firmware
    # Add additional sources here
)

target_include_directories(Keyboard_Firmware PUBLIC
    # Add additional include paths here
)

target_compile_definitions(Keyboard_Firmware PUBLIC
    # Add additional macros here
)

target_compile_options(Keyboard_Firmware PUBLIC
    # Set additional compiler flags here
)

target_link_options(Keyboard_Firmware PUBLIC
    # Set additional linker flags here
)

# Link with the content defined in the SLC project
target_link_libraries(Keyboard_Firmware PRIVATE
    slc_Keyboard_Firmware
)

# Include managed project content if available
include(Keyboard_Firmware_project.cmake OPTIONAL RESULT_VARIABLE managed_project)
if(managed_project)
    message(STATUS "Using managed project content from ${managed_project}")
endif()

# Force the gcc linker command
set_target_properties(Keyboard_Firmware PROPERTIES LINKER_LANGUAGE C)

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET Keyboard_Firmware
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:Keyboard_Firmware>" "$<TARGET_FILE_DIR:Keyboard_Firmware>/$<TARGET_FILE_BASE_NAME:Keyboard_Firmware>.s37"
    COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:Keyboard_Firmware>" "$<TARGET_FILE_DIR:Keyboard_Firmware>/$<TARGET_FILE_BASE_NAME:Keyboard_Firmware>.hex"
    COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:Keyboard_Firmware>" "$<TARGET_FILE_DIR:Keyboard_Firmware>/$<TARGET_FILE_BASE_NAME:Keyboard_Firmware>.bin" 
)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET Keyboard_Firmware
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)
endif()