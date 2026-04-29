#!/usr/bin/env python3
import serial
import time

UART_PORT = "/dev/ttyACM0"  # UART port on Raspberry Pi 3
BAUD_RATE = 115200

def determine_day_night(ldr_value):
    return "Night" if ldr_value <= 0.5 else "Day"

def main():
    print("Sensor Display Program Started...")
    ser = serial.Serial(UART_PORT, BAUD_RATE, timeout=1)

    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            try:
                parts = line.split(',')
                soil = float(parts[0])
                temp = float(parts[1])
                ldr = float(parts[2])
                print(f"Soil Moisture: {soil:.2f}")
                print(f"Temperature: {temp:.2f} °C")
                print(f"Light Status: {determine_day_night(ldr)}")
                print("-" * 40)
            except Exception as e:
                print("Invalid data:", line)
        time.sleep(1)

if __name__ == "__main__":
    main()
