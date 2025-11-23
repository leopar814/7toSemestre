#include <WiFi.h>
#include <WebSocketsServer.h>
#include <index.h>


// ----- Configuración AP -----
const char* ssid = "MiESP32_BERENICE";
const char* password = "jp1234567";

// ----- Servidores -----
WiFiServer httpServer(80);        // Servidor HTTP para servir la página
WebSocketsServer webSocket = WebSocketsServer(81);  // Servidor WebSocket en el puerto 81

// ----- Hardware -----
const int pinRelay1 = 12;  // Pin a controlar
String message = "";

// ----- Prototipos -----
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

String htmlPage();

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(pinRelay1, OUTPUT);
  digitalWrite(pinRelay1, LOW); // Inicialmente apagado


  // Crear punto de acceso
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println();
  Serial.print("AP creado. IP del ESP32: ");
  Serial.println(IP);

  // Iniciar servidor HTTP
  httpServer.begin();
  Serial.println("Servidor HTTP iniciado en puerto 80");

  // Iniciar WebSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket iniciado en puerto 81");
}

void loop() {
  // Manejar clientes HTTP (sirve la página)
  WiFiClient client = httpServer.available();
  if (client) {
    Serial.println("Cliente HTTP conectado");
    // Esperar hasta que haya datos del cliente (con timeout pequeño)
    unsigned long start = millis();
    while (!client.available() && (millis() - start) < 1000) {
      delay(1);
    }

    // Leer petición (no necesitamos parsear todo para este ejemplo)
    String req = client.readStringUntil('\r');
    Serial.println("Petición HTTP: " + req);
    client.flush();

    // Responder con la página HTML
    String page = htmlPage();
   
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html; charset=UTF-8");
    client.println("Connection: close");
    client.println("Content-Length: " + String(page.length()));
    client.println();
    client.print(page);

    delay(1);
    client.stop();
    Serial.println("Cliente HTTP desconectado");
  }

  // Manejar WebSocket (loop no bloqueante)
  webSocket.loop();
}

// -----------------------
// Manejador de eventos WebSocket
// -----------------------

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("Cliente WS %u desconectado.\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("Cliente WS %u conectado desde %s\n", num, ip.toString().c_str());
      // Enviar estado inicial al cliente
  
      break;
    }
    case WStype_TEXT: {
      String message = String((char*)payload);
      Serial.printf("Mensaje WS de %u: %s\n", num, message.c_str());

      // Ejemplo: mensajes esperados: "toggle", "on", "off", "ping"
   if (message == "on1") {
      digitalWrite(pinRelay1, HIGH);
      webSocket.sendTXT(num, "Pin 23 encendido");
    }
    else if (message == "off1") {
      digitalWrite(pinRelay1, LOW);
      webSocket.sendTXT(num, "Pin 23 apagado");
    }
    else {
      webSocket.sendTXT(num, "Comando no reconocido");
    }
      break;
    }
    default:
      break;
  }
}
// -----------------------

