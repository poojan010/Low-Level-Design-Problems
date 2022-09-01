#include <bits/stdc++.h>
#include <string>
#include <iostream>
using namespace std;

class Comment{
    private:
        string content;
        string id;
        string userId;
        string postId;
        bool isParent;
        string parentId;
    public:
        Comment();
        static int commentsCount;
        void setContent(string);
        void setUserId(string);
        void setPostId(string);
        void makeChild();
        void setParentId(string);
        string getId() const;
        string getContent() const;    
        string getUserId() const;
        string getParentId() const;
        string getPostId() const;
        bool getParentStatus() const;
};

int Comment::commentsCount = 0;

class Post{
    private:
        string content;
        string id;
        string userId;
        vector<Comment> comments;
    public:
        Post();
        static int postsCount;
        void setContent(string);
        void setUserId(string);
        string getId() const;
        string getContent() const;    
        string getUserId() const;
        void createComment(string);
        void editComment(string,string);
        void replyToComment(string,string);
        void printAllComments();
        void printCommentReplies(string);
};

int Post::postsCount = 0;

class User{
    private:
        string id;
        string name;
        vector<Post> posts;
    public:
        User();
        static int usersCount;
        void setName(string);
        void createPost(string);
        void editPost(string,string);
        void printPosts();
        void makeComment(string,string);
        void editComment(string,string,string);
        void replyToComment(string,string,string);
        void printPostComments(string);
        void printPostCommentReplies(string,string);
};

int User::usersCount = 0;



/** Comment Class methods */
Comment::Comment(){
    this->id = "c" + to_string(++commentsCount);
    this->content = "";
    this->userId = "";
    this->postId = "";
    this->isParent = true;
    this->parentId = "";
}
void Comment::setContent(string content){
    this->content = content;
};
void Comment::setUserId(string userId){
    this->userId = userId;
};
void Comment::setPostId(string postId){
    this->postId = postId;
};
void Comment::makeChild(){
    this->isParent = false;
};
void Comment::setParentId(string parentId){
    this->parentId = parentId;
};
string Comment::getId() const{
    return this->id;
};
string Comment::getContent() const{
    return this->content;
};    
string Comment::getUserId() const{
    return this->userId;
};
string Comment::getParentId() const{
    return this->parentId;
};
string Comment::getPostId() const{
    return this->postId;
};
bool Comment::getParentStatus() const{
    return this->isParent;
};



/** Post class methods */
Post::Post(){
    this->id = "p" + to_string(++postsCount);
    this->content = "";
    this->userId = "";
};
void Post::setContent(string content){
    this->content = content;
};
void Post::setUserId(string userId){
    this->userId = userId;
};
string Post::getId() const{
    return this->id;
};
string Post::getContent() const{
    return this->content;
};    
string Post::getUserId() const{
    return this->userId;
};
void Post::createComment(string content){
    Comment c;
    c.setContent(content);
    comments.push_back(c);
};
void Post::editComment(string commentId,string content){
    for(int i=0; i<comments.size(); ++i){
        if(comments[i].getId() == commentId)
            comments[i].setContent(content);
    }
};
void Post::replyToComment(string parentCommentId,string content){
    for(int i=0; i<comments.size(); ++i){
        if(comments[i].getId() == parentCommentId){
        
            Comment c;
            c.makeChild();
            c.setContent(content);
            
            // replying to parent comment
            if(comments[i].getParentStatus() == true){
                c.setParentId(parentCommentId);
            }
            // replying to child comment
            else{
                c.setParentId(comments[i].getParentId());
            }

            comments.push_back(c);
        }
    }
};
void Post::printAllComments(){
    for(int i=0; i<comments.size(); ++i){
        if(comments[i].getParentStatus() == true){
            cout << comments[i].getId();
            cout << " ";
            cout << comments[i].getContent();
            cout << endl;
        }
    }
};
void Post::printCommentReplies(string commentId){
    for(int i=0; i<comments.size(); ++i){
        if(comments[i].getParentId() == commentId){
            cout << comments[i].getId();
            cout << " ";
            cout << comments[i].getContent();
            cout << endl;
        }
    }
};


User::User(){
    this->id = "u" + to_string(++usersCount);
    this->name = "";
}
void User::setName(string name){
    this->name = name;
};
void User::createPost(string content){
    Post p;
    p.setContent(content);
    p.setUserId(id);
    posts.push_back(p);
};
void User::editPost(string postId,string content){
    for(int i=0; i<posts.size(); ++i){
        if(posts[i].getId() == postId){
            posts[i].setContent(content);
        }
    }
};
void User::printPosts(){
    for(int i=0; i<posts.size(); ++i){
        cout << posts[i].getId();
        cout << " ";
        cout << posts[i].getContent();
        cout << endl;
    }
};
void User::makeComment(string postId,string commentContent){
    for(int i=0; i<posts.size(); ++i){
        if(posts[i].getId() == postId){
            posts[i].createComment(commentContent);
        }
    }
};
void User::editComment(string postId,string commentId,string commentContent){
    for(int i=0; i<posts.size(); ++i){
        if(posts[i].getId() == postId){
            posts[i].editComment(commentId,commentContent);
        }
    }
};
void User::replyToComment(string postId,string commentId,string commentContent){
    for(int i=0; i<posts.size(); ++i){
        if(posts[i].getId() == postId){
            posts[i].replyToComment(commentId,commentContent);
        }
    }
};
void User::printPostComments(string postId){
    for(int i=0; i<posts.size(); ++i){
        if(posts[i].getId() == postId){
            posts[i].printAllComments();
        }
    }
};
void User::printPostCommentReplies(string postId,string commentId){
    for(int i=0; i<posts.size(); ++i){
        if(posts[i].getId() == postId){
            posts[i].printCommentReplies(commentId);
        }
    }
};


int main() {
    User u1;

    u1.setName("User 1");

    u1.createPost("This is Post 1");
    u1.createPost("This is Post 2");
    u1.createPost("This is Post 3");
    u1.createPost("This is Post 4");

    u1.makeComment("p1", "This is first comment on Post 1");
    u1.makeComment("p1", "This is second comment on Post 1");
    u1.makeComment("p1", "This is third comment on Post 1");

    cout << "Printing Posts" << endl;
    u1.printPosts();
    cout << endl;

    cout << "Printing comments" << endl;
    u1.printPostComments("p1");
    cout << endl;

    u1.editComment("p1", "c1", "This is first comment on Post 1 EDITED");
    u1.editComment("p1", "c2", "This is second comment on Post 1 EDITED");

    cout << "Printing comments" << endl;
    u1.printPostComments("p1");
    cout << endl;

    u1.replyToComment("p1", "c1", "This is first Reply of Post 1 Comment 1");
    u1.replyToComment("p1", "c1", "This is second Reply of Post 1 Comment 1");
    u1.replyToComment("p1", "c4", "This is third Reply of Post 1 Comment 1");

    cout << "Printing comments Replies" << endl;
    u1.printPostCommentReplies("p1","c1");
    cout << endl;

    u1.editComment("p1", "c6", "This is third Reply of Post 1 Comment 1 EDITED");

    cout << "Printing comments Replies" << endl;
    u1.printPostCommentReplies("p1","c1");
    cout << endl;
    
}