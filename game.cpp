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
};
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
    static void createQuestions()
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
};
int main()
{

    return 0;
}