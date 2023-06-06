#include <iostream>
#include <cstring>
using namespace std;

class Game{
protected:
char name[100];
float price;
bool bought;

public:
Game(){}
Game(char *name,float price, bool bought){
    strcpy(this->name,name);
    this->price=price;
    this->bought=bought;
}

friend ostream &operator<<(ostream &os,Game &g){
    os<<"Game: "<<g.name<<", regular price: $"<<g.price;
    if(g.bought){
    os<<", bought on sale"<<endl;
    }
    return os;
}

friend istream &operator>>(istream &is,Game &g){
    is.get();
    is.getline(g.name,100);
    is>>g.price>>g.bought;
    return is;
}

bool operator==(Game &g){
    return strcmp(g.name,name);
}

};

class SubscriptionGame:public Game{
private:
float subscription;
int month,year;
public:
SubscriptionGame(){}
SubscriptionGame(char *name,float price, bool bought,float subscription, int month, int year):Game(name,price,bought){
    this->subscription=subscription;
    this->month=month;
    this->year=year;
}

friend ostream &operator<<(ostream &os,SubscriptionGame &g){
    os<<"Game: "<<g.name<<", regular price: $"<<g.price<<",";
    if(g.bought){
    os<<" bought on sale";
    }
    os<<" monthly fee: $"<<g.subscription<<", purchased: "<<g.month<<"-"<<g.year<<endl;
    return os;
}
friend istream &operator>>(istream &is,SubscriptionGame &g){
    is.get();
    is.getline(g.name,100);
    is>>g.price>>g.bought>>g.subscription>>g.month>>g.year;
    

    return is;
}



};

class User{
private:
char username[100];
  

public:

};



int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}
