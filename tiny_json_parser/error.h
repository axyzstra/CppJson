#pragma once

#include <string>
#include <stdexcept>

namespace axyz {
	namespace json {
		inline void Error(const std::string& message) {
			throw std::logic_error(message);
		}
	}
}