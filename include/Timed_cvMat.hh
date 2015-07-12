// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __Timed__cvMat_hh__
#define __Timed__cvMat_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
#endif



#ifndef __BasicDataType_hh_EXTERNAL_GUARD__
#define __BasicDataType_hh_EXTERNAL_GUARD__
#include <BasicDataType.hh>
#endif



#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





_CORBA_MODULE RTC

_CORBA_MODULE_BEG

  struct cvMat {
    typedef _CORBA_ConstrType_Variable_Var<cvMat> _var_type;

    
    ::CORBA::String_member data_type;

    ::CORBA::Long mat_type;

    ::CORBA::UShort width;

    ::CORBA::UShort height;

    ::CORBA::UShort bpp;

    ::CORBA::Boolean is_shared;

    ::CORBA::String_member name;

    ::CORBA::Long memory_index;

    ::CORBA::Long length;

    typedef _CORBA_Unbounded_Sequence_Octet _data_seq;
    _data_seq data;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef cvMat::_var_type cvMat_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< cvMat,cvMat_var > cvMat_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_cvMat;

  struct Timed_cvMat {
    typedef _CORBA_ConstrType_Variable_Var<Timed_cvMat> _var_type;

    
    Time tm;

    cvMat data;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef Timed_cvMat::_var_type Timed_cvMat_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< Timed_cvMat,Timed_cvMat_var > Timed_cvMat_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_Timed_cvMat;

_CORBA_MODULE_END



_CORBA_MODULE POA_RTC
_CORBA_MODULE_BEG

_CORBA_MODULE_END



_CORBA_MODULE OBV_RTC
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

extern void operator<<=(::CORBA::Any& _a, const RTC::cvMat& _s);
extern void operator<<=(::CORBA::Any& _a, RTC::cvMat* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, RTC::cvMat*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const RTC::cvMat*& _sp);

extern void operator<<=(::CORBA::Any& _a, const RTC::Timed_cvMat& _s);
extern void operator<<=(::CORBA::Any& _a, RTC::Timed_cvMat* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, RTC::Timed_cvMat*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const RTC::Timed_cvMat*& _sp);





#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_Timed__cvMat
#endif

#endif  // __Timed__cvMat_hh__
