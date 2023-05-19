#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
class category{
    public:
    void start(){
        cout<<"####### REWARD RUSH ######\n\n";
        cout<<"1.login"<<endl;
        cout<<"2.signup\n"<<endl;
    }
    void menu(){
        cout<<"\nMENU\n\n";
        cout<<"1.Categories"<<endl;
        cout<<"2.Cart"<<endl;
        cout<<"3.Your Account"<<endl;
        cout<<"4.Contact us"<<endl;
        cout<<"5.Exit\n"<<endl;
    }
    void showcategory(){
        cout<<"\nCATEGORIES\n\n";
        cout<<"1.Food"<<endl;
        cout<<"2.Pharmacy"<<endl;
        cout<<"3.Electronics"<<endl;
        cout<<"4.Fashion\n"<<endl;
    }
    void contact(){
        cout<<"\nCONTACT DETAILS\n\n";
        cout<<"1.Email id: p3shelp@gmail.com "<<endl;
        cout<<"2.Mobile no. 9988776600:"<<endl;
        cout<<"Feel free to contact us any time\n"<<endl;

    }
    void showfood(){
        cout<<"\nFOOD\n\n";
        cout<<"1.Western"<<endl;
        cout<<"2.North Indian"<<endl;
        cout<<"3.South Indian"<<endl;
        cout<<"4.Chinese"<<endl;
        cout<<"5.Italian\n"<<endl;
    }
    void showmedicine(){
        cout<<"\nMEDICINE\n\n";
        cout<<"1.Homeopathic"<<endl;
        cout<<"2.Ayurvedic"<<endl;
        cout<<"3.Allopathic\n"<<endl;
    }
   void showDigit(){
        cout<<"\nELECTRONICS\n\n";
        cout<<"1.TV"<<endl;
        cout<<"2.Mobile"<<endl;
        cout<<"3.Laptop\n"<<endl;
    }
    void showfashion(){
        cout<<"\nFASHION";
        cout<<"1.UPPER"<<endl;
        cout<<"2.LOWER"<<endl;
        cout<<"3.FOOTWEAR\n"<<endl;
    }
    void recheck(){
        cout<<"\nCART\n\n";
        cout<<"1.Remove Item"<<endl;
        cout<<"2.Clear Cart"<<endl;
        cout<<"3.Checkout Cart"<<endl;
        cout<<"4.Exit Cart\n"<<endl;
    }
    void havewhere(){
        cout<<"\nOPTIONS\n"<<endl;
        cout<<"1.Home Delivery"<<endl;
        cout<<"2.Take Away\n"<<endl;
    }

};

class accounts{
    public:
    string fname;
    string lname;
    string  accountname;
    string password;
    string phone;
    string email;
void signup(){
    cout<<"Enter your firstname : ";
    cin>>fname;
    cout<<"Enter your lastname : ";
    cin>>lname;
    cout<<"Enter Account Name : ";
    cin>>accountname;
    cout<<"Enter Password : ";
    cin>>password;
    do{
        cout<<"Enter your phone number (10 digits only): ";
        cin>>phone;
        if(phone.length() != 10){
            cout<<"Invalid phone number. Please try again."<<endl;
        }
    }while(phone.length() != 10);
    cout<<"Enter your email id : ";
    cin>>email;
    ofstream writer;
    writer.open("Details",ios::out|ios::app);
    writer<<accountname<<" "<<password<<" "<<fname<<" "<<lname<<" "<<phone<<" "<<email<<"\n";
    writer.close();
}


    //nothing prints in login when no account is found in file;
int login() {
    int flag = 0;
    string acc, pass;
    cout << "Enter Account Name : ";
    cin >> acc;
    cout << "Enter Password : ";
    cin >> pass;

    fstream reader;
    reader.open("Details", ios::in);

    string check_accountname, check_password, check_fname, check_lname ,check_email;
    string check_phone;

    while(reader >> check_accountname >> check_password >> check_fname >> check_lname >> check_phone >> check_email ) {
        if (check_accountname == acc) {
            flag = 1;
            if (check_password == pass) {
                cout << "Access Granted.\n" << endl;
                accountname = check_accountname;
                password = check_password;
                fname = check_fname;
                lname = check_lname;
                phone = check_phone;
                email = check_email;
                reader.close();
                return 1;
            } else {
                cout << "Wrong Password\n" << endl;
            }
            break;
        }
    }

    if (flag == 0) {
        cout << "Account not found.\n" << endl;
    }

    reader.close();
    return 0;
}
};

