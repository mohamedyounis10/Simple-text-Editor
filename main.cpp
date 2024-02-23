//Simple text Editor
#include <iostream>
using namespace std;

//class node
struct node
{
    string item;
    node *next;
};

//Build ADT stack using linkedlist
class stack_linkedlist
{

private:
    node* top;

public:

    stack_linkedlist() //constructor
    {
        top=NULL;
    }

    bool isempty() //isempty
    {
        return top==NULL;
    }

    void push(string a) //push
    {
        node*ptr = new node;
        ptr->item=a;
        ptr->next=top;
        top=ptr;
    }

    string pop_string()  //pop
    {
        if(isempty())
        {
            cout<<"sorry...stack is empty"<<endl;
            return 0;
        }else{
        string n;
        node *ptr;
        n=top->item;
        ptr=top;
        top=top->next;
        delete ptr;
        return n;
        }
    }


    string get_top() //gettop
    {
       return top->item;
    }

    string delete_last() //delete last character in last string in last node
    {
         if (isempty())
        {
            cout << "Sorry...stack is empty" << endl;
            return" ";
        }

      node *ptr = top;
         while (ptr->next != NULL)
        {
           ptr = ptr->next;
        }

        // Delete the last character of the last string
         string deletedString;

        // Delete the last character of the last string
        if (!ptr->item.empty())
       {
        string a = ptr->item;
        int len = a.size();

        if (len > 0) {
            // Create a new string without the last character
            string newString;
            for (int i = 0; i < len - 1; ++i) {
                newString += a[i];
            }
            deletedString = a[len - 1];
            ptr->item = newString;
          }
        }

        if (ptr->item.empty())
       {
           pop_string();
       }

       return deletedString;
    }

    void display() //display(LIFO OR FILO)
    {
        for(node *ptr=top ; ptr!=NULL ; ptr=ptr->next)
        {
            cout<<ptr->item<<" ";
        }
        cout<<endl;
    }

    string display_index(int index) //display index nodes
    {
         int currentindex = 0;
        stack_linkedlist tempStack;

        // Copy the items to a temporary stack
        for (node* ptr = top; ptr != NULL; ptr = ptr->next)
        {
            tempStack.push(ptr->item);
        }

        for (node* ptr = tempStack.top; ptr != NULL; ptr = ptr->next)
        {
            if (currentindex == index)
            {
                cout << "Item at index " << index << ": " << ptr->item << endl;
                return ptr->item ;
            }
            currentindex++;
        }
        cout << "Not found" << endl;
        return NULL;
    }

    void display_inverse() // display inverse
    {
        if (isempty())
        {
            cout << "Sorry....stack is empty" << endl;
        }

        stack_linkedlist l;
        string a;
        node* ptr;
        for (ptr = top; ptr != NULL; ptr = ptr->next)
        {
            a = ptr->item;
            l.push(a);
        }
        l.display();
    }

};

// Undo operation function
/*
-Know using pointer to pass stack_linkedlist but when use
pointer to access to methods in stack_linkedlist use (->) not (.).
-The arrow notation is a shorthand for dereferencing a pointer and
accessing the member or method.
*/
void UNDO(stack_linkedlist* Undo, stack_linkedlist* Redo)
{
    if (Undo->isempty())
    {
        Undo->push(Redo->pop_string());
        return;
    }

    // Transfer characters from Undo to Redo
    while (!Undo->isempty())
    {
        string undonstring = Undo->pop_string();
        Redo->push(undonstring);
    }
}

//to check if digit or not
int is_digit(char a)
{
    return (a >= '0' && a <= '9');
}

//main function
int main()
{
    //variables
    string choice; //choice of main menu
    string input=""; //accept string from user
    stack_linkedlist text; //main stack
    stack_linkedlist history; //history stack

    bool datastatus = false; //to check if date entre or not

    cout << "----.Hello.-----" << endl;

    do
    {
        cout << "------menu------" << endl;
        cout << "1. Append" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Print" << endl;
        cout << "4. Undo" << endl;
        cout << "5. Exit" << endl;

        // to check number from 1-5 not more or less
        while (true)
        {
            try
            {
                cout << "Enter a number between 1 and 5: ";
                if (cin >> choice)
                {
                    if (choice < "1" || choice > "5")
                    {
                        throw invalid_argument("Please enter a number between 1 and 5.");
                    }
                    break; // Exit the loop if the input is valid
                }
            }
            catch (const invalid_argument)
            {
                cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            }
        }

        cout << "----------------" << endl;
        if (choice == "5")
        {
            cout << "Thank You " << endl;
            return 0;
        }

        if (datastatus == false && choice > "1")
        {
            cout << "Can't do any operation before append" << endl;
        }
        else
        {
            if (choice == "1") // Append
            {
                while (true)
                {
                    cout << "Enter new String : ";
                    cin >> ws;           // consume leading whitespaces
                    getline(cin, input); // accept input with spaces

                    // Check if the input contains any empty spaces or digits
                    bool validInput = true;
                    for (int i = 0; i < input.size(); i++)
                    {
                        if (is_digit(input[i]))
                        {
                            validInput = false;
                            break;
                        }
                    }
                    if (validInput)
                    {
                        break; // Exit the loop if the input is valid
                    }
                    else
                    {
                        cout << "Invalid input. Please enter a name without empty spaces or digits." << endl;
                    }
                }

                text.push(input); //store in stack
                datastatus = true;

            }

            else if (choice == "2") // Delete
            {
                //variables
                int n , number ;

            start: // label

                cout << "1. if you want to delete the last element " << endl;
                cout << "2. if you want to delete a numbers of elements " << endl;
                cout << "3. if you want to delete the entire string" << endl;
                cout << "Enter your choice : ";
                cin >> n;

                if (n == 1)
                {
                    history.push(text.delete_last());
                }
                else if (n == 2)
                {
                    cout<<"String : ";
                    text.display_inverse();
                    cout<<"Enter number of elements you want delete : ";
                    cin>>number;

                    for(int i =0 ; i<number ; i++)
                    {
                        history.push(text.delete_last());
                    }

                }
                else if (n == 3)
                {
                   history.push(text.pop_string());
                }
                else
                {
                    cout << "Invalid choice. Please try again" << endl;
                    cout << "----------------" << endl;
                    goto start; // Back to this label (this label at first of this case)
                }
            }

            else if (choice == "3") // Print
            {
              //variables
              int n , index , specific_index;
              string title;

            loop: // label

                cout << "1. if you want to print a specific index " << endl;
                cout << "2. if you want to print the string " << endl;
                cout << "Enter your choice : ";
                cin >> n;

                if (n == 1)
                {
                    cout<<"Enter index to print : ";
                    cin>>index;
                    title = text.display_index(index);

                    cout<<"Enter index to print specific index in this string : ";
                    cin>>specific_index;
                    for(int i=0 ; i<title.size() ; i++)
                    {
                        if(i==specific_index)
                           cout<<"item in specific index is : "<<title[i]<<endl;
                    }
                }
                else if (n == 2)
                {
                    text.display_inverse();
                }
                else
                {
                    cout << "Invalid choice. Please try again" << endl;
                    cout << "----------------" << endl;
                    goto loop; // Back to this label (this label at first of this case)
                }
            }

            else if (choice == "4") // Undo
               {
                   //passing address of two stack
                   UNDO(&history,&text);
               }

            else if (choice == "5") // Exit
            {
                cout << "Thank You" << endl;
                return 0;
            }
        }
    } while (choice != "5");

    return 0;
}
