set(comp_srcs {{ profile['BasicInfo']['name'] }}.cpp
{%- for name, val in addcode["srcs"].items() %}
	{{ val }}
{%- endfor %}
	)
set(standalone_srcs {{ profile['BasicInfo']['name'] }}Comp.cpp)

find_package(PkgConfig)
pkg_check_modules(HI REQUIRED hibrain)
include_directories(${HI_INCLUDE_DIRS})
link_directories(${HI_LIBRARY_DIRS})
message(HI_LIBRARIES, "${HI_LIBRARIES}")
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

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR}/idl)
include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${OMNIORB_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})

# MATLAB, hi-brain
#-----------------------------------------------------------------------
# MATLAB COMPILER RUNTIME
IF(USE_MATLAB_RUNTIME)
	IF($ENV{MATLAB_RUNTIME_PATH})
	  message(MATLAB_RUNTIME_PATH "$ENV{MATLAB_RUNTIME_PATH}")
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
	ENDIF($ENV{MATLAB_RUNTIME_PATH})
ENDIF(USE_MATLAB_RUNTIME)

add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
  ${comp_headers} ${ALL_IDL_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
IF(USE_MATLAB_RUNTIME)
	target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} ${OpenCV_LIBS} ${matlib} ${HI_LIBRARIES})
ELSE(USE_MATLAB_RUNTIME)
	target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} ${OpenCV_LIBS} ${HI_LIBRARIES})
ENDIF(USE_MATLAB_RUNTIME)

add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
IF(USE_MATLAB_RUNTIME)
	target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES} ${OpenCV_LIBS} ${matlib} ${HI_LIBRARIES})
ELSE(USE_MATLAB_RUNTIME)
	target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES} ${OpenCV_LIBS} ${HI_LIBRARIES})
ENDIF()

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)
