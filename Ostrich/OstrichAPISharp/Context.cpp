

#include <msclr/marshal_cppstd.h>



//C++/CLI Header
#include "Context.h"
#include "CommonException.h"



//C++ Header
#include <commonException.h>



HV::V2::Context::Context(System::IntPtr _pointer, bool is_smart_pointer) {
	if (is_smart_pointer) {

		std::shared_ptr<hv::v2::icontext>* pointer = (std::shared_ptr<hv::v2::icontext>*) _pointer.ToPointer();
		this->_instance = *pointer;
	}
	else {
		hv::v2::icontext* pointer = (hv::v2::icontext*)_pointer.ToPointer();
		this->_instance = pointer;
	}
}


HV::V2::Context::~Context() {
	this->!Context();
}

HV::V2::Context::!Context() {
	this->_instance.reset();
}


System::IntPtr HV::V2::Context::Handle::get() {
	return System::IntPtr(this->_instance.pointer());
}

void HV::V2::Context::Loadlibrary() {
	try {
		this->_instance->loadLibrary();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


void HV::V2::Context::Unloadlibrary() {
	try {
		this->_instance->unloadLibrary();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Context::SetAddonPath(System::String^ path) {
	try {
		this->_instance->setAddonPath(msclr::interop::marshal_as<std::string>(path));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


// 여기서 부터 작업