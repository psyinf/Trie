set(LIB_NAME trie)
#FILES
file(GLOB HEADER_FILES 	CONFIGURE_DEPENDS "*.h")
file(GLOB CPP_FILES 	CONFIGURE_DEPENDS "*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" 
	FILES ${HEADER_FILES}  ${CPP_FILES}
)


add_library(${LIB_NAME} STATIC 
	${HEADER_FILES} 
	${CPP_FILES} 
)
add_library(${PROJECT_NAMESPACE}::${LIB_NAME} ALIAS ${LIB_NAME})

target_link_libraries(${LIB_NAME}

)
target_include_directories(${LIB_NAME}
	INTERFACE
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_INSTALL_PREFIX}/${LIB_NAME}>
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

#INSTALL


install(DIRECTORY ./
	DESTINATION
		${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_INSTALL_PREFIX}/${LIB_NAME}
	COMPONENT
		${DEVELOP_COMPONENT}
	FILES_MATCHING
		PATTERN "*.h"
)


install(TARGETS ${LIB_NAME} EXPORT ${PROJECT_EXPORT_NAME}
	ARCHIVE
		DESTINATION ${CMAKE_INSTALL_ARCHIVEDIR}/${PROJECT_INSTALL_PREFIX}
		COMPONENT ${DEVELOP_COMPONENT}
	LIBRARY
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_INSTALL_PREFIX}
		COMPONENT ${RUNTIME_COMPONENT}
	RUNTIME
		DESTINATION ${CMAKE_INSTALL_BINDIR}
		COMPONENT ${RUNTIME_COMPONENT}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
#install_pdbs(TARGET ${LIB_NAME} DESTINATION ${CMAKE_INSTALL_ARCHIVEDIR}/${PROJECT_INSTALL_PREFIX})