#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;time.h&gt;
int max(int a, int b) {
return (a &gt; b) ? a : b;
}
int knapsack(int W, int wt[], int val[], int n) {
int dp[W + 1];
// Initialize all dp values to 0

for (int w = 0; w &lt;= W; w++)
dp[w] = 0;
// Build table dp[] in bottom-up manner
for (int i = 0; i &lt; n; i++) {
// Traverse weights backwards to avoid recomputation
for (int w = W; w &gt;= wt[i]; w--) {
dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
}
}
return dp[W];
}
int main() {
int n, W;
printf(&quot;Enter number of items: &quot;);
scanf(&quot;%d&quot;, &amp;n);
int *val = (int *)malloc(n * sizeof(int));
int *wt = (int *)malloc(n * sizeof(int));
srand(time(NULL));
// Randomly generate item values and weights
for (int i = 0; i &lt; n; i++) {
val[i] = (rand() % 100) + 1;
wt[i] = (rand() % 50) + 1;
}
W = n * 15;
printf(&quot;Generated knapsack capacity: %d\n&quot;, W);
clock_t start, end;
double cpu_time_used;
start = clock();
int result = knapsack(W, wt, val, n);
end = clock();
cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

printf(&quot;\nMaximum value in Knapsack = %d\n&quot;, result);
printf(&quot;Time taken to execute: %f seconds\n&quot;, cpu_time_used);
free(val);
free(wt);
return 0;
}