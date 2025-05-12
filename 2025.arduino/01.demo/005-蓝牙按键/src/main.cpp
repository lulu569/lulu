#include <Arduino.h>
#include "BleComboGlobal.h"

// 定义按键和指示灯的引脚
const int BUTTON_PIN = 9;
const int LED_PIN = 11; // 假设 GPIOB 对应引脚 11，根据实际情况修改

// 记录上一次按键状态
int lastButtonState = HIGH;

void setup() {
  // 初始化按键引脚为输入模式
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // 初始化指示灯引脚为输出模式
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // 初始状态指示灯熄灭

  // 初始化蓝牙键盘
  Keyboard.begin();
}

void loop() {
  // 读取按键状态
  int buttonState = digitalRead(BUTTON_PIN);

  // 检查蓝牙是否已连接
  if (Keyboard.isConnected()) {
    digitalWrite(LED_PIN, HIGH); // 蓝牙连接时指示灯亮起

    // 检查按键是否按下
    if (buttonState != lastButtonState && buttonState == LOW) {
      // 按键按下，蓝牙键盘发送音量减按键
      Keyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
  } else {
    digitalWrite(LED_PIN, LOW); // 蓝牙未连接时指示灯熄灭
  }

  // 更新上一次按键状态
  lastButtonState = buttonState;

  delay(50); // 简单的消抖延时
}
