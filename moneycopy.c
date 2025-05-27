#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STD_CURR "USD"

int use_symbol = 0;
int use_long = 0;
char *sym = STD_CURR;
double amount = 0;
double exchange_rate = 0;
double exchange_extra = 1;
double final_amount = 0;

void print_final_amount() {
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

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Try 'moneychange --help' for more information.\n");
        return EXIT_FAILURE;
    }

    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: moneychange [OPTIONS]... AMOUNT EXCHANGE [EXTRA]\n");
            printf("Convert from one currency to another (by default into USD).\n\n");
            printf("Options:\n");
            printf("  -l, --long            Use long format output.\n");
            printf("  -s, --symbol SYMBOL   Add 3-letter currency code to output.\n");
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--long") == 0) {
            use_long = 1;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--symbol") == 0) {
            use_symbol = 1;
            if (++i >= argc || strlen(argv[i]) != 3) {
                printf("moneychange: expected 3 letter symbol after -s or --symbol\n");
                return EXIT_FAILURE;
            }
            sym = argv[i];
        } else if (argv[i][0] == '-') {
            printf("moneychange: unrecognized option '%s'\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    int values_found = 0;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if ((strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--symbol") == 0) && i + 1 < argc)
                i++;
            continue; 
        }

        double val = atof(argv[i]);
        if (val == 0.0 && strcmp(argv[i], "0") != 0) continue;

        if (values_found == 0)
            amount = val;
        else if (values_found == 1)
            exchange_rate = val;
        else if (values_found == 2)
            exchange_extra = val;

        values_found++;
    }

    return EXIT_SUCCESS;
}
