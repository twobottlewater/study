#include <stdio.h>
#include <string.h>

void compressString(char *input, char *output) {
    int len = strlen(input);
    int count = 1;
    int j = 0;  // Output index

    for (int i = 0; i < len; i++) {
        if (input[i] == input[i + 1]) {
            count++;
        } else {
            // Append current character and its count to the output
            j += sprintf(output + j, "%c%d", input[i], count);
            count = 1;  // Reset count for the next character
        }
    }
    output[j] = '\0';  // Null-terminate the output string
}

int main() {
    char input[100];
    char output[200];  // Make sure this is large enough to hold the output

    printf("Enter a string: ");
    scanf("%99s", input);  // Read string from user

    compressString(input, output);

    printf("Compressed string: %s\n", output);

    return 0;
}