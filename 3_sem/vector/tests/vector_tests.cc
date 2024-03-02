#include <vector/vector.h>
#include <gtest/gtest.h>
#include <iostream>
#include <complex>
//1
TEST(vector_tests,constructor_params) {
	int* i_coords = new int[2];
	float* f_coords = new float[2];
	double* d_coords = new double[2];
	std::complex<float>* cf_coords = new std::complex<float>[2];
	std::complex<double>* cd_coords = new std::complex<double>[2];
	i_coords[1] = 20;
	i_coords[0] = 0;
	f_coords[1] = 20.23f;
	f_coords[0] = 0.03f;
	d_coords[1] = 20.2343;
	d_coords[0] = 0.2223;
	cf_coords[0] = { 2.23, 4.45 };
	cf_coords[1] = { 2.509, 9.451 };
	cd_coords[0] = { 6.0092, 499.45757 };
	cd_coords[1] = { 2.504939, 7548.451 };
	auto i_vect = vector<int>(2,i_coords);
	auto f_vect = vector<float>(2, f_coords);
	auto d_vect = vector<double>(2, d_coords);
	auto cf_vect = vector<std::complex<float>>(2, cf_coords);
	auto cd_vect = vector<std::complex<double>>(2, cd_coords);
	ASSERT_EQ(i_vect.get_coord(1), 20);
	ASSERT_NEAR(f_vect.get_coord(0), 0.03,0.000000001);
	ASSERT_NEAR(d_vect.get_coord(1), 20.2343, 0.000000001);
	ASSERT_NEAR(cf_vect.get_coord(1).real(), 2.509, 0.001);
	ASSERT_NEAR(cd_vect.get_coord(0).imag(), 499.45757, 0.001);
	delete[] i_coords;
	delete[] f_coords;
	delete[] d_coords;
	delete[] cf_coords;
	delete[] cd_coords;
}
//2
TEST(vector_tests, constructor_random_params) {
	auto i_vect = vector<int>(3, 4,8);
	auto f_vect = vector<float>(2, 8.99,100.32453);
	auto d_vect = vector<double>(2,5.77,473.45678);
	auto cf_vect = vector<std::complex<float>>(2, 1,3);
	auto cd_vect = vector<std::complex<double>>(2, 5,9);
	ASSERT_EQ(i_vect.get_coord(1), 7);
	ASSERT_NEAR(f_vect.get_coord(0),21.3637, 0.001);
	ASSERT_NEAR(d_vect.get_coord(1), 396.292, 0.001);
	ASSERT_NEAR(cf_vect.get_coord(1).real(),1.44207, 0.001);
	ASSERT_NEAR(cd_vect.get_coord(0).imag(), 5.54191, 0.001);
}
//3
TEST(vector_tests, overloading_brackets) {
	int* i_coords = new int[2];
	float* f_coords = new float[2];
	double* d_coords = new double[2];
	std::complex<float>* cf_coords = new std::complex<float>[2];
	std::complex<double>* cd_coords = new std::complex<double>[2];
	i_coords[1] = 20;
	i_coords[0] = 0;
	f_coords[1] = (float)20.23;
	f_coords[0] = (float)0.03;
	d_coords[1] = 20.2343;
	d_coords[0] = 0.2223;
	cf_coords[0] = { 2.23, 4.45 };
	cf_coords[1] = { 2.509, 9.451 };
	cd_coords[0] = { 6.0092, 499.45757 };
	cd_coords[1] = { 2.504939, 7548.451 };
	auto i_vect = vector<int>(2, i_coords);
	auto f_vect = vector<float>(2, f_coords);
	auto d_vect = vector<double>(2, d_coords);
	auto cf_vect = vector<std::complex<float>>(2, cf_coords);
	auto cd_vect = vector<std::complex<double>>(2, cd_coords);
	i_vect[0] = 33;
	ASSERT_EQ(i_vect[0], 33);
	ASSERT_NEAR(f_vect[0], 0.03, 0.000000001);
	ASSERT_NEAR(d_vect[1], 20.2343, 0.000000001);
	ASSERT_NEAR(cf_vect[1].real(), 2.509, 0.001);
	ASSERT_NEAR(cd_vect[0].imag(), 499.45757, 0.001);
	delete[] i_coords;
	delete[] f_coords;
	delete[] d_coords;
	delete[] cf_coords;
	delete[] cd_coords;
}

