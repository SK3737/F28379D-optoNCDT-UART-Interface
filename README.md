# F28379D-optoNCDT-UART-Interface
Real-time RS422 UART distance data acquisition from Micro-Epsilon optoNCDT sensors using the TMS320F28379D C2000 LaunchPad. Implements UART reception, ASCII parsing, and float conversion via SCIA interrupt-driven interface.

## 🔧 Hardware Setup

| Sensor Pin      | Connect To                        |
|-----------------|-----------------------------------|
| RS422 TX+ (pink)| RS422 to TTL RX+ (A)             |
| RS422 TX− (red) | RS422 to TTL RX− (B)             |
| GND (blue)      | MCU GND                          |
| 24V (brown)     | External 24V DC Supply           |
| TTL TX          | TMS320 GPIO42 (SCIA_RX)          |
| TTL GND         | MCU GND                          |

> ⚠️ Use an RS422 → TTL converter (e.g. SN75176) between sensor and MCU.

---

## 🧠 Features

- Receives distance in ASCII over UART
- Parses value to float using `atof()`
- Handles each message using UART interrupt
- Scalable for logging or filtering

---

## 📁 Project Structure

TMS320F28379D_RS422_Reader/
├── src/
│ └── main.c
├── inc/
├── docs/
└── README.md

## 🛠️ How to Build (CCS 12.x)

1. Open **Code Composer Studio**
2. Import this folder as a CCS project
3. Target: **F28379D**, CPU1
4. Build and flash
5. Monitor UART output or distance variable

---

## 🚀 Future Add-ons

- UART TX echo for debugging
- Distance smoothing (filtering)
- Logging to flash or sending to PC

---

## 📜 License

MIT License – free to use and modify.

---
