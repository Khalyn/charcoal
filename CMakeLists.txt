cmake_minimum_required( VERSION 3.21 )
project( charcoal )

set( CMAKE_CXX_STANDARD 23 )

include_directories( . )

add_executable( charcoal
	src/main.cpp
	)

if ( MSVC )
	#[[ https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170 ]]
	target_compile_options( charcoal
		BEFORE
		PRIVATE "/std:c++latest"
		PRIVATE "/MP" #[[ Enable multi-processors builds with MSVC ]]
		PRIVATE "/permissive-"
		PRIVATE "/W4"
		# PRIVATE "/WX" #[[ Treat warning as an error, but overkill for the moment ]]
	)
else()
	message( SEND_ERROR "This project is only configured with MSVC for the moment." )
endif()
