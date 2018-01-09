 #include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NAMELEN 10  //Students' names are no longer than 10 chars
#define COURSES 4   //There are four courses in the system

typedef struct stu_info
{
	char stu_name[NAMELEN];
	int id,score[COURSES];
	float avgScore;
	struct stu_info *next;
}STU_INFO;
typedef struct stu_info STU;
typedef struct stu_info *STUPTR;
STUPTR lastptr=NULL, currentptr=NULL;

float average(int a[],int);									//Functions prototype
int menu();
void detelestu(STUPTR *sptr);
void showlist(STUPTR currentptr);
void assign(STUPTR *sptr,char name[], int, int cour[], float);
void assignsort(STUPTR *sptr,char name[], int, int cour[], float);
void search(STUPTR *sptr);
void analyse(STUPTR *sptr);

int main()
{
	char operater[2], mode[2];
	char name[NAMELEN];
	float aver;
	int cour[COURSES], ident=-1, mod=0;
	int Bo[4]={88,30,78,77};				//Prepare for initialzing the list
	int Al[4]={90,80,88,70};
	int Ca[4]={90,95,90,100};
	int Ge[4]={100,98,100,100};
	int Da[4]={59,59,59,59}; 
	STUPTR headptr=NULL;
	
	printf("Please choose a mode.\n1.default.\n2.sorted.\nYour choice:");
	while(mod==0)							//Program protection.In case user enter a char. 
	{
		scanf("%s",&mode);
		if(mode[0]<'3'&&mode[0]>'0')
		{
			if(mode[0]=='1')
				mod=1;
			else
				mod=2;
			
			if(mod==1)					//Initialize the list in default mode
			{
				assign(&headptr,"Alice",1,Al,average(Al,COURSES));
				assign(&headptr,"Bob"  ,2,Bo,average(Bo,COURSES));
				assign(&headptr,"Carol",3,Ca,average(Ca,COURSES));
				assign(&headptr,"Geek" ,4,Ge,average(Ge,COURSES));
				assign(&headptr,"Dave" ,5,Da,average(Da,COURSES));
			}
			else						//Initialize the list in sorted mode
			{	
				assignsort(&headptr,"Alice",1,Al,average(Al,COURSES));
				assignsort(&headptr,"Bob"  ,2,Bo,average(Bo,COURSES));
				assignsort(&headptr,"Carol",3,Ca,average(Ca,COURSES));
				assignsort(&headptr,"Geek" ,4,Ge,average(Ge,COURSES));
				assignsort(&headptr,"Dave" ,5,Da,average(Da,COURSES));				
			}
			system("cls");
				
			menu();
		
			while(operater[0]!='6')			//Program protection.In case user enter a char.
			{
				scanf("%s",&operater);
				if(operater[0]<'0'||operater[0]>'6')                                  
					printf("You have entered a wrong number,please try again.\n");
				else
				{
			
					switch(operater[0])
					{
						case '1':
							showlist(headptr);
							printf("Press any key to continue.");
							getch();
							system("cls");
							menu();
							break;
						case '2':
							printf("\nID of the new student:\n");
							scanf("%d",&ident);
							
							printf("Name of the new student:\n");
							scanf("%s",&name); 
							if(ident==-1)		//Program protection.Prevent user input a char in ID
							{
								system("cls");
								printf("You have not entered a number in ID.Inserting fail.\n");
								printf("Press any key to continue.");
								getch();
								system("cls");
								menu();
								break;
							}
							printf("Please input the score of C01:\n");
							scanf("%d",&cour[0]);
							printf("Please input the score of C02:\n");
							scanf("%d",&cour[1]);
							printf("Please input the score of C03:\n");
							scanf("%d",&cour[2]);
							printf("Please input the score of C04:\n");
							scanf("%d",&cour[3]);
							if(mod==1)
								assign(&headptr,name,ident,cour,average(cour,COURSES));								
							else								
								assignsort(&headptr,name,ident,cour,average(cour,COURSES)); 							
							printf("Press any key to continue.");
							getch();
							system("cls");
							menu();
							break;
						case '3':
							deletestu(&headptr);
							printf("Press any key to continue.");
							getch();
							system("cls");
							menu();
							break;
						case '4':
							search(&headptr);
							printf("Press any key to continue.");
							getch();
							system("cls");
							menu();
							break; 
						case '5':
							analyse(&headptr);
							printf("Press any key to continue.");
							getch();
							system("cls");
							menu();
							break;	
						}	
					}
			}
			
			printf("Thank you for using!\n");
			
			system("pause"); 
			return 0;
		}
		else		
			printf("You entered a wrong number.Please try again.\n");	
	}
}

