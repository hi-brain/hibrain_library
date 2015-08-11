#include "SharedMemory.h"
#include "Timed_cvMatStub.h"
#include <iostream>
#include <rtm/CORBA_IORUtil.h>
#include <opencv2/opencv.hpp>
#include <boost/format.hpp>
using namespace USM;

void USM::OnConnectedListener::operator()(const RTC::ConnectorInfo& info){

	std::string inport_ior(info.properties["corba_cdr.inport_ior"]);
	IOP::IOR iortmp;
	CORBA_IORUtil::toIOR(inport_ior.c_str(), iortmp);

	if (iortmp.profiles.length() == 0 && strlen(iortmp.type_id) == 0) {
		useSharedMemory = false;
	}

	for (unsigned long count=0; count < iortmp.profiles.length(); ++count) {
		if (iortmp.profiles[count].tag == IOP::TAG_INTERNET_IOP) {
			IIOP::ProfileBody pBody;
			IIOP::unmarshalProfile(iortmp.profiles[count], pBody);
			std::string herip(pBody.address.host);

			if ( my_ip != herip ) {
				useSharedMemory = false;
			}
		}else{
			useSharedMemory = false;
		}
	}
};

USM::OnConnectedListener::OnConnectedListener(bool &useSharedMemory, std::string my_ip)
	: useSharedMemory(useSharedMemory),
      my_ip(my_ip)
{
}

void USM::OnDisconnectedListener::operator()(const RTC::ConnectorInfo& info){
	useSharedMemory = true;

	for (std::vector<RTC::OutPortConnector*>::iterator it = m_connectors.begin(); it != m_connectors.end(); ++it) {
		RTC::ConnectorInfo conInfo = (*it)->profile();
		std::string inport_ior(conInfo.properties["corba_cdr.inport_ior"]);

		if(conInfo.name != info.name){
			IOP::IOR iortmp;
			CORBA_IORUtil::toIOR(inport_ior.c_str(), iortmp);
			if (iortmp.profiles.length() == 0 && strlen(iortmp.type_id) == 0) {
				useSharedMemory = false;
			}
			for (unsigned long count=0; count < iortmp.profiles.length(); ++count) {
				if (iortmp.profiles[count].tag == IOP::TAG_INTERNET_IOP) {
					IIOP::ProfileBody pBody;
					IIOP::unmarshalProfile(iortmp.profiles[count], pBody);
					std::string herip(pBody.address.host);

					if ( my_ip != herip ) {
						useSharedMemory = false;
					}
				}else{
					useSharedMemory = false;
				}
			}
		}
	}
};

USM::OnDisconnectedListener::OnDisconnectedListener(bool &useSharedMemory, std::string &my_ip, std::vector<RTC::OutPortConnector*> &m_connectors)
	: useSharedMemory(useSharedMemory),
	my_ip(my_ip),
	m_connectors(m_connectors)
{
}

namespace USM
{
	template <>
	OutPort<RTC::Timed_cvMat>::OutPort(const char* name, RTC::Timed_cvMat& value)
		: RTC::OutPort<RTC::Timed_cvMat>(name,value),
		m_value(value)
	{
		useSharedMemory = true;
	}

	template <>
	std::string USM::OutPort<RTC::Timed_cvMat>::getIpFromIOR(omniIOR &ior){
		std::string ip="";
		for (int i=0; i< (signed)ior.iopProfiles().length(); i++){
			if ( ior.iopProfiles()[i].tag == IOP::TAG_INTERNET_IOP) {
				IIOP::ProfileBody pBody;
				IIOP::unmarshalProfile( ior.iopProfiles()[i], pBody);
				ip = std::string( pBody.address.host );
			}
		}
		return ip;
	}

	template <>
	void USM::OutPort<RTC::Timed_cvMat>::initialize(){
		my_ip = getIpFromIOR(*(m_objref->_getIOR()));

		addConnectorListener(RTC::ON_CONNECT, new OnConnectedListener(useSharedMemory, my_ip));
		addConnectorListener(RTC::ON_DISCONNECT, new OnDisconnectedListener(useSharedMemory, my_ip, m_connectors));

		try{
			m_buffer_size = 2097152;
			m_idx_num = 10;
			m_curr_idx_num = 0;

			m_memory_name = this->getName();
//			m_shared_memory = boost::interprocess::managed_windows_shared_memory( boost::interprocess::create_only, m_memory_name.c_str(), m_buffer_size*(m_idx_num+1) );
			m_shared_memory = boost::interprocess::managed_shared_memory( boost::interprocess::create_only, m_memory_name.c_str(), m_buffer_size*(m_idx_num+1) );

			for ( int i=0; i<(signed)m_idx_num; i++ ) 
			{
				std::string idx_name = createIndex(i);
				unsigned char* data = m_shared_memory.construct<unsigned char>(idx_name.c_str())[m_buffer_size]();
				m_memory_map[idx_name] = data;
			}
		} catch ( std::exception e ) {
			std::string msg;
			msg = (boost::format("Shared Memory failed. OpenCV_RTC can not allocate memory (%d byte). %s, file %s, line %s")
				%(m_buffer_size*(m_idx_num+1))
				%__FUNCTION__
				%__FILE__
				%__LINE__
				).str();
			throw std::runtime_error( msg );
		}
	};

