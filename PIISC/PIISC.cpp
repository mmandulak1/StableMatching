#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <utility>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

//#define N 30
#define maleInitial true
#define femaleInitial true
#define halfInitial true
#define logFemaleInitial true

#define printDebug true
#define CycleDetect true
#define threeInARowCheck true


class PE
{
    private:
        int leftVal;
        int rightVal;
        bool matchingPair = false;
        bool unstablePair = true;
        PE* c_pointer;
        PE* r_pointer;
        PE* nm1ChainPointerRow = this;
        PE* nm1ChainPointerCol = this;
        int matchingPairInCol = -1;
        int matchingPairInRow = -1;
        int matchingPairInColRightVal = -1;
        int matchingPairInRowLeftVal = -1;
        bool nm2gen = false;
        bool nm1Chain = false;
        bool nm1ChainEnd = false;
        int row;
        int col;
        int matchingForIterations = 0;
        int nm1ChainStartIteration = 0;
    public:
        int getLeftVal(){return leftVal;};
        int getRightVal(){return rightVal;};
        bool isMatchingPair(){return matchingPair;};
        bool isUnstablePair(){return unstablePair;};
        PE* getC_pointer(){return c_pointer;};
        PE* getR_pointer(){return r_pointer;};
        PE* getNm1Row_pointer(){return nm1ChainPointerRow;};
        PE* getNm1Col_pointer(){return nm1ChainPointerCol;};
        int getMatchingPairInCol(){return matchingPairInCol;};
        int getMatchingPairInRow(){return matchingPairInRow;};
        int getMatchingPairInColRightVal(){return matchingPairInColRightVal;};
        int getMatchingPairInRowLeftVal(){return matchingPairInRowLeftVal;};
        int getRow(){return row;};
        int getCol(){return col;};
        bool isNm2Generating(){return nm2gen;};
        bool isNm1Chain(){return nm1Chain;};
        bool isNm1ChainEnd(){return nm1ChainEnd;};
        int getMatchingForIterations(){return matchingForIterations;};
        int getNm1ChainStartIteration(){return nm1ChainStartIteration;};
        void setLeftVal(int x){leftVal=x;};
        void setRightVal(int x){rightVal=x;};
        void setMatchingPair(bool x){matchingPair=x;};
        void setUnstablePair(bool x){unstablePair=x;};
        void setC_pointer(PE* x){c_pointer=x;};
        void setR_pointer(PE* x){r_pointer=x;};
        void setNm1Row_pointer(PE* x){nm1ChainPointerRow=x;};
        void setNm1Col_pointer(PE* x){nm1ChainPointerCol=x;};
        void setMatchingPairInCol(int x){matchingPairInCol=x;};
        void setMatchingPairInRow(int x){matchingPairInRow=x;};
        void setMatchingPairInColRightVal(int x){matchingPairInColRightVal=x;};
        void setMatchingPairInRowLeftVal(int x){matchingPairInRowLeftVal=x;};
        void setNm2Generating(bool x){nm2gen=x;};
        void setNm1Chain(bool x){nm1Chain=x;};
        void setNm1ChainEnd(bool x){nm1ChainEnd=x;};
        void setRow(int x){row=x;};
        void setCol(int x){col=x;};
        void incrementMatchingForIterations(){matchingForIterations++;};
        void resetMatchingForIterations(){matchingForIterations=0;};
        void setNm1ChainStartIteration(int x){nm1ChainStartIteration=x;};
    PE(){}
};
int PIISC(vector<vector<PE>> &matrix, int N);
void PrintMatrix(vector<vector<PE>> &matrix, int N)
{
    cout << endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout << matrix[i][j].getLeftVal() << "," << matrix[i][j].getRightVal() << " ";
        }
        cout << endl;
    }
}
void PrintMatchingMatrix(vector<vector<PE>> &matrix, int N)
{
    cout << "Matching Matrix: " << endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout << matrix[i][j].isMatchingPair() << " ";
        }
        cout << endl;
    }
}
void ResetMatrixValues(vector<vector<PE>> &matrix, int N)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            matrix[i][j].setMatchingPair(false);
            matrix[i][j].setMatchingPairInCol(-1);
            matrix[i][j].setMatchingPairInColRightVal(-1);
            matrix[i][j].setMatchingPairInRow(-1);
            matrix[i][j].setMatchingPairInRowLeftVal(-1);
            matrix[i][j].setNm2Generating(false);
            matrix[i][j].setC_pointer(&matrix[i][j]);
            matrix[i][j].setR_pointer(&matrix[i][j]);
            matrix[i][j].setNm1Chain(false);
            matrix[i][j].setNm1ChainEnd(false);
            matrix[i][j].setNm1Col_pointer(&matrix[i][j]);
            matrix[i][j].setNm1Row_pointer(&matrix[i][j]);
            matrix[i][j].setNm1ChainStartIteration(0);
            matrix[i][j].resetMatchingForIterations();
        }
    }
}
void InitializeMatrix(vector<vector<PE>> &matrix, int N)
{
    vector<PE> v1;
    PE temp;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            v1.push_back(temp);
        }
        matrix.push_back(v1);
    }
}
void InitializePreferences(vector<vector<int>> &preferences, int N)
{
    vector<int> v1;
    int temp = -1;
    for(int i=0;i<2*N;i++)
    {
        for(int j=0;j<N;j++)
        {
            v1.push_back(temp);
        }
        preferences.push_back(v1);
    }
}
bool CheckStableMatching(vector<vector<PE>> &matrix, int N)
{
    bool stableMatching = true;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].getLeftVal()>matrix[i][j].getMatchingPairInRowLeftVal() || matrix[i][j].getRightVal()>matrix[i][j].getMatchingPairInColRightVal() || matrix[i][j].isMatchingPair()==true)
            {
                //cout << "pair at" << i << "," << j << " stable compared to row val" << matrix[i][j].getMatchingPairInRowLeftVal() << "and col val " << matrix[i][j].getMatchingPairInColRightVal() <<  endl;
                matrix[i][j].setUnstablePair(false);
            }
            else
            {
                matrix[i][j].setUnstablePair(true);
            }
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].isUnstablePair())
                stableMatching=false;
        }
    }
    return stableMatching;
}

void ClearMatrixMatching(vector<vector<PE>> &matrix, int N)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            matrix[i][j].setMatchingPair(false);
            matrix[i][j].setMatchingPairInCol(-1);
            matrix[i][j].setMatchingPairInColRightVal(-1);
            matrix[i][j].setMatchingPairInRow(-1);
            matrix[i][j].setMatchingPairInRowLeftVal(-1);
        }
    }
}
void InitializeMatrixPrefs(vector<vector<PE>> &matrix, vector<vector<int>> &preferences, int N)
{
    for(int i=0;i<2*N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i>=N)
            {
                matrix[j][i-N].setRightVal(preferences[i][j]);
            }
            else
            {
                matrix[i][j].setLeftVal(preferences[i][j]);
            }
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            matrix[i][j].setRow(i);
            matrix[i][j].setCol(j);
        }
    }
}

