#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Galaxy A122959";
const char* password = "Apaandah";
const char* namaserver = "http://192.168.100.132:5000/post";  //ipv4 nya

DHT dht(26, DHT11);

void setup() {
  // kode awal mulai
  Serial.begin(115200);

  //Connect to Wifi
  WiFi.begin(ssid, password);
  Serial.print("menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("terhubung ke WiFi");
  dht.begin();  // memulai sensor
}


void loop() {
  // kode utama
  float suhu = dht.readTemperature();  //membaca suhu
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(namaserver);
    http.addHeader("Content-Type", "application/json");
    String jsonP = "{\"suhu\":" + String(suhu) + "}";

    //Send HTTP POST request
    int httpKodeRespon = http.POST(jsonP);

    if (httpKodeRespon > 0) {
      String respon = http.getString();
      Serial.print("http Kode Respon: ");
      Serial.println(httpKodeRespon);
      Serial.print("respon: ");
      Serial.print(respon);
    } else {
      Serial.print("Error dalam mengirim POST :");
      Serial.println(httpKodeRespon);
      Serial.print("penjelasan eror :");
      Serial.println(http.errorToString(httpKodeRespon).c_str());
    }
    http.end();

  } else {
    Serial.println("Error dalam koneksi WiFi");
  }

  //menunjukkan nilai sensor
  Serial.print("suhu:");
  Serial.print(suhu);
  Serial.print("C");
  delay(1200);  // menunggu 1,2 detik sebelum diulang
}
