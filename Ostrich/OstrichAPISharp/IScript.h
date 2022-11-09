#pragma once

#include "ICompositeNode.h"
#include "IAddon.h"



namespace HV {
	namespace V2 {
		public interface class IScript : System::IDisposable {

		public:


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


			virtual void Verification(System::String^ context_name);
			virtual void Clear(System::String^ context_name);
			virtual void Loadlibrary(System::String^ context_name);
			virtual void Unloadlibrary(System::String^ context_name);
			virtual void Loadlibrary();
			virtual void Unloadlibrary();


			virtual void SetAddonPath(System::String^ path);
			virtual System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ AddonInfo(System::String^ context_name);
			virtual System::Collections::Generic::List<IAddon^>^ Addons(System::String^ context_name);



			virtual void Load(System::String^ context_name, System::String^ path);
			virtual void Save(System::String^ context_name, System::String^ path);
			virtual void InitNodes(System::String^ context_name);
			virtual void Run(System::String^ context_name, std::size_t uid);
			virtual void Run(System::String^ context_name, int objectType, System::String^ name);
			virtual void Run(System::String^ context_name);


			virtual System::String^ Serialization(System::String^ context_name);
			virtual void DeSerialization(System::String^ context_name, System::String^ value);
			
			virtual void CreateContext(System::String^ context_name);
			virtual void RenameContext(System::String^ sourceName, System::String^ targetName);
			virtual void RemoveContext(System::String^ name);
			virtual void CopyContext(System::String^ sourceName, System::String^ targetName);

		};
	}
}