
# 📊 **Projeto ESP32-Counter**

Este projeto realiza a **contagem** utilizando um **ESP32** com sensor PIR e exibe as informações em tempo real. A comunicação é feita via **Bluetooth BLE**.

---

## 🚀 **Funcionalidades**

1. **ESP32**:
   - Lê os dados do sensor PIR para detectar movimento.
   - Ativa um buzzer a cada detecção.
   - Envia a contagem via Bluetooth BLE.

2. **Aplicativo Mobile** (React Native):
   - Conecta-se ao ESP32 via Bluetooth BLE.
   - Recebe os dados de contagem em tempo real.
   - Exibe os valores no display do aplicativo.

---

## 🛠️ **Tecnologias Utilizadas**

- **Hardware**:
  - ESP32
  - Sensor PIR HC-SR501
  - Buzzer (Opcional)

- **Software**:
  - **ESP32**:
    - Arduino IDE
    - Biblioteca Bluetooth BLE (ESP32)
    - Biblioteca Adafruit SSD1306 (para display OLED)


## 📱 **Funcionamento do Aplicativo**

1. **Botão de Conexão**: 
   - Inicia o escaneamento e se conecta ao ESP32 via Bluetooth.

2. **Exibição da Contagem**:
   - Mostra a quantidade detectadas.

3. **Status**:
   - Mostra se o dispositivo está conectado.

---

## 📸 **Capturas de Tela**

- Tela do Aplicativo com contagem de pessoas exibida.
- Conexão BLE ativa.

---

## 💡 **Possíveis Melhorias**

- Integração com banco de dados para registrar as contagens.
- Implementação de notificações quando a capacidade máxima for atingida.
- Suporte para dispositivos iOS.

---

## 📄 **Licença**

Este projeto é de uso livre para fins educacionais e pessoais.

---

