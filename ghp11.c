#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // This gets me sized types, such as uint32_t

/*
 * The 32 bit data we'll evaluate is broken into five fields as outlined in the
 * figure below.  The top row of numbers identifies the high and low bits in
 * the fields defined below.  The middle row identifies the names of the
 * fields.  The bottom row of numbers identifies how long each bit field is.
 *
 *  31   29 28  26 25      12   11    10    0
 * +-------+------+----------+-------+-------+
 * | Color | Item | Sequence | Taxed | Count |
 * +-------+------+----------+-------+-------+
 *  3 bits  3 bits  14 bits    1 bit  11 bits
 *
 * Fields...
 * - Color: 3 bit values from 0-7.
 *     0: undefined
 *     1-7 are the "ROYGBIV" colors of the rainbow
 * - Item: This 3 bit number should be printed as an unsigned decimal value
 * - Sequence: This 14 bit value should be printed in binary
 * - Taxed: a Boolean field where 0 = "False" and 1 = "True"
 * - Count: This count should be printed as an unsigned decimal value
 */

/*
 * Bit field positions
 */
const unsigned int COLOR_BIT_LOW = 29;
const unsigned int COLOR_BIT_HIGH = 31;

const unsigned int ITEM_BIT_LOW = 26;
const unsigned int ITEM_BIT_HIGH = 28;

const unsigned int SEQUENCE_BIT_LOW = 12;
const unsigned int SEQUENCE_BIT_HIGH = 25;

const unsigned int TAXED_BIT_LOW = 11;
const unsigned int TAXED_BIT_HIGH = 11;

const unsigned int COUNT_BIT_LOW = 0;
const unsigned int COUNT_BIT_HIGH = 10;

/*
 * Bit field lengths calculated from the above positions
 */
const unsigned int COLOR_BIT_LENGTH = COLOR_BIT_HIGH - COLOR_BIT_LOW + 1;
const unsigned int ITEM_BIT_LENGTH = ITEM_BIT_HIGH - ITEM_BIT_LOW + 1;
const unsigned int SEQUENCE_BIT_LENGTH = SEQUENCE_BIT_HIGH - SEQUENCE_BIT_LOW + 1;
const unsigned int TAXED_BIT_LENGTH = TAXED_BIT_HIGH - TAXED_BIT_LOW + 1;
const unsigned int COUNT_BIT_LENGTH = COUNT_BIT_HIGH - COUNT_BIT_LOW + 1;

/****************************************************************
 ****************************************************************
 * Bitmask definitions... these are junk... all in hex!
 *
 * Replace the inline hex values below with superb bitmasks that utilize the
 * various constants defined above.  This is the ONLY code you should modify.
 ****************************************************************
 ****************************************************************/

const uint32_t MASK_COLOR = ~(~0U<<3)<<29;
const uint32_t MASK_ITEM = ~(~0U<<3)<<26;
const uint32_t MASK_SEQUENCE = ~(~0U<<14)<<12;
const uint32_t MASK_TAXED = 1<<11;
const uint32_t MASK_COUNT = ~(~0U<<11);


void print_color(uint32_t bp);
void print_item(uint32_t bp);
void print_sequence(uint32_t bp);
void print_taxed(uint32_t bp);
void print_count(uint32_t bp);


int main(int argc, char *argv[]) {

    uint32_t bit_patterns[] = {
        0x35df9869,
        0xb761dcff,
        0xff81f29,
        0xbc23d7ab,
        0x769f29e3,
        0x5bee62c2,
        0x91ea231b,
        0x1cc3a82d,
        0x8231f92e,
        0xbaf6579f,
        0xda7fb665,
        0x6b1d57b7,
        0x975d30a3,
        0xd21e095d,
        0xb5c82858
    };
    const int SIZE = sizeof(bit_patterns) / sizeof(bit_patterns[0]);


    for(int i = 0; i < SIZE; i++) {
        uint32_t bp = bit_patterns[i];

        printf("Pattern %d %x: ", i, bp);
        print_color(bp);
        printf(", ");
        print_item(bp);
        printf(", ");
        print_sequence(bp);
        printf(", ");
        print_taxed(bp);
        printf(", ");
        print_count(bp);
        printf("\n");
    }


    return EXIT_SUCCESS;
}


void print_color(uint32_t bp) {
    const char *colors[] = {
        "undefined",
        "Red",
        "Orange",
        "Yellow",
        "Green",
        "Blue",
        "Indigo",
        "Violet"
    };

    printf("Color = %s", colors[(bp & MASK_COLOR) >> COLOR_BIT_LOW]);

    return;
}



void print_item(uint32_t bp) {
    printf("Item = %d", (bp & MASK_ITEM) >> ITEM_BIT_LOW);

    return;
}



void print_sequence(uint32_t bp) {
    printf("Sequence = ");

    int i = SEQUENCE_BIT_HIGH;
    do {
        printf("%d", bp & (1 << i) ? 1 : 0);
        i--;
    } while(i >= SEQUENCE_BIT_LOW);

    return;
}



void print_taxed(uint32_t bp) {
    printf("Taxed = %s", (bp & MASK_TAXED) ? "True" : "False");

    return;
}



void print_count(uint32_t bp) {
    printf("Count = %d", (bp & MASK_COUNT) >> COUNT_BIT_LOW);

    return;
}
