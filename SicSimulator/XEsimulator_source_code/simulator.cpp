/*
 *  SIC/XE Simulator Project, Released Dec,23 2012.
 *
 *  Copyright (C) 2011 Ahmad Mousa
 *  Copyright (C) 2011 Laith Zuhair
 *  Copyright (C) 2011 Sari Sultan
 *
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
 *
 *
 *  In addition, as a special exception, the copyright holders give
 *  permission to link the code of portions of this program with the
 *  Students projects under the conditions of non-commercial projects
 *
 *  You must obey the GNU General Public License in all respects
 *  for all of the code used other than Students needs. *  If you modify
 *  file(s) with this exception, you may extend this exception to your
 *  version of the file(s), but you are not obligated to do so. *  If you
 *  do not wish to do so, delete this exception statement from your
 *  version. *  If you delete this exception statement from all source
 *  files in the program, then also delete it here.
 */
// in order for full functionallity we recommend using Visual C++ 2010
// sorry for not using gcc compiler, but the course terms refused using gcc
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string CodeArray[1000];// machince code byte... byte per line
string PcArray[1000];// every byte pc
string DataChanged[1000];//memory changed data
string DataChangedId[1000];//pc for every change
int Data_Changed_Counter=0;
string OPCODE[60];//mapping for every format (opcode <==> Format)
int FORMAT[60];//format for ==== == = = = = = = = == = = = = = = =

string IOMem[1000];// i/o memory from i/o file
int IOcounter=0;
int IOindex=0;
int IOChangedCounter=0;
string IOChanged[1000];

ofstream OutputFile;
ifstream InputFile ; //object ifstream read files
ifstream IOFile;
string START;//begging of code segment	
string LAST;//end of code segment
string s;// line reading from file
string PC; // variable to store pc
int PcIndex; // to store index of pc array after cheecking it
int Counter=0; // number of byte for the whole machine
int CC=0; // for comp inst if==1 >, ==0 =, ==-1 <



//=================================================== Flags
// for addressing modes
bool Simple=0;
bool Indirect=0;
bool Imm=0;
// if==1 i am in a subroutine
bool SubFlag=0;
//=================================================== Registers
string A ="000000";
string X ="000000";
string L ="000000";
string B ="000000";
string S ="000000";
string T ="000000";
string SW="000000";
string F ="000000000000";
//=================================================== Instructions
void ADDR(string);
void SUBR(string);
void MULR(string);
void DIVR(string);
void CLEAR(string);
void RMO(string);
void ADD(string);
void SUB(string);
void MUL(string);
void DIV(string);
void LDA(string);
void LDCH(string);
void LDB(string);
void LDL(string);
void LDS(string);
void LDT(string);
void LDX(string);
void STA(string);
void STB(string);
void STL(string);
void STS(string);
void STSW(string);
void STT(string);
void STX(string);
void STCH(string);
void AND(string);
void OR(string);
void SHIFTL(string);
void SHIFTR(string);
void COMP(string);
void COMPR(string);
void TIX(string);
void TIXR(string);
void J(string);
void JSUB(string);
void RSUB(string);
void JEQ(string);
void JGT(string);
void JLT(string);
void TD(string);
void RD(string);
void WD(string);
// float
void MULF(string);
void STF(string );
void SUBF(string);
void ADDF(string);
void COMPF(string);
void DIVF(string);
void FIX(string);
void FLOAT(string);
void LDF(string);

string FltToStr( float );
double StrToDbl(string ); 
 string CalculateExponent(int , string);
string DblToStr (double);//dbl to string converter
void ReturnF(string , string);
string convert_to_float(string);
//end float
//===================================================
string Addition(string op1, string op2);
string Multplication(string op1, string op2);
string Subtracation(string op1, string op2);
string Division(string op1, string op2);
void Compare(string val1, string val2);

void ShowAll();// to print the values on output file
void Opcode(string);//determince opcode for the format and to know how much bytes to read
void OPCODETABLE();//m3ba jahez

string TAvalue(string);
void Data_Changed_Fun(string ,string );
void StrFilter(string );//filtering files 
void IOstrFilter(string );
string Fill( string );
string Fill_F( string );
string SignEX( string );
string IntToStr (int);//int to string converter 
int HexToInt (string);//hex to integer converter 
string IntToHex (int);//integer to hex converter 
int StrToInt(string ) ;//sting to int converter
void DelSpace (string &);//delete for space from the input file TABS
void Del_(string &);//del _ 
string HexToBin( string ) ;//hex to binary converter
string BinToHex( string ) ;//binary to hex converter
string ToUpper( string );//lower case to upper case
void TwoComp(string &);

//******************************************************************************************* MAIN
void main ()
{
	string nn;
	OPCODETABLE();

	InputFile.open("Input8.txt");
	if( InputFile.is_open())
	{
		StrFilter(s); // to filter the machine code and out it in codearray
	}

	else 
	{
		cout<<" Unable to open file ";
		goto L1;
	}

	
	IOFile.open("IO.txt");

	if( InputFile.is_open())
	{
		IOstrFilter(nn);
	}

	else 
	{
		cout<<" Unable to open file ";
		goto L1;
	}
	
	cout<< "\nThe Array Instruction is :-\n";
	for( int i=0 ; i<Counter;i++)
	{
		cout<< PcArray[i]<<"\t"<<CodeArray[i]<<endl;
	}


	cout<<endl<<START;
	cout<<endl<<LAST<<endl<<endl;

	PC = START;

	

    while ( HexToInt(PC) <= HexToInt(LAST) || SubFlag) 
	{
		for( int i=0 ; i<Counter;i++)
		{
			if (HexToInt(PcArray[i]) == HexToInt(PC))
			{
			PcIndex=i;
			break;
			}
		}
		
		Opcode(CodeArray[PcIndex]);
	}

	cout<<endl<<endl<<"!_!_! Registers :-";
	cout<<endl<<"A===>\t"<<A;
	cout<<endl<<"B===>\t"<<B;
	cout<<endl<<"L===>\t"<<L;
	cout<<endl<<"S===>\t"<<S;
	cout<<endl<<"T===>\t"<<T;
	cout<<endl<<"X===>\t"<<X;
	PC =Fill(PC);
	cout<<endl<<"PC==>\t"<<PC;
	cout<<endl<<"F===>\t"<<F;

	cout<<endl<<endl<<"!_!_! MEMORY :-";
	for( int i=0 ; i<Data_Changed_Counter;i++)
		{
			cout<<endl<<endl<<"Id==> "<<DataChangedId[i]<<"\t"<<"value = "<<DataChanged[i]<<endl;
			//cout<<endl<<endl<<"Id==> "<<PcArray[i]<<"\t"<<"value = "<<CodeArray[i]<<endl;
	}

	cout<<endl<<endl<<"!_!_! IO :-\n";
	for( int i=0 ; i<IOChangedCounter;i++)
		{
			cout<<IOChanged[i];
			//cout<<endl<<endl<<"Id==> "<<PcArray[i]<<"\t"<<"value = "<<CodeArray[i]<<endl;
		}

	OutputFile.open("Output.txt");
	
	if( OutputFile.is_open())
	{
		ShowAll();
	}

	else 
	{
		cout<<" Unable to open file ";
		goto L1;
	}
	

	L1:cout<<"\n\nPress any key to continue...";
	cin.get();

}
//*******************************************************************************************

void ShowAll()
{
	OutputFile<<endl<<endl<<"!_!_! Registers :-";
	OutputFile<<endl<<"A===>\t"<<A;
	OutputFile<<endl<<"B===>\t"<<B;
	OutputFile<<endl<<"L===>\t"<<L;
	OutputFile<<endl<<"S===>\t"<<S;
	OutputFile<<endl<<"T===>\t"<<T;
	OutputFile<<endl<<"X===>\t"<<X;
	PC =Fill(PC);
	OutputFile<<endl<<"PC==>\t"<<PC;
	OutputFile<<endl<<"F===>\t"<<F;

	OutputFile<<endl<<endl<<"!_!_! MEMORY :-";
	for( int i=0 ; i<Data_Changed_Counter;i++)
		{
			OutputFile<<endl<<endl<<"PC = "<<DataChangedId[i]<<"\t"<<"value = "<<DataChanged[i]<<endl;
	}

	OutputFile<<endl<<endl<<"!_!_! IO :-\n";
	for( int i=0 ; i<IOChangedCounter;i++)
		{
			OutputFile<<IOChanged[i];
		}

	OutputFile.close();
}
void Opcode(string opcode)


