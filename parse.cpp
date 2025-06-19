#include <vector>
#include <string>
#include <sstream>
#include "tinyshell.h"

using namespace std;

static vector<string> split(const string& s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream stream(s);
    while (getline(stream, token, delimiter))
    {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

vector<vector<string>> parse(const string& line)
{
    auto piped = split(line, '|');
    vector<vector<string>> result;
    pipe_count = piped.size() - 1;
    for (auto& cmd : piped)
        result.push_back(split(cmd, ' '));
    return result;
}
