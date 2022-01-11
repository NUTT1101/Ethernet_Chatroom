/*
  簡易SPN加密
  設計者:KennyLin
  日期:2022/1/9
  版本:1.0
*/

#include<iostream>
#include<cmath>
#include <pcap.h>

using namespace std;

class SPN_255
{
  public:
  unsigned char encryption(char);
  unsigned char decrypt(char);

  private:
  bool bit[8];
  unsigned int bitnum_all, bitnum_1, bitnum_2;

  int key(int);
  int turn_1(int);
  int turn_2(int);
  int change_1(int);
  int change_2(int);

  void turn_bitall_bit8();
  void turn_bit8_bitall();
  void turn_bit8_bitnum();
  void turn_bitnum_bit8();
};
int SPN_255::key(int data)
{
  if(data == 0) {return 0xee;}
  if(data == 1) {return 0x44;}
  if(data == 2) {return 0x19;}
  return 0;
}
int SPN_255::turn_1(int data)
{
  if(data == 0) {return 1;}
  if(data == 1) {return 3;}
  if(data == 2) {return 5;}
  if(data == 3) {return 7;}
  if(data == 4) {return 9;}
  if(data == 5) {return 11;}
  if(data == 6) {return 13;}
  if(data == 7) {return 15;}
  if(data == 8) {return 2;}
  if(data == 9) {return 4;}
  if(data == 10) {return 6;}
  if(data == 11) {return 8;}
  if(data == 12) {return 10;}
  if(data == 13) {return 12;}
  if(data == 14) {return 14;}
  if(data == 15) {return 0;}
  return 0;
}
int SPN_255::turn_2(int data)
{
  if(data == 0) {return 15;}
  if(data == 1) {return 0;}
  if(data == 2) {return 8;}
  if(data == 3) {return 1;}
  if(data == 4) {return 9;}
  if(data == 5) {return 2;}
  if(data == 6) {return 10;}
  if(data == 7) {return 3;}
  if(data == 8) {return 11;}
  if(data == 9) {return 4;}
  if(data == 10) {return 12;}
  if(data == 11) {return 5;}
  if(data == 12) {return 13;}
  if(data == 13) {return 6;}
  if(data == 14) {return 14;}
  if(data == 15) {return 7;}
  return 0;
}
int SPN_255::change_1(int data)
{
  if(data == 0) {return 2;}
  if(data == 1) {return 3;}
  if(data == 2) {return 0;}
  if(data == 3) {return 4;}
  if(data == 4) {return 1;}
  if(data == 5) {return 7;}
  if(data == 6) {return 5;}
  if(data == 7) {return 6;}
  return 0;
}
int SPN_255::change_2(int data)
{
  if(data == 0) {return 2;}
  if(data == 1) {return 4;}
  if(data == 2) {return 0;}
  if(data == 3) {return 1;}
  if(data == 4) {return 3;}
  if(data == 5) {return 6;}
  if(data == 6) {return 7;}
  if(data == 7) {return 5;}
  return 0;
}

void SPN_255::turn_bitall_bit8()
{
  unsigned int bitnum = bitnum_all;  ///抓到bug (沒加unsigned)
  for(int i = 0; i < 8; i++)
  {
    int rem = bitnum % 2;
    bit[i] = rem;
    bitnum /= 2;
  }
}
void SPN_255::turn_bit8_bitall()
{
  bitnum_all = 0;
  for(int i = 0; i < 8; i++)
  {
    int d = (int)pow(2.0,(double)i);
    bitnum_all += ((int)bit[i] - 0)*d;
  }
}
void SPN_255::turn_bit8_bitnum()
{
  bitnum_1 = bitnum_2 = 0;
  for(int i = 0; i < 8; i++)
  {
    if(i <= 7 && i >= 4)
    {
      int I = i - 4;
      int d = (int)pow(2.0,(double)I);
      bitnum_2 += ((int)bit[i] - 0)*d;
      continue;
    }
    int d = (int)pow(2.0,(double)i);
    bitnum_1 += ((int)bit[i] - 0)*d;
  }
}
void SPN_255::turn_bitnum_bit8()
{
  int bitnum1 = bitnum_1;
  int bitnum2 = bitnum_2;

  for(int i = 0;i<8;i++)
  {
    int rem;
    if(i < 8 && i >= 4)
    {
      rem = bitnum2 % 2;
      bit[i] = rem;
      bitnum2 /= 2;
      continue;
    }
    rem = bitnum1 % 2;
    bit[i] = rem;
    bitnum1 /=2;
  }
}

unsigned char SPN_255::encryption(char data)
{
  bitnum_all = (short)data;
  bool tem[8];
  for(int i = 0; i < 3; i++)
  {
    turn_bitall_bit8();//ok 才怪
    turn_bit8_bitnum();//ok
    bitnum_1 = turn_1((int)bitnum_1);//ok
    bitnum_2 = turn_1((int)bitnum_2);//ok
    turn_bitnum_bit8();//ok
    for(int j = 0; j < 8; j++)
    {
      tem[change_1(j)] = bit[j];
    }
    for(int j = 0; j < 8; j++)
    {
      bit[j] = tem[j];
    }
    turn_bit8_bitall();//ok
    bitnum_all ^= key(i);//ok
  }

  return bitnum_all;
}
unsigned char SPN_255::decrypt(char data)
{
  bitnum_all = (short)data;
  bool tem[8];
  for(int i = 2; i>=0 ;i--)
  {
    bitnum_all ^= key(i);//ok
    turn_bitall_bit8();//ok 才怪
    for(int j = 0; j < 8; j++)
    {
      tem[change_2(j)] = bit[j];
    }
    for(int j = 0; j < 8; j++)
    {
      bit[j] = tem[j];
    }
    turn_bit8_bitnum();//ok
    bitnum_1 = turn_2((int)bitnum_1);//ok
    bitnum_2 = turn_2((int)bitnum_2);//ok
    turn_bitnum_bit8();//ok
    turn_bit8_bitall();//ok
  }

  return bitnum_all;
}

void packet_encryption(u_char* enc,SPN_255 spn, unsigned int packetLength)
{
  for(unsigned int i = 20; i < packetLength; i++)
  {
    enc[i] = spn.encryption(enc[i]);
  }
}
void packet_decrypt(u_char* dec,SPN_255 spn, unsigned int packetLength)
{
  for(unsigned int i = 20; i < packetLength; i++)
  {
    dec[i] = spn.decrypt(dec[i]);
  }
}
/*
int main()
{
  char a[1500];
  char* b = a;
  SPN_255 spn;
  for(int i = 0; i < 1500; i++)
  {
    cin >> *(b + i);
  }
  for(int i = 0; i < 1500; i++)
  {
    cout << *(b + i);
  }
  cout << endl;
  b = packet_encryption(b,spn);  //這行
  
  for(int i = 0; i < 1500; i++)
  {
    cout << *(b + i);
  }
  
  cout << endl;
  b = packet_decrypt(b,spn); //這行
  for(int i = 0; i < 1500; i++)
  {
    cout << *(b + i);
  }

  return 0;
}
*/