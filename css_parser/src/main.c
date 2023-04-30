#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

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

// ---------------

size_t extract_css_class_name(const char* line, size_t line_len, char* css_name) {
    if (line_len == 0) { return 0; }

    size_t css_idx = 0;

    for (int i = 1; i < line_len; i++) {
        char next_char = line[i];

        if (char_is_newline(next_char)) {
            css_name[css_idx] = '\0';
            ++css_idx;
        } else if (
            char_is_alpha(next_char) ||
            char_is_number(next_char) ||
            next_char == '-'
        ) {
            css_name[css_idx] = next_char;
            ++css_idx;
        } else {
            // do nothing
        }
    }

    css_name[css_idx] = '\0';

    return css_idx;
}

size_t css_to_rust_names(const char* css_name, size_t css_len, char* rust_name) {
    if (css_len == 0) { return 0; }

    // convert first letter to uppercase
    rust_name[0] = char_to_uppercase(css_name[0]);

    int rust_idx = 1;
    for (int css_idx = 1; css_idx < css_len; css_idx++) {
        char next_char = css_name[css_idx];

        // capitalize first character after '-'
        if (next_char == '-') {
            ++css_idx;

            next_char = css_name[css_idx];
            if (char_is_lowercase(next_char)) {
                rust_name[rust_idx] = char_to_uppercase(next_char);
            } else {
                rust_name[rust_idx] = css_name[css_idx];
            }
        }
        // append other characters
        else {
            rust_name[rust_idx] = css_name[css_idx];
        }

        rust_idx++;
    }

    rust_name[rust_idx] = '\0';

    return rust_idx;
}




const int OUT_BUF_SIZE = 4096;
const int LINE_BUF_SIZE = 64;
const size_t MAX_NAMES = 1024;
const size_t MAX_NAME_LEN = 128;

bool parse_file(char* in_file_path, char* out_file_path, char* enum_name) {
    FILE *fp_in;

    // open int file
    fp_in = fopen(in_file_path, "r");
    if (fp_in == NULL) {
        printf("Error opening input file: '%s'\n", in_file_path);
        return false;
    }

    // parse file
    char leader = '.';
    char line_buf[LINE_BUF_SIZE];
    char css_names[MAX_NAMES][MAX_NAME_LEN];
    char rust_names[MAX_NAMES][MAX_NAME_LEN];
    size_t name_count = 0;

    while (fgets(line_buf, LINE_BUF_SIZE, fp_in) != NULL) {
        if (strncmp(line_buf, &leader, 1) == 0) {
            size_t line_len = strlen(line_buf);
            size_t css_len = extract_css_class_name(line_buf, line_len, css_names[name_count]);

            int rust_len = css_to_rust_names(css_names[name_count], css_len, rust_names[name_count]);

            // printf("[CSS ]: '%s' | ", css_names[name_count]);
            // printf("[RUST]: '%s' \n", rust_names[name_count]);

            ++name_count;
        }
    }

    // close input file
    // fclose(fp_in);

    // open output_file
    FILE *fp_out;
    // open out file
    fp_out = fopen(out_file_path, "w");
    if (fp_out == NULL) {
        perror("Error opening input file");
        return false;
    }

    // write enum declaraton
    fprintf(fp_out, "#[allow(unused)]\n");
    fprintf(fp_out, "pub enum %s {\n", enum_name);
    for (size_t i = 0; i < name_count; i++) {
        fprintf(fp_out, "\t%s,\n", rust_names[i]);
    }
    fprintf(fp_out, "}\n");

    // write AsRefimpl block


    fprintf(fp_out, "impl AsRef<str> for %s {\n", enum_name);
    fprintf(fp_out, "\tfn as_ref(&self) -> &str {\n");
    fprintf(fp_out, "\t\tmatch &self {\n");
    for (size_t i = 0; i < name_count; i++) {
        fprintf(fp_out, "\t\t\t%s => \"%s\",\n", rust_names[i], css_names[i]);
    }
    fprintf(fp_out, "\t\t}\n");
    fprintf(fp_out, "\t}\n");
    fprintf(fp_out, "}\n");


    // close output file
    fclose(fp_out);

    return true;
}

int main(int argc, char **argv) {
    printf("parsing css file ...\n");

    assert(argc == 4);
    if (!parse_file(argv[1], argv[2], argv[3])) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("failed to parse file: '%s', '%s', '%s', '%s", cwd, argv[1], argv[2], argv[3]);
        return 1;
    }

    printf("successfully parsed css file ...\n");
    return 0;
}
