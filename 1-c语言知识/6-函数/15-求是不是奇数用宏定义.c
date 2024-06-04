#include <stdio.h>
#if 0
#define COUNT_ELEMENTS(array) (sizeof(array) / sizeof((array)[0]))

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int count = COUNT_ELEMENTS(arr);
    printf("array 的元素个数is: %d\n", count);
    return 0;
}
#endif

#define IS_EVEN(number) (((number) % 2) == 0)

int main() {
    int num = 5;
    if (IS_EVEN(num)) {
        printf("%d is even.\n", num);
    } else {
        printf("%d is odd.\n", num);
    }
    return 0;
}