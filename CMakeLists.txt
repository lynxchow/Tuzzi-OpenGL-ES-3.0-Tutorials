cmake_minimum_required(VERSION 3.7.2)

project(Tutorials)

add_subdirectory(tuzzi)

get_filename_component(TUZZI_TUTORIALS_SRC_DIR
                       ${CMAKE_SOURCE_DIR}
                       ABSOLUTE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DENABLE_LOG")

file(GLOB TUZZI_TUTORIALS_SRCS
                       ${TUZZI_TUTORIALS_SRC_DIR}/Tutorial_01/*.h
                       ${TUZZI_TUTORIALS_SRC_DIR}/Tutorial_01/*.cpp
                       ${TUZZI_TUTORIALS_SRC_DIR}/Tutorial_02/*.h
                       ${TUZZI_TUTORIALS_SRC_DIR}/Tutorial_02/*.cpp
                       ${TUZZI_TUTORIALS_SRC_DIR}/Tutorial_03/*.h
                       ${TUZZI_TUTORIALS_SRC_DIR}/Tutorial_03/*.cpp
                       )
                  
source_group(TREE ${TUZZI_TUTORIALS_SRC_DIR} FILES ${TUZZI_TUTORIALS_SRCS})

if (${Target} MATCHES "macOS")

    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")

    set_source_files_properties(${TUZZI_TUTORIALS_SRC_DIR}/macOS/Assets.xcassets
                                ${TUZZI_TUTORIALS_SRC_DIR}/res
                                PROPERTIES
                                MACOSX_PACKAGE_LOCATION Resources
                                )

    add_executable(Tutorials
                   ${TUZZI_TUTORIALS_SRCS}
                   ${TUZZI_TUTORIALS_SRC_DIR}/macOS/main.m
                   ${TUZZI_TUTORIALS_SRC_DIR}/macOS/AppDelegate.mm
                   ${TUZZI_TUTORIALS_SRC_DIR}/macOS/ViewController.mm
                   ${TUZZI_TUTORIALS_SRC_DIR}/macOS/Assets.xcassets
                   ${TUZZI_TUTORIALS_SRC_DIR}/res
                   )

    target_include_directories(Tutorials PRIVATE
                               ${TUZZI_TUTORIALS_SRC_DIR}
                               ${TUZZI_TUTORIALS_SRC_DIR}/tuzzi/src
                               )

    target_link_libraries(Tutorials
                          Tuzzi TuzziDep
                          "-framework OpenGL"
                          "-framework AppKit"
                          z.1.2.8
                          )

    set_target_properties(Tutorials PROPERTIES
                          MACOSX_BUNDLE TRUE
                          MACOSX_BUNDLE_INFO_PLIST ${TUZZI_TUTORIALS_SRC_DIR}/macOS/Info.plist
                          XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon
                          )
elseif (${Target} MATCHES "iOS")
    set(XCODE_IOS_PLATFORM iphoneos)
    execute_process(COMMAND xcodebuild -version -sdk ${XCODE_IOS_PLATFORM} Path
        OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    message(STATUS "found ios sdk: ${CMAKE_OSX_SYSROOT}")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.0")
    set(CMAKE_OSX_ARCHITECTURES arm64)

    set_source_files_properties(${TUZZI_TUTORIALS_SRC_DIR}/iOS/Assets.xcassets
                                ${TUZZI_TUTORIALS_SRC_DIR}/iOS/Base.lproj/LaunchScreen.storyboard
                                ${TUZZI_TUTORIALS_SRC_DIR}/res
                                PROPERTIES
                                MACOSX_PACKAGE_LOCATION Resources
                                )

    add_executable(Tutorials
                   ${TUZZI_TUTORIALS_SRCS}
                   ${TUZZI_TUTORIALS_SRC_DIR}/iOS/main.m
                   ${TUZZI_TUTORIALS_SRC_DIR}/iOS/AppDelegate.m
                   ${TUZZI_TUTORIALS_SRC_DIR}/iOS/ViewController.mm
                   ${TUZZI_TUTORIALS_SRC_DIR}/iOS/Assets.xcassets
                   ${TUZZI_TUTORIALS_SRC_DIR}/iOS/Base.lproj/LaunchScreen.storyboard
                   ${TUZZI_TUTORIALS_SRC_DIR}/res
                   )

    target_include_directories(Tutorials PRIVATE
                               ${TUZZI_TUTORIALS_SRC_DIR}
                               ${TUZZI_TUTORIALS_SRC_DIR}/tuzzi/src
                               )

    target_link_libraries(Tutorials
                          Tuzzi TuzziDep
                          "-framework UIKit"
                          "-framework OpenGLES"
                          "-framework QuartzCore"
                          "-framework IOKit"
                          z.1.2.8
                          )

    set_target_properties(Tutorials PROPERTIES
                          MACOSX_BUNDLE TRUE
                          MACOSX_BUNDLE_INFO_PLIST ${TUZZI_TUTORIALS_SRC_DIR}/iOS/Info.plist
                          XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon
                          )
endif ()