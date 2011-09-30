#include <stdio.h>
#include <string.h>

#include <vector>

#include "compiler.h"
#include "vm.h"

int main() {
	char expression[] = "5 + ((1 + 2) * 4) - 3";

	yuka::Compiler *compiler = new yuka::Compiler();
	yuka::ByteCode *bc = compiler->compile(expression, strlen(expression));

	yuka::VM *vm = new yuka::VM;
	int result = vm->run(bc);

	delete bc;
	delete compiler;
	delete vm;

	//FILE *f = fopen("exp.ybc", "wb");
	//fwrite(bc->getCode(), 1, bc->getSize(), f);
	//fclose(f);

	return 0;
}
