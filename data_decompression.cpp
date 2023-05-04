#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
unordered_map<string,char> huffman_map = {
    {"1",'A'},
    {"00",'B'},
    {"01",'C'}
};
string compressed="1001011";
string decode(string compressed, unordered_map<string, char> huffman_map) {
    string decoded = "";
    string curr = "";
    for (char c : compressed) {
        curr += c;
        if (huffman_map.count(curr)) {
            decoded += huffman_map[curr];
            curr = "";
        }
    }
    return decoded;
}

int main(){
    string ans = decode(compressed,huffman_map);
    cout<<ans<<endl;
}