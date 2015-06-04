// reading a text file
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
//#incldue <string>
using namespace std;

int main () {
  map<string,int> mymap;
  std::map<string,int>::iterator it;
  string sLong;
  
  ifstream myfile ("test.txt");
  int found;
  char * pch;
  
  if (myfile.is_open())
  {
    while ( getline (myfile,sLong) )
    {
      string sQulity;
      found = sLong.find("x");
      sQulity.append(sLong.begin()+found+1, sLong.end());

      stringstream ss;
      int iQulity;
      int iLong;
      ss << sQulity;
      ss >> iQulity;

      //ss << sLong;
      //ss >> iLong;

      sLong.erase (sLong.begin()+found, sLong.end());

      it=mymap.find(sLong);
      if(it->second == mymap.end()->second)
      	mymap[sLong] = iQulity;
      else
	mymap[sLong] = mymap.find(sLong)->second + iQulity;
    }
    myfile.close();
  }
  
  else cout << "Unable to open file"; 
  
  
  for (map<string,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
  {
    


    std::cout << it->first << " => " << it->second << '\n';


  }
  system("pause");
  return 0;
}
