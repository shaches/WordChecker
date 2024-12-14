cmake_minimum_required(VERSION 3.31.2)
project(WordChecker 
	VERSION 0.0.1
	DESCRIPTION "Checks for repeated words in given text."
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(src/app)

configure_file(src/config.h.in ../src/config.h)
target_include_directories(WordChecker PUBLIC "${PROJECT_BINARY_DIR}")

