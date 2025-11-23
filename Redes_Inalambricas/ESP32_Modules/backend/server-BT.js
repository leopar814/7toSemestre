
const express = require("express");
const cors = require("cors");
const { SerialPort } = require("serialport");
const { WebSocketServer } = require("ws");
const { ReadlineParser } = require("@serialport/parser-readline");


const app = express();
app.use(cors());
app.use(express.json());

// Asignación de puerto y baud
const port = new SerialPort({ path: "COM5", baudRate: 115200 }); // Debe conectarse al "Saliente"

// WebSocket para enviar datos en tiempo real a React
const wss = new WebSocketServer({ port: 8080 });

const parser = port.pipe(new ReadlineParser({ delimiter: "\n" }));
parser.on("data", (line) => {
  const mensaje = line.trim();
  console.log("Serial:", mensaje);

  const payload = JSON.stringify({ type: "serial", message: mensaje, ts: Date.now() });
  
  // reenviar a todos los clientes conectados
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(payload);
    }
  });
});

// // Endpoint para registrar tarjeta desde React
// app.post("/register", (req, res) => {
//   const { uid, usuario } = req.body || {};
//   if (!uid || !usuario) return res.status(400).json({ ok:false, error: "uid y usuario requeridos" });
//   // Mandar al ESP32 por serial
//   port.write(`REGISTER:${uid}:${usuario}\n`, (err) => {
//     if (err) {
//       console.error("Error al escribir:", err);
//       return res.status(500).json({ ok:false, error: err.message });
//     }
//     res.json({ ok: true, msg: "Tarjeta enviada al ESP32" });
//   });
// });

// Nuevo endpoint genérico
app.post("/send", (req, res) => {
  const { mensaje } = req.body;
  port.write(mensaje + "\n"); // manda al ESP32
  res.json({ ok: true });
});

app.post("/signup", (req, res) => {
  const { password } = req.body;
  if (password == 1234) 
    res.json({ ok: true, msg: "Contraseña correcta (modo dev)"  });
  else 
    res.json({ ok: false,  msg: "Contraseña incorrecta"  });
});


app.listen(3001, () => console.log("Servidor HTTP en http://localhost:3001"));
console.log("WebSocket en ws://localhost:8080");
