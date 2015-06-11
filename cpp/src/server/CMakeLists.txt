cmake_minimum_required(VERSION 2.8)

include(../environment.cmake required)

option(nb "non-blocking server mode" OFF)
set(nb ${nb} CACHE BOOL "" FORCE)

if (WIN32 AND ${nb} AND NOT DEFINED LIBEVENT_ROOT)
	message(FATAL_ERROR "LIBEVENT_ROOT variable must be defined")
endif ()
if (NOT DEFINED SRC_PATH_SERVER)
	message(FATAL_ERROR "SRC_PATH_SERVER variable must be defined")
endif ()

if (WIN32 AND ${nb} AND NOT EXISTS ${LIBEVENT_ROOT})
	message(FATAL_ERROR "${LIBEVENT_ROOT} directory does not exist")
endif ()
if (NOT EXISTS ${SRC_PATH_SERVER})
	message(FATAL_ERROR "${SRC_PATH_SERVER} directory does not exist")
endif ()

project(server)

if (UNIX)
	include_directories(/usr/include ${OPENSSL_INCLUDE})
	link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu ${HOME})
	if (${nb})
		add_executable(TutorialServerNB
			${SRC_PATH_SERVER}/servernb.cpp ${SRC_PATH_SERVER}/DummyServiceImpl.cpp
			${SRC_PATH_SERVER}/DummyServiceImpl.h) # link_directories should be before add_executable
		target_link_libraries(TutorialServerNB ssl crypto event rt pthread thrift thriftnb tutorialgencpp)
	else ()
		add_executable(TutorialServer
			${SRC_PATH_SERVER}/server.cpp ${SRC_PATH_SERVER}/DummyServiceImpl.cpp
			${SRC_PATH_SERVER}/DummyServiceImpl.h) # link_directories should be before add_executable
		target_link_libraries(TutorialServer ssl crypto pthread thrift tutorialgencpp)
	endif ()
elseif (WIN32)
	if (${nb})
		include_directories(${OPENSSL_INCLUDE} ${LIBEVENT_ROOT} ${LIBEVENT_ROOT}/include
							${LIBEVENT_ROOT}/WIN32-Code ${LIBEVENT_ROOT}/WIN32-Code/nmake ${SRC_PATH_GENCPP})
		link_directories(${THRIFT_ROOT}/lib/cpp/Debug ${BOOST_ROOT}/stage/lib
						 ${HOME} ${LIBEVENT_ROOT}/build/lib/Debug ${OPENSSL_ROOT}/lib/VC/static)
		add_executable(TutorialServerNB
			${SRC_PATH_SERVER}/servernb.cpp ${SRC_PATH_SERVER}/DummyServiceImpl.cpp
			${SRC_PATH_SERVER}/DummyServiceImpl.h) # link_directories should be before add_executable
		target_link_libraries(TutorialServerNB ${BOOST_LIB} libthrift libthriftnb
							  libtutorialgencpp event libeay32MTd ssleay32MTd)
	else ()
		include_directories(${OPENSSL_INCLUDE} ${SRC_PATH_GENCPP})
		link_directories(${THRIFT_ROOT}/lib/cpp/Debug ${BOOST_ROOT}/stage/lib
						 ${HOME} ${OPENSSL_ROOT}/lib/VC/static)
		add_executable(TutorialServer
			${SRC_PATH_SERVER}/server.cpp ${SRC_PATH_SERVER}/DummyServiceImpl.cpp
			${SRC_PATH_SERVER}/DummyServiceImpl.h) # link_directories should be before add_executable
		target_link_libraries(TutorialServer ${BOOST_LIB} libthrift 
							  libtutorialgencpp libeay32MTd ssleay32MTd)
	endif ()
else ()
	message("unsupported OS")
endif ()

