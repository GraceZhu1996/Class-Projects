// WordChecker.cpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meecd pt
// the requirements.
#include "WordChecker.hpp"
#include <iostream>


WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
	return this->words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
	std::vector<std::string> result;
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::string temp;
// Swapping each adjacent pair of characters in the word.
	for (int i = 1; i < word.size(); ++i)
	{
		temp = word;
		std::swap(temp[i], temp[i-1]);
		if (wordExists(temp) && (std::find(result.begin(), result.end(), temp) == result.end()))
			result.push_back(temp);
	}

// In between each adjacent pair of characters in the word (also before the first character and after the last character), each letter from 'A' through 'Z' is inserted.

	temp = word;
	for (size_t a = 0; a < 26; ++a)
	{
		std::string temp2;
		for (size_t i = 0; i <= word.size(); ++i)
		{
			temp2 = temp;
			temp2.insert(i, alphabet.substr(a, 1));
			if (wordExists(temp2) && (std::find(result.begin(), result.end(), temp2) == result.end()))
				result.push_back(temp2);

		}
	}

// Deleting each character from the word.
	for (int i = 0; i < word.size(); ++i)
	{
		temp = word;
		temp = temp.erase(i,1);
		if (wordExists(temp) && (std::find(result.begin(), result.end(), temp) == result.end()))
			result.push_back(temp);
	}
// Replacing each character in the word with each letter from 'A' through 'Z'.
	temp = word;
	for (size_t a = 0; a < 26; ++a)
	{
		std::string temp2;
		for (size_t i = 0; i <= word.size(); ++i)
		{
			temp2 = temp;
			temp2.replace(i, 1, alphabet.substr(a, 1));
			if (wordExists(temp2) && (std::find(result.begin(), result.end(), temp2) == result.end()))
				result.push_back(temp2);

		}
	}
//Splitting the word into a pair of words by adding a space in between each adjacent pair of characters in the word.
// It should be noted that this will only generate a suggestion if both words in the pair are found in the word set.
	temp = word;
	std::string temp2;
	for (size_t i = 0; i <= word.size(); ++i)
	{
		temp2 = temp;
		temp2.insert(i, " ");
		if (wordExists(temp2) && (std::find(result.begin(), result.end(), temp2) == result.end()))
			result.push_back(temp2);

	}

    return result;
}

