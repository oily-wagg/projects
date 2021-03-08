                                         /* SPI ADC Library */
#include <avr/io.h>
#include "pinDefines.h"


                                 /* Which pin selects ADC as slave? */
#define SLAVE_SELECT    SPI_SS_PORT &= ~(1 << SPI_SS)
#define SLAVE_DESELECT  SPI_SS_PORT |= (1 << SPI_SS)

// Functions
#define ADC_WAKEUP        0b00000001

#define ADC_CH0_READ      0b10000000
#define ADC_CH1_READ      0b10010000
#define ADC_CH2_READ      0b10100000
#define ADC_CH3_READ      0b10110000
#define ADC_CH4_READ      0b11000000
#define ADC_CH5_READ      0b11010000
#define ADC_CH6_READ      0b11100000
#define ADC_CH7_READ      0b11110000

                  /* Init SPI to run EEPROM with phase, polarity = 0,0 */
void initSPI(void);

                  /* Generic.  Just loads up HW SPI register and waits */
void SPI_tradeByte(uint8_t byte);

                        /* gets two bytes from a given memory location */
uint16_t ADC_readWord(uint8_t address);
