# Proyecto: Monitor de Sensor Analógico con Histéresis

Este proyecto utiliza una entrada analógica del Arduino para leer los valores de un sensor (como un potenciómetro o sensor de luz) y mostrar los cambios significativos a través del **Monitor Serie**.  
El objetivo es aprender a filtrar el "ruido" de una señal analógica mediante una técnica de **histéresis**, evitando que el Monitor Serie se sature con variaciones irrelevantes de voltaje.

---

## Materiales

- Arduino Uno
- 1 Potenciómetro (o cualquier sensor analógico)
- Cables de conexión
- Protoboard



---

## Requisitos

- Arduino IDE
- Placa Arduino Uno (o compatible)
- Cable USB de datos

---

## Cómo usar

1. **Conexión:**
   - Conecta los pines extremos del potenciómetro a **5V** y **GND**.
   - Conecta el pin central (señal) al pin analógico **A0** del Arduino.
2. Abre el archivo `.ino` en el Arduino IDE.
3. Configura el **Monitor Serie** a una velocidad de **9600 baudios**.
4. Haz clic en **Cargar**.
5. Mueve el potenciómetro: verás que los datos solo aparecen cuando el giro es lo suficientemente grande como para superar el umbral definido.

---

## Explicación

En los sensores analógicos, es común que el valor fluctúe levemente debido a interferencias eléctricas (ruido). Este código implementa un filtro lógico para ignorar cambios menores.

### Conceptos clave del código:

- **Filtro de Histéresis:**
  La condición `if` compara el valor actual con el anterior (`HistoryValue`). Solo si la diferencia absoluta es mayor a **10**, el programa considera que el cambio es real y lo procesa:
  ```cpp
  if((abs(HistoryValue - value) > 10)) // Simplificación de la lógica del código

- **Uso de `sprintf()` y Buffers:** Para dar formato al texto de salida, se utiliza una matriz de caracteres llamada `printBuffer` junto a la función `sprintf`. Esta técnica es más avanzada y limpia que usar múltiples comandos `Serial.print`, ya que permite construir frases complejas con variables incrustadas en una sola línea de código:
  
  ```cpp
  sprintf(printBuffer, "ADC%d level is %d\n", adc_id, value);

  - **Lectura Analógica (`analogRead`):**
  El microcontrolador del Arduino utiliza un convertidor analógico-digital (**ADC**) para transformar el voltaje físico de entrada (que oscila entre **0V y 5V**) en un número digital procesable por el software. Este valor se representa en una escala de **0 a 1023**.



  > **Nota técnica:** Esta escala de 1024 niveles (2¹⁰) permite que el Arduino detecte cambios de voltaje de aproximadamente **0.0049V (4.9mV)**, lo que proporciona una gran precisión para leer sensores como potenciómetros, fotorresistencias o sensores de temperatura.