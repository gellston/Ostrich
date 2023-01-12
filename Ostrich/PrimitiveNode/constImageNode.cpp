// PrimitiveNode.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include "constImageNode.h"
#include "commonException.h"




namespace hv {
	namespace v2 {
		class impl_constImageNode {
		public:
			int _width;
			int _height;
			int _channel;
			int _stride;
			std::vector<unsigned char> _data;
			int _depth;
			hv::v2::alignType _alignType;


			impl_constImageNode() {
				this->_width = 0;
				this->_height = 0;
				this->_channel = 0;
				this->_stride = 0;
				this->_depth = 0;
				this->_alignType = hv::v2::alignType::normal;

			}
		};
	}
}


hv::v2::constImageNode::constImageNode(std::string name) : hv::v2::constNode(name, 3) {
	this->_instance = std::make_unique<hv::v2::impl_constImageNode>();
}

hv::v2::constImageNode::~constImageNode() {

}

void hv::v2::constImageNode::init() {
	START_ERROR_HANDLE()
		this->clear();
	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}



std::string hv::v2::constImageNode::serialization() {

	return "";
}

void hv::v2::constImageNode::deserialization(std::string value) {

}


int hv::v2::constImageNode::width() {
	return this->_instance->_width;
}

int hv::v2::constImageNode::height() {
	return this->_instance->_height;
}

int hv::v2::constImageNode::channel() {
	return this->_instance->_channel;
}

int hv::v2::constImageNode::stride() {
	return this->_instance->_stride;
}

std::size_t hv::v2::constImageNode::size() {
	return this->_instance->_data.size();
}

void* hv::v2::constImageNode::data() {

	if (this->_instance->_data.size() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid data size");
		throw hv::v2::oexception(message);
	}

	return this->_instance->_data.data();
}

int hv::v2::constImageNode::depth() {
	return this->_instance->_depth;
}


void hv::v2::constImageNode::paste(std::shared_ptr<hv::v2::constImageNode> image) {

	if (image == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image pointer");
		throw hv::v2::oexception(message);
	}


	if (image->verify() == false) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image information");
		throw hv::v2::oexception(message);
	}


	if (this->compareDemension(image) == false) {
		this->_instance->_width = image->width();
		this->_instance->_height = image->height();
		this->_instance->_channel = image->channel();
		this->_instance->_depth = image->depth();
		this->_instance->_stride = image->stride();
		this->_instance->_alignType = image->alignType();

		std::size_t size = this->_instance->_stride * this->_instance->_height;

		this->_instance->_data.resize(size);
		std::memcpy(this->_instance->_data.data(), image->data(), image->size());
	}
	else {


		std::memcpy(this->_instance->_data.data(), image->data(), image->size());

	}

}

void hv::v2::constImageNode::paste(hv::v2::constImageNode* image) {

	if (image == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image pointer");
		throw hv::v2::oexception(message);
	}


	if (image->verify() == false) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image information");
		throw hv::v2::oexception(message);
	}


	if (this->compareDemension(image) == false) {
		this->_instance->_width = image->width();
		this->_instance->_height = image->height();
		this->_instance->_channel = image->channel();
		this->_instance->_depth = image->depth();
		this->_instance->_stride = image->stride();
		this->_instance->_alignType = image->alignType();

		std::size_t size = this->_instance->_stride * this->_instance->_height;

		this->_instance->_data.resize(size);
		std::memcpy(this->_instance->_data.data(), image->data(), image->size());
	}
	else {


		std::memcpy(this->_instance->_data.data(), image->data(), image->size());

	}

}

void hv::v2::constImageNode::create(int _width, int _height, int _channel, int _depth, hv::v2::alignType _type) {

	if (_type == alignType::align4) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Its not implemented.");
		throw hv::v2::oexception(message);
	}


	if (_width <= 0 ||
		_height <= 0 ||
		_channel <= 0 ||
		_depth <= 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image info");
		throw hv::v2::oexception(message);
	}

	this->_instance->_stride = _width * _channel * _depth;
	this->_instance->_width = _width;
	this->_instance->_height = _height;
	this->_instance->_depth = _depth;
	this->_instance->_channel = _channel;
	this->_instance->_alignType = _type;

	std::size_t size = this->_instance->_stride * this->_instance->_height;

	this->_instance->_data.resize(size);
	std::memset(this->_instance->_data.data(), 0, size);

}

void hv::v2::constImageNode::dealloc() {
	this->_instance->_data.clear();
	this->_instance->_width = 0;
	this->_instance->_height = 0;
	this->_instance->_channel = 0;
	this->_instance->_depth = 0;
	this->_instance->_stride = 0;

	this->_instance->_data.clear();

}

void hv::v2::constImageNode::clear() {
	if (this->_instance->_data.size() > 0) {
		std::memset(this->_instance->_data.data(), 0, this->_instance->_data.size());
	}
}

bool hv::v2::constImageNode::verify() {
	if (this->_instance->_channel <= 0 ||
		this->_instance->_width <= 0 ||
		this->_instance->_height <= 0 ||
		this->_instance->_depth <= 0 ||
		this->_instance->_stride <= 0 || 
		this->_instance->_data.size() <= 0) {
		return false;
	}

	return true;
}

hv::v2::alignType hv::v2::constImageNode::alignType() {
	return this->_instance->_alignType;
}


bool hv::v2::constImageNode::compareDemension(std::shared_ptr<hv::v2::constImageNode> image) {

	if (image == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image pointer");
		throw hv::v2::oexception(message);
	}


	if (image->verify() == false) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image information");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_channel != image->channel() ||
		this->_instance->_width != image->width() ||
		this->_instance->_height != image->height() ||
		this->_instance->_depth != image->depth() ||
		this->_instance->_stride != image->stride() ||
		this->_instance->_data.size() != image->size() || 
		this->_instance->_alignType != image->alignType()) {
		return false;
	}

	return true;
}

bool hv::v2::constImageNode::compareDemension(hv::v2::constImageNode* image) {

	if (image == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image pointer");
		throw hv::v2::oexception(message);
	}

	if (image->verify() == false) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid image information");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_channel != image->channel() ||
		this->_instance->_width != image->width() ||
		this->_instance->_height != image->height() ||
		this->_instance->_depth != image->depth() ||
		this->_instance->_stride != image->stride() ||
		this->_instance->_data.size() != image->size() || 
		this->_instance->_alignType != image->alignType()) {
		return false;
	}

	return true;

}