void InitializeVector(vector<int> &vect, int size, int x)
{
    vect.clear();
    for(int i=0;i<size;i++)
    {
        vect.push_back(x);
    }
}

void BroadcastMatchingRow(vector<vector<PE>> &matrix,int row, int val, int N)
{
    for(int j=0;j<N;j++)
    {
        matrix[row][j].setMatchingPairInRow(val);
    }
}

void BroadcastMatchingCol(vector<vector<PE>> &matrix, int col, int val, int N)
{
    for(int i=0;i<N;i++)
    {
        matrix[i][col].setMatchingPairInCol(val);
    }
}

void BroadcastMatchingColVal(vector<vector<PE>> &matrix,int col, int val,int N)
{
    for(int i=0;i<N;i++)
    {
        matrix[i][col].setMatchingPairInColRightVal(val);
    }
}

void BroadcastMatchingRowVal(vector<vector<PE>> &matrix, int row, int val, int N)
{
    for(int j=0;j<N;j++)
    {
        matrix[row][j].setMatchingPairInRowLeftVal(val);
    }
}

bool IsCompleteMatching(vector<vector<PE>> &matrix, int N)
{
    vector<int> matchCheck;
    InitializeVector(matchCheck, N, -1);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].isMatchingPair())
            {
                matchCheck[i]=j;
            }
        }
    }
    bool isComplete = true;
    for(int k=0;k<N;k++)
    {
        if(matchCheck[k]==-1)
        {
            isComplete = false;
        }
    }
    return isComplete;
}
void GenerateRandomPreferences(vector<vector<int>> &preferences, int N)
{
    for(int i=0;i<2*N;i++)
    {
        for(int j=0;j<N;j++)
        {
            preferences[i][j]=-1;
        }
    }
    int spot;
    int pref = 1;
    int row = 0;
    int col = 0;
    spot = (rand()%N);
    while(row!=2*N)
    {
        while(pref!=N+1)
        {
            if(preferences[row][spot]==-1)
            {
                preferences[row][spot]=pref;
                pref++;
            }
            spot = (rand()%N);
        }
        pref = 1;
        row++;
    }

}

void InitialMatching(vector<vector<PE>> &matrix, int N)
{
    vector<int> changes;
    bool roundFlag=false;
    int matchingCount=0;
    int maleProp=1;
    while(matchingCount!=N)
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                //if(printDebug)
                    //cout << "i: " << i << " j: " << j << " matchingi: " << matrix[i][j].getMatchingPairInCol() << " matchingj: " << matrix[i][j].getMatchingPairInRow() << endl;
                if(matrix[i][j].getLeftVal()==maleProp && matrix[i][j].getMatchingPairInRow()==-1 && matrix[i][j].getMatchingPairInCol()==-1)
                {
                    matrix[i][j].setMatchingPair(true);
                    BroadcastMatchingCol(matrix,j,i,N);
                    BroadcastMatchingColVal(matrix,j,matrix[i][j].getRightVal(),N);
                    BroadcastMatchingRow(matrix,i,j,N);
                    BroadcastMatchingRowVal(matrix,i,matrix[i][j].getLeftVal(),N);
                    matchingCount++;
                    changes.push_back(j);
                    //cout << "i: " << i << " j: " << j << endl;
                }
                else if(matrix[i][j].getLeftVal()==maleProp && matrix[i][j].getMatchingPairInRow()==-1 && matrix[i][j].getMatchingPairInCol()!=-1)
                {
                    for(int k=0;k<changes.size();k++)
                    {
                        if(changes[k]==j)
                        {
                            roundFlag=true;
                        }
                    }
                    if(matrix[matrix[i][j].getMatchingPairInCol()][j].getRightVal()>matrix[i][j].getRightVal() && roundFlag)
                    {
                        matrix[matrix[i][j].getMatchingPairInCol()][j].setMatchingPair(false);
                        BroadcastMatchingRow(matrix,matrix[i][j].getMatchingPairInCol(),-1,N);
                        BroadcastMatchingRowVal(matrix,matrix[i][j].getMatchingPairInCol(),-1,N);
                        matrix[i][j].setMatchingPair(true);
                        BroadcastMatchingCol(matrix,j,i,N);
                        BroadcastMatchingColVal(matrix,j,matrix[i][j].getRightVal(),N);
                        BroadcastMatchingRow(matrix,i,j,N);
                        BroadcastMatchingRowVal(matrix,i,matrix[i][j].getLeftVal(),N);
                    }
                    roundFlag=false;
                }
            }
        }
        maleProp++;
        changes.clear();
        /* for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                cout << matrix[i][j].isMatchingPair() << " ";
            }
            cout << endl;
        }
        cout << endl;
 */
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].isMatchingPair()==true)
            {
                matrix[i][j].setUnstablePair(false);
            }
        }
    }
}

void HalfInitialMatching(vector<vector<PE>> &matrix, int N)
{
    vector<int> changes;
    bool roundFlag=false;
    int matchingCount=0;
    bool regMatching = false;
    int maleProp=log2(N);
    while(matchingCount!=N)
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                //cout << "i: " << i << " j: " << j << " matchingi: " << matrix[i][j].getMatchingPairInCol() << " matchingj: " << matrix[i][j].getMatchingPairInRow() << endl;
                if(matrix[i][j].getLeftVal()==maleProp && matrix[i][j].getMatchingPairInRow()==-1 && matrix[i][j].getMatchingPairInCol()==-1)
                {
                    matrix[i][j].setMatchingPair(true);
                    BroadcastMatchingCol(matrix,j,i,N);
                    BroadcastMatchingColVal(matrix,j,matrix[i][j].getRightVal(),N);
                    BroadcastMatchingRow(matrix,i,j,N);
                    BroadcastMatchingRowVal(matrix,i,matrix[i][j].getLeftVal(),N);
                    matchingCount++;
                    changes.push_back(j);
                    //cout << "i: " << i << " j: " << j << endl;
                }
                else if(matrix[i][j].getLeftVal()==maleProp && matrix[i][j].getMatchingPairInRow()==-1 && matrix[i][j].getMatchingPairInCol()!=-1)
                {
                    for(int k=0;k<changes.size();k++)
                    {
                        if(changes[k]==j)
                        {
                            roundFlag=true;
                        }
                    }
                    if(matrix[matrix[i][j].getMatchingPairInCol()][j].getRightVal()>matrix[i][j].getRightVal() && roundFlag)
                    {
                        matrix[matrix[i][j].getMatchingPairInCol()][j].setMatchingPair(false);
                        BroadcastMatchingRow(matrix,matrix[i][j].getMatchingPairInCol(),-1,N);
                        BroadcastMatchingRowVal(matrix,matrix[i][j].getMatchingPairInCol(),-1,N);
                        matrix[i][j].setMatchingPair(true);
                        BroadcastMatchingCol(matrix,j,i,N);
                        BroadcastMatchingColVal(matrix,j,matrix[i][j].getRightVal(),N);
                        BroadcastMatchingRow(matrix,i,j,N);
                        BroadcastMatchingRowVal(matrix,i,matrix[i][j].getLeftVal(),N);
                    }
                    roundFlag=false;
                }
            }
        }
        if(!regMatching){
            maleProp=0;
            regMatching=true;
        }
        maleProp++;
        changes.clear();
        /* for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                cout << matrix[i][j].isMatchingPair() << " ";
            }
            cout << endl;
        }
        cout << endl;
 */
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].isMatchingPair()==true)
            {
                matrix[i][j].setUnstablePair(false);
            }
        }
    }
}

