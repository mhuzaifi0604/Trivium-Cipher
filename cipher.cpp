#include<iostream>
#include<string.h>
#include<string>
#include<bitset>
//#include<bits/stdc++.h>
#include<Bits.h>
#include<cstdlib>
#include<fstream>

using namespace std;


string binary_converter(string str, int l, string name) {

    // initializing a temporary array/ string
    string binary = "";
    cout << name;

    // running loop till the length of key
    for (int i = 0; i < l; i++) {
        string temp = "";
        int bit = int(str[i]); // taking bit from the current char of string
        // loop traverses until string finishes
        while (bit > 0) {
            //binary.push_back('0'); 
            if (bit % 2 == 1)
                temp.push_back('1');// checking for resultant bit to be 1
            else
                temp.push_back('0');// checking for resultant bit to be 0
            bit /= 2;// condition for ending while loop
        }
        temp.push_back('0');
        // reversing the binary of the string
        reverse(temp.begin(), temp.end());// reversing the binary to get correct order
        if (i == l)
            temp.pop_back();// poping back the last extra bit
        binary += temp;
    }
    cout << binary;// printing the bits
    cout << "\n\n Size of converted binary: " << binary.length() << endl << endl;
    return binary;
}

char* LFSR1_Loader(char* LFSR1, string key) {
    // Initializing LFSR1 with 0s
    for (int i = 0; i < 93; i++) {
        LFSR1[i] = '0';
    }

    // Loading 1st 80 bits of LFSR1 with binary converted encryption key
    for (int i = 0; i < 80; i++) {
        LFSR1[i] = key[i];
    }
    return LFSR1;
}

char* LFSR2_Loader(char* LFSR2, string key2) {
    // Initializing LFSR1 with 0s
    for (int i = 0; i < 84; i++) {
        LFSR2[i] = '0';
    }
    // Loading bits of initial vector in 1st 80 bits of LFSR 2
    for (int i = 0; i < 80; i++) {
        LFSR2[i] = key2[i];
    }
    return LFSR2;
}

char* LFSR3_Loader(char* LFSR3) {
    // Initializing LFSR1 with 0s
    for (int i = 0; i < 108; i++) {
        LFSR3[i] = '0';
    }
    // Loaing 01 in last 3 bits of LFSR3
    LFSR3[108] = LFSR3[109] = LFSR3[110] = '1';

    return LFSR3;
}

char* LFSR1_printer(char* LFSR1) {
    for (int i = 0; i < 93; i++) {
        cout << LFSR1[i];
    }
    return LFSR1;
}

char* LFSR2_printer(char* LFSR2) {
    for (int i = 0; i < 84; i++) {
        cout << LFSR2[i];
    }
    return LFSR2;
}

char* LFSR3_printer(char* LFSR3) {
    for (int i = 0; i < 111; i++) {
        cout << LFSR3[i];
    }
    return LFSR3;
}

string binary_converter(string input) {
    string bin = "";
    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        string sub = "";
        for (int j = 0; j < 8; j++) {
            sub += to_string(((ch << j) & 0b10000000) >> 7);
        }
        bin += sub;
    }
    return bin;
}

void randomizer(char* LFSR1, char* LFSR2, char* LFSR3) {
    int count = 0;
    for (int i = 0; i < 1152; i++) {
        int L1O1 = (LFSR1[65] - 48), L1O2 = ((LFSR1[90] - 48) & (LFSR1[91] - 48)), L1O3 = (LFSR1[92] - 48), L1I1 = LFSR1[68];
        int XOR1 = L1O1 ^ L1O2 ^ L1O3;
        int L2O1 = LFSR2[68] - 48, L2O2 = (LFSR2[81] - 48) & (LFSR2[82] - 48), L2O3 = LFSR2[83] - 48, L2I1 = LFSR2[77];
        int XOR2 = L2O1 ^ L2O2 ^ L2O3;
        int L3O1 = LFSR3[65] - 48, L3O2 = (LFSR3[108] - 48) & (LFSR3[109] - 48), L3O3 = LFSR3[110] - 48, L3I1 = LFSR3[86];
        int XOR3 = L3O1 ^ L3O2 ^ L3O3;
        char input1 = (L1I1 ^ XOR3), input2 = (L2I1 ^ XOR1), input3 = (L3I1 ^ XOR2);
        for (int i = 92; i > 0; i--) {
            LFSR1[i] = LFSR1[i - 1];
        }
        LFSR1[0] =  input1;
        for (int i = 83; i > 0; i--) {
            LFSR2[i] = LFSR2[i - 1];
        }
        LFSR2[0] =  input2;
        for (int i = 110; i > 0; i--) {
            LFSR3[i] = LFSR3[i - 1];
        }
        LFSR3[0] =  input3;
        count += 1;
    }
    cout << "Randomizing LFSRs " << count << " times" << endl;

}

