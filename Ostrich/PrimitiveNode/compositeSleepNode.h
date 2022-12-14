#pragma once



#ifndef OSTRICH_COMPOSITE_SLEEP_NODE
#define OSTRICH_COMPOSITE_SLEEP_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeSleepNode;
		class compositeSleepNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeSleepNode> _instance;
		public:
			compositeSleepNode(std::string name, hv::v2::ihandle* context);
			virtual ~compositeSleepNode();


			void init() override;
			hv::v2::resultType process() override;

			COMPOSITE_NODE_CLONE_PATTERN(compositeSleepNode)
		};

	}
}

#endif