#define CATCH_CONFIG_MAIN

#include "include/catch2/catch_amalgamated.hpp"

#include "../LAB5/src/classes/CRomanNumber.hpp"
#include "../LAB5/src/classes/CRomanNumberException.hpp"

#include "../LAB5/src/classes/CException.cpp"
#include "../LAB5/src/classes/CRomanNumber.cpp"
#include "../LAB5/src/classes/CRomanNumberException.cpp"

SCENARIO("Event handler firing for Roman numbers", "[RomanNumber]")
{
    GIVEN("Two Roman numbers")
    {
        WHEN("adding them")
        {
            CRomanNumber romanNumb_f(3988);
            CRomanNumber romanNumb_s(200);

            REQUIRE_THROWS(romanNumb_f + romanNumb_s);
        }

        WHEN("subtracting them")
        {
            CRomanNumber romanNumb_f;
            CRomanNumber romanNumb_s;

            REQUIRE_THROWS(romanNumb_f - romanNumb_s);
        }

        WHEN("multiplying them")
        {
            CRomanNumber romanNumb_f(3888);
            CRomanNumber romanNumb_s(5);

            REQUIRE_THROWS(romanNumb_f * romanNumb_s);
        }
    }
}

SCENARIO("Correct performance of Roman number operations", "[RomanNumber]")
{
    GIVEN("Two Roman numbers")
    {
        CRomanNumber romanNumb_f(10);
        CRomanNumber romanNumb_s(2);

        WHEN("adding them (+)")
        {
            CRomanNumber result = romanNumb_f + romanNumb_s;

            THEN("the result should be 12")
            {
                REQUIRE(result == 12);
            }
        }

        WHEN("subtracting them (-)")
        {
            CRomanNumber result = romanNumb_f - romanNumb_s;

            THEN("the result should be 8")
            {
                REQUIRE(result == 8);
            }
        }

        WHEN("multiplying them (*)")
        {
            CRomanNumber result = romanNumb_f * romanNumb_s;

            THEN("the result should be 20")
            {
                REQUIRE(result == 20);
            }
        }

        WHEN("dividing them (/)")
        {
            CRomanNumber result = romanNumb_f / romanNumb_s;

            THEN("the result should be 5")
            {
                REQUIRE(result == 5);
            }
        }
    }
}

SCENARIO("Correctly performing comparison operations with Roman number", "[RomanNumber]")
{
    GIVEN("Diffrent Roman numbers")
    {
        WHEN("checking equality (==)")
        {
            CRomanNumber romanNumb_f(99);
            CRomanNumber romanNumb_s(99);

            THEN("the two Roman numbers should be equal")
            {
                REQUIRE(romanNumb_f == romanNumb_s);
            }
        }

        WHEN("checking lack of equality !(==)")
        {
            CRomanNumber romanNumb_f(99);
            CRomanNumber romanNumb_s(9);

            THEN("the two Roman numbers should be equal")
            {
                REQUIRE_FALSE(romanNumb_f == romanNumb_s);
            }
        }

        WHEN("checking inequality (!=)")
        {
            CRomanNumber romanNumb_f(99);
            CRomanNumber romanNumb_s(9);

            THEN("the two Roman numbers should not be equal")
            {
                REQUIRE(romanNumb_f != romanNumb_s);
            }
        }

        WHEN("checking lack of inequality !(!=)")
        {
            CRomanNumber romanNumb_f(77);
            CRomanNumber romanNumb_s(77);

            THEN("the two Roman numbers should not be equal")
            {
                REQUIRE_FALSE(romanNumb_f != romanNumb_s);
            }
        }

        WHEN("comparing greater (>)")
        {
            CRomanNumber romanNumb_f(339);
            CRomanNumber romanNumb_s(1);

            THEN("the first Roman number should be greater than the second")
            {
                REQUIRE(romanNumb_f > romanNumb_s);
            }
        }

        WHEN("lack of comparing greater !(>)")
        {
            CRomanNumber romanNumb_f(1);
            CRomanNumber romanNumb_s(2);

            THEN("the first Roman number should be greater than the second")
            {
                REQUIRE_FALSE(romanNumb_f > romanNumb_s);
            }
        }

        WHEN("comparing less (<)")
        {
            CRomanNumber romanNumb_f(8);
            CRomanNumber romanNumb_s(3331);

            THEN("the first Roman number should be less than the second")
            {
                REQUIRE(romanNumb_f < romanNumb_s);
            }
        }

        WHEN("lack of comparing less !(<)")
        {
            CRomanNumber romanNumb_f(3332);
            CRomanNumber romanNumb_s(3331);

            THEN("the first Roman number should be less than the second")
            {
                REQUIRE_FALSE(romanNumb_f < romanNumb_s);
            }
        }

        WHEN("comparing greater or equal (>=)")
        {
            CRomanNumber romanNumb_f(77);
            CRomanNumber romanNumb_s(77);

            THEN("the first Roman number should be greater or equal to the second")
            {
                REQUIRE(romanNumb_f >= romanNumb_s);
            }
        }

        WHEN("comparing lack of greater or equal !(>=)")
        {
            CRomanNumber romanNumb_f(74);
            CRomanNumber romanNumb_s(77);

            THEN("the first Roman number should be greater or equal to the second")
            {
                REQUIRE_FALSE(romanNumb_f >= romanNumb_s);
            }
        }

        WHEN("comparing less or equal (<=)")
        {
            CRomanNumber romanNumb_f(666);
            CRomanNumber romanNumb_s(666);

            THEN("the first Roman number should be less or equal to the second")
            {
                REQUIRE(romanNumb_f <= romanNumb_s);
            }
        }

        WHEN("comparing lack of less or equal !(<=)")
        {
            CRomanNumber romanNumb_f(666);
            CRomanNumber romanNumb_s(420);

            THEN("the first Roman number should be less or equal to the second")
            {
                REQUIRE_FALSE(romanNumb_f <= romanNumb_s);
            }
        }
    }
}

