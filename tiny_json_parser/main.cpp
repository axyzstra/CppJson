#include <iostream>
#include <sstream>
#include "Parser.h"
#include "Scanner.h"
#include "JsonElement.h"

int main() {
    //std::string jsonStr = "{\"name\":\"John\"}";
    //std::string jsonStr = "{\"age\":30}";
    //std::string jsonStr = "{\"isStudent\":true}";
    //std::string jsonStr = "{\"scores\":[90, 95, 88]}";
    // 
    // R �ַ���
    // R"( ... )"
    // ... �ɱ�ʾ�����ַ�������ת��
    // 
    // 
    // 
    //std::string jsonStr = R"({
    //    "AddTest": 20,
    //    "age": -22,
    //    "gender": "��",
    //    "isProgrammer": true,
    //    "name": "��������ľ",
    //    "skills": ["C++", "JS/TS", "Java"],
    //    "university": "whu"
    //})";
    std::string jsonStr = R"({
        "name":"John", 
        "age":30, 
        "isStudent":true, 
        "scores":[90, 95, 88], 
        "address":{
             "city":"New York", 
             "country":"USA"
         }
    })";


    axyz::json::Scanner scanner(jsonStr);
    axyz::json::Parser parser(scanner);
    axyz::json::JsonElement* root = parser.Parse();
    
    if (root != nullptr) {
        std::cout << "Parsed JSON Element:\n";
        std::cout << *root->AsObject() << std::endl;
        delete root;
    }
    else {
        std::cerr << "Failed to parse JSON string!" << std::endl;
    }

    return 0;
}