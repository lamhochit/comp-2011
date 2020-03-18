#include <cmath>
#include <ctime>
#include <iostream>
#include <climits>
#include <cstdlib>

#include "lab6.h"

using namespace std;

// Utility functions
int euclidean_distance(const Point& p1, const Point& p2) {
	float x_diff = p1.x - p2.x;
	float y_diff = p1.y - p2.y;

	return ceil(sqrt(x_diff * x_diff + y_diff * y_diff));
}

void print_location(const Point& location) {
	cout << "Location: (" << location.x << ", " << location.y << ")" << endl;
}

/* functions for fuel */

void init_fuelprice(int fuelprice[][NUM_FUEL_TYPES]) {
	// i=0 Caltex; i=1 Esso; i=2 Sinopec; i=3 Shell
	// j=0 Premium; j=1 Regular; j=2 Diesel
	for (int i = 0; i < NUM_OF_BRANDS; i++)
		for (int j = 0; j < NUM_FUEL_TYPES; j++)
            switch (j) {
                case Premium:
                    fuelprice[i][j] = 19 + (rand() % 5 - 2);
                    break;
                case Regular:
                    fuelprice[i][j] = 18 + (rand() % 5 - 2);
                    break;
                case Diesel:
                    fuelprice[i][j] = 14 + (rand() % 5 - 2);
                    break;
            }
}


void print_fuelprices(const int fuelprice[][NUM_FUEL_TYPES]) {
    cout << endl;
	cout << "===================" << endl;
	cout << "Today's fuel prices" << endl;
	cout << "===================" << endl;
	for (int i = 0; i < NUM_OF_BRANDS; i++) {
		cout << brandname[static_cast<Brand>(i)];
        cout << endl;
        
		for (int j = 0; j < NUM_FUEL_TYPES; j++) {
            cout << '\t';
			cout << fueltype[static_cast<FuelType>(j)];
			cout << ": " << fuelprice[i][j] << endl;
		}
	}
}

/* functions for gas stations */

// FUNCTION 1
/**
   TODO: Initialize an array of GasStations.
   Each gas station is initialized with random brand, and a random location in 2D area.
 **/

void init_gas_stations(GasStation stations[], int num_of_stations) {
	for(int i = 0; i < num_of_stations; i++){
		stations[i].brand = Brand(rand()%NUM_OF_BRANDS);
		stations[i].location.x = rand()%X_RANGE;
		stations[i].location.y = rand()%Y_RANGE;
	}
}

// FUNCTION 2
/**
   TODO: print brand and location information of a given gas station.
   Feel free to decide the output formats as long as it is readable.
 **/
void print_a_gas_station(const GasStation& gs) {
		cout << " Brand: " << brandname[gs.brand] << endl;
		cout << "Location: (" << gs.location.x << ", " << gs.location.y << ")" << endl;
}

// FUNCTION 3
/**
   TODO: print brand and location information of all gas stations.
   Feel free to decide the output formats as long as it is readable.
 **/
void print_gas_stations(const GasStation stations[], int num_of_stations) {
	cout << "\n============\nGas Stations\n============\n";		   
	for(int i = 0; i < num_of_stations; i++){
		cout << "#" << i;	
		print_a_gas_station(stations[i]);
	}
}



/* functions for car */

// FUNCTION 4
/**
   TODO: Initialize a car.
   The car is initialized with random location in 2D area.
   Its tank capacity is FULL_TANK.
   Its remain fuel is a random number in [0, FULL_TANK - 1].
   It uses a random kind of fuel.
 **/
void init_car(Car& car) {
	car.location.x = rand()%X_RANGE;
	car.location.y = rand()%Y_RANGE;
	car.tankcapacity = FULL_TANK;
	car.remainfuel = rand()%FULL_TANK;
	car.fueltype = FuelType(rand() % NUM_FUEL_TYPES);
}

// FUNCTION 5
/**
   TODO: Print car information, i.e. location, tank capacity, type of fuel used, remaining fuel.
   Feel free to decide the output formats as long as it is readable.
 **/
