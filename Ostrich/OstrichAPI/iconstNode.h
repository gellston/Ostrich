#pragma once


#ifndef OSTRICH_ICONST_NODE
#define OSTRICH_ICONST_NODE


#include "inode.h"


namespace hv {
	namespace v2 {
		class iconstNode : public hv::v2::inode {
		public:

			virtual ~iconstNode() { }


			virtual bool isConnected() = 0;
			virtual void isConnected(bool value) = 0;


			virtual int index() = 0;
			virtual void index(int _index) =0;
			

			virtual std::size_t sourceUID() = 0;
			virtual void sourceUID(std::size_t value) = 0;


			virtual std::string sourceName() = 0;
			virtual void sourceName(std::string value) = 0;


			virtual void deserialization(std::string value) = 0;
			virtual std::string serialization() = 0;



			virtual void registerMultipleSourceNode(std::size_t uid, std::string name) = 0;
			virtual void clearMultipleSourceNode() = 0;
			virtual void unRegisterMultipleSourceNode(std::size_t uid, std::string name) = 0;
			virtual void unRegisterMultipleSourceNode(std::size_t uid) = 0;
			virtual std::vector<std::tuple<std::size_t, std::string>> multipleSourceNode() = 0;
			virtual void multipleSourceNode(std::vector<std::tuple<std::size_t, std::string>> nodes) = 0;

			virtual bool isMultiple() = 0;
			virtual void isMultiple(bool value) = 0;


			virtual std::shared_ptr<hv::v2::iconstNode> clone() = 0;

		};
	}
}

#endif

