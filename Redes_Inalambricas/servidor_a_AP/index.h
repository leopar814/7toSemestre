// HTML completo que se guardará en SPIFFS

String htmlPage() {
  String page = R"rawliteral(


<!doctype html>
<html lang="es">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <title>Página de ejemplo — Mi Mini Sitio</title>
  <style>
    :root{--bg:#0f1724;--card:#111827;--accent:#06b6d4;--muted:#9ca3af;color-scheme:dark}
    *{box-sizing:border-box}
    body{margin:0;font-family:Inter, system-ui, -apple-system, "Segoe UI", Roboto, "Helvetica Neue", Arial;background:linear-gradient(180deg,#071025 0%, #0f1724 100%);color:#e6eef6;line-height:1.4}
    .container{max-width:900px;margin:32px auto;padding:20px}
    header{display:flex;align-items:center;justify-content:space-between}
    h1{margin:0;font-size:1.6rem}
    nav a{color:var(--muted);text-decoration:none;margin-left:14px;font-size:0.95rem}

    .hero{background:linear-gradient(90deg,rgba(6,182,212,0.08),transparent);padding:18px;border-radius:12px;margin-top:18px}
    .grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(220px,1fr));gap:14px;margin-top:16px}
    .card{background:var(--card);padding:14px;border-radius:10px;box-shadow:0 6px 18px rgba(2,6,23,0.6)}
    .small{font-size:0.85rem;color:var(--muted)}
    button{background:var(--accent);border:0;padding:8px 12px;border-radius:8px;color:#042023;cursor:pointer;font-weight:600}
    input[type="text"],input[type="email"]{width:100%;padding:8px;border-radius:8px;border:1px solid rgba(255,255,255,0.06);background:transparent;color:inherit}
    footer{opacity:0.8;margin-top:20px;font-size:0.85rem}
    .logo{display:flex;gap:10px;align-items:center}
    .logo .mark{width:38px;height:38px;border-radius:9px;background:linear-gradient(135deg,var(--accent),#7c3aed);display:flex;align-items:center;justify-content:center;font-weight:700;color:#00262a}
    .hint{color:var(--muted);font-size:0.9rem;margin-top:8px}
  </style>
</head>
<body>
  <div class="container">
    <header>
      <div class="logo">
        <div class="mark">M</div>
        <div>
          <h1>Mini Sitio</h1>
          <div class="small">Ejemplo rápido — HTML + CSS + JS</div>
        </div>
      </div>
      <nav>
        <a href="#about">Acerca</a>
        <a href="#projects">Proyectos</a>
        <a href="#contact">Contacto</a>
      </nav>
    </header>

    <section class="hero" id="about">
      <h2>Hola 👋 Bienvenido</h2>
      <p class="hint">Esta es una página de ejemplo con secciones sencillas. Puedes editar el contenido, los colores o añadir más interacción.</p>
      <div style="margin-top:12px;display:flex;gap:10px;flex-wrap:wrap">
        <button onclick="toggleTheme()">Cambiar tema</button>
        <button onclick="alert('Gracias por probar la página :)')">Probar acción</button>
      </div>
    </section>

    <section class="grid" id="projects">
      <article class="card">
        <h3>Proyecto: Calculadora simple</h3>
        <p class="small">Una calculadora pequeña para sumar y restar. Ideal para practicar DOM y eventos.</p>
        <div style="margin-top:10px">
          <button onclick="openDemo('calc')">Abrir demo</button>
        </div>
      </article>

      <article class="card">
        <h3>Proyecto: Lista de tareas</h3>
        <p class="small">Una lista donde agregar tareas rápidas — guarda en memoria de sesión.</p>
        <div style="margin-top:10px">
          <button onclick="openDemo('todo')">Abrir demo</button>
        </div>
      </article>

      <article class="card">
        <h3 id="contact">Suscripción</h3>
        <p class="small">Recibe una notificación (simulada) al suscribirte.</p>
        <div style="margin-top:8px">
          <input id="email" type="email" placeholder="tu@correo.com" />
          <div style="height:8px"></div>
          <button onclick="subscribe()">Suscribirme</button>
        </div>
      </article>
    </section>

    <footer>
      <div class="small">Hecho con ❤ — usa este archivo como base para tu proyecto.</div>
    </footer>
  </div>

  <script>
    function toggleTheme(){
      const r=document.documentElement.style;
      if(document.documentElement.getAttribute('data-light')==='true'){
        document.documentElement.removeAttribute('data-light');
        alert('Tema oscuro');
      } else {
        document.documentElement.setAttribute('data-light','true');
        alert('Tema claro (simulado) - modifica CSS para un tema claro real');
      }
    }

    function subscribe(){
      const e=document.getElementById('email').value.trim();
      if(!e) return alert('Ingresa un correo válido');
      alert('Gracias — hemos registrado ' + e + ' (simulado)');
      document.getElementById('email').value='';
    }

    function openDemo(name){
      if(name==='calc'){
        prompt('Demo calculadora\nIngresa expresión simple (ej: 2+3):','2+3');
      } else if(name==='todo'){
        const task=prompt('Agregar tarea (demo):','Aprender algo nuevo');
        if(task) alert('Tarea agregada: ' + task + ' (simulado)');
      }
    }
  </script>
</body>
</html>
)rawliteral";
  return page;
}