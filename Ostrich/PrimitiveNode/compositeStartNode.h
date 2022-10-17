#pragma once



#ifndef OSTRICH_COMPOSITE_START_NODE
#define OSTRICH_COMPOSITE_START_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeStartNode;
		class compositeStartNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeStartNode> _instance;
		public:
			compositeStartNode(std::string name, hv::v2::ihandle* context);
			~compositeStartNode();


			void init() override;
			void process() override;
		};

	}
}

#endif