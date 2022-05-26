////////////////////////////////////////////////////////////////////////
// COMP1521 21t2 -- Assignment 2 -- shuck, A Simple Shell
// <https://www.cse.unsw.edu.au/~cs1521/21T2/assignments/ass2/index.html>
//
// Written by Zhaoyan LIU (z5271698) on 2021/8/6.
//
// 2021-07-12    v1.0    Team COMP1521 <cs1521@cse.unsw.edu.au>
// 2021-07-21    v1.1    Team COMP1521 <cs1521@cse.unsw.edu.au>
//     * Adjust qualifiers and attributes in provided code,
//       to make `dcc -Werror' happy.
//

#include <sys/types.h>

#include <sys/stat.h>
#include <sys/wait.h>

#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// [[ TODO: put any extra `#include's here ]]
#include <spawn.h>
#include <glob.h>

// [[ TODO: put any `#define's here ]]
#define PATH_MAX 10000
#define READ 2
#define WRITE 1
#define NOTHING 0
#define ERROR 1
#define READ_END 0
#define WRITE_END 1

//
// Interactive prompt:
//     The default prompt displayed in `interactive' mode --- when both
//     standard input and standard output are connected to a TTY device.
//
static const char *const INTERACTIVE_PROMPT = "shuck& ";

//
// Default path:
//     If no `$PATH' variable is set in Shuck's environment, we fall
//     back to these directories as the `$PATH'.
//
static const char *const DEFAULT_PATH = "/bin:/usr/bin";

//
// Default history shown:
//     The number of history items shown by default; overridden by the
//     first argument to the `history' builtin command.
//     Remove the `unused' marker once you have implemented history.
//
static const int DEFAULT_HISTORY_SHOWN __attribute__((unused)) = 10;

//
// Input line length:
//     The length of the longest line of input we can read.
//
static const size_t MAX_LINE_CHARS = 1024;

//
// Special characters:
//     Characters that `tokenize' will return as words by themselves.
//
static const char *const SPECIAL_CHARS = "!><|";

//
// Word separators:
//     Characters that `tokenize' will use to delimit words.
//
static const char *const WORD_SEPARATORS = " \t\r\n";

// [[ TODO: put any extra constants here ]]

// Pipe line:
//     Characters that `|' will use to delimit words. 
static const char *const PIPE_CHARS = "|";

// [[ TODO: put any type definitions (i.e., `typedef', `struct', etc.) here ]]


static void execute_command(char **words, char **path, char **environment);
static void do_exit(char **words);
static int is_executable(char *pathname);
static char **tokenize(char *s, char *separators, char *special_chars);
static void free_tokens(char **tokens);

// [[ TODO: put any extra function prototypes here ]]
static void do_execute(char **words, char **path, char **environment);
static void do_cd(char **words);
static void do_history(char **words);
static void write_histroy(char **words);
static void do_exclamation(char **words, char **path, char **environment);
static pid_t output_file(char **words, char **path, char **environment, FILE *fw, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]);
static pid_t input_file(char **words, char **path, char **environment, FILE *fr, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]);
static int check_error(char **words, int length);
static pid_t check_redirection(char **words, char **path, char **environment, int length, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]);
static char *find_path(char *program, char **path);
static void pipe_line(char **s, char **path, char **environment);
static pid_t pipe_read_input(char **words, char **path, char **environment, FILE *fr, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]);
static pid_t pipe_store_output(char **words, char **path, char **environment, FILE *fw, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]);


