{
  "version": 1,
  "author": "Monalisa",
  "editor": "wokwi",
  "parts": [
    { "type": "board-esp32-devkit-v1", "id": "esp", "top": -50.72, "left": 14.4, "attrs": {} },
    {
      "type": "wokwi-hc-sr04",
      "id": "hcsr04",
      "top": -84.9,
      "left": 149.5,
      "attrs": { "distance": "146" }
    },
    { "type": "wokwi-servo", "id": "servo", "top": 151.6, "left": 192, "attrs": {} },
    {
      "type": "wokwi-led",
      "id": "led_normal",
      "top": -40,
      "left": -100,
      "attrs": { "color": "green", "label": "Normal" }
    },
    {
      "type": "wokwi-led",
      "id": "led_anomaly",
      "top": 20,
      "left": -100,
      "attrs": { "color": "red", "label": "Anomaly" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r_normal",
      "top": -30,
      "left": -40,
      "attrs": { "value": "220" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r_anomaly",
      "top": 30,
      "left": -40,
      "attrs": { "value": "220" }
    }
  ],
  "connections": [
    [ "esp:3V3", "hcsr04:VCC", "red", [] ],
    [ "esp:GND.1", "hcsr04:GND", "black", [] ],
    [ "esp:5", "hcsr04:TRIG", "blue", [] ],
    [ "esp:18", "hcsr04:ECHO", "green", [] ],
    [ "esp:3V3", "servo:VCC", "red", [] ],
    [ "esp:GND.1", "servo:GND", "black", [] ],
    [ "esp:13", "servo:PWM", "orange", [] ],
    [ "esp:2", "r_normal:1", "green", [] ],
    [ "r_normal:2", "led_normal:A", "green", [] ],
    [ "esp:GND.1", "led_normal:C", "black", [] ],
    [ "esp:4", "r_anomaly:1", "red", [] ],
    [ "r_anomaly:2", "led_anomaly:A", "red", [] ],
    [ "esp:GND.1", "led_anomaly:C", "black", [] ],
    [ "hcsr04:TRIG", "esp:D5", "green", [ "v9.6", "h-134.8" ] ],
    [ "hcsr04:ECHO", "esp:D18", "green", [ "v0" ] ],
    [ "servo:PWM", "esp:D13", "green", [ "h0" ] ],
    [ "servo:V+", "esp:VIN", "green", [ "h0" ] ]
  ],
  "dependencies": {}
}
