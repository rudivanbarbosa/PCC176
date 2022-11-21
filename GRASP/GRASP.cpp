#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <list>
#include <time.h>
#include <math.h>
#include <cstdio>
#include <chrono>
#include <random>

using namespace std;

bool verificar_atendimento(int j, vector < vector < int > > &x)
{
    for(int i = 0; i < x.size(); i++)
    {
        if(x[i][j] == 1)
        {
            return true;
        }
    }
return false;
}

bool encontrou(vector < vector <int> > &x)
{
    for(int i = 0; i < x.size(); i++)
    {
        if(x[i][i] = 1)
        {
            return true;
        }
    }
    return false;
}

float soma(vector<int> &y)
{
    int soma = 0;

    for(int i =0; i < y.size(); i++)
    {
        soma+= y[i];
    }
    return soma;
}

float calcula_fo(vector < vector < int > > &x, vector <int> &demanda )
{
    float fo = 0;

    for(int i = 0; i < demanda.size(); i++)
    {
        for(int j = 0; j < demanda.size(); j++)
        {
            fo += demanda[j]*x[i][j];
        }

    }

    return fo;
}

int minimo_elemento(vector <int> &v, set <int> C)
{
    set <int>::iterator it;
    int aux = INT_MAX;
    for(it = C.begin(); it!= C.end(); it++)
    {
        if(aux > v[*it])
        {
            aux = v[*it];
        }
    }

    return aux;
}

int maximo_elemento(vector <int> &v, set <int> C)
{
    int aux = INT_MIN;
    set <int>::iterator it;
    for(it = C.begin(); it!= C.end(); it++)
    {
        if(aux < v[*it])
        {
            aux = v[*it];
        }
    }

    return aux;
}

int select_randomly(vector <int> &LCR, vector < vector <int> > &x)
{
    int r;

    r = rand()%LCR.size();

    while(x[LCR[r]][LCR[r]] == 1)
    {
        r = rand()%LCR.size();
    }

    return LCR[r];
}

int minima_residual(vector < int > &s)
{
    int maior = INT_MIN;

    for(int i = 0; i < s.size(); i++)
    {
        if( s[i] > maior && s[i] != 0)
        {
            maior = s[i];
        }
    }
    return maior;
}

int capacidade_sede(vector <int> &v, int y, vector<int> &demanda, int Cap)
{
    int demanda_atendida = 0;
    int capacidade = y*Cap;

    for(int j = 0; j < v.size(); j++)
    {
        demanda_atendida +=  v[j]*demanda[j];

    }

    return capacidade - demanda_atendida;
}

int repovoar(vector < vector < int > > &x, vector <int> &y, vector <int> &z, vector <int> &demanda, vector < vector <float> > &dist, int Cap, int R, int nC, int j,  int i, int k )
{
    vector < vector <int> > x_atual;
    vector < vector <int> > x_star;
    vector <int> cidades_proximas;
    vector <int> sedes_analisadas;
    int fo, fo_atual, fo_star, capacidade_residual, capacidade_residual_utilizada, l, m, v, w, f;
    fo = fo_atual = fo_star = capacidade_residual =  capacidade_residual_utilizada =  l =  m =  v =  w =  f = 0;
    fo = fo_atual = fo_star = calcula_fo(x,demanda);

    x_star = x_atual = x;
    capacidade_residual_utilizada = 0;

    sedes_analisadas.clear();
    sedes_analisadas.push_back(i);
    sedes_analisadas.push_back(k);

    for(int u = 0; u < sedes_analisadas.size(); u++)
    {
        m = sedes_analisadas[u];

        capacidade_residual = capacidade_sede(x[m], y[m], demanda, Cap);
        for(int t = 0; t < nC; t++)
        {
            if(dist[m][t] <= R && z[t] == 0  && t!= j && (capacidade_residual >= demanda[t])  )
            {
                cidades_proximas.push_back(t);
            }
        }

        for(int v = 0; v < cidades_proximas.size(); v++)
        {
            w = cidades_proximas[v];
            x_atual = x;
            fo_atual = fo;
            capacidade_residual_utilizada = 0;

            if(capacidade_residual_utilizada + demanda[w] <= capacidade_residual && !verificar_atendimento(w, x_atual) )
            {
                x_atual[m][w] = 1;
                fo_atual += demanda[w];
                capacidade_residual_utilizada = demanda[w];

                for(int q = 0; q < cidades_proximas.size(); q++ )
                {
                    f = cidades_proximas[q];

                        if( capacidade_residual_utilizada + demanda[f] <= capacidade_residual && !verificar_atendimento(f, x_atual) && f!=w )
                        {
                            x_atual[m][f] = 1;
                            fo_atual +=  demanda[f];
                            capacidade_residual_utilizada += demanda[f];
                        }
                }

            }
                if( fo_atual > fo_star)
                {
                    fo_star = fo_atual;
                    x_star = x_atual;
                }

        }
            fo = fo_star;
            x = x_star;
            capacidade_residual_utilizada = 0;
            cidades_proximas.clear();
    }
    return fo_star;

}

