cmake_minimum_required(VERSION 2.8)
project(XOR_NN)

# Windows specific stuff
if(WIN32) # Works for both 32 and 64 bit systems btw
	# Define project as a console application
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
	
	# Only available for CMAKE 3.6.0 and higher	
	if(NOT(CMAKE_MAJOR_VERSION LESS 3))
		if(NOT(CMAKE_MINOR_VERSION LESS 6))
			# Tell Visual Studio to use our project as default startup
			set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT XOR_NN)
		endif()
	endif()
endif()

add_subdirectory(src)