#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Cho shuffle
#include <random>    // Cho random_device và mt19937
#include <vector>    // Cho biến cards (vector)

using namespace std;

class Card{
private:
    int Rank;
    int suit;
public:

    Card(){}

    Card(int r, int s): Rank(r),suit(s){};

    int GetValue(){
        if(Rank >= 10) return 0;
        return Rank;
    }
};

class Shoe{
private:
    vector<Card> cards;
public:

    Shoe(int num){
        //tương úng vị trí từ lá A - K
        int Rank[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

        // 1: lá bích 2: lá chuồng 3: lá rô 4: lá cơ
        int suit[] = {1,2,3,4};

        for(int i = 0; i < num; i++){
            for(auto &r : Rank){
                for(auto &s : suit){
                    cards.push_back(Card(r,s));
                }
            }
        }
        Shuffle();
    }

    void Shuffle(){
        random_device rd;
        mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);
    }

    Card draw(){
        Card c;
        c = cards.back();
        cards.pop_back();
        return c;
    }

    int getremaincards(){
        return cards.size();
    }
};

class Hand{
public:
    vector<Card> cards;

    void addcard(const Card &c){
        cards.push_back(c);
    }

    int totalpoint(){
        int sum = 0;
        for(auto &c : cards){
            sum += c.GetValue();
        }
        return sum%10;
    }

    void clear(){
        cards.clear();
    }
};

class GamePlay{
private:
    Shoe* shoe;


    //Hàm kiểm tra xem player hay banker thắng: quy ước 1: Player; 2:Tie; 3: Banker;
    int winner(int Pscore, int Bscore){
        if(Pscore > Bscore) return 1;
        if(Bscore > Pscore) return 3;
        return 2;
    }

    bool thirdcard(int Bscore, int Pthirdcard){
        if(Pthirdcard == -1) return Bscore <=5;
        if(Bscore <= 2) return true;
        if(Bscore == 3) return Pthirdcard !=8;
        if(Bscore == 4) return Pthirdcard >=2 && Pthirdcard <=7;
        if(Bscore == 5) return Pthirdcard >=4 && Pthirdcard <=7;
        if(Bscore == 6) return Pthirdcard ==6 || Pthirdcard == 7;
        return false;
    }
public:

    GamePlay(Shoe* s): shoe(s){}

    int play(){
        Hand Banker, Player;

        for(int i = 0; i < 2; i++){
            Player.addcard(shoe->draw());
            Banker.addcard(shoe->draw());
        }

        int Pscore = Player.totalpoint();
        int Bscore = Banker.totalpoint();

        if(Pscore >= 8 || Bscore >= 8){
            return winner(Pscore,Bscore);
        }

        int Pthirdcard = -1;

        if(Pscore <= 5){
            Card thirdcard = shoe->draw();
            Player.addcard(thirdcard);
            Pthirdcard = thirdcard.GetValue();
            Pscore = Player.totalpoint();
        }

        if(thirdcard(Bscore,Pthirdcard)){
            Banker.addcard(shoe->draw());
            Bscore = Banker.totalpoint();
        }
        Player.clear();
        Banker.clear();
        return winner(Pscore,Bscore);
    }
};

int main()
{
    int player =0;
    int tie = 0;
    int banker = 0;

    Shoe shoe(8);
    for(int i =0; i < 1000000; i ++){
        if(shoe.getremaincards() <50){
            shoe = Shoe(8);
        }

        GamePlay game(&shoe);
        int results = game.play();
        switch(results){
            case 1: player++;
                    break;
            case 2: tie++;
                    break;
            case 3: banker++;
                    break;
            default: break;
        }
    }

    int totalGames = player + tie + banker;
    cout << "Tong so van choi: " << totalGames << endl;
    cout << "Player thang: " << (player * 100.0 / totalGames) << "%" << endl;
    cout << "Banker thang: " << (banker * 100.0 / totalGames) << "%" << endl;
    cout << "Hoa (Tie):    " << (tie * 100.0 / totalGames) << "%" << endl;

    return 0;
}
