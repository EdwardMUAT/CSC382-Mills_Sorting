import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import csv

# Read the CSV file into a DataFrame
df = pd.read_csv('C:/Users/edwar/CSC382/sorting/Data/sorting_times.csv')

# Extract dataset sizes and the time taken for each algorithm
dataset_sizes = df['DatasetSize']
merge_sort_times = df['MergeSortTime']
quick_sort_times = df['QuickSortTime']

# Plot the performance
plt.plot(dataset_sizes, merge_sort_times, label="Merge Sort", marker='o')
plt.plot(dataset_sizes, quick_sort_times, label="QuickSort", marker='x')

# Add trendlines
z_merge = np.polyfit(np.log(dataset_sizes), np.log(merge_sort_times), 1)
z_quick = np.polyfit(np.log(dataset_sizes), np.log(quick_sort_times), 1)

# Calculate trendlines
merge_trendline = np.exp(np.polyval(z_merge, np.log(dataset_sizes)))
quick_trendline = np.exp(np.polyval(z_quick, np.log(dataset_sizes)))

plt.plot(dataset_sizes, merge_trendline, '--', label=f"Merge Sort Trend (O(n^{z_merge[0]:.2f}))")
plt.plot(dataset_sizes, quick_trendline, '--', label=f"QuickSort Trend (O(n^{z_quick[0]:.2f}))")

# Label the axes and add a title
plt.xlabel('Dataset Size')
plt.ylabel('Time Taken (seconds)')
plt.title('Sorting Algorithm Performance by Dataset Size')

# Display the legend
plt.legend()

# Show the plot
plt.xscale('log')
plt.yscale('log')
plt.grid(True)
plt.show()
