#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 8
#define R 10.0
#define M 50

int main()
{
    int i, j, k, t, E = 0;
    int array[N][N] = {0};
    int array_weak[N][N] = {0};
    float vertex[N][2];
    int visited[N] = {0};
    int un_visited[N] = {0};
    int un_num;
    int c_num;

    char CPLEX[100] = "E:\\CDS_something\\release version\\RANDOM_GRAPH\\out_CPLEX";
    char GRASP[100] = "E:\\CDS_something\\release version\\RANDOM_GRAPH\\out_GRASP";
    char GREEDY[100] = "E:\\CDS_something\\release version\\RANDOM_GRAPH\\out_GREEDY";
    int sum_s = strlen(CPLEX);

    while(1)
    {
        memset(array,0,sizeof(int)*N*N);
        memset(array_weak,0,sizeof(int)*N*N);
        memset(visited,0,sizeof(int)*N);
        memset(un_visited,0,sizeof(int)*N);
        un_num = 0;
        c_num = 0;
        E = 0;
        for(i = 0; i < N; i++)
        {
            vertex[i][0] = rand()%M;
            vertex[i][1] = rand()%M;
        }

        for(i = 0; i < N-1; i++)
        {
            for(j = i+1; j < N; j++)
            {
                if(sqrt(pow(vertex[i][0]-vertex[j][0],2)+pow(vertex[i][1]-vertex[j][1],2))< R)
                {
                    E++;
                    array[i][j] = 1;
                    array[j][i] = 1;
                    array_weak[i][j] = 1;
                    array_weak[j][i] = 1;
                }
            }
        }
        visited[0] = 1;
        un_visited[0] = 0;
        un_num = 1;
        while(un_num != 0)
        {
            t = un_visited[un_num-1];
            un_num--;
            c_num++;
            for(i = 0; i < N; i++)
            {
                if(array[t][i] == 1 && visited[i] == 0)
                {
                    un_visited[un_num++] = i;
                    visited[i] = 1;
                }
            }
        }
        if(c_num == N)
            break;

    }


    for(i = 0; i < N-1; i++)
    {
        for(j = i+1; j < N; j++)
        {
            if(array[i][j] == 1)
            {
                for(k = 0; k < N; k++)
                {
                    if(k == i)
                        continue;
                    if(array[j][k] == 1)
                    {
                        array_weak[i][k] = 1;
                        array_weak[k][i] = 1;
                    }
                }
                for(k = 0; k < N; k++)
                {
                    if(k == j)
                        continue;
                    if(array[i][k] == 1)
                    {
                        array_weak[j][k] = 1;
                        array_weak[k][j] = 1;
                    }
                }
            }
        }
    }
    sprintf(CPLEX+sum_s,"_%d_%.0f_%d.txt",M, R, N);
    sprintf(GRASP+sum_s,"_%d_%.0f_%d.mtx",M, R, N);
    sprintf(GREEDY+sum_s,"_%d_%.0f_%d.mtx",M, R, N);
    freopen(CPLEX,"w",stdout);

    printf("int array[N][N]={\n");
    for(i = 0; i < N; i++)
    {
        printf("{");
        for(j = 0; j < N-1; j++)
        {
            printf("%d,", array[i][j]);
        }
        printf("%d},\n", array[i][j]);
    }
    printf("};\n");

    printf("int array_weak[N][N]={\n");
    for(i = 0; i < N; i++)
    {
        printf("{");
        for(j = 0; j < N-1; j++)
        {
            printf("%d,", array_weak[i][j]);
        }
        printf("%d},\n", array_weak[i][j]);
    }
    printf("};\n");

    freopen(GRASP,"w",stdout);
    printf("%d %d\n", N, E);

    for(i = 0; i < N-1; i++)
    {
        for(j = i+1; j < N; j++)
        {
            if(array[i][j] == 1)
            {
                printf("%d %d\n", i, j);
            }
        }

    }

    freopen(GREEDY,"w",stdout);
    printf("%d %d\n", N, E*2);

    for(i = 0; i < N-1; i++)
    {
        for(j = i+1; j < N; j++)
        {
            if(array[i][j] == 1)
            {
                printf("%d %d\n", i, j);
                printf("%d %d\n", j, i);
            }
        }

    }

}
