#pragma once

#include <typeinfo>


using namespace System;


namespace HV {
	namespace V2 {
		public interface class IHandle : public IDisposable {
		public:

			virtual property System::IntPtr Handle {
				System::IntPtr get();
			}


		};
	}
}