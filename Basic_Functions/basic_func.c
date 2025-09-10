/*
Assigned by:
Name: Brian Sch
*/

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// 1D Array Utilities
#define SIZE_1D 10

// 2D Array Sort Check Functions
#define ROWS 5
#define COLS 4


void NextDate();
void IS_Prime();
void crt_array();
void even_odd_arr();



// Basic Functions

// 1
/*
Multiplication Function Summary:
-------------------------------
This function multiplies two integers using repeated addition. It adds the larger number to itself as many times as the value of the smaller number.
This approach mimics the behavior of the '*' operator, but is less efficient and only works for non-negative integers.

Time Complexity:
----------------
Let n = min(base, mult)
The function performs n additions, so the time complexity is:
O(n)
In contrast, the '*' operator is O(1) (constant time), as it is implemented in hardware.
*/
int multiplication(int base, int mult) // Function definition
{
	int result = 0; // Initial definition for the variable so it can be used without affecting the equation
	int i;
	if (base > mult) // Check which number is larger to know in which order it is more efficient to perform the addition
	{
		for (i = 0; i < mult; i++) // Set conditions
			result += base; // Adds the number to itself according to the number of times we multiply the first number
		return result;
	}
	else if (base <= mult)
	{
		for (i = 0; i < base; i++)
			result += mult;
		return result;
	}
}

// Function to get user input, call multiplication, and print result
void multiplication_menu()
{
	int base, mult, result;
	printf("Enter base: ");
	scanf("%d", &base);
	printf("Enter multiplier: ");
	scanf("%d", &mult);
	result = multiplication(base, mult);
	printf("Result: %d\n", result);
}

// 2
/*
Prime Function Summary:
-----------------------
This function prints all prime numbers in a given range [start, end].
For each number in the range, it checks if the number is prime by testing divisibility from 2 up to the square root of the number.
If no divisors are found (other than 1 and itself), the number is printed as a prime.

Time Complexity:
----------------
Let n = end - start + 1 (the number of numbers checked)
Let m = end (the largest number checked)
For each number, divisibility is checked up to sqrt(count), so the worst-case time complexity is:
O(n * sqrt(m))
*/
void Prime(int start, int end) // Function definition
{
	int count = start;
	for (; count <= end; count++) // Loop to advance from the first number to the desired range
	{
		int divider, prime = 1;
		int c = sqrt(count);
		for (divider = 2; divider <= c; divider++) // Loop to divide from 2 up to the square root of the number
		{
			if (count % divider == 0) // Check remainder to see if the number is divisible
			{
				prime = 0;
				break; // Exit the loop if a divisor is found
			}
		}
		if (prime && count > 1) // If no divisors were found, print the number (and skip 1)
		{
			printf("%d, ", count);
		}
	}
}

void prime_menu()
{
	int start, end;
	printf("Enter the start of the range: ");
	scanf("%d", &start);
	printf("Enter the end of the range: ");
	scanf("%d", &end);
	printf("Prime numbers between %d and %d are:\n", start, end);
	Prime(start, end);
	printf("\n");
}

// 3
/*
Reverse Function Summary:
------------------------
This function returns the reverse of a given integer.
It extracts each digit and builds a new number in reverse order.

Time Complexity:
----------------
O(log n), where n is the value of the input number (number of digits).
*/
int Reverse(int num) // Function definition
{
	int R, sum = 0;
	for (; num > 0; num /= 10) // Loop that separates the digits
	{
		R = num % 10; // Extract the units digit from the current number
		sum = sum * 10 + R; // Advance the reversed number and add the extracted digit
	}
	return sum;
}

void reverse_menu()
{
	int num, reversed;
	printf("Enter a number to reverse: ");
	scanf("%d", &num);
	if (num < 0) {
		printf("Negative numbers are not supported.\n");
	} else {
		reversed = Reverse(num);
		printf("Reversed number: %d\n", reversed);
	}
}



