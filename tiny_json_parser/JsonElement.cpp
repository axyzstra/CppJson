#include "JsonElement.h"
#include "error.h"
#include <sstream>

namespace axyz {
	namespace json {
        JsonObject* axyz::json::JsonElement::AsObject()
        {
            if (type_ == Type::JSON_OBJECT) {
                return value_.value_object;
            }
            else {
                Error("Type of JsonElement isn't JsonObject");
                return nullptr;
            }
        }

        JsonArray* axyz::json::JsonElement::AsArray()
        {
            if (type_ == Type::JSON_ARRAY) {
                return value_.value_array;
            }
            else {
                Error("Type of JsonElement isn't JsonArray");
                return nullptr;
            }
        }

        std::string* axyz::json::JsonElement::AsString()
        {
            if (type_ == Type::JSON_STRING) {
                return value_.value_string;
            }
            else {
                Error("Type of JsonElement isn't String");
                return nullptr;
            }
        }

        float axyz::json::JsonElement::AsNumber()
        {
            if (type_ == Type::JSON_NUMBER) {
                return value_.value_number;
            }
            else {
                Error("Type of JsonElement isn't number");
                return 0.0f;
            }
        }

        bool axyz::json::JsonElement::AsBool()
        {
            if (type_ == Type::JSON_BOOL) {
                return value_.value_bool;
            }
            else {
                Error("Type of JsonElement isn't bool");
                return false;
            }
        }

        std::string axyz::json::JsonElement::Dumps()
        {
            std::stringstream ss;
            switch (type_)
            {
            case axyz::json::JsonElement::Type::JSON_OBJECT: {
                ss << *(value_.value_object);
                break;
            }
            case axyz::json::JsonElement::Type::JSON_ARRAY: {
                ss << *(value_.value_array);
                break;
            }
            case axyz::json::JsonElement::Type::JSON_STRING: {
                ss << '\"' << *(value_.value_string) << '\"';
                //ss << *(value_.value_string);
                break;
            }
            case axyz::json::JsonElement::Type::JSON_NUMBER: {
                ss << value_.value_number;
                break;
            }
            case axyz::json::JsonElement::Type::JSON_BOOL: {
                ss << (value_.value_bool == true ? "true" : "false");
                break;
            }
            case axyz::json::JsonElement::Type::JSON_NULL: {
                ss << "null";
                break;
            }
            default:
                break;
            }
            return ss.str();
        }
        std::ostream& operator<<(std::ostream& os, const JsonObject& object) {
            os << "{\n\t";
            for (auto iter = object.begin(); iter != object.end(); iter++) {
                os << '\"' << iter->first << '\"' << " : " << iter->second->Dumps();
                //os << iter->first << iter->second->Dumps();
                // 先对迭代器减 1 再返回
                if (iter != --object.end()) {
                    os << ", \n\t";
                }
            }
            os << "\n}";
            return os;
        }
        std::ostream& operator<<(std::ostream& os, const JsonArray& array) {
            os << "[";
            for (size_t i = 0; i < array.size(); i++) {
                os << array[i]->Dumps();
                if (i != array.size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
            return os;
        }
        std::ostream& operator<<(std::ostream& os, const JsonElement::Type& type)
        {
            switch (type)
            {
            case JsonElement::Type::JSON_ARRAY:
            {
                os << "array";
                break;
            }
            case JsonElement::Type::JSON_OBJECT:
            {
                os << "object";
                break;
            }
            case JsonElement::Type::JSON_STRING:
            {
                os << "string";
                break;
            }
            case JsonElement::Type::JSON_NUMBER:
            {
                os << "number";
                break;
            }
            case JsonElement::Type::JSON_BOOL:
            {
                os << "BOOL";
                break;
            }
            default:
                os << "other";
                break;
            }
            return os;
        }

        std::ostream& operator<<(std::ostream& os, const JsonElement::Value& value)
        {
            switch (value.value_string != nullptr ? axyz::json::JsonElement::Type::JSON_STRING :
                value.value_object != nullptr ? axyz::json::JsonElement::Type::JSON_OBJECT :
                value.value_array != nullptr ? axyz::json::JsonElement::Type::JSON_ARRAY :
                value.value_number != 0.0f ? axyz::json::JsonElement::Type::JSON_NUMBER :
                value.value_bool ? axyz::json::JsonElement::Type::JSON_BOOL :
                axyz::json::JsonElement::Type::JSON_NULL) {
            case axyz::json::JsonElement::Type::JSON_STRING:
                os << *(value.value_string);
                break;
            case axyz::json::JsonElement::Type::JSON_OBJECT:
                os << *(value.value_object);
                break;
            case axyz::json::JsonElement::Type::JSON_ARRAY:
                os << *(value.value_array);
                break;
            case axyz::json::JsonElement::Type::JSON_NUMBER:
                os << value.value_number;
                break;
            case axyz::json::JsonElement::Type::JSON_BOOL:
                os << (value.value_bool ? "true" : "false");
                break;
            case axyz::json::JsonElement::Type::JSON_NULL:
                os << "null";
                break;
            default:
                // 不应发生，此分支用于警告或错误处理
                os << "Invalid or uninitialized JsonElement::Value";
                break;
            }
            return os;
        }
        
    }
}


