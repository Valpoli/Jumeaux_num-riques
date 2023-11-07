#include "adc_cxx.hpp"

namespace idf {

AdcOneshot::AdcOneshot(adc_unit_t unit) {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = unit,
        .ulp_mode = ADC_ULP_MODE_DISABLE, // Assuming normal mode, not ULP
    };

    esp_err_t ret = adc_oneshot_new_unit(&init_config, &handle);
    if (ret != ESP_OK) {
        throw ESPException(ret);
    }
}


void AdcOneshot::configure(adc_channel_t channel, adc_atten_t atten, adc_bitwidth_t bitwidth) {
    adc_oneshot_chan_cfg_t config = {
        .atten = atten,
        .bitwidth = bitwidth,
    };

    esp_err_t ret = adc_oneshot_config_channel(handle, channel, &config);
    if (ret != ESP_OK) {
        throw ESPException(ret);
    }
}

std::pair<adc_unit_t, adc_channel_t> AdcOneshot::ioToChannel(int ioNum) {
    adc_unit_t unit;
    adc_channel_t channel;

    esp_err_t ret = adc_oneshot_io_to_channel(ioNum, &unit, &channel);
    if (ret != ESP_OK) {
        throw ESPException(ret);
    }

    return std::make_pair(unit, channel);
}

int AdcOneshot::readRaw(adc_channel_t channel) {
    int raw_data = 0;
    esp_err_t ret = adc_oneshot_read(handle, channel, &raw_data);
    if (ret != ESP_OK) {
        throw ESPException(ret);
    }
    return raw_data;
}

int AdcOneshot::readMlVolt(adc_channel_t channel) {
    int millivolt = 0;
    esp_err_t ret = adc_oneshot_read(handle, channel, &millivolt);
    if (ret != ESP_OK) {
        throw ESPException(ret);
    }
    return millivolt;
}

} // namespace idf
