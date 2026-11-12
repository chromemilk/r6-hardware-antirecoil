# Hardware anti-recoil/Mouse Macro

## Requirements

* **Hardware:** ESP32-S3 Development Board. [Pre-Assembled Board](https://www.amazon.com/ESP32-S3-N16R8-Development-Board-Flash/dp/B0GVSKY8C5/ref=sr_1_9_so_SINGLE_BOARD_COMPUTER?sr=8-9) If you do not use this link, I recommend looking for boards that have the pins pre-installed  
* **Cables:** 1x  USB Type-C data cable (must carry data lines, not power-only).
* **Software:**
  * [Arduino IDE](https://www.arduino.cc/en/software) you must then install the ESP32 development kit
  * Install the ESP32 dev kit [Video Guide](https://www.youtube.com/watch?v=ikBlhX-erSw), or use AI 
  * Compiled application executable 
  * The firmware file

---

## ESP32 Setup

1. Connect the ESP32-S3 to your PC using the COM port 
2. Open the `.ino` firmware sketch in the Arduino IDE.
3. Open the **Tools** menu at the top and ensure the following settings are selected:
   * **Board:** `ESP32S3 Dev Module`
   * **USB Mode:** `USB-OTG (TinyUSB)` 
   * **USB CDC On Boot:** `Enabled`
   * **Upload Mode:** USB-OTG CDC (TinyUSB)
   * **Port:** Select the active COM port shown for your connected board.
4. Click the **Upload** button (arrow icon).
6. Once the console indicates completion (`Hard resetting via RTS pin...`), press the physical **RESET** button once.

---

## Hardware Setup

1. Plug a type-C USB cable into the USB port
2. Plug  the other end into the PC (the board should light up)
---

## Finding the COM port (hardest part)

1. Open Device Manager
2. Click 'view' and then click 'devices by container'
3. You should see a section for usb/port/COM devices/Mice and other pointing devices, click the dropdowns until you see the Arduino board pop up
4. You should see the COM port that is being used. I.E COM1,COM2,COM3


---

## Program Usafe

1. **Important:** Close the Arduino IDE completely, or ensure its **Serial Monitor** is closed. Windows does not allow two applications to access a COM port simultaneously.
2. Launch the  executable
3. In the application :
   * Enter your active COM port identifier into the **COM Port** field in the misc section (e.g., `COM4`).
   * Choose the delay option, setting low to none may cause the program to freeze if packets are lost but are faster response
   * Click **Connect To esp32**.
   * Click **Test Connection**.
   * Set the bypass type to hardware
   * Enable the anti-cheat bypass setting in the main menu
4. The status indicator should turn **Green (Connected)**. The application is now transmitting movement commands via serial to the ESP32-S3, which dispatches them to Windows as genuine hardware HID reports.

---

## 5. Troubleshooting

| Symptom | Probable Cause | Corrective Action |
| :--- | :--- | :--- |
| **"Access is Denied" / COM Port Busy** | Port is held open by another program. | Close the Arduino Serial Monitor or background instances of your `.exe` in Task Manager. Unplug and replug the USB cable to reset OS handles. |
| **"Disconnected" Status on Test** | Flow control or port string mismatch. | Double-check that the COM number in the UI matches Device Manager. Ensure `fDtrControl = DTR_CONTROL_ENABLE` is applied in the software configuration. |
| **No COM Port on the "USB" Port** | Built under the wrong USB mode. | Re-flash the board with **Tools $\rightarrow$ USB Mode** set to `USB-OTG (TinyUSB)` and **USB CDC On Boot** set to `Enabled`. |
| **Board not detected at all** | Power-only cable or stuck state. | Test with a known data cable. Press the **RESET** button once, or enter bootloader mode to re-flash. |


Or just make a issue in the repo
