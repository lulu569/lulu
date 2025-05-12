
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// 定义 Wi-Fi 网络信息
const char *ssid = "Redmi K60 Pro";
const char *pwd = "yjk1234567";

// 心知天气 API 相关配置
const String xz_api_key = "2";                                  // 心知 API 秘钥
const String city = "fujianFuzhou";                                             // 城市名称
const String weather_api_url = "https://api.seniverse.com/v3/weather/now.json"; // 天气 API URL

// 创建一个动态 JSON 文档，大小为 1024 字节
DynamicJsonDocument doc(1024);

// WiFi 连接函数
void connectToWiFi()
{
    Serial.print("正在连接到 Wi-Fi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pwd);

    // 等待 Wi-Fi 连接成功
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("\n连接成功！");
    Serial.print("本地 IP 地址: ");
    Serial.println(WiFi.localIP());
}

// 获取天气信息的函数
int getWeather()
{
    // 构建完整的 API 请求 URL
    String url = weather_api_url + "?key=" + xz_api_key + "&location=" + city + "&language=zh-Hans&unit=c";

    // 初始化 HTTP 客户端
    HTTPClient http;
    http.begin(url);

    // 发送 GET 请求
    int httpResponseCode = http.GET();

    // 检查 HTTP 响应码
    if (httpResponseCode != HTTP_CODE_OK)
    {
        Serial.printf("GET 请求失败，HTTP 状态码: %d, 错误信息: %s\n", httpResponseCode, http.errorToString(httpResponseCode).c_str());
        http.end(); // 关闭 HTTP 连接
        return -1;
    }

    // 获取响应内容
    String response = http.getString();
    Serial.printf("API 响应: [%s]\n", response.c_str());

    // 解析 JSON 响应
    DeserializationError error = deserializeJson(doc, response);
    if (error)
    {
        Serial.printf("JSON 解析失败: %s\n", error.c_str());
        http.end(); // 关闭 HTTP 连接
        return -1;
    }

    // 提取并打印天气信息
    if (doc["results"].size() > 0)
    {
        JsonObject result = doc["results"][0];

        // 提取位置信息
        JsonObject location = result["location"];
        const char *path = location["path"];
        Serial.printf("地理位置: %s\n", path);

        // 提取当前天气信息
        JsonObject now = result["now"];
        const char *text = now["text"];
        const char *temperature = now["temperature"];
        Serial.printf("天气状况: %s\n", text);
        Serial.printf("当前温度: %s°C\n", temperature);

        // 提取最后更新时间
        const char *lastUpdate = result["last_update"];
        Serial.printf("最后更新时间: %s\n", lastUpdate);
    }
    else
    {
        Serial.println("API 响应中没有找到有效的天气数据");
        return -1;
    }

    // 关闭 HTTP 连接
    http.end();
    return 0;
}

void setup()
{
    // 初始化串口通信
    Serial.begin(115200);
    delay(1000); // 等待串口初始化完成

    // 连接到 Wi-Fi
    connectToWiFi();
}

void loop()
{
    // 每隔 60 秒获取一次天气信息
    if (getWeather() == 0)
    {
        Serial.println("天气信息获取成功！");
    }
    else
    {
        Serial.println("天气信息获取失败！");
    }

    // 等待 60 秒后再次获取天气信息
    delay(60000);
}
