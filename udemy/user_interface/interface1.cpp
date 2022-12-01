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
    cout << "M - Display mean of the numbers" << endl;
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