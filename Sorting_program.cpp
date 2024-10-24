#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>  // For rand()

// Function to generate a dataset of random integers
std::vector<int> generateDataset(int size) {
    std::vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 10000; // Random numbers between 0 and 9999
    }
    return data;
}

// Merge Sort Functions
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// QuickSort Functions
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to measure and return the time taken by a sorting function
double measureSortTime(int arr[], int size, void (*sortFunc)(int[], int, int)) {
    clock_t start = clock();  // Start the timer
    sortFunc(arr, 0, size - 1); // Call the sorting function
    clock_t end = clock();  // End the timer
    return double(end - start) / CLOCKS_PER_SEC;  // Return time in seconds
}

// Function to collect data and write to CSV file
void collectDataForAlgorithms() {
    std::ofstream outfile("sorting_times.csv");
    
    // Check if file opened correctly
    if (!outfile) {
        std::cerr << "Error: Could not open file 'sorting_times.csv' for writing." << std::endl;
        return;
    }

    // Write the header row
    outfile << "DatasetSize,MergeSortTime,QuickSortTime\n";

    // Iterate through various dataset sizes
    for (int size = 100; size <= 100000; size *= 10) {
        std::vector<int> dataset = generateDataset(size);  // Generate random dataset
        int* arrMergeSort = new int[size];
        int* arrQuickSort = new int[size];

        // Copy the dataset to two arrays for both sorts
        std::copy(dataset.begin(), dataset.end(), arrMergeSort);
        std::copy(dataset.begin(), dataset.end(), arrQuickSort);

        // Measure time for MergeSort
        double mergeSortTime = measureSortTime(arrMergeSort, size, mergeSort);

        // Measure time for QuickSort
        double quickSortTime = measureSortTime(arrQuickSort, size, quickSort);

        // Write the data to the CSV file
        outfile << size << "," << mergeSortTime << "," << quickSortTime << "\n";

        // Clean up the dynamically allocated memory
        delete[] arrMergeSort;
        delete[] arrQuickSort;
    }

    // Close the file after writing
    outfile.close();
}

int main() {
    srand(time(0)); // Seed the random number generator
    collectDataForAlgorithms(); // Collect sorting data and write to CSV
    std::cout << "Sorting times written to 'sorting_times.csv'.\n";
    return 0;
}
