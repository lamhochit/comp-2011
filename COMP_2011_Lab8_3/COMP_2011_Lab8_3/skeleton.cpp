#include <iostream>
#include <cstring>
#include "lab8.h"
using namespace std;

// global variable declaration
extern Registry regis;

// helper function for internal usage
Person* searchPerson(const char name[MAX_NAME_LENGTH]) {
    for (int i = 0; i < regis.num; i++)
        if (strncmp(regis.p[i]->name, name, MAX_NAME_LENGTH) == 0)
            return regis.p[i];
    return nullptr;
}

void printPerson(const Person* p, int tab){
    for (int i = 0; i < tab; i++)
        cout << '\t';
    if (p == nullptr){
        cout << "Error:"  << "No such person!" << endl;
        return;
    }

    cout << "Name: " << p->name
            << ", Sex: " << ((p->sex == male)? "Male" : "Female")
            << ", Identity: " << ((p->identity == Wizardkind)? "Wizardkind" : "Muggle")
            << ", Age: " << p->age << endl;
}

// Task 1 (cancelled, code is now given)
// create a new Person object and add him/her to registry
// relationship pointers (e.g. father, mother, spouse, all kids) are nullptr
// return pointer to the person
// Fail to create if registry is full, or the person with same name already in registry
// return nullptr in this case
Person* createPerson(const char name[MAX_NAME_LENGTH], const SEX sex, const IDENTITY identity, int age) {
    if (regis.num >= MAX_REGISTRY_NUM){
        cout << "Error:"  << "Registry is full already! Can't create a new person." << endl;
        return nullptr;
    }
    if (searchPerson(name)){
        cout << "Error: "  << name << "already exist in the registry." << endl;
        return nullptr;
    }

    Person* newPerson = new Person {sex, identity, {}, age, nullptr, nullptr, nullptr, {}};
    strncpy(newPerson->name, name, MAX_NAME_LENGTH);
    regis.p[regis.num++] = newPerson;

    cout << name << " is created and added to registry." << endl;
    return newPerson;
}

// Task 2
// setup spouse pointer for both husband and wife
// bigamy is not allowed
// can't marry to a person who doesn't exist in registry
bool getMarried(const char male[MAX_NAME_LENGTH], const char female[MAX_NAME_LENGTH]) {
    if (!(searchPerson(male) && searchPerson(female))) {
        cout << "Error: " << male << " is not in the registry." << endl;
        return false;
    }
    else
    {
        Person* maleP = searchPerson(male);
        Person* femaleP = searchPerson(female);
        if (maleP->spouse != nullptr || femaleP->spouse != nullptr){
            cout << "Error: " << male << " or/and " << female << " is/are married. " << endl;;
            return false;
        }
        maleP->spouse = femaleP;
        femaleP-> spouse = maleP;
        cout << male << " and " << female << " are married." << endl;
    }

    return true;
}

// Task 3
// setup pointer(s) in kid[] for both mother and father
// setup mother/father pointer for the kid
// can't add the kid if he/she already added or the kid array is full
// Assumption for simplicity:
// father/mother/kid already exist in registry
// No single parent
// No divorce (that is, kid array for a couple should be the same
bool addKid(const char father_name[MAX_NAME_LENGTH], const char mother_name[MAX_NAME_LENGTH], const char kid_name[MAX_NAME_LENGTH]) {
    Person* fatherP = searchPerson(father_name);
    Person* motherP = searchPerson(mother_name);
    Person* kidP = searchPerson(kid_name);
    if (kidP->mother != nullptr || kidP->father != nullptr)
    {
        cout << kid_name << " already has a parent. " << endl;
        return false;
    }
    int i = 0;
    while (i < MAX_KID_NUM)
    {
        if (motherP->kid[i] == nullptr && fatherP->kid[i] == nullptr)
        {
            motherP->kid[i] = kidP;
            fatherP->kid[i] = kidP;
            kidP->mother = motherP;
            kidP->father = fatherP;
            cout << father_name << " and " << mother_name << " has become " << kid_name << "\'s parents" << endl;
            break;
        }
        if (i == MAX_KID_NUM - 1)
        {
            cout << father_name << " and " << mother_name << " already reached the max number of kids." << endl;
            return false;
        }
        i++;
    }
    
    return true;
}



// Task 4
// print information of all kids
void printKids(const char name[MAX_NAME_LENGTH]) {
    Person* targetPerson = searchPerson(name);
    cout << "The kids of " << name << " are: ";
    for (int i = 0; i < MAX_KID_NUM && targetPerson->kid[i] != nullptr; i++)
    {
        cout << targetPerson->kid[i]->name << ", ";
    }
}



// Task 5
// print information of parents
void printParents(const char name[MAX_NAME_LENGTH]) {
    Person* kidP = searchPerson(name);
    cout << "The parents of " << name << " are: " << kidP->mother->name << " and " << kidP->father->name << "."<< endl;
}
    


// Optional
// print information of grandparents
void printGrandParents(const char name[MAX_NAME_LENGTH]) {}



// Optional
// print information of all descendents
// hint recursion
void printAllDescendents(const Person* p, int level) {}

