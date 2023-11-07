#include "dac_cxx.hpp"

namespace idf {

DacOneshot::DacOneshot(dac_channel_t channel) {
    dac_oneshot_config_t oneshot_cfg = {
        .chan_id = channel
    };

    esp_err_t ret = dac_oneshot_new_channel(&oneshot_cfg, &handle);
    if (ret != ESP_OK) {
        throw ESPException(ret);
    }
}

void DacOneshot::setVoltageRaw(uint8_t valueRaw) {
    esp_err_t ret = dac_output_voltage(handle, valueRaw);
    if (ret != ESP_OK) {
        throw ESPException(ret);
    }
}

void DacOneshot::setVoltageMlVolt(uint16_t valueMlVolt) {
    esp_err_t ret = dac_output_voltage(handle, valueMlVolt);
    if (ret != ESP_OK) {
        throw ESPException(ret);
    }
}

} // namespace idf
