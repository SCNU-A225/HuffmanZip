#include "zip.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <huffmantree.h>
#include <string.h>
#include <map>
#include <deque>

ZIP::ZIP()
{

}

void ZIP::encode(char* srcPath, char* dstPath)
{
    FILE *fin = fopen(srcPath, "rb");
    FILE *fout = fopen(dstPath, "wb");
    if(!fin || !fout)
    {
        cout<<"压缩失败！"<<endl<<"参数有误"<<endl;
        return;
    }

    char* fileName = getFileName(srcPath);
    int fileNameLen;
    if((fileNameLen=strlen(fileName)) >= 256)
    {
        cout<<"压缩失败！"<<endl<<"文件【"<<fileName<<"】文件名过长！"<<endl;
        return;
    }
    fputc(fileNameLen,fout);
    fputs(fileName,fout);
    delete[] fileName;

    int c,weights[256];
    memset(weights,0,sizeof(weights));
    while (true) {
        c = fgetc(fin);
        if(feof(fin)) break;
        weights[c]++;
    }

    HuffmanTree tree(weights);

    fwrite(&weights, sizeof(weights[0]), 256, fout);
    delete[] weights;

    {
        map<int,string> codeTable = tree.getCodeTable();
        fseek(fin,0,SEEK_SET);
        string codes = "";
        int len = 0;
        while (true) {
            c = fgetc(fin);
            if(feof(fin)) break;
            codes += codeTable[c];
            while((len=codes.length())>=8)
            {
                int temp = 0;
                for(int i=0;i<8;i++)
                {
                    temp<<=1;
                    temp |= (codes[i]-'0');
                }
                codes = codes.substr(8,len-8);
                fputc(temp,fout);
            }
        }
        int temp = 0;
        for(int i=0;i<len;i++)
        {
            temp<<=1;
            temp |= (codes[i]-'0');
        }
        for(int i=0;i<8-len;i++)
            temp<<=1;
        fputc(temp,fout);
        fputc(len,fout);

        fclose(fin);
        fclose(fout);
    }
}

void ZIP::decode(char* zipPath)
{
    FILE *fin = fopen(zipPath, "rb");

    int fileNameLen = fgetc(fin);
    char* fileName = new char[fileNameLen+2];
    fgets(fileName,fileNameLen+1,fin);
    char dstDir[] = "./";
    char* dstPath = new char[strlen(dstDir)+strlen(fileName)+1];
    memset(dstPath,0,sizeof(dstPath));
    strcat(dstPath,dstDir);
    strcat(dstPath,fileName);




    FILE *fout = fopen(dstPath, "wb");
    if(!fin || !fout)
    {
        cout<<"参数有误"<<endl;
        return;
    }



    int weights[256];
    fread(weights, sizeof(weights[0]), 256, fin);
    HuffmanTree tree(weights);


    deque<char> codeQueue;
    register int c1,c2=fgetc(fin);
    char c;
    HuffmanTreeNode *root,*now;
    root = now = tree.getRoot();
    map<int,string> codeTable = tree.getCodeTable();
    while(true)
    {
        while(codeQueue.size()!=0)
        {
            c = codeQueue.front();
            codeQueue.pop_front();
            if(c=='0' && now->lchild) now=now->lchild;
            else if(c=='1' && now->rchild) now=now->rchild;
            if(now->lchild==NULL && now->rchild==NULL)
            {
                fputc(now->data,fout);
                now = root;
            }
        }
        while(!feof(fin) && codeQueue.size()<=128)
        {
            c1 = c2;
            c2 = fgetc(fin);
            if(feof(fin))
            {
                for(int i=0;i<8-c1;i++)
                    codeQueue.pop_back();
                break;
            }
            for(int i=7;i>=0;i--)
            {
                if(c1&(1<<i)) codeQueue.push_back('1');
                else codeQueue.push_back('0');
            }
        }
        if(feof(fin)&&codeQueue.size()==0) break;
    }
    fclose(fin);
    fclose(fout);


}

char* ZIP::getFileName(char* path)
{
    int idx=-1,len=strlen(path);
    for(int i=0;i<len;i++)
    {
        if(path[i]=='/' || path[i]=='\\')
            idx = i;
    }
    if(idx!=-1)
    {
        char *fileName = new char[len-idx+1];
        strcpy(fileName,path+idx+1);
        return fileName;
    }
    else
        return path;
}
