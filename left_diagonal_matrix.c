#include <stdio.h>

int main() {
    int size, i, j;
    int sum = 0;

    // 1. Get the matrix size from the user (must be a square matrix)
    printf("Enter the size of the square matrix (N x N): ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid matrix size.\n");
        return 1;
    }

    int matrix[size][size];

    // 2. Get the matrix elements from the user
    printf("Enter the elements of the %dx%d matrix:\n", size, size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // 3. Print the entered matrix for visual clarity
    printf("\nYour Matrix:\n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    // 4. Calculate the sum of the left diagonal
    // Optimized approach: We only need one loop since row index == column index (i == j)
    for (i = 0; i < size; i++) {
        sum += matrix[i][i];
    }

    // 5. Output the result
    printf("\nThe sum of the left diagonal elements is: %d\n", sum);

    return 0;
}
