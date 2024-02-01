set(PROJECT_NAME Lesson047)
message("==== ${PROJECT_NAME} ====")
project(${PROJECT_NAME})

my_add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER Tutorials)

#"${PROJECT_SOURCE_DIR}/libs/$<CONFIGURATION>"

# copy cg-toolkit bin folder to output .exe folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	$ENV{CG_BIN_PATH}
	$<TARGET_FILE_DIR:${PROJECT_NAME}>
)
