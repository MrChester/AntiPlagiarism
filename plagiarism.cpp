#include <iostream>

using namespace std;

double antiPlagiarism (string text, string fragment);

int stringLength(string str);

void convertToCharArray(string str, char charArr[N]);

int main()
{
  string text = "\0";
  string fragment = "\0";

  antiPlagiarism(text, fragment);

  return 0;
}

double antiPlagiarism (string text, string fragment)
{
  double result = 0.0;

  cout << "In progress.." << endl;

  return result;
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