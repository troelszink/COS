#include <string>
#include <vector>
#include <iostream>
#include "ArchiveServer.h"

using namespace std;

class ServerRequestReply : public ArchiveServer
{
public:
	ServerRequestReply();

	void extract_Execute();

	~ServerRequestReply();

protected:

	vector <string> requestBuffer;

};

