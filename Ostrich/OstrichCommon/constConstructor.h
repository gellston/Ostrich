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
					return std::make_shared<hv::v2::iconstNode>(new T(name));
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