# STM32 8-Bit LCD Driver Library (LCD_Fonctions.h)

This library provides reusable, inline C functions for controlling a standard **character LCD** (such as the HD44780 16x2 or 20x4) via an 8-bit data bus on STM32F4 microcontrollers.

---

##  **Features**

- **Direct GPIO control**: All LCD signals are mapped to user-defined STM32 pins.
- **8-bit data transfer mode**: Faster and easier setup than 4-bit.
- **Functions for:**  
    - Initializing the LCD  
    - Sending commands and data  
    - Printing characters, integers, floats, and strings  
    - Cursor positioning  
    - Manual E (+ delay) handling  
    - Full test routine to fill/clear/test LCD
- **Simple, inline for efficiency** (can be placed in `main.c`, no external dependencies but STM32 and HAL).

---

##  **Pin Mapping**
| LCD Pin  | STM32 Pin      |
|----------|---------------|
| D0       | PA12          |
| D1       | PA13          |
| D2       | PA14          |
| D3       | PA15          |
| D4       | PB0           |
| D5       | PB1           |
| D6       | PB2           |
| D7       | PB3           |
| RS       | PA9           |
| RW       | PA10          |
| E        | PA11          |

*You can change these by editing/create macros at the top of the file.*

---

## ⚡ **How To Use**

### 1. **Include the Header**

```c
#include "LCD_Fonctions.h"
```

### 2. **Initialize the LCD**
```c
LCD_INIT();
```

### 3. **Print to the LCD**

```c
LCDsendAstring("Hello, world!");
LCDsetCursor(2, 0);
LCDsendINT(1234, 5);
LCDsetCursor(1, 0);
LCDsendFloat(3.1415, 7);
```

### 4. **Commands & Cursor**

```c
LCDsendAcommand(0x01);      // Clear display
LCDsetCursor(1, 3);         // Move to line 1, column 3
```

### 5. **Full Test Pattern**

```c
LCDTESTLCDCASES();
```
Prints a series of test characters in every LCD DDRAM slot.

---

##  **Function Reference**

- `LCD_INIT()` — Initializes the LCD (8-bit mode, display on).
- `LCDsendAstring(char*)` — Print a string at current LCD cursor.
- `LCDsendAcharacter(uint8_t)` — Print a single ASCII character.
- `LCDsendINT(int, unsigned int length)` — Print integer as characters.
- `LCDsendFloat(float, unsigned int MAXlength)` — Print float.
- `LCDsetCursor(int line, int column)` — Set cursor (line: 1-2, column: 0-15).
- `LCDsendAcommand(uint8_t)` — Send raw LCD command byte.
- `LCDReset()` — Clear display, home cursor.
- `LCDLine2Enable()` — Ensure multi-line mode enabled.
- `LCDTESTLCDCASES()` — Fills LCD with X's, reset, writes "Test done !!" lines.
- *Low-level functions*: For custom operations, see `sendByteToLCD`, `sendBitToPortAndPin`, etc.

---

##  **Important Notes**
- You **must call `LCD_INIT()`** before any printing.
- The OLED/LCD pins **must be wired as defined**, or the macros in the header must match your wiring.
- Timing is handled by crude delay loops (`NETimeDelay`) — works for most displays, but you may want to use `HAL_Delay` for more robust behavior.
- The RW pin is used — to save IOs, you might tie it LOW in hardware and skip `SetToReadOrWrite`, modifying your code accordingly.
- For STM32, this library expects all port and pin macros to match the STM32 HAL type system.

---

##  **Example**

```c
#include "LCD_Fonctions.h"

int main(void)
{
    HAL_Init();
    LCD_INIT();

    LCDsendAstring("STM32 LCD Demo");
    LCDsetCursor(2, 0);
    LCDsendAstring("ADC: ");
    int val = 1234;
    LCDsendINT(val, 5);

    while(1) {
        // Update or blink as needed
    }
}
```

---

**Author:** GarablueX  
**Tested on:** STM32F401RE (should work on similar STM32F4 with changed macros/pin mapping)

---