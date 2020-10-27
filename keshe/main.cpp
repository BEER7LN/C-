#include <iostream>
#include<stdio.h>  //调用函数
#include <string.h>  //字符串处理
#include <stdlib.h> //定义杂项函数及内存分配函数
#include<conio.h> //包含一些常用函数
using namespace std;

typedef struct book{
    int book_num; //书籍编号
    char name[100]; //书籍名称
    char author[100]; //著作者
    int num_xc; //现存量
    int num_kc; //库存量
    int bf; //平衡因子
    struct book *lchild; //左子树
    struct book *rchild; //右子树
}*BOOKTree;
struct BORROW{
    int book_num; //书籍编号
    long int time; //归还日期
    long int reader_num; //学号
    BORROW *next;
};

//对书籍的索引初始化
BOOKTree init_book = NULL;
int init_taller = 0;
//定义借阅者指针并初始化
BORROW* head1 = NULL;
BORROW* tail = NULL;
//平衡因子正常取值
const int LH = +1;
const int EH = 0;
const int RH = -1;
void login(); //欢迎页面
void stu_menu(); //1学生入口
void  back_stu_menu(); //返回学生入口
void reader_list(int bnum, int ti, int rnum); //形成学号链表
void borrow_book(); //借书
void find_book_borrow(BOOKTree *tree, int num); //寻找并展示单本书籍的信息
void return_book(); //还书
void reader_return(BORROW* head,int theElement); //寻找借阅记录
void find_book_return(BOOKTree *tree, int num); //寻找并增加现有量
void show_all_book(BOOKTree tree); //展示所有图书信息
void R_Rotate(BOOKTree *P); //向右旋转P所指向的二叉树
void L_Rotate(BOOKTree *P); //向左旋转P所指向的二叉树
void L_Blance(BOOKTree *T); //插入在左子树而调整
void R_Blance(BOOKTree *T); //插入在右子树而调整
void man_menu(); //2管理员入口
void new_book(); //采编入库
void outputreader_list();//显示借阅者相关信息
bool InSert_book(BOOKTree *tree, int *taller, int a, char b[20], char c[20], int d); //采编入库之AVL索引

/*
 * 名称：欢迎页面
 * 功能：
 * 输入：任意键
 * 输出：数字1或2
 * 跳转：两种入口
 */
void login(){
    system("cls");  //清屏函数
    printf("* * * * * 欢迎使用SDU图书管理系统 * * * * *\n");
    printf("\n\t  1 . 学 生 入 口\n");
    printf("\n\t  2 . 管 理 员 入 口\n");
    printf("\n\t  3 . 退 出 系 统\n");
    printf("\n* * * * * * * * * * * * * * * * * * * * * *\n");
    printf("请选择入口（输入数字）：");
    int inter;
    //使用for循环保证输入正确
    for(;;) {
        scanf("%d",&inter);
        if(inter < 1 || inter > 3) {
            printf("\n输入错误，请输入正确的数字：");
        }
        else break;
    }
    switch(inter){
        case 1:
            stu_menu();
            break;
        case 2:
            man_menu();
            break;
        case 3:
            break;
        default:
            printf("入口接入出现错误");
    }
}
void  back_stu_menu(){
    int i;
    printf("\n\n==================================");
    printf("\n*********** 1.返回学生入口\n");
    printf("*********** 2.结束\n");
    //使用for循环保证输入正确
    for(;;){
        scanf("%d",&i);
        if(i < 1 || i > 2) {
            printf("\n输入错误，请输入正确的数字：");
        }
        else break;
    }
    switch(i){
        case 1:
            stu_menu();
            break;
        case 2:
            printf("\n感谢您的使用！");
            break;
        default:
            printf("\n出现错误");
    }
}

/*
 * 名称：1学生入口
 * 功能：选择服务
 * 输入：服务对应的字母
 * 输出：数字1,2,3,4
 * 跳转：对应服务
 */
void stu_menu(){
    system("cls"); //清屏函数
    printf("* * * * * SDU图书馆——服务选择 * * * * *\n");
    printf(" \n\t 1 . 借 书 \n");
    printf(" \n\t 2 . 还 书 \n");
    printf(" \n\t 3 . 查 看 图 书 信 息 \n");
    printf(" \n\t 4 . 退 出 \n");
    printf("\n* * * * * * * * * * * * * * * * * * *\n");
    printf("请 选 择 您 所 需 要 的 服 务 ：");
    int stu_server;
    //使用for循环保证输入正确
    for(;;){
        scanf("%d",&stu_server);
        if(stu_server < 1 || stu_server > 4) {
            printf("\n输入错误，请输入正确的数字：");
        }
        else break;
    }
    switch(stu_server){
        case 1:
            borrow_book();
            break;
        case 2:
            return_book();
            break;
        case 3:
            system("cls");
            printf("* * * * * 学生入口——查看藏书详情 * * * * *\n\n");
            printf("书籍编号\t书籍名称\t书籍作者\t书籍现有数量\n");
            show_all_book(init_book);
            back_stu_menu();
            break;
        case 4:
            login();
            break;
        default:
            printf("服务接入出现错误");
    }
}



