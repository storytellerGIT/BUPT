/*���ƣ��ۺ��������ݹ���ϵͳ
  ������ڣ�2018��9��19��
  ���ߣ�֣�Ʒ����������������Ǭ��������ԣ
  ����ļ���client.txt admin.txt gym.txt order.txt�ĸ��ļ�Ӧ��������ͬһĿ¼��*/
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<math.h>
#define len 100

//����˿ͽṹ������
struct client
{
    char id[11];
    char name[len];
    char gender[len];
    int age;
    char tel[12];
    char password[len];
    char email[len];
    float account;
    char zone[len];
    int sign;
}client_info[len];


//�������Ա�ṹ������
struct admin
{
    char id[11];
    char gymnasium[len];
    char name[len];
    char gender[len];
    char email[len];
    char password[len];
    char tel[12];
}admin_info[len];

//���峡�ؽṹ������
struct gym
{
    char num[len];
    char zone[len];
    char belong_stadium[len];
    char type[len];
    char introdution[len];
    int permit_age[2];
    float rent;
}gym_info[len];

//���嶩���ṹ������
struct order
{
    char user_id[11];
    unsigned long long reserve_date;
    char gymnum[len];
    int rent_date;
    int begin_time;
    int over_time;
    int sign;
}order_info[len];

void initialize(int *p_client_num, int *p_admin_num, int *p_gym_num, int *p_order_num)     //�ĸ�����ָ��ֱ�����ĸ��ṹ�����Ч����
{
    int i;
    FILE *fp_client;             //�����ĸ��ṹ������Ӧ���ĸ�txt���ļ�ָ��
    FILE *fp_admin;
    FILE *fp_gym;
    FILE *fp_order;

    if((fp_client=fopen("client.txt", "rb"))==NULL)                 //�ж��ļ��Ƿ���Դ�
    {
        printf("Cannot open client file\n");
        exit(0);
        system("pause");
    }
    *p_client_num=0;
    for (i = 0; feof(fp_client)==0; i++)
    {
        fread(&client_info[i], sizeof(struct client), 1, fp_client);//���ļ��е����ݶ���ṹ��
        *p_client_num=*p_client_num+1;
    }
    *p_client_num=*p_client_num-1;      //����ѭ��������ָ����ֵ���һ����ͨ���Լ����ָ�����

    if((fp_admin=fopen("admin.txt", "rb"))==NULL)                   //�ж��ļ��Ƿ���Դ�
    {
        printf("Cannot open admin file\n");                         
        exit(0);
        system("pause");
    }
   *p_admin_num=0;
    for (i = 0; feof(fp_admin)==0; i++)
    {
        fread(&admin_info[i], sizeof(struct admin), 1, fp_admin);//���ļ��е����ݶ���ṹ��
        *p_admin_num=*p_admin_num+1;
    }
    *p_admin_num=*p_admin_num-1;        //����ѭ��������ָ����ֵ���һ����ͨ���Լ����ָ�����

    if((fp_gym=fopen("gym.txt", "rb"))==NULL)                       //�ж��ļ��Ƿ���Դ�
    {
        printf("Cannot open gym file\n");
        exit(0);
        system("pause");
    }
    *p_gym_num=0;
    for (i = 0; feof(fp_gym)==0; i++)
    {
        fread(&gym_info[i], sizeof(struct gym), 1, fp_gym);//���ļ��е����ݶ���ṹ��
        *p_gym_num=*p_gym_num+1;
    }
    *p_gym_num=*p_gym_num-1;        //����ѭ��������ָ����ֵ���һ����ͨ���Լ����ָ�����

    if((fp_order=fopen("order.txt", "rb"))==NULL)                   //�ж��ļ��Ƿ���Դ�
    {
        printf("Cannot open order file\n");
        exit(0);
        system("pause");
    }
    *p_order_num=0;
    for (i = 0; feof(fp_order)==0; i++)
    {
        fread(&order_info[i], sizeof(struct order), 1, fp_order);//���ļ��е����ݶ���ṹ��
        *p_order_num=*p_order_num+1;
    }
    *p_order_num=*p_order_num-1;        //����ѭ��������ָ����ֵ���һ����ͨ���Լ����ָ�����
}

unsigned long long computer_time()//��Ҫͷ�ļ�"<stdio.h>"��"<time.h>"������һ������yyyymmddhhmm����������ʾʱ��
{
    time_t tmpcal_ptr;//����time_t����������ֵ
    struct tm *tmp_ptr = NULL;//����struct tm���ͽṹ��ָ��
    unsigned long long ans;//����ֵ

    time(&tmpcal_ptr);//��ȡutcʱ�䵽��ǰʱ�̵�����
    tmp_ptr = gmtime(&tmpcal_ptr);//������ʱ��ת��Ϊһ���ṹ��
    tmp_ptr = localtime(&tmpcal_ptr);//������ʱ��ת��Ϊ����ʱ��
    ans =  (tmp_ptr->tm_hour + 100 * (tmp_ptr->tm_mday + 100 * ((1 + tmp_ptr->tm_mon) + 100 * (1900 + tmp_ptr->tm_year))));
    ans *= 100;
    ans += tmp_ptr->tm_min;

    return (ans);
}

//��������ַ�Ϸ���
int email_judge(char *email)
{
    int i, j, judge, judge_final;

    do
    {
        judge_final=1;

        printf("������ĵ�ַ��");		//��������
        scanf("%s", email);

        if(email[1]=='\0')		//�ж�email�Ƿ�ֻ��һ���ַ�
        {
        	judge_final=0;
        }
        judge=0;
        for(i=1; i<20&&email[i]!='\0'; i++)		//�ж��Ƿ���@
        {
            if(email[i]=='@')
            {
                judge=1;
                break;
            }               
        }
        if(judge==0)
        {
            judge_final=0;
        }

        if(email[i+1]=='\0')		//�ж�@֮���Ƿ����
        {
        	judge_final=0;
        }

        judge=0;
        for(i=i+2; i<40&&email[i]!='\0'; i++)		//�ж�@֮���Ƿ���.  i=i+2�����ж��Ƿ�@��.֮�����ַ�
        {
            if(email[i]=='.')
            {
                judge=1;
                break;
            }
        }
        if(judge==0)
        {
            judge_final=0;
        }
        
        judge=0;
        if(email[i+1]!='\0')		//�ж�.���Ƿ����ַ�
            judge=1;
        if(judge==0)
        {
            judge_final=0;
        }

        if(judge_final==0)
            printf("������������ʽ��������������\n");
    }while(judge_final==0);
}

//�ͻ������Աѡ�����
void print1()
{
    printf("   _______________________________________\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |        ����Ա���ʡ����밴 0          |\n");
    printf("   |                                      |\n");
    printf("   |         �ͻ����ʡ����밴 1           |\n");
    printf("   |                                      |\n");
    printf("   |______________________________________|\n");
     printf("������");
}

//��¼��ע��ѡ��
void print2() 
{
    printf("   _______________________________________\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |         ����ע��������밴 0         |\n");
    printf("   |                                      |\n");
    printf("   |         �������û������밴 1         |\n");
    printf("   |                                      |\n");
    printf("   |______________________________________|\n");
     printf("������");
}

//��������������ַ��������뺯��
int passwd_scan(char ad_pass[len])
{
    int i=0;  
    while ( i < len )
    {
        ad_pass[i] = getch();
        if (ad_pass[i] == '\r') 
        {
            printf("\n"); 
            break;
        }
        if (ad_pass[i] == '\b') 
        { 
            i=i-1; printf("\b \b"); 
        }
        else 
        {
            i=i+1;printf("*");
        }
    }
    ad_pass[i]='\0';
    return 0;
}

//����Ա��½����
void login_ad(int *p_pointer, int *p_a)
{
    char ad_id[11];
    char ad_pass[len];
    int i=0,ok=0;

    printf("���¼\n");
    printf("�������˺�:");
    scanf("%s",ad_id);
    for(i=0;i<len;i++)		//�ж��˺������Ƿ���ȷ
    {
        while((strcmp(ad_id, admin_info[i].id)==0))
        {
            printf("����������:");
            passwd_scan(ad_pass);
            if(strcmp(ad_pass, admin_info[i].password)==0)
            {
                ok=1;
                break; 
            }
            else
            {
                printf("�������,�����ԣ�");
                getchar();
                getchar();
                system ("cls");
                printf("�˺�:%s\n",ad_id);
                ok=0;
            }
        }
        if(ok)
        {
            break;
        }
    }

    if(ok)
    {
        printf("��½�ɹ�����ӭ����");
        *p_pointer=i;
        *p_a=0;  
        getchar();
        getchar();
    }
    if(!ok)
    {
        printf("��¼ʧ�ܣ������ԡ�");
        login_ad(p_pointer, p_a);
    }
    
}

