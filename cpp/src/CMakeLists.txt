cmake_minimum_required(VERSION 2.8)

include(environment.cmake required)

if (NOT DEFINED THRIFT_ROOT OR
	NOT DEFINED BOOST_ROOT OR
	NOT DEFINED OPENSSL_INCLUDE OR
	NOT DEFINED SRC_PATH_GENCPP)
		message(FATAL_ERROR
		"Following variables must be defined: THRIFT_ROOT, BOOST_ROOT, OPENSSL_INCLUDE, SRC_PATH_GENCPP")
endif ()

if (NOT EXISTS ${THRIFT_ROOT})
	message(FATAL_ERROR "${THRIFT_ROOT} directory does not exist")
endif ()
if (NOT EXISTS ${BOOST_ROOT})
	message(FATAL_ERROR "${BOOST_ROOT} directory does not exist")
endif ()
if (NOT EXISTS ${OPENSSL_INCLUDE})
	message(FATAL_ERROR "${OPENSSL_INCLUDE} directory does not exist")
endif ()
if (NOT EXISTS ${SRC_PATH_GENCPP})
	message(FATAL_ERROR "${SRC_PATH_GENCPP} directory does not exist")
endif ()

project(cpp_hello_world)

include_directories(${OPENSSL_INCLUDE} ${SRC_PATH_GENCPP})
link_directories(${THRIFT_ROOT}/lib/cpp/Debug ${BOOST_ROOT}/stage/lib)
AUX_SOURCE_DIRECTORY(${SRC_PATH_GENCPP} SOURCE_LIB)

if (UNIX)
	add_library(tutorialgencpp SHARED ${SOURCE_LIB})
	target_link_libraries(tutorialgencpp event boost_thread-mt-d thrift thriftnb)
elseif (WIN32)
	add_library(libtutorialgencpp STATIC ${SOURCE_LIB})
	target_link_libraries(libtutorialgencpp libboost_thread-vc100-mt-gd-1_58 libthrift libthriftnb)
else ()
	message("unsupported OS")
endif ()

add_subdirectory(server)
add_subdirectory(client)

