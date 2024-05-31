#include<iostream>
#include<string>
using namespace std;
#include<fstream>
#include<sstream>
#include <bits/stdc++.h> 
#include"bidirectional_dijkstra.h"



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

class routes;
class student{
    public:
      string name;
      string password;
      int id;
      string email;
      string dest;
      double fee;
      int time;
      friend void choose_destination(int id);



};




namespace space
{
  int check(string p){   //can add more features
    if (p.size()>8){
        return 0;
    }
    return 1;
  }
}
using namespace space;


student students[10];


void create(){
    string info[4];
    ifstream file;
    file.open("login.csv");
    

    string line,word;
    getline(file, line);
    int y=1;
    while (getline(file, line)) {
        //cout << line << endl;
		stringstream str(line);
        int x=0;
        while(getline(str, word, ',')){
            info[x]=word;
            x++;
        }
        students[y].name=info[0];
        students[y].id=stoi(info[2]);
        students[y].password=info[1];
        students[y].email=info[3];
        y++;   
    }
	
}

string arr[10]={"MG ROAD","CHURCH STREET","ULSOOR","INDIRANAGAR","KORAMANGLA","HOSUR","DIARY CIRCLE","JAYADEVA","SILK BOARD","BG ROAD"};

 void choose_destination(int id){     
        int choice ;
        cout<<"\n\n\n\n\n------------CHOOSE DESTINATION------------\n\n";
        cout<<"||-------------1.MG ROAD-------------------------------||"<<endl;
        cout<<"||-------------2.CHURCH STREET-------------------------||"<<endl;
        cout<<"||-------------3.ULSOOR--------------------------------||"<<endl;
        cout<<"||-------------4.INDIRANAGAR---------------------------||"<<endl;
        cout<<"||-------------5.KORAMANGLA----------------------------||"<<endl;
        cout<<"||-------------6.HOSUR---------------------------------||"<<endl;
        cout<<"||-------------7.DIARY CIRCLE--------------------------||"<<endl;
        cout<<"||-------------8.JAYADEVA------------------------------||"<<endl;
        cout<<"||-------------9.SILK BOARD----------------------------||"<<endl;
        cout<<"||-------------10.BG ROAD------------------------------||"<<endl;

        cin>>choice;
        string arr[10]={"MG ROAD","CHURCH STREET","ULSOOR","INDIRANAGAR","KORAMANGLA","HOSUR","DIARY CIRCLE","JAYADEVA","SILK BOARD","BG ROAD"};

        string destination=arr[choice+1];
	int no_vertices=11;
	cout<<"Enter the destination and number of vertices"<<endl;
	cin>>destination>>no_vertices;
	Dijkstra obj(destination,no_vertices);
	obj.take_input();
	obj.print_graph();
	obj.dijkstra();
	obj.print_distance();

   //store all the nodes from dijkstras in an array;
   students[id].dest=destination;
    routes r(id);


}





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
        public:
        friend class routes;
};


template <typename T> T mycalc(T x, T y)
{
    return 50+((distance-10)*50)*100;
}
inline void time(int d,int speed=8){
   return d*speed;
}


class routes:public student{
    int amount= mycalc<int>(50,90); //get total distance from dijkstras algo ex 90 km
    int t =  time(d);
    
 routes(int id){
    
    students[id].fee=amount;
    students[id].time=t;
    Seat obj(students[id].dest);
    obj.file_open();
    obj.retrieve_seats();
   



 }
  friend void choose_destination(int id);
};











void checkpass(int id,string pass){
cout<<"in id checkbox"<<endl;
if (students[id].password==pass){
    cout<<"logged in successfuly"<<endl;
    choose_destination( id);


}
else{
    cout<<"incorrect password"<<endl;
}

}


void checkpass(string e,string pass){
    cout<<"in email checkbox"<<endl;
    int flag=0;
    for (int x=0;x<20;x++){
       if (students[x].email==e){
        if (students[x].password==pass){
                cout<<"logged in successfuly"<<endl;
                choose_destination(x);
                return;
        }
        else{
            cout<<"incorrect password"<<endl;
            return;
            }           

       }

        }
        cout<<"wrong username"<<endl;
    
}

void login(){
    string u;string p;
    //system("cls");
    cout<<"\n\t\t\tEnter user id or email id:   "<<endl;
    cin >>u;
    cout<<"\t\t\tEnter password:(strictly less than 10 characters)"<<endl;
    cin>>p;
    int res=check(p);
    if (res==1){
     if (u.find('@')!=string::npos){
        checkpass(u,p);
     }//trying to use function oveloading ,even if it is unnecessary
     else{checkpass(stoi(u),p);
     }
    }
    else{
        cout<<"wrong format of password"<<endl;
    }

}


void end(){}


int main(){
   /* int choice;
    cout<<"\t\t\t------------------------------------------------------------\n\n\n";
    cout<<"\t\t\t                 WELCOME TO LOGINPAGE                       \n\n\n";
    cout<<"\t\t\t-------------------------MENU--------------------------------\n\n";
    cout<<"-------------------------PRESS 1 TO LOGIN --------------------------\n";
    cout<<"-------------------------PRESS 2 TO EXIT----------------------------\n";
    cout<<"enter your choice: ";
    cin>>choice;*/

    create();
    login();
    /*switch(choice){
        case 1:
            login();
            break;
        case 2:
            end();
            break;
   


    }*/
}