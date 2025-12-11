# 💡 Proyecto: LED Parpadeante

Este proyecto básico para **Arduino Uno** enciende y apaga un LED conectado al pin 13 de forma intermitente. 

---

##  Materiales

- Arduino Uno
- LED
- Resistencia de 220Ω 
- Cables de conexión
- Protoboard 

---

## 🚀 Cómo usar

1. Conecta un LED al pin 13 (ánodo al pin 13 y cátodo a GND).  
2. Abre el archivo `.ino` en Arduino IDE o Web Editor.  
3. Selecciona la placa **Arduino Uno** y el puerto correcto.  
4. Haz clic en **Cargar**.  
5. Observa cómo el LED parpadea según los tiempos programados.

---

## 📚 Explicación

- `pinMode(13, OUTPUT)` configura el pin 13 como salida digital.  
- `digitalWrite(13, HIGH)` enciende el LED.  
- `digitalWrite(13, LOW)` apaga el LED.  
- `delay(ms)` pausa el programa durante los milisegundos indicados.
