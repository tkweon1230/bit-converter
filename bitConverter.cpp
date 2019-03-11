//Author: Tae Kweon
//Program: This program uses file redirection for the input. It reads a line of bits from packets.dat
//one at a time. Then it checks for error in transmission, if there is an error, it is corrected. Then,
//the gray code is extracted from the packet, converted to binary, binary converted to decimal, then 
//corrected for the excess 127. Finally, the answer is printed as a character using static cast.
//The process is repeated until all of the packets are read from packets.dat

#include <math.h>
#include <iostream>
using namespace std;

//function prototypes
void errorDetect(char []);
void pullOutParityBit(char [], int []);			
void convertToBinary(int [], int []);        
void binaryToDecimal(int []);			
void readPacket(char []);
//main function
int main()
{
	char packet[13];
	int grey[9];		
	int binary[9];



	while(cin)			//while there's data to cin
	{
		readPacket(packet);
		errorDetect(packet);
		pullOutParityBit(packet, grey);
		convertToBinary(grey, binary);
		binaryToDecimal(binary);
	}
	

	cout << endl;	
	return 0;
}

//this function detects whether or not a packet of bits has an error and fixes it
void errorDetect(char packet[])
{
	int pos = 0; 			//index of bit to flip

	//8's parity bit
	if((packet[7]+packet[8]+packet[9]+packet[10]+packet[11]+packet[12]) % 2 == 1)
	{

		pos+=8;
	}

	//4's parity bit
	if((packet[3]+packet[4]+packet[5]+packet[6]+packet[11]+packet[12]) % 2 == 1)
	{
		pos+=4;
	}
	//2's parity bit
	if((packet[1]+packet[2]+packet[5]+packet[6]+packet[9]+packet[10]) % 2 == 1)
	{
		pos+=2;
	}
	//1's parity bit
	if((packet[0]+packet[2]+packet[4]+packet[6]+packet[8]+packet[10]+packet[12]) % 2 == 1)
	{
		pos+=1;
	}
	
	if(pos > 0) //if there is an error flip bits
	{
		if(packet[pos-1] == '0')
		{
			packet[pos-1] = '1';
		}
		else if(packet[pos-1]  == '1')
		{
			packet[pos-1] = '0';
		}
	}
	pos = 0;    //reset position of the bit to flip
}


//this function pulls out the parity bits. Which are 0,1,2,4,8
void pullOutParityBit(char packet[], int grey[])
{
	int j = 0;		//variable to increment to use as grey array's index

	for(int i = 0; i < 13; i++)
	{
		if(i!=0 && i!=1 && i!=3 && i != 7)		//if it's any but 0, 1, 2, 4, or 8's position then
		{						//put the bits into the grey array
			grey[j] = packet[i] - '0';
			j++;					//increment j to put in next bit in the next index of array
		
		}
	}
	
	
}

//this function converts grey code to binary
void convertToBinary(int grey[], int binary[]) 			
{
	int sum = 0;		//must check if sum is odd to flip to bit or not
	for(int i = 0; i < 9; i++)
	{
		if(grey[i-1] == 1)	//check if left number is 1 then add to sum
		{
			sum++;
		}
		if(sum % 2 == 1)		//if odd number of 1s then flip bit
		{	
			if(grey[i] == 0)		//flip bit
			{
				binary[i] = 1;
			}
			else if(grey[i] == 1)
			{
				binary[i] = 0;
			}
		}	
		else if(sum % 2 == 0)			//if even number of 1s then dont flip bit
		{
			if(grey[i] == 0)
			{
				binary[i] = 0;
			}
			else if(grey[i] == 1)
			{
				binary[i] = 1;
			}
		}

	}


}	
//this function converts binary to a decimal number then the decimal
//number is subtracted by 127 to get rid of the excess-127. Then the
//new number is turned into a character using static_cast
void binaryToDecimal(int binary[])   
{
	int decNum = 0;		//var declared to store decimal number
	int newNum = 0;		//new num declared to store decimal number - 127
	int x = 8;		//var declared to set index to the right number when using pow
	char ch;		//var declared to store letter
	for(int i = 9; i > 0; i--)
	{
		if(binary[i] == 1)		//if it's a 1 in the index then add to decNum the binary position
		{
			decNum += pow(2,x-i);   //binary positions 1,2,4,8,16,32......

		}

	}
	newNum = decNum - 127;			//subtract the excess 127
	ch = static_cast<char>(newNum);		//the number is turned into a character
	cout << ch;				

}
//this function reads all the bits in a line of packets.dat
void readPacket(char packet[])
{
	for(int i = 0; i < 13; i++)
	{
		cin >> packet[i];
	}
}
