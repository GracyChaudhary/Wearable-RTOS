#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

int hr_raw = 0;
int hr_smooth = 0;
SemaphoreHandle_t hr_lock;

TaskHandle_t hr_sensor = NULL;
TaskHandle_t hr_processor = NULL;
TaskHandle_t hr_output = NULL;

void read_hr(void *params) {
  TickType_t last_run = xTaskGetTickCount();
  while (1) {
    int temp_hr = random(55, 105);
    xSemaphoreTake(hr_lock, portMAX_DELAY);
    hr_raw = temp_hr;
    Serial.printf("[HR Reader] Pulse: %d BPM\n", hr_raw);
    xSemaphoreGive(hr_lock);
    vTaskDelayUntil(&last_run, pdMS_TO_TICKS(900));
  }
}

void smooth_hr(void *params) {
  TickType_t last_run = xTaskGetTickCount();
  int previous = 0;
  while (1) {
    xSemaphoreTake(hr_lock, portMAX_DELAY);
    hr_smooth = (hr_raw * 3 + previous) / 4;
    previous = hr_raw;
    Serial.printf("[HR Smoother] Adjusted Pulse: %d BPM\n", hr_smooth);
    xSemaphoreGive(hr_lock);
    vTaskDelayUntil(&last_run, pdMS_TO_TICKS(1400));
  }
}

void show_hr(void *params) {
  TickType_t last_run = xTaskGetTickCount();
  while (1) {
    xSemaphoreTake(hr_lock, portMAX_DELAY);
    Serial.printf("[HR Display] Pulse Rate: %d BPM\n", hr_smooth);
    xSemaphoreGive(hr_lock);
    vTaskDelayUntil(&last_run, pdMS_TO_TICKS(1800));
  }
}

void setup() {
  Serial.begin(115200);
  delay(1200);
  randomSeed(esp_random());

  hr_lock = xSemaphoreCreateMutex();
  if (!hr_lock) {
    Serial.println("Mutex failed!");
    while (1);
  }

  if (xTaskCreate(read_hr, "Reader", 2000, NULL, 3, &hr_sensor) != pdPASS) {
    Serial.println("Reader task failed!");
    while (1);
  }
  if (xTaskCreate(smooth_hr, "Smoother", 2000, NULL, 2, &hr_processor) != pdPASS) {
    Serial.println("Smoother task failed!");
    while (1);
  }
  if (xTaskCreate(show_hr, "Display", 2000, NULL, 1, &hr_output) != pdPASS) {
    Serial.println("Display task failed!");
    while (1);
  }

  Serial.println("Wearable system online!");
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(9500));
}
