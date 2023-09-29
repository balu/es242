#include "test.h"

/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */
void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
{     
    int temp[k];
    for (int i = 0; i < k; i++) {
        temp[i] = i;
        b[i] = a[i];
    }
    while (1) {
        process_selection(b, k, data);
        int i = k - 1;
        while (i >= 0 && temp[i] == n - k + i) {
            i--;
        }
        if (i < 0) {
            break;
        }
        temp[i]++;
        b[i] = a[temp[i]];
        for (int j = i + 1; j < k; j++) {
            temp[j] = temp[j - 1] + 1;
            b[j] = a[temp[j]];
        }
    }


}

/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */
void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void (*process_split(char buf[], void *data)))
{
        int start = 0;
    int length_arr = strlen(source);
    int length_buf = 0;
   
    for (int k = 0; k < nwords; ++k)
     {
        int length_word = strlen(dictionary[k]);
        if (length_arr - start >= length_word  && strncmp(source + start, dictionary[k], length_word ) == 0) {
            if (length_buf > 0) {
                buf[length_buf++] = ' ';
            }
            strcpy(buf + length_buf, dictionary[k]);
            start = length_word  + start;
            length_buf = length_word  + length_buf;
            
            if (start == length_arr) {
                process_split(buf, data);
                break;
            }
}
}
}

/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */
void previous_permutation(int a[], int n)
{
     int i = n - 2;
    while (i >= 0 && a[i] <= a[i + 1]) {
        i--;
    }

    if (i >= 0) {
        int j = n - 1;
        while (a[j] >= a[i]) {
            j--;
        }
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
            left++;
            right--;
        }
    }
}

/* Write your tests here. Use the previous assignment for reference. */

int main()
{
    return 0;
}
