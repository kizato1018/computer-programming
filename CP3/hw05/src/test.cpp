#include <iostream>
#include <iomanip>
#include "map_unit.h"

using namespace std;

int main() {
	int arr[5] = {1,2,3,4,5};
	UpgradableUnit *NU = new UpgradableUnit(9,"USA",100,100,arr);
	NU->Map_Show(4);
}