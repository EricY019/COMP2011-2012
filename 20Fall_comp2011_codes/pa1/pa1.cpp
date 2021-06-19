/*
 * COMP2011 (Fall 2020) Assignment 1: Binary Numbers
 *
 * Student name: YANG Jingwen
 * Student ID: 20677029
 * Student email: jyangbv@connect.ust.hk
 *
 * Note:
 * 1. You CANNOT define and use any arrays.
 * 2. You CANNOT define and use any global variables.
 * 3. You CANNOT use the static keyword.
 * 4. You CANNOT include any extra libraries other than iostream.
 * 5. You CANNOT use any bitwise operators: ~, ^, |, & (since they are not taught in this course).
 * 6. You CANNOT change the function headers of the functions given in the tasks.
 * 7. You CANNOT use any string operations.
 * 8. You can add helper functions.
 */

#include <iostream>

using namespace std;

// Power calculation
int power_helper(int base, int power)
{
	int i = 0; long long number = 1;
	for (; i < power; ++i)
	{
		number *= base;
	}
	return number;
}

// Task 1
int get_min_bits_length(int x)
{
	int bit = 1;
	if (x >= 0)
	{
		while (true)
		{
			if (power_helper(2, bit) > x) return (bit + 1);
			bit++;
		}
	}
	else
	{
		while (true)
		{
			if (power_helper(2, bit) >= -x) return (bit + 1);
			bit++;
		}
	}
	return -1;
}

// Task 2
int get_bit_positive(int x, int n)
{
	if (x < 0 || n < 0) return -1;

	int bits_length = get_min_bits_length(x);
	if (n >= bits_length) return 0;

	for (int bit = bits_length - 1; bit >= n; bit--)
	{
		if (bit == n && x >= power_helper(2, bit)) return 1;
		else if (bit == n && x < power_helper(2, bit)) return 0;
		else if (x >= power_helper(2, bit)) x -= power_helper(2, bit);
		else continue;
	}
	return -1;
}

// Task 3
int get_bit_negative(int x, int n)
{
	if (x >= 0 || n < 0) return -1;

	int complement_x = power_helper(2, get_min_bits_length(-x)) + x;
	if (n >= get_min_bits_length(complement_x) - 1) return 1;
	else return get_bit_positive(complement_x, n);
}

// Task 4
void print_2s_complement_representation(int x)
{	
	if (x >= 0)
	{
		for (int total_bits = get_min_bits_length(x) - 1; total_bits >= 0; total_bits--)
		{
		cout << get_bit_positive(x, total_bits);
		}
	}
	else
	{
		for (int total_bits = get_min_bits_length(x) - 1; total_bits >= 0; total_bits--)
		{
			cout << get_bit_negative(x, total_bits);
		}
	}
	cout << endl;
}

// Task 5
void print_addition_carry_out(int a, int b)
{
	int a_length = get_min_bits_length(a), b_length = get_min_bits_length(b);
	int index = ((a_length > b_length) ? a_length : b_length) - 1;
	
	if (a < 0) a = power_helper(2, index + 1) + a;
	if (b < 0) b = power_helper(2, index + 1) + b;

	int abs_sum = a + b, carry_out_bit, abs_sum_bit, a_bit, b_bit, sumab_bit;
	
	if (get_bit_positive(abs_sum, index + 1) == 0) cout << 0;
	else cout << 1;

	for (; index > 0; index--)
	{

		abs_sum_bit = get_bit_positive(abs_sum, index);
		a_bit = get_bit_positive(a, index);
		b_bit = get_bit_positive(b, index);

		if (a_bit == 0 && b_bit == 0) sumab_bit = 0;
		else if ((a_bit == 1 && b_bit == 0) || (a_bit == 0 && b_bit == 1)) sumab_bit = 1;
		else sumab_bit = 0;

		if (abs_sum_bit == 0 && sumab_bit == 0) carry_out_bit = 0;
		else if ((abs_sum_bit == 1 && sumab_bit == 0) || (abs_sum_bit == 0 && sumab_bit == 1)) carry_out_bit = 1;
		else carry_out_bit = 0;
		
		cout << carry_out_bit;
	}
	cout << endl;
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

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