#ifndef __FPRIME_NODES_HPP__
#define __FPRIME_NODES_HPP__ 1

#define fp_string_node(s_ptr) new AST::LiteralNode(*s_ptr, STRING); 
#define fp_int32_node(i) new AST::LiteralNode(i, INT_32);
#define fp_assignment_node(type, s_ptr, expr) new AST::AssignmentNode(type, *s_ptr, expr);

#endif