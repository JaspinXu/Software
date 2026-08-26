# ESP32-S3 E-Calendar

An embedded smart calendar for the ESP32-S3 with a touch display, LVGL interface, Wi-Fi connectivity, lunar-calendar views, weather-style widgets, media controls, and modular mini-apps.

![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32--S3-F5822A?logo=platformio&logoColor=white)
![Arduino](https://img.shields.io/badge/Framework-Arduino-00979D?logo=arduino&logoColor=white)
![LVGL](https://img.shields.io/badge/UI-LVGL-2A8BCE)

## What is included

- Touch-enabled LVGL user interface on a TFT display.
- Home and lunar-calendar screens.
- Wi-Fi connectivity and network-backed application modules.
- Bilibili statistics views for followers, likes, and views.
- Music control with DFPlayer Mini support.
- RTC, DHT sensor, addressable LED, MQTT, email, and OTA dependencies.
- Custom Chinese fonts and image assets compiled into firmware.

## Hardware and firmware target

The checked-in PlatformIO environment targets:

| Item | Configuration |
|---|---|
| Board | `esp32-s3-devkitc-1` |
| Framework | Arduino |
| Flash | 16 MB, QIO, 80 MHz |
| PSRAM | OPI |
| Serial monitor | 115200 baud |
| Upload speed | 921600 baud |
| Partition table | `partitions-no-ota.csv` |

Peripheral pin assignments and display settings are defined in the project headers and bundled library configuration. Review them before flashing different hardware.

## Getting started

### Prerequisites

- VS Code with the PlatformIO extension, or PlatformIO Core
- An ESP32-S3 development board matching the configured display and peripherals
- A USB data cable and the appropriate serial driver

### Build

```bash
git clone https://github.com/JaspinXu/esp32-based-e-calendar.git
cd esp32-based-e-calendar
pio run
```

### Upload and monitor

Update `upload_port` in `platformio.ini` for your machine, then run:

```bash
pio run --target upload
pio device monitor
```

## Configuration and security

Before flashing, replace the Wi-Fi values in `src/main.cpp` with your own configuration. The repository preserves the original prototype setup; credentials should be moved to a private header excluded by Git or injected with PlatformIO build flags for continued use.

Also verify:

- display and touch-controller pins;
- RTC, sensor, LED, and audio connections;
- any network service IDs or tokens used by individual apps;
- the serial upload port for your operating system.

## Project structure

```text
src/main.cpp             Firmware entry point
src/gui.cpp              LVGL application shell
src/app/home/            Home screen
src/app/lunar/           Lunar calendar and zodiac assets
src/app/bilibili/        Bilibili statistics screens
src/app/music/           Audio controls
src/app/ota/             OTA functionality
src/driver/              Display, touch, and filesystem ports
include/                 Shared declarations
lib/                     Bundled display and touch libraries
platformio.ini           Board, memory, dependency, and upload settings
```

## Notes

- The bundled libraries and generated image/font sources make this repository relatively large.
- The partition configuration is named `partitions-no-ota.csv`; confirm the memory layout before relying on the OTA module.
- This is a hardware-specific prototype, so successful flashing alone does not guarantee that a different display or pinout will work unchanged.

