// pa2.cpp

// COMP2011 (Fall 2020)
// Assignment 2: Subtring Pattern Matching
//
// Name: YANG Jingwen
// Student ID: 20677029
// Email: jyangbv@connect.ust.hk

#include <iostream>
#include <limits>
#include <assert.h>

using namespace std;

// C string termination character
const char NULL_CHAR = '\0';

// The "not found" flag
const int NOT_FOUND = -1;

// Single character wildcard
const char DOT = '.';

// Zero or single character wildcard
const char QMARK = '?';

// Zero or more character wildcard
const char PERCENT = '%';

// Matches the beginning of a string
const char CARET = '^';

int matchSub(const char str[], const char pattern[], int &length, int start);
int matchSubWithDot(const char str[], const char pattern[], int &length, int start);
int matchSubWithQmark(const char str[], const char pattern[], int &length, int start);
int matchSubWithPercent(const char str[], const char pattern[], int &length, int start);
int findSubLenAtStrPosWithDot(const char str[], const char pattern[], int strPos, int patPos);

// Declare additional helper functions below when necessary
// Find remaining elements in str[]
int findStrLastElement(const char str[], int strPos)
{
    if (str[strPos] != NULL_CHAR)
        return 1 + findStrLastElement(str, strPos + 1);
    else
        return 0;
}

// Pair wildcards to the most characters
int findWildcardMatchPosition(const char str[], const char pattern[], int strPos, int patPos, int wildcardmin, int wildcardmax, int postvalue, int MatchPos = -1)
{
    int wildcardcount;
    if (wildcardmax == -1) // wildcardmax = -1: wildcardmax = remaining str length
    {
        wildcardcount = findStrLastElement(str, strPos) + postvalue; // wildcardcount = length from wildcardmin to end of string - postvalue
        //cout << "Remaining elements: " << findStrLastElement(str, strPos) << ". Wildcardmin: " << wildcardmin << ". Postvalue: " << postvalue << endl;
    }
    else
        wildcardcount = wildcardmax - wildcardmin + postvalue;

    if (wildcardcount == 0 || str[strPos] == NULL_CHAR) // Case 0: out of bound
    {
        //cout << "Subcase 0" << endl;
        return MatchPos;
    }
    else if (pattern[patPos] != str[strPos]) // Case 1: no match
    {
        //cout << "Subcase 1" << endl;
        if (str[strPos + 1] == NULL_CHAR)
            return MatchPos;
        
        if (wildcardmax != -1)
            return findWildcardMatchPosition(str, pattern, strPos + 1, patPos, wildcardmin, --wildcardmax, postvalue, MatchPos);
        else
            return findWildcardMatchPosition(str, pattern, strPos + 1, patPos, wildcardmin, wildcardmax, postvalue, MatchPos);
    }
    else // Case 2: match
    {
        //cout << "Subcase 2, strPos: " << strPos << endl;
        MatchPos = strPos;
        if (wildcardmax != -1)
            return findWildcardMatchPosition(str, pattern, strPos + 1, patPos, wildcardmin, --wildcardmax, postvalue, MatchPos);
        else
            return findWildcardMatchPosition(str, pattern, strPos + 1, patPos, wildcardmin, wildcardmax, postvalue, MatchPos);
    }
}

