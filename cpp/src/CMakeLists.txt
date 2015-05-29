cmake_minimum_required(VERSION 2.8)

include(environment.cmake required)

project(cpp_hello_world)

include_directories(${OPENSSL_INCLUDE} ${PTHREAD_INCLUDE} ${SRC_PATH_GENCPP})
link_directories(${HOME}/../3rdParty/Thrift/lib/cpp/Debug ${HOME}/../3rdParty/boost_1_58_0/stage/lib)
AUX_SOURCE_DIRECTORY(${SRC_PATH_GENCPP} SOURCE_LIB)

if (UNIX)
	add_library(tutorialgencpp SHARED ${SOURCE_LIB})
	target_link_libraries(tutorialgencpp event boost_thread-mt-d thrift thriftnb)
elseif (WIN32)
	add_library(libtutorialgencpp STATIC ${SOURCE_LIB})
	target_link_libraries(libtutorialgencpp libboost_thread-vc100-mt-gd-1_58 libthrift libthriftnb)
endif ()

add_subdirectory(server)
add_subdirectory(client)

