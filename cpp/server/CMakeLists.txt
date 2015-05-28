cmake_minimum_required(VERSION 2.8)

include(../environment.cmake required)

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
	link_directories(${HOME}/3rdParty/Thrift/lib/cpp/Debug ${HOME}/3rdParty/boost_1_58_0/stage/lib
					 ${HOME} ${LIBEVENT_ROOT}/build/lib/Debug ${OPENSSL_ROOT}/lib/VC/static)
	add_executable(TutorialServer ${SOURCE_SERVER}) # link_directories should be before add_executable
	target_link_libraries(TutorialServer libboost_thread-vc100-mt-gd-1_58 libthrift
						  libthriftnb libtutorialgencpp event libeay32MTd ssleay32MTd)
endif ()
