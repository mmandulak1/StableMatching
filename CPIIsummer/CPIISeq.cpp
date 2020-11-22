#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
//#include "WPCPII.h"

#define N 20
using namespace std;

int factorial(int n)
{
    if(n==0)
        return 1;
    return n*factorial(n-1);
}
void initializeMatrix(int preferences[2*N][N],pair<int,int> matrix[N][N])
{
    for(int i=0;i<2*N;i++)
        {
            if(i<N)
            {
                for(int j=0;j<N;j++)
                {
                    matrix[i][j].first=preferences[i][j];
                }
            }
            else
            {
                for(int j=0;j<N;j++)
                {
                    matrix[j][i-N].second = preferences[i][j]; 
                }
            }
        }
}
void printMatrix(pair<int,int> matrix[N][N])
{
    for(int i=0;i<N;i++)
    {   
        for(int j=0;j<N;j++)
        {
           cout << matrix[i][j].first << "," << matrix[i][j].second << " ";
        }
        cout << endl;
    }
}
void printMatrix(pair<int,int> matrix[N][N], ofstream &output)
{
    output << endl;
    for(int i=0;i<N;i++)
    {   
        for(int j=0;j<N;j++)
        {
           output << matrix[i][j].first << "," << matrix[i][j].second << " ";
        }
        output << endl;
    }
}
int CPII(pair<int, int> matrix[N][N], int matching[N], ofstream &output)
{
    int malePrefRowVal;
    int malePrefRow;
    int femalePrefColVal;
    int femalePrefCol;
    int maleFemaleRowPosition;
    bool femaleFlag=false;
    bool maleFlag=false;
    bool memberShareFlag=false;
    bool matchInColFlag=false;
    int unstableCheckMale;
    int unstableCheckFemale;
    int unstableCount=N*N;
    int iterations=0;
    int matchColIndex;
    vector<int> inputMatching;
    vector<int> setR;
    vector<int> maleDomPairIndex;
    vector<int> maleFemaleDomPairIndex;
    int unstablePairs[N][N];
    vector<int> newMatching;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            inputMatching.push_back(-1);
        }
    }




    while(unstableCount!=0)
    //for(int k=0;k<5;k++)
    {
        unstableCount=0;
        maleDomPairIndex.clear();
        maleFemaleDomPairIndex.clear();
        for(int i=0;i<N;i++)
        {
            maleFemaleDomPairIndex.push_back(-1);
        }
        setR.clear();
        newMatching.clear();
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                unstablePairs[i][j]=-1;
            }
        }
        if(iterations==0)
        {
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    unstablePairs[i][j]=1;
                }
            }
        }
        else
        {
            for(int i=0;i<N;i++)
            {
                if(inputMatching[i]!=-1)
                {
                    unstableCheckMale=matrix[i][inputMatching[i]].first;
                    unstablePairs[i][inputMatching[i]]=2;
                    for(int j=0;j<N;j++)
                    {
                        if(matrix[i][j].first<unstableCheckMale)
                        {
                            unstablePairs[i][j]=1;
                        }
                        else if(unstablePairs[i][j]!=2)
                        {
                            unstablePairs[i][j]=0;
                        }
                    }
                }
            }
            for(int i=0;i<N;i++)
            {
                for(int k=0;k<N;k++)
                {
                    if(inputMatching[k]==i)
                    {
                        matchInColFlag=true;
                        matchColIndex=k;
                    }
                }
                if(matchInColFlag)
                {
                    unstableCheckFemale=matrix[matchColIndex][i].second;
                    for(int j=0;j<N;j++)
                    {
                        if(matrix[j][i].second<unstableCheckFemale && unstablePairs[j][i]==-1)
                        {
                            unstablePairs[j][i]=1;
                        }
                        else if(unstablePairs[j][i]!=2)
                        {
                            unstablePairs[j][i]=0;
                        }
                    }
                }
                matchInColFlag=false;
            }
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(unstablePairs[i][j]==-1)
                    {
                        unstablePairs[i][j]=1;
                    }
                }
            }
        }
        output << endl << "unstable:" << endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                output << unstablePairs[i][j] << " ";
                if(unstablePairs[i][j]==1)
                    unstableCount++;
            }
            output << endl;
        }
        output <<endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(maleFlag==false && unstablePairs[i][j]==1)
                {
                    malePrefRowVal=matrix[i][j].first;
                    malePrefRow=j;
                    maleFlag=true;
                }
                else if(matrix[i][j].first<malePrefRowVal && unstablePairs[i][j]==1 && maleFlag==true)
                {
                    malePrefRowVal=matrix[i][j].first;
                    malePrefRow=j;
                }
            }
            if(maleFlag==true)
                maleDomPairIndex.push_back(malePrefRow);
            else
                maleDomPairIndex.push_back(-1);
            maleFlag=false;
        }
        /*cout << "B:";
        for(int i=0;i<N;i++)
        {
            cout << maleDomPairIndex[i] << " ";
        }
        cout << endl;*/
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(femaleFlag==false && maleDomPairIndex[j]==i && unstablePairs[j][i]==1)
                {
                    //cout << "Here on iter " << iterations << " with i= " << i << " j= " << j << endl;
                    femalePrefColVal=matrix[j][i].second;
                    femalePrefCol=i;
                    maleFemaleRowPosition=j;
                    femaleFlag=true;
                }
                else if(femaleFlag==true && maleDomPairIndex[j]==i && unstablePairs[j][i]==1)
                {
                    if(femalePrefColVal>matrix[j][i].second && unstablePairs[j][i]==1)
                    {
                        femalePrefColVal=matrix[j][i].second;
                        femalePrefCol=i;
                        maleFemaleRowPosition=j;
                    }
                }
            }
            if(femaleFlag==true)
                maleFemaleDomPairIndex[maleFemaleRowPosition]=femalePrefCol;
            femaleFlag=false;
        }
        /*cout << "C:";
        for(int i=0;i<maleFemaleDomPairIndex.size();i++)
        {
            cout << maleFemaleDomPairIndex[i] << " ";
        }
        cout << endl;*/
        for(int i=0;i<N;i++)
        {
            if(inputMatching[i]!=-1 && maleFemaleDomPairIndex[i]!=-1)
                setR.push_back(inputMatching[i]);
            else
            {
                if(inputMatching[i]==-1)
                {
                    setR.push_back(-1);
                }
                else
                {
                    for(int j=0;j<N;j++)
                    {
                        if(inputMatching[i]==maleFemaleDomPairIndex[j] && i!=j)
                        {
                            setR.push_back(inputMatching[i]);
                            memberShareFlag=true;
                        }
                    }
                    if(memberShareFlag==false)
                    {
                        setR.push_back(-1);
                    }
                    memberShareFlag=false;
                }
                    
            }
        }
        /*cout << "R:";
        for(int i=0;i<setR.size();i++)
        {
            cout << setR[i] << " ";
        }
        cout << endl;*/
        for(int i=0;i<N;i++)
        {
            if(inputMatching[i]==-1)
                newMatching.push_back(maleFemaleDomPairIndex[i]);
            else if(inputMatching[i]!=-1 && setR[i]==-1)
            newMatching.push_back(inputMatching[i]);
            else
                newMatching.push_back(-1);
        }
        /*cout << "New K:";
        for(int i=0;i<N;i++)
        {
            cout << newMatching[i] << " ";
        }
        cout << endl;*/
        iterations++;
        inputMatching=newMatching;
    }
    for(int i=0;i<N;i++)
    {
        matching[i]=newMatching[i]+1;
    }
    return iterations;
}
int CPII(pair<int, int> matrix[N][N])
{
    int malePrefRowVal;
    int malePrefRow;
    int femalePrefColVal;
    int femalePrefCol;
    int maleFemaleRowPosition;
    bool femaleFlag=false;
    bool maleFlag=false;
    bool memberShareFlag=false;
    bool matchInColFlag=false;
    int unstableCheckMale;
    int unstableCheckFemale;
    int unstableCount=N*N;
    int iterations=0;
    int matchColIndex;
    vector<int> inputMatching;
    vector<int> setR;
    vector<int> maleDomPairIndex;
    vector<int> maleFemaleDomPairIndex;
    int unstablePairs[N][N];
    vector<int> newMatching;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            inputMatching.push_back(-1);
        }
    }




    while(unstableCount!=0)
    //for(int k=0;k<5;k++)
    {
        unstableCount=0;
        maleDomPairIndex.clear();
        maleFemaleDomPairIndex.clear();
        for(int i=0;i<N;i++)
        {
            maleFemaleDomPairIndex.push_back(-1);
        }
        setR.clear();
        newMatching.clear();
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                unstablePairs[i][j]=-1;
            }
        }
        if(iterations==0)
        {
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    unstablePairs[i][j]=1;
                }
            }
        }
        else
        {
            for(int i=0;i<N;i++)
            {
                if(inputMatching[i]!=-1)
                {
                    unstableCheckMale=matrix[i][inputMatching[i]].first;
                    unstablePairs[i][inputMatching[i]]=2;
                    for(int j=0;j<N;j++)
                    {
                        if(matrix[i][j].first<unstableCheckMale)
                        {
                            unstablePairs[i][j]=1;
                        }
                        else if(unstablePairs[i][j]!=2)
                        {
                            unstablePairs[i][j]=0;
                        }
                    }
                }
            }
            for(int i=0;i<N;i++)
            {
                for(int k=0;k<N;k++)
                {
                    if(inputMatching[k]==i)
                    {
                        matchInColFlag=true;
                        matchColIndex=k;
                    }
                }
                if(matchInColFlag)
                {
                    unstableCheckFemale=matrix[matchColIndex][i].second;
                    for(int j=0;j<N;j++)
                    {
                        if(matrix[j][i].second<unstableCheckFemale && unstablePairs[j][i]==-1)
                        {
                            unstablePairs[j][i]=1;
                        }
                        else if(unstablePairs[j][i]!=2)
                        {
                            unstablePairs[j][i]=0;
                        }
                    }
                }
                matchInColFlag=false;
            }
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(unstablePairs[i][j]==-1)
                    {
                        unstablePairs[i][j]=1;
                    }
                }
            }
        }
        //cout << endl << "unstable:" << endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                //cout << unstablePairs[i][j] << " ";
                if(unstablePairs[i][j]==1)
                    unstableCount++;
            }
            //cout << endl;
        }
        //cout <<endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(maleFlag==false && unstablePairs[i][j]==1)
                {
                    malePrefRowVal=matrix[i][j].first;
                    malePrefRow=j;
                    maleFlag=true;
                }
                else if(matrix[i][j].first<malePrefRowVal && unstablePairs[i][j]==1 && maleFlag==true)
                {
                    malePrefRowVal=matrix[i][j].first;
                    malePrefRow=j;
                }
            }
            if(maleFlag==true)
                maleDomPairIndex.push_back(malePrefRow);
            else
                maleDomPairIndex.push_back(-1);
            maleFlag=false;
        }
        /*cout << "B:";
        for(int i=0;i<N;i++)
        {
            cout << maleDomPairIndex[i] << " ";
        }
        cout << endl;*/
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(femaleFlag==false && maleDomPairIndex[j]==i && unstablePairs[j][i]==1)
                {
                    //cout << "Here on iter " << iterations << " with i= " << i << " j= " << j << endl;
                    femalePrefColVal=matrix[j][i].second;
                    femalePrefCol=i;
                    maleFemaleRowPosition=j;
                    femaleFlag=true;
                }
                else if(femaleFlag==true && maleDomPairIndex[j]==i && unstablePairs[j][i]==1)
                {
                    if(femalePrefColVal>matrix[j][i].second && unstablePairs[j][i]==1)
                    {
                        femalePrefColVal=matrix[j][i].second;
                        femalePrefCol=i;
                        maleFemaleRowPosition=j;
                    }
                }
            }
            if(femaleFlag==true)
                maleFemaleDomPairIndex[maleFemaleRowPosition]=femalePrefCol;
            femaleFlag=false;
        }
        /*cout << "C:";
        for(int i=0;i<maleFemaleDomPairIndex.size();i++)
        {
            cout << maleFemaleDomPairIndex[i] << " ";
        }
        cout << endl;*/
        for(int i=0;i<N;i++)
        {
            if(inputMatching[i]!=-1 && maleFemaleDomPairIndex[i]!=-1)
                setR.push_back(inputMatching[i]);
            else
            {
                if(inputMatching[i]==-1)
                {
                    setR.push_back(-1);
                }
                else
                {
                    for(int j=0;j<N;j++)
                    {
                        if(inputMatching[i]==maleFemaleDomPairIndex[j] && i!=j)
                        {
                            setR.push_back(inputMatching[i]);
                            memberShareFlag=true;
                        }
                    }
                    if(memberShareFlag==false)
                    {
                        setR.push_back(-1);
                    }
                    memberShareFlag=false;
                }
                    
            }
        }
        /*cout << "R:";
        for(int i=0;i<setR.size();i++)
        {
            cout << setR[i] << " ";
        }
        cout << endl;*/
        for(int i=0;i<N;i++)
        {
            if(inputMatching[i]==-1)
                newMatching.push_back(maleFemaleDomPairIndex[i]);
            else if(inputMatching[i]!=-1 && setR[i]==-1)
            newMatching.push_back(inputMatching[i]);
            else
                newMatching.push_back(-1);
        }
        /*cout << "New K:";
        for(int i=0;i<N;i++)
        {
            cout << newMatching[i] << " ";
        }
        cout << endl;*/
        iterations++;
        inputMatching=newMatching;
    }
    return iterations;
}


