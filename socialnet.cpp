#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<time.h>
#include<cctype>
#include<algorithm>
#include<queue>
#include<sstream>

using namespace std;



class TreeNode{
    public:
    TreeNode* left;
    TreeNode* right;
    int height;
    string post_content;
    time_t time_of_creation;
    int post_number;

    TreeNode(string post, int num, time_t timeofcreation){
        post_content = post;
        time_of_creation = timeofcreation;
        post_number = num;
    }
    
};

bool greaterThan(TreeNode* a, TreeNode* b){
    if(a -> time_of_creation != b -> time_of_creation){
        return a -> time_of_creation > b -> time_of_creation;
    }

    else{
        return a -> post_number > b -> post_number;
    }
}


int ht(TreeNode* node){
    if(node == NULL){
        return -1;
    }
    else{
        return node -> height;
    }
}

int balance(TreeNode* node){
    return ht(node -> left) - ht(node -> right);
}

TreeNode* leftRotate(TreeNode* node){
    TreeNode* A = node -> right;
    
    node -> right = A -> left;
    A -> left = node;
    
    node -> height = 1 + max(ht(node -> left), ht(node -> right));
    A -> height = 1 + max(ht(A -> left), ht(A -> right));
    
    return A;
}

TreeNode* rightRotate(TreeNode* node){
    TreeNode* A = node -> left;
    
    node -> left = A -> right;
    A -> right = node;
    
    node -> height = 1 + max(ht(node -> left), ht(node -> right));
    A -> height = 1 + max(ht(A -> left), ht(A -> right));
    
    return A;
}

TreeNode* insertToAVLhelper(TreeNode* root, string post_creation, int post_number, time_t time_of_creation) {

    if(root == NULL){
        TreeNode* temp = new TreeNode(post_creation, post_number, time_of_creation);
        temp -> height = 0;
        return temp;
    }
    
    if(time_of_creation > root -> time_of_creation or (time_of_creation == root -> time_of_creation and post_number > root -> post_number)){
        root -> right = insertToAVLhelper(root -> right, post_creation, post_number, time_of_creation);
    }
    
    if(time_of_creation < root -> time_of_creation or (time_of_creation == root -> time_of_creation and post_number < root -> post_number)){
        root -> left = insertToAVLhelper(root -> left, post_creation, post_number, time_of_creation);
    }
    
    root -> height = 1 + max(ht(root -> left), ht(root -> right));
        
    if(abs(balance(root)) <= 1){
        return root;
    }
    //right right
    if(balance(root) < -1 and (time_of_creation > root -> right -> time_of_creation or (time_of_creation == root -> right -> time_of_creation and post_number > root -> right -> post_number))){
        return leftRotate(root);
    }
    //right left
    if(balance(root) < -1 and (time_of_creation < root -> right -> time_of_creation or (time_of_creation == root -> right -> time_of_creation and post_number < root -> right -> post_number))){
        root -> right = rightRotate(root -> right);
        return leftRotate(root);
    }
    //left left
    if(balance(root) > 1 and (time_of_creation < root -> left -> time_of_creation or (time_of_creation == root -> left -> time_of_creation and post_number < root -> left -> post_number))){
        return rightRotate(root);
    }
    //left right
    if(balance(root) > 1 and (time_of_creation > root -> left -> time_of_creation or (time_of_creation == root -> left -> time_of_creation and post_number > root -> left -> post_number))){
        root -> left = leftRotate(root -> left);
        return rightRotate(root);
    }
}

vector<string> inorder(TreeNode* root){
    //returns inorder vector
    if(root == NULL){
        return {};
    }

    vector<string> l = inorder(root -> left);
    vector<string> r = inorder(root -> right);

    vector<string> ans;

    ans = l;

    ans.push_back(root -> post_content);
    
    ans.insert(ans.end(), r.begin(), r.end());

    return ans;
}

class AVLTree{
    public:
    TreeNode* rootAVL;
    int post_number_total;

    AVLTree(){
        rootAVL = NULL;
        post_number_total = 0;
    }

    void InsertToAVL(string post_creation){
        post_number_total++;
        time_t currtime;
        time(&currtime);
        rootAVL = insertToAVLhelper(rootAVL, post_creation, post_number_total, currtime);
    }


    void Output(int n){
        vector<string> h = inorder(rootAVL);

        if(n < -1){
            cout << "Please enter -1 or a number greater than 0." << endl;
            return;
        }

        if(h.size() == 0){
            cout << "User has no posts." << endl;
            return;
        }
        
        reverse(h.begin(), h.end());
        if(n == -1 or n>h.size()){
            for(int i = 0; i<h.size(); i++){
                cout << i+1 << ". " << h[i] << endl;
            }
            return;
        }

        if(n == 0){
            cout << "Please enter a number greater than 0." << endl;
            return;
        }


        // for(int i = h.size()-1; i>=(h.size()-n); i--){
        //     cout << h.size()-i << ". " << h[i] << endl;
        // }

        for(int i = 0; i<n; i++){
            cout << i+1 << ". " << h[i] << endl;
        }
        return;
    }

};

