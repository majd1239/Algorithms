//
//  dd.h
//  Void
//
//  Created by Majd Takieddine on 12/23/16.
//  Copyright © 2016 Majd Takieddine. All rights reserved.
//

#ifndef algos_h
#define algos_h

#include <iostream>
#include "Linked_List.hpp"
#include<vector>
#include <random>
#include <ctime>


using namespace std;
int static heap_size=8;

int parent(int index, int k){ return index==0? 0 : (index-1)/k ; }

int child(int index, int k, int child_num){ return (k*index + child_num);}


void selection_sort(int list[],int size){
    
    for(int i=0;i<size-1;i++){
        int min=i;
        for(int j=i+1;j<size;j++)
            if(list[j]<list[min]) min=j;
        
        if(min!=i){
            swap(list[i],list[min]);
        }
    }
    
}
void bubble_sort(int list[], int size){
    
    
    while(--size>0){
        bool sorted=true;
        
        for(int i=0;i<size;i++)
            if(list[i]>list[i+1])
            {
                swap(list[i],list[i+1]);
                sorted=false;
            }
        
        if(sorted) break;
    }
    
}
void insertion_sort(int list[], int size){
    
    if(size == 1) return;
    
    insertion_sort(list, size-1);
    
    int value=list[size-1], i=size-2;
    while(i>=0 && value<list[i])
    {
        list[i+1]=list[i];
        i--;
    }
    list[i+1]=value;
    
    
}

void Heap_Sort(int A[], int size)
{
    
    Build_Max_Heap(A, size);
    
    for(int i=size;i>0;i--){
        swap(A[0],A[i]);
        Max_Heap(A, 0, i-1);
    }
    
}
void merge(int list[],int start, int mid, int end){
    
    
    int *L=new int[mid-start];
    int *R=new int[end-mid];
    
    for(int i=0;i<mid-start;i++) L[i]=list[i+start];
    for(int i=0;i<end-mid;i++) R[i]=list[i+mid];
    
    int i=0,j=0,k=start;
    
    while(i<mid-start && j<end-mid){
        
        if(R[j]<L[i]){
            
            list[k]=R[j];
            j++;
            
        }
        else
        {
            list[k]=L[i];
            i++;
        }
        k++;
    }
    while(i<mid-start){
        list[k]=L[i]; i++;k++;
    }
    while(j<end-mid){
        list[k]=R[j]; j++;k++;
    }
    delete [] L; delete [] R;
    
}


void mergesort(int list[], int size, int start=0){
    
    if ((size-start)<2) return;
    
    int mid=((size-start)/2)+start;
    
    mergesort(list,mid,start);
    mergesort(list,size,mid);
    merge(list,start,mid,size);
}

void quicksort(int a[],int start, int end){
    
    while(start<end-1)
    {
        swap(a[random_pivot(start,end-1)],a[end-1]);
        int pivot=start-1;
        
        for(int i=start;i<end-1;i++)
        {
            if(a[end-1]>=a[i])
                if(++pivot!=i) swap(a[i],a[pivot]);
        }
        
        swap(a[++pivot],a[end-1]);
        
        if( end-pivot-1 >= pivot-start) {
            quicksort(a, start, pivot);
            start=pivot+1;
        }
        else {
            quicksort(a,pivot+1,end);
            end=pivot;
        }
        
    }
}

void bucket_sort(double ar[], int size)
{
    
    Linked_List<double> *buckets=new Linked_List<double> [size]();
    
    for(int i=0;i<size;i++)
        buckets[int( size* ar[i] )].insert(ar[i]);
    
    for(int i=0;i<size;i++)
        if(buckets[i].length()!=0)
            buckets[i].sort();
    
    int start=-1;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<buckets[i].length();j++)
            ar[++start]=(buckets[i].pop(j));
    }
    
    delete [] buckets;
}
void radix_counting(int a[], int size, int exp)
{
    int C[10]={0};
    int output[size];
    
    for(int i=0;i<size;i++)
        C[(a[i]/exp) % 10]++;
    
    for(int i=1;i<10;i++)
        C[i]+=C[i-1];
    
    for(int i=size-1; i>=0; i--)
    {
        output[C[(a[i]/exp) % 10]-1]=a[i];
        C[(a[i]/exp) % 10]--;
    }
    
    for(int i=0;i<size;i++)
        a[i]=output[i];
    
}
void radix_sort(int a[], int size)
{
    int max= max_(a,size);
    
    for(int i=1; max/i>0; i*=10)
        radix_counting(a, size, i);
}

