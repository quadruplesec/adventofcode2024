#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

/*
Steps:
1 - Open file
2 - Read # of lines
3 - malloc 2 int arrays of n_line size
4 - sort arrays
5 - check amount of occurences of elements from list 1 in list 2
6 - compute similarity score
*/

int cmp_int(const void *va, const void *vb)
{
  int a = *(int *)va, b = *(int *) vb;
  return a < b ? -1 : a > b ? +1 : 0;
}

int main(void) {
    FILE* input_file = fopen("input.txt", "r");

    char buffer[BUFFER_SIZE];
    int line_count = 0;
    int similarity_score = 0;
    while (true) {
        int n_bytes = fread(buffer, sizeof(char), BUFFER_SIZE, input_file);

        for (int i = 0; i < n_bytes; i++) {
            if (buffer[i] == '\n') {
                line_count++;
            }
        }

        if (feof(input_file)) {
            break;
        }
    }

    rewind(input_file);

    int* array_1 = (int*) malloc(line_count * sizeof(int));
    int* array_2 = (int*) malloc(line_count * sizeof(int));
    int offset = 0;

    int n1, n2;

    while (fscanf(input_file, "%d %d", &n1, &n2) == 2) {
        *(array_1 + offset) = n1;
        *(array_2 + offset) = n2;
        offset++;
    }

    qsort(array_1, line_count, sizeof(int), cmp_int);
    qsort(array_2, line_count, sizeof(int), cmp_int);

    for (int i = 0; i < line_count; i++) {
        int to_check = array_1[i];
        int occurences = 0;

        for (int j = 0; j < line_count; j++) {
            if (array_2[j] == to_check) {
                occurences++;
            }
        }

        similarity_score += to_check * occurences;
    }

    printf("%d\n", similarity_score);

    free(array_1);
    free(array_2);
    fclose(input_file);

    return 0;
}