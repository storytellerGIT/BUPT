/*名称：综合体育场馆管理系统
  完成日期：2018年9月19日
  作者：郑云帆、李广亮、杜宇昂、臧乾博、郭子裕
  相关文件：client.txt admin.txt gym.txt order.txt四个文件应与程序放在同一目录下*/
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<math.h>
#define len 100

//定义顾客结构体数组
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


//定义管理员结构体数组
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

//定义场地结构体数组
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

//定义订单结构体数组
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

void initialize(int *p_client_num, int *p_admin_num, int *p_gym_num, int *p_order_num)     //四个整形指针分别代表四个结构体的有效长度
{
    int i;
    FILE *fp_client;             //定义四个结构体所对应的四个txt的文件指针
    FILE *fp_admin;
    FILE *fp_gym;
    FILE *fp_order;

    if((fp_client=fopen("client.txt", "rb"))==NULL)                 //判断文件是否可以打开
    {
        printf("Cannot open client file\n");
        exit(0);
        system("pause");
    }
    *p_client_num=0;
    for (i = 0; feof(fp_client)==0; i++)
    {
        fread(&client_info[i], sizeof(struct client), 1, fp_client);//将文件中的数据读入结构体
        *p_client_num=*p_client_num+1;
    }
    *p_client_num=*p_client_num-1;      //上面循环结束后，指针数值会多一个，通过自减来恢复正常

    if((fp_admin=fopen("admin.txt", "rb"))==NULL)                   //判断文件是否可以打开
    {
        printf("Cannot open admin file\n");                         
        exit(0);
        system("pause");
    }
   *p_admin_num=0;
    for (i = 0; feof(fp_admin)==0; i++)
    {
        fread(&admin_info[i], sizeof(struct admin), 1, fp_admin);//将文件中的数据读入结构体
        *p_admin_num=*p_admin_num+1;
    }
    *p_admin_num=*p_admin_num-1;        //上面循环结束后，指针数值会多一个，通过自减来恢复正常

    if((fp_gym=fopen("gym.txt", "rb"))==NULL)                       //判断文件是否可以打开
    {
        printf("Cannot open gym file\n");
        exit(0);
        system("pause");
    }
    *p_gym_num=0;
    for (i = 0; feof(fp_gym)==0; i++)
    {
        fread(&gym_info[i], sizeof(struct gym), 1, fp_gym);//将文件中的数据读入结构体
        *p_gym_num=*p_gym_num+1;
    }
    *p_gym_num=*p_gym_num-1;        //上面循环结束后，指针数值会多一个，通过自减来恢复正常

    if((fp_order=fopen("order.txt", "rb"))==NULL)                   //判断文件是否可以打开
    {
        printf("Cannot open order file\n");
        exit(0);
        system("pause");
    }
    *p_order_num=0;
    for (i = 0; feof(fp_order)==0; i++)
    {
        fread(&order_info[i], sizeof(struct order), 1, fp_order);//将文件中的数据读入结构体
        *p_order_num=*p_order_num+1;
    }
    *p_order_num=*p_order_num-1;        //上面循环结束后，指针数值会多一个，通过自减来恢复正常
}

unsigned long long computer_time()//需要头文件"<stdio.h>"和"<time.h>"，返回一个形如yyyymmddhhmm的整形数表示时间
{
    time_t tmpcal_ptr;//储存time_t类型秒数的值
    struct tm *tmp_ptr = NULL;//储存struct tm类型结构的指针
    unsigned long long ans;//返回值

    time(&tmpcal_ptr);//获取utc时间到当前时刻的秒数
    tmp_ptr = gmtime(&tmpcal_ptr);//将所得时间转化为一个结构体
    tmp_ptr = localtime(&tmpcal_ptr);//将所得时间转化为本地时间
    ans =  (tmp_ptr->tm_hour + 100 * (tmp_ptr->tm_mday + 100 * ((1 + tmp_ptr->tm_mon) + 100 * (1900 + tmp_ptr->tm_year))));
    ans *= 100;
    ans += tmp_ptr->tm_min;

    return (ans);
}

//检查邮箱地址合法性
int email_judge(char *email)
{
    int i, j, judge, judge_final;

    do
    {
        judge_final=1;

        printf("您邮箱的地址：");		//输入邮箱
        scanf("%s", email);

        if(email[1]=='\0')		//判断email是否只有一个字符
        {
        	judge_final=0;
        }
        judge=0;
        for(i=1; i<20&&email[i]!='\0'; i++)		//判断是否有@
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

        if(email[i+1]=='\0')		//判断@之后是否结束
        {
        	judge_final=0;
        }

        judge=0;
        for(i=i+2; i<40&&email[i]!='\0'; i++)		//判断@之后是否有.  i=i+2用来判断是否@和.之间有字符
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
        if(email[i+1]!='\0')		//判断.后是否有字符
            judge=1;
        if(judge==0)
        {
            judge_final=0;
        }

        if(judge_final==0)
            printf("您输入的邮箱格式错误，请重新输入\n");
    }while(judge_final==0);
}

//客户或管理员选择界面
void print1()
{
    printf("   _______________________________________\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |        管理员访问——请按 0          |\n");
    printf("   |                                      |\n");
    printf("   |         客户访问——请按 1           |\n");
    printf("   |                                      |\n");
    printf("   |______________________________________|\n");
     printf("请输入");
}

//登录或注册选择
void print2() 
{
    printf("   _______________________________________\n");
    printf("   |                                      |\n");
    printf("   |                                      |\n");
    printf("   |         我已注册过——请按 0         |\n");
    printf("   |                                      |\n");
    printf("   |         我是新用户——请按 1         |\n");
    printf("   |                                      |\n");
    printf("   |______________________________________|\n");
     printf("请输入");
}

//明文密码变隐藏字符密码输入函数
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

