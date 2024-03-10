#pragma once
#include "Scanner.h"
#include "JsonElement.h"


namespace axyz {
	namespace json {
		class Parser {

		public:
			// �����õ� json Ԫ��
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