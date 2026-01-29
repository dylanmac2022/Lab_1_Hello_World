# AI Agent Coding Instructions for Lab_1_Hello_World

## Project Overview
This is an **ESP-IDF embedded systems project** for ESP32/ESP32S3 microcontrollers. It's a FreeRTOS-based application that demonstrates GPIO control and real-time output on Espressif chips. The project uses CMake as the build system and is part of ECE_796 lab assignments.

## Architecture & Key Components

### Build System
- **Framework**: ESP-IDF (Espressif IoT Development Framework)
- **Build Tool**: CMake with idf.py wrapper
- **Build Output**: Located in `build/` directory after compilation
- **Configuration**: ESP-IDF project configuration stored in `sdkconfig` files
- **Minimal Build**: `CMakeLists.txt` uses `MINIMAL_BUILD` to include only necessary components

### Main Application
- **Entry Point**: [main/hello_world_main.c](../main/hello_world_main.c)
- **FreeRTOS Integration**: Uses FreeRTOS tasks, drivers, and timing utilities
- **Key Dependencies** (from [main/CMakeLists.txt](../main/CMakeLists.txt)):
  - `driver`: GPIO control via `gpio_set_direction()`, `gpio_set_level()`
  - `esp_timer`: High-resolution timing with `esp_timer_get_time()`
- **Current Behavior**: LED blink on GPIO pin 2 with 500ms toggle interval

## Development Workflows

### Building
```bash
idf.py build
```
Or use VS Code task: `C/C++: xtensa-esp32-elf-gcc.exe build active file`

### Flashing to Device
```bash
idf.py flash
```

### Serial Monitoring (View Output)
```bash
idf.py monitor
```

### Combined Build, Flash & Monitor
```bash
idf.py build flash monitor
```

### Configuration
```bash
idf.py menuconfig
```
Opens interactive configuration menu for ESP-IDF settings (chip selection, peripheral options).

### Full Clean Rebuild
```bash
idf.py fullclean && idf.py build
```

## Code Patterns & Conventions

### GPIO Control Pattern
```c
// 1. Set direction (output)
gpio_set_direction(PIN_NUMBER, GPIO_MODE_OUTPUT);

// 2. Set level (HIGH=1, LOW=0)
gpio_set_level(PIN_NUMBER, level_value);
```

### FreeRTOS Task Delays
```c
// vTaskDelay takes milliseconds converted via portTICK_PERIOD_MS
vTaskDelay(500 / portTICK_PERIOD_MS);  // 500ms delay
```

### Timing
- Use `esp_timer_get_time()` for microsecond-precision timestamps
- Convert to milliseconds: divide by 1000
- Useful for logging events and measuring performance

### Component Dependencies
- Only add `REQUIRES` directives in [main/CMakeLists.txt](../main/CMakeLists.txt) for components actually used
- Avoid unnecessary dependencies to keep build minimal

## Testing

### Automated Tests
- **Test Script**: [pytest_hello_world.py](../pytest_hello_world.py)
- **Framework**: pytest with pytest-embedded-idf
- **Test Approach**: Validates expected serial output ("Hello world!") from the running device
- **Target Coverage**: Tests run against `supported_targets` and `preview_targets` (all ESP32 variants)
- **Heap Logging**: Tests also log minimum free heap size for memory debugging

### Running Tests
```bash
idf.py pytest
```

## Integration Points & External Dependencies

### ESP-IDF Components (Automatically Managed)
- **FreeRTOS**: Real-time kernel (included via esp_system)
- **ESP ROM**: Hardware abstraction layer
- **HAL**: Hardware Abstraction Layer for chip-specific operations
- **Driver Library**: Peripheral drivers (GPIO, UART, SPI, etc.)

### Standard Libraries
- `stdio.h`: printf() for logging
- `freertos/task.h`: FreeRTOS task APIs

## Important Files Map
| File | Purpose |
|------|---------|
| [CMakeLists.txt](../CMakeLists.txt) | Root CMake config; sets project name, includes IDF tools |
| [main/CMakeLists.txt](../main/CMakeLists.txt) | Registers main component, lists source files & dependencies |
| [main/hello_world_main.c](../main/hello_world_main.c) | Application entry point (`app_main()` function) |
| [pytest_hello_world.py](../pytest_hello_world.py) | Automated test suite for hardware validation |
| [sdkconfig](../sdkconfig) | Build-time configuration (chip type, features) |
| [build/](../build/) | Generated build artifacts (ELF, binaries, config headers) |

## Debugging Tips

- **No Serial Output**: Check `idf.py monitor -p /dev/ttyUSB0` (adjust port) to verify baud rate and connection
- **Build Errors**: Run `idf.py fullclean` to remove stale artifacts, then rebuild
- **Configuration Issues**: Use `idf.py menuconfig` to verify target chip (ESP32 vs ESP32-S3) and other settings
- **Heap Warnings**: Monitor output shows free heap; if too low, reduce buffer sizes or task stack allocations

## Project-Specific Notes

- This is an **educational lab assignment** with intentional simplicity for learning embedded systems concepts
- **No external dependencies** beyond ESP-IDF (which is framework-provided)
- Focus areas: GPIO control, FreeRTOS timing, embedded logging patterns
- Code includes detailed comments for clarity (intentional for learning purpose)
