#pragma once


#include <iaddon.h>



#include "IAddon.h"
#include "managed_shared_ptr.h"

namespace HV {
	namespace V2 {
		public ref class Addon : public IAddon {
		private:
			HV::V2::mananged_shared_ptr<hv::v2::iaddon> _instance;
		public:

			Addon(System::IntPtr instance, bool is_smart_pointer);
			~Addon();
			!Addon();

			virtual bool Exist(int type);

			virtual property System::Collections::Generic::List<HV::V2::NodeInfo^>^ Information {
				System::Collections::Generic::List<HV::V2::NodeInfo^>^ get();
			}
		};
	}
}