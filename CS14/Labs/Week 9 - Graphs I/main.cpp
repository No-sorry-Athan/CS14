#include <iostream>
#include <time.h>
using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

void Quicksort_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numberSize);


const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
	return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[]) {
	for (int i = 0; i < NUMBERS_SIZE; ++i) {
		arr1[i] = genRandInt(0, NUMBERS_SIZE);
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
	}
}

int main() {
	int arr1[NUMBERS_SIZE];
	int arr2[NUMBERS_SIZE];
	int arr3[NUMBERS_SIZE];
	fillArrays(arr1, arr2, arr3);
	/*cout << "\t\tUNSORTED" << endl;
	for (int i = 0; i < NUMBERS_SIZE; i++) {
		cout << arr1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < NUMBERS_SIZE; i++) {
		cout << arr2[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < NUMBERS_SIZE; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << "\t\tSORTED" << endl;*/
	clock_t Start = clock();
	Quicksort_midpoint(arr1, 0, NUMBERS_SIZE-1);
	clock_t End = clock();
	int elapsedTime = (End - Start) / CLOCKS_PER_MS;
	cout << elapsedTime << endl;
	/*for (int i = 0; i < NUMBERS_SIZE; i++) {
		cout << arr1[i] << " ";
	}*/
	/*cout << endl;*/
	Start = clock();
	Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE-1);
	End = clock();
	elapsedTime = (End - Start) / CLOCKS_PER_MS;
	cout << elapsedTime << endl;
	/*for (int i = 0; i < NUMBERS_SIZE; i++) {
		cout << arr2[i] << " ";
	}*/
	/*cout << endl;*/
	Start = clock();
	InsertionSort(arr3, NUMBERS_SIZE);
	End = clock();
	elapsedTime = (End - Start) / CLOCKS_PER_MS;
	cout << elapsedTime << endl;
	/*for (int i = 0; i < NUMBERS_SIZE; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;*/

	return 0;
}

int partition(int numbers[], int i, int k) {
	int midpoint = i + (k-i) / 2;
	int pivot = numbers[midpoint];

	int l = i;
	int h = k;
	bool t = true;
	while (t) {
		while (numbers[l] < pivot) {
			l++;
		}
		while (numbers[h] > pivot) {
			h--;
		}

		if (l >= h) {
			t = false;
		}
		else {
			int temp = numbers[l];
			numbers[l] = numbers[h];
			numbers[h] = temp;
			l++;
			h--;
		}
	}
	return h;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
	int j = 0;
	if (i >= k)
		return;

	j = partition(numbers, i, k);
	Quicksort_midpoint(numbers, i, j);
	Quicksort_midpoint(numbers, j + 1, k);
}

int medianPartition(int numbers[], int i, int k) {
	int m = i + (k - i) / 2;

	int middle = 0;
	if ((numbers[i] >= numbers[k] && numbers[i] <= numbers[m]) || (numbers[i] <= numbers[k] && numbers[i] >= numbers[m])) {
		middle = i;
	}
	else if ((numbers[k] >= numbers[i] && numbers[k] <= numbers[m]) || (numbers[k] <= numbers[i] && numbers[k] >= numbers[m])) {
		middle = k;
	}
	else if ((numbers[m] >= numbers[i] && numbers[m] <= numbers[k]) || (numbers[m] <= numbers[i] && numbers[m] >= numbers[k])) {
		middle = m;
	}
	int pivot = numbers[middle];
	int l = i;
	int r = k;

	bool t = true;
	while (t) {
		while (numbers[l] < pivot) {
			l++;
		}
		while (numbers[r] > pivot) {
			r--;
		}

		if (l >= r) {
			t = false;
		}
		else {
			int temp = numbers[l];
			numbers[l] = numbers[r];
			numbers[r] = temp;
			l++;
			r--;
		}
	}
	return r;
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
	int j = 0;
	if (i >= k) {
		return;
	}
	j = medianPartition(numbers, i, k);
	Quicksort_medianOfThree(numbers, i, j);
	Quicksort_medianOfThree(numbers, j + 1, k);
	

}

void InsertionSort(int numbers[], int numberSize) {
	for (int i = 1; i < numberSize; i++) {
		int j = i;
		while (j > 0 && numbers[j] < numbers[j - 1]) {
			int temp = numbers[j];
			numbers[j] = numbers[j - 1];
			numbers[j - 1] = temp;
			j--;
		}
	}
}