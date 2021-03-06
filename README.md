### 如果 Github 顯示效果不佳，請移步
#### http://codingstory.com.cn/making-changes/


# 前言
> A big THANKS to my "Analysis of Algorithms" course teacher, 張元翔

使用 Dynamic Programming 實現，可得 Optimal Solution。  
**[Source codes have been uploaded to github](https://github.com/ShanQincheng/MakingChanges)**
![](https://github.com/ShanQincheng/MakingChanges/blob/master/Description/0002.jpg)

***
# 環境
```
OS                                    win10, x64
IDE                                   Visual Studio 2017
```

***
# 開始

* 1、Brief Introduction to Dynamic Programming
* 2、How to use DP solve Making Change Problem
* 3、程式碼

***

#### 1、Brief Introduction to Dynamic Programming

* Typically applied to solve **optimization** problems.
* Generally achieve the **optimal solution**.

* **Design Strategy**
![](https://github.com/ShanQincheng/MakingChanges/blob/master/Description/003.png)

***

####  2、How to use DP solve Making Change Problem

###### ( 1 ) 大問題 -> 子問題
**money( 原有的錢 )   -> leftoverMoney ( <= money ) 找零後剩下的錢**  

* 大問題，原有的錢，找零。剩下的錢，變為子問題。  
* 那麼子問題是，剩下的錢，找零。剩下的錢找零后剩下的錢，變為子問題的子問題。
* 一直找錢直到不能再找為止，即 總錢數變為 0 。

###### ( 2 ) 列表法

* 設面額 ( Bases ) base 1 <= base 2 <= ... <= base k  
**E.g.** ( 有三種面額的錢, 1塊， 4塊， 6塊, 那麼 base 1 = 1, base 2 = 4, base 3 = 6, k == 3 )

* 設 leftoverMoney[ i ] ( The least #conis to make change for i )  
  * 要找 1 塊錢, 那麼 leftoverMoney[ 1 ] = = 1, 因為需要**1 張 1 塊錢** 就能找完。
  * 要找 2 塊錢, 那麼 leftoverMoney[ 2 ] = = 2, 因為需要**2 張 1 塊錢** 就能找完。
  * 要找 3 塊錢, 那麼 leftoverMoney[ 3 ] = = 3, 因為需要**3 張 1 塊錢** 就能找完。
  * 要找 4 塊錢, 那麼 leftoverMoney[ 4 ] = = 1, 因為需要**1 張 4 塊錢** 就能找完。
  * 要找 5 塊錢, 那麼 leftoverMoney[ 5 ] = = 2, 因為需要**1 張 4 塊錢 和 1 張 1 塊錢** 就能找完。
  * 要找 6 塊錢, 那麼 leftoverMoney[ 6 ] = = 1, 因為需要**1 張 6 塊錢** 就能找完。
  * **. . .**

leftoverMoney[ i ] 需要注意的是，這是  The least #conins to make change for i.
例如我們要找零 4 塊錢。 可以是 找零**4 張 1 塊錢 一共 4 張**，或是 找零 **1張 4 塊錢 一共 1 張**。我們要從所有可能找零的可能性中**選出找零錢數量最少的那一種**。


**為了更好的理解，請看下圖**
![](https://github.com/ShanQincheng/MakingChanges/blob/master/Description/002.png)



**假設我們需要找 8 塊錢，用上圖的思路列表如下**
![](https://github.com/ShanQincheng/MakingChanges/blob/master/Description/004.png)

***

#### 3、程式碼

###### 重點部分
* **1、需要處理最小的零錢面值不為 1 的情況**
* **2、接第一條，若最小面值不為 1，則需要排除所有無法找零的面額**



請看程式碼注釋部分，便於理解
```language-python line-numbers
// MakingChanges.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


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


```

***
# 以上
2017 年 6 月 17 日