{
	int PcIndex;
	string instruction;
	opcode = HexToBin(opcode);
	opcode =opcode.substr(0,6);
	opcode =opcode+"00";
	opcode=BinToHex(opcode);
	

	int format;
						for(int i=0;i<59;i++)
						{
							if (OPCODE[i]==opcode)
							{
								format=FORMAT[i];
								break;
							}
						}

						for( int i=0 ; i<Counter;i++)
						{
							if (HexToInt(PcArray[i]) == HexToInt(PC))
							{
								PcIndex=i;
								break;
							}
						}

						if(format==1)
						{
							instruction=CodeArray[PcIndex];
							PC=IntToHex(HexToInt(PC)+1);
							PC=Fill(PC);

						}
						else if(format==2)
						{
							instruction=CodeArray[PcIndex];
							instruction=instruction+CodeArray[PcIndex+1];
							PC=IntToHex(HexToInt(PC)+2);
							PC=Fill(PC);

							
						}

						else if(format==3)
						{
							instruction=CodeArray[PcIndex];
							instruction=instruction+CodeArray[PcIndex+1];

							string e =HexToBin(instruction);
							 e=e.substr(11,1);
							if ( e=="0")
							{
								instruction=instruction+CodeArray[PcIndex+2];
								PC=IntToHex(HexToInt(PC)+3);
							    PC=Fill(PC);

							
							}
							else if ( e=="1")
							{
							instruction=instruction+CodeArray[PcIndex+2];
							instruction=instruction+CodeArray[PcIndex+3];
							PC=IntToHex(HexToInt(PC)+4);
							PC=Fill(PC);

							} 
							
						}



	if (opcode=="90")
	{
		ADDR(instruction);
	}
	else
	if(opcode=="94")
		{
			SUBR(instruction);
		}
	else
	if(opcode=="98")
		{
			MULR(instruction);
		}
	else
	if(opcode=="9C")
		{
			DIVR(instruction);
		}
	else
	if(opcode=="B4")
		{
			CLEAR(instruction);
		}
	else
	if(opcode=="AC")
		{
			RMO(instruction);
		}
	else
	if(opcode=="18")
		{
			ADD(instruction);
		}
	else
	if(opcode=="1C")
		{
			SUB(instruction);
		}
	else
	if(opcode=="20")
		{
			MUL(instruction);
		}
	else
	if(opcode=="24")
		{
			DIV(instruction);
		}
	else
	if(opcode=="00")
		{
			LDA(instruction);
		}
	else
	if(opcode=="68")
		{
			LDB(instruction);
		}
	else
	if(opcode=="08")
		{
			LDL(instruction);
		}
	else
	if(opcode=="6C")
		{
			LDS(instruction);
		}
	else
	if(opcode=="74")
		{
			LDT(instruction);
		}
	else
	if(opcode=="04")
		{
			LDX(instruction);
		}
	else
	if(opcode=="0C")
		{
			STA(instruction);
		}
	else
	if(opcode=="78")
		{
			STB(instruction);
		}
	else
	if(opcode=="14")
		{
			STL(instruction);
		}
	else
	if(opcode=="7C")
		{
			STS(instruction);
		}
	else
	if(opcode=="E8")
		{
			STSW(instruction);
		}
	else
	if(opcode=="84")
		{
			STT(instruction);
		}
	else
	if(opcode=="10")
		{
			STX(instruction);
		}
	else
	if(opcode=="50")
		{
			LDCH(instruction);
		}
	else
	if(opcode=="54")
		{
			STCH(instruction);
		}
	else
	if(opcode=="40")
		{
			AND(instruction);
		}
	else
	if(opcode=="44")
		{
			OR(instruction);
		}
	else
	if(opcode=="A4")
		{
			SHIFTL(instruction);
		}
	else
	if(opcode=="A8")
		{
			SHIFTR(instruction);
		}
	else
	if(opcode=="3C")
		{
			J(instruction);
		}
	else
	if(opcode=="30")
		{
			JEQ(instruction);
		}
	else
	if(opcode=="34")
		{
			JGT(instruction);
		}
	else
	if(opcode=="38")
		{
			JLT(instruction);
		}
	else
	if(opcode=="48")
		{
			JSUB(instruction);
		}
	else
	if(opcode=="4C")
		{
			RSUB(instruction);
		}
	else
	if(opcode=="28")
		{
			COMP(instruction);
		}
	else
	if(opcode=="2C")
		{
			TIX(instruction);
		}
	else
	if(opcode=="B8")
		{
			TIXR(instruction);
		}
	else
	if(opcode=="A0")
		{
			COMPR(instruction);
		}
	else
	if(opcode=="E0")
		{
			TD(instruction);
		}
	else
	if(opcode=="D8")
		{
			RD(instruction);
		}
	else
	if(opcode=="DC")
		{
			WD(instruction);
		}
	else
	if(opcode=="88")
		{
			COMPF(instruction);
		}
	else
	if(opcode=="64")
		{
			DIVF(instruction);
		}
	else
	if(opcode=="C4")
		{
			FIX(instruction);
		}
	else
	if(opcode=="C0")
		{
			FLOAT(instruction);
		}
	else
	if(opcode=="70")
		{
			LDF(instruction);
		}
	else
	if(opcode=="60")
		{
			MULF(instruction);
		}
	else
	if(opcode=="80")
		{
			STF(instruction);
		}
	else
	if(opcode=="5C")
		{
			SUBF(instruction);
		}
		else
	if(opcode=="58")
		{
			ADDF(instruction);
		}

	else
		cout<<endl<<PC<<endl;

}
void IOstrFilter(string s)
{
	int hex;
	char c;

			while ( !IOFile.eof())
	{
		IOFile.get(c);
		hex =c ;
		s =IntToHex(hex);
		if(s.length()==1)
			s="0"+s;
		IOMem[IOcounter++]=s;
	
	}
			IOMem[IOcounter-1]="00";
			
}
void StrFilter(string s)
{
	
		while ( !InputFile.eof())
		{
			getline(InputFile,s);

			if(  s == "")
			continue;
		if(  s == "	")
			continue;

		if(  s.find("//") != string::npos || s.find(";") != string::npos ||s.find(";;") != string::npos || s.find("!_!_!") != string::npos)
		{
			if (s.find("START")!= string::npos)
			{
				int pos = s.find("="); 
				s=s.substr(pos+1);

				DelSpace(s);

				START = s;
				PC=START;

				continue;
 
			}
			else 
				if (s.find("LAST")!= string::npos)
			{
				int pos = s.find("=");
				s = s.substr(pos+1);

				DelSpace(s);

				LAST = s;
				continue;
			}
				else 
				if(s.find("!_!_!") >2)
				{
					int pos = s.find("!_!_!");
					s=s.substr(0,pos-1);
					if(  !(s.find("0")!= string::npos || s.find("1")!= string::npos || s.find("2")!= string::npos || s.find("3")!= string::npos 
						|| s.find("4")!= string::npos || s.find("5")!= string::npos || s.find("6")!= string::npos || s.find("7")!= string::npos 
						|| s.find("8")!= string::npos || s.find("9")!= string::npos || s.find("A")!= string::npos || s.find("B")!= string::npos 
						|| s.find("C")!= string::npos || s.find("D")!= string::npos || s.find("E")!= string::npos || s.find("F")!= string::npos))
						continue;
				}
					else
						continue;

		}

						DelSpace(s);
						Del_(s);
						DelSpace(s);
						Del_(s);
						DelSpace(s);
						Del_(s);
//===========================================================================================
///==========================================================================================
						
						for(int pos=0 ; pos<=s.length()-2 ; pos=pos+2)
						{
							CodeArray[Counter]=s.substr(pos,2);
							PcArray[Counter++]=PC;
							PC = IntToHex(HexToInt(PC)+1);
						}
						
	
		}

}
void OPCODETABLE()
{
	OPCODE[0]="60"; FORMAT[0]=3;  OPCODE[1]="98"; FORMAT[1]=2;  OPCODE[2]="C8"; FORMAT[2]=1;  OPCODE[3]="44"; FORMAT[3]=3;
	OPCODE[4]="D8"; FORMAT[4]=3;  OPCODE[5]="AC"; FORMAT[5]=2;  OPCODE[6]="4C"; FORMAT[6]=3;  OPCODE[7]="A4"; FORMAT[7]=2;
	OPCODE[8]="A8"; FORMAT[8]=2;  OPCODE[9]="F0"; FORMAT[9]=1;  OPCODE[10]="EC"; FORMAT[10]=3; OPCODE[11]="0C"; FORMAT[11]=3;
	OPCODE[12]="78"; FORMAT[12]=3; OPCODE[13]="54"; FORMAT[13]=3; OPCODE[14]="80"; FORMAT[14]=3; OPCODE[15]="D4"; FORMAT[15]=3;
	OPCODE[16]="14"; FORMAT[16]=3; OPCODE[17]="7C"; FORMAT[17]=3; OPCODE[18]="E8"; FORMAT[18]=3; OPCODE[19]="84"; FORMAT[19]=3;
	OPCODE[20]="10"; FORMAT[20]=3; OPCODE[21]="1C"; FORMAT[21]=3; OPCODE[22]="5C"; FORMAT[22]=3; OPCODE[23]="94"; FORMAT[23]=2;
	OPCODE[24]="B0"; FORMAT[24]=2; OPCODE[25]="E0"; FORMAT[25]=3; OPCODE[26]="F8"; FORMAT[26]=1; OPCODE[27]="2C"; FORMAT[27]=3;
	OPCODE[28]="B8"; FORMAT[28]=2; OPCODE[29]="DC"; FORMAT[29]=3; OPCODE[30]="18"; FORMAT[30]=3; OPCODE[31]="58"; FORMAT[31]=3;
	OPCODE[32]="90"; FORMAT[32]=2; OPCODE[33]="40"; FORMAT[33]=3; OPCODE[34]="B4"; FORMAT[34]=2; OPCODE[35]="28"; FORMAT[35]=3;
	OPCODE[36]="88"; FORMAT[36]=3; OPCODE[37]="A0"; FORMAT[37]=2; OPCODE[38]="24"; FORMAT[38]=3; OPCODE[39]="64"; FORMAT[39]=3;
	OPCODE[40]="9C"; FORMAT[40]=2; OPCODE[41]="C4"; FORMAT[41]=1; OPCODE[42]="C0"; FORMAT[42]=1; OPCODE[43]="F4"; FORMAT[43]=1;
	OPCODE[44]="3C"; FORMAT[44]=3; OPCODE[45]="30"; FORMAT[45]=3; OPCODE[46]="34"; FORMAT[46]=3; OPCODE[47]="38"; FORMAT[47]=3;
	OPCODE[48]="48"; FORMAT[48]=3; OPCODE[49]="00"; FORMAT[49]=3; OPCODE[50]="68"; FORMAT[50]=3; OPCODE[51]="50"; FORMAT[51]=3;
	OPCODE[52]="70"; FORMAT[52]=3; OPCODE[53]="08"; FORMAT[53]=3; OPCODE[54]="6C"; FORMAT[54]=3; OPCODE[55]="74"; FORMAT[55]=3;
	OPCODE[56]="04"; FORMAT[56]=3; OPCODE[57]="D0"; FORMAT[57]=3; OPCODE[58]="20"; FORMAT[58]=3;
}
void Del_(string &s)
{
	for ( int i=0 ; i < s.length() ; i++)
				{
					int pos;

					if (s.find("_")!= string::npos)
					{
						pos= s.find("_");
						s=s.erase(pos,1);
					}
					
				}
	
}
void  DelSpace(string &s)
{
	int pos;
	for ( int i=0 ; i<s.length();i++)
				{
					if (s.find(" ")!= string::npos)
					{
						pos= s.find(" ");
						s=s.erase(pos,1);
					}
					
				}
	for ( int i=0 ; i<s.length();i++)
				{
					if (s.find("	")!= string::npos)
					{
						pos= s.find("	");
						s=s.erase(pos,1);
					}
					
				}
}
string IntToHex( int i )
  {
	 std::ostringstream Hex;
      Hex << std::hex << i;
	  //cout<<hex<<showbase<<10;
     string s = Hex.str();
	 s= ToUpper(s);  
	  return s;
  }
