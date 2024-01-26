#include <WiFi.h>
#include <PubSubClient.h>
#include "Grove_Temperature_And_Humidity_Sensor.h"

#define DHTTYPE DHT11
#define DHTPIN 15

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "<ssid>";
const char* password = "<password>";

const char* mqtt_server = "172.10.10.1";
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_password = "";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Gestion des messages recu ici
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32-Clement", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temp_hum_val[2] = {0};

  if (!dht.readTempAndHumidity(temp_hum_val)) {
    char tempString[8];
    char humString[8];
    dtostrf(temp_hum_val[1], 4, 1, tempString);
    dtostrf(temp_hum_val[0], 4, 1, humString);

    String topic = "temperature";
    topic += "/esp32";
    client.publish(topic.c_str(), tempString);

    topic = "humidity";
    topic += "/esp32";
    client.publish(topic.c_str(), humString);

    Serial.println("Data sent to MQTT broker");
  } else {
    Serial.println("Failed to get temperature and humidity value.");
  }

  delay(5000); // Envoyer les données toutes les 15 secondes
}
