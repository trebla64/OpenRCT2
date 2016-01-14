extern "C"
{
    #include "../platform/platform.h"
}

#include "Console.hpp"

namespace Console
{
    void Write(char c)
    {
        fputc(c, stdout);
    }

    void Write(const utf8 * str)
    {
        fputs(str, stdout);
    }

    void WriteSpace(size_t count)
    {
        for (size_t i = 0; i < count; i++)
        {
            Write(' ');
        }
    }

    void WriteFormat(const utf8 * format, ...)
    {
        va_list args;

        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
    }

    void WriteLine()
    {
        puts("");
    }

    void WriteLine(const utf8 * str)
    {
        puts(str);
    }

    namespace Error
    {
        void Write(char c)
        {
            fputc(c, stderr);
        }

        void Write(const utf8 * str)
        {
            fputs(str, stderr);
        }

        void WriteFormat(const utf8 * format, ...)
        {
            va_list args;

            va_start(args, format);
            vfprintf(stderr, format, args);
            va_end(args);
        }

        void WriteLine()
        {
            fputs(platform_get_new_line(), stderr);
        }

        void WriteLine(const utf8 * str)
        {
            fputs(str, stderr);
            WriteLine();
        }
    }
}