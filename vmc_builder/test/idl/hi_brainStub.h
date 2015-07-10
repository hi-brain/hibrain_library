// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file hi_brainStub.h 
 * @brief hi_brain client stub header wrapper code
 * @date Tue Jul  7 17:37:34 2015 
 *
 */

#ifndef _HI_BRAINSTUB_H
#define _HI_BRAINSTUB_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "hi_brainC.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "hi_brain.hh"
#elif defined ORB_IS_MICO
#  include "hi_brain.h"
#elif defined ORB_IS_ORBIT2
#  include "hi_brain-cpp-stubs.h"
#elif defined ORB_IS_RTORB
#  include "hi_brain.h"
#else
#  error "NO ORB defined"
#endif

#endif // _HI_BRAINSTUB_H
