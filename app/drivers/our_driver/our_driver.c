#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_config {
    struct gpio_dt_spec led;
    int callibration;
} ;

struct our_driver_data {
    bool led_state;
};

static int our_driver_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val)
{
    LOG_INF("Channel get, channel %d", chan);
    const struct our_driver_config *cfg = dev->config;
    struct our_driver_data *data = dev->data;

    data->led_state = false;
    gpio_pin_set_dt(&cfg->led, 0);

    val->val1 = data->led_state;
    val->val2 = 0;
    LOG_INF("LED state OFF");
    return 0;
}

static int our_driver_sample_fetch(const struct device *dev, enum sensor_channel chan)
{
    LOG_INF("Sample fetch, channel %d", chan);
    const struct our_driver_config *cfg = dev->config;
    struct our_driver_data *data = dev->data;

    data->led_state = true;
    gpio_pin_set_dt(&cfg->led, 1);
    LOG_INF("LED state ON");
    return 0;
}

static DEVICE_API(sensor, our_driver_api) = {
    
    .channel_get = our_driver_channel_get,
    .sample_fetch = our_driver_sample_fetch,
};

// Init function
static int our_driver_init(const struct device *dev)
{
    const struct our_driver_config *cfg = dev->config;

    if (!gpio_is_ready_dt(&cfg->led)) {
        return -ENODEV;
    }

    gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_INACTIVE);
    LOG_INF("Device Initialized!");
    return 0;
}


#define OUR_DRIVER_DEFINE(inst) \
    static const struct our_driver_config our_driver_config_##inst = { \
        .led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios), \
        .callibration = DT_INST_PROP(inst, callibration), \
    }; \
    static struct our_driver_data our_driver_data_##inst; \
    DEVICE_DT_INST_DEFINE(inst, our_driver_init, NULL, &our_driver_data_##inst, &our_driver_config_##inst, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY, &our_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE)