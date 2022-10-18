

#include "commonException.h"


hv::v2::oexception::oexception(const std::string& message) : std::runtime_error(message) {

}

hv::v2::oexception::~oexception() {

}



hv::v2::breakException::breakException(const std::string& message) : hv::v2::oexception(message) {

}

hv::v2::breakException::~breakException() {

}



hv::v2::continueException::continueException(const std::string& message) : hv::v2::oexception(message) {

}

hv::v2::continueException::~continueException() {

}