void InitialMatchingFemale(vector<vector<PE>> &matrix, int N)
{
    vector<int> changes;
    bool roundFlag=false;
    int matchingCount=0;
    int femaleProp=1;
    while(matchingCount!=N)
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                //cout << "i: " << i << " j: " << j << " matchingi: " << matrix[i][j].getMatchingPairInCol() << " matchingj: " << matrix[i][j].getMatchingPairInRow() << endl;
                if(matrix[j][i].getRightVal()==femaleProp && matrix[j][i].getMatchingPairInRow()==-1 && matrix[j][i].getMatchingPairInCol()==-1)
                {
                    matrix[j][i].setMatchingPair(true);
                    BroadcastMatchingCol(matrix,i,j,N);
                    BroadcastMatchingColVal(matrix,i,matrix[j][i].getRightVal(),N);
                    BroadcastMatchingRow(matrix,j,i,N);
                    BroadcastMatchingRowVal(matrix,j,matrix[j][i].getLeftVal(),N);
                    matchingCount++;
                    changes.push_back(j);
                    //cout << "i: " << i << " j: " << j << endl;
                }
                else if(matrix[j][i].getRightVal()==femaleProp && matrix[j][i].getMatchingPairInRow()!=-1 && matrix[j][i].getMatchingPairInCol()==-1)
                {
                    for(int k=0;k<changes.size();k++)
                    {
                        if(changes[k]==j)
                        {
                            roundFlag=true;
                        }
                    }
                    if(matrix[j][matrix[j][i].getMatchingPairInRow()].getLeftVal()>matrix[j][i].getLeftVal() && roundFlag)
                    {
                        matrix[j][matrix[j][i].getMatchingPairInRow()].setMatchingPair(false);
                        BroadcastMatchingCol(matrix,matrix[j][i].getMatchingPairInRow(),-1,N);
                        BroadcastMatchingColVal(matrix,matrix[j][i].getMatchingPairInRow(),-1,N);
                        matrix[j][i].setMatchingPair(true);
                        BroadcastMatchingCol(matrix,i,j,N);
                        BroadcastMatchingColVal(matrix,i,matrix[j][i].getRightVal(),N);
                        BroadcastMatchingRow(matrix,j,i,N);
                        BroadcastMatchingRowVal(matrix,j,matrix[j][i].getLeftVal(),N);
                    }
                    roundFlag=false;
                }
            }
        }
        femaleProp++;
        changes.clear();
        /* for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                cout << matrix[i][j].isMatchingPair() << " ";
            }
            cout << endl;
        }
        cout << endl;
 */
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].isMatchingPair()==true)
            {
                matrix[i][j].setUnstablePair(false);
            }
        }
    }
}
void LogFemaleInitialMatching(vector<vector<PE>> &matrix, int N)
{
    vector<int> changes;
    bool roundFlag=false;
    int matchingCount=0;
    bool regMatching = false;
    int femaleProp=log2(N);
    while(matchingCount!=N)
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                //cout << "i: " << i << " j: " << j << " matchingi: " << matrix[i][j].getMatchingPairInCol() << " matchingj: " << matrix[i][j].getMatchingPairInRow() << endl;
                if(matrix[j][i].getRightVal()==femaleProp && matrix[j][i].getMatchingPairInRow()==-1 && matrix[j][i].getMatchingPairInCol()==-1)
                {
                    matrix[j][i].setMatchingPair(true);
                    BroadcastMatchingCol(matrix,i,j,N);
                    BroadcastMatchingColVal(matrix,i,matrix[j][i].getRightVal(),N);
                    BroadcastMatchingRow(matrix,j,i,N);
                    BroadcastMatchingRowVal(matrix,j,matrix[j][i].getLeftVal(),N);
                    matchingCount++;
                    changes.push_back(j);
                    //cout << "i: " << i << " j: " << j << endl;
                }
                else if(matrix[j][i].getRightVal()==femaleProp && matrix[j][i].getMatchingPairInRow()!=-1 && matrix[j][i].getMatchingPairInCol()==-1)
                {
                    for(int k=0;k<changes.size();k++)
                    {
                        if(changes[k]==j)
                        {
                            roundFlag=true;
                        }
                    }
                    if(matrix[j][matrix[j][i].getMatchingPairInRow()].getLeftVal()>matrix[j][i].getLeftVal() && roundFlag)
                    {
                        matrix[j][matrix[j][i].getMatchingPairInRow()].setMatchingPair(false);
                        BroadcastMatchingCol(matrix,matrix[j][i].getMatchingPairInRow(),-1,N);
                        BroadcastMatchingColVal(matrix,matrix[j][i].getMatchingPairInRow(),-1,N);
                        matrix[j][i].setMatchingPair(true);
                        BroadcastMatchingCol(matrix,i,j,N);
                        BroadcastMatchingColVal(matrix,i,matrix[j][i].getRightVal(),N);
                        BroadcastMatchingRow(matrix,j,i,N);
                        BroadcastMatchingRowVal(matrix,j,matrix[j][i].getLeftVal(),N);
                    }
                    roundFlag=false;
                }
            }
        }
        if(!regMatching){
            femaleProp=0;
            regMatching=true;
        }
        femaleProp++;
        changes.clear();
        /* for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                cout << matrix[i][j].isMatchingPair() << " ";
            }
            cout << endl;
        }
        cout << endl;
 */
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].isMatchingPair()==true)
            {
                matrix[i][j].setUnstablePair(false);
            }
        }
    }

}