int main (void)
{
    // Ensure `stdout' is line-buffered for autotesting.
    setlinebuf(stdout);

    // Environment variables are pointed to by `environ', an array of
    // strings terminated by a NULL value -- something like:
    //     { "VAR1=value", "VAR2=value", NULL }
    extern char **environ;

    // Grab the `PATH' environment variable for our path.
    // If it isn't set, use the default path defined above.
    char *pathp;
    if ((pathp = getenv("PATH")) == NULL) {
        pathp = (char *) DEFAULT_PATH;
    }
    char **path = tokenize(pathp, ":", "");

    // Should this shell be interactive?
    bool interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);

    // Main loop: print prompt, read line, execute command
    while (1) {
        // If `stdout' is a terminal (i.e., we're an interactive shell),
        // print a prompt before reading a line of input.
        if (interactive) {
            fputs(INTERACTIVE_PROMPT, stdout);
            fflush(stdout);
        }

        char line[MAX_LINE_CHARS];
        if (fgets(line, MAX_LINE_CHARS, stdin) == NULL) {
            break;
        }
        
        if (strrchr(line, '|') != NULL) {
            // Subset 5
            char **command_words = tokenize(line, (char *) PIPE_CHARS, (char *) "");
            pipe_line(command_words, path, environ);
            free_tokens(command_words);
        } else {
            // Tokenise and execute the input line.
            char **command_words = tokenize(line, (char *) WORD_SEPARATORS, (char *) SPECIAL_CHARS);
            execute_command(command_words, path, environ);
            free_tokens(command_words);
        }       
    }

    free_tokens(path);
    return 0;
}


//
// Execute a command, and wait until it finishes.
//
//  * `words': a NULL-terminated array of words from the input command line
//  * `path': a NULL-terminated array of directories to search in;
//  * `environment': a NULL-terminated array of environment variables.
//
static void execute_command(char **words, char **path, char **environment)
{
    assert(words != NULL);
    assert(path != NULL);
    assert(environment != NULL);

    char *program = words[0];

    if (program == NULL) {
        // nothing to do
        return;
    }
    
    // Find the length of words.
    int len_words = 0;
    int has_redi = NOTHING;
    for (int i = 0; words[i] != NULL; i++) {
        if (strcmp(words[i], "<") == 0) {
            has_redi = READ;
        } else if (strcmp(words[i], ">") == 0) {
            has_redi = WRITE;
        }
        len_words++;
    } 
    
    if (has_redi != NOTHING) {
        // Subset 4: Input/Output Redirection 
        // create a pipe
        int pipe_file_descriptors[2];
        if (pipe(pipe_file_descriptors) == -1) {
            perror("pipe");
            return;
        }

        // create a list of file actions to be carried out on spawned process
        posix_spawn_file_actions_t actions;
        if (posix_spawn_file_actions_init(&actions) != 0) {
            perror("posix_spawn_file_actions_init");
            return;
        }

        pid_t pid = check_redirection(words, path, environment, len_words, actions, pipe_file_descriptors);
        
        if (has_redi == WRITE) {
            program = words[0];
            program = find_path(program, path);
        } else {
            program = words[2];
            program = find_path(program, path);
        }
        if (program != NULL && pid != NOTHING) {
            // wait for spawned processes to finish 
            int exit_status;
            if (waitpid(pid, &exit_status, 0) == -1) {
                perror("waitpid");
                return;
            } 
            printf("%s exit status = %d\n", program, WEXITSTATUS(exit_status));
        }
        // free the list of file actions
        posix_spawn_file_actions_destroy(&actions);

    } else if (strcmp(program, "exit") == 0) {
        do_exit(words);
        // `do_exit' will only return if there was an error.
        return;
    } else if (strcmp(program, "history") == 0) {
        // print histroy
        do_history(words);

    } else if (strcmp(program, "!") == 0) {
        // ! n which prints the nth command and then executes it, 
        // or, if n is not specified, the last command.
        do_exclamation(words, path, environment);
        return;

    } else if (strcmp(program, "cd") == 0) {
        // change the directory
        do_cd(words);

    } else if (strcmp(program, "pwd") == 0) {
        // print working directory.
        char pathname[PATH_MAX];
        if (getcwd(pathname, sizeof pathname) == NULL) {
            fprintf(stderr, "pwd: error when we can't run getcwd\n");
        }
        printf("current directory is '%s'\n", pathname);

    } else {
        // implement subset 1
        do_execute(words, path, environment);
    }

    // implement subset 2
    // Create or write the target file to store history.
    write_histroy(words);
}

