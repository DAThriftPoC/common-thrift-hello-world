cmake_minimum_required(VERSION 2.8)

include(environment.cmake required)

if (WIN32)
	if (NOT DEFINED THRIFT_ROOT OR
		NOT DEFINED BOOST_ROOT OR
		NOT DEFINED BOOST_LIB)
			message(FATAL_ERROR
			"Following variables must be defined: THRIFT_ROOT, BOOST_ROOT, BOOST_LIB")
	endif ()
endif ()
if (NOT DEFINED OPENSSL_INCLUDE OR
	NOT DEFINED SRC_PATH_GENCPP)
		message(FATAL_ERROR
			"Following variables must be defined: OPENSSL_INCLUDE, SRC_PATH_GENCPP")
endif ()

if (WIN32)
	if (NOT EXISTS ${THRIFT_ROOT})
		message(FATAL_ERROR "${THRIFT_ROOT} directory does not exist")
	endif ()
	if (NOT EXISTS ${BOOST_ROOT})
		message(FATAL_ERROR "${BOOST_ROOT} directory does not exist")
	endif ()
endif ()
if (NOT EXISTS ${OPENSSL_INCLUDE})
	message(FATAL_ERROR "${OPENSSL_INCLUDE} directory does not exist")
endif ()
if (NOT EXISTS ${SRC_PATH_GENCPP})
	message(FATAL_ERROR "${SRC_PATH_GENCPP} directory does not exist")
endif ()

project(cpp_hello_world)

option(nb "non-blocking server mode" OFF)
set(nb ${nb} CACHE BOOL "" FORCE)

link_directories(${THRIFT_ROOT}/lib/cpp/Debug ${BOOST_ROOT}/stage/lib)
AUX_SOURCE_DIRECTORY(${SRC_PATH_GENCPP} SOURCE_LIB) 

if (UNIX)
	include_directories(${OPENSSL_INCLUDE} ${SRC_PATH_GENCPP}  ${THRIFT_ROOT}/lib/cpp/src)
	add_library(tutorialgencpp SHARED ${SOURCE_LIB})
	if (${nb})
		target_link_libraries(tutorialgencpp event thrift thriftnb)
	else ()
		target_link_libraries(tutorialgencpp thrift)
	endif ()
elseif (WIN32)
	include_directories(${OPENSSL_INCLUDE} ${SRC_PATH_GENCPP}  ${THRIFT_ROOT}/lib/cpp/src ${BOOST_ROOT})
	add_library(libtutorialgencpp STATIC ${SOURCE_LIB})
	if (${nb})
		target_link_libraries(libtutorialgencpp ${BOOST_LIB} libthrift libthriftnb)
	else ()
		target_link_libraries(libtutorialgencpp ${BOOST_LIB} libthrift)
	endif ()
else ()
	message("unsupported OS")
endif ()

add_subdirectory(server)
add_subdirectory(client)

