#include "Scanner.h"
#include "error.h"

namespace axyz {
	namespace json {
        // ÿ��ɨ�赽 Token �򷵻�
		Scanner::JsonTokenType Scanner::Scan() {
			if (IsAtEnd()) {
				return JsonTokenType::END_OF_SOURCE;
			}

			prev_pos_ = current_;

			char c = Advance();
            switch (c) {
            case '[':
                return JsonTokenType::BEGIN_ARRAY;
            case ']':
                return JsonTokenType::END_ARRAY;
            case '{':
                return JsonTokenType::BEGIN_OBJECT;
            case '}':
                return JsonTokenType::END_OBJECT;
            case ':':
                return JsonTokenType::NAME_SEPARATOR;
            case ',':
                return JsonTokenType::VALUE_SEPARATOR;
            case 't':
                ScanTrue();
                return JsonTokenType::LITERAL_TRUE;
            case 'f':
                ScanFalse();
                return JsonTokenType::LITERAL_FALSE;
            case 'n':
                ScanNull();
                return JsonTokenType::LITERAL_NULL;
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ScanNumber();
                return JsonTokenType::VALUE_NUMBER;
            case '\"':
                ScanString();
                return JsonTokenType::VALUE_STRING;
            case ' ':
            case '\r':
            case '\n':
            case '\t':
                return Scan();
            default:
                // error
                std::string message = "Unsupported Token: ";
                message += c;
                Error(std::string(message));
                return JsonTokenType::ERROR;
            }
		}
        // �Ƿ񵽽�β
        bool Scanner::IsAtEnd()
        {
            return current_ == source_.size();
        }
        // ��õ�ǰֵ����ǰɨ��һλ
        char Scanner::Advance()
        {
            return source_[current_++];
        }
        bool Scanner::IsDigit(char c)
        {
            return c >= '0' && c <= '9';
        }
        // ���ص�ǰλ�õ��ַ�
        char Scanner::Peek()
        {
            if (IsAtEnd()) {
                return '\0';
            }
            return source_[current_];
        }
        char Scanner::PeekNext()
        {
            if (current_ + 1 >= source_.size()) return '\0';
            return source_[current_ + 1];
        }
        // ɨ�� true�������� current_ ǰ�ƣ����򱨴�
        void Scanner::ScanTrue()
        {
            if (source_.compare(current_, 3, "rue") == 0) {
                current_ += 3;
            }
            else {
                Error("Scan 'true' error");
            }
        }
        void Scanner::ScanFalse()
        {
            if (source_.compare(current_, 4, "alse") == 0) {
                current_ += 4;
            }
            else {
                Error("Scan 'false' error");
            }

        }
        void Scanner::ScanNull()
        {
            if (source_.compare(current_, 3, "ull") == 0) {
                current_ += 3;
            }
            else {
                Error("Scan 'null' error");
            }

        }
        void Scanner::ScanString()
        {
            size_t pos = current_;

            while (Peek() != '\"' && !IsAtEnd()) {
                Advance();
            }

            if (IsAtEnd()) {
                Error("Invalid string: missing clossing \" ");
            }
            // ������ " ������ǰһ��
            Advance();
            value_string_ = source_.substr(pos, current_ - pos - 1);
        }
        void Scanner::ScanNumber()
        {
            // ��¼���ֵ�ǰһ��λ��
            size_t pos = current_ - 1;
            while (IsDigit(Peek()))
            {
                Advance();
            }

            // ��ΪС��������һλΪ����
            if (Peek() == '.' && IsDigit(PeekNext())) {
                Advance();
                while (IsDigit(Peek())) {
                    Advance();
                }
            }
            // ��ɨ����ϵ������ַ���ת��Ϊ float
            value_number_ = std::atof(source_.substr(pos, current_ - pos).c_str());
        }
        void Scanner::RollBack()
        {
            current_ = prev_pos_;
        }
        std::string Scanner::GetStringValue()
        {
            return value_string_;
        }
        float Scanner::GetNumberValue()
        {
            return value_number_;
        }
	}
}
