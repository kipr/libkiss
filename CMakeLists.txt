#################################
#   libkiss CMake Build File   #
#################################

PROJECT(libkiss)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

SET(INCLUDE ${libkiss_SOURCE_DIR}/include)
SET(SRC ${libkiss_SOURCE_DIR}/src)

INCLUDE_DIRECTORIES(${INCLUDE})

FILE(GLOB INCLUDES ${INCLUDE}/*.h ${SRC}/*.h)
SET(SOURCES
	${SRC}/graphics_interface.c
	${SRC}/kiss.c
	${SRC}/kiss_graphics.c
	${SRC}/kiss_graphics_draw.c
	${SRC}/kiss_input.c
	${SRC}/kiss_serial_buffer.c
	${SRC}/kiss_util.c
	${SRC}/serial_interface.c
	${SRC}/thread_interface.c
	${SRC}/timing_interface.c
)

IF(UNIX)
	SET(SOURCES ${SOURCES}
		${SRC}/kiss_serial_unix.c
	)
ELSEIF(WIN32)
	SET(SOURCES ${SOURCES}
		${SRC}/kiss_serial_windows.c
	)
ENDIF(UNIX)

SET(CMAKE_CXX_FLAGS "-Wall")

IF(APPLE)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch x86_64 -g")
ELSEIF(WIN32)
	SET(CMAKE_CXX_FLAGS "-Wl,--enable-auto-import")
ELSEIF(UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ENDIF()

SET(LIBRARY_OUTPUT_PATH ${libkiss_SOURCE_DIR}/lib)

ADD_LIBRARY(kiss STATIC ${SOURCES})
TARGET_LINK_LIBRARIES(kiss pthread glfw)

IF(APPLE)
	FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
	target_link_libraries(kiss ${OPENGL_LIBRARY})
ELSE(APPLE)
	target_link_libraries(kiss opengl)
ENDIF(APPLE)


install(FILES ${INCLUDES} DESTINATION include/kiss)
INSTALL(TARGETS kiss ARCHIVE DESTINATION lib)

add_subdirectory(test)