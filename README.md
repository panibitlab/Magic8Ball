# 🎱 Magic 8 Ball

<p align="center">
  Ask a question, shake the device, and let fate decide. ✨
  A tiny Arduino-powered Magic 8 Ball that answers your questions when you shake it.
</p>


## ❓ How It Works

The Magic 8 Ball uses a **tilt sensor** to detect when the device is shaken. When enough changes in the sensor's state are detected:

1. The screen clears.
2. `"Let's see..."` appears.
3. The device waits for a few seconds.
4. A random answer is selected.
5. The answer is displayed on the TFT.
6. The device returns to `"Ask me!"`.

So... go ahead.

**Ask it anything. 🎱**


## 🔮 Possible Answers

The current version has five possible answers:

* `YES!`
* `Absolutely!`
* `hmm... maybe?`
* `Not Sure...`
* `Absolutely not!`

The answer is selected randomly using Arduino's `random()` function.


## 🛠️ Hardware

* ESP32
* 1.8" ST7735 TFT display
* Tilt sensor
* Jumper wires
* Breadboard


## 📺 Display

The project uses the **Adafruit ST7735** library together with **Adafruit GFX**.
A custom GFX font is used to give the text a more retro appearance.
ه
```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
```


## ✨ Pin Configuration

### TFT Display

| TFT | ESP32 |
| --- | ----: |
| CS  |  `15` |
| DC  |   `2` |
| RST |   `4` |

### Tilt Sensor

| Sensor | ESP32 |
| ------ | ----: |
| Signal |  `21` |

The tilt sensor uses the ESP32's internal pull-up resistor:

```cpp
pinMode(tilt, INPUT_PULLUP);
```

## ✨ Shake Detection

Instead of simply checking whether the sensor is HIGH or LOW, the program monitors how many times its state changes within a short period.

```cpp
return flips >= 4;
```

This makes the device respond to an actual shaking motion rather than a single change in sensor state.

## 📼 Demo

<p align="center">
  <img src="demo.gif" width="50%">
</p>

## ✨ Credits

This project was originally inspired by a YouTube tutorial.
The tutorial provided the starting point for the project, while the code and hardware setup were used as a learning exercise.

check it out:

> *(https://youtu.be/7SrolYCAN8I?si=cCyQIPsMvTJVRHSa)*


## ✨ Author

**Parnian Ghorbani**


---

🎱 **Ask a question. Shake the ball. Trust the universe.**
