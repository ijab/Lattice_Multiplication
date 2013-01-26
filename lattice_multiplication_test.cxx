/**
 * Lattice Multiplication Unit Test
 * All the test cases would be run in this Unit Test file
 *
 * File: lattice_multiplication_test.cxx
 * Author: iJab(Zhan Caibao) zhancaibaoATgmail.com
 * Date: 2013/01/25
 *
 */

#include <UnitTest++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <limits>

#include "lattice_multiplication.hxx"

using namespace std;

// Test Case 1: one digit times one digit
// 7 * 8
TEST(OneDigitTimesOneDigit)
{
	LatticeMultiplication<int, int> _aTest(7, 8);
	CHECK_EQUAL("56", _aTest.run());
}

// Test Case 2: one digit(lef is negative) times one digit
// -7 * 8
TEST(OneDigitNegativeTimesOneDigit)
{
	LatticeMultiplication<int, int> _aTest(-7, 8);
	CHECK_EQUAL("-56", _aTest.run());
}

// Test Case 3: one digit times one digit(right is negative)
// 7 * -8
TEST(OneDigitTimesOneDigitNegative)
{
	LatticeMultiplication<int, int> _aTest(7, -8);
	CHECK_EQUAL("-56", _aTest.run());
}

// Test Case 4: one digit times one digit and both are negative
// -7 * -8
TEST(OneDigitNegativeTimesOneDigitNegative)
{
	LatticeMultiplication<int, int> _aTest(-7, -8);
	CHECK_EQUAL("56", _aTest.run());
}

// Test Case 6: two digits times two digits
// 17 * 28
TEST(TwoDigitsTimesTwoDigits)
{
	ostringstream ss;
	ss << 17*28;
	LatticeMultiplication<int, int> _aTest(17, 28);
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 7: two digits times one digit
// 17 * 8
TEST(TwoDigitsTimesOneDigit)
{
	ostringstream ss;
	ss << 17*8;

	LatticeMultiplication<int, int> _aTest(17, 8);
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 8: one digit times two digits
// 8 * 17
TEST(OneDigitTimesTwoDigits)
{
	ostringstream ss;
	ss << 8*17;

	LatticeMultiplication<int, int> _aTest(8, 17);
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 9: one negative two digits times two digits
// -17 * 28
TEST(TwoDigitsNegativeTimesTwoDigits)
{
	ostringstream ss;
	ss << -17*28;
	LatticeMultiplication<int, int> _aTest(-17, 28);
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 10: negative two digits times negative two digits
// -17 * -28
TEST(TwoDigitsNegativeTimesTwoDigitsNegative)
{
	ostringstream ss;
	ss << -17*-28;
	LatticeMultiplication<int, int> _aTest(-17, -28);
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 11: 4 digits times 2 digits
// 1716 * 28
TEST(FourDigitsTimesTwoDigits)
{
	ostringstream ss;
	ss << 1716*28;
	LatticeMultiplication<int, int> _aTest(1716, 28);
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 11-1: 2 digits times 4 digits
// 28 * 1716
TEST(TwoDigitsTimesFourDigits)
{
	ostringstream ss;
	ss << 1716*28;
	LatticeMultiplication<int, int> _aTest(28, 1716);
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 12: 4 digits times 1 digits
// 1716 * 8
TEST(FourDigitsTimesOneDigits)
{
	ostringstream ss;
	ss << 1716*8;
	LatticeMultiplication<string, string> _aTest("1716", "8");
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 12-1: 1 digits times 4 digits
// 8 * 1716
TEST(OneDigitTimesFourDigits)
{
	ostringstream ss;
	ss << 1716*8;
	LatticeMultiplication<string, string> _aTest("8", "1716");
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 12-3: 4 digits times 4 digits
// 2876 * 1716
TEST(FourDigitsTimesFourDigits)
{
	ostringstream ss;
	ss << 1716*2876;
	LatticeMultiplication<int, string> _aTest(2876, "1716");
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 13: float times float
// 0.3 * 0.4
TEST(FloatTimesFloat)
{
	ostringstream ss;
	ss << 0.3*0.4;
	LatticeMultiplication<string, string> _aTest("0.3", "0.4");
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 14: float times float
// 12.034 * 2.42
TEST(LongFloatTimesFloat)
{
	ostringstream ss;
	ss.precision(numeric_limits<double>::digits10);
	ss << (double)12.034 * 2.42;
	LatticeMultiplication<double, string> _aTest(12.034, "2.42");
	CHECK_EQUAL(ss.str(), _aTest.run());
}

// Test Case 15: very large interger times large interger
// 1234567890123 * 13
TEST(VeryLargeNumberTimesInterger)
{
	LatticeMultiplication<string, int> _aTest("1234567890123", 13);
	CHECK_EQUAL("16049382571599", _aTest.run());
}

// Test Case 16: large inter times very large interger
// 13 * 1234567890123
TEST(IntergerTimesVeryLargeNumber)
{
	LatticeMultiplication<int, string> _aTest(13, "1234567890123");
	CHECK_EQUAL("16049382571599", _aTest.run());
}

// Test Case 17: very large interger times float
// 1234567890123 * 13.23
TEST(VeryLargeNumberTimesFloat)
{
	LatticeMultiplication<string, double> _aTest("1234567890123", 13.23);
	CHECK_EQUAL("16333333186327.29", _aTest.run());
}

// Test Case 18: very large double times inter
// 1234567890123.23 * 13
TEST(VeryLargeDoubleTimesInterger)
{
	LatticeMultiplication<string, int> _aTest("1234567890123.23", 13);
	CHECK_EQUAL("16049382571601.99", _aTest.run());
}

int main(int argc, char* argv[])
{
	int rv = 0;
	rv = UnitTest::RunAllTests();

	getchar();

	return rv;
}