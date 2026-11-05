# Hardware anti-recoil

Disclamer, the readme is vibecoded.

## Hardware

* **Hardware:** ESP32-S3 Development Board.
* **Cables:** 1x  USB Type-C data cable (must carry data lines, not power-only).
* **Software:**
  * [Arduino IDE](https://www.arduino.cc/en/software) (v2.x recommended) with ESP32 platform support installed.
  * Compiled application executable (`.exe`).
  * The firmware file (`.ino`).

---

## 1. Firmware 

1. Connect the ESP32-S3 to your PC using the **UART / COM** port (or put the **USB** port into bootloader mode).
2. Open the `.ino` firmware sketch in the Arduino IDE.
3. Open the **Tools** menu and ensure the following settings are selected:
   * **Board:** `ESP32S3 Dev Module`
   * **USB Mode:** `USB-OTG (TinyUSB)` *(Required for simultaneous CDC serial and HID mouse emulation)*
   * **USB CDC On Boot:** `Enabled`
   * **Upload Mode:** `UART0 / Hardware CDC` (or `USB-OTG CDC (TinyUSB)`)
   * **Port:** Select the active COM port shown for your connected board.
4. **Trigger ROM Bootloader (if the upload fails to connect automatically):**
   * Press and hold the physical **BOOT** button on the ESP32-S3.
   * While holding **BOOT**, press and release the **RESET** (or **EN**) button once.
   * Release the **BOOT** button.
5. Click the **Upload** button (arrow icon).
6. Once the console indicates completion (`Hard resetting via RTS pin...`), press the physical **RESET** button once.

---

## 2. Hardware Setup

1. Unplug the cable from the board.
2. Re-connect the USB-C cable into the board's **native USB** port (labeled `USB`, **not** `UART` or `COM`).
3. Plug the other end directly into a high-speed motherboard USB port on your PC (avoid unpowered USB hubs or keyboard passthrough ports).
4. Tap the board's physical **RESET** button once to boot the sketch cleanly.

---

## 3. Windows Device Verification

1. Open **Device Manager** (`Win + X` $\rightarrow$ **Device Manager**).
2. Expand **Ports (COM & LPT)**:
   * Locate **USB Serial Device (COMx)**.
   * Note down the exact COM port number assigned (e.g., `COM4` or `COM6`).
3. Expand **Mice and other pointing devices**:
   * Confirm that an additional **HID-compliant mouse** appears.
   * *(Optional)* Right-click the mouse $\rightarrow$ **Properties** $\rightarrow$ **Details** $\rightarrow$ select **Bus reported device description** to confirm the spoofed device name (`Logitech G Pro Wireless`).

---

## 4. Connecting the Desktop Application

1. **Important:** Close the Arduino IDE completely, or ensure its **Serial Monitor** is closed. Windows does not allow two applications to access a COM port simultaneously.
2. Launch your application executable (`.exe`).
3. In the application interface:
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