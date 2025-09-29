
const express = require("express");
const { SerialPort } = require("serialport");
const { WebSocketServer } = require("ws");

const app = express();
app.use(express.json());

// ⚠️ Ajusta el puerto según tu sistema (ej. "COM3" en Windows, "/dev/ttyUSB0" en Linux/Mac)
const port = new SerialPort({ path: "COM3", baudRate: 115200 });

// WebSocket para enviar datos en tiempo real a React
const wss = new WebSocketServer({ port: 8080 });

port.on("data", (data) => {
  const mensaje = data.toString();
  console.log("Serial:", mensaje);

  // reenviar a todos los clientes conectados
  wss.clients.forEach((client) => {
    if (client.readyState === 1) {
      client.send(mensaje);
    }
  });
});

// Endpoint para registrar tarjeta desde React
app.post("/register", (req, res) => {
  const { uid, usuario } = req.body;
  // Mandar al ESP32 por serial
  port.write(`REGISTER:${uid}:${usuario}\n`);
  res.json({ ok: true, msg: "Tarjeta enviada al ESP32" });
});

app.listen(3001, () => console.log("Servidor HTTP en http://localhost:3001"));
console.log("WebSocket en ws://localhost:8080");
