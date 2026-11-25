#include "constants.h"
#include "i2s_audio.h"

i2s_chan_handle_t tx_chan;
#define SAMPLE_RATE    44100

void i2s_audio(void)
{
    //i2s_chan_handle_t tx_chan;

    i2s_chan_config_t chan_cfg =
        I2S_CHANNEL_DEFAULT_CONFIG(
            I2S_NUM_0,
            I2S_ROLE_MASTER);

    i2s_new_channel(
        &chan_cfg,
        &tx_chan,
        NULL);

        i2s_std_config_t std_cfg =
    {
        .clk_cfg =
            I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),

        .slot_cfg =
            I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(
                I2S_DATA_BIT_WIDTH_16BIT,
                I2S_SLOT_MODE_STEREO),

        .gpio_cfg =
        {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = GPIO_NUM_26,
            .ws   = GPIO_NUM_25,
            .dout = GPIO_NUM_22,
            .din  = I2S_GPIO_UNUSED,

            .invert_flags =
            {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv   = false
            }
        }
    };

    i2s_channel_init_std_mode(
        tx_chan,
        &std_cfg);

    i2s_channel_enable(tx_chan);
        printf("tx_chan = %p\n", tx_chan);
}
