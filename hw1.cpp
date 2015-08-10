#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
#include <vector>
#include <time.h>
#include <ctime>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
using namespace std;


void SA(map<string, int>&, map<string, int>&, map<string, vector< vector<int> > >&, map<string, int>&, map<string, int>&, map<string, vector< vector<int> > >&, vector<string>&);
map<string, int> pickOneSolution(map<string, int>, map<string, int>);
void genInitialSolution(map<string, int>&, map<string, int>&, map<string, vector< vector<int> > >&);
void selectAnSolution(map<string, int>&, map<string, int>&, map<string, vector< vector<int> > >&, vector<string>&);
void copySummary(map<string, int>&, map<string, int>&);
void copyResult(map<string, int>&, map<string, int>&);
void copyFinalResult(map<string, vector< vector<int> > >&, map<string, vector< vector<int> > >&);
void changeMaterial(map<string, int>&, vector<int>&, map<string, int>&, map<string, vector< vector<int> > >&);
int GRN(int* number, int small, int big, int iNum);
int iMaterial[3] = {6000, 9000, 12000};
int iCost = 0;
int iTotalCnt = 0;


int main () {


  srand(time(0)+getpid());
  map<string,int> mSummary;
  vector<string> vSummary;
  map<string,int> mResult;
  map<string, int> mCopyResult;
  map<string,int> mCopySummary;
  map<string, vector<vector<int> > > mFinalResult;
  map<string, vector<vector<int> > > mCopyFinalResult;
  vector<vector<int> > v6M;
  vector<vector<int> > v9M;
  vector<vector<int> > v12M;

  //vector<int> v9M;



  
  mResult["6M"] = 0;//initialize
  mResult["9M"] = 0;
  mResult["12M"] = 0;
  mResult["Cost"] = 0;

  mCopyResult["6M"] = 0;//initialize
  mCopyResult["9M"] = 0;
  mCopyResult["12M"] = 0;
  mCopyResult["Cost"] = 0;


  mFinalResult["6M"] = v6M;
  mFinalResult["9M"] = v9M;
  mFinalResult["12M"] = v12M;

  mCopyFinalResult["6M"] = v6M;
  mCopyFinalResult["9M"] = v9M;
  mCopyFinalResult["12M"] = v12M;


  std::map<string,int>::iterator it;
  string sLong;
  int iQulity;
  int iLong;
  int iTotal = 0;
  
  stringstream ssTempQulity, sTempLong;
  
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

      
      
      iQulity = std::stoi (sQulity);


      

      sLong.erase (sLong.begin()+found, sLong.end());

      it=mSummary.find(sLong);
      if(it->second == mSummary.end()->second)
      	mSummary[sLong] = iQulity;
      else
	mSummary[sLong] = mSummary.find(sLong)->second + iQulity;
    }
    myfile.close();
  }
  
  else cout << "Unable to open file"; 
  
  
  for (map<string,int>::iterator it=mSummary.begin(); it!=mSummary.end(); ++it)
  {
    
    sTempLong << it->first;
    sTempLong >> iLong;
    iLong = std::stoi (it->first);
    //cout<<iLong<<endl;
    iTotal = iTotal + iLong * it->second;
    iTotalCnt = iTotalCnt + it->second;
    //cout << it->first << " => " << it->second << '\n';
  }
  //cout<<'\n'<<endl;
  //cout<<"Total = "<<iTotal<<endl;
  //cout<<"TotalCnt = "<<iTotalCnt<<endl;
  
  


  //map<string, int> mTest1;
  SA(mSummary, mResult, mFinalResult, mCopySummary, mCopyResult, mCopyFinalResult, vSummary);

  //vector<vector<int> > vTempVector = mFinalResult["6M"];
  std::ofstream outfile ("result.txt",std::ofstream::binary);
  char* buffer = new char[10];


  vector<vector<int> > vTempFinalResultVector;

  for (map<string,vector<vector<int> > >::iterator it=mFinalResult.begin(); it!=mFinalResult.end(); ++it)
  {

      vTempFinalResultVector = it->second;
      if(it->second.size() != 0)
      {
	  outfile.write (it->first.c_str(), it->first.size());
          cout<<it->first<<endl;
      }

      for (int i=0; i<vTempFinalResultVector.size(); i++)
      {
          for (int j=0;j<vTempFinalResultVector[i].size();j++)
	  {
              std::cout << ' ' << vTempFinalResultVector[i][j];
	      outfile<<endl;
              outfile<<vTempFinalResultVector[i][j];
	  }
    	  outfile<<endl;
	  cout<<endl;
      }
      outfile<<endl;
      cout<<endl;
  }
  outfile<<endl;
  cout<<endl;
