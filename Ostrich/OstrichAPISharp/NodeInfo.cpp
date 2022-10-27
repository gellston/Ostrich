#include "NodeInfo.h"





HV::V2::NodeInfo::NodeInfo(System::IntPtr _pointer, bool is_smart_pointer) {
	if (is_smart_pointer) {

		std::shared_ptr<hv::v2::nodeInfo>* pointer = (std::shared_ptr<hv::v2::nodeInfo>*) _pointer.ToPointer();
		this->_instance = *pointer;
	}
	else {
		hv::v2::nodeInfo* nodeInfo = (hv::v2::nodeInfo*)_pointer.ToPointer();
		this->_instance = nodeInfo;
	}
}

HV::V2::NodeInfo::~NodeInfo() {
	this->!NodeInfo();
}

HV::V2::NodeInfo::!NodeInfo() {
	this->_instance.reset();
}


System::String^ HV::V2::NodeInfo::Name::get() {

	return gcnew System::String(this->_instance->name().c_str());
}

System::String^ HV::V2::NodeInfo::Category::get() {

	return gcnew System::String(this->_instance->category().c_str());
}

int HV::V2::NodeInfo::Type::get() {
	return this->_instance->type();
}