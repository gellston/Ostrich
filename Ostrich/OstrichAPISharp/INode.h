#pragma once

#include <typeinfo>


#include "IHandle.h"


using namespace System;


namespace HV {
	namespace V2 {
		public interface class INode : public IHandle{
		public:


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


		};
	}
}