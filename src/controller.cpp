#include <Arduino.h>

#include "hw_config.h"

/* controller is GPIO */
#if defined(HW_CONTROLLER_GPIO)

extern "C" void controller_init()
{
  // pinMode(HW_CONTROLLER_GPIO_UP, INPUT_PULLUP);
  // pinMode(HW_CONTROLLER_GPIO_DOWN, INPUT_PULLUP);
  // pinMode(HW_CONTROLLER_GPIO_LEFT, INPUT_PULLUP);
  // pinMode(HW_CONTROLLER_GPIO_RIGHT, INPUT_PULLUP);
  pinMode(HW_CONTROLLER_GPIO_UP_DOWN, INPUT);
  pinMode(HW_CONTROLLER_GPIO_LEFT_RIGHT, INPUT);
  pinMode(HW_CONTROLLER_GPIO_SELECT, INPUT_PULLUP);
  pinMode(HW_CONTROLLER_GPIO_START, INPUT_PULLUP);
  pinMode(HW_CONTROLLER_GPIO_A, INPUT_PULLUP);
  pinMode(HW_CONTROLLER_GPIO_B, INPUT_PULLUP);
}

extern "C" uint32_t controller_read_input()
{
  uint32_t u, d, l, r, s, t, a, b, x, y;
  int joyY = analogRead(HW_CONTROLLER_GPIO_UP_DOWN);
  int joyX = 4095 - analogRead(HW_CONTROLLER_GPIO_LEFT_RIGHT);

  Serial.printf("joyX: %d, joyY: %d\n", joyX, joyY);

  if (joyY > 2048 + 1024)
  {
    u = 1;
    d = 0;
  }
  else if (joyY < 1024)
  {
    u = 0;
    d = 1;
  }
  else
  {
    u = 1;
    d = 1;
  }

  if (joyX > 2048 + 1024)
  {
    l = 1;
    r = 0;
  }
  else if (joyX < 1024)
  {
    l = 0;
    r = 1;
  }
  else
  {
    l = 1;
    r = 1;
  }

  // u = digitalRead(HW_CONTROLLER_GPIO_UP);
  // d = digitalRead(HW_CONTROLLER_GPIO_DOWN);
  // l = digitalRead(HW_CONTROLLER_GPIO_LEFT);
  // r = digitalRead(HW_CONTROLLER_GPIO_RIGHT);

  s = digitalRead(HW_CONTROLLER_GPIO_SELECT);
  t = digitalRead(HW_CONTROLLER_GPIO_START);
  a = digitalRead(HW_CONTROLLER_GPIO_A);
  b = digitalRead(HW_CONTROLLER_GPIO_B);
  
  Serial.printf("u:%d, d:%d, l:%d, r:%d", u, d, l, r);
  //Serial.printf("u:%d, d:%d, l:%d, r:%d, s:%d, t:%d, X:%d, Y:%d, A:%d, B:%d\n", u, d, l, r, s, t, x, y, a, b);  
  return 0xFFFFFFFF ^ ((!u << 0) | (!d << 1) | (!l << 2) | (!r << 3) | (!s << 4) | (!t << 5) | (!a << 6) | (!b << 7) | (!x << 8) | (!y << 9));
}


#else /* no controller defined */

extern "C" void controller_init()
{
  Serial.printf("GPIO controller disabled in menuconfig; no input enabled.\n");
}

extern "C" uint32_t controller_read_input()
{
  return 0xFFFFFFFF;
}

#endif /* no controller defined */
