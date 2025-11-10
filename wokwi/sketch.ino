#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define DHT_PIN 15
#define LED_VERMELHO 12
#define LED_AZUL 14
#define LED_VERDE 27
#define DHTTYPE DHT22

DHT dht(DHT_PIN, DHTTYPE);

const char* ssid = "Wokwi-GUEST";  
const char* password = "";          
const char* mqttServer = "test.mosquitto.org";
int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// ------------------------  Wi-Fi ------------------------
void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ------------------------ MQTT ------------------------
void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32_BemEstar")) {
      Serial.println("Conectado");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 2s");
      delay(2000);
    }
  }
}

// ------------------------ ULTRASSÔNICO ------------------------
float lerDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracao * 0.034 / 2; // em centímetros
  return distancia;
}

// ------------------------ DHT22 ------------------------
void lerDHT(float &temperatura, float &umidade) {
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
}

// ------------------------ VOID SETUP ------------------------
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  dht.begin();
  conectarWiFi();
  client.setServer(mqttServer, mqttPort);
  conectarMQTT();

  Serial.println("Sistema de Bem-Estar no Trabalho iniciado.");
}

// ------------------------ VOID LOOP ------------------------
void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();

  float distancia = lerDistancia();
  float temperatura, umidade;
  lerDHT(temperatura, umidade);

  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.print(" cm | Temp: ");
  Serial.print(temperatura);
  Serial.print(" °C | Umid: ");
  Serial.print(umidade);
  Serial.println(" %");

  if (distancia < 10) {
    digitalWrite(LED_VERMELHO, HIGH);
  } else {
    digitalWrite(LED_VERMELHO, LOW);
  }

  if (temperatura > 30) {
    digitalWrite(LED_AZUL, HIGH);
    delay(200);
    digitalWrite(LED_AZUL, LOW);
    delay(200);
  } 
  digitalWrite(LED_VERDE, HIGH);

  String payload = String("{\"distancia\":") + distancia +
                   ",\"temperatura\":" + temperatura +
                   ",\"umidade\":" + umidade + "}";
  client.publish("gs/bemestar", payload.c_str());

  delay(2000); 
}