//�ͻ���½����
void login_cl(int *p_pointer, int *p_a)
{
    char cl_id[11];
    char cl_pass[len];
    int i=0,ok=0;

    printf("���¼\n");
    printf("�������˺�:");
    scanf("%s",cl_id);
    for(i=0;i<len;i++)		//�ж��˺������Ƿ���ȷ
    {
        while((strcmp(cl_id, client_info[i].id)==0))
        {
            printf("����������:");
            passwd_scan(cl_pass);
            if(strcmp(cl_pass, client_info[i].password)==0)
            {
                ok=1;
                break; 
            }
            else
            {
                printf("�������,�����ԣ�");
                getchar();
                getchar();
                system ("cls");
                printf("�˺�:%s\n",cl_id);
                ok=0;
            }
        }
        if(ok)
        {
            break;
        }
    }

    if(ok)
    {
        printf("��½�ɹ�����ӭ����");
        *p_pointer=i;
        *p_a=1;  
        getchar();
        getchar();
    }
    if(!ok)
    {
        printf("��¼ʧ�ܣ������ԡ�");
        login_cl(p_pointer, p_a);
    }
    
}

//�ͻ�ע�����
void regist(int* p_client_num)
{
    char id_check[len];
    char tel_check[len];
    int i=0,j=0;
    
    while(i>=0)
    {
        printf("������ע����Ϣ��\n");
        printf("�˺�ID:"); 
        scanf("%s",id_check);
        while(id_check[i] != '\0')		//�ж�������˺��Ƿ����Ҫ��
        {
            i++;
        }
        if( i<6 || i>10 )			
        {
            printf("�˺Ų�����Ҫ���밴��������������롣\n"); 
            getch();
            system("cls");
            i=0;
        }
        if( i>=6 && i<=10 )
        {
            printf("�˺ŷ���Ҫ����������롣\n");
            break;
        }
    }
    strcpy(client_info[*p_client_num].id,id_check);
    
    printf("����:");
    scanf("%s",client_info[*p_client_num].name);
    
    printf("�Ա���/Ů��:");
    scanf("%s",client_info[*p_client_num].gender);
    
    while(j>=0)
    {
        printf("��ϵ�绰(11λ):"); 
        scanf("%s",tel_check);
        while(tel_check[j] != '\0')		//�ж�����ĵ绰�����Ƿ����Ҫ�� 
        {
            j++;
        }
        if(j!=11)
        {
            printf("�绰���벻����Ҫ���밴��������������롣\n"); 
            getch();
            j=0;
        }
        if(j==11)
        {
            printf("�˺ŷ���Ҫ����������롣\n");
            break;
        }
    }
    strcpy(client_info[*p_client_num].tel,tel_check);
    
    printf("����:");
    passwd_scan(client_info[*p_client_num].password);
    printf("��ȷ������:%s\n",client_info[*p_client_num].password);
    
    printf("��������:\n");
    email_judge(client_info[*p_client_num].email);
    
    printf("סַ:");
    scanf("%s",client_info[*p_client_num].zone);
    
    *p_client_num=*p_client_num+1;			//����Ч���ȼ�����չ
}

int client_search(int id, int gym_num, int order_num, int *p_order_num)
{   
    char opera[len];
    int reserve;        //�����Ƿ����Ԥ�������Ĳ�����
    int i;
    char func[2];
    int show=0;

    printf("�����ѯ�ķ�ʽ��\n");       //��ӡѡ���б�
    printf("1.���ݳ�������\n");
    printf("2.���ݳ�������\n");
    printf("3.������������\n");
    printf("4.�����Ƿ��п��ೡ��\n");
    printf("5.�����������\n");
    printf("6.����Ԥ��������\n");
    printf("7.�����Ƽ�\n");
    printf("��ѡ������Ҫ�ķ�ʽ��");
    scanf("%s",func);       //ѡ��������ݣ��ݴ�

    system("cls");
    switch(func[0])                //�ù˿�ѡ���ѯ��ʽ
    {
        case '1':
            printf("1.���ݳ�������\n");
            printf("���ƣ�");
            scanf("%s",&opera);
            for (i = 0; i < gym_num; ++i)       //����gym�ṹ�壬Ѱ�ҳ���
            {
                if(strcmp(opera, gym_info[i].num)==0)
                {
                    show_gym(i, order_num);
                    show=1;
                }
            }
            if(show==0)         //��δ�ӽṹ�����ҵ�����ʾ�û�
            {
                printf("δ�ҵ��ó��ء�\n");
                getch();
                break;
            }
            printf("���Ƿ������Ԥ�����أ���������1����������0��\n");
            scanf("%d",&reserve);
            if(reserve==1)      //���û�ѡ���ѯ���Ƿ����Ԥ������
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '2':
        printf("2.���ݳ�������\n");
            printf("���ƣ�");
            scanf("%s",&opera);
            for (i = 0; i < gym_num; ++i)       //����gym�ṹ�壬Ѱ�ҳ���
            {
                if(strcmp(opera, gym_info[i].belong_stadium)==0)
                {
                    show_gym(i, order_num);
                    show=1;
                }                    
            }
            if(show==0)         //��δ�ӽṹ�����ҵ�����ʾ�û�
            {
                printf("δ�ҵ��ó��ݡ�\n");
                getch();
                break;
            }
            printf("���Ƿ������Ԥ�����أ���������1����������0��\n");
            scanf("%d",&reserve);
            if(reserve==1)      //���û�ѡ���ѯ���Ƿ����Ԥ������
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '3':
            printf("3.��������\n");
            printf("����");
            scanf("%s",&opera);
            for (i = 0; i < gym_num; ++i)       //����gym�ṹ�壬Ѱ������
            {
                if(strcmp(opera, gym_info[i].zone)==0)
                {
                    show_gym(i, order_num);
                    show=1;
                }                    
            }
            if(show==0)         //��δ�ӽṹ�����ҵ�����ʾ�û�
            {
                printf("δ�ҵ�������\n");
                getch();
                break;
            }
            printf("���Ƿ������Ԥ�����أ���������1����������0��\n");
            scanf("%d",&reserve);
            if(reserve==1)      //���û�ѡ���ѯ���Ƿ����Ԥ������
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '4':
            printf("4.�����Ƿ��п��ೡ��\n");
            avail_gym_search(gym_num, order_num);       //���ú���
            printf("���Ƿ������Ԥ�����أ���������1����������0��\n");
            scanf("%d",&reserve);
            if(reserve==1)      //���û�ѡ���ѯ���Ƿ����Ԥ������
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '5':
            printf("5.�����������\n");
            rent_sort(gym_num, order_num);      //���ú���
            printf("���Ƿ������Ԥ�����أ���������1����������0��\n");
            scanf("%d",&reserve);
            if(reserve==1)      //���û�ѡ���ѯ���Ƿ����Ԥ������
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '6':
            printf("6.����Ԥ��������\n");
            order_sort(gym_num, order_num);     //���ú���
            printf("���Ƿ������Ԥ�����أ���������1����������0��\n");
            scanf("%d",&reserve);
            if(reserve==1)      //���û�ѡ���ѯ���Ƿ����Ԥ������
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '7':
            printf("7.�����Ƽ�\n");
            gym_recommend(gym_num, order_num, id);      //���ú���
            printf("���Ƿ������Ԥ�����أ���������1����������0��\n");
            scanf("%d",&reserve);
            if(reserve==1)      //���û�ѡ���ѯ���Ƿ����Ԥ������
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        default:
            printf("����������\n");     //�ݴ���ֹ�˿��������
            system("pause");
            break;
    }
}

int show_gym(int i, int order_num)
{
    int j;
    unsigned long long time_now;
    int temp;
    int alreadyshow=0;

    printf("���ر�ţ�%s\n",gym_info[i].num);
    printf("����������%s\n",gym_info[i].zone);
    printf("�������ݣ�%s\n",gym_info[i].belong_stadium);
    printf("�������%s\n",gym_info[i].type);
    printf("���ؼ�飺%s\n",gym_info[i].introdution);
    printf("׼�����䣺%d-%d\n",gym_info[i].permit_age[0], gym_info[i].permit_age[1]);
    printf("���:%.2f\n",gym_info[i].rent);
    printf("����δ��ԤԼ�����\n");
    time_now = computer_time();             //��ȡ���������ʱ��
    time_now = time_now/10000;
    for(j=0; j<order_num; j++)              //����order�ṹ�壬Ѱ��δ���Ķ���
    {
        if(strcmp(order_info[j].gymnum, gym_info[i].num)==0)
            if(order_info[j].rent_date>=(int)time_now)
            {
                printf("%d��%d��%d��%dʱ����",order_info[j].rent_date/10000, order_info[j].rent_date/100%100, order_info[j].rent_date%100, order_info[j].begin_time);
                printf("%d��%d��%d��%dʱ\n",order_info[j].rent_date/10000, order_info[j].rent_date/100%100, order_info[j].rent_date%100, order_info[j].over_time);
                alreadyshow++;
            }   
    }
    if(alreadyshow==0)          //��δ�ҵ�����������ʾ�û�
    {
        printf("��ǰ����δ����ԤԼ\n");
    }
    printf("\n");
    printf("\n");
}

