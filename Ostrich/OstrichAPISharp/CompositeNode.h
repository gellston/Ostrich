#pragma once


#include <icompositeNode.h>



#include "ICompositeNode.h"
#include "managed_shared_ptr.h"





namespace HV {
	namespace V2 {
		public ref class CompositeNode : public ICompositeNode {
		private:
			HV::V2::mananged_shared_ptr<hv::v2::icompositeNode> _instance;
		public:
			CompositeNode(IntPtr _pointer, bool is_smart_pointer);
			~CompositeNode();
			!CompositeNode();


			virtual property int Depth {
				int get();
			}

			virtual property bool IsConnected {
				bool get();
			}

			virtual bool CheckSourceUID(std::size_t uid);

			virtual property bool IsConditionalNode {
				bool get();
			}

			virtual property bool IsFreezed {
				bool get();
				void set(bool value);
			}

			virtual property bool IsEventNode {
				bool get();
			}


			virtual property System::Collections::Generic::List<HV::V2::IConstNode^>^ Inputs {
				System::Collections::Generic::List<HV::V2::IConstNode^>^ get();
			}

			virtual property System::Collections::Generic::List<HV::V2::IConstNode^>^ Outputs {
				System::Collections::Generic::List<HV::V2::IConstNode^>^ get();
			}

			virtual HV::V2::IConstNode^ Input(System::String^ key);
			virtual HV::V2::IConstNode^ Output(System::String^ key);


			virtual void ReplaceInputs(System::Collections::Generic::List<HV::V2::IConstNode^>^ inputs);
			virtual void ReplaceOutputs(System::Collections::Generic::List<HV::V2::IConstNode^>^ inputs);

			virtual property System::Collections::Generic::List<HV::V2::IConstNode^>^ InputClone {
				System::Collections::Generic::List<HV::V2::IConstNode^>^ get();
			}
			virtual property System::Collections::Generic::List<HV::V2::IConstNode^>^ OutputClone {
				System::Collections::Generic::List<HV::V2::IConstNode^>^ get();
			}


			virtual property System::Collections::Generic::List<std::size_t>^ ConstUID {
				System::Collections::Generic::List<std::size_t>^ get();
			}
			virtual property System::Collections::Generic::List<std::size_t>^ InputConstUID {
				System::Collections::Generic::List<std::size_t>^ get();
			}
			virtual property System::Collections::Generic::List<std::size_t>^ OutputConstUID {
				System::Collections::Generic::List<std::size_t>^ get();
			}


			virtual HV::V2::ResultType Process();
			virtual void Update();


			virtual HV::V2::ICompositeNode^ Clone(HV::V2::IHandle^ contextHandle);


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


			virtual property System::IntPtr Handle {
				System::IntPtr get();
			}

			virtual HV::V2::ResultType Call();

		};
	}
}