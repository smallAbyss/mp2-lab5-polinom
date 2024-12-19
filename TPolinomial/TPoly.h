#pragma once
#include <string>
#include <iostream>
#include <map>
#include <sstream>

using ui = unsigned;

struct Node {
	int c;
	ui grades;
	Node* pNext;
};

class TList {
	friend class TPolinomial;
	Node* pFirst;
	Node* pLast;

public:
	TList(Node* &fst) {
		pLast = pFirst = fst;
		pFirst->pNext = nullptr;
	}

	TList() : pFirst(nullptr) {}

	TList(const TList& lis) {
		Node* pnew = new Node{ lis.pFirst->c, lis.pFirst->grades };
		pFirst = pnew;
		Node* pc = pnew;
		Node* pcl = lis.pFirst->pNext;
		while (pcl != nullptr) {
			pnew = new Node{ pcl->c, pcl->grades };
			pc->pNext = pnew;
			pc = pnew;
			pcl = pcl->pNext;
		}
		
	}

	TList& operator=(const TList& lis) {
		Node* pnew = new Node{ lis.pFirst->c, lis.pFirst->grades };
		pFirst = pnew;
		Node* pc = pnew;
		Node* pcl = lis.pFirst->pNext;
		while (pcl != nullptr) {
			pnew = new Node{ pcl->c, pcl->grades };
			pc->pNext = pnew;
			pc = pnew;
			pcl = pcl->pNext;
		}
		return *this;
	}

	~TList() {
		Node* p;
		while (pFirst != nullptr) {
			p = pFirst;
			pFirst = p->pNext;
			delete p;
		}
	}

	void InsertFirst(Node*& n) {
		Node* p = pFirst;
		pFirst = n;
		pFirst->pNext = p;
	}

	void InsertLast(Node*& n) {
		Node* p = pFirst;
		if (!p) {
			InsertFirst(n);
			return;
		}
		for (; p->pNext; p = p->pNext) {}
		p->pNext = n;
		n->pNext = nullptr;
	}

	/*
	void Insert(Node*& el) {
		Node* p = pFirst;
		InsertFirst(el);
		if (p && (el->grades < p->grades)) {
			el->pNext = p->pNext;
			p->pNext = el;
			pFirst = p;
			p = el->pNext;
		}
		Node* pr = pFirst;
		while (p && (el->grades < p->grades)) {
			pr->pNext = p;
			el->pNext = p->pNext;
			p->pNext = el;

			pr = p;
			p = el->pNext;
		}

	}
	*/
	
	void pr() {
		Node* p = pFirst;
		while (p->pNext) {
			std::cout << p->grades << std::endl;
			p = p->pNext;
		}
		std::cout << p->grades << std::endl;
	}

};

class TPolinomial {
	TList monoms;

	void Insert(Node*& el) {
		Node* p = monoms.pFirst;
		monoms.InsertFirst(el);
		if (p && (el->grades < p->grades)) {
			el->pNext = p->pNext;
			p->pNext = el;
			monoms.pFirst = p;
			p = el->pNext;
		}
		Node* pr = monoms.pFirst;
		while (p && (el->grades < p->grades)) {
			pr->pNext = p;
			el->pNext = p->pNext;
			p->pNext = el;

			pr = p;
			p = el->pNext;
		}

	}

	void Unite() {
		Node* p = monoms.pFirst;
		Node* next = 0;
		while (p->pNext) {
			next = p->pNext;
			if (p->grades == next->grades) {
				p->c += next->c;
				p->pNext = next->pNext;
				delete next;
			}
			else
				p = p->pNext;
		}

	}
	
	bool check(const std::string &s) {
		std::string syms = "1234567890+-xyz";
		std::string pm = "++_+-_-+_--";

		if (syms.find(s[0]) == -1) return false;
		if ((s.size() > 1) && (pm.find(s[0] + s[1]) != -1)) return false;
		for (size_t i = 1; i < s.size(); i++) {
			if (syms.find(s[i]) < 0) return false;
			if (pm.find(s[i-1] + s[i]) != -1) return false;
			return true; 
		}
	}

