#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int use_symbol = 0; /* start false */
int use_long = 0;   /* start false */
char *sym = "a";    /* placeholder */
double amount = 0;  /* placeholder */
double exchange_rate = 0;
double exchange_extra = 0;
double final_amount = 0;

void print_final_amount() {
    if (exchange_extra == 0.00)
        exchange_extra = 1;
    final_amount = amount * exchange_rate / exchange_extra;

    if (use_symbol && use_long) {
        printf("%.2f becomes %.2f%s\n", amount, final_amount, sym);
    } else if (use_symbol && !use_long) {
        printf("%.2f%s\n", final_amount, sym);
    } else if (!use_symbol && use_long) {
        printf("%.2f becomes %.2f\n", amount, final_amount);
    } else {
        printf("%.2f\n", final_amount);
    }
}

void print_help() {
    printf("Usage: moneychange [OPTIONS]... AMOUNT EXCHANGE [EXCHANGE]\n");
    printf("Convert from one currency to another (by default convert the AMOUNT into USD).\n");
    printf("\nOptions:\n");
    printf("        -l, --long\t\tuse long format output.\n");
    printf("        -s, --symbol SYMBOL\tadd three letter currency code to output.\n");
    printf("\nExit status:\n");
    printf("        0\tif OK,\n");
    printf("        1\tif problem encountered.\n");
    printf("\nmoneychange by joshua macpherson\n\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Try 'moneychange --help' for more information.\n");
        return EXIT_FAILURE;
    }

    if (argc > 7) {
        printf("Try 'moneychange --help' for more information.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "--help") == 0) {
        print_help();
        return EXIT_FAILURE;
    }

    int i; /* first arg value */
    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-') { /* if first value is not an option, skip looking for options */
            break;
        }
        /* OPTIONS */
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--long") == 0) {
            if (use_long) {
                printf("moneychange: cannot use -l option twice");
                return EXIT_FAILURE;
            }
            use_long = 1;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--symbol") == 0) {
            if (use_symbol) {
                printf("moneychange: cannot use -s option twice");
                return EXIT_FAILURE;
            }
            use_symbol = 1;

            if (i + 1 >= argc) {
                printf("Try 'moneychange --help' for more information.\n");
                return EXIT_FAILURE;
            }
            i++; /* move to symbol */
            if (strlen(argv[i]) == 3) {
                sym = argv[i];
            } else {
                printf("moneychange: invalid currency symbol\n");
                printf("Try 'moneychange --help' for more information.\n");
                return EXIT_FAILURE;
            }
        }
    }
    /* AFTER OPTIONS */

    /* amount */
    if (i >= argc || atof(argv[i]) == 0.0) {
        printf("moneychange: amount expected\nTry 'moneychange --help' for more information.\n");
        return EXIT_FAILURE;
    }
    amount = atof(argv[i++]);

    if (i >= argc || atof(argv[i]) == 0.0) {
        printf("moneychange: exchange rate expected\nTry 'moneychange --help' for more information.\n");
        return EXIT_FAILURE;
    }
    exchange_rate = atof(argv[i++]);

    if (i < argc) {
        if (atof(argv[i]) == 0.0) {
            printf("moneychange: invalid additional exchange rate\nTry 'moneychange --help' for more information.\n");
            return EXIT_FAILURE;
        }
        exchange_extra = atof(argv[i]);
    }
    print_final_amount();
    return EXIT_SUCCESS;
}