//������qsort���躯��, ��С����
int float_cmp(const void *a, const void *b)       
{
     return (*(float *)a-*(float *)b);
}

//����qsort���躯��,�Ӵ�С
int int_cmp(const void *a, const void *b)
{
     return (*(int *)b-*(int *)a);
}

int rent_sort(int gym_num, int order_num)
{
    int i, j, k, x, judge;
    float rent[gym_num];
    float alreadyshow[gym_num];
    printf("�����ݰ�����С��������\n\n");

    for(i=0; i<gym_num; i++)                                    //�����ظ������ʼ��
        alreadyshow[i]=-1;

    for(i=0; i<gym_num; i++)                                    //�����г��ص����ֵ��һ���ɹ�����ĸ�����������
    {
        rent[i]=gym_info[i].rent;
    }
    qsort(rent, gym_num, sizeof(float), float_cmp);             //���ɹ�����������������
    
    j=0;
    k=0;
    for(i=0; i<gym_num; i++)                                    //�����Ѿ�����������飬�ӵ�һλ���ӳ�����Ѱ�Ҷ�Ӧ�ĳ���
    {
        judge=1;                                                
        for(x=0; x<k; x++)                                      //���ں����forѭ���޷��жϵ�һ��λ���Ƿ��ظ�����ѭ������ȷ����һ��λ���Ƿ��ظ� 
            if(alreadyshow[x]==0)
                judge=0;
        while(rent[i]!=gym_info[j].rent || judge==0)              //Ѱ�Ҹ��������Ӧ�ĳ���
        {
            j++;
                
            judge=1;                                            //�����Ƿ��ظ�
            for(x=0; x<k; x++)                                  
                if(alreadyshow[x]==j)
                    judge=0;
        }
        show_gym(j, order_num);                                 //���ҵ��ĳ������
        alreadyshow[k]=j;                                       //���Ѿ�����ĳ��ص�λ�ø�ֵ�������ظ�����
        k++;
        j=0;
    }
}

int order_sort(int gym_num, int order_num)
{
    int number[gym_num], temp[gym_num], alreadyshow[gym_num];
    int i, j, k, x, judge;
    printf("�����ذ�����ʷ���У��������Ӵ�С����:\n\n");

    for(i=0; i<gym_num; i++)                                        //�����ظ������ʼ��
    {
        alreadyshow[i]=-1;
        number[i]=0;
    }
        
    for (i=0; i<gym_num; i++)                                       //����������صĶ�����    
    {
        for(j=0; j<order_num; j++)                                  //ͨ������order_info�ṹ�����飬���㵥�����صĶ�����
            if(strcmp(order_info[j].gymnum, gym_info[i].num)==0)
                number[i]++;
    }
    
    for(i=0; i<gym_num; i++)                                        //���������صĶ�������ֵ��һ���ɹ��������������
    {
        temp[i]=number[i];
    }
    qsort(temp, gym_num, sizeof(int), int_cmp);                     //���ɹ�����������������
    
    j=-1;
    k=0;
    for(i=0; i<gym_num; i++)                                        //�����Ѿ�����������飬�ӵ�һλ���ӳ�����Ѱ�Ҷ�Ӧ�ĳ���
    {
        judge=1;                                        //���ں����forѭ���޷��жϵ�һ��λ���Ƿ��ظ�����ѭ������ȷ����һ��λ���Ƿ��ظ� 
        for(x=0; x<k; x++)
            if(alreadyshow[x]==0)
                judge=0;
        while(number[j]!=temp[i]||judge==0)                   //Ѱ�Ҹö���������Ӧ�ĳ���
        {
            j++;
                
            judge=1;                                            //�����Ƿ��ظ�
            for(x=0; x<k; x++)  
                if(alreadyshow[x]==j)
                    judge=0;            
        }
        
        show_gym(j, order_num);                                                //���ҵ��ĳ������
        alreadyshow[k]=j;                                           //���Ѿ�����ĳ��ص�λ�ø�ֵ�������ظ�����
        k++;
        j=0;
    }
}

