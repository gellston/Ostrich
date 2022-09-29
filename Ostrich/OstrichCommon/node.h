#pragma once



#ifndef OSTRICH_NODE
#define OSTRICH_NODE

#include "inode.h"
#include "objectType.h"
#include "common_export.h"

namespace hv {
	namespace v2 {

		class impl_node;

		class node : public hv::v2::inode{
		private:
			std::unique_ptr<hv::v2::impl_node> _instance;

		public:
			OSTRICH_COMMON_API node(std::string name, int type);
			OSTRICH_COMMON_API virtual ~node() override;

			OSTRICH_COMMON_API std::string name() override;
			OSTRICH_COMMON_API std::string nick() override;
			OSTRICH_COMMON_API void nick(std::string value) override;
			OSTRICH_COMMON_API int type() override;
		
		
		};
	}
}


#endif