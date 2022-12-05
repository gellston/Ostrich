#pragma once


//C++ Header
#include <constNode.h>


//CLI Header
#include "IConstNode.h"
#include "managed_shared_ptr.h"


//C# NamgeSpace
using namespace System;


namespace HV {
	namespace V2 {
		public ref class ConstNode : public IConstNode {


		private:
			HV::V2::mananged_shared_ptr<hv::v2::iconstNode> _instance;

		public:

			ConstNode(System::IntPtr pointer, bool is_smart_pointer);

			~ConstNode();
			!ConstNode();


			virtual property System::String^ Name {
				System::String^ get();
			}


			virtual property std::size_t Uid {
				std::size_t get();
			}

			virtual property int Type {
				int get();
			}

			virtual void Init();


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

			virtual System::Object^ Clone();

			virtual property System::IntPtr Handle {
				System::IntPtr get();
			}


			virtual void RegisterMultipleSourceNode(std::size_t uid, System::String^ name);
			virtual void ClearMultipleSourceNode();
			virtual void UnRegisterMultipleSourceNode(std::size_t, System::String^ name);


			virtual property System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ MultipleSourceNode {
				System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ get();
				void set(System::Collections::Generic::List<System::Tuple<std::size_t, System::String^>^>^ nodes);
			}
			
		};
	}
}