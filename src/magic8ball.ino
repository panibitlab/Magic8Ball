#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include <PNGdec.h>
#include "bg.h"

#include <Fonts/FreeMonoOblique9pt7b.h>

#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST   4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const int fortune_num = 5;
const int tilt = 21;

PNG png;

int pngDraw(PNGDRAW *pDraw) {
  
  uint16_t lineBuffer[160];

  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_LITTLE_ENDIAN, 0xFFFFFFFF);
  tft.drawRGBBitmap(0, pDraw->y, lineBuffer, pDraw->iWidth, 1);

  return 1;
}

void showMessage(const char* line1, const char* line2 = nullptr) {

  tft.fillScreen(ST77XX_BLACK);

  // Draw background again
  int result = png.openFLASH((uint8_t *)bg, sizeof(bg), pngDraw);

  if (result == PNG_SUCCESS) {png.decode(NULL, 0); png.close();}

  tft.setTextColor(ST77XX_WHITE);
  tft.setFont(&FreeMonoOblique9pt7b);

  int16_t x1, y1; uint16_t w, h;

  tft.getTextBounds(txt, 0, 0, &x1, &y1, &w, &h);

  int x1pos = (tft.width() - w) / 2;
  int y1pos;

  if (line2 != nullptr) {y1pos = tft.height() / 2 - 15;} 
  else {y1pos = (tft.height() - h) / 2;}

  tft.setCursor(x1pos, y1pos);
  tft.print(line1);

  // Second line
  if (line2 != nullptr) {

    tft.getTextBounds(line2, 0, 0, &x1, &y1, &w, &h);

    int x2pos = (tft.width() - w) / 2;
    int y2pos = tft.height() / 2 + 15;

    tft.setCursor(x2pos, y2pos);
    tft.print(line2);
  }
}

bool shaken() {

  int flips = 0;
  int last = digitalRead(tilt);

  unsigned long start = millis();

  while (millis() - start < 300) {

    int now = digitalRead(tilt);

    if (now != last) {flips++; last = now;}

    delay(5);
  }
  
  return flips >= 4;
}

void setup() {

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setFont(&FreeMonoOblique9pt7b);

  int result = png.openFLASH((uint8_t *)bg, sizeof(bg), pngDraw);
  if (result == PNG_SUCCESS) {png.decode(NULL, 0);}
  png.close();

  pinMode(tilt, INPUT_PULLUP);
  randomSeed(analogRead(0));

  showMessage("\"Ask me!\"");
}

void loop() {

  if (shaken()) {
    showMessage("\"Let's", "see...\"");
    delay(3000);

    int answer = random(fortune_num);

    switch (answer) {
      case 0:
        showMessage("\"YES!\"");
        break;

      case 1:
        showMessage("\"Absolutely!\"");
        break;

      case 2:
        showMessage("\"Hmm...", "maybe?\"");
        break;

      case 3:
        showMessage("\"Not", "sure...\"");
        break;

      case 4:
        showMessage("\"Absolutely", "not!\"");
        break;
    }

    delay(3000);

    showMessage("\"Ask me!\"");
  }
}
