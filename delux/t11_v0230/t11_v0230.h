//#ifndef KB_H
//#define KB_H

#pragma once
#include "quantum.h"

//#include "config_common.h"

// 아래 layout 안에는 절대 다른문자가 들어가면 안됨 코맨트도 안됨

#define XXX KC_NO

/* << K20 original layout >>
#define LAYOUT( \
	K00, K01, K02, \
	K10, K11, K12, \
	K20, K21, K22, \
	K30, K31, K32, \
	K40, K41, K42, \
	K50, K51, K52, \
	K60, K61,      \
	K70  \
) { \
	{ K00,   K01,   K02 }, \
	{ K10,   K11,   K12 }, \
	{ K20,   K21,   K22 }, \
	{ K30,   K31,   K32 }, \
	{ K40,   K41,   K42 }, \
	{ K50,   K51,   K52 }, \
	{ K60,   K61,   KC_NO }, \
	{ K70,   KC_NO, KC_NO }  \
}

//	(엔코더 CC, CCW를 키에 맵핑)
#define LAYOUT( \
	K00, K01, K02, K70, K71, K62, K72,\
	K10, K11, K12, K61, \
	K20, K21, K22, K60,\
	K30, K31, K32, \
	K40, K41, K42, K52, \
	K50,      K51 \
  \
) { \
	{ K00,   K01,   K02 }, \
	{ K10,   K11,   K12 }, \
	{ K20,   K21,   K22 }, \
	{ K30,   K31,   K32 }, \
	{ K40,   K41,   K42 }, \
	{ K50,   K51,   K52 }, \
	{ K60,   K61,   K62 }, \
	{ K70,   K71,   K72 }  \
}
*/

/* << K20 RGB dual encoder (waycos에서 설계) >> */
/*
#define LAYOUT( \
  	K00, K01, K02, K03, \
	K10, K11, K12, K13, \
	K20, K21, K22, K33,\
	K30, K31, K32, \
	K40, K41, K42, K53,\
	K50,      K52 \
) { \
    { K00,   K01,   K02,   K03 }, \
	{ K10,   K11,   K12,   K13 }, \
	{ K20,   K21,   K22,   XXX }, \
	{ K30,   K31,   K32,   K33 }, \
	{ K40,   K41,   K42,   XXX }, \
	{ K50,   XXX,   K52,   K53 }, \
}
*/

/* << K30 RGB single encoder (Metable에서의 첫 설계) >>
	(엔코더 CC, CCW를 키에 맵핑했었음)
#define LAYOUT( \
  	K00, K01, K02, K51, K03, K53,\
	K10, K11, K12, K13, \
	K20, K21, K22, K23, \
	K30, K31, K32, \
	K40, K41, K42, K43, \
	K50,      K52 \
) { \
    { K00,   K01,   K02,   K03 }, \
	{ K10,   K11,   K12,   K13 }, \
	{ K20,   K21,   K22,   K23 }, \
	{ K30,   K31,   K32,   XXX }, \
	{ K40,   K41,   K42,   K43 }, \
	{ K50,   K51,   K52,   K53 }, \
}
*/

// << Delux 한손키보드, Designer T11. RGB, single encoder (waycos에서 점퍼, 만듬) >>

#define LAYOUT( \
	K00, K01, K02, K03, \
	K10, K11, K12, K13, K14, K15, K16, K17, \
	K20, K21, K22, K23, K24, K25, K26, \
	K30, K31, K32, K33, K34, \
	K40, K41, K42, K43, K44 \
) { \
    { K00,   K01,   K02,   K03,   XXX,   XXX,   XXX,   XXX }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17 }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26,   XXX }, \
	{ K30,   K31,   K32,   K33,   K34,   XXX,   XXX,   XXX }, \
	{ K40,   K41,   K42,   K43,   K44,   XXX,   XXX,   XXX } \
}

/* Function Prototype */
void off_all_leds(void);
void on_all_leds(void);

//#endif
