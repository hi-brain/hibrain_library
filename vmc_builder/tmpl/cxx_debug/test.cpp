#include "filter3d.h"
#include <iostream>

void setconfig(hi::filter3d &obj){
// Set Configuration Parameters
{%- for name, ary in profile["ConfigurationSet"].items() %}
//	{{ ary['objectName'] }}.{{ ary['variableName'] }};
{%- endfor %}

};

void input_onActivated(hi::filter3d &obj){
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onActivated' and ary["portType"] == "DataInPort" %}
//	model.{{ ary['variableName'] }};
	{%- endif %}
{%- endfor %}
};
void input_onExecute(hi::filter3d &obj){
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onActivated' and ary["portType"] == "DataInPort" %}
//	model.{{ ary['variableName'] }};
	{%- endif %}
{%- endfor %}
};
void input_onDeactivated(hi::filter3d &obj){
{%- for name, ary in profile["Dataports"].items() %}
	{%- if ary['Action'] ==  'onDeactivated' and ary["portType"] == "DataInPort" %}
//	model.{{ ary['variableName'] }};
	{%- endif %}
{%- endfor %}
	
};


// Main
int main(){
{%- for oname, cname in profile["Objects"].items() %}
	{{ cname }} {{ oname }};
{%- endfor %}
	
	// set parameters
{%- for name, ary in profile["ConfigurationSet"].items() %}
//	{{ ary['objectName'] }}.{{ ary['variableName'] }};
{%- endfor %}
	
	std::cout << "onActivated" << std::endl;
	input_onActivated(model);
	model.create();
	
{%- for name, ary in profile["Dataports"].items() %}
	{%- if "Viewer" in ary %}
	{{ ary['v_objectName'] }}.initialize("{{ name }}", &model.{{ ary['variableName'] }});
	{%- endif %}
{%- endfor %}
	viewer_output.initialize("output", &objmodel.output);
	
	std::cout << "onExecute" << std::endl;
	input_onExecute(model);
	std::cout << "first_execute()" << std::endl;
	obj.first_execute();
	std::cout << "execute()" << std::endl;
	obj.execute();
	
	//std::cout << obj.output << std::endl;
	//cv::imshow("output", model.output);
{%- for name, ary in profile["Dataports"].items() %}
	{%- if "Viewer" in ary %}
	{{ ary['v_objectName'] }}.vswitch(1);
	{%- endif %}
{%- endfor %}
	std::cout << "Plz press any key (on viewer window)" << std::endl;
	cv::waitKey(0);
	
	std::cout << "onDeactivated" << std::endl;
	input_onDeactivated(model);
	obj.release();
	
	return 0;
}
