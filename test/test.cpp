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

TEST_CASE("Input") {
	ShowBin b;
	SUBCASE("Detect Decimal") {
		std::string inputString = " 123";
		CHECK(NumberType::Decimal == b.detectBase(inputString));

		inputString = " 1234 ";
		CHECK(NumberType::Decimal == b.detectBase(inputString));

		inputString = " 123a4";
		CHECK(NumberType::Decimal != b.detectBase(inputString));

		inputString = "0x123";
		CHECK(NumberType::Decimal != b.detectBase(inputString));

		inputString = "0b101";
		CHECK(NumberType::Decimal != b.detectBase(inputString));

		inputString = "10o1";
		CHECK(NumberType::Decimal != b.detectBase(inputString));
	}

	SUBCASE("Detect Hexidecimal") {
		std::string inputString = " 234";
		CHECK(NumberType::Hexidecimal != b.detectBase(inputString));

		inputString = "0x234";
		CHECK(NumberType::Hexidecimal == b.detectBase(inputString));

		inputString = "0x123a";
		CHECK(NumberType::Hexidecimal == b.detectBase(inputString));

		inputString = "0x12F3";
		CHECK(NumberType::Hexidecimal == b.detectBase(inputString));

		inputString = "0x12G3";
		CHECK(NumberType::Hexidecimal != b.detectBase(inputString));

		inputString = "0b101";
		CHECK(NumberType::Hexidecimal != b.detectBase(inputString));

		inputString = "10o1";
		CHECK(NumberType::Hexidecimal != b.detectBase(inputString));

	}

	SUBCASE("Detect Binary") {
		std::string inputString = " 123";
		CHECK(NumberType::Binary != b.detectBase(inputString));

		inputString = "0x123";
		CHECK(NumberType::Binary != b.detectBase(inputString));

		inputString = "0b101";
		CHECK(NumberType::Binary == b.detectBase(inputString));

		inputString = "10o1";
		CHECK(NumberType::Binary != b.detectBase(inputString));

		inputString = "0b111";
		CHECK(NumberType::Binary == b.detectBase(inputString));
	}

	SUBCASE("Detect Octal") {
		std::string inputString = " 678";
		CHECK(NumberType::Octal != b.detectBase(inputString));

		inputString = "0x678";
		CHECK(NumberType::Octal != b.detectBase(inputString));

		inputString = "0b101";
		CHECK(NumberType::Octal != b.detectBase(inputString));

		inputString = "10o1";
		CHECK(NumberType::Octal != b.detectBase(inputString));

		inputString = "0o678";
		CHECK(NumberType::Octal == b.detectBase(inputString));

		inputString = "0o679";
		CHECK(NumberType::Octal != b.detectBase(inputString));
	}
}

TEST_CASE("Convert") {

}
