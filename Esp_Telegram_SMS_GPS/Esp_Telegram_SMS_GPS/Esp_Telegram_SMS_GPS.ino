#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "shakhawat";  // Replace with your WiFi SSID
const char* password = "14146469";  // Replace with your WiFi password
const char* BOTtoken = "6701536287:AAGWxXDzlKyLR3z125amS4X-oxwrP9Sa2Lw";  // Replace with your bot token
const char* CHAT_ID = "5117068333";  // Replace with your chat ID

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup()
{
  Serial.begin(9600);
  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    a++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "WiFi Connected!", "");
  bot.sendMessage(CHAT_ID, "System has Started!!", "");
}

void loop()
{
  while (Serial.available())
  {
    String data = Serial.readString();
    sendTelegramMessage(data);
    bot.sendMessage(CHAT_ID, "House No: 114 " + data);
  }
}


void sendTelegramMessage(String data)
{
  Serial.println("Received GPS Data: " + data);

  // Add your logic to send data to Telegram bot
  // Example: bot.sendMessage(CHAT_ID, data, "");

  // Now, you can add SMS sending logic here
  // Replace the following line with your SMS sending code
  sendSMS("House No: 114 " + data);
  
}

void sendSMS(String message)
{
  // Add your SMS sending logic here
  // You may use GSM module libraries or other methods
  // Example: Serial.println("Sending SMS: " + message);
}