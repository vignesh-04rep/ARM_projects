# I2C Smart Street Light Monitoring with Vehicle Count

## 📌 Overview
A smart street lighting system using **I2C communication**, **LDR sensor**, and **EEPROM**.  
It automatically adjusts street light brightness based on ambient light and vehicle detection, while logging data for analysis.

---

## ✨ Features
- 🌙 **Ambient Light Detection**: LDR + I2C ADC (ADS1115) for day/night switching.  
- 🚗 **Vehicle Counting**: IR/PIR sensor detects passing vehicles and logs counts.  
- 💡 **Smart Lighting Control**:  
  - Lights OFF during daytime  
  - Dim mode at night  
  - Boost brightness when vehicles are detected  
- 📝 **Data Logging**: I2C EEPROM (24LC256) stores events (vehicle counts, light states, ambient readings).  

---

## 🛠️ Hardware
- ARM Microcontroller (lpc2129)  
- LDR sensor (ambient light)  
- IR/PIR/Ultrasonic sensor (vehicle detection)  
- ADS1115 I2C ADC  
- 24LC256 EEPROM  
- MOSFET/LED driver for street light control  
- *(Optional)* DS3231 RTC for timestamps  

---

## ⚙️ Workflow
1. MCU reads ambient light via I2C ADC.  
2. If **daytime** → lights OFF.  
3. If **nighttime** → lights in **dim mode**.  
4. If **vehicle detected** → lights switch to **boost mode** for a short duration.  
5. Events logged into EEPROM for later analysis.  

---

## 📊 EEPROM Data Format
Each record includes:
- Timestamp (RTC/system clock)  
- Event type (vehicle, light ON/OFF, ambient reading)  
- Value (count, ADC reading, PWM level)  
- CRC for integrity  

---
