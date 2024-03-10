#include "Parser.h"
#include "error.h"

namespace axyz {
	namespace json {
		using Type = JsonElement::Type;
		using JsonTokenType = Scanner::JsonTokenType;

		JsonElement* Parser::Parse()
		{
			JsonElement* element = new JsonElement();
			JsonTokenType token_type = scanner_.Scan();

			switch (token_type) {
			case JsonTokenType::BEGIN_OBJECT: {
				JsonObject* object = ParseObject();
				element->value(object);
				break;
			}
			case JsonTokenType::BEGIN_ARRAY: {
				JsonArray* array = ParseArray();
				element->value(array);
				break;
			}
			case JsonTokenType::VALUE_STRING: {
				std::string* val = new std::string(scanner_.GetStringValue());
				element->value(val);
				break;
			}
			case JsonTokenType::VALUE_NUMBER: {
				element->value(scanner_.GetNumberValue());
				break;
			}
			case JsonTokenType::LITERAL_TRUE: {
				element->value(true);
				break;
			}
			case JsonTokenType::LITERAL_FALSE: {
				element->value(false);
				break;
			}
			case JsonTokenType::LITERAL_NULL:
				break;
			default:
				break;
			}
			//std::cout << element->type() << std::endl;
			return element;
		}
		// 解析 json 对象
		JsonObject* Parser::ParseObject()
		{
			JsonObject* res = new JsonObject();
			JsonTokenType curToken = scanner_.Scan();

			if (curToken == JsonTokenType::END_OBJECT) {
				return res;
			}
			scanner_.RollBack();
			while (true)
			{
				curToken = scanner_.Scan();
				if (curToken != JsonTokenType::VALUE_STRING) {
					Error("Key must be string");
				}
				std::string key = scanner_.GetStringValue();
				curToken = scanner_.Scan();
				if (curToken != JsonTokenType::NAME_SEPARATOR) {
					Error("Expected ':' in object!");
				}
				// 上面已经读取了 {"age":20} 的 ‘:’ 接下来继续读取
				(*res)[key] = Parse();
				curToken = scanner_.Scan();
				if (curToken == JsonTokenType::END_OBJECT) {
					break;
				}
				if (curToken != JsonTokenType::VALUE_SEPARATOR) {
					Error("Expected ',' in object!");
				}
			}
			return res;
		}
		// 解析 json 数组
		JsonArray* Parser::ParseArray()
		{
			JsonArray* res = new JsonArray();
			JsonTokenType curToken = scanner_.Scan();;
			if (curToken == JsonTokenType::END_ARRAY) {
				return res;
			}
			scanner_.RollBack();

			while (true) {
				res->push_back(Parse());
				curToken = scanner_.Scan();
				if (curToken == JsonTokenType::END_ARRAY) {
					break;
				}
				if (curToken != JsonTokenType::VALUE_SEPARATOR) {
					Error("Expected ',' in array");
				}
			}
			return res;
		}
	}
}
