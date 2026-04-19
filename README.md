# Smart Security Access and Intrusion Detection System

An embedded systems project built on Arduino (simulated in Tinkercad) that models a **realistic security system** with arming/disarming, intrusion detection, entry delay (grace period), and alarm latching.

---

## 📌 Overview

This project implements a **multi-sensor security system** with the help of switches and ir that monitors:

* Door state (open/closed)
* Motion inside a restricted area
* System mode (armed/disarmed)

The system intelligently distinguishes between:

* **Authorized access attempts** (via entry delay)
* **Unauthorized access/intrusions** (immediate or delayed alarm)

It is designed as a **finite state machine (FSM)** integrating with **cooperative scheduling**:

* Event-driven logic
* Time-based control (`millis()`)
* Sensor fusion
* Persistent alarm behavior

---

## 🚀 Features

* 🔐 **Arm / Disarm control**
* 🚪 **Door state detection**
* 🕵️ **Motion detection (PIR sensor)**
* ⏱ **Grace period (entry delay)**
* 🚨 **Alarm latching (persists until reset)**
* 🔁 **Manual reset functionality**
* 🧠 **State-driven system design**

---

## 🧱 System Architecture

### Inputs

| Component         | Description             | Pin |
| ----------------- | ----------------------- | --- |
| Door Sensor       | Detects door open/close | 2   |
| PIR Sensor        | Detects motion          | 3   |
| Reset Button      | Clears alarm state      | 4   |
| Arm/Disarm Switch | Enables/disables system | 5   |

---

### Outputs

| Component  | Description                  | Pin |
| ---------- | ---------------------------- | --- |
| Normal LED | Indicates safe state         | 8   |
| Alarm LED  | Indicates intrusion detected | 9   |

---

## 🔌 Circuit Design

### 🖼 Circuit Diagram

> Add your Tinkercad screenshots below:

#### Full Circuit

![Full Circuit](images/full_circuit.png)

#### Arduino Connections

![Arduino Wiring](images/arduino_wiring.png)

---

## ⚙️ Hardware Configuration

### Door Sensor (Slide Switch - SPDT)

* COM → Pin 2
* One terminal → 5V
* Other terminal → GND
* 10kΩ resistor → Pin 2 → GND

---

### Arm/Disarm Switch (Slide Switch - SPDT)

* COM → Pin 5
* One terminal → 5V
* Other terminal → GND
* 10kΩ resistor → Pin 5 → GND

---

### PIR Sensor

* VCC → 5V
* GND → GND
* OUT → Pin 3

---

### Reset Button

* One side → Pin 4
* Other side → GND
* Uses `INPUT_PULLUP` (no external resistor needed)

---

### LEDs

* Pin → Resistor (220Ω) → LED → GND

---

## 🧠 System Logic (FSM)

The system operates in the following states:

| State       | Description                      |
| ----------- | -------------------------------- |
| DISARMED    | System inactive, no monitoring   |
| ARMED_IDLE  | Monitoring with door closed      |
| ENTRY_DELAY | Door opened, grace period active |
| ALARM       | Intrusion detected               |

---

## 🔄 State Transition Table

| Current Condition            | Next State  | Output Behavior   |
| ---------------------------- | ----------- | ----------------- |
| Disarmed                     | DISARMED    | Normal LED ON     |
| Armed + Door Closed          | ARMED_IDLE  | Normal LED ON     |
| Armed + Motion (door closed) | ALARM       | Alarm LED ON      |
| Armed + Door Opens           | ENTRY_DELAY | Start grace timer |
| ENTRY_DELAY + Motion         | ALARM       | Alarm LED ON      |
| ENTRY_DELAY + Time Expired   | ALARM       | Alarm LED ON      |
| ALARM + Reset                | ARMED_IDLE  | Alarm OFF         |

---

## ⏱ Grace Period Behavior

* Triggered when **door opens while system is armed**
* Default duration: **5 seconds**
* During this time:

  * Motion → triggers alarm
  * No disarm → alarm after timeout

---

## 🧪 Testing Scenarios

| Scenario                 | Expected Result     |
| ------------------------ | ------------------- |
| System disarmed          | No alarm            |
| Motion while door closed | Immediate alarm     |
| Door opened (armed)      | Grace period starts |
| Motion during grace      | Alarm triggered     |
| No motion, grace expires | Alarm triggered     |
| Reset pressed            | Alarm cleared       |

---

## 📂 Project Structure

```
smart-security-access-and-intrusion-detection-system/
├── README.md          
├── code/           
│   ├── smart_security_access1.ino
└── schematic/
|    └── smart-security-access schematic.pdf  
└── screenshots/
```

---

## 🧩 Design Decisions

### Why use a grace period?

To allow **authorized entry** without triggering false alarms.
To also cater for instances where the door is opened for inspection by authorized personnel

### Why latch the alarm?

To ensure intrusions are not missed and require **explicit reset**.

### Why detect motion when door is closed?

To handle **non-door entry attacks** (e.g., window intrusion, perimeter breach).

### Why use an arm/disarm switch?

To simulate **user-controlled system states** without adding keypad complexity.

---

## 🔮 Future Improvements

* 🔢 Keypad-based authentication (PIN entry)
* 🔊 Buzzer for audible alarm
* 📟 LCD display for system feedback
* 🌐 IoT integration (remote monitoring)
* 🧠 TinyML for smarter motion classification

---

## 📚 Learning Outcomes

This project demonstrates:

* Finite State Machine (FSM) design
* Event-driven programming
* Embedded timing using `millis()`
* Sensor integration and signal handling
* Real-world system modeling

---

## 📸 Demo (Optional)

> Add screenshots or GIFs here showing:

* Alarm triggering
* Grace period behavior
* Reset functionality

---

## 📜 License

This project is open-source and available under the MIT License.

---

## 👤 Authors

**Tumwesigye Brian**
Software Engineering | Embedded Systems

**Anyeko Stella**
Software Engineering | Embedded Systems

---

## ⭐ Contributing

Contributions, suggestions, and improvements are welcome!
