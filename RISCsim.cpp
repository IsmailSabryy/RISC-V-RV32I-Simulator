#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cstdint>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;
vector<pair<string, string>> reg;
map<int, string> fileaddresses;
map<int, string> codeaddresses;
map<int, string> fakecodeaddresses;

string dectobinary(const string &numStr) // using twos complement
{
    int num = stoi(numStr);
    int numbits = 32; // to get the number of bits for number
    string binary = "";

    if (num < 0) // when dealing with negative nums. use two's complement
    {
        num = -num;
        for (int i = 0; i < numbits; ++i)
        {
            if (num % 2 == 0)
                binary = "0" + binary;
            else
                binary = "1" + binary;
            num /= 2;
        }
        for (char &c : binary)
        {
            if (c == '0')
                c = '1';
            else
                c = '0';
        }
        int carry = 1;
        for (int i = numbits - 1; i >= 0; --i)
        {
            if (binary[i] == '1' && carry == 1)
            {
                binary[i] = '0';
            }
            else if (binary[i] == '0' && carry == 1)
            {
                binary[i] = '1';
                carry = 0;
            }
        }
    }
    else
    {
        for (int i = 0; i < numbits; ++i)
        {
            if (num % 2 == 0)
                binary = "0" + binary;
            else
                binary = "1" + binary;
            num /= 2;
        }
    }
    return binary;
}
string dectohex(const string &numstr)
{
    string binary = dectobinary(numstr); // convert the num to binary using the previous function
    int numbits = binary.length();

    while (binary.length() % 4 != 0) // checks if the length of binary string is divisble by 4 or not. if not then append zeros.
    {
        binary = "0" + binary;
    }
    string hex = "";
    for (int i = 0; i < numbits; i += 4)
    {
        string nibble = binary.substr(i, 4);
        int decimal = stoi(nibble, nullptr, 2); // Convert binary to decimal
        char hexdigit;
        if (decimal < 10)
        {
            hexdigit = '0' + decimal;
        }
        else
        {
            hexdigit = 'A' + (decimal - 10);
        }

        hex += hexdigit;
    }
    return hex;
}
string to_binary(string number)
{
    int num;
    num = stoi(number);
    string binary;
    while (num > 0)
    {
        binary = to_string(num % 2) + binary;
        num /= 2;
    }
    while (binary.length() < 32)
    {
        binary = "0" + binary;
    }
    return binary;
}
int bin_to_dec(string binary)
{
    int base = 1;
    int deci = 0;
    for (int i = binary.length() - 1; i >= 0; --i)
    {
        if (binary[i] == '1')
        {
            deci += base;
        }
        base *= 2;
    }

    return deci;
}
string strbin_to_dec(string binary)
{
    int base = 1;
    int deci = 0;
    for (int i = binary.length() - 1; i >= 0; --i)
    {
        if (binary[i] == '1')
        {
            deci += base;
        }
        base *= 2;
    }

    return to_string(deci);
}
string to_hexa(string number)
{
    string num;
    num = to_binary(number);
    string hexa;
    for (int i = 0; i < num.length(); i += 4)
    {
        string substring = num.substr(i, 4);
        int dec = bin_to_dec(substring);
        switch (dec)
        {
        case 0:
            hexa += '0';
            break;
        case 1:
            hexa += '1';
            break;
        case 2:
            hexa += '2';
            break;
        case 3:
            hexa += '3';
            break;
        case 4:
            hexa += '4';
            break;
        case 5:
            hexa += '5';
            break;
        case 6:
            hexa += '6';
            break;
        case 7:
            hexa += '7';
            break;
        case 8:
            hexa += '8';
            break;
        case 9:
            hexa += '9';
            break;
        case 10:
            hexa += 'A';
            break;
        case 11:
            hexa += 'B';
            break;
        case 12:
            hexa += 'C';
            break;
        case 13:
            hexa += 'D';
            break;
        case 14:
            hexa += 'E';
            break;
        case 15:
            hexa += 'F';
            break;
        default:
            break;
        }
    }
    return hexa;
}
void ADDI(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3 = temp2 + temp1;
    it_rd->second = to_string(temp3);
}

void SLTI(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3;
    if (temp1 < temp2)
        temp3 = 1;
    else
        temp3 = 0;
    it_rd->second = to_string(temp3);
}

