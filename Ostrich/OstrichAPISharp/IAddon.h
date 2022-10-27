#pragma once


#include "NodeInfo.h"


namespace HV {
	namespace V2 {
		public interface class IAddon : public IDisposable {
		public:

			virtual bool Exist(int type);


			virtual property System::Collections::Generic::List<NodeInfo^>^ Information {
				System::Collections::Generic::List<NodeInfo^>^ get();
			}
		};
	}
}
