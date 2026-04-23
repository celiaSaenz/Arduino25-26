# Proyecto: Coche Propulsado por Motor de Aspas (Hélice)

Este proyecto consiste en un vehículo impulsado por la fuerza del aire generada por un motor con hélices (aspas) controlado por un Arduino. A diferencia de los coches con tracción en las ruedas, este modelo se desplaza por propulsión, similar a un aerodeslizador o un avión.

---

## 📂 Contenido de la Carpeta

En esta carpeta encontrarás dos variantes del código según el comportamiento que desees para el coche:

| Archivo | ¿Para qué sirve? |
| :--- | :--- |
| **`MotorSinPausa.ino`** | El motor se enciende y mantiene una marcha constante. Ideal para carreras de larga distancia o pruebas de velocidad máxima. |
| **`MotorConPausa.ino`** | El motor funciona de forma intermitente (avanza y se detiene). Útil para observar la inercia del coche y ahorrar batería durante las pruebas. |

---

## 🛠️ Conexión del Hardware

El montaje es sencillo, pero requiere atención a la potencia del motor para no dañar el Arduino.

### Componentes necesarios:
* **Arduino Uno** (montado sobre el chasis del coche).
* **Motor DC con hélices / aspas**.
* **Transistor (ej. PN2222)**: Necesario para que el Arduino pueda encender el motor sin quemarse.
* **Diodo de protección**: Para evitar retornos de corriente del motor.
* **Batería externa**: Para dar suficiente fuerza a las aspas.

### Configuración de Pines:
* **Pin Digital 9**: Envía la señal de encendido al motor (a través del transistor).
* **GND**: Conexión común de tierra entre la batería y el Arduino.



---

## 🚀 Cómo ponerlo en marcha

1. **Montaje mecánico:** Asegúrate de que el motor esté bien sujeto al chasis y que las aspas tengan espacio libre para girar sin golpear los cables.
2. **Elección de código:**
   - Si quieres que el coche recorra un pasillo recto sin parar, carga `MotorSinPausa.ino`.
   - Si vas a probarlo en un espacio reducido, carga `MotorConPausa.ino`.
3. **Sentido del aire:** Si el coche se mueve hacia atrás, simplemente intercambia los dos cables del motor para que las aspas giren en sentido contrario y empujen el aire hacia atrás.

---

## ⚠️ Consejos de Seguridad

* **Hélices:** Mantén los dedos alejados de las aspas cuando el Arduino esté encendido.
* **Peso:** Intenta que el coche sea lo más ligero posible (usa cartón o plástico ligero) para que la fuerza del aire sea suficiente para mover el peso del Arduino y las baterías.