//4
TEST(vector_tests, get_length) {
	int* coords1 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	auto vect1 = vector<int>(2, coords1);
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	ASSERT_NEAR(vect1.get_length(), 19.235, 0.001);
	ASSERT_NEAR(cf_vect1.get_length().real(), 1.55, 0.01);
	delete[] coords1;
	delete[] cf_coords1;
}

//5
TEST(vector_tests, operator_dif_eq) {
	int* coords1 = new int[2];
	int* coords2 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	std::complex<float>* cf_coords2 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	coords2[0] = 1;
	coords2[1] = 1;
	auto vect1 = vector<int>(2, coords1);
	auto vect2 = vector<int>(2, coords2);
	vect1 -= vect2;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	cf_coords2[0] = { 1,2.1 };
	cf_coords2[1] = { 1.1,0.1 };
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto cf_vect2 = vector<std::complex<float>>(2, cf_coords2);
	cf_vect1 -= cf_vect2;
	ASSERT_NEAR(cf_vect1[1].imag(), 2.1, 0.01);
	ASSERT_EQ(vect1[1], 16);
    delete[] coords1;
	delete[] coords2;
	delete[] cf_coords1;
	delete[] cf_coords2;
}
//6
TEST(vector_tests, operator_sum_eq) {
	int* coords1 = new int[2];
	int* coords2 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	std::complex<float>* cf_coords2 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	coords2[0] = 1;
	coords2[1] = 1;
	auto vect1 = vector<int>(2, coords1);
	auto vect2 = vector<int>(2, coords2);
	vect1 += vect2;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	cf_coords2[0] = { 1,2.1 };
	cf_coords2[1] = { 1.1,0.1 };
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto cf_vect2 = vector<std::complex<float>>(2, cf_coords2);
	cf_vect1 += cf_vect2;
	ASSERT_NEAR(cf_vect1[1].imag(), 2.3, 0.01);
	ASSERT_EQ(vect1[1], 18);
	delete[] coords1;
	delete[] coords2;
	delete[] cf_coords1;
	delete[] cf_coords2;
}
//7
TEST(vector_tests, copy_constructor) {
	int* coords1 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	auto vect1 = vector<int>(2, coords1);
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto copy_vect(vect1);
	auto copy_cf_vect(cf_vect1);
	ASSERT_NEAR(copy_cf_vect[1].imag(), 2.2, 0.01);
	ASSERT_EQ(copy_vect[1], 17);
	delete[] coords1;
	delete[] cf_coords1;
}
//8
TEST(vector_tests, operator_sum) {
	int* coords1 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	auto vect1 = vector<int>(2, coords1);
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto copy_vect(vect1);
	auto copy_cf_vect(cf_vect1);
	auto sum_vect = copy_vect + vect1+copy_vect;
	auto sum_c_vect = cf_vect1 + cf_vect1 + copy_cf_vect;
	ASSERT_NEAR(sum_c_vect[1].imag(), 6.6, 0.01);
	ASSERT_EQ(sum_vect[1], 51);
	delete[] coords1;
	delete[] cf_coords1;
}

//9
TEST(vector_tests, operator_dif) {
	int* coords1 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	auto vect1 = vector<int>(2, coords1);
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto copy_vect(vect1);
	auto copy_cf_vect(cf_vect1);
	auto sum_vect = copy_vect - vect1 - copy_vect;
	auto sum_c_vect = cf_vect1 - cf_vect1 - copy_cf_vect;
	ASSERT_NEAR(sum_c_vect[1].imag(), -2.2, 0.01);
	ASSERT_EQ(sum_vect[1], -17);
	delete[] coords1;
	delete[] cf_coords1;
}

