Yuka
====

Yuka is a lightweight expression evaluator writen in C++. 

How To Use It
-------------

Just create an instance of `yuka::Compiler` and use it for compiling your expression into Yuka bytecode. The bytecode can later be fed to an instance of `yuka::VM` for evaluation.

	#include "yuka/yuka.h"
	...
	char expression[] = "(5^2)+3*5";
	yuka::Compiler *compiler = new yuka::Compiler();
	yuka::ByteCode *bc = compiler->compile(expression, strlen(expression));

	yuka::VM *vm = new yuka::VM;
	yuka::t_yuka_value result = vm->run(bc);
	cout << result.int_value << endl; // 40

TODO:
-----

* Add support for constants (and variables?)
* Function support

