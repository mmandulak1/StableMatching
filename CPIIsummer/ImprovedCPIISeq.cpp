#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>

#define N 6
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
int CPII(pair<int, int> matrix[N][N])
{
    int malePrefRowVal;
    int malePrefRow;
    int femalePrefColVal;
    int femalePrefCol;

    int femalePrefRowVal;
    int femalePrefRow;
    int malePrefColVal;
    int malePrefCol;

    int maleFemaleRowPosition;
    int femaleMaleColPosition;
    bool femaleFlag=false;
    bool maleFlag=false;
    bool memberShareFlag=false;
    bool matchInColFlag=false;
    int unstableCheckMale;
    int unstableCheckFemale;
    int unstableCount=N*N;
    int iterations=0;
    int matchColIndex;
    int countMaleDom=0;
    int countFemaleDom=0;
    int stableScoreM=0;
    int stableScoreF=0;
    vector<int> inputMatching;
    vector<int> setR;
    vector<int> maleDomPairIndex;
    vector<int> maleFemaleDomPairIndex;
    vector<int> femaleDomPairIndex;
    vector<int> femaleMaleDomPairIndex;
    vector<int> convertMaleIndex;
    int unstablePairs[N][N];
    vector<int> newMatching;

    bool FemalePrefFlag=false;
    double fScore=0;
    double mScore=0;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            inputMatching.push_back(-1);
        }
    }




    while(unstableCount!=0)
    //for(int k=0;k<1;k++)
    {
        unstableCount=0;
        maleDomPairIndex.clear();
        maleFemaleDomPairIndex.clear();
        femaleDomPairIndex.clear();
        femaleMaleDomPairIndex.clear();
        convertMaleIndex.clear();
        countFemaleDom=0;
        countMaleDom=0;
        stableScoreM=0;
        stableScoreF=0;
        for(int i=0;i<N;i++)
        {
            maleFemaleDomPairIndex.push_back(-1);
            femaleMaleDomPairIndex.push_back(-1);
            convertMaleIndex.push_back(-1);
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
        /* cout << "B:";
        for(int i=0;i<N;i++)
        {
            cout << maleDomPairIndex[i] << " ";
        }
        cout << endl; */
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
            {
                maleFemaleDomPairIndex[maleFemaleRowPosition]=femalePrefCol;
                countMaleDom++;
                stableScoreM+=matrix[maleFemaleRowPosition][femalePrefCol].second;
            }
            femaleFlag=false;
        }
        //cout <<"SSM: " << stableScoreM << endl;
        /* cout << "C:";
        for(int i=0;i<maleFemaleDomPairIndex.size();i++)
        {
            cout << maleFemaleDomPairIndex[i] << " ";
        }
        cout << endl;  */


        //FemaleDomPairs

        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(femaleFlag==false && unstablePairs[j][i]==1)
                {
                    femalePrefColVal=matrix[j][i].second;
                    femalePrefCol=j;
                    femaleFlag=true;
                }
                else if(matrix[j][i].second<femalePrefColVal && unstablePairs[j][i]==1 && femaleFlag==true)
                {
                    femalePrefColVal=matrix[j][i].second;
                    femalePrefCol=j;
                }
            }
            if(femaleFlag==true)
                femaleDomPairIndex.push_back(femalePrefCol);
            else
                femaleDomPairIndex.push_back(-1);
            femaleFlag=false;
        }
        /* cout << "D:";
        for(int i=0;i<femaleDomPairIndex.size();i++)
        {
            cout << femaleDomPairIndex[i] << " ";
        }
        cout << endl; */

        //FemaleMaleDomPairs

        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(maleFlag==false && femaleDomPairIndex[j]==i && unstablePairs[i][j]==1)
                {
                    malePrefRowVal=matrix[i][j].first;
                    maleFlag=true;
                    malePrefRow=j;
                    femaleMaleColPosition=i;
                }
                else if(maleFlag==true && femaleDomPairIndex[j]==i && unstablePairs[i][j]==1)
                {
                    if(malePrefRowVal>matrix[i][j].first && unstablePairs[i][j]==1)
                    {
                        malePrefRowVal=matrix[i][j].first;
                        malePrefRow=j;
                        femaleMaleColPosition=i;
                    }
                }
            }
            if(maleFlag==true)
            {
                femaleMaleDomPairIndex[malePrefRow]=femaleMaleColPosition;
                countFemaleDom++;
                stableScoreF+=matrix[femaleMaleColPosition][malePrefRow].first;
            }
            maleFlag=false;
        }
        //cout << "SSF: " << stableScoreF << endl;
        /* cout << "E:";
        for(int i=0;i<femaleMaleDomPairIndex.size();i++)
        {
            cout << femaleMaleDomPairIndex[i] << " ";
        }
        cout << endl; */


        //Convert to male indexing
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(femaleMaleDomPairIndex[j]==i)
                {
                    convertMaleIndex[i]=j;
                }
            }
        }
        /* cout << "mIndex:";
        for(int i=0;i<convertMaleIndex.size();i++)
        {
            cout << convertMaleIndex[i] << " ";
        }
        cout << endl; */
        /*if((countFemaleDom>countMaleDom && countMaleDom!=N) || countFemaleDom==N || stableScoreF<stableScoreM)
        {
            maleFemaleDomPairIndex=convertMaleIndex;
        }*/
        fScore=(double)stableScoreF/countFemaleDom;
        mScore=(double)stableScoreM/countMaleDom;
        if(FemalePrefFlag==true)
        {
            maleFemaleDomPairIndex=convertMaleIndex;
        }
        //else if(iterations==0 && (countFemaleDom>countMaleDom || (countFemaleDom==countMaleDom && stableScoreF<stableScoreM)))
        else if(iterations==0 && (fScore<mScore && mScore-fScore<1))
        {
            maleFemaleDomPairIndex=convertMaleIndex;
            FemalePrefFlag=true;
        }
        //R
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
        /* cout << "R:";
        for(int i=0;i<setR.size();i++)
        {
            cout << setR[i] << " ";
        }
        cout << endl; */
        for(int i=0;i<N;i++)
        {
            if(inputMatching[i]==-1)
                newMatching.push_back(maleFemaleDomPairIndex[i]);
            else if(inputMatching[i]!=-1 && setR[i]==-1)
                newMatching.push_back(inputMatching[i]);
            else if(inputMatching[i]!=-1 && setR[i]!=-1)
                newMatching.push_back(maleFemaleDomPairIndex[i]);
            else
                newMatching.push_back(-1);
        }
        /* cout << "New K:";
        for(int i=0;i<N;i++)
        {
            cout << newMatching[i] << " ";
        }
        cout << endl; */
        iterations++;
        inputMatching=newMatching;
    }
    return iterations;
}

int main()
{
    pair<int, int> matrix[N][N];
    int preferences[2*N][N];/*={
        {2,5,6,3,1,4},
        {6,4,3,1,5,2},
        {1,5,6,4,2,3},
        {6,2,3,1,4,5},
        {4,1,6,5,2,3},
        {3,4,5,6,1,2},
        {1,3,5,2,4,6},
        {6,1,5,3,4,2},
        {6,1,4,2,3,5},
        {3,4,1,5,2,6},
        {2,3,4,1,6,5},
        {1,6,5,2,3,4},
    };*/
    int arr[N];
    int matching[N];
    for(int i=0;i<N;i++)
    {
        arr[i]=i+1;
    }
    for(int i=0;i<1000;i++)
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
        //printMatrix(matrix);
        int iters=CPII(matrix);
        if(iters-1>N)
        { 
            cout << "Iterations: " << iters-1 << endl;
            printMatrix(matrix);
            /*for(int i=0;i<N;i++)
            {
                cout << matching[i] << " ";
            }
            cout <<endl;
        */}
    }
    return 0;
}