
#include <msclr/marshal_cppstd.h>



//C++/CLI Header
#include "Script.h"
#include "CommonException.h"
#include "CompositeNode.h"
#include "Addon.h"

//C++ Header
#include <commonException.h>
#include <script.h>



HV::V2::Script::Script() {
	try {
		auto nativePointer = std::make_shared<hv::v2::script>();
		auto castedNativePointer = std::dynamic_pointer_cast<hv::v2::iscript>(nativePointer);
		this->_instance = castedNativePointer;
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

HV::V2::Script::~Script() {
	this->!Script();
}

HV::V2::Script::!Script() {
	this->_instance.reset();
}


HV::V2::ICompositeNode^ HV::V2::Script::Search(System::String^ context_name, std::size_t uid) {
	try {
		auto node = this->_instance->search(msclr::interop::marshal_as<std::string>(context_name), uid);
		return gcnew HV::V2::CompositeNode(System::IntPtr(&node), true);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}
HV::V2::ICompositeNode^ HV::V2::Script::Search(System::String^ context_name, System::String^ name) {
	try {
		auto node = this->_instance->search(msclr::interop::marshal_as<std::string>(context_name), 
											msclr::interop::marshal_as<std::string>(name));
		return gcnew HV::V2::CompositeNode(System::IntPtr(&node), true);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


void HV::V2::Script::Connect(System::String^ context_name, std::size_t sourceUID, System::String^ sourceName, std::size_t targetUID, System::String^ targetName) {
	try {
		this->_instance->connect(msclr::interop::marshal_as<std::string>(context_name),
								 sourceUID,
								 msclr::interop::marshal_as<std::string>(sourceName),
								 targetUID,
								 msclr::interop::marshal_as<std::string>(targetName));
	
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Connect(System::String^ context_name, HV::V2::ICompositeNode^ sourceNode, System::String^ sourceName, HV::V2::ICompositeNode^ targetNode, System::String^ targetName) {
	try {

		auto nativeSourceNode = *((std::shared_ptr<hv::v2::icompositeNode>*)sourceNode->Handle.ToPointer());
		auto nativeTargetNode = *((std::shared_ptr<hv::v2::icompositeNode>*)targetNode->Handle.ToPointer());

		this->_instance->connect(msclr::interop::marshal_as<std::string>(context_name),
								 nativeSourceNode,
								 msclr::interop::marshal_as<std::string>(sourceName),
								 nativeTargetNode,
								 msclr::interop::marshal_as<std::string>(targetName));

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}



void HV::V2::Script::Disconnect(System::String^ context_name, System::String^ name) {
	try {

		this->_instance->disconnect(msclr::interop::marshal_as<std::string>(context_name),
								    msclr::interop::marshal_as<std::string>(name));

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Disconnect(System::String^ context_name, std::size_t targetUID, System::String^ targetName) {
	try {

		this->_instance->disconnect(msclr::interop::marshal_as<std::string>(context_name),
								    targetUID,
									msclr::interop::marshal_as<std::string>(targetName));

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}



void HV::V2::Script::Disconnect(System::String^ context_name, HV::V2::ICompositeNode^ targetNode, System::String^ targetName) {
	try {
		auto nativeNode = *((std::shared_ptr<hv::v2::icompositeNode>*) targetNode->Handle.ToPointer());
		this->_instance->disconnect(msclr::interop::marshal_as<std::string>(context_name),
									nativeNode,
									msclr::interop::marshal_as<std::string>(targetName));

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Disconnect(System::String^ context_name, std::size_t targetUID) {
	try {
		this->_instance->disconnect(msclr::interop::marshal_as<std::string>(context_name), targetUID);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Disconnect(System::String^ context_name, HV::V2::ICompositeNode^ targetNode) {
	try {
		auto nativeNode = *((std::shared_ptr<hv::v2::icompositeNode> *) targetNode->Handle.ToPointer());
		this->_instance->disconnect(msclr::interop::marshal_as<std::string>(context_name), nativeNode);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}



HV::V2::ICompositeNode^ HV::V2::Script::AddNode(System::String^ context_name, System::String^ name, int objectType) {
	try {
		auto node = this->_instance->addNode(msclr::interop::marshal_as<std::string>(context_name),
											 msclr::interop::marshal_as<std::string>(name),
											 objectType);

		return gcnew HV::V2::CompositeNode(System::IntPtr(&node), true);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::RemoveNode(System::String^ context_name, std::size_t uid) {
	try {
		this->_instance->removeNode(msclr::interop::marshal_as<std::string>(context_name), uid);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::RemoveNode(System::String^ context_name, HV::V2::ICompositeNode^ node) {
	try {
		
		auto nativeNode = *(std::shared_ptr<hv::v2::icompositeNode>*)node->Handle.ToPointer();
		this->_instance->removeNode(msclr::interop::marshal_as<std::string>(context_name), nativeNode);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::RemoveNode(System::String^ context_name, System::String^ name) {
	try {
		this->_instance->removeNode(msclr::interop::marshal_as<std::string>(context_name),
									msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}



void HV::V2::Script::Verification(System::String^ context_name) {
	try {
		this->_instance->verification(msclr::interop::marshal_as<std::string>(context_name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Clear(System::String^ context_name) {
	try {
		this->_instance->clear(msclr::interop::marshal_as<std::string>(context_name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Loadlibrary(System::String^ context_name) {
	try {
		this->_instance->loadLibrary(msclr::interop::marshal_as<std::string>(context_name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Unloadlibrary(System::String^ context_name) {
	try {
		this->_instance->unloadLibrary(msclr::interop::marshal_as<std::string>(context_name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Loadlibrary() {
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

void HV::V2::Script::Unloadlibrary() {
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



void HV::V2::Script::SetAddonPath(System::String^ path) {
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

System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ HV::V2::Script::AddonInfo(System::String^ context_name) {
	try {
		System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ result;
		auto nativeResult = this->_instance->addonInfo(msclr::interop::marshal_as<std::string>(context_name));
		for (auto& addonInfo : nativeResult) {
			result->Add(gcnew System::Tuple<System::String^, System::String^>(
				gcnew System::String(std::get<0>(addonInfo).c_str()),
				gcnew System::String(std::get<1>(addonInfo).c_str())
			));
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

System::Collections::Generic::List<HV::V2::IAddon^>^ HV::V2::Script::Addons(System::String^ context_name) {
	try {
		System::Collections::Generic::List<HV::V2::IAddon^>^ result;
		auto nativeResult = this->_instance->addons(msclr::interop::marshal_as<std::string>(context_name));
		for (auto& addon : nativeResult) {
			result->Add(gcnew HV::V2::Addon(System::IntPtr(&addon), true));
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




void HV::V2::Script::Load(System::String^ context_name, System::String^ path) {
	try {
		this->_instance->load(msclr::interop::marshal_as<std::string>(context_name),
			msclr::interop::marshal_as<std::string>(path));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Save(System::String^ context_name, System::String^ path) {
	try {
		this->_instance->save(msclr::interop::marshal_as<std::string>(context_name),
			msclr::interop::marshal_as<std::string>(path));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::InitNodes(System::String^ context_name) {
	try {
		this->_instance->initNodes(msclr::interop::marshal_as<std::string>(context_name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Run(System::String^ context_name, std::size_t uid) {
	try {
		this->_instance->run(msclr::interop::marshal_as<std::string>(context_name), uid);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Run(System::String^ context_name, int objectType, System::String^ name) {
	try {
		this->_instance->run(msclr::interop::marshal_as<std::string>(context_name), 
							 objectType,
							 msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::Run(System::String^ context_name) {
	try {
		this->_instance->run(msclr::interop::marshal_as<std::string>(context_name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}



System::String^ HV::V2::Script::Serialization(System::String^ context_name) {
	try {
		auto nativeJsonContext = this->_instance->serialization(msclr::interop::marshal_as<std::string>(context_name));
		return gcnew System::String(nativeJsonContext.c_str());
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::DeSerialization(System::String^ context_name, System::String^ value) {
	try {
		this->_instance->deserialization(msclr::interop::marshal_as<std::string>(context_name),
			msclr::interop::marshal_as<std::string>(value));

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


void HV::V2::Script::CreateContext(System::String^ context_name) {
	try {
		this->_instance->createContext(msclr::interop::marshal_as<std::string>(context_name));

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::RenameContext(System::String^ sourceName, System::String^ targetName) {
	try {
		this->_instance->renameContext(msclr::interop::marshal_as<std::string>(sourceName),
									   msclr::interop::marshal_as<std::string>(targetName));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::RemoveContext(System::String^ name) {
	try {
		this->_instance->removeContext(msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Script::CopyContext(System::String^ sourceName, System::String^ targetName) {
	try {
		this->_instance->copyContext(msclr::interop::marshal_as<std::string>(sourceName),
									 msclr::interop::marshal_as<std::string>(targetName));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}