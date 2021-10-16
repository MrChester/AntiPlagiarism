#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;
#define N 128
#define NUMBER_UNIONS 15

double antiPlagiarism (string text, string fragment);

int stringLength(string str);
int strLenghtText(string line[]);
int getCharArrayLength(char str[]);

bool isUppercaseLetter(char symbol);
bool isSeparator(char symbol);

void convertToLowercase(string &str);
void convertToCharArray(string str, char charArr[N]);
void splitIntoWords(string str, string words[N]);
void unionsDelete(string words[N]);
void printStringArr(string str[]);
//int strLenghtText(string line[]);
void createShingles(string words[], string shinglesArray[]);
void getStrCat(char dest[N], char src[N]);

///////////////////////////////////////////////////////////////
unsigned int A; 
unsigned int B; 
unsigned int C; 
unsigned int D; 

unsigned int T[64];


unsigned int F(unsigned int X, unsigned int Y, unsigned int Z) { return (X & Y) | (~X & Z); }
unsigned int G(unsigned int X, unsigned int Y, unsigned int Z) { return (X & Z) | (~Z & Y); }
unsigned int H(unsigned int X, unsigned int Y, unsigned int Z) { return X^Y^Z; }
unsigned int I(unsigned int X, unsigned int Y, unsigned int Z) { return Y^(~Z|X); }


unsigned int shiftLeft(unsigned int x, unsigned int n) {
    return (x<<n) | (x>>(32-n));
}

void addingLenght(vector<unsigned char>& buf, const unsigned long long len){
    
    for (auto i = 7; i >= 0; i--)
        buf.push_back((unsigned char)((len >> (i * 8)) & 0xFF));
}

void addingNulls(vector<unsigned char>& buf) {
    do
        buf.push_back(0);
    while (buf.size() % 64 != 56);
}

void initMDbuf(){
    A = 0x67452301; 
    B = 0xEFCDAB89; 
    C = 0x98BADCFE;
    D = 0x10325476;
    for (auto i = 0; i < 64; i++)
        T[i] = (unsigned int)(pow(2, 32) * abs(sin(double(i + 1))));
    
}

void adding1byte(vector<unsigned char>& buf) {
    buf.push_back(128);   //128 = 1000 0000
}

int conv512to32(vector<unsigned char>& buf, unsigned int*& words){
    auto wSize = buf.size();
    words = new unsigned int[wSize/4];

    for (auto i = 0, j=0; i < wSize; i+=4, j=i/4) {
        words[j] = 0;
        words[j] += (unsigned int)(buf[i]);
        words[j] += (unsigned int)(buf[i+1])<<8;
        words[j] += (unsigned int)(buf[i+2])<<16;
        words[j] += (unsigned int)(buf[i+3])<<24;
    }
    
    return wSize/4;
}