int client_reserve(int *p_order_num, int id, int gym_num)
{
    int number, position, rent_begin_time, rent_over_time;
    int condition_age, condition_time;                              //�ж���ȷ�Ĳ�����
    int i, j, k, temp_begin;
    float allrent=0;
    int show, c_judge, c_time_judge;
    char c_number[2], c_rent_date[9], c_begin_time[3], c_over_time[3];

    if(client_info[id].sign>3)                                   //�жϸù˿�ˬԼ�����Ƿ����
        printf("��ˬԼ�����Ѿ�����3�Σ��������ٴ�Ԥ����\n");
    else
    {
        do
        {
            c_judge=1;
            printf("����Ԥ���������أ�");            //��ȡ�ôζ�������
            scanf("%s",c_number);
            if(((int)c_number[0])<48 ||((int)c_number[0])>57)       //�ж������ʽ�Ƿ�Ϸ�
            {
                c_judge=0;
                printf("�����������������롣\n");
            }
        }while(c_judge==0);
        number=(int)c_number[0]-48;     //��������ַ���ת��Ϊ����

        for(i=0; i<number; i++)
        {
            strcpy(order_info[*p_order_num].user_id, client_info[id].id);               //��order_info�ṹ��Ĳ�����Ϣ���и�ֵ
            order_info[*p_order_num].reserve_date = computer_time();
            condition_age=1;    //��ʼ���жϵ��ж��������Ƿ���ʵĲ�����
            do                                                  
            {
                do
                {
                    show=0;
                    printf("����������ҪԤ���ĳ�������\n");
                    scanf("%s",order_info[*p_order_num].gymnum);
                    for(j=0; j<gym_num; j++)                                    //��ȡ�˿�����ĳ�������gym_info�ṹ�������е�λ��
                    {
                        if(strcmp(order_info[*p_order_num].gymnum, gym_info[j].num)==0)
                        {
                            position=j;
                            show=1;
                            break;
                        }
                    }
                    if(show==0)     //��ṹ����û�иó��أ���ʾ�û���������
                    {
                        printf("δ�ҵ��ó��أ����������롣\n");
                    }
                }while(show==0);
                if(client_info[id].age<gym_info[position].permit_age[0]||client_info[id].age>gym_info[position].permit_age[1])  //�жϸù˿͵������Ƿ��ʺϸó���
                {
                    condition_age=0;
                    printf("�������䲻�ʺϴ˳��ص��˶���Ŀ�������ԡ�\n");
                }
            }while(condition_age==0);
            
            
            do
            {
            condition_time=1;   //��ʼ���ж�ʱ���Ƿ��ͻ�Ĳ�����
                do
                {
                    c_judge=1;
                    printf("�������������õ����ڣ�ʾ�����������������Ϊ2018��9��12�գ�������20180912����\n");     //��ȡ�ͻ�����ʱ���
                    scanf("%s", c_rent_date);
                    for(k=0; k<8; k++)
                    {
                        if(((int)c_rent_date[k])>57 || ((int)c_rent_date[k])<48)        //�ж��û�����ʱ���ʽ�Ƿ���ȷ
                        {
                            c_judge=0;
                            printf("��ʽ�������������롣\n");        //������������ʾ�û���������
                            break;
                        }
                    }
                }while(c_judge==0);
                order_info[*p_order_num].rent_date=0;
                for(k=0; k<8; k++)      //���û����������ת��Ϊ���β���ֵ��order_info[*p_order_num].rent_date
                {
                    order_info[*p_order_num].rent_date=order_info[*p_order_num].rent_date+((int)(c_rent_date[k])-48)*(int)pow(10,7-k);
                }

                do
                {
                    c_time_judge=1;
                    do
                    {
                        c_judge=1;
                        printf("�������������õľ�����ʼʱ��,�������㿪ʼ,���ؿ���ʱ��Ϊ6����22�㣨ʾ������������õľ�����ʼʱ��Ϊ9�㣬������9����\n");
                        scanf("%s", c_begin_time);
                        for(k=0; k<2; k++)      //�ж��û�����ʱ���ʽ�Ƿ���ȷ
                        {
                            if(c_begin_time[k]=='\0')
                                break;
                            if(((int)c_begin_time[k])>57 || ((int)c_begin_time[k])<48 )     //�����������ʾ�û���������
                            {
                                c_judge=0;
                                printf("��ʽ�������������롣\n");
                                break;
                            }
                        }
                    }while(c_judge==0);
                    order_info[*p_order_num].begin_time=0;
                    if(c_begin_time[1]=='\0')                   //���û������ʱ��ת��Ϊ���Σ�����ֵ���ṹ��
                        order_info[*p_order_num].begin_time=(int)c_begin_time[0]-48;
                    else
                        order_info[*p_order_num].begin_time=((int)c_begin_time[0]-48)*10+(int)c_begin_time[1]-48;

                    if(order_info[*p_order_num].begin_time<6 || order_info[*p_order_num].begin_time>21)     //�ж��û�ѡ���ʱ��ʱ���ڿ���ʱ����
                    {
                        printf("��ѡ���ʱ��δ�ڿ���ʱ���ڡ�\n");
                        c_time_judge=0;
                    }
                }while(c_time_judge==0);

                do
                {
                    c_time_judge=1;
                    do
                    {
                        c_judge=1;
                        printf("�������������õľ������ʱ��,�����������,���ؿ���ʱ��Ϊ6����22�㣨ʾ������������õľ������ʱ��Ϊ10�㣬������10����\n");
                        scanf("%s", c_over_time);
                        for(k=0; k<2; k++)      //�ж��û�����ʱ���ʽ�Ƿ���ȷ
                        {
                            if(c_over_time[k]=='\0')
                                break;
                            if(((int)c_over_time[k])>57 || ((int)c_over_time[k])<48 )       //�����������ʾ�û���������
                            {
                                c_judge=0;
                                printf("��ʽ�������������롣\n");
                                break;
                            }
                        }
                    }while(c_judge==0);
                    order_info[*p_order_num].over_time=0;
                    if(c_over_time[1]=='\0')                    //���û������ʱ��ת��Ϊ���Σ�����ֵ���ṹ��
                        order_info[*p_order_num].over_time=(int)c_over_time[0]-48;
                    else
                        order_info[*p_order_num].over_time=((int)c_over_time[0]-48)*10+(int)c_over_time[1]-48;
                    if(order_info[*p_order_num].over_time<=order_info[*p_order_num].begin_time || order_info[*p_order_num].over_time>22)        //�ж��û������ʱ���Ƿ����Ҫ��
                    {
                        printf("��ѡ��Ľ���ʱ���������������롣\n");
                        c_time_judge=0;
                    }
                }while(c_time_judge==0);
                
                rent_begin_time=order_info[*p_order_num].rent_date*100+order_info[*p_order_num].begin_time/100;     //�Խṹ����и�ֵ
                rent_over_time=order_info[*p_order_num].rent_date*100+order_info[*p_order_num].over_time/100;
                for(j=0; j<*p_order_num; j++)                       //�ж��û�ѡ���ʱ���Ƿ�����ж����г�ͻ
                {
                    if(strcmp(order_info[j].gymnum, order_info[*p_order_num].gymnum)==0)
                    {
                        if(order_info[j].rent_date==order_info[*p_order_num].rent_date)
                        {
                            if(order_info[*p_order_num].begin_time>order_info[j].begin_time && order_info[*p_order_num].begin_time<order_info[j].over_time)
                                condition_time=0;
                            if(order_info[*p_order_num].over_time>order_info[j].begin_time && order_info[*p_order_num].over_time<order_info[j].over_time)
                                condition_time=0;
                            if(order_info[*p_order_num].begin_time==order_info[j].begin_time)
                                condition_time=0;
                            if(order_info[*p_order_num].over_time==order_info[j].over_time)
                                condition_time=0;
                        }
                    }
                }
                if(condition_time==0)
                    printf("����ѡ���ʱ���г�ͻ��������ѡ��\n");      //���ó�ͻ����ʾ�û���������
            }while(condition_time==0);

            allrent=allrent+gym_info[position].rent*((float)order_info[*p_order_num].over_time - (float)order_info[*p_order_num].begin_time);       //�����ܽ��
            *p_order_num=*p_order_num+1;
        }
        if(allrent > client_info[id].account)               //�ж��˻�����Ƿ��㹻
        {
            printf("�����˻�������֧���˴�Ԥ�����ܽ����β���ʧ�ܡ�\n");
            getch();
            *p_order_num=*p_order_num - number;                 //ʧ�ܺ�order_info����Ч�����˻ص�Ԥ��ǰ
        }
        else
        {
        	printf("Ԥ���ɹ���\n");
        	getch();
		}
    }
}

int avail_gym_search(int gym_num, int order_num)
{
    char c_day_num[9], c_begin_hours[3], c_over_hours[3];
    int day_num, begin_hours, over_hours;           
    int i, j, show_num, judge, c_judge;

    do
    {
        c_judge=1;
        printf("�����ѯ�������п���ʱ��ĳ���:��ʾ������������ѯ2018��9��13���п���ʱ��ĳ��أ�������20180913\n");     //��ȡ�ͻ�����ʱ���
        scanf("%s", c_day_num);
        for(i=0; i<8; i++)          //�ж��û�����ʱ��ʱ�����Ҫ��
        {
            if(((int)c_day_num[i])>57 || ((int)c_day_num[i])<48)
            {
                c_judge=0;
                printf("��ʽ�������������롣\n");            //������������ʾ�û���������
                break;
            }
        }
    }while(c_judge==0);
    day_num=0;
    for(i=0; i<8; i++)          //���û������ʱ��ת��Ϊ����
    {
        day_num=day_num+((int)(c_day_num[i])-48)*(int)pow(10,7-i);
    }

    do
    {
        c_judge=1;
        printf("�����ѯ��ʲôʱ���п����ʱ�䣺��ʾ������������ѯ��10�㿪ʼ�Ŀ���ʱ�䣬������10\n");
        scanf("%s", c_begin_hours);
        for(i=0; i<2; i++)
        {
            if(c_begin_hours[i]=='\0')
                break;
            if(((int)c_begin_hours[i])>57 || ((int)c_begin_hours[i])<48 )       //�ж��û������ʱ���Ƿ����Ҫ��
            {
                c_judge=0;
                printf("��ʽ�������������롣\n");            //������������ʾ�û���������
                break;
            }
        }
        if(c_judge==1)
        {
        	begin_hours=0;
        	if(c_begin_hours[1]=='\0')      //���û������ʱ��ת��Ϊ����
	            begin_hours=(int)c_begin_hours[0]-48;
	        else
	            begin_hours=((int)c_begin_hours[0]-48)*10+(int)c_begin_hours[1]-48;

	        if(begin_hours<6 || begin_hours>21)
	        {
	            printf("��ѡ���ʱ��δ�ڿ���ʱ���ڡ�������ѡ��\n");
	            c_judge=0;
	        }
        }
    }while(c_judge==0);
    

    do
    {
        c_judge=1;
        printf("�����ѯ�п���ʱ���ֹ��ʲôʱ�򣺣�ʾ������������ѯ��xx�㵽12��Ŀ���ʱ�䣬������12\n");
        scanf("%s", c_over_hours);
        for(i=0; i<2||c_over_hours[i]=='\0'; i++)               
        {
            if(c_over_hours[i]=='\0')
                break;
            if(((int)c_over_hours[i])>57 || ((int)c_over_hours[i])<48)              //�ж��û������ʱ���Ƿ����Ҫ��
            {
                c_judge=0;
                printf("��ʽ�������������롣\n");            //������������ʾ�û���������
                break;
            }
        }
        if(c_judge==1)
        {
        	over_hours=0;
	        if(c_over_hours[1]=='\0')           //���û������ʱ��ת��Ϊ����
	            over_hours=(int)c_over_hours[0]-48;
	        else
	            over_hours=((int)c_over_hours[0]-48)*10+(int)c_over_hours[1]-48;
	        if(over_hours<=begin_hours || over_hours>22)
	        {
	            printf("��ѡ���ʱ����������������\n");
	            c_judge=0;
	        }
        }
    }while(c_judge==0);
    
    system("cls");
    
    show_num=0;
    for(i=0; i<gym_num; i++)        //�����ṹ��gymѰ��ÿ������
    {
        judge=1;
        for(j=0; j<order_num; j++)      //����order�ṹ��Ѱ�Ҹó��صĶ���
        {
            if(strcmp(order_info[j].gymnum, gym_info[i].num)==0)
            {
                if(order_info[j].rent_date==day_num)            //�жϸó����Ƿ��п���ʱ��
                {
                    if(begin_hours>order_info[j].begin_time && begin_hours<order_info[j].over_time)
                        judge=0;
                    if(over_hours>order_info[j].begin_time && over_hours<order_info[j].over_time)
                        judge=0;
                    if(begin_hours==order_info[j].begin_time)
                        judge=0;
                    if(over_hours==order_info[j].over_time)
                        judge=0;
                }
            }
        }
        if(judge==1)        //������Ҫ��ĳ������
        {
            show_gym(i, order_num);
            show_num++;
        }
    }
    if(show_num==0)                         //���û�г����п���ʱ�䣬��֪�˿�
        printf("��Ǹ����ѡ���ʱ�����û�п��ೡ��\n");
}

