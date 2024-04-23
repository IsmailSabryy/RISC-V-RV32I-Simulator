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
using namespace std;

vector<pair<string, string>> reg;
map<int, string> fileaddresses;
map<int, string> codeaddresses;

string dectobinary(const string &numStr) // using twos complement
{
    int num = stoi(numStr);
    int numbits = (int)log2(abs(num)) + 1; // to get the number of bits for number
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
    // cout << "New value of " << it_rd->first << ": " << it_rd->second << endl;
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

void AUIPC(string rd, string imm)
{
    string auipcstring;
    auipcstring = to_binary(imm);
    auipcstring.erase(0, 12);
    auipcstring += "000000000000";
    ADDI(rd, strbin_to_dec(auipcstring), strbin_to_dec("0"));
}

int JAL(string rd, string imm, int currentaddress)
{
    int jumpaddress = currentaddress + stoi(imm);
    return jumpaddress;
}

int JALR(string ra, string offset)
{
    int jumpaddress = stoi(offset) + 4 /*+ ra adress */;
    return jumpaddress;
}

int BEQ(string rs1, string rs2, string imm, int currentaddress)
{

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int jumpaddress = currentaddress;
    if (temp1 == temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}

int BNE(string rs1, string rs2, string imm, int currentaddress)
{

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int jumpaddress = currentaddress;
    if (temp1 != temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}

int BLT(string rs1, string rs2, string imm, int currentaddress)
{

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int jumpaddress = currentaddress;
    if (temp1 < temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}

int BGE(string rs1, string rs2, string imm, int currentaddress)
{
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int jumpaddress = currentaddress;
    if (temp1 > temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}

int BLTU(string rs1, string rs2, string imm, int currentaddress)
{

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    unsigned int temp1 = stoi(it_rs1->second);
    unsigned int temp2 = stoi(it_rs2->second);
    int jumpaddress = currentaddress;
    if (temp1 < temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}

int BGEU(string rs1, string rs2, string imm, int currentaddress)
{

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs2; });
    unsigned int temp1 = stoi(it_rs1->second);
    unsigned int temp2 = stoi(it_rs2->second);
    int jumpaddress = currentaddress;
    if (temp1 > temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}

void LH(string rd, string rs1, string offset)
{
    int RsValue;
    int value;
    for (auto i : reg)
    {
        if (i.first == rs1)
        {
            RsValue = stoi(i.second);
            break;
        }
    }

    int RdValue = RsValue + stoi(offset);

    for (auto i : codeaddresses)
    {
        if (i.first == RdValue)
        {
            value = stoi(i.second);
            break;
        }
    }
    for (auto i : reg)
    {
        if (i.first == rd)
        {
            i.second = to_string(value);
            break;
        }
    }
}

void LB(string rd, string rs1, string offset)
{
    /*int destination = stoi(offset);
    string binary = to_binary(rs1);
    // int value = stoi(rd) && ((1 << 8 ) - 1);
    int value = bin_to_dec(binary) && ((1 << 8) - 1);
    int msb = 1 << (32 - 1);
    if (value & msb)
    {
        msb = 1;
    }
    else
    {
        msb = 0;
    }
    string binary_value;
    for (int i = 0; i < 32 - to_binary(to_string(value)).size(); i++)
    {
        binary_value += to_string(msb);
    }
    value = bin_to_dec(binary_value);*/
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
    cout << "RdValue is " << RdValue << endl;
    for (const auto &i : fileaddresses)
    {
        if (i.first == RdValue)
        {

            value = i.second;
            cout << " Value" << value << endl;
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
}

void LHU(string rd, string rs1, string offset)
{
}

void SB(string rd, string rs1, string offset)
{
}

void SH(string rd, string rs1, string offset)
{
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
    cout << "Effective Add is " << effectiveAdd << endl;

    for (auto &i : reg)
    {
        if (i.first == value)
        {
            sValue = stoi(i.second);
            break;
        }
    }
    cout << "sValue is " << sValue << endl;
    for (auto &i : fileaddresses)
    {
        if (i.first == effectiveAdd)
        {
            i.second = to_string(sValue);
            cout << "Value in Effective address is " << i.second << endl;
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
    int temp3 = temp1 & temp2;
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
        return true;
    }
    else
        return false;
}

int main()
{
    int address;
    cout << " Input starting adress" << endl;
    cin >> address;

    vector<string> filelines;
    ifstream reader("riscvcode.txt");
    ifstream registerstate("registerstate.txt");
    ifstream filead("ad.txt");
    string linereg;
    while (getline(registerstate, linereg))
    {
        stringstream str(linereg);
        string linesep1, linesep2;
        getline(str, linesep1, ',');
        getline(str, linesep2);
        reg.push_back(make_pair(linesep1, linesep2));
    }
    string linead;
    while (getline(filead, linead))
    {
        stringstream str(linead);
        string linesep1, linesep2;
        getline(str, linesep1, ',');
        getline(str, linesep2);
        fileaddresses[stoi(linesep1)] = linesep2;
    }
    string line;
    while (getline(reader, line))
    {
        string inputline;
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
            filelines.push_back(inputline);
        }
    }
    auto it_complete = find(filelines.begin(), filelines.end(), "main:");
    auto itfiner = fileaddresses.begin();
    if (it_complete != filelines.end())
    {
        it_complete++;
        while (it_complete != filelines.end() && itfiner != fileaddresses.end())
        {
            if (itfiner->first == address)
            {
                string s = *it_complete;
                codeaddresses[address] = s;
                address += 4;
                it_complete++;
                itfiner++;
            }
            else
            {
                itfiner++;
                it_complete++;
            }
        }
    }
    for (const auto &pair : codeaddresses)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
    auto it = codeaddresses.begin();
    while (it != codeaddresses.end())
    {
        stringstream sep(it->second);
        string insname, RD, RS1, RS2, IMM, OFF;
        getline(sep, insname, ' ');
        address = it->first + 4;
        if (insname == "ADDI" || insname == "addi")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                break;
            }

            ADDI(RD, RS1, IMM);
        }
        else if (insname == "ADD" || insname == "add")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            if (isX0(RD))
            {
                break;
            }
            add(RD, RS1, RS2);
        }
        else if (insname == "SUB" || insname == "sub")
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
        }
        else if (insname == "LUI" || insname == "lui")
        {
            getline(sep, RD, ',');
            getline(sep, IMM);
            if (isX0(RD))
            {
                break;
            }
            LUI(RD, IMM);
        }
        else if (insname == "SLTI" || insname == "slti")
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
        }
        else if (insname == "SLTIU" || insname == "sltiu")
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
        }
        else if (insname == "ORI" || insname == "ori")
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
        }
        else if (insname == "OR" || insname == "or")
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
        }
        else if (insname == "AND" || insname == "and")
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
        }
        else if (insname == "ANDI" || insname == "andi")
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
        }
        else if (insname == "XORI" || insname == "xori")
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
        }
        else if (insname == "XOR" || insname == "xor")
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
        }
        else if (insname == "BNE" || insname == "bne")
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
                // bne();
            }
        }
        else if (insname == "BEQ" || insname == "beq")
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
                // beq();
            }
        }
        else if (insname == "BLT" || insname == "blt")
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
                // blt();
            }
        }
        else if (insname == "BGE" || insname == "bge")
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
                // bge();
            }
        }
        else if (insname == "BLTU" || insname == "blt")
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
                // bltu();
            }
        }
        else if (insname == "SRLI" || insname == "srli")
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
        }
        else if (insname == "SLLI" || insname == "slli")
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
        }
        else if (insname == "SRAI" || insname == "srai")
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
        }
        else if (insname == "SLL" || insname == "sll")
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
        }
        else if (insname == "SLT" || insname == "slt")
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
        }
        else if (insname == "SLTU" || insname == "sltu")
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
        }
        else if (insname == "SRL" || insname == "srl")
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
        }
        else if (insname == "SRA" || insname == "sra")
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
        }
        else if (insname == "LW" || insname == "lw")
        {
            getline(sep, RD, ',');
            getline(sep, OFF, '(');
            getline(sep, RS1, ')');
            // cout << "OFFset is " << OFF << endl;
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                LW(RD, RS1, OFF);
            }
        }
        // else if (insname == "LH" || insname == "lh"){}
        // else if (insname == "LB" || insname == "lb"){}
        // else if (insname == "LBU" || insname == "lbu"){}
        // else if (insname == "LHU" || insname == "lhu"){}
        // else if (insname == "SB" || insname == "sb"){}
        // else if (insname == "SH" || insname == "sh"){}
        else if (insname == "SW" || insname == "sw")
        {
            // SW ra,0(sp)
            getline(sep, RS1, ',');
            getline(sep, OFF, '(');
            getline(sep, RD, ')');
            // cout << "OFFset is " << OFF << endl;
            if (isX0(RD))
            {
                return 0;
            }
            else
            {

                SW(RD, RS1, OFF);
                for (pair<string, string> linee : reg)
                {
                    cout << linee.first << " " << linee.second << endl;
                }
            }
        }
        // else if (insname == "LUI" || insname == "lui"){}
        // else if (insname == "AUIPC" || insname == "auipc"){}
        else if (insname == "FENCE" || insname == "ECALL" || insname == "EBREAK")
        {
            cout << " Exit instruction entered, aborting process" << endl;
            return 0;
        }
        else if (insname == "fence" || insname == "ecall" || insname == "ebreak")
        {
            cout << " Exit instruction entered, aborting process" << endl;
            return 0;
        }

        it = codeaddresses.find(address);
    }
    for (pair<string, string> linee : reg)
    {
        cout << linee.first << " " << linee.second << endl;
    }

    return 0;
}
