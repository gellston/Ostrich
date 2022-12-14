
#include <msclr/marshal_cppstd.h>

//C++/CLI Header
#include "Diagram.h"
#include "CommonException.h"
#include "CompositeNode.h"
#include "Addon.h"
#include "Context.h"
#include "ConstNode.h"

//C++ Header
#include <commonException.h>
#include <diagram.h>



HV::V2::Diagram::Diagram() {
	try {
		auto nativePointer = std::make_shared<hv::v2::diagram>();
		auto castedNativePointer = std::dynamic_pointer_cast<hv::v2::idiagram>(nativePointer);
		this->_instance = castedNativePointer;


		this->_managedContext = gcnew System::Collections::Generic::Dictionary<System::String^, HV::V2::IContext^>();

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

HV::V2::Diagram::~Diagram() {


	this->!Diagram();
}

HV::V2::Diagram::!Diagram() {

	for each (auto keyPair in this->_managedContext)
	{
		HV::V2::IContext^ context = keyPair.Value;
		context->ResetConstChangedEvent();
		context->ResetProcessStartEvent();
		context->ResetProcessCompleteEvent();

		delete context;
	}

	this->_managedContext->Clear();
	this->_instance.~mananged_shared_ptr();
}



void HV::V2::Diagram::RegisterProcessCompleteEvent(System::String^ context_name, HV::V2::IContext::OnProcessCompleteHandler^ eventHandler) {
	try {
		if (this->_managedContext->ContainsKey(context_name) == false) {
			auto nativeContext = this->_instance->context(msclr::interop::marshal_as<std::string>(context_name));
			auto managedContext = gcnew HV::V2::Context(System::IntPtr(&nativeContext), true);
			this->_managedContext->Add(context_name, managedContext);
		}

		this->_managedContext[context_name]->RegisterProcessCompleteEvent(eventHandler);

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}

}

void HV::V2::Diagram::RegisterProcessStartEvent(System::String^ context_name, HV::V2::IContext::OnProcessStartHandler^ eventHandler) {
	try {
		if (this->_managedContext->ContainsKey(context_name) == false) {
			auto nativeContext = this->_instance->context(msclr::interop::marshal_as<std::string>(context_name));
			auto managedContext = gcnew HV::V2::Context(System::IntPtr(&nativeContext), true);
			this->_managedContext->Add(context_name, managedContext);
		}

		this->_managedContext[context_name]->RegisterProcessStartEvent(eventHandler);

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


void HV::V2::Diagram::RegisterConstChangedEvent(System::String^ context_name, HV::V2::IContext::OnConstChangedHandler^ eventHandler) {
	try {
		if (this->_managedContext->ContainsKey(context_name) == false) {
			auto nativeContext = this->_instance->context(msclr::interop::marshal_as<std::string>(context_name));
			auto managedContext = gcnew HV::V2::Context(System::IntPtr(&nativeContext), true);
			this->_managedContext->Add(context_name, managedContext);
		}

		this->_managedContext[context_name]->RegisterConstChangedEvent(eventHandler);

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


void HV::V2::Diagram::RegisterErrorEvent(System::String^ context_name, HV::V2::IContext::OnErrorHandler^ eventHandler) {
	try {
		if (this->_managedContext->ContainsKey(context_name) == false) {
			auto nativeContext = this->_instance->context(msclr::interop::marshal_as<std::string>(context_name));
			auto managedContext = gcnew HV::V2::Context(System::IntPtr(&nativeContext), true);
			this->_managedContext->Add(context_name, managedContext);
		}

		this->_managedContext[context_name]->RegisterErrorEvent(eventHandler);

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


void HV::V2::Diagram::ResetProcessCompleteEvent(System::String^ context_name) {
	try {

		this->_managedContext[context_name]->ResetProcessCompleteEvent();

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Diagram::ResetConstChangedEvent(System::String^ context_name) {
	try {

		this->_managedContext[context_name]->ResetConstChangedEvent();

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Diagram::ResetProcessStartEvent(System::String^ context_name) {
	try {

		this->_managedContext[context_name]->ResetProcessStartEvent();

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Diagram::ResetErrorEvent(System::String^ context_name) {
	try {

		this->_managedContext[context_name]->ResetErrorEvent();

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Diagram::UpdateAllConstNode(System::String^ context_name) {

	try {

		if (this->_managedContext->ContainsKey(context_name) == false) {
			auto nativeContext = this->_instance->context(msclr::interop::marshal_as<std::string>(context_name));
			auto managedContext = gcnew HV::V2::Context(System::IntPtr(&nativeContext), true);
			this->_managedContext->Add(context_name, managedContext);
		}

		this->_managedContext[context_name]->UpdateAllConstNode();

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}




HV::V2::ICompositeNode^ HV::V2::Diagram::Search(System::String^ context_name, std::size_t uid) {
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
HV::V2::ICompositeNode^ HV::V2::Diagram::Search(System::String^ context_name, System::String^ name) {
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

bool HV::V2::Diagram::CheckConnectability(System::String^ context_name, std::size_t sourceUID, System::String^ sourceName, std::size_t targetUID, System::String^ targetName) {
	try {
		return this->_instance->checkConnectability(msclr::interop::marshal_as<std::string>(context_name),
													sourceUID,
													msclr::interop::marshal_as<std::string>(sourceName),
													targetUID,
													msclr::interop::marshal_as<std::string>(targetName));

	}
	catch (hv::v2::oexception e) {
		return false;
	}
	catch (std::exception e) {
		return false;
	}
}



void HV::V2::Diagram::Connect(System::String^ context_name, std::size_t sourceUID, System::String^ sourceName, std::size_t targetUID, System::String^ targetName) {
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

void HV::V2::Diagram::Connect(System::String^ context_name, HV::V2::ICompositeNode^ sourceNode, System::String^ sourceName, HV::V2::ICompositeNode^ targetNode, System::String^ targetName) {
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



void HV::V2::Diagram::Disconnect(System::String^ context_name, System::String^ name) {
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

void HV::V2::Diagram::Disconnect(System::String^ context_name, std::size_t targetUID, System::String^ targetName) {
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



void HV::V2::Diagram::Disconnect(System::String^ context_name, HV::V2::ICompositeNode^ targetNode, System::String^ targetName) {
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

void HV::V2::Diagram::Disconnect(System::String^ context_name, std::size_t targetUID) {
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

void HV::V2::Diagram::Disconnect(System::String^ context_name, HV::V2::ICompositeNode^ targetNode) {
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



HV::V2::ICompositeNode^ HV::V2::Diagram::AddNode(System::String^ context_name, System::String^ name, int objectType) {
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

int HV::V2::Diagram::ExecutionDelay::get() {
	try {
		return this->_instance->executionDelay();
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Diagram::ExecutionDelay::set(int ms) {
	try {
		this->_instance->executionDelay(ms);
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


void HV::V2::Diagram::RemoveNode(System::String^ context_name, std::size_t uid) {
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

void HV::V2::Diagram::RemoveNode(System::String^ context_name, HV::V2::ICompositeNode^ node) {
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

void HV::V2::Diagram::RemoveNode(System::String^ context_name, System::String^ name) {
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

HV::V2::IConstNode^ HV::V2::Diagram::ConstNode(System::String^ context_name, std::size_t uid) {
	try {
		auto nativeConstNode = this->_instance->constNode(msclr::interop::marshal_as<std::string>(context_name),
													      uid);

		auto managedConstNode = gcnew HV::V2::ConstNode(System::IntPtr(&nativeConstNode), true);
		return managedConstNode;
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}



void HV::V2::Diagram::Verification(System::String^ context_name) {
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

void HV::V2::Diagram::Clear(System::String^ context_name) {
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

void HV::V2::Diagram::Loadlibrary(System::String^ context_name) {
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

void HV::V2::Diagram::Unloadlibrary(System::String^ context_name) {
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

void HV::V2::Diagram::Loadlibrary() {
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

void HV::V2::Diagram::Unloadlibrary() {
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



void HV::V2::Diagram::SetAddonPath(System::String^ path) {
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

System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ HV::V2::Diagram::AddonInfo(System::String^ context_name) {
	try {
		System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ result = gcnew System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>();
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

System::Collections::Generic::List<HV::V2::IAddon^>^ HV::V2::Diagram::Addons(System::String^ context_name) {
	try {
		System::Collections::Generic::List<HV::V2::IAddon^>^ result = gcnew System::Collections::Generic::List<HV::V2::IAddon^>();
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




void HV::V2::Diagram::Load(System::String^ context_name, System::String^ path) {
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

void HV::V2::Diagram::Save(System::String^ context_name, System::String^ path) {
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

void HV::V2::Diagram::InitNodes(System::String^ context_name) {
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

void HV::V2::Diagram::Run(System::String^ context_name, std::size_t uid) {
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

void HV::V2::Diagram::Run(System::String^ context_name, int objectType, System::String^ name) {
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

void HV::V2::Diagram::Run(System::String^ context_name) {
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

void HV::V2::Diagram::Stop(System::String^ context_name) {
	try {
		this->_instance->stop(msclr::interop::marshal_as<std::string>(context_name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}


System::String^ HV::V2::Diagram::Serialization(System::String^ context_name) {
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

void HV::V2::Diagram::DeSerialization(System::String^ context_name, System::String^ value) {
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






HV::V2::IContext^ HV::V2::Diagram::Context(System::String^ context_name) {
	try {

		auto context = this->_instance->context(msclr::interop::marshal_as<std::string>(context_name));

		auto managedContext = gcnew HV::V2::Context(System::IntPtr(&context), true);

		return managedContext;

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}




void HV::V2::Diagram::CreateContext(System::String^ context_name) {
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

void HV::V2::Diagram::RenameContext(System::String^ sourceName, System::String^ targetName) {
	try {

		this->_instance->renameContext(msclr::interop::marshal_as<std::string>(sourceName),
									   msclr::interop::marshal_as<std::string>(targetName));

		auto context = this->_managedContext[sourceName];
		this->_managedContext->Remove(sourceName);
		this->_managedContext->Add(targetName, context);

	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Diagram::RemoveContext(System::String^ name) {
	try {
		if (this->_managedContext->ContainsKey(name) == true) {
			this->_managedContext[name]->~IContext();
			this->_managedContext->Remove(name);
		}
		this->_instance->removeContext(msclr::interop::marshal_as<std::string>(name));
	}
	catch (hv::v2::oexception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew HV::V2::OException(gcnew System::String(e.what()));
	}
}

void HV::V2::Diagram::CopyContext(System::String^ sourceName, System::String^ targetName) {
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
