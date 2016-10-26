#include <cctype>
#include <fstream>
#include <cassert>
#include "headers/driver.hpp"
#include "util/debug_new/debug_new.h"

FrontEnd::Driver::~Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

int
FrontEnd::Driver::parse( const char *const filename )
{
  file = std::string(filename);
  assert(filename != nullptr);
  std::ifstream in_file( filename );
  if( !in_file.good() )
  {
    std::cout << "File not found " << filename << std::endl;
    return EXIT_FAILURE;
  }

  delete(scanner);
  try
  {
    scanner = new FrontEnd::Scanner( &in_file, file);
  }
  catch( std::bad_alloc &ba )
  {
    std::cerr << "Failed to allocate scanner: (" <<
      ba.what() << "), exiting!!\n";
    return ( EXIT_FAILURE );
  }

  delete(parser);

  try
  {
    parser = new FrontEnd::Parser( *scanner, *this );
  }
  catch( std::bad_alloc &ba )
  {
    std::cerr << "Failed to allocate parser: (" <<
      ba.what() << "), exiting!!\n";
    return ( EXIT_FAILURE );
  }

  parser->parse();

  return ( EXIT_SUCCESS );
}

void
FrontEnd::Driver::push_stack( std::vector<AST::AbstractNode*> stack)
{
  for (int i = 0; i < stack.size(); i++)
  {
    AST::Stack::nodes.push_back( stack[i] );
  }
}

void
FrontEnd::Driver::push_node( AST::AbstractNode *node )
{
  AST::Stack::nodes.push_back(node);
}
