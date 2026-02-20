# Proyecto: Decodificador de Mandos IR (Elegoo) con Arduino

Este proyecto permite **recibir y decodificar** señales de un **mando a distancia infrarrojo (IR)** usando un **receptor IR** y la librería **IRremote**.  
Cuando pulsas un botón del mando, el Arduino imprime en el **Monitor Serie**:

- El **código IR** en hexadecimal (`0x...`)
- El **nombre del botón** (POWER, VOL+, 1, 2, 3, etc.) según una tabla de mapeo

Además, detecta y gestiona correctamente los **códigos repetidos** (cuando mantienes un botón pulsado).

---

## Materiales

- Arduino Uno / Nano
- 1× Receptor infrarrojo IR (tipo VS1838B o similar)
- 1× Mando IR (por ejemplo el típico de kits Elegoo)
- Cables Dupont
- Protoboard (opcional)

---

## Requisitos

- Arduino IDE
- Librería **IRremote** (la moderna, compatible con `IRrecv` y `decodedIRData`)

### Instalar IRremote
1. Arduino IDE → **Herramientas → Administrar bibliotecas…**
2. Buscar **IRremote**
3. Instalar la librería (autor: Armin Joachimsmeyer)

---

## Montaje

### Conexión del receptor IR
Los receptores IR suelen tener 3 pines:

- **VCC** → 5V
- **GND** → GND
- **OUT / SIG** → **D11** (según el código)

En este proyecto se usa:
- `int receiver = 11;` → la señal del receptor va al **pin digital 11**.

> Nota: algunos módulos tienen los pines en distinto orden. Si no funciona, revisa el datasheet o el serigrafiado del módulo (VCC/GND/OUT).

---

## Cómo usar

1. Conecta el receptor IR al Arduino.
2. Carga el sketch en la placa.
3. Abre **Herramientas → Monitor Serie** a **9600 baudios**.
4. Pulsa botones del mando apuntando al receptor.
5. Verás en el Monitor Serie:
   - El código IR en formato `0x...`
   - La traducción a nombre de botón (POWER, 0, 1, 2, VOL+, etc.)

---

## Explicación del código (sin incluir el código)

### 1) Inclusión de la librería
Se usa `IRremote.h`, que aporta las funciones para:
- inicializar el receptor
- decodificar señales IR
- acceder al resultado decodificado (`decodedIRData`)

---

### 2) Pin de entrada del receptor
Se define una variable con el pin donde está conectada la señal del receptor:

- `receiver = 11`

Esto permite cambiar fácilmente el pin si lo necesitas.

---

### 3) Creación del objeto receptor IR
Se crea un objeto `IRrecv` asociado al pin de entrada.  
Este objeto es el que:
- escucha señales IR
- decodifica los paquetes recibidos

---

### 4) Gestión de códigos repetidos (REPEAT)
Muchos mandos, cuando **mantienes pulsado** un botón, no envían el mismo código completo continuamente: envían un **código “repeat”**.

Para solucionarlo, el programa:
- guarda el **último código válido** en `last_decodedRawData`
- si detecta que el paquete actual es un repeat (`decodedIRData.flags`), reemplaza el valor actual por el último código guardado
- imprime `REPEAT!` para indicar que es repetición

Resultado: aunque mantengas pulsado, el programa sigue interpretando el botón correcto.

---

### 5) Impresión del código IR
Si no es repetición, se imprime en el Monitor Serie el valor recibido en hexadecimal:

- `IR code:0x...`

Esto es útil para:
- comprobar que el receptor funciona
- obtener códigos para mapear botones nuevos

---

### 6) Traducción del código a botón (switch-case)
El núcleo del proyecto es un `switch` que compara el código recibido con valores conocidos.

Ejemplo:
- Si recibe `0xBA45FF00` → imprime `"POWER"`
- Si recibe `0xF30CFF00` → imprime `"1"`
- etc.

Si el código no está en la lista, se muestra `"other button"`.

Esta parte se puede ampliar para:
- añadir tu propio mando
- controlar dispositivos (LEDs, servo, relés, etc.) en vez de solo imprimir texto

---

### 7) Ciclo principal (loop)
En el `loop()` el programa:
1. Comprueba si ha llegado una señal (`irrecv.decode()`)
2. Si llegó, llama a la función que traduce e imprime (`translateIR()`)
3. Luego llama a `irrecv.resume()` para “limpiar” el receptor y prepararlo para el siguiente código

---

## Personalización / Ideas de ampliación

- Encender/apagar un LED con POWER
- Subir/bajar brillo con VOL+ / VOL-
- Controlar un servo con UP/DOWN
- Guardar comandos para controlar un robot por IR

---

## Solución de problemas

- **No aparece nada en el Monitor Serie**
  - Revisa que el baud rate esté en **9600**
  - Verifica el pin de señal: está configurado en **D11**
  - Comprueba el orden de pines del receptor IR (VCC/GND/OUT)
  - Acerca el mando al receptor (10–30 cm) para probar

- **Los botones no coinciden con los nombres**
  - Tu mando puede usar otros códigos: mira el `IR code:0x...` y sustituye/añade casos en el `switch`

---