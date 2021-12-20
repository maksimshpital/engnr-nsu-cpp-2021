#include "other.h"


int main(int args, char *argv[])
{
    ifstream file;
    string help, path, mode;
    help = "You can use: ./hasher -m <mode> <filename> or ./hasher <filename> -m <mode>. \n<mode> is adler32 or sum64";
    if (args == 2)
    {
        if (!strcmp(argv[1], "-h"))
        {
            cout << help << endl;
            return 0;
        }
        else
        {
            cerr << "Error, invalid command. " << endl
                 << help << endl;
            return 1;
        }
    }
    else if (args == 4)
    {
        if (not(strcmp(argv[1], "-m")) && (not(strcmp(argv[2], "adler32")) || not(strcmp(argv[2], "sum64"))))
        {
            mode = argv[2];
            path = argv[3];
        }
        else if (not(strcmp(argv[2], "-m")) && (not(strcmp(argv[3], "adler32")) || not(strcmp(argv[3], "sum64"))))
        {
            mode = argv[3];
            path = argv[1];
        }
        else
        {
            cerr << "Error, wrong arguments" << endl
                 << help << endl;
            return 1;
        }
    }
    else
    {
        if (args == 1)
        {
            cerr << "Error, no arguments" << endl
                 << help << endl;
            return 1;
        }
        else
        {
            cerr << "Error, unknown command" << endl
                 << help << endl;
            return 1;
        }
    }

    file.open(path, ios_base::binary);

    if (!(file.is_open()))
    {
        cerr << "Error, file is not found" << endl
             << help << endl;
        return 1;
    }
    if (file.peek() == EOF)
    {
        if (mode == "adler32")
        {
            cout << 1 << endl;
        }
        if (mode == "sum64")
        {
            cout << 0 << endl;
        }
        return 0;
    }

    try
    {
        if (mode == "adler32")
        {
            uint32_t hash = adler32(file);
            cout << hex << hash << endl;
        }
        if (mode == "sum64")
        {
            cout << hex << sum64(file) << endl;
        }
    }
    catch (exception &error)
    {
        cerr << error.what();
        return 1;
    }
    return 0;
}