bool compare(pair<string,int> a, pair<string,int> b){
    if(a.second!=b.second){
        return a.second > b.second;
    }

    else{
        return a < b;
    }
}

class NetworkGraph{
    public:
    unordered_map<string, vector<string>> FriendConnections;
    unordered_map<string, AVLTree> UserPosts;

    NetworkGraph(){
        
    }
    void AddUser(string username){
        transform(username.begin(), username.end(), username.begin(), ::tolower);
        if(FriendConnections.count(username) == 0){
            FriendConnections[username] = {};
            AVLTree h;
            UserPosts[username] = h;
            cout << "Successfully added " << username << " to the network." << endl;
            return; 
        }
        else{
            cout << "User already present." << endl;
            return;
        }
        
    }

    void AddFriend(string username1, string username2){
        transform(username1.begin(), username1.end(), username1.begin(), ::tolower);
        transform(username2.begin(), username2.end(), username2.begin(), ::tolower);

        if(FriendConnections.count(username1) == 0){
            cout << username1 << " doesn't exist." << endl;
            return;
        }

        if(FriendConnections.count(username2) == 0){
            cout << username2 << " doesn't exist." << endl;
            return;
        }

        if(username1 == username2){
            cout << "Please input 2 different users." << endl;
            return;
        }


        for(int i = 0; i<FriendConnections[username1].size(); i++){
            if(FriendConnections[username1][i] == username2){
                cout << "Already friends." << endl;
                return;
            }
        }
        FriendConnections[username1].push_back(username2);
        FriendConnections[username2].push_back(username1);

        cout << "Added "  << username1 << " and " << username2 << " as friends." << endl;
    }

    void ListFriends(string username){
        transform(username.begin(), username.end(), username.begin(), ::tolower);
        if(FriendConnections.count(username) == 0){
            cout << "User doesn't exist." << endl;
            return;
        }
        vector<string> h = FriendConnections[username];
        sort(h.begin(), h.end());

        if(h.size() == 0){
            cout << "User has no friends." << endl;
            return;
        }
        cout << "Listing friends of " << username << endl;
        for(int i =0; i<h.size(); i++){
            cout << i+1 << ". " << h[i] << endl;
        }
    }


    void SuggestFriends(string username, int n){
        transform(username.begin(), username.end(), username.begin(), ::tolower);
        if(FriendConnections.count(username) == 0){
            cout << "User doesn't exist." << endl;
            return;
        }

        if(n<=0){
            cout << "Please enter a number greater than 0." << endl;
            return;
        }

        queue<string> q1;
        unordered_map<string, bool> explored;
        explored[username] = true;

        if(FriendConnections[username].size() == 0){
            cout << "User has no friends. " << endl;
            return;
        }

        for(int i = 0; i<FriendConnections[username].size(); i++){
            q1.push(FriendConnections[username][i]);
            explored[FriendConnections[username][i]] = true;
        }

        unordered_map<string, int> mutualfreq;

        while(!q1.empty()){
            string h = q1.front();
            q1.pop();

            for(int i = 0; i<FriendConnections[h].size(); i++){
                if(explored[FriendConnections[h][i]] == true){

                }
                else{
                    if(mutualfreq.count(FriendConnections[h][i]) == 0){
                        mutualfreq[FriendConnections[h][i]] = 0;
                    }
                    mutualfreq[FriendConnections[h][i]]++;
                }
            }
        }

        vector<pair<string,int>> ans;
        
        if(mutualfreq.size() == 0){
            cout << "User has no possible suggestions. " << endl;
            return;
        }
        for(auto x : mutualfreq){
            ans.push_back({x.first, x.second});
        }

        sort(ans.begin(), ans.end(), compare);

        int k = ans.size();

        for(int i = 0; i<min(n, k); i++){
            cout << i+1 << ". " << ans[i].first << endl;
        }
    }

