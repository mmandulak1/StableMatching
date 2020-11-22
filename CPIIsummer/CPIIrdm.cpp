#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
//#include "WPCPII.h"

#define N 59
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
int CPII(pair<int, int> matrix[N][N], int matching[N])
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
        //output << endl << "unstable:" << endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                //output << unstablePairs[i][j] << " ";
                if(unstablePairs[i][j]==1)
                    unstableCount++;
            }
            //output << endl;
        }
        //output <<endl;
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



int main()
{
    int highest=-1;
    ofstream output;
    ofstream outputdummy;
    output.open("outputrdm.txt");
    outputdummy.open("outputwhatever.txt");
    pair<int, int> matrix[N][N];
    int preferences[2*N][N];
    int arr[N];
    int matching[N];
    for(int i=0;i<N;i++)
    {
        arr[i]=i+1;
    }
    for(int i=0;i<300000;i++)
    {
        for(int j=0;j<2*N;j++)
        {
            random_shuffle(arr,arr+N);
            for(int k=0;k<N;k++)
            {
                preferences[j][k]=arr[k];
            }
        }
        initializeMatrix(preferences,matrix);
        int iters=CPII(matrix,matching);
        //int iters2=WCPII(matrix);
        if(iters-1>N)
        {
            /*if(iters-1==15)
            {
                CPII(matrix,matching,output);
                printMatrix(matrix,output);
                output.close();
                outputdummy.close();
                return 0;
            }*/
            if(iters-1>highest)
                highest=iters-1;
            cout << "Iterations: " << iters-1<<endl; //" " << iters2-1 << endl;
            //CPII(matrix,matching,output);
            //printMatrix(matrix,output);
            //cout << endl;
            //output.close();
            //outputdummy.close();
            //return 0;
            //printMatrix(matrix,output);
            /*for(int i=0;i<N;i++)
            {
                cout << matching[i] << " ";
            }*/
            //cout <<endl;
        }
    }
    cout<<"Iteration highest: " <<  highest << endl;
    output.close();
    outputdummy.close();
    return 0;
}
