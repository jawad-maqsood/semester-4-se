#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<Windows.h>

using namespace std;

//------------------------------------------------------------------------------------------------------------
//												items class
//------------------------------------------------------------------------------------------------------------  

class Items                                                                                                  
{
	string itemName;                                                                                            
	int istoreId;
	int itemId;
	float price;
public:
	Items()
	{
		itemName="";
		istoreId=itemId=0;
		price=0;
	}
	Items(string name,int sid,int id,float price)
	{
		setitem(name,sid,id,price);
	}
	void setitem(string name,int sid,int id ,float price)
	{
		if(sid < 0 && id < 0 && price < 0)
		{
			throw 1;
		}
		else
		{

			itemId=id;
			istoreId=sid;
			this->price=price;
			this->itemName=name;
		}
	}

	bool operator==(Items& item)
	{
		if(itemName==item.itemName && this->getItemId()==item.itemId &&this->istoreId==item.istoreId)
		{
			return true;
		}
		else 
			return false;
	}
	string getItemName()
	{
		return itemName;
	}
	int getItemStoreId()
	{
		return istoreId;
	}
	int getItemId()
	{
		return itemId;
	}
	float getItemPrice()
	{
		return price;
	}
};


//------------------------------------------------------------------------------------------------------
//                                      SHOPPING CART
//------------------------------------------------------------------------------------------------------

class ShoppingCart
{
	Items items[30];
	int count;

public:

	ShoppingCart()
	{
		count=0;
	}

	void addItems(Items item)
	{
		if (count<30)
		{
			items[count]=item;
			count++;
		}
		else
		{
			throw 1;
		}
	}

	void removeItem(Items item)
	{
		if(count>0)
		{
			for (int i=0;i<count;i++)
			{
				if(items[i]==item)
				{
					items[i]=items[count];
					count--;
				}
				else
				{
					throw 1;
				}
			}
		}
	}

	int getItemCount()
	{
		return count;
	}

	Items getitem(int index)
	{
		//if(index<count&&index>0)
		//{
			return items[index];
		//}
		//else
		//{
			//throw 1;
		//}
	}
};

//------------------------------------------------------------------------------------------------------------
//                                                  MALL
//------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------
//                                                CUSTOMER
//--------------------------------------------------------------------------------------------------------

class Customer
{
	string name;
	ShoppingCart shoppingcart;
	int storeid;
public:
	Customer()
	{
		name="";
		storeid=0;
	}
	void setCustomer(string name,ShoppingCart cart,int id)
	{
		this->name=name;
		shoppingcart=cart;
		if(id>0)
			storeid=id;
		else 
			id=0;

	}


	void setShoppingCart(ShoppingCart sc)
	{
		shoppingcart=sc;
	}

	void changeStore(int id)
	{
		if(id>=0)
		{
			storeid=id;
		}
		else
			throw 1;
	}
	ShoppingCart getshoppingcart()
	{
		return shoppingcart;
	}
	string getCustomerName()
	{
		return name;
	}
	int getCustomerStoreId()
	{
		return storeid;
	}
};


//-------------------------------------------------------------------------------------------------------------
//                                          SUPER claSS OF STOREs
//-------------------------------------------------------------------------------------------------------------

class Store
{
protected:
	string storeName;
	Items *stock;
	int storeId;
	Customer customers;
	int customersCount;
	int stockCount;

public:
	Store()
	{
		storeName="";
		stock=new Items[5];
		storeId=0;
		stockCount=0;
		customersCount=0;
	}

	Store(int count,string name,int id)
	{
		if(count>5)
		{
			stockCount=count;
			stock=new Items[count];
		}
		else
		{
			stock=new Items[5];
		}
		customersCount=0;
		storeName=name;
		storeId=id;

	}
	virtual string getStoreName()=0;
	virtual int getStoreid()=0;
	virtual void  enterInStore(Customer& c)=0;
	virtual void exitStore(Customer& c)=0;
	virtual int getCustomersCount()=0;
	virtual void addToCart( ShoppingCart& scart,Items& item)=0;
	virtual void removeFromCart(ShoppingCart& scart,Items& item)=0;
	
 
};


//-----------------------------------------------------------------------------------------------------------
//                                     BOOK STORE
//-----------------------------------------------------------------------------------------------------------

class BookStore:public Store
{

public:
	BookStore():Store(2,"Book Store",1)
	{
		stock[0].setitem("se",1,1,200);
		stock[1].setitem("dsa",1,2,300);
		stockCount=2;
	}

