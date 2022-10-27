#include "Addon.h"

#include "CommonException.h"
#include "NodeInfo.h"

HV::V2::Addon::Addon(System::IntPtr _pointer, bool is_smart_pointer) {
	if (is_smart_pointer) {

		std::shared_ptr<hv::v2::iaddon>* pointer = (std::shared_ptr<hv::v2::iaddon>*) _pointer.ToPointer();
		this->_instance = *pointer;
	}
	else {
		hv::v2::iaddon* pointer = (hv::v2::iaddon*)_pointer.ToPointer();
		this->_instance = pointer;
	}
}

HV::V2::Addon::~Addon() {
	this->!Addon();
}

HV::V2::Addon::!Addon() {
	this->_instance.reset();
}

bool HV::V2::Addon::Exist(int type) {
	return this->_instance->exist(type);
}

System::Collections::Generic::List<HV::V2::NodeInfo^>^ HV::V2::Addon::Information::get() {
	try {
		System::Collections::Generic::List<HV::V2::NodeInfo^>^ result = gcnew System::Collections::Generic::List<HV::V2::NodeInfo^>();
		auto nativeInputs = this->_instance->information();
		for (auto& node : nativeInputs) {
			result->Add(gcnew HV::V2::NodeInfo(System::IntPtr(&node), true));
		}
		return result;
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}