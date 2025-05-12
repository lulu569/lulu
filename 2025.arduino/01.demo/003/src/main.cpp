#include <u8g2lib.h>
#include <Wire.h>
#include <Arduino.h>
#include "FastDiode.h"

// 使用 LEDC PWM 方式
FastDiode led1(8, EPinPolarity::ACTIVE_LOW, "LED1");
// 定义屏幕起点的偏移量
#define SCREEN_OFFSET_X 30
#define SCREEN_OFFSET_Y 24

// 创建宏来自动补偿屏幕起点偏移，分别处理X和Y坐标
#define COMPENSATE_X(x) ((x) + SCREEN_OFFSET_X)
#define COMPENSATE_Y(y) ((y) + SCREEN_OFFSET_Y)

// 定义ESP32-C3 OLED开发板与OLED屏幕之间的连接引脚：
// U8G2_SSD1306_128X64_NONAME_F_SW_I2C是构造函数，用于初始化一个基于软件I2C的SSD1306 128x64分辨率的OLED显示屏对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(/* 旋转角度*/ U8G2_R0, /* clock/SCL=*/6, /* data/SDA=*/5, /* reset=*/U8X8_PIN_NONE);

void setup(void)
{
  // 初始化串口通信，波特率为 115200
  Serial.begin(115200);

  // 等待串口初始化完成
  // 等待直到串口准备就绪
  while (!Serial)
  {
  }
  // 打印启动消息
  Serial.println("Serial Test: Ready to send data.");
  u8g2.setContrast(250); // 设置屏幕对比度为250，数值范围通常是0-255
  u8g2.begin();    
  Serial.begin(115200);

    // 初始化 LEDC 模式 (可选)
    led1.init(CHANNEL_0);  // 5KHz PWM

    // 设置呼吸灯效果
    // led1.breathing(500);  // 500ms 周期      // 初始化u8g2对象，开始与OLED显示屏的通信
    led1.flickering(500);
}

void loop(void)
{
  //  // 基础控制
  //   led1.open();                     // 打开 LED
  //   delay(1000);

  //   led1.setBrightness(122);         // 设置亮度 (0-255)
  //   delay(1000);

  //   led1.flickering(500, 3);         // 闪烁3次后恢复
  //   delay(2000);

  //   led1.fodeOn(2000);              // 2秒内渐亮
  //   delay(2000);

  //   led1.fodeOff(2000);             // 2秒内渐暗
  //   delay(2000);

  //   led1.breathing(500);            // 呼吸灯效果
  //   delay(5000);
  // 调用firstPage()开始新的页面绘制
  // 这个函数会清除缓冲区并准备绘制新内容
  u8g2.firstPage();

  // do-while循环确保页面内容被正确绘制
  // nextPage()返回false时表示所有页面都已绘制完毕
  do
  {
    // 创建一个字符串变量str，存储自程序启动以来经过的毫秒数
    String str = String(millis());
    Serial.println(str);
    // 设置字体为u8g2_font_ncenB10_tr，这是一种等宽的粗体10点字体
    u8g2.setFont(u8g2_font_ncenB10_tr);

    // 在屏幕上指定位置绘制字符串
    u8g2.drawStr(COMPENSATE_X(0), COMPENSATE_Y(0) + 10, "lujingshan");
    u8g2.drawStr(COMPENSATE_X(0), COMPENSATE_Y(0) + 20, "--------------------");
    u8g2.drawStr(COMPENSATE_X(0), COMPENSATE_Y(0) + 30, str.c_str());

  } while (u8g2.nextPage()); // 继续绘制下一页，直到所有页都绘制完成
}
