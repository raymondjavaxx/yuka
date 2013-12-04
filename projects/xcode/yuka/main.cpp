//
//  main.cpp
//  yuka
//
//  Created by Ramon Torres on 9/29/11.
//  Copyright 2011 Ramon Torres. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "compiler.h"
#include "vm.h"

using namespace std;

int main (int argc, const char * argv[]) {
	char expression[] = "(1/4) * (4 - 1/2)";

	yuka::Compiler *compiler = new yuka::Compiler();
	yuka::ByteCode *bc = compiler->compile(expression, strlen(expression));
	
	yuka::VM *vm = new yuka::VM;
	yuka::Value result = vm->run(bc);

	cout << "Result: " << result.int_value << endl;
	cout << "Result: " << result.float_value << endl;

	delete bc;
	delete compiler;
	delete vm;

    return 0;
}

