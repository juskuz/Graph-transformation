#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

bool sprawdz_czy_1_graf( int tab1[], int tab2[], int n) // sprawdza czy jest to 1-graf, czyli nie ma łukow wielokrotnych
{
    bool jeden_graf;
    for(int i=0; i<(n); i++)
    {
        for (int j=0; j<(n); j++)
        {
            if(j!=i)
            {
                if(tab1[i]==tab1[j])
                {
                    if (tab2[i]==tab2[j]) // jest powtorzony ten sam luk
                    {
                        cout<<"1-graf: NIE"<<endl<<endl; // jesli wartosci sie powtorza to nie jest to 1-graf
                        return false;
                    }
                }
            }
        }
    }

    cout<<"1-graf: TAK"<<endl<<endl;  //jesli jest to 1-graf
    return true;
}

int sprawdz_czy_sprzezony (int grafG[50][50], int liczba_nastepnikow[], int liczba_wierzcholkow)
{

    int identyczne; // 2 - nie sa identyczne, 1 - sa identyczne, return 0 - nie sprawdzaj juz liniowosci
    bool liniowy=1;

    for(int i=0; i<liczba_wierzcholkow-1; i++) // i - numer indeksu wierzcholka1 (poprzednika)
    {
        for(int j=i+1;j<liczba_wierzcholkow;j++) // j - numer indeksu wierzcholka2 (poprzednika) // porownujemy tylko kolejne indeksy, nie cofamy sie
        {
            int takie_same=0;
            int inne=0;

            for(int k=1; k<(liczba_nastepnikow[i]+1); k++) // k - numer kolumny - numer indeksu nastepnika wierzcholkow (poprzednikow) w tablicy
            {
                identyczne=0;
                for(int l=1; l<(liczba_nastepnikow[j]+1);l++)
                {
                    if(grafG[i][k]==grafG[j][l])
                    {
                        identyczne=1;
                    }
                }
                if (identyczne==1)
                {
                    takie_same++; // istnieje taki sam nastepnik
                }
                if (identyczne==0)
                {
                   inne++; // nie istnieje taki sam nastepnik
                }
            }

            if(takie_same==(liczba_nastepnikow[i])) // nastepniki sa takie same
                {
                    liniowy=1; // trzeba sprawdzic czy liniowy
                }
            else if (inne==(liczba_nastepnikow[i]))// wszystkie nastepniki sa rozne
                {
                    liniowy=2; // na pewno liniowy
                }
            else
            {
                cout<<"\nsprzezony: NIE"<<endl<<endl;
                return 0;
            }
        }
    }

cout<<"\nsprzezony: TAK"<<endl<<endl;
return liniowy; // zwroc 1 (sprawdz czy liniowy) lub 2(na pewno liniowy)


}


bool utworz_graf_G2 (int liczba_wierzcholkow, int grafG2 [50][50], int nastepnikGoryg[], int poprzednikGoryg[], int liczbapoprzednikow[])
{

int iloscG2=liczba_wierzcholkow;
int nastepnikG[50], poprzednikG[50];


for(int i=0; i<iloscG2; i++)
{
    poprzednikG[i]=poprzednikGoryg[i];
    nastepnikG[i]=nastepnikGoryg[i];
}

for (int i=0;i<iloscG2-1;i++) // sortowanie tablic wg numeru nastepnika
            {
                for (int j=0;j<iloscG2-1;j++)
                {
                    if(nastepnikG[j]>nastepnikG[j+1])
                    {
                        swap(poprzednikG[j],poprzednikG[j+1]);
                        swap(nastepnikG[j],nastepnikG[j+1]);
                    }

                    if((nastepnikG[j]==nastepnikG[j+1])&&(poprzednikG[j]>poprzednikG[j+1]))
                    {
                        swap(poprzednikG[j],poprzednikG[j+1]);
                        swap(nastepnikG[j],nastepnikG[j+1]);
                    }
                }
            }


            int a=0; // indeks nastepnika (numer kolejny nastepnika - wiersze)
            int b=1; // zlicza liczbe poprzednikow nastepnika a (nr kolumny)

            for (int i=0;i<iloscG2;i++)
            {
                b=1;

                if(poprzednikG[i]==0) //
                {
                    iloscG2--;
                    break;
                }
                grafG2[a][0]=nastepnikG[i];
                grafG2[a][b]=poprzednikG[i];
                for (int j=i;j<iloscG2;j++)
                {
                    if(nastepnikG[j]==nastepnikG[j+1])
                    {
                        grafG2[a][b+1]=poprzednikG[j+1];
                        b++;
                    }
                    else
                    {
                        i=j;
                        break;
                    }
                }
                liczbapoprzednikow[a]=b;
                a++;
            }

}


