#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <math.h>
#include <conio.h>
#include <Windows.h>

using namespace std;
//------------------------------------------------------cities
struct cities
{
	string s[312];
	int fit;
	int rank;
	int lowerbound;
	int upperbound;
	string getcity(int i)
	{
		return (s[i]);
	}

	void setcity(int place, string i)
	{
		s[place] = i;
	}

	cities()
	{
		fit = 0;
		rank = 0;
		lowerbound = 0;
		upperbound = 0;
	}
};

//------------------------------------------------------insertion sort

void insertion_sort(vector<cities>& v) {
	int j, temp;
	cities tempc;

	for (int i = 0; i < v.size(); i++) {
		j = i;

		while (j > 0 && v[j].fit < v[j - 1].fit) {
			tempc = v[j];
			v[j] = v[j - 1];
			v[j - 1] = tempc;
			j--;
		}
	}
}


void insertion_sortdec(vector<cities>& v) {
	int j, temp;
	cities tempc;

	for (int i = 0; i < v.size(); i++) {
		j = i;

		while (j > 0 && v[j].fit > v[j - 1].fit) {
			tempc = v[j];
			v[j] = v[j - 1];
			v[j - 1] = tempc;
			j--;
		}
	}
}

void insertion_sort_rank(vector<cities>& v) {
	int j, temp;
	cities tempc;

	for (int i = 0; i < v.size(); i++) {
		j = i;

		while (j > 0 && v[j].rank < v[j - 1].rank) {
			tempc = v[j];
			v[j] = v[j - 1];
			v[j - 1] = tempc;
			j--;
		}
	}
}

void insertion_sort_rank_desc(vector<cities>& v) {
	int j, temp;
	cities tempc;

	for (int i = 0; i < v.size(); i++) {
		j = i;

		while (j > 0 && v[j].rank > v[j - 1].rank) {
			tempc = v[j];
			v[j] = v[j - 1];
			v[j - 1] = tempc;
			j--;
		}
	}
}
//--------------------------------------------------------------
void randomcities(cities & c)
{
	Sleep(1000);
	int num_of_time_swap = rand() % 100;
	int num1 = 0;
	int num2 = 0;
	string c1;
	string c2;

	for (int i = 0; i < num_of_time_swap; i++)
	{

		num1 = rand() % 312;
		Sleep(50);
		num2 = rand();
		num2 = (num2 + i*num1) % 312;
		c1 = c.getcity(num1);
		c2 = c.getcity(num2);

		c.setcity(num1, c2);
		c.setcity(num2, c1);
	}

}
//--------------------------------------------------------------fitness
void Calculatefitness(vector<int> v, cities & c)
{
	int count = 0;
	int temp = 0;
	int index1 = 0;
	int index2 = 0;
	int fitness = 0;

	for (int i = 0; i < 311; i++)
	{
		temp = 0;
		temp = 312 * stoi(c.getcity(i));
		index1 = stoi(c.getcity(i)) + temp;
		index2 = stoi(c.getcity(i + 1)) + temp;
		fitness = fitness + abs(v[index1] - v[index2]);

		count = count + 1;
	}
	temp = 0;
	temp = 312 * 311;

	index1 = stoi(c.getcity(311)) + temp;
	index2 = stoi(c.getcity(0)) + temp;
	fitness = fitness + abs(v[index1] - v[index2]);

	c.fit = -(fitness - 300000);
}

double round(double d)
{
	return floor(d + 0.5);
}

int setprobabilities(cities & c, long long int totalf, int low)
{
	double temp = 0;
	c.lowerbound = low;
	temp = (static_cast<double>(c.fit) / static_cast<double>(totalf)) * 100;
	c.upperbound = low + round(temp) - 1;
	return c.upperbound;
}


