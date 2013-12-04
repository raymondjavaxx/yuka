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

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "vm.h"

using namespace std;

int main (int argc, const char * argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " expr" << endl;
		exit(1);
	}

	yuka::Compiler *compiler = new yuka::Compiler();
	yuka::ByteCode *bc = compiler->compile(argv[1], strlen(argv[1]));

	yuka::VM *vm = new yuka::VM;
	yuka::Value result = vm->run(bc);

	if (result.type == yuka::ValueType_Integer) {
		cout << result.int_value << endl;
	} else {
		cout << result.float_value << endl;
	}

	delete bc;
	delete compiler;
	delete vm;

	return 0;
}

