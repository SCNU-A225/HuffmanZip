#ifndef ZIP_H
#define ZIP_H
#include <fstream>
#include <QProgressDialog>
/*
ZIP
压缩工具类
用于提供压缩、解压以及一些其他方法。
*/
class ZIP
{
public:
    static void encode(const char* srcPath, const char* dstPath,QProgressDialog* progress);//压缩
    static void decode(const char* zipPath, const char *dstPath, QProgressDialog* progress);//解压
    static char* getFileName(const char* path);//分离出文件名
    static char* getZipFileName(const char* path);//获取源文件名
    static bool checkZip(FILE* f);//检查压缩文件合法性
    static bool UTF8ToUnicode(const char* UTF8, wchar_t* strUnicode);//字符转换
private:
    ZIP();
};

#endif // ZIP_H
