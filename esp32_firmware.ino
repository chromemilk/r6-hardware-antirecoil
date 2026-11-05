#include "USB.h"
#include "USBHIDMouse.h"

USBHIDMouse Mouse;

#pragma pack(push, 1)
struct MovePacket {
  uint8_t header; // 0xAA
  int8_t  dx;     // -127 to 127
  int8_t  dy;     // -127 to 127
};
#pragma pack(pop)

void setup() {
  USB.VID(0x046D);                 // Logitech VID
  USB.PID(0xC539);                 // LIGHTSPEED Receiver PID (Composite mouse + serial safe)
  USB.productName("Logitech G Pro Wireless");
  USB.manufacturerName("Logitech");
  USB.serialNumber("100000000001");

  Serial.begin(115200);
  Mouse.begin();

  USB.begin();
}

void loop() {
  if (Serial.available() > 0) {
    uint8_t header = Serial.peek();

    if (header == 0xFF) {
      Serial.read();
      Serial.write(0xFE);
      Serial.flush();
      return;
    }

    if (Serial.available() >= sizeof(MovePacket)) {
      if (header == 0xAA) {
        MovePacket pkt;
        Serial.readBytes((char*)&pkt, sizeof(MovePacket));

        if (pkt.dx != 0 || pkt.dy != 0) {
          Mouse.move(pkt.dx, pkt.dy);
        }
      } else {
        Serial.read();
      }
    }
  }
}