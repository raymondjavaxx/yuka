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

#include <stack>

#include "compiler.h"
#include "parser.h"

#ifdef DEBUG
#define YUKA_DEBUG(STR) printf(STR);
#define YUKA_DEBUGF(STR, ARG1) printf(STR, ARG1);
#else
#define YUKA_DEBUG(STR)
#define YUKA_DEBUGF(STR, ARG1)
#endif

namespace yuka {

ByteCode *Compiler::compile(const char *data, size_t len) {
	Parser *parser = new Parser();
	TokenObjVector tokens = parser->parse(data, len);
	tokens = shuntingYard(tokens);

	ByteCode *bc = new ByteCode;

	TokenObjVectorIterator it;
	for (it = tokens.begin(); it != tokens.end(); it++) {
		TokenObj *token = (TokenObj*)*it;

		switch (token->getType())
		{
		case Token_Number: {
			if (token->getValueType() == ValueType_Integer) {
				YUKA_DEBUGF("number %d\n", token->getIntValue());
				bc->newInteger(token->getIntValue());
			} else {
				YUKA_DEBUGF("number %f\n", token->getFloatValue());
				bc->newFloat(token->getFloatValue());
			}
		}
		break;

		case Token_Pow: {
			YUKA_DEBUG("exp\n");
			bc->addOpcode(Op_Pow);
		}
		break;

		case Token_Add: {
			YUKA_DEBUG("add\n");
			bc->addOpcode(Op_Add);
		}
		break;

		case Token_Sub: {
			YUKA_DEBUG("sub\n");
			bc->addOpcode(Op_Sub);
		}
		break;

		case Token_Mul: {
			YUKA_DEBUG("mul\n");
			bc->addOpcode(Op_Mul);
		}
		break;

		case Token_Div: {
			YUKA_DEBUG("div\n");
			bc->addOpcode(Op_Div);
		}
		break;

		default:
			bc->addOpcode(Op_NOP);
		break;
		}
	}

	bc->addOpcode(Op_EOF);

	return bc;
}

// http://en.wikipedia.org/wiki/Shunting-yard_algorithm
TokenObjVector Compiler::shuntingYard(TokenObjVector tokens) {
	TokenObjVector output;
	std::stack<TokenObj*> op_stack;

	TokenObjVectorIterator it;
	for (it = tokens.begin(); it != tokens.end(); it++) {
		TokenObj *token = (TokenObj*)*it;
		Token type = token->getType();

		if (type == Token_Number) {
			output.push_back(token);
		} else if (token->isOperator()) {
			if (type == Token_Add || type == Token_Sub) {
				if (op_stack.size() > 0) {
					if (op_stack.top()->getType() == Token_Add && type == Token_Sub) {
						output.push_back(op_stack.top());
						op_stack.pop();
					}
				}

				op_stack.push(token);
			} else {
				if (op_stack.size() > 0) {
					if (op_stack.top()->getType() == Token_Mul && type == Token_Div) {
						output.push_back(op_stack.top());
						op_stack.pop();
					}
				}
				op_stack.push(token);
			}
		} else if (type == Token_OpenParentesis) {
			op_stack.push(token);
		} else if (type == Token_CloseParentesis) {
			while(op_stack.top()->getType() != Token_OpenParentesis) {
				output.push_back(op_stack.top());
				op_stack.pop();
			}
			op_stack.pop();
		}
	}

	while (op_stack.size() > 0) {
		output.push_back(op_stack.top());
		op_stack.pop();
	}
	
	return output;
}

};
