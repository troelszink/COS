#include "ArchiveServer.h"
#include <string>
#include <bitset>
#include <stdio.h>

using namespace std;
ArchiveServer::ArchiveServer()
{
	fileAmount = 0;
	characterAmount = 0;
	currentFile = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

void ArchiveServer::constructFile(string name, string address, int root, int fileType, string dataToWrite)
{

	File newFile(name, address, root, fileType, dataToWrite);
	addFile(newFile);
	write(name, dataToWrite);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

string ArchiveServer::searchForFileAddress(string fileName)
{
	string fileAddress;															// Filens addresse i selve server-mappen.
	string fileRootAddress;														// Root-adressen til selve serveren.
	string fileExtension;														// Filens type.

	for (int i = 0; i < fileAmount; i++)										// For-loopet k�rer for alle filer i vektoren Files, 
																				// hvorefter der tjekkes p� om en af dem matcher navnet p� den �nskede fil.
	{

		if (files[i].getName() == fileName)									// Der tjekkes hvorvidt fil i's navn er det samme som den �nskede fils navn.
		{
			fileAddress = files[i].getAddress();
			fileRootAddress = getRootAddress();
			fileExtension = getFileType();
			string fileRAE = fileRootAddress.append(fileAddress).append(fileExtension);
			return fileRAE;														// Returnerer den fulde sti til filen.
		}

	}
}

void ArchiveServer::addFile(File f)
{																				// For hvert fil tilf�jet til vektoren Files, incrementeres fileAmount.
	files.push_back(f);
	fileAmount++;
}

void ArchiveServer::listFiles()
{
	cout << endl << "-----------------------------[Files on server]----------------------------------" << endl;
	for (int i = 0; i < fileAmount; i++)
	{
		cout << "~[ " <<files[i].getAddress() + files[i].getFileType() << " ]~" << endl;
	}
	cout << endl;
}

void ArchiveServer::fileOnServer(string fileNameCon)
{

	for (int i = 0; i < fileAmount; i++)										// For-loopet k�rer for alle filer i vektoren Files, 
																				// hvorefter der tjekkes p� om en af dem matcher navnet p� den �nskede fil.
	{

		if (files[i].getName() == fileNameCon)									// Der tjekkes hvorvidt fil i's navn er det samme som den �nskede fils navn.
		{
			currentFile = i;
		}

	}
}

void ArchiveServer::convertToBinaryString()
{
	int fileLength = completeFile.length();										// fileLength s�ttes lig filens l�ngde, dvs. dens m�ngde af ascii karakterer.
	string binaryString = "";													// En tom string, binaryString, oprettes hvor de l�bende konverterede ascii v�rdier gemmes i.

	for (int i = 1; i <= fileLength; i++)										// For loopet vil forts�tte indtil hele stringen fileLength er l�bet igennem.
	{

		int valueAscii = int(completeFile[fileLength - i]);						// Decimalv�rdien af den nuv�rende ASCII karekter gemmes som en int navngivet, valueAscii. Den sidste char i completeFile gemmes f�rst, grundet konverteringsmetoden fra ASCII til bin�r (omvendt repr�sentation)
		int valueCopy = valueAscii;												// En kopi af valueAscii gemmes i heltallet: valueCopy. 
		string extendedChar = "������";


		while (valueAscii > 0)													// While-loopet forts�tter imens v�rdien af valueAscii er over 0.
		{
			(valueAscii % 2) ? binaryString.push_back('1') :					// Modulus 2 tages af valueAscii, hvis der er rest tilf�jes et "1" til stringen binaryString
				binaryString.push_back('0');									// Ellers hvis resten er 0, tilf�jes et "0" til stringen binary.
			valueAscii /= 2;													// valueAscii s�ttes lig dens halve v�rdi. Dette vil svarer til at shifte den bin�re v�rdi en til h�jre.
		}

		// Da while-loopet ikke tager h�jde for at en ASCII-karakter er 8 bits lang, skal der tjekkes om der mangler 0'er til venstre for det mest betydende bit p� 1
		// for at repr�sentere den korrekte ASCII-karakter.
		if (valueCopy < 128 && valueCopy > 63)
		{
			binaryString.append("0");
		}
		if (valueCopy < 64 && valueCopy>31)
		{
			binaryString.append("00");
		}
		if (valueCopy < 32 && valueCopy > 15)
		{
			binaryString.append("000");
		}
		if (valueCopy < 16 && valueCopy > 7)
		{
			binaryString.append("0000");
		}
		if (valueCopy < 8 && valueCopy > 3)
		{
			binaryString.append("00000");
		}
		if (valueCopy < 4 && valueCopy > 1)
		{
			binaryString.append("000000");
		}
		if (valueCopy < 2 && valueCopy > 0)
		{
			binaryString.append("0000000");
		}

		// �, �, �, �, � og � er ikke tilg�ngelige i C++. Derfor appendes de individuelt til binaryString n�r/hvis de forekommer i en fil.
		/*if (completeFile[fileLength - i] == extendedChar[0])
		{
		binaryString.append("10001001");
		}
		if (completeFile[fileLength - i] == extendedChar[1])
		{
		binaryString.append("01001001");
		}
		if (completeFile[fileLength - i] == extendedChar[2])
		{
		binaryString.append("11011001");
		}
		if (completeFile[fileLength - i] == extendedChar[3])
		{
		binaryString.append("10111001");
		}
		if (completeFile[fileLength - i] == extendedChar[4])
		{
		binaryString.append("01100001");
		}
		if (completeFile[fileLength - i] == extendedChar[5])
		{
		binaryString.append("11110001");
		}*/

	}
	// Pga. m�den elementer tilf�jes til binaryString, vil de v�re i omvendt r�kkef�lge.
	// Den skal derfor vendes.
	reverse(binaryString.begin(), binaryString.end());
	// completeFileBinary s�ttes lig binaryString
	completeFileBinary = binaryString;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//


void ArchiveServer::write(string fileName, string dataToWrite)
{
	string testString = fileName;
	ofstream fileToWrite;														// Opretter en stream, hvori en fil kan �bnes.
	fileToWrite.open(fileName.append(".txt"));									// Den �nskede fil �bnes.
	fileToWrite << dataToWrite;													// Det �nskede data skrives ind i den �bne fil.
	fileToWrite.close();
	fileOnServer(testString);
	logWrite(currentFile,testString);														// Logger p� serveren hvilken fil der er uploadet, og af hvilken klient.
	cout << endl << "-------------------------[File written to server]------------------------------" << endl << endl;
	cout << "~[ " << fileName << ".txt ]~"<< endl;
}

void ArchiveServer::read(string specificFile)
{
	ifstream openFile(searchForFileAddress(specificFile));										// �bner en bestemt fil, specificFile, ind i streamen. 
	string readFile{ istreambuf_iterator<char>(openFile), istreambuf_iterator<char>() };		// Opretter en constructor for en string, hvor hvert char element fra filen appendes til stringen.
	completeFile = readFile;																	// S�tter completeFile lig readFile, hvilket er den l�ste fil.
	convertToBinaryString();
	cout << endl << "--------------------------[File read from server]------------------------------" << endl << endl << "~[ " <<specificFile << ".txt ]~" << endl;
	cout <<endl<< specificFile << " contains:" << endl << completeFile << endl;																// Skal fjernes - kun til test.
	fileOnServer(specificFile);
	logRead(currentFile, specificFile);																	// Logger p� serveren hvilken fil der er downloadet, og af hvilken klient.
}

void ArchiveServer::removeFile(string fileName)
{

	string fileToBeRemoved = searchForFileAddress(fileName);

	const char *fileToBeRemovedConv = fileToBeRemoved.c_str();

	remove(fileToBeRemovedConv);
	fileOnServer(fileName);
	logRemove(currentFile, fileName);																		//Logger p� serveren hvilken fil der er slettet, og af hvilken klient.
	fileOnServer(fileName);
	files.erase(files.begin() + currentFile);
	fileAmount = fileAmount - 1;
	cout << endl << "-------------------------[File removed from server]-----------------------------" << endl;
	cout << "~[ "<< fileName << ".txt ]~"<< endl;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

string ArchiveServer::getCompleteFileBinary()
{
	return completeFileBinary;
}

string ArchiveServer::getCompleteFile()
{
	return completeFile;
}

int ArchiveServer::getFileAmount()
{
	return fileAmount;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

ArchiveServer::~ArchiveServer()
{
}
