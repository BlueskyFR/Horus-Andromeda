#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SAVEFILE "savefile.ini"
#define MAX_LINE_LENGTH 100

float readSaveFile(const char* nom)
{
	FILE *saveFile;
	int i = 0;
	int j = 0;
	long k = 0;
	float result = 0;
	bool leaveloop = 0;

	char read[MAX_LINE_LENGTH];
	char readChar;

	saveFile = fopen(SAVEFILE, "r+");

	while (strcmp(read, nom) != 0 && !leaveloop)
	{
		readChar = 'b';
		k = ftell(saveFile);
		fgets(read, MAX_LINE_LENGTH, saveFile);
		fseek(saveFile, k, SEEK_SET);

		for (j = 0; j < MAX_LINE_LENGTH && readChar != '\n'; j++)
		{
			readChar = fgetc(saveFile);

			if (readChar == '=')
			{
				read[j] = '\0';
				k = ftell(saveFile);
			}
		}

		if (k == ftell(saveFile))
		{
			k = ftell(saveFile);
			leaveloop = 1;
		}
	}

	fseek(saveFile, k, SEEK_SET);

	fscanf(saveFile, "%e", &result);
	fclose(saveFile);
	return result;
}

void writeToSaveFile(const char* nom, const float value)
{
	FILE *saveFile;
	int i = 0;
	int j = 0;
	long k = 0;
	bool leaveloop = 0;

	char read[MAX_LINE_LENGTH];
	char readChar;

	saveFile = fopen(SAVEFILE, "r+");

	while (strcmp(read, nom) != 0 && !leaveloop)
	{
		readChar = 'b'; //placeholder letter (just need to not be \n)

		k = ftell(saveFile);
		fgets(read, MAX_LINE_LENGTH, saveFile);
		fseek(saveFile, k, SEEK_SET);

		for (j = 0; j < MAX_LINE_LENGTH && readChar != '\n'; j++)
		{
			readChar = fgetc(saveFile);
			if (readChar == '=')
			{
				//fseek(saveFile, -1, SEEK_CUR);
				read[j] = '\0';
				//k = ftell(saveFile);
			}
		}

		if (k == ftell(saveFile))
		{
			k = ftell(saveFile);
			leaveloop = 1;
		}
	}

	fseek(saveFile, k, SEEK_SET);

	if (leaveloop)
		fprintf(saveFile, "%s=%e                 \n", nom, value);
	else
		fprintf(saveFile, "%s=%e     ", nom, value);


	fclose(saveFile);
}