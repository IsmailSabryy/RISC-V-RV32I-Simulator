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
using namespace std;

// map<string, vector<string>> registers;
vector<pair<string, string>> reg;
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
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                         { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string> &p)
                          { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3 = temp2 + temp1;
    it_rd->second = to_string(temp3);
    //cout << "New value of " << it_rd->first << ": " << it_rd->second << endl;
}

void SLTI(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3 = temp1 ^ temp2;
    it_rd->second = to_string(temp3); 
}

void ORI(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(imm);
    int temp3 = temp1 | temp2;
    it_rd->second = to_string(temp3); 
}

void ANDI(string rd, string rs1, string imm)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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

    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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
    int destination = stoi(offset) /*+ desination of rd*/;
    string binary = to_binary(rs1);
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
    int destination = stoi(offset);
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
    value = bin_to_dec(binary_value);
}

void LW(string rd, string rs1, string offset)
{
    int destination = stoi(offset);
    int value = stoi(rs1);
    string binary_value = to_binary(rs1);

    // Extracting the least significant 32 bits of binary_value
    binary_value = binary_value.substr(binary_value.length() - 32);
    int msb = binary_value[0] == '1' ? 1 : 0;

    for (int i = binary_value.length(); i < 32; i++)
        binary_value = to_string(msb) + binary_value;

    value = bin_to_dec(binary_value);

    // register[rd] = value;
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

void SW(string rd, string rs1, string offset)
{
}

void srli(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 >> temp2;
    it_rd->second = to_string(temp3);
}

void slli(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 << temp2;
    it_rd->second = to_string(temp3);
}

void srai(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 - temp2;
    it_rd->second = to_string(temp3);
}

void sll(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 << temp2;
    it_rd->second = to_string(temp3);
}

void slt(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = (temp1 < temp2) ? 1 : 0;
    it_rd->second = to_string(temp3);
}

void sltu(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    unsigned int temp1 = stoi(it_rs1->second);
    unsigned int temp2 = stoi(it_rs2->second);
    int temp3 = (temp1 < temp2) ? 1 : 0;
    it_rd->second = to_string(temp3);
}

void XOR(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 ^ temp2;
    it_rd->second = to_string(temp3);
}

void srl(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    unsigned int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 >> temp2;
    it_rd->second = to_string(temp3);
}

void sra(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 >> temp2;
    it_rd->second = to_string(temp3);
}

void OR(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs2; });
    int temp1 = stoi(it_rs1->second);
    int temp2 = stoi(it_rs2->second);
    int temp3 = temp1 | temp2;
    it_rd->second = to_string(temp3);
}

void AND(string rd, string rs1, string rs2)
{
    auto it_rd = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rd; });
    auto it_rs1 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
        { return p.first == rs1; });
    auto it_rs2 = find_if(reg.begin(), reg.end(), [&](const pair<string, string>& p)
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
bool isX0 (string rd)
{
    if (rd == "X0") {
        cout << "Invalid input, rd cannot be Register 0" << endl;
        
    }
}

int main()
{
    int address;
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
    auto it = find(filelines.begin(), filelines.end(), "main:");
    for (auto it2 = it; it2 != filelines.end(); ++it2)
    {
        stringstream sep(*it2);
        string insname, RD, RS1, RS2, IMM, OFF;
        getline(sep, insname, ' ');

        if (insname == "ADDI" || insname == "addi")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            ADDI(RD, RS1, IMM);
        }
        else if (insname == "ADD" || insname == "add")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            add(RD, RS1, RS2);
        }
        else if (insname == "SUB" || insname == "sub")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            sub(RD, RS1, RS2); 
        else if (insname == "LUI" || insname == "lui")
        {
            getline(sep, RD, ',');
            getline(sep, IMM);
            LUI(RD, IMM);
        }
        else if (insname == "SLTI" || insname == "slti")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM); 
            SLTI(RD, RS1, IMM);
        }
        else if (insname == "SLTIU" || insname == "sltiu")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            SLTIU(RD, RS1, IMM);
        }
        else if (insname == "ORI" || insname == "ori")
        {
            getline(sep, RD, ','); 
            getline(sep, RS1, ','); 
            getline(sep, IMM); 
            ORI(RD, RS1, IMM); 
        }
        else if (insname == "OR" || insname == "or")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            OR(RD, RS1, RS2);
        }
        else if (insname == "AND" || insname == "and")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            AND(RD, RS1, RS2);
        }
        else if (insname == "ANDI" || insname == "andi")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            ANDI(RD, RS1, IMM);
        }
        else if (insname == "XORI" || insname == "xori")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, IMM);
            XORI(RD, RS1, IMM);
        }
        else if (insname == "XOR" || insname == "xor")
        {
            getline(sep, RD, ',');
            getline(sep, RS1, ',');
            getline(sep, RS2);
            XOR(RD, RS1, RS2);
        }
       /* else if (insname == "BNE" || insname == "bne")

    }*/
    for (pair<string, string> linee : reg)
    {
        cout << linee.first << " " << linee.second << endl;
    }

    return 0;
}
