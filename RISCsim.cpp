#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

map<string, vector<string>> registers;
// unsigned int pc; // program counter
// unsigned char memory[];
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
    int temp1 = stoi(rs1);
    int temp2 = stoi(imm);
    int temp3 = stoi(rd);
    temp3 = temp2 + temp1;
    cout << temp3;
}

void SLTI(string rd, string rs1, string imm)
{
    int temp1 = stoi(rs1);
    int temp2 = stoi(imm);
    int temp3 = stoi(rd);
    if (temp1 < temp2)
        temp3 = 1;
    else
        temp3 = 0;
}

void SLTIU(string rd, string rs1, string imm)
{
    int temp1 = stoi(rs1);
    int temp2 = stoi(imm);
    int temp3 = stoi(rd);
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
}

void XORI(string rd, string rs1, string imm)
{
    int temp1 = stoi(rs1);
    int temp2 = stoi(imm);
    int temp3 = stoi(rd);
    temp3 = temp1 ^ temp2;
}

void ORI(string rd, string rs1, string imm)
{
    int temp1 = stoi(rs1);
    int temp2 = stoi(imm);
    int temp3 = stoi(rd);
    temp3 = temp1 | temp2;
}

void ANDI(string rd, string rs1, string imm)
{
    int temp1 = stoi(rs1);
    int temp2 = stoi(imm);
    int temp3 = stoi(rd);
    temp3 = temp1 & temp2;
}

void LUI(string rd, string imm)
{
    string luistring;
    luistring = to_binary(imm);
    luistring.erase(0, 12);
    luistring += "000000000000";
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
    int temp1 = stoi(rs1);
    int temp2 = stoi(rs2);
    int jumpaddress = currentaddress;
    if (temp1 == temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}
int BNE(string rs1, string rs2, string imm, int currentaddress)
{
    int temp1 = stoi(rs1);
    int temp2 = stoi(rs2);
    int jumpaddress = currentaddress;
    if (temp1 != temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}
int BLT(string rs1, string rs2, string imm, int currentaddress)
{
    int temp1 = stoi(rs1);
    int temp2 = stoi(rs2);
    int jumpaddress = currentaddress;
    if (temp1 < temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}
int BGE(string rs1, string rs2, string imm, int currentaddress)
{
    int temp1 = stoi(rs1);
    int temp2 = stoi(rs2);
    int jumpaddress = currentaddress;
    if (temp1 > temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}
int BLTU(string rs1, string rs2, string imm, int currentaddress)
{
    unsigned int temp1 = stoi(rs1);
    unsigned int temp2 = stoi(rs2);
    int jumpaddress = currentaddress;
    if (temp1 < temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}

int BGEU(string rs1, string rs2, string imm, int currentaddress)
{
    unsigned int temp1 = stoi(rs1);
    unsigned int temp2 = stoi(rs2);
    int jumpaddress = currentaddress;
    if (temp1 > temp2)
    {
        jumpaddress = currentaddress + stoi(imm);
    }
    return jumpaddress;
}

void LH(string rd, string rs1, string offset)
{
    int destination = stoi(offset) /*+ desination of rd*/;
    string binary = to_binary(rd);
    int value = bin_to_dec(binary) && ((1 << 16) - 1);
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
    value = bin_to_dec(binary_value);
}
void LB(string rd, string rs1, string offset)
{
    int destination = stoi(offset) /*+ desination of rd*/;
    string binary = to_binary(rd);
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
    value = bin_to_dec(binary_value);
}
int main()
{
    return 0;
}
