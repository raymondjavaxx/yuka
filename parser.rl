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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#ifdef DEBUG
#define YUKA_DEBUG(STR) printf(STR);
#define YUKA_DEBUGF(STR, ARG1) printf(STR, ARG1);
#else
#define YUKA_DEBUG(STR)
#define YUKA_DEBUGF(STR, ARG1)
#endif

namespace yuka {

%%{
	machine yuka_script;

	newline = '\n' @{ curline += 1; };

	any_count_line = any | newline;

	main := |*
		# Alpha numberic characters or underscore.
		alnum_u = alnum | '_';

		# Alpha charactres or underscore.
		alpha_u = alpha | '_';

		add_operator = '+';
		sub_operator = '-';
		mul_operator = '*';
		div_operator = '/';
		
		exponentiation = '^';

		parentesis_open = '(';
		parentesis_close = ')';

		parentesis_open {
			YUKA_DEBUG("open parentesis\n")
			TokenObj *obj = new TokenObj(Token_OpenParentesis);
			tokens.push_back(obj);
		};

		parentesis_close {
			YUKA_DEBUG("close parentesis\n")
			TokenObj *obj = new TokenObj(Token_CloseParentesis);
			tokens.push_back(obj);
		};

		add_operator {
			YUKA_DEBUG("plus\n")
			TokenObj *obj = new TokenObj(Token_Add);
			tokens.push_back(obj);
		};

		sub_operator {
			YUKA_DEBUG("minus\n")
			TokenObj *obj = new TokenObj(Token_Sub);
			tokens.push_back(obj);
		};

		mul_operator {
			YUKA_DEBUG("mul\n")
			TokenObj *obj = new TokenObj(Token_Mul);
			tokens.push_back(obj);
		};

		div_operator {
			YUKA_DEBUG("div\n")
			TokenObj *obj = new TokenObj(Token_Div);
			tokens.push_back(obj);
		};

		exponentiation {
			YUKA_DEBUG("exp\n")
			TokenObj *obj = new TokenObj(Token_Pow);
			tokens.push_back(obj);
		};

		digit+ {
			char number[32] = {0};
			strncpy(number, ts, MIN(te-ts, 32));
			YUKA_DEBUGF("number %d\n", atoi(number))

			TokenObj *obj = new TokenObj(Token_Number);
			obj->setIntValue(atoi(number));

			tokens.push_back(obj);
		};

    digit* '.' digit+ | digit+ '.' {
		  char number[32] = {0};
		  strncpy(number, ts, MIN(te-ts, 32));
		  YUKA_DEBUGF("number %f\n", atof(number))

		  TokenObj *obj = new TokenObj(Token_Number);
		  obj->setFloatValue(static_cast<float>(atof(number)));

		  tokens.push_back(obj);
    };

		# consume whitespace
		(any - 33..126)+;
	*|;
}%%

%% write data nofinal;

Parser::Parser() {
	// construct
}

Parser::~Parser() {
	//destroy
}

TokenObjVector Parser::parse(const char *data, size_t len) {
	std::vector<TokenObj*> tokens;

	const char *p = data;
	const char *pe = data + len;
	int cs;
	int act;
	char *ts;
	char *te;
	char *eof = pe;
	//int curline = 1;

	%% write init;

	%% write exec;

	if (cs == yuka_script_error) {
		fprintf(stderr, "PARSE ERROR\n");
	}

	return tokens;
}

}// namespace yuka
