// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file hi_brainSkel.h 
 * @brief hi_brain server skeleton header wrapper code
 * @date Tue Jul  7 17:37:34 2015 
 *
 */

#ifndef _HI_BRAINSKEL_H
#define _HI_BRAINSKEL_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "hi_brainC.h"
#  include "hi_brainS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "hi_brain.hh"
#elif defined ORB_IS_MICO
#  include "hi_brain.h"
#elif defined ORB_IS_ORBIT2
#  include "/hi_brain-cpp-stubs.h"
#  include "/hi_brain-cpp-skels.h"
#elif defined ORB_IS_RTORB
#  include "hi_brain.h"
#else
#  error "NO ORB defined"
#endif

#endif // _HI_BRAINSKEL_H
