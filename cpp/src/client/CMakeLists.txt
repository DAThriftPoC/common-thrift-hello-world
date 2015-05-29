cmake_minimum_required(VERSION 2.8)

include(../environment.cmake required)

project(client)

AUX_SOURCE_DIRECTORY(${SRC_PATH_CLIENT} SOURCE_CLIENT)

if (UNIX)
	link_directories(/usr/local/lib ${HOME})
	add_executable(TutorialClient ${SOURCE_CLIENT}) # link_directories should be before add_executable
	target_link_libraries(TutorialClient ssl crypto rt pthread thrift tutorialgencpp)
elseif (WIN32)
	link_directories(${HOME}/../3rdParty/Thrift/lib/cpp/Debug ${HOME}/../3rdParty/boost_1_58_0/stage/lib ${HOME})
	add_executable(TutorialClient ${SOURCE_CLIENT}) # link_directories should be before add_executable
	target_link_libraries(TutorialClient libboost_thread-vc100-mt-gd-1_58 libthrift libtutorialgencpp)
endif ()
