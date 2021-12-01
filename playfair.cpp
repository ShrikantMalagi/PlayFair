#include<bits/stdc++.h>
#include<algorithm>

using namespace std;

void removespaces(string &s)
{   
    int idx =0;
    for(int i = 0;i<s.length();i++)
    {
        if(s[i] != ' '){
            s[idx++] = s[i];
        }

    }
    s.erase(idx);
}
string encrypt_util(string s)
{   // function
    // divides into groups of two
    // if the two characters are the same then inserts 'x' between them 
    string res;
    int i =0,j=1;
    while(j<s.length()&& i<s.length())
    {   
        res.push_back(s[i]);
        if(s[i] == s[j])
        {
            res.push_back('x');
            i=j;
            j++;
            continue;
        }
        res.push_back(s[j]);
        i+=2;
        j+=2;
        
    }
    j = min(j,i);
    while(j<s.length()) res.push_back(s[j++]);
    if(res.length()%2) res.push_back('x');
    return res;
}

string encrypt(vector<vector<char>> key_matrix,unordered_map<char,vector<int>>map,string message){

    string res;

    removespaces(message);
    message = encrypt_util(message);

    for(int i =0;i<message.length();i+=2)
    {   
        vector<int> position_1 = map[message[i]],position_2 = map[message[i+1]];

        //if same row
        if(position_1[0] == position_2[0]){
            res.push_back(key_matrix[(position_1[0]+1)%5][position_1[1]]);
            res.push_back(key_matrix[(position_2[0]+1)%5][position_2[1]]);
        }
        //if same column
        else if(position_2[1] == position_1[1]){
            res.push_back(key_matrix[position_1[0]][(position_1[1]+1)%5]);
            res.push_back(key_matrix[position_2[0]][(position_2[1]+1)%5]);
        }
        //diff columns
        else{
            res.push_back(key_matrix[position_1[0]][position_2[1]]);
            res.push_back(key_matrix[position_2[0]][position_1[1]]);
        }
    }

    return res;
}

string decrypt (vector<vector<char>> key_matrix,unordered_map<char,vector<int>> map,string message)
{
    string res;

    for(int i =0;i<message.length();i+=2)
    {   
        vector<int> position_1 = map[message[i]],position_2 = map[message[i+1]];

        //if same row
        if(position_1[0] == position_2[0]){
            if(key_matrix[(position_1[0]+1)%5][position_1[1]]!='x')res.push_back(key_matrix[(position_1[0]+1)%5][position_1[1]]);
            if(key_matrix[(position_2[0]+1)%5][position_2[1]]!='x')res.push_back(key_matrix[(position_2[0]+1)%5][position_2[1]]);
        }
        //if same column
        else if(position_2[1] == position_1[1]){
            if(key_matrix[position_1[0]][(position_1[1]+1)%5]!='x')res.push_back(key_matrix[position_1[0]][(position_1[1]+1)%5]);
            if(key_matrix[position_2[0]][(position_2[1]+1)%5]!='x')res.push_back(key_matrix[position_2[0]][(position_2[1]+1)%5]);
        }
        //diff columns
        else{
            if(key_matrix[position_1[0]][position_2[1]]!='x')res.push_back(key_matrix[position_1[0]][position_2[1]]);
            if(key_matrix[position_2[0]][position_1[1]]!='x')res.push_back(key_matrix[position_2[0]][position_1[1]]);
        }
    }

    return res;

}


int main(){


    cout<<"Enter the Key: "<<"\n";

    string key;
    cin>>key;
    removespaces(key);
    int alphas[26] ={0};
    vector<vector<char>> key_matrix(5,vector<char>(5));

    int idx =0;

    unordered_map<char,vector<int>> map; // for quick searching of the position

    int i,j;

    // inserting the key at the top of the matrix
    for(i =0;i<5 && idx<key.length() ;i++)
    {
        for(j=0;j<5 && idx < key.length();j++)
        {   
            key[idx] = tolower(key[idx]);
            if(key[idx] == 'i'||key[idx] == 'j'){
                key_matrix[i][j] = 'i';
                alphas['i'-'a']++;
                alphas['j'-'a']++;
                if(key[idx] == i) {
                    map['j'].push_back(i);
                    map['j'].push_back(j);
                }
                else{
                    map['i'].push_back(i);
                    map['i'].push_back(j);
                }
            }
            else{
                alphas[key[idx] - 'a']++;
                key_matrix[i][j] = tolower(key[idx]);
                
            }

            map[key[idx]].push_back(i);
            map[key[idx]].push_back(j);
            idx++;
            
        }
        if(idx>=key.length()) break;
    }
    
    idx =0;
    // filling the matrix
    for(i;i<5&& idx<26;i++)
        {
            for(j;j<5 && idx<26 ;j++)
            {   
                while(alphas[idx] !=0)idx++; // searching for the character that has not appeared yet

                    if(idx == 'i'-'a' || idx == 'j' - 'a')
                    {
                        key_matrix[i][j] = 'i';
                        alphas['i' - 'a']++;
                        alphas['j' - 'a']++;
                        if(key[idx] == i) {
                            map['j'].push_back(i);
                            map['j'].push_back(j);
                        }
                        else{
                            map['i'].push_back(i);
                            map['i'].push_back(j);
                        }
                    }
                    else{
                        alphas[idx]++;
                        key_matrix[i][j] = char('a'+idx);
                        
                    }
                    map[char(int('a')+idx)].push_back(i);
                    map[char(int('a')+idx)].push_back(j);
                    idx++;
            }   
            j=0;
        }
    // Printing the Key matrix
    cout<<"The Key Matrix is: "<<"\n";
    for(i =0;i<5;i++)
        {
            for(j =0;j<5;j++)
            {
                cout<<key_matrix[i][j]<<" ";
            }
            cout<<"\n";
        }
    cout<<"\n";

    string message;

    cout<<"Enter the message you want to send: \n";
    cin>> message;
    cout<<"\n";
    removespaces(message);
    
    
    string encrypted_msg = encrypt(key_matrix,map,message);
    string decrypted_msg = decrypt(key_matrix,map,encrypted_msg);
    cout<<"The encrpyted message is : "<<encrypted_msg<<" \n\n";
    cout<<"The decrypted message is : "<<decrypted_msg;
    return 0;
}