string IntToStr( int n )
  {
  std::ostringstream result;
  result << n;
  return result.str();
}
int HexToInt( string s )
  {
	  int i;
	  stringstream convert ;
	  convert= (stringstream)s;
	  convert>> std::hex >> i;
	  
	  return i;
  }
int StrToInt(string in) 
{    
	int ret_val = 0;    
std::stringstream sstr(in);    
sstr >> ret_val;    
/* (sstr.fail()) 
{ //Check if conversion worked       
	throw std::exception(std::string("Failed conversion for: " + in).c_str());  
}   */ 
return ret_val;
}
string HexToBin( string hexNumber) 
{ 
   std::string binaryNum; 
    
   for (int i = 0; i <= hexNumber.length() ; i++) 
   { 
      if (hexNumber.substr(i,1) == "0") 
         binaryNum  += "0000"; 
      if (hexNumber.substr(i,1) == "1") 
         binaryNum  += "0001"; 
      if (hexNumber.substr(i,1) == "2") 
         binaryNum  += "0010"; 
      if (hexNumber.substr(i,1) == "3") 
         binaryNum  += "0011"; 
      if (hexNumber.substr(i,1) == "4") 
         binaryNum  += "0100"; 
      if (hexNumber.substr(i,1) == "5") 
         binaryNum  += "0101"; 
      if (hexNumber.substr(i,1) == "6") 
         binaryNum  += "0110"; 
      if (hexNumber.substr(i,1) == "7") 
         binaryNum  += "0111"; 
      if (hexNumber.substr(i,1) == "8") 
         binaryNum  += "1000"; 
      if (hexNumber.substr(i,1) == "9") 
         binaryNum  += "1001"; 
      if (hexNumber.substr(i,1) == "a"||hexNumber.substr(i,1) == "A") 
         binaryNum  += "1010"; 
      if (hexNumber.substr(i,1) == "b"||hexNumber.substr(i,1) == "B") 
         binaryNum  += "1011"; 
      if (hexNumber.substr(i,1) == "c"||hexNumber.substr(i,1) == "C") 
         binaryNum  += "1100"; 
      if (hexNumber.substr(i,1) == "d"||hexNumber.substr(i,1) == "D") 
         binaryNum  += "1101"; 
      if (hexNumber.substr(i,1) == "e"||hexNumber.substr(i,1) == "E") 
         binaryNum  += "1110"; 
      if (hexNumber.substr(i,1) == "f"||hexNumber.substr(i,1) == "F") 
         binaryNum  += "1111"; 
   } 
   return binaryNum; 
} 
string BinToHex( string BinNum) 
{ 
   std::string HexNum; 
    
   for (int i = 0; i <= BinNum.length() ; i=i+4) 
   { 
      if (BinNum.substr(i,4) == "0000") 
         HexNum  += "0"; 
      if (BinNum.substr(i,4) == "0001") 
         HexNum  += "1"; 
      if (BinNum.substr(i,4) == "0010") 
         HexNum  += "2"; 
      if (BinNum.substr(i,4) == "0011") 
         HexNum  += "3"; 
      if (BinNum.substr(i,4) == "0100") 
         HexNum  += "4"; 
      if (BinNum.substr(i,4) == "0101") 
         HexNum  += "5"; 
      if (BinNum.substr(i,4) == "0110") 
         HexNum  += "6"; 
      if (BinNum.substr(i,4) == "0111") 
         HexNum  += "7"; 
      if (BinNum.substr(i,4) == "1000") 
         HexNum  += "8"; 
      if (BinNum.substr(i,4) == "1001") 
         HexNum  += "9"; 
      if (BinNum.substr(i,4) == "1010") 
         HexNum  += "A"; 
      if (BinNum.substr(i,4) == "1011") 
         HexNum  += "B"; 
      if (BinNum.substr(i,4) == "1100") 
         HexNum  += "C"; 
      if (BinNum.substr(i,4) == "1101") 
         HexNum  += "D"; 
      if (BinNum.substr(i,4) == "1110") 
         HexNum  += "E"; 
      if (BinNum.substr(i,4) == "1111") 
         HexNum  += "F"; 
   } 
   return HexNum; 
} 
string ToUpper( string s) 
{ 
	string Uper;
    
   for (int i = 0; i <= s.length() ; i++) 
   {

	   if (s.substr(i,1) == "0") 
         Uper  += "0"; 
	   if (s.substr(i,1) == "1") 
         Uper  += "1"; 
	   if (s.substr(i,1) == "2") 
         Uper  += "2"; 
	   if (s.substr(i,1) == "3") 
         Uper  += "3"; 
	   if (s.substr(i,1) == "4") 
         Uper  += "4"; 
	   if (s.substr(i,1) == "5") 
         Uper  += "5"; 
	   if (s.substr(i,1) == "6") 
         Uper  += "6"; 
	   if (s.substr(i,1) == "7") 
         Uper  += "7"; 
	   if (s.substr(i,1) == "8") 
         Uper  += "8"; 
	   if (s.substr(i,1) == "9") 
         Uper  += "9"; 
	   if (s.substr(i,1) == "a") 
         Uper  += "A"; 
	   if (s.substr(i,1) == "b") 
         Uper  += "B"; 
	   if (s.substr(i,1) == "c") 
         Uper  += "C"; 
	   if (s.substr(i,1) == "d") 
         Uper  += "D"; 
	   if (s.substr(i,1) == "e") 
         Uper  += "E"; 
	   if (s.substr(i,1) == "f") 
         Uper  += "F"; 
	   if (s.substr(i,1) == "A") 
         Uper  += "A";
	   if (s.substr(i,1) == "B") 
         Uper  += "B"; 
	   if (s.substr(i,1) == "C") 
         Uper  += "C"; 
	   if (s.substr(i,1) == "D") 
         Uper  += "D"; 
	   if (s.substr(i,1) == "E") 
         Uper  += "E"; 
	   if (s.substr(i,1) == "F") 
         Uper  += "F"; 
      
   }
   return Uper;
} 
void TwoComp(string &s)
{
	int Comp = HexToInt(s);
	Comp=~Comp+1;

	s= IntToHex(Comp);
	s=s.substr(2,6);
}
string Fill( string s)
{
	if(s.length()==0)
		s="000000";
	else if (s.length()==1)
		s="00000"+s;
	else if (s.length()==2)
		s="0000"+s;
	else if (s.length()==3)
		s="000"+s;
	else if (s.length()==4)
		s="00"+s;
	else if (s.length()==5)
		s="0"+s;
	return s;
}
string Fill_F( string s)
{
	if(s.length()==0)
		s="FFFFFF";
	else if (s.length()==1)
		s="FFFFF"+s;
	else if (s.length()==2)
		s="FFFF"+s;
	else if (s.length()==3)
		s="FFF"+s;
	else if (s.length()==4)
		s="FF"+s;
	else if (s.length()==5)
		s="F"+s;
	return s;
}
string SignEX( string s)
{
	s= HexToBin(s);
	if (s[0]=='0')
	{
	s= BinToHex(s);
	if(s.length()==0)
		s="000000";
	else if (s.length()==1)
		s="00000"+s;
	else if (s.length()==2)
		s="0000"+s;
	else if (s.length()==3)
		s="000"+s;
	else if (s.length()==4)
		s="00"+s;
	else if (s.length()==5)
		s="0"+s;
	}
	else if (s[0]=='1')
	{
		s= BinToHex(s);
	 if (s.length()==1)
		s="FFFFF"+s;
	else if (s.length()==2)
		s="FFFF"+s;
	else if (s.length()==3)
		s="FFF"+s;
	else if (s.length()==4)
		s="FF"+s;
	else if (s.length()==5)
		s="F"+s;
	}

	return s;
}
string TAvalue(string instruction)
{
		string ins=HexToBin(instruction);

		string ni = ins.substr(6,2);
		string x = ins.substr(8,1);
		string b = ins.substr(9,1);
		string p = ins.substr(10,1);
		string e = ins.substr(11,1);
		string nix = ins.substr(6,3);
		string nixbpe = ins.substr(6,6);
		string address=BinToHex(ins.substr(12,instruction.length()-12));
		string disp=BinToHex(ins.substr(12,12));
		string TA;

		if(nixbpe == "110000")
		{
			Simple=1; Indirect=0;  Imm=0;
			disp=SignEX(disp);
			TA = disp;
		}
		else if(nixbpe == "110001")
		{
			Simple=1; Indirect=0;  Imm=0;
		    address=SignEX(address);
			TA=address;
		}
		else if(nixbpe == "110010")
		{
			Simple=1; Indirect=0;  Imm=0;
			disp=SignEX(disp);
			TA=Addition(disp,PC);
		}
		else if(nixbpe == "110100")
		{
			Simple=1; Indirect=0;  Imm=0;
			
			TA=IntToHex(HexToInt(disp)+HexToInt(B));
		}

		else if(nixbpe == "111000")
		{
			Simple=1; Indirect=0;  Imm=0;
			
			TA=IntToHex(HexToInt(disp)+HexToInt(X));
		}

		else if(nixbpe == "111001")
		{
			Simple=1; Indirect=0;  Imm=0;
			
			TA=IntToHex(HexToInt(address)+HexToInt(X));
		}

		else if(nixbpe == "111010")
		{
			Simple=1; Indirect=0;  Imm=0;
			disp=SignEX(disp);
			string temp =Addition(disp,PC);
			TA=Addition(temp,X);
		}
		else if(nixbpe == "111100")
		{
			Simple=1; Indirect=0;  Imm=0;
			
			TA=IntToHex(HexToInt(disp)+HexToInt(X)+HexToInt(B));
		}
		else if(nix == "000")
		{
			Simple=1; Indirect=0;  Imm=0;
			disp=HexToBin(disp);
			disp= b+p+e+disp;
			disp="0"+disp;
			disp=BinToHex(disp);
			
			TA=IntToHex(HexToInt(disp));
		}
		else if(nix == "001")
		{
			Simple=1; Indirect=0;  Imm=0;
			disp=HexToBin(disp);
			disp= b+p+e+disp;
			disp="0"+disp;
			disp=BinToHex(disp);

			TA=IntToHex(HexToInt(disp)+HexToInt(X));
		}

		else if(nixbpe == "100000")
		{
			Simple=0; Indirect=1;  Imm=0;
			disp=SignEX(disp);
			TA=disp;
		}
		else if(nixbpe == "100001")
		{
			Simple=0; Indirect=1;  Imm=0;
			address=SignEX(address);
			TA=address;
		}

		else if(nixbpe == "100010")
		{
			Simple=0; Indirect=1;  Imm=0;
			disp=SignEX(disp);
			TA=Addition(PC,disp);
		}
		else if(nixbpe == "100100")
		{
			Simple=0; Indirect=1;  Imm=0;
			
			TA=IntToHex(HexToInt(disp)+HexToInt(B));
		}

		else if(nixbpe == "010000")
		{
			Simple=0; Indirect=0;  Imm=1;
			disp=SignEX(disp);
			TA=disp;
		}
		else if(nixbpe == "010001")
		{
			Simple=0; Indirect=0;  Imm=1;
			address=SignEX(address);
			TA=address;
		}

		else if(nixbpe == "010010")
		{
			Simple=0; Indirect=0;  Imm=1;
			disp=SignEX(disp);
			TA=Addition(PC,disp);
		}

		else if(nixbpe == "010100")
		{
			Simple=0; Indirect=0;  Imm=1;

			TA=IntToHex(HexToInt(disp)+HexToInt(B));
		}

		return TA;
}
void Data_Changed_Fun(string ID,string Data)
{
	int IdIndex=-1 ;
	for (int i=0;i<Data_Changed_Counter;i++)
	{
		if (HexToInt(DataChangedId[i]) == HexToInt(ID))
				{
					IdIndex=i;
					DataChanged[IdIndex]=Data;
					break;
				}
	}

	if(IdIndex==-1)
		{
			DataChanged[Data_Changed_Counter]=Data;
			ID=Fill(ID);
			DataChangedId[Data_Changed_Counter++]=ID;
		}
	
}


