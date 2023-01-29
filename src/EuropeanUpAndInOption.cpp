#include<cmath>
#include<iostream>
#include<algorithm>

#include"getOneGaussianByBoxMueller.h"
#include"EuropeanUpAndInOption.h"


//definition of constructor
EuropeanUpAndInOption::EuropeanUpAndInOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_,
    double barrier_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
        barrier = barrier_;
		generatePath();
}

//method definition
void EuropeanUpAndInOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();

	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}

//method definition
void EuropeanUpAndInOption::printPath(){

	for(int i = 0;  i < nInt; i++){

		std::cout << thisPath[i] << "\n";

	}

}

//method definition
double EuropeanUpAndInOption::getEuropeanUpAndInOptionCallPrice(int nReps){

	double rollingSum = 0.0;

	for(int i = 0; i < nReps; i++){
		generatePath();

        double maxPrice = *std::max_element(thisPath.begin(), thisPath.end());

        if ((maxPrice >= barrier) & (thisPath.back() > strike)) {
            rollingSum += thisPath.back() - strike;
        }
	}

	return exp(-r*expiry)*rollingSum/double(nReps);

}

//method definition
double EuropeanUpAndInOption::getEuropeanUpAndInOptionPutPrice(int nReps){

	double rollingSum = 0.0;

	for(int i = 0; i < nReps; i++){
		generatePath();

        double maxPrice = *std::max_element(thisPath.begin(), thisPath.end());

        if ((maxPrice >= barrier) & (thisPath.back() < strike)) {
            rollingSum += strike - thisPath.back();
        }
	}

	return exp(-r*expiry)*rollingSum/double(nReps);

}

//overloaded operator ();
double EuropeanUpAndInOption::operator()(char type, int nReps){
    if (type == 'C') return getEuropeanUpAndInOptionCallPrice(nReps);
    else if (type == 'P') return getEuropeanUpAndInOptionPutPrice(nReps);
    else return -99;
}
