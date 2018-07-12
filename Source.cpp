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
	Items *items[20];
	int count;

public:

	ShoppingCart()
	{
		count=0;
		for(int i=0;i<20;i++)
		{
			items[i]=NULL;
		}
	}

	void addItems(Items* item)
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

	void removeItem(Items& item)
	{
		if(count>0)
		{
			for (int i=0;i<count;i++)
			{
				if(items[i]->getItemId()==item.getItemId())
				{
					
					items[i]=items[--count];
					break;
				}
				else
				{
				
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
			return *items[index];
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
	ShoppingCart& getshoppingcart()
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
		stock[2].setitem("os",1,3,300);
		stock[3].setitem("db",1,4,300);
		stockCount=4;
	}

	void enterInStore(Customer& c)
	{
		
		cout<<endl<<endl<<endl<<endl<<"                       WELCOME TO BOOK STORE "<<endl;
		cout<<"                      ______________________"<<endl;
		entertainCustomer(c);

	}

	void storecheckout(ShoppingCart& sc)
	{
		system("cls");
		if(sc.getItemCount()>0)
		{
		int total=0;
		cout<<setw(15)<<"NAME"<<setw(10)<<"price"<<setw(10)<<"item id"<<endl;
		for(int i=0;i<sc.getItemCount();i++)
		{
			if(sc.getitem(i).getItemStoreId()==1)
			{
				cout<<setw(10)<<i+1<<"-"<<sc.getitem(i).getItemName()<<setw(10)<<sc.getitem(i).getItemPrice()<<setw(10)<<sc.getitem(i).getItemId()<<endl;
				total+=sc.getitem(i).getItemPrice();
			}
		}
		cout<<setw(20)<<"total  : "<<total<<endl;
		}
		else
		{
			cout<<"YOU DIDN'T BUY ANYTHING from this store "<<endl;
		}
	}

	void entertainCustomer(Customer& c)
	{	customers=c;
		customersCount++;
		system("cls");
		string selection;
while(selection!="3")
{
		system("cls");
		
		cout<<"            "<<storeName<<endl;
		cout<<"----------------------------------------"<<endl;
		cout<<"         0-show shoes"<<endl;
		cout<<"         1- BUY"<<endl;
		cout<<"         2-checkout"<<endl;
		cout<<"         3- exit "<<endl;

		cin>>selection;
		if(selection=="1")
		{
			
			sellBooks(c);
			continue;
			
		}
		else if(selection=="0")
		{
			showBooks(c);
			system("pause");
		}
		else if(selection=="2")
		{
			storecheckout(c.getshoppingcart());
			int index;
			cout<<"Enter id of the item you want to remove or any key to exit : ";
			cin>>index;
			cin.clear();
			int i=0;
			while(index!=stock[i].getItemId()&&i<stockCount)
			{
				i++;
			}
			if(index==stock[i].getItemId())
			{
				removeFromCart(c.getshoppingcart(),stock[i]);
			}
			else
			{

			}
		}
		else
			exitStore(c);
	}
	}

	void addToCart(ShoppingCart& scart,Items& item)
	{
		scart.addItems(&item);

		
	}

	void removeFromCart(ShoppingCart& scart,Items& item)
	{
		scart.removeItem(item);
	}

	void sellBooks(Customer& c)
	{
		system("cls");
		while(1)
		{
		showBooks(c);
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
				break;
				Sleep(1000);
				system("cls");
			
			}
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
		stock[0].setitem("cod 4",2,201,200);
		stock[1].setitem("gta",2,202,300);
		stock[2].setitem("fifa 16",2,203,300);
		stock[3].setitem("cs",2,204,300);
		stockCount=4;
	}


	void storecheckout(ShoppingCart& sc)
	{
		system("cls");
		if(sc.getItemCount()>0)
		{
		int total=0;
		cout<<setw(15)<<"NAME"<<setw(10)<<"price"<<setw(10)<<"item id"<<endl;
		for(int i=0;i<sc.getItemCount();i++)
		{
			if(sc.getitem(i).getItemStoreId()==2)
			{
				cout<<setw(10)<<i+1<<"-"<<sc.getitem(i).getItemName()<<setw(10)<<sc.getitem(i).getItemPrice()<<setw(10)<<sc.getitem(i).getItemId()<<endl;
				total+=sc.getitem(i).getItemPrice();
			}
		}
		cout<<setw(20)<<"total  : "<<total<<endl;
		}
		else
		{
			cout<<"YOU DIDN'T BUY ANYTHING from this store "<<endl;
		}
	}


	void enterInStore(Customer& c)
	{

		cout<<endl<<endl<<endl<<endl<<"                       WELCOME TO GAME STORE "<<endl;
		cout<<"                      ______________________"<<endl;
		entertainCustomer(c);

	}


	void entertainCustomer(Customer& c)
	{	customers=c;
		customersCount++;
		system("cls");
		string selection;
while(selection!="3")
{
		system("cls");
		
		cout<<"            "<<storeName<<endl;
		cout<<"----------------------------------------"<<endl;
		cout<<"         0-show shoes"<<endl;
		cout<<"         1- BUY"<<endl;
		cout<<"         2-checkout"<<endl;
		cout<<"         3- exit "<<endl;

		cin>>selection;
		if(selection=="1")
		{
			sellgames(c);
			continue;
			
		}
		else if(selection=="0")
		{
			showgames(c);
			system("pause");
		}
		else if(selection=="2")
		{
			storecheckout(c.getshoppingcart());
			int index;
			cout<<"Enter id of the item you want to remove or any key to exit : ";
			cin>>index;
			cin.clear();
			int i=0;
			while(index!=stock[i].getItemId()&&i<stockCount)
			{
				i++;
			}
			if(index==stock[i].getItemId())
			{
				removeFromCart(c.getshoppingcart(),stock[i]);
			}
			else
			{

			}
			system("pause");
		}
		else
			exitStore(c);
	}
	}

	void addToCart(ShoppingCart& scart,Items& item)
	{
		scart.addItems(&item);

		
	}

	void removeFromCart(ShoppingCart& scart,Items& item)
	{
		scart.removeItem(item);
	}

	void sellgames(Customer& c)
	{
		system("cls");
		while(1)
		{
		showgames(c);
		cout<<"ENTER THE ID oF THE game YOU WANT TO Buy or any other key to exit : " ;
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
				break;
				Sleep(1000);
				system("cls");
			
			}
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
	ShoesStore():Store(2,"SHOES Store",3)
	{
		stock[0].setitem("casuals 4",3,301,200);
		stock[1].setitem("school shoes",3,302,300);
		stock[2].setitem("loafers",3,303,300);
		stock[3].setitem("formals",3,304,300);
		stockCount=4;
	}

	void storecheckout(ShoppingCart& sc)
	{
		system("cls");
		if(sc.getItemCount()>0)
		{
		int total=0;
		cout<<setw(15)<<"NAME"<<setw(10)<<"price"<<setw(10)<<"item id"<<endl;
		for(int i=0;i<sc.getItemCount();i++)
		{
			if(sc.getitem(i).getItemStoreId()==3)
			{
				cout<<setw(10)<<i+1<<"-"<<sc.getitem(i).getItemName()<<setw(10)<<sc.getitem(i).getItemPrice()<<setw(10)<<sc.getitem(i).getItemId()<<endl;
				total+=sc.getitem(i).getItemPrice();
			}
		}
		cout<<"total  : "<<total<<endl;
		}
		else
		{
			cout<<"YOU DIDN'T BUY ANYTHING from this store "<<endl;
		}
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
		system("cls");
		string selection;
while(selection!="3")
{
		system("cls");
		
		cout<<"            "<<storeName<<endl;
		cout<<"----------------------------------------"<<endl;
		cout<<"         0-show shoes"<<endl;
		cout<<"         1- BUY"<<endl;
		cout<<"         2-checkout"<<endl;
		cout<<"         3- exit "<<endl;

		cin>>selection;
		if(selection=="1")
		{
			sellshoes(c);
			continue;
			
		}
		else if(selection=="0")
		{
			showshoes(c);
			system("pause");
		}
		else if(selection=="2")
		{
			storecheckout(c.getshoppingcart());
			int index;
			cout<<"Enter id of the item you want to remove or any key to exit : ";
			cin>>index;
			cin.clear();
			int i=0;
			while(index!=stock[i].getItemId()&&i<stockCount)
			{
				i++;
			}
			if(index==stock[i].getItemId())
			{
				removeFromCart(c.getshoppingcart(),stock[i]);
			}
			else
			{

			}
		}
		else
			exitStore(c);
	}
	}
	void addToCart(ShoppingCart& scart,Items& item)
	{
		scart.addItems(&item);

		
	}

	void removeFromCart(ShoppingCart& scart,Items& item)
	{
		scart.removeItem(item);
	}

	void sellshoes(Customer& c)
	{
		system("cls");
		while(1)
		{
		showshoes(c);
		cout<<"ENTER THE ID oF THE shoes YOU WANT TO Buy or any other number to exit : " ;
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
				break;
				system("cls");
			
			}

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
		string sel="";
		welcome();
		//Sleep(3000);
		system("cls");
		while(sel!="4")
		{
			system("cls");
			cout<<endl<<endl<<mallName<<endl;
			cout<<"----------------------------------------------------"<<endl;
			cout<<""<<endl<<endl;
			cout<<"          "<<"1-Enter in store"<<endl;
			cout<<"          "<<"2-Get Shopping cart"<<endl;
			cout<<"          "<<"3-Chekout "<<endl;
			cout<<"          " <<"4-Exit"<<endl;

		
			cin>>sel;
			cin.clear();

			if(sel=="2")
			{
				c.setShoppingCart(provideShoppingcart());
				cout<<"you have got your shopping cart "<<endl;
				Sleep(1000);

			}
			else if(sel=="1")
			{
				while(sel=="1")
				{
				
					system("cls");
					Store* tempst=ShownSelectStores(c);
					c.changeStore(tempst -> getStoreid());
					tempst->enterInStore(c);
					sel="";

				}
			}
			else if(sel=="3")
			{
				system("cls");
				checkout(c.getshoppingcart());
				system("pause");
			}
			else if(sel=="4")
			{
				continue;
			}
			else
			{

				continue;
			}
		

		}
		exit(c);
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
		if(sc.getItemCount()>0)
		{
		int total=0;
		for(int i=0;i<sc.getItemCount();i++)
		{
			cout<<setw(15)<<i+1<<"-"<<sc.getitem(i).getItemName()<<setw(6)<<sc.getitem(i).getItemPrice()<<endl;
			total+=sc.getitem(i).getItemPrice();
		}
		cout<<setw(20)<<"total  : "<<total<<endl;
		}
		else
		{
			cout<<"YOU DIDN'T BUY ANYTHING YET "<<endl;
		}
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
	
	Mall m;
	Store* st=&b;
	m.setStores(st);
	st=&g;
	m.setStores(st);
	st=&str;
	m.setStores(st);
	cout<<"Enter your name : ";
	string name;
	cin>>name;
	c.setCustomer(name,s,1);


	m.Enter(c);
	
	//b.enterInStore(c);
	//cout<<s.getItemCount()<<endl;

	system("pause");
}