//管理员登陆界面
void login_ad(int *p_pointer, int *p_a)
{
    char ad_id[11];
    char ad_pass[len];
    int i=0,ok=0;

    printf("请登录\n");
    printf("请输入账号:");
    scanf("%s",ad_id);
    for(i=0;i<len;i++)		//判断账号密码是否正确
    {
        while((strcmp(ad_id, admin_info[i].id)==0))
        {
            printf("请输入密码:");
            passwd_scan(ad_pass);
            if(strcmp(ad_pass, admin_info[i].password)==0)
            {
                ok=1;
                break; 
            }
            else
            {
                printf("密码错误,请重试！");
                getchar();
                getchar();
                system ("cls");
                printf("账号:%s\n",ad_id);
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
        printf("登陆成功，欢迎您！");
        *p_pointer=i;
        *p_a=0;  
        getchar();
        getchar();
    }
    if(!ok)
    {
        printf("登录失败，请重试。");
        login_ad(p_pointer, p_a);
    }
    
}

//客户登陆界面
void login_cl(int *p_pointer, int *p_a)
{
    char cl_id[11];
    char cl_pass[len];
    int i=0,ok=0;

    printf("请登录\n");
    printf("请输入账号:");
    scanf("%s",cl_id);
    for(i=0;i<len;i++)		//判断账号密码是否正确
    {
        while((strcmp(cl_id, client_info[i].id)==0))
        {
            printf("请输入密码:");
            passwd_scan(cl_pass);
            if(strcmp(cl_pass, client_info[i].password)==0)
            {
                ok=1;
                break; 
            }
            else
            {
                printf("密码错误,请重试！");
                getchar();
                getchar();
                system ("cls");
                printf("账号:%s\n",cl_id);
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
        printf("登陆成功，欢迎您！");
        *p_pointer=i;
        *p_a=1;  
        getchar();
        getchar();
    }
    if(!ok)
    {
        printf("登录失败，请重试。");
        login_cl(p_pointer, p_a);
    }
    
}

//客户注册界面
void regist(int* p_client_num)
{
    char id_check[len];
    char tel_check[len];
    int i=0,j=0;
    
    while(i>=0)
    {
        printf("请输入注册信息。\n");
        printf("账号ID:"); 
        scanf("%s",id_check);
        while(id_check[i] != '\0')		//判断输入的账号是否符合要求
        {
            i++;
        }
        if( i<6 || i>10 )			
        {
            printf("账号不符合要求，请按任意键后重新输入。\n"); 
            getch();
            system("cls");
            i=0;
        }
        if( i>=6 && i<=10 )
        {
            printf("账号符合要求，请继续输入。\n");
            break;
        }
    }
    strcpy(client_info[*p_client_num].id,id_check);
    
    printf("姓名:");
    scanf("%s",client_info[*p_client_num].name);
    
    printf("性别（男/女）:");
    scanf("%s",client_info[*p_client_num].gender);
    
    while(j>=0)
    {
        printf("联系电话(11位):"); 
        scanf("%s",tel_check);
        while(tel_check[j] != '\0')		//判断输入的电话号码是否符合要求 
        {
            j++;
        }
        if(j!=11)
        {
            printf("电话号码不符合要求，请按任意键后重新输入。\n"); 
            getch();
            j=0;
        }
        if(j==11)
        {
            printf("账号符合要求，请继续输入。\n");
            break;
        }
    }
    strcpy(client_info[*p_client_num].tel,tel_check);
    
    printf("密码:");
    passwd_scan(client_info[*p_client_num].password);
    printf("请确认密码:%s\n",client_info[*p_client_num].password);
    
    printf("电子邮箱:\n");
    email_judge(client_info[*p_client_num].email);
    
    printf("住址:");
    scanf("%s",client_info[*p_client_num].zone);
    
    *p_client_num=*p_client_num+1;			//将有效长度加以扩展
}

int client_search(int id, int gym_num, int order_num, int *p_order_num)
{   
    char opera[len];
    int reserve;        //定义是否调用预定函数的操作数
    int i;
    char func[2];
    int show=0;

    printf("您想查询的方式：\n");       //打印选择列表
    printf("1.依据场地名称\n");
    printf("2.依据场馆名称\n");
    printf("3.依据所属区域\n");
    printf("4.依据是否有空余场地\n");
    printf("5.依据租金排序\n");
    printf("6.依据预定量排序\n");
    printf("7.热门推荐\n");
    printf("请选择您想要的方式：");
    scanf("%s",func);       //选择操作内容，容错

    system("cls");
    switch(func[0])                //让顾客选择查询方式
    {
        case '1':
            printf("1.依据场地名称\n");
            printf("名称：");
            scanf("%s",&opera);
            for (i = 0; i < gym_num; ++i)       //遍历gym结构体，寻找场地
            {
                if(strcmp(opera, gym_info[i].num)==0)
                {
                    show_gym(i, order_num);
                    show=1;
                }
            }
            if(show==0)         //如未从结构体中找到，提示用户
            {
                printf("未找到该场地。\n");
                getch();
                break;
            }
            printf("您是否想继续预定场地？是请输入1，否请输入0。\n");
            scanf("%d",&reserve);
            if(reserve==1)      //让用户选择查询后是否继续预定场地
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '2':
        printf("2.依据场馆名称\n");
            printf("名称：");
            scanf("%s",&opera);
            for (i = 0; i < gym_num; ++i)       //遍历gym结构体，寻找场馆
            {
                if(strcmp(opera, gym_info[i].belong_stadium)==0)
                {
                    show_gym(i, order_num);
                    show=1;
                }                    
            }
            if(show==0)         //如未从结构体中找到，提示用户
            {
                printf("未找到该场馆。\n");
                getch();
                break;
            }
            printf("您是否想继续预定场地？是请输入1，否请输入0。\n");
            scanf("%d",&reserve);
            if(reserve==1)      //让用户选择查询后是否继续预定场地
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '3':
            printf("3.所属区域\n");
            printf("区域：");
            scanf("%s",&opera);
            for (i = 0; i < gym_num; ++i)       //遍历gym结构体，寻找区域
            {
                if(strcmp(opera, gym_info[i].zone)==0)
                {
                    show_gym(i, order_num);
                    show=1;
                }                    
            }
            if(show==0)         //如未从结构体中找到，提示用户
            {
                printf("未找到该区域。\n");
                getch();
                break;
            }
            printf("您是否想继续预定场地？是请输入1，否请输入0。\n");
            scanf("%d",&reserve);
            if(reserve==1)      //让用户选择查询后是否继续预定场地
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '4':
            printf("4.依据是否有空余场地\n");
            avail_gym_search(gym_num, order_num);       //调用函数
            printf("您是否想继续预定场地？是请输入1，否请输入0。\n");
            scanf("%d",&reserve);
            if(reserve==1)      //让用户选择查询后是否继续预定场地
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '5':
            printf("5.依据租金排序\n");
            rent_sort(gym_num, order_num);      //调用函数
            printf("您是否想继续预定场地？是请输入1，否请输入0。\n");
            scanf("%d",&reserve);
            if(reserve==1)      //让用户选择查询后是否继续预定场地
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '6':
            printf("6.依据预定量排序\n");
            order_sort(gym_num, order_num);     //调用函数
            printf("您是否想继续预定场地？是请输入1，否请输入0。\n");
            scanf("%d",&reserve);
            if(reserve==1)      //让用户选择查询后是否继续预定场地
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        case '7':
            printf("7.热门推荐\n");
            gym_recommend(gym_num, order_num, id);      //调用函数
            printf("您是否想继续预定场地？是请输入1，否请输入0。\n");
            scanf("%d",&reserve);
            if(reserve==1)      //让用户选择查询后是否继续预定场地
            {
                client_reserve(p_order_num, id, gym_num);
            }
            break;
        default:
            printf("您输入有误。\n");     //容错，防止顾客输入错误
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

    printf("场地编号：%s\n",gym_info[i].num);
    printf("所属地区：%s\n",gym_info[i].zone);
    printf("所属场馆：%s\n",gym_info[i].belong_stadium);
    printf("场地类别：%s\n",gym_info[i].type);
    printf("场地简介：%s\n",gym_info[i].introdution);
    printf("准入年龄：%d-%d\n",gym_info[i].permit_age[0], gym_info[i].permit_age[1]);
    printf("租金:%.2f\n",gym_info[i].rent);
    printf("场地未来预约情况：\n");
    time_now = computer_time();             //获取计算机本地时间
    time_now = time_now/10000;
    for(j=0; j<order_num; j++)              //遍历order结构体，寻找未来的订单
    {
        if(strcmp(order_info[j].gymnum, gym_info[i].num)==0)
            if(order_info[j].rent_date>=(int)time_now)
            {
                printf("%d年%d月%d日%d时——",order_info[j].rent_date/10000, order_info[j].rent_date/100%100, order_info[j].rent_date%100, order_info[j].begin_time);
                printf("%d年%d月%d日%d时\n",order_info[j].rent_date/10000, order_info[j].rent_date/100%100, order_info[j].rent_date%100, order_info[j].over_time);
                alreadyshow++;
            }   
    }
    if(alreadyshow==0)          //如未找到订单，则提示用户
    {
        printf("当前暂无未来的预约\n");
    }
    printf("\n");
    printf("\n");
}

//浮点型qsort所需函数, 从小到大
int float_cmp(const void *a, const void *b)       
{
     return (*(float *)a-*(float *)b);
}

//整形qsort所需函数,从大到小
int int_cmp(const void *a, const void *b)
{
     return (*(int *)b-*(int *)a);
}

int rent_sort(int gym_num, int order_num)
{
    int i, j, k, x, judge;
    float rent[gym_num];
    float alreadyshow[gym_num];
    printf("各场馆按租金从小到大排序：\n\n");

    for(i=0; i<gym_num; i++)                                    //检验重复数组初始化
        alreadyshow[i]=-1;

    for(i=0; i<gym_num; i++)                                    //将所有场地的租金赋值到一个可供排序的浮点型数组中
    {
        rent[i]=gym_info[i].rent;
    }
    qsort(rent, gym_num, sizeof(float), float_cmp);             //将可供排序的数组进行排序
    
    j=0;
    k=0;
    for(i=0; i<gym_num; i++)                                    //按着已经排序过的数组，从第一位，从场地中寻找对应的场地
    {
        judge=1;                                                
        for(x=0; x<k; x++)                                      //由于后面的for循环无法判断第一个位置是否重复，次循环用于确定第一个位置是否重复 
            if(alreadyshow[x]==0)
                judge=0;
        while(rent[i]!=gym_info[j].rent || judge==0)              //寻找该租金所对应的场地
        {
            j++;
                
            judge=1;                                            //检验是否重复
            for(x=0; x<k; x++)                                  
                if(alreadyshow[x]==j)
                    judge=0;
        }
        show_gym(j, order_num);                                 //将找到的场地输出
        alreadyshow[k]=j;                                       //将已经输出的场地的位置赋值给检验重复数组
        k++;
        j=0;
    }
}

int order_sort(int gym_num, int order_num)
{
    int number[gym_num], temp[gym_num], alreadyshow[gym_num];
    int i, j, k, x, judge;
    printf("各场地按（历史所有）订单量从大到小排序:\n\n");

    for(i=0; i<gym_num; i++)                                        //检验重复数组初始化
    {
        alreadyshow[i]=-1;
        number[i]=0;
    }
        
    for (i=0; i<gym_num; i++)                                       //计算各个场地的订单量    
    {
        for(j=0; j<order_num; j++)                                  //通过遍历order_info结构体数组，计算单个场地的订单量
            if(strcmp(order_info[j].gymnum, gym_info[i].num)==0)
                number[i]++;
    }
    
    for(i=0; i<gym_num; i++)                                        //将各个场地的订单量赋值到一个可供排序的整形数组
    {
        temp[i]=number[i];
    }
    qsort(temp, gym_num, sizeof(int), int_cmp);                     //将可供排序的数组进行排序
    
    j=-1;
    k=0;
    for(i=0; i<gym_num; i++)                                        //按着已经排序过的数组，从第一位，从场地中寻找对应的场地
    {
        judge=1;                                        //由于后面的for循环无法判断第一个位置是否重复，此循环用于确定第一个位置是否重复 
        for(x=0; x<k; x++)
            if(alreadyshow[x]==0)
                judge=0;
        while(number[j]!=temp[i]||judge==0)                   //寻找该订单量所对应的场地
        {
            j++;
                
            judge=1;                                            //检验是否重复
            for(x=0; x<k; x++)  
                if(alreadyshow[x]==j)
                    judge=0;            
        }
        
        show_gym(j, order_num);                                                //将找到的场地输出
        alreadyshow[k]=j;                                           //将已经输出的场地的位置赋值给检验重复数组
        k++;
        j=0;
    }
}

int client_reserve(int *p_order_num, int id, int gym_num)
{
    int number, position, rent_begin_time, rent_over_time;
    int condition_age, condition_time;                              //判断正确的操作数
    int i, j, k, temp_begin;
    float allrent=0;
    int show, c_judge, c_time_judge;
    char c_number[2], c_rent_date[9], c_begin_time[3], c_over_time[3];

    if(client_info[id].sign>3)                                   //判断该顾客爽约次数是否过多
        printf("您爽约次数已经超过3次，并不能再次预定。\n");
    else
    {
        do
        {
            c_judge=1;
            printf("您想预订几个场地：");            //获取该次订单数量
            scanf("%s",c_number);
            if(((int)c_number[0])<48 ||((int)c_number[0])>57)       //判断输入格式是否合法
            {
                c_judge=0;
                printf("输入有误，请重新输入。\n");
            }
        }while(c_judge==0);
        number=(int)c_number[0]-48;     //将输入的字符型转换为整形

        for(i=0; i<number; i++)
        {
            strcpy(order_info[*p_order_num].user_id, client_info[id].id);               //对order_info结构体的部分信息进行赋值
            order_info[*p_order_num].reserve_date = computer_time();
            condition_age=1;    //初始化判断的判断数年龄是否合适的操作数
            do                                                  
            {
                do
                {
                    show=0;
                    printf("请输入您想要预订的场地名：\n");
                    scanf("%s",order_info[*p_order_num].gymnum);
                    for(j=0; j<gym_num; j++)                                    //获取顾客输入的场地所在gym_info结构体数组中的位置
                    {
                        if(strcmp(order_info[*p_order_num].gymnum, gym_info[j].num)==0)
                        {
                            position=j;
                            show=1;
                            break;
                        }
                    }
                    if(show==0)     //如结构体中没有该场地，提示用户重新输入
                    {
                        printf("未找到该场地，请重新输入。\n");
                    }
                }while(show==0);
                if(client_info[id].age<gym_info[position].permit_age[0]||client_info[id].age>gym_info[position].permit_age[1])  //判断该顾客的年龄是否适合该场地
                {
                    condition_age=0;
                    printf("您的年龄不适合此场地的运动项目，请重试。\n");
                }
            }while(condition_age==0);
            
            
            do
            {
            condition_time=1;   //初始化判断时间是否冲突的操作数
                do
                {
                    c_judge=1;
                    printf("请输入您想租用的日期（示例：如果您租用日期为2018年9月12日，请输入20180912）：\n");     //获取客户搜索时间段
                    scanf("%s", c_rent_date);
                    for(k=0; k<8; k++)
                    {
                        if(((int)c_rent_date[k])>57 || ((int)c_rent_date[k])<48)        //判断用户输入时间格式是否正确
                        {
                            c_judge=0;
                            printf("格式错误，请重新输入。\n");        //如果输入错误，提示用户重新输入
                            break;
                        }
                    }
                }while(c_judge==0);
                order_info[*p_order_num].rent_date=0;
                for(k=0; k<8; k++)      //将用户输入的数据转化为整形并赋值给order_info[*p_order_num].rent_date
                {
                    order_info[*p_order_num].rent_date=order_info[*p_order_num].rent_date+((int)(c_rent_date[k])-48)*(int)pow(10,7-k);
                }

                do
                {
                    c_time_judge=1;
                    do
                    {
                        c_judge=1;
                        printf("请输入您想租用的具体起始时间,请以整点开始,场地开放时间为6点至22点（示例：如果您租用的具体起始时间为9点，请输入9）：\n");
                        scanf("%s", c_begin_time);
                        for(k=0; k<2; k++)      //判断用户输入时间格式是否正确
                        {
                            if(c_begin_time[k]=='\0')
                                break;
                            if(((int)c_begin_time[k])>57 || ((int)c_begin_time[k])<48 )     //如输入错误，提示用户重新输入
                            {
                                c_judge=0;
                                printf("格式错误，请重新输入。\n");
                                break;
                            }
                        }
                    }while(c_judge==0);
                    order_info[*p_order_num].begin_time=0;
                    if(c_begin_time[1]=='\0')                   //将用户输入的时间转化为整形，并赋值给结构体
                        order_info[*p_order_num].begin_time=(int)c_begin_time[0]-48;
                    else
                        order_info[*p_order_num].begin_time=((int)c_begin_time[0]-48)*10+(int)c_begin_time[1]-48;

                    if(order_info[*p_order_num].begin_time<6 || order_info[*p_order_num].begin_time>21)     //判断用户选择的时间时候在开放时间内
                    {
                        printf("您选择的时间未在开放时间内。\n");
                        c_time_judge=0;
                    }
                }while(c_time_judge==0);

                do
                {
                    c_time_judge=1;
                    do
                    {
                        c_judge=1;
                        printf("请输入您想租用的具体结束时间,请以整点结束,场地开放时间为6点至22点（示例：如果您租用的具体结束时间为10点，请输入10）：\n");
                        scanf("%s", c_over_time);
                        for(k=0; k<2; k++)      //判断用户输入时间格式是否正确
                        {
                            if(c_over_time[k]=='\0')
                                break;
                            if(((int)c_over_time[k])>57 || ((int)c_over_time[k])<48 )       //如输入错误，提示用户重新输入
                            {
                                c_judge=0;
                                printf("格式错误，请重新输入。\n");
                                break;
                            }
                        }
                    }while(c_judge==0);
                    order_info[*p_order_num].over_time=0;
                    if(c_over_time[1]=='\0')                    //将用户输入的时间转化为整形，并赋值给结构体
                        order_info[*p_order_num].over_time=(int)c_over_time[0]-48;
                    else
                        order_info[*p_order_num].over_time=((int)c_over_time[0]-48)*10+(int)c_over_time[1]-48;
                    if(order_info[*p_order_num].over_time<=order_info[*p_order_num].begin_time || order_info[*p_order_num].over_time>22)        //判断用户输入的时间是否符合要求
                    {
                        printf("您选择的结束时间有误，请重新输入。\n");
                        c_time_judge=0;
                    }
                }while(c_time_judge==0);
                
                rent_begin_time=order_info[*p_order_num].rent_date*100+order_info[*p_order_num].begin_time/100;     //对结构体进行赋值
                rent_over_time=order_info[*p_order_num].rent_date*100+order_info[*p_order_num].over_time/100;
                for(j=0; j<*p_order_num; j++)                       //判断用户选择的时间是否和已有订单有冲突
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
                    printf("您所选择的时间有冲突，请重新选择。\n");      //如用冲突，提示用户重新输入
            }while(condition_time==0);

            allrent=allrent+gym_info[position].rent*((float)order_info[*p_order_num].over_time - (float)order_info[*p_order_num].begin_time);       //计算总金额
            *p_order_num=*p_order_num+1;
        }
        if(allrent > client_info[id].account)               //判断账户余额是否足够
        {
            printf("您的账户余额不足以支付此次预定的总金额，本次操作失败。\n");
            getch();
            *p_order_num=*p_order_num - number;                 //失败后将order_info的有效长度退回到预定前
        }
        else
        {
        	printf("预定成功。\n");
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
        printf("您想查询哪天内有空余时间的场地:（示例：如果您想查询2018年9月13号有空余时间的场地，请输入20180913\n");     //获取客户搜索时间段
        scanf("%s", c_day_num);
        for(i=0; i<8; i++)          //判断用户输入时间时候符合要求
        {
            if(((int)c_day_num[i])>57 || ((int)c_day_num[i])<48)
            {
                c_judge=0;
                printf("格式错误，请重新输入。\n");            //如输入有误，提示用户重新输入
                break;
            }
        }
    }while(c_judge==0);
    day_num=0;
    for(i=0; i<8; i++)          //将用户输入的时间转化为整形
    {
        day_num=day_num+((int)(c_day_num[i])-48)*(int)pow(10,7-i);
    }

    do
    {
        c_judge=1;
        printf("您想查询从什么时候有空余的时间：（示例：如果您想查询从10点开始的空余时间，请输入10\n");
        scanf("%s", c_begin_hours);
        for(i=0; i<2; i++)
        {
            if(c_begin_hours[i]=='\0')
                break;
            if(((int)c_begin_hours[i])>57 || ((int)c_begin_hours[i])<48 )       //判断用户输入的时间是否符合要求
            {
                c_judge=0;
                printf("格式错误，请重新输入。\n");            //如输入有误，提示用户重新输入
                break;
            }
        }
        if(c_judge==1)
        {
        	begin_hours=0;
        	if(c_begin_hours[1]=='\0')      //将用户输入的时间转化为整形
	            begin_hours=(int)c_begin_hours[0]-48;
	        else
	            begin_hours=((int)c_begin_hours[0]-48)*10+(int)c_begin_hours[1]-48;

	        if(begin_hours<6 || begin_hours>21)
	        {
	            printf("您选择的时间未在开放时间内。请重新选择。\n");
	            c_judge=0;
	        }
        }
    }while(c_judge==0);
    

    do
    {
        c_judge=1;
        printf("您想查询有空余时间截止至什么时候：（示例：如果您想查询从xx点到12点的空余时间，请输入12\n");
        scanf("%s", c_over_hours);
        for(i=0; i<2||c_over_hours[i]=='\0'; i++)               
        {
            if(c_over_hours[i]=='\0')
                break;
            if(((int)c_over_hours[i])>57 || ((int)c_over_hours[i])<48)              //判断用户输入的时间是否符合要求
            {
                c_judge=0;
                printf("格式错误，请重新输入。\n");            //如输入有误，提示用户重新输入
                break;
            }
        }
        if(c_judge==1)
        {
        	over_hours=0;
	        if(c_over_hours[1]=='\0')           //将用户输入的时间转化为整形
	            over_hours=(int)c_over_hours[0]-48;
	        else
	            over_hours=((int)c_over_hours[0]-48)*10+(int)c_over_hours[1]-48;
	        if(over_hours<=begin_hours || over_hours>22)
	        {
	            printf("您选择的时间有误，请重新输入\n");
	            c_judge=0;
	        }
        }
    }while(c_judge==0);
    
    system("cls");
    
    show_num=0;
    for(i=0; i<gym_num; i++)        //遍历结构体gym寻找每个场地
    {
        judge=1;
        for(j=0; j<order_num; j++)      //遍历order结构体寻找该场地的订单
        {
            if(strcmp(order_info[j].gymnum, gym_info[i].num)==0)
            {
                if(order_info[j].rent_date==day_num)            //判断该场地是否有空余时间
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
        if(judge==1)        //将符合要求的场地输出
        {
            show_gym(i, order_num);
            show_num++;
        }
    }
    if(show_num==0)                         //如果没有场地有空余时间，告知顾客
        printf("抱歉，您选择的时间段内没有空余场地\n");
}

int gym_recommend(int gym_num, int order_num, int id)
{
    int number[gym_num], temp[gym_num], alreadyshow[gym_num];
    int i, j, k, x, judge;
    for(i=0; i<gym_num; i++)                                        //检验重复数组初始化
    {
        alreadyshow[i]=-1;
        number[i]=0;
    }
        
    for (i=0; i<gym_num; i++)                                       //计算各个场地的订单量    
    {
        for(j=0; j<order_num; j++)                                  //通过遍历order_info结构体数组，计算单个场地的订单量
            if(strcmp(order_info[j].gymnum, gym_info[i].num)==0)
                number[i]++;
    }
    
    for(i=0; i<gym_num; i++)                                        //将各个场地的订单量赋值到一个可供排序的数组
    {
        temp[i]=number[i];
    }
    qsort(temp, gym_num, sizeof(int), int_cmp);                     //将可供排序的数组进行排序
    
    j=-1;
    k=0;
    for(i=0; i<gym_num; i++)                                        //按着已经排序过的数组，从第一位，从场地中寻找对应的场地
    {
        judge=1;                                        //由于后面的for循环无法判断第一个位置是否重复，此循环用于确定第一个位置是否重复 
        for(x=0; x<k; x++)
            if(alreadyshow[x]==0)
                judge=0;
        while(number[j]!=temp[i]||judge==0)                   //寻找该订单量所对应的场地
        {
            j++;
                
            judge=1;                                            //检验是否重复
            for(x=0; x<k; x++)  
                if(alreadyshow[x]==j)
                    judge=0;            
        }                                                
        alreadyshow[k]=j;
        if(strcmp(client_info[id].zone, gym_info[j].zone)==0)       //判断该场地是否与该客户属于一个区域，符合则输出
            show_gym(j, order_num);                                           
        k++;
        j=0;
    }
}

int change_info(int leng)//修改用户个人信息，变量是该用户的脚码 
{
    char option;//标记变量 
    char tel_tem[12], password_tem1[len], password_tem2[len], email_tem[len], zone_tem[len];//储存被修改信息的临时变量 
    int index;//局部循环变量
    int option1 ;//判断变量 
    
    printf("下列操作中\"y\"代表“是”，\"n\"或其它字符代表“否”\n");//对下面的操作进行说明 
    printf("您希望修改您的电话信息吗？(Y/n)\n");//询问用户是否进行此操作（下同） 
    fflush(stdin);//将缓冲区清空，防止输入不正确格式时崩溃 
    while(1)
    {
        scanf("%c", &option);
        fflush(stdin);
        if(option == 'y' || option == 'Y')//若输入其它字符，则不进行本项修改 （下同） 
        {
            while(1)//若修改过程错误，则进行循环，重新输入 
            {
                printf("请输入新的电话信息:\n");
                fflush(stdin); 
                scanf("%s", tel_tem);
                fflush(stdin);
                option1 = 0;//给判断变量（重新）赋值 
                for(index = 0; index < 11; index ++)
                {
                    if(48 > tel_tem[index] || tel_tem[index] > 57)
                    {
                        option1 = 1;//确认输入有误 
                        printf("电话信息输入有误\n");
                        break;
                    }
                }
                if(option1 == 1)
                {
                    continue;
				}
    	        strcpy(client_info[leng].tel, tel_tem);
	        	printf("电话号码修改成功！\n");
				break; 
        	}
    	    break;
        }
        else if(option == 'n' || option == 'N') 
        {
            printf("已取消修改电话号码\n");
            break;
        }
            
        else
        {
            printf("请重新输入。\n");
            continue;
        }
    }

    printf("您希望修改您的密码吗(Y/n)\n");
    while(1)
    {
        scanf("%c", &option); 
        fflush(stdin);
        if(option == 'y' || option == 'Y')
        {
           while(1)
            {
                printf("请输入新密码：\n");
                scanf("%s", password_tem1); 
                fflush(stdin);
                printf("请再次输入新密码：\n");//再次输入，防止输入错误 
                scanf("%s", password_tem2);
                fflush(stdin);
                if(strcmp(password_tem1, password_tem2)==0)//判断两次输入是否一致 
                {
                    strcpy(client_info[leng].password, password_tem1);
                    printf("密码修改成功！\n");
	                break;
                } 
                else
                    printf("两次输入不相同，请重新输入\n");
            }
            break;
        }
        else if(option == 'n' || option == 'N')
        {
            printf("已取消修改密码\n");
            break;
        }
        else
        {
            printf("请重新输入\n");
            continue;
        }
    }
        
    printf("您希望修改您的邮箱吗？(Y/n)\n");
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
    
            
    printf("您希望修改您的地址吗?(Y/n)\n");//询问是否修改地址
    while(1)
    {
        fflush(stdin);
        scanf("%c", &option);
        fflush(stdin);
        if(option == 'y' || option == 'Y')
        {
            while(1)
            {
                printf("请输入新的地址：\n");
                scanf("%s", zone_tem);
                fflush(stdin);
                strcpy(client_info[leng].zone, zone_tem);
                printf("地址修改成功！\n");
                break;
            }
            break;
        }
        else if(option == 'n' || option == 'N')
        {
            printf("已取消修改地址\n");
            break;
            
        }
        else
        {
            printf("请重新输入\n");
            continue;
        }
    }

    printf("修改结束！\n");
    system("pause");
}

int query_info(char *cli_id,int *leng)//参数为用户id和结构长度 
{
    int index = 0, index1 = 0;//局部循环变量 
    int order_num[*leng];//存放用户的订单号 
    unsigned long long year , mon, day, hour, min;

    for(index = 0, index1 = 0; index < *leng; index ++)//找出要用户的目标编号 
    {
        if(strcmp(cli_id, order_info[index].user_id) == 0)
        {
            order_num[index1] = index;
            index1 ++;
        }
    }
    for(index = 0; index < index1; index ++)//输出查询结果（用户订单）
    {
        printf("订单编号：%s%-llu\n", order_info[order_num[index]].user_id, order_info[order_num[index]].reserve_date);//打印 预定编号 
        year = order_info[order_num[index]].reserve_date / 100000000;
        mon = (order_info[order_num[index]].reserve_date / 1000000) % 100;
        day = (order_info[order_num[index]].reserve_date / 10000) % 100;
        hour = (order_info[order_num[index]].reserve_date / 100) % 100;
        min = order_info[order_num[index]].reserve_date % 100;
        printf("预定日期：%llu年%llu月%llu日%llu时%llu分\n", year, mon, day, hour, min);//预定日期 
        printf("场地编号：%s\n", order_info[order_num[index]].gymnum);//输场地编号 
        year = order_info[order_num[index]].rent_date / 10000;
        mon = (order_info[order_num[index]].rent_date / 100) % 100;
        day = order_info[order_num[index]].rent_date % 100;
        printf("预定日期：%d年%d月%d日\n", year, mon, day);//租借场地日期 
        printf("开始时间：%d点\n", order_info[order_num[index]].begin_time);//租借场地开始时间 
        printf("结束时间：%d点\n", order_info[order_num[index]].over_time);//租借场地结束时间
        printf("是否到场");
        if(order_info[order_num[index]].sign == 1)//是否按时到场 
            printf("YES");
        else
            printf(" NO");
        printf("\n\n");
    }
}


int delete_info(char *cli_id, int *leng)//删除，两个变量分别代表用户id和订单结构长度 
{
    unsigned long long ord_num;//日期 
    char key[20];
    int index = 0;//局部循环变量 
    int del_num;//删除目标的编号 
    int option = 0;
 
    query_info(cli_id, leng);//显示用户订单，方便删除工作 
    printf("请输入要删除的订单的编号的日期的部分（后12位数）：\n");
    scanf("%llu", &ord_num);
    fflush(stdin);//将缓冲区清空，防止输入字符时程序崩溃 

    for(index = 0; index < *leng; index ++)//找出要删除的目标编号 
    {   
        if(strcmp(cli_id, order_info[index].user_id) == 0 && order_info[index].reserve_date == ord_num)
        {
            del_num = index;
            for(index = del_num; index < (*leng-1); index ++)//把被删除目标赋值为后面的结构体，并向后重复 
            {
                order_info[index] = order_info[index+1];
            }
            *leng = *leng - 1;//将结构长度减小
            option = 1;//表示成功删除 
            break;//找到目标编号后退出循环 
        }
    }
    
    if(option == 1)
        printf("\n删除成功\n");
    else
        printf("\n删除失败\n");

    system("pause");
}

int ad_menu1()
{
    printf("尊敬的管理员，您好！\n\n");
    printf("--------------------管理员系统------------------\n");
    printf("1.查询自己管理场馆预定情况。\n");
    printf("2.统计用户预定信息\n");
    printf("3.查询场地信息\n");
    printf("4.添加新场地\n");
    printf("5.修改个人信息\n");
    printf("6.退出程序\n");
    printf("------------------------------------------------\n");
    printf("请输入："); 
}

int ad_menu2()
{
    printf("------------------统计用户预定信息--------------\n");
    printf("1.按预定量对本场馆所属场地排序。\n");
    printf("2.统计场馆营业额。\n");
    printf("3.统计不同场地的用户年龄层次分布。\n");
    printf("4.按营业额对本场馆的所有场地排序。\n");
    printf("5.根据性别统计最受男士/女士欢迎的运动。\n");
    printf("6.按时间段统计不同类型场地的租用情况。\n");
    printf("------------------------------------------------\n");
    printf("请输入："); 
}


int ad_check(int *ad_point, int order_num)
{
	int i = 0;
	int year, mon, day, hour, min;
	int y, m, d;
	printf("您管理的是%s号场馆。\n", admin_info[*ad_point].gymnasium);
	printf("--------------本场馆历史上订单记录------------\n\n");
	for (i = 0; i < order_num; i++)                                                              //检索历史订单
	{
		year = order_info[i].reserve_date / 100000000;
		mon = (order_info[i].reserve_date / 1000000) % 100;
		day = (order_info[i].reserve_date / 10000) % 100;
		hour = (order_info[i].reserve_date / 100) % 100;
		min = order_info[i].reserve_date % 100;

		y = order_info[i].rent_date / 10000;
		m = (order_info[i].rent_date / 100) % 100;
		d = order_info[i].rent_date % 100;
		if (strncmp(admin_info[*ad_point].gymnasium, order_info[i].gymnum, 6) == 0)             //打印历史订单                                                 //检索管理员结构体，匹配至登陆管理员 
		{
			printf("用户ID:%s\n", order_info[i].user_id);                                                                                         //打印需要信息 
			printf("体育场馆编号:%s\n", order_info[i].gymnum);
			printf("预定日期:%llu年%llu月%llu日%llu时%llu分\n", year,mon,day,hour,min);
			printf("使用日期:%d年%d月%d日 %d时到%d时\n", y,m,d, order_info[i].begin_time, order_info[i].over_time);
			printf("是否享用场地:%d(签到为1，反之为0)\n\n\n", order_info[i].sign);
		}
	}
	printf("----------------------------------------------\n");
}

int ad_stat_gender(int gym_num, int client_num, int order_num)
{
    int i, j, k;
    int man[gym_num], woman[gym_num];                                                     //创建数组，以便储存不同性别的订单
    int m_max, w_max;

    for (i = 0; i < gym_num; i++)
    {
        man[i] = 0;
        woman[i] = 0;
    }

    for (i = 0; i < gym_num; i++)                                                        //检索顾客、管理员和体育场链表 
        for (j = 0; j < order_num; j++)
            if (strcmp(gym_info[i].num, order_info[j].gymnum) == 0)
                for (k = 0; k < client_num; k++)
                    if (strcmp(order_info[j].user_id, client_info[k].id) == 0)           //匹配顾客id与订单id
                    {
                        if (strcmp(client_info[k].gender, "女") == 0)                    //匹配性别
                            woman[i]++;
                        else if (strcmp(client_info[k].gender, "男") == 0)
                            man[i]++;
                    }

    printf("在男性中：\n");
    m_max = man[0];
    for (i = 0; i < gym_num; i++)
    {
        printf("喜欢去%s场的有%d人\n", gym_info[i].num, man[i]);
        if ((i > 0) && (man[i] > man[i - 1]))
            m_max = i;                                                                   //检索男性中最受欢迎的场地
    }
    printf("男性最喜欢去:%s\n\n", gym_info[m_max].num);

    printf("在女性中：\n");
    w_max = woman[0];
    for (i = 0; i < gym_num; i++)
    {
        printf("喜欢去%s场的有%d人\n", gym_info[i].num, woman[i]);
        if ((i > 0) && (woman[i] > woman[i - 1]))
            w_max = i;
    }
    printf("女性最喜欢去:%s\n", gym_info[w_max].num);
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

    for (i = 0; i < gym_num; i++)                                                                     //检索顾客、管理员和体育场链表
        for (j = 0; j < order_num; j++)    
            if (strcmp(gym_info[i].num, order_info[j].gymnum) == 0)
                for (k = 0; k < client_num; k++)
                    if (strcmp(order_info[j].user_id, client_info[k].id) == 0)                        //匹配顾客id和订单id
                        if (client_info[k].age < 30)                                                  //匹配年龄
                            young[i]++;
                        else if ((30 <= client_info[k].age) && (client_info[k].age < 55))
                            mid[i]++;
                        else if (client_info[k].age >= 55)
                            old[i]++;

    printf("--------------------年龄统计--------------------\n");
    printf("                青年\t中年\t老年\n");
    for (i = 0; i < gym_num; i++)                                                                     //打印年龄结构
        printf("场地编号%s\t%d\t%d\t%d\n", gym_info[i].num, young[i], mid[i], old[i]);
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
                    quan[i] += (order_info[j].over_time - order_info[j].begin_time);             //本场馆租用时间
                    q[i]++;                           //本场馆订单量
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
                printf("本场馆其余场地订单量为零！\n");
                break;
            }
            else
                printf("场地%s订单量%d\n", gym_info[p[i]].num, (int)t[i]);     // 本场馆营业额
        printf("---------------------------------------\n");
    }

    for (i = 0; i < gym_num; i++)
    {
        money_gym[i] = gym_info[i].rent*quan[i];
        money += money_gym[i];
    }
    if (func_2 == 2)
    {
        printf("---------------场馆营业额--------------\n");           //本场馆总营业额
        printf("您管理的是%s场馆\n", admin_info[*ad_point].gymnasium);
        printf("营业额共%.2f元。\n", money);
        printf("---------------------------------------\n");
    }

    else if (func_2 == 4)
    {
        printf("---------地营业额排序(由大到小)--------\n");    //本场馆营业额排序
        for (i = 0; i < gym_num; i++)
            temp[i] = money_gym[i];
        for (i = 0; i < gym_num; i++)
            position[i] = i;
        b_sort(temp, position, gym_num);

        for (i = 0; i < gym_num; i++)
            if (temp[i] == 0)
            {
                printf("本场馆其余场地营业额为零！\n");
                break;
            }
            else
                printf("场地%s营业额%.2f元\n", gym_info[position[i]].num, temp[i]);
        printf("---------------------------------------\n");
    }
}

int gymnasium_search(int *ad_point,int gym_num, int order_num)         //查询场地信息 
{
    int i,j,k,time_now;
    for(i=0; i<gym_num; i++)                                 //验证该场馆是否存在
    {
        if(strcmp(admin_info[i].gymnasium, admin_info[*ad_point].gymnasium)==0)
            k++;
    }
    if(k==0)                                                //若未找到匹配场馆则显示错误报告 
    {
        printf("该场馆不存在\n");                                 
        return 0;
    }
    for(i=0;i<gym_num;i++)                                  //展示场馆所属场地的信息 
    {
        if(strcmp(admin_info[*ad_point].gymnasium,gym_info[i].belong_stadium)==0)
        {
            show_gym(i, order_num);
        } 
    } 
}

int gymnasium_add(int gym_num, int order_num, int *ad_point, int *p_gym_num)    //添加一个新场地 
{
    int j=gym_num;
    char type[len],introduction[len],num[len], zone[len];
    int permit_age_s,permit_age_l;
    float rent;
    printf("请输入场馆编号:\n");                                   //接收场地信息 
    scanf("%s",num);
    printf("请输入场地所属区域\n");
    scanf("%s", zone);
    printf("请输入场地种类:\n");
    scanf("%s",type);
    printf("请输入场地介绍:\n");
    scanf("%s",introduction); 
    printf("请输入允许年龄下限，上限及租金：\n");
    scanf("%d%d%f",&permit_age_s,&permit_age_l,&rent);
    strcpy(gym_info[j].num,num);                                    //录入场地信息 
    strcpy(gym_info[j].zone,zone);
    strcpy(gym_info[j].belong_stadium,admin_info[*ad_point].gymnasium);
    strcpy(gym_info[j].type,type);
    strcpy(gym_info[j].introdution,introduction);
    gym_info[j].permit_age[0]=permit_age_s;
    gym_info[j].permit_age[1]=permit_age_l;
    gym_info[j].rent=rent;
    show_gym(j, order_num);
    *p_gym_num=*p_gym_num+1;                                        //增加场地数量 
    printf("操作完成\n");                                           //录入完成 
}


int modify(int *ad_point)                                           //修改个人信息 
{
    int i,j,judge;
    char ema[len],pas1[len],pas2[len],tel[len];
    printf("选择你想要修改的信息:\n");
    printf("1.电子邮箱\n2.密码\n3.电话\n4.取消\n");                   //选择一项进行修改
    scanf("%d",&i);     
    if(i==1) 
    {
        printf("请输入新邮箱:\n");
        email_judge(ema);                                            //修改邮箱 
        printf("邮箱修改成功"); 
    }
    else if(i==2)
    {
        while(1)
        {
        printf("请输入新密码:\n");
        scanf("%s",pas1);
        printf("请再次输入新密码:\n");                              //确认新密码 
        scanf("%s",pas2);                                           //确认两次输入是否一致 
            if(strcmp(pas1,pas2)!=0)
            {
                printf("两次密码不同 请重新输入\n");
                
            }
            else
            {
                strcpy(admin_info[*ad_point].password,pas1);
                printf("修改成功\n");
                break;
            }
        }
    } 
    else if(i==3)                                                   //修改电话 
    {
        do
        {
            judge=1;
            printf("请输入新电话号码:\n");
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
                    printf("电话号码不合法 请重新输入\n"); 
                    break;
                }
            }  
        }while(judge==0);
        strcpy(admin_info[*ad_point].tel, tel);
        printf("修改完成\n");
    }
    else if(i==4)                                                   //取消修改 
    {
        printf("修改取消\n"); 
    }
    else                                                    
    {
        printf("该选项不存在"); 
    }        
}

int aviliablity_sort(int *ad_point,int gym_num,int order_num)       //按时间段对场地利用率进行排序 
{
    int number_ad[gym_num], temp[gym_num],alreadyshow[gym_num];
    int i, j, k, x, begin,judge;
    char gym[gym_num];
    k=0; 
    for(i=0; i<gym_num; i++)                                        //验证该场馆是否存在
    {
        if(strcmp(admin_info[i].gymnasium, admin_info[*ad_point].gymnasium)==0)
            k++;
    }
    if(k==0)                                                         
    {
        printf("该场馆不存在\n");                                 
        return 0;
    }   
    printf("每一小时为一个时间段\n");                             
    printf("请输入您想查询的起始时间(6-21):");                      //管理员输入想查询的时间段 
    scanf("%d",&begin);
    if(begin<6||begin>21)
    {
        printf("该时段不存在\n");
        return 0; 
    }
    for(i=0; i<gym_num; i++)                                        //检验重复数组初始化
    {
        alreadyshow[i]=-1;
        number_ad[i]=0;
    }
    for (i=0; i<gym_num; i++)                                       //计算各个场地的订单量    
    {
        for(j=0; j<gym_num; j++)                                    //通过遍历gym_info结构体数组，计算特定时间段内单个场地的预订情况 
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
    
    for(i=0; i<gym_num; i++)                                        //将该时间段内各个场地的订单量赋值到一个可供排序的数组
    {
        temp[i]=number_ad[i];
    }
    qsort(temp, gym_num, sizeof(int), int_cmp);                     //将可供排序的数组进行排序

    j=0;
    k=0;
    for(i=0; i<gym_num; i++)                                        //按着已经排序过的数组，从第一位，从场地中寻找对应的场地
    {
        judge=1;                                                    //由于后面的for循环无法判断第一个位置是否重复，此循环用于确定第一个位置是否重复 
        for(x=0; x<k; x++)
            if(alreadyshow[x]==0)
                judge=0;
        while(number_ad[j]!=temp[i]||judge==0)                      //寻找该订单量所对应的场地
        {
            j++;
                
            judge=1;                                                //检验是否重复
            for(x=0; x<k; x++)  
                if(alreadyshow[x]==j)
                    judge=0;            
        }
        if(strcmp(gym_info[j].belong_stadium,admin_info[*ad_point].gymnasium)==0)
            show_gym(j,order_num);                                            //将找到的场地输出
        alreadyshow[k]=j;                                           //将已经输出的场地的位置赋值给检验重复数组
        k++;
        j=0;
    }
}


int save(int client_num, int admin_num, int gym_num, int order_num)
{
    int i;
    FILE *fp_client;             //定义四个结构体所对应的四个txt的文件指针
    FILE *fp_admin;
    FILE *fp_gym;
    FILE *fp_order;

    if((fp_client=fopen("client.txt", "wb"))==NULL)     //判断是否可以打开文件
    {
        printf("Cannot open client file\n");
        exit(0);
    }
    for(i=0; i<client_num; i++)             //将结构体中的数据写入到文件中
    {
        fwrite(&client_info[i], sizeof(struct client), 1, fp_client);
    }
    fclose(fp_client);

    if((fp_admin=fopen("admin.txt", "wb"))==NULL)       //判断是否可以打开文件
    {
        printf("Cannot open admin file\n");
        exit(0);
    }
    for(i=0; i<admin_num; i++)              //将结构体中的数据写入到文件中
    {
        fwrite(&admin_info[i], sizeof(struct admin), 1, fp_admin);
    }
    fclose(fp_admin);

    if((fp_gym=fopen("gym.txt", "wb"))==NULL)       //判断是否可以打开文件
    {
        printf("Cannot open gym file\n");
        exit(0);
    }
    for(i=0; i<gym_num; i++)                //将结构体中的数据写入到文件中
    {
        fwrite(&gym_info[i], sizeof(struct gym), 1, fp_gym);
    }
    fclose(fp_gym);

    if((fp_order=fopen("order.txt", "wb"))==NULL)       //判断是否可以打开文件
    {
        printf("Cannot open order file\n");
        exit(0);
    }
    for(i=0; i<order_num; i++)              //将结构体中的数据写入到文件中
    {
        fwrite(&order_info[i], sizeof(struct order), 1, fp_order);
    }
    fclose(fp_order);
}      

int main()
{
    int client_num, admin_num, gym_num, order_num;      //定义四个结构体数组的实际有效长度
    int *p_client_num, *p_admin_num, *p_gym_num, *p_order_num;          //定义四个结构体数组的实际有效长度的指针
    int pointer, ca;     //定义登录函数返回的用户在结构体数组的位置和用户的类型
    int *p_pointer, *p_ca;           //定义登录函数返回的用户在结构体数组的位置和用户的类型的指针
    int func_2, n;
    char func[2];
    int con1=1,con2=1;

    p_pointer=&pointer;     //取地址
    p_ca=&ca;

    p_client_num = &client_num;     //取地址
    p_admin_num = &admin_num;
    p_gym_num = &gym_num;
    p_order_num = &order_num;

    initialize(p_client_num, p_admin_num, p_gym_num, p_order_num);      //调用函数对程序初始化，将文件中的数据读入到内存中
    
    /*选择以客户或管理员的身份运行系统 */
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
        /*客户选择注册或登陆*/ 
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
                    login_cl(p_pointer,p_ca);//注册完转到登录界面
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
                    printf("请输入0或1!\n");
                }
            }
        } 
        else
        {    
            getchar();
            system("cls");
            printf("请输入0或1!\n");                    
        }
    }
    
    
    if(ca==1)
    {
        do
        { 
            system("cls");
            printf("尊敬的%s顾客，您好！\n",client_info[pointer].name);
            printf("---------------------顾客系统-------------------\n");       //打印列表
            printf("请输入您想选择的功能\n");
            printf("1.查询场地\n");
            printf("2.预定场地\n");
            printf("3.修改个人信息\n");
            printf("4.删除订单\n");
            printf("5.查询订单\n");
            printf("6.退出程序\n");
            printf("------------------------------------------------\n");
            printf("请输入：");
            scanf("%s", func);
            system("cls");
            switch(func[0])
            {
                case '1':
                    client_search(pointer, gym_num, order_num, p_order_num);        //查询场地
                    break;
                case '2':
                    client_reserve(p_order_num, pointer, gym_num);      //预定订单
                    break;
                case '3':
                    change_info(pointer);//修改个人信息
                    break;
                case '4':
                    delete_info(client_info[pointer].id, p_order_num);//删除订单
                    break;
                case '5':
                    query_info(client_info[pointer].id, p_order_num);//查询订单
                    system("pause");
                    break;
                case '6':       //退出程序
                    break;
                default:
                    printf("您输入有误，请重新输入。\n");       //如用户输入错误，提示用户重新输入
                    system("pause");
                    break;
            }
            save(client_num, admin_num, gym_num, order_num);        //将修改后的数据覆盖到原文件中
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
                        printf("输入有误，请重新输入\n"); 
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
                case '6':       //退出程序
                    break;
                default:
                    printf("输入有误，请重新输入\n");         //如用户输入错误，提示用户重新输入
                    system("pause");
                    system("cls");
                    break;
            }
            save(client_num, admin_num, gym_num, order_num);            //将修改后的数据覆盖到原文件中
        }while (func[0]!='6');
    }
    save(client_num, admin_num, gym_num, order_num);            //将修改后的数据覆盖到原文件中

    return 0;
}
