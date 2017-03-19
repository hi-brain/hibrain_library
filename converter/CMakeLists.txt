PROJECT(libhi_convert)                  #プロジェクト名
SET(CMAKE_C_FLAGS_RELEASE "-Wall -O2")  # リリースビルド用オプション
SET(CMAKE_C_FLAGS_DEBUG "-g")           # デバッグビルド用オプション
SET(CMAKE_BUILD_TYPE Release)           # ビルドのタイプはリリース
option(USE_MATLAB_RUNTIME "USE MATLAB LIBRARIES" ON)

IF(USE_MATLAB_RUNTIME)  #MATLAB
  message(STATUS "$ENV{MATLAB_RUNTIME_PATH}")
  set(MATLAB_INCLUDE_DIRS "$ENV{MATLAB_RUNTIME_PATH}/extern/include;") #"${PROJECT_SOURCE_DIR}/MATLAB_DIR;")
  set(MATLAB_LIBRARY_DIRS "$ENV{MATLAB_RUNTIME_PATH}/runtime/glnxa64;" "$ENV{MATLAB_RUNTIME_PATH}/bin/glnxa64;")
  set(matlib libmwmclmcrrt.so)
  if (DEFINED MATLAB_INCLUDE_DIRS)
    string(REGEX REPLACE "-I" ";"
      MATLAB_INCLUDE_DIRS "${MATLAB_INCLUDE_DIRS}")
    string(REGEX REPLACE " ;" ";"
      MATLAB_INCLUDE_DIRS "${MATLAB_INCLUDE_DIRS}")
  endif (DEFINED MATLAB_INCLUDE_DIRS)
  if (DEFINED MATLAB_LIBRARY_DIRS)
    string(REGEX REPLACE "-L" ";"
      MATLAB_LIBRARY_DIRS "${MATLAB_LIBRARY_DIRS}")
    string(REGEX REPLACE " ;" ";"
      MATLAB_LIBRARY_DIRS "${MATLAB_LIBRARY_DIRS}")
  endif (DEFINED MATLAB_LIBRARY_DIRS)
  if (DEFINED matlib)
    string(REGEX REPLACE "-l" ";"
      matlib "${matlib}")
    string(REGEX REPLACE " ;" ";"
      matlib "${matlib}")
  endif (DEFINED matlib)
  include_directories(${MATLAB_INCLUDE_DIRS})
  link_directories(${MATLAB_LIBRARY_DIRS})
ENDIF()

set(comp_srcs src/hi_convert.cpp)
set(comp_hdrs include/hi_convert.h)
# バージョン番号
SET(serial "1.0.0")
# 共有ライブラリのバージョン番号
SET(soserial "1")
# ライブラリ名
SET(LIB_NAME hi_convert)
#MESSAGE(STATUS ${headers})
find_package(OpenRTM)
if(${OpenRTM_FOUND})
  MESSAGE(STATUS "OpenRTM configuration Found")
else(${OpenRTM_FOUND})
  message(STATUS "Use cmake/Modules/FindOpenRTM.cmake in the project")
  list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
  find_package(OpenRTM REQUIRED)
endif(${OpenRTM_FOUND})

find_package(OpenCV REQUIRED)
if (DEFINED OPENRTM_INCLUDE_DIRS)
  string(REGEX REPLACE "-I" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
endif (DEFINED OPENRTM_INCLUDE_DIRS)

if (DEFINED OPENRTM_LIBRARY_DIRS)
  string(REGEX REPLACE "-L" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
endif (DEFINED OPENRTM_LIBRARY_DIRS)

if (DEFINED OPENRTM_LIBRARIES)
  string(REGEX REPLACE "-l" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
endif (DEFINED OPENRTM_LIBRARIES)

# ビルドするためにインクルードするヘッダーファイルの場所
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/idls/include")
include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${OMNIORB_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})

ADD_LIBRARY(${LIB_NAME} SHARED ${comp_srcs} ${comp_hdrs})

IF(USE_MATLAB_RUNTIME)
  target_link_libraries(${LIB_NAME} ${OPENRTM_LIBRARIES} ${OpenCV_LIBS} ${matlib})
ELSE(USE_MATLAB_RUNTIME)
  target_link_libraries(${LIB_NAME} ${OPENRTM_LIBRARIES} ${OpenCV_LIBS})
ENDIF()
# バージョン番号の適用
SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES VERSION ${serial} SOVERSION ${soserial})

#MESSAGE(STATUS ${CMAKE_INSTALL_PREFIX}/hi-brain/lib)
#MESSAGE(STATUS ${CMAKE_CURRENT_BINARY_DIR})

# 共有ライブラリのインストール指定
# INSTALL(TARGETS ターゲット タイプ DESTINATION インストール先)
INSTALL(TARGETS ${LIB_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/hi-brain/lib)
# 共有ライブラリ用ヘッダーファイルのインストール指定
# INSTALL(FILES ファイル DESTINATION インストール先)
INSTALL(FILES ${comp_hdrs} DESTINATION ${CMAKE_INSTALL_PREFIX}/hi-brain/include)
