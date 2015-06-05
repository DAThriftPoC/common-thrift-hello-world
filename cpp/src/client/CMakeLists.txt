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
	include_directories(/usr/include ${OPENSSL_INCLUDE} ${SRC_PATH_GENCPP})
	link_directories(/usr/local/lib /usr/lib/x86_64-linux-gnu ${HOME})
	add_executable(TutorialClient ${SOURCE_CLIENT}) # link_directories should be before add_executable
	target_link_libraries(TutorialClient ssl crypto pthread thrift tutorialgencpp)
elseif (WIN32)
	include_directories(${OPENSSL_INCLUDE} ${SRC_PATH_GENCPP})
	link_directories(${THRIFT_ROOT}/lib/cpp/Debug ${BOOST_ROOT}/stage/lib ${HOME}
									 ${OPENSSL_ROOT}/lib/VC/static)
	add_executable(TutorialClient ${SOURCE_CLIENT}) # link_directories should be before add_executable
	target_link_libraries(TutorialClient ${BOOST_LIB} libthrift libtutorialgencpp
												libeay32MTd ssleay32MTd)
else ()
	message("unsupported OS")
endif ()