	void enterInStore(Customer& c)
	{

		cout<<endl<<endl<<endl<<endl<<"                       WELCOME TO BOOK STORE "<<endl;
		cout<<"                      ______________________"<<endl;
		entertainCustomer(c);

	}


	void entertainCustomer(Customer& c)
	{
		customers=c;
		customersCount++;
		Sleep(1000);
		system("cls");
		showBooks(c);
		Sleep(1000);		
		cout<<"1- BUY"<<endl;
		cout<<"2- exit "<<endl;
		string selection;
		cin>>selection;
		if(selection=="1")
		{
			sellBooks(c);
			while(1)
			{
				cout<<" do you want to buy more books "<<endl;
					cout<<"y- yes            any key to exit"<<endl;
					string sel;
					cin>>sel;
					if(sel=="y")
					{
						showBooks(c);
						sellBooks(c);
					}
					else
					{
						break;
					}
			}
			
		}
		exitStore(c);
	}

	void addToCart(ShoppingCart& scart,Items& item)
	{
		scart.addItems(item);

		
	}

	void removeFromCart(ShoppingCart& scart,Items& item)
	{
		scart.removeItem(item);
	}

	void sellBooks(Customer& c)
	{
		cout<<"ENTER THE ID oF THE BOOK YOU WANT TO Buy : " ;
		int id;
		cin>>id;
		cin.clear();
		int i=0;
		while(id!=stock[i].getItemId()&&i<stockCount)
		{
			i++;
		}
		if(id==stock[i].getItemId())
			{
				ShoppingCart cc=c.getshoppingcart();
				addToCart(cc,stock[i]);
				c.setShoppingCart(cc);
				cout<<" book added to the cart "<<c.getshoppingcart().getItemCount()<<endl;
				Sleep(1000);
				system("cls");
				
			}
			else
			{
				cout<<"Sorry book not found "<<endl;
				Sleep(1000);
				system("cls");
			
			}

	}

	void showBooks(Customer& c)const
	{
		system("cls");
		cout<<"      ------------------------------------------------------------------------"<<endl;
		cout<<"      |				BOOKS AVAILABLE AT STORE                     |"<<endl;					
		cout<<"      ------------------------------------------------------------------------"<<endl;
		cout<<"                                                 MY Cart "<<c.getshoppingcart().getItemCount()<<endl;
		for(int i=0;i<stockCount;i++)
		{
			cout<<"  ==> BOOK   NO   "<<i+1<<endl;
			cout<<"         name  "<<stock[i].getItemName()<<endl;
			cout<<"         ID    "<<stock[i].getItemId()<<endl;
			cout<<"         price "<<stock[i].getItemPrice()<<endl<<endl;
		}

	}

	int getCustomersCount()
	{
		return customersCount;
	}

	void exitStore(Customer& c)
	{
		
		
			system("cls");
			cout<<"Thanks for coming ! ";
			Sleep(1000);
			system("cls");
			customersCount--;
			c.changeStore(0);
			
		

	}

	string getStoreName()
	{
		return storeName;
	}
    int getStoreid()
	{
		return storeId;
	}


};


//-----------------------------------------------------------------------------------------------------------
//                                     GAME STORE
//-----------------------------------------------------------------------------------------------------------

class GameStore:public Store
{

public:
	GameStore():Store(2,"game Store",2)
	{
		stock[0].setitem("cod 4",1,1,200);
		stock[1].setitem("gta",1,2,300);
		stockCount=2;
	}

	void enterInStore(Customer& c)
	{

		cout<<endl<<endl<<endl<<endl<<"                       WELCOME TO GAME STORE "<<endl;
		cout<<"                      ______________________"<<endl;
		entertainCustomer(c);

	}


	void entertainCustomer(Customer& c)
	{
		customers=c;
		customersCount++;
		Sleep(1000);
		system("cls");
		showgames(c);
		Sleep(1000);		
		cout<<"1- BUY"<<endl;
		cout<<"2- exit "<<endl;
		string selection;
		cin>>selection;
		if(selection=="1")
		{
			sellgames(c);
			while(1)
			{
				cout<<" do you want to buy more games "<<endl;
					cout<<"y- yes            any key to exit"<<endl;
					string sel;
					cin>>sel;
					if(sel=="y")
					{
						showgames(c);
						sellgames(c);
					}
					else
					{
						break;
					}
			}
			
		}
		exitStore(c);
	}

	void addToCart(ShoppingCart& scart,Items& item)
	{
		scart.addItems(item);

		
	}

