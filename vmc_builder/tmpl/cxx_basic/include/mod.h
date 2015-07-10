// -*- C++ -*-
/*!
 * @file  {{ profile['BasicInfo']['name'] }}.h
 * @brief {{ profile['BasicInfo']['description'] }}
 * @date  $Date$
 *
 * $Id$
 */

#ifndef {{ profile['BasicInfo']['name'].upper() }}_H
#define {{ profile['BasicInfo']['name'].upper() }}_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
{%- for hdr in profile["Code"]['includes'] %}
#include "{{ hdr }}"
{%- endfor %}
// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "hi_brainStub.h"
#include "hi_convert_vision.h"

// </rtc-template>

using namespace RTC;
using namespace Vision;

/*!
 * @class ModuleName
 * @brief ModuleDescription
 *
 */
class {{ profile['BasicInfo']['name'] }}
  : public RTC::{{ profile['BasicInfo']['componentKind'] }}Base
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  {{ profile['BasicInfo']['name'] }}(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~{{ profile['BasicInfo']['name'] }}();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onInitialize'] == "true" %}
   virtual RTC::ReturnCode_t onInitialize();
{%- else -%}
  // virtual RTC::ReturnCode_t onInitialize();
{%- endif %}

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onFinalize'] == "true" %}
   virtual RTC::ReturnCode_t onFinalize();
{%- else %}
  // virtual RTC::ReturnCode_t onFinalize();
{%- endif %}

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onStartup'] == "true" %}
   virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);
{%- endif %}
  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onShutdown'] == "true" %}
   virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);
{%- endif %}

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onActivated'] == "true" %}
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
{%- endif %}

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onDeactivated'] == "true" %}
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
{%- endif %}

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onExecute'] == "true" %}
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);
{%- endif %}

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onAborting'] == "true" %}
   virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);
{%- endif %}

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onError'] == "true" %}
   virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);
{%- endif %}

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onReset'] == "true" %}
   virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
{%- endif %}
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onStateUpdate'] == "true" %}
   virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);
{%- endif %}

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
{%- if profile['Actions']['onRateChanged'] == "true" %}
   virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);
{%- else %}
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);
{%- endif %}


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
{%- for name, ary in profile["Dataports"].items() %}
    {%- if ary["portType"] == "DataInPort" %}
  InPort<{{ ary["type"] }}> m_{{ ary['variableName'] }}In;
    {%- endif -%}
{%- endfor %}
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
{%- for name, ary in profile["Dataports"].items() %}
    {%- if ary["portType"] == "DataOutPort" %}
  OutPort<{{ ary["type"] }}> m_{{ ary['variableName'] }}Out;
    {%- endif -%}
{%- endfor %}
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>
{%- for name, ary in profile["Dataports"].items() %}
  {{ ary['type'] }} m_{{ ary['variableName'] }};
{%- endfor %}
{%- for oname, cname in profile["Objects"].items() %}
  {{ cname }} {{ oname }};
{%- endfor %}
  bool fflg;
 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void {{ profile['BasicInfo']['name'] }}Init(RTC::Manager* manager);
};

#endif // {{ profile['BasicInfo']['name'].upper() }}_H
