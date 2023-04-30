#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool char_is_uppercase(char c) {
    return c >= 'A' && c <= 'Z';
}

bool char_is_lowercase(char c) {
    return c >= 'a' && c <= 'z';
}

bool char_is_alpha(char c) {
    return char_is_uppercase(c) || char_is_lowercase(c);
}

bool char_is_number(char c) {
    return c >= '0' && c <= '9';
}

bool char_is_newline(char c) {
    return c == '\n';
}

char char_to_uppercase(char c) {
    return c - 'a' + 'A';
}

size_t str_remove_at(char* str, size_t len, int index) {
    for (int i = index; i < len; i++) {
        str[i] = str[i + 1];
    }

    return --len;
}

size_t css_class_to_rust_type_name(char* line, size_t len) {
    if (len == 0) { return 0; }

    len = str_remove_at(line, len, 0);
    line[0] = char_to_uppercase(line[0]);

    for (int i = 1; i < len; i++) {
        char next_char = line[i];

        if (next_char == '-') {
            len = str_remove_at(line, len, i);

            next_char = line[i];
            if (char_is_lowercase(next_char)) {
                line[i] = char_to_uppercase(next_char);
            }
        } else if (char_is_newline(next_char)) {
            line[i] = '\0';
        } else if (
            char_is_alpha(next_char) ||
            char_is_number(next_char)
        ) {
            // do nothing
        } else {
            len = str_remove_at(line, len, i);
            --i;
        }
    }

    return len;
}




const int BUF_SIZE = 1024;

int main() {
    printf("parsing css file ...\n");

    FILE *fp_in;
    FILE *fp_out;
    char buf_in[BUF_SIZE];
    char buf_out[BUF_SIZE];

    // open file for reading
    fp_in  = fopen("data/utils.in.css", "r");
    fp_out = fopen("data/utils.out.rs", "w");

    if (fp_in == NULL) {
        perror("Error opening file");
        return -1;
    }

    fputs("pub struct Utils {\n", fp_out);

    char leader = '.';
    while (fgets(buf_in, BUF_SIZE, fp_in) != NULL) {
        if (strncmp(buf_in, &leader, 1) == 0) {
            int len = strlen(buf_in);
            memcpy(buf_out, buf_in, len);
            len = css_class_to_rust_type_name(buf_out, len);

            sprintf(buf_out, "%s,\n", buf_out);
            fputs(buf_out, fp_out);
        }
    }

    fputs("}", fp_out);

    fclose(fp_in);
    fclose(fp_out);

    return 1;
}
