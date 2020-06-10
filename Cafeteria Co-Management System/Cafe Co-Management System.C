/*
THIS IS THE CAFETERIA CO-MANAGEMENT PROGRAM , WHICH IS PASSWORD PROTECTED AND HAS HIERARCHAL AND PARALLEL ACCESS OF INFORMATION
AND ARCHIVAL OF DATA IS ALSO MADE.
THIS HAS FOUR MAIN MODULES NAMELY
1.OWNER
2.MANAGER
3.BILLING
4.KITCHEN

AUTHORS:
A . KIRTHIC VISHNU(19Z301)
BHARATH . S(19Z308)
MAHESH BOOPATHY . M(19Z330)
SURTIK . S(19Z351)
TARUN VISVA . R (19Z358)
*/

//HEADER FILES

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#include<windows.h>
#include<time.h>


//GLOBAL VARIABLE DECLARATION AND INITIALIZATION

int total_sales=0;
int total_profit=0;
COORD coord= {0,0}; // In here , the numbers within the braces denote x and y co-ordinate of output screen respectively.

//STRUCTURE DEFENITION


struct emp_login    //This is the employee login structure and holds various details of the employee and also their login details
{
  char username[30];
  char password[30];
  char name[50];
  int empid;
  long int salary;
  char job_title_name[20];
  int job_title;
};
struct item        //This is the item structure where details of various items being sold in the cafe are written.
{
int item_id;//Every item holds a unique,sequential , system - assigned id for easy and fast access
int price;
int profit;
char item_name[50];
int noofitems;//This variable stores the number of items produced by the kitchen
};
struct propri//This structure is used to record sales data of a particular date
{
    int price;
    int profit;
};
/*

FUNCTION DECLARATIONS

*/

//DISPLAY EDITORS
void gotoxy(int x,int y);
void clrscr();
void delay(int ms);

//FUNCTIONS OPEREATING ON EMPLOYEE-LOGIN STRUCTURE
void create_emp_details();
struct emp_login readempdat(int emp_id,int job_title);
void edit_emp_details(int emp_id,int job_title) ;
void remove_employee_dat(int emp_id);
int emp_red_chk(int emp_id);//Checks if the entered emp_id is redundant or not
void readallemp();//This function reads and displays details of all employees
int read_login_details(char username[], char password[]);
int seeklocemp(int emp_id);

//FUNCTIONS OPERATING ON ITEM STRUCRURE
void itemwrite();
void readall();
struct item itemread(int id,int job_title);
void edit_item(int item_id);

//FUNCTIONS OPERATING ON STRUCTURE PROPRI
void getpropri(int job_title);
void putpropri();

//FUNCTION WHICH DISPLAYS LOGIN SCREEN
//REDIRECTS USER TO REQUIRED MODULE
void login_screen();

//OWNER MODULE
void owner();

//MANAGER MODULE
void manager();

//BILLING MODULE
void billing();
void bill();
void dbill();

