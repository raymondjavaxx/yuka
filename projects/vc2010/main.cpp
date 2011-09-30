#include <iostream>
#include <stdio.h>

#include <vector>

#include "compiler.h"
#include "vm.h"

using namespace std;

int main (int argc, const char * argv[]) {
	char expression[] = "5 ^ 2";

	yuka::Compiler *compiler = new yuka::Compiler();
	yuka::ByteCode *bc = compiler->compile(expression, strlen(expression));
	
	yuka::VM *vm = new yuka::VM;
	yuka::t_yuka_value result = vm->run(bc);

	cout << "Result: " << result.int_value << endl;
	cout << "Result: " << result.float_value << endl;

	delete bc;
	delete compiler;
	delete vm;

	return 0;
}
