#include "doctest.h"
#include "showbin.hpp"
#include <string>

int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

// 1. Get input, detecting base
//    - 0bXXXX : Binary
//    - 0xXXXX : Hex
//    - 0oXXXX : Octal
//    - XXXX   : decimal
//    - XXXXb  : binary
//    - XXXXx  : Hex
//    - XXXXo  : Octal
// 2. Convert to integer
// 3. Output to desired base, formatting it nicely.
//    - -b flag for binary output, etc

TEST_CASE("Input Detect Decimal") {
	NumberTypeParser p;
	std::string inputString = " 123";
	CHECK(NumberType::Decimal == p.detectBase(inputString));

	inputString = " 1234 ";
	CHECK(NumberType::Decimal == p.detectBase(inputString));

	inputString = " 123a4";
	CHECK(NumberType::Decimal != p.detectBase(inputString));

	inputString = "0x123";
	CHECK(NumberType::Decimal != p.detectBase(inputString));

	inputString = "0b101";
	CHECK(NumberType::Decimal != p.detectBase(inputString));

	inputString = "10o1";
	CHECK(NumberType::Decimal != p.detectBase(inputString));
}

TEST_CASE("Detect Hexidecimal") {
	NumberTypeParser p;
	std::string inputString = " 234";
	CHECK(NumberType::Hexidecimal != p.detectBase(inputString));

	inputString = "0x234";
	CHECK(NumberType::Hexidecimal == p.detectBase(inputString));

	inputString = "0x123a";
	CHECK(NumberType::Hexidecimal == p.detectBase(inputString));

	inputString = "0x12F3";
	CHECK(NumberType::Hexidecimal == p.detectBase(inputString));

	inputString = "0x12G3";
	CHECK(NumberType::Hexidecimal != p.detectBase(inputString));

	inputString = "0b101";
	CHECK(NumberType::Hexidecimal != p.detectBase(inputString));

	inputString = "10o1";
	CHECK(NumberType::Hexidecimal != p.detectBase(inputString));

}

TEST_CASE("Detect Binary") {
	NumberTypeParser p;
	std::string inputString = " 123";
	CHECK(NumberType::Binary != p.detectBase(inputString));

	inputString = "0x123";
	CHECK(NumberType::Binary != p.detectBase(inputString));

	inputString = "0b101";
	CHECK(NumberType::Binary == p.detectBase(inputString));

	inputString = "10o1";
	CHECK(NumberType::Binary != p.detectBase(inputString));

	inputString = "0b111";
	CHECK(NumberType::Binary == p.detectBase(inputString));
}

TEST_CASE("Detect Octal") {
	NumberTypeParser p;
	std::string inputString = " 678";
	CHECK(NumberType::Octal != p.detectBase(inputString));

	inputString = "0x678";
	CHECK(NumberType::Octal != p.detectBase(inputString));

	inputString = "0b101";
	CHECK(NumberType::Octal != p.detectBase(inputString));

	inputString = "10o1";
	CHECK(NumberType::Octal != p.detectBase(inputString));

	inputString = "0o678";
	CHECK(NumberType::Octal == p.detectBase(inputString));

	inputString = "0o679";
	CHECK(NumberType::Octal != p.detectBase(inputString));
}


TEST_CASE("Convert Decimal") {
	ShowBin b;
	std::string inputString = "1";
	CHECK(1 == b.convertToNumber(inputString));

	inputString = "10";
	CHECK(10 == b.convertToNumber(inputString));

	inputString = "11";
	CHECK(11 == b.convertToNumber(inputString));

	inputString = "112";
	CHECK(112 == b.convertToNumber(inputString));

	inputString = "927";
	CHECK(927 == b.convertToNumber(inputString));

}

TEST_CASE("Convert Hex") {
	ShowBin b;

	std::string inputString = "0x1";
	CHECK(1 == b.convertToNumber(inputString));

	inputString = "0xa";
	CHECK(10 == b.convertToNumber(inputString));

	inputString = "0xA";
	CHECK(10 == b.convertToNumber(inputString));

	inputString = "0xb";
	CHECK(11 == b.convertToNumber(inputString));

	inputString = "0x10";
	CHECK(16 == b.convertToNumber(inputString));

	inputString = "0xABCD";
	CHECK(0xABCD == b.convertToNumber(inputString));
}

TEST_CASE("Convert Octal") {
	ShowBin b;

	std::string inputString = "0o1";
	CHECK(1 == b.convertToNumber(inputString));

	inputString = "0o2";
	CHECK(2 == b.convertToNumber(inputString));

	inputString = "0o10";
	CHECK(8 == b.convertToNumber(inputString));

	inputString = "0o11";
	CHECK(9 == b.convertToNumber(inputString));
}

