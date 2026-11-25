#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2s_audio.h"
#include "wav_player.h"


static uint8_t pcm_buffer[512];

void play_wav(const char *filename)
{
    printf("wav_player tx_chan = %p\n", tx_chan);

    FILE *f = fopen(filename, "rb");

    if (f == NULL)
    {
        printf("Failed to open %s\n", filename);
        return;
    }

    printf("Opened %s successfully\n", filename);

    uint8_t header[44];

    fread(header, 1, 44, f);
    uint32_t data_size =
    header[40] |
    (header[41] << 8) |
    (header[42] << 16) |
    (header[43] << 24);

    printf("Data size = %lu\n", (unsigned long)data_size);

    printf("Chunk ID : %.4s\n", &header[0]);
    printf("Format   : %.4s\n", &header[8]);
    printf("Subchunk : %.4s\n", &header[12]);

    printf("Starting playback...\n");

    size_t bytes_read;
    size_t bytes_written;

    size_t total_bytes = 0;

while (1)
{
    bytes_read = fread(
        pcm_buffer,
        1,
        sizeof(pcm_buffer),
        f);

    if (bytes_read == 0)
    {
        break;
    }

    total_bytes += bytes_read;

    i2s_channel_write(
        tx_chan,
        pcm_buffer,
        bytes_read,
        &bytes_written,
        portMAX_DELAY);
}

        printf("Played %u bytes\n",
       (unsigned int)total_bytes);
}