//Need to make vector to pass from PIISC to here (cycleMatching)
//Need to do cycle detection
//Do not need to convert female (already done in PIISCFemale)
int CycleDetection(vector<vector<PE>> &matrix,vector<int> &cycleMatching, vector<int> nm1Pairs, int iterations, int N)
{
    if(iterations==3*N)
    {
        InitializeVector(cycleMatching,N,-1);
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isMatchingPair())
                {
                    cycleMatching[i]=j;
                }
            }
        }
    }
    else
    {
        bool sameMatching = true;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isMatchingPair())
                {
                    matrix[i][j].incrementMatchingForIterations();
                    if(j!=cycleMatching[i])
                        sameMatching = false;
                }
            }
        }
        for(int k=0;k<N;k++)
        {
            if(nm1Pairs[k]!=-1)
            {
                matrix[k][nm1Pairs[k]].setNm1Chain(true);
                matrix[k][nm1Pairs[k]].setNm1ChainStartIteration(iterations);
            }
        }
        //Create chains
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isNm1Chain())
                {
                    //cout << "PE" << i << j << " StartIteration:" << matrix[i][j].getNm1ChainStartIteration() << endl;
                    for(int k=0;k<N;k++)
                    {
                        if(matrix[i][k].isNm1Chain() && matrix[i][k].getNm1ChainStartIteration()==(matrix[i][j].getNm1ChainStartIteration()-1))
                        {
                            //cout << "PE" << i << j << " row linking to PE" << i << k << " on iter " << iterations << endl;
                            matrix[i][j].setNm1Row_pointer(&matrix[i][k]);
                            matrix[i][k].setNm1Row_pointer(&matrix[i][j]);
                        }
                        if(matrix[k][j].isNm1Chain() && matrix[k][j].getNm1ChainStartIteration()==(matrix[i][j].getNm1ChainStartIteration()-1))
                        {
                            //cout << "PE" << i << j << " col linking to PE" << k << j << " on iter " << iterations << endl;
                            matrix[i][j].setNm1Col_pointer(&matrix[k][j]);
                            matrix[k][j].setNm1Col_pointer(&matrix[i][j]);
                        }
                    }
                }
            }
        }
        //Decide on chain ends
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isNm1Chain())
                {   
                    //If the PE has one pointer on itself and the other on another PE
                    if((matrix[i][j].getNm1Col_pointer()==&matrix[i][j] && matrix[i][j].getNm1Row_pointer()!=&matrix[i][j]) || (matrix[i][j].getNm1Col_pointer()!=&matrix[i][j] && matrix[i][j].getNm1Row_pointer()==&matrix[i][j]))
                    {
                        matrix[i][j].setNm1ChainEnd(true);
                    }
                    else if(matrix[i][j].getNm1Col_pointer()==&matrix[i][j] && matrix[i][j].getNm1Row_pointer()==&matrix[i][j])
                    {
                        matrix[i][j].setNm1ChainEnd(true);
                    }
                    else
                    {
                        matrix[i][j].setNm1ChainEnd(false);
                    }
                }
            }
        }
        if(printDebug)
        {
            cout << "Nm1chain matrix on iter " << iterations << endl;
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    cout << matrix[i][j].isNm1Chain() << " ";
                }
                cout << endl;
            }
            cout << "Nm1chainptr on iter " << iterations << endl;
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(matrix[i][j].isNm1Chain())
                        cout << "PE" << i << j << " points to " << (*(matrix[i][j].getNm1Col_pointer())).getRow() << "," << j << " in col and "<< i << "," << (*(matrix[i][j].getNm1Row_pointer())).getCol() << " in row" << endl;
                }
            }
            cout << endl << "Nm1chainend on iter " << iterations << endl; 
            for(int i=0;i<N;i++)
            {
               for(int j=0;j<N;j++)
                {
                    cout << matrix[i][j].isNm1ChainEnd() << " ";
                }
                cout << endl;
            }
        }
        if(threeInARowCheck)
        {
            int countThrees=0;
            //Check rows
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(matrix[i][j].isNm1Chain())
                        countThrees++;
                }
                if(countThrees>2)
                {
                    cout << "Three in a row found" << endl;
                    return -1;
                }
                countThrees=0;
            }
            //Check columns
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(matrix[j][i].isNm1Chain())
                        countThrees++;
                }
                if(countThrees>2)
                {
                    cout << "Three in a column found " << endl;
                    return -1;
                }
                countThrees=0;
            }
        }
        if(sameMatching==true)
        {
            ClearMatrixMatching(matrix,N);
            //Roots
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(matrix[i][j].getMatchingForIterations()==(iterations-3*N))
                    {
                        matrix[i][j].setMatchingPair(true);
                        BroadcastMatchingCol(matrix,j,i,N);
                        BroadcastMatchingRow(matrix,i,j,N);
                        BroadcastMatchingColVal(matrix,j,matrix[i][j].getRightVal(),N);
                        BroadcastMatchingRowVal(matrix,i,matrix[i][j].getLeftVal(),N);
                    }
                }
            }
            //LINK CHAINS
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(matrix[i][j].isNm1ChainEnd())
                    {
                        for(int k=0;k<N;k++)
                        {
                            if(matrix[i][k].isNm1ChainEnd() && k!=j)
                            {
                                matrix[i][j].setNm1Row_pointer(&matrix[i][k]);
                            }
                            if(matrix[k][j].isNm1ChainEnd() && k!=i)
                            {
                                matrix[i][j].setNm1Col_pointer(&matrix[k][j]);
                            }
                        }
                    }
                }
            }
            //cout << "done with linking chain ends " << endl;
            //Cycles
            int switchvar = 0;
            PE* currCyclePE;
            int nm1chainI;
            int nm1chainJ;
            bool firstPE = false;
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    if(matrix[i][j].isNm1Chain())
                    {
                        if(!firstPE)
                        {
                            nm1chainI = i;
                            nm1chainJ = j;
                            firstPE=true;
                        }
                    }
                }
            }
            currCyclePE = &matrix[nm1chainI][nm1chainJ];
            //cout << "Starting at PE" << (*(currCyclePE)).getRow() << (*(currCyclePE)).getCol() << endl;
            //cout << "First nm1Col PE" << (*((*(currCyclePE)).getNm1Col_pointer())).getRow() << (*((*(currCyclePE)).getNm1Col_pointer())).getCol() << endl;
            while((*(currCyclePE)).getNm1Col_pointer()!=&matrix[nm1chainI][nm1chainJ])
            {
                if(switchvar%2==0)
                {
                    //cout << "Adding PE" << (*(currCyclePE)).getRow() << (*(currCyclePE)).getCol() << " to the matching " << endl;
                    (*(currCyclePE)).setMatchingPair(true);
                    BroadcastMatchingCol(matrix,(*(currCyclePE)).getCol(),(*(currCyclePE)).getRow(),N);
                    BroadcastMatchingRow(matrix,(*(currCyclePE)).getRow(),(*(currCyclePE)).getCol(),N);
                    BroadcastMatchingColVal(matrix,(*(currCyclePE)).getCol(),(*(currCyclePE)).getRightVal(),N);
                    BroadcastMatchingRowVal(matrix,(*(currCyclePE)).getRow(),(*(currCyclePE)).getLeftVal(),N);
                    currCyclePE = (*(currCyclePE)).getNm1Row_pointer();
                }
                else
                {
                    currCyclePE = (*(currCyclePE)).getNm1Col_pointer();
                }
                switchvar++;
            }
            return 1;
        }
    }
    return 0;

}
int PIISCFemale(vector<vector<PE>> &matrix, int N)
{
    PE* prevPtr;
    bool stableMatching=true;
    int iterationCount=0;
    vector<int> currentMatching;
    vector <int> cycleMatching;
    InitializeVector(cycleMatching,N,-1);
    while(true){
        //PrintMatchingMatrix(matrix);
        stableMatching=true;
        //Set unstable pairings
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].getLeftVal()>matrix[i][j].getMatchingPairInRowLeftVal() || matrix[i][j].getRightVal()>matrix[i][j].getMatchingPairInColRightVal() || matrix[i][j].isMatchingPair()==true)
                {
                    //cout << "pair at" << i << "," << j << " stable compared to row val" << matrix[i][j].getMatchingPairInRowLeftVal() << "and col val " << matrix[i][j].getMatchingPairInColRightVal() <<  endl;
                    matrix[i][j].setUnstablePair(false);
                }
                else
                {
                    matrix[i][j].setUnstablePair(true);
                }
            }
        }
        //Check for unstable pairings (SM)
        //cout << endl << "unstable pair matrix on " << iterationCount << endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(printDebug)
                    cout << matrix[i][j].isUnstablePair() << " ";
                if(matrix[i][j].isUnstablePair()==true)
                {
                    stableMatching=false;
                }
            }
            if(printDebug)
                cout << endl;
        }
        if(stableMatching==true)
        {
            //cout << "StepsF:" << iterationCount << endl;
            return iterationCount;
        }
        //Find female-dominant unstable pairings
        bool firstFlag=true;
        int colMin=-1;
        int colMinrow=-1;
        vector <int> femaleDominantPairs;
        vector <int> femaleDominantPairsRow;
        InitializeVector(femaleDominantPairs,N,-1);
        InitializeVector(femaleDominantPairsRow,N,-1);
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[j][i].isUnstablePair() && firstFlag==true)
                {
                    colMin=matrix[j][i].getRightVal();
                    colMinrow=j;
                    firstFlag=false;
                }
                else if(matrix[j][i].isUnstablePair() && firstFlag==false)
                {
                    if(colMin>matrix[j][i].getRightVal())
                    {
                        colMin=matrix[j][i].getRightVal();
                        colMinrow=j;
                    }
                }
            }
            femaleDominantPairs[i]=colMin;
            femaleDominantPairsRow[i]=colMinrow;
            firstFlag=true;
            colMin=-1;
            colMinrow=-1;
        }
        if(printDebug)
        {
            cout << "Female Dom Pairs: ";
            for(int i=0;i<femaleDominantPairsRow.size();i++)
            {
                cout << femaleDominantPairsRow[i] << " ";
            }
            //Find male-female-dominant unstable pairings
            cout<<endl << "unstable pairs: " << endl;
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    cout << matrix[i][j].isUnstablePair() << " ";
                }
                cout << endl;
            }
        }
        int rowMin=-1;
        int rowMinCol=-1;
        vector <int> femaleMaleDominantPairs;
        vector <int> femaleMaleDominantPairsPos;
        vector <int> checkPrevPairs;
        InitializeVector(femaleMaleDominantPairs,N,-1);
        InitializeVector(femaleMaleDominantPairsPos,N,-1);
        InitializeVector(checkPrevPairs, N, -1);
        int rowMarker=0;
        firstFlag=true;
        for(int k=0;k<N;k++)
        {
            for(int i=0;i<N;i++)
            {
                if(femaleDominantPairsRow[i]==rowMarker && firstFlag==true)
                {
                    rowMin=matrix[rowMarker][i].getLeftVal();
                    rowMinCol=i;
                    firstFlag=false;
                }
                else if(femaleDominantPairsRow[i]==rowMarker && firstFlag==false)
                {
                    //cout << "here with rowMarker and femaleDom and compare " << rowMarker << " " << femaleDominantPairsRow[i] << " " << matrix[i][rowMarker].getLeftVal()<< endl;
                    //cout << "rowMin: " << rowMin << " compared to " << matrix[i][rowMarker].getLeftVal() << "of pair " << i << "," << rowMarker << endl;
                    if(rowMin>matrix[rowMarker][i].getLeftVal())
                    {
                        rowMin=matrix[rowMarker][i].getLeftVal();
                        //cout << "new row min " << rowMin << endl;
                        rowMinCol=i;
                    }
                }
            }
            firstFlag=true;
            if(rowMinCol!=-1)
                femaleMaleDominantPairsPos[rowMarker]=rowMinCol;
            rowMarker++;
            rowMin=-1;
            rowMinCol=-1;
        }
        if(printDebug)
        {
        cout << endl << "female male dom pairs: ";
            for(int i=0;i<N;i++)
            {
                cout << femaleMaleDominantPairsPos[i] << " ";
            }
        }
        //Set nm2 generating

        for(int i=0;i<N;i++)
        {
            if(femaleMaleDominantPairsPos[i]!=-1)
                matrix[matrix[i][femaleMaleDominantPairsPos[i]].getMatchingPairInCol()][matrix[i][femaleMaleDominantPairsPos[i]].getMatchingPairInRow()].setNm2Generating(true);
        }
        if(printDebug)
        {
            cout << endl << "Nm2 gen matrix: " << endl;
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    cout << matrix[i][j].isNm2Generating() << " ";
                }
                cout << endl;
            }
        }
        //set r and c pointers
        bool rPointerFlag=false;
        bool cPointerFlag=false;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isNm2Generating())
                {
                    for(int l=0;l<N;l++)
                    {
                        if(matrix[l][j].isMatchingPair())
                        {
                            for(int k=0;k<N;k++)
                            {
                                if(matrix[l][k].isNm2Generating())
                                {
                                    cPointerFlag=true;
                                    matrix[i][j].setC_pointer(&matrix[l][k]);
                                }
                            }
                        }
                    }
                    if(!cPointerFlag)
                        matrix[i][j].setC_pointer(&matrix[i][j]);
                    cPointerFlag=false;
                    for(int l=0;l<N;l++)
                    {
                        if(matrix[i][l].isMatchingPair())
                        {
                            for(int k=0;k<N;k++)
                            {
                                if(matrix[k][l].isNm2Generating())
                                {
                                    rPointerFlag=true;
                                    matrix[i][j].setR_pointer(&matrix[k][l]);
                                }
                            }
                        }
                    }
                    if(!rPointerFlag)
                        matrix[i][j].setR_pointer(&matrix[i][j]);
                    rPointerFlag=false;
                }
            }
        }
       /*for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isNm2Generating())
                {   
                    cout << "nm2gen pair at " << (*(matrix[i][j].getC_pointer())).getRow() << "," << (*(matrix[i][j].getC_pointer())).getCol() <<" "<< i << "-" << j << endl;
                    cout << "nm2gen pair at " << (*(matrix[i][j].getR_pointer())).getRow() << "," << (*(matrix[i][j].getR_pointer())).getCol() <<" "<< i << "-" << j << endl;
                }
            }
        }*/

        //check new matching pairs
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isNm2Generating())
                {
                    if((*(matrix[i][j].getR_pointer())).getRow()==matrix[i][j].getRow() && (*(matrix[i][j].getC_pointer())).getRow()==matrix[i][j].getRow())
                    {
                        matrix[i][j].setMatchingPair(true);
                        //cout << "Pair " << i << "," << j << " broadcasting independent nm2" << endl;
                        BroadcastMatchingCol(matrix,j,i,N);
                        BroadcastMatchingRow(matrix,i,j,N);
                        BroadcastMatchingColVal(matrix,j,matrix[i][j].getRightVal(),N);
                        BroadcastMatchingRowVal(matrix,i,matrix[i][j].getLeftVal(),N);
                    }
                    else if((*(matrix[i][j].getR_pointer())).getRow()==matrix[i][j].getRow() && (*(matrix[i][j].getC_pointer())).getRow()!=matrix[i][j].getRow())
                    {
                        //cout << "in with C pointer diff " << i << " " <<  j << endl;
                        while(true)
                        {
                            prevPtr=matrix[i][j].getC_pointer();
                            matrix[i][j].setC_pointer((*(matrix[i][j].getC_pointer())).getC_pointer());
                            if(matrix[i][j].getC_pointer()==prevPtr)
                                break;
                        }
                        matrix[i][(*(matrix[i][j].getC_pointer())).getCol()].setMatchingPair(true);
                        //cout << "Pair " << i << "," << (*(matrix[i][j].getC_pointer())).getCol() << " broadcasting c ptr" << endl;
                        BroadcastMatchingCol(matrix,(*(matrix[i][j].getC_pointer())).getCol(),i,N);
                        BroadcastMatchingRow(matrix,i,(*(matrix[i][j].getC_pointer())).getCol(),N);
                        BroadcastMatchingColVal(matrix,(*(matrix[i][j].getC_pointer())).getCol(),(*(matrix[i][j].getC_pointer())).getRightVal(),N);
                        BroadcastMatchingRowVal(matrix,i,(*(matrix[i][j].getC_pointer())).getLeftVal(),N); 


                        
                    }
                    else if((*(matrix[i][j].getR_pointer())).getRow()!=matrix[i][j].getRow() && (*(matrix[i][j].getC_pointer())).getRow()==matrix[i][j].getRow())
                    {
                        while(true)
                        {
                            prevPtr=matrix[i][j].getR_pointer();
                            matrix[i][j].setR_pointer((*(matrix[i][j].getR_pointer())).getR_pointer());
                            if(matrix[i][j].getR_pointer()==prevPtr)
                                break;
                        }
                        matrix[(*(matrix[i][j].getR_pointer())).getRow()][j].setMatchingPair(true);
                        //cout << "Pair " << (*(matrix[i][j].getR_pointer())).getRow() << "," << j << " broadcasting r ptr" << endl;
                        //cout << "values: " << (*(matrix[i][j].getR_pointer())).getLeftVal() << " " << (*(matrix[i][j].getR_pointer())).getRightVal() << " of pair " << (*(matrix[i][j].getR_pointer())).getCol() << "," << (*(matrix[i][j].getR_pointer())).getRow() << endl;
                        BroadcastMatchingCol(matrix,(*(matrix[i][j].getR_pointer())).getCol(),i,N);
                        BroadcastMatchingRow(matrix,(*(matrix[i][j].getR_pointer())).getRow(),j,N);
                        BroadcastMatchingColVal(matrix,(*(matrix[i][j].getR_pointer())).getCol(),(*(matrix[i][j].getR_pointer())).getRightVal(),N);
                        BroadcastMatchingRowVal(matrix,(*(matrix[i][j].getR_pointer())).getRow(),(*(matrix[i][j].getR_pointer())).getLeftVal(),N);
                    }
                }
            }
        }
        for(int i=0;i<N;i++)
        {
            if(femaleMaleDominantPairsPos[i]!=-1)
            {
                matrix[i][femaleMaleDominantPairsPos[i]].setMatchingPair(true);
                BroadcastMatchingCol(matrix,femaleMaleDominantPairsPos[i],i,N);
                BroadcastMatchingRow(matrix,i,femaleMaleDominantPairsPos[i],N);
                BroadcastMatchingColVal(matrix,femaleMaleDominantPairsPos[i],matrix[i][femaleMaleDominantPairsPos[i]].getRightVal(),N);
                BroadcastMatchingRowVal(matrix,i,matrix[i][femaleMaleDominantPairsPos[i]].getLeftVal(),N);
            }
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isMatchingPair() && (matrix[i][j].getMatchingPairInCol()!=i || matrix[i][j].getMatchingPairInRow()!=j))
                {
                    matrix[i][j].setMatchingPair(false);
                }
            }
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                matrix[i][j].setR_pointer(&matrix[i][j]);
                matrix[i][j].setC_pointer(&matrix[i][j]);
            }
        }
        //Cycle detection
        int cycleResult;
        if(iterationCount>=3*N && CycleDetect)
        {
            cycleResult = CycleDetection(matrix,cycleMatching,femaleMaleDominantPairsPos,iterationCount,N);
            if(cycleResult==1)
                return (-1 * (iterationCount));  
            else if(cycleResult==-1)
                return -999;  
        }
        else if(iterationCount>=3*N && !CycleDetect)
            return -999;
        iterationCount++;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                matrix[i][j].setNm2Generating(false);
            }
        }
        if(printDebug){
            PrintMatchingMatrix(matrix,N);
            cout << endl;
        }
    }
}

