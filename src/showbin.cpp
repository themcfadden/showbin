
#include "../inc/showbin.hpp"
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

std::string NumberTypeParser::_str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

string NumberTypeParser::_trim(char const *str)
{
  // Trim leading non-letters
  while(!isalnum(*str)) str++;

  // Trim trailing non-letters
  const char* end = str + strlen(str) - 1;
  while(end > str && !isalnum(*end)) end--;

  return string(str, end+1);
}


bool NumberTypeParser::_onlyHasHexDigits(string s) {
    s = _str_tolower(s);
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

//const char * NumberTypeParser::_movePastPrefixIfPresent(std::string in) {
const string NumberTypeParser::_movePastPrefixIfPresent(std::string in) {
    in = _str_tolower(in);
    const char* newStart;

    if (_hasPrefix(BINARY_PREFIX, in) ||
        _hasPrefix(HEX_PREFIX, in) ||
        _hasPrefix(OCTAL_PREFIX, in) ) {

        newStart = in.c_str();
        newStart += 2 * sizeof(char);
    }
    return newStart;
}


bool NumberTypeParser::_hasPrefix(std::string prefix, std::string in)
{
//    DEBUG_PRINT(in + " ");
//    DEBUG_PRINT(prefix + "\n");
//    if (in.find(prefix) == 0) DEBUG_PRINT("Has prefix\n");
//    else DEBUG_PRINT("NO prefix\n");
    return in.find(prefix) == 0;
}

int NumberTypeParser::parseToInt(std::string in) {
    int digitPosition {1};
    int n {0};

    for(int i = in.size(); i > 0; i--) {
        n += (in[i-1] - '0') * digitPosition;
        digitPosition *= 10;
    }
    return n;
}

int NumberTypeParser::parseHexToInt(std::string in) {
    int digitPosition {1};
    int n {0};

    in = _movePastPrefixIfPresent(in);

    for(int i = in.size(); i > 0; i--) {
        if (isdigit(in[i-1])) {
            n += (in[i-1] - '0') * digitPosition;
        } else if (isalpha(in[i-1])) {
            n += (10 + in[i-1] - 'a') * digitPosition;
        }
        digitPosition *= 16;
    }
    return n;
}

int NumberTypeParser::parseOctalToInt(std::string in) {
    int digitPosition {1};
    int n {0};

    in = _movePastPrefixIfPresent(in);

    for(int i = in.size(); i > 0; i--) {
        if (isdigit(in[i-1])) {
            n += (in[i-1] - '0') * digitPosition;
        }
        digitPosition *= 8;
    }
    return n;
}


//
//
//
//bool ShowBin::_checkForPrefix(string prefix, string in) {
//    return in.rfind(prefix, 0) == 0;
//}

//bool ShowBin::_checkForShortPrefix(string prefix, string in) {
//    return in.rfind(BINARY_SHORT_PREFIX, 0) == 0;
//}


bool NumberTypeParser::_prefixedNumberOnlyHasHexDigits(std::string in)
{
    const std::string newStart = _movePastPrefixIfPresent(in);
    return _onlyHasHexDigits(newStart);
}

bool NumberTypeParser::_prefixedNumberOnlyHasOctalDigits(std::string in)
{
    const std::string newStart = _movePastPrefixIfPresent(in);
    return _onlyHasOctalDigits(newStart);
}

bool NumberTypeParser::_prefixedNumberOnlyHasDigits(std::string in)
{
    const std::string newStart = _movePastPrefixIfPresent(in);
    return _onlyHasDigits(newStart);
}

bool NumberTypeParser::_prefixedNumberOnlyHasBinaryDigits(std::string in)
{
    const std::string newStart = _movePastPrefixIfPresent(in);
    return _onlyHasBinaryDigits(newStart);
}

bool NumberTypeParser::_isDecimalNumber(std::string in)
{
//    DEBUG_PRINT(in + "\n");
    if (_onlyHasDigits(in)) {
//        DEBUG_PRINT("only has digits\n");
        return true;
    }
    else {
//        DEBUG_PRINT("number does not have only digits\n");
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

enum NumberType NumberTypeParser::detectBase(std::string inString) {
    const auto c_string = inString.c_str();
    auto s = _trim(c_string);

    return NumberTypeParser::getNumberType(s);
}

int ShowBin::convertToNumber(std::string in) {
    int n {-1};

    switch (NumberTypeParser::detectBase(in)) {
        case NumberType::Binary:
            cout << "Not implemented yet\n";
            break;
        case NumberType::Decimal:
            return NumberTypeParser::parseToInt(in);
            break;
        case NumberType::Octal:
            return NumberTypeParser::parseOctalToInt(in);
            break;
        case NumberType::Hexidecimal:
            return NumberTypeParser::parseHexToInt(in);
            break;
        default:
            DEBUG_PRINT("Unknown number type\n");
            break;
    }
    return -1;
}

void ShowBin::displayAsPrettyBinary(int n) {
    char buffer[64] {0};
    char* p = buffer + 64;

    do
    {
        *--p = '0' + (n & 1);
    } while (n >>= 1);

    string outString = std::string(p, buffer + 64);

    // |33222222222211111111110000000000|
    // |10987654321098765432109876543210|
    // |--------------------------------|
    // |01010101010101010101010101010101|

    int outLength = outString.size();

    for (int sizer = 8; sizer < 64; sizer += 8) {
        if (outLength <= sizer) {
            outLength = sizer;
            break;
        }
    }

    cout << "|";
    for (int i = outLength - 1; i >= 0; i--) {
        cout << i/10;
    }
    cout << "|" << endl << "|";
    for (int i = outLength - 1; i >= 0; i--) {
        cout << i % 10;
    }
    cout << "|" << endl << "|";
    for (int i = outLength - 1; i >= 0; i--) {
        cout << "-";
    }
    cout << "|" << endl << "|";
    for (int i = 0; i < outLength - outString.size(); i++) {
        cout << "0";
    }
    cout << outString;
    cout << "|" << endl;


}

void ShowBin::convertAndDisplay(std::string in) {

    int n = convertToNumber(in);
    displayAsPrettyBinary(n);

}
