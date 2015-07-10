// -*- C++ -*-
/*!
 * @file  ModuleName.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "ModuleName.h"

// Module specification
// <rtc-template block="module_spec">
static const char* modulename_spec[] =
  {
    "implementation_id", "ModuleName",
    "type_name",         "ModuleName",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.conf_name0", "1",
    // Widget
    "conf.__widget__.conf_name0", "ordered_list",
    // Constraints
    "conf.__constraints__.conf_name0", "{ON:1,OFF:0}",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ModuleName::ModuleName(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_in_v1In("in_port1", m_in_v1),
    m_out_v1Out("out_port1", m_out_v1),
    m_out_v2Out("out_port2", m_out_v2)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ModuleName::~ModuleName()
{
}



RTC::ReturnCode_t ModuleName::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in_port1", m_in_v1In);
  
  // Set OutPort buffer
  addOutPort("out_port1", m_out_v1Out);
  addOutPort("out_port2", m_out_v2Out);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("conf_name0", m_param1, "1");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ModuleName::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ModuleName::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ModuleName::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ModuleName::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ModuleName::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ModuleName::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ModuleName::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ModuleName::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ModuleName::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ModuleName::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ModuleName::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ModuleNameInit(RTC::Manager* manager)
  {
    coil::Properties profile(modulename_spec);
    manager->registerFactory(profile,
                             RTC::Create<ModuleName>,
                             RTC::Delete<ModuleName>);
  }
  
};


