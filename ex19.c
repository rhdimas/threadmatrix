/* ************************************************************************ *
 *    THREADMATRIX, VERSION                                                 *
 *    Multiplies matrices using threads                                     *
 *                                                                          *
 *    Copyright (C) 2015 by Ricardo Henrique Simplicio Dimas                *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or modify  *
 *    it under the terms of the GNU General Public License as published by  *
 *    the Free Software Foundation; either version 2 of the License, or     *
 *    (at your option) any later version.                                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program; if not, write to the                         *
 *    Free Software Foundation, Inc.,                                       *
 *    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                          *
 *    To contact the author, please write to:                               *
 *    Ricardo Henrique Simplicio Dimas <rhenrique.dimas@gmail.com>          *
 *    Webpage: http://www.upe.br                                            *
 *    Phone: +55 (81) 99730-4919                                            *
 * ************************************************************************ *
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 
#include <time.h>
#include <pthread.h>

#define MAX 1080

typedef struct st_rest
{
    long int vet1[MAX][MAX],
             vet2[MAX][MAX],
             total[MAX][MAX];
    int thr[9], indice;
    struct st_rest *prox;
}Matriz;


void* inc1(void *vet1);
void* mult(void* m2);
void* inc2(void* v1);
void ordena(int n, Matriz *m);


int main(void)
{
    int i,j;
    clock_t tempo1, tempo2;

    double tempo[9];
    Matriz *m= malloc(sizeof(Matriz));
    pthread_t *tr = malloc(sizeof(pthread_t));
    pthread_t *tr2 = malloc(sizeof(pthread_t));
    pthread_t t[9];

    for(i = 0; i < 9; i++)
        m->thr[i]=0;

    srand(time(NULL));

    pthread_create(tr, NULL, inc1, (void*)m);
    pthread_create(tr2, NULL, inc2, (void*)m);

    m->indice=0;

    for(i = 1; i <= 8; i++)
    {
        tempo1 = time(NULL);
        ordena(i, m);
        for(j = 1; j <= i; j++)
            pthread_join(t[j], NULL);

        m->indice=0;
        for(k = 0; k <= i; k++)
            m->thr[k] = 0;
        tempo2 = time(NULL);

        tempo[i] = tempo2 - tempo1;
    }

    for(k = 1; k <= 8; k++)
        printf("Threads: %d | Tempo: %f segundos\n", k, tempo[k]);
  
    return 0;
}

void* ordena(int n, Matriz *m)
{
    int i, divisao,resto;
    divisao= MAX / n;
    resto = MAX%n;

    for (i=1; i<=n; i++)
        m->thr[i] = m->thr[i] + divisao;

    if (resto!=0)
         for (i=1; i<= n; i++)
             {
                 m->thr[i] ++;
                 m->thr[i]+= m->thr[i-1];
             }
         for(i=resto+1; i<=n; i++)
             m->thr[i]+=m->thr[i-1];

    return NULL;
}

void* inc1(void* v1)
{
    int i,j;
    Matriz *m = (Matriz *)v1;

    for(i=0;i<MAX;i++)
        for(j=0;j<MAX;j++)
            m-> vet1[i][j] = rand()%MAX;

    return NULL;
}

void* inc2(void* v1)
{
    int i,j;
    Matriz *m = (Matriz *)v1;

    for(i=0; i<MAX; i++)
        for(j=0; j<MAX; j++)
            m-> vet2[i][j]=rand()%MAX;

    return NULL;
}

void* mult(void* m2)
{
    Matriz *m = (Matriz *)m2;
    int i=m->indice++;
    int k = 0, soma = 0;

    if (m->indice<8)
        m->indice++;
    else
        m->indice=0;

    for(k=m->thr[m->indice-1]; k<m->thr[m->indice]; k++)
    {
        for(l = 0; l < MAX; l++)
        {
            soma = 0;
            for(i = 0; i < MAX; i++)
                soma = m->vetor1[k][i] * m->vetor2[i][l]+soma;
            m->resultado[k][l]=soma;
        }
    }

    return NULL;
}

