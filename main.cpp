#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*              Project 5
                November 02, 2017

        This project calculates the standard deviation for a list of numbers
        that is read from a file. The file name is determined by the user.
*/


double avg(double [], int);
//Pre-condition: array and n to be initialized
//Task: Calculate the average from a list of numbers using an array
//Post-condition: Return the average

double sum(double [], int);
//Pre-condition: array and n to be initialized
//Task: Initialize average and summation & sum array - average square it
//Post-coniditon: Return summation

double stddev(double [], int);
//Pre-condition: array and n to be initialized
//Task: initialiaze summation with sum function, take sqrt of summation/(n-1)
//Post-condition: Return value of sqrt

int fill(ifstream &, double[], int);
//Pre-condition: fin, array, n to be initialized
//Task: initialize data and i, run through the array and count elements and close file
//Post-condition: Return i

void filename(ifstream &);
//Pre-condition: fin to be initialized
//Task: Read in file name from user and attempt to open file, if it fails to open 3 times close program
//Post-condition: Open file or exit program (depending on input)

void output(double [], int);
//Pre-condition: arr and total to be initialized
//Task: use stddev function to finish calculations
//Post-condition: Output results

int main() {
    //Initialize variables
    int n = 200, total;
    double array[n];
    ifstream fin;

    //Input
    filename(fin);

    //Processing
    total = fill(fin, array, n);

    //Output
    output(array, total);

    return 0;
}

void output(double arr[], int total) {
    cout << "The standard deviation is: ";
    cout << stddev(arr, total) << endl;
}

int fill(ifstream &fin, double arr[], int n) {
    int i = 0;
    double data;

    //Fill array and count index
    while (fin >> data && i < n) {
        arr[i] = data;
        i++;
    }

    //Close file when we're done with it
    fin.close();

    return i;
}

double avg(double arr[], int size) {
    double average = 0;

    //Add up array
    for (int i = 0; i < size; i++) {
        average += arr[i];
    }

    //Calculate average
    return average / size;
}

double sum(double arr[], int n) {
    double average = avg(arr, n);
    double summation = 0;

    //Calculate numerator for equation
    for (int i = 0; i < n; i++) {
        summation += pow(arr[i] - average, 2);
    }

    return summation;
}

double stddev(double arr[], int n) {
    //Numerator for equation
    double summation = sum(arr, n);

    //Calculate and return rest of equation
    return sqrt(summation / n);
}

void filename(ifstream &fin) {
    int i = 0;
    string name;

    //Prompt user for input
    cout << "Enter the file name: ";
    cin >> name;
    fin.open(name.c_str());
    //Check validity of input
    while ((i < 2) && (fin.fail())) {
        cout << "ERROR: " << name << " couldn't be opened.\n";
        cout << "Enter the file name: ";
        cin >> name;
        fin.open(name.c_str());
        i++;
    }
    //Exit program if failed too many times
    if (fin.fail()) {
        cout << "ERROR: " << name << " couldn't be opened.\n";
        exit(1);
    }
    //Echo
    if (!fin.fail())
        cout << name << " opened successfully.\n";
}