int vizinho(vector < vector < int > > &x, vector <int> &y, vector <int> &z, vector <int> &demanda, vector < vector <float> > &dist, int Cap, int R, int nC, int j,  int i, int k )
{
    int l, residual, t;
    int fo = INT_MIN;
    vector <int> cidades_alocadas;
    vector <int> demanda_cidades_alocadas;

    l = residual = t = 0;
    residual = y[k]*Cap - demanda[k];
//INICIO DA REALOCAO
    for(int u = 0; u < nC; u++)
        {
            if(x[k][u] == 1 & k != u)
            {
                cidades_alocadas.push_back(u);
            }
        }

    if(x[i][j] == 1 && dist[k][j] <= R && residual >= demanda[j])
    {

        while(capacidade_sede(x[k], y[k], demanda, Cap) < demanda[j] && t < cidades_alocadas.size() )
        {
            l = cidades_alocadas[t];
            x[k][l] = 0;// desatender a cidade l da sede k
            t++;
        }
        swap(x[i][j], x[k][j]);
        //FIM DA REALOCACAO
        fo = repovoar (x, y, z, demanda, dist, Cap, R, nC, j, i, k );
    }

    return fo;
}

int construtiva(vector < vector <int> > &x, vector<int> &y, vector<int> &z,  vector <int> &demanda , vector < vector <float> > &dist, set <int> C, vector <int> &sedes, int Cap, int qM, int dMin, int R, int nC, float alpha)
{
    int j, u, v, l, m, t,  g_t_min, g_t_max, qMu, fo, fo_atual, fo_star, capacidade_residual_utilizada ;
    vector <int> capacidade_residual(nC, 0);
    vector <int> cidades_proximas;
    vector < vector <int> > x_star;
    vector < vector <int> > x_atual;
    vector <int> LCR;
    set <int>::iterator it;
    fo = fo_atual =  fo_star = capacidade_residual_utilizada = qMu = 0;



    for( int i = 0; i < C.size(); i++ )
    {
        g_t_min = minimo_elemento(demanda, C);
        g_t_max = maximo_elemento(demanda, C);

        for (it = C.begin(); it != C.end(); it++)
        {
             if(demanda[*it] >= g_t_max  + alpha*(g_t_min - g_t_max) )
               {
                LCR.push_back(*it);
               }
        }

        t = select_randomly(LCR, x);
        if( qMu + ceil(float(demanda[t])/Cap) <= qM)
           {
               x[t][t] = 1;
               z[t] = 1;
               y[t] = ceil(float(demanda[t])/Cap);
              qMu += y[t];
           }

        C.erase(t);
        LCR.clear();
    }

    sedes.clear();

    for(int i = 0; i < nC; i++)
     {
        if(z[i] == 1 )
        {
            sedes.push_back(i);
        }
     }

    for(int i = 0; i < sedes.size(); i++)
    {
        m = sedes[i];
        capacidade_residual[m] = y[m]*Cap - demanda[m];
    }

        if(soma(y) < qM)
        {
             t = minima_residual(capacidade_residual);

             y[t] +=  qM - soma(y);
        }

    x_star = x_atual =  x;
    fo = fo_atual = fo_star = calcula_fo(x,demanda);

    for(int i = 0; i < sedes.size(); i++)
    {
        m = sedes[i];

        for(int j = 0; j < nC; j++)
        {
            if(dist[m][j] <= R && z[j] == 0 && (capacidade_residual[m] >= demanda[j])  )
            {
                cidades_proximas.push_back(j);
            }
        }

        if(cidades_proximas.size()!=0)
        {

            for(int v = 0; v < cidades_proximas.size(); v++)
            {
                j = cidades_proximas[v];
                x_atual = x;
                fo_atual = fo;
                capacidade_residual_utilizada = 0;

                if(capacidade_residual_utilizada + demanda[j] <= capacidade_residual[m] && !verificar_atendimento(j, x_atual) )
                {
                    x_atual[m][j] = 1;
                    fo_atual += demanda[j];
                    capacidade_residual_utilizada = demanda[j];

                    for(int k = 0; k < cidades_proximas.size(); k++ )
                    {
                        u = cidades_proximas[k];

                            if( capacidade_residual_utilizada + demanda[u] <= capacidade_residual[m] && !verificar_atendimento(u, x_atual) && u!=j )
                            {
                                    x_atual[m][u] = 1;
                                    fo_atual +=  demanda[u];
                                    capacidade_residual_utilizada += demanda[u];
                            }
                    }

                }
                    if( fo_atual > fo_star)
                    {
                        fo_star = fo_atual;
                        x_star = x_atual;
                    }

            }
            fo = fo_star;
            x = x_star;
        }
        capacidade_residual_utilizada = 0;
        cidades_proximas.clear();
    }
    return fo_star;

}

