#pragma once

#include <typeinfo>


#include "INode.h"
#include "IRunable.h"
#include "IConstNode.h"


using namespace System::ComponentModel;
using namespace System::Collections;



namespace HV {
	namespace V2 {
		public interface class ICompositeNode : public INode, public IRunable{
		public:

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
			virtual void UpdateConst(int nodeType, std::size_t uid);

			
			virtual HV::V2::ICompositeNode^ Clone(HV::V2::IHandle^ contextHandle);

			virtual HV::V2::ResultType Call();
		};
	}
}