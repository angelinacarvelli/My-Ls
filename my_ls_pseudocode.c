Define + Include

STRUCTURE FileInfo
    name
    path
    modification_time
    is_directory
    exists
END STRUCTURE

STRUCTURE Options
    opt_a
    opt_t
END STRUCTURE

FUNCTION my_strlen(string)
    length <- 0
    WHILE string exists AND string[length] exists
        length <- length + 1
    END WHILE

    RETURN length
END FUNCTION

FUNCTION my_strcmp(string1, string2)
    i <- 0

    WHILE string1[i] exists
          AND string2[i] exists
          AND string1[i] = string2[i]
        i <- i + 1
    END WHILE

    RETURN difference between string1[i] and string2[i]
END FUNCTION

FUNCTION my_strdup(string)
    length <- my_strlen(string)
    allocate memory
    IF allocation fails
        RETURN NULL
    END IF

    copy string
    RETURN duplicated string
END FUNCTION

FUNCTION my_strjoin(string1, string2)
    length1 <- my_strlen(string1)
    length2 <- my_strlen(string2)
    allocate memory

    IF allocation fails
        RETURN NULL
    END IF

    copy string1
    add "/"
    copy string2
    add '\0'
    RETURN result
END FUNCTION

FUNCTION free_file_info(file)
    IF file = NULL
        RETURN
    END IF

    free file.name
    free file.path
    free file
END FUNCTION

FUNCTION compare_files(file1, file2, opt_t)
    IF opt_t = true
        IF file1.modification_time.seconds
           ≠ file2.modification_time.seconds
            RETURN result for newest first
        END IF

        IF file1.modification_time.nanoseconds
           ≠ file2.modification_time.nanoseconds
            RETURN result for newest first
        END IF

    END IF
    RETURN my_strcmp(file1.name, file2.name)
END FUNCTION

FUNCTION sort_files(array, count, opt_t)
    FOR i FROM 0 TO count - 2
        FOR j FROM 0 TO count - i - 2
            IF compare_files(
                array[j],
                array[j + 1],
                opt_t
            ) > 0
                temp <- array[j]
                array[j] <- array[j + 1]
                array[j + 1] <- temp
            END IF

        END FOR

    END FOR
END FUNCTION

FUNCTION print_error(name)
    print error:
    "my_ls: cannot access 'name': No such file or directory"
END FUNCTION

FUNCTION list_directory(path, display_name, options, show_header)
    directory <- opendir(path)
    IF directory = NULL
        print_error(display_name)
        RETURN
    END IF

    capacity <- 10
    count <- 0
    allocate array files
    FOR EACH entry IN directory
        IF options.opt_a = false
           AND entry.name starts with "."
            CONTINUE
        END IF

        allocate file
        file.name <- my_strdup(entry.name)
        file.path <- my_strjoin(path, entry.name)
        IF lstat(file.path) succeeds
            get modification_time
            determine if file is a directory
        ELSE
            modification_time <- 0
            is_directory <- false
        END IF

        file.exists <- true
        IF count >= capacity
            capacity <- capacity × 2
            allocate new array
            copy old array into new array
            free old array
            array <- new array
        END IF

        files[count] <- file
        count <- count + 1
    END FOR

    closedir(directory)
    sort_files(
        files,
        count,
        options.opt_t
    )
    IF show_header = true
        print display_name + ":"
    END IF

    FOR i FROM 0 TO count - 1
        print files[i].name
        free_file_info(files[i])
    END FOR

    free files
END FUNCTION


MAIN
    options.opt_a <- false
    options.opt_t <- false
    op_start <- 1
    FOR i FROM 1 TO argc - 1
        IF argv[i] starts with "-"
           AND argv[i] is not "-"
            IF argv[i] = "--"
                op_start <- i + 1
                BREAK
            END IF

            valid_flag <- true
            FOR EACH character IN argv[i] after "-"
                IF character = "a"
                    options.opt_a <- true
                ELSE IF character = "t"
                    options.opt_t <- true
                ELSE
                    valid_flag <- false
                    BREAK
                END IF

            END FOR
            IF valid_flag = true
                op_start <- i + 1
            ELSE
                op_start <- i
                BREAK
            END IF

        ELSE
            BREAK
        END IF

    END FOR

    num_ops <- argc - op_start
    IF num_ops = 0
        list_directory(
            ".",
            ".",
            options,
            false
        )
        RETURN
    END IF

    allocate array non_dirs
    allocate array dirs
    nd_count <- 0
    d_count <- 0
    FOR i FROM op_start TO argc - 1
        op <- argv[i]
        allocate file
        file.name <- my_strdup(op)
        file.path <- my_strdup(op)
        IF lstat(op) fails
            print_error(op)
            free_file_info(file)
            CONTINUE
        END IF

        get modification_time
        file.exists <- true
        IF op is a directory
            file.is_directory <- true
            dirs[d_count] <- file
            d_count <- d_count + 1
        ELSE
            file.is_directory <- false
            non_dirs[nd_count] <- file
            nd_count <- nd_count + 1
        END IF
    END FOR

    sort_files(
        non_dirs,
        nd_count,
        options.opt_t
    )
    sort_files(
        dirs,
        d_count,
        options.opt_t
    )
    FOR i FROM 0 TO nd_count - 1
        print non_dirs[i].name
        free_file_info(non_dirs[i])
    END FOR

    FOR i FROM 0 TO d_count - 1
        IF nd_count > 0
           OR d_count > 1
            IF i > 0
               OR nd_count > 0
                print empty line
            END IF

            list_directory(
                dirs[i].path,
                dirs[i].name,
                options,
                true
            )
        ELSE
            list_directory(
                dirs[i].path,
                dirs[i].name,
                options,
                false
            )
        END IF

        free_file_info(dirs[i])
    END FOR

    free non_dirs
    free dirs
END MAIN