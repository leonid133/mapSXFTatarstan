#ifndef CODEPAGE_H
#define CODEPAGE_H
#include <lib/all.h>

namespace codepage
{
    std::string ansi_to_utf8(const std::string ansi);
    std::wstring utf8_to_wstring(const std::string utf8);
};

#endif // CODEPAGE_H
