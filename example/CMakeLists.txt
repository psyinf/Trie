set(APP_NAME example)
project(${APP_NAME} LANGUAGES CXX)

file(GLOB HEADER_FILES 	CONFIGURE_DEPENDS "*.h")
file(GLOB CPP_FILES 	CONFIGURE_DEPENDS "*.cpp")

add_executable(${APP_NAME} 
	${HEADER_FILES}
	${CPP_FILES}
)
			   
			   


target_link_libraries (${APP_NAME} 
	PRIVATE				
		${PROJECT_NAMESPACE}::trie
)




target_include_directories(${APP_NAME}
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" 
	FILES ${HEADER_FILES} ${CPP_FILES}
)

install(TARGETS ${APP_NAME}
        CONFIGURATIONS Debug Release RelWithDebInfo 
        RUNTIME DESTINATION bin)


set_target_properties(
    ${APP_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin"
)
