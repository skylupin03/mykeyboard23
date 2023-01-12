/*
Copyright 2021 Don Kjer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
/* HSE=>   8Mhz     12MHz     (board.h)
  PLLMUL    6         4       (mcuconf.h)  */

#define STM32_HSECLK                12000000U       // 8000000U, 12000000U
#include_next <board.h>
#undef STM32_HSE_BYPASS
