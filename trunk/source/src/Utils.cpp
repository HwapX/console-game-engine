#include "Utils.h"

string IntToStr(const uint32_t number, const uint8_t digits)
{
    string num;
    char cnum[16];
    itoa(number, cnum, 10);
    num = cnum;
    if(num.size() < digits)
    {
        num.insert(0, digits - num.size(), '0');
    }
    return(num);
}

string FloatToStr(const float number, const uint8_t digits)
{
    char num[25];
    string format = "%." + IntToStr(digits) + "f";
    sprintf(num, format.c_str(), number);
    return(num);
}

string BoolToStr(const bool expression, const string &yes, const string &no)
{
    if(expression)
    {
        return(yes);
    }
    else
    {
        return(no);
    }
}

string IntToHex(const uint32_t number, const uint8_t digits)
{
    string num;
    char cnum[16];
    itoa(number, cnum, 16);
    num = cnum;
    if(num.size() < digits)
    {
        num.insert(0, digits - num.size(), '0');
    }
    return(num);
}

string ToUpper(const string &text)
{
    string new_text;
    for(uint16_t i = 0; i < text.size(); ++i)
    {
        new_text+= toupper(text[i]);
    }
    return(new_text);
}

string ToLower(const string &text)
{
    string new_text;
    for(uint16_t i = 0; i < text.size(); ++i)
    {
        new_text+= tolower(text[i]);
    }
    return(new_text);
}

char ToUpper(char character)
{
    return(toupper(character));
}

char ToLower(char character)
{
    return(tolower(character));
}

bool FileExists(const string &filename)
{
    return(GetFileAttributes(filename.c_str()) != 0xFFFFFFFF);
}

uint32_t CompressRLE(const char data[], const uint32_t size, char **result)
{
    uint8_t count = 1;
    char current = 0;
    char next = 0;
    char pos = 0;

    for(uint32_t i = 0; i < size; ++i)
    {
        current = data[i];
        if(i < size)
            next = data[i + 1];
        //checar se este if pode ser acoplado ao outro
        if(i != size)
        {
            if(current == next && count < 255)
            {
                ++count;
            }
        }
        if(current != next || i == size)
        {
            for(uint8_t c = 0; c < count; ++c)
            {
                void *ptemp = NULL;

                ptemp = realloc((void*)(*result), pos + 1);
                if(ptemp != NULL)
                {
                    (*result) = (char*)ptemp;
                }
                else
                {
                    //error
                }

                (*result)[pos] = current;
                ++pos;

                if(c == 2)
                {
                    ptemp = NULL;

                    ptemp = realloc((void*)(*result), pos + 1);
                    if(ptemp != NULL)
                    {
                        (*result) = (char*)ptemp;
                    }
                    else
                    {
                        //error
                    }

                    (*result)[pos] = count - 3;
                    ++pos;
                    break;
                }
            }
            count = 1;
        }
    }

    return(pos);
}

uint32_t DecompressRLE(const char data[], const uint32_t size, char **result)
{
    uint8_t count = 1;
    char current = 0;
    char next = 0;
    uint32_t pos = 0;

    (*result) = NULL;

    for(uint32_t i = 0; i < size; ++i)
    {
        current = data[i];
        if(i < size)
            next = data[i + 1];

        if(current == next && i != size)
        {
            ++count;
        }
        else
        {
            if(count == 3)
            {
                ++i;
                //rever unsigned + signed
                count = count + (uint8_t)data[i];
            }
            for(uint8_t c = 0; c < count; ++c)
            {
                void *ptemp = NULL;

                ptemp = realloc((void*)(*result), pos + 1);
                if(ptemp != NULL)
                {
                    (*result) = (char*)ptemp;
                }
                else
                {
                    //error
                }
                (*result)[pos] = current;
                ++pos;
            }
            count = 1;
        }
    }
    return(pos);
}


bool CopyFile(string source, string dest)
{
    FILE *fsource = fopen(source.c_str(), "rb");

    if(fsource == NULL)
    {
        return(false);
    }

    if(FileExists(dest))
    {
        return(false);
    }

    FILE *fdest = fopen(dest.c_str(), "wb");

    if(fdest == NULL)
    {
        fclose(fsource);
        return(false);
    }

    int c = fgetc(fsource);

    while(c != EOF)
    {
        fputc(c, fdest);
        c = fgetc(fsource);
    };

    fclose(fsource);
    fclose(fdest);
    return(true);
}

int FindDataInFile(char filepath[], char data[], uint16_t size, int start)
{
    FILE *file = fopen(filepath, "rb");
    if(file == NULL)
    {
        return(-1);
    }

    unsigned short p = 0;
    int c = fgetc(file);
    fseek(file, start, 0);
    while(c != EOF)
    {
        if(data[p] == c)
        {
            p++;
        }
        else
        {
            p = 0;
        }
        if(p == size)
        {
            int result = ftell(file) - size;
            fclose(file);
            return(result);
        }

        c = fgetc(file);
    };


    fclose(file);

    return(-1);
}

bool CompareData(char data1[], char data2[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(data1[i] != data2[i])
        {
            return(false);
        }
    }
    return(true);
}

bool CompareFileData(char filepath[], int position, char data[], int size)
{
    FILE *file = fopen(filepath, "rb");

    if(file == NULL)
    {
        return(false);
    }

    fseek(file, position, SEEK_SET);

    for(int i = 0; i < size; i++)
    {
        int c = fgetc(file);
        if(c != EOF)
        {
            if(c != data[i])
            {
                fclose(file);
                return(false);
            }
        }
        else
        {
            fclose(file);
            return(false);
        }
    }
    fclose(file);
    return(true);
}

bool CompareFileWithFile(char filepath1[], int offset1, char filepath2[], int offset2, int size)
{
    FILE *file1 = fopen(filepath1, "rb");

    if(file1 == NULL)
    {
        return(false);
    }

    FILE *file2 = fopen(filepath2, "rb");

    if(file2 == NULL)
    {
        fclose(file1);
        return(false);
    }

    if(size == 0)
    {
        fseek(file2, 0, SEEK_END);
        size = ftell(file2);
    }

    fseek(file1, offset1, SEEK_SET);
    fseek(file2, offset2, SEEK_SET);



    for(int i = 0; i < size; i++)
    {
        int c1 = fgetc(file1);
        int c2 = fgetc(file2);
        if(c1 == EOF || c2 == EOF || c1 != c2)
        {
            fclose(file1);
            fclose(file2);
            return(false);
        }
    }

    fclose(file1);
    fclose(file2);
    return(true);
}

int GetResource(short resid, char type[], void **result)
{
    HRSRC hres = FindResource(NULL, MAKEINTRESOURCE(resid), RT_RCDATA);
    if(hres == NULL)
    {
        return(0);
    }
    HGLOBAL hgl = LoadResource(NULL, hres);
    if(hgl == NULL)
    {
        return(0);
    }
    void *res = LockResource(hgl);
    if(res == NULL)
    {
        return(0);
    }
    int ressize = SizeofResource(NULL, hres);
    if(ressize == 0)
    {
        return(0);
    }
    *result = res;
    return(ressize);
}