int first_improvement(vector < vector < int > > &x, vector <int> &y, vector <int> &z, vector <int> &demanda, vector < vector <float> > &dist, vector <int> &sedes, int Cap, int R, int nC)
{
    int fo, fo_star, i, k, j;
    vector < vector < int > > x_atual;
    vector < vector < int > > x_star;
    vector <int> y_atual;
    vector <int> z_atual;
    vector <int> y_star;
    vector <int> z_star;
    vector <int> cidades_alocadas;
    x_atual = x_star = x;
    y_atual = y_star = y;
    z_atual = z_star = z;

    fo = fo_star = calcula_fo(x, demanda);

    for(int u = 0; u < sedes.size(); u ++)
    {
        i = sedes[u];
        cidades_alocadas.clear();
        for(int n = 0; n < nC; n++)
        {
            if(x[i][n] == 1)
            {
                cidades_alocadas.push_back(n);
            }
        }

        for(int n = 0; n < cidades_alocadas.size(); n++)
        {
            j = cidades_alocadas[n];
            for(int v = 0; v < sedes.size(); v++)
            {
                k = sedes[v];

                if( i!= k && dist[k][j] <= R)
                {
                    fo = vizinho(x_atual, y_atual, z_atual, demanda, dist, Cap,  R, nC,  j,  i, k );

                    if( fo > fo_star)
                    {

                        fo_star = fo;
                        x_star[i] = x_atual[i];
                        x_star[k] = x_atual[k];
                        x[i] = x_star[i];
                        x[k] = x_star[k];
                        return fo_star;

                    }
                        x_atual[i] = x[i];
                        x_atual[k] = x[k];

                }

            }
        }
    }

    return fo_star;
}

