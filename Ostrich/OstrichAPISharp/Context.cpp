

#include <msclr/marshal_cppstd.h>



//C++/CLI Header
#include "Context.h"
#include "CommonException.h"
#include "CompositeNode.h"
#include "Addon.h"


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



System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ HV::V2::Context::AddonInfo::get() {

	try {
		System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ result = gcnew System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>();

		auto addoninfo = this->_instance->addonInfo();

		for (auto& info : addoninfo) {
			result->Add(gcnew System::Tuple<System::String^, System::String^>(gcnew System::String(std::get<0>(info).c_str()),
																		      gcnew System::String(std::get<0>(info).c_str())));

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

System::Collections::Generic::List<HV::V2::IAddon^>^ HV::V2::Context::Addons::get() {

	try {
		System::Collections::Generic::List<HV::V2::IAddon^>^ result = gcnew System::Collections::Generic::List<HV::V2::IAddon^>();

		auto addoninfo = this->_instance->addons();

		for (auto& info : addoninfo) {
			result->Add(gcnew HV::V2::Addon(System::IntPtr(&info), true));
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



void HV::V2::Context::Load(System::String^ path) {

	try {
		this->_instance->load(msclr::interop::marshal_as<std::string>(path));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Save(System::String^ path) {
	try {
		this->_instance->save(msclr::interop::marshal_as<std::string>(path));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::InitNodes() {
	try {
		this->_instance->initNodes();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Verification() {
	try {
		this->_instance->verification();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Clear() {
	try {
		this->_instance->clear();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Run(std::size_t uid) {
	try {
		this->_instance->run(uid);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Run(int objectType, System::String^ name) {
	try {
		this->_instance->run(objectType, msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Run() {
	try {
		this->_instance->run();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


System::String^ HV::V2::Context::Serialization() {
	try {
		auto jsonContent = this->_instance->serialization();
		return gcnew System::String(jsonContent.c_str());
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::DeSerialization(System::String^ value) {
	try {
		this->_instance->deserialization(msclr::interop::marshal_as<std::string>(value));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
HV::V2::ICompositeNode^ HV::V2::Context::Search(std::size_t uid) {
	try {
		auto node = this->_instance->search(uid);


		return gcnew HV::V2::CompositeNode(System::IntPtr(&node), true);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
HV::V2::ICompositeNode^ HV::V2::Context::Search(System::String^ name) {
	try {
		auto node = this->_instance->search(msclr::interop::marshal_as<std::string>(name));


		return gcnew HV::V2::CompositeNode(System::IntPtr(&node), true);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}




void HV::V2::Context::Connect(std::size_t sourceUID, System::String^ sourceName, std::size_t targetUID, System::String^ targetName) {
	try {
		this->_instance->connect(sourceUID, msclr::interop::marshal_as<std::string>(sourceName),
			targetUID, msclr::interop::marshal_as<std::string>(targetName));

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Connect(HV::V2::ICompositeNode^ sourceNode, System::String^ sourceName, HV::V2::ICompositeNode^ targetNode, System::String^ targetName) {
	try {

		auto nativeSourceNode = *((std::shared_ptr<hv::v2::icompositeNode> *)sourceNode->Handle.ToPointer());
		auto nativeTargetNode = *((std::shared_ptr<hv::v2::icompositeNode> *)targetNode->Handle.ToPointer());

		this->_instance->connect(nativeSourceNode, msclr::interop::marshal_as<std::string>(sourceName),
							     nativeTargetNode, msclr::interop::marshal_as<std::string>(targetName));

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}




void HV::V2::Context::Disconnect(System::String^ name) {
	try {

		this->_instance->disconnect(msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Disconnect(std::size_t targetUID, System::String^ targetName) {
	try {

		this->_instance->disconnect(targetUID, msclr::interop::marshal_as<std::string>(targetName));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Disconnect(HV::V2::ICompositeNode^ targetNode, System::String^ targetName) {
	try {
		auto nativeTargetNode = *((std::shared_ptr<hv::v2::icompositeNode>*)targetNode->Handle.ToPointer());
		this->_instance->disconnect(nativeTargetNode, msclr::interop::marshal_as<std::string>(targetName));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Disconnect(std::size_t targetUID) {
	try {
		this->_instance->disconnect(targetUID);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::Disconnect(HV::V2::ICompositeNode^ targetNode) {
	try {
		auto nativeTargetNode = *((std::shared_ptr<hv::v2::icompositeNode>*)targetNode->Handle.ToPointer());
		this->_instance->disconnect(nativeTargetNode);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}




HV::V2::ICompositeNode^ HV::V2::Context::AddNode(System::String^ name, int objectType) {
	try {
		auto node = this->_instance->addNode(msclr::interop::marshal_as<std::string>(name), objectType);

		return gcnew HV::V2::CompositeNode(System::IntPtr(&node), true);

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::RemoveNode(std::size_t uid) {
	try {
		this->_instance->removeNode(uid);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::RemoveNode(HV::V2::ICompositeNode^ node) {
	try {
		auto nativeNode = *((std::shared_ptr<hv::v2::icompositeNode>*)node->Handle.ToPointer());
		this->_instance->removeNode(nativeNode);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
void HV::V2::Context::RemoveNode(System::String^ name) {
	try {
		this->_instance->removeNode(msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


System::Object^ HV::V2::Context::Clone() {
	try {
		auto _context = this->_instance->clone();
		auto managedContext = gcnew HV::V2::Context(System::IntPtr(&_context), true);
		return managedContext;
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}