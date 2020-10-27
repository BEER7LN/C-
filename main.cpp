#include <iostream>
#include<stdio.h>  //���ú���
#include <string.h>  //�ַ�������
#include <stdlib.h> //������������ڴ���亯��
#include<conio.h> //����һЩ���ú���
using namespace std;

typedef struct book{
    int book_num; //�鼮���
    char name[100]; //�鼮����
    char author[100]; //������
    int num_xc; //�ִ���
    int num_kc; //�����
    int bf; //ƽ������
    struct book *lchild; //������
    struct book *rchild; //������
}*BOOKTree;
struct BORROW{
    int book_num; //�鼮���
    long int time; //�黹����
    long int reader_num; //ѧ��
    BORROW *next;
};

//���鼮��������ʼ��
BOOKTree init_book = NULL;
int init_taller = 0;
//���������ָ�벢��ʼ��
BORROW* head1 = NULL;
BORROW* tail = NULL;
//ƽ����������ȡֵ
const int LH = +1;
const int EH = 0;
const int RH = -1;
void login(); //��ӭҳ��
void stu_menu(); //1ѧ�����
void  back_stu_menu(); //����ѧ�����
void reader_list(int bnum, int ti, int rnum); //�γ�ѧ������
void borrow_book(); //����
void find_book_borrow(BOOKTree *tree, int num); //Ѱ�Ҳ�չʾ�����鼮����Ϣ
void return_book(); //����
void reader_return(BORROW* head,int theElement); //Ѱ�ҽ��ļ�¼
void find_book_return(BOOKTree *tree, int num); //Ѱ�Ҳ�����������
void show_all_book(BOOKTree tree); //չʾ����ͼ����Ϣ
void R_Rotate(BOOKTree *P); //������תP��ָ��Ķ�����
void L_Rotate(BOOKTree *P); //������תP��ָ��Ķ�����
void L_Blance(BOOKTree *T); //������������������
void R_Blance(BOOKTree *T); //������������������
void man_menu(); //2����Ա���
void new_book(); //�ɱ����
void outputreader_list();//��ʾ�����������Ϣ
bool InSert_book(BOOKTree *tree, int *taller, int a, char b[20], char c[20], int d); //�ɱ����֮AVL����

/*
 * ���ƣ���ӭҳ��
 * ���ܣ�
 * ���룺�����
 * ���������1��2
 * ��ת���������
 */
