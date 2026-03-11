# TV-Typewriter

Homage to the legendary **TV Typewriter (1973)** by Don Lancaster, recreated with an **Arduino Nano** and a small **analog keypad**.

This project generates **composite video output** directly from the Arduino and lets you type characters that appear on a television screen, similar to the original homebrew video terminal.

---

# Hardware

## Parts

- **Arduino Nano**  
https://www.dfrobot.com/product-67.html?tracking=hOuIhw4fDaJRTdy4abz04npbQC78dqxBkqVt7XMFYxEXj2s0ukWgm71wbut0ewUP

- **Analog Keypad**  
(use **3 keypads** for the complete alphabet)  
https://www.dfrobot.com/product-2267.html?tracking=hOuIhw4fDaJRTdy4abz04npbQC78dqxBkqVt7XMFYxEXj2s0ukWgm71wbut0ewUP

- 1 × **330 Ω resistor**  
- 1 × **1 kΩ resistor**  
- 1 × **RCA connector**

---

# Wiring

Build the **TVOut cable** according to the following diagram.

![TVOut schematic](https://github.com/user-attachments/assets/e3879ecc-4cd1-432f-9554-80093f0daf6a)

### Pin connections

| Signal | Arduino Pin |
|------|------|
| SYNC | D7 |
| VIDEO | D9 |
| Keypad output | A0 |
| GND | GND |

The RCA connector goes to the **composite VIDEO IN** of the TV.

---

# Software

## 1. Install TVOut Library

Install the **TVOut** library in the Arduino IDE.

Then copy the folder:

```
TVOutFonts
```

into:

```
Arduino/libraries/
```

---

## 2. Upload the code

Upload the provided **.ino sketch** to the Arduino Nano.

---

## 3. Connect the TV

Connect the **RCA cable** to the **VIDEO IN** port of your TV.

After reset, characters typed on the keypad will appear on the screen.

---

# Notes

- One keypad provides **10 keys**.
- To cover the full alphabet you can connect **three keypads** and map additional characters in the sketch.
- The video signal is **composite NTSC**, generated directly by the Arduino using the **TVOut** library.

---

# Contact

**Roni Bandini**

LinkedIn  
https://www.linkedin.com/in/ronibandini/

Instagram  
https://www.instagram.com/ronibandini/