void calcBlocks(unsigned int *buf, const int len) {
    for(auto i = 0; i < len; i+=16) {
        auto AA=A, BB=B, CC=C, DD=D;

        //ROUND I

        A = B + shiftLeft((A + F(B, C, D) + buf[i + 0] + T[0]), 7);
        D = A + shiftLeft((D + F(A, B, C) + buf[i + 1] + T[1]), 12);
        C = D + shiftLeft((C + F(D, A, B) + buf[i + 2] + T[2]), 17);
        B = C + shiftLeft((B + F(C, D, A) + buf[i + 3] + T[3]), 22);

        A = B + shiftLeft((A + F(B, C, D) + buf[i + 4] + T[4]), 7);
        D = A + shiftLeft((D + F(A, B, C) + buf[i + 5] + T[5]), 12);
        C = D + shiftLeft((C + F(D, A, B) + buf[i + 6] + T[6]), 17);
        B = C + shiftLeft((B + F(C, D, A) + buf[i + 7] + T[7]), 22);
        
        A = B + shiftLeft((A + F(B, C, D) + buf[i + 8] + T[8]), 7);
        D = A + shiftLeft((D + F(A, B, C) + buf[i + 9] + T[9]), 12);
        C = D + shiftLeft((C + F(D, A, B) + buf[i + 10] + T[10]), 17);
        B = C + shiftLeft((B + F(C, D, A) + buf[i + 11] + T[11]), 22);

        A = B + shiftLeft((A + F(B, C, D) + buf[i + 12] + T[12]), 7);
        D = A + shiftLeft((D + F(A, B, C) + buf[i + 13] + T[13]), 12);
        C = D + shiftLeft((C + F(D, A, B) + buf[i + 14] + T[14]), 17);
        B = C + shiftLeft((B + F(C, D, A) + buf[i + 15] + T[15]), 22);

        //ROUND II

        A = B + shiftLeft((A+G(B, C, D)+buf[i+1]+T[16]), 5);
		D = A + shiftLeft((D+G(A, B, C)+buf[i+6]+T[17]), 9);
		C = D + shiftLeft((C+G(D, A, B)+buf[i+11]+T[18]), 14);
		B = C + shiftLeft((B+G(C, D, A)+buf[i+0]+T[19]), 20);

		A = B + shiftLeft((A+G(B, C, D)+buf[i+5]+T[20]), 5);
		D = A + shiftLeft((D+G(A, B, C)+buf[i+10]+T[21]), 9);
		C = D + shiftLeft((C+G(D, A, B)+buf[i+15]+T[22]), 14);
		B = C + shiftLeft((B+G(C, D, A)+buf[i+4]+T[23]), 20);

		A = B + shiftLeft((A+G(B, C, D)+buf[i+9]+T[24]), 5);
		D = A + shiftLeft((D+G(A, B, C)+buf[i+14]+T[25]), 9);
		C = D + shiftLeft((C+G(D, A, B)+buf[i+3]+T[26]), 14);
		B = C + shiftLeft((B+G(C, D, A)+buf[i+8]+T[27]), 20);

		A = B + shiftLeft((A+G(B, C, D)+buf[i+13]+T[28]), 5);
		D = A + shiftLeft((D+G(A, B, C)+buf[i+2]+T[29]), 9);
		C = D + shiftLeft((C+G(D, A, B)+buf[i+7]+T[30]), 14);
		B = C + shiftLeft((B+G(C, D, A)+buf[i+12]+T[31]), 20);

        //ROUND III

        A = B + shiftLeft((A + H(B, C, D) + buf[i + 5] + T[32]), 4);
        D = A + shiftLeft((D + H(A, B, C) + buf[i + 8] + T[33]), 11);
        C = D + shiftLeft((C + H(D, A, B) + buf[i + 11] + T[34]), 16);
        B = C + shiftLeft((B + H(C, D, A) + buf[i + 14] + T[35]), 23);

        A = B + shiftLeft((A + H(B, C, D) + buf[i + 1] + T[36]), 4);
        D = A + shiftLeft((D + H(A, B, C) + buf[i + 4] + T[37]), 11);
        C = D + shiftLeft((C + H(D, A, B) + buf[i + 7] + T[38]), 16);
        B = C + shiftLeft((B + H(C, D, A) + buf[i + 10] + T[39]), 23);

        A = B + shiftLeft((A + H(B, C, D) + buf[i + 13] + T[40]), 4);
        D = A + shiftLeft((D + H(A, B, C) + buf[i + 0] + T[41]), 11);
        C = D + shiftLeft((C + H(D, A, B) + buf[i + 3] + T[42]), 16);
        B = C + shiftLeft((B + H(C, D, A) + buf[i + 6] + T[43]), 23);
        
        A = B + shiftLeft((A + H(B, C, D) + buf[i + 9] + T[44]), 4);
        D = A + shiftLeft((D + H(A, B, C) + buf[i + 12] + T[45]), 11);
        C = D + shiftLeft((C + H(D, A, B) + buf[i + 15] + T[46]), 16);
        B = C + shiftLeft((B + H(C, D, A) + buf[i + 2] + T[47]), 23);

        //ROUND IV

        A = B + shiftLeft((A + I(B, C, D) + buf[i + 0] + T[48]), 6);
        D = A + shiftLeft((D + I(A, B, C) + buf[i + 7] + T[49]), 10);
        C = D + shiftLeft((C + I(D, A, B) + buf[i + 14] + T[50]), 15);
        B = C + shiftLeft((B + I(C, D, A) + buf[i + 5] + T[51]), 21);

        A = B + shiftLeft((A + I(B, C, D) + buf[i + 12] + T[52]), 6);
        D = A + shiftLeft((D + I(A, B, C) + buf[i + 3] + T[53]), 10);
        C = D + shiftLeft((C + I(D, A, B) + buf[i + 10] + T[54]), 15);
        B = C + shiftLeft((B + I(C, D, A) + buf[i + 1] + T[55]), 21);

        A = B + shiftLeft((A + I(B, C, D) + buf[i + 8] + T[56]), 6);
        D = A + shiftLeft((D + I(A, B, C) + buf[i + 15] + T[57]), 10);
        C = D + shiftLeft((C + I(D, A, B) + buf[i + 6] + T[58]), 15);
        B = C + shiftLeft((B + I(C, D, A) + buf[i + 13] + T[59]), 21);
        
        A = B + shiftLeft((A + I(B, C, D) + buf[i + 4] + T[60]), 6);
        D = A + shiftLeft((D + I(A, B, C) + buf[i + 11] + T[61]), 10);
        C = D + shiftLeft((C + I(D, A, B) + buf[i + 2] + T[62]), 15);
        B = C + shiftLeft((B + I(C, D, A) + buf[i + 9] + T[63]), 21);

        A+=AA; B+=BB; C+=CC; D+=DD;
    }
}

