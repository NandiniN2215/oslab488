#include <stdio.h>

int main() {
    int rows, cols, i, j;

    // 1. Get matrix dimensions from the user
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    if (rows <= 0 || cols <= 0) {
        printf("Invalid dimensions. Rows and columns must be greater than 0.\n");
        return 1;
    }

    int matrix[rows][cols];

    // 2. Get matrix elements from the user
    printf("\nEnter the elements of the %dx%d matrix:\n", rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // 3. Print the matrix for visual clarity
    printf("\n--- Entered Matrix ---\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("----------------------\n");

    // 4. Calculate and print Row Sums
    printf("\n--- Sum of Rows ---\n");
    for (i = 0; i < rows; i++) {
        int row_sum = 0;
        for (j = 0; j < cols; j++) {
            row_sum += matrix[i][j];
        }
        printf("Sum of Row %d = %d\n", i + 1, row_sum);
    }

    // 5. Calculate and print Column Sums
    printf("\n--- Sum of Columns ---\n");
    for (j = 0; j < cols; j++) {
        int col_sum = 0;
        for (i = 0; i < rows; i++) {
            col_sum += matrix[i][j]; // Notice we iterate through rows while keeping column 'j' fixed
        }
        printf("Sum of Column %d = %d\n", j + 1, col_sum);
    }

    return 0;
}
