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
    static void encode(const char* srcPath, const char* dstPath);//压缩
    static void decode(const char* zipPath, const char *dstDir, const char* fileName);//解压
    static char* getFileName(const char* path);//分离出文件名
    static char* getZipFileName(const char* path);//获取源文件名
private:
    ZIP();
};

#endif // ZIP_H
