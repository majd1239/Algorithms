//
//  Dynamic_Programming.cpp
//  Void
//
//  Created by Majd Takieddine on 1/30/17.
//  Copyright © 2017 Majd Takieddine. All rights reserved.
//

#include "Dynamic_Programming.hpp"
#include <string>
#include <vector>
int Memo_Cut_Rod_Aux(int p[], int n, int s[] ,int r[])
{
    int q;
    
    if(r[n]>=0)
        return  r[n];
    if(n==0)
        q=0;
    else
        q=INT_MIN;
    
    for(int i=0;i<n;i++)
    {
        q=max(q,p[i] + Memo_Cut_Rod_Aux( p, n-(i+1), s, r));
        
        if( p[i]+r[n-(i+1)] == q)
            s[n]=i+1;
    }
    
    r[n]=q;
    return q;
}

void Memo_Cut_Rod(int p[], int n)
{
    int r[n+1],s[n+1];
    for(int &x: r) x=INT_MIN;
    for(int &x: s) x=INT_MIN;
    
    int optimal_price=Memo_Cut_Rod_Aux(p,n,s,r);
    
    cout<<"Optimal price is: "<<optimal_price<<endl<<"With cuts at: ";
    
    while (n>0)
    {
        cout<<s[n]<<"  ";
        n=n-s[n];
    }
    cout<<endl;
    
}

int Dynamic_Fib(int n)
{
    int s[n+1];
    s[0]=0; s[1]=1;
    int ans=0;
    for(int i=2;i<=n;i++)
    {
        ans=s[i-1]+s[i-2];
        s[i]=ans;
    }
    
    return s[n];
}
string LCS(string ar1, string ar2)
{
    long size1=ar1.length(), size2=ar2.length();
    
    int table[size1+1][size2+1];
    
    for(int i=0,j=0;i<=size1 || j<=size2; i++,j++)
    { if(i<=size1)
        table[i][0]=0;
        if(j<=size2)
            table[0][j]=0;
    }
  
    for(int i=1; i<=size1; i++)
    {
        for(int j=1; j<=size2; j++)
        {
            if(ar1[i-1]==ar2[j-1])
                table[i][j]=table[i-1][j-1]+1;
            
            else if(table[i-1][j]>=table[i][j-1])
                table[i][j]=table[i-1][j];
            else
                table[i][j]=table[i][j-1];
        }
        
    }
    for(int i=1; i<=size1; i++)
    {cout<<endl;
        for(int j=1; j<=size2; j++)
        {cout<<table[i][j]<<" ";}
    }
    cout<<endl;
    int length=table[size1][size2]; int tl=length;
    cout<<"length"<<length<<endl;
    char result[length];
  
    while(size1 && size2)
    {
        if(ar1[size1-1]==ar2[size2-1])
        {
            result[--length]=ar1[size1-1];
            size1-- ;size2--;
        }
        else if(table[size1-1][size2] >= table[size1][size2-1])
            size1--;
        else
            size2--;
    }
    result[tl]='\0';
    return result;
}


int Knapsack(int val[],int wt[],int n,int W)
{
    int i, w;
    int K[n+1][W+1];
    
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i==0 || w==0)
                K[i][w] = 0;
            else if (wt[i-1] <= w)
                K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
            else
                K[i][w] = K[i-1][w];
        }
    }

    return K[n][W];
    
}


int Max_Inventory(int D[],double h,int s, int size, int cons)
{
    double memo[2][size+1]; int p=0,min=0; int units[size][size];
    
    for(int i=0;i<size;i++)  { units[size][i]=D[size-1]-i; memo[p][i]= (D[size-1]-i)+s; }
    
    units[size][size]=memo[p][size]=0;
    
    for(int i=size-2; i>=0;i--)
    {   p=!p;
        
        for(int j=0;j<=size;j++)
        {
            int max_units=-1;
            
            memo[p][j]=INT_MAX;
            
            while(++max_units<=5)
            {
                int end_inv=j + max_units - D[i];
                
                int cost= !max_units ? 0 : (max_units+s);
                
                if(end_inv <=4 && end_inv>=0)
                {
                    if(memo[p][j] > h*(end_inv)+cost+ memo[!p][end_inv])
                    {
                        memo[p][j] = h*(end_inv)+cost+ memo[!p][end_inv];
                        min=max_units;
                    }
                    cout<<"prv: "<< memo[!p][end_inv]<<" ";
                }
                
            }
            
            units[i][j]=min;
            
            if(!i && !j) break;
        }
    }
    
    return memo[p][0];
}

int interval_coloring(int s[],int f[], int size)
{
    vector<int> a(s,s+size);
    
    sort(a.begin(),a.end(),[](int a,int b){return a<b;});
    
    int count=0;
    for(int i=0,j=0;i<size;i++)
        f[j]>a[i] ? count++ : j++;
    
    return count;
}



