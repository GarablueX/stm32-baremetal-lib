# STM32F4 Bare-Metal Peripheral Library

A minimal register-level C library for STM32F4 microcontrollers—**no HAL, no dependencies, just clean code you control.**  
Ideal for students, hobbyists, and anyone who wants to *really* understand microcontroller peripheral setup.

---

## ✨ Features

- Digital I/O (input/output, speed, pull, open-drain, etc.)
- Direct GPIO register access
- Analog input (ADC) configuration & single-read (with customizable resolution and sample time)
- HD44780 2×16 LCD control (or similar character LCDs)
- Tiny, header-only design (just include and go!)

---

## 🚀 Getting Started

1. **Copy the Files**  
   Clone this repo or copy `fonctions.h` and `LCD_Fontions.h` into your STM32CubeIDE, Keil, or Make-based project.

2. **Connect Your Hardware**  
   - STM32F4xx MCU or board (e.g. STM32F401, STM32F411, Nucleo/Discovery)
   - Optionally, a standard HD44780 LCD (parallel 8-bit mode)
   - Analog input (potentiometer or sensor) on a supported ADC-capable GPIO pin (see your chip's datasheet)

3. **Include in Your Code:**
    ```c
    #include "stm32f4xx.h"
    #include "fonctions.h"
    #include "LCD_Fontions.h"
    ```

4. **Example Usage:**  
    ```c
    int main(void) {
        Port_Clocks(GPIOC);
        Port_Clocks(GPIOB);
        LCD_INIT();
        LCDReset();
        uint16_t adc_val = Port_ADC(GPIOC, 0, 10, 12, 480); // Read PC0 (ADC1_IN10)
        LCDsetCursor(1, 0);
        LCDsendAstring("ADC:");
        LCDsendINT(adc_val, 5);
        while(1);
    }
    ```
   _(See `main.c` for a complete demo!)_

---

## 🛠️ Peripherals Covered

- **GPIO**  
  - Set pin modes (INPUT, OUTPUT, ANALOG, ALTERNATE)
  - Pull-up, pull-down, open-drain, output speed, digital read & write

- **ADC**  
  - Single conversion, configurable sample time/resolution

- **LCD (HD44780 8-bit interface)**  
  - Easy string/number display and cursor control

---

## 📦 Supported Chips/Boards

- STM32F401, STM32F411, and most STM32F4xx with similar peripheral bases
- Nucleo/Discovery & "Blue Pill F4" dev boards (see datasheet for ADC/gpio pin mapping)
- Should port easily to other STM32 families with minor tweaks

---

## ⛑️ Why Use This Library?

- **Learn how STM32F4 hardware really works.**
- No vendor lock-in or HAL complexity.
- Minimal code: drop in, use, and hack.
- Full control for real bare-metal projects, labs, or coursework.

---

## 🏗️ Contributing

- Suggestions, bug reports, and pull requests welcome!
- To request a feature/port, open an Issue or post in [your favorite embedded forum].
- Please share how you used the library and improvements.

---

## 📖 License

Open source under the MIT License.  
See [LICENSE](./LICENSE) for details.

---

### 💬 Feedback wanted!

If you’re a beginner or an embedded pro, I’d love to know:
- Is the code portable enough?
- Any best-practices or style fixes?
- What features should I add next?
- Did this help you in your bare-metal learning journey?

_Thanks for checking out my project!_
