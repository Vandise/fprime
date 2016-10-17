#ifndef __FPRIME_HPP__
#define __FPRIME_HPP__ 1

enum FDataType {
  UNDEFINED,

/* SPECIAL TYPES */
  BYTE,
  BOOLEAN,
  POINTER,

/* DEFAULT BEHAVIOR INTEGERS */
  INT_8,                     // same as BYTE 
  INT_16,
  INT_32,
  INT_64,
  INTEGER,

/* DECIMALS */
  FLOAT,
  DOUBLE,

/* STRINGS */
  CHAR,
  STRING,

/* ITERABLE */
  ARRAY

};

#endif