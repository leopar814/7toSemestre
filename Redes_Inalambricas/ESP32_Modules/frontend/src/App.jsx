// import { useEffect, useState } from "react";

// function App() {
//   const [logs, setLogs] = useState([]);
//   const [input, setInput] = useState("");
//   const [uid, setUid] = useState("");
//   const [usuario, setUsuario] = useState("");

//   useEffect(() => {
//     const ws = new WebSocket("ws://localhost:8080");

//     ws.onmessage = (event) => {
//       const data = JSON.parse(event.data);
//       const mensaje = event.data.trim();
//       setLogs((prev) => [...prev, mensaje]);
//       console.log("Mensaje:", data);
//     };
//     return () => ws.close();
//   }, []);

//   const registrarTarjeta = async () => {
//     await fetch("http://localhost:3001/register", {
//       method: "POST",
//       headers: { "Content-Type": "application/json" },
//       body: JSON.stringify({ uid, usuario }),
//     });
//     setUid("");
//     setUsuario("");
//   };

//   return (
//     <div style={{ padding: 20 }}>
//       <h2>Salida Serial ESP32</h2>
//       <div style={{ background: "#111", color: "#0f0", padding: 10, width: 500, height: 200, overflowY: "scroll" }}>
//         {logs.map((linea, i) => (
//           <div key={i}>{linea}</div>
//         ))}
//       </div>

//       <h2>Registrar Tarjeta RFID</h2>
//       <input value={uid} onChange={(e) => setUid(e.target.value)} placeholder="UID" />
//       <input value={usuario} onChange={(e) => setUsuario(e.target.value)} placeholder="Usuario" />
//       <button onClick={registrarTarjeta}>Registrar</button>
//     </div>
//   );
// }

// export default App;


import { useEffect, useState } from "react";

function App() {
  const [logs, setLogs] = useState([]);
  const [input, setInput] = useState("");
  const [modo, setModo] = useState(null); // "pass", "usuario", null

  useEffect(() => {
    const ws = new WebSocket("ws://localhost:8080");

    ws.onmessage = (event) => {
      const mensaje = event.data.trim();
      setLogs((prev) => [...prev, mensaje]);

      // Detectar prompts del ESP32
      if (mensaje.includes("Introduce contraseña admin")) {
        setModo("pass");
      } else if (mensaje.includes("Ingresa nombre de usuario")) {
        setModo("usuario");
      } else if (
        mensaje.includes("Contraseña incorrecta") ||
        mensaje.includes("Usuario agregado correctamente.") ||
        mensaje.includes("No hay espacio")
      ) {
        setModo(null);
      }
    };

    return () => ws.close();
  }, []);

  const enviar = async () => {
    if (!input.trim()) return;
    await fetch("http://localhost:3001/send", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ mensaje: input }),
    });
    setLogs((prev) => [...prev, "> " + input]);
    setInput("");
  };

  return (
    <div style={{ padding: 20 }}>
      <h1 className="text-xl">Salida Serial ESP32</h1>
      <div
        // style={{
        //   background: "#111",
        //   color: "#0f0",
        //   padding: 10,
        //   width: 500,
        //   height: 300,
        //   overflowY: "scroll",
        //   fontFamily: "monospace",
        // }}
        className="bg-gray-900 text-gray-100 w-full h-80"
      >
        {logs.map((linea, i) => (
          <div key={i}>{linea}</div>
        ))}
      </div>

      {modo === "pass" && <h3>Ingrese contraseña admin:</h3>}
      {modo === "usuario" && <h3>Ingrese nombre de usuario:</h3>}

      <div style={{ marginTop: 10 }}>
        <input
          value={input}
          onChange={(e) => setInput(e.target.value)}
          placeholder={
            modo === "pass"
              ? "Contraseña admin"
              : modo === "usuario"
              ? "Nombre de usuario"
              : "Escribir comando"
          }
        />
        <button className="border rounded-lg w-20 p-1 hover:bg-gray-300" onClick={enviar}>Enviar</button>
      </div>
    </div>
  );
}

export default App;


