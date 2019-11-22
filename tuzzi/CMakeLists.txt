cmake_minimum_required(VERSION 2.8)

project(Tuzzi)

get_filename_component(TUZZI_LIB_DIR
                       ${CMAKE_SOURCE_DIR}/src
                       ABSOLUTE)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DENABLE_LOG")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DENABLE_LOG")

file(GLOB TUZZI_LIB_SRCS
     ${TUZZI_LIB_DIR}/*.h
     ${TUZZI_LIB_DIR}/*.cpp
     ${TUZZI_LIB_DIR}/string/*.h
     ${TUZZI_LIB_DIR}/string/*.h
     ${TUZZI_LIB_DIR}/gl/*.h
     ${TUZZI_LIB_DIR}/gl/*.cpp
     )

source_group(TREE ${TUZZI_LIB_DIR}/.. FILES ${TUZZI_LIB_SRCS})
add_library(Tuzzi ${TUZZI_LIB_SRCS})

if (${Target} MATCHES "macOS")
     set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")
     file(GLOB TUZZI_LIB_MAC_SRCS
          ${TUZZI_LIB_DIR}/mac/*.h
          ${TUZZI_LIB_DIR}/mac/*.cpp
          ${TUZZI_LIB_DIR}/mac/*.m
          ${TUZZI_LIB_DIR}/mac/*.mm
     )

     source_group(TREE ${TUZZI_LIB_DIR}/.. FILES ${TUZZI_LIB_MAC_SRCS})
     target_sources(Tuzzi PRIVATE ${TUZZI_LIB_MAC_SRCS})

elseif (${Target} MATCHES "iOS")
     set(XCODE_IOS_PLATFORM iphoneos)
     execute_process(COMMAND xcodebuild -version -sdk ${XCODE_IOS_PLATFORM} Path
          OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
          ERROR_QUIET
          OUTPUT_STRIP_TRAILING_WHITESPACE)
     message(STATUS "found ios sdk: ${CMAKE_OSX_SYSROOT}")
     set(CMAKE_OSX_DEPLOYMENT_TARGET "8.0")
     set(CMAKE_OSX_ARCHITECTURES arm64)

     file(GLOB TUZZI_LIB_IOS_SRCS
               ${TUZZI_LIB_DIR}/ios/*.h
               ${TUZZI_LIB_DIR}/ios/*.cpp
               ${TUZZI_LIB_DIR}/ios/*.m
               ${TUZZI_LIB_DIR}/ios/*.mm
          )

     source_group(TREE ${TUZZI_LIB_DIR}/.. FILES ${TUZZI_LIB_IOS_SRCS})
     target_sources(Tuzzi PRIVATE ${TUZZI_LIB_IOS_SRCS})

elseif (${Target} MATCHES "Android")

     file(GLOB TUZZI_LIB_ANDROID_SRCS
          ${TUZZI_LIB_DIR}/android/*.h
          ${TUZZI_LIB_DIR}/android/*.cpp
     )

     source_group(TREE ${TUZZI_LIB_DIR}/.. FILES ${TUZZI_LIB_ANDROID_SRCS})
     target_sources(Tuzzi PRIVATE ${TUZZI_LIB_ANDROID_SRCS})
     add_library(TuzziApp SHARED
          ${CMAKE_SOURCE_DIR}/../Tutorial_01/DemoApplication.h
          ${CMAKE_SOURCE_DIR}/../Tutorial_01/DemoApplication.cpp
          ${CMAKE_SOURCE_DIR}/../Android/app/src/main/cpp/jni.cpp
          )

     file(GLOB TUZZI_TUTORIAL_SRCS
          ${CMAKE_SOURCE_DIR}/../Tutorial_01/DemoApplication.cpp
          ${CMAKE_SOURCE_DIR}/../Android/app/src/main/cpp/jni.cpp
          )

     target_include_directories(TuzziApp PRIVATE ${CMAKE_SOURCE_DIR}/..)
     source_group(TREE ${CMAKE_SOURCE_DIR}/.. FILES ${TUZZI_TUTORIAL_SRCS})

     target_link_libraries(TuzziApp
          Tuzzi
          android log z OpenSLES EGL GLESv3
          )

elseif (${Target} MATCHES "Windows")

	file(GLOB TUZZI_TUTORIAL_SRCS
          ${CMAKE_SOURCE_DIR}/../Tutorial_01/DemoApplication.cpp
          ${CMAKE_SOURCE_DIR}/../Windows/main.cpp
          )
	add_executable(TuzziApp
          ${TUZZI_TUTORIAL_SRCS}
          )

     set_property(TARGET TuzziApp PROPERTY LINK_FLAGS "/SUBSYSTEM:WINDOWS")

     target_include_directories(TuzziApp PRIVATE ${CMAKE_SOURCE_DIR}/..)

     target_link_libraries(TuzziApp
                           Tuzzi
                           )
endif ()

