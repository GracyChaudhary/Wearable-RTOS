# Wearable-RTOS
A simulated RTOS for wearable devices using FreeRTOS

# Heart Rate Sensor with Real-Time Operating System (RTOS) for Wearable Devices

## Overview

This project demonstrates a wearable heart rate sensor system implemented on an **ESP32** using **FreeRTOS**. The system simulates heart rate data acquisition, smoothing, and display using three concurrent tasks, making it ideal for wearable health-monitoring devices.

---

## Features

- **Multi-tasking with FreeRTOS**  
  Utilizes three separate tasks:
  - `read_hr`: Simulates real-time heart rate data generation.
  - `smooth_hr`: Applies a smoothing algorithm for noise reduction.
  - `show_hr`: Displays the processed heart rate.

- **Thread-Safe Data Sharing**  
  Uses a FreeRTOS **mutex (Semaphore)** to ensure safe access to shared heart rate data between tasks.

- **Real-Time Simulation**  
  Simulates pulse values in the range of 55–105 BPM with adjustable update intervals.

---

## Hardware Requirements

- **ESP32 Development Board**
- **USB cable** for programming and serial communication
- **Optional:** OLED display or Bluetooth module (for future real-world expansion)

---

## Software Requirements

- **Arduino IDE**
- **ESP32 Board Support** via Board Manager
- **FreeRTOS libraries** (pre-included with ESP32 core)
- **Serial Monitor** for viewing output

---

## Task Scheduling

| Task Name    | Priority | Interval (ms) | Description                         |
|--------------|----------|----------------|-------------------------------------|
| HR Reader    | 3        | 900            | Simulates pulse data                |
| HR Smoother  | 2        | 1400           | Smoothens the raw heart rate data   |
| HR Display   | 1        | 1800           | Displays smoothed pulse rate        |

---

## Code Explanation

- **`read_hr()`**: Simulates heart rate data and updates the `hr_raw` variable.
- **`smooth_hr()`**: Applies a weighted average filter for noise reduction.
- **`show_hr()`**: Prints the smoothed BPM value to the Serial Monitor.
- **Mutex** (`hr_lock`) ensures safe access to `hr_raw` and `hr_smooth` across tasks.
- `setup()` initializes Serial communication, mutex, and tasks.
- `loop()` delays indefinitely as all functionality is handled by RTOS tasks.

---

## Sample Output
## 📟 Sample Output

Wearable system online!
[HR Reader] Pulse: 87 BPM
[HR Smoother] Adjusted Pulse: 85 BPM
[HR Display] Pulse Rate: 85 BPM
[HR Reader] Pulse: 95 BPM
[HR Smoother] Adjusted Pulse: 90 BPM
[HR Display] Pulse Rate: 90 BPM
[HR Reader] Pulse: 76 BPM
[HR Smoother] Adjusted Pulse: 86 BPM
[HR Display] Pulse Rate: 86 BPM