void showlist(STUPTR currentptr)
{
	//Program protection.Prevent progran from outputting messy information when there is no student
	if(currentptr==NULL)			
		printf("There is no student.\n");
	else
	{
		printf("**********************List Info**********************\n");
		printf("ID     ");
		printf("Name      ");
		printf("C01     C02     C03     C04     Avg\n");
		while(currentptr!=NULL)
		{
			printf("%-2d     ",currentptr->id);
			printf("%-10s",currentptr->stu_name);
			printf("%-3d     %-3d     ",currentptr->score[0],currentptr->score[1]);
			printf("%-3d     %-3d     ",currentptr->score[2],currentptr->score[3]);
			printf("%.1f\n",currentptr->avgScore);
			currentptr=currentptr->next;
		}
		printf("******************************************************\n");
	}
}
//Insert a student in default mode
void assign(STUPTR *sptr,char name[], int iden, int cour[], float avg)
{
	int i;
	float aver;
		
	currentptr=*sptr;
	while(currentptr!=NULL&&iden!=currentptr->id)
		currentptr=currentptr->next;
		
	if(currentptr==NULL)						//Prevent user use a ID which already exists.
	{
		currentptr=(STUPTR)malloc(sizeof(STU));
		if(currentptr!=NULL)
		{
			currentptr->id=iden;
			strcpy(currentptr->stu_name,name);
			for(i=0;i<NAMELEN;i++)
				currentptr->score[i]=cour[i];
			currentptr->avgScore=average(cour, COURSES);
			currentptr->next=NULL;
			if(*sptr==NULL)						//New student is the first student
			{
				*sptr=currentptr;
				lastptr=currentptr;
			}
			else								//New student is behind other student.
			{
				lastptr->next=currentptr;
				lastptr=currentptr;
			}
		}
	}
	else
		printf("This ID already exists.Inserting fail.\n");	
}
//Insert a student in sorted mode
void assignsort(STUPTR *sptr,char name[], int iden, int cour[], float avg)
{
	int i;
	STUPTR nowptr, previousptr=NULL;
	nowptr=(STUPTR)malloc(sizeof(STU));
	currentptr=*sptr;
	while(currentptr!=NULL&&iden!=currentptr->id)
	currentptr=currentptr->next;
	
	if(currentptr==NULL)					//Prevent user use a ID which already exists.
	{
		currentptr=*sptr;
		nowptr->id=iden;
		strcpy(nowptr->stu_name,name);
		for(i=0;i<NAMELEN;i++)
			nowptr->score[i]=cour[i];
		nowptr->avgScore=avg;	
		
		while(currentptr!=NULL&&avg<=currentptr->avgScore)		//Looking for location
		{
			previousptr=currentptr;
			currentptr=currentptr->next;
		}
		if(previousptr==NULL)				//New student's location is head pointer
		{
			nowptr->next=currentptr;
			*sptr=nowptr;
		}		
		else if(currentptr==NULL)			//New student's location is end pointer
		{
			previousptr->next=nowptr;
			nowptr->next=NULL;
		}
		else								//New student's location is middle pointer
		{
			previousptr->next=nowptr;
			nowptr->next=currentptr;
		}
	}
	else
		printf("This ID already exists.\n");
}

