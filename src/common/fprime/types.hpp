#ifndef __FPRIME_TYPES_HPP__
#define __FPRIME_TYPES_HPP__ 1

typedef enum {
  VOID     = 0x0000,
  INT_32   = 0x0001,
  INT_64   = 0x0002,
  FLOAT_32 = 0x0003,
  FLOAT_64 = 0x0004,      /* double alias */
  DOUBLE   = 0x0005,
  STRING   = 0x0006
} FPTYPE;

#endif