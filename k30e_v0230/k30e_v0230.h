//#ifndef KB_H
//#define KB_H

#pragma once
#include "quantum.h"

//#include "config_common.h"

// 아래 layout 안에는 절대 다른문자가 들어가면 안됨 코맨트도 안됨

#define XXX KC_NO
/*
#define LAYOUT( \
  	K00, K01, K02, K03, \
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
	{ K50,   XXX,   K52,   XXX }, \
}*/

//// 위 layout에서 digital encoder(CC,button,CCW)를 키맵에 추가, 버튼은 원래키,
//// 가상으로 CCW는 K51, CC는 K53 (230403)
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

/* Function Prototype */
void off_all_leds(void);
void on_all_leds(void);

//#endif
