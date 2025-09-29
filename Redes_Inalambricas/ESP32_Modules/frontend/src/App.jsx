import { useEffect, useState } from "react";

function App() {
  const [logs, setLogs] = useState([]);
  const [uid, setUid] = useState("");
  const [usuario, setUsuario] = useState("");

  useEffect(() => {
    const ws = new WebSocket("ws://localhost:8080");
    ws.onmessage = (event) => {
      setLogs((prev) => [...prev, event.data]);
    };
    return () => ws.close();
  }, []);

  const registrarTarjeta = async () => {
    await fetch("http://localhost:3001/register", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ uid, usuario }),
    });
    setUid("");
    setUsuario("");
  };

  return (
    <div style={{ padding: 20 }}>
      <h2>Salida Serial ESP32</h2>
      <div style={{ background: "#111", color: "#0f0", padding: 10, width: 500, height: 200, overflowY: "scroll" }}>
        {logs.map((linea, i) => (
          <div key={i}>{linea}</div>
        ))}
      </div>

      <h2>Registrar Tarjeta RFID</h2>
      <input value={uid} onChange={(e) => setUid(e.target.value)} placeholder="UID" />
      <input value={usuario} onChange={(e) => setUsuario(e.target.value)} placeholder="Usuario" />
      <button onClick={registrarTarjeta}>Registrar</button>
    </div>
  );
}

export default App;