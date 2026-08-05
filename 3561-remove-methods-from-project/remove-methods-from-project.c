
#include <stdbool.h>
#include <stdlib.h>

void dfs(int node, int *head, int *to, int *next, bool *visited)
{
    visited[node] = true;

    for (int i = head[node]; i != -1; i = next[i])
    {
        int v = to[i];

        if (!visited[v])
            dfs(v, head, to, next, visited);
    }
}

int* remainingMethods(int n, int k, int** invocations, int invocationsSize,
                      int* invocationsColSize, int* returnSize)
{
    
    int *head = (int *)malloc(n * sizeof(int));
    int *to = (int *)malloc(invocationsSize * sizeof(int));
    int *next = (int *)malloc(invocationsSize * sizeof(int));
    bool *visited = (bool *)calloc(n, sizeof(bool));

    for (int i = 0; i < n; i++)
        head[i] = -1;

    int idx = 0;

    for (int i = 0; i < invocationsSize; i++)
    {
        int u = invocations[i][0];
        int v = invocations[i][1];

        to[idx] = v;
        next[idx] = head[u];
        head[u] = idx;
        idx++;
    }

    
    dfs(k, head, to, next, visited);

    
    for (int i = 0; i < invocationsSize; i++)
    {
        int u = invocations[i][0];
        int v = invocations[i][1];

        if (!visited[u] && visited[v])
        {
            int *ans = (int *)malloc(n * sizeof(int));

            for (int j = 0; j < n; j++)
                ans[j] = j;

            *returnSize = n;
            return ans;
        }
    }

    int *ans = (int *)malloc(n * sizeof(int));
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            ans[count++] = i;
    }

    *returnSize = count;

    free(head);
    free(to);
    free(next);
    free(visited);

    return ans;
}