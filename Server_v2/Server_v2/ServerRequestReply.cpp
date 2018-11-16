#include "ServerRequestReply.h"




ServerRequestReply::ServerRequestReply()
{
}

void ServerRequestReply::extract_Execute()
{
	while (!requestBuffer.empty())
	{
		for (int i = 0; i < requestBuffer.size(); i++)
		{
			string elementS = requestBuffer[i];
			int elementI = elementS[0];


			string command = requestBuffer[i].substr(0, 1);
			if (command == "0")
			{
				listFiles();
			}
			else if (command == "1")
			{
				constructFile(requestBuffer[i].substr(), files[].getName(), 0, 0, );
			}

			else if (command == "2")
			{
				cout << requestBuffer[i].substr(0, 1) << endl;
			}
			else if (command == "3")
			{
				cout << requestBuffer[i].substr(0, 1) << endl;
			}

		}

	}
}

ServerRequestReply::~ServerRequestReply()
{
}
