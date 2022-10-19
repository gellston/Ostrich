#pragma once



#ifndef OSTRICH_COMPOSITE_FOR_NODE
#define OSTRICH_COMPOSITE_FOR_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeForNode;
		class compositeForNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeForNode> _instance;
		public:
			compositeForNode(std::string name, hv::v2::ihandle* context);
			~compositeForNode();


			void init() override;
			hv::v2::resultType process() override;
		};

	}
}

#endif