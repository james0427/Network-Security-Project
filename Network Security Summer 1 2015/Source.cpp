#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void main()
{
	char cipher[6][6];
	string alphanumericbet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	string key, keyc, plaintext, ciphertext, go;
	int ind = 0, a = 0;
	char first, second;
	int f1, f2, s1, s2, len;
	
		//get the key
		cout << "Please enter the key: ";
		getline(cin, key);
		cout << endl;
		key.erase(remove_if(key.begin(), key.end(), isspace), key.end());

		int i = 0;
		while (key[i])
		{
			key[i] = toupper(key[i]);
			i++;
		}
		keyc = key;

		//get the plaintext
		cout << "Please enter the plaintext: ";
		getline(cin, plaintext);
		cout << endl;

		i = 0;
		while (plaintext[i])
		{
			plaintext[i] = toupper(plaintext[i]);
			i++;
		}

		plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), isspace), plaintext.end());

		//look at the content of the plaintext and then decide if X's need to be inserted.
		for (i = 0; i < plaintext.length(); i += 2)
		{
			if (plaintext[i] == plaintext[i + 1])
			{
				plaintext.insert(i + 1, "X");
			}
		}
		
		len = keyc.length();

		for (i = 0; i < len; i++)
		{
			size_t f = alphanumericbet.find(keyc[i-a], 0);

			if (f != std::string::npos)
			{
				alphanumericbet.erase(remove(alphanumericbet.begin(), alphanumericbet.end(), keyc[i-a]), alphanumericbet.end());

			}

			else if (f == std::string::npos)
			{
				keyc.erase(i-a, 1);
				a++;
			}
		}

		//reset the alphanumericbet
		alphanumericbet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

		//look at the end and see if and x needs to be appended
		if (plaintext.length() % 2 == 1)
		{
			plaintext.append("X");
		}

		//fill the cipher array
		//loop through the plaintext and create the cipher array
		for (i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{

				if (keyc != "")
				{
					size_t found = alphanumericbet.find(keyc[0], 0);
					if (found != std::string::npos)
					{
						cipher[i][j] = keyc[0];
						alphanumericbet.erase(remove(alphanumericbet.begin(), alphanumericbet.end(), keyc[0]), alphanumericbet.end());
						keyc.erase(remove(keyc.begin(), keyc.end(), keyc[0]), keyc.end());
					}
				}

				else
				{
					cipher[i][j] = alphanumericbet[0];
					alphanumericbet.erase(0, 1);
				}

				ind++;
			}
		}

		//encrypt the plaintext
		for (i = 0; i < plaintext.length(); i += 2)
		{
			first = plaintext[i];
			second = plaintext[i + 1];

			//find the indecies of the two letters
			for (int k = 0; k < 6; k++)
			{
				for (int l = 0; l < 6; l++)
				{
					if (cipher[k][l] == first)
					{
						f1 = k;
						f2 = l;
					}

					else if (cipher[k][l] == second)
					{
						s1 = k;
						s2 = l;
					}
				}
			}

			//if are in the same row, then replace with letter to the right
			if (f1 == s1)
			{
				if (f2 != 5){
					ciphertext.append(1, cipher[f1][f2 + 1]);
				}
				if (f2 == 5){
					ciphertext.append(1, cipher[f1][0]);
				}
				if (s2 != 5){
					ciphertext.append(1, cipher[s1][s2 + 1]);
				}
				if (s2 == 5){
					ciphertext.append(1, cipher[s1][0]);
				}

			}

			//if are in the same col, then replace with letter below
			else if (f2 == s2){
				if (f1 != 5){
					ciphertext.append(1, cipher[f1 + 1][f2]);
				}
				if (f1 == 5){
					ciphertext.append(1, cipher[0][f2]);
				}
				if (s1 != 5){
					ciphertext.append(1, cipher[s1 + 1][s2]);
				}
				if (s1 == 5){
					ciphertext.append(1, cipher[0][s2]);
				}
			}

			//not same row or same col, then replace with  letter in same row and in the column of
			//the other letter of the pair
			else
			{
				ciphertext.append(1, cipher[f1][s2]);
				ciphertext.append(1, cipher[s1][f2]);
			}
		}

		//display the encrypted message
		cout << ciphertext << endl << endl;
		cout << endl;

	system("pause");
}