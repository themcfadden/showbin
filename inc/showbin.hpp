#ifndef __INC_H__
#define __INC_H__

#include <string>


#define DEBUG_PRINT(msg) cout << __FILE__ << ":" <<__LINE__ << ": " << (msg) << std::endl;
//#define DEBUG_PRINT(msg) ((void) (msg))

enum class NumberType {Unknown, Binary, Octal, Decimal, Hexidecimal};

class NumberTypeParser
{
    public:
        NumberTypeParser() {}
        static enum NumberType getNumberType(std::string in);
        static int parseToInt(std::string in);
        static int parseHexToInt(std::string in);

    private:
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

class ShowBin {
    public:
        ShowBin() {};
        enum NumberType detectBase(std::string inputNUmber);
        int convertToNumber(std::string in);

    private:
        bool _checkForPrefix(std::string prefix, std::string in);
        bool _checkForShortPrefix(std::string prefix, std::string in);
        bool _checkForPostfix(std::string postfix, std::string in);
        std::string _trim(char const *str);
};

#endif
