cmake_minimum_required(VERSION 3.7.2)

project(Tuzzi)

get_filename_component(TUZZI_LIB_SRC_DIR
                       ${CMAKE_CURRENT_SOURCE_DIR}/src
                       ABSOLUTE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DENABLE_LOG")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DENABLE_LOG")

file(GLOB TUZZI_DEP_SRCS
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jaricom.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcapimin.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcapistd.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcarith.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jccoefct.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jccolor.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcdctmgr.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jchuff.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcinit.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcmainct.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcmarker.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcmaster.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcomapi.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcparam.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcprepct.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jcsample.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jctrans.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdapimin.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdapistd.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdarith.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdatadst.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdatasrc.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdcoefct.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdcolor.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jddctmgr.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdhuff.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdinput.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdmainct.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdmarker.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdmaster.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdmerge.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdpostct.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdsample.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jdtrans.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jerror.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jfdctflt.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jfdctfst.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jfdctint.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jidctflt.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jidctfst.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jidctint.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jmemmgr.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jmemnobs.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jquant1.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jquant2.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/jpeg/jutils.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/png.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngerror.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngget.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngmem.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngpread.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngread.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngrio.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngrtran.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngrutil.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngset.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngtrans.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngwio.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngwrite.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngwtran.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/png/pngwutil.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/zlib/ioapi.c
     ${TUZZI_LIB_SRC_DIR}/3rdparty/zlib/unzip.c
     )

source_group(TREE ${TUZZI_LIB_SRC_DIR}/3rdparty FILES ${TUZZI_DEP_SRCS})

add_library(TuzziDep STATIC ${TUZZI_DEP_SRCS})

target_include_directories(TuzziDep PRIVATE
                           ${TUZZI_LIB_SRC_DIR}/
                           ${TUZZI_LIB_SRC_DIR}/3rdparty/
                           )

file(GLOB TUZZI_LIB_SRCS
     ${TUZZI_LIB_SRC_DIR}/*.h
     ${TUZZI_LIB_SRC_DIR}/*.cpp
     ${TUZZI_LIB_SRC_DIR}/string/*.h
     ${TUZZI_LIB_SRC_DIR}/string/*.cpp
     ${TUZZI_LIB_SRC_DIR}/gl/*.h
     ${TUZZI_LIB_SRC_DIR}/gl/*.cpp
     ${TUZZI_LIB_SRC_DIR}/io/*.h
     ${TUZZI_LIB_SRC_DIR}/io/*.cpp
     ${TUZZI_LIB_SRC_DIR}/memory/*.h
     ${TUZZI_LIB_SRC_DIR}/memory/*.cpp
     ${TUZZI_LIB_SRC_DIR}/image/*.h
     ${TUZZI_LIB_SRC_DIR}/image/*.cpp
     ${TUZZI_LIB_SRC_DIR}/math/*.h
     ${TUZZI_LIB_SRC_DIR}/math/*.cpp
     ${TUZZI_LIB_SRC_DIR}/container/*.h
     ${TUZZI_LIB_SRC_DIR}/container/*.cpp
     ${TUZZI_LIB_SRC_DIR}/graphics/*.h
     ${TUZZI_LIB_SRC_DIR}/graphics/*.cpp
     )

source_group(TREE ${TUZZI_LIB_SRC_DIR}/.. FILES ${TUZZI_LIB_SRCS})

add_library(Tuzzi STATIC ${TUZZI_LIB_SRCS})

target_include_directories(Tuzzi PRIVATE
                           ${TUZZI_LIB_SRC_DIR}
                           ${TUZZI_LIB_SRC_DIR}/3rdparty)

target_sources(Tuzzi PRIVATE ${TUZZI_LIB_SRCS})

if (${Target} MATCHES "macOS")
     set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")
     file(GLOB TUZZI_LIB_MAC_SRCS
          ${TUZZI_LIB_SRC_DIR}/mac/*.h
          ${TUZZI_LIB_SRC_DIR}/mac/*.cpp
          ${TUZZI_LIB_SRC_DIR}/mac/*.m
          ${TUZZI_LIB_SRC_DIR}/mac/*.mm
     )

     source_group(TREE ${TUZZI_LIB_SRC_DIR}/.. FILES ${TUZZI_LIB_MAC_SRCS})

     target_sources(Tuzzi PRIVATE ${TUZZI_LIB_MAC_SRCS})

elseif (${Target} MATCHES "iOS")
     set(XCODE_IOS_PLATFORM iphoneos)
     execute_process(COMMAND xcodebuild -version -sdk ${XCODE_IOS_PLATFORM} Path
          OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
          ERROR_QUIET
          OUTPUT_STRIP_TRAILING_WHITESPACE)
     message(STATUS "found ios sdk: ${CMAKE_OSX_SYSROOT}")
     set(CMAKE_OSX_DEPLOYMENT_TARGET "10.0")
     set(CMAKE_OSX_ARCHITECTURES arm64)

     file(GLOB TUZZI_LIB_IOS_SRCS
               ${TUZZI_LIB_SRC_DIR}/ios/*.h
               ${TUZZI_LIB_SRC_DIR}/ios/*.cpp
               ${TUZZI_LIB_SRC_DIR}/ios/*.m
               ${TUZZI_LIB_SRC_DIR}/ios/*.mm
          )

     source_group(TREE ${TUZZI_LIB_SRC_DIR}/.. FILES ${TUZZI_LIB_IOS_SRCS})

     target_sources(Tuzzi PRIVATE ${TUZZI_LIB_IOS_SRCS})

elseif (${Target} MATCHES "Android")

     file(GLOB TUZZI_LIB_ANDROID_SRCS
          ${TUZZI_LIB_SRC_DIR}/android/*.h
          ${TUZZI_LIB_SRC_DIR}/android/*.cpp
     )

     source_group(TREE ${TUZZI_LIB_SRC_DIR}/.. FILES ${TUZZI_LIB_ANDROID_SRCS})
     target_sources(Tuzzi PRIVATE ${TUZZI_LIB_ANDROID_SRCS})

elseif (${Target} MATCHES "Windows")

	file(GLOB TUZZI_TUTORIAL_SRCS
          ${CMAKE_CURRENT_SOURCE_DIR}/../Windows/main.cpp
          )

endif ()

