#include <GyverSegment.h>
#include <SoftwareSerial.h>

#define sclk 5
#define rclk 6
#define dio 7

#define softwareRX 2
#define softwareTX 3

SoftwareSerial espSerial(softwareRX, softwareTX);

Disp595_4 disp(dio, sclk, rclk);
uint8_t value;

int readIntegerFromUART(SoftwareSerial &serial) {
  int number = 0;
  bool isNegative = false;

  while (serial.available()) {
    char c = serial.read();

    if (c == '-') { 
      isNegative = true; // Обробка від'ємного числа
    } else if (c >= '0' && c <= '9') { 
      number = number * 10 + (c - '0'); // Формування числа
    } else if (c == '\n' || c == '\r') { 
      // Кінець числа (можна замінити на свій роздільник)
      break; 
    }
  }

  return isNegative ? -number : number;
}

void setup() {
  espSerial.begin(9600);
  disp.clear();
}

void loop() {
  if (espSerial.available()) {
    value = readIntegerFromUART(espSerial);
    if (aboba != 0) {
      disp.clear();
      disp.setCursor(0);
      disp.print(value);
      disp.update();
    }
  }

  disp.tick();
}
