// MakingChanges.cpp : Defines the entry point for the console application.
//

//	Algorithm Analysis
//	演算法分析機測
//	學號: 10311115 /	04106034
//	姓名：陳震瑜	/	何政霖
//	中原大學資訊工程系


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
		vector<double> bases; // each base denomination
		for (int i = 2; i < counter; i++)
		{
			bases.push_back(inputArray[i]); // assign bases vector
		}
		sort(bases.begin(), bases.end()); // sort bases denomination from low to high

		double minimumBase = bases[0];
		//vector<double> leftoverMoney; // leftover money
		double* leftoverMoney = (double*)calloc((money + 1), sizeof(double)); // change type from vector to array
		for (int i = 0; i < money + 1; i++)
		{
			leftoverMoney[i] = INT_MAX; // use INT_MAX avoid those money can't be changed
		}
		// record making change denomination for each posible money
		double* changeRecord = (double*)calloc((money + 1), sizeof(double));
		/*
			there are two most basic making changes situation
			1 、 no money need to change
			2 、 the minimum money need to change
		*/
		//leftoverMoney.push_back(0);
		leftoverMoney[0] = 0;
		changeRecord[0] = 0;
		//leftoverMoney.insert((leftoverMoney.begin() + minimumBase), 1);
		leftoverMoney[(int)minimumBase] = 1; // array can assign to specify positon as long as that position has been malloced 
		changeRecord[(int)minimumBase] = minimumBase;

		//for (int i = (2 * minimumBase); i <= (int)money; i += minimumBase)
		//for (int i = (2 * minimumBase); i <= (int)money; i++)
		for (int i = (minimumBase + 1); i <= (int)money; i++)
		{
			int minimumCoin = INT_MAX;
			int j = 0; // find the minumun change coins from bases[0] to bases[size]

			while (j < bases.size() && i >= bases[j]) // if current leftover money can be change by using current base
			{
				if (leftoverMoney[(int)(i - bases[j])] == INT_MAX) // 如果當前的錢找零後，剩下的錢需要找零的次數是無限大的話，說明當前找零錢方案行不通
				{
					j++; // for another change plan
					continue;
				}
					
				int tempCoin = leftoverMoney[(int)(i - bases[j])] + 1; // from that money plus bases[j] equal to total money need to be changed
				if (tempCoin < minimumCoin)
				{
					minimumCoin = tempCoin;
					changeRecord[i] = bases[j];
				}
				j++;
			}
			//leftoverMoney.insert((leftoverMoney.begin() + i), minimumCoin);
			leftoverMoney[i] = minimumCoin;
		}

		int* baseChangeNum = (int*)calloc((bases.back() + 1), sizeof(int)); // record each base was changed times
		double leftoverMoneyAfterChange = money;
		while (leftoverMoneyAfterChange != 0)
		{
			baseChangeNum[(int)changeRecord[(int)leftoverMoneyAfterChange]]++; // correspond base changed time ++
			leftoverMoneyAfterChange -= changeRecord[(int)leftoverMoneyAfterChange];
		}

		//cout << leftoverMoney[money] << endl; // output the number of making changes coins
		cout << leftoverMoney[(int)money] << endl; // output the number of making changes coins

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

