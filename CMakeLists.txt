cmake_minimum_required(VERSION 3.18)

option(OPT_CG_TOOLKIT "OPT_CG_TOOLKIT" OFF)
if (OPT_CG_TOOLKIT)
	message("OPT_CG_TOOLKIT ON")
	message("CG_BIN_PATH=$ENV{CG_BIN_PATH}")
	message("CG_LIB_PATH=$ENV{CG_LIB_PATH}")
	message("CG_INC_PATH=$ENV{CG_INC_PATH}")
endif(OPT_CG_TOOLKIT)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(NeHeOpenGL)

set(cmake_root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(cmake_root_bin_dir ${CMAKE_CURRENT_BINARY_DIR})

function(my_source_group src_path src_files)
	foreach(FILE ${src_files}) 
		get_filename_component(PARENT_DIR "${FILE}" PATH)
		file(RELATIVE_PATH PARENT_DIR ${src_path} ${PARENT_DIR})
		string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")
		set(GROUP "${GROUP}")
		source_group("${GROUP}" FILES "${FILE}")	
	endforeach()
endfunction()

function(my_add_executable target_name src_path)
	file(GLOB_RECURSE src_files
		"${src_path}/*.*"
	)

	my_source_group(${src_path} "${src_files}")
	add_compile_definitions(MY_CMAKE_BIN_DIR="${cmake_root_bin_dir}")
	add_executable(${target_name}
		${src_files}
		${cmake_root_dir}/my_common.h
		${cmake_root_dir}/main.cpp
	)

	target_link_options(${target_name} PUBLIC "$<$<C_COMPILER_ID:MSVC>:-SAFESEH:NO>") # https://stackoverflow.com/questions/14710577/error-lnk2026-module-unsafe-for-safeseh-image

	target_link_directories(${target_name} PUBLIC ${cmake_root_dir}/lib) # linker additional library directories

	target_include_directories(${target_name} PUBLIC
		${cmake_root_dir} 			# need '#include <gl\glaux.h>'
		${cmake_root_dir}/freetype  # need '#include <ft2build.h>'
	) 

	if (OPT_CG_TOOLKIT)
		target_include_directories(${target_name} PUBLIC $ENV{CG_INC_PATH}) # need '#include <cg\cg.h>' '#include <cg\cggl.h>'
		target_link_directories(${target_name} PUBLIC $ENV{CG_LIB_PATH}) # linker additional library directories
	endif(OPT_CG_TOOLKIT)

endfunction()

#----------
add_subdirectory(Lesson01)
add_subdirectory(Lesson02)
add_subdirectory(Lesson03)
add_subdirectory(Lesson04)
add_subdirectory(Lesson05)
add_subdirectory(Lesson06)
add_subdirectory(Lesson07)
add_subdirectory(Lesson08)
add_subdirectory(Lesson09)
add_subdirectory(Lesson10)
add_subdirectory(Lesson11)
add_subdirectory(Lesson12)
add_subdirectory(Lesson13)
add_subdirectory(Lesson14)
add_subdirectory(Lesson15)
add_subdirectory(Lesson16)
add_subdirectory(Lesson17)
add_subdirectory(Lesson18)
add_subdirectory(Lesson19)
add_subdirectory(Lesson20)
add_subdirectory(Lesson21)
add_subdirectory(Lesson22)
add_subdirectory(Lesson23)
add_subdirectory(Lesson24)
add_subdirectory(Lesson25)
add_subdirectory(Lesson26)
add_subdirectory(Lesson27)
add_subdirectory(Lesson28)
add_subdirectory(Lesson29)
add_subdirectory(Lesson30)
add_subdirectory(Lesson31)
add_subdirectory(Lesson32)
add_subdirectory(Lesson33)
add_subdirectory(Lesson34)
add_subdirectory(Lesson35)
add_subdirectory(Lesson36)
add_subdirectory(Lesson37)
add_subdirectory(Lesson38)
add_subdirectory(Lesson39)
add_subdirectory(Lesson40)
add_subdirectory(Lesson41)
add_subdirectory(Lesson42)
add_subdirectory(Lesson43)
add_subdirectory(Lesson44)
add_subdirectory(Lesson45)
add_subdirectory(Lesson46)
add_subdirectory(Lesson48)

if (OPT_CG_TOOLKIT)	
	include_directories($ENV{CG_INC_PATH})
	add_subdirectory(Lesson47)
endif(OPT_CG_TOOLKIT)

#set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT Lesson01)