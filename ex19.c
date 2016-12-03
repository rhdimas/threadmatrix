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

#define MAX 1000

typedef struct st_rest
{
    long int vet1[MAX][MAX],
             vet2[MAX][MAX],
             total[MAX][MAX];
    int thr[9], i;
    struct st_rest *prox;
}Matriz;


void* inc1(void *vetor1);
void* mult(void* m2);
void* inc2(void* v1);
void organize(int n, Matriz *m);


int main(void)
{

    return 0;
}




