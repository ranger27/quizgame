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
        if (getLives())
        {
            lives -= 1;
        }else{
            cout << "Game over...."<< endl;
            cout << "Your score= " << score << endl;
        }
    }
    void display();
    // overloaded functions
    friend istream &operator>>(istream &cin, Player &p);
};
istream &operator>>(istream &cin, Player &p)
{
    cout << "Enter name of the player. " << endl;
    cin >> p.name;
    return cin;
}
void Player::display()
{
    cout << "I am player. My name is: " << name << "\nScore = " << score << "\nLives= " << lives << endl;
}
class Game
{
    Player p;
    Question *currentQuestion;
    static Question *allQuestions;

public:
    Game(Player &player) : p(player)
    {
        cout << "Game is being loaded....." << endl;
        createQuestions();
        currentQuestion = allQuestions;
    }
    ~Game(){
        delete[] allQuestions;
    }
    void nextQuestion(){
        cout << currentQuestion->getQuestion() <<endl;
        currentQuestion = allQuestions+1;
    }
    static void createQuestions();
};
Question* Game::allQuestions = NULL;
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
    game.nextQuestion();
    return 0;
}