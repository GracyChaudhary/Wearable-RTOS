# Wearable-RTOS
A simulated RTOS for wearable devices using FreeRTOS

# WearableRTOS
Simulated RTOS for a wearable device using FreeRTOS. Tracks pulse with three tasks:

Reader: Gets pulse data every 900ms.
Smoother: Adjusts data every 1400ms.
Display: Shows pulse every 1800ms.
Run in Arduino IDE (ESP32) or Wokwi. Output at 115200 baud.
