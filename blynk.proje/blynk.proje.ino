#define BLYNK_TEMPLATE_ID "TMPL66Fn37910"  //BLYNK'den gelen kütüphaneler 
#define BLYNK_TEMPLATE_NAME "sıcaklık ve nem"
#define BLYNK_AUTH_TOKEN "Pv3GyWtY4ZXZRpSeUSCTjPG3ZDq41NO1"
#define BLYNK_PRINT Serial
#include <WiFi.h>  //Wifi kütüphanesi
#include <BlynkSimpleEsp32.h>
#include <DHT.h> //sensörün kütüphanesi

char auth[] = BLYNK_AUTH_TOKEN;  //Blynk'in interneti tanıması için gerekli bilgilerin tanımlanması
char ssid[] = "SeydaInt";  // wifi adı
char pass[] = "aresko06";  // wifi şifresi
BlynkTimer timer;

#define DHTPIN 4 //takılacak pinin tanımlanması
#define DHTTYPE DHT11 //sensörün türünün tanımlanması
DHT dht(DHTPIN, DHTTYPE);

void sendSensor()   //Değerlerin alınması için yazılan fonksiyon
{
  float h = dht.readHumidity(); //float cinsinden nemin alınması
  float t = dht.readTemperature(); // float cinsinden sıcaklığın celcius değerlerinin alınması 
  if (isnan(h) || isnan(t)) {  //alınan değerlerin sayısal değer olmaması durumu
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
    Blynk.virtualWrite(V0, t); //sıcaklığın blynk'teki sanal pinlere bağlanması
    Blynk.virtualWrite(V1, h); //nemin blynk'teki sanal pinlere bağlanması
    Serial.print("Temperature : ");  //ekrana yazdırma işlemleri
    Serial.print(t);
    Serial.print("  Humidity : ");
    Serial.println(h);
}
void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, sendSensor);
 
  }
void loop() //programın sürekli çalışması için loop fonksiyonu
{
  Blynk.run();
  timer.run();
 }
