#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class TextEditor{
    private:
        vector<string> content;
        string clipBoard;
        stack<vector<string>> undoStack, redoStack;
    public:
        TextEditor();
        void display(int n,int m);
        void display();
        void deleteContent(int n,int m);
        void deleteContent(int n);
        void insertContent(int n,string text);
        void copyContent(int n,int m);
        void pasteContent(int n);
        void undo();
        void redo();
};

TextEditor::TextEditor(){
    content.resize(5,"");
    content[0] = "Abcd Efgh", content[1] = "Ifjk Lmn", content[2] = "Opqr Stu";
    content[3] = "vw xyz", content[4] = "123 456";
    clipBoard = "";
}
void TextEditor::display(int n,int m){
    int size = content.size() - 1;
    for(int i=n; i<=min(size,m); ++i){
        cout << i << " : " << content[i] << endl;
    }
};
void TextEditor::display(){
    int size = content.size() - 1;
    for(int i=0; i<=size; ++i){
        cout << i << " : " << content[i] << endl;
    }
};
void TextEditor::deleteContent(int n,int m){

    vector<string> temp = content;
    
    int size = content.size() - 1;

    if(n > size){
        cout << "Can not delete Out of Bound" << endl;
        return;
    }
        
    int newN = min(n,size), newM = min(m,size);

    if(newN == newM){
        content.erase(next(content.begin(),newN));
    }
    else{
        content.erase( next(content.begin(),newN), next(content.begin(),newM+1) );
    }
    
    undoStack.push(temp);
};
void TextEditor::deleteContent(int n){
    
    vector<string> temp = content;
    
    int size = content.size() - 1;

    if(n > size){
        cout << "Can not delete. Out of Bound" << endl;
        return;
    }
        
    int newN = min(n,size);
    content.erase(next(content.begin(),newN));
    
    undoStack.push(temp);
};
void TextEditor::insertContent(int n,string text){

    vector<string> temp = content;
    
    int size = content.size() - 1;

    if(n > size){
        content.push_back(text);
    }
    else{
        content[n] += " " + text;
    }
    
    undoStack.push(temp);
};
void TextEditor::copyContent(int n,int m){

    int size = content.size() - 1;

    if(n > size){
        cout << "Can not delete Out of Bound" << endl;
        return;
    }
    
    int newN = min(n,size), newM = min(m,size);

    string str = "";
    for(int i=newN; i <= newM; ++i){
        str += content[i];
    }

    clipBoard = str;
    
};
void TextEditor::pasteContent(int n){
    insertContent(n,clipBoard);
};
void TextEditor::undo(){
    
    if(undoStack.empty()){
        cout << " Can not perform this operation " << endl;
        return;
    }
    
    vector<string> temp = undoStack.top();
    undoStack.pop();

    redoStack.push(content);

    content = temp;

    cout << "Undo Performed" << endl;
    
};
void TextEditor::redo(){
    
    if(redoStack.empty()){
        cout << " Can not perform this operation " << endl;
        return;
    }

    vector<string> temp = redoStack.top();
    redoStack.pop();

    undoStack.push(content);
    
    content = temp;

    cout << "Redo Performed" << endl;
};


int main() {
    TextEditor textEditor;

    textEditor.display();


    cout << endl << "---------------------1----------------------" << endl;
    cout << "Action : Displaying First 2 lines " << endl;
    textEditor.display(0,1);

    cout << endl << "---------------------2----------------------" << endl;
    cout << "Action : Inserting yeah to the First line " << endl;
    textEditor.insertContent(0,"yeah");
    textEditor.display();

    cout << endl << "---------------------3----------------------" << endl;
    cout << "Action : Undoing last move " << endl;
    textEditor.undo();
    textEditor.display();

    cout << endl << "---------------------4----------------------" << endl;
    cout << "Action : Redoing last move " << endl;
    textEditor.redo();
    textEditor.display();

    cout << endl << "---------------------5----------------------" << endl;
    cout << "Action : Deleting First line " << endl;
    textEditor.deleteContent(0);
    textEditor.display();

    cout << endl << "---------------------6----------------------" << endl;
    cout << "Action : Undoing last move " << endl;
    textEditor.undo();
    textEditor.display();

    cout << endl << "---------------------7----------------------" << endl;
    cout << "Action : Undoing last move " << endl;
    textEditor.undo();
    textEditor.display();
    
    cout << endl << "---------------------8----------------------" << endl;
    cout << "Action : Deleting First 2 lines " << endl;
    textEditor.deleteContent(0,1);
    textEditor.display();
    
    cout << endl << "---------------------9----------------------" << endl;
    cout << "Action : Undoing last move " << endl;
    textEditor.undo();
    textEditor.display();

    
    cout << endl << "---------------------10----------------------" << endl;
    cout << "Action : Copying lines 1 to 2 and pasting them on 3rd line" << endl;
    textEditor.copyContent(0,1);
    textEditor.pasteContent(2); 
    textEditor.display();

    cout << endl << "---------------------11----------------------" << endl;
    cout << "Action : Undoing last move " << endl;
    textEditor.undo();
    textEditor.display();

    cout << endl << "---------------------12----------------------" << endl;
    cout << "Action : Redoing last move " << endl;
    textEditor.redo();
    textEditor.display();
}