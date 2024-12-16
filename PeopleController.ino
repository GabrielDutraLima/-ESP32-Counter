#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PIR_PIN 4
#define BUZZER_PIN 5
int pirState = LOW;
int contador = 0;

unsigned long lastSendTime = 0; 
unsigned long sendInterval = 5000; 

// Defina o UUID do serviço e da característica
#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-123456789abc"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// Callback para monitorar o estado de conexão
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        Serial.println("Cliente BLE conectado");
    }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        Serial.println("Cliente BLE desconectado");
        BLEDevice::startAdvertising(); 
    }
};

void setup() {
    Serial.begin(115200);
    pinMode(PIR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Inicialização do display OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("Falha na inicialização do OLED"));
        for (;;);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Aguardando movimento...");
    display.display();

    // Configuração do BLE
    BLEDevice::init("ESP32_Sensor");
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    
    // Cria o serviço e a característica
    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ | 
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
    pCharacteristic->addDescriptor(new BLE2902());
    
    // Inicia o serviço e a propaganda BLE
    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("Esperando conexão de um cliente BLE...");
}

void loop() {
    int pirVal = digitalRead(PIR_PIN);

    if (pirVal == HIGH && pirState == LOW) {
        contador++;
        pirState = HIGH;

        // Atualizar display
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.print("Pessoas:");
        display.setCursor(0, 30);
        display.setTextSize(3);
        display.print(contador);
        display.display();

        Serial.print("Contagem atual: ");
        Serial.println(contador);

        // Buzzer opcional
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);

        lastSendTime = millis();
    } else if (pirVal == LOW && pirState == HIGH) {
        pirState = LOW;
    }

    // Enviar dados BLE periodicamente
    if (deviceConnected && (millis() - lastSendTime > sendInterval)) {
        String contadorStr = String(contador);
        pCharacteristic->setValue(contadorStr.c_str());
        pCharacteristic->notify();
        Serial.print("Contagem enviada via BLE: ");
        Serial.println(contadorStr);
        lastSendTime = millis();
    }
}