void build_indices(int a[],int C[],int** indices ,int &i)
{
    if(indices[a[i]]==NULL){
        indices[a[i]]=new int[C[a[i]]+2];
        indices[a[i]][0]=1;
        indices[a[i]][1]=2;
        indices[a[i]][2]=i;
        
    }
    else
        indices[a[i]][++(indices[a[i]][1])]=i;
}

void swap_and_update(int a[],int &i,int &j, int &start, int **indices)
{
    swap(a[++start],a[indices[i][++j]]);
    if(start!=indices[i][j])
    {
        if((indices[a[indices[i][j]]][0])+1 <= indices[a[indices[i][j]]][1] )
            (indices[a[indices[i][j]]][0])++;
        
        indices[ a[indices[i][j]] ][ indices[a[indices[i][j]]][0] ]=indices[i][j];
    }
}

void index_sorting(int a[],int size, int k)
{
    int* C=new int[k+1]{};
    
    for(int i=0; i<size; i++) C[a[i]]++;
    
    int* *indices=new int*[k+1]();
    
    for(int i=0;i<size;i++)
        build_indices(a, C,indices,i);
    
    int start=-1,i=0,j=1;
    
    while(i<=k)
    {
        if(--C[i]>=0)
            swap_and_update(a, i, j, start, indices);
        else
        {   delete [] indices[i];
            i++;
            j=1;
        }
        
    }
    
    delete[] indices;
    delete[] C;
}

int binarysearch(int a[], int value, int size, int start=0){
    
    if( size-start>1 ){
        int midpoint=(size+start)/2;
        
        if (a[midpoint]==value) return midpoint;
        
        else
            if (value<a[midpoint]) return binarysearch(a, value, midpoint,start);
        
            else
                return binarysearch(a, value, size, midpoint);
    }
    
    return -1;
    
    
}
struct trouple{
    int left;
    int right;
    int sum;
};

trouple crossover_sub(int a[],int start,int end, int mid){
    
    int left_max_sum=INT_MIN, right_max_sum=INT_MIN, sum=0;
    trouple ret{0,0,0};
    
    for(int i=mid; i>=start; i--)
    {
        sum+=a[i];
        
        if(sum>left_max_sum)
        {
            left_max_sum=sum;
            ret.left=i;
        }
    }
    
    sum=0;
    
    for(int j=mid+1; j<=end; j++)
    {
        sum+=a[j];
        
        if(sum>right_max_sum)
        {
            right_max_sum=sum;
            ret.right=j;
        }
    }
    
    ret.sum=right_max_sum+left_max_sum;
    
    return ret;
}

trouple maxsub(int a[],int start, int end){
    
    trouple empty{0,0,0};
    
    if(end-start<1){
        trouple rec={start,end,a[start]};
        return rec;
    }
    else
    {
        int mid=(start+end)/2;
        
        trouple first_half=maxsub(a, start, mid);
        trouple second_half=maxsub(a,mid+1,end);
        trouple crossover=crossover_sub(a,start,end,mid);
        
        
        if(first_half.sum>=second_half.sum && first_half.sum>crossover.sum)
        {
            if(first_half.sum<0) return empty;
            else
                return first_half;
        }
        
        else if(second_half.sum>=first_half.sum && second_half.sum>crossover.sum)
        {
            if(second_half.sum<0) return empty;
            else
                return second_half;
        }
        else
            return crossover;
        
    }
    
}

trouple maxsub_brutal_force(int a[], int left, int right)
{
    int largest=INT_MIN;
    trouple ret{0,0,0};
    int sum=0;
    for (int i=left;i<right;i++)
    {   sum=a[i];
        for(int j=i+1;j<right;j++)
        {
            if(sum>largest){
                ret.left=i;
                ret.right=j-1;
                largest=sum;
            }
            sum+=a[j];
        }
    }
    
    ret.sum=largest;
    
    return ret;
    
}
trouple linear_max_sub(int a[], int start, int end)
{
    trouple max_sub={0,0,a[0]};
    
    int temp_sum=0,temp_left=0;
    
    for(int i=start;i<end;i++)
    {
        temp_sum = (  a[i] > (temp_sum + a[i]) ?  a[i] : temp_sum + a[i]);
        
        if(temp_sum > max_sub.sum){
            
            max_sub.sum=temp_sum;
            max_sub.right=i;
            max_sub.left=temp_left;
        }
        if(temp_sum==a[i]){
            temp_left=i;
        }
    }
    
    return max_sub;
}


void Max_Heap(int A[],int index,int size){
    
    int left_child=(index*2);
    int right_child=(index*2)+1;
    int largest=index;
    
    if(size>=left_child &&  A[left_child]>A[index])
        largest=left_child;
    
    if(size>=right_child && A[right_child]>A[largest])
        largest=right_child;
    
    if(largest!=index)
    {
        swap(A[largest],A[index]);
        Max_Heap(A, largest, size);
    }
    
}
void Build_Max_Heap(int A[],int size){
    
    for(int i=(size/2)-1;i>=0;i--)
        Max_Heap(A, i, size);
    
}