int gym_recommend(int gym_num, int order_num, int id)
{
    int number[gym_num], temp[gym_num], alreadyshow[gym_num];
    int i, j, k, x, judge;
    for(i=0; i<gym_num; i++)                                        //�����ظ������ʼ��
    {
        alreadyshow[i]=-1;
        number[i]=0;
    }
        
    for (i=0; i<gym_num; i++)                                       //����������صĶ�����    
    {
        for(j=0; j<order_num; j++)                                  //ͨ������order_info�ṹ�����飬���㵥�����صĶ�����
            if(strcmp(order_info[j].gymnum, gym_info[i].num)==0)
                number[i]++;
    }
    
    for(i=0; i<gym_num; i++)                                        //���������صĶ�������ֵ��һ���ɹ����������
    {
        temp[i]=number[i];
    }
    qsort(temp, gym_num, sizeof(int), int_cmp);                     //���ɹ�����������������
    
    j=-1;
    k=0;
    for(i=0; i<gym_num; i++)                                        //�����Ѿ�����������飬�ӵ�һλ���ӳ�����Ѱ�Ҷ�Ӧ�ĳ���
    {
        judge=1;                                        //���ں����forѭ���޷��жϵ�һ��λ���Ƿ��ظ�����ѭ������ȷ����һ��λ���Ƿ��ظ� 
        for(x=0; x<k; x++)
            if(alreadyshow[x]==0)
                judge=0;
        while(number[j]!=temp[i]||judge==0)                   //Ѱ�Ҹö���������Ӧ�ĳ���
        {
            j++;
                
            judge=1;                                            //�����Ƿ��ظ�
            for(x=0; x<k; x++)  
                if(alreadyshow[x]==j)
                    judge=0;            
        }                                                
        alreadyshow[k]=j;
        if(strcmp(client_info[id].zone, gym_info[j].zone)==0)       //�жϸó����Ƿ���ÿͻ�����һ�����򣬷��������
            show_gym(j, order_num);                                           
        k++;
        j=0;
    }
}

int change_info(int leng)//�޸��û�������Ϣ�������Ǹ��û��Ľ��� 
{
    char option;//��Ǳ��� 
    char tel_tem[12], password_tem1[len], password_tem2[len], email_tem[len], zone_tem[len];//���汻�޸���Ϣ����ʱ���� 
    int index;//�ֲ�ѭ������
    int option1 ;//�жϱ��� 
    
    printf("���в�����\"y\"�����ǡ���\"n\"�������ַ�������\n");//������Ĳ�������˵�� 
    printf("��ϣ���޸����ĵ绰��Ϣ��(Y/n)\n");//ѯ���û��Ƿ���д˲�������ͬ�� 
    fflush(stdin);//����������գ���ֹ���벻��ȷ��ʽʱ���� 
    while(1)
    {
        scanf("%c", &option);
        fflush(stdin);
        if(option == 'y' || option == 'Y')//�����������ַ����򲻽��б����޸� ����ͬ�� 
        {
            while(1)//���޸Ĺ��̴��������ѭ������������ 
            {
                printf("�������µĵ绰��Ϣ:\n");
                fflush(stdin); 
                scanf("%s", tel_tem);
                fflush(stdin);
                option1 = 0;//���жϱ��������£���ֵ 
                for(index = 0; index < 11; index ++)
                {
                    if(48 > tel_tem[index] || tel_tem[index] > 57)
                    {
                        option1 = 1;//ȷ���������� 
                        printf("�绰��Ϣ��������\n");
                        break;
                    }
                }
                if(option1 == 1)
                {
                    continue;
				}
    	        strcpy(client_info[leng].tel, tel_tem);
	        	printf("�绰�����޸ĳɹ���\n");
				break; 
        	}
    	    break;
        }
        else if(option == 'n' || option == 'N') 
        {
            printf("��ȡ���޸ĵ绰����\n");
            break;
        }
            
        else
        {
            printf("���������롣\n");
            continue;
        }
    }

    printf("��ϣ���޸�����������(Y/n)\n");
    while(1)
    {
        scanf("%c", &option); 
        fflush(stdin);
        if(option == 'y' || option == 'Y')
        {
           while(1)
            {
                printf("�����������룺\n");
                scanf("%s", password_tem1); 
                fflush(stdin);
                printf("���ٴ����������룺\n");//�ٴ����룬��ֹ������� 
                scanf("%s", password_tem2);
                fflush(stdin);
                if(strcmp(password_tem1, password_tem2)==0)//�ж����������Ƿ�һ�� 
                {
                    strcpy(client_info[leng].password, password_tem1);
                    printf("�����޸ĳɹ���\n");
	                break;
                } 
                else
                    printf("�������벻��ͬ������������\n");
            }
            break;
        }
        else if(option == 'n' || option == 'N')
        {
            printf("��ȡ���޸�����\n");
            break;
        }
        else
        {
            printf("����������\n");
            continue;
        }
    }
        
    printf("��ϣ���޸�����������(Y/n)\n");
    while(1)
    {
    	scanf("%c", &option);
    	fflush(stdin);
    	if(option == 'y' || option == 'Y')
    	{
    		email_judge(client_info[leng].email);
    		break;
		}
		else if(option == 'n' || option == 'N')
		{
			break;
		}
		else
			continue;
    	
	}
    
            
    printf("��ϣ���޸����ĵ�ַ��?(Y/n)\n");//ѯ���Ƿ��޸ĵ�ַ
    while(1)
    {
        fflush(stdin);
        scanf("%c", &option);
        fflush(stdin);
        if(option == 'y' || option == 'Y')
        {
            while(1)
            {
                printf("�������µĵ�ַ��\n");
                scanf("%s", zone_tem);
                fflush(stdin);
                strcpy(client_info[leng].zone, zone_tem);
                printf("��ַ�޸ĳɹ���\n");
                break;
            }
            break;
        }
        else if(option == 'n' || option == 'N')
        {
            printf("��ȡ���޸ĵ�ַ\n");
            break;
            
        }
        else
        {
            printf("����������\n");
            continue;
        }
    }

    printf("�޸Ľ�����\n");
    system("pause");
}

int query_info(char *cli_id,int *leng)//����Ϊ�û�id�ͽṹ���� 
{
    int index = 0, index1 = 0;//�ֲ�ѭ������ 
    int order_num[*leng];//����û��Ķ����� 
    unsigned long long year , mon, day, hour, min;

    for(index = 0, index1 = 0; index < *leng; index ++)//�ҳ�Ҫ�û���Ŀ���� 
    {
        if(strcmp(cli_id, order_info[index].user_id) == 0)
        {
            order_num[index1] = index;
            index1 ++;
        }
    }
    for(index = 0; index < index1; index ++)//�����ѯ������û�������
    {
        printf("������ţ�%s%-llu\n", order_info[order_num[index]].user_id, order_info[order_num[index]].reserve_date);//��ӡ Ԥ����� 
        year = order_info[order_num[index]].reserve_date / 100000000;
        mon = (order_info[order_num[index]].reserve_date / 1000000) % 100;
        day = (order_info[order_num[index]].reserve_date / 10000) % 100;
        hour = (order_info[order_num[index]].reserve_date / 100) % 100;
        min = order_info[order_num[index]].reserve_date % 100;
        printf("Ԥ�����ڣ�%llu��%llu��%llu��%lluʱ%llu��\n", year, mon, day, hour, min);//Ԥ������ 
        printf("���ر�ţ�%s\n", order_info[order_num[index]].gymnum);//�䳡�ر�� 
        year = order_info[order_num[index]].rent_date / 10000;
        mon = (order_info[order_num[index]].rent_date / 100) % 100;
        day = order_info[order_num[index]].rent_date % 100;
        printf("Ԥ�����ڣ�%d��%d��%d��\n", year, mon, day);//��賡������ 
        printf("��ʼʱ�䣺%d��\n", order_info[order_num[index]].begin_time);//��賡�ؿ�ʼʱ�� 
        printf("����ʱ�䣺%d��\n", order_info[order_num[index]].over_time);//��賡�ؽ���ʱ��
        printf("�Ƿ񵽳�");
        if(order_info[order_num[index]].sign == 1)//�Ƿ�ʱ���� 
            printf("YES");
        else
            printf(" NO");
        printf("\n\n");
    }
}