/*
 * 名称/功能：显示借阅者信息
 * 输出：借阅信息
 * 跳转：回到管理者功能页
 */
void outputreader_list() {
    system("cls");
    BORROW* m = head1;
    printf("* * * * * 管理员入口——借阅信息 * * * * *\n\n");
    printf("学号\t\t书籍编号\t归还时间\t\t\n");
    while (m != NULL) {
        printf("%d\t\t%d\t\t%d\t\t\n",m->reader_num,m->book_num,m->time);
        m = m->next;
    }
    int i;
    printf("\n\n==================================");
    printf("\n\n\t1.返回管理员入口\n\n");
    printf("\t2.结束\n\n");
    printf("\t请输入您的选择：");
    for(;;){
        scanf("%d",&i);
        if(i < 1 || i > 2) {
            printf("\n输入错误，请输入正确的数字：");
        }
        else break;
    }
    switch(i){
        case 1:
            man_menu();
            break;
        case 2:
            printf("\n感谢您的使用！");
            break;
        default:
            printf("出现错误!");
    }
}
/*
 * 名称/功能：借书
 * 输入：图书编号
 */
void borrow_book(){
    int bo_num;
    system("cls"); //清屏函数
    printf("* * * * * 学生入口——借书 * * * * *\n");
    printf("\n请输入需要借阅的书籍的编号：");
    scanf("%d",&bo_num);
    find_book_borrow(&init_book, bo_num);
    back_stu_menu();
}
/*
 * 名称/功能：借书之图书信息详细展示及相关登记
 * 输入：书籍编号
 * 输出：相关提示
 */
void find_book_borrow(BOOKTree *tree, int num) {
    long int time = 0, hao = 0;
    if (tree == NULL)
        return;
    if (((*tree)->book_num) == num) {
        printf("\n以下为您需要的书籍的信息：\n");
        printf("\n书籍名称：");
        printf((*tree)->name);
        printf("\n书籍作者：");
        printf((*tree)->author);
        printf("\n书籍现有数量：");
        cout << (*tree)->num_xc;
        if ((*tree)->num_xc == 0) {
            printf("\n抱歉，该书已经借完\n");
        }
        else {
            (*tree)->num_xc--;
            printf("\n\n请输入您的学号：");
            scanf("%d", &hao);
            printf("\n请按照20200101的样式，输入您要归还图书的日期：");
            scanf("%d", &time);
            printf("\n借阅成功，请按时还书！\n");
        }
        reader_list(num, time, hao);
        return;
    }
    else if(((*tree)->book_num) > num) {
        find_book_borrow(&((*tree)->lchild),num);
    }
    else if(((*tree)->book_num) < num) {
        find_book_borrow(&((*tree)->rchild),num);
    }
}
/*
 * 名称/功能：形成学号的链表
 * 输入：学号
 */
void reader_list(int bnum, int ti, int rnum) {
    BORROW* newnode;
    newnode = new BORROW;
    newnode->book_num = bnum;
    newnode->time = ti;
    newnode->reader_num = rnum;
    if(head1 == NULL){
        head1 = newnode;
        tail = newnode;
    }
    else{
        tail->next = newnode;
        tail = newnode;
    }
    tail->next = NULL;
}
/*
 * 名称/功能：还书
 * 输入：学号
 * 输出：所借阅的图书编号
 */
void reader_return(BORROW* head,int theElement) {
    BORROW* p = head;
    while (p != NULL && p->reader_num != theElement) {
        p = p->next;
    }
    if (p != NULL){
        printf("\n您需要归还的书籍的编号为：");
        cout << p->book_num;
        find_book_return(&init_book,p->book_num);
        printf("\n按下任意键确认归还\n");
        getch();
        printf("\n感谢您的及时归还！");
    }
    else{
        printf("\n学号输入错误，请重试：");
        int again_num;
        scanf("%d",&again_num);
        reader_return(head, again_num);
    }
}
void return_book(){
    long int reader_num;
    system("cls"); //清屏函数
    printf("* * * * * 学生入口——还书 * * * * *\n");
    printf("\n请输入您的学号：");
    scanf("%d",&reader_num);
    reader_return(head1,reader_num);
    back_stu_menu();
}
void find_book_return(BOOKTree *tree, int num) {
    if (tree == NULL)
        return;
    if ((*tree)->book_num == num) {
        (*tree)->num_xc++;
        return;
    }
    find_book_return(&((*tree)->lchild),num);
    find_book_return(&((*tree)->rchild),num);
}
/*
 * 名称/功能：中序递归遍历展示所有图书信息
 */
