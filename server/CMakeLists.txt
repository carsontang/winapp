project(server)

set(server_SOURCES
	server.cpp)

if(MSVC)
	add_compile_options("$<$<CONFIG:RelWithDebInfo>:/MT>")
endif()

# main.cpp uses a WinMain entry point, thus the need for Win32
# See https://cmake.org/cmake/help/v3.8/command/add_executable.html
add_executable(server
	${server_SOURCES})

# target_include_directories(server PRIVATE ${server_HEADERS})

target_link_libraries(server d3d11 dxguid)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(_output_suffix "64")
else()
	set(_output_suffix "32")
endif()
 
set_target_properties(server
    PROPERTIES
    OUTPUT_NAME "server${_output_suffix}")

install(TARGETS server DESTINATION bin)

message(STATUS "Will install server in ${CMAKE_INSTALL_PREFIX}/bin")