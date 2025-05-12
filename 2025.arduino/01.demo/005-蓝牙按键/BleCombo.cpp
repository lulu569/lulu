#include <Arduino.h>
#include "BleCombo.h"
// 定义按键和指示灯的引脚
const int BUTTON_PIN = 0;
const int LED_PIN = 11; // 假设 GPIOB 对应引脚 11，根据实际情况修改

BleComboKeyboard Keyboard("BLE KEYBOARD");
BleComboMouse Mouse(&Keyboard);

// 记录上一次按键状态
int lastButtonState = HIGH;

// ... 其余代码保持不变 ...