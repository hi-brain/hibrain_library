# ModuleName CMake config file
#
# This file sets the following variables:
# ModuleName_FOUND - Always TRUE.
# ModuleName_INCLUDE_DIRS - Directories containing the ModuleName include files.
# ModuleName_IDL_DIRS - Directories containing the ModuleName IDL files.
# ModuleName_LIBRARIES - Libraries needed to use ModuleName.
# ModuleName_DEFINITIONS - Compiler flags for ModuleName.
# ModuleName_VERSION - The version of ModuleName found.
# ModuleName_VERSION_MAJOR - The major version of ModuleName found.
# ModuleName_VERSION_MINOR - The minor version of ModuleName found.
# ModuleName_VERSION_REVISION - The revision version of ModuleName found.
# ModuleName_VERSION_CANDIDATE - The candidate version of ModuleName found.

message(STATUS "Found ModuleName-1.0.0")
set(ModuleName_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(ModuleName_INCLUDE_DIRS
#    "/usr/local/include/usbcamera-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(ModuleName_IDL_DIRS
#    "/usr/local/include/usbcamera-1/idl")
set(ModuleName_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(ModuleName_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(ModuleName_LIBRARIES
        "/usr/local/components/lib/libusbcamera.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(ModuleName_LIBRARIES
        "/usr/local/components/lib/libusbcamera.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(ModuleName_DEFINITIONS ${<dependency>_DEFINITIONS})

set(ModuleName_VERSION 1.0.0)
set(ModuleName_VERSION_MAJOR 1)
set(ModuleName_VERSION_MINOR 0)
set(ModuleName_VERSION_REVISION 0)
set(ModuleName_VERSION_CANDIDATE )
