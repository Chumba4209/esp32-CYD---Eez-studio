#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Bus_SPI _bus;
  lgfx::Panel_ILI9341 _panel;
  lgfx::Light_PWM _light;
  lgfx::Touch_XPT2046 _touch;

public:
  LGFX(void)
  {
    // ================= SPI BUS =================
    {
      auto cfg = _bus.config();
      cfg.spi_host = VSPI_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read  = 16000000;

      cfg.pin_sclk = 18;
      cfg.pin_mosi = 23;
      cfg.pin_miso = 19;
      cfg.pin_dc   = 2;

      _bus.config(cfg);
      _panel.setBus(&_bus);
    }

    // ================= PANEL ===================
    {
      auto cfg = _panel.config();
      cfg.pin_cs   = 15;
      cfg.pin_rst  = 4;

      cfg.memory_width  = 240;
      cfg.memory_height = 320;
      cfg.panel_width   = 240;
      cfg.panel_height  = 320;

      cfg.offset_x = 0;
      cfg.offset_y = 0;
      //cfg.rotation = 0;

      _panel.config(cfg);
    }

    // ================= BACKLIGHT ===============
    {
      auto cfg = _light.config();
      cfg.pin_bl = 21;
      cfg.invert = false;
      cfg.freq   = 5000;
      cfg.pwm_channel = 7;

      _light.config(cfg);
      _panel.setLight(&_light);
    }

    // ================= TOUCH ===================
    {
      auto cfg = _touch.config();

      cfg.spi_host = VSPI_HOST;
      cfg.freq = 1000000;
      cfg.pin_cs  = 33;
      cfg.pin_int = 36;

      cfg.x_min = 0;
      cfg.x_max = 320;
      cfg.y_min = 0;
      cfg.y_max = 240;

      cfg.offset_rotation = 0;

      _touch.config(cfg);
      _panel.setTouch(&_touch);
    }

    setPanel(&_panel);
  }
};
