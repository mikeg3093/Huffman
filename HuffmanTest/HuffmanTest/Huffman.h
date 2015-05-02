#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


struct HuffNode
{	
	char HuffNodeChar;			// a single character
	int	 HuffNodeFreq;			// frequency of said character in a file
	HuffNode* HuffNodeQnext;	// pointer to next node in a queue
	HuffNode* HuffNodeleft;		// left child in a tree
	HuffNode* HuffNoderight;	// right child in a tree
};

class Huffman
{
private:

	//VARIABLE DECLARATIONS
	FILE* outfile;					// pointers for reading and writing data
	FILE* infile;
	map<char,int> HuffFreqmap;		// map that stores chars and frequencies(ints)
	map<char, string> HuffKeymap;	// map that stores chars and huffmancodes(strings)
	map<string, char> HuffKeymap2;  // inverse
	HuffNode* HuffNodeQhead;		// pointer for head of queue and eventually head of tree
	string Huffmancode;				// 0s and 1s
	//char psuedoeof;					// doesnt work
	char chUserchoice;				// menu choice for compress or decompress
	char fusercompress[50];			//    -
	char fhuffcompress[50];			//    |    variable names of files
	char fuserdecompress[50];		//    |   
	char fhuffdecompress[50];		//    -

	//FUNCTION DECLARATIONS
	void PrintOpenMenu();
	void CallCompressMenu();
	void CallDecompressMenu();
	void FrequencyMap(char*);
	void BuildQueue();
	void PrintQueue();
	void BuildTree();
	void BuildKey(HuffNode*,string);
	void WriteHuffTemp(char*);
	void WriteHeader(HuffNode*, FILE*);
	void Compress(char*);
	void Decompress(char*, char*);
	void ReadHeader(FILE *, int);

public:
	Huffman(void);
	void Run();
	~Huffman(void);
};