int PIISC(vector<vector<PE>> &matrix, int N)
{
    PE* prevPtr;
    bool stableMatching=true;
    int iterationCount=0;
    vector<int> currentMatching;
    vector <int> cycleMatching;
    InitializeVector(cycleMatching,N,-1);
    while(true){
        //PrintMatchingMatrix(matrix);
        stableMatching=true;
        //Set unstable pairings
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].getLeftVal()>matrix[i][j].getMatchingPairInRowLeftVal() || matrix[i][j].getRightVal()>matrix[i][j].getMatchingPairInColRightVal() || matrix[i][j].isMatchingPair()==true)
                {
                    //cout << "pair at" << i << "," << j << " stable compared to row val" << matrix[i][j].getMatchingPairInRowLeftVal() << "and col val " << matrix[i][j].getMatchingPairInColRightVal() <<  endl;
                    matrix[i][j].setUnstablePair(false);
                }
                else
                {
                    matrix[i][j].setUnstablePair(true);
                }
            }
        }
        if(printDebug){
            PrintMatchingMatrix(matrix,N);
            cout << endl;
        }
        //Check for unstable pairings (SM)
        //cout << endl << "unstable pair matrix on " << iterationCount << endl;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(printDebug)
                    cout << matrix[i][j].isUnstablePair() << " ";
                if(matrix[i][j].isUnstablePair()==true)
                {
                    stableMatching=false;
                }
            }
            if(printDebug)
                cout << endl;
        }
        if(stableMatching==true)
        {
            //cout << "StepsM:" << iterationCount << endl;
            return iterationCount;
        }
        //Find male-dominant unstable pairings
        bool firstFlag=true;
        int rowMin=-1;
        int rowMinCol=-1;
        vector <int> maleDominantPairs;
        vector <int> maleDominantPairsCol;
        InitializeVector(maleDominantPairs,N,-1);
        InitializeVector(maleDominantPairsCol,N,-1);
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isUnstablePair() && firstFlag==true)
                {
                    rowMin=matrix[i][j].getLeftVal();
                    rowMinCol=j;
                    firstFlag=false;
                }
                else if(matrix[i][j].isUnstablePair() && firstFlag==false)
                {
                    if(rowMin>matrix[i][j].getLeftVal())
                    {
                        rowMin=matrix[i][j].getLeftVal();
                        rowMinCol=j;
                    }
                }
            }
            maleDominantPairs[i]=rowMin;
            maleDominantPairsCol[i]=rowMinCol;
            firstFlag=true;
            rowMin=-1;
            rowMinCol=-1;
        }
        if(printDebug)
        {
            cout << "Male Dom Pairs: ";
            for(int i=0;i<maleDominantPairsCol.size();i++)
            {
                cout << maleDominantPairsCol[i] << " ";
            }
            //Find male-female-dominant unstable pairings
            cout<<endl << "unstable pairs: " << endl;
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    cout << matrix[i][j].isUnstablePair() << " ";
                }
                cout << endl;
            }
        }

        int colMin=-1;
        int colMinRow=-1;
        vector <int> maleFemaleDominantPairs;
        vector <int> maleFemaleDominantPairsPos;
        vector <int> checkPrevPairs;
        InitializeVector(maleFemaleDominantPairs,N,-1);
        InitializeVector(maleFemaleDominantPairsPos,N,-1);
        InitializeVector(checkPrevPairs, N, -1);
        int colMarker=0;
        for(int k=0;k<N;k++)
        {
            for(int i=0;i<N;i++)
            {
                if(maleDominantPairsCol[i]==colMarker && firstFlag==true)
                {
                    colMin=matrix[i][colMarker].getRightVal();
                    colMinRow=i;
                    firstFlag=false;
                }
                else if(maleDominantPairsCol[i]==colMarker && firstFlag==false)
                {
                    if(colMin>matrix[i][colMarker].getRightVal())
                    {
                        colMin=matrix[i][colMarker].getRightVal();
                        colMinRow=i;
                    }
                }
            }
            firstFlag=true;
            if(colMinRow!=-1)
                maleFemaleDominantPairsPos[colMinRow]=colMarker;
            colMarker++;
            colMin=-1;
            colMinRow=-1;
        }
        if(printDebug)
        {
            cout << endl << "male female dom pairs: ";
            for(int i=0;i<N;i++)
            {
                cout << maleFemaleDominantPairsPos[i] << " ";
            }
        }
        //Set nm2 generating

        for(int i=0;i<N;i++)
        {
            if(maleFemaleDominantPairsPos[i]!=-1)
                matrix[matrix[i][maleFemaleDominantPairsPos[i]].getMatchingPairInCol()][matrix[i][maleFemaleDominantPairsPos[i]].getMatchingPairInRow()].setNm2Generating(true);
        }
        if(printDebug)
        {
            cout << endl << "Nm2 gen matrix: " << endl;
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    cout << matrix[i][j].isNm2Generating() << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        //set r and c pointers
        bool rPointerFlag=false;
        bool cPointerFlag=false;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isNm2Generating())
                {
                    for(int l=0;l<N;l++)
                    {
                        if(matrix[l][j].isMatchingPair())
                        {
                            for(int k=0;k<N;k++)
                            {
                                if(matrix[l][k].isNm2Generating())
                                {
                                    cPointerFlag=true;
                                    matrix[i][j].setC_pointer(&matrix[l][k]);
                                }
                            }
                        }
                    }
                    if(!cPointerFlag)
                        matrix[i][j].setC_pointer(&matrix[i][j]);
                    cPointerFlag=false;
                    for(int l=0;l<N;l++)
                    {
                        if(matrix[i][l].isMatchingPair())
                        {
                            for(int k=0;k<N;k++)
                            {
                                if(matrix[k][l].isNm2Generating())
                                {
                                    rPointerFlag=true;
                                    matrix[i][j].setR_pointer(&matrix[k][l]);
                                }
                            }
                        }
                    }
                    if(!rPointerFlag)
                        matrix[i][j].setR_pointer(&matrix[i][j]);
                    rPointerFlag=false;
                }
            }
        }
       /* for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isNm2Generating())
                {   
                    cout << "nm2gen pair at " << (*(matrix[i][j].getC_pointer())).getRow() << "," << (*(matrix[i][j].getC_pointer())).getCol() <<" "<< i << "-" << j << endl;
                    cout << "nm2gen pair at " << (*(matrix[i][j].getR_pointer())).getRow() << "," << (*(matrix[i][j].getR_pointer())).getCol() <<" "<< i << "-" << j << endl;
                }
            }
        } */

        //check new matching pairs
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isNm2Generating())
                {
                    if((*(matrix[i][j].getR_pointer())).getRow()==matrix[i][j].getRow() && (*(matrix[i][j].getC_pointer())).getRow()==matrix[i][j].getRow())
                    {
                        matrix[i][j].setMatchingPair(true);
                       // cout << "Pair " << i << "," << j << " broadcasting independent nm2" << endl;
                        BroadcastMatchingCol(matrix,j,i,N);
                        BroadcastMatchingRow(matrix,i,j,N);
                        BroadcastMatchingColVal(matrix,j,matrix[i][j].getRightVal(),N);
                        BroadcastMatchingRowVal(matrix,i,matrix[i][j].getLeftVal(),N);
                    }
                    else if((*(matrix[i][j].getR_pointer())).getRow()==matrix[i][j].getRow() && (*(matrix[i][j].getC_pointer())).getRow()!=matrix[i][j].getRow())
                    {
                        //cout << "in with C pointer diff " << i << " " <<  j << endl;
                        while(true)
                        {
                            prevPtr=matrix[i][j].getC_pointer();
                            matrix[i][j].setC_pointer((*(matrix[i][j].getC_pointer())).getC_pointer());
                            if(matrix[i][j].getC_pointer()==prevPtr)
                                break;
                        }
                        matrix[i][(*(matrix[i][j].getC_pointer())).getCol()].setMatchingPair(true);
                        //cout << "Pair " << i << "," << (*(matrix[i][j].getC_pointer())).getCol() << " broadcasting c ptr" << endl;
                        BroadcastMatchingCol(matrix,(*(matrix[i][j].getC_pointer())).getCol(),i,N);
                        BroadcastMatchingRow(matrix,i,(*(matrix[i][j].getC_pointer())).getCol(),N);
                        BroadcastMatchingColVal(matrix,(*(matrix[i][j].getC_pointer())).getCol(),(*(matrix[i][j].getR_pointer())).getRightVal(),N);
                        BroadcastMatchingRowVal(matrix,i,(*(matrix[i][j].getC_pointer())).getLeftVal(),N);


                        
                    }
                    else if((*(matrix[i][j].getR_pointer())).getRow()!=matrix[i][j].getRow() && (*(matrix[i][j].getC_pointer())).getRow()==matrix[i][j].getRow())
                    {
                        while(true)
                        {
                            prevPtr=matrix[i][j].getR_pointer();
                            matrix[i][j].setR_pointer((*(matrix[i][j].getR_pointer())).getR_pointer());
                            if(matrix[i][j].getR_pointer()==prevPtr)
                                break;
                        }
                        matrix[(*(matrix[i][j].getR_pointer())).getRow()][j].setMatchingPair(true);
                        //cout << "Pair " << (*(matrix[i][j].getR_pointer())).getRow() << "," << j << " broadcasting r ptr" << endl;
                        BroadcastMatchingCol(matrix,(*(matrix[i][j].getR_pointer())).getCol(),i,N);
                        BroadcastMatchingRow(matrix,(*(matrix[i][j].getR_pointer())).getRow(),j,N);
                        BroadcastMatchingColVal(matrix,j,(*(matrix[i][j].getR_pointer())).getRightVal(),N);
                        BroadcastMatchingRowVal(matrix,(*(matrix[i][j].getR_pointer())).getRow(),(*(matrix[i][j].getC_pointer())).getLeftVal(),N);
                    }
                }
            }
        }
        for(int i=0;i<N;i++)
        {
            if(maleFemaleDominantPairsPos[i]!=-1)
            {
                matrix[i][maleFemaleDominantPairsPos[i]].setMatchingPair(true);
                BroadcastMatchingCol(matrix,maleFemaleDominantPairsPos[i],i,N);
                BroadcastMatchingRow(matrix,i,maleFemaleDominantPairsPos[i],N);
                BroadcastMatchingColVal(matrix,maleFemaleDominantPairsPos[i],matrix[i][maleFemaleDominantPairsPos[i]].getRightVal(),N);
                BroadcastMatchingRowVal(matrix,i,matrix[i][maleFemaleDominantPairsPos[i]].getLeftVal(),N);
            }
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(matrix[i][j].isMatchingPair() && (matrix[i][j].getMatchingPairInCol()!=i || matrix[i][j].getMatchingPairInRow()!=j))
                {
                    matrix[i][j].setMatchingPair(false);
                }
            }
        }
        //Cycle detection
        int cycleResult;
        if(iterationCount>=3*N && CycleDetect)
        {
            cycleResult = CycleDetection(matrix,cycleMatching,maleFemaleDominantPairsPos,iterationCount,N);
            if(cycleResult==1)
                return (-1 * (iterationCount));
            else if(cycleResult==-1)
                return -999;  
        }
        else if(iterationCount>=3*N && !CycleDetect)
            return -999;

        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                matrix[i][j].setNm2Generating(false);
            }
        }
        //PrintMatchingMatrix(matrix);
        iterationCount++;
    }
}

