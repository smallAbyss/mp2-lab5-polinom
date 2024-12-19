#include <iostream>
#include "TPoly.h"

using namespace std;

void main1() {
	TList l;
	Node* n0 = new Node{ 0, 301, 0 };
	Node* n5 = new Node{ 0, 301, 0 };
	Node* n1 = new Node{ 0, 200, 0 };
	Node* n2 = new Node{ 0, 15, 0 };
	Node* n3 = new Node{ 0, 132, 0 };
	l.InsertFirst(n2);
	l.InsertFirst(n3);
	l.InsertFirst(n1);
	l.InsertFirst(n0);
	l.InsertFirst(n5);

	Node* n = new Node{ 0, 139, 0 };
	l.pr();
	cout << endl << endl;
	//l.Insert(n);
	l.pr();


}

void main() {
	cout << "\"add\" - sum of two polinomials\n";
	cout << "\"sub\" - difference of two polinomials\n";
	cout << "\"mult\" - product of polinomial and constant value\n";
	cout << "\n";
	cout << "Enter \"poly\" to add polynomial to memory\n";
	cout << "Enter \"show\" to show polynomials in memory\n";
	cout << "Enter \"calc\" to calculate polynomial value at the point\n";
	cout << "Enter \"exit\" to close the program\n";
	cout << "Memory limit - 998 polinomials\n";
	string inp = "", poly = "";
	//map<unsigned, TPolinomial>
	TPolinomial polynomials[1000];

	size_t i = 0;
	bool fg = false;
	TPolinomial p;


	while (true) {
		
		cout << "Enter command: \n";
		getline(cin, inp);
		if (inp == "poly") {
			try {
				do {
					getline(cin, poly);

					fg = false;
					if (poly == "exit") {
						break;
						fg = true;
					}
					TPolinomial tmp(poly);
					polynomials[i++] = tmp;
					//p = tmp;
				} while (fg);
			} 
			catch (string ex) {
				fg = true;
				cout << ex << "\nPlease, try again\n";
			}
			if (fg) continue;
			//
		}
		if (inp == "show") {
			for (size_t j = 0; j < i; j++) {
				cout << j << ": " << polynomials[j] << endl;
			}
		}
		if (inp == "add") {
			unsigned a, b;
			cout << "Enter numbers of poly";
			cin >> a >> b;
			if (a >= i or b >=i) {
				cout << "Incorrect numbers";
				continue;
			}
			TPolinomial p = polynomials[a] + polynomials[b];
			cout << p;
			cout << endl << "Want to save? [0/1]" << endl;
			int in = 0;
			do {
				cin >> in;
			} while (in != 0 && in != 1);
			if (in == 1)
				polynomials[i++] = p;
			continue;
		}
		if (inp == "sub") {
			unsigned a, b;
			cout << "Enter numbers of poly";
			cin >> a >> b;
			if (a >=i or b >=i) {
				cout << "Incorrect numbers";
				continue;
			}
			TPolinomial p = polynomials[a] - polynomials[b];
			cout << p;
			cout << endl << "Want to save?[yes/no]" << endl;
			do {
				cin >> inp;
			} while (inp != "yes" && inp != "no");
			if (inp == "yes")
				polynomials[i++] = p;
			continue;
		}
		if (inp == "mult") {
			unsigned a;
			int b = 0;
			cout << "Enter number of polynomial: ";
			cin >> a;
			if (a >=i) {
				cout << "Incorrect number";
				continue;
			}
			cout << "Enter multiplyer: ";
			cin >> a;
			
			TPolinomial p = polynomials[a]*b;
			cout << p;
			cout << endl << "Want to save?[yes/no]" << endl;
			do {
				cin >> inp;
			} while (inp != "yes" && inp != "no");
			if (inp == "yes")
				polynomials[i++] = p;
			continue;
		}
		if (inp == "calc") {
			int a, b, c, x;
			cout << "Enter polinomial number: ";
			cin >> x;
			if (x >= i) {
				cout << "Incorrect number";
				continue;
			}
			cout << "Enter variables x, y, z: ";
			cin >> a >> b >> c;
			cout << polynomials[x].calculate(a, b, c) << endl;
			continue;
		}
		if (inp == "exit") break;
		if (i == 999) i = 0;
	}
	
}