// If a '|' appears between two commands, the standard output of the first command should be 
// connected to the standard input of the second command.
static void pipe_line(char **s, char **path, char **environment) {
    int total_s = 0;
    for (int i = 0; s[i] != NULL; i++) {
        total_s++;
    }
    char *program = NULL;
    
    // create a pipe
    int fd1[2]; // Used to store two ends of first pipe
    if (pipe(fd1) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid = NOTHING;

    // create a list of file actions to be carried out on spawned process
    posix_spawn_file_actions_t actions;
    if (posix_spawn_file_actions_init(&actions) != 0) {
        perror("posix_spawn_file_actions_init");
        return;
    }

    for (int i = 0; i < total_s - 1; i++) {
        char **outp = tokenize(s[i], (char *) WORD_SEPARATORS, (char *) SPECIAL_CHARS);
        char **inp = tokenize(s[i+1], (char *) WORD_SEPARATORS, (char *) SPECIAL_CHARS);

        // close read_end and write output into pipe 
        // the standard output of the first command
        int out_l = 0;  // count the length of outp
        int has_redi_out = NOTHING;
        for (int j = 0; outp[j] != NULL; j++) {
            if (strcmp(outp[i], "<") == 0) {
                has_redi_out = READ;
            } else if (strcmp(outp[i], ">") == 0) {
                has_redi_out = WRITE;
            }
            out_l++;
        }
        // execute program
        // write output in text file
        FILE *fw = fopen("store.txt", "w");
        if (has_redi_out != NOTHING) {
            if (has_redi_out == WRITE) {
                fprintf(stderr, "invalid output redirection\n");
                return;
            }
            // READ redirection 
            
        } else {
            pid = pipe_store_output(outp, path, environment, fw, actions, fd1);
        }
        fclose(fw);
        // parent
        // parent read pipe, and put output in stdout   
        
        // Read a string using first pipe
        int has_redi_in = NOTHING;
        int in_l = 0; // count the length of inp    
        for (int j = 0; inp[j] != NULL; j++) {
            if (strcmp(inp[i], "<") == 0) {
                has_redi_in = READ;
            } else if (strcmp(inp[i], ">") == 0) {
                has_redi_in = WRITE;
            }
            in_l++;
        }
        FILE *fr = fopen("store.txt", "r");
        if (has_redi_in != NOTHING) {
            if (has_redi_in == READ) {
                fprintf(stderr, "invalid input redirection\n");
                return;
            }
            // WRITE redi
        } else {
            pid = pipe_read_input(inp, path, environment, fr, actions, fd1);
        }
        program = inp[0];
        program = find_path(program, path);
        fclose(fr);
    } 
    if (program != NULL && pid != NOTHING) {
        // wait for spawned processes to finish 
        int exit_status;
        if (waitpid(pid, &exit_status, 0) == -1) {
            perror("waitpid");
            return;
        } 
        printf("%s exit status = %d\n", program, WEXITSTATUS(exit_status));
    }
    // free the list of file actions
    posix_spawn_file_actions_destroy(&actions);
    write_histroy(s);
}

// Check redirection error
static int check_error(char **words, int length) {
    for (int i = 0; words[i] != NULL; i++) {
        // if > or < appear anywhere elsewhere on the command-line;
        // error message should be printed.
        if (strcmp(words[i], "<") == 0) {
            if (i != 0 || length == 1) {
                fprintf(stderr, "invalid input redirection\n");
                return ERROR;
            }
        } else if (strcmp(words[i], ">") == 0) {
            if (i != length - 2 && i != length - 3) {
                fprintf(stderr, "invalid output redirection\n");
                return ERROR;
            } else if (i == length - 3 && strcmp(words[i+1], ">") != 0) {
                fprintf(stderr, "invalid output redirection\n");
                return ERROR; 
            }
        }

        if ((strcmp(words[i], "history") == 0) || (strcmp(words[i], "pwd") == 0) || \
        (strcmp(words[i], "cd") == 0) || (strcmp(words[i], "exit") == 0) || \
        (strcmp(words[i], "!") == 0)) {
            // if a builtin command is specified with I/O redirection.
            struct stat statbuf;
            if (stat(words[i], &statbuf) != 0) {
                // does the file exist?
                if (i == 0) {
                    // read file not exist, so its command
                    fprintf(stderr, "%s: I/O redirection not permitted for builtin commands\n", words[i]);
                    return ERROR; 
                } else if (strcmp(words[i - 1], ">") == 0) {
                    // we can write and create the file
                } else {
                    fprintf(stderr, "%s: I/O redirection not permitted for builtin commands\n", words[i]);
                    return ERROR; 
                }  
            } else {
                if (S_ISREG(statbuf.st_mode) != 1) {
                    // is not a file
                    fprintf(stderr, "%s: I/O redirection not permitted for builtin commands\n", words[i]);
                    return ERROR; 
                } 
            }
        } 
    }
    return NOTHING;
}

//
// Implement Input/Output Redirection
//
static pid_t check_redirection(char **words, char **path, char **environment, int length, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]) {
    pid_t pid = NOTHING;
    if (check_error(words, length) == ERROR) {
        // check error
        return NOTHING;
    }
    if (strcmp(words[0], "<") == 0) {
        // read input into specified file.
        FILE *fr = fopen(words[1], "r");
        if (fr == NULL) {
            perror(words[1]);
            return NOTHING;
        }
        pid = input_file(words, path, environment, fr, actions, pipe_file_descriptors);
        fclose(fr);
    } else if (strcmp(words[length - 2], ">") == 0) {
        // tell spawned process to close unused read end of pipe
        // without this - spawned process would not receive EOF
        // when read end of the pipe is closed below,
        if (strcmp(words[length - 3], ">") == 0) {
            // append output into specified file.
            FILE *fw = fopen(words[length - 1], "a");
            if (fw == NULL) {
                perror(words[length - 1]);
                return NOTHING;
            }
            pid = output_file(words, path, environment, fw, actions, pipe_file_descriptors);
            fclose(fw);
        } else {
            // write output into specified file.
            FILE *fw = fopen(words[length - 1], "w");
            if (fw == NULL) {
                perror(words[length - 1]);
                return NOTHING;
            }
            pid = output_file(words, path, environment, fw, actions, pipe_file_descriptors);
            fclose(fw);
        }
    }
    return pid;
}

