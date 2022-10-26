#pragma once

namespace HV {
	namespace V2 {
		public ref class OException : public System::Exception {
		
		public:
			OException(System::String^ context);

		};
	}
}