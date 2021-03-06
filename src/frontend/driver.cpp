#include <cctype>
#include <fstream>
#include <cassert>

#include "headers/driver.hpp"

FrontEnd::Driver::~Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
   delete(stack);
   stack = nullptr;
}

void
FrontEnd::Driver::push_stack()
{

}

void
FrontEnd::Driver::push_node()
{

}

int
FrontEnd::Driver::parse( const char * const filename )
{
   file = std::string(filename);
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() ) exit( EXIT_FAILURE );

   delete(scanner);
   try
   {
      scanner = new FrontEnd::Scanner( &in_file, std::string(filename) );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   delete(parser);
   try
   {
      parser = new FrontEnd::Parser( (*scanner), (*this) );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }

   return parser->parse();
}
