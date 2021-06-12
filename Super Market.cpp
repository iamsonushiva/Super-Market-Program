#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
using namespace std;
class product
{
 int pno;
 char name[50];
 float price,qty,tax,dis;
 public:
	void createproduct()
	{
	 cout<<"\nPlease Enter The Product No. of The Product ";
	 cin>>pno;
	 cout<<"\n\nPlease Enter The Name of The Product ";
	 cin>>name;
	 cout<<"\nPlease Enter The Price of The Product ";
	 cin>>price;
	 cout<<"\nPlease Enter The Discount (%) ";
	 cin>>dis;
	 }

	void showproduct()
	{
	 cout<<"\nThe Product No. of The Product : "<<pno;
	 cout<<"\nThe Name of The Product : ";
	 puts(name);
	 cout<<"\nThe Price of The Product : "<<price;
	 cout<<"\nDiscount : "<<dis;
	 }

  int  retpno()
  {return pno;}

  float retprice()
  {return price;}

  char* retname()
  {return name;}

  int retdis()
  {return dis;}

};
 fstream fp;
 product pr;


void writeproduct()
   {
    fp.open("Shop.dat",ios::out|ios::app);
    pr.createproduct();
    fp.write((char*)&pr,sizeof(product));
    fp.close();
    cout<<"\n\nThe Product Has Been Created ";
    getch();
   }



void display_all()
{

    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 pr.showproduct();
	 cout<<"\n\n====================================\n";
	 getch();
	 }
    fp.close();
    getch();
}


void displaysp(int n)
{
    int flag=0;
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()==n)
		{
		 
		 pr.showproduct();
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\nrecord not exist";
    getch();
}


void modifyproduct()
{
    int no,found=0;
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Product No. of The Product";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(product)) && found==0)
	   {
	    if(pr.retpno()==no)
		   {
		    pr.showproduct();
		    cout<<"\nPlease Enter The New Details of Product"<<endl;
		    pr.createproduct();
		    int s=sizeof(pr);
		    int pos=-1*s;
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(product));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
    getch();
}


void deleteproduct()
   {
    int no;
     system("cls");
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
	{
	 if(pr.retpno()!=no)
		{
		 fp2.write((char*)&pr,sizeof(product));
		 }
	 }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat","Shop.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }

    void menu()
    {
     system("cls");
     fp.open("Shop.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }

     cout<<"\n\n\t\tProduct MENU\n\n";
	  cout<<"====================================================\n";
	  cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	  cout<<"====================================================\n";

      while(fp.read((char*)&pr,sizeof(product)))
	 {
	   cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
     fp.close();
}


   void placeorder()
   {
    int  order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout<<"\n============================";
    cout<<"\n    PLACE YOUR ORDER";
    cout<<"\n============================\n";
    do{
	 cout<<"\n\nEnter The Product No. Of The Product : ";
	 cin>>order_arr[c];
	 cout<<"\nQuantity in number : ";
	 cin>>quan[c];
	 c++;
	 cout<<"\nDo You Want To Order Another Product ? (y/n)";
	 cin>>ch;
    }while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You For Placing The Order";getch();
    system("cls");
      cout<<"\n\n********************************INVOICE************************\n";
      cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
      for(int x=0;x<=c;x++)
	{
		 fp.open("Shop.dat",ios::in);
		 fp.read((char*)&pr,sizeof(product));
		  while(!fp.eof())
			{
			if(pr.retpno()==order_arr[x])
				{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(product));
			}

		 fp.close();
	 }
       cout<<"\n\n\t\t\t\t\t TOTAL = "<<total;
    getch();
    }


void adminmenu()
{
  system("cls");
  char ch2;
  cout<<"\n\n\n\t  ADMIN MENU";
  cout<<"\n\n\t1.CREATE PRODUCT";
  cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
  cout<<"\n\n\t3.QUERY ";
  cout<<"\n\n\t4.MODIFY PRODUCT";
  cout<<"\n\n\t5.DELETE PRODUCT";
  cout<<"\n\n\t6.VIEW PRODUCT MENU";
  cout<<"\n\n\t7.BACK TO MAIN MENU";
  cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
  ch2=getche();
  switch(ch2)
  {
    case '1': system("cls");
	      writeproduct();
	      break;
    case '2': display_all();break;
    case '3':
	       int num;
	       system("cls");
	       cout<<"\n\n\tPlease Enter The Product No. ";
	       cin>>num;
	       displaysp(num);
	       break;
      case '4': modifyproduct();break;
      case '5': deleteproduct();break;
      case '6': menu();
		getch();
      case '7': break;
      default:cout<<"\a";adminmenu();
   }
}




int main()
{
  char ch;

  do
    {
	  system("cls");
	  cout<<setw(40)<<"       ###THE INDIA'S BIGGEST ONLINE SHOPPING MALL###       "<<endl;
	  cout<<setw(40)<<"       ______________________________________________       "<<endl;
	  cout<<setw(40)<<"                        MAIN MENU                           "<<endl;
	  cout<<setw(40)<<"*********************************************************** "<<endl;
	  cout<<setw(40)<<"*                       1. CUSTOMER                       * "<<endl;
	  cout<<setw(40)<<"*                       2. ADMINISTRATOR                  * "<<endl;
	  cout<<setw(40)<<"*                       3. EXIT                           * "<<endl;
	  cout<<setw(40)<<"************************************************************"<<endl;
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1':
		 	system("cls");
			   placeorder();
			   getch();
			   break;
		  case '2': adminmenu();
			    break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='3');
    return 0;
}

