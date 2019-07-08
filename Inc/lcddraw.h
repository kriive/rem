/*
 * lcddraw.h
 *
 *  Created on: Jun 5, 2019
 *      Author: kriive
 */

#ifndef LCDDRAW_H_
#define LCDDRAW_H_
#include "stm32f4xx_hal.h"

#define	ROW_INFINITE_COUNTER	1
#define ROW_SHORT_COUNTER		0

#define	UNIT_CPM	0
#define UNIT_nSM	1

void DrawFirstRow(const uint64_t secondsSinceStartup, const uint64_t potvalue, const uint64_t counter, const uint8_t unitMeasure);
void DrawSecondRow(const uint64_t secondsSinceStartup, const uint64_t counter, const uint8_t unitMeasure);

#endif /* LCDDRAW_H_ */
