#include <encoder.h>


Encoder::Encoder(uint8_t pin1, uint8_t pin2)
{
		
		pinMode(pin1, INPUT_PULLUP);
		pinMode(pin2, INPUT_PULLUP);
		encoder.pin1_register = PIN_TO_BASEREG(pin1);
		encoder.pin1_bitmask = PIN_TO_BITMASK(pin1);
		encoder.pin2_register = PIN_TO_BASEREG(pin2);
		encoder.pin2_bitmask = PIN_TO_BITMASK(pin2);
		encoder.position = 0;
		delayMicroseconds(2000);
		uint8_t s = 0;
		if (DIRECT_PIN_READ(encoder.pin1_register, encoder.pin1_bitmask)) s |= 1;
		if (DIRECT_PIN_READ(encoder.pin2_register, encoder.pin2_bitmask)) s |= 2;
		encoder.state = s;
}
	
void Encoder::update(Encoder_internal_state_t *arg) {

		uint8_t p1val = DIRECT_PIN_READ(arg->pin1_register, arg->pin1_bitmask);
		uint8_t p2val = DIRECT_PIN_READ(arg->pin2_register, arg->pin2_bitmask);
		uint8_t state = arg->state & 3;
		if (p1val) state |= 4;
		if (p2val) state |= 8;
		arg->state = (state >> 2);
		switch (state) {
			case 1: case 7: case 8: case 14:
				arg->position++;
				return;
			case 2: case 4: case 11: case 13:
				arg->position--;
				return;
			case 3: case 12:
				arg->position += 2;
				return;
			case 6: case 9:
				arg->position -= 2;
				return;
		}

	}

uint8_t Encoder::attach_interrupt(uint8_t pin, Encoder_internal_state_t *state) {
		switch (pin) {
		
			case CORE_INT16_PIN:
				interruptArgs[16] = state;
				attachInterrupt(16, isr16, CHANGE);
				break;
	
		
			case CORE_INT17_PIN:
				interruptArgs[17] = state;
				attachInterrupt(17, isr17, CHANGE);
				break;
			
			case CORE_INT18_PIN:
				interruptArgs[18] = state;
				attachInterrupt(18, isr18, CHANGE);
				break;
	
		
			case CORE_INT19_PIN:
				interruptArgs[19] = state;
				attachInterrupt(19, isr19, CHANGE);
				break;
			default:
				return 0;
		}
		return 1;
	}

int32_t Encoder::read() {
		    noInterrupts();
		    update(&encoder);
		    int32_t ret = encoder.position;
		    interrupts();
		    return ret;
	    }

