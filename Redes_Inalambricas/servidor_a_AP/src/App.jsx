import { useEffect, useState, useRef } from "react";
import Header from "./components/Header";
import Modal from "./components/Modal";

function App() {
  const [logs, setLogs] = useState([]);
  const [input, setInput] = useState("");
  const [modo, setModo] = useState("usuario"); // "admin", "usuario"
  const [modoComando, setModoComando] = useState(null); // "pass", "usuario", null
  const [connected, setConnected] = useState(true);
  const [modalMessage, setModalMessage] = useState(null);
  const [modoModal, setModoModal] = useState("signup");
  const [password, setPassword] = useState("");
  const [passwordValid, setPasswordValid] = useState(false);

  const bottomRef = useRef(null);


  useEffect(() => {
    const ws = new WebSocket("ws://localhost:8080");

    ws.onmessage = (event) => {
      const data = JSON.parse(event.data);
      const mensaje = data.message.trim();
      setLogs((prev) => [...prev, mensaje]);

      if (mensaje.includes("Introduce contraseña")) {
          setModoComando("pass");
        } else if (mensaje.includes("Ingresa nombre de usuario")) {
          setModoComando("usuario");
        } else if (
          mensaje.includes("Contraseña incorrecta") ||
          mensaje.includes("Usuario agregado correctamente.") ||
          mensaje.includes("No hay espacio")
        ) {
          setModoComando(null);
        }
      if(mensaje.includes("Contraseña correcta")) {
            setModo("admin");
            console.log(modo, modoComando);
          }
      };
      

    return () => ws.close();
  }, []);

  useEffect(() => {
    bottomRef.current?.scrollIntoView({ behavior: "smooth" });
  }, [logs]);


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

  const abrirModalSignup = () => {
    setModoModal("signup");
    setModalMessage("Ingrese contraseña de administrador");
  };

  const signup = async(e) => {
    if (!password.trim()) return;

    const res = await fetch("http://localhost:3001/signup", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ password }),
    });

    const json = await res.json();

    setModoModal("resultado");

    if (json.ok) {
      setModalMessage(json.msg || "Acceso concedido");
      setModo("admin");
      setPasswordValid(true);
    }
    else {
      setModalMessage(json.msg || json.error || "Contraseña inválida");
      setPasswordValid(false);
    }

  }

  return (
    <div>
      <Modal // Ingreso de password
        isOpen={modalMessage}
        onClose={() => setModalMessage(null)}
        modoModal={modoModal}
        setPassword={setPassword}
        passwordValid={passwordValid}
        modalMessage={modalMessage}
        signup={signup}
      />  
      <Header
        abrirModalSignup={abrirModalSignup}
        modo={modo}
        setModo={setModo}
      />
      <div>
        <div className="flex justify-between items-center mx-5 mb-5">
          <button 
            className={
              `border rounded px-4 h-12 mb-2 ${connected === true ? "bg-gray-300 hover:bg-gray-400" : "bg-emerald-50 hover:bg-green-200"}`
            }
          >
            {connected === false ? "Conectar" : "Desconectar"}
          </button>
          { modo == "admin" ? <button className="h-16 border rounded px-4 py-2 bg-emerald-50 hover:bg-green-200 mb-2">Tarjetas registradas</button>
            : null
          }
        </div>
        <div className="flex flex-col items-center">
          <div className="relative bg-gray-900 text-gray-100 w-[60vw] h-100 rounded-xl mb-3 mx-5 overflow-y-auto">
            {logs.map((linea, i) => (
              <div
                className="text-lg"
                key={i}
              >
                {linea}
              </div>
            ))}
            <div ref={bottomRef} />
            { !connected && logs.length === 0 &&
              <div className="absolute inset-0 flex items-center justify-center">
                <span className="text-4xl text-gray-700">Logs</span>
              </div>
            }
          </div>
          <div>
            <input
              value={input}
              onChange={(e) => setInput(e.target.value)}
              placeholder={
                modoComando === "pass"
                  ? "Contraseña admin"
                  : modoComando === "usuario"
                  ? "Nombre de usuario"
                  : "Escribir comando"
              }
            />
            <button className="border rounded-lg w-20 p-1 hover:bg-gray-300" onClick={enviar}>
              Enviar
            </button>
          </div>
        </div>
      </div>

    </div>
  );
}

export default App;