#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>


namespace axyz {
	namespace json {

		class JsonElement;
		using JsonObject = std::unordered_map<std::string, JsonElement*>;
		using JsonArray = std::vector<JsonElement*>;

		// ������json����
		class JsonElement {
		public:
			// ��Ҫ��Ϊ�˼�¼��ǰ json ������
			enum class Type {
				JSON_OBJECT,
				JSON_ARRAY,
				JSON_STRING,
				JSON_NUMBER,
				JSON_BOOL,
				JSON_NULL
			};

			// Json �� Value, union ֻ����һ����Ա����ʵֵ
			union Value {
				JsonObject* value_object;
				JsonArray* value_array;

				std::string* value_string;
				float value_number;
				bool value_bool;
			};

			// ���췽��
			JsonElement() : type_(Type::JSON_NULL) {}
			JsonElement(JsonObject* value_object) : type_(Type::JSON_OBJECT) { value(value_object); }
			JsonElement(JsonArray* value_array) : type_(Type::JSON_ARRAY) { value(value_array); }
			JsonElement(std::string* value_string) : type_(Type::JSON_STRING) { value(value_string); }
			JsonElement(float value_number) : type_(Type::JSON_NUMBER) { value(value_number); }
			JsonElement(bool value_bool) : type_(Type::JSON_BOOL) { value(value_bool); }

			~JsonElement() {
				if (type_ == Type::JSON_OBJECT) {
					delete value_.value_object;
					value_.value_object = nullptr;
				}
				else if (type_ == Type::JSON_ARRAY) {
					delete value_.value_array;
					value_.value_array = nullptr;
				}
				else if (type_ == Type::JSON_STRING) {
					delete value_.value_string;
					value_.value_string = nullptr;
				}
			}



			Type type() { return type_; }
			Value value() { return value_; }



			// ����ת�͵ķ���
			JsonObject* AsObject();
			JsonArray* AsArray();
			std::string* AsString();
			float AsNumber();
			bool AsBool();

			// תΪ json �ַ���
			std::string Dumps();
			friend std::ostream& operator<<(std::ostream& os, const JsonObject& object);
			friend std::ostream& operator<<(std::ostream& os, const JsonArray& array);
			friend std::ostream& operator<<(std::ostream& os, const JsonElement::Type& type);
			friend std::ostream& operator<<(std::ostream& os, const JsonElement::Value& value);

			void value(JsonObject* value) {
				type_ = Type::JSON_OBJECT;
				value_.value_object = value;
			}

			void value(JsonArray* value) {
				type_ = Type::JSON_ARRAY;
				value_.value_array = value;
			}

			void value(std::string* value) {
				type_ = Type::JSON_STRING;
				value_.value_string = value;
			}

			void value(float value) {
				type_ = Type::JSON_NUMBER;
				value_.value_number = value;
			}

			void value(bool value) {
				type_ = Type::JSON_BOOL;
				value_.value_bool = value;
			}

		private:
			Type type_;
			Value value_;
		};
	}
}
