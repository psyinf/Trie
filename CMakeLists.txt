cmake_minimum_required(VERSION 3.21)
set(PROJECT Trie)
project(${PROJECT} VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_RELWITHDEBINFO_POSTFIX _rd)

set(PROJECT_NAMESPACE ${PROJECT})			# namespace for target aliases in this project
set(PROJECT_EXPORT_NAME ${PROJECT})			# export name to be used by install() and downstream find_package()
set(PROJECT_INSTALL_PREFIX ${PROJECT})		# folder 'prefix' for installed includes and libs


install(EXPORT ${PROJECT_EXPORT_NAME} 
	FILE
		${PROJECT_EXPORT_NAME}Targets.cmake
	NAMESPACE
		${PROJECT_NAMESPACE}::
	DESTINATION
		${CMAKE_INSTALL_ARCHIVEDIR}/cmake/${PROJECT_EXPORT_NAME}
	COMPONENT
		${DEVELOP_COMPONENT}
)


add_subdirectory(trie)
add_subdirectory(example)
