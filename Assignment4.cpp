/*******************************************************************
Name: Assignment 4.cpp 
Description: Palindrome detector, frequency of words, 
and frequency of all words
Pre-Conditions: User inputs a sentence or pargraph, and an 
integer for which choice they want
Post-Conditions: Outputs true or false for palindrome, outputs the 
frequency of words for other two
*********************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

//get int for user choice
int get_int(string prompt) {
	int final = 0;
	for (int i = 0; i < prompt.size(); i++) {
		if ((prompt[i] > 57 || prompt[i] < 48)) { //numbers
			return -1;
		}
		final += int(prompt[i] - 48) * pow(10, (prompt.size() - 1 - i));
	}
	return final;
}

//Ask user for string input
void get_sentence(char*s) {
	cout << "Please enter a sentence or paragraph: ";
	cin.getline(s, 1024);
}

	//1 - PALINDROME DETECTOR

bool is_palindrome(char *palindrome) {   
	int l=0, p = strlen(palindrome)-1;
	//lowercase string
	for (int m = 0; m < p; m++)
		palindrome[m] = tolower(palindrome[m]);

	//compares character until they are equal
	while(l <= p) {

		//if there is another symbol in left of sentence
		if (!(palindrome[l] >= 'a' && palindrome[l] <= 'z')&& 
			!(palindrome[l] >= '1' && palindrome[l] <= '9'))
			l++;

		//if there is another symbol in right of sentence
		else if (!(palindrome[p] >= 'a' && palindrome[p] <= 'z')&&
			!(palindrome[p] >= '1' && palindrome[p] <= '9'))
			p--;

		//if chracters are equal
		else if (palindrome[l] == palindrome[p])
			l++, p--;

		else
			return false; //if characters are not equal (not palindrome)		
	}
	return true; //if sentence is palindrome
}

	//2 - OUTPUT FREQUENCY OF ALL WORDS (static array)

string to_lower(string sentence) {
	for (int i = 0; i < sentence.size(); i++) {
		if (sentence[i] < 91 & sentence[i] > 64) { //uppercase
			sentence[i] += 32;
		}
	}
	return sentence;
}

string to_proper(string word) {
	string proper_word = "";
	for (int i = 0; i < word.length(); i++) {
		if (word[i] >= 65 && word[i] <= 90) {
			proper_word+=(word[i]);
		}
		if (word[i] >= 97 && word[i] <= 122) {
			proper_word += (word[i]);
		}
	}
	return to_lower(proper_word);
}

void all_frequency(char *sent) {
	string words[256] = {}; string temp = ""; int word_index = 0; int counter = 1; int print_index = 0;
	for (int i = 0; i < strlen(sent); i++) {
		if (sent[i] != 32)
			temp += sent[i];
		else {
			words[word_index] = to_proper(temp);
			temp = "";
			word_index++;
		}
	}
	words[word_index] = to_proper(temp);
	bool has_been_printed = false; string chosen_word = ""; string printed[256] = {};
	for(int i=0;i<256;i++){
		chosen_word = words[i];
		for (int j = 0; j < 256; j++) {
			if (chosen_word == printed[j])
				has_been_printed = true;
		}
		if (!has_been_printed) {
			for (int j = i + 1; j < 256; j++) {
				if (chosen_word == words[j])
					counter++;
			}
			has_been_printed = true;
			cout << chosen_word << ": " << counter << endl;
			printed[print_index] = chosen_word;
			print_index++;
			counter = 1;
		}
		has_been_printed = false;
	}
}

	//3 - OUTPUT THE FREQUENCY OF GIVEN WORD (dynamic array)

	//Ask user how many words they want to search for
void get_num_words(int &num) {
	cout << "How many words do you want to search for? ";
	cin >> num;
}

	//Ask user for word(s) they want to search for
void get_words(int &num, string*words) {
	cin.ignore(256, '\n');
	for (int i = 0; i < num; i++) {
		cout << "Please enter a word: ";
		cin >> words[i];
	}
}

	//Output frequency of the word
void frequency(int &num, string*words, char*sentence) {
	for (int i = 0; i < num; i++) {
		int word_frequency = 0;
		for (int j = 0; j < strlen(sentence); j++) {
			if (sentence[j] == words[i][0]) {
				int count = 0;
				for (int k = 0; k < words[i].length(); k++) {
					if (sentence[j + k] == words[i][k]) {
							count++;
					}
				}
				if (count == words[i].length()) {
						word_frequency++;
						count = 0;
			}
			}
		}
		cout << words[i] << ": " << word_frequency << endl;
	}
}

int main()
{
	int again = 1; 
	do {
		int choice = 0; string input; 
		char *sentence = new char[1024];
		get_sentence(sentence);
		do {
			cout << "What do you want to do? (1-Palindrome Detector, 2-Frequency of All Words, 3-Frequency of Given Words) " << endl;
			getline(cin, input);
			choice = get_int(input);
		} while (choice != 1 && choice != 2 && choice != 3);

		//1 - Palindrome Detector
		if (choice == 1) {
			cout << is_palindrome(sentence) << endl;
		}

		//2 - Frequency of All Words
		if (choice == 2) {
			all_frequency(sentence);
		}

		//3 - Frequency of Given Word(s)
		if (choice == 3) {
			int size = strlen(sentence);
			int num, word_frequency = 0;
			get_num_words(num);
			string *words = new string[num];
			char *new_sentence = new char[size];
			for (int i = 0; i < size; i++) {
				new_sentence[i] = tolower(sentence[i]);
			}
			get_words(num, words);
			frequency(num, words, sentence);
			delete[] words;
			delete[] new_sentence;
		}

		do {
			string input_again;
			cin.ignore();
			cout << "Do you want to start again? (0-no, 1-yes) " << endl;			
			getline(cin, input_again);
			again = get_int(input_again);
		} while (again != 1 && again != 0);
		delete[] sentence;
	}while (again == 1);
	return 0;
}