string Addition(string op1, string op2)
{
	op1=SignEX(op1);
	op2=SignEX(op2);
	 string BinReg1= HexToBin(op1); 
	 string BinReg2= HexToBin(op2);
	 string TempReg;
	 if ( BinReg1[0]=='0' && BinReg2[0]=='0')
	 {
		 op2=IntToHex(HexToInt(op1)+HexToInt(op2));
		 op2=Fill(op2);
	 }
	  else if ( BinReg1[0]=='0' && BinReg2[0]=='1')
	 {
		 TwoComp(op2);
		 if (op2>op1)
		 {
		 TempReg=IntToHex(HexToInt(op1)-HexToInt(op2));
		 op2=TempReg.substr(2,6);
		 }
		 else if(op2 <= op1)
		 {
			 TempReg=IntToHex(HexToInt(op1)-HexToInt(op2));
			 op2=Fill(TempReg);
		 }
	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='0')
	 {
		 TwoComp(op1);
		 if (op1>op2)
		 {
		 TempReg=IntToHex(HexToInt(op2)-HexToInt(op1));
		 op2=TempReg.substr(2,6);
		 }
		 else if(op1<=op2)
		 {
			 TempReg=IntToHex(HexToInt(op2)-HexToInt(op1));
			 op2=Fill(TempReg);
		 }
	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='1')
	 {
		 TwoComp(op1);TwoComp(op2);
		 TempReg=IntToHex(HexToInt(op1)+HexToInt(op2));
		 TwoComp(TempReg);
		 op2= TempReg;
		
		
	 } 
	   return op2;
}
string Subtraction(string op1, string op2)
{
	op1=SignEX(op1);
	op2=SignEX(op2);

	string BinReg1= HexToBin(op1);
	 string BinReg2= HexToBin(op2);
	 string TempReg;
	 if ( BinReg1[0]=='0' && BinReg2[0]=='0')
	 {
		  if (op2>=op1)
		 {
		 op2=IntToHex(HexToInt(op2)-HexToInt(op1));
		 op2=Fill(op2);
		  }
		  else if (op1>op2)
		 {
			 TempReg=IntToHex(HexToInt(op2)-HexToInt(op1));
			 op2=TempReg.substr(2,6);
		  }
	 }
	  else if ( BinReg1[0]=='0' && BinReg2[0]=='1')
	 {
		 TwoComp(op2);
		 TempReg=IntToHex(HexToInt(op2)+HexToInt(op1));
		 TwoComp(TempReg);
		 op2=TempReg;

	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='0')
	 {
		 TwoComp(op1);
		 TempReg=IntToHex(HexToInt(op2)+HexToInt(op1));
		 op2=Fill(TempReg);
	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='1')
	 {
		 TwoComp(op1);TwoComp(op2);
		 if (op1>op2)
		 {
		 TempReg=IntToHex(HexToInt(op1)-HexToInt(op2));
		 op2=Fill(TempReg);
		 }
		 else if(op1<op2)
		 {
			 TempReg=IntToHex(HexToInt(op2)-HexToInt(op1));
			 TwoComp(TempReg);
			 op2=TempReg;
		 }
		  else if(op1==op2)
		 {
			 TempReg=IntToHex(HexToInt(op2)-HexToInt(op1));
			 op2=Fill(TempReg);
		 }
		
	 } 
	  return op2;
	  
}
string Multiplication(string op1, string op2)
{
	op1=SignEX(op1);
	op2=SignEX(op2);
	  	  	 string BinReg1= HexToBin(op1);
	 string BinReg2= HexToBin(op2);
	 string TempReg;
	 if ( BinReg1[0]=='0' && BinReg2[0]=='0')
	 {
		 op2=IntToHex(HexToInt(op2)*HexToInt(op1));
		 op2=Fill(op2);
	 }
	  else if ( BinReg1[0]=='0' && BinReg2[0]=='1')
	 {
		 TwoComp(op2);
		 TempReg=IntToHex(HexToInt(op2)*HexToInt(op1));
		 TwoComp(TempReg);
		 op2=TempReg;

	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='0')
	 {
		 TwoComp(op1);
		 TempReg=IntToHex(HexToInt(op2)*HexToInt(op1));
		 TwoComp(TempReg);
		 op2=TempReg;
	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='1')
	 {
		 TwoComp(op1);TwoComp(op2);
		 TempReg=IntToHex(HexToInt(op2)*HexToInt(op1));
		 op2=TempReg;
		 op2=Fill(op2);
		
	 } 
	  
	   return op2;
}
string Division(string op1, string op2)
{
	op1=SignEX(op1);
	op2=SignEX(op2);

	 string BinReg1= HexToBin(op1);
	 string BinReg2= HexToBin(op2);
	 string TempReg;
	 if ( BinReg1[0]=='0' && BinReg2[0]=='0')
	 {
		 op2=IntToHex(HexToInt(op2)/HexToInt(op1));
		 op2=Fill(op2);
	 }
	  else if ( BinReg1[0]=='0' && BinReg2[0]=='1')
	 {
		 TwoComp(op2);
		 TempReg=IntToHex(HexToInt(op2)/HexToInt(op1));
		 TwoComp(TempReg);
		 op2=TempReg;

	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='0')
	 {
		 TwoComp(op1);
		 TempReg=IntToHex(HexToInt(op2)/HexToInt(op1));
		 TwoComp(TempReg);
		 op2=TempReg;
	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='1')
	 {
		 TwoComp(op1);TwoComp(op2);
		 TempReg=IntToHex(HexToInt(op2)/HexToInt(op1));
		 op2=TempReg;
		 op2=Fill(op2);
		
	 } 

	   return op2;
}
void Compare(string val1, string val2)
{
	val1=SignEX(val1);
	val2=SignEX(val2);
	string BinReg1= HexToBin(val1);
	 string BinReg2= HexToBin(val2);
	 int R1,R2;
	 if ( BinReg1[0]=='0' && BinReg2[0]=='0')
	 {
		 R1=HexToInt(val1);
		 R2=HexToInt(val2);
	 }
	  else if ( BinReg1[0]=='0' && BinReg2[0]=='1')
	 {
		 TwoComp(val2);
		 R1=HexToInt(val1);
		 R2=(HexToInt(val2)*-1);

	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='0')
	 {
		 TwoComp(val1);
		 R1=(HexToInt(val1)*-1);
		 R2=HexToInt(val2);
	 }
	  else if ( BinReg1[0]=='1' && BinReg2[0]=='1')
	 {
		  TwoComp(val1);TwoComp(val2);
		 R1=(HexToInt(val1)*-1);
		 R2=(HexToInt(val2)*-1);
		
	 } 

				if( R1>R2)
				{
					CC=1; //  A Greater Than Memory
				}
				else if( R1<R2)
				{
					CC=-1; //  A Less Than Memory
				}
				else if( R1==R2)
				{
					CC=0; //  A equal to Memory
				}
}
//===================== Functions ======================

