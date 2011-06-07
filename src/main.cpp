#include <stdio.h>
#include <string>
#include <exception>

#include "md2/md2.h"

int main(int argc, char **argv)
{
	printf("MD2-to-MESH Converter\n");

	if (argc == 1)
	{
		printf("Usage: md2tomesh.exe [inputfile]\n\n");
		return 1;
	}

	std::string file = argv[1];
	std::string extension;

	try
	{
		extension = file.substr(file.find_last_of('.'), std::string::npos);
		for (int i = 0; i < extension.size(); ++i)
			extension[i] = tolower(extension[i]);
	}
	catch (std::exception &e)
	{
		extension = "";
	}

	std::string meshFile = "";
	if (extension.length() > 0)
	{
		meshFile = file;
		meshFile.erase(meshFile.find_last_of('.'), std::string::npos);
		meshFile.append(".mesh");
	}

	Md2 *md2 = new Md2();
	if (!md2->Load(file))
	{
		printf("Error loading MD2 file.\n\n");
		return 1;
	}
	if (!md2->ConvertToMesh(meshFile))
	{
		printf("Error converting MD2 to MESH.\n\n");
		return 1;
	}

	printf("Finished converting to %s\n", meshFile.c_str());

	return 0;

}
