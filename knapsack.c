#include <stdio.h>

#define MAX 100

struct Item
{
    int id;
    float weight;
    float profit;
    float ratio;
    float fraction;
};

/* Calculate Profit/Weight Ratio */
void calculateRatio(struct Item item[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (item[i].weight > 0)
            item[i].ratio = item[i].profit / item[i].weight;
        else
            item[i].ratio = 0;
    }
}

/* Enter Item Details */
void enterDetails(struct Item item[], int *n, float *capacity)
{
    int i;

    printf("\nEnter number of items: ");
    scanf("%d", n);

    if (*n <= 0 || *n > MAX)
    {
        printf("\nInvalid number of items.\n");
        *n = 0;
        return;
    }

    printf("Enter vehicle capacity: ");
    scanf("%f", capacity);

    if (*capacity <= 0)
    {
        printf("\nCapacity must be positive.\n");
        *capacity = 0;
        return;
    }

    for (i = 0; i < *n; i++)
    {
        item[i].id = i + 1;

        printf("\nItem %d\n", i + 1);

        do
        {
            printf("Enter weight: ");
            scanf("%f", &item[i].weight);

            if (item[i].weight <= 0)
                printf("Weight must be positive. Please enter again.\n");

        } while (item[i].weight <= 0);

        do
        {
            printf("Enter profit/value: ");
            scanf("%f", &item[i].profit);

            if (item[i].profit <= 0)
                printf("Profit must be positive. Please enter again.\n");

        } while (item[i].profit <= 0);

        item[i].ratio = 0;
        item[i].fraction = 0;
    }

    calculateRatio(item, *n);

    printf("\nItem details entered successfully.\n");
}

/* Display Item Details */
void displayDetails(struct Item item[], int n)
{
    int i;

    if (n == 0)
    {
        printf("\nPlease enter item details first.\n");
        return;
    }

    calculateRatio(item, n);

    printf("\n===============================================\n");
    printf("              ITEM DETAILS\n");
    printf("===============================================\n");

    printf("ID\tWeight\tProfit\tRatio\n");
    printf("-----------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               item[i].id,
               item[i].weight,
               item[i].profit,
               item[i].ratio);
    }

    printf("-----------------------------------------------\n");
}

/* Display Profit/Weight Ratio */
void showRatio(struct Item item[], int n)
{
    int i;

    if (n == 0)
    {
        printf("\nPlease enter item details first.\n");
        return;
    }

    calculateRatio(item, n);

    printf("\n===============================================\n");
    printf("         PROFIT/WEIGHT RATIO TABLE\n");
    printf("===============================================\n");

    printf("ID\tWeight\tProfit\tRatio\n");
    printf("-----------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               item[i].id,
               item[i].weight,
               item[i].profit,
               item[i].ratio);
    }

    printf("-----------------------------------------------\n");
}

/* Sort Items by Decreasing Profit/Weight Ratio */
void sortItems(struct Item item[], int n)
{
    int i, j;
    struct Item temp;

    if (n == 0)
    {
        printf("\nPlease enter item details first.\n");
        return;
    }

    calculateRatio(item, n);

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (item[j].ratio < item[j + 1].ratio)
            {
                temp = item[j];
                item[j] = item[j + 1];
                item[j + 1] = temp;
            }
        }
    }

    printf("\nItems sorted by decreasing Profit/Weight Ratio.\n");

    printf("\n===============================================\n");
    printf("          SORTED ITEM TABLE\n");
    printf("===============================================\n");

    printf("ID\tWeight\tProfit\tRatio\n");
    printf("-----------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               item[i].id,
               item[i].weight,
               item[i].profit,
               item[i].ratio);
    }

    printf("-----------------------------------------------\n");
}

