#include <stdio.h>

#define LOWER_UPPERCASE_DIFF 32

#define HELP "help"

#define SEEK "seek"
#define CHANGE "change"

/* different params are distinguished by their Ns digit. 
 * e.g. SEEK_* params are units digit params;
 * CHANGE_* params are tens digit params                */
typedef enum {
    UNDEFINED,

    /* seek flags */
    SEEK_GROUP = 1,
    SEEK_DIGITS = SEEK_GROUP,
    SEEK_LETTERS,
    SEEK_SPACES,
    SEEK_CAPITALS,
    SEEK_LOWERCASE,
    SEEK_PUNCTUATION,

    /* change flags */
    CHANGE_GROUP = 10,
    CHANGE_UPPER = CHANGE_GROUP,
    CHANGE_LOWER,

    /* gibberish flags */
    GIBBERISH_GROUP = 100,
    GIBBERISH = GIBBERISH_GROUP
} param_t;

typedef int (*seek_func_t)(int);
typedef void (*change_func_t)(int *);

int strcmp_z(const char *str1, const char *str2) {
    if (!str1) { return 0; }

    for (int i = 0; str1[i]; i++) {
        if (str1[i] != str2[i]) {
            return 0; /* not equal */
        }
    }

    return 1;
}

void help_docs() {
    puts("FILT - a program-filter.\n"
            "Parameters\n"
            "seek - SEEK for a specified characters.\n"
            "\tdigits\n"
            "\tletters\n"
            "\tspaces\n"
            "\tcapital-letters\n"
            "\tlowercase-letters\n"
            "\tpunctuation\n\n"
            "change - CHANGE the format.\n"
            "\tletters-lower - formats any capital letters to lower.\n"
            "\tletters-upper - vice versa."
            " Formats any lowercase letters to uppercase.");
}

/* 'seek param' boolean functions */
int seek_digits(int ch) {
    return (ch >= '0') && (ch <= '9');
}
int seek_letters(int ch) {
    return ((ch >= 'a') && (ch <= 'z')) || 
        ((ch >= 'A') && (ch <= 'Z'));
}
int seek_spaces(int ch) {
    return ch <= 32;
}
int seek_uppercase(int ch) {
    return (ch >= 'A') && (ch <= 'Z');
}
int seek_lowercase(int ch) {
    return (ch >= 'a') && (ch <= 'z');
}
int seek_punctuation(int ch) {
    return ((ch >= '!') && (ch <= '/')) ||
        ((ch >= ':') && (ch <= '@')) ||
        ((ch >= '[') && (ch <= '`')) ||
        ((ch >= '{') && (ch <= '~'));
}

/* 'change param' functions 
 * They'll be changing ch according to condition. */
void to_uppercase(int *ch) {
    if ((*ch >= 'a') && (*ch <= 'z')) {
        *ch -= LOWER_UPPERCASE_DIFF;
    }
}
void to_lowercase(int *ch) {
    if ((*ch >= 'A') && (*ch <= 'Z')) {
        *ch += LOWER_UPPERCASE_DIFF;
    }
}

/* 2 level 'checkers' */
param_t check_seek_params(char *arg2) {
    if (strcmp_z(arg2, "digits")) {
        return SEEK_DIGITS;
    }
    if (strcmp_z(arg2, "letters")) {
        return SEEK_LETTERS;
    }
    if (strcmp_z(arg2, "spaces")) {
        return SEEK_SPACES;
    }
    if (strcmp_z(arg2, "capital-letters")) {
        return SEEK_CAPITALS;
    }
    if (strcmp_z(arg2, "lowercase-letters")) {
        return SEEK_LOWERCASE;
    }
    if (strcmp_z(arg2, "punctuation")) {
        return SEEK_PUNCTUATION;
    }
    return UNDEFINED;
}

param_t check_change_params(char *arg2) {
    if (strcmp_z(arg2, "letters-upper")) {
        return CHANGE_UPPER;
    }
    if (strcmp_z(arg2, "letters-lower")) {
        return CHANGE_LOWER;
    }
    return UNDEFINED;
}

/* 1 level 'checker' */
param_t check_params(char *arg1, char *arg2) { 
    param_t result = UNDEFINED;
    if (strcmp_z(arg1, SEEK)) {
        result = check_seek_params(arg2);
    }

    if (strcmp_z(arg1, CHANGE)) {
        result = check_change_params(arg2);
    }
    return result;
}

seek_func_t define_seek_func(param_t state) {
    switch (state) {
        case SEEK_DIGITS:
            return &seek_digits;
            break;
        case SEEK_LETTERS:
            return &seek_letters;
            break;
        case SEEK_SPACES:
            return &seek_spaces;
            break;
        case SEEK_CAPITALS:
            return &seek_uppercase;
            break;
        case SEEK_LOWERCASE:
            return &seek_lowercase;
            break;
        case SEEK_PUNCTUATION:
            return &seek_punctuation;
            break;
        default:
            return NULL;
            break;
    }
}

change_func_t define_change_func(param_t state) {
    switch (state) {
        case CHANGE_UPPER:
            return &to_uppercase;
            break;
        case CHANGE_LOWER:
            return &to_lowercase;
            break;
        default:
            return NULL;
            break;
    }
}

int main(int argc, char *argv[]) {
    if (strcmp_z(argv[1], HELP)) {
        help_docs();
        return 0;
    }
    if (argc < 3) {
        fputs("Specify the arguments.\n\n" 
                "Type './filt help' for details.\n",
                stderr);
        return 1;
    }


    param_t state = check_params(argv[1], argv[2]);
    if (state == UNDEFINED) {
        fprintf(stderr, "[ERROR] Could not define the parameter '%s'\n",
                argv[1]);
        return 2;
    }


    if (state >= SEEK_GROUP && state < CHANGE_GROUP) {
        int count = 0;
        int (*seek_func)(int) = define_seek_func(state);
        if (!seek_func) {
            fputs("[ERROR] Defining condition failed.\n", stderr);
        }

        int ch;
        while ((ch = getchar()) != EOF) {
            if ((*seek_func)(ch)) {
                putchar(ch);
                count++;
            }
        }
        printf("\nFound characters: %d\n", count);
    }

    if (state >= CHANGE_GROUP && state < GIBBERISH_GROUP) {
        void (*change_func)(int *) = define_change_func(state);
        if (!change_func) {
            fputs("[ERROR] Defining condition failed.\n", stderr);
        }

        int ch;
        while ((ch = getchar()) != EOF) {
            (*change_func)(&ch);
            putchar(ch);
        }
    }

    return 0;
}