int Extract_Max(int a[])
{
    int max=a[0];
    a[0]=a[heap_size];
    heap_size--;
    Max_Heap(a, 0, heap_size);
    
    return max;
    
}
void Increase_Key(int a[],int index,int key){
    
    if(key<a[index]){
        cout<<"Error, new key is smaller than current key."<<endl;
        return;
    }
    int i=index;
    for(;i>0 && key>a[parent(i,2)]; i=(i+1)/2-1)
        a[i]=a[parent(i,2)];
    
    a[i]=key;
}
void Insert_Key(int a[],int key){
    
    heap_size++;
    
    a[heap_size]=INT_MIN;
    
    Increase_Key(a,heap_size,key);
}

void d_ary_max(int A[],int k, int index,int size){
    
    int largest=index;
    
    for(int i=1;i<=k;i++)
        if(size>=child(index, k, i) && A[child(index, k, i)]>A[largest])
            largest=child(index,k,i);
    
    if(largest!=index)
    {
        swap(A[largest],A[index]);
        d_ary_max(A,k, largest, size);
    }
    
}

void Build_d_aray(int A[],int size, int k){
    
    for(int i=(size-1)/k;i>=0;i--)
        d_ary_max(A,k,i, size);
    
}

int Extract_Max_d_array(int a[],int k)
{
    int max=a[0];
    a[0]=a[heap_size];
    heap_size--;
    d_ary_max(a,k, 0, heap_size);
    
    return max;
    
}
void Insert_Key_d_array(int a[],int key, int k){
    
    heap_size++;
    
    a[heap_size]=INT_MIN;
    
    Increase_Key(a,heap_size,key);
}
void Increase_Key_d_array(int a[],int index,int key, int k){
    
    if(key<a[index]){
        cout<<"Error, new key is smaller than current key."<<endl;
        return;
    }
    int i=index;
    for(;i>0 && key>a[parent(i,k)]; i=parent(i,k))
        a[i]=a[parent(i,k)];
    
    a[i]=key;
}
void Heap_Sort_d_aray(int A[], int size, int k){
    
    Build_d_aray(A, size, k);
    
    for(int i=size;i>0;i--){
        swap(A[0],A[i]);
        d_ary_max(A, k, 0, i-1);
    }
    
}
int random_pivot(int start, int end){
    random_device random_;
    
    uniform_int_distribution<int> uni(start,end);
    
    return uni(random_);
    
}

int interval_query(int a[], int size, int k, int interval[]){
    
    int* C=new int[k+1]();
    
    for(int i=0;i<size;i++)
        C[a[i]]++;
    int smallest=0;
    
    if(C[0]!=0)
        smallest=0;
    
    for(int i=1;i<k+1;i++)
    {   C[i]+=C[i-1];
        if(C[i]==0)
            smallest=i;
    }
    
    
    if (interval[0]<=smallest)
        return interval[1]<=k ? C[interval[1]] :  C[k];
    else
        return interval[1]>k ? C[k]-C[interval[0]-1] :  C[interval[1]]-C[interval[0]-1];
    
}

int max_(int a[], int size)
{
    Build_Max_Heap(a, size);
    return a[0];
}


int randomized_partition(int a[],int start, int end)
{
    swap(a[random_pivot(start,end-1)],a[end-1]);
    
    int pivot=start-1;
    
    for(int i=start;i<end;i++)
    {
        if(a[end-1]>a[i])
        {
            pivot++;
            if(a[i]!=a[pivot])
                swap(a[i],a[pivot]);
        }
    }
    
    swap(a[end-1],a[++pivot]);
    
    return pivot;
}

int randomized_select(int a[],int start,int end, int index){
    
    if(start==end-1)
        return a[start];
    
    int pivot=randomized_partition(a, start, end);
    
    int k=pivot-start+1;
    
    if(index==k)
        return a[pivot];
    else
        if(index<k)
            return randomized_select(a, start, pivot, index);
        else
            return randomized_select(a, pivot+1, end, index-k);
    
}
int median_insertion_sort(int list[], int start, int size){
    
    for(int i=start+1;i<size;i++)
    {
        int position=i; int value=list[position];
        while(value<list[position-1] && position>start)
        {
            list[position]=list[position-1];
            position--;
        }
        
        list[position]=value;
    }
    
    return (size+start)%2 ? list[(size+start-1)/2] : list[(size+start)/2 - 1];
    
    
}
int select_partition(int a[],int start, int end, int index)
{
    
    for(int i=start;i<end;i++){
        if(a[i]==index)
        {
            swap(a[i], a[end-1]);
            break;
        }
    }
    
    int pivot=start-1;
    
    for(int i=start;i<end;i++)
    {
        if(a[end-1]>a[i])
            if(++pivot!=i) swap(a[i],a[pivot]);
    }
    
    swap(a[++pivot],a[end-1]);
    
    return pivot;
}