int delete_info(char *cli_id, int *leng)//ɾ�������������ֱ�����û�id�Ͷ����ṹ���� 
{
    unsigned long long ord_num;//���� 
    char key[20];
    int index = 0;//�ֲ�ѭ������ 
    int del_num;//ɾ��Ŀ��ı�� 
    int option = 0;
 
    query_info(cli_id, leng);//��ʾ�û�����������ɾ������ 
    printf("������Ҫɾ���Ķ����ı�ŵ����ڵĲ��֣���12λ������\n");
    scanf("%llu", &ord_num);
    fflush(stdin);//����������գ���ֹ�����ַ�ʱ������� 

    for(index = 0; index < *leng; index ++)//�ҳ�Ҫɾ����Ŀ���� 
    {   
        if(strcmp(cli_id, order_info[index].user_id) == 0 && order_info[index].reserve_date == ord_num)
        {
            del_num = index;
            for(index = del_num; index < (*leng-1); index ++)//�ѱ�ɾ��Ŀ�긳ֵΪ����Ľṹ�壬������ظ� 
            {
                order_info[index] = order_info[index+1];
            }
            *leng = *leng - 1;//���ṹ���ȼ�С
            option = 1;//��ʾ�ɹ�ɾ�� 
            break;//�ҵ�Ŀ���ź��˳�ѭ�� 
        }
    }
    
    if(option == 1)
        printf("\nɾ���ɹ�\n");
    else
        printf("\nɾ��ʧ��\n");

    system("pause");
}

int ad_menu1()
{
    printf("�𾴵Ĺ���Ա�����ã�\n\n");
    printf("--------------------����Աϵͳ------------------\n");
    printf("1.��ѯ�Լ�������Ԥ�������\n");
    printf("2.ͳ���û�Ԥ����Ϣ\n");
    printf("3.��ѯ������Ϣ\n");
    printf("4.����³���\n");
    printf("5.�޸ĸ�����Ϣ\n");
    printf("6.�˳�����\n");
    printf("------------------------------------------------\n");
    printf("�����룺"); 
}

int ad_menu2()
{
    printf("------------------ͳ���û�Ԥ����Ϣ--------------\n");
    printf("1.��Ԥ�����Ա�����������������\n");
    printf("2.ͳ�Ƴ���Ӫҵ�\n");
    printf("3.ͳ�Ʋ�ͬ���ص��û������ηֲ���\n");
    printf("4.��Ӫҵ��Ա����ݵ����г�������\n");
    printf("5.�����Ա�ͳ��������ʿ/Ůʿ��ӭ���˶���\n");
    printf("6.��ʱ���ͳ�Ʋ�ͬ���ͳ��ص����������\n");
    printf("------------------------------------------------\n");
    printf("�����룺"); 
}


int ad_check(int *ad_point, int order_num)
{
	int i = 0;
	int year, mon, day, hour, min;
	int y, m, d;
	printf("���������%s�ų��ݡ�\n", admin_info[*ad_point].gymnasium);
	printf("--------------��������ʷ�϶�����¼------------\n\n");
	for (i = 0; i < order_num; i++)                                                              //������ʷ����
	{
		year = order_info[i].reserve_date / 100000000;
		mon = (order_info[i].reserve_date / 1000000) % 100;
		day = (order_info[i].reserve_date / 10000) % 100;
		hour = (order_info[i].reserve_date / 100) % 100;
		min = order_info[i].reserve_date % 100;

		y = order_info[i].rent_date / 10000;
		m = (order_info[i].rent_date / 100) % 100;
		d = order_info[i].rent_date % 100;
		if (strncmp(admin_info[*ad_point].gymnasium, order_info[i].gymnum, 6) == 0)             //��ӡ��ʷ����                                                 //��������Ա�ṹ�壬ƥ������½����Ա 
		{
			printf("�û�ID:%s\n", order_info[i].user_id);                                                                                         //��ӡ��Ҫ��Ϣ 
			printf("�������ݱ��:%s\n", order_info[i].gymnum);
			printf("Ԥ������:%llu��%llu��%llu��%lluʱ%llu��\n", year,mon,day,hour,min);
			printf("ʹ������:%d��%d��%d�� %dʱ��%dʱ\n", y,m,d, order_info[i].begin_time, order_info[i].over_time);
			printf("�Ƿ����ó���:%d(ǩ��Ϊ1����֮Ϊ0)\n\n\n", order_info[i].sign);
		}
	}
	printf("----------------------------------------------\n");
}

int ad_stat_gender(int gym_num, int client_num, int order_num)
{
    int i, j, k;
    int man[gym_num], woman[gym_num];                                                     //�������飬�Ա㴢�治ͬ�Ա�Ķ���
    int m_max, w_max;

    for (i = 0; i < gym_num; i++)
    {
        man[i] = 0;
        woman[i] = 0;
    }

    for (i = 0; i < gym_num; i++)                                                        //�����˿͡�����Ա������������ 
        for (j = 0; j < order_num; j++)
            if (strcmp(gym_info[i].num, order_info[j].gymnum) == 0)
                for (k = 0; k < client_num; k++)
                    if (strcmp(order_info[j].user_id, client_info[k].id) == 0)           //ƥ��˿�id�붩��id
                    {
                        if (strcmp(client_info[k].gender, "Ů") == 0)                    //ƥ���Ա�
                            woman[i]++;
                        else if (strcmp(client_info[k].gender, "��") == 0)
                            man[i]++;
                    }

    printf("�������У�\n");
    m_max = man[0];
    for (i = 0; i < gym_num; i++)
    {
        printf("ϲ��ȥ%s������%d��\n", gym_info[i].num, man[i]);
        if ((i > 0) && (man[i] > man[i - 1]))
            m_max = i;                                                                   //�������������ܻ�ӭ�ĳ���
    }
    printf("������ϲ��ȥ:%s\n\n", gym_info[m_max].num);

    printf("��Ů���У�\n");
    w_max = woman[0];
    for (i = 0; i < gym_num; i++)
    {
        printf("ϲ��ȥ%s������%d��\n", gym_info[i].num, woman[i]);
        if ((i > 0) && (woman[i] > woman[i - 1]))
            w_max = i;
    }
    printf("Ů����ϲ��ȥ:%s\n", gym_info[w_max].num);
}

int ad_stat_age(int gym_num, int client_num, int order_num)
{
    int i, j, k;
    int young[gym_num], mid[gym_num], old[gym_num];

    for (i = 0; i < gym_num; i++)
    {
        young[i] = 0;
        mid[i] = 0;
        old[i] = 0;
    }

    for (i = 0; i < gym_num; i++)                                                                     //�����˿͡�����Ա������������
        for (j = 0; j < order_num; j++)    
            if (strcmp(gym_info[i].num, order_info[j].gymnum) == 0)
                for (k = 0; k < client_num; k++)
                    if (strcmp(order_info[j].user_id, client_info[k].id) == 0)                        //ƥ��˿�id�Ͷ���id
                        if (client_info[k].age < 30)                                                  //ƥ������
                            young[i]++;
                        else if ((30 <= client_info[k].age) && (client_info[k].age < 55))
                            mid[i]++;
                        else if (client_info[k].age >= 55)
                            old[i]++;

    printf("--------------------����ͳ��--------------------\n");
    printf("                ����\t����\t����\n");
    for (i = 0; i < gym_num; i++)                                                                     //��ӡ����ṹ
        printf("���ر��%s\t%d\t%d\t%d\n", gym_info[i].num, young[i], mid[i], old[i]);
    printf("------------------------------------------------\n");
}

int b_sort(float *temp, int *position, int gym_num)                                       //bubble sort
{
    int i, j;
    int now;
    float now1;

    for (j = 1; j <= gym_num - 1; j++)
        for (i = 0; i <= gym_num - j - 1; i++)
        {
            if (temp[i] <= temp[i + 1])
            {
                now1 = temp[i + 1];
                temp[i + 1] = temp[i];
                temp[i] = now1;
                now = position[i + 1];
                position[i + 1] = position[i];
                position[i] = now;
            }
        }
}