string hex(unsigned int num) {
    stringstream stream;
 
    for (auto i = 0; i < 4; i++) {
        stream << setfill('0') << std::setw(2) <<hex <<num%256;
        num/=256;
    }
    return stream.str();
}

string md5(const string msg){
    unsigned int* blocks;
    unsigned long long len = msg.length();

    vector<unsigned char> buf(len);
    for (auto i = 0; i<len;i++)
        buf[i]=msg[i];
    
    len = _byteswap_uint64(len*8); 

    
    adding1byte(buf);      
    
    addingNulls(buf);   
    
    addingLenght(buf,len);  
    
    initMDbuf();       
    
    calcBlocks(blocks,conv512to32(buf,blocks));   
   
    
    return hex(A)+hex(B)+hex(C)+hex(D);
}

int main()
{
  string text = "Lorem Ipsum is simply dummy";
  string fragment = "Lorem Ipsum is simply dummy Ipsum is simply";

  antiPlagiarism(text, fragment);

  return 0;
}

double antiPlagiarism (string text, string fragment)
{
  double result = 0.0;
  string str = text;
  string textArray[N] = {"\0"};
  string fragmentArray[N] = {"\0"};
  string shinglesArray[] = {"\0"};

  convertToLowercase(text);
  splitIntoWords(text, textArray);
  unionsDelete(textArray);
  int lenghtString = strLenghtText(textArray);
  createShingles(textArray, shinglesArray);

  cout << "Words :: Array" << endl;
  printStringArr(textArray);
  cout << "Shingles :: Array" << endl;
  printStringArr(shinglesArray);
  return result;
}

void splitIntoWords(string str, string wordsArr[N])
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
        wordsArr[k] = word;
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

int strLenghtText(string line[])
{
	int temp = 0;
	for (int i = 0; line[i] != "\0"; i++)
	{
		temp++;
	}
	return temp;
}

void printStringArr(string str[])
{
  for (int i = 0; str[i] != "\0"; i++)
  {
    cout << "array [" << i << "] = " << str[i] << endl;
  }
  cout << endl;
}

void createShingles(string wordsArr[], string shinglesArray[])
{
	char shingleBuffer[N] = {0};
  char wordsBuffer[N] = {'\0'};
  int counter = 0;
  int is = 0;
  int iw = 0;

  for(int i = 0; wordsArr[i] != "\0"; i++)
  {
    if (counter == 3)
    {
      i -= 2;
      counter = 0;
      for(int i = 0; i < N; i++)
      {
    	shingleBuffer[i] = 0;
      }
    }
	
    for(int i = 0; i < N; i++)
    {
    	wordsBuffer[i] = 0;
    }

    for(int j = 0; wordsArr[i][j] != '\0'; j++)
    {
      wordsBuffer[j] = wordsArr[i][j];
    }

    getStrCat(shingleBuffer, wordsBuffer);
    
    if (counter == 2)
    {
    	cout << "dest: " << shingleBuffer << endl;
      shinglesArray[is] = shingleBuffer;
      is++;
    }
    counter++;
    iw++;
  }
}

void getStrCat(char dest[N], char src[N])
{
  int destLength = getCharArrayLength(dest);

  for (int i = 0; src[i] != '\0'; i++)
  {
    dest[destLength + i] = src[i];
  }
}

int getCharArrayLength(char str[])
{
  int i = 0;

  while (str[i] != '\0') i++;

  return i;
}