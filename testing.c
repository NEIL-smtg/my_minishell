#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Enter a command: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0'; // remove the newline character from input

    char* token;
    char* rest = input;
    int in_quotes = 0;
    int in_single_quotes = 0;
    int in_brackets = 0;
    int escape_next_char = 0;

    while ((token = strtok_r(rest, " ", &rest))) {
        int len = strlen(token);
        for (int i = 0; i < len; i++) {
            char c = token[i];
            if (c == '\\') {
                escape_next_char = 1;
            } else if (c == '"' && !in_single_quotes) {
                in_quotes = !in_quotes;
            } else if (c == '\'' && !in_quotes) {
                in_single_quotes = !in_single_quotes;
            } else if (c == '(' && !in_quotes && !in_single_quotes) {
                in_brackets++;
            } else if (c == ')' && !in_quotes && !in_single_quotes) {
                in_brackets--;
            }
        }

        if (escape_next_char) {
            printf("%s\\", token);
            escape_next_char = 0;
        } else if (in_quotes || in_single_quotes || in_brackets) {
            printf("%s ", token);
        } else {
            printf("%s\n", token);
        }
    }

    return 0;
}