/* Find Maximum Profit using Fractional Knapsack */
void findMaximumProfit(struct Item item[], int n, float capacity)
{
    int i;
    float remaining;
    float usedCapacity = 0;
    float totalProfit = 0;

    if (n == 0)
    {
        printf("\nPlease enter item details first.\n");
        return;
    }

    if (capacity <= 0)
    {
        printf("\nPlease enter a valid vehicle capacity first.\n");
        return;
    }

    /* Sort according to Profit/Weight ratio */
    sortItems(item, n);

    remaining = capacity;

    /* Reset fractions */
    for (i = 0; i < n; i++)
    {
        item[i].fraction = 0;
    }

    /* Greedy selection */
    for (i = 0; i < n; i++)
    {
        if (remaining <= 0)
            break;

        /* Take complete item */
        if (item[i].weight <= remaining)
        {
            item[i].fraction = 1;

            remaining = remaining - item[i].weight;
            usedCapacity = usedCapacity + item[i].weight;
            totalProfit = totalProfit + item[i].profit;
        }

        /* Take fractional part */
        else
        {
            item[i].fraction = remaining / item[i].weight;

            usedCapacity = usedCapacity + remaining;

            totalProfit = totalProfit +
                          (item[i].profit * item[i].fraction);

            remaining = 0;
        }
    }

    printf("\n===============================================\n");
    printf("           GREEDY LOADING RESULT\n");
    printf("===============================================\n");

    printf("Vehicle Capacity   : %.2f\n", capacity);
    printf("Used Capacity      : %.2f\n", usedCapacity);
    printf("Remaining Capacity : %.2f\n", remaining);
    printf("Maximum Profit     : %.2f\n", totalProfit);

    printf("-----------------------------------------------\n");

    if (usedCapacity <= capacity)
        printf("Weight does not exceed the capacity.\n");
    else
        printf("Capacity exceeded.\n");

    printf("===============================================\n");
}

/* Display Selected Items */
void displaySelected(struct Item item[], int n)
{
    int i;
    float selectedWeight;
    float selectedProfit;
    float totalWeight = 0;
    float totalProfit = 0;

    if (n == 0)
    {
        printf("\nPlease enter item details first.\n");
        return;
    }

    printf("\n===============================================================\n");
    printf("                  LOADING PLAN\n");
    printf("===============================================================\n");

    printf("ID\tWeight\tProfit\tFraction\tSelected Weight\tSelected Profit\n");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (item[i].fraction > 0)
        {
            selectedWeight =
                item[i].weight * item[i].fraction;

            selectedProfit =
                item[i].profit * item[i].fraction;

            printf("%d\t%.2f\t%.2f\t%.2f\t\t%.2f\t\t%.2f\n",
                   item[i].id,
                   item[i].weight,
                   item[i].profit,
                   item[i].fraction,
                   selectedWeight,
                   selectedProfit);

            totalWeight = totalWeight + selectedWeight;
            totalProfit = totalProfit + selectedProfit;
        }
    }

    printf("---------------------------------------------------------------\n");

    printf("Total Weight Used : %.2f\n", totalWeight);
    printf("Maximum Profit    : %.2f\n", totalProfit);

    printf("===============================================================\n");

    printf("\nItems loaded:\n");

    for (i = 0; i < n; i++)
    {
        if (item[i].fraction > 0)
        {
            printf("Item %d : %.2f%% loaded\n",
                   item[i].id,
                   item[i].fraction * 100);
        }
    }
}

/* Main Function */
int main()
{
    struct Item item[MAX];

    int n = 0;
    int choice;
    float capacity = 0;

    do
    {
        printf("\n");
        printf("===============================================\n");
        printf("       CARGO LOADING OPTIMIZER\n");
        printf("       USING FRACTIONAL KNAPSACK\n");
        printf("===============================================\n");

        printf("1. Enter Item Details\n");
        printf("2. Display Item Details\n");
        printf("3. Calculate Profit/Weight Ratio\n");
        printf("4. Sort Items by Ratio\n");
        printf("5. Find Maximum Profit\n");
        printf("6. Display Loading Plan\n");
        printf("7. Exit\n");

        printf("===============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterDetails(item, &n, &capacity);
                break;

            case 2:
                displayDetails(item, n);
                break;

            case 3:
                showRatio(item, n);
                break;

            case 4:
                sortItems(item, n);
                break;

            case 5:
                findMaximumProfit(item, n, capacity);
                break;

            case 6:
                displaySelected(item, n);
                break;

            case 7:
                printf("\nProgram terminated successfully.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}
