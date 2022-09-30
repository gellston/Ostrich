#pragma once


#ifndef OSTRICH_ADDON
#define OSTRICH_ADDON


#include "iaddon.h"

#include "varConstructor.h"
#include "nodeInfo.h"
#include "constConstructor.h"


namespace hv {
	namespace v2 {
		class impl_addon;
		class addon : public hv::v2::iaddon {
		private:
			std::unique_ptr<hv::v2::impl_addon> _instance;

		protected:

			OSTRICH_COMMON_API void varConstructor(int type, std::shared_ptr<hv::v2::ivarConstructor> _constructor);
			OSTRICH_COMMON_API void constConstructor(int type, std::shared_ptr<hv::v2::iconstConstructor> _constructor);
			OSTRICH_COMMON_API void information(std::shared_ptr<hv::v2::nodeInfo> info);


		public:
			OSTRICH_COMMON_API addon();
			OSTRICH_COMMON_API virtual ~addon() override;

			OSTRICH_COMMON_API bool exist(int type) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::ivarConstructor> varConstructor(int type) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::iconstConstructor> constConstructor(int type) override;
			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::nodeInfo>> information() override;

			template<typename T> void addVar(int type, std::string category) {
				try {

					auto constructor = std::make_shared<hv::v2::varConstructor<T>>();
					this->varConstructor(type, constructor);

					auto arg = std::make_shared<hv::v2::argument>();
					arg->add("category", category);
					arg->add("type", type);

					auto info = std::make_shared<hv::v2::nodeInfo>(typeid(T).name(), arg);
					this->information(info);
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}


			template<typename T> void addConst(int type, std::string category) {
				try {

					auto constructor = std::make_shared<hv::v2::constConstructor<T>>();
					this->constConstructor(type, constructor);

					auto arg = std::make_shared<hv::v2::argument>();
					arg->add("category", category);
					arg->add("type", type);

					auto info = std::make_shared<hv::v2::nodeInfo>(typeid(T).name(), arg);
					this->information(info);
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}


			OSTRICH_COMMON_API static std::shared_ptr<hv::v2::addon> createAddon();
		};
	}
}



#endif