void login(){
    system("cls");  //��������
    printf("* * * * * ��ӭʹ��SDUͼ�����ϵͳ * * * * *\n");
    printf("\n\t  1 . ѧ �� �� ��\n");
    printf("\n\t  2 . �� �� Ա �� ��\n");
    printf("\n\t  3 . �� �� ϵ ͳ\n");
    printf("\n* * * * * * * * * * * * * * * * * * * * * *\n");
    printf("��ѡ����ڣ��������֣���");
    int inter;
    //ʹ��forѭ����֤������ȷ
    for(;;) {
        scanf("%d",&inter);
        if(inter < 1 || inter > 3) {
            printf("\n���������������ȷ�����֣�");
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
            printf("��ڽ�����ִ���");
    }
}
void  back_stu_menu(){
    int i;
    printf("\n\n==================================");
    printf("\n*********** 1.����ѧ�����\n");
    printf("*********** 2.����\n");
    //ʹ��forѭ����֤������ȷ
    for(;;){
        scanf("%d",&i);
        if(i < 1 || i > 2) {
            printf("\n���������������ȷ�����֣�");
        }
        else break;
    }
    switch(i){
        case 1:
            stu_menu();
            break;
        case 2:
            printf("\n��л����ʹ�ã�");
            break;
        default:
            printf("\n���ִ���");
    }
}

/*
 * ���ƣ�1ѧ�����
 * ���ܣ�ѡ�����
 * ���룺�����Ӧ����ĸ
 * ���������1,2,3,4
 * ��ת����Ӧ����
 */
void stu_menu(){
    system("cls"); //��������
    printf("* * * * * SDUͼ��ݡ�������ѡ�� * * * * *\n");
    printf(" \n\t 1 . �� �� \n");
    printf(" \n\t 2 . �� �� \n");
    printf(" \n\t 3 . �� �� ͼ �� �� Ϣ \n");
    printf(" \n\t 4 . �� �� \n");
    printf("\n* * * * * * * * * * * * * * * * * * *\n");
    printf("�� ѡ �� �� �� �� Ҫ �� �� �� ��");
    int stu_server;
    //ʹ��forѭ����֤������ȷ
    for(;;){
        scanf("%d",&stu_server);
        if(stu_server < 1 || stu_server > 4) {
            printf("\n���������������ȷ�����֣�");
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
            printf("* * * * * ѧ����ڡ����鿴�������� * * * * *\n\n");
            printf("�鼮���\t�鼮����\t�鼮����\t�鼮��������\n");
            show_all_book(init_book);
            back_stu_menu();
            break;
        case 4:
            login();
            break;
        default:
            printf("���������ִ���");
    }
}



/*
 * ����/���ܣ���ʾ��������Ϣ
 * �����������Ϣ
 * ��ת���ص������߹���ҳ
 */
void outputreader_list() {
    system("cls");
    BORROW* m = head1;
    printf("* * * * * ����Ա��ڡ���������Ϣ * * * * *\n\n");
    printf("ѧ��\t\t�鼮���\t�黹ʱ��\t\t\n");
    while (m != NULL) {
        printf("%d\t\t%d\t\t%d\t\t\n",m->reader_num,m->book_num,m->time);
        m = m->next;
    }
    int i;
    printf("\n\n==================================");
    printf("\n\n\t1.���ع���Ա���\n\n");
    printf("\t2.����\n\n");
    printf("\t����������ѡ��");
    for(;;){
        scanf("%d",&i);
        if(i < 1 || i > 2) {
            printf("\n���������������ȷ�����֣�");
        }
        else break;
    }
    switch(i){
        case 1:
            man_menu();
            break;
        case 2:
            printf("\n��л����ʹ�ã�");
            break;
        default:
            printf("���ִ���!");
    }
}
/*
 * ����/���ܣ�����
 * ���룺ͼ����
 */
void borrow_book(){
    int bo_num;
    system("cls"); //��������
    printf("* * * * * ѧ����ڡ������� * * * * *\n");
    printf("\n��������Ҫ���ĵ��鼮�ı�ţ�");
    scanf("%d",&bo_num);
    find_book_borrow(&init_book, bo_num);
    back_stu_menu();
}
/*
 * ����/���ܣ�����֮ͼ����Ϣ��ϸչʾ����صǼ�
 * ���룺�鼮���
 * ����������ʾ
 */
void find_book_borrow(BOOKTree *tree, int num) {
    long int time = 0, hao = 0;
    if (tree == NULL)
        return;
    if (((*tree)->book_num) == num) {
        printf("\n����Ϊ����Ҫ���鼮����Ϣ��\n");
        printf("\n�鼮���ƣ�");
        printf((*tree)->name);
        printf("\n�鼮���ߣ�");
        printf((*tree)->author);
        printf("\n�鼮����������");
        cout << (*tree)->num_xc;
        if ((*tree)->num_xc == 0) {
            printf("\n��Ǹ�������Ѿ�����\n");
        }
        else {
            (*tree)->num_xc--;
            printf("\n\n����������ѧ�ţ�");
            scanf("%d", &hao);
            printf("\n�밴��20200101����ʽ��������Ҫ�黹ͼ������ڣ�");
            scanf("%d", &time);
            printf("\n���ĳɹ����밴ʱ���飡\n");
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
 * ����/���ܣ��γ�ѧ�ŵ�����
 * ���룺ѧ��
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
 * ����/���ܣ�����
 * ���룺ѧ��
 * ����������ĵ�ͼ����
 */
void reader_return(BORROW* head,int theElement) {
    BORROW* p = head;
    while (p != NULL && p->reader_num != theElement) {
        p = p->next;
    }
    if (p != NULL){
        printf("\n����Ҫ�黹���鼮�ı��Ϊ��");
        cout << p->book_num;
        find_book_return(&init_book,p->book_num);
        printf("\n���������ȷ�Ϲ黹\n");
        getch();
        printf("\n��л���ļ�ʱ�黹��");
    }
    else{
        printf("\nѧ��������������ԣ�");
        int again_num;
        scanf("%d",&again_num);
        reader_return(head, again_num);
    }
}
void return_book(){
    long int reader_num;
    system("cls"); //��������
    printf("* * * * * ѧ����ڡ������� * * * * *\n");
    printf("\n����������ѧ�ţ�");
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
 * ����/���ܣ�����ݹ����չʾ����ͼ����Ϣ
 */
void show_all_book(BOOKTree tree) {
    if (tree != NULL) {
        show_all_book(tree->lchild);
        printf("%d\t\t%s\t\t%s\t\t%d\t\t\n",tree->book_num,tree->name,tree->author,tree->num_xc);
        show_all_book(tree->rchild);
    }
}
/*
 * ����/���ܣ�������תP��ָ��Ķ�����,������ƽ������
 */
void R_Rotate(BOOKTree *P){
    BOOKTree tempR;
    tempR = (*P)->lchild;
    (*P)->lchild = tempR->rchild;
    tempR->rchild = (*P);
    *P = tempR;
}
/*
 * ����/���ܣ�������תP��ָ��Ķ�����,������ƽ������
 */
void L_Rotate(BOOKTree *P){
    BOOKTree tempL;
    tempL = (*P)->rchild;
    (*P)->rchild = tempL->lchild;
    tempL->lchild = (*P);
    *P = tempL;
}
/*
 * ����/���ܣ�Ϊ�½ڵ������T���������϶�����
 */
void L_Blance(BOOKTree *T){
    BOOKTree temp1, temp2;
    temp1 = (*T)->lchild;
    switch (temp1->bf){
        //������temp1����������
        case LH:
            R_Rotate(T);
            temp1->bf = (*T)->bf = EH;
            break;
        //������temp1����������
        case RH:
            temp2 = temp1->rchild;
            switch (temp2->bf){
                //������Ҷ�ڵ���
                case EH:
                    L_Rotate(&((*T)->lchild));
                    R_Rotate(T);
                    temp1->bf = temp2->bf = (*T)->bf = EH;
                    break;
                //���뵽��temp2����������
                case LH:
                    L_Rotate(&((*T)->lchild));
                    R_Rotate(T);
                    temp1->bf = temp2->bf = EH;
                    (*T)->bf = RH;
                    break;
                //���뵽��temp2����������
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
 * ����/���ܣ�������T���������϶�����
 */
void R_Blance(BOOKTree *T){
    BOOKTree temp3, temp4;
    temp3 = (*T)->rchild;
    switch (temp3->bf){
        //������temp3����������
        case RH:
            L_Rotate(T);
            temp3->bf = (*T)->bf = EH;
            break;
        //������temp3����������
        case LH:
            temp4 = temp3->lchild;
            switch (temp4->bf){
                //������Ҷ�ڵ���
                case EH:
                    R_Rotate(&((*T)->rchild));
                    L_Rotate(T);
                    temp4->bf = temp4->bf = (*T)->bf = EH;
                    break;
                    //���뵽��temp4����������
                case LH:
                    R_Rotate(&((*T)->rchild));
                    L_Rotate(T);
                    temp4->bf = (*T)->bf = EH;
                    temp3->bf = RH;
                    break;
                    //���뵽��temp4����������
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
 * ���ƣ�2����Ա���
 * ���ܣ�ѡ�����
 * ���룺�����Ӧ����ĸ
 * ���������1,2
 * ��ת����Ӧ����
 */
void man_menu(){
    system("cls"); //��������
    printf("* * * * * SDUͼ��ݡ�������ѡ�� * * * * *\n");
    printf(" \n\t 1 . �� �� �� �� \n");
    printf(" \n\t 2 . �� �� �� Ϣ \n");
    printf(" \n\t 3 . �� �� \n");
    printf("\n* * * * * * * * * * * * * * * * * * * * *\n");
    printf("�� ѡ �� �� �� �� Ҫ �� �� �� ��");
    int man_server;
    //ʹ��forѭ����֤������ȷ
    for(;;){
        scanf("%d",&man_server);
        if(man_server < 1 || man_server > 3) {
            printf("\n���������������ȷ�����֣�");
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
            printf("���������ִ���");
    }
}

/*
 * ���ƣ��ɱ����AVLʵ�ַ���
 * ��������ɹ�����
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
    //�˱��ͼ���Ѿ�����
    if ((*tree)->book_num == a){
        printf("\n�˱��ͼ���Ѿ����ڣ�������⽫ֱ��������������������\n");
        //int m;
        //scanf("%d", m);
        (*tree)->num_kc += d;
        (*tree)->num_xc += d;
        return false;
    }
    //���뵽ͷ�ڵ����������
    if((*tree)->book_num > a){
        bool suc = InSert_book(&((*tree)->lchild),taller, a, b, c, d);
        //�˱��ͼ���Ѿ����ڣ����贴���½ڵ�
        if(!suc)
            return false;
        //���½ڵ����ʽ������AVL���������е���
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
    //���뵽ͷ�ڵ����������
    else if((*tree)->book_num < a){
        //�˱��ͼ���Ѿ����ڣ����贴���½ڵ�
        if(!InSert_book(&((*tree)->rchild), taller, a, b, c, d))
            return false;
        //���½ڵ����ʽ��������AVL�������ĵ���
        if(*taller == 1){
            //�½��ڵ�ĸ��ڵ����½ڵ����ǰ��ƽ������
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
 * ���ƣ��ɱ����
 * ���룺������Ϣ
 */
void new_book(){
    int thebook_num; //�鼮���
    char thename[100]; //�鼮����
    char theauthor[100]; //������
    int thenum; //����
    system("cls");
    printf("* * * * * ����Ա��ڡ����ɱ���� * * * * *\n\n");
    printf("�밴����ʾ�����·�����������Ϣ\n");
    printf("\n�������鼮��ţ�");
    scanf("%d", &thebook_num);
    printf("\n�������鼮���ƣ�");
    cin >> thename;
    //scanf("%s", thename);
    printf("\n�������鼮�����ߣ�");
    cin >> theauthor;
    //scanf("%s", theauthor);
    printf("\n�������鼮������");
    scanf("%d", &thenum);
    InSert_book(&init_book,&init_taller,thebook_num,thename,theauthor,thenum);
    printf("\n\n==================================");
    printf("\n\t�������ɹ���");
    int i;
    printf("\n==================================");
    printf("\n\n\t1.���ع���Ա���\n\n");
    printf("\t2.����\n\n");
    printf("\t����������ѡ��");
    for(;;){
        scanf("%d",&i);
        if(i < 1 || i > 2) {
            printf("\n���������������ȷ�����֣�");
        }
        else break;
    }
    switch(i){
        case 1:
            man_menu();
            break;
        case 2:
            printf("\n��л����ʹ�ã�");
            break;
        default:
            printf("���ִ���!");
    }
}

int main() {
    login();
    return 0;
}