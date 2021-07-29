#include "iSERVO.h"

iSERVO::iSERVO(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 100;
}

void iSERVO::init(void) {
  memset(last_set_angle, 0, 16);

  for (int i=0;i<16;i++) {
    t_min[i] = 0.5;
    t_max[i] = 2.5;
  }

	state = s_detect;
}

int iSERVO::prop_count(void) {
	// not supported
	return 0;
}

bool iSERVO::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool iSERVO::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool iSERVO::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool iSERVO::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool iSERVO::prop_write(int index, char *value) {
	// not supported
	return false;
}

void iSERVO::process(Driver *drv) {
  i2c = (I2CDev *)drv;

	switch (state) {
		case s_detect:
			if (i2c->detect(channel, address) == ESP_OK) {
        uint8_t buff[2] = { 0, 0 };
  
        uint32_t _oscillator_freq = 27000000;
        uint32_t freq = 50;
        uint8_t prescaleval = (((float)_oscillator_freq / ((float)freq * 4096.0)) + 0.5) - 1.0;
        
        buff[0] = 0xFE;
        buff[1] = prescaleval;
        if (i2c->write(channel, address, buff, 2) == ESP_OK) {
          buff[0] = 0x00;
          buff[1] = 0b10100000; // RESTART triger, Auto-Increment register
          if (i2c->write(channel, address, buff, 2) == ESP_OK) {
            error = false;
            initialized = true;

            state = s_angle_update;
          } else {
            state = s_error;
          }
        } else {
					state = s_error;
				}
			} else {
				state = s_error;
			}
			break;

		case s_angle_update:
      for (uint8_t i=0;i<16;i++) {
        setAngle(i, last_set_angle[i]);
      }
      state = s_check;
      polling_tickcnt = get_tickcnt();
			break;

    case s_check:
      if (is_tickcnt_elapsed(polling_tickcnt, polling_ms)) {
        if (i2c->detect(channel, address) == ESP_OK) {
          polling_tickcnt = get_tickcnt();
          state = s_check;
        } else {
          state = s_error;
        }
      }
      break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

void iSERVO::setAngle(uint8_t n, uint8_t angle) {
  if (!i2c) return;
  if (n > 15) return;

	angle = angle > 200 ? 200 : angle;

  float angleToMS = (angle * (t_max[n] -  t_min[n]) / 200.0) + t_min[n];
  uint16_t pulse_u16 = (angleToMS * 4095.0 / 20.0) * 0.93;
	
	uint8_t buff[5] = { 
    (uint8_t)(0x06 + (n * 4)), // LED0_ON_L 
    0, // ON LSB
    0, // ON MSB
    (uint8_t)(pulse_u16 & 0xFF),
    (uint8_t)((pulse_u16 >> 8) & 0xFF)
  };

  if (i2c->write(channel, address, buff, 5) != ESP_OK) {
    state = s_error;
  }

  last_set_angle[n] = angle;
}

void iSERVO::calibrate(uint8_t n, float min, float max) {
  t_min[n] = min;
	t_max[n] = max;
}