//KITCHEN MODULE
void kitchen();
void kitchen_quantity_update(int item_id);


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
int main()
{

	clrscr();
	login_screen();
	clrscr();
	getch();
	return 0;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


//---------------------------------------------------------------------------------------------------------------------------------------------------------------

//DISPLAY EDITORS
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void clrscr()
{
    system("cls");
}
void delay(int ms)
{
    clock_t start_time =clock();
    while(clock()<start_time+ms);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------


//FUNCTIONS OPEREATING ON EMPLOYEE-LOGIN STRUCTURE
void create_emp_details()
{

	struct emp_login create;
	char ch='y';
	FILE *fptr;

	clrscr();

	while(ch=='y')
	{
	   clrscr();
	   gotoxy(24,1);
	   printf("EMPLOYEE DETAIL ENTRY");
	   printf("\n");
	   printf("\nEnter employee details : ");
	   printf("\n\nEnter employee id : ");
	   scanf("%d",&create.empid);
	   if(emp_red_chk(create.empid)>=1)
	   {
		printf("\nEntered Emp id already exists . Try again");
		getch();
		continue;
	   }
	   fptr=fopen("emp.bin","ab");
	   printf("\nEnter name : ");
	   scanf("     %[^\n]",&create.name);
	   printf("\nJob title :\n1 for owner \n2 for manager\n3 for billing \n4 for chef ");
	   printf("\nEnter the correcponding job title number : ");
	   scanf("%d",&create.job_title);
	   printf("\nEnter Salary : ");
	   scanf("%ld",&create.salary);
	   switch(create.job_title)
	   {
	      case 1:
	      {
		 strcpy(create.job_title_name,"Owner");
		 break;
	      }
	      case 2:
	      {
		 strcpy(create.job_title_name,"Manager");
		 break;
	      }
	      case 3:
	      {
		strcpy(create.job_title_name,"Billing");
		break;
	      }
	      case 4:
	      {
		strcpy(create.job_title_name,"Chef");
		break;
	      }
	      default:
	      {
		strcpy(create.job_title_name,"Billing");
		create.job_title=3;
		break;
	      }
	   }
	   printf("\nUsername : ");
	   scanf(" %[^\n]",&create.username);
	   printf("\nPassword(no space allowed) : " );
	   scanf("  %s",&create.password);
	   fwrite(&create,sizeof(struct emp_login),1,fptr);
	   fclose(fptr);
	   printf("Do you want to create another login (y/n) : ");
	   scanf(" %c",&ch);
	   if(ch=='y'||ch=='n'){}
	   else
	   {
		printf("\nWrong charecter... aborting...");
		ch='n';
	   }
	}
}

struct emp_login readempdat(int emp_id,int job_title)
{
	int n;
	struct emp_login emp;
	FILE *fptr;
	fptr=fopen("emp.bin","rb");
	if(fptr==NULL)
	{
		printf("Error in opening file\n");
	}
	else
	{
		while((fread(&emp,sizeof(struct emp_login),1,fptr)!=0))
		{
		   if(emp_id==emp.empid)
		   {
		     if(job_title==1&&emp.job_title==1)
		     {
		     printf("\nName : %s \nEmp id : %d \nSalary : %ld\nJob title : %s",emp.name,emp.empid,emp.salary,emp.job_title_name);
		     }
		     else if(job_title!=1&&emp.job_title==1)
		     {
		     printf("\nYou dont have authourization to access this information");
		     break;
		     }
		     else
		     {
		     printf("\nName : %s \nEmp id : %d \nSalary : %ld\nJob title : %s",emp.name,emp.empid,emp.salary,emp.job_title_name);
		     }
		     break;
		   }
		}
	}
	getch();
	fclose(fptr);
	return emp;
}

void edit_emp_details(int emp_id,int job_title)
{
	int flag=0,pos;
	struct emp_login edit;
	FILE *fptr;
	fptr=fopen("emp.bin","r+b");
	clrscr();
	if(fptr==NULL)
	{
		printf("\nError in opening file");
	}
	else
	{
		   int choice;
		   clrscr();
		   gotoxy(24,1);
		   printf("EDIT EMPLOYEE DETAIL");
		   printf("\n");
		   printf("\nDetails of employee whose data is to be edited : ");
		   fclose(fptr);

		   edit=readempdat(emp_id,1);
		   fptr=fopen("emp.bin","r+b");
		   if(edit.job_title==1&&job_title!=1)
		   {
		   printf("\n\nYou dont have authorization to edit that information ... Redirecting ...");
		   }
		   else
		   {
		   getch();
		   clrscr();
		   gotoxy(24,1);
		   printf("EDIT EMPLOYEE DETAIL");
		   printf("\n\n1.Name\n2.Job Title\n3.Salary\n4.Username\n5.Password");
		   printf("\nEnter yout choice : ");
		   scanf("%d",&choice);
		   switch(choice)
		   {
		   case 1:
		   {
		   printf("\n\nEnter new name : ");
		   scanf("     %[^\n]",&edit.name);
		   break;
		   }
		   case 2:
		   {
		   printf("\nJob title :\n1 for owner \n2 for manager\n3 for billing \n4 for chef ");
		   printf("\nEnter the correcponding job title number : ");
		   scanf("%d",&edit.job_title);
		   while(edit.job_title==1&&job_title!=1)
		   {
			printf("\nYou dont have authorization to enter Job title as Owner");
			printf("\nJob title :\n1 for owner \n2 for manager\n3 for billing \n4 for chef ");
			printf("\nEnter the correcponding job title number : ");
			scanf("%d",&edit.job_title);

		   }
		   break;
		   }
		   case 3:
		   {
		   printf("\nEnter new Salary : ");
		   scanf("%ld",&edit.salary);
		   break;
		   }

		   case 4:
		   {
		   printf("\nEnter new Username : ");
		   scanf(" %[^\n]",&edit.username);
		   break;
		   }
		   case 5:
		   {
		   printf("\nEnter new Password(no space allowed) : " );
		   scanf("  %s",&edit.password);
		   break;
		   }
		   default :
		   {
		   flag=1;
		   break;
		   }
		   }
		   if (flag==0)
		   {
		   switch(edit.job_title)
		   {
		      case 1:
		      {
			 strcpy(edit.job_title_name,"Owner");
			 break;
		      }
		      case 2:
		      {
			 strcpy(edit.job_title_name,"Manager");
			 break;
		      }
		      case 3:
		      {
			strcpy(edit.job_title_name,"Billing");
			break;
		      }
		      case 4:
		      {
			strcpy(edit.job_title_name,"Chef");
			break;
		      }
		      default:
		      {
			strcpy(edit.job_title_name,"Billing");
			edit.job_title=3;
			break;
		      }
		   }
		   pos=seeklocemp(emp_id);

		   fseek(fptr,sizeof(struct emp_login)*(pos),SEEK_SET);
		   fwrite(&edit,sizeof(struct emp_login),1,fptr);
		   printf("\n\nEDITED SUCCESSFULLY");
		}
		fclose(fptr);
	}           }
}

void remove_employee_dat(int emp_id)
{
	struct emp_login old_dat,new_dat;
	FILE *fin,*fout;
	fin=fopen("emp.bin","rb");
	fout=fopen("temp.bin","wb");
	while((fread(&old_dat,sizeof(struct emp_login),1,fin)!=0))
	{

	   if(emp_id==old_dat.empid)
	   {
	   printf("\nData deleted successfully");
	   continue;
	   }
	   else
	   {
	   new_dat=old_dat;
	   fwrite(&new_dat,sizeof(struct emp_login),1,fout);
	   }
	}
	fclose(fin);
	fclose(fout);
	remove("emp.bin");
	rename("temp.bin","emp.bin");


}

int emp_red_chk(int emp_id)
{
	int count=0;
	struct emp_login emp;
	FILE *fptr;
	fptr=fopen("emp.bin","rb");
	if(fptr==NULL)
	{

	}
	else
	{
		while((fread(&emp,sizeof(struct emp_login),1,fptr)!=0))
		{
		   if(emp_id==emp.empid)
		   {
			count++;
		   }
		}
	}
	fclose(fptr);
	//printf("\nCOUNT : %d",count);
	return count;
}

void readallemp()
{
	int n;
	struct emp_login emp;
	FILE *fptr;
	fptr=fopen("emp.bin","rb");
	if(fptr==NULL)
	{
		printf("Error in opening file\n");
	}
	else
	{
		while((fread(&emp,sizeof(struct emp_login),1,fptr)!=0))
		{

		     printf("\nName : %s \nEmp id : %d \nSalary : %ld\nJob title : %s\nUsername : %s\nPassword : %s",emp.name,emp.empid,emp.salary,emp.job_title_name,emp.username,emp.password);
		     getch();
		}
	}
	fclose(fptr);

}

int read_login_details(char username[], char password[])
{
	struct emp_login datread;
	FILE *fp;
	int flag=0;
	fp=fopen("emp.bin","rb");


	clrscr();
	if(fp!=NULL)
	{
	{
	while((fread(&datread,sizeof(struct emp_login),1,fp)==1))
	{

        clrscr();

	    if(strcmp(username,datread.username)==0)
	    {
		if(strcmp(password,datread.password)==0)
		{
			printf("\nLogin data accepted ... Welcome");
			delay(2500);
			flag=1;
			return datread.job_title;

		}

	    }


	}
	if(flag==0)
	{
	   printf("\nError ... Username not found");
	   delay(2500);
		return 0;
	}
	}
	}
	else
	{
	  printf("\nError ... cannot open file ...");
	  return 0;
	}
	return 0;
}

int seeklocemp(int emp_id)
{
	int n;
	struct emp_login emp;
	FILE *fptr;
	fptr=fopen("emp.bin","rb");
	if(fptr==NULL)
	{
		printf("Error in opening file\n");
	}
	else
	{
		while((fread(&emp,sizeof(struct emp_login),1,fptr)!=0))
		{
		   if(emp_id==emp.empid)
		   {
		      return ((ftell(fptr)/sizeof(struct emp_login))-1);
		   }
		}
	}
	fclose(fptr);
	return NULL;

}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

//FUNCTIONS OPERATING ON ITEM STRUCRURE
void itemwrite()
{
	FILE *f;
	int i=1,size;
	char ch='y';
	clrscr();
	gotoxy(33,1);
	printf("Item Entry");

	f=fopen("cafe.bin","ab");
	fseek(f,0,SEEK_END);
	i=1+(ftell(f)/sizeof(struct item));
	while(f!=NULL&&ch=='y')
	{
		struct item comodity;
		clrscr();
		gotoxy(33,1);
		printf("Item Entry");
		printf("\n\nItem ID:%d",i);
		comodity.item_id=i;
		printf("\nEnter the Item name:");
		scanf("  %[^\n]",&comodity.item_name);

		printf("\nEnter item price:");
		scanf("%d",&comodity.price);
		printf("\nEnter net profit from item(single piece):");
		scanf("%d",&comodity.profit);
		comodity.noofitems=0;
		fwrite(&comodity,sizeof(struct item),1,f);
		if(fwrite!=0)
		{
			i++;
			gotoxy(33,20);
			printf("ENTRY SUCCESSFUL");
			printf("\n\nDo you want to add more(y/n) : ");
			scanf("    %c",&ch);
		}

	}
	if(f==NULL)
	{
		printf("\nFILE DOES NOT EXIST//ERROR TRY AGAIN");
	}
	fclose(f);
}
void readall()
{
	struct item icom;
	FILE *fp;
	int i=0;

	fp=fopen("cafe.bin","rb");
	while(fread(&icom,sizeof(struct item),1,fp)==1)
	{

	    printf("\n%d",i);i++;
	    printf("Item name:%s \n",icom.item_name);
	    printf("Item Id:%d\n",icom.item_id);
	    printf("Number produced:%d\n",icom.noofitems);
	    printf("Item price:%d\n",icom.price);
	    printf("Item profit:%d\n\n",icom.profit);
	    getch();
	    }

    fclose(fp);
}
struct item itemread(int id,int job_title)
{

	struct item icom;
	FILE *fp;
	int flag = 0;
	clrscr();
	fp=fopen("cafe.bin","rb");
	if(fp!=NULL)
	{

	{
	while(fread(&icom,sizeof(struct item),1,fp)==1)
	{

	    if(id==icom.item_id)
	    {
	    printf("\n");
	    printf("Item name:%s \n",icom.item_name);
	    printf("Item Id:%d\n",icom.item_id);
	    printf("Number produced:%d\n",icom.noofitems);
	    printf("Item price:%d\n",icom.price);
	    if(job_title==1)
	    printf("Item profit:%d\n\n",icom.profit);
	    getch();
	    flag=1;
	    break;
	    }


	}
	if (flag==0)
	    {
	    strcpy(icom.item_name,"noexist");
	    printf("\nItem with id %d doesnt exist",id);
	    }
	}
	fclose(fp);
	}
	else
    {

	printf("\t\tERROR//FILE DOES NOT EXIST");
    }
    return (icom);

}

void edit_item(int item_id)
{
	int ch;
	struct item edit;
	FILE *fp;

	fp=fopen("cafe.bin","r+b");
	if(fp!=NULL)
	{
	fseek(fp,sizeof(struct item)*(item_id-1),SEEK_SET);

	printf("\nDetails of the item you want to edit : ");
	edit=itemread(item_id,1);
	if(strcmp(edit.item_name,"noexist")==0)
	{
	getch();
	return;
	}
	printf("\n\n1.Item name\n2.Item price\n3.Item profit");
	printf("\nEnter the choice (1/2/3) : ");
	scanf("%d",&ch);
	switch(ch)
	{
	  case 1:
	  {
		printf("\nEnter the new name of item : ");
		scanf("  %[^\n]",&edit.item_name);
		fwrite(&edit,sizeof(struct item),1,fp);
		break;
	  }
	  case 2:
	  {
		printf("\nEnter the new price of item : ");
		scanf("%d",&edit.price);
		fwrite(&edit,sizeof(struct item),1,fp);
		break;

	  }
	  case 3:
	  {
		printf("\nEnter the new profit of item : ");
		scanf("%d",&edit.profit);
		fwrite(&edit,sizeof(struct item),1,fp);
		break;
	  }

	  default:
	  {
		printf("\nWrong choice ... Redirecting ...");
		break;
	  }
	}
	}
	fclose(fp);
	if(ch<4)
	printf("\nSUCCESSFULLY EDITED") ;
	getch();

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

//FUNCTIONS OPERATING ON STRUCTURE DATE
void getpropri(int job_title)
{
        char day[4],month[4],year[5];
        char name[20]="dat";
        struct propri pp;
        clrscr();
        gotoxy(25,1);
        printf("GET SALES DATA");
        printf("\nEnter date of which you want to get total sales details of : ");
        printf("\nEnter month (MMM): ");
        scanf("  %s",month);

        printf("\nEnter day (dd): ");
        scanf("  %s",day);

        printf("\nEnter year (yyyy):");
        scanf("  %s",year);
        strcpy(month,strlwr(month));
        month[0]-=32;
        strcat(month," ");
        strcat(name,month);
         strcat(day," ");
        strcat(name,day);

        strcat(name,year);
        strcat(name,".bin");
        FILE *fp;
        fp=fopen(name,"rb");
        if(fp==NULL)
        {
            printf("\nFILE DOESNT EXIST");
            return;
        }
        else
        {
            fread(&pp,sizeof(struct propri),1,fp);
            if(job_title==1)
            {
                printf("\nTotal profit on that date = %d",pp.profit);
            }
            printf("\nTotal sales on that date = %d",pp.price);

        }
        fclose(fp);
}
void putpropri()
{
    struct propri pp;
    char name[20]="dat";
    strcat(name,__DATE__);
    strcat(name,".bin");
    FILE *fp;
    fp=fopen(name,"r+b");
    if(fp==NULL)
    {
        fclose(fp);
        fp=fopen(name,"wb");
        pp.price=0;
        pp.profit=0;
    }
    else
    {
        fread(&pp,sizeof(struct propri),1,fp);
    }
    pp.profit+=total_profit;
    pp.price+=total_sales;
    fseek(fp,0,SEEK_SET);
    fwrite(&pp,1,sizeof(struct propri),fp);
    fclose(fp);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//FUNCTION WHICH DISPLAYS LOGIN SCREEN
//REDIRECTS USER TO REQUIRED MODULE
void login_screen()
{
	int retval=0;
	char username[30],password[30];
	clrscr();
	gotoxy(1,25);
	printf("Enter username as exit and password as exit to exit the application");
	gotoxy(21,1);
	printf("Welcome to Cafeteria Management System");
	printf("\n\nUsername : ");
	scanf("  %[^\n]",username);
	printf("\nPassword : ");
	scanf("     %s",password);
	if(strcmpi(username,"exit")==0&&strcmpi(password,"exit")==0)
	{
		printf("\n\n\n\nThank you for using this application ... \n\nPress any key to exit...");
		getch();
		exit(1);
	}

	while(retval==0)
	{

		retval = read_login_details(username , password);
		clrscr();
		if (retval==1)
		{
			printf("Welcome Owner ... Transferring to owner section");
			delay(1000);
			owner();
			break;
		}
		else if (retval==2)
		{
			printf("Welcome manager ... Transferring to manager section");
			delay(1000);
			manager();
			break;
		}
		else if(retval==3)
		{
			printf("Welcome employee ... Transferring to billing section");
			delay(1000);
			billing();
			break;
		}
		else if (retval==4)
		{
			printf("Welcome employee ... Transferring to kitchen section");
			delay(1000);
			kitchen();
			break;
		}
		else if(retval==0)
		{
			clrscr();
			printf("Oops... seems you have entered something wrong ... \n\nRedirecting to login screen...");
			delay(2000);
			clrscr();
			gotoxy(1,25);
			printf("Enter username as exit and password as exit to exit the application");
			gotoxy(21,1);
			printf("Welcome to Cafeteria Management System");
			printf("\n\nUsername : ");
			scanf("  %[^\n]",username);
			printf("\nPassword : ");
			scanf("    %s",password);
			if(strcmpi(username,"exit")==0&&strcmpi(password,"exit")==0)
			{
			  printf("\n\n\n\nThank you for using this application ... \n\nPress any key to exit...");
			  getch();
			  exit(1);
			}

		}

	}

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

//OWNER MODULE
void owner()
{
	int ch=1;
	clrscr();
	while(ch<11)
	{
	clrscr();
	gotoxy(25,1);
	printf("OWNER SCREEN") ;
	printf("\n1.Add employee details");
	printf("\n2.Edit employee details") ;
	printf("\n3.Read employee details");
	printf("\n4.Remove employee details");
	printf("\n5.Add item data");
	printf("\n6.Edit item data");
	printf("\n7.Read item data ");
	printf("\n8.See total sales of current session");
	printf("\n9.See total profit of current session");
	printf("\n10.See sales data of a particular date");
	printf("\n11.Return to login screen");
	printf("\nEnter your choice : ");
	scanf("%d",&ch);
	switch(ch)
	{
	case 1:
	{
	create_emp_details();
	break;
	}
	case 2:
	{
	int emp_id;
	printf("\n\nEnter employee id of employee whose details you want to edit : ");
	scanf("%d",&emp_id);
	edit_emp_details(emp_id,1);
	getch();
	break;
	}
	case 3:
	{
	int emp_id;
	printf("\nEnter emploee id of employee whose details you want to read : ");
	scanf("%d",&emp_id);
	readempdat(emp_id,1);
	break;
	}

	case 4:
	{
	int id;
	char ch;
	printf("\nEnter id of employee whose data is to be removed : ");
	scanf("%d",&id);
	printf("\nDetails of employee whose data is to be removed : ");
	readempdat(id,1) ;
	printf("Proceed to remove data (y/n)?");
	scanf("%c",&ch);
	if(ch=='y')
	{
	remove_employee_dat(id);
	}
	break;
	}
	case 5:
	{
	itemwrite();
	break;
	}
	case 6:
	{
	int item_id;
	printf("\nEnter item id of item whose details you want to edit : ");
	scanf("%d",&item_id);
	edit_item(item_id);
	break;
	}
	case 7:
	{
	int item_id;
	struct item temp;
	printf("\nEnter item id of item whose details you want to see : ");
	scanf("%d",&item_id);
	temp=itemread(item_id,1);
	if(strcmp(temp.item_name,"noexist")==0)
    {
        printf("\nItem doesnt exist");
    }
	getch();
	break;
	}
	case 8:
	{
	printf("\nTotal sales for the session : %d",total_sales);
	getch();
	break;
	}
	case 9:
	{
	printf("\nTotal profit for the session : %d",total_profit);
	getch();
	break;
	}
	case 10:
    {
    getpropri(1);
    getch();
    break;
    }
	default:
	{
	login_screen();
	break;
	}
	}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void manager()
{
	int ch=1;
	clrscr();
	while(ch<7)
	{
    clrscr();
	gotoxy(25,1);
	printf("MANAGER SCREEN") ;
	printf("\n1.Edit employee details") ;
	printf("\n2.Read employee details");
	printf("\n3.Read item data ");
	printf("\n4.See total sales of current session");
	printf("\n5.See total sales of a particular date");
	printf("\n6.Return to login screen");
	printf("\nEnter your choice : ");
	scanf("%d",&ch);
	switch(ch)
	{
	case 1:
	{
	int emp_id;
	printf("\n\nEnter employee id of employee whose details you want to edit : ");
	scanf("%d",&emp_id);
	edit_emp_details(emp_id,2);
	getch();
	break;
	}
	case 2:
	{
	int emp_id;
	printf("\nEnter emploee id of employee whose details you want to read : ");
	scanf("%d",&emp_id);
	readempdat(emp_id,2);
	break;
	}
	case 3:
	{
	int item_id;
	struct item temp;
	printf("\nEnter item id of item whose details you want to see : ");
	scanf("%d",&item_id);
	temp=itemread(item_id,2);
	if(strcmp(temp.item_name,"noexist")==0)
    {
        printf("\nItem doesnt exist");
    }
	getch();
	break;

	}
	case 4:
	{
	printf("\nTotal sales for the session : %d",total_sales);
	getch();
	break;
	}
	case 5:
    {
    getpropri(2);
    getch();
    break;
    }
	default:
	{
	login_screen();
	break;
	}

	}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

//BILLING MODULE
void billing()
{
	int choice=1;
	while(choice==1)
	{
	clrscr();
	gotoxy(25,1);
	printf("Billing");
	printf("\n\n1.Calculate new bill");
	printf("\n2.Return to login screen");
	printf("\n\nEnter your choice : ");
	scanf("%d",&choice);
	if(choice==1)
	{
		bill();
	}
	else
	{
		login_screen();
		break;
	}
	}
}
void bill()
{
    int item_id;
    char ch;
    int j=13,quantity=0,size=0,i=1;
    int total=0,gtotal=0,profit=0,gprofit=0;
    struct item items;
    FILE *file;
    file=fopen("cafe.bin","r+b");
    rewind(file);
    clrscr();
    dbill();
    gotoxy(26,10);
    printf("Enter  \"0\" to finish input");
    while(1)
    {
	gotoxy(25,3);
	printf("                    ");
	gotoxy(25,4);
	printf("                    ");
	gotoxy(1,6);
	printf("                                                                               ");
	gotoxy(25,3);
	printf("Enter Item ID:");
	scanf("%d",&item_id);
	if(item_id==0)
	{
	    break;
	}
	gotoxy(25,4);
	printf("Enter Quantity:");
	scanf("%d",&quantity);
	rewind(file);
	while(fread(&items,sizeof(struct item),1,file))
	{

	    if(items.item_id==item_id)
	    {
		if(items.noofitems==0)
		{
		gotoxy(1,6);
		printf("Sorry , item not available");
		getch();
		continue;
		}
		else if(quantity>items.noofitems)
		{
		gotoxy(1,6);
		printf("Sorry,only %d number of those items available.To add enter 'y' ",items.noofitems);
		scanf("       %c",&ch);
		if(ch=='y')
		{
		quantity=items.noofitems;
		items.noofitems=0;
		}
		else
		{
		continue;
		}
		}
		else
		{
		items.noofitems=items.noofitems-quantity;
		}
		total=items.price*quantity;
		profit=items.profit*quantity;
		gotoxy(4,j);
		printf("%d",i);
		gotoxy(7,j);
		printf("    %s",items.item_name);
		gotoxy(39,j);
		printf("%d",quantity);
		gotoxy(51,j);
		printf("%d",items.price);
		gotoxy(65,j);
		printf("%d",total);
		gtotal=gtotal+total;
		gprofit+=profit;
		size=sizeof(struct item);

		j++;
		i++;
		fseek(file,-size,SEEK_CUR);
		fwrite(&items,sizeof(struct item),1,file);
		break;
	    }
	}
    }
    if(gtotal!=0)
    {
	gotoxy(26,10);
	printf("TOTAL AMOUNT = NRs. %6d",gtotal);
	total_sales+=gtotal;
	total_profit+=gprofit;
	putpropri();
    }
    fclose(file);
    getch();
}

void dbill()
{
    int i;
    gotoxy(32,1);
    printf("CUSTOMER'S BILL") ;

    gotoxy(4,12);
    printf("SN.         Item Name           Quantity      Rate          Total");

}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//KITCHEN MODULE
void kitchen()
{
	int ch,item_id;
	clrscr();
	gotoxy(37,1);
	printf("KITCHEN");
	printf("\n\n1.Update quantity produced for the day");
	printf("\n2.Return to login screen");
	printf("\n\nEnter your choice : ");
	scanf("%d",&ch);
	while(ch==1)
	{
		clrscr();
		gotoxy(25,1);
		printf("Quantity updation") ;
		printf("\n\nEnter item id of product whose quantity is to be updated : ");
		scanf("%d",&item_id);
		kitchen_quantity_update(item_id);
		printf("\nPress any key to go back to kitchen menu : ");
		getch();
		clrscr();
		gotoxy(37,1);
		printf("KITCHEN");
		printf("\n\n1.Update quantity produced for the day");
		printf("\n2.Return to login screen");
		printf("\n\nEnter your choice : ");
		scanf("%d",&ch);
	}
	if(ch!=1)
	{
		printf("\n\nReturning to login screen ...");
		delay(100);
		login_screen();
	}
}

void kitchen_quantity_update(int item_id)
{
	struct item updt;
	FILE *fp;
	fp=fopen("cafe.bin","r+b");
	if(fp!=NULL)
	{
		printf("\nDetails of item whose quantity is to be updated : ");
		updt=itemread(item_id,4);
		if(strcmp(updt.item_name,"noexist")==0)
		{
            printf("\nItem with id %d doesnt exist",item_id);
		}
		else
        {
		printf("\n\nEnter new quantity : ");
		scanf("%d",&updt.noofitems);
		fseek(fp,sizeof(struct item)*(item_id-1),SEEK_SET);
		fwrite(&updt,sizeof(struct item),1,fp);
		printf("\n\nSUCCESSFULLLY UPDATED");
        }
	}
	fclose(fp);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