void ADDR (string inst)  
{
	string instruction =inst;
	
	string s1=instruction.substr(2,1);
	string s2=instruction.substr(3,1);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	*reg2= Addition(*reg1,*reg2);

}
void SUBR (string inst)  
{
	string instruction =inst;
	//00_00 
	string s1=instruction.substr(2,1);
	string s2=instruction.substr(3,1);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	  	*reg2= Subtraction(*reg1,*reg2);
	  

}
void MULR (string inst)  
{
	string instruction =inst;
	//00_00 
	string s1=instruction.substr(2,1);
	string s2=instruction.substr(3,1);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;
	 *reg2=Multiplication(*reg1,*reg2);

}
void DIVR (string inst)  
{
	string instruction =inst;
	//00_00 
	string s1=instruction.substr(2,1);
	string s2=instruction.substr(3,1);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;


	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	*reg2= Division(*reg1,*reg2);

}
void CLEAR (string inst)  
{
	string instruction =inst;
	//00_00 
	string s1=instruction.substr(2,1);
	string s2=instruction.substr(3,1);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	  *reg1="000000";
	  *reg1=Fill(*reg1);

}
void RMO (string inst)  
{
	string instruction =inst;
	//00_00 
	string s1=instruction.substr(2,1);
	string s2=instruction.substr(3,1);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	  *reg2=*reg1;
	  //*reg2=Fill(*reg2);

}

void LDA(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
			} 
			else
			{
				
					A=CodeArray[PcIndex++];
					A=CodeArray[PcIndex++]+A;
					A=CodeArray[PcIndex]+A;
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
			} 
			else
			{
					A=CodeArray[PcIndex++];
					A=CodeArray[PcIndex++]+A;
					A=CodeArray[PcIndex]+A;

			}
		}
		
	
		else if(Imm )
		{
			A=TA;
			A=Fill(A);

		}


}
void LDCH(string instruction)
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				A = A.substr(0,4);
				A=A+"00";
			} 
			else
			{
				
				    A = A.substr(0,4);
					A=A+CodeArray[PcIndex];
					
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				A = A.substr(0,4);
				A=A+"00";
			} 
			else
			{
					A = A.substr(0,4);
					A=A+CodeArray[PcIndex];

			}
		}
		
	
		else if(Imm )
		{
			
			TA = TA.substr(12,2);
			A = A.substr(0,4);
			A = A+TA;
			A = Fill(A);

		}


}
void LDB(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				A="000000";
			} 
			else
			{
				
					B=CodeArray[PcIndex++];
					B=CodeArray[PcIndex++]+B;
					B=CodeArray[PcIndex]+B;
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				B="000000";
			} 
			else
			{
					B=CodeArray[PcIndex++];
					B=CodeArray[PcIndex++]+B;
					B=CodeArray[PcIndex]+B;

			}
		}
		
	
		else if(Imm )
		{
			B=TA;
			B=Fill(B);

		}


}
void LDL(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				L="000000";
			} 
			else
			{
				
					L=CodeArray[PcIndex++];
					L=CodeArray[PcIndex++]+L;
					L=CodeArray[PcIndex]+L;
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				L="000000";
			} 
			else
			{
					L=CodeArray[PcIndex++];
					L=CodeArray[PcIndex++]+L;
					L=CodeArray[PcIndex]+L;

			}
		}
		
	
		else if(Imm )
		{
			L=TA;
			L=Fill(L);

		}


}
void LDS(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				S="000000";
			} 
			else
			{
				
					S=CodeArray[PcIndex++];
					S=CodeArray[PcIndex++]+S;
					S=CodeArray[PcIndex]+S;
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				S="000000";
			} 
			else
			{
					S=CodeArray[PcIndex++];
					S=CodeArray[PcIndex++]+S;
					S=CodeArray[PcIndex]+S;

			}
		}
		
	
		else if(Imm )
		{
			S=TA;
			S=Fill(S);

		}


}
void LDT(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				T="000000";
			} 
			else
			{
				
					T=CodeArray[PcIndex++];
					T=CodeArray[PcIndex++]+T;
					T=CodeArray[PcIndex]+T;
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				T="000000";
			} 
			else
			{
					T=CodeArray[PcIndex++];
					T=CodeArray[PcIndex++]+T;
					T=CodeArray[PcIndex]+T;

			}
		}
		
	
		else if(Imm )
		{
			T=TA;
			T=Fill(T);

		}


}
void LDX(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				X="000000";
			} 
			else
			{
				
					X=CodeArray[PcIndex++];
					X=CodeArray[PcIndex++]+X;
					X=CodeArray[PcIndex]+X;
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				X="000000";
			} 
			else
			{
					X=CodeArray[PcIndex++];
					X=CodeArray[PcIndex++]+X;
					X=CodeArray[PcIndex]+X;

			}
		}
		
	
		else if(Imm )
		{
			X=TA;
			X=Fill(X);

		}


}

void STA(string instruction)       
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=A.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = A.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=A.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex++]=A.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = A.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=A.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=A.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = A.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=A.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
			} 
			else
			{
					string ID,Data;

				Data=CodeArray[PcIndex++]=A.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = A.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=A.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}

}
void STB(string instruction)       
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=B.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = B.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=B.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex++]=B.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = B.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=B.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=B.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = B.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=B.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
			} 
			else
			{
					string ID,Data;

				Data=CodeArray[PcIndex++]=B.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = B.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=B.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}

}
void STCH(string instruction)
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=A.substr(4,2);
				ID=PcArray[PcIndex] =TA;
				Data_Changed_Fun(ID,Data);
				Counter=Counter+1;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex]=A.substr(4,2);
				ID=PcArray[PcIndex] =TA;
				Data_Changed_Fun(ID,Data);

			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=A.substr(4,2);
				ID=PcArray[PcIndex] =TA;
				Data_Changed_Fun(ID,Data);
				Counter=Counter+1;
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex]=A.substr(4,2);
				ID=PcArray[PcIndex] =TA;
				Data_Changed_Fun(ID,Data);

			}
		}

}
void STL(string instruction)       
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=L.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = L.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=L.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex++]=L.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = L.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=L.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=L.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = L.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=L.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
			} 
			else
			{
					string ID,Data;

				Data=CodeArray[PcIndex++]=L.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = L.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=L.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}

}
void STS(string instruction)       
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=S.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = S.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=S.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex++]=S.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = S.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=S.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=S.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = S.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=S.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
			} 
			else
			{
					string ID,Data;

				Data=CodeArray[PcIndex++]=S.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = S.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=S.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}

}
void STSW(string instruction)       
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=SW.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = SW.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=SW.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex++]=SW.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = SW.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=SW.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=SW.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = SW.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=SW.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
			} 
			else
			{
					string ID,Data;

				Data=CodeArray[PcIndex++]=SW.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = SW.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=SW.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}

}
void STT(string instruction)       
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=T.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = T.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=T.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex++]=T.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = T.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=T.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=T.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = T.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=T.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
			} 
			else
			{
					string ID,Data;

				Data=CodeArray[PcIndex++]=T.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = T.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=T.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}

}
void STX(string instruction)       
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=X.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = X.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=X.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex++]=X.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = X.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=X.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=X.substr(4,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = X.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=X.substr(0,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+3;
			} 
			else
			{
					string ID,Data;

				Data=CodeArray[PcIndex++]=X.substr(4,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = X.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=X.substr(0,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);
			}
		}

}

void ADD(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				
				string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A=Addition(Mem,A);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A=Addition(Mem,A);

			}
		}
		
	
		else if(Imm )
		{
			A=Addition(TA,A);

		}


}
void SUB(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				
				string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A=Subtraction(Mem,A);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A=Subtraction(Mem,A);

			}
		}
		
	
		else if(Imm )
		{
			A=Subtraction(TA,A);

		}


}
void MUL(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				
				string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A=Multiplication(Mem,A);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A=Multiplication(Mem,A);

			}
		}
		
	
		else if(Imm )
		{
			A=Multiplication(TA,A);

		}


}
void DIV(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				
				string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A=Division(Mem,A);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A=Division(Mem,A);

			}
		}
		
	
		else if(Imm )
		{
			A=Division(TA,A);
		}


}

