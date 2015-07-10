#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "usbcamera" for configuration ""
set_property(TARGET usbcamera APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(usbcamera PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "pthread;omniORB4;omnithread;omniDynamic4;RTC;coil;opencv_videostab;opencv_video;opencv_ts;opencv_superres;opencv_stitching;opencv_photo;opencv_ocl;opencv_objdetect;opencv_nonfree;opencv_ml;opencv_legacy;opencv_imgproc;opencv_highgui;opencv_gpu;opencv_flann;opencv_features2d;opencv_core;opencv_contrib;opencv_calib3d;/usr/local/MATLAB/R2014b/runtime/glnxa64/libmwmclmcrrt.so;/usr/local/hi-brain/lib/libhi_convert.so;/usr/local/hi-brain/lib/libhi_models.so"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/usbcamera.so"
  IMPORTED_SONAME_NOCONFIG "usbcamera.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS usbcamera )
list(APPEND _IMPORT_CHECK_FILES_FOR_usbcamera "${_IMPORT_PREFIX}/components/lib/usbcamera.so" )

# Import target "usbcameraComp" for configuration ""
set_property(TARGET usbcameraComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(usbcameraComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/usbcameraComp"
  )

list(APPEND _IMPORT_CHECK_TARGETS usbcameraComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_usbcameraComp "${_IMPORT_PREFIX}/components/bin/usbcameraComp" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
