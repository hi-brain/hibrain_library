set(comp_srcs usbcamera.cpp
	hi_usbcamera.cpp
	)
set(standalone_srcs usbcameraComp.cpp)

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

add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})

# MATLAB, hi-brain
#-----------------------------------------------------------------------
# MATLAB COMPILER RUNTIME
IF(WIN32)
	# Search for a version of Matlab available, starting from the most modern one to older versions
	FOREACH(MATVER "8.1" "8.0" "7.20" "7.19" "7.18" "7.17" "7.16" "7.15" "7.14" "7.13" "7.12" "7.11" "7.10" "7.9" "7.8" "7.7" "7.6" "7.5" "7.4")
		IF((NOT DEFINED MATLAB_ROOT) OR ("${MATLAB_ROOT}" STREQUAL "") OR ("${MATLAB_ROOT}" STREQUAL "/registry"))
			GET_FILENAME_COMPONENT(MATLAB_ROOT
			"[HKEY_LOCAL_MACHINE\\SOFTWARE\\MathWorks\\MATLAB\\${MATVER};MATLABROOT]"
			ABSOLUTE)
		ENDIF((NOT DEFINED MATLAB_ROOT) OR ("${MATLAB_ROOT}" STREQUAL "") OR ("${MATLAB_ROOT}" STREQUAL "/registry"))
	ENDFOREACH(MATVER)
	# Directory name depending on whether the Windows architecture is 32 bit or 64 bit
	if(EXISTS "${MATLAB_ROOT}/extern/lib/win64/microsoft")
		set(MCR_LIBRARY_DIRS "${MATLAB_ROOT}/extern/lib/win64/microsoft;" "${PROJECT_SOURCE_DIR}/MATLAB_DIR;")
	elseif(EXISTS "${MATLAB_ROOT}/extern/lib/win32/microsoft")
		set(MCR_LIBRARY_DIRS "${MATLAB_ROOT}/extern/lib/win32/microsoft;" "${PROJECT_SOURCE_DIR}/MATLAB_DIR;")
	else(EXISTS "${MATLAB_ROOT}/extern/lib/win64/microsoft")
		message(FATAL_ERROR "Could not find whether Matlab is 32 bit or 64 bit")
	endif(EXISTS "${MATLAB_ROOT}/extern/lib/win64/microsoft")
	set(MCR_INCLUDE_DIRS "${MATLAB_ROOT}/extern/include;" "${PROJECT_SOURCE_DIR}/MATLAB_DIR;")
	find_library(MCR_MWMCLMCRRT_LIB
	  libmclmcrrt
	  ${MCR_LIBRARY_DIRS}/
	  )
ELSE( WIN32 )
	IF((NOT DEFINED MATLAB_ROOT) OR ("${MATLAB_ROOT}" STREQUAL ""))
		# check that command "matlab" is in the path
		execute_process(
			COMMAND which matlab
			OUTPUT_VARIABLE MATLAB_ROOT
		)
		if("${MATLAB_ROOT}" STREQUAL "")
			FOREACH(MATVER "v81" "v80" "v720" "v719" "v718" "v717" "v716" "v715" "v714" "v713" "v712" "v711" "v710" "v79" "v78" "v77" "v76" "v75" "v74")
				IF((NOT DEFINED MATLAB_ROOT) OR ("${MATLAB_ROOT}" STREQUAL ""))
					if(EXISTS "/usr/local/MATLAB/MATLAB_Compiler_Runtime/${MATVER}")
						set(MATLAB_ROOT "/usr/local/MATLAB/MATLAB_Compiler_Runtime/${MATVER}")
					endif(EXISTS "/usr/local/MATLAB/MATLAB_Compiler_Runtime/${MATVER}")
				ENDIF((NOT DEFINED MATLAB_ROOT) OR ("${MATLAB_ROOT}" STREQUAL ""))
			ENDFOREACH(MATVER)
		else("${MATLAB_ROOT}" STREQUAL "")
			# get path to the Matlab root directory
			execute_process(
				COMMAND which matlab
				COMMAND xargs readlink -m
				COMMAND xargs dirname
				COMMAND xargs dirname
				COMMAND xargs echo -n
				OUTPUT_VARIABLE MATLAB_ROOT
			)
		endif()
	ENDIF((NOT DEFINED MATLAB_ROOT) OR ("${MATLAB_ROOT}" STREQUAL ""))
	
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	  # Regular x86
	  set(MCR_INCLUDE_DIRS "${MATLAB_ROOT}/extern/include;" "${PROJECT_SOURCE_DIR}/MATLAB_DIR;")
	  set(MCR_LIBRARY_DIRS
		${MATLAB_ROOT}/runtime/glnx86
		${MATLAB_ROOT}/bin/glnx86
		${PROJECT_SOURCE_DIR}/MATLAB_DIR
	    )
	else(CMAKE_SIZEOF_VOID_P EQUAL 4)
	  # AMD64:
	  set(MCR_INCLUDE_DIRS "${MATLABCOMPILER_DIR}/extern/include;" "${PROJECT_SOURCE_DIR}/MATLAB_DIR;")
	  set(MCR_LIBRARY_DIRS
		${MATLAB_ROOT}/runtime/glnxa64
		${MATLAB_ROOT}/bin/glnxa64
		${PROJECT_SOURCE_DIR}/MATLAB_DIR
	    )
	endif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	find_library(MCR_MWMCLMCRRT_LIB
	  mwmclmcrrt
	  ${MCR_LIBRARY_DIRS}/
	  )
ENDIF(WIN32)
if(MCR_MWMCLMCRRT_LIB)
	set(MCR_LIBS
	  ${MCR_MWMCLMCRRT_LIB}
	)
	include_directories(${MCR_INCLUDE_DIRS})
	link_directories(${MCR_LIBRARY_DIRS})
else(MCR_MWMCLMCRRT_LIB)
	message(FATAL_ERROR, "matlab compiler runtime not found")
endif(MCR_MWMCLMCRRT_LIB)

# HIBRAIN LIBRARIES
IF(WIN32)
	find_library(HI_CONVERT_LIB
	  libhi_convert
	  )
	find_library(HI_MODELS_LIB
	  libhi_models
	  )
ELSE( WIN32 )
	set(HIBRAIN_INCLUDE_DIRS "/usr/local/hi-brain/include;")
	set(HIBRAIN_LIBRARY_DIRS "/usr/local/hi-brain/lib;")
	find_library(HI_CONVERT_LIB
	  hi_convert
	  ${HIBRAIN_LIBRARY_DIRS}/
	  )
	find_library(HI_MODELS_LIB
	  hi_models
	  ${HIBRAIN_LIBRARY_DIRS}/
	  )
ENDIF(WIN32)
if(HI_CONVERT_LIB)
	set(HI_LIBS
	  ${HI_CONVERT_LIB}
	  ${HI_MODELS_LIB}
	)
	include_directories(${HIBRAIN_INCLUDE_DIRS})
	link_directories(${HIBRAIN_LIBRARY_DIRS})
else(HI_CONVERT_LIB)
	message(FATAL_ERROR, "hibrain libraries not found")
endif(HI_CONVERT_LIB)
#-----------------------------------------------------------------------

add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
  ${comp_headers} ${ALL_IDL_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} ${OpenCV_LIBS} ${MCR_LIBS} ${HI_LIBS})

add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES} ${OpenCV_LIBS} ${MCR_LIBS} ${HI_LIBS})

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)