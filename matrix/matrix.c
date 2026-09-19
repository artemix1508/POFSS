#include <stdio.h> // Standard things e.g. printf()
#include <stdlib.h> // For rand() & srand()
#include <time.h> // For time()
#include <unistd.h> // For nanosleep() and timespec
#include <string.h> // For strlen()
#include <stddef.h> // For size_t
#include <signal.h>

/*
 * POFSS matrix - distributed under the BSD 3-Clause license.
 *
 * Created by https://github.com/ilikeminecraft22
 */

#define MS_TO_NS(x) (x*1000000) // Conversion from milliseonds to nanoseconds.

struct timespec sleep_time = {
    .tv_sec = 0,
    .tv_nsec = MS_TO_NS(10) // 100 millisecond delay before the next character is printed.
};

void cleanup(int sig) { // Cleanup routine
    printf("\033[0m\n");
    fflush(stdout);
    exit(0);
}

int main(void) {

    signal(SIGINT, cleanup); // Make sure the program turns the terminal colour back to the default one when doing ^C.

    srand(time(NULL)); // Generate the pseudo-random algorithm's seed using the current time since 01/01/1970.

    printf("\x1B[32;40m"); // Set the colour to green for that "matrix" effect.

    const char *available_characters = "0123456789ABCDEF"; // Available character list to select from

    const int _len_available_characters
        = strlen(available_characters); // Get the available_characters length.

    size_t loop_counter = 0;

    while(1) {
        if(loop_counter % 64 == 0) { // Print a newline every 64 characters.
            printf("\n");
        }
        /* Print a number from 0-9 */
        printf(
            "%c", // Use the character type - obviously.
            available_characters[rand() % _len_available_characters] // Print pseudo-random number capped at _len_available_characters.
        );
        fflush(stdout); // Making sure it prints the character immediately

        /* Wait some time until the next number to stop wasting performance and make it good-looking.
         *
         * Not using sleep() here, since it only regocnizes seconds (no decimals), I found out the hard way.
         */
        nanosleep(
            &sleep_time,
            NULL
        );

        loop_counter++; // Increase the loop counter so it properly puts a newline.
    }

    return 0;
}