    void DegreesOfSeparation(string username1, string username2){
        transform(username1.begin(), username1.end(), username1.begin(), ::tolower);
        transform(username2.begin(), username2.end(), username2.begin(), ::tolower);

        if(FriendConnections.count(username1) == 0){
            cout << username1 << " doesn't exist." << endl;
            return;
        }

        if(FriendConnections.count(username2) == 0){
            cout << username2 << " doesn't exist." << endl;
            return;
        }

        if(username1 == username2){
            cout << "Degree of separation is 0." << endl;
            return;
        }

        queue<pair<string,int>> q;

        unordered_map<string,bool>explored;

        q.push({username1,0});
        explored[username1] = true;

        int distans = -1;

        while(!q.empty()){
            string h = q.front().first;
            int dist = q.front().second;
            q.pop();

            if(h == username2){
                distans = dist;
                break;
            }

            for(int i = 0; i<FriendConnections[h].size(); i++){
                if(explored[FriendConnections[h][i]] == true){

                }
                else{
                    q.push({FriendConnections[h][i], dist+1});
                    explored[FriendConnections[h][i]] = true;
                }
            }

        }

        cout << "Degrees of separation are " << distans << "." << endl;
        return;
    }

    void AddPost(string username, string post_content){
        transform(username.begin(), username.end(), username.begin(), ::tolower);
        transform(post_content.begin(), post_content.end(), post_content.begin(), ::tolower);

        if(FriendConnections.count(username) == 0){
            cout << "User doesn't exist." << endl;
            return;
        }

        UserPosts[username].InsertToAVL(post_content);
        cout << "Added post successfully."  << endl;
        return;        
    }

    void OutputPosts(string username, int n){
        transform(username.begin(), username.end(), username.begin(), ::tolower);
        if(FriendConnections.count(username) == 0){
            cout << "User doesn't exist." << endl;
            return;
        }

        UserPosts[username].Output(n);
        return;
    }
};


int main(){

    NetworkGraph SocialNet;

    string sen;

    while(getline(cin, sen)){
        
        stringstream ss(sen);

        string command;
        ss >> command;

        //normal file functions

        if(command == "ADD_USER"){
            string username;
            ss >> username;
            if(username == ""){
                cout << "Error: No username given." << endl;
            }
            else{
                SocialNet.AddUser(username);
            }  
        }

        else if(command == "ADD_FRIEND"){
            string username1;
            ss >> username1;
            string username2;
            ss >> username2;

            if(username1 == "" or username2 == ""){
                cout << "Error: Empty usernames given." << endl;
            }
            else{
                SocialNet.AddFriend(username1, username2);
            }  
        }

        else if(command == "LIST_FRIENDS"){
            string username;
            ss >> username;
            if(username == ""){
                cout << "Error: No username given." << endl;
            }
            else{
                SocialNet.ListFriends(username);
            }  
        }

        else if(command == "SUGGEST_FRIENDS"){
            string username;
            ss >> username;
            if(username == ""){
                cout << "Error: No username given." << endl;
                continue;
            }

            string n;
            ss >> n;

            if(n.empty()){
                cout << "Please enter valid number." << endl;
                continue;
            }
            else{
                bool chec = true;
                for(int i = 0; i<n.size(); i++){
                    if(!::isdigit(n[i])){
                        cout << "Please enter valid number." << endl;
                        chec = false;
                        break;
                    }
                }
                if(chec == false){
                    continue;
                }
            }

            int f = stoi(n);

            SocialNet.SuggestFriends(username, f);
        }
        
        else if(command == "DEGREES_OF_SEPARATION"){
            string username1;
            ss >> username1;
            string username2;
            ss >> username2;

            if(username1 == "" or username2 == ""){
                cout << "Error: Empty usernames given." << endl;
            }
            else{
                SocialNet.DegreesOfSeparation(username1, username2);
            } 
        }

        else if(command == "ADD_POST"){
            string username;
            ss >> username;

            if(username == ""){
                cout << "Error: No username given." << endl;
                continue;
            }

            string post_content;
            getline(ss, post_content);

            if(post_content == ""){
                cout << "Please enter non empty post content. " << endl;
                continue;
            }

            else{
                SocialNet.AddPost(username, post_content);
            }

        }

        else if(command == "OUTPUT_POSTS"){
            string username;
            ss >> username;

            if(username == ""){
                cout << "Error: No username given." << endl;
                continue;
            }

            string n;
            ss >> n;

            if(n.empty()){
                cout << "Please enter valid number." << endl;
                continue;
            }
            if(n == "-1"){
                SocialNet.OutputPosts(username, -1);
                continue;
            }
            else{
                bool chec = true;
                for(int i = 0; i<n.size(); i++){
                    if(!::isdigit(n[i])){
                        cout << "Please enter valid number." << endl;
                        chec = false;
                        break;
                    }
                }
                if(chec == false){
                    continue;
                }
            }


            int f = stoi(n);

            SocialNet.OutputPosts(username, f);
        }

        else{   
            cout << "Command is invalid." << endl;
            continue;
        }

    }
}

