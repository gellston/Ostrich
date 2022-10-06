#pragma once


#ifndef OSTRICH_CONSTCONSTRUCTOR
#define OSTRICH_CONSTCONSTRUCTOR


#include "iconstConstructor.h"
#include "commonException.h"

namespace hv {
	namespace v2 {
		template<typename T> class constConstructor : public hv::v2::iconstConstructor {
		public:

			constConstructor() {}
			virtual ~constConstructor() {}


			std::shared_ptr<hv::v2::iconstNode> create(std::string name) override {
				try {
					return std::dynamic_pointer_cast<hv::v2::iconstNode>(std::make_shared<T>(name));
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}


			hv::v2::constructorType type() override {
				return hv::v2::constructorType::constConstructor;
			}

		};
	}
}

#endif