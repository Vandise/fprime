#ifndef __SECTION_MANAGER_HPP__
#define __SECTION_MANAGER_HPP__ 1

#include <string>
#include <vector>
#include <map>

namespace Generator
{
  class SectionManager
  {
    private:
      std::map< std::string, std::vector<std::string> > sections;

    public:
      SectionManager();
      virtual ~SectionManager();
      void add_section(std::string section_name);
      void push_section(std::string section_name, std::string section_line);
      std::map< std::string, std::vector<std::string> > get_sections();
  };
}

#endif