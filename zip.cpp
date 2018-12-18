#include "zip.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <huffmantree.h>
#include <string.h>
#include <map>
#include <deque>
#include <QDebug>

ZIP::ZIP()
{

}

/*
压缩
将目标文件压缩到指定路径
char* srcPath: 被压缩的文件路径
char* dstPath: 压缩到的文件路径
*/
void ZIP::encode(const char* srcPath, const char* dstPath)
{
    FILE *fin = fopen(srcPath, "rb");//被压文件
    FILE *fout = fopen(dstPath, "wb");//压缩后的文件
    if(!fin)
    {
        qDebug()<<"压缩失败！不能打开被压文件！"<<endl;
        throw runtime_error("不能打开被压文件！\n请检查选择文件路径");
    }
    else if(!fout)
    {
        qDebug()<<"压缩失败！不能打开目标文件！"<<endl;
        throw runtime_error("不能打开目标文件！\n请检查压缩到路径");
    }

    char* fileName = getFileName(srcPath);//获取文件名
    int fileNameLen;//文件名长度
    if((fileNameLen=strlen(fileName)) >= 256)
    {
        qDebug()<<"压缩失败！文件【"<<fileName<<"】文件名过长！"<<endl;
        return;
    }

    fputc(fileNameLen,fout);//将文件名长度写入压缩文件中
    fputs(fileName,fout);//将文件名也写入到压缩文件中

    //建立哈夫曼树
    int c,weights[256];
    memset(weights,0,sizeof(weights));
    while (true) {
        c = fgetc(fin);
        if(feof(fin)) break;
        weights[c]++;
    }
    HuffmanTree tree(weights);

    //将权值数组写入压缩文件中
    fwrite(&weights, sizeof(weights[0]), 256, fout);
    //delete[] &weights;

    {//压缩文件数据
        map<int,string> codeTable = tree.getCodeTable();//获取编码表
        fseek(fin,0,SEEK_SET);//重新开始读取被压文件
        string codes = "";//待压缩的二进制数据，用string临时存储
        int len = 0;//用于存储codes长度
        while (true) {
            c = fgetc(fin);
            if(feof(fin)) break;//文件结束 退出
            codes += codeTable[c];//通过编码表获得编码
            while((len=codes.length())>=8)//每满8个二进制位就存储一次
            {
                //将二进制转为0-255之间的数字
                int temp = 0;
                for(int i=0;i<8;i++)
                {
                    temp<<=1;
                    temp |= (codes[i]-'0');
                }
                //字符串缩短
                codes = codes.substr(8,len-8);
                //将压缩后的数据写入
                fputc(temp,fout);
            }
        }
        //写入最后不满8位的数据，用0补齐
        int temp = 0;
        for(int i=0;i<len;i++)
        {
            temp<<=1;
            temp |= (codes[i]-'0');
        }
        for(int i=0;i<8-len;i++)
            temp<<=1;
        fputc(temp,fout);
        //写入最后剩余的位数
        fputc(len,fout);
    }

    //关闭文件
    fclose(fin);
    fclose(fout);

    //释放内存
    delete[] fileName;
}

/*
解压
char* zipPath: 压缩文件路径
char* dstDir: 解压的目标文件夹
char* fileNam: 文件名
*/
void ZIP::decode(const char* zipPath, const char* dstDir, const char* fileName)
{
    FILE *fin = fopen(zipPath, "rb");//打开压缩文件

    int fileNameLen = fgetc(fin);//获取文件名长度
    char* dstPath= new char[strlen(dstDir)+strlen(fileName)+1];//解压路径
    fseek(fin,fileNameLen,SEEK_CUR);
    memset(dstPath,0,sizeof(dstPath));//路径清空
    //生成解压路径
    strcat(dstPath,dstDir);
    strcat(dstPath,fileName);

    //todo: 替换提醒
    FILE *fout = fopen(dstPath, "wb");//打开解压文件

    //todo: 路径合法性检测
    if(!fin)
    {
        qDebug()<<"解压失败！不能打开压缩文件！"<<endl;
        throw runtime_error("不能打开压缩文件！\n请检查压缩文件路径！");
    }
    else if(!fout)
    {
        qDebug()<<"解压失败！不能打开目标解压文件！"<<endl;
        throw runtime_error("不能打开目标解压文件！\n请检查命名以及解压到路径！");
    }

    //重新读取权值数组，重建哈夫曼树
    int weights[256];
    fread(weights, sizeof(weights[0]), 256, fin);
    HuffmanTree tree(weights);

    //获取编码，进行解码
    deque<char> codeQueue;//01序列
    register int c1,c2=fgetc(fin);//用于临时储存压缩文件数据
    char c;//用于临时存储序列数据
    HuffmanTreeNode *root,*now;//root为哈夫曼树根节点地址，now为工作地址
    root = now = tree.getRoot();
    map<int,string> codeTable = tree.getCodeTable();//获取编码表
    while(true)//解码
    {
        while(codeQueue.size()!=0)//当序列不为空，不断走哈夫曼树解码
        {
            c = codeQueue.front();
            codeQueue.pop_front();
            if(c=='0' && now->lchild) now=now->lchild;
            else if(c=='1' && now->rchild) now=now->rchild;
            if(now->lchild==nullptr && now->rchild==nullptr)
            {
                //todo: 数据正确性判断
                fputc(now->data,fout);//找到叶子节点，存入对应数据
                now = root;
            }
        }
        while(!feof(fin) && codeQueue.size()<=128)//获取数据，规定每次获取上限减少内存使用
        {
            c1 = c2;
            c2 = fgetc(fin);
            if(feof(fin))//若文件结束，清空多余的位数
            {
                for(int i=0;i<8-c1;i++)
                    codeQueue.pop_back();
                break;
            }
            for(int i=7;i>=0;i--)//重新转化为二进制，并加入到序列
            {
                if(c1&(1<<i)) codeQueue.push_back('1');
                else codeQueue.push_back('0');
            }
        }
        if(feof(fin)&&codeQueue.size()==0) break;//处理结束
    }

    //关闭文件
    fclose(fin);
    fclose(fout);

    //释放内存
    delete[] dstPath;
}

/*
分离出文件名（包括扩展名）
char* path: 文件路径
return: char* 文件名
*/
char* ZIP::getFileName(const char* path)
{
    int idx=-1,len=strlen(path);
    for(int i=0;i<len;i++)//获取最后的文件夹分隔符
    {
        if(path[i]=='/' || path[i]=='\\')
            idx = i;
    }
    char *fileName = new char[len-idx+1];
    if(idx!=-1)//若有分隔符，则切割
    {
        strcpy(fileName,path+idx+1);
    }
    else
    {
        strcpy(fileName,path);
    }
    return fileName;
}

/*
获取源文件名
char* path: 压缩文件路径
return: char* 原文件名
*/
char *ZIP::getZipFileName(const char* path)
{
    FILE *fin = fopen(path, "rb");//打开压缩文件
    int fileNameLen = fgetc(fin);//获取文件名长度
    char* fileName = new char[fileNameLen+2];//用于储存文件名
    fgets(fileName,fileNameLen+1,fin);//获取被压文件名
    if(ferror(fin)) throw runtime_error("文件读取失败");
    fclose(fin);
    return fileName;
}
