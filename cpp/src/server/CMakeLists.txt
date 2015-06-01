cmake_minimum_required(VERSION 2.8)

include(../environment.cmake required)

if (NOT DEFINED SRC_PATH_SERVER OR
	NOT DEFINED LIBEVENT_ROOT)
		message(FATAL_ERROR
		"Following variables must be defined: SRC_PATH_SERVER, LIBEVENT_ROOT")
endif ()

if (NOT EXISTS ${SRC_PATH_SERVER})
	message(FATAL_ERROR "${SRC_PATH_SERVER} directory does not exist")
endif ()
if (NOT EXISTS ${LIBEVENT_ROOT})
	message(FATAL_ERROR "${LIBEVENT_ROOT} directory does not exist")
endif ()

project(server)

AUX_SOURCE_DIRECTORY(${SRC_PATH_SERVER} SOURCE_SERVER)

if (UNIX)
	include_directories(/usr/include ${OPENSSL_INCLUDE})
	link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu ${HOME})
	add_executable(TutorialServer ${SOURCE_SERVER}) # link_directories should be before add_executable
	target_link_libraries(TutorialServer ssl crypto event rt pthread thrift thriftnb tutorialgencpp)
elseif (WIN32)
	include_directories(${OPENSSL_INCLUDE} ${LIBEVENT_ROOT} ${LIBEVENT_ROOT}/include
						${LIBEVENT_ROOT}/WIN32-Code ${LIBEVENT_ROOT}/WIN32-Code/nmake ${SRC_PATH_GENCPP})
	link_directories(${THRIFT_ROOT}/lib/cpp/Debug ${BOOST_ROOT}/stage/lib
					 ${HOME} ${LIBEVENT_ROOT}/build/lib/Debug ${OPENSSL_ROOT}/lib/VC/static)
	add_executable(TutorialServer ${SOURCE_SERVER}) # link_directories should be before add_executable
	target_link_libraries(TutorialServer libboost_thread-vc100-mt-gd-1_58 libthrift
						  libthriftnb libtutorialgencpp event libeay32MTd ssleay32MTd)
else ()
	message("unsupported OS")
endif ()

