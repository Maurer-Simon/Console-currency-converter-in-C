#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Create a structure for the currency data
typedef struct {
	char currencyname[30];
	char shortcut[3];
	float conversionrate;
}cs ; //currencystructure


// Convert the input amount to the desired currency
float currencyconvert(float amounteur, float conversionrate) {
	return amounteur * conversionrate;
}


int main(int argc, char* argv []) {

	printf("\n");

	// Check how many arguments were handed over.
	if (argc < 2) {
		printf("Too few arguments were handed over!");
		return -1;
	}

	// Convert 1 input argument to currencyname
	char *currency = argv[1];

	// Convert 2 input argument to amount of money in Euro
	float amounteuro = strtof(argv[2], NULL);

	// Create variable for the converted amount
	float converted = 0;

	// Check passed arguments
	printf("> The currency %s and the amount %.02f were read in.\n", currency, amounteuro);
	printf("> %d arguments were submitted.\n", argc);

	// Create structure cs1
	cs cs1;

	// Open the file
	FILE *file = fopen("E:\\Programming\\C Programming\\Console currency converter in C\\cmake-build-debug\\currency_data.txt", "r");

	// If filename not found exit the program
	if (file == NULL) {
		fprintf(stderr, "Error opening file\n");
		return 1;
	}

	// Define the word to search for, which is the first input (the desired currency)
	const char *searchWord = currency;

	// Read lines from the file
	char line[50]; // Adjust the buffer size as needed

	while (fgets(line, sizeof(line), file) != NULL) {
		// Check if the word is present in the line
		if (strstr(line, searchWord) != NULL) {
			// Extract data using sscanf and populate the struct
			sscanf(line, "%79[^;];%3[^;];%f", cs1.currencyname, cs1.shortcut, &cs1.conversionrate);

			// Print the line with the searchWord
			printf("> Data: %s", line);
		}
	}

	// Call function to calculate the converted currency amount
	converted = currencyconvert(amounteuro, cs1.conversionrate);


	printf("> %.02f Euros is the equivalent of %.2f %s!\n", amounteuro, converted, cs1.currencyname);

	fclose(file);
	return 0;
}