// Find the absolute path can excute
static char *find_path(char *program, char **path) {
    char *file_path = NULL;
    if (strrchr(program, '/') == NULL) {
        char slash[2] = {'/'};
        for (char **p = path; *p != NULL; p++) {
            file_path = malloc(sizeof *file_path *PATH_MAX);
            strncpy (file_path, *p, PATH_MAX);
            strcat(file_path, slash);
            strcat(file_path, program);
            if (is_executable(file_path) == 1) {
                return file_path;
            }
            free(file_path);
        }
    }
    return NULL;
}

static pid_t pipe_store_output(char **words, char **path, char **environment, FILE *fw, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]) { 
    // tell spawned process to close unused read end of pipe without this - 
    // spawned process would not receive EOF when read end of the pipe is closed below,
    if (posix_spawn_file_actions_addclose(&actions, pipe_file_descriptors[READ_END]) != 0) {
        perror("posix_spawn_file_actions_init");
        return NOTHING;
    }

    // tell spawned process to replace file descriptor 1 (stdout)
    // with write end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, pipe_file_descriptors[WRITE_END], 1) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        return NOTHING;
    }
    
    char *program = words[0];
    program = find_path(program, path);

    // execute the program.
    if (is_executable(program)) {
        // If a command contains a '/', you do not need to search for 
        // it in the path directories.
        // spawn words as a separate process
        char *run_argv[PATH_MAX] = {words[0]};
        for (int i = 1; words[i] != NULL; i++) {
            run_argv[i] = words[i];
        }
        pid_t pid;
        if (posix_spawn(&pid, program, &actions, NULL, run_argv, environment) != 0) {
            perror("spawn");
            return NOTHING;
        }
        
        // create a stdio stream from read stdin
        FILE *f = fdopen(pipe_file_descriptors[READ_END], "r");
        if (f == NULL) {
            perror("fdopen");
            return NOTHING;
        }

        // read a line from read-end of pipe
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, f)) != -1) {
            fprintf(fw, "%s", line);
        }
       
        // close read-end of the pipe
        // spawned process will now receive EOF if attempts to read input
        fclose(f);
        free(program);
        return pid;
    } else {
        // program cannot execute
        fprintf(stderr, "%s: command not found\n", program);
    }
    return NOTHING;
}

