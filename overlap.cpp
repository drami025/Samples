#include <iostream>
#include <string>
#include <vector>

using namespace std;

void readKeyWords (const vector<string>&);
int overlapCheck (string, string);

int main()
{
    //keystrings vector saves the 3 key words needed to compare to other words.
    //keys vector saves the words that overlap with the 3 individual keys
    // the most.
    //overlap vector saves the amount of overlap the closely overlapped words
    // have.
    vector <string> keyStrings;
    vector <string> keys(3, "");
    vector <int> overlap(3, 0);
    string keyWord, tempWord;

    //first the three key words are read in.
    readKeyWords(keyStrings);

    //after that, the rest of the words from the input.txt are read in with 
    // this loop.
    while (cin >> keyWord)
    {
        //When the first word from the input.txt is read, it is compared to 
        // all the 3 key words. The first inputted word after the keystrings 
        // is saved into the overlap and keys vectors. After that, only a word
        // with more overlap is saved into them.
        for (int i = 0; i < 3; i++)
        {
            tempWord = keyStrings.at(i);
            if(overlap.at(i) < overlapCheck(tempWord, keyWord))
            {
                overlap.at(i) = overlapCheck(tempWord, keyWord);
                keys.at(i) = keyWord;
            }
        }
    }
    
    // the keys and words with the most overlapped is read out (if any).
    for (int i = 0; i < 3; i++)
    {
        cout << "Key: " << keyStrings.at(i) << endl;
        cout << "Match: ";
        
        if (keys.at(i) != "")
            cout << keys.at(i) << endl;
        else
            cout << "No Match" << endl;
            
        cout << "Overlap: " << overlap.at(i) << endl << endl;
    }
    return 0;
}

/// @brief Assigns the 3 key words into vector parameter.
/// @param keyStrings vector that will hold the 3 key words.
void readKeyWords (const vector<string>& keyStrings)
{
    string keyWord;
    
    for (int i = 0; i < 3; i++)
    {
        cin >> keyWord;
        keyStrings.push_back(keyWord);
    }
}

/// @brief Checks how much overlap there is between the two parameters
///
///     The first loop checks the over lap in the front of the compared word
///     and saves the amount of overlap in count1. The second loop checks the 
///     overlap in the back of the compared word and saves the amount in count2.
///     
/// @param keyString one of the three key words to be compared to other words.
/// @param keyWord one of the words from the inputted text file.
/// @return the largest overlap amount of the two words, count1 or count2.
int overlapCheck (string keyString, string keyWord)
{
    int count1 = 0, count2 = 0, i = 0;
    string tempWord = keyWord;
    
    while (i < keyWord.size())
    {
        if (keyString.find(keyWord) != string::npos && 
            keyString.find(keyWord) == keyString.size() - keyWord.size())
        {
            count1 = keyWord.size();
            break;
        }
        else if(keyString.find(keyWord, keyString.size() - 1) != string::npos)
        {
            count1 = keyWord.size();
            break;
        }
        else
            keyWord.resize(keyWord.size() - 1);
    }
    
    keyWord = tempWord;
    
    while(i < keyWord.size())
    {
        if (keyString.find(keyWord) != string::npos && 
            keyString.find(keyWord) == 0)
        {
            count2 = keyWord.size();
            break;
        }
        else
        {
            for (int j = 0; j < keyWord.size() - 1; j++)
            {
                keyWord.at(j) = keyWord.at(j + 1);
            }
            keyWord.resize(keyWord.size() - 1);
        }
    }
    
    if (count1 >= count2)
        return count1;
    else if (count2 >= count1)
        return count2;
    else
        return 0;
}