int main()
{
    ofstream output;
    output.open("output.txt");
    pair<int, int> matrix[N][N];
    int preferences[2*N][N]={
        {15,12,16,14,19,1,18,17,10,9,3,13,4,7,2,5,8,11,20,6},
        {12,8,19,20,9,16,18,14,5,10,4,15,7,3,17,11,6,2,1,13},
        {2,4,10,15,8,12,17,11,16,5,20,7,13,1,3,14,18,9,6,19},
        {17,11,1,4,12,13,10,18,6,7,8,2,3,14,20,19,16,9,15,5},
        {9,8,11,3,12,17,13,10,1,2,6,16,4,14,5,20,7,19,15,18},
        {19,8,7,13,18,3,12,16,20,10,17,4,5,15,2,6,1,11,9,14},
        {7,17,12,14,16,11,2,9,10,18,8,15,4,5,19,13,6,3,20,1},
        {5,12,14,15,2,20,9,4,13,1,10,6,19,16,8,11,18,3,7,17},
        {5,7,10,4,18,13,8,1,20,9,3,15,2,6,19,17,12,16,14,11},
        {5,6,13,20,10,8,17,4,15,1,12,3,11,18,9,7,2,14,19,16},
        {11,1,17,15,10,18,2,16,4,3,13,6,19,12,7,20,5,14,8,9},
        {5,9,1,2,17,10,20,6,3,18,15,7,14,16,8,13,4,12,19,11},
        {8,10,14,20,12,19,2,17,6,18,15,3,9,5,4,16,11,1,13,7},
        {7,5,12,3,9,14,8,13,17,4,2,16,18,11,1,15,20,19,10,6},
        {8,2,13,12,18,9,7,20,19,5,17,10,1,15,3,16,6,14,4,11},
        {2,11,15,14,16,3,12,19,7,17,9,4,18,6,8,20,5,10,1,13},
        {14,15,2,19,3,12,7,11,4,10,20,16,17,5,1,9,8,18,13,6},
        {14,19,7,18,8,2,5,11,6,13,3,17,15,10,12,4,20,9,16,1},
        {16,6,19,11,14,18,4,20,10,2,5,17,12,1,7,13,3,9,15,8},
        {11,20,7,5,13,14,6,4,19,10,15,3,2,1,9,8,17,12,16,18},
        {5,4,9,7,14,13,12,2,16,3,11,20,10,1,6,15,19,18,8,17},
        {20,10,16,17,11,1,2,13,4,3,5,7,14,6,8,19,15,12,9,18},
        {20,10,2,6,5,14,16,17,3,12,13,7,1,19,8,11,9,18,15,4},
        {13,8,6,9,5,1,16,4,10,14,15,7,20,18,3,2,12,17,19,11},
        {1,6,2,16,8,18,11,10,9,19,20,14,15,17,4,3,7,12,13,5},
        {15,7,3,18,6,2,12,14,11,1,17,5,8,19,4,20,10,9,13,16},
        {11,20,16,18,13,14,19,6,3,7,5,4,17,10,9,15,1,2,8,12},
        {9,10,6,13,5,14,17,19,16,20,1,18,3,7,4,12,11,2,8,15},
        {19,17,9,12,3,5,11,10,4,14,2,7,8,20,18,16,13,6,1,15},
        {5,10,19,15,11,12,16,20,8,9,7,2,4,13,6,17,14,18,3,1},
        {17,3,20,16,6,14,11,2,12,9,1,5,4,13,10,15,18,19,8,7},
        {19,6,5,16,10,20,2,15,8,3,17,9,14,13,7,18,1,4,12,11},
        {6,15,11,2,13,3,17,18,12,5,14,20,1,9,10,4,16,8,19,7},
        {14,2,7,11,17,3,10,12,18,6,15,9,4,19,16,20,8,1,5,13},
        {10,9,16,1,3,14,8,2,7,5,15,19,6,12,20,17,11,4,18,13},
        {15,14,9,5,17,10,7,13,18,3,8,16,19,1,11,4,12,2,20,6},
        {7,1,14,3,19,15,16,18,8,11,5,2,4,9,10,6,13,17,12,20},
        {19,13,8,2,1,3,20,14,7,6,11,18,16,15,10,5,4,9,17,12},
        {16,10,17,2,5,18,19,12,15,20,1,9,7,4,8,14,3,6,13,11},
        {17,1,18,8,2,7,10,15,5,12,9,14,6,20,11,13,4,3,16,19},
    };
    int arr[N];
    int matching[N];
    for(int i=0;i<N;i++)
    {
        arr[i]=i+1;
    }
    for(int i=0;i<1;i++)
    {
        /*for(int j=0;j<2*N;j++)
        {
            random_shuffle(arr,arr+N);
            for(int k=0;k<N;k++)
            {
                preferences[j][k]=arr[k];
            }
        }*/
        initializeMatrix(preferences,matrix);
        int iters=CPII(matrix,matching, output);
        //int iters2=WCPII(matrix);
        if(iters-1==29)
        {
            cout << "Iterations: " << iters-1<<endl; //" " << iters2-1 << endl;
            //printMatrix(matrix);
            printMatrix(matrix,output);
            /*for(int i=0;i<N;i++)
            {
                cout << matching[i] << " ";
            }*/
            //cout <<endl;
            output.close();
            return 0;
        }
    }
    output.close();
    return 0;
}

