// -*- C++ -*-
/*!
 * @file  ModuleName.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "{{ profile['BasicInfo']['name'] }}.h"

// Module specification
// <rtc-template block="module_spec">
static const char* {{ profile['BasicInfo']['name'].lower() }}_spec[] =
  {
    "implementation_id", "{{ profile['BasicInfo']['name'] }}",
    "type_name",         "{{ profile['BasicInfo']['name'] }}",
    "description",       "{{ profile['BasicInfo']['description'] }}",
    "version",           "{{ profile['BasicInfo']['version'] }}",
    "vendor",            "{{ profile['BasicInfo']['vendor'] }}",
    "category",          "{{ profile['BasicInfo']['category'] }}",
    "activity_type",     "{{ profile['BasicInfo']['activityType'] }}",
    "kind",              "{{ profile['BasicInfo']['componentKind'] }}",
    "max_instance",      "{{ profile['BasicInfo']['maxInstances'] }}",
    "language",          "{{ profile['lang'] }}",
    "lang_type",         "compile",
    // Configuration variables
{%- for name, ary in profile["ConfigurationSet"].items() %}
    "conf.default.{{ name }}", "{{ ary['defaultValue'] }}",
{%- endfor %}
    // Widget
{%- for name, ary in profile["ConfigurationSet"].items() %}
    {%- if ary['widget'] %}
    "conf.__widget__.{{ name }}", "{{ ary['widget'] }}",
    {%- endif %}
{%- endfor %}
    // Constraints
{%- for name, ary in profile["ConfigurationSet"].items() %}
    {%- if ary['constraint'] %}
    "conf.__constraints__.{{ name }}", "{{ ary['constraint'] }}",
    {%- endif %}
{%- endfor %}
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
{{ profile['BasicInfo']['name'] }}::{{ profile['BasicInfo']['name'] }}(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager)
{%- for name, ary in profile["Dataports"].items() -%}
    {%- if ary["portType"] == "DataInPort" -%}
, m_{{ ary['variableName'] }}In("{{ name }}", m_{{ ary['variableName'] }})
    {%- endif -%}
{%- endfor -%}
{%- for name, ary in profile["Dataports"].items() -%}
    {%- if ary["portType"] == "DataOutPort" -%}
, m_{{ ary['variableName'] }}Out("{{ name }}", m_{{ ary['variableName'] }})
    {%- endif -%}
{%- endfor -%}
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
{{ profile['BasicInfo']['name'] }}::~{{ profile['BasicInfo']['name'] }}()
{
}


{%- if profile['Actions']['onInitialize'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
{%- for name, ary in profile["Dataports"].items() %}
    {%- if ary["portType"] == "DataInPort" %}
  addInPort("{{ name }}", m_{{ ary['variableName'] }}In);
    {%- endif %}
{%- endfor %}
  
  // Set OutPort buffer
{%- for name, ary in profile["Dataports"].items() %}
    {%- if ary["portType"] == "DataOutPort" %}
  addOutPort("{{ name }}", m_{{ ary['variableName'] }}Out);
    {%- endif %}
{%- endfor %}
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
{%- for name, ary in profile["ConfigurationSet"].items() %}
  bindParameter("{{ name }}", {{ ary['objectName'] }}.{{ ary['variableName'] }}, "{{ ary['defaultValue'] }}");
{%- endfor %}
  // </rtc-template>
  
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onInitialize'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onFinalize'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onFinalize()
{
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onFinalize'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onStartup'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onStartup'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onShutdown'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onShutdown'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onActivated'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onActivated(RTC::UniqueId ec_id)
{
{%- for name, ary in profile["ConfigurationSet"].items() %}
  updateParameters("{{ name }}");
{%- endfor %}
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onActivated' and ary["portType"] == "DataInPort" %}
  std::cout << "waiting for input {{ ary['variableName'] }}..." ;
  while(!m_{{ ary['variableName'] }}In.isNew()){}
  m_{{ ary['variableName'] }}In.read();
  m_{{ ary['variableName'] }} >> model.{{ ary['variableName'] }};
  std::cout << "  ...ok" << std::endl;
	{%- endif %}
{%- endfor %}
  // model.create, viewer.Initialize
  fflg = false;
  model.create();
{%- for name, ary in profile["Dataports"].items() %}
	{%- if "Viewer" in ary %}
		{%- if ary["portType"] == "DataInPort" %}
  {{ ary['v_objectName'] }}.initialize(m_{{ ary['variableName'] }}In.getName(), &model.{{ ary['variableName'] }});
		{%- else %}
  {{ ary['v_objectName'] }}.initialize(m_{{ ary['variableName'] }}Out.getName(), &model.{{ ary['variableName'] }});
		{%- endif %}
	{%- endif %}
{%- endfor %}
  //portWrite()
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onActivated' and ary["portType"] == "DataOutPort" %}
  model.{{ ary['variableName'] }} >> m_{{ ary['variableName'] }};
  m_{{ ary['variableName'] }}Out.write();
	{%- endif %}
{%- endfor %}
  //show on Activate
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onActivated' and "Viewer" in ary %}
  {{ ary['v_objectName'] }}.vswitch();
	{%- endif %}
{%- endfor %}
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onActivated'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onDeactivated'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onDeactivated(RTC::UniqueId ec_id)
{
  // portRead on Deactivate
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onDeactivated' and ary["portType"] == "DataInPort" %}
  std::cout << "waiting for input {{ ary['variableName'] }}..." ;
  while(!m_{{ ary['variableName'] }}In.isNew()){}
  m_{{ ary['variableName'] }}In.read();
  m_{{ ary['variableName'] }} >> model.{{ ary['variableName'] }};
  std::cout << "  ...ok" << std::endl;
	{%- endif %}
{%- endfor %}
  // portWrite on Deactivate
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onDeactivated' and ary["portType"] == "DataOutPort" %}
  model.{{ ary['variableName'] }} >> m_{{ ary['variableName'] }};
  m_{{ ary['variableName'] }}Out.write();
	{%- endif %}
{%- endfor %}
  // model release
  model.release();
  // buffer release;
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary["portType"] == "DataInPort" %}
  while(m_{{ ary['variableName'] }}In.isNew()) m_{{ ary['variableName'] }}In.read();
	{%- endif %}
{%- endfor %}
  // viewer close
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] !=  'onDeactivated' and "Viewer" in ary %}
  {{ ary['v_objectName'] }}.vswitch(0);
	{%- endif %}
{%- endfor %}
  //show on Deactivate
{%- if 'ShowonDeactivated' in profile["Flags"] %}
	{%- for name, ary in profile["Dataports"].items() %}
		{%- if ary['Action'] ==  'onDeactivated' and "Viewer" in ary %}
  {{ ary['v_objectName'] }}.vswitch();
		{%- endif %}
	{%- endfor %}
  cv::waitKey(0);
{%- endif %}
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onDeactivated'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onExecute'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onExecute(RTC::UniqueId ec_id)
{
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onExecute' and ary["portType"] == "DataInPort" %}
  if(!m_{{ ary['variableName'] }}In.isNew()) return RTC::RTC_OK;
	{%- endif %}
{%- endfor %}
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onExecute' and ary["portType"] == "DataInPort" %}
  m_{{ ary['variableName'] }}In.read();
  m_{{ ary['variableName'] }} >> model.{{ ary['variableName'] }};
	{%- endif %}
{%- endfor %}
  if(fflg == false){
    model.first_execute();
    fflg = true;
  }
  model.execute();
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onExecute' and ary["portType"] == "DataOutPort" %}
  model.{{ ary['variableName'] }} >> m_{{ ary['variableName'] }};
  m_{{ ary['variableName'] }}Out.write();
	{%- endif %}
{%- endfor %}
  // show() on Execute;
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] !=  'onDeactivated' and "Viewer" in ary %}
  {{ ary['v_objectName'] }}.vswitch();
	{%- endif %}
{%- endfor %}
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onExecute'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onAborting'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onAborting(RTC::UniqueId ec_id)
{
  vmodel->onAborting();
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onAborting'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onError'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onError(RTC::UniqueId ec_id)
{
  vmodel->onError();
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onError'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onReset'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onReset(RTC::UniqueId ec_id)
{
  vmodel->onReset();
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onReset'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onStateUpdate'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onStateUpdate(RTC::UniqueId ec_id)
{
  vmodel->onStateUpdate();
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onStateUpdate'] == "false" %}
*/
{%- endif %}

{%- if profile['Actions']['onRateChanged'] == "false" %}
/*
{%- endif %}
RTC::ReturnCode_t {{ profile['BasicInfo']['name'] }}::onRateChanged(RTC::UniqueId ec_id)
{
  vmodel->onRateChanged();
  return RTC::RTC_OK;
}
{%- if profile['Actions']['onRateChanged'] == "false" %}
*/
{%- endif %}

extern "C"
{
 
  void {{ profile['BasicInfo']['name'] }}Init(RTC::Manager* manager)
  {
    coil::Properties profile({{ profile['BasicInfo']['name'].lower() }}_spec);
    manager->registerFactory(profile,
                             RTC::Create<{{ profile['BasicInfo']['name'] }}>,
                             RTC::Delete<{{ profile['BasicInfo']['name'] }}>);
  }
  
};


