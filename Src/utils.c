/*
 * utils.c
 *
 *  Created on: Jul 7, 2019
 *      Author: kriive
 */
#include "utils.h"

// Implementation from -- https://www.arduino.cc/reference/en/language/functions/math/map/#_appendix
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
