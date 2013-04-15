#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <string.h>
#include <math.h>
using namespace std;
set<string> dict;
vector<vector<string> > board;
set<string> words;
int isPrefix(const char *str1);

int main(int argc, char* argv[])
{
	ifstream dictstream(argv[1]);
	ifstream boardstream(argv[2]);
	ofstream wordstream(argv[3]);
	void findWords(string current, unsigned int r, unsigned int c);
	int row;

	if (dictstream) //parse through dictionary, store in set
        {
                string dictword;
		while(getline(dictstream,dictword))
                {

                        for (unsigned int i = 0;i<dictword.length();i++)
                                dictword[i] = tolower(dictword[i]);
                        dict.insert(dictword);
                }
        }

	if (boardstream) //parse through game board store in 2d vector
	{
		board.push_back( vector<string>() );
		string boardrow,columns,tile;
		row = 0;
		int tileat = 0;
		int numtiles = 0;
		double tilesqr = 0;
		while (boardstream >> tile)
			numtiles = numtiles + 1;
		tilesqr = sqrt(numtiles);
		boardstream.clear();
		boardstream.seekg(0,ios::beg);
		while (boardstream >> tile)
		{	
			
			if (tileat >= tilesqr )		
			{
				board.push_back( vector<string>() );
				tileat = 0;
				row++;
			}
			tileat++;
			for (unsigned int i = 0;i < 1;i++)
                  			tile[i] = tolower(tile[i]);
			board[row].push_back(tile);
			
		}	
	}	
		
	for (unsigned int r = 0; r < board.size(); r++)
		for (unsigned int c = 0; c < board[r].size(); c++)
		{
			findWords("",r,c);
			//cout << " at r: " << r << " c: " << c << "  is: " << board[r][c] << endl;
		}
	if (wordstream)
	{
		set<string>::iterator i;
		for (i = words.begin(); i != words.end(); ++i)
			{
				wordstream << *i << endl;
				//cout << *i << endl;
			}
	}
}

void findWords(string current, unsigned int r, unsigned int c)
{
	
	if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size() && board[r][c] != "*" )
	{
		current = current + board[r][c];	
		set<string>::iterator i;
		i = dict.find(current);
		if (i != dict.end()  && current.length() > 3) // check for word atleast 4 letters long and in dictionary
			words.insert(current);	
		string nextCurrent = current;
		nextCurrent[nextCurrent.length() - 1]++;
		i = dict.lower_bound(current);
		if (dict.lower_bound(current) != dict.lower_bound(nextCurrent))/* check for prefix match */
		{		
				/* found closest match */ 
				string temp = board[r][c]; //store current string in temporary variable
				board[r][c] = "*";//mark string as already used
				findWords(current,r-1,c-1); //up to the left
				findWords(current,r-1,c);  //up
				findWords(current,r-1,c+1); //up to the right
				findWords(current,r,c-1); //left
				findWords(current,r,c+1); //right
				findWords(current,r+1,c-1);//down to the left
				findWords(current,r+1,c); //down
				findWords(current,r+1,c+1); //down to the right
				board[r][c] = temp;//restore string 
		}	
	}
}

