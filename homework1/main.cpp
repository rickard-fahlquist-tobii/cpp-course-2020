#include <iostream>
#include <fstream>
#include <algorithm>
#include <experimental/filesystem>

/* README
compile -> g++-8 -std=c++17 words.cpp -lstdc++ -lstdc++fs -o a.out
*/
using namespace std;
namespace fs = std::experimental::filesystem;

class ParseFile
{
public:
    ParseFile (string filename):filename_(filename)
    { cout << "ParseFile :" << filename_ << endl;
        fs_.open(filename_);
    }
    void parse()
    {
        for (string line; getline(fs_, line);)
        {
            cout << "ParseFile :" << line << endl;
            transform(line.begin(), line.end(), line.begin(), [](auto ch) -> auto { if (isalpha(ch)) return ch; return ' '; });
            cout << "ParseFile :" << line << endl;
        }
    }
private:
    string filename_;
    fstream fs_;
};


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << "Error: Missing file name parameter as option 1" << endl;
        return -1;
    }
    string filename = argv[1];
    if (!fs::exists(filename))
    {
        cout << "Error: "<< filename << " Not Found" << endl;
        return -1;
    }
    ParseFile pf(filename);
    pf.parse();


    return 0;
}