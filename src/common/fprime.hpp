#ifndef __FPRIME_HPP__
#define __FPRIME_HPP__ 1

typedef enum e_FPTYPE {
  VOID     = 0x0,
  INT_32   = 0x1,
  INT_64   = 0x2,
  FLOAT_32 = 0x3,
  FLOAT_64 = 0x4,      /* double alias */
  DOUBLE   = 0x5,
  STRING   = 0x6
} FPTYPE;

#endif
