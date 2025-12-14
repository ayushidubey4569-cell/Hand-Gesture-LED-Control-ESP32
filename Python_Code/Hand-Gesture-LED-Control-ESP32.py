import cv2
import mediapipe as mp
import requests
import time

ESP32_IP = "http://192.168.29.84"

mp_hands = mp.solutions.hands
hands = mp_hands.Hands(
    max_num_hands=1,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.7
)
mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

last_sent = -1
current_gesture = -1
gesture_start = 0

GESTURE_HOLD = 0.6   # seconds


def count_fingers(lm):
    fingers = 0
    tips = [8, 12, 16, 20]

    for tip in tips:
        if lm[tip].y < lm[tip - 2].y:
            fingers += 1

    if lm[4].x < lm[3].x:  # Right hand thumb
        fingers += 1

    return fingers


while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    result = hands.process(rgb)

    if result.multi_hand_landmarks:
        hand = result.multi_hand_landmarks[0]
        lm = hand.landmark
        fingers = count_fingers(lm)

        if fingers < 0 or fingers > 5:
            continue

        cv2.putText(frame, f"Fingers: {fingers}", (20, 50),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

        if fingers != current_gesture:
            current_gesture = fingers
            gesture_start = time.time()

        else:
            if time.time() - gesture_start >= GESTURE_HOLD:
                if fingers != last_sent:
                    try:
                        if fingers == 0:
                            requests.get(f"{ESP32_IP}/OFF", timeout=0.4)
                        else:
                            requests.get(f"{ESP32_IP}/F{fingers}", timeout=0.4)
                        last_sent = fingers
                    except:
                        pass

        mp_draw.draw_landmarks(frame, hand, mp_hands.HAND_CONNECTIONS)

    cv2.imshow("Cumulative Gesture LED Control", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()