void TSP()
{
	//-------------------------------------------------declarations
	long long int total_fitness = 0;
	int temp = 0;
	int k = 0;
	cities c;
	vector<cities> number_of_chromosomes;
	vector<cities> temp_chromosomes;
	vector<int> dist;
	//----------------------------------------------------filing
	// Reading data from File

	ifstream fin;	// object to read data from file.
	string myString;
	int word_count = 0;

	fin.open("input.txt", ios::in);	// opening file input.txt.

	if (!fin)	//Check if file has been opened or not.
	{
		cout << "Could not open the input file.\n";
		return;
	}

	cout << "Reading data character by character:\n";

	while (!fin.eof())		//Read until end of file.
	{
		fin >> myString;		//Read a word from file.
		dist.push_back(stoi(myString));
		word_count++;
	}

	fin.close();		//Close file after reading data.
						//cout<<dist[dist.size()-2]<<endl;
						//cout<<"Word Count = "<<word_count<<endl;




						//----------------------------------------------------- cities


	for (int i = 0; i<312; i++)
	{
		string temp2 = to_string(i);
		c.setcity(i, temp2);
	}
	//randomcities(c);
	//for(int i=0;i<312;i++)
	//{
	//	cout<<c.getcity(i)<<" ";
	//}
	//----------------------------------------------------population
	int mut = 0;
	cout << "enter Population of problem" << endl;
	cin >> k;
	int cross;
	cout << "enter crossover technique" << endl;
	cin >> cross;
	int select = 0;

	cout << "enter selection criteria" << endl;
	cin >> select;

	cout << "Select Mutation Rate" << endl;
	cin >> mut;
	int iteration = 0;
	int minimumfitness = 0;
	cout << "Select iterations" << endl;
	cin >> iteration;
	cout << "Select fitness" << endl;
	cin >> minimumfitness;

	cout << "-------------------------------" << endl;
	for (int i = 0; i < k; i++)
	{
		randomcities(c);
		Calculatefitness(dist, c);
		number_of_chromosomes.push_back(c);
		temp_chromosomes.push_back(c);
		Sleep(100);
	}

	//----------------------------------------------------------------------total fitness
	int found = 0;
	//------------------------------------------------------------------------testing
	//insertion_sortdec(number_of_chromosomes);
	for (int p = 0; p < iteration; p++)
	{
		total_fitness = 0;
		for (int i = 0; i < number_of_chromosomes.size(); i++)
		{
			//cout<<"---------"<<endl;
			//for(int j = 0 ; j < 312 ; j++)
			//{
			//cout<<number_of_chromosomes[i].getcity(j)<<" ";

			//}
			//cout<<"\\\\\\\\\\\\\\\\\\\\"<<number_of_chromosomes[i].fit<<endl;
			total_fitness = total_fitness + number_of_chromosomes[i].fit;
			if (number_of_chromosomes[i].fit >= minimumfitness)
			{
				found = 1;
				cout << "found cromosome with required fitness " << number_of_chromosomes[i].fit << endl;
				break;
			}

		}//--------------------------------------end of for
		 //----------------------------------------------------------------------------------------------------------------

		if (found == 1)
		{
			break;
		}

		int temp4 = 0;
		for (int i = 0; i < number_of_chromosomes.size(); i++)
		{



			temp4 = setprobabilities(number_of_chromosomes[i], total_fitness, temp4 + 1);
			cout << "lower bound" << number_of_chromosomes[i].lowerbound;
			cout << "upper bound" << number_of_chromosomes[i].upperbound << endl;
		}//--------------------------------------end of for


		 //----------------------------------------------------------------------Selection by fitness

		cities c1, c2, c3;
		//--------------------------------
		for (int o = 0; o < k / 2; o++)
		{
			if (select == 1)
			{

				int random = 0;

				while (random == 0)
				{
					random = rand() % 101;
				}
				for (int i = 0; i < number_of_chromosomes.size(); i++)
				{
					if (random >= number_of_chromosomes[i].lowerbound && random <= number_of_chromosomes[i].upperbound)
					{
						c1 = number_of_chromosomes[i];
					}

				}//--------------------------------------end of for
				Sleep(1000);
				random = 0;
				while (random == 0)
				{
					random = rand() % 101;
				}
				for (int i = 0; i < number_of_chromosomes.size(); i++)
				{
					if (random >= number_of_chromosomes[i].lowerbound && random <= number_of_chromosomes[i].upperbound)
					{
						c2 = number_of_chromosomes[i];
					}

				}//--------------------------------------end of for
			}//---------------------------------------end of select

			c3 = c1;
			//---------------------------------------------------crossover
			if (cross == 1)
			{
				int random2 = rand() % 312;
				string temp5;
				for (int i = 0; i < random2; i++)
				{
					for (int j = 0; j < 311; j++)
					{
						if (c1.getcity(j) == c2.getcity(i))
						{
							temp5 = c1.getcity(i);
							//c1.getcity(i) = c1.getcity(j);
							c1.setcity(i, c1.getcity(j));
							//c1.getcity(j) = temp5;
							c1.setcity(j, temp5);
							break;
						}
					}

				}
				//-------------------------

				for (int i = 311; i > random2; i--)
				{
					for (int j = 0; j < 311; j++)
					{
						if (c3.getcity(i) == c2.getcity(j))
						{
							temp5 = c2.getcity(i);
							//c2.getcity(i) = c2.getcity(j);
							c2.setcity(i, c2.getcity(j));
							//c2.getcity(j) = temp5;
							c2.setcity(j, temp5);
							break;
						}
					}

				}
			}

			//-------------------------------------------end of crossover
			//----------------------------------------------------------------------Mutation
			int random3 = 0;
			int swap1 = 0;
			int swap2 = 0;

			random3 = rand() % 100;
			swap1 = rand() % 100;
			swap2 = rand() % 100;

			if (random3 <= mut)
			{
				string temp7;
				string temp8;
				swap1 = rand() % 312;
				Sleep(1000);
				swap2 = rand() % 312;
				temp7 = c1.getcity(swap1);
				temp8 = c1.getcity(swap2);
				c1.setcity(swap1, temp8);
				c1.setcity(swap1, temp7);

			}

			//-----------------------------------------------------------------------
			Calculatefitness(dist, c1);
			Calculatefitness(dist, c2);
			temp_chromosomes.push_back(c1);
			temp_chromosomes.push_back(c2);
		}
		insertion_sortdec(temp_chromosomes);
		number_of_chromosomes.clear();
		for (int i = 0; i < k; i++)
		{
			number_of_chromosomes.push_back(temp_chromosomes[i]);
		}
		temp_chromosomes = number_of_chromosomes;



		//--------------------------------------------------------------------------------------------------------------
		for (int i = 0; i < number_of_chromosomes.size(); i++)
		{
			//cout<<"---------"<<endl;
			//for(int j = 0 ; j < 312 ; j++)
			//{
			//cout<<number_of_chromosomes[i].getcity(j)<<" ";

			//}
			//cout<<"\\\\\\\\\\\\\\\\\\\\"<<number_of_chromosomes[i].fit<<endl;
			total_fitness = total_fitness + number_of_chromosomes[i].fit;
			if (number_of_chromosomes[i].fit >= minimumfitness)
			{
				found = 1;
				cout << "found cromosome with required fitness " << number_of_chromosomes[i].fit << endl;
				break;
			}

		}//--------------------------------------end of for
		 //----------------------------------------------------------------------------------------------------------------

		if (found == 1)
		{
			break;
		}
		//--------------------------------------------------------------------------------------------------------------
	}
	//cout<<"total"<<total_fitness<<endl;
	//Calculatefitness(dist,c);
	//cout<<"\\\\\\\\\\\\\\\\\\\\"<<c.fit;
	if (found == 0)
	{
		cout << "not found" << endl;
		insertion_sortdec(number_of_chromosomes);
		cout << number_of_chromosomes[0].fit << endl;
	}
}

void main()
{
	srand((int)time(0));
	TSP();


	//cout<<rand();
	//TSP();
}