static pid_t pipe_read_input(char **words, char **path, char **environment, FILE *fr, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]) {
    // tell spawned process to close unused write end of pipe
    // without this - spawned process will not receive EOF
    // when write end of the pipe is closed below,
    // because spawned process also has the write-end open
    // deadlock will result
    if (posix_spawn_file_actions_addclose(&actions, pipe_file_descriptors[WRITE_END]) != 0) {
        perror("posix_spawn_file_actions_init");
        return NOTHING;
    }

    // tell spawned process to replace file descriptor 0 (stdin)
    // with read end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, pipe_file_descriptors[READ_END], 0) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        return NOTHING;
    }

    char *program = words[0];
    program = find_path(program, path);

    // execute the program.
    if (is_executable(program)) {
        // If a command contains a '/', you do not need to search for 
        // it in the path directories.
        // spawn words as a separate process
        char *run_argv[PATH_MAX] = {words[0]};
        for (int i = 1; words[i] != NULL; i++) {
            run_argv[i] = words[i];
        }
        pid_t pid;
        if (posix_spawn(&pid, program, &actions, NULL, run_argv, environment) != 0) {
            perror("spawn");
            return NOTHING;
        }

        // create a stdio stream from write-end of pipe
        FILE *f = fdopen(pipe_file_descriptors[WRITE_END], "w");
        if (f == NULL) {
            perror("fdopen");
            return NOTHING;
        }

        // read a line from fr
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, fr)) != -1) {
            fprintf(f, "%s", line);
        }
        // close write-end of the pipe without this sort will hang waiting for more input
        fclose(f);
        free(program);
        return pid;
    } else {
        // program cannot execute
        fprintf(stderr, "%s: command not found\n", program);
    }
    return NOTHING;
}


// Execute with its standard input connected to the specified file.
static pid_t input_file(char **words, char **path, char **environment, FILE *fr, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]) {
    // tell spawned process to close unused write end of pipe
    // without this - spawned process will not receive EOF
    // when write end of the pipe is closed below,
    // because spawned process also has the write-end open
    // deadlock will result
    if (posix_spawn_file_actions_addclose(&actions, pipe_file_descriptors[WRITE_END]) != 0) {
        perror("posix_spawn_file_actions_init");
        return NOTHING;
    }

    // tell spawned process to replace file descriptor 0 (stdin)
    // with read end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, pipe_file_descriptors[READ_END], 0) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        return NOTHING;
    }

    char *program = words[2];
    program = find_path(program, path);

    // execute the program.
    if (is_executable(program)) {
        // If a command contains a '/', you do not need to search for 
        // it in the path directories.
        // spawn words as a separate process
        char *run_argv[PATH_MAX] = {words[2]};
        FILE *fw = NULL;
        for (int i = 3; words[i] != NULL; i++) {
            if (strcmp(words[i], ">") == 0) {
                if (strcmp(words[i+1], ">") == 0) {
                    // append output into specified file.
                    fw = fopen(words[i+1], "a");
                } else {
                    // write output into specified file.
                    fw = fopen(words[i+1], "w");
                }
                if (fw == NULL) {
                    perror(words[i]);
                    return NOTHING;
                }
                break;
            } else {
                run_argv[i-2] = words[i];
            }
        }
        pid_t pid;
        if (posix_spawn(&pid, program, &actions, NULL, run_argv, environment) != 0) {
            perror("spawn");
            return NOTHING;
        }

        // create a stdio stream from write-end of pipe
        FILE *f = fdopen(pipe_file_descriptors[WRITE_END], "w");
        if (f == NULL) {
            perror("fdopen");
            return NOTHING;
        }

        // read a line from fr
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, fr)) != -1) {
            fprintf(f, "%s", line);
        }
        // close write-end of the pipe without this sort will hang waiting for more input
        fclose(f);

        if (fw != NULL) {
            // close unused write end of pipe
            //close(pipe_file_descriptors[1]);
            // create a stdio stream from read stdin
            f = fdopen(pipe_file_descriptors[READ_END], "r");
            if (f == NULL) {
                perror("fdopen");
                return NOTHING;
            }
            
            // read a line from read-end of pipe
            while ((read = getline(&line, &len, f)) != -1) {
                fprintf(fw, "%s", line);
            }
            // close read-end of the pipe
            // spawned process will now receive EOF if attempts to read input
            fclose(f);
            fclose(fw);
        }
        free(program);
        return pid;
    } else {
        // program cannot execute
        fprintf(stderr, "%s: command not found\n", program);
    }
    return NOTHING;
}


