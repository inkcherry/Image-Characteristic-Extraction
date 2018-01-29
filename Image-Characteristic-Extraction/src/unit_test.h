#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <Windows.h>
namespace test {
	double** get_mat();
	void show_mat(double **mat_, const int &width, const int &height);
}

namespace unit {
	void test_init_kernel();
	void test_conv();
}