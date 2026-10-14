# Pseudo-code de my_ls
FUNCTION print_text(string)
    i <- 0
    WHILE string[i] != '\0'
        write character string[i] to standard output
        i <- i + 1
    END WHILE
END FUNCTION

FUNCTION string_length(string)
    length <- 0
    WHILE string[length] != '\0'
        length <- length + 1
    END WHILE
    RETURN length
END FUNCTION

FUNCTION compare_words(string1, string2)
    i <- 0
    WHILE string1[i] != '\0' AND string2[i] != '\0' AND string1[i] = string2[i]
        i <- i + 1
    END WHILE
    RETURN difference between the character codes of string1[i] and string2[i]
END FUNCTION

FUNCTION copy_word(source, destination)
    i <- 0
    WHILE source[i] != '\0'
        destination[i] <- source[i]
        i <- i + 1
    END WHILE
    destination[i] <- '\0'
END FUNCTION

FUNCTION sort_files(files, file_count)
    DECLARE temp[256]
    FOR i FROM 0 TO file_count - 2
        FOR j FROM 0 TO file_count - i - 2
            IF compare_words(files[j], files[j + 1]) > 0
                copy_word(files[j], temp)
                copy_word(files[j + 1], files[j])
                copy_word(temp, files[j + 1])
            END IF
        END FOR
    END FOR
END FUNCTION

FUNCTION read_directory(option_a)
    directory <- opendir(".")
    IF directory = NULL
        print "Error: could not open directory."
        RETURN
    END IF
    DECLARE file_list[256][256]
    total_files <- 0
    WHILE next entry exists in directory
        IF option_a = false AND entry.name starts with "."
            CONTINUE
        END IF
        copy_word(entry.name, file_list[total_files])
        total_files <- total_files + 1
    END WHILE
    closedir(directory)
    sort_files(file_list, total_files)
    FOR i FROM 0 TO total_files - 1
        print_text(file_list[i])
        print_text("\n")
    END FOR
END FUNCTION

MAIN
    option_a <- false
    FOR i FROM 1 TO argc - 1
        IF argv[i][0] = '-'
            FOR j FROM 1 WHILE argv[i][j] != '\0'
                IF argv[i][j] = 'a'
                    option_a <- true
                END IF
            END FOR
        END IF
    END FOR
    read_directory(option_a)
    RETURN 0
END MAIN