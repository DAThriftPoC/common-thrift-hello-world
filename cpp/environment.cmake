set(HOME ${CMAKE_HOME_DIRECTORY})

set(SRC_PATH_SERVER ${HOME}/src/server)
set(SRC_PATH_CLIENT ${HOME}/src/client)
set(SRC_PATH_GENCPP ${HOME}/src/gen-cpp)

if (UNIX)
	set(OPENSSL_INCLUDE /usr/include/openssl)
#	RT_INCLUDE
#	PTHREAD_INCLUDE 
elseif (WIN32)
endif()