void show_all_book(BOOKTree tree) {
    if (tree != NULL) {
        show_all_book(tree->lchild);
        printf("%d\t\t%s\t\t%s\t\t%d\t\t\n",tree->book_num,tree->name,tree->author,tree->num_xc);
        show_all_book(tree->rchild);
    }
}
/*
 * 名称/功能：向右旋转P所指向的二叉树,不调整平衡因子
 */
void R_Rotate(BOOKTree *P){
    BOOKTree tempR;
    tempR = (*P)->lchild;
    (*P)->lchild = tempR->rchild;
    tempR->rchild = (*P);
    *P = tempR;
}
/*
 * 名称/功能：向左旋转P所指向的二叉树,不调整平衡因子
 */
void L_Rotate(BOOKTree *P){
    BOOKTree tempL;
    tempL = (*P)->rchild;
    (*P)->rchild = tempL->lchild;
    tempL->lchild = (*P);
    *P = tempL;
}
/*
 * 名称/功能：为新节点插入在T的左子树上而调整
 */
void L_Blance(BOOKTree *T){
    BOOKTree temp1, temp2;
    temp1 = (*T)->lchild;
    switch (temp1->bf){
        //插入在temp1的左子树上
        case LH:
            R_Rotate(T);
            temp1->bf = (*T)->bf = EH;
            break;
        //插入在temp1的右子树上
        case RH:
            temp2 = temp1->rchild;
            switch (temp2->bf){
                //出现在叶节点上
                case EH:
                    L_Rotate(&((*T)->lchild));
                    R_Rotate(T);
                    temp1->bf = temp2->bf = (*T)->bf = EH;
                    break;
                //插入到了temp2的左子树上
                case LH:
                    L_Rotate(&((*T)->lchild));
                    R_Rotate(T);
                    temp1->bf = temp2->bf = EH;
                    (*T)->bf = RH;
                    break;
                //插入到了temp2的右子树上
                case RH:
                    L_Rotate(&((*T)->lchild));
                    R_Rotate(T);
                    (*T)->bf = temp2->bf = EH;
                    temp1->bf = RH;
                    break;
            }
            break;
        case EH:
            break;
    }
}
/*
 * 名称/功能：插入在T的右子树上而调整
 */
void R_Blance(BOOKTree *T){
    BOOKTree temp3, temp4;
    temp3 = (*T)->rchild;
    switch (temp3->bf){
        //插入在temp3的右子树上
        case RH:
            L_Rotate(T);
            temp3->bf = (*T)->bf = EH;
            break;
        //插入在temp3的左子树上
        case LH:
            temp4 = temp3->lchild;
            switch (temp4->bf){
                //出现在叶节点上
                case EH:
                    R_Rotate(&((*T)->rchild));
                    L_Rotate(T);
                    temp4->bf = temp4->bf = (*T)->bf = EH;
                    break;
                    //插入到了temp4的左子树上
                case LH:
                    R_Rotate(&((*T)->rchild));
                    L_Rotate(T);
                    temp4->bf = (*T)->bf = EH;
                    temp3->bf = RH;
                    break;
                    //插入到了temp4的右子树上
                case RH:
                    R_Rotate(&((*T)->rchild));
                    L_Rotate(T);
                    temp3->bf = temp4->bf = EH;
                    (*T)->bf = LH;
                    break;
            }
            break;
        case EH:
            break;
    }
}
/*
 * 名称：2管理员入口
 * 功能：选择服务
 * 输入：服务对应的字母
 * 输出：数字1,2
 * 跳转：对应服务
 */
void man_menu(){
    system("cls"); //清屏函数
    printf("* * * * * SDU图书馆——服务选择 * * * * *\n");
    printf(" \n\t 1 . 采 编 入 库 \n");
    printf(" \n\t 2 . 借 阅 信 息 \n");
    printf(" \n\t 3 . 退 出 \n");
    printf("\n* * * * * * * * * * * * * * * * * * * * *\n");
    printf("请 选 择 您 所 需 要 的 服 务 ：");
    int man_server;
    //使用for循环保证输入正确
    for(;;){
        scanf("%d",&man_server);
        if(man_server < 1 || man_server > 3) {
            printf("\n输入错误，请输入正确的数字：");
        }
        else break;
    }
    switch(man_server){
        case 1:
            new_book();
            break;
        case 2:
            outputreader_list();
            break;
        case 3:
            login();
            break;
        default:
            printf("服务接入出现错误");
    }
}