class cart{
public:
    accounts obj;
    string user;
    string product;
    int qty;
    float price;
    int total=0;
    void createFile() {
        ofstream file("cart.txt");
        cout << "File created successfully." << endl;
        file.close();
    }

    void additem(string user, string product, int qty, float price) {
        ofstream myfile;
        myfile.open("cart.txt", std::ios::app);
        if (myfile.is_open()) {
            myfile << user << " " << product << " " << qty << " " << price << endl;
            myfile.close();
            cout << "Data added successfully!\n" << endl;
        } else {
            cout << "Error opening file!\n" << endl;
        }
    }

    void getitem(string user1) {
        total=0;
        ifstream myfile("cart.txt");
        if (myfile.is_open()) {
            while (myfile >> user >> product >> qty >> price) {
                if (user==user1){
                cout <<product <<" "<< qty  <<" " <<price <<endl;
                total+=price*qty;
            }}
            myfile.close();
            cout << "Total: " << total << endl;
        }
        else {
            cout << "Error opening file!\n";
    }
}


void deleteitem(string user, string product, int delete_qty) {
    ifstream infile("cart.txt");
    ofstream outfile("temp.txt");
    if (infile.is_open()) {
        string user1;
        string prod;
        int qty;
        float price;
        int total = 0;
        while (infile >> user1 >> prod >> qty >> price) {
            if (user1 == user && prod == product) {
                if (qty > delete_qty) {
                    outfile << user << " " << prod << " " << (qty - delete_qty) << " " << price << endl;
                    total += price * delete_qty;
                }
                else {
                    total += price * qty;
                    // If the entire product is not being deleted, we skip it
                    continue;
                }
            }
            else {
                outfile << user1 << " " << prod << " " << qty << " " << price << endl;
                total += price * qty;
            }
        }
        infile.close();
        outfile.close();
        remove("cart.txt");
        rename("temp.txt", "cart.txt");
        cout << "Deleted " << delete_qty << " " << product << " from " << user << "'s cart\n";
    }
    else {
        cout << "Error opening file!\n";
    }
}

    void deletecart(string user1) {
        ifstream infile("cart.txt");
        ofstream outfile("temp.txt");
        if (infile.is_open()) {
            string user;
            string product;
            int qty;
            float price;
            int total = 0;
            while (infile >> user >> product >> qty >> price) {
                if (user != user1) {
                    outfile << user << " " << product << " " << qty << " " << price << endl;
                }
            }
        } else {
            cout << "Error opening file!" << endl;
        }
        infile.close();
        outfile.close();
        remove("cart.txt");
        rename("temp.txt", "cart.txt");
        total=0;
    }
int gettotal(string user1) {
        ifstream myfile("cart.txt");
        if (myfile.is_open()) {
            string user;
            string product;
            int qty;
            float price;
            int total=0;
            while (myfile >> user >> product >> qty >> price) {
                if (user==user1){
                total+=price*qty;
            }}
            myfile.close();
            return total;
        }
        else {
            cout << "Error opening file!\n";
        }
    }
};

class coins{
    public:
    vector<string> ref;
    vector<int> refprice;
    coins(){
        ref={"bonanza","FLAT50","WEDNES75","DIS45","FIRST","PIZZA200"};
        refprice={100,50,75,45,50,100};
    }
};



