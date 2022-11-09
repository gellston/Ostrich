#pragma once

#include <typeinfo>


#include "IHandle.h"
#include "IAddon.h"

using namespace System;


namespace HV {
	namespace V2 {

		public interface class IContext : public IHandle, public ICloneable {
		public:


			virtual property System::IntPtr Handle {
				System::IntPtr get();
			}

			virtual void Loadlibrary();
			virtual void Unloadlibrary();
			virtual void SetAddonPath(System::String^ path);
			virtual property System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ AddonInfo{
				System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ get();
			}
			virtual property System::Collections::Generic::List<IAddon^>^ Addons {
				System::Collections::Generic::List<IAddon^>^ get();
			}


			virtual void Load(System::String^ path);
			virtual void Save(System::String^ path);
			virtual void InitNodes();
			virtual void Verification();
			virtual void Clear();
			virtual void Run(std::size_t uid);
			virtual void Run(int objectType, System::String^ name);
			virtual void Run();


			virtual System::String^ Serialization();
			virtual void DeSerialization(System::String^ value);
			//Clone Here

			virtual HV::V2::ICompositeNode^ Search(std::size_t uid);
			virtual HV::V2::ICompositeNode^ Search(System::String^ name);


			virtual bool CheckConnectability(std::size_t sourceUID, System::String^ sourceName, std::size_t targetUID, System::String^ targetName);
			virtual void Connect(std::size_t sourceUID, System::String^ sourceName, std::size_t targetUID, System::String^ targetName);
			virtual void Connect(HV::V2::ICompositeNode^ sourceNode, System::String^ sourceName, HV::V2::ICompositeNode^ targetNode, System::String^ targetName);


			virtual void Disconnect(System::String^ name);
			virtual void Disconnect(std::size_t targetUID, System::String^ targetName);
			
			
			virtual void Disconnect(HV::V2::ICompositeNode^ targetNode, System::String^ targetName);
			virtual void Disconnect(std::size_t targetUID);
			virtual void Disconnect(HV::V2::ICompositeNode^ targetNode);


			virtual HV::V2::ICompositeNode^ AddNode(System::String^ name, int objectType);
			
			virtual void RemoveNode(std::size_t uid);
			virtual void RemoveNode(HV::V2::ICompositeNode^ node);
			virtual void RemoveNode(System::String^ name);


		};
	}
}