/*
 * 名称：采编入库AVL实现方案
 * 输出：入库成功提醒
 */
bool InSert_book(BOOKTree *tree, int *taller,int a, char b[20], char c[20], int d){
    if((*tree) == NULL){
        *taller = 1;
        BOOKTree newnode = (BOOKTree)malloc(sizeof(BOOKTree));
        newnode->bf = 0;
        newnode->rchild = newnode->lchild = NULL;
        newnode->book_num = a;
        memcpy(newnode->name,b,strlen(b));
        newnode->name[strlen(b)]='\0';
        //memcpy(newnode->name, reinterpret_cast<const void *>(b), sizeof(b));
        memcpy(newnode->author,c,strlen(c));
        newnode->author[strlen(c)]='\0';
        //memcpy(newnode->author, reinterpret_cast<const void *>(c), sizeof(c));
        newnode->num_kc = d;
        newnode->num_xc = d;
        *tree = newnode;
        return true;
    }
    //此编号图书已经存在
    if ((*tree)->book_num == a){
        printf("\n此编号图书已经存在，本次入库将直接增加其库存量和现有量\n");
        //int m;
        //scanf("%d", m);
        (*tree)->num_kc += d;
        (*tree)->num_xc += d;
        return false;
    }
    //插入到头节点的左子树中
    if((*tree)->book_num > a){
        bool suc = InSert_book(&((*tree)->lchild),taller, a, b, c, d);
        //此编号图书已经存在，无需创建新节点
        if(!suc)
            return false;
        //以新节点的形式插入后的AVL搜索树进行调整
        if(*taller == 1){
            switch ((*tree)->bf){
                case LH:
                    *taller = 0;
                    L_Blance(tree);
                    break;
                case EH:
                    (*tree)->bf = LH;
                    *taller = 1;
                    break;
                case RH:
                    (*tree)->bf = EH;
                    *taller = 0;
                    break;
            }
        }
        return true;
    }
    //插入到头节点的右子树中
    else if((*tree)->book_num < a){
        //此编号图书已经存在，无需创建新节点
        if(!InSert_book(&((*tree)->rchild), taller, a, b, c, d))
            return false;
        //以新节点的形式插入后进行AVL搜索树的调整
        if(*taller == 1){
            //新建节点的父节点在新节点插入前的平衡因子
            switch ((*tree)->bf){
                case LH:
                    (*tree)->bf = EH;
                    *taller = 0;
                    break;
                case EH:
                    (*tree)->bf = RH;
                    *taller = 1;
                    break;
                case RH:
                    R_Blance(tree);
                    *taller = 0;
                    break;
            }
        }
        return true;
    }
}
/*
 * 名称：采编入库
 * 输入：新书信息
 */
void new_book(){
    int thebook_num; //书籍编号
    char thename[100]; //书籍名称
    char theauthor[100]; //著作者
    int thenum; //数量
    system("cls");
    printf("* * * * * 管理员入口——采编入库 * * * * *\n\n");
    printf("请按照提示，在下方输入新书信息\n");
    printf("\n请输入书籍编号：");
    scanf("%d", &thebook_num);
    printf("\n请输入书籍名称：");
    cin >> thename;
    //scanf("%s", thename);
    printf("\n请输入书籍著作者：");
    cin >> theauthor;
    //scanf("%s", theauthor);
    printf("\n请输入书籍数量：");
    scanf("%d", &thenum);
    InSert_book(&init_book,&init_taller,thebook_num,thename,theauthor,thenum);
    printf("\n\n==================================");
    printf("\n\t新书入库成功！");
    int i;
    printf("\n==================================");
    printf("\n\n\t1.返回管理员入口\n\n");
    printf("\t2.结束\n\n");
    printf("\t请输入您的选择：");
    for(;;){
        scanf("%d",&i);
        if(i < 1 || i > 2) {
            printf("\n输入错误，请输入正确的数字：");
        }
        else break;
    }
    switch(i){
        case 1:
            man_menu();
            break;
        case 2:
            printf("\n感谢您的使用！");
            break;
        default:
            printf("出现错误!");
    }
}

int main() {
    login();
    return 0;
}