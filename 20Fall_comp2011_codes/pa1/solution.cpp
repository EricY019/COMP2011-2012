#include <iostream>

using namespace std;

// Task 1
int get_min_bits_length(int x)
{
	int i = 1;
	long long p = 2;

	while ( ! (-p <= x && x < p)) {
		++i;
		p = p * 2;
	}

	return i + 1;
}

// Task 2
int get_bit_positive(int x, int n)
{
	if (x < 0 || n < 0)
		return -1;

	if (n > get_min_bits_length(x) - 1)
		return 0;

	int i = 0;

	while (i++ < n)
		x = x / 2;

	return x % 2;
}

// Helper function
int flip(int bit)
{
	if (bit == 0)
		return 1;
	else
		return 0;
}

// Task 3
int get_bit_negative(int x, int n)
{
	if (x >= 0 || n < 0)
		return -1;

	int i = 0;
	int bit = 0;
	int carry = 0;

	while (i <= n) {
		if (i == 0)
			bit = flip(get_bit_positive(-x, i)) + 1;
		else
			bit = flip(get_bit_positive(-x, i)) + carry;

		carry = bit / 2;
		++i;
	}

	return bit % 2;
}

// Task 4
void print_2s_complement_representation(int x)
{
	for (int i = get_min_bits_length(x) - 1; i >= 0; --i) {
		if (x >= 0)
			cout << get_bit_positive(x, i);
		else
			cout << get_bit_negative(x, i);
	}
	cout << endl;
}

// Helper function
int get_carry_bit(int a, int b, int n)
{
	int i = 0;
	int carry = 0;

	while (i <= n) {
		int bit_a = (a >= 0) ? get_bit_positive(a, i) : get_bit_negative(a, i);
		int bit_b = (b >= 0) ? get_bit_positive(b, i) : get_bit_negative(b, i);

		int bit_c = bit_a + bit_b + carry;

		carry = bit_c / 2;
		++i;
	}

	return carry;
}

// Helper function
int my_max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

// Task 5
void print_addition_carry_out(int a, int b)
{
	for (int i = my_max(get_min_bits_length(a), get_min_bits_length(b)) - 1; i >= 0; --i)
		cout << get_carry_bit(a, b, i);

	cout << endl;
}

int main()
{
	while (true) {
		int option = 0;

		do {
			cout << "1. Task 1" << endl;
			cout << "2. Task 2" << endl;
			cout << "3. Task 3" << endl;
			cout << "4. Task 4" << endl;
			cout << "5. Task 5" << endl;
			cout << "0. Exit" << endl;
			cout << "Enter an option (0-5): ";
			cin >> option;
		} while (option < 0 || option > 5);
		
		if (option == 0)
			break;
		else if (option == 1) {
			int number;
			cout << "Enter a number: ";
			cin >> number;
			cout << number << " needs " << get_min_bits_length(number) << " bits." << endl;
		}
		else if (option == 2) {
			int number;
			int bit;

			cout << "Enter a number: ";
			cin >> number;

			cout << "Which bit? ";
			cin >> bit;
			
			cout << "The number " << bit << " bit of " << number << " is " << get_bit_positive(number, bit) << endl;
		}
		else if (option == 3) {
			int number;
			int bit;

			cout << "Enter a number: ";
			cin >> number;

			cout << "Which bit? ";
			cin >> bit;
			
			cout << "The number " << bit << " bit of " << number << " is " << get_bit_negative(number, bit) << endl;
		}
		else if (option == 4) {
			int number;
			cout << "Enter a number: ";
			cin >> number;
			cout << "The 2's complement representation of " << number << " is:" << endl;
			print_2s_complement_representation(number);
		}
		else if (option == 5) {
			int a, b;
			cout << "Enter number A: ";
			cin >> a;
			cout << "Enter number B: ";
			cin >> b;
			cout << "The sum of " << a << " and " << b << " is " << a + b << ". The carry bits are:" << endl;
			print_addition_carry_out(a, b);
		}

		cout << endl;
	}
	return 0;
}