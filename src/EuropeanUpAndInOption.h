#include<vector>

class EuropeanUpAndInOption{
public:

	//constructor
	EuropeanUpAndInOption(
		int nInt_,
		double strike_,
		double spot_,
		double vol_,
		double r_,
		double expiry_,
		double barrier_
		);

	//destructor
	~EuropeanUpAndInOption(){};

	//methods
	void generatePath();
	void printPath();
    double getEuropeanUpAndInOptionCallPrice(int nReps);
    double getEuropeanUpAndInOptionPutPrice(int nReps);
	double operator()(char type, int nReps);
	
	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;
	double barrier;

};
