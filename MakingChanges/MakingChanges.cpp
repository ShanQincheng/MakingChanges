// MakingChanges.cpp : Defines the entry point for the console application.
//

#pragma once

#include "stdafx.h"


int main()
{
	while (true)
	{
		int i = 0; // iterator variable
		string line;
		int counter = 1;
		double* inputArray = (double*)calloc(1, sizeof(double));

		rewind(stdin);
		getline(cin, line);// use getline() read one line input
		istringstream in(line);	// create a istringstream object for this line
		while (in >> inputArray[counter - 1])
		{
			double* reallocPointer;
			counter++;
			reallocPointer = (double*)realloc(inputArray, counter * sizeof(double));
			inputArray = reallocPointer;
		}
		counter--; // remove last '\n'
		if (counter == 2) // if input is "0 0", exit the program
		{
			system("pause");
			return 0;
		}
			
		double money = inputArray[0]; // the amount of money  to be changed
		int basesNum = (int)inputArray[1]; // the number of bases
		//double* bases = (double*)calloc((counter - 2), sizeof(double)); // each base size
		vector<double> bases; // each base denomination
		for (int i = 2; i < counter; i++)
		{
			//bases[i - 2] = inputArray[i]; // assign bases array
			bases.push_back(inputArray[i]);
		}
		sort(bases.begin(), bases.end()); // sort base denomination from low to high

		double minimumBase = bases[0];
		vector<double> leftoverMoney; // leftover money
		// record making change denomination for each posible money
		double* changeRecord = (double*)calloc((money + 1), sizeof(double));
		/*
			there are two most basic making changes situation
			1 ¡¢ no money need to change
			2 ¡¢ the minimum money need to change
		*/
		leftoverMoney.push_back(0);
		changeRecord[0] = 0;
		leftoverMoney.insert((leftoverMoney.begin() + minimumBase), 1);
		changeRecord[(int)minimumBase] = minimumBase;

		for (int i = (2 * minimumBase); i <= (int)money; i += minimumBase)
		{
			int minimumCoin = INT_MAX;
			int j = 0; // find the minumun change coins from bases[0] to bases[size]

			while (j < bases.size() && i >= bases[j]) // if current leftover money can be change by using current base
			{
				int tempCoin = leftoverMoney[i - bases[j]] + 1; // from that money plus bases[j] equal to total money need to be changed
				if (tempCoin < minimumCoin)
				{
					minimumCoin = tempCoin;
					changeRecord[i] = bases[j];
				}
				j++;
			}
			leftoverMoney.insert((leftoverMoney.begin() + i), minimumCoin);
		}

		int* baseChangeNum = (int*)calloc((bases.back() + 1), sizeof(int)); // record each base was changed times
		double leftoverMoneyAfterChange = money;
		while (leftoverMoneyAfterChange != 0)
		{
			baseChangeNum[(int)changeRecord[(int)leftoverMoneyAfterChange]]++; // correspond base changed time ++
			leftoverMoneyAfterChange -= changeRecord[(int)leftoverMoneyAfterChange];
		}

		cout << leftoverMoney[money] << endl; // output the number of making changes coins

		for (int i = 0; i < bases.size(); i++)
		{
			if (baseChangeNum[(int)bases[i]] != 0)
			{
				cout << bases[i] << " x " << "(" << baseChangeNum[(int)bases[i]] << ")" << " + ";	
			}
		}

		cout << '\b' << '\b'; // Cursor moves 1 position backwards
		cout << " " << endl; // Overwrites character '+' with space

	} // while ( true )

	return 0;
}

