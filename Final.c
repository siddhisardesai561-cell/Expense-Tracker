// add edit option

#include <stdio.h>
#include <stdlib.h>

struct Expense
{
    int id;
    char date[20];
    char category[20];
    float amount;
};

void addExpense();
void viewExpense();
void editExpense();

int main()
{
    int choice;

    while(1)
    {
        printf("\n==============================");
        printf("\n      EXPENSE TRACKER");
        printf("\n==============================");
        printf("\n1. Add Expense");
        printf("\n2. View Expenses");
        printf("\n3. Edit Expense");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpense();
                break;

            case 3:
                editExpense();
                break;

            case 4:
                printf("\nThank You!\n");
                exit(0);    

            default:
                printf("\nInvalid Choice\n");
        }
    }

    return 0;
}

void addExpense()
{
    FILE *fp;
    struct Expense e;

    fp = fopen("expense.dat", "ab");

    if(fp == NULL)
    {
        printf("\nUnable to open file!\n");
        return;
    }

    printf("\nEnter Expense ID: ");
    scanf("%d", &e.id);

    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", e.date);

    printf("Enter Category: ");
    scanf("%s", e.category);

    printf("Enter Amount: ");
    scanf("%f", &e.amount);

    fwrite(&e, sizeof(e), 1, fp);

    fclose(fp);

    printf("\nExpense Saved Successfully!\n");
}

void viewExpense()
{
    FILE *fp;
    struct Expense e;

    fp = fopen("expense.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Expense Records Found!\n");
        return;
    }

    printf("\n=================================================");
    printf("\nID\tDate\t\tCategory\tAmount");
    printf("\n=================================================\n");

    while(fread(&e, sizeof(e), 1, fp) == 1)
    {
        printf("%d\t%s\t%s\t\t%.2f\n",
               e.id,
               e.date,
               e.category,
               e.amount);
    }

    fclose(fp);
}

void editExpense()
{
    FILE *fp, *temp;
    struct Expense e;
    int searchId;
    int found = 0;

    fp = fopen("expense.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Expense Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("\nEnter Expense ID to Edit: ");
    scanf("%d", &searchId);

    while(fread(&e, sizeof(e), 1, fp) == 1)
    {
        if(e.id == searchId)
        {
            found = 1;

            printf("\nExpense Found!\n");

            printf("Enter New Date: ");
            scanf("%s", e.date);

            printf("Enter New Category: ");
            scanf("%s", e.category);

            printf("Enter New Amount: ");
            scanf("%f", &e.amount);
        }

        fwrite(&e, sizeof(e), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("expense.dat");
    rename("temp.dat", "expense.dat");

    if(found)
        printf("\nExpense Updated Successfully!\n");
    else
        printf("\nExpense ID Not Found!\n");
}