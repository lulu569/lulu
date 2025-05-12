#include <Arduino.h>
#include "FastDiode.h"
#include <OneButton.h>

// 使用 LEDC PWM 方式
FastDiode led1(8, EPinPolarity::ACTIVE_HIGH, "LED1");
OneButton oneButton(9);

// 按钮点击处理函数
void handleClick() {
    // 关闭LED
    led1.close();
    Serial.println("Button clicked, LED turned off!");
    // 可以在这里添加更多功能
}

void setup() {
    Serial.begin(115200);
    Serial.println("hello,FastDiodel!");
    // 初始化LEDC模式
    led1.init(CHANNEL_0);  // 5KHz PWM
    oneButton.attachClick(handleClick);
    // 设置呼吸灯效果
    led1.breathing(500);  // 500ms周期

}

void loop() {
    oneButton.tick();
    
    

    //  led1.open();
    //  delay(1000);
    //  led1.setBrightness(122);
    //  delay(1000);
    //  led1.flickering(500, 3);
    //  delay(2000);
    //  led1.fodeOn(2000);
    //  delay(2000);
    //  led1.fodeOff(2000);
    //  delay(2000);
    //  led1.breathing(500);
    //  delay(5000);
}