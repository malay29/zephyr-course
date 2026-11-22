#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>


// create handler
// static int cmd_channel_get_handler(const struct shell *sh, int argc, char** argv)
// {   
//     shell_info(sh, "Hello from channel get");
//     return 0;
// }

static int cmd_fetch_handler(const struct shell *sh, int argc, char** argv)
{   
    const struct device *dev = shell_device_get_binding(argv[1]);
    if (!dev) {
        shell_error(sh, "Device not found %s", argv[1]);
        return -ENODEV;
    }

    int ret = sensor_sample_fetch(dev);
    if(ret != 0) {
        shell_error(sh, "sensor_sample_fetch failed with error %d", ret);
        return -EFAULT;
    }
    // shell_info(sh, "sensor_sample_fetch returned %d", ret);
    return 0;
}

static int cmd_channel_get_handler(const struct shell *sh, int argc, char** argv)
{   
    const struct device *dev = shell_device_get_binding(argv[1]);
    if (!dev) {
        shell_error(sh, "Device not found %s", argv[1]);
        return -ENODEV;
    }

    struct sensor_value val;
    int ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    if(ret != 0) {
        shell_error(sh, "sensor_channel_get failed with error %d", ret);
        return -EFAULT;
    }
    shell_info(sh, "sensor_channel_get returned %d", val.val1);
    return 0;
}

static int cmd_info_handler(const struct shell *sh, int argc, char** argv)
{   
    const struct device *dev = shell_device_get_binding(argv[1]);
    if (!dev) {
        shell_error(sh, "Device not found %s", argv[1]);
        return -ENODEV;
    }

    shell_info(sh, "Device name: %s", dev->name);
    shell_info(sh, "Device ready state: %d", device_is_ready(dev));
    return 0;
}


SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmd,
    SHELL_CMD_ARG(fetch, NULL, "Call sensor_sample_fetch", cmd_fetch_handler, 2, 0),
    SHELL_CMD_ARG(read, NULL, "call sensor_channel_get", cmd_channel_get_handler, 2, 0),
    SHELL_CMD_ARG(info, NULL, "print device name and ready state", cmd_info_handler, 2, 0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "Our driver set of commands", NULL);