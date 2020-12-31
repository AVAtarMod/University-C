#ifndef STRING
#define STRING

namespace cstr
{
    char getSymbolUser(const char *text = " ");
    char *getStringUser(bool isLine);

    int countWords(char *string);
    int *indexSymbols(char *string, char symbol, int &count);

    void changeCase(char *string);
    int *countSymbols(char *str, int &sizeArray);
    void replace(char *string, int *indexes, int lengthIndexes, char symbol);
    void print(const char *string);
    void doOffset(char *string, int offset);
    bool isPalindrome(char *str);
} // namespace cstr

namespace classStr
{
    using std::string;
    //////////////////////////////

    string getString(bool isLine);

    uint16_t countWords(string str);

    uint8_t *indexSymbols(string str, char symbol, uint8_t &numberMatches);

    int *countSymbols(string str, int &sizeArray);
    void changeCase(string &str);
    int *countSymbols(string str, int &sizeArray);
    void replace(string &str, uint8_t *indexes, uint8_t numberReplaces, char replace);
    void print(string str);
    bool isPalindrome(string str);
} // namespace classStr

#endif