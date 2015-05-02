#include "Huffman.h"


Huffman::Huffman(void)
{
	Huffmancode = "";
	HuffNodeQhead = NULL;
	//char psuedoeof = 17;
}
//----------------------------------------------------------------------------
// Run: Calls PrintOpenMenu and then calls compress/decompress menu based
//						on user choice.
// @Param: void
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::Run()
{		
	PrintOpenMenu();
	if(chUserchoice == '1') 
		CallCompressMenu();
	else if(chUserchoice == '2')	
		CallDecompressMenu();
}
//----------------------------------------------------------------------------
// PrintOpenMenu: Simple welcome menu, user chooses compress or decompress.
// @Param: void
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::PrintOpenMenu()
{
	cout << "----------------------------------------\n";
	cout << "  Huffman Code Compressor/Decompressor\n";
	cout << "----------------------------------------\n\n";
	cout << "What would you like to do?\n";
	cout << "1. Compress a file\n";
	cout << "2. Decompress a file\n";
	cin >> chUserchoice;
}
//----------------------------------------------------------------------------
// CallCompressMenu: Requests a file tobe compressed and a new file name.
//						Contains function calls for actual compression.
// @Param: void
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::CallCompressMenu()
{
		cout << "\nWhat is the name of the file that you would like to compress?\n";
		cout << "(Please include a .txt extension)\n";
		scanf("%s", fusercompress);
		cout << "\nWhat would you like your compressed file to be called?\n";
		cout << "(Please include a .txt extension)\n";
		scanf("%s", fhuffcompress);
		FrequencyMap(fusercompress);
		BuildQueue();
		system("pause>0");
		BuildTree();
		BuildKey(HuffNodeQhead, Huffmancode);
		cout << "       :Huffman codes for characters:\n";
		system("pause>0");
		WriteHuffTemp(fusercompress);
		Compress(fhuffcompress);
		cout << "\nYour file has been compressed!";
		system("pause>0");
}
//----------------------------------------------------------------------------
// CallDecompressMenu: Requests a file tobe decompressed and a new file name.
//						Contains function calls for actual decompression.
// @Param: void
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::CallDecompressMenu()
{
	cout << "\nWhat is the name of the file that you would like to decompress?\n";
	cout << "(Please include a .txt extension)\n";
	scanf("%s", fuserdecompress);
	cout << "\nWhat would you like your decompressed file to be called?\n";
	cout << "(Please include a .txt extension)\n";
	scanf("%s", fhuffdecompress);
	Decompress(fuserdecompress, fhuffdecompress);
	cout << "\nYour file has been decompressed!";
	system("pause>0");
}
//----------------------------------------------------------------------------
// FrequencyMap: Counts character frequencies of FMusercompress (file)
//						and stores them in HuffFreqmap[] (map);
// @Param: char* FMusercompress - user file to be compressed
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::FrequencyMap(char* FMfusercompress)
{	
	infile = fopen(FMfusercompress, "rb");
	char FMreadchar = 0;
	
	//HuffFreqmap[psuedoeof]++;
	while(!feof(infile))				
	{									
		FMreadchar = fgetc(infile);

		//if(FMreadchar != -1)
		//{
			HuffFreqmap[FMreadchar]++;
		//}
	}
}
//----------------------------------------------------------------------------
// BuildQueue: Takes HuffFreqmap[] and creates a priority queue from its elements.	
//					less frequent = closer to front    e.x. 10->18->27...
// @Param: void
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::BuildQueue()
{	
	map<char, int>::iterator it;

	for (it=HuffFreqmap.begin(); it != HuffFreqmap.end(); it++)
	{
		//Initializes new node with map data
		HuffNode* Temp = new HuffNode;
		Temp->HuffNodeChar = it->first;
		Temp->HuffNodeFreq = it->second;
		Temp->HuffNodeQnext = NULL;
	
		//If queue is empty
		if(!HuffNodeQhead)
		{
			HuffNodeQhead=Temp;
		}
		else
		{	//If it is at the front of the queue
			if(Temp->HuffNodeFreq <= HuffNodeQhead->HuffNodeFreq)
			{
				Temp->HuffNodeQnext = HuffNodeQhead;
				HuffNodeQhead = Temp;
			}
			else
			{	//If somewhere else
				HuffNode *Ptr = HuffNodeQhead;
				HuffNode *Prev = HuffNodeQhead;
				//Find proper location to insert 
				while(Ptr != NULL && Temp->HuffNodeFreq >= Ptr->HuffNodeFreq)
				{	
					Prev = Ptr;
					Ptr = Ptr->HuffNodeQnext;
				}
				//Link node into place
				Prev->HuffNodeQnext = Temp;
				Temp->HuffNodeQnext = Ptr;
			}
		}
	}
	PrintQueue();
}
//----------------------------------------------------------------------------
// PrintQueue: Prints queued characters and frequencies for user reference.
//					
// @Param: void
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::PrintQueue()
{
	HuffNode* TravQueue= HuffNodeQhead;
	int Qsize = 0;
	
	while(TravQueue!=NULL)
	{
		cout <<endl << TravQueue->HuffNodeChar <<" - "<<TravQueue->HuffNodeFreq;
		TravQueue = TravQueue->HuffNodeQnext;
		Qsize++;
	}
	cout << "     :Character Frequencies:\n\n";
	cout << "Number of unique characters in your file: " << Qsize << endl;
}
//----------------------------------------------------------------------------
// BuildTree: Builds the Huffman tree from the Huffman nodes of the priority queue
//						
// @Param: void
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::BuildTree()
{	
	//Create a new node for hufftree and ptrs for finding its proper location
	HuffNode* HuffNodeTemp;
	HuffNode* Qptr;
	HuffNode* Qprev;
	HuffNode* delHuffNode;

	while(HuffNodeQhead->HuffNodeQnext != NULL)
	{	//Reset
		HuffNodeTemp = new HuffNode;
		Qptr = HuffNodeQhead->HuffNodeQnext->HuffNodeQnext;
		Qprev = HuffNodeQhead->HuffNodeQnext;
		delHuffNode = HuffNodeQhead->HuffNodeQnext;
			//Initialize new node 
			HuffNodeTemp->HuffNodeFreq = HuffNodeQhead->HuffNodeFreq+HuffNodeQhead->HuffNodeQnext->HuffNodeFreq;


			HuffNodeTemp->HuffNodeChar = '\0';//***Denotes an InnerNode***


			//HuffNodeTemp->HuffNodeChar = HuffNodeQhead->HuffNodeChar;




			HuffNodeTemp->HuffNodeleft = HuffNodeQhead;
			HuffNodeTemp->HuffNoderight = HuffNodeQhead->HuffNodeQnext;
			//Find new location
			while(Qptr != NULL && HuffNodeTemp->HuffNodeFreq > Qptr->HuffNodeFreq)
			{	
				Qprev = Qptr;
				Qptr = Qptr->HuffNodeQnext;
			}
			//Set new Location in tree
			Qprev->HuffNodeQnext = HuffNodeTemp;
			HuffNodeTemp->HuffNodeQnext = Qptr;
			HuffNodeQhead = delHuffNode->HuffNodeQnext;
	}
}
//----------------------------------------------------------------------------
// BuildKey: Recursive function to generate huffman codes for characters.
//				Traverses the tree that was built from the priority queue.
//
// @Param: HuffNode*HuffNodeQheadt - pointer to node in tree
// @Param: string Hcode			   - dynamic string that is built from traversal
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::BuildKey(HuffNode*HuffNodeQheadt, string Hcode)
{	
	if(HuffNodeQheadt->HuffNodeChar != '\0')
	//if(HuffNodeQheadt->HuffNodeleft == NULL && HuffNodeQheadt->HuffNoderight == NULL)
	{	//Leaf nodes have a charater value. 
		//when at a leaf, that value is mapped
		cout << endl << HuffNodeQheadt->HuffNodeChar;
		cout << " -> " << Hcode;
		HuffKeymap[HuffNodeQheadt->HuffNodeChar] = Hcode;
		return;
	}
	else 
	{	//In-order traversal
		BuildKey(HuffNodeQheadt->HuffNodeleft, Hcode+="0");
		Hcode.erase(Hcode.size()-1,1);//?
		BuildKey(HuffNodeQheadt->HuffNoderight, Hcode+="1");
	}
}
//----------------------------------------------------------------------------
// WriteHuffTemp: Writes a temporary file of huffman code strings that will 
//				      be read from to encode the compressed file.
//
// @Param: char* WHfusercompress - user file to be compressed
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::WriteHuffTemp(char* WHfusercompress)
{	//Writes a temporary file of huffman code strings that will
	//be read from to encode the compressed file
	infile = fopen(WHfusercompress, "rb");
	outfile = fopen("Hufftemp.txt", "wb");
	char WHTreadchar;
	string HuffKeytemp;
	char bitread, test = 0;
	
	do
	{	//Grabs a character from uncompressed file
		WHTreadchar = fgetc(infile);
		HuffKeytemp = HuffKeymap[WHTreadchar];
		//Borrowed code for converting a string to a char[]
		char* HuffKeytemp2=new char[HuffKeytemp.size()+1];
		HuffKeytemp2[HuffKeytemp.size()]=0;
		memcpy(HuffKeytemp2,HuffKeytemp.c_str(),HuffKeytemp.size());
		//Write that charater's huffman code as a string of 1s and 0s
		fputs(HuffKeytemp2, outfile);
	}while(!feof(infile));
	/*WHTreadchar = psuedoeof;
	HuffKeytemp = HuffKeymap[WHTreadchar];
	char* HuffKeytemp2=new char[HuffKeytemp.size()+1];
	HuffKeytemp2[HuffKeytemp.size()]=0;
	memcpy(HuffKeytemp2,HuffKeytemp.c_str(),HuffKeytemp.size());
	fputs(HuffKeytemp2, outfile);*/
	fclose(infile);
	fclose(outfile);
}
//----------------------------------------------------------------------------
// Compress: Reads from temp file and writes to compressed file. 
//					Calls WriteHeader().
//
// @Param: Cfhuffcompress - user file name choice for compressed file
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::Compress(char* Cfhuffcompress)
{	
	infile = fopen("Hufftemp.txt", "rb");
	outfile = fopen(Cfhuffcompress, "wb");
	
	char Ccodedchar = NULL, Creadchar = NULL;
	int Ccounter = 0, Cheadersize = 0;
	string hcodeheader = "";
	HuffNode* hcodebuilder = HuffNodeQhead;
	
	fputs("000", outfile);

	WriteHeader(hcodebuilder, outfile);
	
	fseek (outfile, 0, SEEK_END);
    Cheadersize=ftell(outfile);
	fseek(outfile, 0, SEEK_SET);
	fputc(Cheadersize/100+48, outfile);
	fputc(Cheadersize%100/10+48, outfile);
	fputc(Cheadersize%10+48,outfile);
	
	fseek(outfile, Cheadersize, SEEK_SET);
	
	do
	{	//Build a character bit by bit based on the
		//1s and 0s in the temporary file
		while(Ccounter<8)
		{	//add a 1 or 0 to the character and
			//bit shift left by one
			Creadchar = fgetc(infile);			
			Ccodedchar += (Creadchar - 48);
			//no bit shift for last time 
			if(Ccounter<7)
				Ccodedchar = Ccodedchar << 1;		
			Ccounter++;
		}
		//Write encoded character to compressed file
		fputc(Ccodedchar, outfile);
		Ccodedchar = NULL;
		Ccounter = 0;

	}while(!feof(infile));
	//pads last character with zeros 
	//i.e. left justifies bit information
	while(Ccounter<8)
	{
		Ccodedchar = Ccodedchar << 1;
		Ccounter++;
	}
	fputc(Ccodedchar, outfile);
	fclose(infile);
	fclose(outfile);
}
//----------------------------------------------------------------------------
// WriteHeader: Serializes Huffman tree in header so that it is stored for  
//					decompression. does so by traversing huff man tree. 
//
// @Param: HuffNode* hcbuild - pointer to a node in huff tree
// @Param: FILE* file        - compressed file(during compression)
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::WriteHeader(HuffNode* hcbuild, FILE* file)
{	
	if(hcbuild->HuffNodeChar != '\0')
	{
		fputc('1', file);
		fputc(hcbuild->HuffNodeChar, file);
	}
	else
	{	
		fputc('0', file);
		WriteHeader(hcbuild->HuffNodeleft, file);
		WriteHeader(hcbuild->HuffNoderight, file);
	}
}
//----------------------------------------------------------------------------
// Decompress: Reads compressed file by character and builds a string
//								from the bit information in the character.
//				When that string exists in our map, prints its character
//												and emptys the string.
//				Map information is stored in the header.
//
//					Calls ReadHeader()
//
// @Param: Dfuserdecompress - user file name choice for file to be decompressed
// @Param: Dfhuffdecompress - user file name choice for decompressed file
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::Decompress(char* Dfuserdecompress, char* Dfhuffdecompress)
{	
	infile = fopen(Dfuserdecompress, "rb");
	outfile = fopen(Dfhuffdecompress, "wb");
	map<char, string>::iterator it;
	int Dheadersize = 0;
	char CompChar, Dbitread;
	string HCodekey = "";

	Dheadersize+=(fgetc(infile)-48)*100;
	Dheadersize+=(fgetc(infile)-48)*10;
	Dheadersize+=(fgetc(infile)-48);
	
	ReadHeader(infile, Dheadersize);
	fseek(infile, Dheadersize, SEEK_SET);

	do
	{	//grab character
		CompChar = fgetc(infile);
		for(int i = 7; i >= 0 ; i--)
		{	//read bits
			Dbitread = CompChar >> i; 
			Dbitread &= 1;
			Dbitread += 48;
			//add bit to string
			HCodekey+= Dbitread;
			//check if string is in the map
			if(HuffKeymap2.count(HCodekey)>0)
			{	//print mapped character
				fputc(HuffKeymap2[HCodekey], outfile);
				HCodekey = ""; // reset string
			}		
		}
	}while(!feof(infile));
	fclose(infile);
	fclose(outfile);
}
//----------------------------------------------------------------------------
// ReadHeader: Confusing method for genrating a new map from information in
//					the header.
//
// @Param: File* file - compressed file
// @Param: int RHheadersize - size of header, determines how long to execute ReadHeader(...)
// @Returns: void
//----------------------------------------------------------------------------
void Huffman::ReadHeader(FILE* file, int RHheadersize)
{	
	int RHcounter = 0;
	char RHreadchar = 0, RHprevreadchar = 0;
	string RHcode = "";
	
	fseek(file, 3, SEEK_SET);
	while(RHcounter < RHheadersize-3)
	{
		RHreadchar = fgetc(file);
		RHcounter++;
		if(RHreadchar == '0')
		{	
			RHcode+='0';
			RHprevreadchar = RHreadchar;
		}
		else if(RHreadchar == '1')
		{	
			HuffKeymap2[RHcode] = fgetc(infile);
			RHcounter++;
			if(RHprevreadchar == '1')
			{
				RHcode.erase(RHcode.size()-1,1);
				while(RHcode.at(RHcode.size()-1) == '1') 
				{	
					RHcode.erase(RHcode.size()-1,1);
					if(RHcode.size()==0)
						break;
				}
		}
		if(RHcode.size()>0)
			RHcode.erase(RHcode.size()-1,1);
		RHprevreadchar = RHreadchar;
		RHcode+='1';
		}
	}
}

Huffman::~Huffman(void)
{
}




	