// Execute with its standard output connected to the specified file 
// such that its output is appended / write to the file
static pid_t output_file(char **words, char **path, char **environment, FILE *fw, posix_spawn_file_actions_t actions, int pipe_file_descriptors[2]) { 
    // tell spawned process to close unused read end of pipe without this - 
    // spawned process would not receive EOF when read end of the pipe is closed below,
    if (posix_spawn_file_actions_addclose(&actions, pipe_file_descriptors[READ_END]) != 0) {
        perror("posix_spawn_file_actions_init");
        return NOTHING;
    }

    // tell spawned process to replace file descriptor 1 (stdout)
    // with write end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, pipe_file_descriptors[WRITE_END], 1) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        return NOTHING;
    }
    
    char *program = words[0];
    program = find_path(program, path);

    // execute the program.
    if (is_executable(program)) {
        // If a command contains a '/', you do not need to search for 
        // it in the path directories.
        // spawn words as a separate process
        char *run_argv[PATH_MAX] = {words[0]};
        for (int i = 1; strcmp(words[i], ">") != 0; i++) {
            run_argv[i] = words[i];
        }
        pid_t pid;
        if (posix_spawn(&pid, program, &actions, NULL, run_argv, environment) != 0) {
            perror("spawn");
            return NOTHING;
        }
        
        // create a stdio stream from read stdin
        FILE *f = fdopen(pipe_file_descriptors[READ_END], "r");
        if (f == NULL) {
            perror("fdopen");
            return NOTHING;
        }

        // read a line from read-end of pipe
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, f)) != -1) {
            fprintf(fw, "%s", line);
        }
       
        // close read-end of the pipe
        // spawned process will now receive EOF if attempts to read input
        fclose(f);
        free(program);
        return pid;
    } else {
        // program cannot execute
        fprintf(stderr, "%s: command not found\n", program);
    }
    return NOTHING;
}


//
// Implement the execute shell built-in (execute commands).
//
static void do_execute(char **words, char **path, char **environment)
{
    char *abpath = find_path(words[0], path);
    char *program = words[0];
    if (abpath != NULL) {
        program = abpath;
    }

    // execute the program.
    if (is_executable(program)) {
        // If a command contains a '/', you do not need to search for 
        // it in the path directories.
        // spawn words as a separate process
        char *run_argv[PATH_MAX] = {words[0]};
        int j = 1;
        for (int i = 1; words[i] != NULL; i++) {
            // Subset 3: Filename Expansion
            glob_t matches; // holds pattern expansion
            int result = glob(words[i], GLOB_NOCHECK|GLOB_TILDE, NULL, &matches);
            if (result != 0) {
                // no result
                run_argv[j] = words[i];
                j++;
            } else {
                // put all matched filename in run_argv
                for (int k = 0; k < matches.gl_pathc; k++) {
                    run_argv[j] = matches.gl_pathv[k];
                    j++;
                }
            }  
        }
       
        pid_t pid;
        if (posix_spawn(&pid, program, NULL, NULL, run_argv, environment) != 0) {
            perror("spawn");
            return;
        }
        
        // wait for spawned processes to finish 
        int exit_status;
        
        if (waitpid(pid, &exit_status, 0) == -1) {
            perror("waitpid");
            return;
        }
        printf("%s exit status = %d\n", program, WEXITSTATUS(exit_status));
       
        if (abpath != NULL) {
            free(abpath);
        }
    } else {
        // program cannot execute
        fprintf(stderr, "%s: command not found\n", program);
    }
}

