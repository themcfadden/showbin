#ifndef __NUMTYPEPARSER_H__
#define __NUMTYPEPARSER_H__

#include <string>


#define DEBUG_PRINT(msg) cout << __FILE__ << ":" <<__LINE__ << ": " << (msg) << std::endl;
//#define DEBUG_PRINT(msg) ((void) (msg))

const char* BINARY_PREFIX {"0b"};
//const char* BINARY_SHORT_PREFIX {"b"};
//const char* BINARY_POSTFIX {"b"};
const char* HEX_PREFIX {"0x"};
//const char* HEX_SHORT_PREFIX {"x"};
//const char* HEX_POSTFIX {"x"};
const char* OCTAL_PREFIX {"0o"};
//const char* OCTAL_SHORT_PREFIX {"o"};
//const char* OCT_POSTFIX {"o"};

enum class NumberType {Unknown, Binary, Octal, Decimal, Hexidecimal};

class NumberTypeParser
{
    public:
        NumberTypeParser() {}
        static enum NumberType getNumberType(std::string in);
        static int parseToInt(std::string in);
        static int parseHexToInt(std::string in);

    private:
        static std::string _trim(char const *str);
        static bool _onlyHasDigits(std::string s);
        static bool _onlyHasHexDigits(std::string s);
        static bool _onlyHasBinaryDigits(std::string s);
        static bool _onlyHasOctalDigits(std::string s);

        //static const char* _movePastPrefixIfPresent(std::string in);
        static const std::string _movePastPrefixIfPresent(std::string in);

        static bool _hasPrefix(std::string prefix, std::string in);
        //static bool _hasPostfix(std::string prefix, std::string in);
        static bool _prefixedNumberOnlyHasDigits(std::string in);
        static bool _prefixedNumberOnlyHasHexDigits(std::string in);
        static bool _prefixedNumberOnlyHasBinaryDigits(std::string in);
        static bool _prefixedNumberOnlyHasOctalDigits(std::string in);

        static bool _isDecimalNumber(std::string s);
        static bool _isOctalNumber(std::string s);
        static bool _isHexNumber(std::string s);
        static bool _isBinaryNumber(std::string s);

};

#endif
