#ifndef _INPUT_HEADER_
#define _INPUT_HEADER_
#include <string>

class Input {
  private:
    std::string m_Name;
    std::string m_Value;
    bool        m_Name_Optional;
    bool        m_Value_Optional;


  public:
    Input (
        const std::string& _name,
        const std::string& _value,
        const bool _name_optional,
        const bool _value_optional);

    Input (
        const std::string& _name,
        const bool _name_optional);

    const std::string&  get_name()          const;
    const std::string&  get_value()         const;
    const bool          has_value()         const;
    const bool          is_flag()           const;
    const bool          is_name_optional()  const;
    const bool          is_value_optional() const;
};
#endif
