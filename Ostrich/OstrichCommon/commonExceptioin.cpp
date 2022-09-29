

#include "commonException.h"


hv::v2::oexception::oexception(const std::string& message) : std::runtime_error(message) {

}

hv::v2::oexception::~oexception() {

}
