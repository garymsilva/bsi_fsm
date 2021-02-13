#include <stdio.h>
#include <stdlib.h>

const long int SIZE_IN_BYTES = 10 * 1024 * 1024; // 10MB
const float ENTROPY_RATIO = 0.8;                 // decimal percentage

void writeFile(char *fileName, unsigned char *data)
{
  FILE *fp = fopen(fileName, "w");
  fwrite(data, SIZE_IN_BYTES, 1, fp);
  printf("File %s created with %ld bytes\n", fileName, SIZE_IN_BYTES);
}

unsigned char getRandomValueUpTo(int maxValue)
{
  return (unsigned char)(rand() % maxValue);
}

void createRandomizedFile(char *filename, int maxCharValue)
{
  unsigned char *data = malloc(SIZE_IN_BYTES);
  int counter = 0;
  unsigned char randomNumber;
  while (counter < SIZE_IN_BYTES)
  {
    randomNumber = getRandomValueUpTo(maxCharValue);
    data[counter] = randomNumber;
    counter++;
  }
  writeFile(filename, data);
  free(data);
}

void createPartialRandomizedFile(char *filename, int maxCharValue)
{
  unsigned char *data = malloc(SIZE_IN_BYTES);
  int counter = 0;
  unsigned char randomNumber = getRandomValueUpTo(maxCharValue);

  int minCounter = (int)(ENTROPY_RATIO * -100.0);
  int maxCounter = (int)(100.0 + minCounter);

  int _switch = minCounter;

  while (counter < SIZE_IN_BYTES)
  {
    if (_switch >= 0)
    {
      randomNumber = getRandomValueUpTo(maxCharValue);
    }
    data[counter] = randomNumber;
    counter++;

    _switch++;
    if (_switch == maxCounter)
    {
      _switch = minCounter;
    }
  }
  writeFile(filename, data);
  free(data);
}

int main(void)
{
  createRandomizedFile("out/atividade1_arquivo1", 255);
  createRandomizedFile("out/atividade1_arquivo2", 26);
  createPartialRandomizedFile("out/atividade1_arquivo3", 255);
  createPartialRandomizedFile("out/atividade1_arquivo4", 26);
  return 0;
}