void validador(vector < vector <int> > &x, vector<int> &y, vector <int> &demanda, int Cap)
{
    int demanda_atendida = 0, demanda_total_atendida = 0;
    cout << "\n Validador\n";
    cout << "---------------------------------------------------------------------\n";
    for(int i = 0; i < x.size(); i++)
    {
        if(y[i] > 0)
        {
            for(int j = 0; j < x.size(); j++)
            {
                demanda_atendida += demanda[j]*x[i][j];
            }
            demanda_total_atendida += demanda_atendida;
            cout << "Capacidade: " << Cap*y[i] << "\t qtd de mamografos: "<<y[i] << "\t demanda atendida: " << demanda_atendida;
            if(Cap*y[i] < demanda_atendida)
            {
                cout << " capacidade estourada\n";
            }
            else{
                cout << " capacidade respeitada\n";
            }
        }
        demanda_atendida = 0;

    }
    cout << "---------------------------------------------------------------------\n";
    cout << "Demanda total atendida: " << demanda_total_atendida << "\n";

}

void GRASP(vector < vector <int> > &x, vector < int > &y, vector < int > &z, vector < int > &demanda, vector < vector < float > > &dist, set <int> C, vector <int> &sedes, int Cap, int qM, int dMin, int nC, int R, float alpha, int GRASPmax)
{
    remove("resultados.txt");
    ofstream dados("resultados.txt", ios_base::app);


    vector <int> y_atual(nC, 0);
    vector <int> z_atual(nC, 0);
    vector < vector <int> > x_atual(nC, y_atual);

    int fo_atual = INT_MIN;
    int fo_star = INT_MIN;
    int fo_construtiva = 0;
    double tempo = 0.0;
    clock_t begin = clock();

for(int i = 0; i < GRASPmax; i++)
{

    fo_construtiva = construtiva(x_atual,  y_atual, z_atual,  demanda , dist, C, sedes, Cap, qM, dMin, R,  nC, alpha);
    fo_atual = first_improvement(x_atual,  y_atual, z_atual, demanda, dist, sedes, Cap, R, nC);

    if(fo_atual < 0)
    {
        fo_atual = fo_construtiva;
    }
    dados << i + 1 << " " << fo_atual << "\n";
    if(  fo_atual > fo_star )
    {
        x = x_atual;
        y = y_atual;
        z = z_atual;

        fo_star = fo_atual ;
    }

    for(int i = 0; i < nC; i++)
    {
        y_atual[i] = 0;
        z_atual[i] = 0;

    }

    for(int i = 0; i < nC; i++)
    {
        for(int j = 0; j < nC; j++)
        {
            x_atual[i][j] = 0;

        }

    }

}
clock_t end = clock();
tempo += (double)(end - begin) / CLOCKS_PER_SEC;
cout << "GRASP: " << fo_star << "\n\n";
cout << "Tempo de execucao: " << tempo << "\n";


}


int main()
{
    srand(time(NULL));
    int Cap;
    int qM;
    int R;
    int dMin;
    int nC;
    float aux1;
    vector <int> demanda;
    vector < vector <float> > dist;
    vector <float> aux2;
    set <int> C;
    ifstream dados("MG-310.dat");
    dados >>  Cap;
    dados >> qM;
    dados >> R;
    dados >> dMin;
    dados >> nC;
    vector <int> y(nC, 0);
    vector <int> z(nC, 0);
    vector < vector < int > > x(nC, y);
    vector <int> sedes;
    for(int i = 0; i < nC; i++)
    {
        dados >> aux1;
        demanda.push_back(aux1);


    }

    for(int i = 0; i < nC; i++)
    {
        for(int i = 0; i < nC; i++)
            {
                dados >> aux1;
                aux2.push_back(aux1);

            }
            dist.push_back(aux2);
            aux2.clear();
    }

    for(int i = 0; i < nC; i++)
    {
        if(demanda[i] > dMin)
        {
            C.insert(i);
        }
    }

float alpha = 1.00;
int GRASPmax = 100;

GRASP(x, y, z, demanda, dist, C, sedes, Cap, qM, dMin, nC, R, alpha, GRASPmax);
validador(x, y, demanda, Cap);



}
