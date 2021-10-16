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
void unionsDelete(string words[N]);
void printStringArr(string str[]);
int strLenghtText(string line[]);
void createShinglesArray(string words[], string shinglesArray[], int lenghtString);

int main()
{
  string text = "if.(5A c) c then d!!! I1 f G {}H i j K)";
  string fragment = "\0";

  antiPlagiarism(text, fragment);

  return 0;
}

double antiPlagiarism (string text, string fragment)
{
  double result = 0.0;
  string str = text;
  string words[N] = {"\0"};
  string shinglesArray[] = {"\0"};

  convertToLowercase(text);
  splitIntoWords(text, words);
  unionsDelete(words);
  int lenghtString = strLenghtText(words);
  createShinglesArray(words, shinglesArray, lenghtString);

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

void unionsDelete(string words[N])
{
	string unionsArr[NUMBER_UNIONS] = {"and", "as", "or", "then", "but", "if", "till", "how", "so", "because", "unless", "until", "although", "however", "whenever"};  
	for (int i = 0; words[i] != "\0"; i++)
	{
    	for (int j = 0; j < NUMBER_UNIONS; j++)
 		{
    		if (words[i] == unionsArr[j])
    		{
    			for (int k = i; words[k] != "\0"; k++)
    			{
    				words[k] = words[k + 1];
    				i = 0;
				}
			}
			else
			{
				continue;
			}
		}
	}
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

int strLenghtText(string line[])
{
	int temp = 0;
	for (int i = 0; line[i] != "\0"; i++)
	{
		temp++;
	}
	return temp;
}

void createShinglesArray(string words[], string shinglesArray[], int lenghtString)
{
	int k = 0;
	int l = 0;
	int temp = 0;
	int numberOfShingles = 0;
	for (int i = 0; i < lenghtString; i++)
	{
		for (int j = 0; words[i][j] != '\0'; j++)
		{
			shinglesArray[k][l] = words[i][j];
			l++;
		}
		temp++;
		if (temp % 3 == 0)
		{
			i -= 2;
			k++;
			l = 0;
			numberOfShingles++;
			if (numberOfShingles == lenghtString - 2)
			{
				break;
			}
		}
	}
}