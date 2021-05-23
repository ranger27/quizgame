#include <iostream>
#include <string>

using namespace std;

class Question
{
    string question;
    int id;
    string answer;
    static int maxNumberOfQuestions;
    static int numberOfQuestions;

public:
    Question() {}
    Question(string q, string ans)
    {
        question = q;
        answer = ans;
        id = numberOfQuestions + 1;
        numberOfQuestions++;
    }
    string getQuestion()
    {
        return question;
    }
    string getAnswer()
    {
        return answer;
    }
    static int getCount()
    {
        return numberOfQuestions;
    }
    static int getMaxCount()
    {
        return maxNumberOfQuestions;
    }
};

int Question::numberOfQuestions = 0;
int Question::maxNumberOfQuestions = 5;

class Player
{
    string name;
    int score = 0;
    int lives = 2;

public:
    Player(){};
    Player(string name)
    {
        this->name = name;
    }
    Player(Player &p)
    {
        name = p.name;
    }
    // getters
    int getScore()
    {
        return score;
    }
    int getLives()
    {
        return lives;
    }
    // setters
    void increaseScore()
    {
        score += 10;
    }
    // decreases the lives or ends the game.
    void decreaseLives()
    {
        lives -= 1;
    }
    bool shouldGameBeRunning()
    {
        if (getLives() + 1) // +1 done because for lives=0 also the if block should run.
        {
            return true;
        }
        else
        {
            cout << "Game over...."<<endl;
            cout << "Your Score= "<< score<<endl;
            return false;
        }
    }
    // overloaded functions
    friend istream &operator>>(istream &cin, Player &p);
};
istream &operator>>(istream &cin, Player &p)
{
    cout << "Enter name of the player. " << endl;
    cin >> p.name;
    return cin;
}

class Game
{

    Question *currentQuestion;
    static Question *allQuestions;

public:
    // FIXME: Should i make the following data member public??
    // the problem will occur if outside world changes the player object to some another player object
    // but the other things like changing data of the same player object cant occur due to private 
    // variables of the player object.
    Player p;
    Game(Player &player) : p(player)
    {
        cout << "Game is being loaded....." << endl;
        createQuestions();
        currentQuestion = allQuestions;
    }
    ~Game()
    {
        delete[] allQuestions;
    }
    void nextQuestion()
    {
        cout << currentQuestion->getQuestion() << endl;
    }
    void checkAnswer(){
        string answer;
        cin >> answer;
        if(answer==currentQuestion->getAnswer()){
            currentQuestion = allQuestions + 1;
            p.increaseScore();
            cout << "Game Status: "<< endl;
            cout << "Score: "<<p.getScore()<<endl;
            cout << "Lives: "<<p.getLives()<<endl;
        }else{
            p.decreaseLives();
            cout << "Game Status: "<< endl;
            cout << "Score: "<<p.getScore()<<endl;
            cout << "Lives: "<<p.getLives()<<endl;
        }
    }
    static void createQuestions();
};
Question *Game::allQuestions = NULL;
void Game::createQuestions()
{
    // local variable
    int numOfQuestionsToBeCreated = Question::getMaxCount();
    // member variable ( //TODO: allocating dynamically so we need destructor )
    allQuestions = new Question[numOfQuestionsToBeCreated];

    // FIXME: try to initialize the following array using numOfQuestionsToBeCreated variable.
    Question ques[5] = {Question("What is the Capital City of Bhutan?", "thimpu"), Question("What is the Capital City of Australia?", "canberra"), Question("What is the Capital City of Germany?", "berlin"), Question("What is the Capital City of England?", "london"), Question("What is the Capital City of Ireland?", "dublin")};

    for (int i = 0; i < numOfQuestionsToBeCreated; i++)
    {
        *(allQuestions + i) = ques[i];
    }
}
int main()
{
    cout << "=======WELCOME TO THE QUIZ GAME=======" << endl;
    Player p1;
    cin >> p1;
    Game game(p1);
    while (game.p.shouldGameBeRunning()){
        game.nextQuestion();
        game.checkAnswer();
    }

    return 0;
}