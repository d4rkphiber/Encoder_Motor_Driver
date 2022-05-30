#include <Arduino.h>
//#include <direct_pin_read.h>
//#define ENCODER_USE_INTERRUPTS
#include <interrupt_pins.h>
#define ENCODER_ARGLIST_SIZE CORE_NUM_INTERRUPT




typedef struct {
	volatile IO_REG_TYPE * pin1_register;
	volatile IO_REG_TYPE * pin2_register;
	IO_REG_TYPE            pin1_bitmask;
	IO_REG_TYPE            pin2_bitmask;
	uint8_t                state;
	int32_t                position;
} Encoder_internal_state_t;

//Sieht der Compiler als Encode_internal_state, deshalb kein Name!
	
class Encoder
{
public:
	Encoder_internal_state_t encoder;
	Encoder(uint8_t pin1, uint8_t pin2);	
	static Encoder_internal_state_t * interruptArgs[ENCODER_ARGLIST_SIZE];
	int32_t read();
	static void update(Encoder_internal_state_t *arg);
	uint8_t interrupts_in_use;
	uint8_t attach_interrupt(uint8_t pin, Encoder_internal_state_t *state);
	static void isr16(void) { update(interruptArgs[16]); }
	static void isr17(void) { update(interruptArgs[17]); }
	static void isr18(void) { update(interruptArgs[18]); }
	static void isr19(void) { update(interruptArgs[19]); }


};





