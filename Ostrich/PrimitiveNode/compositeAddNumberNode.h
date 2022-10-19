#pragma once



#ifndef OSTRICH_COMPOSITE_ADD_NUMBER_NODE
#define OSTRICH_COMPOSITE_ADD_NUMBER_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeAddNumberNode;
		class compositeAddNumberNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeAddNumberNode> _instance;
		public:
			compositeAddNumberNode(std::string name, hv::v2::ihandle* context);
			~compositeAddNumberNode();


			void init() override;
			hv::v2::resultType process() override;
		};

	}
}

#endif