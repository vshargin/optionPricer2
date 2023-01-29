#include<Rcpp.h>
#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"EuropeanUpAndInOption.h"

using std::vector;
using std::cout;
using std::cin;

// [[Rcpp::export]]
double getEuropeanUpAndInOptionPrice(
	int nInt,
	double strike,
	double spot,
	double vol,
	double r,
	double expiry,
	double barrier,
	int nReps,
	char type
) {
	// set the seed
	srand(time(NULL));

	//create a new instance of class
	EuropeanUpAndInOption myOption(nInt, strike, spot, vol, r, expiry, barrier);

	double price = 0.0;

	if (type == 'C') {
		price = myOption.getEuropeanUpAndInOptionCallPrice(nReps);
	} else if (type == 'P') {
		price = myOption.getEuropeanUpAndInOptionPutPrice(nReps);
	}

	return price;
}
