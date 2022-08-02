
class Meeting;
typedef unordered_map<int,vector<Meeting>> Calendar;


/** Room class */
class Room{
    string name;
    Calendar calendar;
    public:
        Room(string);    
        bool book(int,int,int);
        string getName() const;
};




/** Meeting class */
class Meeting{
    int start,end;
    Room room;
    public:
        Meeting(int,int,Room);
        int getStart() const;
        int getEnd() const;
};




/** Scheduler class  */
class Scheduler{
    vector<Room> rooms;
    public:
    Scheduler(vector<Room> rooms);
    string book(int,int,int);
};





/** Room class methods */
Room::Room(string name){
    this->name = name;
}

string Room::getName() const{
    return name;
}

bool Room::book(int day,int start, int end){
    
    for(Meeting m : calendar[day]){
        if(m.getStart() < end && start < m.getEnd())
            return false;
    }
    
    Meeting meeting(start,end,*this);
    
    calendar[day].push_back(meeting);
    
    return true;
}







/** Meeting class methods */

Meeting::Meeting(int start,int end,Room room) : room(room) {
    this->start = start;
    this->end = end;
}

int Meeting::getStart() const{
    return start;
}

int Meeting::getEnd() const{
    return end;
}







/** Scheduler class methods */

Scheduler::Scheduler(vector<Room> rooms){
    this->rooms = rooms;
}

string Scheduler::book(int day,int start,int end){
    
    for(Room &room : rooms){
        bool flag = room.book(day,start,end);
        if(flag) return room.getName();
    }
    
    return "No rooms available !";
}







int main() {
    
    Room room1("Atlas");
    Room room2("Nexus");
    Room room3("HolyCow");
    
    vector<Room> rooms;
    rooms.push_back(room1);
    rooms.push_back(room2);
    rooms.push_back(room3);
    
    Scheduler scheduler(rooms);
    
    cout << scheduler.book(10,2,5) << endl;
    cout << scheduler.book(10,5,8) << endl;
    cout << scheduler.book(10,4,8) << endl;
    cout << scheduler.book(10,3,6) << endl;
    cout << scheduler.book(10,7,8) << endl;
    cout << scheduler.book(11,6,9) << endl;
        
    return 0;        

}



