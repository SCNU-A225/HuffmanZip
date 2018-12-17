#ifndef ZIP_H
#define ZIP_H

/*
ZIP
压缩工具类
用于提供压缩、解压以及一些其他方法。
*/
class ZIP
{
public:
    static void encode(char* srcPath, char* dstPath);//压缩
    static void decode(char* zipPath);//解压
    static char* getFileName(char* path);//获取文件名
private:
    ZIP();
};

#endif // ZIP_H