int ad_stat_money(int func_2, int gym_num, int order_num, int *ad_point)
{
    int i, j, k;
    int quan[gym_num], q[gym_num];                                 
    float money_gym[gym_num];
    float temp[gym_num], t[gym_num];
    float money;
    int position[gym_num], p[gym_num];

    for (i = 0; i < gym_num; i++)
    {
        quan[i] = 0;
        q[i] = 0;
        money_gym[i] = 0;
    }

    for (i = 0; i < gym_num; i++)
        for (j = 0; j < order_num; j++)
            if (strcmp(gym_info[i].num, order_info[j].gymnum) == 0)
                if (strncmp(admin_info[*ad_point].gymnasium, gym_info[i].num, 6) == 0)
                {
                    quan[i] += (order_info[j].over_time - order_info[j].begin_time);             //����������ʱ��
                    q[i]++;                           //�����ݶ�����
                }

    if (func_2 == 1)
    {
        for (i = 0; i < gym_num; i++)
            t[i] = (float)q[i];
        for (i = 0; i < gym_num; i++)
            p[i] = i;
        b_sort(t, p, gym_num);

        for (i = 0; i < gym_num; i++)
            if (t[i] == 0)
            {
                printf("���������ೡ�ض�����Ϊ�㣡\n");
                break;
            }
            else
                printf("����%s������%d\n", gym_info[p[i]].num, (int)t[i]);     // ������Ӫҵ��
        printf("---------------------------------------\n");
    }

    for (i = 0; i < gym_num; i++)
    {
        money_gym[i] = gym_info[i].rent*quan[i];
        money += money_gym[i];
    }
    if (func_2 == 2)
    {
        printf("---------------����Ӫҵ��--------------\n");           //��������Ӫҵ��
        printf("���������%s����\n", admin_info[*ad_point].gymnasium);
        printf("Ӫҵ�%.2fԪ��\n", money);
        printf("---------------------------------------\n");
    }

    else if (func_2 == 4)
    {
        printf("---------��Ӫҵ������(�ɴ�С)--------\n");    //������Ӫҵ������
        for (i = 0; i < gym_num; i++)
            temp[i] = money_gym[i];
        for (i = 0; i < gym_num; i++)
            position[i] = i;
        b_sort(temp, position, gym_num);

        for (i = 0; i < gym_num; i++)
            if (temp[i] == 0)
            {
                printf("���������ೡ��Ӫҵ��Ϊ�㣡\n");
                break;
            }
            else
                printf("����%sӪҵ��%.2fԪ\n", gym_info[position[i]].num, temp[i]);
        printf("---------------------------------------\n");
    }
}

int gymnasium_search(int *ad_point,int gym_num, int order_num)         //��ѯ������Ϣ 
{
    int i,j,k,time_now;
    for(i=0; i<gym_num; i++)                                 //��֤�ó����Ƿ����
    {
        if(strcmp(admin_info[i].gymnasium, admin_info[*ad_point].gymnasium)==0)
            k++;
    }
    if(k==0)                                                //��δ�ҵ�ƥ�䳡������ʾ���󱨸� 
    {
        printf("�ó��ݲ�����\n");                                 
        return 0;
    }
    for(i=0;i<gym_num;i++)                                  //չʾ�����������ص���Ϣ 
    {
        if(strcmp(admin_info[*ad_point].gymnasium,gym_info[i].belong_stadium)==0)
        {
            show_gym(i, order_num);
        } 
    } 
}

int gymnasium_add(int gym_num, int order_num, int *ad_point, int *p_gym_num)    //���һ���³��� 
{
    int j=gym_num;
    char type[len],introduction[len],num[len], zone[len];
    int permit_age_s,permit_age_l;
    float rent;
    printf("�����볡�ݱ��:\n");                                   //���ճ�����Ϣ 
    scanf("%s",num);
    printf("�����볡����������\n");
    scanf("%s", zone);
    printf("�����볡������:\n");
    scanf("%s",type);
    printf("�����볡�ؽ���:\n");
    scanf("%s",introduction); 
    printf("�����������������ޣ����޼����\n");
    scanf("%d%d%f",&permit_age_s,&permit_age_l,&rent);
    strcpy(gym_info[j].num,num);                                    //¼�볡����Ϣ 
    strcpy(gym_info[j].zone,zone);
    strcpy(gym_info[j].belong_stadium,admin_info[*ad_point].gymnasium);
    strcpy(gym_info[j].type,type);
    strcpy(gym_info[j].introdution,introduction);
    gym_info[j].permit_age[0]=permit_age_s;
    gym_info[j].permit_age[1]=permit_age_l;
    gym_info[j].rent=rent;
    show_gym(j, order_num);
    *p_gym_num=*p_gym_num+1;                                        //���ӳ������� 
    printf("�������\n");                                           //¼����� 
}


int modify(int *ad_point)                                           //�޸ĸ�����Ϣ 
{
    int i,j,judge;
    char ema[len],pas1[len],pas2[len],tel[len];
    printf("ѡ������Ҫ�޸ĵ���Ϣ:\n");
    printf("1.��������\n2.����\n3.�绰\n4.ȡ��\n");                   //ѡ��һ������޸�
    scanf("%d",&i);     
    if(i==1) 
    {
        printf("������������:\n");
        email_judge(ema);                                            //�޸����� 
        printf("�����޸ĳɹ�"); 
    }
    else if(i==2)
    {
        while(1)
        {
        printf("������������:\n");
        scanf("%s",pas1);
        printf("���ٴ�����������:\n");                              //ȷ�������� 
        scanf("%s",pas2);                                           //ȷ�����������Ƿ�һ�� 
            if(strcmp(pas1,pas2)!=0)
            {
                printf("�������벻ͬ ����������\n");
                
            }
            else
            {
                strcpy(admin_info[*ad_point].password,pas1);
                printf("�޸ĳɹ�\n");
                break;
            }
        }
    } 
    else if(i==3)                                                   //�޸ĵ绰 
    {
        do
        {
            judge=1;
            printf("�������µ绰����:\n");
            scanf("%s",tel);
            for(i=0;i<11;i++)
            {
                if(tel[i]=='\0')
                {
                    judge=0;
                    break;
                }
                if(((int)tel[i])<48||((int)tel[i])>57)
                {
                    judge=0;
                    printf("�绰���벻�Ϸ� ����������\n"); 
                    break;
                }
            }  
        }while(judge==0);
        strcpy(admin_info[*ad_point].tel, tel);
        printf("�޸����\n");
    }
    else if(i==4)                                                   //ȡ���޸� 
    {
        printf("�޸�ȡ��\n"); 
    }
    else                                                    
    {
        printf("��ѡ�����"); 
    }        
}

int aviliablity_sort(int *ad_point,int gym_num,int order_num)       //��ʱ��ζԳ��������ʽ������� 
{
    int number_ad[gym_num], temp[gym_num],alreadyshow[gym_num];
    int i, j, k, x, begin,judge;
    char gym[gym_num];
    k=0; 
    for(i=0; i<gym_num; i++)                                        //��֤�ó����Ƿ����
    {
        if(strcmp(admin_info[i].gymnasium, admin_info[*ad_point].gymnasium)==0)
            k++;
    }
    if(k==0)                                                         
    {
        printf("�ó��ݲ�����\n");                                 
        return 0;
    }   
    printf("ÿһСʱΪһ��ʱ���\n");                             
    printf("�����������ѯ����ʼʱ��(6-21):");                      //����Ա�������ѯ��ʱ��� 
    scanf("%d",&begin);
    if(begin<6||begin>21)
    {
        printf("��ʱ�β�����\n");
        return 0; 
    }
    for(i=0; i<gym_num; i++)                                        //�����ظ������ʼ��
    {
        alreadyshow[i]=-1;
        number_ad[i]=0;
    }
    for (i=0; i<gym_num; i++)                                       //����������صĶ�����    
    {
        for(j=0; j<gym_num; j++)                                    //ͨ������gym_info�ṹ�����飬�����ض�ʱ����ڵ������ص�Ԥ����� 
            if(strcmp(order_info[j].gymnum, gym_info[i].num)==0
            &&order_info[j].begin_time<begin
            &&order_info[j].over_time<(begin+1)
            &&order_info[j].sign==1)
                number_ad[i]++;
            else if(strcmp(order_info[j].gymnum, gym_info[i].num)==0&&
            order_info[j].begin_time<(begin+1)
            &&order_info[j].sign==1)
                number_ad[i]++;
            else if(strcmp(order_info[j].gymnum, gym_info[i].num)==0&&
            order_info[j].begin_time>begin
            && order_info[j].over_time<(begin+1)
            &&order_info[j].sign==1)
                number_ad[i]++;          
    }
    
    for(i=0; i<gym_num; i++)                                        //����ʱ����ڸ������صĶ�������ֵ��һ���ɹ����������
    {
        temp[i]=number_ad[i];
    }
    qsort(temp, gym_num, sizeof(int), int_cmp);                     //���ɹ�����������������

    j=0;
    k=0;
    for(i=0; i<gym_num; i++)                                        //�����Ѿ�����������飬�ӵ�һλ���ӳ�����Ѱ�Ҷ�Ӧ�ĳ���
    {
        judge=1;                                                    //���ں����forѭ���޷��жϵ�һ��λ���Ƿ��ظ�����ѭ������ȷ����һ��λ���Ƿ��ظ� 
        for(x=0; x<k; x++)
            if(alreadyshow[x]==0)
                judge=0;
        while(number_ad[j]!=temp[i]||judge==0)                      //Ѱ�Ҹö���������Ӧ�ĳ���
        {
            j++;
                
            judge=1;                                                //�����Ƿ��ظ�
            for(x=0; x<k; x++)  
                if(alreadyshow[x]==j)
                    judge=0;            
        }
        if(strcmp(gym_info[j].belong_stadium,admin_info[*ad_point].gymnasium)==0)
            show_gym(j,order_num);                                            //���ҵ��ĳ������
        alreadyshow[k]=j;                                           //���Ѿ�����ĳ��ص�λ�ø�ֵ�������ظ�����
        k++;
        j=0;
    }
}


