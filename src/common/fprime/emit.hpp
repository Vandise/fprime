#ifndef __FP_EMIT_HPP__
#define __FP_EMIT_HPP__ 1

#define EMIT_0(opcode)             \
{                                  \
  cg->push_buffer(                 \
    cg->instruction(opcode));      \
  cg->push_line();                 \
}

#define EMIT_1(opcode, operand1)   \
{                                  \
  cg->push_buffer(                 \
    cg->instruction(opcode));      \
  cg->push_buffer(operand1);       \
  cg->push_line();                 \
}

#define EMIT_2(opcode, operand1, operand2)   \
{                                            \
  cg->push_buffer(                           \
    cg->instruction(opcode));                \
  cg->push_buffer(operand1);                 \
  cg->push_buffer(", ");                     \
  cg->push_buffer(operand2);                 \
  cg->push_line();                           \
}

#define EMIT_FRAME_START(cg)                        \
{                                                   \
  cg->push_buffer("push    rbp\nmov     rbp, rsp"); \
  cg->push_line();                                  \
}

#define EMIT_FRAME_EXIT(cg)           \
{                                     \
  cg->push_buffer("pop    rbp\nret"); \
  cg->push_line();                    \
}

#endif