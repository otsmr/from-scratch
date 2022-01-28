/*
 * Copyright (c) 2022, Tobias <git@tsmr.eu>
 * 
 */

#pragma once

#include <string.h>
#include <stdlib.h>
#include <cmath>

#ifdef __linux__
typedef u_int8_t uint8_t;
#endif

void base64_decode (char *input, uint8_t **output, size_t *length);
void base64_encode (uint8_t *input, char **output, size_t length);