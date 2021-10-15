#include <iostream>

using namespace std;

double antiPlagiarism (string text, string fragment);

bool isUppercaseLetter(char symbol);

void convertToLowercase(string &str);

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

  convertToLowercase(text);

  for (int i = 0; text[i] != '\0'; i++)
  {
    cout << text[i];
  }

  return result;
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