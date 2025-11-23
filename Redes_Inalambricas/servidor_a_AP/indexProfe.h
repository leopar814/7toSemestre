// HTML completo que se guardará en SPIFFS



String htmlPage() {
  String page = R"rawliteral(


<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Monitor de Temperatura - ESP32</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            transition: background 0.5s ease;
        }
        .container {
            background: rgba(255, 255, 255, 0.95);
            padding: 40px;
            border-radius: 20px;
            box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3);
            text-align: center;
            max-width: 500px;
            width: 90%;
        }
        h1 { margin-bottom: 30px; color: #333; font-size: 2em; }
        .temp-display {
            font-size: 5em;
            font-weight: bold;
            margin: 20px 0;
            transition: color 0.3s ease;
        }
        .temp-label { font-size: 1.2em; color: #666; margin-bottom: 30px; }
        .thermometer {
            width: 60px;
            height: 300px;
            margin: 30px auto;
            position: relative;
            background: #f0f0f0;
            border-radius: 30px;
            box-shadow: inset 0 0 10px rgba(0, 0, 0, 0.1);
        }
        .bulb {
            width: 80px;
            height: 80px;
            background: #ff4444;
            border-radius: 50%;
            position: absolute;
            bottom: -10px;
            left: 50%;
            transform: translateX(-50%);
            transition: background 0.5s ease;
        }
        .mercury {
            width: 30px;
            height: 0%;
            background: linear-gradient(to top, #ff4444, #ff8844);
            position: absolute;
            bottom: 35px;
            left: 50%;
            transform: translateX(-50%);
            border-radius: 15px 15px 0 0;
            transition: height 0.5s ease, background 0.5s ease;
        }
        .slider-container { margin: 30px 0; }
        .slider {
            width: 100%;
            height: 10px;
            border-radius: 5px;
            outline: none;
            -webkit-appearance: none;
            background: linear-gradient(to right, #4444ff, #44ff44, #ffff44, #ff8844, #ff4444);
        }
        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: white;
            cursor: pointer;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.3);
        }
        .status {
            font-size: 1.5em;
            font-weight: bold;
            margin: 20px 0;
            padding: 15px;
            border-radius: 10px;
            transition: all 0.3s ease;
        }
        .emoji { font-size: 3em; margin: 10px 0; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🌡️ Monitor ESP32</h1>
        <div class="temp-display" id="tempDisplay">25°C</div>
        <div class="temp-label">Temperatura Actual</div>
        <div class="thermometer">
            <div class="mercury" id="mercury"></div>
            <div class="bulb" id="bulb"></div>
        </div>
        <div class="slider-container">
            <input type="range" min="-10" max="50" value="25" class="slider" id="tempSlider">
        </div>
        <div class="emoji" id="emoji">😊</div>
        <div class="status" id="status">Temperatura Agradable</div>
    </div>
    <script>
        const slider = document.getElementById('tempSlider');
        const tempDisplay = document.getElementById('tempDisplay');
        const mercury = document.getElementById('mercury');
        const bulb = document.getElementById('bulb');
        const status = document.getElementById('status');
        const emoji = document.getElementById('emoji');
        const body = document.body;

        function updateTemperature() {
            const temp = parseInt(slider.value);
            tempDisplay.textContent = temp + '°C';
            const mercuryHeight = ((temp + 10) / 60) * 100;
            mercury.style.height = Math.max(0, Math.min(100, mercuryHeight)) + '%';
            
            if (temp < 0) {
                body.style.background = 'linear-gradient(135deg, #667eea 0%, #764ba2 100%)';
                mercury.style.background = 'linear-gradient(to top, #4444ff, #6666ff)';
                bulb.style.background = '#4444ff';
                tempDisplay.style.color = '#4444ff';
                status.textContent = '¡Congelante!';
                status.style.background = '#e3f2fd';
                status.style.color = '#1565c0';
                emoji.textContent = '🥶';
            } else if (temp < 10) {
                body.style.background = 'linear-gradient(135deg, #89f7fe 0%, #66a6ff 100%)';
                mercury.style.background = 'linear-gradient(to top, #4488ff, #66aaff)';
                bulb.style.background = '#4488ff';
                tempDisplay.style.color = '#4488ff';
                status.textContent = 'Muy Frío';
                status.style.background = '#e1f5fe';
                status.style.color = '#01579b';
                emoji.textContent = '❄️';
            } else if (temp < 18) {
                body.style.background = 'linear-gradient(135deg, #a1c4fd 0%, #c2e9fb 100%)';
                mercury.style.background = 'linear-gradient(to top, #44aaff, #66ccff)';
                bulb.style.background = '#44aaff';
                tempDisplay.style.color = '#44aaff';
                status.textContent = 'Fresco';
                status.style.background = '#e0f7fa';
                status.style.color = '#006064';
                emoji.textContent = '😌';
            } else if (temp < 26) {
                body.style.background = 'linear-gradient(135deg, #ffecd2 0%, #fcb69f 100%)';
                mercury.style.background = 'linear-gradient(to top, #44ff44, #88ff88)';
                bulb.style.background = '#44ff44';
                tempDisplay.style.color = '#22aa22';
                status.textContent = 'Temperatura Agradable';
                status.style.background = '#e8f5e9';
                status.style.color = '#1b5e20';
                emoji.textContent = '😊';
            } else if (temp < 32) {
                body.style.background = 'linear-gradient(135deg, #ff9a56 0%, #fecfef 100%)';
                mercury.style.background = 'linear-gradient(to top, #ffaa44, #ffcc66)';
                bulb.style.background = '#ffaa44';
                tempDisplay.style.color = '#ff8800';
                status.textContent = 'Cálido';
                status.style.background = '#fff3e0';
                status.style.color = '#e65100';
                emoji.textContent = '😅';
            } else if (temp < 38) {
                body.style.background = 'linear-gradient(135deg, #fa709a 0%, #fee140 100%)';
                mercury.style.background = 'linear-gradient(to top, #ff6644, #ff8844)';
                bulb.style.background = '#ff6644';
                tempDisplay.style.color = '#ff4422';
                status.textContent = 'Caliente';
                status.style.background = '#fbe9e7';
                status.style.color = '#bf360c';
                emoji.textContent = '🥵';
            } else {
                body.style.background = 'linear-gradient(135deg, #f093fb 0%, #f5576c 100%)';
                mercury.style.background = 'linear-gradient(to top, #ff4444, #ff2222)';
                bulb.style.background = '#ff4444';
                tempDisplay.style.color = '#ff0000';
                status.textContent = '¡Extremo!';
                status.style.background = '#ffebee';
                status.style.color = '#b71c1c';
                emoji.textContent = '🔥';
            }
        }

        async function saveTemperature() {
            const temp = parseInt(slider.value);
            try {
                await fetch('/settemp?value=' + temp);
            } catch (error) {
                console.log('Error guardando');
            }
        }

        async function loadTemperature() {
            try {
                const response = await fetch('/gettemp');
                const temp = await response.text();
                slider.value = temp;
                updateTemperature();
            } catch (error) {
                console.log('Error cargando');
            }
        }

        slider.addEventListener('input', updateTemperature);
        slider.addEventListener('change', saveTemperature);
        
        loadTemperature();
        updateTemperature();
        setInterval(loadTemperature, 2000);
    </script>
</body>
</html>
)rawliteral";
  return page;
}