void SLTIU(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3;
    if (imm == "1")
    {
        if (temp1 == 0)
            temp3 = 1;
        else
            temp3 = 0;
    }
    else
    {
        if (temp1 < temp2)
            temp3 = 1;
        else
            temp3 = 0;
    }
    it_rd->second = to_string(temp3);
}

void XORI(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3 = temp1 ^ temp2;
    it_rd->second = to_string(temp3);
}

void ORI(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3 = temp1 | temp2;
    it_rd->second = to_string(temp3);
}

void ANDI(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3 = temp1 & temp2;
    it_rd->second = to_string(temp3);
}

void LUI(string rd, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    string luistring;
    luistring = to_binary(imm);
    luistring.erase(0, 12);
    luistring += "000000000000";
    it_rd->second = to_string(bin_to_dec(luistring));
}

void LH(string rd, string rs1, string offset)
{
    int RsValue;
    int value;
    for (auto &i : reg)
    {
        if (i.first == rs1)
        {
            RsValue = stoi(i.second); // address stored in rs1
            break;
        }
    }
    int RdValue = RsValue + stoi(offset); // Effective address

    for (const auto &i : fileaddresses)
    {
        if (i.first == RdValue)
        {
            value = stoi(i.second); // Value in effective Address
            break;
        }
    }
    int32_t sign_extended_value = (value << 16) >> 16;
    for (auto &i : reg)
    {
        if (i.first == rd)
        {
            i.second = to_string(sign_extended_value); // Value in effAdd  -> rd
            break;
        }
    }
}

void LB(string rd, string rs1, string offset)
{
    int RsValue;
    int value;
    for (auto &i : reg)
    {
        if (i.first == rs1)
        {
            RsValue = stoi(i.second); // address stored in rs1
            break;
        }
    }
    int RdValue = RsValue + stoi(offset); // Effective address

    for (const auto &i : fileaddresses)
    {
        if (i.first == RdValue)
        {
            value = stoi(i.second); // Value in effective Address
            break;
        }
    }
    int8_t sign_extended_value = value; // Converting value to 8-bit signed integer
    int32_t sign_extended_32 = static_cast<int32_t>(sign_extended_value);
    for (auto &i : reg)
    {
        if (i.first == rd)
        {
            i.second = to_string(sign_extended_value); // Value in effAdd  -> rd
            break;
        }
    }
}

void LW(string rd, string rs1, string offset)
{
    int RsValue;
    string value;

    for (const auto &i : reg)
    {
        if (i.first == rs1)
        {
            RsValue = stoi(i.second);
            break;
        }
    }

    int RdValue = RsValue + stoi(offset);
    for (const auto &i : fileaddresses)
    {
        if (i.first == RdValue)
        {

            value = i.second;
            break;
        }
    }
    for (auto &i : reg)
    {
        if (i.first == rd)
        {
            i.second = value;
            break;
        }
    }
}

void LBU(string rd, string rs1, string offset)
{
    int RsValue;
    int value;
    for (auto &i : reg)
    {
        if (i.first == rs1)
        {
            RsValue = stoi(i.second); // address stored in rs1
            break;
        }
    }
    int RdValue = RsValue + stoi(offset); // Effective address

    for (const auto &i : fileaddresses)
    {
        if (i.first == RdValue)
        {
            value = stoi(i.second); // Value in effective Address
            break;
        }
    }
    int32_t zero_extended_value = (value & 0xFF);
    for (auto &i : reg)
    {
        if (i.first == rd)
        {
            i.second = to_string(zero_extended_value); // Value in effAdd  -> rd
            break;
        }
    }
}

void LHU(string rd, string rs1, string offset)
{
    int RsValue;
    int value;
    for (auto &i : reg)
    {
        if (i.first == rs1)
        {
            RsValue = stoi(i.second); // address stored in rs1
            break;
        }
    }
    int RdValue = RsValue + stoi(offset); // Effective address
    for (auto &i : fileaddresses)
    {
        if (i.first == RdValue)
        {
            value = stoi(i.second); // Value in effective Address
            break;
        }
    }
    int32_t zero_extended_value = (value & 0xFFFF);
    for (auto &i : reg)
    {
        if (i.first == rd)
        {
            i.second = to_string(zero_extended_value);
            break;
        }
    }
}