class checkout:public accounts,cart{
    public :
    int paymentmode;
    string cardno;
    string cardname;
    string address;
    int cvv;
    int pin;
    string upi;
    void payment(){
        cout<<"1.Cash On Delivery"<<endl;
        cout<<"2.Debit or Credit Card"<<endl;
        cout<<"3.UPI\n"<<endl;
        cout<<"Enter S.NO :";
        cin>>paymentmode;
        if(paymentmode==1){
            cout<<"Thank you for your Order.\n"<<endl;
        }
        else if(paymentmode==2){
            cout<<"Enter Card No. :";
            cin>>cardno;
            cout<<"Enter Card Name :";
            cin>>cardname;
            cout<<"Enter CVV :";
            cin>>cvv;
            cout<<"Enter PIN :";
            cin>>pin;
            cout<<"Thank you for your Order.]\n"<<endl;
        }
        else if(paymentmode==3){
            cout<<"Enter your UPI id :";
            cin>>upi;
            cout<<"Thank you for your Order.\n"<<endl;
        }
    }


};
class food{
    public:
    string name;
    string cal;
    float price;
}west[5],south[5],north[5],china[5],italy[5];

class pharmacy{
    public:
    string name;
    int qty;
    float price;
}Homo[7],Ayu[7],Allo[7];

class electronics{
    public:
    string name;
    string size;
    float price;

}TV[7],Mobile[5],Laptop[5];

class fashion{
    public:
    string name;
    int qty;
    float price;
}up[5],low[5],foot[5];

