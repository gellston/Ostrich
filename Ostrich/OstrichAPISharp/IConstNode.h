#pragma once



#include "INode.h"


using namespace System;


namespace HV {
	namespace V2 {
		public interface class IConstNode : public INode, public ICloneable{
		public:

			virtual property bool IsConnected {
				bool get();
			}

			virtual property bool IsMultiple {
				bool get();
			}

			virtual property int Index {
				int get();
			}

			virtual property std::size_t SourceUID {
				std::size_t get();
			}

			virtual property System::String^ SourceName {
				System::String^ get();
			}


			virtual void RegisterMultipleSourceNode(std::size_t uid, System::String^ name);
			virtual void ClearMultipleSourceNode();
			virtual void UnRegisterMultipleSourceNode(std::size_t uid, System::String^ name);
			virtual void UnRegisterMultipleSourceNode(std::size_t uid);

			virtual property System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ MultipleSourceNode {
				System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ get();
				void set(System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ nodes);
			}
			
			
		};
	}
}