cout<<"6M = "<<mResult["6M"]<<endl;
outfile<<"6M = "<<mResult["6M"]<<endl;
cout<<"9M = "<<mResult["9M"]<<endl;
outfile<<"9M = "<<mResult["9M"]<<endl;
cout<<"12M = "<<mResult["12M"]<<endl;
outfile<<"12M = "<<mResult["12M"]<<endl;
cout<<"Cost = "<<mResult["Cost"]<<endl;
outfile<<"Cost = "<<mResult["Cost"]<<endl;


  /*cout<<"Cost: "<<mResult["Cost"]<<endl;
  cout<<"6M:" << mResult["6M"]<<endl;*/


/*  for (map<string,int>::iterator it=mTest1.begin(); it!=mTest1.end(); ++it)
  {
      cout << it->first << " => " << it->second << '\n';
 
  }*/
    
	  
	system("pause");
  return 0;
}

void SA(map<string, int>& mSummary, map<string, int>& mResult, map<string, vector< vector<int> > >& mFinalResult, 
	map<string, int>& mCopySummary, map<string, int>& mCopyResult, map<string, vector< vector<int> > >& mCopyFinalResult,
	vector<string>& vSummary)
{
    double dTempurature = 100000;
    int n[50] = {};
    int iRanNum = GRN(n, 10, 59, 8);
    cout<<"gen a random num: "<<iRanNum<<endl;
    map<string, int> mTest;

    for (map<string,int>::iterator it=mSummary.begin(); it!=mSummary.end(); ++it)
	vSummary.push_back(it->first);
    
    copySummary(mSummary, mCopySummary);
    selectAnSolution(mCopySummary, mResult, mFinalResult, vSummary);
   
  vector<vector<int> > vTempFinalResultVector;

  /*for (map<string,vector<vector<int> > >::iterator it=mFinalResult.begin(); it!=mFinalResult.end(); ++it)
  {

      vTempFinalResultVector = it->second;
      cout<<it->first<<endl;
      for (int i=0; i<vTempFinalResultVector.size(); i++)
      {
          for (int j=0;j<vTempFinalResultVector[i].size();j++)
	  {
              std::cout << ' ' << vTempFinalResultVector[i][j];

	  cout<<"size:"<<vTempFinalResultVector[i].size()<<endl;
	  }
	  cout<<endl;

      }

  cout<<endl;
  }*/

  //cout<<endl;
/*cout<<"6M = "<<mResult["6M"]<<endl;
cout<<"9M = "<<mResult["9M"]<<endl;
cout<<"12M = "<<mResult["12M"]<<endl;
cout<<"Cost = "<<mResult["Cost"]<<endl;*/


    //genInitialSolution(mSummary, mResult, mFinalResult); 

    //copyResult(mResult, mCopyResult);
    //copyFinalResult(mFinalResult, mCopyFinalResult);
    while(dTempurature>500)
    {
	for(int i=0; i<30; i++)
	{
	cout<<"Temp = "<<dTempurature<<endl;
    	    copySummary(mSummary, mCopySummary);

	    for (map<string,int>::iterator it=mSummary.begin(); it!=mSummary.end(); ++it)
		    vSummary.push_back(it->first);
	    selectAnSolution(mCopySummary, mCopyResult, mCopyFinalResult, vSummary);
	    cout<<"new cost = "<<mCopyResult["Cost"]<<endl;
	    cout<<"old cost = "<<mResult["Cost"]<<endl;
	    if(mCopyResult["Cost"] - mResult["Cost"]<0)
	    {
		copyResult(mCopyResult, mResult);
    		copyFinalResult(mCopyFinalResult, mFinalResult);
		mCopyResult.clear();
		mCopyFinalResult.clear();
	    }
	    else
	    {
		double dRanNum = static_cast<double>( 1. * rand() * 100 / (RAND_MAX + 1.))/100;
		//cout<<dRanNum<<"  JDK"<<endl;
		//cout<<exp((mResult["Cost"] - mCopyResult["Cost"])/dTempurature)<<"   ilju"<<endl;
		if(dRanNum < exp((mResult["Cost"] - mCopyResult["Cost"])/dTempurature))
		{
		    copyResult(mCopyResult, mResult);
    		    copyFinalResult(mCopyFinalResult, mFinalResult);
		    mCopyResult.clear();
		    mCopyFinalResult.clear();


		}
		else
		{
		    mCopyResult.clear();
		    mCopyFinalResult.clear();
		}


	    }


	}
	dTempurature = dTempurature * 0.9988;
    }
    


  
	
    //return mResult;

}