// 4 (Iterative)
/*
Fibonacci (Iterative) Function Summary:
--------------------------------------
This function returns the nth Fibonacci number using an iterative approach (loop).
It starts from the first two Fibonacci numbers and builds up to the desired position by summing the previous two numbers.

Time Complexity:
----------------
O(n), where n is the position in the Fibonacci sequence.
Each Fibonacci number is calculated only once in a loop.
*/
int fibonacci(int num) // Function definition
{
	int a = 0, b = 1, i, next = 0;
	if (num == 1) // Can't work with the first numbers in the sequence, so define and return the known answer
	{
		return 0;
	}
	else if (num == 2)
	{
		return 1;
	}
	else if (num >= 3) // Can work from the third number in the sequence
	{
		for (i = 3; i <= num; i++) // Loop to advance to the desired position in the sequence
		{
			next = a + b; // The next number depends on the previous two numbers, so we advance in the sequence
			a = b; // Move the last two numbers forward to calculate the next number
			b = next;
		}
		return next; // Return the number at the desired position
	}
}

// 4 (Recursive)
/*
Fibonacci (Recursive) Function Summary:
--------------------------------------
This function returns the nth Fibonacci number using a simple recursive approach.
It calls itself for the two previous positions until it reaches the base cases (1 or 2).

Time Complexity:
----------------
O(2^n), where n is the position in the Fibonacci sequence.
This approach recalculates the same values many times and is much less efficient than the iterative version.
*/
int fibonacci_recursive(int num)
{
	if (num == 1)
		return 0;
	else if (num == 2)
		return 1;
	else
		return fibonacci_recursive(num - 1) + fibonacci_recursive(num - 2);
}

void fibonacci_menu()
{
	int num, result;
	clock_t start, end;
	double cpu_time_used;
	printf("Enter the position in the Fibonacci sequence: ");
	scanf("%d", &num);
	if (num <= 0) {
		printf("Position must be a positive integer.\n");
	} else {
		// Iterative timing
		start = clock();
		result = fibonacci(num);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("Fibonacci number at position %d (iterative): %d\n", num, result);
		printf("Time taken (iterative): %f seconds\n", cpu_time_used);

		// Recursive timing
		start = clock();
		result = fibonacci_recursive(num);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("Fibonacci number at position %d (recursive): %d\n", num, result);
		printf("Time taken (recursive): %f seconds\n", cpu_time_used);
	}
}

// 5
/*
ArmstrongMenu Function Summary:
------------------------------
This function provides a menu for checking Armstrong (narcissistic) numbers.

What is an Armstrong number?
---------------------------
An Armstrong number (also called a narcissistic number) is a number that is equal to the sum of its own digits each raised to the power of the number of digits.
For 3-digit numbers, this means: num = x^3 + y^3 + z^3, where x, y, z are the digits of num.
Example: 153 is an Armstrong number because 1^3 + 5^3 + 3^3 = 153.

Function Modes:
---------------
Mode 1: Checks if a single input number is an Armstrong number and prints true or false.
Mode 2: Takes a range and prints all Armstrong numbers in that range.
Uses the Check() function as a helper to determine if a number is an Armstrong number.

Time Complexity:
----------------
Mode 1: O(1) (single check)
Mode 2: O(n), where n is the size of the range (each number is checked once).
*/
int Check(int num) // Function definition
{
	int units, tens, hundreds, c; // Variable definitions
	units = num % 10; // Separate the units digit from the number
	c = num / 10; // Remove the units digit to focus on the tens
	tens = c % 10; // Separate the tens digit from the number
	c = num / 100; // Remove the tens so only the hundreds remain
	hundreds = c; // No further action needed
	if (pow(units, 3) + pow(tens, 3) + pow(hundreds, 3) == num) // Condition for the property we're looking for, after separating all digits and using the pow function to raise them to the third power
	{
		return num; // If the number satisfies the property, return the number
	}
	else
	{
		return 0; // If the number does not satisfy the property, return 0
	}
}

