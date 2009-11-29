/* vim:ts=4 sts=4 et tw=80
 *
 *         fnordlicht firmware next generation
 *
 *    for additional information please
 *    see http://lochraster.org/fnordlicht
 *
 * (c) by Alexander Neumann <alexander@bumpern.de>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STATIC_PROGRAMS_H
#define __STATIC_PROGRAMS_H

#include <stdint.h>
#include "config.h"
#include "pt/pt.h"

struct process_t;
/* return value is char, see definition of PT_THREAD() */
typedef char (*program_handler)(struct process_t *current);

/* parameter structures (max 10 bytes) */
struct colorwheel_params_t
{
    uint8_t fade_step;
    uint8_t fade_delay;
    uint8_t fade_sleep;
    uint16_t hue_start;
    int16_t hue_step;
    uint8_t saturation;
    uint8_t value;
};

struct random_params_t
{
    uint16_t seed;
    uint8_t use_address;
    uint8_t fade_step;
    uint8_t fade_delay;
    uint8_t fade_sleep;
    uint8_t saturation;
    uint8_t value;
    uint8_t min_distance;
};

union program_params_t
{
    /* parameters for static programs */
    uint8_t raw[PROGRAM_PARAMETER_SIZE];
    struct colorwheel_params_t colorwheel;
    struct random_params_t random;
};

/* global process struct */
struct process_t {
    program_handler execute;
    struct pt pt;
    uint8_t enable:1;
    union program_params_t params;
};

#if CONFIG_SCRIPT

/* global list of programs */
#define STATIC_PROGRAMS_LEN 2
extern program_handler static_programs[];

PT_THREAD(program_colorwheel(struct process_t *process));
PT_THREAD(program_random(struct process_t *process));

#endif
#endif