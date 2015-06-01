cmake_minimum_required(VERSION 2.8)

include(../environment.cmake required)

if (NOT DEFINED SRC_PATH_CLIENT)
		message(FATAL_ERROR
		"SRC_PATH_CLIENT variable must be defined")
endif ()

if (NOT EXISTS ${SRC_PATH_CLIENT})
	message(FATAL_ERROR "${SRC_PATH_CLIENT} directory does not exist")
endif ()

project(client)

AUX_SOURCE_DIRECTORY(${SRC_PATH_CLIENT} SOURCE_CLIENT)

if (UNIX)
	link_directories(/usr/local/lib ${HOME})
	add_executable(TutorialClient ${SOURCE_CLIENT}) # link_directories should be before add_executable
	target_link_libraries(TutorialClient ssl crypto rt pthread thrift tutorialgencpp)
elseif (WIN32)
	link_directories(${THRIFT_ROOT}/lib/cpp/Debug ${BOOST_ROOT}/stage/lib ${HOME})
	add_executable(TutorialClient ${SOURCE_CLIENT}) # link_directories should be before add_executable
	target_link_libraries(TutorialClient libboost_thread-vc100-mt-gd-1_58 libthrift libtutorialgencpp)
else ()
	message("unsupported OS")
endif ()

