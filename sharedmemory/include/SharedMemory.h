#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <string>
#include <rtm/ConnectorListener.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
//#include <boost/interprocess/managed_windows_shared_memory.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace cv {
	class Mat;
};

namespace RTC {
	struct Timed_cvMat;
	class OutPortConnector;
};

namespace USM
{
	
	class OnConnectedListener : public RTC::ConnectorListener
	{
	private:
		bool &useSharedMemory;
		std::string my_ip;

	public:
		OnConnectedListener(bool &useSharedMemory, std::string my_ip);
		void operator()(const RTC::ConnectorInfo& info);
	};

	class OnDisconnectedListener : public RTC::ConnectorListener
	{
	private:
		bool &useSharedMemory;
		std::string &my_ip;
		std::vector<RTC::OutPortConnector*> &m_connectors;

	public:
		OnDisconnectedListener(bool &useSharedMemory, std::string &my_ip, std::vector<RTC::OutPortConnector*> &m_connectors);
		void operator()(const RTC::ConnectorInfo& info);
	};

	template <class DataType>
	class OutPort
		: public RTC::OutPort<DataType>
	{
		DataType& m_value;

	private:
		std::string getIpFromIOR(omniIOR &ior);
		std::string my_ip;
		boost::interprocess::managed_shared_memory m_shared_memory;
//		boost::interprocess::managed_windows_shared_memory m_shared_memory;
		bool useSharedMemory;
		unsigned int m_idx_num;

		unsigned int m_curr_idx_num;

		unsigned int m_buffer_size;

		std::map<std::string, unsigned char*> m_memory_map;

		std::string m_memory_name;

		void cvMat2Timed_cvMat(cv::Mat src, RTC::Timed_cvMat &dst);


	public:
		OutPort(const char* name, DataType& value);
		~OutPort(){};

		void initialize();

		bool write();
		bool write(RTC::Timed_cvMat src);

		bool write(cv::Mat src);

		void setMemoryFlag(bool flag);
	};
	template <class DataType>
	class InPort
		: public RTC::InPort<DataType>
	{
		DataType& m_value;

	public:
		InPort(const char* name, DataType& value);
		~InPort(){};

		// RTC::InPort.read()Ç∆ìØólÇÃãììÆÇÇ∑ÇÈì«Ç›çûÇ›ä÷êî
		bool read();

		// InPortÇ©ÇÁì«Ç›çûÇ›ÅCTimed_cvMatÇ©ÇÁcv::MatÇ÷ÇÃïœä∑ÇçsÇ§ä÷êî
		bool read(cv::Mat& dst);
	};

	std::string createIndex(int idx);
};

#endif  // SHARED_MEMORY_H