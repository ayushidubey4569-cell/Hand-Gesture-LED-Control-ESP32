# Hand Gesture Controlled LED System using ESP32

This project demonstrates a real-time hand gesture recognition system that controls multiple LEDs using an ESP32 microcontroller and Python-based computer vision.

## 🔧 Technologies Used
- ESP32
- Python
- OpenCV
- MediaPipe
- WiFi Web Server

## 📌 Features
- Control LEDs using hand gestures
- Cumulative LED control (number of fingers = number of LEDs ON)
- Real-time response using WiFi
- Auto OFF when hand is closed

## 🖐 Gesture Mapping
| Fingers | Action |
|-------|--------|
| 1 | LED1 ON |
| 2 | LED1 + LED2 ON |
| 3 | LED1 + LED2 + LED3 ON |
| 4 | LED1–LED4 ON |
| 5 | LED1–LED5 ON |
| 0 | All LEDs OFF |

## ⚙️ Hardware Required
- ESP32 Dev Module
- 5 LEDs
- 5 × 220Ω resistors
- Jumper wires
- Breadboard

## ▶️ How to Run
1. Upload ESP32 code using Arduino IDE
2. Note the ESP32 IP address
3. Update IP in Python file
4. Run Python script:
   ```bash
   python hand_gesture_control.py

## 📷 Output
Hand gestures are detected via webcam and LEDs respond accordingly.

## 👩‍💻 Author
Ayushi Kumari 
Aadrika Dikshit
Akansha singh
Electronics and Communication Engineering 
