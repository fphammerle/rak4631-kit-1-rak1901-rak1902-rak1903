#include <OneWire.h>
#include <DallasTemperature.h>

#include "app.h"

OneWire onewire(WB_IO1);
DallasTemperature onewire_sensor(&onewire);

bool init_onewire(void) {
    byte address[8];
    if(!onewire.search(address)) {
        MYLOG("1WIRE", "No device found");
        return false;
    } else {
        MYLOG(
            "1WIRE", "Address: %0X%0X%0X%0X%0X%0X%0X%0X",
            address[0], address[1], address[2], address[3],
            address[4], address[5], address[6], address[7]
        );
        return true;
    }
}

void read_onewire() {
    MYLOG("1WIRE", "Requesting temperatures");
    onewire_sensor.requestTemperatures();
    MYLOG("1WIRE", "Temperature: %.1f C", onewire_sensor.getTempCByIndex(0));
    g_solution_data.addTemperature(
        LPP_CHANNEL_TEMP_1WIRE,
        onewire_sensor.getTempCByIndex(0)
    );
}
