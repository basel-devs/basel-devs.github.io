#ifndef JS_DOM_HPP
#define JS_DOM_HPP

#include <locale>
#include <codecvt> 

#include <js/bind.hpp>

namespace js {
  
  /**
   * \param a JS encoded string (UTF16 or else)
   * \returns an UTF-8 string
   */
  inline std::string to_string(const emscripten::val& js_ref) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.to_bytes( js_ref.as<std::wstring>() );
  }

}

#endif