	template <>
	bool OutPort<RTC::Timed_cvMat>::write(){
		return RTC::OutPort<RTC::Timed_cvMat>::write();
	};

	template <>
	bool OutPort<RTC::Timed_cvMat>::write(cv::Mat src){
		cvMat2Timed_cvMat(src,m_value);
		return RTC::OutPort<RTC::Timed_cvMat>::write();
	};

	template <>
	bool OutPort<RTC::Timed_cvMat>::write(RTC::Timed_cvMat src){
//		return RTC::OutPort<DataType>::write(src);
		return RTC::OutPort<RTC::Timed_cvMat>::write(src);
	};

	std::string createIndex( int idx )
	{
		return (boost::format("data_idx%d")%idx).str();
	}

	template<class DataType>
	void USM::OutPort<DataType>::cvMat2Timed_cvMat(cv::Mat src, RTC::Timed_cvMat &dst){
		if(src.empty()){
			std::cerr << "cvMat2Timed_cvMat: src is empty" << std::endl;
			return;
		}

		if(useSharedMemory){
			unsigned int size = (unsigned int) (src.cols * src.rows * src.elemSize());
			dst.data.data.length( static_cast<unsigned long>(size) );
			dst.data.width     = src.cols;
			dst.data.height    = src.rows;
			dst.data.bpp       = static_cast<unsigned short>(src.elemSize());
			dst.data.mat_type  = src.type();
			dst.data.data_type = typeid(src).name();

			unsigned char* memory = m_memory_map[ createIndex(m_curr_idx_num) ];
			memcpy( memory, (uchar*)(&src.data[0]), size );


			dst.data.data.length(0);
			dst.data.data.release();
			dst.data.is_shared		= true;
			dst.data.name			= m_memory_name.c_str();
			dst.data.memory_index	= m_curr_idx_num;
			dst.data.length          = size;

			m_curr_idx_num++;
			m_curr_idx_num %= m_idx_num;

		}else{
			size_t size = src.cols * src.rows * src.elemSize();
			dst.data.data.length( static_cast<unsigned long>(size) );
			dst.data.is_shared = false;
			dst.data.width     = src.cols;
			dst.data.height    = src.rows;
			dst.data.bpp       = static_cast<unsigned short>(src.elemSize());
			dst.data.mat_type  = src.type();
			dst.data.data_type = typeid(src).name();
			memcpy( (uchar*)(&dst.data.data[0]), (uchar*)(&src.data[0]), size );
		}
	};

	template <>
	void USM::OutPort<RTC::Timed_cvMat>::setMemoryFlag(bool flag){
		this->useSharedMemory = flag;
	}

	template <>
	InPort<RTC::Timed_cvMat>::InPort(const char* name, RTC::Timed_cvMat& value)
		: RTC::InPort<RTC::Timed_cvMat>(name,value),
		m_value(value)
	{
	};

	template <>
	bool USM::InPort<RTC::Timed_cvMat>::read(){
		return RTC::InPort<RTC::Timed_cvMat>::read();
	}

	template <>
	bool InPort<RTC::Timed_cvMat>::read(cv::Mat& dst){
		bool ret = RTC::InPort<RTC::Timed_cvMat>::read();
		if(ret == false){
			return false;
		}

//		boost::interprocess::managed_windows_shared_memory shared_memory;
		boost::interprocess::managed_shared_memory shared_memory;
		unsigned char* memory;
		unsigned long mem_size;


		if ( m_value.data.is_shared == true ) {
//			const std::string file_name = m_value.data.name;
			const char* file_name_char = m_value.data.name;
			const std::string file_name = std::string(file_name_char);
			unsigned long index         = m_value.data.memory_index;
			const std::string index_str = createIndex( index );
			mem_size                    = m_value.data.length;

//			shared_memory = boost::interprocess::managed_windows_shared_memory( boost::interprocess::open_only, file_name.c_str() );
			shared_memory = boost::interprocess::managed_shared_memory( boost::interprocess::open_only, file_name.c_str() );
			memory = shared_memory.find<unsigned char>( index_str.c_str() ).first;

			if ( memory == NULL ) {
				std::string msg;
				msg = (boost::format("Assertion failed cannot find shared memory in %s, file %s, line %s")
					%__FUNCTION__
					%__FILE__
					%__LINE__
					).str();
				throw std::runtime_error( msg );
			}
		}else{
			mem_size = m_value.data.data.length();
			memory = (unsigned char*)(&m_value.data.data[0]);
		}

		if(mem_size > 0){
			unsigned int cols = m_value.data.width;
			unsigned int rows = m_value.data.height;
			long mat_type     = m_value.data.mat_type;
			dst.create(rows, cols, mat_type);
			memcpy(dst.data, memory, mem_size);
		}
		return true;

	}
}