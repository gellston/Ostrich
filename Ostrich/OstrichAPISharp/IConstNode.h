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

			virtual property int Index {
				int get();
			}

			virtual property std::size_t SourceUID {
				std::size_t get();
			}

			virtual property System::String^ SourceName {
				System::String^ get();
			}



			
		};
	}
}