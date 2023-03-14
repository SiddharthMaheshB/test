/*TO DO:


BUGS: 

*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>

struct dish
{
    char name[20];
    int price;
};

struct bill
{
    int bill_no;
    int table_no;
    int status;
    int total_dishes;
    struct dish dishes[10];
    int total_bill;
};

int menu_status = 0;

void display_menu(struct bill*);
void create_menu(struct bill*,struct bill*);
void create_order(struct bill*, struct bill*);
void check_table(struct bill*, struct bill*);
void initialise(struct bill*,struct bill*);
void admin_login(struct bill*, struct bill*);
void edit_order(struct bill*, struct bill*);
void login(struct bill*, struct bill*);
void admin(struct bill*, struct bill*);
void cust(struct bill*, struct bill*);
void display_bill(struct bill*, struct bill*);
void view_table(struct bill*, struct bill*);
void cust_login(struct bill*, struct bill*);
void checkout(struct bill*, struct bill*);
void edit_menu(struct bill*, struct bill*);


int main()
{
    struct bill menu,table[5];
    struct bill *menup = &menu,*tablep = &table[0];
    
    initialise(menup,tablep);    
}


void display_menu(struct bill* menup)
{
    int i;

    printf("S.no Dish                  Cost\n");
    for(i=0;i<menup->total_dishes;i++)
    {
        printf("%5d %-20s %d\n",i+1,menup->dishes[i].name, menup->dishes[i].price);
    }
}

void create_menu(struct bill* menup,struct bill* tablep)
{
    system("cls");
    FILE *f1;
    menup->total_dishes=0;
    f1 = fopen("menu.txt","r");
    char ch;
    int i=0,n=0,mode=0,j=0;
    char str[20];
    int num;
    
    
    FILE *fp;
    fp = fopen("menu.txt", "r"); // assuming the file name is input.txt
    
    if (fp == NULL) {
        printf("Unable to open file.");
    }
    else{
        while (fscanf(fp, "%[^,],%d\n", str, &num) == 2) 
        { // reading values from file
            //printf("String: %s\n", str);
            strcpy(menup->dishes[i].name,str);
            //printf("Integer: %d\n", num);
            menup->dishes[i].price = num;
            menup->total_dishes++;
            i++;
        }
    }
    
    fclose(fp);
    display_menu(menup);
    
    menu_status = 1;
    printf("Menu updated!\n");
    Sleep(2000);
    login(menup,tablep);
}

void create_order(struct bill* menup, struct bill* tablep)
{
    char check = 'n';
    int input=1,i=0;
    int flag = 1;
    system("cls");
    tablep->status = 1;
    tablep->bill_no = rand()%100+1;
    printf("Table no: %d\n",tablep->table_no);
    printf("Your Bill no is: %d\n",tablep->bill_no);
    printf("\e[1mPlease keep note of your bill number.\e[m\n\n");
    while(check == 'n')
    {
        i = 0;
        display_menu(menup);
        printf("\nPlease enter the serial number of the items you would like to order (if you want more than one quantity of an item, please enter its serial number twice): \n");
        printf("Please enter 0 when you are done\n");
        do
        {
            if(flag == 0)
            {
                tablep->dishes[i-1].price = menup->dishes[input-1].price;
                strcpy(tablep->dishes[i-1].name,menup->dishes[input-1].name);
            }
            flag = 0;
            scanf("%d",&input);
            if(input<1 || input>menup->total_dishes)
            {
                flag = 1;
            }
            i++;
        }while(input!=0);
        i--;
        tablep->total_dishes = i;
        printf("\e[1mThis is your order: \e[m\n");
        display_menu(tablep);
        printf("\nfinalize? (y/n)\n");
        scanf("\n%c",&check);
    }
    printf("Your order has been finalised!");
    Sleep(2000);
    cust(menup,tablep);
}

void check_table(struct bill* menup, struct bill* tablep)
{
    int i;
    int check = 0;
    for(i=0;i<5;i++)
    {
        if((tablep+i)->status==1)
            continue;
        else
        {
            check = 1;
            break;
        }
    }
    if(check == 1)
    {
        printf("Table %d is free!\n",i+1);
        //tablep->table_no = i+1;
        (tablep+i)->status = 1;
        Sleep(2000);
        create_order(menup,tablep+i);
    }
    else
    {
        printf("All tables are currently full, please wait for some time");
    }
}

void initialise(struct bill* menup,struct bill* tablep)
{
    char table_no;
    int i;

    //setting all tables status to unoccupied
    for(i=0;i<5;i++)
    {
        (tablep+i)->status = 0;
        (tablep+i)->table_no = i+1;
        
    }
    
    create_menu(menup,tablep);
}

void admin_login(struct bill* menup, struct bill* tablep)
{
    char password[10] = "password";
    int i;
    printf("Logging in as admin...\n");
    for(i=0;i<5;i++){
        printf("Enter Password: ");
        scanf("%s",password);
        
        if(!strcmp(password,"password"))
        {
            printf("Successful login!\n");
            Sleep(2000);
            admin(menup,(tablep-((tablep->table_no)-1)));
            break;
        }
        else{
            printf("Please try again\n");
        }
    }
    printf("Too many incorrect attempts. Logging out...");
    Sleep(2000);
    login(menup,(tablep-((tablep->table_no)-1)));
}

void edit_order(struct bill* menup, struct bill* tablep)
{
    char check = 'n';
    int i,input=1,j,flag=0,k,p;
    
    struct bill temp;
    while(check == 'n')
    {
        flag = 0;
        input = 1;
        display_menu(menup);
        printf("\nPlease enter the serial number of the items you would like to order (if you want more than one quantity of an item, please enter its serial number twice): \n");
        printf("Please enter 0 when you are done\n");
        
        for(i=0;input!=0;i++)
        {
            if(flag == 1)
            {
                temp.dishes[i].price = menup->dishes[input-1].price;
                strcpy(temp.dishes[i].name,menup->dishes[input-1].name);
            }
            scanf("%d",&input);
            flag = 1;
            if(input<1 || input>menup->total_dishes)
            {
                flag = 0;
                
            }
        }
        
        printf("\e[1mThis is your order: \e[m\n");
        display_menu(tablep);
        for(p=1;p<i;p++)
        {
            printf("%5d %-20s %d\n",(tablep->total_dishes)+p,temp.dishes[p].name, temp.dishes[p].price);
        }

        printf("\nfinalize? (y/n)");
        scanf("\n%c",&check);
        //printf("%c",check);
    }

    for(j=tablep->total_dishes,k=1;k<i;k++,j++)
    {
        //printf("%s\n",temp.dishes[k].name);
        tablep->dishes[j].price = temp.dishes[k].price;
        strcpy(tablep->dishes[j].name,temp.dishes[k].name);
    }
    tablep->total_dishes = j;
    Sleep(2000);
    cust(menup,tablep);
}

void login(struct bill* menup,struct bill* tablep)  
{

    //log in to tables system
    char table_no;
    system("cls");
    printf("Please enter your table number(if new, please enter 0)(if admin, please enter a)\nTo exit, enter e:\n");
    scanf("\n%c",&table_no);
    printf("\n");
    if(table_no == 'a')
    {  
        admin_login(menup,(tablep-((tablep->table_no)-1)));
    }
    else if(table_no == 'e')
    {
        printf("Exiting... ");
        Sleep(1000);
        exit(0);
    }
    else
    {
        if(menu_status == 1)            //checks if menu has been created or not
        {
            if((tablep + (((int)table_no)-49))->status == 1)
            {
                //printf("Table no: %d\n",(int)table_no-48);
                cust_login(menup,tablep+(((int)table_no)-49));
                //table_no(tablep+((int)table_no)-1);
            }
            else if(((int)table_no) == 48)
            {
                printf("Logging in as a new customer...");
                Sleep(1000);
                check_table(menup, (tablep-((tablep->table_no)-1)));
            }
            else
            {
                printf("Please enter valid table number\n");
                Sleep(2000);
            }
        }
        else
        {
            printf("The restaurant hasn't opened yet, please wait.\n");
            Sleep(3000);
        }
    }
    login(menup,tablep-((tablep->table_no)-1));
}

void admin(struct bill*menup,struct bill*tablep)
{
    int n;
    char yesNo;
    system("cls");
    printf("Welcome, Admin!\n");
    one:
    printf("What action would you like to perform?\n");
    printf("1. Edit menu\n");
    printf("2. View a table's order\n");
    printf("3. Close restraunt\n");
    printf("4. Log out\n");
    scanf("%d",&n);

    switch(n)
    {
        case 1:
            
            edit_menu(menup,(tablep-((tablep->table_no)-1)));
            break;
        case 2:
            //printf("view_table_order(tableno)\n");
            view_table(menup,tablep);
            break;
        case 3:
            printf("Are you sure you want to close the restaurant? (y/n)\n");
            scanf("\n%c",&yesNo);
            if(yesNo == 'y')
            {
                printf("Closing restaurant...\n");
                exit(0);
            }
            else
            {
                goto one;
            }
            break;
        case 4:
            printf("Logging out...");
            login(menup,tablep-((tablep->table_no)-1));
            break;
        default:
            printf("Invalid input\n");
    }
}

void cust(struct bill*menup,struct bill*tablep)
{
    int n;
    system("cls");
    printf("Welcome, customer!\n");
    printf("What action would you like to perform?\n");
    printf("1. Order more items\n");
    printf("2. View bill\n");
    printf("3. Log out\n");
    scanf("%d",&n);

    switch(n)
    {
        case 1:
            printf("Opening your order...\n");
            edit_order(menup,tablep);
            break;
        case 2:
            display_bill(menup,tablep);
            checkout(menup,tablep);
            break;
        case 3:
            printf("Logging out...\n");
            login(menup,tablep-((tablep->table_no)-1));
            break;
        default:
            printf("Invalid input\n");
    }

}

void display_bill(struct bill* menup, struct bill* tablep)
{
    int i,j;
    int quantity=1,sum=0,sno=1,rep=0;
    char yesno;
    printf("S.no Dish                  Cost  Quantity\n");
    for(i=0;i<tablep->total_dishes;i++)
    {
        quantity = 1;
        rep = 0;
        for(j=i-1;j>=0;j--)
        {
            if(strcmp(tablep->dishes[i].name,tablep->dishes[j].name) == 0)
            {
                rep = 1;
                break;
            }
        }
        if(rep == 0)
        {
            for(j=i+1;j<tablep->total_dishes;j++)
            {
                if(strcmp(tablep->dishes[i].name,tablep->dishes[j].name) == 0)
                {
                    quantity++;
                }
            }
            printf("%4d %-20s %5d  %d\n",sno,tablep->dishes[i].name, tablep->dishes[i].price,quantity);
            sno++;
            sum+= tablep->dishes[i].price*quantity;
        }
        else
        {
            continue;
        }

        
    }
    printf("\n\e[1mTotal amount: %d\e[m",sum);

    //checkout(menup,tablep);
    //login(menup,(tablep-((tablep->table_no)-1)));
}

void view_table(struct bill* menup, struct bill* tablep)
{
    int n;
    char temp;
    if(menu_status == 0)
    {
        printf("Restaurant is not open yet. Please create the menu first. ");
        Sleep(2000);
        admin(menup,(tablep-((tablep->table_no)-1)));
    }
    
    printf("Please enter the table number: \n");
    printf("Press 0 to go back\n");
    while(1)
    {
        scanf("%d",&n);
        if((tablep+n)->status == 1)
        {
            printf("\n\e[1mHere is the order and bill from table no. %d:\e[m\n",(tablep+(n-1))->table_no);
            printf("Bill no: %d\n",(tablep+(n-1))->bill_no);
            display_bill(menup,tablep+(n-1));
            printf("\nPress any key to go back");
            scanf("\n%c",&temp);
            admin(menup,(tablep-((tablep->table_no)-1)));
        }
        else if(n==0)
        {
            admin(menup,tablep);
        }
        else
        {
            if(n>5&&n<0)
            {
                printf("Invalid table number, please try again \n");
                printf("\n Press any key to go back");
                scanf("\n%c",&temp);
                admin(menup,(tablep-((tablep->table_no)-1)));
            }
            else
            {
                printf("Table is not occupied \n");
                printf("\n Press any key to go back");
                scanf("\n%c",&temp);
                admin(menup,(tablep-((tablep->table_no)-1)));
            }
        }
    }
}

void cust_login(struct bill* menup, struct bill* tablep)
{
    int n;
    int i;
    for(i=0;i<5;i++)
    {
        printf("Table no: %d\n",tablep->table_no);
        printf("Please enter your bill number: \n");
        scanf("%d",&n);
        if(n == tablep->bill_no)
        {
            printf("Successful login!\n");
            cust(menup,tablep);
        }
        else
        {
            printf("please enter correct bill number. If lost, contact manager\n");
        }
    }
    printf("Too many incorrect attempts. Logging out...\n");
    Sleep(2000);
    login(menup,tablep-((tablep->table_no)-1));
}

void checkout(struct bill* menup,struct bill* tablep)
{
    char yesno;
    printf("\nWould you like to pay now? (y/n) ");
    scanf("\n%c",&yesno);
    if(yesno == 'n')
    {
        printf("Going back to menu...\n");
        Sleep(1000);
        cust(menup,tablep);
    }
    else if(yesno == 'y')
    {
        printf("Thank you for eating at our restaurant");
        Sleep(2000);
        tablep->status = 0;
        login(menup,tablep-((tablep->table_no)-1));
    }
    
}

void edit_menu(struct bill* menup, struct bill* tablep)
{
    int n,i,j;
    system("cls");
    display_menu(menup);
    printf("\nPlease select action to be performed:\n");
    printf("1. Edit menu\n");
    printf("2. Save changes to menu\n");
    printf("3. Exit\n");
    

    while(1)
    {
        scanf("%d",&n);
        switch(n)
        {
            case 1: system("menu.txt");
            break;
        
            case 2: create_menu(menup,tablep);
            break;

            case 3: admin(menup,tablep);
            break;

            default: printf("Invalid input");
            Sleep(2000);
            edit_menu(menup,tablep);
            break;
        }
    }
}