//
// Implement the `cd' shell built-in (change directory).
//
static void do_cd(char **words)
{
    char *program = words[0];
    if (words[1] != NULL) {
        if (chdir(words[1]) != 0) {
            fprintf(stderr, "cd: %s: No such file or directory\n", words[1]);
        }
    } else {
        // If the cd command runs with no argument, it should change directory to the 
        // value specified in the HOME environment variable.
        char *home_name = getenv("HOME");
        if (chdir(home_name) != 0) {
            fprintf(stderr, "cd: %s: No such file or directory\n", program);
        } 
    }
}

//
// Implement the `history' shell built-in.
// which prints the last n commands, or, if n is not specified 10;
static void do_history(char **words)
{
    int n = 10;
    if (words[1] != NULL) {
        n = atoi(words[1]);
        if (n == 0) {
            fprintf(stderr, "history: %s: numeric argument required\n", words[1]);
            return;
        }
        if (words[2] != NULL) {
            fprintf(stderr, "history: too many arguments\n");
            return;
        }
    }
    char *home = getenv("HOME");
    char *his_file = {"/.shuck_history"};
    char home_name[PATH_MAX] = {};
    strcat(home_name, home);
    strcat(home_name, his_file);
	FILE *f;
    if ((f = fopen(home_name, "r")) == NULL) {
        perror(home_name);
        return;
    }
    
    // Extract characters from file and store in character c
    int total_line = 0;
    int c;
    for (c = getc(f); c != EOF; c = getc(f))
        if (c == 10) // Increment count if this character is newline
            total_line++;
    
    int nline = n + 1;    // we find previous "\n" on this line
    int i = 0;
	while (nline > 0 && fseek(f, i, SEEK_END) == 0) {
        // Find nlines from back to front.
		c = fgetc(f);
        if (c == 10) // 10 is \n in ascii encoding
            nline--;
		i--;
    }
    
    if (fseek(f, i, SEEK_END) != 0) {
        // Found the head of file
        fseek(f, 0, SEEK_SET);
        i = 0;
    } else {
        fseek(f, 2, SEEK_CUR);
        i = total_line - n;
    }
    

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, f)) != -1) {
        printf("%d: %s",i, line);
        i++;
    }
    fclose(f);
}

//
// write the history to the file
// 
static void write_histroy(char **words)
{
    char *home = getenv("HOME");
    char *his_file = {"/.shuck_history"};
    char home_name[PATH_MAX] = {};
    strcat(home_name, home);
    strcat(home_name, his_file);
    FILE *f;
    if ((f = fopen(home_name, "a+")) == NULL) {
        perror(home_name);
    } else {
        int i = 0;
        while (words[i] != NULL) {
            fprintf(f, "%s ", words[i]);
            i++;
        }
        fprintf(f, "\n"); 
        fclose(f);
    }
}

