/*
 * machine.h
 */

#ifndef MACHINE_H
#define MACHINE_H

#include <stdint.h>
#include <stdbool.h>

struct Machine {
     uint16_t M[256];  /* memory */
     int16_t  ACC;     /* accumulator */
     uint16_t PC;      /* program counter */
     bool     HALT;
};
#endif
