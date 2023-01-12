#pragma once



#ifndef OSTRICH_COMPOSITE_RANDOM_NOISE_IMAGE_NODE
#define OSTRICH_COMPOSITE_RANDOM_NOISE_IMAGE_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeRandomNoiseImageNode;
		class compositeRandomNoiseImageNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeRandomNoiseImageNode> _instance;
		public:
			compositeRandomNoiseImageNode(std::string name, hv::v2::ihandle* context);
			virtual ~compositeRandomNoiseImageNode();


			void init() override;
			hv::v2::resultType process() override;

			COMPOSITE_NODE_CLONE_PATTERN(compositeRandomNoiseImageNode)

		};

	}
}

#endif