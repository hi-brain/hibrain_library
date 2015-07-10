// -*- C++ -*-
/*!
 * @file  ModuleName.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "usbcamera.h"

// Module specification
// <rtc-template block="module_spec">
static const char* usbcamera_spec[] =
  {
    "implementation_id", "usbcamera",
    "type_name",         "usbcamera",
    "description",       "None",
    "version",           "1.0.0",
    "vendor",            "kazuki urabe",
    "category",          "None",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.viewer_output", "0:OFF",
    "conf.default.device_num", "0",
    // Widget
    "conf.__widget__.viewer_output", "radio",
    "conf.__widget__.device_num", "text",
    // Constraints
    "conf.__constraints__.viewer_output", "(1:ON,0:OFF)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
usbcamera::usbcamera(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager), m_outputOut("output", m_output)// </rtc-template>
{
}

/*!
 * @brief destructor
 */
usbcamera::~usbcamera()
{
}
RTC::ReturnCode_t usbcamera::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("output", m_outputOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("viewer_output", matviewer_output.view, "0:OFF");
  bindParameter("device_num", model.device_num, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}
/*
RTC::ReturnCode_t usbcamera::onFinalize()
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t usbcamera::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t usbcamera::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
RTC::ReturnCode_t usbcamera::onActivated(RTC::UniqueId ec_id)
{
  updateParameters("viewer_output");
  updateParameters("device_num");
  // model.create, viewer.Initialize
  fflg = false;
  model.create();
  matviewer_output.initialize(m_outputOut.getName(), &model.output);
  //portWrite()
  //show on Activate
  return RTC::RTC_OK;
}
RTC::ReturnCode_t usbcamera::onDeactivated(RTC::UniqueId ec_id)
{
  // portRead on Deactivate
  // portWrite on Deactivate
  // model release
  model.release();
  // buffer release;
  // viewer close
  matviewer_output.vswitch(0);
  //show on Deactivate
  return RTC::RTC_OK;
}
RTC::ReturnCode_t usbcamera::onExecute(RTC::UniqueId ec_id)
{
  if(fflg == false){
    model.first_execute();
    fflg = true;
  }
  model.execute();
  model.output >> m_output;
  m_outputOut.write();
  // show() on Execute;
  matviewer_output.vswitch();
  return RTC::RTC_OK;
}
/*
RTC::ReturnCode_t usbcamera::onAborting(RTC::UniqueId ec_id)
{
  vmodel->onAborting();
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t usbcamera::onError(RTC::UniqueId ec_id)
{
  vmodel->onError();
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t usbcamera::onReset(RTC::UniqueId ec_id)
{
  vmodel->onReset();
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t usbcamera::onStateUpdate(RTC::UniqueId ec_id)
{
  vmodel->onStateUpdate();
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t usbcamera::onRateChanged(RTC::UniqueId ec_id)
{
  vmodel->onRateChanged();
  return RTC::RTC_OK;
}
*/

extern "C"
{
 
  void usbcameraInit(RTC::Manager* manager)
  {
    coil::Properties profile(usbcamera_spec);
    manager->registerFactory(profile,
                             RTC::Create<usbcamera>,
                             RTC::Delete<usbcamera>);
  }
  
};

