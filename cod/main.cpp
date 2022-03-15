#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
ifstream f("teste.in");
int n,nmax;
void ShellSort(vector <int>& v, int n)
{
    for(int gap=n/2; gap>0; gap/=2)
        for(int i=gap;i<n;i+=1)
        {
            int aux=v[i],j;
            for(j=i;j>=gap && v[j-gap]>aux;j-= gap)
                v[j] = v[j-gap];
            v[j]=aux;
        }
}

void CountingSort(vector <int>& v,int n)
{
    int maxim=v[0];
    vector <int> fr;
    fr.resize(nmax,0);
    for(int i=0;i<n;i++)
    {
        fr[v[i]]++;
        if(v[i]>maxim) maxim=v[i];
    }
    int k=0;
    for(int i=0;i<=maxim;i++)
        for(int j=1;j<=fr[i];j++)
            v[k++]=i;
}

void MergeSort(vector <int>& v,int st,int dr, vector <int>& aux)
{
    if(st<dr)
    {
        int m=(st+dr)/2;
        MergeSort(v,st,m,aux);
        MergeSort(v,m+1,dr,aux);
        int i=st,j=m+1,k=0;
        while(i<=m && j<=dr)
            if(v[i]<v[j])
                aux[k]=v[i],i++,k++;
            else
                aux[k]=v[j],k++,j++;
        while(i<=m)
            aux[k]=v[i],k++,i++;
        while(j<=dr)
            aux[k]=v[j],k++,j++;
        for(int i=st, j=0; i<=dr; i++, j++)
            v[i]=aux[j];
    }
}

void CocktailShakerSort(vector <int>& v, int n)
{
    int ok=1,st=0,dr=n-1;
    while(ok==1)
    {
        ok=0;
        for(int i=st; i<dr; i++)
            if(v[i]>v[i+1])
            {
                int aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                ok=1;
            }
        if(ok==0)
            break;
        ok=0;
        dr--;
        for(int i=dr-1; i>=st; i--)
            if(v[i]>v[i+1])
            {
                int aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                ok=1;
            }
        st++;
    }
}

void CountSort(vector <int>& v, int n, int p)
{
    int fr[10]={0};
    vector <int> a;
    a.resize(n,0);
    for (int i=0; i<n; i++)
        fr[(v[i]/p)%10]++;
    for (int i=1; i<10; i++)
        fr[i]=fr[i]+fr[i-1];
    for (int i=n-1; i>=0; i--)
    {
        a[fr[(v[i]/p)%10]-1]=v[i];
        fr[(v[i]/p)%10]--;
    }
    for (int i=0; i<n; i++)
        v[i]=a[i];
}

void RadixSort(vector <int>& v, int n)
{
    int maxim=v[0];
    for(int i=1;i<n;i++)
        if(v[i]>maxim) maxim=v[i];
    for (int p=1; maxim/p>0; p*=10)
        CountSort(v, n, p);
}

int verificare(vector <int> v2, vector <int>& v,int n)
{
    int ok=1;
    sort(v2.begin(), v2.end());
    for(int i=0;i<n;i++)
        if(v[i]!=v2[i]) return 0;
    return 1;
}

int main()
{

    int t,nr=1;
    srand((int)time(NULL));
    f>>t;
    for(int i=1;i<=t;i++)
    {
        f>>n>>nmax;
        vector <int> v;
        v.resize(n,0);
        vector <int> v2;
        v2.resize(n,0);
        cout<<"n="<<n<<" "<<"nmax="<<nmax<<endl;
        cout<<"Testul nr. "<<nr<<": "<<endl;
        nr++;


        int ok=1;
        for(int i=0;i<n;i++)
            v[i]=rand()%nmax;
        for(int i=0;i<n;i++)
            v2[i]=v[i];
        auto start = chrono::steady_clock::now();
        sort(v.begin(), v.end());
        auto end = chrono::steady_clock::now();
        cout<<"Timpul de rulare al sortarii native este de ";
        double time_taken;
        time_taken=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        cout << fixed<< time_taken << setprecision(10)<< " sec" << endl;


        for(int i=0;i<n;i++)
            v[i]=v2[i];
        start = chrono::steady_clock::now();
        ShellSort(v,n);
        end = chrono::steady_clock::now();
        cout<<"Timpul de rulare al algoritmului ShellSort este de ";
        time_taken=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        cout << fixed<< time_taken << setprecision(10)<< " sec" << endl;
        if(verificare(v2,v,n)==1) cout<<"Array-ul a fost sortat corect."<<endl;
        else cout<<"Array-ul nu a fost sortat corect. :("<<endl;

        for(int i=0;i<n;i++)
            v[i]=v2[i];
        cout<<"Timpul de rulare al algoritmului CountingSort este de ";
        start = chrono::steady_clock::now();
        CountingSort(v,n);
        end = chrono::steady_clock::now();
        time_taken=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        cout << fixed<< time_taken << setprecision(10)<< " sec" << endl;
        if(verificare(v2,v,n)==1) cout<<"Array-ul a fost sortat corect."<<endl;
        else cout<<"Array-ul nu a fost sortat corect. :("<<endl;

        vector <int> aux;
        aux.resize(n,0);
        for(int i=0;i<n;i++)
            v[i]=v2[i];
        cout<<"Timpul de rulare al algoritmului MergeSort este de ";
        start = chrono::steady_clock::now();
        MergeSort(v,0,n-1,aux);
        end = chrono::steady_clock::now();
        time_taken=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        cout << fixed<< time_taken << setprecision(10)<< " sec" << endl;
        if(verificare(v2,v,n)==1) cout<<"Array-ul a fost sortat corect."<<endl;
        else cout<<"Array-ul nu a fost sortat corect. :("<<endl;

        for(int i=0;i<n;i++)
            v[i]=v2[i];
        cout<<"Timpul de rulare al algoritmului RadixSort este de ";
        start = chrono::steady_clock::now();
        RadixSort(v,n);
        end = chrono::steady_clock::now();
        time_taken=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        cout << fixed<< time_taken << setprecision(10)<< " sec" << endl;
        if(verificare(v2,v,n)==1) cout<<"Array-ul a fost sortat corect."<<endl;
        else cout<<"Array-ul nu a fost sortat corect. :("<<endl;

        for(int i=0;i<n;i++)
            v[i]=v2[i];
        cout<<"Timpul de rulare al algoritmului CocktailShakerSort este de ";
        start = chrono::steady_clock::now();
        CocktailShakerSort(v,n);
        end = chrono::steady_clock::now();
        time_taken=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        cout << fixed<< time_taken << setprecision(10)<< " sec" << endl;
        if(verificare(v2,v,n)==1) cout<<"Array-ul a fost sortat corect."<<endl;
        else cout<<"Array-ul nu a fost sortat corect. :("<<endl;

        cout<<endl<<endl;

    }
    return 0;
}