int main(){
    west[0].name="Burger";
    west[0].price=250;
    west[1].name="Sandwich";
    west[1].price=200;
    west[2].name="Wrap";
    west[2].price=250;
    west[3].name="Fries";
    west[3].price=100;
    west[4].name="Salad";
    west[4].price=150;
    west[0].cal="180cal";
    west[1].cal="300cal";
    west[2].cal="250cal";
    west[3].cal="240cal";
    west[4].cal="200cal";
    italy[0].name="Pizza";
    italy[0].price=300;
    italy[1].name="Pasta";
    italy[1].price=250;
    italy[2].name="Lasagna";
    italy[2].price=325;
    italy[3].name="Carbonara";
    italy[3].price=299;
    italy[4].name="Polenta";
    italy[4].price=350;
    italy[0].cal="500cal";
    italy[1].cal="250cal";
    italy[2].cal="300cal";
    italy[3].cal="300cal";
    italy[4].cal="250cal";
    china[0].name="Manchurian";
    china[0].price=190;
    china[1].name="Hakka_noodles";
    china[1].price=180;
    china[2].name="Spring_roll";
    china[2].price=150;
    china[3].name="Dumplings";
    china[3].price=120;
    china[4].name="Chilly_Potato";
    china[4].price=150;
    china[0].cal="200cal";
    china[1].cal="230cal";
    china[2].cal="240cal";
    china[3].cal="150cal";
    china[4].cal="300cal";
    north[0].name="Dal_makhani";
    north[0].price=220;
    north[1].name="Panner_Butter_Masala";
    north[1].price=250;
    north[2].name="Butter_Naan";
    north[2].price=80;
    north[3].name="Butter_Chicken";
    north[3].price=250;
    north[4].name="Chole_Bhature";
    north[4].price=180;
    north[0].cal="200cal";
    north[1].cal="400cal";
    north[2].cal="150cal";
    north[3].cal="350cal";
    north[4].cal="450al";
    south[0].name="Rawa_Dosa";
    south[0].price=200;
    south[1].name="Idli";
    south[1].price=120;
    south[2].name="Vada_Sambhar";
    south[2].price=150;
    south[3].name="Uttapam";
    south[3].price=100;
    south[4].name="Upma";
    south[4].price=120;
    south[0].cal="347cal";
    south[1].cal="120cal";
    south[2].cal="200cal";
    south[3].cal="180cal";
    south[4].cal="150cal";

    Homo[0].name="Avenaa";
    Homo[0].price=180;
    Homo[1].name="Spondin";
    Homo[1].price=152;
    Homo[2].name="Alfalfa";
    Homo[2].price=148;
    Homo[3].name="Vulgaris";
    Homo[3].price=165;
    Homo[4].name="Rhus";
    Homo[4].price=178;
    Homo[5].name="Justicia";
    Homo[5].price=180;
    Homo[6].name="Adven_sinus";
    Homo[6].price=135;
    Ayu[0].name="Braham_Bati";
    Ayu[0].price=86;
    Ayu[1].name="Ashwagandha";
    Ayu[1].price=399;
    Ayu[2].name="Shatavar";
    Ayu[2].price=199;
    Ayu[3].name="Musli";
    Ayu[3].price=230;
    Ayu[4].name="Medohar_Vati";
    Ayu[4].price=195;
    Ayu[5].name="Munakka_vati";
    Ayu[5].price=289;
    Ayu[6].name="Kapiva_juice";
    Ayu[6].price=432;
    Ayu[7].name="Alo_juice";
    Ayu[7].price=180;
    Allo[0].name="Azithral";
    Allo[0].price=98;
    Allo[1].name="Ascoril";
    Allo[1].price=118;
    Allo[2].name="Allegra";
    Allo[2].price=218;
    Allo[3].name="Dolo";
    Allo[3].price=30;
    Allo[4].name="Combiflam";
    Allo[4].price=46;
    Allo[5].name="ciplox";
    Allo[5].price=15;
    Allo[6].name="Smuth";
    Allo[6].price=127;
    Allo[7].price=118;

    Laptop[0].name="HP_PAvilion";
    Laptop[0].price=55990;
    Laptop[1].name="Apple_Mackbook_Air";
    Laptop[1].price=82900;
    Laptop[2].name="Ideapad";
    Laptop[2].price=36789;
    Laptop[3].name="Samsung_Book3";
    Laptop[3].price=74990;
    Laptop[4].name="Asus_TUF";
    Laptop[4].price=73989;
    Laptop[0].size="14 inch";
    Laptop[1].size="13.3 inch";
    Laptop[2].size="15.6 inch";
    Laptop[3].size="16 inches";
    Laptop[4].size="15.6 inches";
    Mobile[0].name="Apple_Iphone_13";
    Mobile[0].price=57999;
    Mobile[1].name="Samsung_Galaxy_S21";
    Mobile[1].price=31999;
    Mobile[2].name="One_Plus_11R";
    Mobile[2].price=44000;
    Mobile[3].name="Realme_GT_2";
    Mobile[3].price=24999;
    Mobile[4].name="Motorola_G82";
    Mobile[4].price=21499;
    Mobile[5].name="Redmi_Note_12";
    Mobile[5].price=24999;
    Mobile[0].size="6.06inch";
    Mobile[1].size="6.4inch";
    Mobile[2].size="6.1inch";
    Mobile[3].size="6.6inch";
    Mobile[4].size="6.2inch";
    TV[0].name="Xiaomi_5A";
    TV[0].price=20999;
    TV[0].size="43 inch";
    TV[1].name="Acer_P";
    TV[1].price=16999;
    TV[1].size="32 inch";
    TV[2].name="Samsung_65";
    TV[2].price=81990;
    TV[0].size="65 inch";
    TV[3].name="Toshiba_72";
    TV[3].price=91990;
    TV[0].size="72 inch";
    TV[4].name="Sony_Bravia";
    TV[4].price=78880;
    TV[0].size="72 inch";
    TV[5].name="VU_masterpeice";
    TV[5].price=139000;
    TV[0].size="75 inch";
    TV[6].name="LG_OLED";
    TV[6].price=178900;
    TV[0].size="72 inch";

    foot[0].name="Shoes";
    foot[0].price=3500;
    foot[1].name="Slippers";
    foot[1].price=500;
    foot[2].name="Sandals";
    foot[2].price=1200;
    foot[3].name="Heels";
    foot[3].price=1400;
    foot[4].name="Boots";
    foot[4].price=1699;
    up[0].name="Tshirt";
    up[0].price=600;
    up[1].name="Shirt";
    up[1].price=1100;
    up[2].name="Hoodie";
    up[2].price=1600;
    up[3].name="Jacket";
    up[3].price=3000;
    up[4].name="Vest";
    up[4].price=400;
    low[0].name="Jeans";
    low[0].price=1500;
    low[1].name="Lower";
    low[1].price=900;
    low[2].name="Shorts";
    low[2].price=800;
    low[3].name="Socks";
    low[3].price=200;
    low[4].name="Trouser";
    low[4].price=1100;

    category obj1;
    accounts obj2;
    cart obj3;
    checkout obj4;
    coins coi;
    preultimate:
    obj1.start();
    int choice1,option,option2,option3,option4,option5,qt;
    string fooditem;
    int rqt;
    string userinput;
    string refop;
    string referal;
    cout<<"Enter S.NO :";
    cin>>choice1;
    if(choice1==1){
        if(obj2.login()){
            ultimate:
            obj1.menu();
            cout<<"Enter S.NO :";
            cin>>option;
            switch(option){
            case 1:
            int option1;
            obj1.showcategory();
            cout<<"Enter S.NO :";
            cin>>option1;
            switch(option1){
                case 1:
                obj1.showfood();
                cout<<"Enter S.NO :";
                cin>>option2;
                switch(option2){
                    case 1:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<west[i].name<<"  "<<west[i].price<<" "<<west[i].cal<<endl;
                    }
                    cout<<"Enter S.NO :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,west[option3-1].name,qt,west[option3-1].price);
                    goto ultimate;
                    break;
                    case 2:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<north[i].name<<"  "<<north[i].price<<" "<<north[i].cal<<endl;
                    }
                    cout<<"Enter S.NO :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,north[option3-1].name,qt,north[option3-1].price);
                    goto ultimate;
                    break;
                    case 3:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<south[i].name<<"  "<<south[i].price<<" "<<south[i].cal<<endl;
                    }
                    cout<<"Enter S.NO :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,south[option3-1].name,qt,south[option3-1].price);
                    break;
                    goto ultimate;
                    case 4:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<china[i].name<<"  "<<china[i].price<<" "<<china[i].cal<<endl;
                    }
                    cout<<"Enter S.NO :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,china[option3-1].name,qt,china[option3-1].price);
                    break;
                    goto ultimate;
                    case 5:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<italy[i].name<<"  "<<italy[i].price<<" "<<italy[i].cal<<endl;
                    }
                    cout<<"Enter S.NO :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,italy[option3-1].name,qt,italy[option3-1].price);
                    goto ultimate;
                    break;
                }
                break;
                case 2:
                obj1.showmedicine();
                cout<<"Enter S.NO :";
                cin>>option2;
                switch(option2){
                    case 1:
                    for(int i=0;i<7;i++){
                        cout<<i+1<<"."<<Homo[i].name<<"  "<<Homo[i].price<<endl;
                    }
                    cout<<"Enter S.NO  :";
                    cin>>option3;
                    cout<<"Enter quantity (price is as per 1 leaf of tablets):";
                    cin>>qt;
                    obj3.additem(obj2.accountname,Homo[option3-1].name,qt,Homo[option3-1].price);
                    goto ultimate;
                    break;
                    case 2:
                    for(int i=0;i<7;i++){
                        cout<<i+1<<"."<<Ayu[i].name<<"  "<<Ayu[i].price<<endl;
                    }
                    cout<<"Enter S.NO  :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,Ayu[option3-1].name,qt,Ayu[option3-1].price);
                    goto ultimate;
                    break;
                    case 3:
                    for(int i=0;i<7;i++){
                        cout<<i+1<<"."<<Allo[i].name<<"  "<<Allo[i].price<<endl;
                    }
                    cout<<"Enter S.NO  :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,Allo[option3-1].name,qt,Allo[option3-1].price);
                    goto ultimate;
                    break;
                }
                break;
                case 3:
                obj1.showDigit();
                cout<<"Enter S.NO :";
                cin>>option2;
                switch(option2){
                    case 1:
                    for(int i=0;i<7;i++){
                        cout<<i+1<<"."<<TV[i].name<<"  "<<TV[i].price<<endl;
                    }
                    cout<<"Enter S.NO  :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,TV[option3-1].name,qt,TV[option3-1].price);
                    goto ultimate;
                    break;
                    case 2:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<Mobile[i].name<<"  "<<Mobile[i].price<<endl;
                    }
                    cout<<"Enter S.NO  :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,Mobile[option3-1].name,qt,Mobile[option3-1].price);
                    goto ultimate;
                    break;
                    case 3:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<Laptop[i].name<<"  "<<Laptop[i].price<<endl;
                    }
                    cout<<"Enter S.NO  :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,Laptop[option3-1].name,qt,Laptop[option3-1].price);
                    goto ultimate;
                    break;
                }
                break;
                case 4:
                obj1.showfashion();
                cout<<"Enter S.NO :";
                cin>>option2;
                switch(option2){
                    case 1:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<up[i].name<<"  "<<up[i].price<<endl;
                    }
                    cout<<"Enter S.NO  :";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,up[option3-1].name,qt,up[option3-1].price);
                    goto ultimate;
                    break;
                    case 2:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<low[i].name<<"  "<<low[i].price<<endl;
                    }
                    cout<<"Enter S.NO:";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,low[option3-1].name,qt,low[option3-1].price);
                    goto ultimate;
                    break;
                    case 3:
                    for(int i=0;i<5;i++){
                        cout<<i+1<<"."<<foot[i].name<<"  "<<foot[i].price<<endl;
                    }
                    cout<<"Enter S.NO:";
                    cin>>option3;
                    cout<<"Enter quantity :";
                    cin>>qt;
                    obj3.additem(obj2.accountname,foot[option3-1].name,qt,foot[option3-1].price);
                    goto ultimate;
                    break;
                    case 4:
                    goto ultimate;
                    break;
                }
                break;
            }
            break;
            case 2:
            obj3.getitem(obj2.accountname);
            obj1.recheck();
            if(obj3.total==0){
                goto ultimate;
            }
            cout<<"Enter S.NO :";
            cin>>option4;
            switch(option4){
                case 1:
                //remove item
                cout<<"Enter the name of item to be deleted as shown above :";
                cin>>fooditem;
                cout<<"Enter the quantity to be removed :";
                cin>>rqt;
                obj3.deleteitem(obj2.accountname,fooditem,rqt);
                goto ultimate;
                break;
                case 2:
                cout<<"Are you Sure to Clear your Cart (y/n):";
                cin>>userinput;
                if(userinput=="y" || userinput=="Y"){
                    obj3.deletecart(obj2.accountname);
                }
                else{
                    cout<<"";
                }
                goto ultimate;
                break;
                case 3:
                //checkout cart
                obj1.havewhere();
                cout<<"Enter S.NO :";
                cin>>option5;
                if(option5==1){
                    cout<<"Address :";
                    cin>>obj4.address;
                }
                else{
                    cout<<"";
                }
                cout<<"Do you have a referal code (y/n):";
                cin>>refop;
                if(refop=="y" || refop=="Y"){
                    cout<<"Enter referal code :";
                    cin>>referal;
                    for(int i=0;i<coi.ref.size();i++){
                        if(referal==coi.ref[i]){
                            obj3.total=obj3.total-coi.refprice[i];

                        }
                    }
                }
                else{
                    cout<<"";
                }
                cout<<"Your Total is ="<<obj3.total<<endl;
                obj4.payment();
                obj3.deletecart(obj2.accountname);
                goto ultimate;
                break;
                case 4:
                goto ultimate;
                break;
                default:
                cout<<"Enter Valid input";
                break;
            }

            break;
            case 3:
            //your account
            cout<<"First Name :"<<obj2.fname<<endl;
            cout<<"Last Name :"<<obj2.lname<<endl;
            cout<<"Account Name :"<<obj2.accountname<<endl;
            cout<<"Phone Number :"<<obj2.phone<<endl;
            cout<<"Email id :"<<obj2.fname<<"\n"<<endl;
            goto ultimate;
            break;
            case 4:
            obj1.contact();
            goto ultimate;
            break;
            case 5:
            break;
            default:
            cout<<"Enter Valid Input.\n";
            goto ultimate;
            break;
            }
        }
        else{
            cout<<"";
            goto preultimate;
        }

    }
    else if(choice1==2){
        obj2.signup();
        goto ultimate;
    }
    else{
        cout<<"Invalid entry."<<endl;
        goto preultimate;
    }
    return 0;
}