int select_algorithim(int a[], int start, int end, int index){
    
    
    int size=end-start, groups=size/5, medians[(size+4)/5],i,j;
    
    
    for(j=0,i=0;i<groups; j+=5,i++)
        medians[i]=median_insertion_sort(a,j,j+5 );
    
    
    if( size%5 )
    {
        medians[i]=median_insertion_sort(a,groups*5,size);
        i++;
    }
    
    int median_of_medians= i>=5 ? select_algorithim(medians, 0, i,(i-1)/2 ) : median_insertion_sort(medians,0,i);
    
    int pivot=select_partition(a, start, end, median_of_medians);
    
    int k=pivot-start+1;
    
    if(index==k)
        return a[pivot];
    else
        if(index>k)
            return select_algorithim(a, pivot+1, end, index-k);
        else
            return select_algorithim(a, start, pivot, index);
    
}

int second_largest(int arr[],int start, int end, int index)
{
    if(start==end-1)
        return arr[start];
    
    int pivot=start-1;
    
    for(int i=start;i<end;i++)
    { if(arr[i]>arr[end-1])
        if(arr[i]!=arr[++pivot])
            swap(arr[i], arr[pivot]);
        if(pivot>0 && arr[pivot]==arr[pivot-1])
            --pivot;
    }
    
    swap(arr[end-1],arr[++pivot]);
    
    int k=pivot-start+1;
    
    if(k==index)
        return arr[pivot];
    else
    {
        if(index>k)
            return second_largest(arr, pivot+1, end, index-k);
        else
            return second_largest(arr, start, pivot, index);
    }
    
    
}

unsigned long long C(int n, int k)
{
    
    if(n<0 || k<0 || k>n) return 0;
    
    long double lower=1, upper=1;
    
    int limit=n-(n-k);
    
    for (int i = 1; i <= (n-k); i++)
        lower *= i;
    
    for(int i=n; i>limit;i--)
        upper*=i;
    
    return upper / lower;
}

int sum_digits(int K, int N)
{
    long long answer;
    for(int i=0;i<=N;i++)
    {
        int x1=(K+(N-1))-(10*i);
        int x2=K-(10*i);
        
        answer+=pow(-1,i)*C(N,i)*C(x1,x2);
        
    }
    return answer;
}


vector<int> primes(int n)
{
    bool mask[n];
    for(int i=2;i<n;i++)
        mask[i]=true;
    
    for(int i=2; i*i<n;i+=2)
    {
        if(mask[i])
        {
            for(int j=i*i; j<n; j+=i)
                mask[j]=false;
        }
    }
    vector<int> primes;
    
    for(int i=2;i<n;i++)
        if(mask[i])
            primes.push_back(i);
    
    return primes;
}

bool Is_Prime1(int64_t n)
{
    if(n<=3 == n>1)
        return true;
    
    if( !(n%2) || !(n%3) || n<=1)
        return false;
    
    for(int64_t i=5; i*i<n; i+=6)
        if(!(n%i) || !(n%(i+2)))
            return false;
    
    return true;
}

bool Is_Prime(uintmax_t n)
{
    if(n<=3 == n>1)
        return true;
    
    if( !(n%2) || !(n%3) || n<=1)
        return false;
    
    uintmax_t d=n-1, x=1; int s=0;
    
    while(!(d%2)) { d/=2; s++; }
    
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    
    vector<uintmax_t> coprime;
    
    if( n< (x<<11) )
        coprime.insert(coprime.end(),primes,primes+1);
    else if( n< (x<<20) )
        coprime.insert(coprime.end(),primes,primes+2);
    else if( n< (x<<25) )
        coprime.insert(coprime.end(),primes,primes+3);
    else if( n< (x<<31) )
        coprime.insert(coprime.end(),primes,primes+4);
    else
        coprime.insert(coprime.end(),primes,primes+12);
    
    for(int i=0; i<coprime.size(); i++)
    {
        bool strong_prob=true;
        
        uintmax_t a=pow(coprime[i],d);
        
        for(int r=0;r<s;r++)
        {
            a=pow(coprime[i],d*(x>>r));
            
            if( (a%n) !=1 )
            {
                strong_prob=false;
                break;
            }
        }
        
        if( (a%n)!=1 && !strong_prob)
            return false;
    }
    
    return true;
}

#endif /* dd_h */