void SB(string baseAdd, string value, string offset)
{
    int dValue;
    int effectiveAdd;
    int sValue;
    int8_t temp8;
    

    for (auto &i : reg)
    {
        if (i.first == baseAdd)
        {
            dValue = stoi(i.second); // address in rs (sp)
            break;
        }
    }
    for (auto &i : reg)
    {
        if (i.first == value)
        {
            sValue = stoi(i.second); // value in ra
            break;
        }
    }
    if (sValue <= 256)
    {
        int offsetTemp = stoi(offset) / 4;        // offset can be any number -> if address = 1005 -> find 1004 and store lowest Byte
        effectiveAdd = dValue + (offsetTemp * 4); // Effective address
        sValue = sValue & 0xFF;                   // masking the lower 8 bits
        //sValue |= 0xFFFFFF00; // Sign extend
        
        for (auto &i : fileaddresses)
        {
            if (i.first == effectiveAdd)
            {
                i.second = to_string(sValue);
                break;
            }
        }
    }
    else
    {
        system("cls");
        cout << "Cannot store the value " << sValue << " as a 8 bit byte" << endl;
    }
}

void SH(string baseAdd, string value, string offset)
{

    int dValue;
    int effectiveAdd;
    int sValue;

    for (auto &i : reg)
    {
        if (i.first == baseAdd)
        {
            dValue = stoi(i.second);
            break;
        }
    }

    for (auto &i : reg)
    {
        if (i.first == value)
        {
            sValue = stoi(i.second);
            break;
        }
    }
    int offsetTemp = stoi(offset) / 4;        // offset can be a multiple of 2 -> if address = 1005 -> find 1004 and store lowest half word
    effectiveAdd = dValue + (offsetTemp * 4); // Effective address
    if (sValue <= 65536)
    {
        sValue = sValue & 0xFFFF; // masking the lower 16 bits
        for (auto &i : fileaddresses)
        {
            if (i.first == effectiveAdd)
            {
                i.second = to_string(sValue);
                break;
            }
        }
    }
    else
    {
        system("cls");
        cout << "Cannot store the value " << sValue << " as a 16 bit halfword" << endl;
    }
}

void SW(string baseAdd, string value, string offset)
{
    int dValue;
    int effectiveAdd;
    int sValue;

    for (auto &i : reg)
    {
        if (i.first == baseAdd)
        {
            dValue = stoi(i.second);
            break;
        }
    }

    effectiveAdd = dValue + stoi(offset);

    for (auto &i : reg)
    {
        if (i.first == value)
        {
            sValue = stoi(i.second);
            break;
        }
    }
    for (auto &i : fileaddresses)
    {
        if (i.first == effectiveAdd)
        {
            i.second = to_string(sValue);
            break;
        }
    }
}

void srli(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 >> temp2;
    it_rd->second = to_string(temp3);
}

void slli(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 << temp2;
    it_rd->second = to_string(temp3);
}

void srai(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 >> temp2;
    it_rd->second = to_string(temp3);
}

void add(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp2 + temp1;
    it_rd->second = to_string(temp3);
}

void sub(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 - temp2;
    it_rd->second = to_string(temp3);
}

void sll(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 << temp2;
    it_rd->second = to_string(temp3);
}

void slt(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = (temp1 < temp2) ? 1 : 0;
    it_rd->second = to_string(temp3);
}

void sltu(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    unsigned int temp1 = stoi(it_rs1->second);
    unsigned int temp2 = stoi(it_rs2->second);
    int temp3 = (temp1 < temp2) ? 1 : 0;
    it_rd->second = to_string(temp3);
}

void XOR(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 ^ temp2;
    it_rd->second = to_string(temp3);
}

void srl(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    unsigned int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 >> temp2;
    it_rd->second = to_string(temp3);
}

void sra(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 >> temp2;
    it_rd->second = to_string(temp3);
}

void OR(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 | temp2;
    it_rd->second = to_string(temp3);
}

void AND(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 && temp2;
    it_rd->second = to_string(temp3);
}

