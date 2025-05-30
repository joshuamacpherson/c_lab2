/*
    Name: Joshua MacPherson
    Student No.: 041166405
    Section: CST8234 311
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

int main(int argc, char *argv[]) {
    int use_symbol        = FALSE;
    int use_long          = FALSE;     
    char *sym             = "a";  
    double amount         = 0;    
    double exchange_rate  = 0;
    double exchange_extra = 0;
    int i                 = 1;
    double final_amount   = 0;

    /* check for no args */
    if (argc == 1) {
        printf("Try 'moneychange --help' for more information.\n");
        return EXIT_FAILURE;
    }

    /* if first option is help, print help */
    if (strcmp(argv[1], "--help") == 0) {
        printf("Usage: moneychange [OPTIONS]... AMOUNT EXCHANGE [EXCHANGE]\n");
        printf("Convert from one currency to another (by default convert the AMOUNT into USD).\n");
        printf("\nOptions:\n");
        printf("        -l, --long\t\tuse long format output.\n");
        printf("        -s, --symbol SYMBOL\tadd three letter currency code to output.\n");
        printf("\nExit status:\n");
        printf("        0\tif OK,\n");
        printf("        1\tif problem encountered.\n");
        printf("\nmoneychange by joshua macpherson\n\n");
        return EXIT_SUCCESS;
    }

    /* parsing options first */
    for (; i < argc; i++) {

        /* if first value is not an option, skip looking for options */
        if (argv[i][0] != '-') { 
            break;
        }

        /* check for -l, then -s, then for 3 char symbol for -s, then break once no more options are found */
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--long") == 0) {
            if (use_long) {
                printf("moneychange: cannot use -l option twice");
                return EXIT_FAILURE;
            }
            use_long = TRUE;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--symbol") == 0) {
            if (use_symbol) {
                printf("moneychange: cannot use -s option twice");
                return EXIT_FAILURE;
            }
            use_symbol = TRUE;

            if (i + 1 >= argc) {
                printf("Try 'moneychange --help' for more information.\n");
                return EXIT_FAILURE;
            }
            i++; /* move to symbol index to parse, error if unable */
            if (strlen(argv[i]) == 3) {
                sym = argv[i];
            } else {
                printf("moneychange: invalid currency symbol\nTry 'moneychange --help' for more information.\n");
                return EXIT_FAILURE;
            }
        }
    }

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
        exchange_extra = atof(argv[i++]);
    }

    if (argc > i) {
        printf("Try 'moneychange --help' for more information.\n");
        return EXIT_FAILURE;
    }

    if (exchange_extra == 0.00)  exchange_extra = 1;
    final_amount = 0; final_amount = amount * exchange_rate / exchange_extra;

    if (use_symbol && use_long) {
        printf("%.2f becomes %.2f%s\n", amount, final_amount, sym);
    } else if (use_symbol && !use_long) {
        printf("%.2f%s\n", final_amount, sym);
    } else if (!use_symbol && use_long) {
        printf("%.2f becomes %.2f\n", amount, final_amount);
    } else {
        printf("%.2f\n", final_amount);
    }
    
    return EXIT_SUCCESS;
}