void AND(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				
				string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A= IntToHex(HexToInt(A)&HexToInt(Mem));
					A=Fill(A);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A= IntToHex(HexToInt(A)&HexToInt(Mem));
					A=Fill(A);

			}
		}
		
	
		else if(Imm )
		{
			TA=SignEX(TA);
			A=IntToHex(HexToInt(A)&HexToInt(TA));
			A=Fill(A);

		}


}
void OR(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				
				string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A= IntToHex(HexToInt(A)|HexToInt(Mem));
					A=Fill(A);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;
					A= IntToHex(HexToInt(A)|HexToInt(Mem));
					A=Fill(A);

			}
		}
		
	
		else if(Imm )
		{
			TA=SignEX(TA);
			A=IntToHex(HexToInt(A)|HexToInt(TA));
			A=Fill(A);

		}


}
void SHIFTL(string instruction)
{
	string inst =instruction;

	int n;
	string s1=inst.substr(2,1);
	string s2=inst.substr(3,1);
	n= HexToInt(s2);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	 string SHLstring=*reg1;
	 SHLstring= HexToBin(SHLstring);
	for (int i=0 ; i<n ;i++)
	{
		string Lbit = SHLstring.substr(0,1);
		SHLstring=SHLstring.erase(0,1);
		SHLstring=SHLstring+Lbit;
	}
	SHLstring= BinToHex(SHLstring);
	*reg1=SHLstring;
}
void SHIFTR(string instruction)
{
	string inst =instruction;

	int n;
	string s1=inst.substr(2,1);
	string s2=inst.substr(3,1);
	n= HexToInt(s2);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	 string SHRstring=*reg1;
	 SHRstring= HexToBin(SHRstring);
	for (int i=0 ; i<n ;i++)
	{
		string Rbit = SHRstring.substr(0,1);
		SHRstring=SHRstring.erase(SHRstring.length()-1,1);
		SHRstring=Rbit+SHRstring;
	}
	SHRstring= BinToHex(SHRstring);
	*reg1=SHRstring;
}

void COMP(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				string Mem ;
				Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;

					Compare(A,Mem);
	 
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
			} 
			else
			{
					string Mem ;
				Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;

				Compare(A,Mem);

			}
		}
		
	
		else if(Imm )
		{
				Compare(A,TA);
		}


}
void COMPR (string inst)  
{
	string instruction =inst;

	string s1=instruction.substr(2,1);
	string s2=instruction.substr(3,1);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	  Compare(*reg1,*reg2);
}
void TIX(string instruction)     
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				string Mem ;
				Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;

					string One="000001";
					X=Addition(X,One);

				Compare(X,Mem);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
			} 
			else
			{
					string Mem ;
				Mem=CodeArray[PcIndex++];
					Mem=CodeArray[PcIndex++]+Mem;
					Mem=CodeArray[PcIndex]+Mem;

					string One="000001";
					X=Addition(X,One);

				Compare(X,Mem);

			}
		}
		
	
		else if(Imm )
		{
			string One="000001";
					X=Addition(X,One);

				Compare(X,TA);

		}


}
void TIXR (string inst)  
{
	string instruction =inst;

	string s1=instruction.substr(2,1);
	string s2=instruction.substr(3,1);
	  string *reg1= &s1;
	 string *reg2=&s2;
	 
	 if (*reg1=="0")
		 reg1=&A;
	 else if (*reg1=="1")
		 reg1=&X;
	 else if (*reg1=="2")
		 reg1=&L;
	 else if (*reg1=="3")
		 reg1=&B;
	 else if (*reg1=="4")
		 reg1=&S;
	 else if (*reg1=="5")
		 reg1=&T;
	 else if (*reg1=="6")
		 reg1=&F;
	 else if (*reg1=="8")
		 reg1=&PC;
	 else if (*reg1=="9")
		 reg1=&SW;

	  
 if (*reg2=="0")
		 reg2=&A;
	 else if (*reg2=="1")
		 reg2=&X;
	 else if (*reg2=="2")
		 reg2=&L;
	 else if (*reg2=="3")
		 reg2=&B;
	 else if (*reg2=="4")
		 reg2=&S;
	 else if (*reg2=="5")
		 reg2=&T;
	 else if (*reg2=="6")
		 reg2=&F;
	 else if (*reg2=="8")
		 reg2=&PC;
	 else if (*reg2=="9")
		 reg2=&SW;

	string One="000001";
	X=Addition(X,One);

	  Compare(X,*reg1);
}
void J(string instruction)
{
	string TA=TAvalue(instruction);

//====================================================

		PC=TA;

}
void JSUB(string instruction)
{
	SubFlag=true;
	string TA=TAvalue(instruction);

//====================================================

			L=PC;
			PC=TA;

}
void RSUB(string instruction)
{
	SubFlag=false;
	PC=L;
}
void JEQ(string instruction)
{
	string TA=TAvalue(instruction);

//====================================================

	
			
			if( CC== 0)
				{
					PC=TA;
				}


}
void JGT(string instruction)
{
	string TA=TAvalue(instruction);

//====================================================

			if( CC== 1)
				{
					PC=TA;
				}


}
void JLT(string instruction)
{
	string TA=TAvalue(instruction);

//====================================================

	
			if( CC== -1)
				{
					PC=TA;
				}


}

void TD(string instruction)
{
	CC=-1;
}
void RD(string instruction)
{
	if (IOindex < IOcounter)
	{
	A = A.substr(0,4);
	A=A+IOMem[IOindex++];
	}

}
void WD(string instruction)
{
	char Ascii=HexToInt(A.substr(4,2));
	IOChanged[IOChangedCounter++]=Ascii;

}

//======================= Floating 

