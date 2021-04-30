#include "buffer.h"

#define NUM_BITS 8

//Function to insert value to the buffer
void buffer_insert(uint8_t *buffer, uint8_t start, uint8_t length, uint64_t value)
{
    uint8_t start_bit, end_bit, data, position;
    int index = start / NUM_BITS;
    position = start % NUM_BITS;
    uint64_t allones = ~0;

    while (length)
    {
        if ((NUM_BITS - position) < length)
        {
            end_bit = NUM_BITS - 1;
            start_bit = position;
            data = value & (allones >> (NUM_BITS - position));
            value >>= (NUM_BITS - position);
            length -= (NUM_BITS - position);
            position = 0;
        }
        else
        {
            start_bit = position;
            end_bit = position + length - 1;
            data = value;
            length = 0;
        }

        // Prepare the mask
        uint8_t left = allones << (end_bit + 1);
        uint8_t right = ((1 << start_bit) - 1);
        uint8_t mask = left | right;

        // Clear bits start_bit through end_bit
        uint8_t byte_cleared = buffer[index] & mask;

        // Move data into correct position.
        uint8_t data_shifted = data << start_bit;

        // Update buffer with new value
        buffer[index] = (byte_cleared | data_shifted);
        index++;
    }
}

//Function to extract value from the buffer
uint64_t buffer_extract(uint8_t *buffer, uint8_t start, uint8_t length)
{
    int extract_len = 0;
    uint64_t value = 0;
    int index = start / NUM_BITS;
    uint8_t position = start % NUM_BITS;
    uint8_t tmp, shift = 0;
    uint8_t remlen = length;

    while (remlen)
    {
        if ((NUM_BITS - position) < remlen)
        {
            extract_len = NUM_BITS - position;
            tmp = (((1 << extract_len) - 1) & (buffer[index] >> position));
            shift = length - remlen;
            remlen -= extract_len;
            position = 0;
        }
        else
        {
            extract_len = remlen;

            shift = length - remlen;
            tmp = (((1 << extract_len) - 1) & (buffer[index] >> position));
            remlen = 0;
        }
        value |= (uint64_t)tmp << shift;
        index++;
    }

    return value;
}
