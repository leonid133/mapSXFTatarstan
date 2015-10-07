#include <lib/file.h>
#include <lib/all.h>

CFile::CFile(const string fname)
{
    fl = NULL;
    fl = fopen(fname.c_str(), "rb");
    //throw_null(fl = fopen(fname.c_str(), "rb"));
}
/*
CFile::CFile(const QString qfname)
{
    string fname = qfname.toStdString();
    fl = NULL;
    fl = fopen(fname.c_str(), "rb");
    //throw_null(fl = fopen(fname.c_str(), "rb"));
}
*/
CFile::~CFile()
{
    if(fl != NULL)
        fclose(fl);
}

void CFile::operator()(void * buf, const size_t size)
{
    fread(buf, 1, size, fl) != size;
    //throw_if(fread(buf, 1, size, fl) != size);
}

void CFile::seek(const uint32_t offset)
{
    fseek(fl, offset, SEEK_SET);
    //throw_if(fseek(fl, offset, SEEK_SET));
}

long CFile::offset()
{
    return ftell(fl);
}