void changeMaterial(map<string, int>& mSummary, vector<int>& vSummary, 
	map<string, int>& mResult, map<string, vector< vector<int> > >& mFinalResult)
{
    int iVectorCost = 0;
    vector<vector<int> > vTempFinalResultVector;

    for (map<string,vector<vector<int> > >::iterator it=mFinalResult.begin(); it!=mFinalResult.end(); ++it)
    {

       vTempFinalResultVector = it->second;
       cout<<it->first<<endl;
       for (int i=0; i<vTempFinalResultVector.size(); i++)
       {
           for (int j=0;j<vTempFinalResultVector[i].size();j++)
	   {
               std::cout << ' ' << vTempFinalResultVector[i][j];

	       cout<<"size:"<<vTempFinalResultVector[i].size()<<endl;
	   }
	   cout<<endl;
       }
       cout<<endl;
   }
}


void genInitialSolution(map<string, int>& mSummary, map<string, int>& mResult, map<string, vector< vector<int> > >& mFinalResult)
{
    stringstream ssTempQulity, sTempLong;
    string sLong;
    int iQulity;
    int iLong;
    int iTotal = 0;
    int iCNT = 0;
    int iCostCnt = 1;
    string sCurrntStick;
    vector<int> vTempVector;
 
    int iCurrentCost = 0;
    int iTempCost = 6000;
    mResult["6M"] = mResult["6M"] + 1;

    for (map<string,int>::iterator it=mSummary.begin(); it!=mSummary.end(); ++it)
    {
	iLong = std::stoi (it->first);

        iTotal = iTotal + iLong * it->second;
	cout<<"total = "<<iTotal<<" iLong = "<<iLong<<endl;
	while(iTempCost - iLong*it->second<0)
	{
	    iTempCost = iTempCost + 6000;
	    iCostCnt++;
	}

	if(iTempCost - iLong*it->second >=0)
	{
	    cout<<"before iTempCost = "<<iTempCost<<endl;
	    iTempCost = iTempCost - iLong*it->second;
	    cout<<"after iTempCost = "<<iTempCost<<endl;
	    cout<<"iCurrentCost = "<<iCurrentCost<<endl;
	    iCNT ++;

	    iTempCost = 6000;
	    cout<<"iCostCnt = "<<iCostCnt<<endl;
	    mResult["6M"] = mResult["6M"] + iCostCnt;

	    for(int i=0; i<it->second; i++)
	    {
		//map<string,int>::iterator itFinalResult=mFinalResult.begin();
		vTempVector.push_back(iLong);
		//mFinalResult["6M"].push_back(iLong);

	    }
	    iCostCnt = 1;
            mFinalResult["6M"].push_back(vTempVector);
	    vTempVector.clear();
	    cout<<"SIZE "<<mFinalResult["6M"].size()<<endl;
	    cout<<endl;
	}
	/*else if(iCurrentCost - iLong*it->second < 0)
	{
	    iCost = iCost + iCurrentCost;
	    //cout<<"iCurrentCost = "<<iCurrentCost<<endl;
	    iCurrentCost = 6000;
	    mResult["6M"] = mResult["6M"] + 1;
	    mResult["Cost"] = mResult["Cost"] + iCost;
            mFinalResult["6M"].push_back(vTempVector);
	    vTempVector.clear();
	    for(int i=0; i<it->second; i++)
	    {
		//map<string,int>::iterator itFinalResult=mFinalResult.begin();
		vTempVector.push_back(iLong);
		//mFinalResult["6M"].push_back(iLong);

	    }
	}*/

//	mResult["6M"] = mResult["Cost"] + iCost;
    }

    //mResult["Cost"] = mResult["Cost"] + iCurrentCost;
    //mFinalResult["6M"].push_back(vTempVector);

	    cout<<"ddd "<<mResult["Cost"]<<"  ddd"<<endl;
}