string DblToStr( double nn )
  {
  std::ostringstream result;
  result << nn;
  return result.str();
}
double StrToDbl(string in) 
{    
	float ret_val = 0;    
std::stringstream sstr(in);    
sstr >> ret_val;    
/* (sstr.fail()) 
{ //Check if conversion worked       
	throw std::exception(std::string("Failed conversion for: " + in).c_str());  
}   */ 
return ret_val;
}
string CalculateExponent(int len , string sign) 
{ 	string exponent;
if ( sign == "0" ) 
	{
		if ( len == 1)
		exponent = "00000000001";
	if (len ==2 ) 
		exponent = "00000000010";
	if (len==3 )
		exponent = "00000000011";
	if (len==4 )
		exponent = "00000000100";
	if (len==5 )
		exponent = "00000000101";
	if (len==6 )
		exponent = "00000000110";
	if (len==7 )
		exponent = "00000000111";
	if (len==8)
		exponent = "00000001000";
	}
else
{
	{
		if ( len == 1)
		exponent = "10000000001";
	if (len ==2 ) 
		exponent = "10000000010";
	if (len==3 )
		exponent = "10000000011";
	if (len==4 )
		exponent = "10000000100";
	if (len==5 )
		exponent = "10000000101";
	if (len==6 )
		exponent = "10000000110";
	if (len==7 )
		exponent = "10000000111";
	if (len==8)
		exponent = "10000001000";
	}
}
	return exponent ; 
}
void ReturnF(string Mem, string operation){
				
				cout<<"Mem_HEX= 0x"<<Mem<<"\n";
				cout<<"Mem_BIN= "<<HexToBin(Mem)<<"\n";
				cout<<"\nFreg_HEX= 0x"<<F<<"\n";
				cout<<"Freg_BIN= "<<HexToBin(F)<<"\n";
//------------- Convert Memory to Double -------------
string Membin = HexToBin(Mem);
string Memsign_bit = Membin.substr(0,1);
string Memexponent="0"+Membin.substr(1,11);
string Memfraction=Membin.substr(12,36);
string Memfraction_flipped;// Flip it if 1= 00000001 not 100000000
double Memfractionvalue=0.00;
double Memexponentvalue=0.00;
double Memvalue;
int Memregsign;
				
if ( Memsign_bit =="0" )
	{Memregsign = 1;}
else
	{Memregsign = -1;}
/*--- Flip Memory fraction -----
					for (int i = 35 ; i >= 0 ; i--)
					Memfraction_flipped+=Memfraction.substr(i,1);
				    Memfraction=Memfraction_flipped;
//---- END FLIPPING MEMORY -------*/
	for ( int i = 0 ; i < 36 ; i++)
	{ string bitcheck = Memfraction.substr(i,1);
		if ( bitcheck == "1" )
		{Memfractionvalue+= pow(2.00,(-i-1));}
	}
				int track =HexToInt(BinToHex(Memexponent));
				cout<<"\n+------------------------------------------------------------\n";
				cout<<"|-->MEM ="<<Memregsign<<"* 2^("<<track<<"-1024)*0."<<Memfraction<<"\n";
				cout<<"|       ="<<Memregsign<<"* 2^("<<track-1024<<")*0."<<Memfraction<<"\n"; // Debugging command
				Memexponentvalue = HexToInt(BinToHex(Memexponent))-1024;
				Memvalue = Memregsign * Memfractionvalue * pow(2.00,Memexponentvalue);
				cout<<"|       ="<<Memregsign<<"*"<<pow(2.00,Memexponentvalue)<<"*"<<Memfractionvalue<<"\n";
				cout<<"|       ="<<pow(2.00,Memexponentvalue)<<"*"<<Memregsign*Memfractionvalue<<"\n";
				cout<<"|       ="<<Memvalue<<"\n";
//================================ MEMory converting DONE =====================

double Ffractionvalue=0.00;
double Fexponentvalue=0.00;
double Fvalue;
double debug_fracF=0.00;
string Fbin = HexToBin(F);

string Fsign_bit = Fbin.substr(0,1);
string Fexponent="0"+Fbin.substr(1,11);
string Ffraction=Fbin.substr(12,36);
string Ffraction_flipped;
int Fregsign;
int track_F =HexToInt(BinToHex(Fexponent));

				if ( Fsign_bit =="0" )
					Fregsign = 1;
				else
					Fregsign = -1;
/*-------- FLIPPING F Fraction ---------------
for (int i = 35 ; i >= 0 ; i--)
{Ffraction_flipped+=Ffraction.substr(i,1);}
			Ffraction=Ffraction_flipped;
//------- Done Flipping F Fraction -----------*/
for ( int i = 0 ; i < 36 ; i++)
	{ 
		if ( Ffraction.substr(i,1) == "1" )
			Ffractionvalue+= pow(2.00,(-i-1));
	}
				Fexponentvalue = HexToInt(BinToHex(Fexponent))-1024;
				Fvalue = Fregsign * Ffractionvalue * pow(2.00,Fexponentvalue);
/*for (int i = 1 ; i<=36 ; i++ )
	{if(Ffraction.substr(i-1,1)=="1")
	debug_fracF+=pow(2.00,-i);}*/
				cout<<"|------------------------------------------------------------\n";
				cout<<"|-->Freg ="<<Fregsign<<"* 2^("<<track_F<<"-1024)*0."<<Ffraction<<"\n"; // Debugging command
				cout<<"|        ="<<Fregsign<<"* 2^("<<track_F-1024<<")*0."<<Ffraction<<"\n";
				cout<<"|        ="<<Fregsign<<"*"<<pow(2.00,Fexponentvalue)<<"*"<<Ffractionvalue<<"\n";
				cout<<"|        ="<<Fregsign*Ffractionvalue*pow(2.00,Fexponentvalue)<<"\n";
//===========----------------------------------- Done converting F Value ----------------==========;
				
//=========== Different Functions ==================
double FplusMem;
string totalsign;

               if(operation == "ADDF")
			   {
				   FplusMem= Fvalue + Memvalue;
				cout<<"|---------------------ADDITION----------------------------\n";
				cout<<"|-->Freg+Mem ="<<Fvalue<<"+"<<Memvalue<<endl;
				cout<<"|            ="<<Fvalue+Memvalue<<"\n";
			   }
			   else
				    if ( operation == "SUBF" )
						{
							FplusMem= Fvalue - Memvalue;
				cout<<"|-------------------SUBTRACTION-------------------------------\n";
				cout<<"|-->Freg-Mem ="<<Fvalue<<"-"<<Memvalue<<endl;
				cout<<"|            ="<<Fvalue-Memvalue<<"\n";
						}
					else
						if ( operation == "MULF" )
							{
								FplusMem= Fvalue * Memvalue;
								cout<<"|-------------------------MULTIPLICATION--------------------------\n";
								cout<<"|-->Freg-Mem ="<<Fvalue<<"*"<<Memvalue<<endl;
								cout<<"|            ="<<Fvalue*Memvalue<<"\n";

							}
						else
							if ( operation == "DIVF" )
								{
									FplusMem= Fvalue / Memvalue;
								cout<<"|-------------------DIVISION-----------------------------\n";
								cout<<"|-->Freg-Mem ="<<Fvalue<<" / "<<Memvalue<<endl;
								cout<<"|            ="<<Fvalue/Memvalue<<"\n";
								}
							else
								if ( operation == "COMPF" )
									{   cout<<"|-------------------COMPARE-----------------------------\n";
										if( Fvalue > Memvalue )
										CC = 1;
										else 
											if(Fvalue<Memvalue)
												CC=-1;
											else
												CC=0; // equal
										cout<<"====== CC =>"<<CC<<endl;
									}
if (  operation !="COMPF")
{
if (FplusMem < 0 )
	{
		totalsign="1";
		FplusMem=-1*FplusMem;
	}
else
		totalsign="0";



	//========= PASS 1 ============
if (FplusMem!=0)
{
int FplusMem_int = (int)FplusMem;
string pass1 = HexToBin(IntToHex(FplusMem_int));
pass1=pass1.substr(pass1.find_first_not_of("0"),pass1.length()-pass1.find_first_not_of("0"));
int pass1_exponent; 
string FplusMemfraction="";
string pass1_exponent_bin="";
if ( FplusMem_int !=0 )
	{
		pass1_exponent = pass1.length()-pass1.find_first_not_of("0");
		for ( int i=0; i<pass1_exponent ; i++)
		FplusMemfraction+=pass1.substr(i,1);
		pass1_exponent_bin = HexToBin(IntToHex(pass1_exponent));
	}
				
		if( pass1_exponent_bin.length()>10)
			{
					cout<<"+------------------------------------------------------------+\n"
					    <<"|		<ERROR CODE 0XFLOAT_exponent_OUT_of_RANGE>          |\n"
						<<"|   :+ the sum of the floats you have added have:            |\n"
						<<"|    |-> 1) Exponent Size = "<<pass1_exponent_bin.length()<<"                              |\n"
						<<"|   -- THE VALUE OF THE FLOAT REGISTER WILL BE INCORRECT --  |\n"
						<<"|------------------------------------------------------------|\n"
						<<"| *Press Any key to continue executing with incorrect value* |\n"
						<<"+------------------------------------------------------------|\n";
				system("PAUSE");
			}
for(int i =0 ; pass1_exponent_bin.length()<10;i++)
			pass1_exponent_bin="0"+pass1_exponent_bin;
			if (  FplusMem==0)
				pass1_exponent_bin="0"+pass1_exponent_bin;
			else
				pass1_exponent_bin="1"+pass1_exponent_bin;
					
//===================== PASS 2 =============
double fracFplusMem = FplusMem-FplusMem_int;
int counter; 
if ( FplusMemfraction.length()==0)
	counter = 1;
else
	counter =FplusMemfraction.length();
double debug_fracFplusMem= 0.00;
			for ( int i =counter ; i <36 ; i++ ) 
				{
					if ( fracFplusMem >= pow(2.00,-i-1+counter))
						{
							FplusMemfraction+="1";
						    fracFplusMem-=pow(2.00,-i-1+counter);
						}
					else
							FplusMemfraction+="0";	
					}
	while(FplusMemfraction.length()<36)
			FplusMemfraction+="0";
	for (int i = 1 ; i<=36 ; i++ )
		{
			if(FplusMemfraction.substr(i-1,1)=="1")
				debug_fracFplusMem+=pow(2.00,-i);
		}
if ( totalsign == "0")
		{
			cout<<"|            ="<<"(1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))<<"-1024) *0."<<FplusMemfraction<<"\n";
			cout<<"|            ="<<"(1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))-1024<<") *0."<<FplusMemfraction<<"\n";
			cout<<"|            ="<<"(1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))-1024<<") *"<<debug_fracFplusMem<<"\n";
		}
else
		{
			cout<<"|            ="<<"(-1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))<<"-1024) *0."<<FplusMemfraction<<"\n";
			cout<<"|            ="<<"(-1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))-1024<<") *0."<<FplusMemfraction<<"\n";
			cout<<"|            ="<<"(1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))-1024<<") *"<<debug_fracFplusMem<<"\n";
		}
					
//================= END Of conversion ======
				F = BinToHex(totalsign + pass1_exponent_bin +FplusMemfraction);
					cout<<"|            =0x"<<F<<"\n";
					cout<<"+------------------------------------------------------------\n";

}
else if (FplusMem==0)
	F="000000000000";
}
}
string convert_to_float(string operand)
{
if(operand!="000000")
	{string Ahex = HexToBin(operand);
	int A_int; 
	string neg;
	string pass1;
	if (Ahex.substr(0,1)=="0")
	{
		A_int=HexToInt(operand);
		pass1 = HexToBin(IntToHex(A_int));
	}
	else
	{	int Comp = HexToInt(operand);
	Comp=~Comp+1;

	neg= IntToHex(Comp);
	neg=neg.substr(2,6);
	A_int=0-HexToInt(neg);
	pass1 = HexToBin(IntToHex(HexToInt(neg)));
	}
	string Asign=Ahex.substr(0,1);
	//string Aunsigned_bin = "0"+Ahex.substr(1,23);
 //A_int = HexToInt(BinToHex(Aunsigned_bin));

pass1=pass1.substr(pass1.find_first_not_of("0"),pass1.length()-pass1.find_first_not_of("0"));
int pass1_exponent; 
string Afraction="";
string pass1_exponent_bin="";
double debug_Afraction=0.00;
if ( A_int !=0 )
	{
		pass1_exponent = pass1.length()-pass1.find_first_not_of("0");
		for ( int i=0; i<pass1_exponent ; i++)
		Afraction+=pass1.substr(i,1);
		pass1_exponent_bin = HexToBin(IntToHex(pass1_exponent));
	}
				
		if( pass1_exponent_bin.length()>10)
			{
					cout<<"+------------------------------------------------------------+\n"
					    <<"|		<ERROR CODE 0XFLOAT_exponent_OUT_of_RANGE>          |\n"
						<<"|   :+ the sum of the floats you have added have:            |\n"
						<<"|    |-> 1) Exponent Size = "<<pass1_exponent_bin.length()<<"                              |\n"
						<<"|   -- THE VALUE OF THE FLOAT REGISTER WILL BE INCORRECT --  |\n"
						<<"|------------------------------------------------------------|\n"
						<<"| *Press Any key to continue executing with incorrect value* |\n"
						<<"+------------------------------------------------------------|\n";
				system("PAUSE");
			}
for(int i =0 ; pass1_exponent_bin.length()<10;i++)
			pass1_exponent_bin="0"+pass1_exponent_bin;
			if (  A_int==0)
				pass1_exponent_bin="0"+pass1_exponent_bin;
			else
				pass1_exponent_bin="1"+pass1_exponent_bin;

			while(Afraction.length()<36)
			Afraction+="0";

	for (int i = 1 ; i<=36 ; i++ )
		{
			if(Afraction.substr(i-1,1)=="1")
				debug_Afraction+=pow(2.00,-i);
		}




if ( Asign == "0")
		{
			cout<<"|A           ="<<"(1) *"<<A_int<<"\n";
			cout<<"|            ="<<"(1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))<<"-1024) *0."<<Afraction<<"\n";
			cout<<"|            ="<<"(1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))-1024<<") *0."<<Afraction<<"\n";
			cout<<"|            ="<<"(1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))-1024<<") *"<<debug_Afraction<<"\n";
		}