// Task 1,2,3 Recursion
int findSubLenAtStrPos(const char str[], const char pattern[], int strPos = 0, int patPos = 0, int wildcardmin = 0, int wildcardmax = 0, int postvalue = 0)
{
    if (pattern[patPos] != PERCENT && pattern[patPos] != QMARK && str[strPos] == NULL_CHAR)
        return NOT_FOUND;
    
    if (pattern[patPos] == CARET) // Case 1: CARET
    {
        //cout << "Case 1" << endl;
        strPos = 0;
        return findSubLenAtStrPos(str, pattern, strPos, patPos + 1);
    }
    else if (pattern[patPos] == DOT) // Case 2: DOT
    {
        //cout << "Case 2" << endl;
        if (wildcardmax != -1)
            ++wildcardmax;
        if (str[strPos] == NULL_CHAR && pattern[patPos + 1] == NULL_CHAR)
            return NOT_FOUND;
        return findSubLenAtStrPos(str, pattern, strPos, patPos + 1, ++wildcardmin, wildcardmax);
    }
    else if (pattern[patPos] == QMARK) // Case 3: QMARK
    {
        //cout << "Case 3" << endl;
        if (wildcardmax != -1)
            ++wildcardmax;
        if (str[strPos] == NULL_CHAR && pattern[patPos + 1] == NULL_CHAR)
            return 0;
        return findSubLenAtStrPos(str, pattern, strPos, patPos + 1, wildcardmin, wildcardmax);
    }
    else if (pattern[patPos] == PERCENT) // Case 4: PERCENT
    {
        //cout << "Case 4" << endl;
        if (str[strPos] == NULL_CHAR && pattern[patPos + 1] == NULL_CHAR)
            return 0;
        return findSubLenAtStrPos(str, pattern, strPos, patPos + 1, wildcardmin, -1); // -1, infinite wildcards
    }
    else if (pattern[patPos] == NULL_CHAR && (pattern[patPos - 1] == DOT || pattern[patPos - 1] == QMARK || pattern[patPos - 1] == PERCENT)) // Case 5a: NULLCHAR, after wildcard
    {
        //cout << "Case 5" << endl;
        int remainstrlength = findStrLastElement(str, strPos);
        if (remainstrlength < wildcardmin)
            return NOT_FOUND;
        else if (wildcardmax != -1)
            return (wildcardmax > remainstrlength) ? remainstrlength : wildcardmax;
        else
            return remainstrlength;
    }
    else if (pattern[patPos] != NULL_CHAR && pattern[patPos - 1] != DOT && pattern[patPos - 1] != QMARK && pattern[patPos - 1] != PERCENT) // Case 6a: character, no wildcard
    {
        if (pattern[patPos] == str[strPos]) // character match 
        {
            //cout << "Case 6a, match" << endl;
            if (pattern[patPos + 1] == NULL_CHAR) // NULLCHAR next in pattern 
                return 1;
            
            if (str[strPos + 1] == NULL_CHAR && (pattern[patPos + 1] == DOT || pattern[patPos + 1] == QMARK || pattern[patPos + 1] == PERCENT)) // str next NULLCHAR, pattern next not NULLCHAR
            {
                int result = findSubLenAtStrPos(str, pattern, strPos + 1, patPos + 1);
                if (result != NOT_FOUND)
                    return 1 + result;
            }

            int result = findSubLenAtStrPos(str, pattern, strPos + 1, patPos + 1);
            if (result != NOT_FOUND)
                return 1 + result;
        }
        //cout << "Case 6a, no match" << endl;
    }
    else if (pattern[patPos] != NULL_CHAR && (pattern[patPos - 1] == DOT || pattern[patPos - 1] == QMARK || pattern[patPos - 1] == PERCENT)) // Case 6b: charcater, after wildcard
    {
        //cout << "Case 6b" << endl;
        int find;
        if (wildcardmax != -1)
            find = findWildcardMatchPosition(str, pattern, strPos + wildcardmin, patPos, wildcardmin, wildcardmax + 1, postvalue); // TAKE NOTE: strPos is indexed to the first valid value
        else // wildcardmax == -1
            find = findWildcardMatchPosition(str, pattern, strPos + wildcardmin, patPos, wildcardmin, wildcardmax, postvalue); // TAKE NOTE: strPos is indexed to the first valid value

        //cout << "Wildcardmin: " << wildcardmin << " Wildcardmax: " << wildcardmax << " Find: " << find << endl;

        if (find == -1) // No match
            return NOT_FOUND;
        else if (pattern[patPos + 1] == NULL_CHAR) // End of pattern, match
            return find - strPos + 1;
        else if (str[strPos + 1] == NULL_CHAR) // End of str, check if it matches with remaining pattern
        {
            int result = findSubLenAtStrPos(str, pattern, strPos + 1, patPos + 1);
            if (result != NOT_FOUND) // remaining pattern are wildcards, result = 0
                return 1;
            else // find a smaller match
                return findSubLenAtStrPos(str, pattern, strPos, patPos, wildcardmin, wildcardmax, --postvalue);
        }
        else // a match
        {
            int result = findSubLenAtStrPos(str, pattern, find + 1, patPos + 1);
            if (result != NOT_FOUND)
                return find - strPos + 1 + result;
            else // find a smaller match
                return findSubLenAtStrPos(str, pattern, strPos, patPos, wildcardmin, wildcardmax, --postvalue);
        }
    }
    return NOT_FOUND;
}
// Helper for Task 0.
// Returns the length of the substring in `str` located at `strPos` that
// matches `pattern`.
// If `pattern` is not found, returns the value `NOT_FOUND`.
// The `pattern` may contain the single character wildcard (`.`).
int findSubLenAtStrPosWithDot(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    if (pattern[patPos] != NULL_CHAR && str[strPos] == NULL_CHAR) // the substring is shorter than the pattern to match
        return NOT_FOUND;
    if (pattern[patPos] == DOT || pattern[patPos] == str[strPos]) // character match, DOT
    {
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithDot(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                      // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    return NOT_FOUND;
}

// Task 0 (0 point)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the length of the substring matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the single character wildcard (`.`).
int matchSubWithDot(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithDot(str, pattern, start);
    if (testLength != NOT_FOUND)
    {
        length = testLength;
        return start;
    }
    return matchSubWithDot(str, pattern, length, start + 1);
}

// Task 1 (40 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the zero or single character wildcard (`?`).
int matchSubWithQmark(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testlength = findSubLenAtStrPos(str, pattern, start);
    if (testlength != NOT_FOUND)
    {
        length = testlength;
        return start;
    }
    return matchSubWithQmark(str, pattern, length, start + 1);
}

// Task 2 (35 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the zero or more character wildcard (`%`).
int matchSubWithPercent(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testlength = findSubLenAtStrPos(str, pattern, start);
    if (testlength != NOT_FOUND)
    {
        length = testlength;
        return start;
    }
    return matchSubWithPercent(str, pattern, length, start + 1);
}

// Task 3 (25 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the '^', '.', '?', and '%' wildcards.
int matchSub(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testlength = findSubLenAtStrPos(str, pattern, start);
    if (testlength != NOT_FOUND)
    {
        length = testlength;
        return start;
    }
    return matchSub(str, pattern, length, start + 1);
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

// Given `str`, prints the substring that begins at `start` with length `length`.
// Raises an assertion error when an attempt is made to print beyond the available length.
// You are not allowed to use loops in your solution, though we use them here.
void printString(const char str[], const int start, const int length)
{
    for (int i = start; i < start + length; i++)
        assert(str[i] != NULL_CHAR);
    for (int i = start; i < start + length; i++)
        cout << str[i];
}

// A driver program for testing your solution.
int main()
{
    const int MAX_LENGTH = 1000;
    char pattern[MAX_LENGTH];
    char str[MAX_LENGTH];
    int option, pos, length;

    while (true)
    {
        cout << "Task No. (-1 to exit): "; cin >> option;
        if (cin.fail())
        {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (option == -1)
            break;
        if (option < 0 || option > 3)
            continue;
        cout << endl;
        cout << "Enter the string to match: "; cin >> str;
        cout << "Enter the pattern to match: "; cin >> pattern;
        length = 0;
        switch (option)
        {
            case 0:
                pos = matchSubWithDot(str, pattern, length);
                break;
            case 1:
                pos = matchSubWithQmark(str, pattern, length);
                break;
            case 2:
                pos = matchSubWithPercent(str, pattern, length);
                break;
            case 3:
                pos = matchSub(str, pattern, length);
                break;
        }
        cout << endl;
        if (pos == NOT_FOUND)
        {
            cout << "Pattern is not found." << endl;
        }
        else
        {
            cout << "Pattern's first occurence is at " << pos << ", with longest possible length = " << length << "." << endl;
            cout << "Matched substring is '"; printString(str, pos, length); cout << "'." << endl;
        }
        cout << "---------------------------------------------------------------------" << endl;
    }
    cout << "bye" << endl;
}