void ArmstrongMenu() {
	int mode;
	printf("Choose mode:\n1 - Check a single number\n2 - Check a range of numbers\nEnter your choice: ");
	scanf("%d", &mode);
	if (mode == 1) {
		int num;
		printf("Enter a number to check if it is an Armstrong number: ");
		scanf("%d", &num);
		if (Check(num)) {
			printf("true\n");
		} else {
			printf("false\n");
		}
	} else if (mode == 2) {
		int start, end;
		printf("Enter the start of the range: ");
		scanf("%d", &start);
		printf("Enter the end of the range: ");
		scanf("%d", &end);
		printf("Armstrong numbers in the range %d to %d:\n", start, end);
		for (int num = start; num <= end; num++) {
			if (Check(num)) {
				printf("%d ", num);
			}
		}
		printf("\n");
	} else {
		printf("Invalid mode selected.\n");
	}
}



// Advanced Functions

// 6
/*
NextDate Function Summary:
-------------------------
This function calculates and prints the next calendar date given a day, month, and year as input.
It handles leap years and validates the input date.

Time Complexity:
----------------
O(1) — All operations are performed in constant time.
*/
void NextDate()
{

	int day, month, year, flag = 1;
	
	printf("Enter a date\n");
	printf("Enter a day: ");
	scanf("%d", &day);
	printf("Enter a month: ");
	scanf("%d", &month);
	printf("Enter a year: ");
	scanf("%d", &year);


	switch (month)
	{
	case 01:
		if (day >= 31)
		{
			day = 1;
			month += 1;
		}
		
		else if(day > 31)
		{
			flag = 0;
		}

		else
		{
			day += 1;
		}
		break;
	case 02:
		if (day == 28)
		{
			if (year % 4 == 0)
			{
				if (year % 100 == 0)
				{
					if (year % 400 == 0)
					{
						day = 29;
					}
					else
					{
						day = 1;
						month += 1;
					}
				}
				day = 29;
			}
			else
			{
				day = 1;
				month += 1;
			}
		}
		else if (day > 29)
		{
			flag = 0;
		}
		else if (day == 29)
		{
			day = 1;
			month += 1;
		}
		else
		{
			day += 1;
		}
		break;
	case 03:
		if (day == 31)
		{
			day = 1;
			month += 1;
		}
		else if (day > 31)
		{
			flag = 0;
		}
		else
		{
			day += 1;
		}
		break;
	case 04:
		if (day == 30)
		{
			day = 1;
			month += 1;
		}
		else if (day > 30)
		{
			flag = 0;
		}
		else
		{
			day = +1;
		}
		break;
	case 05:
		if (day == 31)
		{
			day = 1;
			month += 1;
		}
		else if (day > 31)
		{
			flag = 0;
		}
		else
		{
			day += 1;
		}
		break;
	case 06:
		if (day == 30)
		{
			day = 1;
			month += 1;
		}
		else if (day > 30)
		{
			flag = 0;
		}
		else
		{
			day += 1;
		}
		break;
	case 07:
		if (day == 31)
		{
			day = 1;
			month += 1;
		}
		else if (day > 31)
		{
			flag = 0;
		}
		else
		{
			day += 1;
		}
		break;
	case 8:
		if (day == 31)
		{
			day = 1;
			month += 1;
		}
		else if (day > 31)
		{
			flag = 0;
		}
		else
		{
			day += 1;
		}
	case 9:
		if (day == 30)
		{
			day = 1;
			month += 1;
		}
		else if (day > 30)
		{
			flag = 0;
		}
		else
		{
			day += 1;
		}
	case 10:
		if (day == 31)
		{
			day = 1;
			month += 1;
		}
		else if (day > 31)
		{
			flag = 0;
		}
		else
		{
			day += 1;
		}
		break;
	case 11:
		if (day == 30)
		{
			day = 1;
			month += 1;
		}
		else if (day > 30)
		{
			flag = 0;
		}
		else
		{
			day += 1;
		}
		break;
	case 12:
		if (day == 31)
		{
			day = 1;
			month = 1;
			year += 1;
		}
		else if (day > 31)
		{
			flag = 0;
		}
		else
		{
			day = +1;
		}
		break;

	default:
		break;
	}
	if (flag == 0)
	{
		printf("Error: no such day in a month\n");
	}
	else
	{
		printf("\nNext day is: ");
		printf("%d / %d / %d\n", day, month, year);

	}
}

