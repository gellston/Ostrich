#pragma once



#ifndef OSTRICH_CONST_IMAGE_NODE
#define OSTRICH_CONST_IMAGE_NODE


#include <constNode.h>
#include <macro.h>

namespace hv {
	namespace v2 {

		enum class alignType {
			normal,
			align4,
		};


		class impl_constImageNode;
		class constImageNode : public hv::v2::constNode {
		private:
			std::unique_ptr<hv::v2::impl_constImageNode> _instance;
		public:
			constImageNode(std::string name);
			virtual ~constImageNode();

		

			void init() override;


			int width();
			int height();
			int channel();
			int stride();
			std::size_t size();
			void* data();
			int depth();
			void paste(std::shared_ptr<hv::v2::constImageNode> image);
			void paste(hv::v2::constImageNode* image);
			void create(int width, int height, int channel, int depth, hv::v2::alignType type = hv::v2::alignType::normal);
			void clear();
			void dealloc();
			bool verify();
			bool compareDemension(std::shared_ptr<hv::v2::constImageNode> image);
			bool compareDemension(hv::v2::constImageNode* image);
			hv::v2::alignType alignType();


			std::string serialization();
			void deserialization(std::string value);


			START_CONST_NODE_CLONE_PATTERN(constImageNode, object)
				object->paste(this);
			END_CONST_NODE_CLONE_PATTERN(object)

		};

	}
}

#endif