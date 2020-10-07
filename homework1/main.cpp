#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <random>
#include <chrono>

/* README
compile -> g++-8 -std=c++17 words.cpp -lstdc++ -lstdc++fs -o a.out
*/
using namespace std;
namespace fs = std::filesystem;

using namespace string_literals;

const char header[] = R"(
<html>
     <head> Dev's and Rick's awesome thing </head>
     <body>
     <h1>Word Freqs</h1>
)";

const char tail[] = R"(
    </body>
</html>
)";

class ParseFile
{
public:
    struct Stats
    {
        int numWords = 0;

    };

    ParseFile (string filename):filename_(filename)
    { cout << "ParseFile :" << filename_ << endl;
        fs_.open(filename_);
    }

    // (1)
    void parse(size_t minWordLength)
    {

        for (string line; getline(fs_, line);)
        {
            transform(line.begin(), line.end(), line.begin(), [](auto ch) -> auto {
                if (isalpha(ch)) {
                    return ch;
                }
                else {
                    return ' ';
                }
            });
            auto buf  = istringstream{line};
            for (string word; buf >> word;) {
                if (word.length() > minWordLength) {
                    ++db_[word];
                    numWords_++;
                }
            }
        }
    }

    // (2)
    void sort_and_keep_n(int n)
    {
        vector<pair<string, unsigned>> freqs{db_.begin(), db_.end()};

        partial_sort(freqs.begin(), freqs.begin() + n, freqs.end(), [](auto& lhs, auto& rhs){
            return lhs.second > rhs.second;
        });

        copy_n(freqs.begin(), n, back_inserter(sorted_));
    }

    // (3)
    void generate_html()
    {
        auto max = sorted_.front().second;
        auto min = sorted_.back().second;
        auto delta = max - min;

        transform(sorted_.begin(), sorted_.end(), sorted_.begin(), [delta, min](auto& p) {
            const auto normalized = (135. / delta) * (p.second - min) + 15.;
            return make_pair(p.first, static_cast<unsigned>(normalized));
        });

        transform(sorted_.begin(), sorted_.end(), back_inserter(spans_), [](auto& p){
            stringstream ss;
            ss << "<span style=\"font-size:" << p.second << "\">" << p.first << "</span>" << "\n";
            return ss.str();
        });

        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(spans_.begin(), spans_.end(), g);

        stringstream html;
        html << header;

        for (auto& span: spans_) {
            html << span;
        }
        html << tail;

        fstream out{"output.html"s, ios::out};
        out << html.str();
    }

    auto constexpr getNumWords() const {
        return numWords_;
    };

private:
    string filename_;
    fstream fs_;
    unordered_map<string, unsigned> db_;
    vector<pair<string, unsigned>> sorted_;
    vector<string> spans_;
    size_t numWords_ = 0;
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
    const auto start = std::chrono::system_clock::now();
    pf.parse(5);
    pf.sort_and_keep_n(50);
    pf.generate_html();
    const auto stop = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = stop - start;


    cout << "Processed " << pf.getNumWords() << " words in " << diff.count() << "seconds \n";


    return 0;
}