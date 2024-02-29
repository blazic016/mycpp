#ifndef _MY_BIG_INT_
#define _MY_BIG_INT_

#include <cstdint>
#include <array>
#include <ostream>
#include <iostream>
#include <algorithm>

#define MAX_DIGITS 70
// #define DEBUG

using namespace std;

struct MyBigInt
{
private:
	// std::array<int, size> digits = {0};
	int_least8_t* digits = nullptr;
public:
	int num_of_digits = 0;
	
	MyBigInt(const MyBigInt& num){ // copy ctor
		num_of_digits = num.num_of_digits;
		digits = new int_least8_t[MAX_DIGITS];
	
		for(int i=0; i<MAX_DIGITS; i++){
			digits[i] = num.digits[i];
		}
	}

	MyBigInt(MyBigInt&& num){
		num_of_digits = num.num_of_digits;
		digits = num.getDigits();

		num.num_of_digits = 0;
		num.digits = nullptr;
	}

	explicit MyBigInt(int num)
	{
		digits = new int_least8_t[MAX_DIGITS];

		for(int i=0; i<MAX_DIGITS; i++){
			digits[i] = 0;
		}

		int cnt = 0;
		while (num > 0)
		{
			digits[cnt] = num % 10;
			num = num / 10;
			cnt++;
		}
		
		num_of_digits = cnt;
#ifdef DEBUG
		if (num_of_digits) {
			for (int j = 0; j < num_of_digits; ++j){
				cout << "digits=" << digits[j] << " ";
			}
		} else {
			cout << "digits[0]=" << digits[0];
		}
			cout << endl;
#endif
	}

	explicit MyBigInt(const char *str)
	{
		digits = new int_least8_t[MAX_DIGITS];
		
		for(int i=0; i<MAX_DIGITS; i++){
			digits[i] = 0;
		}
		int cnt = 0;
		const char *tmp = str;
		while (*str++)
		{
			cnt++;
		}
		num_of_digits = cnt;
		while (cnt)
		{
			digits[cnt - 1] = *tmp++ - '0';
			cnt--;
		}
	}

	~MyBigInt(){
		delete digits;
	}

	MyBigInt operator+(MyBigInt other) const
	{

		MyBigInt ret{0};
		int n_max = max(num_of_digits, other.getNumOfDigits());
		int carry = 0;

		for (uint8_t i = 0; i < n_max; i++)
		{
			int n1 = digits[i];
			int n2 = other.getDigits()[i];
			int sum = (n1 + n2 + carry) % 10; 	// 8+2+1=11 % 10 = 1; 0+9+1=10 % 10 = 0
			carry = (n1 + n2 + carry) / 10;		// 8+2+1=11 / 10 = 1; 0+9+1=10 / 10 = 1
			ret.getDigits()[i] = sum;
		}
		if (carry == 1)
		{
			ret.getDigits()[n_max] = 1;
			ret.num_of_digits = n_max + 1;
		}
		else
		{
			ret.num_of_digits = n_max;
		}
		return ret;
	}

	MyBigInt operator+(int integer) const
	{
		std::vector<int> int_digits;
		while (integer > 0)
		{
			int_digits.insert(int_digits.begin(), integer % 10);
			integer /= 10;
		}
		std::reverse(int_digits.begin(), int_digits.end());
		int size_integer = static_cast<int>(int_digits.size());

		MyBigInt ret{0};

		int n_max = max(num_of_digits, size_integer);
		// cout << "max=" << n_max << endl;
		int carry = 0;

		for (uint8_t i = 0; i < n_max; i++)
		{
			int n1 = digits[i];
			int n2 = int_digits[i];
			int sum = (n1 + n2 + carry) % 10; 	// 8+2+1=11 % 10 = 1; 0+9+1=10 % 10 = 0
			carry = (n1 + n2 + carry) / 10;		// 8+2+1=11 / 10 = 1; 0+9+1=10 / 10 = 1
			ret.getDigits()[i] = sum;
		}
		
		if (carry == 1)
		{
			ret.getDigits()[n_max] = 1;
			ret.num_of_digits = n_max + 1;
		}
		else
		{
			ret.num_of_digits = n_max;
		}
		return ret;
	}

	bool operator!=(MyBigInt other) const
	{
		if (num_of_digits != other.num_of_digits)
			return true;
		for (int i = 0; i < num_of_digits; i++)
		{
			if (digits[i] != other.getDigits()[i])
				return true;
		}
		return false;
	}

    MyBigInt& operator=(MyBigInt& other) {
        
        if (this != &other) { 
            num_of_digits = other.num_of_digits;
	
			for(int i=0; i<MAX_DIGITS; i++){
				digits[i] = other.digits[i];
			}
		}

        return *this;
    }

    MyBigInt& operator=(MyBigInt&& other) {
        
        if (this != &other) { 
            num_of_digits = other.num_of_digits;
			digits = other.getDigits();

			other.num_of_digits = 0;
			other.digits = nullptr;
		}

        return *this;
    }

	int getNumOfDigits() const { return num_of_digits; }
	// std::array<int, MAX_DIGITS> &getDigits() { return digits; }
	int_least8_t* getDigits() { return digits; }

};

MyBigInt operator+(int number, const MyBigInt &bigint)
{
	return bigint + number;
}

ostream &operator<<(ostream &os, MyBigInt num)
{
	// std::array<int, MAX_DIGITS> &d = num.getDigits();
	int_least8_t* d = num.getDigits();
	for (int i = num.num_of_digits - 1; i >= 0; i--)
	{
		os << (int)d[i];
	}
	return os;
}

MyBigInt operator""_mbi(const char *str)
{
	return MyBigInt(str);
}

#endif