	void removeFromCart(ShoppingCart& scart,Items& item)
	{
		scart.removeItem(item);
	}

	void sellgames(Customer& c)
	{
		cout<<"ENTER THE ID oF THE game YOU WANT TO Buy : " ;
		int id;
		cin>>id;
		cin.clear();
		int i=0;
		while(id!=stock[i].getItemId()&&i<stockCount)
		{
			i++;
		}
		if(id==stock[i].getItemId())
			{
				ShoppingCart cc=c.getshoppingcart();
				addToCart(cc,stock[i]);
				c.setShoppingCart(cc);
				cout<<" game added to the cart "<<endl;
				Sleep(1000);
				system("cls");
				
			}
			else
			{
				cout<<"Sorry game not found "<<endl;
				Sleep(1000);
				system("cls");
			
			}

	}

	void showgames(Customer& c)const
	{
		system("cls");
		cout<<"      ------------------------------------------------------------------------"<<endl;
		cout<<"      |				GAMES AVAILABLE AT STORE                     |"<<endl;					
		cout<<"      ------------------------------------------------------------------------"<<endl;
		cout<<"                                                 MY Cart "<<c.getshoppingcart().getItemCount()<<endl;
		for(int i=0;i<stockCount;i++)
		{
			cout<<"  ==> GAME   NO   "<<i+1<<endl;
			cout<<"         name  "<<stock[i].getItemName()<<endl;
			cout<<"         ID    "<<stock[i].getItemId()<<endl;
			cout<<"         price "<<stock[i].getItemPrice()<<endl<<endl;
		}

	}

	int getCustomersCount()
	{
		return customersCount;
	}

	void exitStore(Customer& c)
	{
		system("cls");
			cout<<"Thanks for coming ! ";
			Sleep(1000);
			system("cls");
			customersCount--;
			c.changeStore(0);
			
		

	}

	string getStoreName()
	{
		return storeName;
	}
    int getStoreid()
	{
		return storeId;
	}


};

//-----------------------------------------------------------------------------------------------------------
//                                     SHOES STORE
//-----------------------------------------------------------------------------------------------------------

class ShoesStore:public Store
{

public:
	ShoesStore():Store(2,"SHOES Store",2)
	{
		stock[0].setitem("cod 4",1,1,200);
		stock[1].setitem("gta",1,2,300);
		stockCount=2;
	}

	void enterInStore(Customer& c)
	{

		cout<<endl<<endl<<endl<<endl<<"                       WELCOME TO SHOES STORE "<<endl;
		cout<<"                      ______________________"<<endl;
		entertainCustomer(c);

	}


	void entertainCustomer(Customer& c)
	{
		customers=c;
		customersCount++;
		Sleep(1000);
		system("cls");
		showshoes(c);
		Sleep(1000);		
		cout<<"1- BUY"<<endl;
		cout<<"2- exit "<<endl;
		string selection;
		cin>>selection;
		if(selection=="1")
		{
			sellshoes(c);
			while(1)
			{
				cout<<" do you want to buy more shoes "<<endl;
					cout<<"y- yes            any key to exit"<<endl;
					string sel;
					cin>>sel;
					if(sel=="y")
					{
						showshoes(c);
						sellshoes(c);
					}
					else
					{
						break;
					}
			}
			
		}
		exitStore(c);
	}

	void addToCart(ShoppingCart& scart,Items& item)
	{
		scart.addItems(item);

		
	}

	void removeFromCart(ShoppingCart& scart,Items& item)
	{
		scart.removeItem(item);
	}

	void sellshoes(Customer& c)
	{
		cout<<"ENTER THE ID oF THE shoes YOU WANT TO Buy : " ;
		int id;
		cin>>id;
		cin.clear();
		int i=0;
		while(id!=stock[i].getItemId()&&i<stockCount)
		{
			i++;
		}
		if(id==stock[i].getItemId())
			{
				ShoppingCart cc=c.getshoppingcart();
				addToCart(cc,stock[i]);
				c.setShoppingCart(cc);
				cout<<" shoes added to the cart "<<endl;
				Sleep(1000);
				system("cls");
				
			}
			else
			{
				cout<<"Sorry shoes not found "<<endl;
				Sleep(1000);
				system("cls");
			
			}

	}