//10
TEST(vector_tests, operator_mult) {
	int* coords1 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	auto vect1 = vector<int>(2, coords1);
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto copy_vect(vect1);
	auto copy_cf_vect(cf_vect1);
	double mult_vect = vect1 * copy_vect;
	auto c_mult_vect = copy_cf_vect * cf_vect1;
	auto mult = vect1 * 3;
	auto mult1 = 3 * vect1;
	auto c_mult = cf_vect1 * 3;
	auto c_mult1 = 3* cf_vect1;
	ASSERT_EQ(mult_vect,81+289);
	ASSERT_EQ(mult[1], 17*3);
	ASSERT_EQ(mult1[1], 17 * 3);
	ASSERT_NEAR(c_mult_vect.imag(), 0, 0.01);
	ASSERT_NEAR(c_mult[1].imag(), 6.6, 0.01);
	ASSERT_NEAR(c_mult1[1].imag(), 6.6, 0.01);
	delete[] coords1;
	delete[] cf_coords1;
}

//11
TEST(vector_tests, operator_div) {
	int* coords1 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	auto vect1 = vector<int>(2, coords1);
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto div_vec = vect1/3;
	auto c_div_vec= cf_vect1/3;
	ASSERT_EQ(div_vec[0], 3);
	ASSERT_NEAR(c_div_vec[1].real(), 0.366, 0.01);
	delete[] coords1;
	delete[] cf_coords1;
}
//12
TEST(vector_tests, operator_comp_eq) {
	int* coords1 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	auto vect1 = vector<int>(2, coords1);
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto copy(vect1);
	auto copy_cf(cf_vect1);
	ASSERT_TRUE(copy == vect1);
	ASSERT_TRUE(copy_cf == cf_vect1);
	delete[] coords1;
	delete[] cf_coords1;
}
//13
TEST(vector_tests, operator_comp_uneq) {
	int* coords1 = new int[2];
	std::complex<float>* cf_coords1 = new std::complex<float>[2];
	coords1[0] = 9;
	coords1[1] = 17;
	cf_coords1[0] = { 1.1,2.2 };
	cf_coords1[1] = { 1.1,2.2 };
	auto vect1 = vector<int>(2, coords1);
	auto cf_vect1 = vector<std::complex<float>>(2, cf_coords1);
	auto copy(vect1);
	auto copy_cf(cf_vect1);
	copy *= 2;
	copy_cf *= 5;
	ASSERT_TRUE(copy != vect1);
	ASSERT_TRUE(copy_cf != cf_vect1);
	delete[] coords1;
	delete[] cf_coords1;
}

//13
TEST(vector_tests, calculate_parallelogram_angles) {
	int* coords1 = new int[3];
	int* coords2 = new int[3];
	std::complex<float>* cf_coords1 = new std::complex<float>[3];
	std::complex<float>* cf_coords2 = new std::complex<float>[3];
	coords1[0] = 4;
	coords1[1] = 3;
	coords1[2] = 0;
	coords2[0] = 0;
	coords2[1] = 12;
	coords2[2] = 5;
	cf_coords1[0] = { 4, 0};
	cf_coords1[1] = { 3,0};
	cf_coords1[2] = { 0,0 };
	cf_coords2[0] = { 0, 0 };
	cf_coords2[1] = { 12,0 };
	cf_coords2[2] = { 5,0 };
	auto vect1 = vector<int>(3, coords1);
	auto vect2 = vector<int>(3, coords2);
	auto cf_vect1 = vector<std::complex<float>>(3, cf_coords1);
	auto cf_vect2 = vector<std::complex<float>>(3, cf_coords2);
	double* angl = new double[2];
	std::complex<float>* angl_c = new std::complex<float>[2];
	angl = calculate_parallelogram_angles(vect1, vect2);
	angl_c = calculate_parallelogram_angles(cf_vect1,cf_vect2);
	ASSERT_NEAR(angl[1] + angl[0], 180,0.001);
	ASSERT_NEAR(angl[0], 56.36, 0.01);
	ASSERT_NEAR(angl[1], 123.63, 0.01);
	ASSERT_NEAR(angl_c[0].real(), 0.553, 0.01);
	ASSERT_NEAR(angl_c[0].imag(), 0, 0.01);
	ASSERT_NEAR(angl_c[1].real(), -0.553, 0.01);
	ASSERT_NEAR(angl_c[1].imag(), 0, 0.01);
	delete[] coords1;
	delete[] coords2;
	delete[] angl;
	delete[] angl_c;
	delete[] cf_coords1;
	delete[] cf_coords2;
}