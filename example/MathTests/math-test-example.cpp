import std;
import test;

int factorial(int number)
{
    if (number <= 1)
        return 1;

    return number * factorial(number - 1);
}

bool isPrime(int number)
{
    if (number <= 1)
        return false;

    for (int i = 2; i < number; i++)
        if (number % i == 0)
            return false;

    return true;
}

int countPrimes(int end)
{
    int count = 0;

    for (int i = 1; i < end; i++)
        if (isPrime(i))
            count++;

    return count;
}

int main()
{
    test::suite(
        "Factorial",
        []() -> test::result
        {
            return assert::greaterThan(
                factorial(0), 0,
                "0! > 0"
            );
        },
        []() -> test::result
        {
            return assert::equals(
                factorial(1), 1,
                "1! = 1"
            );
        },
        []() -> test::result
        {
            return assert::equals(
                factorial(5), 120,
                "5! = 120"
            );
        }
    );

    test::suite(
        "Prime Counting",
        "Counting how many prime numbers are in ranges≤.",
        []() -> test::result
        {
            return assert::lessThan_equals(
                countPrimes(10000),  1229
            );
        }
    );
}
