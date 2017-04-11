#include "headers/sectionManager.hpp"

Generator::SectionManager::~SectionManager()
{

}

Generator::SectionManager::SectionManager()
{
  this->sections["text"] = std::vector<std::string>();
  this->sections["bss"] = std::vector<std::string>();
  this->sections["data"] = std::vector<std::string>();
}

void
Generator::SectionManager::add_section(std::string section_name)
{
  this->sections[section_name] = std::vector<std::string>();
}

void
Generator::SectionManager::push_section(std::string section_name, std::string section_line)
{
  this->sections[section_name].push_back(section_line);
}

std::map< std::string, std::vector<std::string> >
Generator::SectionManager::get_sections()
{
  return this->sections;
}