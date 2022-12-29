#pragma once

#include <typeinfo>


#include "IHandle.h"
#include "IAddon.h"
#include "IConstNode.h"

using namespace System;


namespace HV {
	namespace V2 {

		public interface class IContext : public IHandle, public ICloneable, public System::IDisposable{


		public:


			virtual property System::IntPtr Handle {
				System::IntPtr get();
			}

			virtual System::Object^ Clone();




			//Event Callback
			delegate void OnProcessCompleteEventCallback(int nodeType, std::size_t composite_uid);
			delegate void OnConstChangedEventCallback(std::size_t constUID);
			delegate void OnProcessStartEventCallback(int nodeType, std::size_t composite_uid);


			//Event Handler
			delegate void OnProcessCompleteHandler(System::Object^ sender, int nodeType, std::size_t compositeUID);
			delegate void OnConstChangedHandler(System::Object^ sender, std::size_t constUID);
			delegate void OnProcessStartHandler(System::Object^ sender, int nodeType, std::size_t compositeUID);



			event OnProcessCompleteHandler^ OnProcessComplete;
			event OnConstChangedHandler^ OnConstChanged;
			event OnProcessStartHandler^ OnProcessStart;



			virtual void RegisterProcessCompleteEvent(OnProcessCompleteHandler^ eventHandler);
			virtual void RegisterConstChangedEvent(OnConstChangedHandler^ eventHandler);
			virtual void RegisterProcessStartEvent(OnProcessStartHandler^ eventHandler);

			virtual void ResetProcessCompleteEvent(OnProcessCompleteHandler^ eventHandler);
			virtual void ResetConstChangedEvent(OnConstChangedHandler^ eventHandler);
			virtual void ResetProcessStartEvent(OnProcessStartHandler^ eventHandler);




			virtual void Loadlibrary();
			virtual void Unloadlibrary();
			virtual void SetAddonPath(System::String^ path);
			virtual property System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ AddonInfo{
				System::Collections::Generic::List<System::Tuple<System::String^, System::String^>^>^ get();
			}
			virtual property System::Collections::Generic::List<IAddon^>^ Addons {
				System::Collections::Generic::List<IAddon^>^ get();
			}
			
			virtual property int ExecutionDelay {
				int get();
				void set(int);
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
			virtual HV::V2::IConstNode^ ConstNode(std::size_t uid);

		};
	}
}