int save(int client_num, int admin_num, int gym_num, int order_num)
{
    int i;
    FILE *fp_client;             //�����ĸ��ṹ������Ӧ���ĸ�txt���ļ�ָ��
    FILE *fp_admin;
    FILE *fp_gym;
    FILE *fp_order;

    if((fp_client=fopen("client.txt", "wb"))==NULL)     //�ж��Ƿ���Դ��ļ�
    {
        printf("Cannot open client file\n");
        exit(0);
    }
    for(i=0; i<client_num; i++)             //���ṹ���е�����д�뵽�ļ���
    {
        fwrite(&client_info[i], sizeof(struct client), 1, fp_client);
    }
    fclose(fp_client);

    if((fp_admin=fopen("admin.txt", "wb"))==NULL)       //�ж��Ƿ���Դ��ļ�
    {
        printf("Cannot open admin file\n");
        exit(0);
    }
    for(i=0; i<admin_num; i++)              //���ṹ���е�����д�뵽�ļ���
    {
        fwrite(&admin_info[i], sizeof(struct admin), 1, fp_admin);
    }
    fclose(fp_admin);

    if((fp_gym=fopen("gym.txt", "wb"))==NULL)       //�ж��Ƿ���Դ��ļ�
    {
        printf("Cannot open gym file\n");
        exit(0);
    }
    for(i=0; i<gym_num; i++)                //���ṹ���е�����д�뵽�ļ���
    {
        fwrite(&gym_info[i], sizeof(struct gym), 1, fp_gym);
    }
    fclose(fp_gym);

    if((fp_order=fopen("order.txt", "wb"))==NULL)       //�ж��Ƿ���Դ��ļ�
    {
        printf("Cannot open order file\n");
        exit(0);
    }
    for(i=0; i<order_num; i++)              //���ṹ���е�����д�뵽�ļ���
    {
        fwrite(&order_info[i], sizeof(struct order), 1, fp_order);
    }
    fclose(fp_order);
}      

int main()
{
    int client_num, admin_num, gym_num, order_num;      //�����ĸ��ṹ�������ʵ����Ч����
    int *p_client_num, *p_admin_num, *p_gym_num, *p_order_num;          //�����ĸ��ṹ�������ʵ����Ч���ȵ�ָ��
    int pointer, ca;     //�����¼�������ص��û��ڽṹ�������λ�ú��û�������
    int *p_pointer, *p_ca;           //�����¼�������ص��û��ڽṹ�������λ�ú��û������͵�ָ��
    int func_2, n;
    char func[2];
    int con1=1,con2=1;

    p_pointer=&pointer;     //ȡ��ַ
    p_ca=&ca;

    p_client_num = &client_num;     //ȡ��ַ
    p_admin_num = &admin_num;
    p_gym_num = &gym_num;
    p_order_num = &order_num;

    initialize(p_client_num, p_admin_num, p_gym_num, p_order_num);      //���ú����Գ����ʼ�������ļ��е����ݶ��뵽�ڴ���
    
    /*ѡ���Կͻ������Ա���������ϵͳ */
    while(con1)
    {
        print1();
        char visitor[len];
        scanf("%s",visitor);
        
        if(visitor[0]=='0' && visitor[1]=='\0')
        {
            getchar();
            system ("cls");
            login_ad(p_pointer,p_ca);
            con1=0;
        }   
        if(visitor[0]=='1' && visitor[1]=='\0')
        {
        /*�ͻ�ѡ��ע����½*/ 
            getchar();
            system ("cls");
            while(con2)
            {
                print2();
                char settle[len];
                scanf("%s",settle);
                if(settle[0]=='1' && settle[1]=='\0')
                {
                    getchar();
                    system ("cls");
                    regist(p_client_num);
                    login_cl(p_pointer,p_ca);//ע����ת����¼����
                    con2=0;                                 
                    con1=0;
                }
                if(settle[0]=='0' && settle[1]=='\0')
                {
                    getchar();
                    system ("cls");
                    login_cl(p_pointer,p_ca);
                    con2=0;
                    con1=0; 
                }
                    
                else
                {
                    getchar();
                    system("cls");
                    printf("������0��1!\n");
                }
            }
        } 
        else
        {    
            getchar();
            system("cls");
            printf("������0��1!\n");                    
        }
    }
    
    
    if(ca==1)
    {
        do
        { 
            system("cls");
            printf("�𾴵�%s�˿ͣ����ã�\n",client_info[pointer].name);
            printf("---------------------�˿�ϵͳ-------------------\n");       //��ӡ�б�
            printf("����������ѡ��Ĺ���\n");
            printf("1.��ѯ����\n");
            printf("2.Ԥ������\n");
            printf("3.�޸ĸ�����Ϣ\n");
            printf("4.ɾ������\n");
            printf("5.��ѯ����\n");
            printf("6.�˳�����\n");
            printf("------------------------------------------------\n");
            printf("�����룺");
            scanf("%s", func);
            system("cls");
            switch(func[0])
            {
                case '1':
                    client_search(pointer, gym_num, order_num, p_order_num);        //��ѯ����
                    break;
                case '2':
                    client_reserve(p_order_num, pointer, gym_num);      //Ԥ������
                    break;
                case '3':
                    change_info(pointer);//�޸ĸ�����Ϣ
                    break;
                case '4':
                    delete_info(client_info[pointer].id, p_order_num);//ɾ������
                    break;
                case '5':
                    query_info(client_info[pointer].id, p_order_num);//��ѯ����
                    system("pause");
                    break;
                case '6':       //�˳�����
                    break;
                default:
                    printf("�������������������롣\n");       //���û����������ʾ�û���������
                    system("pause");
                    break;
            }
            save(client_num, admin_num, gym_num, order_num);        //���޸ĺ�����ݸ��ǵ�ԭ�ļ���
        }while(func[0]!='6');
    }

    if(ca==0)
    {
        system("cls");
        do
        {

            ad_menu1();
            scanf("%s", &func);
            system("cls");
            switch (func[0])
            {
                case '1':
                    ad_check(p_pointer, order_num);
                    system("pause");
                    system("cls");
                    break;

                case '2':
                    ad_menu2();
                    scanf("%d", &func_2);
                    switch (func_2)
                    {
                    case 1:
                        ad_stat_money(func_2,gym_num,order_num,p_pointer);
                        system("pause");
                        system("cls");
                        break;
                    case 2:
                        ad_stat_money(func_2, gym_num, order_num, p_pointer);
                        system("pause");
                        system("cls");
                        break;
                    case 3:
                        ad_stat_age(gym_num, client_num, order_num);
                        system("pause");
                        system("cls");
                        break;
                    case 4:
                        ad_stat_money(func_2, gym_num, order_num, p_pointer);
                        system("pause");
                        system("cls");
                        break;
                    case 5:
                        ad_stat_gender(gym_num, client_num, order_num);
                        system("pause");
                        system("cls");
                        break;
                    case 6:
                        aviliablity_sort(p_pointer,gym_num,order_num);
                        system("pause");
                        system("cls");
                        break;
                    default:
                        printf("������������������\n"); 
                        system("pause");
                        system("cls");
                        break;
                    }
                    break;
                case '3':
                    gymnasium_search(p_pointer,gym_num,order_num);
                    system("pause");
                    system("cls");
                    break;
                case '4':
                    gymnasium_add(gym_num, order_num, p_pointer, p_gym_num);
                    system("pause");
                    system("cls");
                    break;
                case '5':
                    modify(p_pointer);
                    system("pause");
                    system("cls");
                    break;
                case '6':       //�˳�����
                    break;
                default:
                    printf("������������������\n");         //���û����������ʾ�û���������
                    system("pause");
                    system("cls");
                    break;
            }
            save(client_num, admin_num, gym_num, order_num);            //���޸ĺ�����ݸ��ǵ�ԭ�ļ���
        }while (func[0]!='6');
    }
    save(client_num, admin_num, gym_num, order_num);            //���޸ĺ�����ݸ��ǵ�ԭ�ļ���

    return 0;
}
