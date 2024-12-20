#include "TPoly.h"
#include "gtest.h"

TEST(TPolinomial, can_Create_Zero_Polynomial) {
	EXPECT_NO_THROW(TPolinomial p);
}

TEST(TPolinomial, can_Create_Empty_Polynomial_With_Spaces) {
	TPolinomial ps("2x5-y4+42");
	TPolinomial p("2x5+42 - y4");
	EXPECT_NO_THROW(ps.getStrVers() == p.getStrVers());
}

TEST(TPolinomial, different_Order_Doesnt_Matter) {
	TPolinomial p1("24xyz+42x-4242");
	TPolinomial p2("xyz+2+y");

	TPolinomial p3("25xyz+42x+y-4240");

	EXPECT_TRUE(p3 == (p1 + p2));
}

TEST(TPolinomial, cant_Create_Not_A_Polynomial) {
	EXPECT_ANY_THROW(TPolinomial p("xdcfvgbhn"));
}

TEST(TPolinomial, can_Create_Right_Polynomial_With_String) {
	TPolinomial p("24xyz +  42x - 4242");
	EXPECT_NO_THROW(p.getStrVers() == std::string("24xyz +  42x - 4242"));
}

TEST(TPolinomial, can_Create_Polynomial) {
	EXPECT_NO_THROW(TPolinomial p("24xyz +  42x - 4242"));
}

TEST(TPolinomial, add_Works) {
	TPolinomial p1("24xyz+42x-4242");
	TPolinomial p2("xyz+2+y");

	TPolinomial p3("25xyz+42x+y-4240");

	EXPECT_TRUE(p3 == (p1 + p2));
}

TEST(TPolinomial, sub_Works) {
	TPolinomial p1("24xyz+42x-4242");
	TPolinomial p2("xyz+2+y");

	TPolinomial p3("23xyz+42x-y-4244");

	EXPECT_TRUE(p3 == (p1 - p2));
}

TEST(TPolinomial, mult_Works) {
	TPolinomial p1("24xyz+42x-4242");
	TPolinomial p2("48xyz+84x-8484");

	EXPECT_TRUE(p2 == p1*2);
}

TEST(TPolinomial, copied_Polynomial_Have_Another_Memory_assign) {
	TPolinomial p1("42");
	if (true) {
		TPolinomial p2("4242");
		p1 = p2;
	} // p2 deleted;
	EXPECT_EQ(p1.getStrVers(), std::string("4242"));
}

TEST(TPolinomial, copied_Polynomial_Have_Another_Memory_constructor) {
	TPolinomial p1("42");
	TPolinomial p3;
	if (true) {
		TPolinomial p2(p1);
		p3 = p2;
	} // p2 deleted;
	EXPECT_EQ(p3.getStrVers(), std::string("42"));
}

TEST(TPolinomial, calculate_Works) {
	TPolinomial p1("x+2y+3z");

	double res = p1.calculate(1, 2, 3);
	EXPECT_TRUE(res == 14);
}