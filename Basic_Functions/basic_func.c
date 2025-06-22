/*
Assigned by:
Name: Brian Sch
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>


void NextDate();
void IS_Prime();
void crt_array();
void even_odd_arr();

// Functions

// 1.1
void NextDate() {

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

// 1.2
void IS_Prime() {
	

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

// 1.3
int Remove_Dup(int arry1[], int arry2[], int size) {

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

void Sort(int sort[], int size) {
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


void crt_array() {
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

// 1.4
void even_odd_arr() {

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

// Main program

void main() {

	printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!\n");
	printf("1.1 Next Day calculator\n\n");
	NextDate();

	printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!\n");
	printf("1.2 Prime Calculator\n\n");
	IS_Prime();

	printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!\n");
	printf("1.3 Remove Duplicates\n\n");
	crt_array();

	printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!\n");
	printf("1.4 Odd Even Arrays\n\n");
	even_odd_arr();

}

