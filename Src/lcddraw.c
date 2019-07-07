/*
 * lcddraw.c
 *
 *  Created on: Jun 5, 2019
 *      Author: kriive
 */
#include "lcddraw.h"
#include "Display_LCD.h"
#include "math.h"
#include "assert.h"

int getDigits(uint32_t data)
{
	// We used floorf and log10f to take advantage of STM32F401RE FPU
	return (int) floorf(log10f(data)) + 1;	// floorf arrotonda per difetto
											// int tra parentesi è un cast
											// serve a dire al compilatore di trattare il valore come intero
											// e non come float (floorf ritorna un float)
}

void DrawFirstRow(const uint64_t secondsSinceStartup, const uint64_t potvalue, const uint64_t counter, const uint8_t unitMeasure)
{
	uint8_t digits = getDigits(potvalue);
	uint64_t dataToShow = 0;

	switch(unitMeasure) {
	case UNIT_CPM:
		StampaStringaSuLCD(ROW_SHORT_COUNTER, N_COLONNE - 4 - digits, "CPM~");
		dataToShow = counter;
		break;
	case UNIT_nSM:
		StampaStringaSuLCD(ROW_SHORT_COUNTER, N_COLONNE - 5 - digits, "nS/m~");
		// Note that (uint64_t) cast cuts away decimals, without computing approximations.
		dataToShow = (uint64_t) ((float) counter / 3.54f); // f suffix clarifies that 3.54 is to be treated as float
		break;
	}

	StampaInteroSuLCD(ROW_SHORT_COUNTER, 0, dataToShow);
	StampaInteroSuLCD(ROW_SHORT_COUNTER, N_COLONNE - digits, potvalue);
}

void DrawSecondRow(uint64_t secondsSinceStartup, uint64_t counter, uint8_t unitMeasure)
{
	/*
	 * Prima scriviamo la stringa legata all'unità di misura
	 * Calcoliamo il numero di cifre e poi scriviamo la stringa un carattere dopo
	 */
	uint16_t dataToPrint = 0;

	switch(unitMeasure) {
	case UNIT_CPM:
		dataToPrint = (uint16_t) ((float) counter / ((float) secondsSinceStartup / 60.0f)); // 60.0f tells compiler it's a float constant
		StampaStringaSuLCD(ROW_INFINITE_COUNTER, getDigits((uint64_t) dataToPrint) + 1, "CPM");
		break;
	case UNIT_nSM:
		dataToPrint = (uint16_t) ((float) (counter) / ((float) secondsSinceStartup / 60.0f) / 3.54f);		// Use nS
		StampaStringaSuLCD(ROW_INFINITE_COUNTER, getDigits((uint64_t) dataToPrint) + 1, "nS/m");
		break;
	default:
		assert(unitMeasure > 1 || unitMeasure < 0); //	Serve per debug,
													//	quando la variabile è fuori dai valori giusti
													//	il debugger impazzisce
		break;
	}
	StampaInteroSuLCD(ROW_INFINITE_COUNTER, 0, dataToPrint);
}

