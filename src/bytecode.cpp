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

#include "ByteCode.h"

#include <stdlib.h>
#include <memory.h>
#include <string.h>

namespace yuka {

const int kDefaultBufferSize = 32;

ByteCode::ByteCode() {
	m_code = (char*)malloc(kDefaultBufferSize);
	memset(m_code, NULL, kDefaultBufferSize);
	m_buffer_size = kDefaultBufferSize;
	m_size = 0;
}

ByteCode::~ByteCode() {
	free(m_code);
}

ByteCode::ByteCode(char *c, unsigned int s) {
	m_code = (char*)malloc(s);
	memcpy(m_code, c, s);
	m_size = s;
	m_buffer_size = s;
}

const char *ByteCode::getCode() {
	return m_code;
}

unsigned int ByteCode::getSize() {
	return m_size;
}

void ByteCode::addOpcode(Opcode op) {
	resize(sizeof(char));
	m_code[m_size++] = op;
}

void ByteCode::newInteger(int n) {
	addOpcode(op_new_integer);
	resize(sizeof(int));
	memcpy(m_code+m_size, &n, sizeof(n));
	m_size += sizeof(n);
}

void ByteCode::resize(unsigned int s) {
	unsigned int new_size = m_size + s;

	if (new_size > m_buffer_size) {
		m_buffer_size = (new_size * 2);
		m_code = (char*)realloc(m_code, m_buffer_size);
	}
}

}; //namespace
