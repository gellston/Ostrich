
//C++/CLI Header
#include "ConstNode.h"
#include "CommonException.h"



//C++ Header
#include <commonException.h>


HV::V2::ConstNode::ConstNode(System::IntPtr _pointer, bool is_smart_pointer) {
	if (is_smart_pointer) {

		std::shared_ptr<hv::v2::iconstNode>* pointer = (std::shared_ptr<hv::v2::iconstNode>*) _pointer.ToPointer();
		this->_instance = *pointer;
	}
	else {
		hv::v2::iconstNode* pointer = (hv::v2::iconstNode*) _pointer.ToPointer();
		this->_instance = pointer;
	}
}

HV::V2::ConstNode::~ConstNode() {
	this->!ConstNode();
}

HV::V2::ConstNode::!ConstNode() {
	this->_instance.~mananged_shared_ptr();
}

System::IntPtr HV::V2::ConstNode::Handle::get() {
	
	return System::IntPtr(this->_instance.pointer());
}

System::String^ HV::V2::ConstNode::Name::get() {
	try {
		return gcnew System::String(this->_instance->name().c_str());
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

std::size_t HV::V2::ConstNode::Uid::get() {
	try {
		return this->_instance->uid();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

int HV::V2::ConstNode::Type::get() {
	try {
		return this->_instance->type();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

void HV::V2::ConstNode::Init() {
	try {
		this->_instance->init();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}


int HV::V2::ConstNode::Index::get() {
	try {
		return this->_instance->index();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

bool HV::V2::ConstNode::IsConnected::get() {
	try {
		return this->_instance->isConnected();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

System::String^ HV::V2::ConstNode::SourceName::get() {
	try {
		return gcnew System::String(this->_instance->sourceName().c_str());
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

std::size_t HV::V2::ConstNode::SourceUID::get() {
	try {
		return this->_instance->sourceUID();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}


System::Object^ HV::V2::ConstNode::Clone() {
	try {
		auto nativeCloneObject = this->_instance->clone();
		auto managedCloneObject = gcnew HV::V2::ConstNode(System::IntPtr(&nativeCloneObject), true);
		return managedCloneObject;
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}