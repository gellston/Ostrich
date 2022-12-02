#include "constNode.h"
#include "commonException.h"


namespace hv {
	namespace v2 {
		class impl_constNode {
		public:
			bool _isConnected;
			bool _isMultiple;
			std::size_t _sourceUID;
			std::string _sourceName;

			bool _isFreezed;
			int _index;

			std::vector<std::size_t> _sourceMultiUID;
			std::vector<std::string> _sourceMultiNames;

			impl_constNode() {
				_isConnected = false;
				_sourceUID = 0;
				_sourceName = "";
				_isFreezed = false;
				_isMultiple = false;
				_index = 0;
			}
		};
	}
}


hv::v2::constNode::constNode(std::string name, int type) : hv::v2::node(name, type) {


	this->_instance = std::make_unique<hv::v2::impl_constNode>();

}

hv::v2::constNode::~constNode() {

}


bool hv::v2::constNode::isConnected() {
	return this->_instance->_isConnected;
}

void hv::v2::constNode::isConnected(bool value) {
	this->_instance->_isConnected = value;
}

bool hv::v2::constNode::isMultiple() {
	return this->_instance->_isMultiple;
}
void hv::v2::constNode::isMultiple(bool value) {
	this->_instance->_isMultiple = value;
}


int hv::v2::constNode::index() {
	return this->_instance->_index;
}

void hv::v2::constNode::index(int _index) {
	this->_instance->_index = _index;
}


std::size_t hv::v2::constNode::sourceUID() {
	return this->_instance->_sourceUID;
}

void hv::v2::constNode::sourceUID(std::size_t id) {
	this->_instance->_sourceUID = id;
}



std::string hv::v2::constNode::sourceName() {
	return this->_instance->_sourceName;
}

void hv::v2::constNode::sourceName(std::string name) {
	this->_instance->_sourceName = name;
}


std::vector<std::size_t> hv::v2::constNode::sourceMultiUID() {
	return this->_instance->_sourceMultiUID;
}
std::vector<std::string> hv::v2::constNode::sourceMultiNames() {
	return this->_instance->_sourceMultiNames;
}

void hv::v2::constNode::sourceMultiUID(std::vector<std::size_t> uids) {
	this->_instance->_sourceMultiUID = uids;
}
void hv::v2::constNode::sourceMultiNames(std::vector<std::string> names) {
	this->_instance->_sourceMultiNames = names;
}



std::string hv::v2::constNode::name() {

	return hv::v2::node::name();
}
//std::string hv::v2::constNode::nick() {
//	return hv::v2::node::nick();
//}
//void hv::v2::constNode::nick(std::string value) {
//	hv::v2::node::nick(value);
//}
int hv::v2::constNode::type() {
	return hv::v2::node::type();
}


std::size_t hv::v2::constNode::uid() {
	return hv::v2::node::uid();
}
void hv::v2::constNode::uid(std::size_t value) {
	hv::v2::node::uid(value);
}
