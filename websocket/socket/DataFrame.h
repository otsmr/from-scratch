/*
 * Copyright (c) 2022, Tobias <git@tsmr.eu>
 * 
 */

#pragma once

#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>

#define MAX_PACKET_SIZE 4096

#ifdef __linux__
typedef u_int8_t uint8_t;
#endif

// #include "WebSocket.h"

class DataFrame {
public:

    DataFrame ();
    ~DataFrame ();

    enum Bool {
        NotSet = 0,
        Set = 1
    };

    Bool fin;
    Bool mask;

    enum RSV {
        RSV1 = 0b1,
        RSV2 = 0b10,
        RSV3 = 0b100
    };
    uint8_t rsv;
    enum Opcode {
        ContinuationFrame = 0x0,
        TextFrame = 0x1,
        BinaryFrame = 0x2,
        ConectionClose = 0x8,
        Ping = 0x9,
        Pong = 0xA
    };
    Opcode opcode;

    // "Extension data" + the length of the "Application data"
    // The length of the "Extension data" may be
    // zero, in which case the payload length is the length of the
    // "Application data"
    uint64_t payload_len_bytes = 0; // max 64 bits in length
    int payload_full() { return ((payload_len_bytes - application_data.size()) == 0) ? 1 : 0; }
    
    uint8_t masking_key[4];

    std::vector<uint8_t> extensions_data;
    std::vector<uint8_t> application_data;

    std::string get_utf8_string() {
        std::string s(application_data.begin(), application_data.end());
        return s;
    }

    size_t add_payload_data (uint8_t buffer[MAX_PACKET_SIZE], int offset, int buffer_size);
    int parse_raw_frame (uint8_t buffer[MAX_PACKET_SIZE], int buffer_size);
    
};