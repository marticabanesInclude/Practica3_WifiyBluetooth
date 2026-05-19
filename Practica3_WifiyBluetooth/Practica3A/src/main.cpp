#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// --- CONFIGURACIÓN DE RED ---
const char* ssid = "Nautilus"; 
const char* password = "20000Leguas"; 

WebServer server(80);

String getHTML() {
  String html = "<!DOCTYPE html><html lang='en-US'>";
  html += "<head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Ever Dream This ESP32?</title>";
  
  html += "<style>";
  // Estética de "This Man" (Tipografía y colores base)
  html += "body { margin: 0; overflow-x: hidden; background: #fff; font-family: 'Open Sans', sans-serif; text-align: center; }";
  html += "#falling-canvas { position: fixed; top: 0; left: 0; width: 100%; height: 100%; z-index: -1; }";
  
  // Header estilo ThisMan.org
  html += ".header-thisman { background: #636363; color: #ffffff; padding: 20px; border-bottom: 5px solid #000; box-shadow: 0 4px 10px rgba(0,0,0,0.3); }";
  html += ".site-title { font-size: 2em; text-transform: uppercase; margin: 0; letter-spacing: 2px; }";
  html += ".site-description { font-size: 0.8em; font-style: italic; margin-top: 5px; }";
  
  // Contenedor de contenido
  html += ".main-content { background: rgba(255, 255, 255, 0.85); max-width: 600px; margin: 20px auto; padding: 20px; border: 1px solid #ccc; box-shadow: 0 0 20px rgba(0,0,0,0.2); }";
  html += ".portrait { width: 150px; height: auto; border: 4px solid #000; margin: 15px; transition: transform 0.3s; }";
  html += ".portrait:hover { transform: scale(1.1) rotate(5deg); }";
  
  // Variables ESP32
  html += ".esp-data { background: #f0f0f0; border-left: 5px solid #636363; padding: 10px; text-align: left; margin: 10px 0; font-family: monospace; }";
  html += "h2 { color: #333; border-bottom: 2px solid #636363; padding-bottom: 5px; }";
  html += "</style></head><body>";

  // Efecto Falling de fondo
  html += "<canvas id='falling-canvas'></canvas>";

  // Encabezado fusionado
  html += "<div class='header-thisman'>";
  html += "  <p class='site-description'>AQUESTA WEB PERTANY A: CABOSCH_ESP32</p>";
  html += "</div>";

  // Contenido principal
  html += "<div class='main-content'>";
  html += "  <h2>CABOSCH_ESP32</h2>";
  
  html += "  <div class='esp-data'>";
  html += "    <strong>Uptime:</strong> " + String(millis() / 1000) + " seconds<br>";
  html += "    <strong>Memory:</strong> " + String(ESP.getFreeHeap() / 1024) + " KB Free<br>";
  html += "    <strong>Chip:</strong> " + String(ESP.getChipModel()) + "<br>";
  html += "    <strong>IP:</strong> " + WiFi.localIP().toString();
  html += "  </div>";
  
  html += "  <p>Al 2006 van neixer dos upc'rs desde llavors hi han rumors que comentan que viuen dintre del ESP32 server :))).</p>";
  html += "</div>";

  // JavaScript para el efecto de colores infinitos (Falling Falling)
  html += "<script>";
  html += "const canvas = document.getElementById('falling-canvas');";
  html += "const ctx = canvas.getContext('2d');";
  html += "let w, h, colors = [];";
  html += "function init() {";
  html += "  w = window.innerWidth; h = window.innerHeight;";
  html += "  canvas.width = w; canvas.height = h;";
  html += "  for(let i=0; i<15; i++) colors.push(`hsl(${Math.random()*360}, 70%, 60%)`);";
  html += "}";
  html += "let offset = 0;";
  html += "function draw() {";
  html += "  offset += 1.5;";
  html += "  if (offset > 100) { offset = 0; colors.unshift(`hsl(${Math.random()*360}, 70%, 60%)`); colors.pop(); }";
  html += "  for(let i=colors.length-1; i>=0; i--) {";
  html += "    ctx.fillStyle = colors[i];";
  html += "    let size = (i * 100) + offset;";
  html += "    ctx.fillRect(w/2 - size/2, h/2 - size/2, size, size);";
  html += "  }";
  html += "  requestAnimationFrame(draw);";
  html += "}";
  html += "window.onresize = init; init(); draw();";
  html += "</script></body></html>";
  
  return html;
}

void handle_root() {
  server.send(200, "text/html", getHTML());
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("Conectando a la red de los sueños...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConexión establecida.");
  Serial.print("Busca esta IP en tu navegador: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_root);
  server.begin();
}

void loop() {
  server.handleClient();
}