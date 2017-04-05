#ifndef __FRAME_HPP__
#define __FRAME_HPP__ 1

#include <string>

/*
  Frame Container
*/
namespace Generator
{
  class Frame
  {
    private:
      std::string label;

    public:
      Frame(std::string label);
      virtual ~Frame();
      std::string get_label();
  };
}

#endif