	void showshoes(Customer& c)const
	{
		system("cls");
		cout<<"      ------------------------------------------------------------------------"<<endl;
		cout<<"      |				SHOES AVAILABLE AT STORE                     |"<<endl;					
		cout<<"      ------------------------------------------------------------------------"<<endl;
		cout<<"                                                 MY Cart "<<c.getshoppingcart().getItemCount()<<endl;
		for(int i=0;i<stockCount;i++)
		{
			cout<<"  ==> SHOES   NO   "<<i+1<<endl;
			cout<<"         name  "<<stock[i].getItemName()<<endl;
			cout<<"         ID    "<<stock[i].getItemId()<<endl;
			cout<<"         price "<<stock[i].getItemPrice()<<endl<<endl;
		}

	}

	int getCustomersCount()
	{
		return customersCount;
	}

	void exitStore(Customer& c)
	{
		
			system("cls");
			cout<<"Thanks for coming ! ";
			Sleep(1000);
			system("cls");
			customersCount--;
			c.changeStore(0);
			
		

	}

	string getStoreName()
	{
		return storeName;
	}
    int getStoreid()
	{
		return storeId;
	}


};

//--------------------------------------------------------------------------------------------------
//|                                        M A L L                                        |
//--------------------------------------------------------------------------------------------------

class Mall
{
	string mallName;
	Customer mallCustomers;
	int mallCustCount;
	int mallStCount;
	Store*  stores[20];
public:
	Mall()
	{
		mallName="L E G E N D A R Y      M A L L";
		mallCustCount=0;
		mallStCount=0;
		for(int i=0;i<20;i++)
		{
			stores[i]=NULL;
		}
	}

	void Enter(Customer& c)
	{
		welcome();
		Sleep(3000);
		system("cls");

		cout<<"press 1 to get shopping cart          any key to extit "<<endl;
		string sel;
		cin>>sel;
		cin.clear();

		if(sel=="1")
		{
			c.setShoppingCart(provideShoppingcart());
			while(sel=="1")
			{
				
				system("cls");
				Store* tempst=ShownSelectStores(c);
				c.changeStore(tempst -> getStoreid());
				tempst->enterInStore(c);
				cout<<"Do you want to enter another store ?"<<endl;
				cout<<"press 1 if yes       else any key to exit";
				cin>>sel;

			}
			checkout(c.getshoppingcart());

		}
		else
		{
			exit(c);
		}
		


	}

	Store* ShownSelectStores(Customer& c)
	{
		cout<<"--------------------------------------------------------------------------------------"<<endl;
		cout<<"                        STORES  IN  MALL"<<endl;
		cout<<"--------------------------------------------------------------------------------------"<<endl;
		for(int i=0;i<mallStCount;i++)
		{
			
			cout<<setw(10)<<i+1<<"- "<<stores[i]->getStoreName()<<endl;
		}

		cout<<"Enter the store Number : ";
		int sel;
		cin>>sel;
		cin.clear();

		while(sel < 0 || sel > mallStCount)
		{
			cout<<"invalid ! enter again ";
			cin>>sel;
			cin.clear();
		}

		system("cls");
		return stores[sel-1];
	}

	ShoppingCart provideShoppingcart()
	{
		ShoppingCart st;
		return st;
	}


	void welcome()
	{
		cout<<endl<<endl<<endl<<endl<<endl;
		
		cout<<"                          W E L C O M E  T O      "<<endl;
		cout<<"                    "<<mallName<<endl;
	
	
	}

	void checkout(ShoppingCart& sc)
	{
		system("cls");
		int total=0;
		for(int i=0;i<sc.getItemCount();i++)
		{
			cout<<setw(15)<<i+1<<"-"<<sc.getitem(i).getItemName()<<setw(6)<<sc.getitem(i).getItemPrice()<<endl;
			total+=sc.getitem(i).getItemPrice();
		}
		cout<<setw(20)<<"total  : "<<total<<endl;
	}

	void exit(Customer& c)
	{

	}

	void setStores(Store* str)
	{
		stores[mallStCount]=str;
		mallStCount++;
	}

	int getMallCustomerCount()
	{
		return mallCustCount;
	}
};





void main()
{
	BookStore b;
	GameStore g;
	ShoesStore str;
	Customer c;
	
	ShoppingCart s;
	c.setCustomer("jawad",s,1);
	Items i("abc",1,1,111);
	Mall m;
	Store* st=&b;
	m.setStores(st);
	st=&g;
	m.setStores(st);
	st=&str;
	m.setStores(st);

	m.Enter(c);
	
	//b.enterInStore(c);
	//cout<<s.getItemCount()<<endl;

	system("pause");
}
