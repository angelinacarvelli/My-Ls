#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

void print_text(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        write(1, &str[i], 1);
        i++;
    }
}

int string_length(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int compare_words(char *str1, char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) {
        i++;
    }
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}

void copy_word(char *source, char *destination) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

void sort_files(char files[256][256], int file_count) {
    char temp[256];
    for (int i = 0; i < file_count - 1; i++) {
        for (int j = 0; j < file_count - i - 1; j++) {
            if (compare_words(files[j], files[j + 1]) > 0) {
                copy_word(files[j], temp);
                copy_word(files[j + 1], files[j]);
                copy_word(temp, files[j + 1]);
            }
        }
    }
}

void read_directory(int option_a) {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        print_text("Error: could not open directory.\n");
        return;
    }

    struct dirent *entry;
    char file_list[256][256];
    int total_files = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (!option_a && entry->d_name[0] == '.') {
            continue;
        }

        copy_word(entry->d_name, file_list[total_files]);
        total_files++;
    }
    closedir(dir);

    sort_files(file_list, total_files);

    for (int i = 0; i < total_files; i++) {
        print_text(file_list[i]);
        print_text("\n");
    }
}

int main(int argc, char **argv) {
    int option_a = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                if (argv[i][j] == 'a') {
                    option_a = 1;
                }
            }
        }
    }

    read_directory(option_a);

    return 0;
}