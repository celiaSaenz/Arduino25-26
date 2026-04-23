# Proyecto: Sistema de Control de Acceso RFID con Servo

Este repositorio contiene una serie de herramientas para trabajar con módulos de lectura/escritura de tarjetas **RFID (RC522)** y un servomotor. El objetivo es proporcionar una base completa que va desde la configuración inicial de una tarjeta hasta la implementación de una cerradura electrónica automatizada.

---

## 📂 Contenido de la Carpeta

Aquí tienes una guía rápida de para qué sirve cada fichero incluido:

| Archivo | ¿Para qué sirve? |
| :--- | :--- |
| **`InicializarTarjeta.ino`** | Se usa la primera vez que tienes una tarjeta nueva. Prepara la estructura interna de la tarjeta para que pueda recibir datos. |
| **`EscribirTarjeta.ino`** | Permite guardar información personalizada dentro de la tarjeta (como un nombre o un código de usuario). |
| **`LeerTarjeta.ino`** | Sirve para verificar qué hay guardado en una tarjeta. Muestra los datos por el Monitor Serie al acercarla al lector. |
| **`AbrirServoUIDTarjeta.ino`** | Es el proyecto final. Identifica el número de serie único de la tarjeta y, si es la correcta, activa un servomotor (ideal para maquetas de puertas o cajas fuertes). |

---

## 🛠️ Esquema de Conexión

En la carpeta correspondiente encontrarás el archivo **`esquemaTarjeta.jpg`**, que muestra cómo conectar los componentes. 

### Resumen de conexiones principales:
* **Módulo RFID:** Se conecta a los pines digitales de comunicación especial (SPI) del Arduino.
* **Servomotor:** Se conecta a un pin digital con capacidad de movimiento (PWM) para controlar la apertura.
* **Alimentación:** Es muy importante conectar el módulo RFID al pin de **3.3V** (¡no a 5V!) para no dañarlo.


---

## 🚀 Requisitos

1. **Hardware:**
   - Arduino Uno (o compatible).
   - Lector RFID-RC522 con tarjeta/llavero.
   - Servomotor estándar.
2. **Software:**
   - Arduino IDE.
   - Librería **MFRC522** (instalar desde el Gestor de Librerías).

---

## 📝 Notas de uso

1. **Paso 1:** Conecta todo según el esquema.
2. **Paso 2:** Usa `LeerTarjeta.ino` para descubrir cuál es el código (UID) de tu tarjeta.
3. **Paso 3:** Copia ese código en `AbrirServoUIDTarjeta.ino` para que el sistema reconozca tu tarjeta como la "llave maestra".
4. **Paso 4:** ¡Carga el código y prueba tu cerradura electrónica!

---