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

#include <math.h>
#include "vm.h"
#include "opcode.h"

namespace yuka {

#define FloatValue(val) \
	((val.type == ValueType_Float) ? val.float_value : static_cast<YukaFloat>(val.int_value))

#define IntegerValue(val) \
	((val.type == ValueType_Integer) ? val.int_value : static_cast<YukaInt>(val.float_value))

static inline Value MakeFloat(YukaFloat f) {
	Value v;
	memset(&v, 0, sizeof(Value));
	v.type = ValueType_Float;
	v.float_value = f;
	return v;
}

static inline Value MakeInteger(YukaInt n) {
	Value v;
	memset(&v, 0, sizeof(Value));
	v.type = ValueType_Integer;
	v.int_value = n;
	return v;
}

Value VM::run(ByteCode *bc) {
	const char *code = bc->getCode();
	int code_size = bc->getSize();
	int code_pos = 0;

	while (code_pos < code_size) {
		Opcode op = (Opcode)code[code_pos++];

		switch (op)
		{
		case Op_NewInteger: {
			YukaInt n;
			memcpy(&n, code+code_pos, sizeof(YukaInt));
			m_stack.push(MakeInteger(n));
			code_pos += sizeof(YukaInt);
		}
		break;

		case Op_NewFloat: {
			YukaFloat f;
			memcpy(&f, code+code_pos, sizeof(YukaFloat));
			m_stack.push(MakeFloat(f));
			code_pos += sizeof(YukaFloat);
		}
		break;

		case Op_Add: {
			Value a = m_stack.top();
			m_stack.pop();

			Value b = m_stack.top();
			m_stack.pop();

			Value v;

			if (a.type == ValueType_Float || b.type == ValueType_Float) {
				v = MakeFloat(FloatValue(a) + FloatValue(b));
			} else {
				v = MakeInteger(IntegerValue(a) + IntegerValue(b));
			}

			m_stack.push(v);
		}
		break;

		case Op_Sub: {
			Value a = m_stack.top();
			m_stack.pop();

			Value b = m_stack.top();
			m_stack.pop();

			Value v;

			if (a.type == ValueType_Float || b.type == ValueType_Float) {
				v = MakeFloat(FloatValue(b) - FloatValue(a));
			} else {
				v = MakeInteger(IntegerValue(b) - IntegerValue(a));
			}

			m_stack.push(v);
		}
		break;

		case Op_Mul: {
			Value a = m_stack.top();
			m_stack.pop();

			Value b = m_stack.top();
			m_stack.pop();

			Value v;

			if (a.type == ValueType_Float || b.type == ValueType_Float) {
				v = MakeFloat(FloatValue(b) * FloatValue(a));
			} else {
				v = MakeInteger(IntegerValue(b) * IntegerValue(a));
			}

			m_stack.push(v);
		}
		break;

		case Op_Div: {
			Value a = m_stack.top();
			m_stack.pop();

			Value b = m_stack.top();
			m_stack.pop();

			Value v = MakeFloat(FloatValue(b) / FloatValue(a));
			m_stack.push(v);
		}
		break;

		case Op_Pow: {
			Value exponent = m_stack.top();
			m_stack.pop();

			Value base = m_stack.top();
			m_stack.pop();

			Value result = MakeFloat(::pow(FloatValue(base), FloatValue(exponent)));
			m_stack.push(result);
		}
		break;

		case Op_NOP:
		case Op_EOF:
		break;
		}
	}

	return m_stack.top();
}

}
