#include <avr/io.h>
#include "BIT.h"
#include "EXIT_INT_INTERFACE.h"


void INT0_init() {
	
 
  // Enable external interrupt on INT0, trigger on falling edge
   SET_BIT( EICRA,ISC01);
   CLR_BIT( EICRA,ISC00);
   
   SET_BIT( EIMSK,INT0_PIN );
  
}
void INT1_init() {
	// Enable external interrupt on INT1, trigger on falling edge
	SET_BIT(EICRA, ISC11);
	CLR_BIT(EICRA, ISC10);

	// Enable INT1
	SET_BIT(EIMSK, INT1_PIN );
}