void selectAnSolution(map<string, int>& mCopySummary, map<string, int>& mCopyResult, 
	map<string, vector<vector<int> > >& mCopyFinalResult, vector<string>& vSummary)
{
    int iTempurature = 100;
    int n[50] = {};
    int iSumSize = mCopySummary.size();
    int iRanNum;
    //int iRanNum = GRN(n, 10, 59, iSumSize)-1;
    int iRanNumM = 0;
    int iTempTotalCnt = iTotalCnt;
    vector<int> vTempVector;
    string sStick;
    iCost = 0;

    //cout<<"gen a random num: "<<iRanNum<<endl;
    //cout<<"map size: "<<iSumSize<<endl;

    

    
    /*cout<<iTotalCnt<<" itotal"<<endl;
    for (vector<string>::iterator it=vSummary.begin(); it!=vSummary.end(); ++it)
    {
	std::cout << ' ' << *it;
    }*/

    cout<<endl;

    iRanNumM = static_cast<int>( 1. * rand() * 3 / (RAND_MAX + 1.));
    if(iRanNumM == 0)
        mCopyResult["6M"]++;	
    else if(iRanNumM == 1)
	mCopyResult["9M"]++;
    else if(iRanNumM == 2)
	mCopyResult["12M"]++;

	iCost = iMaterial[iRanNumM];


    while(!vSummary.empty())
    {
	
        iRanNum = static_cast<int>( 1. * rand() * vSummary.size() / (RAND_MAX + 1.));
	sStick = vSummary[iRanNum];
	
	if(iCost - stoi(sStick)>=0)
	{
	    //cout<<"FKNB = "<<sStick<<endl;;

	    iCost = iCost - stoi(sStick);
	    mCopySummary[sStick]--;
	    vTempVector.push_back(stoi(sStick));
	    if(mCopySummary[sStick] == 0)
	    {
		std::vector<string>::iterator it;
         	it = find (vSummary.begin(), vSummary.end(), vSummary[iRanNum]);
	        //cout<<*it<<endl;
	        vSummary.erase(it);
                /*for (vector<string>::iterator it=vSummary.begin(); it!=vSummary.end(); ++it)
                {
                	std::cout << ' ' << *it;
                }*/
	    }
	    /*for (vector<int>::iterator it=vTempVector.begin(); it!=vTempVector.end(); ++it)
            {
                	std::cout << ' ' << *it;
            }
	    cout<<endl;*/

	}
	else
	{
	    mCopyResult["Cost"] = mCopyResult["Cost"] + iCost;
	    if(iRanNumM == 0)
            	mCopyFinalResult["6M"].push_back(vTempVector);
	    else if(iRanNumM == 1)
            	mCopyFinalResult["9M"].push_back(vTempVector);
	    else if(iRanNumM == 2)
            	mCopyFinalResult["12M"].push_back(vTempVector);
	    vTempVector.clear();
	    iRanNumM = static_cast<int>( 1. * rand() * 3 / (RAND_MAX + 1.));
            if(iRanNumM == 0)
		mCopyResult["6M"]++;	
	    else if(iRanNumM == 1)
		mCopyResult["9M"]++;
    	    else if(iRanNumM == 2)
		mCopyResult["12M"]++;


	    iCost = iMaterial[iRanNumM];


//	    mCopyFinalResult

	}

	iTempTotalCnt--;

    }
    //cout<<"last cost ======= "<<iCost<<endl;
    //cout<<"last cost ======= "<<iRanNumM<<endl;

    mCopyResult["Cost"] = mCopyResult["Cost"] + iCost;
    if(iRanNumM == 0)
	mCopyFinalResult["6M"].push_back(vTempVector);
    else if(iRanNumM == 1)
        mCopyFinalResult["9M"].push_back(vTempVector);
    else if(iRanNumM == 2)
	mCopyFinalResult["12M"].push_back(vTempVector);
    vTempVector.clear();

  /*vector<vector<int> > vTempFinalResultVector;
  cout<<endl;
for (map<string,vector<vector<int> > >::iterator it=mCopyFinalResult.begin(); it!=mCopyFinalResult.end(); ++it)
  {

      vTempFinalResultVector = it->second;
      for (int i=0; i<vTempFinalResultVector.size(); i++)
      {
          for (int j=0;j<vTempFinalResultVector[i].size();j++)
	  {
              std::cout << ' ' << vTempFinalResultVector[i][j];

	  cout<<"size:"<<vTempFinalResultVector[i].size()<<endl;
	  }
	  cout<<endl;

      }

  cout<<endl;
  }
cout<<"6M = "<<mCopyResult["6M"]<<endl;
cout<<"9M = "<<mCopyResult["9M"]<<endl;
cout<<"12M = "<<mCopyResult["12M"]<<endl;
cout<<"Cost = "<<mCopyResult["Cost"]<<endl;
*/
}