void deletestu(STUPTR *sptr)
{
	STUPTR previousptr=NULL;
	int ident;
	
	printf("Please enter the ID of the student to delete:\nID=");
	currentptr=*sptr;
	scanf("%d",&ident);
	//Program protection.Prevent user from entering a ID which doesn't exist.
	while(currentptr!=NULL&&currentptr->id!=ident)	  
	{
		previousptr=currentptr;
		currentptr=currentptr->next;
	}	
	if(currentptr!=NULL)
	{
		if(previousptr==NULL)			//deleted student is the first student
			*sptr=currentptr->next;
		else
			previousptr->next=currentptr->next;
			
		free(currentptr);
		printf("Delete operation complete.\n");
	}
	else
		printf("The ID doesn't exist.\n");
		
}

void search(STUPTR *sptr)
{
	char name[NAMELEN]; 

	currentptr=*sptr;
	printf("Please enter the name of the student to search:\nName:");
	scanf("%s",&name);
	while(currentptr!=NULL&&strcmp(currentptr->stu_name,name)!=0)
		currentptr=currentptr->next;
		
	if(currentptr!=NULL)
	{
		printf("ID     ");
		printf("Name      ");
		printf("C01     C02     C03     C04     Avg\n");
		printf("%-2d     ",currentptr->id);
		printf("%-10s",currentptr->stu_name);
		printf("%-3d     %-3d     ",currentptr->score[0],currentptr->score[1]);
		printf("%-3d     %-3d     %.1f\n",currentptr->score[2],currentptr->score[3],currentptr->avgScore);
	}
	else
		printf("Student <%s> not found.\n",name);
}

void analyse(STUPTR *sptr)
{
	int c, people=0, i=0;
	int min, max;
	float pass;
	//Program protection.Preventing progran from outputting messy information when there is no student
	if(*sptr==NULL)						
		printf("There is no student.\n");
	else
	{
		printf("Please input the course ID you want to analyze:\n");
		scanf("%d",&c);
		if(c<5&&c>0)
		{
			currentptr=*sptr;
			
			while(currentptr!=NULL)					//Calculate number of students
			{
				people++;
				currentptr=currentptr->next;
			}
	
			int cour[people];
			currentptr=*sptr;
			while(currentptr!=NULL)					//Assign all of students' scores to a array
			{
				cour[i]=currentptr->score[c-1];
				currentptr=currentptr->next;
				i++;
			}
			max=cour[0];
			min=cour[0];
			
			for(i=0;i<people;i++)
			{
				if(max<cour[i])
					max=cour[i];
				if(min>cour[i])
					min=cour[i];
				if(cour[i]>=60)
					pass++;	
			}
			printf("Course Info of C0%d:\n",c);
			printf("Max=%.1f\n",(float)max);
			printf("Min=%.1f\n",(float)min);
			printf("Avg=%.1f\n",average(cour,people));
			printf("PasssingRate=%.2f\n",pass/people);
		}
		else
			printf("The ID of the course doesn't exist.\n");
	}
}

int menu()
{
	int i;
	
	printf("\n");
	for(i=0;i<15;i++)
		printf("*");
	printf("Main Menu");
	for(i=0;i<15;i++)
		printf("*");
	printf("\n");
	for(i=0;i<10;i++)
		printf(" ");	
	printf("1. Show Current List\n");	
	for(i=0;i<10;i++)
		printf(" ");	
	printf("2. Insert Student\n");
	for(i=0;i<10;i++)
		printf(" ");
	printf("3. Delete Student\n");
	for(i=0;i<10;i++)
		printf(" ");
	printf("4. Search Student\n");
	for(i=0;i<10;i++)
		printf(" ");
	printf("5. Analyze Course\n");
	for(i=0;i<10;i++)
		printf(" ");
	printf("6. Exit the program\n");
	for(i=0;i<39;i++)
		printf("*");
		printf("\nPlease choose a function:");
}

float average(int a[], int len)				//Calculate average
{
	int i, sum=0;
	float aver;
		
	for(i=0;i<len;i++)
		sum=sum+a[i];
	
	aver=(float)sum/(float)len;	
	return aver;
}
