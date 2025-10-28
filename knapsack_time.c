#include &lt;stdio.h&gt;
#include &lt;time.h&gt;
#include &lt;stdlib.h&gt;
struct Item {
int value, weight;
float ratio;
};
void swap(struct Item *a, struct Item *b) {
struct Item temp = *a;
*a = *b;
*b = temp;
}
void sortItems(struct Item items[], int n) {
for (int i = 0; i &lt; n-1; i++) {
for (int j = i+1; j &lt; n; j++) {
if (items[i].ratio &lt; items[j].ratio)
swap(&amp;items[i], &amp;items[j]);
}
}
}
float fractionalKnapsack(int W, struct Item items[], int n) {
sortItems(items, n);
int curWeight = 0;
float finalValue = 0.0;
for (int i = 0; i &lt; n; i++) {
if (curWeight + items[i].weight &lt;= W) {
curWeight += items[i].weight;
finalValue += items[i].value;
} else {
int remain = W - curWeight;
finalValue += items[i].value * ((float)remain / items[i].weight);
break;
}
}

return finalValue;
}
int main() {
int n, W;
printf(&quot;Enter number of items: &quot;);
scanf(&quot;%d&quot;, &amp;n);
struct Item items[n];
srand(time(NULL));
for (int i = 0; i &lt; n; i++) {
items[i].value = (rand() % 100) + 1;
items[i].weight = (rand() % 50) + 1;
items[i].ratio = (float)items[i].value / items[i].weight;
}
W = n * 15;
printf(&quot;Randomly generated knapsack capacity: %d\n&quot;, W);
clock_t start, end;
double cpu_time_used;
start = clock();
float result = fractionalKnapsack(W, items, n);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf(&quot;\nMaximum value in Knapsack = %.2f\n&quot;, result);
printf(&quot;Time taken to execute: %f seconds\n&quot;, cpu_time_used);
return 0;
}