void print_car(const Car& car) {
	cout << "\n============\nLab6 Car\n============" << endl;
	cout << "Location: (" << car.location.x << ", " << car.location.y << ")" << endl;
	cout << "Fuel: " << fueltype[car.fueltype] << endl;
	cout << "Tank capacity: " << car.tankcapacity << endl;
	cout << "Remained fuel: " << car.remainfuel << endl;
}

// FUNCTION 6
/**
   TODO: Find all gas stations that the car can reach with gasoline left in the tank.
   For example, if the car has 20 litres of gasoline left,
   assuming gasoline consumption is GAS_PER_KM (which is 1) litre per km,
   the car can only reach gas stations within distance 20.
   The car will consume more gasoline when drive towards the gas station.
   When the car reaches the gas station, it will add gasoline to full tank.

   For each gas station reachable, print its distance to the car location, gasoline to be added, and total gasoline cost
   Feel free to decide the output formats as long as it is readable.

   The function should return the index of gas station, with minimum gasoline cost.
   If the car can't reach any gas station, return -1.
 **/

int choose_station(const GasStation stations[], int num_of_stations, const int fuelprice[][NUM_FUEL_TYPES], const Car& car) {
	int counter = 0;
	int idx = 0;
	int price, min;
	min = (car.tankcapacity - (car.remainfuel - euclidean_distance(stations[0].location, car.location) * GAS_PER_KM))*(fuelprice[stations[0].brand][car.fueltype]);
	for(int i = 0; i < num_of_stations; i++){
		if(euclidean_distance(stations[i].location, car.location) <= car.remainfuel / GAS_PER_KM){
			counter++;
			price = (car.tankcapacity - (car.remainfuel - euclidean_distance(stations[i].location, car.location) * GAS_PER_KM))*(fuelprice[stations[i].brand][car.fueltype]);
			if(price < min){
				min = price;
				idx = i;
			}
		}	
	}
	if(counter != 0)
		cout << "\n===========================\nGas stations can be reached\n===========================" << endl;
	if(counter == 0)
		return -1;
	for(int i = 0; i < num_of_stations; i++){
		if(euclidean_distance(stations[i].location, car.location) <= car.remainfuel / GAS_PER_KM){
			cout << "#" << i << "   Brand:" << brandname[stations[i].brand] << "   Location: (" << stations[i].location.x << ", " << stations[i].location.y << ")" << endl;
			cout << "     Dist: " << euclidean_distance(stations[i].location, car.location);
			int new_remain_fuel = car.remainfuel - euclidean_distance(stations[i].location, car.location) * GAS_PER_KM;
			cout << "  Gas to add: " << car.tankcapacity - new_remain_fuel << "L" << endl;
			cout << "     Price: " << fuelprice[stations[i].brand][car.fueltype];
			cout << "   Total: " << fuelprice[stations[i].brand][car.fueltype] * (car.tankcapacity - new_remain_fuel) << endl;
		}
	}
	return idx;
}

/* Driver program to test all functions */
int main() {
	srand(time(0));

	// set imaginary fuel prices
	int fuelprice[NUM_OF_BRANDS][NUM_FUEL_TYPES];
	init_fuelprice(fuelprice);
	print_fuelprices(fuelprice);

	// create gas stations at random locations

	GasStation stations[NUM_OF_STATIONS];
	init_gas_stations(stations, NUM_OF_STATIONS);
	print_gas_stations(stations, NUM_OF_STATIONS);

	// car information
	Car lab6car;
	init_car(lab6car);
	print_car(lab6car);

	// choose gas station
	int idx = choose_station(stations, NUM_OF_STATIONS, fuelprice, lab6car);
	if (idx == -1) {
		cout << "No feasible solution" << endl;
	}
	else {
		cout << endl << "Best choice:" << endl;
		cout << "#" << idx;
		print_a_gas_station(stations[idx]);
	}
}

