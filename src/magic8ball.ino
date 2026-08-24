#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include <Fonts/FreeMonoOblique9pt7b.h>

#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST   4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const int fortune_num = 5;
const char* fortunes[] = {
  "YES!",
  "Absolutly!",
  "hmm... maybe?",
  "Not Sure...",
  "Absolutely not!"
};

const int tilt = 21;

void showMessage(const char* txt) {

  int16_t x1, y1; uint16_t w, h;

  tft.getTextBounds(txt, 0, 0, &x1, &y1, &w, &h);

  int x = (tft.width() - w) / 2;
  int y = (tft.height() - h) / 2;

  tft.setCursor(x, y);
  tft.println(txt);

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

  pinMode(tilt, INPUT_PULLUP);
  randomSeed(analogRead(0));

  showMessage("Ask me!");

}

void loop() {

  if (shaken()) {
    tft.fillScreen(ST77XX_BLACK);
    showMessage("Let's see...");
    delay(3000);

    tft.fillScreen(ST77XX_BLACK);
    showMessage(fortunes[random(fortune_num)]);
    delay(3000);

    tft.fillScreen(ST77XX_BLACK);
    showMessage("Ask me!");
  }
}
