# 🏭 The Hoocha System

A Linux-based proof-of-concept simulator that models a network of production machines communicating with a central server, including support for fault injection and system monitoring.

## 📁 Project Structure

```
Hoochamacallit/
├── DC/               # Data Creator
│   ├── src/
│   ├── bin/
│   └── Makefile
├── DR_DX/            # Data Reader & Data Corruptor (shared folder)
│   ├── src/
│   ├── bin/
│   └── Makefile
├── COMMON/           # Shared Resources used in DC, DR, DX
│   ├── src/
│   ├── bin/
│   └── Makefile
├── Makefile          # Top-level Makefile
└── README.md         # Project documentation
```
---

## 🛠️ Technologies & Tools Used

| Area                     | Tool/Concept                         |
|--------------------------|--------------------------------------|
| Operating System         | Linux                                |
| Programming Language     | C (Modular design required)          |
| Build System             | Makefiles (per component + top-level)|
| IPC Mechanism (DC → DR)  | System V Message Queues              |
| IPC Mechanism (DR ↔ DX)  | System V Shared Memory               |
| Logging                  | Plaintext logs in `/tmp/` directory  |
| Stress Testing           | DX process simulating faults         |

---

## 🧱 Components

### 🔹 Data Creator (`DC`)
- Simulates production machines.
- Sends status messages (via message queue) to `Data Reader`.
- Waits for queue availability before sending.
- Generates random status codes (0–6), including:
  - `0`: Everything is OKAY
  - `6`: Machine is Off-line (causes DC to exit)
- Sleeps randomly (10–30s) between messages.
- Logs activity to `/tmp/dataCreator.log`.

### 🔹 Data Reader (`DR`)
- Acts as the backend server.
- Creates and owns the message queue and shared memory.
- Receives messages from `DC` processes.
- Maintains a master list of active DCs in shared memory.
- Removes DCs that are:
  - Non-responsive (35+ seconds of silence)
  - Sent an "Off-line" message
- Shuts down gracefully when all DCs are gone.
- Logs activity to `/tmp/dataMonitor.log`.

### 🔹 Data Corruptor (`DX`)
- Attaches to shared memory to learn active DCs.
- Randomly executes one of 21 actions from the "Wheel of Destruction":
  - Terminate specific DCs using `SIGHUP`
  - Delete the message queue
  - Do nothing
- Logs activity to `/tmp/dataCorruptor.log`.

---

## 📄 Log File Locations

| Component | Log File Path            | Description                            |
|-----------|--------------------------|----------------------------------------|
| DC        | `/tmp/dataCreator.log`   | Message status sent to DR              |
| DR        | `/tmp/dataMonitor.log`   | All events regarding DC tracking       |
| DX        | `/tmp/dataCorruptor.log` | Actions taken during fault simulation  |

---

## ✅ Compilation Instructions

From the root project folder:

```bash
make        # Builds all components: DC, DR, DX
