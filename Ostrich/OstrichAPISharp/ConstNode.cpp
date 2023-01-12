


#include <msclr/marshal_cppstd.h>


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


bool HV::V2::ConstNode::IsMultiple::get() {
	try {
		return this->_instance->isMultiple();
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

void HV::V2::ConstNode::RegisterMultipleSourceNode(std::size_t uid, System::String^ name) {
	try {
		this->_instance->registerMultipleSourceNode(uid, msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::ConstNode::ClearMultipleSourceNode() {
	try {
		this->_instance->clearMultipleSourceNode();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::ConstNode::UnRegisterMultipleSourceNode(std::size_t uid, System::String^ name) {
	try {
		this->_instance->unRegisterMultipleSourceNode(uid, msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::ConstNode::UnRegisterMultipleSourceNode(std::size_t uid) {
	try {
		this->_instance->unRegisterMultipleSourceNode(uid);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ HV::V2::ConstNode::MultipleSourceNode::get() {


	try {
		System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ result = gcnew System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>();
		auto nativeResult = this->_instance->multipleSourceNode();

		for (auto element : nativeResult) {
			auto uid = std::get<0>(element);
			auto name = std::get<1>(element);
			auto managedTuple = gcnew System::Tuple<std::size_t, System::String^>(uid, gcnew System::String(name.c_str()));
			result->Add(managedTuple);
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



void HV::V2::ConstNode::MultipleSourceNode::set(System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ collection) {

	try {

		std::vector<std::tuple<std::size_t, std::string>> nativeCollection;

		auto count = collection->Count;
		for (auto index = 0; index < count; index++) {
			auto managedElement = collection[index];
			auto nativeSourceUID = managedElement->Item1;
			auto nativeSourceName = msclr::interop::marshal_as<std::string>(managedElement->Item2);

			nativeCollection.push_back(std::tuple<std::size_t, std::string>(nativeSourceUID, nativeSourceName));
		}

		this->_instance->multipleSourceNode(nativeCollection);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}