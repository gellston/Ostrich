#pragma once


#include <nodeInfo.h>



#include "ICompositeNode.h"
#include "managed_shared_ptr.h"


namespace HV {
	namespace V2 {
		public ref class NodeInfo : public IDisposable {
		private:
			
			HV::V2::mananged_shared_ptr<hv::v2::nodeInfo> _instance;

		public:


			NodeInfo(System::IntPtr pointer, bool is_smart_pointer);
			~NodeInfo();
			!NodeInfo();

			property System::String^ Name {
				System::String^ get();
			}

			property System::String^ Category {
				System::String^ get();
			}

			property int Type {
				int get();
			}
		};
	}
}