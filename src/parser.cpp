
/* #line 1 "parser.rl" */
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


/* #line 123 "parser.rl" */



/* #line 48 "src/parser.cpp" */
static const char _yuka_script_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10
};

static const char _yuka_script_key_offsets[] = {
	0, 0, 2, 15, 17, 19
};

static const char _yuka_script_trans_keys[] = {
	48, 57, 40, 41, 42, 43, 45, 46, 
	47, 33, 44, 48, 57, 58, 126, 33, 
	126, 48, 57, 46, 48, 57, 0
};

static const char _yuka_script_single_lengths[] = {
	0, 0, 7, 0, 0, 1
};

static const char _yuka_script_range_lengths[] = {
	0, 1, 3, 1, 1, 1
};

static const char _yuka_script_index_offsets[] = {
	0, 0, 2, 13, 15, 17
};

static const char _yuka_script_trans_targs[] = {
	4, 0, 2, 2, 2, 2, 2, 1, 
	2, 0, 5, 0, 3, 2, 3, 4, 
	2, 4, 5, 2, 2, 2, 2, 0
};

static const char _yuka_script_trans_actions[] = {
	0, 0, 5, 7, 13, 9, 11, 0, 
	15, 0, 0, 0, 0, 21, 0, 0, 
	19, 0, 0, 17, 21, 19, 17, 0
};

static const char _yuka_script_to_state_actions[] = {
	0, 0, 1, 0, 0, 0
};

static const char _yuka_script_from_state_actions[] = {
	0, 0, 3, 0, 0, 0
};

static const char _yuka_script_eof_trans[] = {
	0, 0, 0, 21, 22, 23
};

static const int yuka_script_start = 2;
static const int yuka_script_error = 0;

static const int yuka_script_en_main = 2;


/* #line 126 "parser.rl" */

Parser::Parser() {
	// construct
}

Parser::~Parser() {
	//destroy
}

TokenObjVector Parser::parse(char *data, size_t len) {
	std::vector<TokenObj*> tokens;

	char *p = data;
	char *pe = data + len;
	int cs;
	int act;
	char *ts;
	char *te;
	char *eof = pe;
	//int curline = 1;

	
/* #line 130 "src/parser.cpp" */
	{
	cs = yuka_script_start;
	ts = 0;
	te = 0;
	act = 0;
	}

/* #line 148 "parser.rl" */

	
/* #line 141 "src/parser.cpp" */
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_acts = _yuka_script_actions + _yuka_script_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
/* #line 1 "NONE" */
	{ts = p;}
	break;
/* #line 162 "src/parser.cpp" */
		}
	}

	_keys = _yuka_script_trans_keys + _yuka_script_key_offsets[cs];
	_trans = _yuka_script_index_offsets[cs];

	_klen = _yuka_script_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _yuka_script_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _yuka_script_trans_targs[_trans];

	if ( _yuka_script_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _yuka_script_actions + _yuka_script_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
/* #line 62 "parser.rl" */
	{te = p+1;{
			YUKA_DEBUG("open parentesis\n")
			TokenObj *obj = new TokenObj(Token_OpenParentesis);
			tokens.push_back(obj);
		}}
	break;
	case 3:
/* #line 68 "parser.rl" */
	{te = p+1;{
			YUKA_DEBUG("close parentesis\n")
			TokenObj *obj = new TokenObj(Token_CloseParentesis);
			tokens.push_back(obj);
		}}
	break;
	case 4:
/* #line 74 "parser.rl" */
	{te = p+1;{
			YUKA_DEBUG("plus\n")
			TokenObj *obj = new TokenObj(Token_Add);
			tokens.push_back(obj);
		}}
	break;
	case 5:
/* #line 80 "parser.rl" */
	{te = p+1;{
			YUKA_DEBUG("minus\n")
			TokenObj *obj = new TokenObj(Token_Sub);
			tokens.push_back(obj);
		}}
	break;
	case 6:
/* #line 86 "parser.rl" */
	{te = p+1;{
			YUKA_DEBUG("mul\n")
			TokenObj *obj = new TokenObj(Token_Mul);
			tokens.push_back(obj);
		}}
	break;
	case 7:
/* #line 92 "parser.rl" */
	{te = p+1;{
			YUKA_DEBUG("div\n")
			TokenObj *obj = new TokenObj(Token_Div);
			tokens.push_back(obj);
		}}
	break;
	case 8:
/* #line 98 "parser.rl" */
	{te = p;p--;{
			char number[32] = {0};
			strncpy(number, ts, MIN(te-ts, 32));
			YUKA_DEBUGF("number %d\n", atoi(number))

			TokenObj *obj = new TokenObj(Token_Number);
			obj->setIntValue(atoi(number));

			tokens.push_back(obj);
		}}
	break;
	case 9:
/* #line 109 "parser.rl" */
	{te = p;p--;{
		  char number[32] = {0};
		  strncpy(number, ts, MIN(te-ts, 32));
		  YUKA_DEBUGF("number %f\n", atof(number))

		  TokenObj *obj = new TokenObj(Token_Number);
		  obj->setFloatValue(static_cast<float>(atof(number)));

		  tokens.push_back(obj);
    }}
	break;
	case 10:
/* #line 121 "parser.rl" */
	{te = p;p--;}
	break;
/* #line 305 "src/parser.cpp" */
		}
	}

_again:
	_acts = _yuka_script_actions + _yuka_script_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
/* #line 1 "NONE" */
	{ts = 0;}
	break;
/* #line 318 "src/parser.cpp" */
		}
	}

	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _yuka_script_eof_trans[cs] > 0 ) {
		_trans = _yuka_script_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	_out: {}
	}

/* #line 150 "parser.rl" */

	if (cs == yuka_script_error) {
		fprintf(stderr, "PARSE ERROR\n");
	}

	return tokens;
}

}// namespace yuka
