#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define WORD    "[a-zA-Z0-9]+(('|-)[a-zA-Z0-9]+)*"
#define OPTIONS "ht:f:ms"
#define BLOCK   512

//help function print
void synopsis(void) {
    printf("SYNOPSIS\n");
    printf("  A word filtering program for the GPRSC.\n");
    printf("  Filters out and reports bad words parsed from stdin.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./banhammer [-hsm] [-t size] [-f size]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h           Program usage and help.\n");
    printf("  -s           Print program statistics.\n");
    printf("  -m           Enable move-to-front rule.\n");
    printf("  -t size      Specify hash table size (default: 10000).\n");
    printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
}

int main(int argc, char **argv) {
    int opt = 0;
    int table_Size = 10000;
    int bloom_Size = 1048576;
    //flags
    bool mtf = false;
    bool statistic = false;
    bool synop = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': synop = true; break;
        case 't':
            table_Size = (atoi(optarg));
            if (atoi(optarg) == 0) {
                printf("./banhammer: option requires an argument -- 'n'\n");
                return 0;
            }
            break;
        case 'f':
            bloom_Size = (atoi(optarg));
            if (atoi(optarg) == 0) {
                printf("./banhammer: option requires an argument -- 'n'\n");
                return 0;
            }
            break;
        case 'm': mtf = true; break;
        case 's': statistic = true; break;
        default: synop = true; break;
        }
    }
    if (synop == true) {
        synopsis();
        return 0;
    }
    //file in - file out
    FILE *bad;
    FILE *new;
    bad = fopen("badspeak.txt", "r");
    new = fopen("newspeak.txt", "r");

    //creates the hash table and bloom filter
    HashTable *ht = ht_create(table_Size, mtf);
    BloomFilter *bf = bf_create(bloom_Size);

    //fills up ht and bf for bad words / thought crimes
    char buff_Bad[BLOCK];
    while (1) {
        if (feof(bad)) { //if end of file break
            break;
        }
        fscanf(bad, "%s\n", buff_Bad);
        bf_insert(bf, buff_Bad);
        char null[] = "";
        ht_insert(ht, buff_Bad, null);
    }

    //fills up ht and bf for old words and their new counterparts
    char buff_New[BLOCK];
    char buff_Old[BLOCK];
    while (1) {
        if (feof(new)) { //if end of file break
            break;
        }
        fscanf(new, "%s %s\n", buff_Old, buff_New);
        bf_insert(bf, buff_Old);
        ht_insert(ht, buff_Old, buff_New);
    }

    //creates linked lists for tracking what is encountered in stdin
    LinkedList *bad_ll = ll_create(mtf);
    LinkedList *old_ll = ll_create(mtf);

    //regex, got in pdf
    regex_t re;
    regcomp(&re, WORD, REG_EXTENDED);
    char *word = NULL;
    //flags for what is printed
    bool thought = false;
    bool badspeak = false;
    //checks bf then ht and puts in correct ll if true
    while ((word = next_word(stdin, &re)) != NULL) {
        if (bf_probe(bf, word)) {
            Node *look = ht_lookup(ht, word);
            if (look != NULL) {
                if (0 == strcmp(look->newspeak, "")) {
                    badspeak = true;
                    ll_insert(bad_ll, look->oldspeak, look->newspeak);
                } else if (0 != strcmp(look->newspeak, "")) {
                    thought = true;
                    ll_insert(old_ll, look->oldspeak, look->newspeak);
                }
            }
        }
    }

    //stats if thats set to true
    if (statistic) {
        printf("Seeks: %lu\n", seeks);
        printf("Average seeks: %.6f\n", (float) links / (float) seeks);
        printf("Hash table load: %.6f%c\n", 100 * (((float) ht_count(ht)) / ((float) ht_size(ht))),
            '%');
        printf("Bloom filter load: %.6f%c\n",
            100 * (((float) bf_count(bf)) / ((float) bf_size(bf))), '%');
    } else { // else one of the three are printed in stdout
        printf("Dear beloved citizen of the GPRSC,\n\n");
        if (thought && badspeak) {
            printf("We have some good news, and we have some bad news.\n"
                   "The good news is that there is bad news. The bad news is that you will\n"
                   "be sent to joycamp and subjected to a week-long destitute existence.\n"
                   "This is the penalty for using degenerate words, as well as using\n"
                   "oldspeak in place of newspeak. We hope you can correct your behavior.\n\n"
                   "Your transgressions, followed by the words you must think on:\n\n");
        } else if (thought && !badspeak) {
            printf("You have been caught using degenerate words that may cause\n"
                   "distress among the moral and upstanding citizens of the GPSRC.\n"
                   "As such, you will be sent to joycamp. It is there where you will\n"
                   "sit and reflect on the consequences of your choice in language.\n\n"
                   "Your transgressions:\n\n");
        } else if (!thought && badspeak) {
            printf("We recognize your efforts in conforming to the language standards\n"
                   "of the GPSRC. Alas, you have been caught uttering questionable words\n"
                   "and thinking unpleasant thoughts. You must correct your wrongspeak\n"
                   "and badthink at once. Failure to do so will result in your deliverance\n"
                   "to joycamp.\n\n"
                   "Words that you must think on:\n\n");
        }
        //prints out the words that are bad
        ll_print(bad_ll);
        ll_print(old_ll);
    }
    //frees up the things used
    ll_delete(&bad_ll);
    ll_delete(&old_ll);
    ht_delete(&ht);
    bf_delete(&bf);
    clear_words();
    regfree(&re);
    return 0;
}