// 7
/*
IS_Prime Function Summary:
-------------------------
This function checks if a user-input number is prime and prints the result.
It also prints all prime numbers between 1 and 1000 using the Sieve of Eratosthenes.

Time Complexity:
----------------
Prime check: O(sqrt(n)), where n is the input number.
Sieve: O(n log log n), where n = 1000.
*/
void IS_Prime()
{
	
	int field[1001], num, flag = 0;
	int i, j, k = sqrt(1001);

	printf("Choose a number:\n");
	scanf("%d", &num);

	for (i = 2; i <= num / 2; ++i)
	{
		if (num % i == 0)
		{
			flag = 1;
			break;
		}
	}

	if (flag == 0)
		printf("%d is a prime number.\n\n", num);
	else
		printf("%d is not a prime number.\n\n", num);

	for (i = 2; i < 1001; i++)
		field[i] = 1;

	for (i = 2; i < k; i++)
		if (field[i])
			for (j = i; j * i < 1001; j++)
				field[j * i] = 0;

	printf("The Prime numbers between 1 and 100 are:\n");

	for (i = 1; i < 100; i++) {
		if (field[i] == 1)
			printf("%d\n", i);
	}
}

// 8
/*
crt_array, Remove_Dup, and Sort Function Summary:
------------------------------------------------
These functions work together to:
	- Read an array from user input
	- Sort the array in ascending order
	- Remove duplicate elements
	- Print the original and deduplicated arrays

Time Complexity:
----------------
Sort: O(n^2) (Bubble sort)
Remove_Dup: O(n)
Overall: O(n^2), where n is the array size.
*/
int Remove_Dup(int arry1[], int arry2[], int size)
{

	int i, j;
	arry2[0] = arry1[0];
	for (i = 0, j = 0; i <= size; i++) {
		if (arry2[j] != arry1[i + 1]) {
			arry2[j + 1] = arry1[i + 1];
			j++;
		}
	}
	return j;
}

void Sort(int sort[], int size)
{
	int i, j, temp;

	for (i = 0; i < (size - 1); i++) {
		for (j = 0; j < size - i - 1; j++) {
			if (sort[j] > sort[j + 1]) {
				temp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = temp;
			}
		}
	}
}

void crt_array()
{
	int arry1[50], *arry2;
	int size;
	int i, j;

	printf("Enter size of the array: ");

	scanf("%d", &size);

	printf("Enter elements in array:\n");

	for (i = 0; i < size; i++) {
		printf("Element[%d]:", i);
		scanf("%d", &arry1[i]);
	}

	Sort(arry1, size);

	printf("\nThe original array is: ");

	for (i = 0; i < size; i++)
		printf(" %d", arry1[i]);

	arry2 = (int*)malloc(sizeof(int) * size);

	j = Remove_Dup(arry1, arry2, size);

	printf("\nArray elements after removing duplicates: ");
	for (i = 0; i < j; i++)
		printf("%d ", arry2[i]);

	free (arry2);
}

// 9
/*
even_odd_arr Function Summary:
-----------------------------
This function separates a fixed array of integers into even and odd arrays, then prints all three arrays (original, even, odd).

Time Complexity:
----------------
O(n), where n is the size of the array.
*/
void even_odd_arr()
{

	int i = 0, j=0, k=0 , *arr1, *arr2, arr[] =  {6, 57, 14, 21, 11, 3, 22, 42, 9, 15};
	int size_of_arr = sizeof(arr) / sizeof(arr[0]);

	arr1 = (int*)malloc(sizeof(arr));
	arr2 = (int*)malloc(sizeof(arr));

	for (;i< size_of_arr; i++)
	{
		if (arr[i] % 2 == 0)
		{
			arr1[j] = arr[i];
			j++;
		}
		else
		{
			arr2[k] = arr[i];
			k++;
		}

	}


	printf("The original array is: ");
	for (i = 0; i < size_of_arr; i++)
		printf("%d ", arr[i]);

	printf("\nThe even array is: ");
	for (i = 0; i < j; i++)
		printf("%d ", arr1[i]);

	printf("\nThe odd array is: ");
	for (i = 0; i < k; i++)
		printf("%d ", arr2[i]);

	free(arr1);
	free(arr2);


}

