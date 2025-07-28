#include <iostream>
#include <cstdlib>   
#include <ctime>     
#include <string>
using namespace std;


enum enQustionLevel
{
    Easy = 1,
    Medium = 2,
    Hard = 3,
    MixLevel = 4  // ← هذه القيمة جديدة
};
enum enOperationType
{
    Add = 1,
    Sub = 2,
    Mult = 3,
    Div = 4,
    MixOperation = 5
};

struct stGameResults
{
    short RoundsPlayed;
    short RoundsStarted;
    short RoundsWon;
    short RoundsLost;
};
struct stQuestion
{
    int FirstNumber;
    int SecondNumber;
    enOperationType OperationType;
    enQustionLevel QuestionLevel;
    int Answer;
};



int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyRounds()
{
    short HowManyRounds;
    do
    {
        cout << "Enter how many rounds you want to play (1-10): ";
        cin >> HowManyRounds;
    } while (HowManyRounds < 1 || HowManyRounds > 10);
    return HowManyRounds;
}

string Tabs(int Count)
{
    string TabsStr = "";
    for (int i = 0; i < Count; i++)
        TabsStr += "\t";
    return TabsStr;
}

enOperationType ReadOperationType()
{
    short OperationType;
    do
    {
        cout << Tabs(2) << "Select operation type (1-Add, 2-Sub, 3-Mult, 4-Div, 5-Mix): ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);

    return enOperationType(OperationType);

}

enQustionLevel ReadQuestionLevel()
{
    short QuestionLevel;
    do
    {
        cout << Tabs(2) << "Select question level (1-Easy, 2-Medium, 3-Hard , 4-Mix ): ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);


    return enQustionLevel(QuestionLevel);
}

stQuestion LevelRange(stQuestion& Question, enQustionLevel Level)
{
    // معالجة حالة MixLevel أولاً
    enQustionLevel ActualLevel = Level;
    if (ActualLevel == MixLevel)
    {
        ActualLevel = enQustionLevel(RandomNumber(1, 3));
    }

    switch (ActualLevel)
    {
    case Easy:
        Question.FirstNumber = RandomNumber(1, 10);
        Question.SecondNumber = RandomNumber(1, 10);
        break;
    case Medium:
        Question.FirstNumber = RandomNumber(11, 50);
        Question.SecondNumber = RandomNumber(11, 50);
        break;
    case Hard:
        Question.FirstNumber = RandomNumber(51, 100);
        Question.SecondNumber = RandomNumber(51, 100);
        break;
    default:
        // الحالة الافتراضية
        Question.FirstNumber = RandomNumber(1, 10);
        Question.SecondNumber = RandomNumber(1, 10);
        break;
    }

    Question.QuestionLevel = ActualLevel;  // حفظ المستوى الفعلي
    return Question;
}


stQuestion GenerateQuestion(enOperationType OperationType, enQustionLevel QuestionLevel)
{
    stQuestion Question;
    LevelRange(Question, QuestionLevel);

    enOperationType ActualOperationType = OperationType;
    if (ActualOperationType == MixOperation)
    {
        ActualOperationType = enOperationType(RandomNumber(1, 4)); // توليد نوع عشوائي
    }

    switch (ActualOperationType)  // ← استخدم القيمة الجديدة هنا
    {
    case Add:
        Question.Answer = Question.FirstNumber + Question.SecondNumber;
        break;
    case Sub:
        Question.Answer = Question.FirstNumber - Question.SecondNumber;
        break;
    case Mult:
        Question.Answer = Question.FirstNumber * Question.SecondNumber;
        break;
    case Div:
        if (Question.SecondNumber == 0)
            Question.SecondNumber = 1;
        Question.Answer = Question.FirstNumber / Question.SecondNumber;
        break;
    default:
        Question.Answer = 0;
        break;
    }

    Question.OperationType = ActualOperationType;
    return Question;
}


void PrintQuestion(stQuestion Question)
{
    switch (Question.OperationType)
    {
    case Add:
        cout << Tabs(2) << "What is " << Question.FirstNumber << " + " << Question.SecondNumber << "?  \n";
        break;
    case Sub:
        cout << Tabs(2) << "What is " << Question.FirstNumber << " - " << Question.SecondNumber << "?  \n";
        break;
    case Mult:
        cout << Tabs(2) << "What is " << Question.FirstNumber << " * " << Question.SecondNumber << "?  \n";
        break;
    case Div:
        cout << Tabs(2) << "What is " << Question.FirstNumber << " / " << Question.SecondNumber << "?  \n";
        break;
    default:
        break;
    }
}

int ReadAnswer()
{
    int Answer;
    cout << Tabs(2) << "Your answer: ";
    cin >> Answer;
    return Answer;
}

bool CheckAnswer(int UserAnswer, stQuestion& Question)
{
    if (UserAnswer == Question.Answer)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ScreenColor(bool IsCorrect)
{
    if (IsCorrect)
    {
        system("color 2F"); // Green for correct answer
    }
    else
    {
        system("color 4F"); // Red for wrong answer
        cout << "\a"; // Beep sound
    }
}

void PrintResult(bool IsCorrect, stQuestion Question, stGameResults GameResults)
{
    cout << Tabs(2) << "--------------------------------------\n\n " << endl;
    if (IsCorrect)
    {
        cout << Tabs(2) << "Right Answer :-)" << "\n\n " << endl;
        ScreenColor(true);
    }
    else
    {
        cout << Tabs(2) << "Wrong Answer Fail :-( \n" << endl;
        cout << Tabs(2) << "The Right Answer Is : " << Question.Answer << "\n\n" << endl;
        ScreenColor(false);
    }
    cout << Tabs(2) << "--------------------------------------\n\n " << endl;
}

string GetLevelName(enQustionLevel Level)
{
    switch (Level)
    {
    case Easy:
        return "Easy";
    case Medium:
        return "Medium";
    case Hard:
        return "Hard";
    case MixLevel:
        return "Mix";
    default:
        return "Unknown";
    }
}

char GetOperationSymbol(enOperationType OperationType)
{
    switch (OperationType)
    {
    case Add:
        return '+';
    case Sub:
        return '-';
    case Mult:
        return '*';
    case Div:
        return '/';
	case MixOperation:
		return 'M'; // Mix operation
    default:
        return '?'; // Unknown operation
    }
}

void PrintGameResults(stGameResults GameResults, enQustionLevel QuestionLevel, enOperationType OperationType)
{
    cout << "\n\n" << endl;
    cout << Tabs(2) << "------------[Game Results]------------\n\n " << endl;
    cout << Tabs(2) << "Rounds Played: " << GameResults.RoundsPlayed << endl;
    cout << Tabs(2) << "Rounds Won: " << GameResults.RoundsWon << endl;
    cout << Tabs(2) << "Rounds Lost: " << GameResults.RoundsLost << endl;
    cout << Tabs(2) << "Question Level: " << GetLevelName(QuestionLevel) << endl;
    cout << Tabs(2) << "Operation Type: " << GetOperationSymbol(OperationType) << "\n\n" << endl;
    cout << Tabs(2) << "--------------------------------------\n\n " << endl;


}

bool CheckFinalResults(stGameResults GameResults)
{
    if (GameResults.RoundsWon > GameResults.RoundsLost)
    {
        cout << Tabs(4) << "You Win! 😊\n";
        return true;
    }
    else
    {
        cout << Tabs(4) << "You Lose! 😢\n";
        return false;
    }
}

void PlayGame()
{
    stGameResults GameResults{ 0, 0, 0, 0 };
    int HowManyRounds = ReadHowManyRounds();
    GameResults.RoundsStarted = HowManyRounds;
    enQustionLevel QuestionLevel = ReadQuestionLevel();
    enOperationType OperationType = ReadOperationType();
	stQuestion Question;
    for (int i = 1; i <= HowManyRounds; i++)
    {
        GameResults.RoundsPlayed++;
        cout << "\n" << Tabs(4) << "Round [ " << i << " / " << GameResults.RoundsStarted << " ]" << endl;


        Question = GenerateQuestion(OperationType,QuestionLevel );
        PrintQuestion(Question); // ← استخدام القيم الفعلية

        int Answer = ReadAnswer();
        bool IsCorrect = CheckAnswer(Answer, Question);

        if (IsCorrect)
            GameResults.RoundsWon++;
        else
            GameResults.RoundsLost++;

        PrintResult(IsCorrect, Question, GameResults);
    }
	ScreenColor(CheckFinalResults(GameResults));
    PrintGameResults(GameResults, QuestionLevel, OperationType);
}

void ResetConsole()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetConsole();

        PlayGame();
        cout << Tabs(2) << "Do you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}



int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}