	std::string despace(const std::string& str) {
		std::string s = "";
		for (size_t i = 0; i < str.size(); i++)
			if (str[i] != ' ')
				s += str[i] ;
		return s;
	}
public: 
	// string last sym is \n
	TPolinomial(const std::string &poly) {
		std::string polynomial = despace(poly);
		if (!check(poly)) 
			throw std::string("Unacceptable symbols in polynomial string");
		
		if (polynomial[0] != '-') polynomial = '+' + polynomial;
		int c = 0;
		int sign = 1;
		ui grade = 0;
		for (size_t i = 0; i < polynomial.size(); i++) {
			if (polynomial[i] == ' ') continue;
			if (polynomial[i] == '+' or polynomial[i] == '-') {
				Node* el = new Node{ sign * c, grade, nullptr }; //  empty monomon the fisrt iteration
				if (el->c !=0) 
					Insert(el);

				c = 0; grade = 0;
				sign = (polynomial[i] == '-' ? -1 : 1);
				continue;
			}

			//get coef
			
			for (; '0' <= polynomial[i] && polynomial[i] <= '9'; i++) {
				c *= 10;
				c += (polynomial[i] - int('0'));
  			}
			if ((polynomial[i - 1] == '+') or (polynomial[i - 1] == '-')) // if there is no num. eg: x2z2
				c = 1;

			//get grades
			if (polynomial[i] == 'x') {
				if ((polynomial[i + 1] > '9') or (polynomial[i + 1] < '0'))
					grade += 100;
				else 
					grade += (polynomial[++i] - int('0')) * 100;
				continue; //i++
			}
			if (polynomial[i] == 'y') {
				if ((polynomial[i + 1] > '9') or (polynomial[i + 1] < '0'))
					grade += 10;
				else
					grade += (polynomial[++i] - int('0')) * 10;
				continue; //i++
			}
			if (polynomial[i] == 'z') {
				if ((polynomial[i + 1] > '9') or (polynomial[i + 1] < '0'))
					grade += 1;
				else
					grade += (polynomial[++i] - int('0')) * 1;
				continue; //i++
			}
			i--; // grade == 0 -> it was a const -> the curent sym is sign for the next -> get back
		}
		Node* el = new Node{ sign * c, grade, nullptr };
		if (el->c != 0) 
			Insert(el);
		Unite();
	}

	TPolinomial() {	}

	~TPolinomial() = default;

	TPolinomial(const TPolinomial& pl) {
		/*Node* tmp = nullptr;
		Node* p = pl.monoms.pFirst;
		for (; p; p = tmp) {
			tmp = p->pNext;
			monoms.InsertLast(p);
		}
		*/
		monoms = pl.monoms;
		
	}

	std::string getStringVers() const  {
		std::string poly_str = "";
		Node* p = monoms.pFirst;
		std::string vars = "xyz";
		ui grade[] = { (p->grades / 100), ((p->grades) / 10 - (p->grades / 100 * 10)), (p->grades - p->grades / 10 * 10)};
		
		if (p->c == -1 or p->c < 0)
			poly_str += '-';
		if (p->grades == 0)
			poly_str += (p->c > 0 ? p->c : -1 * p->c);
		if ((p->c != 1) && (p->c != -1) && (p->grades != 0))
			poly_str += (p->c > 0 ? p->c : -1 * p->c);
		for (ui i = 0; i < vars.size(); i++) {
			if (grade[i] > 0)
				poly_str += vars[i];
			if (grade[i] > 1)
				poly_str += grade[i];
		}
		p = p->pNext;

		while (p) {
			grade[0] = (p->grades / 100);
			grade[1] = ((p->grades) / 10 - (p->grades / 100 * 10));
			grade[2] = (p->grades - p->grades / 10 * 10);

			if (p->c < 0)
				poly_str += '-';
			if (p->c > 0)
				poly_str += '+';

			if (p->grades == 0)
				poly_str += (p->c > 0 ? p->c : -1 * p->c);
			if ((p->c != 1) && (p->c != -1) && (p->grades != 0))
				poly_str += (p->c > 0 ? p->c : -1 * p->c);
			for (ui i = 0; i < vars.size(); i++) {
				if (grade[i] > 0)
					poly_str += vars[i];
				if (grade[i] > 1)
					poly_str += grade[i];
			}
			p = p->pNext;
		}
		return poly_str;
	}

