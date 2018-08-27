project(carson-winapp)

set(carson-winapp_SOURCES
	main.cpp)

if(MSVC)
	add_compile_options("$<$<CONFIG:RelWithDebInfo>:/MT>")
endif()

# main.cpp uses a WinMain entry point, thus the need for Win32
# See https://cmake.org/cmake/help/v3.8/command/add_executable.html
add_executable(carson-winapp
    WIN32
	${carson-winapp_SOURCES})

target_link_libraries(carson-winapp)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(_output_suffix "64")
else()
	set(_output_suffix "32")
endif()
 
set_target_properties(carson-winapp
    PROPERTIES
    OUTPUT_NAME "carson-winapp${_output_suffix}")

install(TARGETS carson-winapp DESTINATION bin)
 
message(STATUS "Will install carson-winapp in ${CMAKE_INSTALL_PREFIX}/bin")