SCENARIO("Roman number output", "[RomanNumber]")
{
    GIVEN("Roman numbers with different decimal values")
    {
        CRomanNumber romanNumb_1(1);
        CRomanNumber romanNumb_2(2);
        CRomanNumber romanNumb_4(4);
        CRomanNumber romanNumb_5(5);
        CRomanNumber romanNumb_56(56);
        CRomanNumber romanNumb_199(199);
        CRomanNumber romanNumb_447(447);
        CRomanNumber romanNumb_568(568);
        CRomanNumber romanNumb_934(934);
        CRomanNumber romanNumb_3810(3810);

        WHEN("getting Roman number representations")
        {
            THEN("the Roman number and decimal value should be correct for each case")
            {
                REQUIRE(romanNumb_1.getRomanNumber() == "I");
                REQUIRE(romanNumb_1.getDecimalNumber() == 1);

                REQUIRE(romanNumb_2.getRomanNumber() == "II");
                REQUIRE(romanNumb_2.getDecimalNumber() == 2);

                REQUIRE(romanNumb_4.getRomanNumber() == "IV");
                REQUIRE(romanNumb_4.getDecimalNumber() == 4);

                REQUIRE(romanNumb_5.getRomanNumber() == "V");
                REQUIRE(romanNumb_5.getDecimalNumber() == 5);

                REQUIRE(romanNumb_56.getRomanNumber() == "LVI");
                REQUIRE(romanNumb_56.getDecimalNumber() == 56);

                REQUIRE(romanNumb_199.getRomanNumber() == "CXCIX");
                REQUIRE(romanNumb_199.getDecimalNumber() == 199);

                REQUIRE(romanNumb_447.getRomanNumber() == "CDXLVII");
                REQUIRE(romanNumb_447.getDecimalNumber() == 447);

                REQUIRE(romanNumb_568.getRomanNumber() == "DLXVIII");
                REQUIRE(romanNumb_568.getDecimalNumber() == 568);

                REQUIRE(romanNumb_934.getRomanNumber() == "CMXXXIV");
                REQUIRE(romanNumb_934.getDecimalNumber() == 934);

                REQUIRE(romanNumb_3810.getRomanNumber() == "MMMDCCCX");
                REQUIRE(romanNumb_3810.getDecimalNumber() == 3810);
            }
        }
    }
}