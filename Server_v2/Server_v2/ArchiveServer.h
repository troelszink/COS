#include <vector>
#include "File.h"
#include <fstream>
#include <iostream>
#include "User.h"
#include "UserConnection.h"

using namespace std;

class ArchiveServer : public File, User, UserConnection
{
public:

	ArchiveServer();

	void	userLogin();
	void	userLogout();

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	void constructFile(string name, string address, int root, int fileType, string dataToWrite);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	string searchForFileAddress(string fileName);		// Leder efter adressen på filen med oplyste navn. Hvis filen findes returneres dens fulde adresse.
	void addFile(File f);								// Tilføjer filer til vektoren Files. Her ligger alle filer på serveren.
	void listFiles();									// Skal sende alle filnavne klienten ikke har 
	void   fileOnServer(string fileName);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
	
	void write(string fileName, string dataToWrite);	// Opretter en fil, i første omgang .txt, hvilken der skrives det ønskede indhold til.
	void read(string specificFile);						// Åbner en fil og læser den ind i en stream, hvorefter indholdet gemmes i en string kaldet completeFile.
	void removeFile(string fileName);
	void convertToBinaryString();						// Konverterer stringen completeFile til binær ASCII-repræsentation af indholdets ASCII-værdier, 
														// og gemmer dette i stringen completeFileBinary.
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	string getCompleteFileBinary();						// Anvendes til at hente stringen completeFileBinary.
	string getCompleteFile();			//KIIIG			// KUN TIL TEST
	int	   getFileAmount();

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	~ArchiveServer();

protected:

	vector <File> files;
	string completeFile;
	string completeFileBinary;
	int fileAmount;
	int currentFile;
	int characterAmount;

};

