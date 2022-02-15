#include <Arduino.h>

#include "hw_config.h"

/* controller is GPIO */
#if defined(HW_CONTROLLER_GPIO)

extern "C" void controller_init() {
  pinMode(HW_CONTROLLER_GPIO_UP_DOWN, INPUT);
  pinMode(HW_CONTROLLER_GPIO_LEFT_RIGHT, INPUT);
  pinMode(HW_CONTROLLER_GPIO_SELECT, INPUT_PULLUP);
  pinMode(HW_CONTROLLER_GPIO_START, INPUT_PULLUP);
  pinMode(HW_CONTROLLER_GPIO_A, INPUT_PULLUP);
  pinMode(HW_CONTROLLER_GPIO_B, INPUT_PULLUP);
}

extern "C" uint32_t controller_read_input() {
  // 1 is nothing, 0 is the logical level for the input
  // Left/Right and Up/Down are connected together with a 3 level: 0, 1979, 4085 on analog input.
  uint32_t u, d, l, r, s, t, a, b, x, y;
  int joyY = analogRead(HW_CONTROLLER_GPIO_UP_DOWN);
  int joyX = analogRead(HW_CONTROLLER_GPIO_LEFT_RIGHT);

  //Serial.printf("joyX: %d, joyY: %d\n", joyX, joyY);

  if (joyY > 3072) {
    u = 0;  // up 4095
    d = 1;
  } else if (joyY < 1024) {
    u = 1;  // Low is nothing 0
    d = 1;
  } else {
    u = 1;
    d = 0;  // down 1879
  }

  if (joyX > 3072) {
    l = 1;
    r = 0;  // right 4095
  } else if (joyX < 1024) {
    l = 1;  // low nothing 0
    r = 1;
  } else {
    l = 0;  // left 1872
    r = 1;
  }
  //Serial.printf("u:%d, d:%d, l:%d, r:%d\n", u, d, l, r);

  s = digitalRead(HW_CONTROLLER_GPIO_SELECT);
  t = digitalRead(HW_CONTROLLER_GPIO_START);
  a = digitalRead(HW_CONTROLLER_GPIO_A);
  b = digitalRead(HW_CONTROLLER_GPIO_B);
  x = 1;
  y = 1;
  //Serial.printf("s:%d, t:%d, a:%d, b:%d\n", s, t, a, b);

  // Serial.printf("u:%d, d:%d, l:%d, r:%d, s:%d, t:%d, X:%d, Y:%d, A:%d, B:%d\n", u, d, l, r, s, t, x, y, a, b);
  return 0xFFFFFFFF ^ ((!u << 0) | (!d << 1) | (!l << 2) | (!r << 3) | (!s << 4) | (!t << 5) | (!a << 6) | (!b << 7) | (!x << 8) | (!y << 9));
}

#else /* no controller defined */

extern "C" void controller_init() {
  Serial.printf("GPIO controller disabled in menuconfig; no input enabled.\n");
}

extern "C" uint32_t controller_read_input() {
  return 0xFFFFFFFF;
}

#endif /* no controller defined */
