#include <stdio.h>

#define ROW_SIZE 21
#define INPUT_SIZE 200
#define ARRAY_SIZE (ROW_SIZE)*(ROW_SIZE+1)/2

long long compute_diff(long long* array, int start, int end);
long long compute_diff_backward(long long* array, int start, int end);
void print_diff(long long* array);

int main(int argc, char** argv) {
    long long result, result_2;

    result = 0LL;
    result_2 = 0LL;

    for (int j = 0; j < INPUT_SIZE; ++j) {
        long long row[ARRAY_SIZE] = { 0L };
        for (int i = 0; i < ROW_SIZE; ++i) {
            scanf("%lld", &row[i]);
        }
        long long tmp_result = compute_diff(row, 0, ROW_SIZE);
        result += tmp_result;
        long long tmp_result_2 = compute_diff_backward(row, 0, ROW_SIZE);
        result_2 += tmp_result_2;
    }

    printf("\n(1) %lld (2) %lld\n", result, result_2);

    return 0;
}


long long compute_diff(long long* array, int row_start, int row_end) {
    long last_row = 1;

    
    for (int i = 0; i < row_end-row_start-1; i++) {
        long diff = array[row_start + i + 1] - array[row_start + i];
        array[row_end + i] = diff;
        last_row = last_row && (diff == 0);
    }


    if (last_row == 0) {
        int next_start = row_end;
        int next_end = next_start + (row_end - row_start -1);
        long long diff = compute_diff(array, next_start, next_end);

        return diff + array[row_end-1];
    }

    return array[row_end - 1];
}

long long compute_diff_backward(long long* array, int row_start, int row_end) {
    long last_row = 1;

    
    for (int i = 0; i < row_end-row_start-1; i++) {
        long diff = array[row_start + i + 1] - array[row_start + i];
        array[row_end + i] = diff;
        last_row = last_row && (diff == 0);
    }


    if (last_row == 0) {
        int next_start = row_end;
        int next_end = next_start + (row_end - row_start -1);
        long long diff = compute_diff_backward(array, next_start, next_end);

        return array[row_start] - diff;
    }

    return array[row_start];
}

void print_diff(long long* array) {
    int break_at = ROW_SIZE;
    int count = 1;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (i == break_at) {
            putchar('\n');
            break_at += (ROW_SIZE) - count;
            count++;
        }
        printf("%8lld ", array[i]);
    }

}
