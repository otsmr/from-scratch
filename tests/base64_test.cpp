/*
 * Copyright (c) 2022, Tobias <git@tsmr.eu>
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "base64/base64.h"

void test_base64(char *input, char *expected, int length) {

    char output[20]{};
    uint8_t string_decoded[20]{};
    size_t decoded_length = -1;

    Base64::encode((uint8_t *) input, output, length);

    for (int i = 0; i < strlen(expected); i++)
    {
        if (output[i] != expected[i]) {
            printf("FAILED %s != %s", output, expected);
        }
    }
    
    Base64::decode(output, string_decoded, &decoded_length);

    if (decoded_length != length) {
        printf("FAILED decoded_length (%zu) != length (%d)", decoded_length, length);
    }

    for (int i = 0; i < decoded_length; i++)
    {
        if (string_decoded[i] != input[i]) {
            printf("FAILED %s != %s", string_decoded, input);
        }
    }

}

int main(int argc, char **argv) {

    test_base64((char *) "", (char *) "", 0);
    test_base64((char *) "f", (char *) "Zg==", 1);
    test_base64((char *) "fo", (char *) "Zm8=", 2);
    test_base64((char *) "foo", (char *) "Zm9v", 3);
    test_base64((char *) "foob", (char *) "Zm9vYg==", 4);
    test_base64((char *) "fooba", (char *) "Zm9vYmE=", 5);
    test_base64((char *) "foobar", (char *) "Zm9vYmFy", 6);

}