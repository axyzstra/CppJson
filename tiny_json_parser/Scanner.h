#pragma once
/**
* 该类读取json字符串将其解析为 token
*/
#include <iostream>
#include <string>

namespace axyz {
	namespace json {
		class Scanner {
		public:
			Scanner(std::string source) : source_(source), current_(0) {}

			enum class JsonTokenType {
				BEGIN_OBJECT,		// {
				END_OBJECT,			// }

				VALUE_SEPARATOR,		// ,
				NAME_SEPARATOR,		// :

				VALUE_STRING,		// string
				VALUE_NUMBER,		// 1,2,3

				LITERAL_TRUE,		// true
				LITERAL_FALSE,		// false
				LITERAL_NULL,		// null

				BEGIN_ARRAY,		// [
				END_ARRAY,			// ]

				END_OF_SOURCE,		// EOF

				ERROR
			};

			friend std::ostream& operator<<(std::ostream& os, const JsonTokenType& type) {
				switch (type) {
				case JsonTokenType::BEGIN_ARRAY:
					os << "[";
					break;
				case JsonTokenType::END_ARRAY:
					os << "]";
					break;
				case JsonTokenType::BEGIN_OBJECT:
					os << "{";
					break;
				case JsonTokenType::END_OBJECT:
					os << "}";
					break;
				case JsonTokenType::NAME_SEPARATOR:
					os << ":";
					break;
				case JsonTokenType::VALUE_SEPARATOR:
					os << ",";
					break;
				case JsonTokenType::VALUE_NUMBER:
					os << "number";
					break;
				case JsonTokenType::VALUE_STRING:
					os << "string";
					break;
				case JsonTokenType::LITERAL_TRUE:
					os << "true";
					break;
				case JsonTokenType::LITERAL_FALSE:
					os << "false";
					break;
				case JsonTokenType::LITERAL_NULL:
					os << "null";
					break;
				case JsonTokenType::END_OF_SOURCE:
					os << "EOF";
					break;
				default:
					break;
				}
				return os;
			}

			// 从当前扫描的 token 出发寻找下一个 token
			JsonTokenType Scan();
			bool IsAtEnd();
			char Advance();
			bool IsDigit(char c);
			char Peek();
			char PeekNext();

			void ScanTrue();
			void ScanFalse();
			void ScanNull();
			void ScanString();
			void ScanNumber();

			void RollBack();

			std::string GetStringValue();
			float GetNumberValue();

		private:
			std::string source_;

			size_t prev_pos_;
			size_t current_;

			float value_number_;
			std::string value_string_;
		};
	}
}