bool sprawdz_czy_liniowy (int grafG[50][50], int liczba_nastepnikow[], int liczba_wierzcholkow, int grafG2[50][50], int liczbapoprzednikow[])
{
    bool liniowy=true;

    for(int i=0; i<liczba_wierzcholkow-1; i++) // i - numer indeksu wierzcholka1 (poprzednika)
    {
        for(int j=i+1; j<liczba_wierzcholkow; j++) // j - numer indeksu wierzcholka2 (poprzednika) // porownujemy tylko kolejne indeksy, nie cofamy sie
        {
            for(int k=1; k<liczba_nastepnikow[i]+1; k++) // k - numer kolumny - numer indeksu nastepnika wierzcholkow (poprzednikow) w tablicy
            {
                for(int l=1; l<liczba_nastepnikow[j]+1;l++)
                {
                    if(grafG[i][k]==grafG[j][l])
                    {
                        {
                            int x, y;
                            for (x=0; x<liczba_wierzcholkow; x++) // musi sobie znalezc numer indeksu w G2 pierwszego wierzcholka
                            {
                                if (grafG2[x][0]==0) continue;
                                if (grafG2[x][0]==grafG[i][0])
                                {
                                    break;
                                }
                            }
                            for(y=0; y<liczba_wierzcholkow; y++) // numer indeksu w G2 drugiego wierzcholka do porownania
                            {
                                if (grafG2[y][0]==0) continue;
                                if (grafG2[y][0]==grafG[j][0])
                                {
                                    break;
                                }
                            }

                            // sprawdz identycznosc dla i oraz j (x i y)
                            for (int m=1; m<liczbapoprzednikow[x]+1; m++)
                            {
                                for (int n=1; n<liczbapoprzednikow[y]+1;n++)
                                {
                                    if (grafG2[x][m]==grafG2[y][n])
                                    {
                                        liniowy=false;
                                        cout<<"\nliniowy: NIE"<<endl<<endl;
                                        return liniowy;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout<<"\nliniowy: TAK"<<endl<<endl;

return liniowy;
}

 int przeksztalc_graf(int poprzednikG[], int nastepnikG[], int iloscG, int poprzednikH [], int nastepnikH [], int* iloscH, int wierzcholek_w_G [], int H_poprzednik[], int H_krawedz[], int H_nastepnik[], bool liniowy)
 {

    int nowy_numer=1;
    int indeks=0;
    int nastepnik_w_G[50];
    int obecnyH[50];

for (int i=0; i<iloscG; i++) // buduje krawedzie w tablicy
{
    if(nastepnikG[i]==poprzednikG[i]) // petla wlasna
    {
        poprzednikH[indeks]=obecnyH[indeks]=nastepnikH[indeks]=nowy_numer;
        wierzcholek_w_G[indeks]=nastepnik_w_G[indeks]=nastepnikG[indeks];
        nowy_numer++;
        indeks++;
        (*iloscH)=(*iloscH)+2;
    }
    else
        {
        poprzednikH[indeks]=nowy_numer;
        obecnyH[indeks]=nowy_numer+1;
        nastepnikH[indeks]=(nowy_numer+2);
        wierzcholek_w_G[indeks]=poprzednikG[i]; // pomocnicze
        nastepnik_w_G[indeks]=nastepnikG[i]; // pomocnicze

        (*iloscH)=(*iloscH)+2;; // zwieksz liczbe lukow

        indeks++; // wpisz numer kolejnej nowej krawedzi

        nowy_numer=nowy_numer+3;
    }
}


bool zamiana=true;
while (zamiana)
{

for(int i=0; i<indeks; i++)
{
zamiana=false;
    if (nastepnik_w_G[i]==0) {continue;}

    for (int j=0; j<indeks; j++)
    {
        if(i==j) {continue;}
        else if ((nastepnik_w_G[i]==wierzcholek_w_G[j]) && (nastepnik_w_G[j]==wierzcholek_w_G[i]))
        {
            if (obecnyH[j]!=poprzednikH[i] || nastepnikH[j]!=obecnyH[i] || nastepnikH[i]!=poprzednikH[i] || poprzednikH[j]!=obecnyH[i])
            {
                obecnyH[j] = poprzednikH[i];
                nastepnikH[j] = obecnyH[i];
                nastepnikH[i]= poprzednikH[i];
                poprzednikH[j] = obecnyH[i];
                zamiana=true;


                for (int k=0; k<indeks; k++)
                {
                    if(k==i) {continue;}
                    if (wierzcholek_w_G[k]==wierzcholek_w_G[j])
                    {
                        if ((nastepnik_w_G[k]==nastepnik_w_G[j]))
                        {
                            wierzcholek_w_G[k]=0;
                            nastepnik_w_G[k]=0;
                            poprzednikH[k]=0;
                            obecnyH[k]=0;
                            nastepnikH[k]=0;
                        }
                        else
                        {
                            obecnyH[k]=obecnyH[j];
                            poprzednikH[k]=poprzednikH[j];
                        }
                    }
                    else if (nastepnik_w_G[k]==nastepnik_w_G[j])
                    {
                        if(wierzcholek_w_G[k]==wierzcholek_w_G[j])
                        {
                            wierzcholek_w_G[k]=0;
                            nastepnik_w_G[k]=0;
                            poprzednikH[k]=0;
                            obecnyH[k]=0;
                            nastepnikH[k]=0;
                        }
                        else
                        {
                            obecnyH[k]=obecnyH[j];
                            nastepnikH[k]=nastepnikH[j];
                        }
                    }
                    else if (nastepnik_w_G[k]==wierzcholek_w_G[j])
                    {
                        if(wierzcholek_w_G[k]==nastepnik_w_G[j])
                        {
                            wierzcholek_w_G[k]=0;
                            nastepnik_w_G[k]=0;
                            poprzednikH[k]=0;
                            obecnyH[k]=0;
                            nastepnikH[k]=0;
                        }
                        else
                        {
                            obecnyH[k]=poprzednikH[j];
                            nastepnikH[k]=obecnyH[j];
                        }
                    }
                    else if (wierzcholek_w_G[k]==nastepnik_w_G[j])
                    {
                        if(nastepnik_w_G[k]==wierzcholek_w_G[j])
                        {
                            wierzcholek_w_G[k]=0;
                            nastepnik_w_G[k]=0;
                            poprzednikH[k]=0;
                            obecnyH[k]=0;
                            nastepnikH[k]=0;
                        }
                        else
                        {
                            poprzednikH[k]=obecnyH[j];
                            obecnyH[k]=nastepnikH[j];
                        }
                    }
                }
            }
        }
        else if((wierzcholek_w_G[i]==wierzcholek_w_G[j]) && (wierzcholek_w_G[i]==nastepnik_w_G[j]))
        {
            if (poprzednikH[j]!= poprzednikH[i] || obecnyH[j]!= poprzednikH[i] || nastepnikH[j]!=poprzednikH[i] || obecnyH[i]!=poprzednikH[i])
            {
                poprzednikH[j]= poprzednikH[i];
                obecnyH[j]= poprzednikH[i];
                nastepnikH[j]=poprzednikH[i];
                obecnyH[i]=poprzednikH[i];
                zamiana=true;
            }
        }
        else if((nastepnik_w_G[i]==wierzcholek_w_G[j])&&(wierzcholek_w_G[j]==nastepnik_w_G[j]))
        {
            if (poprzednikH[j]!=obecnyH[i] || obecnyH[j]!=obecnyH[i] || nastepnikH[j]!=obecnyH[i] || nastepnikH[i]!=obecnyH[i])
            {
                poprzednikH[j]=obecnyH[i];
                obecnyH[j]=obecnyH[i];
                nastepnikH[j]=obecnyH[i];
                nastepnikH[i]=obecnyH[i];
                zamiana=true;
            }
        }
        else if ((wierzcholek_w_G[i]==nastepnik_w_G[i])&&(nastepnik_w_G[i]==wierzcholek_w_G[j]))
        {
            if (poprzednikH[j]!=poprzednikH[i] || obecnyH[j]!=poprzednikH[i] || obecnyH[i]!=poprzednikH[i] || nastepnikH[i]!=poprzednikH[i])
            {
                poprzednikH[j]=poprzednikH[i];
                obecnyH[j]=poprzednikH[i];
                obecnyH[i]=poprzednikH[i];
                nastepnikH[i]=poprzednikH[i];
                zamiana=true;
            }
        }
        else if ((wierzcholek_w_G[i]==nastepnik_w_G[i])&&(nastepnik_w_G[i]==nastepnik_w_G[j]))
        {
            if (obecnyH[j]!=poprzednikH[i] || nastepnikH[j]!=poprzednikH[i])
            {
                obecnyH[j]=poprzednikH[i];
                nastepnikH[j]=poprzednikH[i];
                zamiana=true;
            }
        }
        else if ((wierzcholek_w_G[i]==nastepnik_w_G[j]))
        {
            if (obecnyH[j]!=poprzednikH[i] || nastepnikH[j]!=obecnyH[i])
            {
                obecnyH[j]=poprzednikH[i];
                nastepnikH[j]=obecnyH[i];
                zamiana=true;
            }
        }
        else if ((nastepnik_w_G[i]==wierzcholek_w_G[j]))
        {
            if (poprzednikH[j]!=obecnyH[i] || obecnyH[j]!=nastepnikH[i])
            {
                poprzednikH[j]=obecnyH[i];
                obecnyH[j]=nastepnikH[i];
                zamiana=true;
            }
        }
        else if ((nastepnik_w_G[i]==nastepnik_w_G[j]))
        {
            if (obecnyH[j]!=obecnyH[i] || nastepnikH[j]!=nastepnikH[i])
            {
                obecnyH[j]=obecnyH[i];
                nastepnikH[j]=nastepnikH[i];
                zamiana=true;
            }
        }
        else if ((wierzcholek_w_G[i]==wierzcholek_w_G[j]))
        {
            if (poprzednikH[j]!=poprzednikH[i] || obecnyH[j]!=obecnyH[i])
            {
                poprzednikH[j]=poprzednikH[i];
                obecnyH[j]=obecnyH[i];
                zamiana=true;
            }
        }
    }
}

}

for (int i=0; i<indeks; i++)
    {
        for(int j=i; j<indeks; j++)
        {
            if((poprzednikH[i]==obecnyH[i]) && (obecnyH[i]==nastepnikH[i]))
            {
                nastepnik_w_G[i]=poprzednikH[i]=obecnyH[i]=nastepnikH[i]=wierzcholek_w_G[i]=0;
                (*iloscH)--;
            }
            else if(i==j) {continue;}
            else if((wierzcholek_w_G[i]==wierzcholek_w_G[j])&&(poprzednikH[i]==poprzednikH[j])&&(obecnyH[i]==obecnyH[j]))
            {
                wierzcholek_w_G[j]=0;
                (*iloscH)--;
            }
            else if((wierzcholek_w_G[i]==nastepnik_w_G[j])&&(poprzednikH[i]==obecnyH[j])&&(obecnyH[i]==nastepnikH[j]))
            {
                nastepnik_w_G[j]=0;
                (*iloscH)--;
            }
            else if((nastepnik_w_G[i]==wierzcholek_w_G[j])&&(obecnyH[i]==poprzednikH[j])&&(nastepnikH[i]==obecnyH[j]))
            {
                wierzcholek_w_G[j]=0;
                (*iloscH)--;
            }
            else if((nastepnik_w_G[i]==nastepnik_w_G[j])&&(obecnyH[i]==obecnyH[j])&&(nastepnikH[i]==nastepnikH[j]))
            {
                nastepnik_w_G[j]=0;
                (*iloscH)--;
            }
        }
    }


    cout<<"Przetransformowano graf."<<endl;
    {
        cout<<"\n\nGRAF ORYGINALNY:"<<endl<<endl;

int wypisane [25];
for (int z=0; z<25; z++)
{
    wypisane[z]=0;
}
bool wypisz=true;
int a=0;

        for (int i=indeks-1; i>=0; i--)
        {
            if((wierzcholek_w_G[i]!=0)&&(nastepnik_w_G[i]!=0))
            {
                for(int w=0; w<25; w++)
                {
                    if (wierzcholek_w_G[i]!=wypisane[w])
                    {wypisz=true;}
                    else {wypisz=false; wierzcholek_w_G[i]=0; break;}
                }

                if(wypisz)
                {
                    cout<<poprzednikH[i]<<"\t["<<wierzcholek_w_G[i]<<"]\t"<<obecnyH[i]<<endl;
                    wypisane[a]=wierzcholek_w_G[i];
                    a++;
                }

                for(int w=0; w<25; w++)
                {
                    if (nastepnik_w_G[i]!=wypisane[w])
                    {wypisz=true;}
                    else {wypisz=false; nastepnik_w_G[i]=0; break;}
                }

                if(wypisz)
                {
                    cout<<obecnyH[i]<<"\t["<<nastepnik_w_G[i]<<"]\t"<<nastepnikH[i]<<endl;
                    wypisane[a]=nastepnik_w_G[i];
                    a++;
                }
            }
            else if ((wierzcholek_w_G[i]!=0))
            {
                for(int w=0; w<25; w++)
                {
                    if (wierzcholek_w_G[i]!=wypisane[w])
                    {wypisz=true;}
                    else {wypisz=false; wierzcholek_w_G[i]=0; break;}
                }

                if(wypisz)
                {
                    cout<<poprzednikH[i]<<"\t["<<wierzcholek_w_G[i]<<"]\t"<<obecnyH[i]<<endl;
                    wypisane[a]=wierzcholek_w_G[i];
                    a++;
                }
            }
            else if ((nastepnik_w_G[i]!=0))
            {
                for(int w=0; w<25; w++)
                {
                    if (nastepnik_w_G[i]!=wypisane[w])
                    {wypisz=true;}
                    else {wypisz=false; nastepnik_w_G[i]=0; break;}
                }

                if(wypisz)
                {
                    cout<<"\t\t"<<obecnyH[i]<<"\t["<<nastepnik_w_G[i]<<"]\t"<<nastepnikH[i]<<endl;
                    wypisane[a]=nastepnik_w_G[i];
                    a++;
                }
            }
        }
    }

    int j=0;
    for (int i=0; i<indeks; i++)
        {
            if (poprzednikH[i]==0 || obecnyH[i]==0 || nastepnikH[i]==0) {continue;}
            if((wierzcholek_w_G[i]!=0)&&(nastepnik_w_G[i]!=0))
            {
                H_poprzednik[j] = poprzednikH[i];
                H_krawedz[j] = wierzcholek_w_G[i];
                H_nastepnik[j] = obecnyH[i];
                j++;
                H_poprzednik[j] = obecnyH[i];
                H_krawedz[j] = nastepnik_w_G[i];
                H_nastepnik [j] = nastepnikH[i];
                j++;
            }
            else if ((wierzcholek_w_G[i]!=0))
            {
                H_poprzednik[j] = poprzednikH[i];
                H_krawedz[j] = wierzcholek_w_G[i];
                H_nastepnik[j] = obecnyH[i];
                j++;
            }
            else if ((nastepnik_w_G[i]!=0))
            {
                H_poprzednik[j] = obecnyH[i];
                H_krawedz[j] = nastepnik_w_G[i];
                H_nastepnik [j] = nastepnikH[i];
                j++;
            }
        }
    (*iloscH)=j;
 }


int main()
{
    int v1,v2,iloscG,iloscH;
    int poprzednikG[50],nastepnikG[50],grafG[50][50];
    int liczbanastepnikow[50]; // zlicza liczbe nastepnikow danego wierzcholka(poprzednika)
    int sprzezony=-1; //potrzebne do sprawdzenia czy mozna zrobic transformacje
    bool liniowy=false;
    bool jedno_graf=true;
    bool trans=false;

    int grafG2[50][50];
    int liczbapoprzednikow[50];
    int iloscG2;

    int poprzednikH[50],nastepnikH[50],wierzcholek_w_G[50];

    int H_poprzednik[50], H_krawedz[50], H_nastepnik[50];

    string opcja;

    iloscG=0; //ilosc wczytywanych wierszy z pliku
    iloscH=0; //ilosc wierszy zapisywanych do pliku po transformacji

    do
    {
        system("CLS");
        cout<<" Podaj opcje: "<<endl<<endl;
        cout<<" - 'wczytaj' - wczytuje graf G z pliku grafG.txt"<<endl;
        cout<<" - 'sprawdz' - sprawdza sprzezenie i liniowosc grafu G "<<endl;
        cout<<" - 'transformuj' - transformuje graf sprzezony G do grafu oryginalnego H "<<endl;
        cout<<" - 'H' - wyswietl graf oryginalny H (po transformacji)"<<endl;
        cout<<" - 'zapisz' - zapisuje graf H do pliku grafH.txt"<<endl;
        cout<<" - 'koniec' - konczy dzialanie programu "<<endl<<endl;
        cout<< " opcja: ";
        cin>>opcja;

        if (opcja=="wczytaj")
        {
            system("CLS"); // wyczysc ekran
            fstream plik;
            plik.open("grafG.txt", ios::in);
            while(plik>>v1>>v2)
            {
                poprzednikG[iloscG]=v1;
                nastepnikG[iloscG]=v2;
                iloscG++;
            }

            for (int i=0;i<iloscG-1;i++) // sortowanie tablic
            {
                for (int j=0;j<iloscG-1;j++)
                {
                    if(poprzednikG[j]>poprzednikG[j+1])
                    {
                        swap(poprzednikG[j],poprzednikG[j+1]);
                        swap(nastepnikG[j],nastepnikG[j+1]);
                    }

                    if((poprzednikG[j]==poprzednikG[j+1])&&(nastepnikG[j]>nastepnikG[j+1]))
                    {
                        swap(poprzednikG[j],poprzednikG[j+1]);
                        swap(nastepnikG[j],nastepnikG[j+1]);
                    }
                }
            }

            int a=0; // indeks wierzcholka (poprzednika) (numer kolejny poprzednika - wiersze)
            int b=1; // zlicza liczbe nastepnikow wierzcholka (poprzednika a) (nr kolumny)

            for (int i=0;i<iloscG;i++)
            {
                b=1;
                grafG[a][0]=poprzednikG[i];
                grafG[a][b]=nastepnikG[i];
                for (int j=i;j<iloscG;j++)
                {
                    if(poprzednikG[j]==poprzednikG[j+1])
                    {
                        grafG[a][b+1]=nastepnikG[j+1];
                        b++;
                    }
                    else
                    {
                        i=j;
                        break;
                    }
                }
                liczbanastepnikow[a]=b;
                a++;
            }

            cout<<" Lista nastepnikow: "<<endl<<endl;

            for (int i=0;i<a;i++)
            {
                cout<<" "<<grafG[i][0]<<" -> ";
                for (int j=1;j<liczbanastepnikow[i]+1;j++)
                {
                    cout<<grafG[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl<<endl<<" ";
            plik.close(); // zamknij plik na koniec
            system("PAUSE");
        }

        if (opcja=="sprawdz")
        {
            system("CLS");

            cout<<"GRAF G:"<<endl<<endl;
            jedno_graf=sprawdz_czy_1_graf(poprzednikG, nastepnikG, iloscG);

            system("PAUSE");

            if(jedno_graf)
            {

                sprzezony=sprawdz_czy_sprzezony (grafG, liczbanastepnikow, iloscG);
                system("PAUSE");

                if (sprzezony==0)
                {
                    cout<<"\nliniowy: NIE (nie jest sprzezony)"<<endl<<endl;
                }
                else if(sprzezony==1)
                {
                    utworz_graf_G2(iloscG, grafG2, nastepnikG, poprzednikG, liczbapoprzednikow);
                    liniowy=sprawdz_czy_liniowy(grafG, liczbanastepnikow, iloscG, grafG2, liczbapoprzednikow);
                }
                else if (sprzezony==2)
                {
                    cout<<"\nliniowy: TAK "<<endl<<endl;
                }
                else cout<<"\npojawil sie blad w programie.\n sprzezony = "<<sprzezony<<endl;

                cout<<"Skonczono sprawdzanie sprzezenia i liniowosci."<<endl<<endl;
                system("PAUSE");
            }

        }

        if (opcja=="transformuj")
        {
            system("CLS");
            if (jedno_graf==false)
            {
                cout<<"Graf G nie jest 1-grafem, wiec nie można go transformowac"<<endl;
            }
            else if(sprzezony==1||sprzezony==2)
            {
                trans=true;
                przeksztalc_graf(poprzednikG, nastepnikG, iloscG, poprzednikH, nastepnikH, &iloscH, wierzcholek_w_G, H_poprzednik, H_krawedz, H_nastepnik, liniowy);
            }
            else if(jedno_graf==true || sprzezony==-1)
            {
                cout<<"Najpierw wybierz opcje 'sprawdz'. Potem mozesz transformowac."<<endl;
            }
            else if(sprzezony==0)
            {
                cout<<"Grafu G nie mozna transformowac do grafu oryginalnego H."<<endl;
            }
            else cout<<"Blad programu."<<endl;

            system("PAUSE");
        }

        if (opcja=="H")
        {
            system("CLS");
            if(trans==true)
            {
               cout<<"GRAF ORYGINALNY H:"<<endl<<endl;
                cout<<"liczba krawedzi: "<<iloscH<<endl<<endl;
                for(int i=0;i<iloscH;i++)
                {
                    cout<<H_poprzednik[i]<<" ----\t["<<H_krawedz[i]<<"]-->\t"<<H_nastepnik[i]<<endl;
                }
            }
            else
            {
                cout<<"Graf oryginalny H nie istnieje lub nie zostal jeszcze utworzony."<<endl;
            }


            system("PAUSE");
        }

        if (opcja=="zapisz")
        {
            system("CLS");
            fstream file;
            file.open("grafH.txt", ios::out);
            for(int i=0;i<iloscH;i++)
            {
                file<<H_poprzednik[i]<<" "<<H_nastepnik[i]<<endl;
            }
            cout<<" Zapisano graf H do pliku grafH.txt "<<endl<<endl<<endl<<" ";
            system("PAUSE");
        }

    } while (opcja!="koniec");

    return 0;
}

