#ifndef __ISERVO_H__
#define __ISERVO_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "stdio.h"
#include "string.h"

class iSERVO : public Device {
	private:		
		enum {
			 s_detect, s_angle_update, s_check, s_error, s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;

        I2CDev *i2c = NULL;

		uint8_t last_set_angle[16];
		float t_min[16];
		float t_max[16];

	public:
		// constructor
		iSERVO(int bus_ch, int dev_addr) ;
		
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		void setAngle(uint8_t n, uint8_t angle) ;
		void calibrate(uint8_t n, float min, float max) ;
		
};

#endif
