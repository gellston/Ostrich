#pragma once

#include <iscript.h>


#include "IScript.h"
#include "managed_shared_ptr.h"




namespace HV {
	namespace V2 {
		public ref class Script : public HV::V2::IScript {
		private:

			HV::V2::mananged_shared_ptr<hv::v2::iscript> _instance;

			System::Collections::Generic::Dictionary<System::String^, HV::V2::IContext^>^ _managedContext;


		public:

			Script();
			!Script();
			~Script();

			virtual void RegisterProcessCompleteEvent(System::String^ context_name, HV::V2::IContext::OnProcessCompleteHandler^ eventHandler);
			virtual void RegisterConstChangedEvent(System::String^ context_name, HV::V2::IContext::OnConstChangedHandler^ eventHandler);
			virtual void RegisterProcessStartEvent(System::String^ context_name, HV::V2::IContext::OnProcessStartHandler^ eventHandler);
			virtual void RegisterErrorEvent(System::String^ context_name, HV::V2::IContext::OnErrorHandler^ eventHandler);


			virtual void ResetProcessCompleteEvent(System::String^ context_name);
			virtual void ResetConstChangedEvent(System::String^ context_name);
			virtual void ResetProcessStartEvent(System::String^ context_name);
			virtual void ResetErrorEvent(System::String^ context_name);




			virtual void UpdateAllConstNode(System::String^ context_name);


			virtual HV::V2::ICompositeNode^ Search(System::String^ context_name, std::size_t uid);
			virtual HV::V2::ICompositeNode^ Search(System::String^ context_name, System::String^ name);

			virtual bool CheckConnectability(System::String^ context_name, std::size_t sourceUID, System::String^ sourceName, std::size_t targetUID, System::String^ targetName);

			virtual void Connect(System::String^ context_name, std::size_t sourceUID, System::String^ sourceName, std::size_t targetUID, System::String^ targetName);
			virtual void Connect(System::String^ context_name, HV::V2::ICompositeNode^ sourceNode, System::String^ sourceName, HV::V2::ICompositeNode^ targetNode, System::String^ targetName);


			virtual void Disconnect(System::String^ context_name, System::String^ name);
			virtual void Disconnect(System::String^ context_name, std::size_t targetUID, System::String^ targetName);


			virtual void Disconnect(System::String^ context_name, HV::V2::ICompositeNode^ targetNode, System::String^ targetName);
			virtual void Disconnect(System::String^ context_name, std::size_t targetUID);
			virtual void Disconnect(System::String^ context_name, HV::V2::ICompositeNode^ targetNode);


			virtual HV::V2::ICompositeNode^ AddNode(System::String^ context_name, System::String^ name, int objectType);
			virtual void RemoveNode(System::String^ context_name, std::size_t uid);
			virtual void RemoveNode(System::String^ context_name, HV::V2::ICompositeNode^ node);
			virtual void RemoveNode(System::String^ context_name, System::String^ name);
			virtual HV::V2::IConstNode^ ConstNode(System::String^ context_name, std::size_t uid);


			virtual void Verification(System::String^ context_name);
			virtual void Clear(System::String^ context_name);
			virtual void Loadlibrary(System::String^ context_name);
			virtual void Unloadlibrary(System::String^ context_name);
			virtual void Loadlibrary();
			virtual void Unloadlibrary();


			virtual void SetAddonPath(System::String^ path);
			virtual System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ AddonInfo(System::String^ context_name);
			virtual System::Collections::Generic::List<IAddon^>^ Addons(System::String^ context_name);

			virtual property int ExecutionDelay {
				int get();
				void set(int);
			}


			virtual void Load(System::String^ context_name, System::String^ path);
			virtual void Save(System::String^ context_name, System::String^ path);
			virtual void InitNodes(System::String^ context_name);
			virtual void Run(System::String^ context_name, std::size_t uid);
			virtual void Run(System::String^ context_name, int objectType, System::String^ name);
			virtual void Run(System::String^ context_name);
			virtual void Stop(System::String^ context_name);

			virtual System::String^ Serialization(System::String^ context_name);
			virtual void DeSerialization(System::String^ context_name, System::String^ value);


			virtual HV::V2::IContext^ Context(System::String^ context_name);
			virtual void CreateContext(System::String^ context_name);
			virtual void RenameContext(System::String^ sourceName, System::String^ targetName);
			virtual void RemoveContext(System::String^ name);
			virtual void CopyContext(System::String^ sourceName, System::String^ targetName);

		};
	}
}