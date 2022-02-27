/*
 * C++ Corner Grocer Code
 * 
 * Updates made by: Jacob M. Petrelle
 * Date: 02/27/22
 */

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream> // Include for working with files

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code"); // Changed to name of py file
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}


/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code"); // Changed to name of py file
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}


/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code"); // Changed to name of py file
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


// Program logic for prompts, inputs, and outputs
void Menu() {
	// Decalre variables for user inputs
	string userChoice;
	string userString;
	int itemFrequency; // Declare variable for how many times a produce item appears on list
	// Declare an exit key
	bool exitKey = false;

	// Start loop for menu
	while (!exitKey == true) {
		// Print a menu with possible choices
		cout << "*************************************************************************************************" << endl;
		cout << "* 1: Display list of all produce and the frequency that each produce was purchased              *" << endl;
		cout << "* 2: Display frequency of a certain produce that was purchased                                  *" << endl;
		cout << "* 3: Display list of all produce with '*'s representing the frequency of each purchased produce *" << endl;
		cout << "* 4: Exit                                                                                       *" << endl;
		cout << "*************************************************************************************************" << endl;
		
		// Prompt and get user input
		cout << "Enter 1, 2, 3, or 4: ";
		cin >> userChoice;
		cout << endl;
		
		// Check what user input is
		if (userChoice == "1") {
			CallProcedure("PrintProduceAndNumberList"); // Call CallProcedure function to have Python print produce and fequency list
		}

		else if (userChoice == "2") {
			// Prompt and get second user input as a string
			cout << "Enter name of a produce item, capitalized and ending in 's' where possible: ";
			cin >> userString;
			cout << endl;

			// Pass user string to python function to return frequency 
			itemFrequency = callIntFunc("PrintFrequencyOfProduceItem", userString);
			
			// If userString is not on the list, then it has a frequency of 0
			if (itemFrequency == 0) {
				cout << "Item is not on list" << endl; 
			}
			else {
				cout << "Number of times produce item was purchased: " << itemFrequency << endl; // Print frequency
			}
		}

		else if (userChoice == "3") {
			CallProcedure("WritingProduceAndNumberFile"); // Call CallProcedure function to have Python create a file
			ifstream file; //Input file stream
			string itemName; // Hold itemName 
			int itemFrequency; // Declare frequency variable for produce items
			file.open("frequency.dat"); // Open file that Python Created

			// Check if file is open
			if (file.is_open()) {
				// Loop to assign each pair of elements from opened file with itemName and itemFrequency
				while (file >> itemName >> itemFrequency) {
					cout << itemName << " "; // Print itemName with a space
					// Loop to print '*'s equal to the number of itemFrequency
					for (int i = 0; i < itemFrequency; ++i) {
						cout << "*";
					}
					cout << endl; // Newline
				}
			}
			// Print error if file cannot open
			else {
				cout << "File cannot open" << endl;
			}
		}
		else if (userChoice == "4") {
			cout << "Exit Program" << endl;
			exitKey = true; // Change exitKey to end program
		}

		// Print error message for input validation
		else {
			cin.clear(); // Clear previous input
			cin.ignore(100, '\n');
			cout << "Invalid input" << endl;
		}
		cout << endl << endl;
	}
}


int main() {
	Menu(); // Call menu logic
}