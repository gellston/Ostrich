#pragma once



#ifndef OSTRICH_CONST_NUMBER_NODE
#define OSTRICH_CONST_NUMBER_NODE


#include <constNode.h>
#include <macro.h>

namespace hv {
	namespace v2 {
		class impl_constNumberNode;
		class constNumberNode : public hv::v2::constNode{
		private:
			std::unique_ptr<hv::v2::impl_constNumberNode> _instance;
		public:
			constNumberNode(std::string name);
			virtual ~constNumberNode();

			double data();
			void data(double value);
			
			void init() override;

			std::string serialization();
			void deserialization(std::string value);


			START_CONST_NODE_CLONE_PATTERN(constNumberNode, object)
				object->data(this->data());
			END_CONST_NODE_CLONE_PATTERN(object)

		};

	}
}

#endif