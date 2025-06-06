from flask import Flask, jsonify
import threading
import serial

# ========== CONFIG ==========
PORT = "COM4"       # Set your actual ESP32 COM port
BAUD = 115200
# ============================

app = Flask(__name__)
DATA = {"roll": 0.0, "pitch": 0.0, "yaw": 0.0}

def serial_reader():
    global DATA
    try:
        ser = serial.Serial(PORT, BAUD, timeout=1)
        print(f"🔌 Connected to {PORT}")
    except Exception as e:
        print(f"❌ Could not open {PORT}: {e}")
        return

    while True:
        try:
            raw = ser.readline().decode(errors="ignore").strip()
            if raw:
                print(f"📥 Received: {raw}")  # ADD THIS LINE

            if raw.startswith("EULER"):
                parts = raw.split(",")
                if len(parts) == 4:
                    roll  = float(parts[1])
                    pitch = float(parts[2])
                    yaw   = float(parts[3])
                    DATA.update({"roll": roll, "pitch": pitch, "yaw": yaw})
        except Exception as e:
            print(f"⚠️ Serial read error: {e}")


@app.route("/data")
def get_data():
    return jsonify(DATA)

if __name__ == "__main__":
    threading.Thread(target=serial_reader, daemon=True).start()
    print("🌐 Server running at http://localhost:5000/data")
    app.run(host="0.0.0.0", port=5000)