// 10
/*
PrintArray Function Summary:
---------------------------
Prints the contents of a 2D array in matrix format.
Time Complexity: O(rows * cols)
Parameters:
	a    - The 2D array to print.
	rows - Number of rows in the array.
	cols - Number of columns in the array.
*/
void PrintArray(int a[ROWS][COLS], int rows, int cols) {
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			printf("[%d] ", a[j][i]);
		}
		printf("\n");
	}
}

/*
InputArray Function Summary:
---------------------------
Prompts the user to input values for a 2D array.
Time Complexity: O(rows * cols)
Parameters:
	a    - The 2D array to fill.
	rows - Number of rows in the array.
	cols - Number of columns in the array.
*/
void InputArray(int a[ROWS][COLS], int rows, int cols) {
	printf("size of array=[%d][%d] \n", rows, cols);
	printf("insert [%d][%d] numbers to the array:\n", rows, cols);
	for (int j = 0; j < cols; j++) {
		for (int i = 0; i < rows; i++) {
			printf("n[%d][%d]=", i, j);
			scanf("%d", &a[i][j]);
		}
		printf("\n");
	}
}

/*
SortCheck Function Summary:
--------------------------
Checks if the rows and/or columns of a 2D array are sorted in strictly increasing order.
Time Complexity: O(rows * cols)
Parameters:
	a    - The 2D array to check.
	rows - Number of rows in the array.
	cols - Number of columns in the array.
Returns:
	3 if both rows and columns are sorted
	2 if only rows are sorted
	1 if only columns are sorted
	0 if neither are sorted
*/
int SortCheck(int a[ROWS][COLS], int rows, int cols) {
	int rowcheck = 2;
	int colcheck = 1;
	for (int j = 0; j < cols; j++) {
		for (int i = 0; i < rows - 1; i++) {
			if (a[i][j] >= a[i + 1][j]) {
				colcheck = 0;
				break;
			}
		}
		printf("colnum[%d], colcheck=%d\n", j, colcheck);
	}
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols - 1; i++) {
			if (a[j][i] >= a[j][i + 1]) {
				rowcheck = 0;
				break;
			}
		}
		printf("rownum[%d], rowcheck=%d\n", j, rowcheck);
	}
	if (rowcheck == 2 && colcheck == 1) {
		return 3;
	} else if (rowcheck == 0 && colcheck == 1) {
		return 1;
	} else if (rowcheck == 2 && colcheck == 0) {
		return 2;
	} else {
		return 0;
	}
}

/*
array2d_sort_check_menu Function Summary:
----------------------------------------
Menu wrapper for the 2D array sort check feature. Handles user input, displays the array, checks sorting, and prints the result.
Time Complexity: O(rows * cols)
*/
void array2d_sort_check_menu() {
	int array[ROWS][COLS];
	InputArray(array, ROWS, COLS);
	PrintArray(array, ROWS, COLS);
	int Check = SortCheck(array, ROWS, COLS);
	printf("Check=%d \n", Check);
	switch (Check) {
		case 3:
			printf("The Matrix is sorted\n");
			break;
		case 2:
			printf("Only the rows are sorted\n");
			break;
		case 1:
			printf("Only the columns are sorted\n");
			break;
		case 0:
			printf("The Matrix is not sorted\n");
			break;
	}
}

