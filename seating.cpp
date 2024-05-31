#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Files
{
    public:
    //virtual function for opening csv files
    virtual void file_open()
    {
        cout<<"opening file"<<endl;
    }

    //virtual function for writing into csv files
    virtual void file_write()
    {
        cout<<"writeback to file"<<endl;
    }
};

class Seat:public Files
{
    string dest; //the destination of the uset
    vector<vector<string>> data; //2d vector of data inside of csv file 
    public:
        //parameterised constructor which initialises the destination
        Seat(string d):dest(d){};

        //function that opens files
        void file_open()
        {
            ifstream file("buses.csv"); //creating a file object for reading (file handler)
            if(!file) //checks if file opening was successful
            {
                cout<<"error"<<endl;
            }

            string line; //string that stores every line of csv file read
            while(getline(file,line)) //accessing every line of csv file until the end of file
            {
                vector<string>row; //creating a vector to store a row of csv file
                stringstream ss(line); //retrieve a series of value from the line read
                string each;

                while(getline(ss,each,',')) //retrieving each value within the row
                {
                    row.push_back(each); //pushing the value of each cell into the row vector
                }
                data.push_back(row); //row vector pushed into data vector
            }
            file.close();//file handler closed
        }

        //function that writes into the file
        void file_write() 
        {
            ofstream file("buses.csv",ofstream::out);
            for(auto& row:data) //accessing row in the 2d data vector
            {
                for(auto& each:row)
                {
                    file<<each<<','; //writing into the file value by value with ',' as delimiter
                }
                file<<'\n'; //moving to next line while storing
            }
            file.close();
        }

        void retrieve_seats()
        {
            int check;
            for(auto& row:data) //accessing row by row
            {
                if(row[0]==dest) //if the dest requested is same as row header
                {
                    int c=stoi(row[1]); //the capacity of bus retrieved
                    int o=stoi(row[2]); //the number of seats occupied
                    if(c==o) //if they are equal, the capacity would exceed
                    {
                        cout<<"AT FULL CAPACITY!"<<endl;
                        cout<<"Please choose another destination."<<endl;
                        break;
                    }
                    else //when the capacity is not exceeded
                    {
                        string o=to_string(stoi(row[2])+1); //converting the occupied into int, incrementing it and then converting back to string
                        row[2]=o; //rewriting the data, to new number of occupied
                        cout<<"changed:"<<row[2]<<endl;
                    }

                } 
            }
            file_write(); //calling of write function
        }
};

int main()
{
    string s;
    cout<<"enter destination:";
    cin>>s;
    Seat obj(s);
    obj.file_open();
    obj.retrieve_seats();
}