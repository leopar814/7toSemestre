// src/components/Modal.jsx

export default function Modal({ isOpen, onClose, modoModal,  setPassword, passwordValid, modalMessage, signup }) {
  if (!isOpen) return null;

  return (
    <div className="fixed inset-0 flex items-center justify-center backdrop-blur-sm z-50">
      <div className="bg-gray-800 p-7 rounded-lg w-80 text-center shadow-xl">
        <h2 className="text-white text-xl font-bold mb-4">{modoModal === "signup" ? modalMessage : ""}</h2>
        
        { modoModal === "signup" &&(
        <div>
          <input
            type="password"
            onChange={(e) => setPassword(e.target.value)}
            className="bg-gray-100 border rounded text-black p-1"
          />
          <button
              className="mt-6 px-5 py-2 bg-blue-600 hover:bg-blue-400 rounded"
              onClick={() => {
                  signup();
              }}
          >
            Enviar
          </button>
        </div>
      )}

      {modoModal === "resultado" && (
        <div>
          <p className={`mb-4 text-xl ${passwordValid ? "text-green-400" : "text-red-400"}`}>
            {passwordValid ? "✅ Acceso concedido" : "❌ Contraseña incorrecta"}
          </p>
          <button
            className="mt-2 px-5 py-2 bg-gray-600 hover:bg-gray-500 rounded w-full"
            onClick={onClose}
          >
            Cerrar
          </button>
        </div>
      )}
      </div>
    </div>
    
  );
}
