#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void promptPokemon(ifstream&);
bool parsePokemon(ifstream&, string, bool);
void calcStats();
void printStats();
void promptStats();
void calcType();

string headStats[6], bodyStats[6];
string type[4];
int result[6];
int total = 0;

string resultType[2];
char cont;

const int TOTALPOKEMON = 721;

string head, body;

int main()
{
    ifstream fin;

    fin.open("pokemon.csv");

    while(true)
    {
        promptPokemon(fin);
        calcStats();
        calcType();
        printStats();

        cout << "Do you want to do another fusion? (Y/N): ";
        cin >> cont;

        if(cont == 'n' || cont == 'N')
            break;
    }
}

void promptStats()
{
    cout << "Enter Body pokemon's stats: " << endl
         << "HP: ";
    cin >> bodyStats[0];
    cout << "ATT: ";
    cin >> bodyStats[1];
    cout << "DEF: ";
    cin >> bodyStats[2];
    cout << "SPA: ";
    cin >> bodyStats[3];
    cout << "SPD: ";
    cin >> bodyStats[4];
    cout << "SPE: ";
    cin >> bodyStats[5];

    cout << "Enter Head pokemon's stats: " << endl
         << "HP: ";
    cin >> headStats[0];
    cout << "ATT: ";
    cin >> headStats[1];
    cout << "DEF: ";
    cin >> headStats[2];
    cout << "SPA: ";
    cin >> headStats[3];
    cout << "SPD: ";
    cin >> headStats[4];
    cout << "SPE: ";
    cin >> headStats[5];
}

void promptPokemon(ifstream &fin)
{
    while(true)
    {
        cout << "Enter Body Pokemon name: ";
        cin >> body;
        if(parsePokemon(fin, body, true))
            break;
        else
            cout << "Cannot find that Pokemon, please try again... (Case Sensitive)" << endl;
    }
    while(true)
    {
        cout << "Enter Head Pokemon name: ";
        cin >> head;
        if(parsePokemon(fin, head, false))
            break;
        else
            cout << "Cannot find that Pokemon, please try again... (Case Sensitive)" << endl;
    }
}

void calcStats()
{
    for(int i = 0; i < 6; i++)
    {
        if(i == 0 || i == 3 || i == 4)
            result[i] = (2 * stoi(headStats[i]) + stoi(bodyStats[i])) / 3;

        else
            result[i] = (2 * stoi(bodyStats[i]) + stoi(headStats[i])) / 3;
    }
}

bool parsePokemon(ifstream &fin, string name, bool isBody) //very shitty linear search algorithm for now
{
    string currName;
    bool found = false;
    fin.seekg(0);
    for(int i = 0; i < TOTALPOKEMON; i++)
    {
        getline(fin, currName, ','); //index number
        getline(fin, currName, ','); //name
        if(name == currName)
        {
            getline(fin, type[0], ','); //type 1
            getline(fin, type[1], ','); //type 2
            getline(fin, currName, ','); //stat total
            for(int j = 0; j < 6; j++)
            {
                if(isBody)
                {
                    type[2] = type[0];
                    type[3] = type[1];
                    getline(fin, bodyStats[j], ',');
                }
                else
                {
                    getline(fin, headStats[j], ',');
                }
            }
            found = true;
            break;
        }
        else    
        {
            getline(fin, currName);//clears line
        }
    }
    return found;
}

void printStats()
{
    cout << endl;
    for(int i = 0; i < 6; i++)
        total += result[i];

    head.erase(0, head.length() / 2);
    body.erase(body.length() / 2, body.length());

    cout << body << head << endl;
    cout << "Type: " << resultType[0];
    if(resultType[1] != "")
        cout << " & " << resultType[1];
    cout << endl << endl;

    cout << "HP: " << result[0] << endl;
    cout << "ATT: " << result[1] << endl;
    cout << "DEF: " << result[2] << endl;
    cout << "SPA: " << result[3] << endl;
    cout << "SPD: " << result[4] << endl;
    cout << "SPE: " << result[5] << endl << endl;

    cout << "Stat Total: " << total << endl << endl;
    total = 0;
}

void calcType()
{
    for(int i = 0; i < 4; i++)
    {
        if(type[1] == "") //if body doesnt have second type, use first type
            resultType[1] = type[0];
        else   // else use the second type of body for second type
            resultType[1] = type[1];

        resultType[0] = type[2]; //primary type is primary type of head

        if(resultType[0] == resultType[1])
        {
            resultType[1] = type[1];
        }

        if(resultType[0] == resultType[1])
        {
            resultType[1] = "";
        }
    }
}