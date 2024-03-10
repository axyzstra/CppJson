#pragma once
#include "Scanner.h"
#include "JsonElement.h"


namespace axyz {
	namespace json {
		class Parser {

		public:
			// 解析得到 json 元素
			JsonElement* Parse();

			Parser(const Scanner& scanner) : scanner_(scanner) {}
		private:
			JsonObject* ParseObject();
			JsonArray* ParseArray();

		private:
			Scanner scanner_;
		};
	}
}