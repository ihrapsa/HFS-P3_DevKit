#include "buzzer.h"
#include "main.h"
#include "outputs.h"

//play a beep of 100ms
void play_beep(){
	for (int i=0; i<=400; i++)
	{
		BUZZER_ON();
		FL_DelayUs(125);
		BUZZER_OFF();
		FL_DelayUs(125);
	}
}

// Play a tone by generating a square wave at the specified frequency
void play_tone(uint32_t frequency, uint32_t duration) {
    uint32_t period = 1000000 / frequency;  // Period in microseconds
    uint32_t half_period = period / 2;

    for (uint32_t i = 0; i < (duration * 1000) / period; i++) {
        BUZZER_ON();  // Set pin high
        FL_DelayMs(half_period);
        BUZZER_OFF(); // Set pin low
        FL_DelayMs(half_period);
    }
}

// Play a simple melody
void play_melody(void) {
    play_tone(262, 500);  // C4, 500ms
    FL_DelayMs(100);
    play_tone(294, 500);  // D4, 500ms
    FL_DelayMs(100);
    play_tone(330, 500);  // E4, 500ms
    FL_DelayMs(100);
    play_tone(349, 500);  // F4, 500ms
    FL_DelayMs(100);
    play_tone(392, 500);  // G4, 500ms
    FL_DelayMs(100);
    play_tone(440, 500);  // A4, 500ms
    FL_DelayMs(100);
    play_tone(494, 500);  // B4, 500ms
    FL_DelayMs(100);
    play_tone(523, 1000); // C5, 1000ms
}