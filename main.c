#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include "sd_card_mount.h"
#include "i2s_audio.h"
#include "wav_player.h"

void app_main(void)
{
    sd_card_mount();
    i2s_audio();
   // play_wav("/sdcard/sample-3s.wav");
    //play_wav("/sdcard/sample-speech-1m.wav");
    play_wav("/sdcard/sample-12s.wav");
}