	void print() {
		std::string poly_str = "";
		Node* p = monoms.pFirst;
		std::string vars = "xyz";
		ui grade[] = { (p->grades / 100), ((p->grades) / 10 - (p->grades / 100 * 10)), (p->grades - p->grades / 10 * 10) };

		if (p->c == -1 or p->c < 0)
			std::cout << '-';
		if (p->grades == 0)
			std::cout << (p->c > 0 ? p->c : -1 * p->c);
		if ((p->c != 1) && (p->c != -1) && (p->grades != 0))
			std::cout << (p->c > 0 ? p->c : -1 * p->c);
		for (ui i = 0; i < vars.size(); i++) {
			if (grade[i] > 0)
				std::cout << vars[i];
			if (grade[i] > 1)
				std::cout << grade[i];
		}
		p = p->pNext;

		while (p) {
			grade[0] = (p->grades / 100);
			grade[1] = ((p->grades) / 10 - (p->grades / 100 * 10));
			grade[2] = (p->grades - p->grades / 10 * 10);

			if (p->c < 0)
				std::cout << '-';
			if (p->c > 0)
				std::cout << '+';

			if (p->grades == 0)
				std::cout << (p->c > 0 ? p->c : -1 * p->c);
			if ((p->c != 1) && (p->c != -1) && (p->grades != 0))
				std::cout << (p->c > 0 ? p->c : -1 * p->c);
			for (ui i = 0; i < vars.size(); i++) {
				if (grade[i] > 0)
					std::cout << vars[i];
				if (grade[i] > 1)
					std::cout << grade[i];
			}
			p = p->pNext;
		}
	}
	

	long calculate(const int px, const int py, const int pz) {
		Node* p = monoms.pFirst;
		long sum = 0;
		while (p) {
			ui grade[] = { (p->grades / 100), ((p->grades) / 10 - (p->grades / 100 * 10)), (p->grades - p->grades / 10 * 10) };
			sum += p->c * pow(px, grade[0]) * pow(py, grade[1]) * pow(pz, grade[2]);
			p = p->pNext;
		}
		return sum;
	}

	TPolinomial operator+(const TPolinomial& pl) const {
		TPolinomial sum;
		Node* p1 = monoms.pFirst;
		Node *p2 = pl.monoms.pFirst;

		ui grade1 = 0, grade2 = 0;
		int c1 = 0, c2 = 0;
		while (p1 or p2) {
			if (p1) {
				grade1 = p1->grades;
				c1 = p1->c;
			}
			if (p2) {
				grade2 = p2->grades;
				c2 = p2->c;
			}

			ui s_grade;
			int s_c;
			if (grade1 == grade2) { 
				s_grade = grade1;
				s_c = c1 + c2;

				if (p1)
					p1 = p1->pNext;
				if (p2)
					p2 = p2->pNext;
			}
			if (grade1 > grade2) {
				s_grade = grade1;
				s_c = c1;
				if (p1)
					p1 = p1->pNext;
			}
			if (grade1 < grade2) {
				s_grade = grade2;
				s_c = c2;
				if (p2)
					p2 = p2->pNext;
			}
			if (s_c == 0) continue;
			Node* el = new Node{ s_c, s_grade, nullptr };
			sum.Insert(el);

			grade1 = 0; grade2 = 0;
			c1 = 0; c2 = 0;
		}

		if (!sum.monoms.pFirst) {
			Node* el = new Node{ 0, 0, nullptr };
			sum.Insert(el);
		}
		return sum;
	}

	TPolinomial operator*(int& ct) const {
		TPolinomial prod;
		Node* p = monoms.pFirst;
		Node* el = nullptr;
		ui grade = 0;
		int c = 0;
		while (p) {
			grade = p->grades;
			c = ct * p->c;
			el = new Node{ c, grade, nullptr };
			prod.Insert(el);
			p = p->pNext;
		}
		return prod;
	}

	TPolinomial operator-(const TPolinomial& pl) const {
		int h = -1;
		TPolinomial sum = (*this) + pl.operator*(h);
		return sum;
	}
	
	TPolinomial& operator=(const TPolinomial& pl) {
		/* Node* p = monoms.pFirst;
		Node* tmp = nullptr;
		while (monoms.pFirst != nullptr) {
			p = monoms.pFirst;
			monoms.pFirst = p->pNext;
			delete p;
		}
		monoms.pFirst = 0;

		p = pl.monoms.pFirst;
		for (; p; p = tmp) {
			tmp = p->pNext;
			monoms.InsertLast(p);
		}*/
		monoms = pl.monoms;
 		return *this;
	};

	friend std::ostream &operator<<(std::ostream& os, const TPolinomial& pl);
};





std::ostream& operator<<(std::ostream& os,  TPolinomial& pol) {
	pol.print();
	return os;
}