int* generator(char* LFSR1, char* LFSR2, char* LFSR3, int length) {
    int* output = new int[length * 8];
    int count = 0;
    for (int i = 0; i < (length * 8); i++) {
        int L1O1 = (LFSR1[65] - 48), L1O2 = ((LFSR1[90] - 48) & (LFSR1[91] - 48)), L1O3 = (LFSR1[92] - 48), L1I1 = LFSR1[68];
        int XOR1 = L1O1 ^ L1O2 ^ L1O3;
        int L2O1 = LFSR2[68] - 48, L2O2 = (LFSR2[81] - 48) & (LFSR2[82] - 48), L2O3 = LFSR2[83] - 48, L2I1 = LFSR2[77];
        int XOR2 = L2O1 ^ L2O2 ^ L2O3;
        int L3O1 = LFSR3[65] - 48, L3O2 = (LFSR3[108] - 48) & (LFSR3[109] - 48), L3O3 = LFSR3[110] - 48, L3I1 = LFSR3[86];
        int XOR3 = L3O1 ^ L3O2 ^ L3O3;
        output[i] = XOR1 ^ XOR2 ^ XOR3;
        char input1 = (L1I1 ^ XOR3), input2 = (L2I1 ^ XOR1), input3 = (L3I1 ^ XOR2);
        for (int i = 92; i > 0; i--) {
            LFSR1[i] = LFSR1[i - 1];
        }
        LFSR1[0] = input1 ;
        for (int i = 83; i > 0; i--) {
            LFSR2[i] = LFSR2[i - 1];
        }
        LFSR2[0] = input2 ;
        for (int i = 110; i > 0; i--) {
            LFSR3[i] = LFSR3[i - 1];
        }
        LFSR3[0] = input3;
        count += 1;
    }
    return output;

}

int* int_converter(int* encrypted, string plaintext, int* stream, int length) {
    int* converted = new int[length];
    cout << "Text to be encrypted: " << plaintext << endl;
    for (int i = 0; i < length; i++) {
        converted[i] = plaintext[i] - 48;
    }
    cout << "\n\nEncrypted Binary: ";
    for (int i = 0; i < length; i++) {
        encrypted[i] = converted[i] ^ stream[i];
    }
    return encrypted;
}

