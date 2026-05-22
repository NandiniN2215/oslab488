#include <stdio.h>
#include <limits.h> // Required for INT_MAX

int main() {
    int n, i;

    // 1. Get the size of the array from the user
    printf("Enter the number of elements in the array: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    // A valid array needs at least 2 elements to have a "second smallest"
    if (n < 2) {
        printf("Error: Array must contain at least 2 elements.\n");
        return 1;
    }

    int arr[n];

    // 2. Get the array elements from the user
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 3. Initialize smallest and second smallest to the maximum possible integer value
    int smallest = INT_MAX;
    int second_smallest = INT_MAX;

    // 4. Find the second smallest element in one pass
    for (i = 0; i < n; i++) {
        if (arr[i] < smallest) {
            // If current element is smaller than 'smallest',
            // then the old 'smallest' becomes the 'second_smallest'
            second_smallest = smallest;
            smallest = arr[i];
        }
        // If current element is between 'smallest' and 'second_smallest'
        else if (arr[i] < second_smallest && arr[i] != smallest) {
            second_smallest = arr[i];
        }
    }

    // 5. Print the result
    if (second_smallest == INT_MAX) {
        printf("There is no second smallest element (all elements might be identical).\n");
    } else {
        printf("The smallest element is: %d\n", smallest);
        printf("The second smallest element is: %d\n", second_smallest);
    }

    return 0;
}
