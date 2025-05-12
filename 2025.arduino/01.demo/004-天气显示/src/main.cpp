#include <U8g2lib.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// 定义屏幕起点的偏移量
#define SCREEN_OFFSET_X 30
#define SCREEN_OFFSET_Y 10

// 创建宏来自动补偿屏幕起点偏移
#define COMPENSATE_X(x) ((x) + SCREEN_OFFSET_X)
#define COMPENSATE_Y(y) ((y) + SCREEN_OFFSET_Y)

// Wi-Fi 网络信息
const char *ssid = "iPhone X";
const char *pwd = "1234567890";

// 心知天气 API 配置
const String xz_api_key = "SdgDS_ZfGBegnyfSF";
const String city = "fujianZhangzhou";  // 修改为漳州
const String weather_api_url = "https://api.seniverse.com/v3/weather/now.json";

// JSON 文档
DynamicJsonDocument doc(1024);

// OLED 屏幕对象
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock/SCL=*/6, /* data/SDA=*/5, /* reset=*/U8X8_PIN_NONE);

void connectToWiFi() {
    Serial.print("正在连接到 Wi-Fi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pwd);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("\n连接成功！");
    Serial.print("本地 IP 地址: ");
    Serial.println(WiFi.localIP());
}

int getWeather() {
    String url = weather_api_url + "?key=" + xz_api_key + "&location=" + city + "&language=zh-Hans&unit=c";
    HTTPClient http;
    http.begin(url);

    int httpResponseCode = http.GET();
    if (httpResponseCode != HTTP_CODE_OK) {
        Serial.printf("GET 请求失败，HTTP 状态码: %d\n", httpResponseCode);
        http.end();
        return -1;
    }

    String response = http.getString();
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
        Serial.printf("JSON 解析失败: %s\n", error.c_str());
        http.end();
        return -1;
    }

    http.end();
    return 0;
}

void displayWeather() {
    if (doc["results"].size() > 0) {
        JsonObject result = doc["results"][0];
        JsonObject location = result["location"];
        JsonObject now = result["now"];

        const char *cityName = location["name"];
        const char *weather = now["text"];
        const char *temp = now["temperature"];

        u8g2.firstPage();
        do {
            u8g2.setFont(u8g2_font_wqy12_t_gb2312);
            // 显示地区
            u8g2.drawUTF8(COMPENSATE_X(0), COMPENSATE_Y(0) + 10, "地区:");
            u8g2.drawUTF8(COMPENSATE_X(40), COMPENSATE_Y(0) + 10, cityName);
            // 显示天气
            u8g2.drawUTF8(COMPENSATE_X(0), COMPENSATE_Y(0) + 25, "天气:");
            u8g2.drawUTF8(COMPENSATE_X(40), COMPENSATE_Y(0) + 25, weather);
            // 显示温度
            u8g2.drawUTF8(COMPENSATE_X(0), COMPENSATE_Y(0) + 40, "温度:");
            u8g2.drawUTF8(COMPENSATE_X(40), COMPENSATE_Y(0) + 40, temp);
            u8g2.drawUTF8(COMPENSATE_X(70), COMPENSATE_Y(0) + 40, "°C");
        } while (u8g2.nextPage());
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    u8g2.setContrast(250);
    u8g2.begin();

    connectToWiFi();
}

void loop() {
    if (getWeather() == 0) {
        displayWeather();
    }
    delay(60000);  // 每分钟更新一次
}
