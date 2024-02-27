#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#define MaxSize 10000
//struct number_node{
//
//    struct number_node *next;
//};

int main(){
    FILE *video_data;
    char string[MaxSize];
    char view_string[MaxSize];
    long long views,sum=0;
    int i, count=0;
    //打开文件
    if ((video_data = fopen("D:\\学习材料\\软件实训\\books.csv", "r"))==NULL){
        printf("File Open Error!");
        exit(0);
    }
    //获取每一行的数据
    for (; !feof(video_data);){
        //字符串清空
        for(i=0;i<MaxSize;i++){
            view_string[i] = '\0';
        }
        //获取一行的数据
        fgets(string, sizeof(string), video_data);
//        printf("%s\n", string);
        //获取第一个‘,’之前的数据，也就是view
        for(i=0; string[i] !=',';i++){
            view_string[i]  = string[i];
        }
        //将view从字符串转化为整数
//        printf("%s\n", view_string);
        views = atoll(view_string);
        //整个求和
        sum += views;
    }
    //最后一条数据写入了两次，所以减去一次
    sum -= views;
    printf("总合%lld\n",sum);
    //计算平均值
    sum = sum / 1600;
    printf("平均值%lld", sum);
    return 0;
}
//typedef  struct Student_sore{
//    int math;
//    int chinese;
//    int english;
//}StudentSore, studentOne;
//
//struct  Student{
//    char name[100];
//    int *age;
//    char gender;
//    StudentSore *student_infomation;
//};

//StudentSore* creatLinkList();



//    fgets(string, 4, test_file);
//    printf("%s\n", string);
////    rewind(test_file);文件指针回到文件头
////    fseek(test_file, -1,SEEK_CUR); 随机选位置
////    ftell(test_file);
//
//    ch = fgetc(test_file);
//    printf("%c", ch);

//}
//    fgets(input_buff,sizeof(string),test_file);
//    !feof(test_file)
//    printf("%s", input_buff);
//    printf("---------------------------------------------------------");
//    fgets(input_buff,sizeof(string),test_file);
//    printf("%s", input_buff);
//    fclose(test_file);
//    fputc('\n', test_file);
//    fputc('\n', test_file);
//    printf("Pleas input a string");
//    gets(string); //从控制台获取一个字符串，存在string里面以'\n'判断结束
//
//
//    fputs(string, test_file);//向文件里写字符串
//    return 0;




//int main(){
//    FILE *input_file, *output_file;
//    char ch;
//    if ((input_file = fopen(  "D:\\Projcet\\C_projec\\FileProcess\\test.txt", "r"))==NULL){
//        printf("File Open Error!");
//        exit(0);
//    }
//
//    if ((output_file = fopen(  "D:\\Projcet\\C_projec\\FileProcess\\output.txt", "w"))==NULL){
//        printf("File Open Error!");
//        exit(0);
//    }
//    printf("file open success!\n");
//
//    for (;(ch= fgetc(input_file))!=EOF;)
//    {
//        fputc(ch, output_file);
//    }
//
//    printf("file copy end\n");
//    fclose(input_file);
//    fclose(output_file);
//
//    return 0;
//}




// 文本文件 二进制文件

//int main(){
//    FILE * test_file;
//    char ch1 ;
//    if ((test_file = fopen(  "D:\\Projcet\\C_projec\\FileProcess\\test.txt", "a"))==NULL){
//        printf("File Open Error!");
//        exit(0);
//    }// r+ w+ a()
//    printf("Please input a string:");
//    for (; (ch1 =getchar())!='#';){
//        fputc(ch1,test_file);
//    }
//    fclose(test_file);
// 在控制台中输入字符串，保存在文件中，字符串以‘#’结束；
//getchar()

// 完成文件的复制

//}
//
//int main() {
//    FILE *test_file;
//    char ch;
//    char string_input[MaxLength],string_output[MaxLength];
//    if ((test_file = fopen("../test.txt", "r")) == NULL) {
//        printf("FIle Open Error!");
//    }
//    for (;(ch=getchar())!='@';)
//    {
//        fputc(ch,test_file);
//    }

//    for(;(ch= fgetc(test_file)) != EOF;){
//        putchar(ch) ;
//    }
//    fclose(test_file);


//    printf("please input a string");
//    gets(string);
//    fputs(string, test_file);
//
//    fclose(test_file);

/* */
//    fgets(string_output, 11, test_file);
//
//    printf("%s",string_output );

//    fread(string_output, 10,1,test_file);
//    printf("%s",string_output);
//
//
//    return 0;
//}
//int count(int *point)
//{
//    int counter = 0;
//    while (*point)
//    {
//        if (*point == 1)
//        {
//            counter++;
//        }
//        point++;
//    }
//    return counter;
//}

//int fun_b_demo(void)
//{
//    int sum = 0;
//    int b[99];
//    int x = 0;
//    int target = 0;
//    int scanner1 = 0;//scanner of '1'
//    sum = 13;
//    printf("enter number of people:");
//    scanf("%d", &sum);
//    for (int i = 0; i < sum; i++)
//    {
//        b[i] = 1;
//    }
//    x = 6;
//    printf("enter the serial number of one person:");
//    scanf("%d", &x);
//    for(int i = 0; count(b) > 1; i++)
//    {
//        if (x + i + 1 >= sum)
//        {
//            x = x  - sum;
//        }
//        if(b[x + i + 1] == 1)
//        {
//            scanner1++;
//        }
//        if ((scanner1 + 1) % 3 == 0)
//        {
//            b[x + i + 1] = -1;
//        }
//    }
//
//    for (int i = 0; i < sum; i++)
//    {
//        printf("%d ", b[i]);
//        if (b[i] == 1)
//        {
//            target = i;
//        }
//    }
//
//    printf("\nlast serial number: %d", target);
//    return 0;
//}
