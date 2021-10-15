#include <iostream>
#include <string>
#include <cstring>

using namespace std;
#define N 128
#define NUMBER_UNIONS 15

double antiPlagiarism (string text, string fragment);

int stringLength(string str);

bool isUppercaseLetter(char symbol);
bool isSeparator(char symbol);

void convertToLowercase(string &str);
void convertToCharArray(string str, char charArr[N]);
void splitIntoWords(string str, string words[N]);
void printStringArr(string str[]);

int main()
{
  string text = ".(5A c) c d!!! I1 f G {}H i j K)";
  string fragment = "\0";

  antiPlagiarism(text, fragment);

  return 0;
}

double antiPlagiarism (string text, string fragment)
{
  double result = 0.0;
  string str = text;
  string words[N] = {"\0"};

  convertToLowercase(text);
  splitIntoWords(text, words);

  printStringArr(words);

  return result;
}

void splitIntoWords(string str, string words[N])
{
  char charArr[N] = {'\0'};
  char word[N] = {'\0'};
  int i = 0;
	int j = 0;
  int k = 0;
	
  convertToCharArray(str, charArr);

  for (i = 0; charArr[i] != '\0'; i++)
  {
    if (!isSeparator(charArr[i]))
    {
      word[j] = charArr[i];
      j++;
      if (isSeparator(charArr[i+1]) || charArr[i+1] == '\0')
      {
        word[j] = '\0';
        words[k] = word;
        k++;
        j = 0;
      }
    }
  }
}

bool isSeparator(char symbol)
{
	char separatorArr[] = " .,!?;:-+{}()[]*@%$^&#`~_=<>/|'\"\\";
	
	for (int i = 0; separatorArr[i] != '\0'; i++)
	{
		if (separatorArr[i] == symbol)
			return true;
	}
	return false;
}

void convertToLowercase(string &str)
{
  for(int i = 0; str[i] != '\0'; i++)
  {
    if (isUppercaseLetter(str[i]))
    {
      str[i] += 32;
    }
  }
}

bool isUppercaseLetter(char symbol)
{
	if(symbol >= 65 && symbol <= 90)
		return true;
	return false;	
}

void convertToCharArray(string str, char charArr[N])
{
  for (int i = 0; i < stringLength(str); i++)
  {
    charArr[i] = str[i];
  }
}

int stringLength(string str)
{
  int i = 0;
  while (str[i] != '\0') i++;
  return i;
}

void printStringArr(string str[])
{
  for (int i = 0; str[i] != "\0"; i++)
  {
    cout << "words[" << i << "] = " << str[i] << endl;
  }
  cout << endl;
}