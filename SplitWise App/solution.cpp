#include <bits/stdc++.h>
#include <string>
#include <iostream>
using namespace std;

vector<string> splitString(string str){
    vector<string> ans;
    
    string word = "";
    for (auto x : str){
        if (x == ' '){
            ans.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }

    if(word.length() > 0)
        ans.push_back(word);
    
    return ans;
}




class User{
    private:
        string userId, name;
        string email,mobileNo;
    public:
        User();
        static int usersCount;
        string getUserId() const;        
        string getName() const;
        string getEmail() const;
        string getMobileNo() const;
        void setName(string); 
        void setEmail(string); 
        void setMobileNo(string); 
};

int User::usersCount = 0;

User::User(){
    ++usersCount;
    this->userId = "u" + to_string(usersCount);
}

string User::getUserId() const {
    return userId;
}
string User::getName() const {
    return name;
}
string User::getEmail() const {
    return email;
}
string User::getMobileNo() const {
    return mobileNo;
}
void User::setName(string name){
    this->name = name;
}
void User::setEmail(string email){
    this->email = email;
}
void User::setMobileNo(string mobileNo){
    this->mobileNo = mobileNo;
}





class System{
    private:
        vector<User> users;
        unordered_map<string,unordered_map<string,int>> owns;
        string findUserName(string id);
        void updateBalances(string spentUser,string ownUser, double expense); 

    public:
        void registerUser(User& u); 
        void splitEqual(double expense, string spentUserId, vector<string> users);
        void splitExact(vector<double> expenses, vector<string> users, string spentUserId);
        void splitPercent(vector<double> percentages, vector<string> users, double expense, string spentUserId);
        bool showUserOwnRecords(string userId);
        void runSystem(); 

};

void System::registerUser(User& u){
    string uid = u.getUserId();
    owns[uid] = {};
    users.push_back(u);
}

void System::updateBalances(string spentUser,string ownUser, double expense){
    if(owns[spentUser].count(ownUser)){
        if(owns[spentUser][ownUser] >= expense){
             owns[spentUser][ownUser] -= expense;
        }
        else{
            int spendUserOwns = owns[spentUser][ownUser];
            int currentUserOwns = expense - spendUserOwns;
            owns[spentUser][ownUser] = 0.0;
            owns[ownUser][spentUser] += currentUserOwns;
        }
    }
    else{
        owns[ownUser][spentUser] += expense;
    }
}; 

string System::findUserName(string id){
    string name;
    for(User u : users){
        if(u.getUserId() == id){
            return u.getName();
        }
    }
    
    return name;
}

void System::splitEqual(double expense, string spentUserId,vector<string> users){
    double usersCnt = users.size();
    double equalExpense = expense/usersCnt;
    
    for(string id : users){      
        if(id == spentUserId) continue;
        updateBalances(spentUserId,id,equalExpense);
    }
}

void System::splitExact(vector<double> expenses, vector<string> users, string spentUserId){
    int n = users.size();

    for(int i=0; i<n; ++i){
        if(users[i] == spentUserId) continue;
        updateBalances(spentUserId,users[i],expenses[i]);
    }
};

void System::splitPercent(vector<double> percentages,vector<string> users, double expense, string spentUserId){
        int n = percentages.size();

    for(int i=0; i<n; ++i){
        if(users[i] == spentUserId) continue;
        updateBalances(spentUserId,users[i],percentages[i]*expense/100.00);
    }
};

bool System::showUserOwnRecords(string userId){
    bool isBalanceAvailable = false;
    string userName1 = findUserName(userId);

    for(auto it : owns[userId]){ 
        if(it.second > 0){
            
            if(!isBalanceAvailable)
                isBalanceAvailable = true;
            
            string userName2 = findUserName(it.first);
            cout << userName1 << " owes " << userName2 << " : " << it.second << endl; 
        }
    }
    
    return isBalanceAvailable;
}

void System::runSystem(){

    while(true){
        string input;
        getline(cin,input);

        vector<string> words = splitString(input);

        string action = words[0];
        
        if(action == "END"){
            break;
        }
        else if(action == "SHOW"){
            bool shouldPrintNoBalance = true;
            
            if(words.size() > 1){
                string userId = words[1];
                bool flag = showUserOwnRecords(userId);

                if(flag) shouldPrintNoBalance = false;
            }
            else{
                for(User u : users){
                    bool flag = showUserOwnRecords(u.getUserId());
                    if(flag) shouldPrintNoBalance = false;
                }
            }

            if(shouldPrintNoBalance){
                cout << "No Balance" << endl;
            }
        }
        else if(action == "EXPENSE"){
 
            string spentUserId = words[1];

            double totalExpense = stod(words[2]);

            int count = stoi(words[3]);

            int i = 4;
            /** Stoting user IDs */
            vector<string> users(count);
            for(int x=0; x< count; ++x){
                users[x] = words[i++];
            }

            string splitType = words[i++];

            if(splitType == "EQUAL"){
                splitEqual(totalExpense,spentUserId,users);
            }
            else if(splitType == "EXACT"){

                vector<double> expenses(count);
                double temp_totalExpense = 0;
                for(int x=0; x< count; ++x){
                    expenses[x] = stod(words[i++]);
                    temp_totalExpense += expenses[x];
                }
                if(temp_totalExpense != totalExpense){
                    cout << " Exact Expenses not add upto total Expense" << endl;
                }
                else{
                    splitExact(expenses,users,spentUserId);
                }
            }
            else if(splitType == "PERCENT"){
                vector<double> percentages(count);
                double totalPercentage = 0;
                for(int x=0; x< count; ++x){
                    percentages[x] = stod(words[i++]);
                    totalPercentage += percentages[x];
                }
                if(totalPercentage != 100){
                    cout << " Percentages does not add upto 100" << endl;
                }
                else{
                    splitPercent(percentages,users,totalExpense,spentUserId);
                }
            }
            
        }
        
    }
    
}

int main() {

    User u1,u2,u3,u4;
    u1.setName("User1");
    u2.setName("User2");
    u3.setName("User3");
    u4.setName("User4");

    System s;
    s.registerUser(u1);
    s.registerUser(u2);
    s.registerUser(u3);
    s.registerUser(u4);

    s.runSystem();

}