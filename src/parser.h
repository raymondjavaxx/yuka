//
// Copyright (c) 2011 Ramon E. Torres Salomon
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef _YUKA_PARSER_H
#define _YUKA_PARSER_H

#include <vector>

namespace yuka {

	enum Token {
		Token_Invalid = 0,
		Token_Add,
		Token_Sub,
		Token_Div,
		Token_Mul,
		Token_Number,
		Token_OpenParentesis,
		Token_CloseParentesis
	};

	class TokenObj
	{
	public:
		TokenObj(Token type) {
			m_type = type;
			m_int_value = 0;
		}

		void setIntValue(int value) {
			m_int_value = value;
		}

		int getIntValue() {
			return m_int_value;
		}

		Token getType() {
			return m_type;
		}

		bool isOperator() {
			return m_type == Token_Add ||
				m_type == Token_Sub ||
				m_type == Token_Div ||
				m_type == Token_Mul;
		}

	protected:
		Token m_type;
		int m_int_value;
	};

	typedef std::vector<TokenObj*> TokenObjVector;
	typedef std::vector<TokenObj*>::iterator TokenObjVectorIterator;

	class Parser
	{
	public:
		Parser();
		virtual ~Parser();

		TokenObjVector parse(char *data, size_t len);
	private:
	/* data */
	};
};

#endif //_YUKA_PARSER_H