else
		{
			cout<<"|A           ="<<"(-1) *"<<A_int<<"\n";
			cout<<"|            ="<<"(-1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))<<"-1024) *0."<<Afraction<<"\n";
			cout<<"|            ="<<"(-1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))-1024<<") *0."<<Afraction<<"\n";
			cout<<"|            ="<<"(-1) * 2^("<<HexToInt(BinToHex("0"+pass1_exponent_bin))-1024<<") *"<<debug_Afraction<<"\n";
		}
					
				string convertedF = BinToHex(Asign + pass1_exponent_bin +Afraction);
					cout<<"|            =0x"<<convertedF<<"\n";
					cout<<"+------------------------------------------------------------\n";
					
return convertedF;
}
else
{	string zerof="000000000000";
	return zerof;
}
}
//===================Floating Poing Functions===========
void MULF(string instruction)
{
		string ins=HexToBin(instruction);
	string TA=TAvalue(instruction);
		
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				cout<<" HALT !! PC INDEX = -1"; 
			} 
			else
			{
				string Mem ;
				Mem=CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex];
					
		 ReturnF(Mem,"MULF"); // WOW IT LOOKS SO EASY
			}
		}

		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;
					


		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
				Mem=CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex];
					ReturnF(Mem,"MULF"); 

			}
		}
		
	
		else if(Imm )
		{

			 ReturnF(convert_to_float(TA),"MULF"); 
		}

}
void STF(string instruction)
{
	string TA = TAvalue(instruction);

	
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=F.substr(0,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = F.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = F.substr(4,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = F.substr(6,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+3);
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = F.substr(8,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+4);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=F.substr(10,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+5);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+6;
				
			} 
			else
			{
				string ID,Data;

				Data=CodeArray[PcIndex++]=F.substr(0,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = F.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex++]=F.substr(4,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex++]=F.substr(6,2);
				ID = IntToHex(HexToInt(TA)+3);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex++]=F.substr(8,2);
				ID = IntToHex(HexToInt(TA)+4);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex++]=F.substr(10,2);
				ID = IntToHex(HexToInt(TA)+5);
				Data_Changed_Fun(ID,Data);
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				string ID,Data;
				PcIndex=Counter;

				Data=CodeArray[PcIndex]=F.substr(0,2);
				ID=PcArray[PcIndex++] =TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = F.substr(2,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = F.substr(4,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = F.substr(6,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+3);
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex] = F.substr(8,2);
				ID=PcArray[PcIndex++] = IntToHex(HexToInt(TA)+4);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=F.substr(10,2);
				ID = PcArray[PcIndex]= IntToHex(HexToInt(TA)+5);
				Data_Changed_Fun(ID,Data);

				Counter=Counter+6;
			} 
			else
			{
					string ID,Data;
					
				Data=CodeArray[PcIndex++]=F.substr(0,2);
				ID=TA;
				Data_Changed_Fun(ID,Data);

				Data=CodeArray[PcIndex++] = F.substr(2,2);
				ID= IntToHex(HexToInt(TA)+1);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex++]=F.substr(4,2);
				ID = IntToHex(HexToInt(TA)+2);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex++]=F.substr(6,2);
				ID = IntToHex(HexToInt(TA)+3);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex++]=F.substr(8,2);
				ID = IntToHex(HexToInt(TA)+4);
				Data_Changed_Fun(ID,Data);

				Data = CodeArray[PcIndex]=F.substr(10,2);
				ID = IntToHex(HexToInt(TA)+5);
				Data_Changed_Fun(ID,Data);
			}
		}
}
void SUBF(string instruction)
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				
				string Mem;
				Mem=CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex];
					
				ReturnF(Mem,"SUBF"); // WOW IT LOOKS SO EASY
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;
					


		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
				Mem=CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex];

					ReturnF(A,"SUBF");

			}
		}
		
	
		else if(Imm )
		{
			 ReturnF(convert_to_float(TA),"SUBF"); 

		}
}
void ADDF(string instruction)
{
	string ins=HexToBin(instruction);
	string TA=TAvalue(instruction);
		
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				cout<<" HALT !! PC INDEX = -1"; 
			} 
			else
			{
				string Mem ;
				Mem=CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex];
					
		 ReturnF(Mem,"ADDF"); // WOW IT LOOKS SO EASY
			}
		}

		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;
					

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex];
					ReturnF(Mem,"ADDF"); 

			}
		}
		
	
		else if(Imm )
		{

			ReturnF(convert_to_float(TA),"ADDF"); 
		}

		
}
void COMPF(string instruction)
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				//
			} 
			else
			{
				string Mem ;
				Mem=CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex];

				ReturnF(Mem,"COMPF");
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
			} 
			else
			{
					string Mem ;
				Mem=CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex];

			ReturnF(Mem,"COMPF");

			}
		}
		
	
		else if(Imm )
		{
			
				ReturnF(convert_to_float(TA),"COMPF");

		}

}
void DIVF(string instruction)
{
		string ins=HexToBin(instruction);
	string TA=TAvalue(instruction);
		
		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				cout<<" HALT !! PC INDEX = -1"; 
			} 
			else
			{
				string Mem ;
				Mem=CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex++];
				Mem=Mem+CodeArray[PcIndex];
					
		 ReturnF(Mem,"DIVF"); // WOW IT LOOKS SO EASY
			}
		}

		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;
					

		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				
			} 
			else
			{
					string Mem;
					Mem=CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex++];
					Mem=Mem+CodeArray[PcIndex];
					 ReturnF(Mem,"DIVF"); 

			}
		}
		
	
		else if(Imm )
		{

			 ReturnF(convert_to_float(TA),"DIVF"); 
		}

}
void FIX(string instruction) 
{
double Ffractionvalue=0.00;
double Fexponentvalue=0.00;
double Fvalue;
double debug_fracF=0.00;
string Fbin = HexToBin(F);
string Fsign_bit = Fbin.substr(0,1);
string Fexponent="0"+Fbin.substr(1,11);
string Ffraction=Fbin.substr(12,36);
string Ffraction_flipped;
int Fregsign;
int track_F =HexToInt(BinToHex(Fexponent));

				if ( Fsign_bit =="0" )
					Fregsign = 1;
				else
					Fregsign = -1;
//-------- FLIPPING F Fraction ---------------
/*for (int i = 35 ; i >= 0 ; i--)
{Ffraction_flipped+=Ffraction.substr(i,1);}
			Ffraction=Ffraction_flipped;*/
//------- Done Flipping F Fraction -----------
for ( int i = 0 ; i < 36 ; i++)
	{ 
		if ( Ffraction.substr(i,1) == "1" )
			Ffractionvalue+= pow(2.00,(-i-1));
	}
				Fexponentvalue = HexToInt(BinToHex(Fexponent))-1024;
				Fvalue = Fregsign * Ffractionvalue * pow(2.00,Fexponentvalue);
/*for (int i = 1 ; i<=36 ; i++ )
	{if(Ffraction.substr(i-1,1)=="1")
	debug_fracF+=pow(2.00,-i);}*/

				Fvalue=Fvalue-(Fvalue-(int)Fvalue);
				cout<<"|------------------------------------------------------------\n";
				cout<<"|-->Freg ="<<Fvalue<<endl; // Debugging command
				cout<<"|-->Freg ="<<Fregsign<<"* 2^("<<track_F<<"-1024)*0."<<Ffraction<<"\n"; // Debugging command
				cout<<"|        ="<<Fregsign<<"* 2^("<<track_F-1024<<")*0."<<Ffraction<<"\n";
				cout<<"|        ="<<Fregsign<<"*"<<pow(2.00,Fexponentvalue)<<"*"<<Ffractionvalue<<"\n";
				cout<<"|        ="<<Fregsign*Ffractionvalue*pow(2.00,Fexponentvalue)<<"\n";
				string Fvalue_bin=HexToBin(IntToHex(Fvalue));
				A=BinToHex(Fvalue_bin);
				//
				for(int i =0 ; i<23;i++)
				{ if (Fvalue_bin.length()<23)
					Fvalue_bin= "0"+Fvalue_bin;
				}
				if (Fvalue_bin.length()<24)
				{
				if (Fregsign==1)
					A=BinToHex("0"+Fvalue_bin);
				}
				if(Fvalue_bin.length()>24)
					A=A.substr(2,6); // exception for negative sign to remove FF
				
				  
//===========----------------------------------- Done converting F Value ----------------==========;
}
void FLOAT(string instruction)
{   cout<<"----------FLOAT\n";
	F=convert_to_float(A);
}
void LDF(string instruction)
{
	string TA=TAvalue(instruction);

//====================================================

		if (Simple)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				F="000000000000";
			} 
			else
			{
				
					F=CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex];
			}
		}
		else if(Indirect)
		{
			int PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA)))
				{
					PcIndex=i;
					break;
				}
			}
		string TA2;
		
					TA2=CodeArray[PcIndex++];
					TA2=CodeArray[PcIndex++]+TA2;
					TA2=CodeArray[PcIndex]+TA2;
		PcIndex=-1;
			for( int i=0 ; i<Counter;i++)
			{
				if (HexToInt(PcArray[i]) == (HexToInt(TA2)))
				{
					PcIndex=i;
					break;
				}
			}

			if (PcIndex==-1)
			{
				F="000000000000";
			} 
			else
			{
					F=CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex++];
					F=F+CodeArray[PcIndex];

			}
		}
		
	
		else if(Imm )
		{
			F=convert_to_float(TA);

		}
}
