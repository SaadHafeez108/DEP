#include<iostream>
#include<string>
#include<fstream>
using namespace std;
streampos filesize(const string& filepath)
{
	ifstream file(filepath, ios::binary | ios::ate);
	return file.tellg();
}
int main()
{
	ofstream outfile;
	outfile.open("File_1.txt");
	if (outfile.is_open())
	{
		outfile << "AAABBBCCCDDDEEEFFFF";
		outfile.close();
	}
	else
	{
		cerr << "Cannot open file to write";
		return 1;
	}
	streampos o_filesize = filesize("File_1.txt");
	if(o_filesize<=-1)
	{
		cout << "Cannot be able to get the correct size of the file ";
		return 1;
	}
	else
	{
		cout << "Orignal size: " << o_filesize<<" byters\n";
	}
	ifstream readfile;
	readfile.open("File_1.txt");
	ofstream com_file;
	com_file.open("compressed.txt");
	
	if (readfile.is_open() || com_file.is_open())
	{
		char curr_char, pre_char;
		int count = 0;
		readfile.get(pre_char);
		count = 1;
		while (readfile.get(curr_char))
		{
			if (pre_char == curr_char)
			{
				count++;
			}
			else
			{
				com_file << pre_char << count;
				pre_char = curr_char;
				count = 1;
			}
		}
		com_file << pre_char << count;
		readfile.close();
		com_file.close();
	}
	else
	{
		cerr << "Cannot open file!";
		return 1;
	}
	streampos com_filesize = filesize("Compressed.txt");
	if (com_filesize == -1) {
		cerr << "Error getting size of the compressed file!" << endl;
		return 1;
	}
	else {
		cout << "Compressed file size: " << com_filesize << " bytes" << endl;
	}
	return 0;
}