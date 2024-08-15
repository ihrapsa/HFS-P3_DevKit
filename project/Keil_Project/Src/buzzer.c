#include "buzzer.h"
#include "main.h"
#include "outputs.h"
//#include "math.h"
//#include "time.h"
#include "leds.h"


/*
FUET 5020 passive 4000Hz buzzer. 
*/

//play a 4kHz beep of 100ms
void play_beep(){
	for (int i=0; i<=400; i++)
	{
		BUZZER_ON();
		FL_DelayUs(125);
		BUZZER_OFF();
		FL_DelayUs(125);
	}
}

//play a 4kHz click of 2.5ms
void play_click(){
	for (int i=0; i<=10; i++)
	{
		BUZZER_ON();
		FL_DelayUs(125);
		BUZZER_OFF();
		FL_DelayUs(125);
	}
	
}


//play a 4kHz click of 1ms
void play_click_1ms(){
	for (int i=0; i<=4; i++)
	{
		BUZZER_ON();
		FL_DelayUs(125);
		BUZZER_OFF();
		FL_DelayUs(125);
	}
	
}

//play a 4kHz click of 0.5ms
void play_click_500us(){
	for (int i=0; i<=2; i++)
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


//Function to simulate radioactive decay clicks since my Tungsten TIG welding rod is not radioactive enough.

//void simulate_radioactive_decay(double half_life_seconds, double duration_seconds, int initial_atoms) {
//    double decay_constant = log(2) / half_life_seconds;
//    int remaining_atoms = initial_atoms;
//    double elapsed_time = 0;
//    
//    // Initialize random number generator
//    srand(time(NULL));

//    while (elapsed_time < duration_seconds) {
//        // Calculate the probability of decay in the next 0.1 second interval
//        double decay_probability = 1 - exp(-decay_constant * 0.1);
//        
//        // Check each atom for decay
//        for (int i = 0; i < remaining_atoms; i++) {
//            if ((double)rand() / RAND_MAX < decay_probability) {
//                play_click_500us();
//								LED1_ON();
//								FL_DelayMs(100);
//								LED1_OFF();
//                remaining_atoms--;
//            }
//        }
//        
//        // Simulate passage of time (100 ms)
//        // In a real-time system, you might use a timer or delay function here
//        elapsed_time += 0.1;
//        
//        // Optional: break if all atoms have decayed
//        if (remaining_atoms == 0) {
//            break;
//        }
//    }
//	}