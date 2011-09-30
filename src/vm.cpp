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

#include "vm.h"
#include "opcode.h"

namespace yuka {

static inline float FloatValue(t_yuka_value v) {
	if (v.type == ValueType_Float) {
		return v.float_value;
	}

	return static_cast<float>(v.int_value);
}

static inline int IntegerValue(t_yuka_value v) {
	if (v.type == ValueType_Integer) {
		return v.int_value;
	}

	return static_cast<int>(v.float_value);
}


t_yuka_value VM::run(ByteCode *bc) {
	const char *code = bc->getCode();
	int code_size = bc->getSize();
	int code_pos = 0;

	while (code_pos < code_size) {
		Opcode op = (Opcode)code[code_pos++];

		switch (op)
		{
		case op_new_integer: {
			t_yuka_value v;
			memset(&v, 0, sizeof(t_yuka_value));
			v.type = ValueType_Integer;
			memcpy(&v.int_value, code+code_pos, sizeof(int));

			m_stack.push(v);

			code_pos += sizeof(int);
		}
		break;

		case op_new_float: {
			t_yuka_value v;
			memset(&v, 0, sizeof(t_yuka_value));
			v.type = ValueType_Float;
			memcpy(&v.float_value, code+code_pos, sizeof(int));

			m_stack.push(v);
			
			code_pos += sizeof(int);
		}
		break;

		case op_add: {
			t_yuka_value a = m_stack.top();
			m_stack.pop();

			t_yuka_value b = m_stack.top();
			m_stack.pop();

			t_yuka_value v;
			memset(&v, 0, sizeof(t_yuka_value));

			if (a.type == ValueType_Float || b.type == ValueType_Float) {
				v.type = ValueType_Float;
				v.float_value = FloatValue(a) + FloatValue(b);
			} else {
				v.type = ValueType_Integer;
				v.int_value = IntegerValue(a) + IntegerValue(b);
			}

			m_stack.push(v);
		}
		break;

		case op_sub: {
			t_yuka_value a = m_stack.top();
			m_stack.pop();

			t_yuka_value b = m_stack.top();
			m_stack.pop();

			t_yuka_value v;
			memset(&v, 0, sizeof(t_yuka_value));
			
			if (a.type == ValueType_Float || b.type == ValueType_Float) {
				v.type = ValueType_Float;
				v.float_value = FloatValue(b) - FloatValue(a);
			} else {
				v.type = ValueType_Integer;
				v.int_value = IntegerValue(b) - IntegerValue(a);
			}
			
			m_stack.push(v);
		}
		break;

		case op_mul: {
			t_yuka_value a = m_stack.top();
			m_stack.pop();

			t_yuka_value b = m_stack.top();
			m_stack.pop();

			t_yuka_value v;
			memset(&v, 0, sizeof(t_yuka_value));

			if (a.type == ValueType_Float || b.type == ValueType_Float) {
				v.type = ValueType_Float;
				v.float_value = FloatValue(b) * FloatValue(a);
			} else {
				v.type = ValueType_Integer;
				v.int_value = IntegerValue(b) * IntegerValue(a);
			}

			m_stack.push(v);
		}
		break;

		case op_div: {
			t_yuka_value a = m_stack.top();
			m_stack.pop();
			
			t_yuka_value b = m_stack.top();
			m_stack.pop();
			
			t_yuka_value v;
			memset(&v, 0, sizeof(t_yuka_value));
			
			//if (a.type == ValueType_Float || b.type == ValueType_Float) {
				v.type = ValueType_Float;
				v.float_value = FloatValue(b) / FloatValue(a);
			//} else {
			//	v.type = ValueType_Integer;
			//	v.int_value = IntegerValue(b) / IntegerValue(a);
			//}
			
			m_stack.push(v);
		}
		break;

		case op_noop:
		case op_eof:
		break;
		}
	}

	return m_stack.top();
}

}
