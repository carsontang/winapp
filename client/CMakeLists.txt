project(client)

set(client_SOURCES
	client.cpp)

if(MSVC)
	add_compile_options("$<$<CONFIG:RelWithDebInfo>:/MT>")
endif()

# main.cpp uses a WinMain entry point, thus the need for Win32
# See https://cmake.org/cmake/help/v3.8/command/add_executable.html
add_executable(client
	${client_SOURCES})

# target_include_directories(client PRIVATE ${client_HEADERS})

target_link_libraries(client d3d11 dxguid)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(_output_suffix "64")
else()
	set(_output_suffix "32")
endif()
 
set_target_properties(client
    PROPERTIES
    OUTPUT_NAME "client${_output_suffix}")

install(TARGETS client DESTINATION bin)

message(STATUS "Will install client in ${CMAKE_INSTALL_PREFIX}/bin")