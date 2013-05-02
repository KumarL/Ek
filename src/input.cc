#include "input.h"

Input::Input(
        const std::string& _name,
        const std::string& _value,
        const bool _name_optional,
        const bool _value_optional) 
  : m_Name(_name),
    m_Value(_value),
    m_Name_Optional(_name_optional),
    m_Value_Optional(_value_optional)
{
}

Input::Input(
        const std::string& _name,
        const bool _name_optional) : m_Name(_name),
    m_Value(""),
    m_Name_Optional(_name_optional),
    m_Value_Optional(false)
{
}

const std::string&
Input::get_name() const {
  return m_Name;
}

const std::string&
Input::get_value() const {
  return m_Value;
}

const bool
Input::has_value() const {
  return !get_value().empty();
}

const bool
Input::is_name_optional() const {
  return m_Name_Optional;
}

const bool
Input::is_value_optional() const {
  return m_Value_Optional;
}

const bool
Input::is_flag() const {
  return !has_value() && is_name_optional();
}
