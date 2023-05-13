#include <iostream>
#include <Windows.h>
#include <omp.h>
#include<cstdlib>
using namespace std;

int static MIN_SIZE = 2;
int static MAX_SIZE = 20;


int ** declare_MxN_matrixay(int row, int col) {
	int** matrix = new int* [row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new int[col];
	}
	return matrix;
}

void randomGenerator(int ** matrix, int row, int col) {

	srand((unsigned)time(NULL));

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int randm = 1 + rand() % 10;
			matrix[i][j] = randm;
		}
	}
	
}

void printMatrix(int** matrix, int row, int col) {
	cout << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}


int partition(int* arr, int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1);


	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than the pivot
		if (arr[j] < pivot) {
			i++; // increment index of smaller element
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}


void quickSort(int* arr, int low, int high)
{

	if (low < high) {
		int index = partition(arr, low, high);
#pragma omp parallel sections
		{
#pragma omp section
			quickSort(arr, low, index - 1);
#pragma omp section
			quickSort(arr, index + 1, high);
		}
	}
}

void quickSortAsce(int** matrix, int row, int col) {
	//set number of threads dynamically
	omp_set_num_threads(row);
	//omp_set_nested(1);
#pragma omp parallel for
	for (int i = 0; i < row; i++) {
		cout << "\nID assigned to threads :  " << omp_get_thread_num();
		quickSort(matrix[i], 0, col - 1);
	}

}

void matrix_multiplication_static_default(int** matrix, int row, int col, int threads = 0) {
	long long product = 1;
	double start_time, end_time;


	if (threads == 0) {
		cout << "\nThreads should be specified: ";
		return;
	}

	omp_set_num_threads(threads);

	start_time = omp_get_wtime();

#pragma omp parallel for reduction(*:product) schedule(static)
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			product *= matrix[i][j];
		}
	}

	end_time = omp_get_wtime();
	double elapsed_time = end_time - start_time;

	cout << "\nThreads:  " << threads << "\t |  Mapping Scheme:  static \t |  Chunk Size:  df" << "\t |  Elapsed time:  " << elapsed_time << "\t |  Result: " << product;
}

void matrix_multiplication_static(int** matrix, int row, int col, int threads = 0, int chunk_size = 0) {
	long long product = 1;
	double start_time, end_time;


	if (threads == 0 || chunk_size == 0) {
		cout << "\nThread/ Chunk Size should be specified: ";
		return;
	}
	
	omp_set_num_threads(threads);

	start_time = omp_get_wtime();

#pragma omp parallel for reduction(*:product) schedule(static, chunk_size)
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			product *= matrix[i][j];
		}
	}

	end_time = omp_get_wtime();
	double elapsed_time = end_time - start_time;

	cout << "\nThreads:  " << threads << "\t |  Mapping Scheme:  static \t |  Chunk Size:  " << chunk_size << "\t |  Elapsed time:  " << elapsed_time << "\t |  Result: " << product;
}

void matrix_multiplication_dynamic_default(int** matrix, int row, int col, int threads = 0) {
	long long product = 1;
	double start_time, end_time;


	if (threads == 0) {
		cout << "\nThreads should be specified: ";
		return;
	}

	omp_set_num_threads(threads);

	start_time = omp_get_wtime();

#pragma omp parallel for reduction(*:product) schedule(dynamic)
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			product *= matrix[i][j];
		}
	}

	end_time = omp_get_wtime();
	double elapsed_time = end_time - start_time;

	cout << "\nThreads:  " << threads << "\t |  Mapping Scheme:  dynamic \t |  Chunk Size:  df" << "\t |  Elapsed time:  " << elapsed_time << "\t |  Result: " << product;
}

void matrix_multiplication_dynamic(int** matrix, int row, int col, int threads = 0, int chunk_size = 0) {
	long long product = 1;
	double start_time, end_time;


	if (threads == 0 || chunk_size == 0) {
		cout << "\nThread/ Chunk Size should be specified: ";
		return;
	}

	omp_set_num_threads(threads);

	start_time = omp_get_wtime();

#pragma omp parallel for reduction(*:product) schedule(dynamic, chunk_size)
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			product *= matrix[i][j];
		}
	}

	end_time = omp_get_wtime();
	double elapsed_time = end_time - start_time;

	cout << "\nThreads:  " << threads << "\t |  Mapping Scheme:  dynamic\t |  Chunk Size:  " << chunk_size << "\t |  Elapsed time:  " << elapsed_time << "\t |  Result: " << product;
}

void matrix_multiplication_guided_default(int** matrix, int row, int col, int threads = 0) {
	long long product = 1;
	double start_time, end_time;


	if (threads == 0) {
		cout << "\nThreads should be specified: ";
		return;
	}

	omp_set_num_threads(threads);

	start_time = omp_get_wtime();

#pragma omp parallel for reduction(*:product) schedule(guided)
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			product *= matrix[i][j];
		}
	}

	end_time = omp_get_wtime();
	double elapsed_time = end_time - start_time;

	cout << "\nThreads:  " << threads << "\t |  Mapping Scheme:  guided \t |  Chunk Size:  df" << "\t |  Elapsed time:  " << elapsed_time << "\t |  Result: " << product;
}

