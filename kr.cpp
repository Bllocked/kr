#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int HashKey(string klucz,int lp,int pod)
{
	int suma = 0;
	int x;
	for (size_t i = 0; i < klucz.size(); i++)
	{
		/*if (int(klucz[i]) < 0)
			x = int(klucz[i]) + 256;
		else*/
			x = int(klucz[i]);
		suma += x%lp;
		if (i < klucz.size() - 1)
		{
			suma *= pod;
		}
		suma = suma % lp;
	}
	return suma;
}

int HashValue(int h0, int licz_pop, int licz_nast,int lp,int pod,int n)
{
	/*if (licz_pop < 0)
		licz_pop += 256;
	if (licz_nast < 0)
		licz_nast += 256;*/
	for (int i = 0; i < n - 1; i++)
	{
		licz_pop = licz_pop % lp;
		licz_pop *= pod;
	}
	licz_pop = licz_pop % lp;
	h0=h0-licz_pop;
	if (h0 < 0)
		h0 += lp;
	h0 *= pod;
	h0 = h0 % lp;
	h0 = h0 + licz_nast;
	h0 = h0 % lp;
	return h0;

}
string czytplik(const string& path)
{
	auto ss = ostringstream{};
	ifstream input_file(path);
	if (!input_file.is_open()) {
		/*cerr << "Could not open the file - '"
			<< path << "'" << endl;*/
		exit(EXIT_FAILURE);
	}
	ss << input_file.rdbuf();
	return ss.str();
}
int main()
{
	int liczba_pierwsza = 151;
	int podstawa = 256;
	podstawa = podstawa % liczba_pierwsza;
	int hashkey;
	int hash;
	int ilosc;
	cin >> ilosc;
	while (ilosc > 0)
	{
		bool check = false;
		string plik;
		cin >> plik;
		string klucz;
		cin.ignore();
		getline(cin, klucz);
		int n = klucz.size();
		string tekst;
		tekst = czytplik(plik);
		string t;
		t.resize(klucz.size());
		for (size_t i = 0; i < klucz.size(); i++)
		{
			t[i] = tekst[i];
		}
		hashkey = HashKey(klucz, liczba_pierwsza, podstawa);
		hash = HashKey(t, liczba_pierwsza, podstawa);
		//cout << "\nHashKey: " << hashkey;
		for (size_t i = 0; i <= tekst.size() - n; i++)
		{
			//cout << "\nHash: " << hash;
			if (hashkey == hash)
			{
				for (size_t j = 0; j < klucz.size(); j++)
				{
					if (klucz[j] != tekst[j + i])
						break;
					if (j == klucz.size() - 1)
						check = true;
				}
				if (check == true)
				{
						cout << i << " ";
				}
			}
			check = false;
			hash=HashValue(hash, tekst[i], tekst[i + n], liczba_pierwsza, podstawa, n);
		}
		cout << endl;
		ilosc--;
	}
}