void PreferencesFromRDMFile(vector<vector<int>> &preferences, int N)
{
    ifstream rdm;
    rdm.open("prefList.txt");
    string inp;
    int num;
    int mIndexRow=0;
    int mIndexCol=0;
    int fIndexRow=N;
    int fIndexCol=0;
    bool turn = true;
    char c;
    while(getline(rdm,inp))
    {
         //cout << inp << endl;
        for(int k=0;k<inp.length();k++)
        {
            c = inp[k];
            //cout << "c:" << c << endl;
            if(c!=' ' && c!= '\n' && c!=',')
            {
                num = c - '0';
                //cout << "num:"<<num<<endl;
                if(turn)
                {
                    preferences[mIndexRow][mIndexCol]=num;
                    mIndexCol++;
                    turn = false;
                }
                else
                {
                    preferences[fIndexRow][fIndexCol]=num;
                    fIndexRow++;
                    turn = true;
                }
            }
        }
        fIndexCol++;
        mIndexRow++;
        fIndexRow=N;
        mIndexCol=0;
    }
    rdm.close();
}

void PrintSteps(int iterations, string indicator)
{
    cout << "Steps" << indicator << ": " << iterations << endl;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    if(argc<3){
        cout << "Missing parameters: (Loop amount, N)" << endl;
        return 1;
    }
    int loopTimes = atoi(argv[1]);
    //cout << "LOOP"<<loopTimes << endl;
    int result;
    int N = atoi(argv[2]);
    vector<vector<int>> preferences;
    vector<vector<PE>> matrix;
    InitializeMatrix(matrix, N);
    InitializePreferences(preferences, N);
    for(int i=0;i<loopTimes;i++)
    {
        ResetMatrixValues(matrix,N);
        GenerateRandomPreferences(preferences,N);
        InitializeMatrixPrefs(matrix,preferences,N);
        if(printDebug)
            PrintMatrix(matrix,N);
        if(maleInitial)
        {
            InitialMatching(matrix,N);
            result = PIISC(matrix,N);
            if(result>-1)
            {
                PrintSteps(result, "M");
                continue;
            }
            if(result!=-999)
            {
                if(IsCompleteMatching(matrix,N))
                {
                    if(CheckStableMatching(matrix,N))
                    {    
                      PrintSteps(-1*result, "M-CD");
                      continue;
                    }
                    PrintMatrix(matrix,N);
                    PrintMatchingMatrix(matrix,N);
                }
            }
        }
        if(femaleInitial)
        {
            ResetMatrixValues(matrix,N);
            InitialMatchingFemale(matrix,N);
            result = PIISCFemale(matrix,N);
            if(result>-1)
            {
                PrintSteps(result, "F");
                continue;
            }
            if(result!=-999)
            {
                if(IsCompleteMatching(matrix,N))
                {
                    if(CheckStableMatching(matrix,N))
                    {    
                      PrintSteps(-1*result, "F-CD");
                      continue;
                    }
                    PrintMatrix(matrix,N);
                    PrintMatchingMatrix(matrix,N);
                }
            }
        }
        if(halfInitial)
        {
            ResetMatrixValues(matrix,N);
            HalfInitialMatching(matrix,N);
            result = PIISC(matrix,N);
            if(result>-1)
            {
                PrintSteps(result, "ML");
                continue;
            }
            if(result!=-999)
            {
                if(CheckStableMatching(matrix,N))
                {    
                    PrintSteps(-1*result, "ML-CD");
                    continue;
                }
                PrintMatrix(matrix,N);
                PrintMatchingMatrix(matrix,N);
            }
        }
        if(logFemaleInitial)
        {
            ResetMatrixValues(matrix,N);
            LogFemaleInitialMatching(matrix,N);
            result = PIISCFemale(matrix,N);
            if(result>-1)
            {
                PrintSteps(result, "FL");
                continue;
            }
            if(result!=-999)
            {
                if(CheckStableMatching(matrix,N))
                {    
                    PrintSteps(-1*result, "FL-CD");
                    continue;
                }
                PrintMatrix(matrix,N);
                PrintMatchingMatrix(matrix,N);
            }
        }
        cout << "Cycle detected after tests" << endl;
        PrintMatrix(matrix,N);
    }
    return 0;
}