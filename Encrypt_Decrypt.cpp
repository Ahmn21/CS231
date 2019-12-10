#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;

class encrypt_decrypt
{
public:
    void file_read(string*,const int*);
    void encrypt(string*,char*,const int*);
    void decrypt(string*);
    void decrypt_write(string*, char*,const int*);
};

void encrypt_decrypt::decrypt_write(string* recieved_file_name, char* recieved_char_from_file,const int* recieved_key)
{
    char map[66]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',' ','\n','.',','};
    string file_name_decrypted=*recieved_file_name+"_decrypted.txt";
    ofstream file_write;
    int current_char_key;
    for(int i=0;i<66;i++)
    {
        if(*recieved_char_from_file==map[i])
        {
            current_char_key=i;
            break;
        }
    }
    if(current_char_key==0)
    {
        current_char_key=66-*recieved_key;
    }
    else if(current_char_key-*recieved_key<0)
    {
        current_char_key=current_char_key-*recieved_key+66;
    }
    else
    {
        current_char_key=current_char_key-*recieved_key;
    }
    file_write.open(file_name_decrypted, ios::out | ios::app);
    file_write<<map[current_char_key];
    file_write.close();
}

void encrypt_decrypt::decrypt(string* recieved_file_name)
{
    char map[66]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',' ','\n','.',','};
    ifstream file_read;
    file_read.open(*recieved_file_name+".txt");
    char first_char, char_from_file;
    file_read.get(first_char);
    file_read.close();
    int key_read_from_file, difference_in_key;
    for(int i=0;i<66;i++)
    {
        if(first_char==map[i])
        {
            key_read_from_file=i;
            break;
        }
    }
    if(key_read_from_file>29)
    {
        difference_in_key=key_read_from_file-29;
    }
    else if(key_read_from_file<29)
    {
        difference_in_key=key_read_from_file-29+65;
    }
    else if(key_read_from_file==29)
    {
        cout<<"\nFile not encrypted\n";
        return;
    }
    file_read.open(*recieved_file_name+".txt");
    while(file_read.get(char_from_file))
    {
        decrypt_write(recieved_file_name, &char_from_file, &difference_in_key);
    }
    file_read.close();
}

void encrypt_decrypt::encrypt(string* recieved_file_name, char* recieved_char,const int* recieved_key)
{
    char map[66]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',' ','\n','.',','};
    int char_key;
    for(int i=0;i<66;i++)
    {
        if(*recieved_char==map[i])
        {
            char_key=i+*recieved_key;
            if(char_key>65)
            {
                char_key=char_key - 66;
            }
            ofstream output_file;
            string cipher_file=*recieved_file_name+"_encrypted.txt";
            output_file.open(cipher_file, ios::out | ios::app);
            if(output_file.is_open() && output_file.good())
            {
                output_file<<map[char_key];
            }
            else
            {
                cout<<"\nError creating cipher file!!\n";
            }
            output_file.close();
            break;
        }
    }
}

void encrypt_decrypt::file_read(string* recieved_file_name,const int* recieved_key)
{
    char word_from_file;
    ifstream input_file;
    input_file.open(*recieved_file_name+".txt");
    if(input_file.good() && input_file.is_open())
    {
        while(input_file.get(word_from_file))
        {
            encrypt(recieved_file_name, &word_from_file, recieved_key);
        }
        input_file.close();
    }
    else
    {
        cout<<"\nError opening file\n\n";
    }
}

int main()
{
    encrypt_decrypt object;
    string file_name;
    int choice, key_choice, random_key;
    while(1)
    {
        cout<<"1. Encrypt file\n2. Decrypt file\n0. Exit\nINPUT: ";
        cin>>choice;
        if(choice==1)
        {
            cout<<"NOTE: '.txt' extension will be appended by the program!!\nEnter file name to be encrypted: ";
            cin.ignore();
            getline(cin,file_name);
            cout<<"Enter key: ";
            cin>>random_key;
            if (random_key>65)
            {
                random_key=random_key%66;
                object.file_read(&file_name, &random_key);
            }
            else if(random_key>0 && random_key<66)
            {
                object.file_read(&file_name, &random_key);
            }
            else
            {
                cout<<"\nInvalid key!!!\n";
            }
        }
        else if(choice==2)
        {
            cout<<"NOTE: '.txt' extension will be appended by the program!!\nEnter file name to be decrypted: ";
            cin.ignore();
            getline(cin,file_name);
            object.decrypt(&file_name);
        }
        else if(choice==0)
        {
            return 0;
        }
        else
        {
            cout<<"\nINVALID INPUT!!\n\n";
        }
    }
}