//
// To implement a built-in command ! n which prints the nth command and then executes it, 
// or, if n is not specified, the last command.
// 
static void do_exclamation(char **words, char **path, char **environment)
{
    int nline = -1;
    if (words[1] != NULL) {
        nline = atoi(words[1]);
        printf("%d\n", nline);
        if (nline <= 0) {
            // incorrect input number
            fprintf(stderr, "!: %s: numeric argument required\n", words[1]);
            return;
        }
    }
    
    char *home = getenv("HOME");
    char *his_file = {"/.shuck_history"};
    char home_name[PATH_MAX] = {};
    strcat(home_name, home);
    strcat(home_name, his_file);
	FILE *f;
    if ((f = fopen(home_name, "a+")) == NULL) {
        perror(home_name);
        return;
    }
    
    if (nline != -1) {
        // print n th commond
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        int i = 0;
        while ((read = getline(&line, &len, f)) != -1) {
            if (i == nline) {
                printf("%s", line);
                char **token = tokenize(line, (char *) WORD_SEPARATORS, (char *) SPECIAL_CHARS);    
                execute_command(token, path, environment);
                free_tokens(token);
                break;
            }     
            i++;
        }
    } else {
        // print last command
        int c;
        int n = 0; // ignore the last "\n"
        int i = 0;
        while (fseek(f, n, SEEK_END) == 0 && i < 2) {
            // Find last line from back to front.
            c = fgetc(f);
            if (c == 10) {
                // 10 is \n in ascii encoding
                i++;
            }    
            n--;
        }
        if (fseek(f, n, SEEK_END) != 0) {
            // Found the head of file
            fseek(f, 0, SEEK_SET);
        } else {
            fseek(f, 2, SEEK_CUR);
        }   
        char line[MAX_LINE_CHARS];
        if (fgets(line, MAX_LINE_CHARS, f) == NULL) {
            return;
        }
        printf("%s", line);
        char **token = tokenize(line, (char *) WORD_SEPARATORS, (char *) SPECIAL_CHARS);    
        execute_command(token, path, environment);
        free_tokens(token);
    }
    fclose(f);
}


//
// Implement the `exit' shell built-in, which exits the shell.
//
// Synopsis: exit [exit-status]
// Examples:
//     % exit
//     % exit 1
//
static void do_exit(char **words)
{
    assert(words != NULL);
    assert(strcmp(words[0], "exit") == 0);

    int exit_status = 0;

    if (words[1] != NULL && words[2] != NULL) {
        // { "exit", "word", "word", ... }
        fprintf(stderr, "exit: too many arguments\n");

    } else if (words[1] != NULL) {
        // { "exit", something, NULL }
        char *endptr;
        exit_status = (int) strtol(words[1], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "exit: %s: numeric argument required\n", words[1]);
        }
    }

    exit(exit_status);
}


//
// Check whether this process can execute a file.  This function will be
// useful while searching through the list of directories in the path to
// find an executable file.
//
static int is_executable(char *pathname)
{
    struct stat s;
    return
        // does the file exist?
        stat(pathname, &s) == 0 &&
        // is the file a regular file?
        S_ISREG(s.st_mode) &&
        // can we execute it?
        faccessat(AT_FDCWD, pathname, X_OK, AT_EACCESS) == 0;
}


//
// Split a string 's' into pieces by any one of a set of separators.
//
// Returns an array of strings, with the last element being `NULL'.
// The array itself, and the strings, are allocated with `malloc(3)';
// the provided `free_token' function can deallocate this.
//
static char **tokenize(char *s, char *separators, char *special_chars)
{
    size_t n_tokens = 0;

    // Allocate space for tokens.  We don't know how many tokens there
    // are yet --- pessimistically assume that every single character
    // will turn into a token.  (We fix this later.)
    char **tokens = calloc((strlen(s) + 1), sizeof *tokens);
    assert(tokens != NULL);

    while (*s != '\0') {
        // We are pointing at zero or more of any of the separators.
        // Skip all leading instances of the separators.
        s += strspn(s, separators);

        // Trailing separators after the last token mean that, at this
        // point, we are looking at the end of the string, so:
        if (*s == '\0') {
            break;
        }

        // Now, `s' points at one or more characters we want to keep.
        // The number of non-separator characters is the token length.
        size_t length = strcspn(s, separators);
        size_t length_without_specials = strcspn(s, special_chars);
        if (length_without_specials == 0) {
            length_without_specials = 1;
        }
        if (length_without_specials < length) {
            length = length_without_specials;
        }

        // Allocate a copy of the token.
        char *token = strndup(s, length);
        assert(token != NULL);
        s += length;

        // Add this token.
        tokens[n_tokens] = token;
        n_tokens++;
    }

    // Add the final `NULL'.
    tokens[n_tokens] = NULL;

    // Finally, shrink our array back down to the correct size.
    tokens = realloc(tokens, (n_tokens + 1) * sizeof *tokens);
    assert(tokens != NULL);

    return tokens;
}


//
// Free an array of strings as returned by `tokenize'.
//
static void free_tokens(char **tokens)
{
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
