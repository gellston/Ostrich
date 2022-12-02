
#include <msclr/marshal_cppstd.h>


#include <compositeNode.h>


#include "CompositeNode.h"
#include "CommonException.h"
#include "ConstNode.h"





HV::V2::CompositeNode::CompositeNode(IntPtr _pointer, bool is_smart_pointer) {

	if (is_smart_pointer) {

		std::shared_ptr<hv::v2::icompositeNode>* pointer = (std::shared_ptr<hv::v2::icompositeNode>*) _pointer.ToPointer();
		this->_instance = *pointer;
	}
	else {
		hv::v2::icompositeNode* pointer = (hv::v2::icompositeNode*)_pointer.ToPointer();
		this->_instance = pointer;
	}
}

HV::V2::CompositeNode::~CompositeNode() {
	this->!CompositeNode();
}

HV::V2::CompositeNode::!CompositeNode() {
	this->_instance.reset();
}

int HV::V2::CompositeNode::Depth::get() {
	try {
		return this->_instance->depth();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

bool HV::V2::CompositeNode::IsConnected::get() {
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

bool HV::V2::CompositeNode::CheckSourceUID(std::size_t uid) {
	try {
		return this->_instance->checkSourceUID(uid);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


bool HV::V2::CompositeNode::IsConditionalNode::get() {
	try {
		return this->_instance->isConditionalNode();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

bool HV::V2::CompositeNode::IsFreezed::get() {
	try {
		return this->_instance->isFreezed();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::CompositeNode::IsFreezed::set(bool value) {
	try {
		return this->_instance->isFreezed(value);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

bool HV::V2::CompositeNode::IsEventNode::get() {
	try {
		return this->_instance->isEventNode();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

System::Collections::Generic::List<HV::V2::IConstNode^>^ HV::V2::CompositeNode::Inputs::get() {
	try {
		auto result = gcnew System::Collections::Generic::List<HV::V2::IConstNode^>();
		auto nativeInputs = this->_instance->inputs();
		for (auto &node : nativeInputs) {
			result->Add(gcnew HV::V2::ConstNode(System::IntPtr(&node), true));
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

System::Collections::Generic::List<HV::V2::IConstNode^>^ HV::V2::CompositeNode::Outputs::get() {
	try {
		auto result = gcnew System::Collections::Generic::List<HV::V2::IConstNode^>();
		auto nativeOutputs = this->_instance->outputs();
		for (auto& node : nativeOutputs) {
			result->Add(gcnew HV::V2::ConstNode(System::IntPtr(&node), true));
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

System::Collections::Generic::List<HV::V2::IConstNode^>^ HV::V2::CompositeNode::InputClone::get() {
	try {
		auto result = gcnew System::Collections::Generic::List<HV::V2::IConstNode^>();
		auto nativeInputs = this->_instance->inputClone();
		for (auto& node : nativeInputs) {
			result->Add(gcnew HV::V2::ConstNode(System::IntPtr(&node), true));
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

System::Collections::Generic::List<HV::V2::IConstNode^>^ HV::V2::CompositeNode::OutputClone::get() {
	try {
		auto result = gcnew System::Collections::Generic::List<HV::V2::IConstNode^>();
		auto nativeOutputs = this->_instance->outputClone();
		for (auto& node : nativeOutputs) {
			result->Add(gcnew HV::V2::ConstNode(System::IntPtr(&node), true));
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


HV::V2::IConstNode^ HV::V2::CompositeNode::Input(System::String^ key) {
	try {
		auto nativeObject = this->_instance->input(msclr::interop::marshal_as<std::string>(key));
		return gcnew HV::V2::ConstNode(System::IntPtr(&nativeObject), true);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

HV::V2::IConstNode^ HV::V2::CompositeNode::Output(System::String^ key) {
	try {
		auto nativeObject = this->_instance->output(msclr::interop::marshal_as<std::string>(key));
		return gcnew HV::V2::ConstNode(System::IntPtr(&nativeObject), true);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::CompositeNode::ReplaceInputs(System::Collections::Generic::List<HV::V2::IConstNode^>^ inputs) {
	try {

		std::vector<std::shared_ptr<hv::v2::iconstNode>> nativeGroup;

		for (int index = 0; index < inputs->Count; index++) {
			auto managedConstNode = inputs[index];
			auto nativeConstNodePointer = (std::shared_ptr<hv::v2::iconstNode>*) managedConstNode->Handle.ToPointer();
			nativeGroup.push_back(*nativeConstNodePointer);
		}
		this->_instance->replaceInputs(nativeGroup);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::CompositeNode::ReplaceOutputs(System::Collections::Generic::List<HV::V2::IConstNode^>^ outputs) {
	try {

		std::vector<std::shared_ptr<hv::v2::iconstNode>> nativeGroup;

		for (int index = 0; index < outputs->Count; index++) {
			auto managedConstNode = outputs[index];
			auto nativeConstNodePointer = (std::shared_ptr<hv::v2::iconstNode>*) managedConstNode->Handle.ToPointer();
			nativeGroup.push_back(*nativeConstNodePointer);
		}
		this->_instance->replaceOuputs(nativeGroup);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


System::Collections::Generic::List<std::size_t>^ HV::V2::CompositeNode::ConstUID::get() {
	try {
		auto result = gcnew System::Collections::Generic::List<std::size_t>();
		auto nativeGroup = this->_instance->constUID();
		for (auto& uid : nativeGroup) {
			result->Add(uid);
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

System::Collections::Generic::List<std::size_t>^ HV::V2::CompositeNode::InputConstUID::get() {
	try {
		auto result = gcnew System::Collections::Generic::List<std::size_t>();
		auto nativeGroup = this->_instance->inputConstUID();
		for (auto& uid : nativeGroup) {
			result->Add(uid);
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



System::Collections::Generic::List<std::size_t>^ HV::V2::CompositeNode::OutputConstUID::get() {
	try {
		auto result = gcnew System::Collections::Generic::List<std::size_t>();
		auto nativeGroup = this->_instance->outputConstUID();
		for (auto& uid : nativeGroup) {
			result->Add(uid);
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

HV::V2::ResultType HV::V2::CompositeNode::Process() {
	try {
		return (HV::V2::ResultType)this->_instance->process();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::CompositeNode::UpdateConst(std::size_t uid) {
	try {
		this->_instance->updateConst(uid);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

HV::V2::ICompositeNode^ HV::V2::CompositeNode::Clone(HV::V2::IHandle^ contextHandle) {
	try {
		auto cloneObject = this->_instance->clone((hv::v2::ihandle* )contextHandle->Handle.ToPointer());
		return gcnew HV::V2::CompositeNode(System::IntPtr(& cloneObject), true);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

System::String^ HV::V2::CompositeNode::Name::get() {
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

std::size_t HV::V2::CompositeNode::Uid::get() {
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

int HV::V2::CompositeNode::Type::get() {
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

void HV::V2::CompositeNode::Init() {
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

System::IntPtr HV::V2::CompositeNode::Handle::get() {
	try {
		return System::IntPtr(this->_instance.pointer());
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

HV::V2::ResultType HV::V2::CompositeNode::Call() {
	try {
		return (HV::V2::ResultType)this->_instance->call();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}