bool isSpace(char ch)
{
    return (ch == ' ');
}
bool isX0(string rd)
{
    if (rd == "zero")
    {
        cout << "Zero register cannot be altered, check your code" << endl;
        return true;
    }
    else
        return false;
}
char menu[4][45] = {
    {" 1] Input Starting Address          "},
    {" 2] Exit Solver                     "}};
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void setColor(int color)
{
    HANDLE hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void goto_row_col(int row, int col)
{
    COORD c;
    c.X = col;
    c.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int showMenu()
{
    char ch;
    int pos = 1;

    do
    {
        ShowConsoleCursor(false);
        setColor(15);
        goto_row_col(10, 39);
        cout << menu[0];
        goto_row_col(11, 39);
        cout << menu[1];
        goto_row_col(12, 39);
        cout << menu[2];
        goto_row_col(13, 39);
        cout << menu[3];
        setColor(240);
        goto_row_col(10 + pos - 1, 39);
        cout << menu[pos - 1];
        ch = getch();
        switch (ch)
        {
        case 13:
            switch (pos)
            {
            case 1:
                setColor(15);
                ShowConsoleCursor(true);
                system("cls");
                int address;
                cout << "Input Address :";
                cin >> address;
                system("cls");
                return address;
                break;
            case 2:
                setColor(15);
                ShowConsoleCursor(true);
                exit(0);
                break;
            }
            break;
        case -32:
            ch = getch();
            switch (ch)
            {
            case 72:
                pos--;
                if (pos == 0)
                    pos = 4;
                break;
            case 80:
                pos++;
                if (pos == 5)
                    pos = 1;
                break;
            }
        }
    } while (true);
}
void printevstep(int pccounter)
{
    cout << left << setw(10) << "REG" << setw(10) << "DEC" << setw(40) << "BIN" << setw(40) << "HEX" << endl;

    for (const auto &linee : reg)
    {
        string bin = "0b" + dectobinary(linee.second);
        string hex = "0x" + dectohex(linee.second);
        cout << left << setw(10) << linee.first << setw(10) << linee.second << setw(40) << bin << setw(40) << hex << endl;
    }
    cout << "PC counter For the Above cycle:" << pccounter << endl;
    cout << "Memory addresses:" << endl;
    for (const auto &pair : fileaddresses)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << endl;
}
char menu2[5][45] = {
    {" 1] Print Register Content         "},
    {" 2] Print Code to be executed       "},
    {" 3] Print Labels and their addresses "},
    {" 4] Iterate the next step            "},
    {" 5] Exit Solver                     "}};
int showResult(const vector<pair<string, string>> &reg, const map<int, string> &codeaddresses, const map<int, string> &fakecodeaddresses, int PC)
{
    char ch;
    int pos = 1;

    do
    {
        ShowConsoleCursor(false);
        setColor(15);
        goto_row_col(10, 39);
        cout << menu2[0];
        goto_row_col(11, 39);
        cout << menu2[1];
        goto_row_col(12, 39);
        cout << menu2[2];
        goto_row_col(13, 39);
        cout << menu2[3];
        goto_row_col(14, 39);
        cout << menu2[4];
        setColor(240);
        goto_row_col(10 + pos - 1, 39);
        cout << menu2[pos - 1];
        ch = getch();
        switch (ch)
        {
        case 13:
            switch (pos)
            {
            case 1:

                setColor(15);
                ShowConsoleCursor(true);
                system("cls");
                if (reg.empty())
                {
                    cout << "Registers are empty." << endl;
                }
                printevstep(PC);
                getch();
                system("cls");
                break;
            case 2:
                setColor(15);
                ShowConsoleCursor(true);
                system("cls");
                cout << "Code to be executed : " << endl;
                cout << "Note that the values next to the instruction represnet memory addresses " << endl;
                for (const auto &pair : codeaddresses)
                {
                    cout << pair.first << ": " << pair.second << endl;
                }
                getch();
                system("cls");
                break;
            case 3:
                setColor(15);
                ShowConsoleCursor(true);
                system("cls");
                cout << "Labels and their respective address : " << endl;
                for (const auto &pair : fakecodeaddresses)
                {
                    cout << pair.first << ": " << pair.second << endl;
                }
                getch();
                system("cls");
                break;
            case 4:
                setColor(15);
                ShowConsoleCursor(true);
                return 1;
                break;
            case 5:
                setColor(15);
                ShowConsoleCursor(true);
                exit(0);
                break;
            }
            break;
        case -32:
            ch = getch();
            switch (ch)
            {
            case 72:
                pos--;
                if (pos == 0)
                    pos = 5;
                break;
            case 80:
                pos++;
                if (pos == 6)
                    pos = 1;
                break;
            }
        }
    } while (true);
}
int main()
{
    int address = showMenu();
    int startAdd = address;
    int nextStep = 0;
    vector<string> filelines;
    ifstream reader("riscvcode.txt");
    ifstream registerstate("registerstate.txt");
    string linereg;
    while (getline(registerstate, linereg))
    {
        stringstream str(linereg);
        string linesep1, linesep2;
        getline(str, linesep1, ',');
        getline(str, linesep2);
        reg.push_back(make_pair(linesep1, linesep2));
    }
    string line;
    while (getline(reader, line))
    {
        string inputline;
        string finalline;
        bool found = false;
        int count = 0;
        if (!line.empty())
        {
            for (int i = 0; i < line.length(); i++)
            {
                if (isalpha(line[i]))
                {
                    break;
                }

                count++;
            }
            inputline = line.substr(count, line.length());
            for (int j = 0; j < inputline.length(); j++)
            {
                if (inputline[j] == ':')
                {
                    continue;
                }
                else
                    finalline += inputline[j];
            }
            filelines.push_back(finalline);
        }
    }
    auto it_complete = find(filelines.begin(), filelines.end(), "main");
    auto itfiner = fileaddresses.begin();
    while (it_complete != filelines.end())
    {

        string s = *it_complete;
        fileaddresses[address] = "0";
        int count = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ',')
            {
                count++;
            }
        }
        if (count != 0)
        {
            codeaddresses[address] = s;
            address += 4;
        }
        else
        {
            fakecodeaddresses[address] = s;
        }
        it_complete++;
        itfiner++;
    }

    auto it = codeaddresses.begin();
    for (auto &i : reg)
    {
        if (i.first == "sp")
        {
            i.second = to_string(startAdd + 12); // increment stack by 3 words
        }
    }
    while (it != codeaddresses.end())
    {
        bool jumpflag = false;
        stringstream sep(it->second);
        string insname, RD, RS1, RS2, IMM, OFF;
        getline(sep, insname, ' ');
        address = it->first;

        if (insname == "ADDI" || insname == "addi") // 1
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                return 0;
            }

            ADDI(RD, RS1, IMM);
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "ADD" || insname == "add") // 2
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            add(RD, RS1, RS2);
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SUB" || insname == "sub") // 3
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                sub(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "LUI" || insname == "lui") // 4
        {
            getline(sep, RD, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                return 0;
            }
            LUI(RD, IMM);
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SLTI" || insname == "slti") // 5
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                SLTI(RD, RS1, IMM);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SLTIU" || insname == "sltiu") // 6
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                SLTIU(RD, RS1, IMM);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "ORI" || insname == "ori") // 7
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                ORI(RD, RS1, IMM);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "OR" || insname == "or") // 8
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                OR(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "AND" || insname == "and") // 9
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                AND(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "ANDI" || insname == "andi") // 10
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                ANDI(RD, RS1, IMM);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "XORI" || insname == "xori") // 11
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                XORI(RD, RS1, IMM);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "XOR" || insname == "xor") // 12
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                XOR(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "BNE" || insname == "bne") // 13
        {
            string jump;
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, jump);
            auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                 { return p.first == RD; });
            auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                  { return p.first == RS1; });

            if (it_rd->second != it_rs1->second)
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {
                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "BEQ" || insname == "beq") // 14
        {
            string jump;
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, jump);
            auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                 { return p.first == RD; });
            auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                  { return p.first == RS1; });

            if (it_rd->second == it_rs1->second)
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {
                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "BLT" || insname == "blt") // 15
        {
            string jump;
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, jump);
            auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                 { return p.first == RD; });
            auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                  { return p.first == RS1; });

            if (stoi(it_rd->second) < stoi(it_rs1->second))
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {
                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "BGE" || insname == "bge") // 16
        {
            string jump;
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, jump);
            auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                 { return p.first == RD; });
            auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                  { return p.first == RS1; });

            if (stoi(it_rd->second) > stoi(it_rs1->second))
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {
                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "BLTU" || insname == "blt") // 17
        {
            string jump;
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, jump);
            auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                 { return p.first == RD; });
            auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                  { return p.first == RS1; });

            unsigned int rd1 = stoi(it_rd->second);
            unsigned int rs11 = stoi(it_rs1->second);
            if (rd1 < rs11)
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {
                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "BGEU" || insname == "bgeu") // 18
        {
            string jump;
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, jump);
            auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                 { return p.first == RD; });
            auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                  { return p.first == RS1; });

            unsigned int rd1 = stoi(it_rd->second);
            unsigned int rs11 = stoi(it_rs1->second);
            if (rd1 > rs11)
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {
                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SRLI" || insname == "srli") // 19
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                srli(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SLLI" || insname == "slli") // 20
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                slli(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SRAI" || insname == "srai") // 21
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                srai(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SLL" || insname == "sll") // 22
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                sll(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SLT" || insname == "slt") // 23
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                slt(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SLTU" || insname == "sltu") // 24
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                sltu(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SRL" || insname == "srl") // 25
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                srl(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SRA" || insname == "sra") // 26
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                return 0;
            }
            else
            {
                sra(RD, RS1, RS2);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "LW" || insname == "lw") // 27
        {
            getline(sep, RD, ',');
            getline(sep, OFF, '(');
            getline(sep, RS1, ')');
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                LW(RD, RS1, OFF);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "LH" || insname == "lh") // 28
        {
            getline(sep, RD, ',');
            getline(sep, OFF, '(');
            getline(sep, RS1, ')');
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                LH(RD, RS1, OFF);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "LB" || insname == "lb") // 29
        {
            getline(sep, RD, ',');
            getline(sep, OFF, '(');
            getline(sep, RS1, ')');
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                LB(RD, RS1, OFF);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "LBU" || insname == "lbu") // 30
        {
            getline(sep, RD, ',');
            getline(sep, OFF, '(');
            getline(sep, RS1, ')');
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                LBU(RD, RS1, OFF);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "LHU" || insname == "lhu") // 31
        {
            getline(sep, RD, ',');
            getline(sep, OFF, '(');
            getline(sep, RS1, ')');
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                LHU(RD, RS1, OFF);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SB" || insname == "sb") // 32
        {
            getline(sep, RS1, ',');
            getline(sep, OFF, '(');
            getline(sep, RD, ')');
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                SB(RD, RS1, OFF);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SH" || insname == "sh") // 33
        {
            getline(sep, RS1, ',');
            getline(sep, OFF, '(');
            getline(sep, RD, ')');
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                SH(RD, RS1, OFF);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "SW" || insname == "sw") // 34
        {
            // SW ra,0(sp)
            getline(sep, RS1, ',');
            getline(sep, OFF, '(');
            getline(sep, RD, ')');
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                SW(RD, RS1, OFF);
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "JAL" || insname == "jal") // 35
        {
            string jump;
            getline(sep, RD, ',');
            getline(sep, jump);

            if (RD == "zero")
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {
                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            else
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {

                        jumpflag = true;
                        address = address + 4;
                        auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                             { return p.first == RD; });

                        it_rd->second = to_string(address);
                        address = i.first;
                    }
                }
            }
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "JALR" || insname == "jalr") // 36
        {
            string jump;
            int tempAdd = address;
            getline(sep, RD, ',');
            getline(sep, RS1, ','); // register containing address
            getline(sep, OFF);
            auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                  { return p.first == RS1; });
            unsigned int sValue = stoi(it_rs1->second); // address stored in register rs1
            int jumpTemp = sValue + stoi(OFF);

            for (auto i : fakecodeaddresses)
            {
                if (i.first == jumpTemp)
                {
                    jump = i.second;
                }
            }
            if (RD == "zero")
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {

                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            else
            {
                for (auto i : fakecodeaddresses)
                {
                    if (i.second == jump)
                    {
                        jumpflag = true;
                        address = i.first;
                    }
                }
            }
            auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                 { return p.first == RD; });
            it_rd->second = to_string(tempAdd + 4);
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "AUIPC" || insname == "auipc") // 37
        {
            getline(sep, RD, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                break;
            }
            string auipcstring;
            int stoiimm;
            stoiimm = stoi(IMM) + address;
            IMM = to_string(stoiimm);
            auipcstring = to_binary(IMM);
            auipcstring.erase(0, 12);
            auipcstring += "000000000000";
            auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                                 { return p.first == RD; });
            int deci = bin_to_dec(auipcstring);
            it_rd->second = to_string(deci);
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
        }
        else if (insname == "FENCE" || insname == "ECALL" || insname == "EBREAK") // 40
        {
            system("cls");
            cout << " Exit instruction entered, aborting process" << endl;
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
            return 0;
        }
        else if (insname == "fence" || insname == "ecall" || insname == "ebreak")
        {
            system("cls");
            cout << " Exit instruction entered, aborting process" << endl;
            nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
            if (nextStep == 1)
            {
                nextStep = 0;
            }
            return 0;
        }
        if (jumpflag == false)
        {
            address = it->first + 4;
            it = codeaddresses.find(address);
        }
        else
        {
            it = codeaddresses.find(address);
            address += 4;
        }
    }
    nextStep = showResult(reg, codeaddresses, fakecodeaddresses, address);
    return 0;
}