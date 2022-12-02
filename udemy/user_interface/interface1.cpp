#include <iostream>
#include <vector>
#include <cctype> 

using namespace std;

// Prototype
void display_menu();
char get_selection();


// Handling
void handle_add(vector<int> &x);
void handle_print(vector<int> &x);
void handle_remove(vector<int> &x);
void handle_smallest(vector<int> &x);
void handle_largest(vector<int> &x);
void handle_average(vector<int> &x);
void handle_find(vector<int> &x);


// Logic prototype
void print_list(vector<int> &x);


int main ()
{
    vector<int> numbers;
    char selection;

    do
    {
        display_menu();
        selection = get_selection();
        
        switch (selection)
        {
        case 'A':
            handle_add(numbers);
            break;
        case 'P':
            handle_print(numbers);
            break;
        case 'R':
            handle_remove(numbers);
            break;
        case 'S':
            handle_smallest(numbers);
            break;
        case 'L':
            handle_largest(numbers);
            break;
        case 'M':
            handle_average(numbers);
            break;
        case 'F':
            handle_find(numbers);
            break;
        default:
            break;
        }
    } while (selection != 'Q');

    return 0;
}

void display_menu()
{
    cout << "\nP - Print numbers" << endl;
    cout << "A - Add a number" << endl;
    cout << "R - Remove all numbers" << endl;
    cout << "M - Display average value" << endl;
    cout << "S - Display the smallest number" << endl;
    cout << "L - Display the largest number"<< endl;
    cout << "F - Find a number" << endl;
    cout << "Q - Quit" << endl;
    cout << "\nEnter your choice: ";
}

char get_selection()
{
    char selection {};
    cin >> selection;
    return toupper(selection);
}

void handle_add(vector<int> &x)
{
    int input {};
    cout << "Enter a integer number: ";
    cin >> input;
    x.push_back(input);
    cout << " added" << endl;
}

void print_list(vector<int> &x)
{
    cout << " [ ";
    for (int i:x)
    {
        cout << " " << i << " "; 
    }
    cout << " ] ";
}


void handle_print(vector<int> &x)
{
    if (x.size() == 0)
    {
        cout << " List is empty." << endl;
    }
    else
    {
        print_list(x);
    }
}

void handle_remove(vector<int> &x)
{
    if (x.size() == 0)
    {
        cout << " List is empty." << endl;
    }
    else
    {
        x.clear();
        cout << " Whole list is removed." << endl;
    }
}

int get_smallest(vector<int> &x)
{
    int smallest = x.at(0);
    for (int num:x)
    {
        if (num < smallest)
            smallest = num;
    }
    return smallest;
}

void handle_smallest(vector<int> &x)
{
    if (x.size() == 0)
    {
        cout << " List is empty." << endl;
    }
    else
    {
        cout << " The smallest number is: " << get_smallest(x) << endl;
    }
}

int get_largest(vector<int> &x)
{
    int largest = x.at(0);
    for (int num:x)
    {
        if (num > largest)
            largest = num;
    }
    return largest;
}

void handle_largest(vector<int> &x)
{
    if (x.size() == 0)
    {
        cout << " List is empty." << endl;
    }
    else
    {
        cout << " The largest number is: " << get_largest(x) << endl;
    }
}

double calculate_average(vector<int> &x)
{
    double sum {};
    for (int num:x)
    {
        sum += num;
    }
    return (sum/x.size());
}

void handle_average(vector<int> &x)
{
    if (x.size() == 0)
    {
        cout << " List is empty." << endl;
    }
    else
    {
        cout << " Average number is: " << calculate_average(x) << endl;
    }
}

bool find_number(vector<int> &x, int target)
{
    for (int num:x)
    {
        if (num  == target)
            return true;
    }
    return false;
}

void handle_find(vector<int> &x)
{
    int target {};
    cout << " Enter number to find: "<< endl;
    cin >> target;


    cout << " Is exist number: " << target;
    if ( find_number(x, target) )
        cout << " TRUE";
    else
        cout << " FALSE";
    cout << endl;
}