// 11
/*
inputArray1D Function Summary:
-----------------------------
Prompts the user to input values for a 1D array.
Time Complexity: O(n)
Parameters:
	a   - The 1D array to fill.
	len - Number of elements in the array.
*/
void inputArray1D(int a[], int len) {
	printf("size of array=%d \n", len);
	printf("insert %d numbers to the array:\n", len);
	for (int i = 0; i < len; i++) {
		printf("n[%d]=", i);
		scanf("%d", &a[i]);
	}
}

/*
printArray1D Function Summary:
-----------------------------
Prints the contents of a 1D array.
Time Complexity: O(n)
Parameters:
	a   - The 1D array to print.
	len - Number of elements in the array.
*/
void printArray1D(int a[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

/*
removeDup1D Function Summary:
----------------------------
Removes duplicate elements from a 1D array in-place.
Time Complexity: O(n^2)
Parameters:
	a   - The 1D array to process.
	len - Number of elements in the array.
Returns:
	The new length of the array after removing duplicates.
*/
int removeDup1D(int a[], int len) {
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; ) {
			if (a[i] == a[j]) {
				for (int k = j; k < len - 1; k++) {
					a[k] = a[k + 1];
				}
				len--;
			} else {
				j++;
			}
		}
	}
	return len;
}

/*
selectionSort1D Function Summary:
--------------------------------
Sorts a 1D array in ascending order using selection sort.
Time Complexity: O(n^2)
Parameters:
	n    - The 1D array to sort.
	leng - Number of elements in the array.
*/
void selectionSort1D(int n[], int leng) {
	int temp, temp2;
	for (int i = 0; i < leng - 1; i++) {
		temp = n[i];
		temp2 = i;
		for (int j = i + 1; j < leng; j++) {
			if (temp > n[j]) {
				temp = n[j];
				temp2 = j;
			}
		}
		n[temp2] = n[i];
		n[i] = temp;
		printArray1D(n, leng);
	}
}

void array1d_utilities_menu() {
	int ar[SIZE_1D];
	int len = SIZE_1D;
	int choice;
	do {
		printf("\n1D Array Utilities Menu\n");
		printf("1. Input Array\n");
		printf("2. Print Array\n");
		printf("3. Remove Duplicates\n");
		printf("4. Selection Sort\n");
		printf("0. Return to Main Menu\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				inputArray1D(ar, len);
				break;
			case 2:
				printArray1D(ar, len);
				break;
			case 3:
				len = removeDup1D(ar, len);
				printf("Array after removing duplicates:\n");
				printArray1D(ar, len);
				break;
			case 4:
				selectionSort1D(ar, len);
				printf("Array after selection sort:\n");
				printArray1D(ar, len);
				break;
			case 0:
				break;
			default:
				printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 0);
}

// Main program

int main() {
	int choice;
	do {
		printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!\n");
		printf("Main Menu\n");
		printf("1. Multiplication\n");
		printf("2. Prime Number in Range\n");
		printf("3. Reverse Number\n");
		printf("4. Fibonacci (Iterative & Recursive)\n");
		printf("5. Armstrong Number Check\n");
		printf("6. Next Day Calculator\n");
		printf("7. Prime Calculator (Sieve)\n");
		printf("8. Remove Duplicates from Array\n");
		printf("9. Odd/Even Array Split\n");
		printf("10. 2D Array Sort Check\n");
		printf("11. 1D Array Utilities\n");
		printf("0. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		printf("\n");
		switch (choice) {
			case 1:
				multiplication_menu();
				break;
			case 2:
				prime_menu();
				break;
			case 3:
				reverse_menu();
				break;
			case 4:
				fibonacci_menu();
				break;
			case 5:
				ArmstrongMenu();
				break;
			case 6:
				NextDate();
				break;
			case 7:
				IS_Prime();
				break;
			case 8:
				crt_array();
				break;
			case 9:
				even_odd_arr();
				break;
			case 10:
				array2d_sort_check_menu();
				break;
			case 11:
				array1d_utilities_menu();
				break;
			case 0:
				printf("Exiting program. Goodbye!\n");
				break;
			default:
				printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 0);
	return 0;
}
