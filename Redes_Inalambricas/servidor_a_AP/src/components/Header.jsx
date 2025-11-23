import usuario from "/user.png";
import admin from "/adminUser.png";

export default function Header({ modo, setModo, abrirModalSignup }) {
  return (
    <header className="flex w-full bg-gray-100 justify-between header p-5 mb-5">
        <h1 className="text-3xl">Conexión ESP32</h1>
        <div className="flex gap-5">
            <button 
                className="border rounded p-2 bg-blue-100 hover:bg-blue-300"
                onClick={() => {
                    if (modo === "admin")
                        setModo("usuario");
                    else
                        abrirModalSignup();
                    }}
            >
                {modo === "admin" ? "Modo usuario" : "Modo Administrador"}
            </button>
            <button className="">
                <img src={modo === "admin" ? admin : usuario} alt="modo de interfaz" className="w-10 h-10" />
            </button>
        </div>
    </header>
  )
}

