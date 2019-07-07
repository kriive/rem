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
	return (int) floor(log10(data)) + 1;	// floor arrotonda per difetto
											// int tra parentesi è un cast
											// serve a dire al compilatore di trattare il valore come intero
											// e non come double (floor ritorna un double)
}

// TODO: fix every double change to single procision
// TODO: pass only precomputed values to while? Think about computational tradeoff

void DrawFirstRow(const uint64_t secondsSinceStartup, const uint64_t potvalue, const uint64_t counter, const uint8_t unitMeasure)
{
	// double dataToPrint = 0;
	//uint8_t mappedValue = map(potentiometerValue, 0, 4096, 0, 100);
	uint8_t digits = getDigits(potvalue);
	uint64_t dataToShow = 0;

	switch(unitMeasure) {
	case UNIT_CPM:
		// dataToPrint = 0;
		StampaStringaSuLCD(ROW_SHORT_COUNTER, N_COLONNE - 4 - digits, "CPM~");
		dataToShow = counter;
		break;
	case UNIT_nSM:
		// dataToPrint = 0;
		StampaStringaSuLCD(ROW_SHORT_COUNTER, N_COLONNE - 5 - digits, "nS/m~"); // TODO: fix cast
		dataToShow = (uint64_t) ((double) counter / 3.54);
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
	double dataToPrint = 0;

	switch(unitMeasure) {
	case UNIT_CPM:
		dataToPrint = ((double) counter / ((double) secondsSinceStartup / 60.0)); // contatore / (secondi / 60)
		StampaStringaSuLCD(ROW_INFINITE_COUNTER, getDigits((uint64_t) dataToPrint) + 1, "CPM");
		break;
	case UNIT_nSM:
		dataToPrint = (uint64_t) ((double) (counter) / ((double) secondsSinceStartup / 60.0) / 3.54);		// Use nS
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

