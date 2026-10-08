#include <stdio.h>

struct Item {
    int id;
    float weight;
    float profit;
    float pw;
    float fraction;
};

int main() {
    struct Item item[100], temp;
    int n, i, j;
    float capacity, remainingCap, usedCap = 0, totalProfit = 0;


    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter vehicle capacity: ");
    scanf("%f", &capacity);

    
    for (i = 0; i < n; i++) {
        item[i].id = i + 1;

        printf("\nItem %d\n", i + 1);

        printf("Enter weight: ");
        scanf("%f", &item[i].weight);

        printf("Enter profit: ");
        scanf("%f", &item[i].profit);

        item[i].pw = item[i].profit / item[i].weight;
        item[i].fraction = 0;
    }

   // sort pw
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (item[i].pw < item[j].pw) {
                temp = item[i];
                item[i] = item[j];
                item[j] = temp;
            }
        }
    }

  
    remainingCap = capacity;

    for (i = 0; i < n; i++) {

        if (remainingCap == 0)
            break;

        if (item[i].weight <= remainingCap) {
          // taking complete item
            item[i].fraction = 1;

            remainingCap = remainingCap - item[i].weight;
            usedCap = usedCap + item[i].weight;
            totalProfit = totalProfit + item[i].profit;
        }
        else {
            // Take fractional part 
            item[i].fraction = remainingCap / item[i].weight;

            usedCap = usedCap + remainingCap;
            totalProfit = totalProfit +(item[i].profit * item[i].fraction);

            remainingCap = 0;
        }
    }

   printf("\n");
    printf("p/w table : \n");
 printf("\n");
    printf("ID\tWeight\tProfit\tRatio\tFraction\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\t%.2f\t%.2f\n",
               item[i].id,
               item[i].weight,
               item[i].profit,
               item[i].pw,
               item[i].fraction);
    }

     printf("\n");
    printf("\nloaded greedily until capacity\n");

    for (i = 0; i < n; i++) {
        if (item[i].fraction > 0) {
            printf("Item %d: %.2f%% loaded\n",
                   item[i].id,
                   item[i].fraction * 100);
        }
    }

  
   printf("\n");
    printf("Vehicle Capacity   : %.2f\n", capacity);
    printf("Used Capacity      : %.2f\n", usedCap);
    printf("Remaining Capacity : %.2f\n", remainingCap);
    printf("Maximum Profit     : %.2f\n", totalProfit);
 printf("\n");
    if (usedCap <= capacity)
        printf(" Weight does not exceed the capacity.\n");
    else
        printf("Capacity exceeded.\n");

    return 0;
}