void copyResult(map<string, int>& mResult, map<string, int>& mCopyResult)
{
    mCopyResult.clear();
    mCopyResult["6M"] = mResult["6M"];//initialize
    mCopyResult["9M"] = mResult["9M"];
    mCopyResult["12M"] = mResult["12M"];
    mCopyResult["Cost"] = mResult["Cost"];


}

void copyFinalResult(map<string, vector<vector<int> > >& mFinalResult, map<string, vector<vector<int> > >& mCopyFinalResult)
{
    mCopyFinalResult.clear();
    mCopyFinalResult["6M"] = mFinalResult["6M"];//initialize
    mCopyFinalResult["9M"] = mFinalResult["9M"];
    mCopyFinalResult["12M"] = mFinalResult["12M"];


}


void copySummary(map<string, int>& mSummary, map<string, int>& mCopySummary)
{
    mCopySummary.clear(); 
    mCopySummary.insert(mSummary.begin(), mSummary.end());

/*  for (map<string,int>::iterator it=mCopySummary.begin(); it!=mCopySummary.end(); ++it)
  {
    
    cout << it->first << " => " << it->second << '\n';
  }*/


}



int GRN(int* number, int small, int big, int iNum)
{//產生 small~big 的亂數 
    //srand(time(NULL));
    int n1=0, n2=0, temp=0;
    for(int i=0;i<big-small+1;i++)
    {//數字分配 0~big-small 
	number[i]=i;
    }
    for(int i=0;i<big-small+1;i++)
    {//兩兩交換 
	n1=rand()%(big-small+1);
        n2=rand()%(big-small+1);
        temp=number[n1];
        number[n1]=number[n2];
        number[n2]=temp;
    }
    for(int i=0;i<big-small+1;i++)
    {//數字位移 small~big 
	number[i]+=small;
    }
/*    for(int i=0;i<big-small+1;i++)
    {//數字列印    
	cout<<number[i]%iNum+1<<' ';
        if(i%10==9)  
	    cout<<endl;
    }*/


    n1=rand()%(big-small+1);
    //cout<<"number = "<<number[n1]%iNum+1<<endl;
    //cout<<endl;
    return number[n1]%iNum+1;
}


