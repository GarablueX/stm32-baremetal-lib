# STM32F4xx Reusable GPIO & ADC Functions Library

This library (`FONCTIONS.h`) provides a collection of **reusable, easy-to-use C functions** for quickly managing GPIO pins and the ADC peripheral on STM32F401RE (and similar STM32F4) microcontrollers.  
It abstracts away common register manipulations for GPIO configuration, digital I/O, and ADC setup/reading.

---

##  **Included Features**

### 1. **GPIO Configuration and Control**
- **Pin Mode:** Easily set pins as `INPUT`, `OUTPUT`, `ANALOG`, or `ALTERNATE` functions.
- **Output Type:** Select between Push-Pull (`PP`) and Open-Drain (`OD`).
- **Output Speed:** Choose `LOW`, `MEDIUM`, `FAST`, or `HIGH` output speed.
- **Input Pull Configuration:** Enable `NO` pull, `PULL-UP` (`PU`), or `PULL-DOWN` (`PD`).
- **Digital Read:** Read the state of an input pin.
- **Port Clock Enable:** Dynamically enable the necessary GPIO port clock before use.

### 2. **ADC (Analog-to-Digital Converter)**
- **Single-Channel ADC Setup and Sampling:** One function (`Port_ADC`) handles
  - Port clock and pin analog mode setup
  - ADC peripheral setup (resolution, sample time)
  - Channel selection
  - Triggers a single conversion and reads the result

---

##  **How To Use**

### 1. **Include the Header**
```c
#include "FONCTIONS.h"
```

### 2. **Configure a GPIO Pin Example**
```c
// Set PA5 as high-speed push-pull output
Port_Clocks(GPIOA);
Port_Mode(GPIOA, OUTPUT, 5);
Output_Types(GPIOA, PP, 5);
Output_Speed(GPIOA, HIGH, 5);
Input_types(GPIOA, NO, 5); // Not strictly needed in output mode
```

### 3. **Read from a GPIO Pin Example**
```c
Port_Mode(GPIOA, INPUT, 6);
Input_types(GPIOA, PU, 6); // Enable pull-up
uint8_t value = Read_Pin(GPIOA, 6); // value is 0 or 1
```

### 4. **Single ADC Conversion Example**
```c
// Read analog value from PA0 (ADC1_IN0), 12-bit resolution, 56 cycles sample time
uint16_t val = Port_ADC(GPIOA, 0, 0, 12, 56);
// Arguments: (Port, pin_number, ADC_channel, resolution, sample_time)
```

---

##  **Available Macros**

- **Pin modes:** `INPUT`, `OUTPUT`, `ANALOG`, `ALTER`
- **Output types:** `PP` (Push-Pull), `OD` (Open-Drain)
- **Output speeds:** `LOW`, `MEDIUM`, `FAST`, `HIGH`
- **Input types:** `NO` (No pull), `PU` (Pull-up), `PD` (Pull-down)

---

##  **Function List**

- `Port_Clocks(GPIO_TypeDef *Port)` — Enable RCC clock for a given port (GPIOA to GPIOH).
- `Port_Mode(GPIO_TypeDef *Port, uint8_t type, int pinNumber)` — Set pin mode.
- `Output_Types(GPIO_TypeDef *Port, uint8_t type, int pinNumber)` — Set output push-pull/open-drain.
- `Output_Speed(GPIO_TypeDef *Port, uint8_t type, int pinNumber)` — Set output speed.
- `Input_types(GPIO_TypeDef *Port, uint8_t type, int pinNumber)` — Configure input pull settings.
- `Read_Pin(GPIO_TypeDef *Port, int pinNumber)` — Read input pin state.
- `Port_ADC(GPIO_TypeDef *Port, int pinNumber, int Channel, int Resolution, int Samples)` — Configure and read ADC value from a given channel and pin.

---

##  **Notes/Tips**

- All functions are `inline static` for efficiency — include in a single compilation unit or your main file.
- `Port_ADC` is for **single ADC readings**; for multi-channel or continuous/DMA conversions, you’ll need extended functions.
- Ensure you match the correct pin number and ADC channel as per STM32F401RE datasheet.
- If using GPIOF, GPIOG, or GPIOH, verify those ports exist on your microcontroller.

---

##  **Example Project**

See `main.c` in this repository for a real example that:
- Toggles outputs,
- Reads digital inputs,
- Performs ADC conversions on multiple pins,
using only functions from this `FONCTIONS.h` library.

---

**Author:** GarablueX  
**Tested on:** STM32F401RE (should work with minor changes on similar STM32F4 series MCUs)

---