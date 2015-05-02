//---------------------------------------------------------------------
//
// Name:    Mike Grayson
//
// Course:  CS 1053, Section 202, Spring 2012
//
// Program Name: HuffmanTest
//
// Purpose: This is a program for compressing and decompressing .txt files
//				based on Huffman codes. The general idea behind Huffman codes 
//				is that characters that are used more frequently should be 
//				represented with a smaller number of bits. 
//			This program is capable of performing one compression or decompression
//				before exiting. For multiple comps/decomps, the program must be 
//				restarted.
//
// Input:   User-based menu prompted input. Input types include:
//				Menu Choices/Selections
//              .txt file names for reading from and writing to.
//              
// Output:  Depending on direction, a compressed .txt file or a
//				decompressed .txt file.
//
//---------------------------------------------------------------------

#include "Huffman.h"
using namespace std;

void main()
{
	Huffman TEST;
	TEST.Run();
}