void matrix_multiplication_guided(int** matrix, int row, int col, int threads = 0, int chunk_size = 0) {
	long long product = 1;
	double start_time, end_time;


	if (threads == 0 || chunk_size == 0) {
		cout << "\nThread/ Chunk Size should be specified: ";
		return;
	}

	omp_set_num_threads(threads);

	start_time = omp_get_wtime();

#pragma omp parallel for reduction(*:product) schedule(guided, chunk_size)
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			product *= matrix[i][j];
		}
	}

	end_time = omp_get_wtime();
	double elapsed_time = end_time - start_time;

	cout << "\nThreads:  " << threads << "\t |  Mapping Scheme:  guided\t |  Chunk Size:  " << chunk_size << "\t |  Elapsed time:  " << elapsed_time << "\t |  Result: " << product;
}

void call_static_dynamic_guided(int** matrix, int matrix_rows, int matrix_cols, int threads) {
	// static : threads 2,4,8,16 , chunk size : default
	matrix_multiplication_static_default(matrix, matrix_rows, matrix_cols, threads);

	//static : threads 2,4,8,16 , chunk size 1
	matrix_multiplication_static(matrix, matrix_rows, matrix_cols, threads, 1);

	//static : threads 2,4,8,16 , chunk size 2
	matrix_multiplication_static(matrix, matrix_rows, matrix_cols, threads, 2);

	//static : threads 2,4,8,16 , chunk size 4
	matrix_multiplication_static(matrix, matrix_rows, matrix_cols, threads, 4);

	// dynamic : threads 2,4,8,16 , chunk size : default
	matrix_multiplication_dynamic_default(matrix, matrix_rows, matrix_cols, threads);

	//dynamic : threads 2,4,8,16 , chunk size 1
	matrix_multiplication_dynamic(matrix, matrix_rows, matrix_cols, threads, 1);

	//dynamic : threads 2,4,8,16 , chunk size 2
	matrix_multiplication_dynamic(matrix, matrix_rows, matrix_cols, threads, 2);

	//dynamic : threads 2,4,8,16 , chunk size 4
	matrix_multiplication_dynamic(matrix, matrix_rows, matrix_cols, threads, 4);

	//guided : threads 2,4,8,16 , chunk size : default
	matrix_multiplication_guided_default(matrix, matrix_rows, matrix_cols, threads);

	//guided : threads 2,4,8,16 , chunk size 1
	matrix_multiplication_guided(matrix, matrix_rows, matrix_cols, threads, 1);

	//guided : threads 2,4,8,16 , chunk size 2
	matrix_multiplication_guided(matrix, matrix_rows, matrix_cols, threads, 2);

	//guided : threads 2,4,8,16 , chunk size 4
	matrix_multiplication_guided(matrix, matrix_rows, matrix_cols, threads, 4);
}

int main() {

	//********************** Part A **********************
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MAXIMIZE);

	int matrix_rows = 0, matrix_cols = 0;

	cout << "***** This is a multithreaded matrix operation task *****";
	cout << "\nEnter Number of Rows: ";
	cin >> matrix_rows;
	cout << "\nEnter Number of Columns: ";
	cin >> matrix_cols;

	if (matrix_rows < MIN_SIZE || matrix_cols < MIN_SIZE || matrix_rows > MAX_SIZE || matrix_cols > MAX_SIZE) {
		cout << "\nMIN ROW AND COLUMN SHOULD BE 2 AND MAX SIZE SHOUDL BE 20";
		return 0;
	}

	//initialize matrixay
	int** matrix = declare_MxN_matrixay(matrix_rows, matrix_cols);

	//initialize with random numbers
	randomGenerator(matrix, matrix_rows, matrix_cols);


	//print
	cout << "\nBefore Sorting: ";
	printMatrix(matrix, matrix_rows, matrix_cols);


	//sorting
	quickSortAsce(matrix, matrix_rows, matrix_cols);

	//print
	cout << "\nAfter Sorting: ";
	printMatrix(matrix, matrix_rows, matrix_cols);



	//********************** Part B **********************
	cout << "\nThreads 2,4,8,16\n";
	call_static_dynamic_guided(matrix, matrix_rows, matrix_cols, 2);
	cout << endl;
	call_static_dynamic_guided(matrix, matrix_rows, matrix_cols, 4);
	cout << endl;
	call_static_dynamic_guided(matrix, matrix_rows, matrix_cols, 8);
	cout << endl;
	call_static_dynamic_guided(matrix, matrix_rows, matrix_cols, 16);


	return 0;
}