int convert(string num) {
    int newnum = stoi(num);
    int dec = 0, i = 0, rem;

    while (newnum != 0) {
        rem = newnum % 10;
        newnum /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}

string encryptor(int* encrypted, int length) {
    string dec = "";
    string temp = "";
    string ciphertext = "";
    for (int i = 0; i < length; i += 8) {
        for (int j = i; j < i + 8; j++) {
            temp = to_string(encrypted[j]);
            dec += temp;
            cout << "stringed: " << dec << " ";
        }
        int decimal = convert(dec);
        cout << "decimals: " << decimal;
       /*if (decimal > 0 && decimal < 9) {
            cout << " chared: " << char(decimal+48) << endl;
            ciphertext += char(decimal+48);
            temp = dec = "\0";
            cout << endl;
        }
        else {*/
            cout << " chared: " << char(decimal) << endl;
            ciphertext += char(decimal);
            temp = dec = "\0";
            cout << endl;
        //}
    }
    //cout<<"\n\n Ciphertext: "<<ciphertext<<endl<<endl;
    return ciphertext;
}

int main() {


    // initializing strings for plaintext, encryption key and initail vector
    string plaintext = "\0";
    string key = "\0";
    string in_vector = "\0";

    // getting plaintext from user
    cout << "Enter plain text to encrypt: ";
    getline(cin, plaintext);

again:
    // getting key to encrypt plain text
    cout << "Enter key to encrypt plain text: ";
    getline(cin, key);

    // getting length of key
    int len = key.length();
    if (len != 10) { // key's lenght must be 10 bytes(80 bits)
        cout << "The key entered should be exactly 10 bytes~(80 bits)" << endl;
        goto again; // moving again to the label if the key is not of 80 bytes
    }

againiv:
    // getting the initial vector from the user
    cout << "Enter the initail vector: ";
    getline(cin, in_vector);

    // getting length of initial vector
    int len2 = in_vector.length();
    if (len2 != 10) {
        cout << "Initial vector must have a total of 10 bytes~(80 bits)" << endl;
        goto againiv;
    }

    // printing inputs taken from user and their size in bytes
    cout << "\n\nPlaintext: " << plaintext << "\t Size of plain text    : " << plaintext.length() << " bytes" << endl;
    cout << "\nEnc_Key  : " << key << "\t Size of Encryption Key      : " << len << " bytes" << endl;
    cout << "\nIn_vector: " << in_vector << "\t Size of Initial Vector: " << in_vector.length() << " bytes\n" << endl;

    // string binaries of inputs in main function
    string pt_converted = binary_converter(plaintext);
    string key_converted = binary_converter(key);
    string iv_converted = binary_converter(in_vector);
    /*string pt_converted = binary_converter(plaintext, plaintext.length(), "Converted PlainText: ");
    string key_converted = binary_converter(key, len, "Converted Encrypted Key: ");
    string iv_converted = binary_converter(in_vector, len2, "Converted Initial vector: ");

    /* Checks for verifying binaries
    cout<<"\n\nConverted plaintext check : "<<pt_converted<<endl<<endl;
    cout<<"\n\nConverted Encry_key check : "<<key_converted<<endl<<endl;
    cout<<"\n\nConverted in_vector check : "<<iv_converted<<endl<<endl;*/

    // Creating dynamic array for LFSR1
    char* LFSR1 = new char[93];
    // Calling function for initializing and loading LFSR with encryption key
    LFSR1 = LFSR1_Loader(LFSR1, iv_converted);

    // Creating dynamic array for LFSR2
    char* LFSR2 = new char[84];
    // Calling function for initializing and loading LFSR with initial vector
    LFSR2 = LFSR2_Loader(LFSR2, key_converted);

    // Creating dynamic array for LFSR3
    char* LFSR3 = new char[111];
    // Calling function to initialize and load 3rd LFSR
    LFSR3 = LFSR3_Loader(LFSR3);

    cout << "\n\t\t\t Loaded LFSR's" << endl;

    // Prinitnig elements of 1st LFSR
    cout << "\nLFSR1: ";
    LFSR1_printer(LFSR1);

    // Prinitng elements of 2ndd LFSR
    cout << "\nLFSR2: ";
    LFSR2_printer(LFSR2);

    // Printing elements of 3rd LFSR
    cout << "\nLFSR3: ";
    LFSR3_printer(LFSR3);

    cout << "\n\n\t\t\t Randomized LFSRs \n\n";
    randomizer(LFSR1, LFSR2, LFSR3);

    cout << "\n\nLFSR1: ";
    LFSR1_printer(LFSR1);

    // Prinitng elements of 2ndd LFSR
    cout << "\nLFSR2: ";
    LFSR2_printer(LFSR2);

    // Printing elements of 3rd LFSR
    cout << "\nLFSR3: ";
    LFSR3_printer(LFSR3);

    int* key_stream = new int[(plaintext.length()) * 8];
    key_stream = generator(LFSR1, LFSR2, LFSR3, plaintext.length());

    cout << "\n\n\t\t\t Randomized LFSRs after key stream generation" << endl;

    cout << "\n\nLFSR1: ";
    LFSR1_printer(LFSR1);

    // Prinitng elements of 2ndd LFSR
    cout << "\nLFSR2: ";
    LFSR2_printer(LFSR2);

    // Printing elements of 3rd LFSR
    cout << "\nLFSR3: ";
    LFSR3_printer(LFSR3);

    cout << "\n\n\t\t\tKey Stream: \n\n";
    int count = 0;
    for (int i = 0; i < plaintext.length() * 8; i++) {
        cout << key_stream[i];
        count += 1;
    }
    cout << "\nLength of keystream: " << count << endl;
    int* converted = new int[pt_converted.length()];
    converted = int_converter(converted, pt_converted, key_stream, pt_converted.length());

    for (int i = 0; i < pt_converted.length(); i++) {
        cout << converted[i];
    }
    cout << "\n\n\t\t\t cutting encrypted binary in groups of 8 and converting into ciphertext\n\n";
    string ciphertext = encryptor(converted, pt_converted.length());

    cout   << "\n\n Ciphertext: " << "\033[92m" << ciphertext << "\033[0m" << endl << endl;
    cout << "lenght of cipher text: " << ciphertext.length() << endl << endl;
    string binary_cipher = binary_converter(ciphertext);
    cout << "Binary Cipher: " << binary_cipher << endl;
    /*for (int i = 0; i < ciphertext.length(); i++) {
        cout << binary_cipher[i];
    }*/
    int* integered_cipher = new int[binary_cipher.length()];
    integered_cipher = int_converter(integered_cipher, binary_cipher, key_stream, binary_cipher.length());
    string converted_cipher = encryptor(integered_cipher, binary_cipher.length());

    cout << "\nConverted ciphertext (plaintext): " << "\033[92m" << converted_cipher << "\033[0m" << endl << endl;
    return 0;

    
}