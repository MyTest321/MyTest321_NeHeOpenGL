set(PROJECT_NAME Lesson046)
message("==== ${PROJECT_NAME} ====")
project(${PROJECT_NAME})

my_add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER Tutorials)
