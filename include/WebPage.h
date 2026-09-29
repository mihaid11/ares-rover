#pragma once

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
  <style>
    body { text-align: center; font-family: Arial; background-color: #222; color: white; margin-top: 30px; user-select: none; }
    .btn { padding: 15px; font-size: 24px; margin: 5px; width: 80px; height: 80px; background-color: #4CAF50; color: white; border: none; border-radius: 15px; touch-action: manipulation;}
    .btn:active { background-color: #45a049; }
    .btn-stop { background-color: #f44336; }
    .btn-stop:active { background-color: #da190b; }
    .slider { width: 80%; margin: 20px 0; }
    .controls { display: inline-block; margin-top: 20px; }
    .telemetry { background-color: #333; padding: 10px; border-radius: 10px; margin: 15px auto; width: 80%; font-size: 14px;}
    .telemetry p { margin: 5px 0; }
    .eco { margin: 25px auto 15px; display: flex; align-items: center; gap: 12px; font-size: 16px; }
    .eco input { width: 45px; height: 24px; }
  </style>
</head>
<body>
  <h2>Ares Rover - RC Mode</h2>

  <div class="telemetry">
    <p>Viteza: <span id="speedVal">150</span></p>
    <p>Obstacol: Fata <span id="distF">--</span> cm | Spate <span id="distB">--</span> cm</p>    
    <p>Baterie: <span id="batVal">--</span>% (<span id="voltVal">--</span> V)</p>
    <p>Consum: <span id="currVal">--</span> mA | <span id="powVal">--</span> mW</p>
    <p>Temp: <span id="tempVal">--</span> &deg;C | Umid: <span id="humVal">--</span> %</p>
    <p>Acc: X:<span id="ax">--</span> Y:<span id="ay">--</span> Z:<span id="az">--</span></p>
    <p>Gyr: X:<span id="gx">--</span> Y:<span id="gy">--</span> Z:<span id="gz">--</span></p>
  </div>

  <input type="range" id="speed" class="slider" min="80" max="255" value="150">

  <div class="controls">
    <div>
      <button class="btn" ontouchstart="send('F')" ontouchend="send('S')" onmousedown="send('F')" onmouseup="send('S')">W</button>
    </div>
    <div>
      <button class="btn" ontouchstart="send('L')" ontouchend="send('S')" onmousedown="send('L')" onmouseup="send('S')">A</button>
      <button class="btn btn-stop" ontouchstart="send('S')" onmousedown="send('S')">STOP</button>
      <button class="btn" ontouchstart="send('R')" ontouchend="send('S')" onmousedown="send('R')" onmouseup="send('S')">D</button>
    </div>
    <div>
      <button class="btn" ontouchstart="send('B')" ontouchend="send('S')" onmousedown="send('B')" onmouseup="send('S')">S</button>
    </div>
  </div>

  <div class="eco">
    <span>Eco Mode</span>
    <input type="checkbox" id="ecoToggle" onchange="toggleEco()">
  </div>

  <script>
    var speedSlider = document.getElementById("speed");
    var speedVal = document.getElementById("speedVal");

    speedSlider.oninput = function() { speedVal.innerHTML = this.value; }

    function send(dir) {
      fetch("/action?dir=" + dir + "&speed=" + speedSlider.value);
    }

    var eco = false;
    var timers = [];

    function toggleEco() {
      eco = document.getElementById("ecoToggle").checked;
      fetch("/eco?state=" + (eco ? 1 : 0));

      timers.forEach(clearInterval);
      timers = [];

      timers.push(setInterval(function() {
        fetch("/distance").then(r => r.json()).then(data => {
          document.getElementById("distF").innerHTML = data.f;
          document.getElementById("distB").innerHTML = data.b;
        });
      }, eco ? 300 : 100));

      timers.push(setInterval(function() {
        fetch("/power").then(r => r.json()).then(data => {
          document.getElementById("voltVal").innerHTML = data.v;
          document.getElementById("currVal").innerHTML = data.c;
          document.getElementById("powVal").innerHTML = data.p;
          document.getElementById("batVal").innerHTML = data.b;
        });
      }, eco ? 3000 : 700));

      timers.push(setInterval(function() {
        fetch("/env").then(r => r.json()).then(data => {
          document.getElementById("tempVal").innerHTML = data.t;
          document.getElementById("humVal").innerHTML = data.h;
        });
      }, eco ? 10000 : 2000));

      timers.push(setInterval(function() {
        fetch("/inertial").then(r => r.json()).then(data => {
          document.getElementById("ax").innerHTML = data.ax;
          document.getElementById("ay").innerHTML = data.ay;
          document.getElementById("az").innerHTML = data.az;
          document.getElementById("gx").innerHTML = data.gx;
          document.getElementById("gy").innerHTML = data.gy;
          document.getElementById("gz").innerHTML = data.gz;
        });
      }, eco ? 2000 : 500));
    }

    toggleEco();
  </script>
</body>
</html>
)rawliteral";
