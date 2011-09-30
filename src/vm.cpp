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

int VM::run(ByteCode *bc) {
	const char *code = bc->getCode();
	int code_size = bc->getSize();
	int code_pos = 0;

	while (code_pos < code_size) {
		Opcode op = (Opcode)code[code_pos++];

		switch (op)
		{
		case op_new_integer: {
			int n;
			memcpy(&n, code+code_pos, sizeof(int));
			m_stack.push(n);
			code_pos += sizeof(int);
		}
		break;

		case op_add: {
			int a = m_stack.top();
			m_stack.pop();

			int b = m_stack.top();
			m_stack.pop();

			int c = b + a;
			m_stack.push(c);
		}
		break;

		case op_sub: {
			int a = m_stack.top();
			m_stack.pop();

			int b = m_stack.top();
			m_stack.pop();

			int c = b - a;
			m_stack.push(c);
		}
		break;

		case op_mul: {
			int a = m_stack.top();
			m_stack.pop();

			int b = m_stack.top();
			m_stack.pop();

			int c = b * a;
			m_stack.push(c);
		}
		break;

		case op_div: {
			int a = m_stack.top();
			m_stack.pop();

			int b = m_stack.top();
			m_stack.pop();

			int c = b / a;
			m_stack.push(c);
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
