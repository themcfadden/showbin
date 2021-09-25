
#include "showbin.hpp"
#include <cstring>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;


const char* BINARY_PREFIX {"0b"};
//const char* BINARY_SHORT_PREFIX {"b"};
//const char* BINARY_POSTFIX {"b"};
const char* HEX_PREFIX {"0x"};
//const char* HEX_SHORT_PREFIX {"x"};
//const char* HEX_POSTFIX {"x"};
const char* OCTAL_PREFIX {"0o"};
//const char* OCTAL_SHORT_PREFIX {"o"};
//const char* OCT_POSTFIX {"o"};

//
// Private
//

//
// Helpers
//
string Base::_trim(char const *str)
{
  // Trim leading non-letters
  while(!isalnum(*str)) str++;

  // Trim trailing non-letters
  const char* end = str + strlen(str) - 1;
  while(end > str && !isalnum(*end)) end--;

  return string(str, end+1);
}


std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

bool NumberTypeParser::_onlyHasHexDigits(string s) {
    s = str_tolower(s);
    return s.find_first_not_of( "0123456789abcdef" ) == string::npos;
}

bool NumberTypeParser::_onlyHasDigits(string s) {
    return s.find_first_not_of( "0123456789" ) == string::npos;
}

bool NumberTypeParser::_onlyHasOctalDigits(string s) {
    return s.find_first_not_of( "012345678" ) == string::npos;
}

bool NumberTypeParser::_onlyHasBinaryDigits(string s) {
    return s.find_first_not_of( "01" ) == string::npos;
}

const char * NumberTypeParser::_movePastPrefixIfPresent(std::string in) {
    in = str_tolower(in);
    const char* newStart;

    if (_hasPrefix(BINARY_PREFIX, in) ||
        _hasPrefix(HEX_PREFIX, in) ||
        _hasPrefix(OCTAL_PREFIX, in) ) {

        newStart = in.c_str();
        newStart += 2 * sizeof(char);
    }
    return newStart;
}

bool NumberTypeParser::_prefixedNumberOnlyHasHexDigits(std::string in)
{
    const char* newStart = _movePastPrefixIfPresent(in);
    return _onlyHasHexDigits(newStart);
}

bool NumberTypeParser::_prefixedNumberOnlyHasOctalDigits(std::string in)
{
    const char* newStart = _movePastPrefixIfPresent(in);
    return _onlyHasOctalDigits(newStart);
}

bool NumberTypeParser::_prefixedNumberOnlyHasDigits(std::string in)
{
    const char* newStart = _movePastPrefixIfPresent(in);
    return _onlyHasDigits(newStart);
}

bool NumberTypeParser::_prefixedNumberOnlyHasBinaryDigits(std::string in)
{
    const char* newStart = _movePastPrefixIfPresent(in);
    return _onlyHasBinaryDigits(newStart);
}


bool NumberTypeParser::_hasPrefix(std::string prefix, std::string in)
{
    DEBUG_PRINT(in + " ");
    DEBUG_PRINT(prefix + "\n");
    if (in.find(prefix) == 0) DEBUG_PRINT("Has prefix\n");
    else DEBUG_PRINT("NO prefix\n");
    return in.find(prefix) == 0;
}

bool NumberTypeParser::_isDecimalNumber(std::string in)
{
    DEBUG_PRINT(in + "\n");
    if (_onlyHasDigits(in)) {
        DEBUG_PRINT("only has digits\n");
        return true;
    }
    else {
        DEBUG_PRINT("number does not have only digits\n");
        return false;
    }
}

bool NumberTypeParser::_isOctalNumber(std::string in)
{
    if (_hasPrefix(OCTAL_PREFIX, in)) {
        if (_prefixedNumberOnlyHasOctalDigits(in)) {
            return true;
        }
    }
    return false;
}

bool NumberTypeParser::_isHexNumber(std::string in)
{
    if (_hasPrefix(HEX_PREFIX, in)) {
        if (_prefixedNumberOnlyHasHexDigits(in)) {
            return true;
        }
    }
    return false;
}

bool NumberTypeParser::_isBinaryNumber(std::string in)
{
    if (_hasPrefix(BINARY_PREFIX, in)) {
        if (_prefixedNumberOnlyHasBinaryDigits(in)) {
            return true;
        }
    }
    return false;
}


enum NumberType NumberTypeParser::getNumberType(std::string in)
{
    if (_isDecimalNumber(in)) return NumberType::Decimal;
    else if (_isOctalNumber(in)) return NumberType::Octal;
    else if (_isHexNumber(in)) return NumberType::Hexidecimal;
    else if (_isBinaryNumber(in)) return NumberType::Binary;
    else return NumberType::Unknown;
}

//
//
//
bool Base::_checkForPrefix(string prefix, string in) {
    return in.rfind(prefix, 0) == 0;
}

//bool Base::_checkForShortPrefix(string prefix, string in) {
//    return in.rfind(BINARY_SHORT_PREFIX, 0) == 0;
//}

NumberType Base::detectBase(std::string inString) {
    const auto c_string = inString.c_str();
    auto s = _trim(c_string);

    return NumberTypeParser::getNumberType(s);
}
