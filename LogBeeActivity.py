import tkinter as tk
from tkinter import scrolledtext
import serial
import csv
from datetime import datetime
import threading

ser = None
stop_logging = False

csv_file = 'bee_log.csv'

with open(csv_file, mode='a+', newline='') as file:
    file.seek(0)
    if not file.read(1):
        writer = csv.writer(file)
        writer.writerow(["time", "bee type", "in or out"])

def log_data(gui_output):
    global stop_logging, ser
    try:
        ser = serial.Serial('COM5', 9600)
        gui_output.insert(tk.END, "Logging bee activity...\n")
        gui_output.see(tk.END)

        while not stop_logging:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                gui_output.insert(tk.END, f"Received: {line}\n")
                gui_output.see(tk.END)

                if "Sensor" in line and "Type" in line:
                    parts = line.split(" - ")
                    if len(parts) == 3:
                        sensor = parts[0].strip()
                        bee_type = parts[1].replace("Type ", "").strip()
                        direction = parts[2].strip()
                        now = datetime.now().strftime('%H:%M:%S')

                        with open(csv_file, mode='a', newline='') as file:
                            writer = csv.writer(file)
                            writer.writerow([now, bee_type, direction])
                            gui_output.insert(tk.END, f"Logged: {now}, {bee_type}, {direction}\n")
                            gui_output.see(tk.END)
    except Exception as e:
        gui_output.insert(tk.END, f"Error: {str(e)}\n")
        gui_output.see(tk.END)

def start_logging(gui_output):
    global stop_logging
    stop_logging = False
    threading.Thread(target=log_data, args=(gui_output,), daemon=True).start()

def stop_logging_func(gui_output):
    global stop_logging, ser
    stop_logging = True
    if ser:
        ser.close()
    gui_output.insert(tk.END, "Logging stopped.\n")
    gui_output.see(tk.END)

def gui():
    root = tk.Tk()
    root.title("Bee Activity Log")

    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)
    root.rowconfigure(1, weight=0)
    root.rowconfigure(2, weight=0)

    log_display = scrolledtext.ScrolledText(root, wrap=tk.WORD, font=("Courier", 10))
    log_display.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

    start_button = tk.Button(root, text="Gather Bee Data", command=lambda: start_logging(log_display))
    stop_button = tk.Button(root, text="Stop", command=lambda: stop_logging_func(log_display))
    start_button.grid(row=1, column=0, pady=5, sticky="ew")
    stop_button.grid(row=2, column=0, pady=5, sticky="ew")

    root.mainloop()

gui()
