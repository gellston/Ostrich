#pragma once


#include <icontext.h>




#include "IContext.h"
#include "managed_shared_ptr.h"





namespace HV {
	namespace V2 {

		public ref class Context : public HV::V2::IContext {
		private:
			HV::V2::mananged_shared_ptr<hv::v2::icontext> _instance;


			void NativeProcessCompleteEvent(int nodeType, std::size_t composite_uid);
			void NativeConstChangedEvent(std::size_t constUID);


			System::Runtime::InteropServices::GCHandle ProcessCompleteEventGCHandle;
			System::Runtime::InteropServices::GCHandle ConstChangedEventGCHandle;




		public:



			virtual event HV::V2::IContext::OnProcessCompleteHandler^ OnProcessComplete;
			virtual event HV::V2::IContext::OnConstChangedHandler^ OnConstChanged;


			virtual void RegisterProcessCompleteEvent(HV::V2::IContext::OnProcessCompleteHandler^ eventHandler);
			virtual void RegisterConstChangedEvent(HV::V2::IContext::OnConstChangedHandler^ eventHandler);

			virtual void ResetProcessCompleteEvent(HV::V2::IContext::OnProcessCompleteHandler^ eventHandler);
			virtual void ResetConstChangedEvent(HV::V2::IContext::OnConstChangedHandler^ eventHandler);


			Context(System::IntPtr _pointer, bool is_smart_pointer);
			~Context();
			!Context();



			virtual property System::IntPtr Handle {
				System::IntPtr get();
			}





			virtual void Loadlibrary();
			virtual void Unloadlibrary();
			virtual void SetAddonPath(System::String^ path);
			virtual property System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ AddonInfo {
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
			virtual System::Object^ Clone();

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