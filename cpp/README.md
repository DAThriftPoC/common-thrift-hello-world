# cpp-thrift-hello-world

# License

cpp-thrift-hello-world is built by [DataArt](http://dataart.com) and distributed
 under [MIT License](http://en.wikipedia.org/wiki/MIT_License).

# Building for Windows

1. Download Boost from <http://sourceforge.net/projects/boost/files/boost/1.58.0>
 and extract the files from the archive to the cpp\\3rdParty subdirectory of the
 base directory.

2. Launch the Visual Studio Command Prompt. Change your current directory to the
 Boost root directory and invoke bootstrap.bat. To build Boost.Thread library
 invoke b2.exe as follows:  
  ```
> b2.exe --with-thread --with-date_time --build-type=complete --link=static --runtime-link=static --runtime-debugging=on`
  ```
Boost library binaries will be placed in the stage\\lib subdirectory of your
 build directory.

3. Download "Win32 OpenSSL v1.0.2a" file from
 <http://slproweb.com/products/Win32OpenSSL.html> and install OpenSSL.

4. Download cmake from <http://www.cmake.org/download/> and install it.

5. Open the environment.cmake file in a text editor and edit values of the listed
 environment variables.

  5.1. **OPTIONAL.** *If you want to build the libthriftnb library and the Threaded Server
 application you need to build the libevent library previously.  
Download libevent from <https://github.com/libevent/libevent.git>.  
Launch the Visual Studio Command Prompt. Change your current directory to the
 libevent root directory and type:*

    ```
> mkdir build && cd build
> cmake -G "Visual Studio 10" ..
> msbuild libevent.sln
    ```

6. You need to provide the information about the 3rd party components for MSBuild.
 Open the environment.bat file in a text editor and edit values of the listed
 environment variables.

7. Download Thrift from <https://github.com/apache/thrift/tree/0.9.2>.  
Launch the Visual Studio Command Prompt and change your current directory to the
 cpp subdirectory of the base directory. To build the libthrift library run:  
  ```
> build-libthrift.bat
  ```
The libthrift library will be created in the lib\\cpp\\Debug subdirectory of the
 Thrift root directory.

  7.1. **OPTIONAL.** *If you want to build the Threaded Server application you
 need to link it with the libthriftnb library. To build the libthriftnb library run:*

  ```
> build-libthriftnb.bat
  ```

   *The libthriftnb library will be created in the lib\\cpp\\Debug subdirectory of the
 Thrift root directory.*

8. Change your current directory to the thrift subdirectory of the base directory
 and run:  
  ```
> gencpp.bat  
  ```
The Thrift compiler will create the cpp\\src\\gen-cpp subdirectory of the base
 directory and place source code files there.

9. Change your current directory to the cpp subdirectory of the base directory
 and type:  
  ```
> cmake .
  ```

  9.1. **OPTIONAL.** *If you want to build the Threaded Server application then
	type:*

  ```
> cmake -Dnb=ON .
  ```

  You will obtain the files needed to build the server and client projects via
 Visual Studio.  
Open the Visual Studio solution file and build the solution.

# Building for Linux

1. Install Boost:  
  ```
$ sudo apt-get install libboost-dev libboost-test-dev
  ```

2. Install libtool:  
  ```
$ sudo apt-get install libtool
  ```

3. Install autoconf:  
  ```
$ sudo apt-get install autoconf
  ```

4. Install automake:  
  ```
$ sudo apt-get install automake
  ```

5. Install yacc and lex:  
  ```
$ sudo apt-get install byacc flex
  ```

  5.1. **OPTIONAL.** *If you want to build the libthriftnb library and the Threaded Server
 application you need to install the libevent library previously. To install libevent do:*  

  ```
$ sudo apt-get install libevent-dev
  ```

6. Install cmake:  
  ```
$ sudo apt-get install cmake
  ```

7. Install libssl-dev:  
  ```
$ sudo apt-get install libssl-dev
  ```

8. Download Thrift from <https://github.com/apache/thrift/tree/0.9.2>.  
Change your current directory to the Thrift root directory.  
Run bootstrap.sh:  
  ```
$ ./bootstrap.sh
  ```
Configure Thrift:  
  ```
$ ./configure --with-cpp --with-boost --without-qt4 --without-csharp --without-java --without-erlang --without-nodejs --without-lua --without-python --without-perl --without-php --without-php_extension --without-ruby --without-haskell --without-go --without-d
  ```
Build Thrift:  
  ```
$ make
  ```
Install Thrift:  
  ```
$ sudo make install
  ```
Add shared libraries directories to the dynamic linker cache:  
  ```
$ sudo ldconfig
  ```

9. Change your current directory to the thrift subdirectory of the base directory
 and run:  
  ```
$ sh gencpp.sh
  ```
The Thrift compiler will create the cpp/src/gen-cpp subdirectory of the base
 directory and place source code files there.

10. Change your current directory to the cpp/src subdirectory of the base directory
 and type:  
  ```
$ cmake .
  ```

  10.1. **OPTIONAL.** *If you want to build the Threaded Server application then
	type:*

  ```
> cmake -Dnb=ON .
  ```

  You will obtain the Makefile. Run make to build the server and client projects:  
  ```
$ make
  ```

