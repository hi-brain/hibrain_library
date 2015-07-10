// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file hi_brainSkel.cpp 
 * @brief hi_brain server skeleton wrapper
 * @date Tue Jul  7 17:37:34 2015 
 *
 */

#include "hi_brainSkel.h"

#if defined ORB_IS_TAO
#  include "hi_brainC.cpp"
#  include "hi_brainS.cpp"
#elif defined ORB_IS_OMNIORB
#  include "hi_brainSK.cc"
#  include "hi_brainDynSK.cc"
#elif defined ORB_IS_MICO
#  include "hi_brain.cc"
#  include "hi_brain_skel.cc"
#elif defined ORB_IS_ORBIT2
#  include "hi_brain-cpp-stubs.cc"
#  include "hi_brain-cpp-skels.cc"
#elif defined ORB_IS_RTORB
#  include "OpenRTM-aist-decls.h"
#  include "hi_brain-common.c"
#  include "hi_brain-stubs.c"
#  include "hi_brain-skels.c"
#  include "hi_brain-skelimpl.c"
#else
#  error "NO ORB defined"
#endif

// end of hi_brainSkel.cpp
