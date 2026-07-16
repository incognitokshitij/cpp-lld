#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <cstdlib>

using namespace std;

// Observer Pattern
class IObserver {
public:
    virtual void update(string msg) = 0;
    virtual ~IObserver() {}
};

class SnakeAndLadderConsoleNotifier : public IObserver {
public:
    void update(string msg) override {
        cout << "[NOTIFICATION] " << msg << endl;
    }
};

// Dice class
class Dice {
private:
    int faces;

public:
    Dice(int f) {
        faces = f;
    }

    int roll() {
        return (rand() % faces) + 1;
    }
};

// Base class for Snake and Ladder (both have start and end positions)
class BoardEntity {
protected:
    int startPosition;
    int endPosition;

public:
    BoardEntity(int start, int end) {
        startPosition = start;
        endPosition = end;
    }

    int getStart() {
        return startPosition;
    }

    int getEnd() {
        return endPosition;
    }

    virtual void display() = 0;
    virtual string name() = 0;
    virtual ~BoardEntity() {}
};

// Snake class
class Snake : public BoardEntity {
public:
    Snake(int start, int end) : BoardEntity(start, end) {
        if(end >= start) {
            cout << "Invalid snake! End must be less than start." << endl;
        }
    }

    void display() override {
        cout << "Snake: " << startPosition << " -> " << endPosition << endl;
    }

    string name() override {
        return "SNAKE";
    }
};

// Ladder class
class Ladder : public BoardEntity {
public:
    Ladder(int start, int end) : BoardEntity(start, end) {
        if(end <= start) {
            cout << "Invalid ladder! End must be greater than start." << endl;
        }
    }

    void display() override {
        cout << "Ladder: " << startPosition << " -> " << endPosition << endl;
    }

    string name() override {
        return "LADDER";
    }
};

class BoardSetupStrategy;

// Board class
class Board {
private:
    int size;
    map<int, BoardEntity*> boardEntities;

public:
    Board(int s) {
        size = s * s;  // m*m board
    }

    bool canAddEntity(int position) {
        return boardEntities.find(position) == boardEntities.end();
    }

    void addBoardEntity(BoardEntity* boardEntity) {
        if(canAddEntity(boardEntity->getStart())) {
            boardEntities[boardEntity->getStart()] = boardEntity;
        }
    }

    void setupBoard(BoardSetupStrategy* strategy);

    BoardEntity* getEntity(int position) {
        if(boardEntities.find(position) != boardEntities.end()) {
            return boardEntities[position];
        }
        return nullptr;
    }

    int getBoardSize() {
        return size;
    }

    void display() {
        cout << "\n=== Board Configuration ===" << endl;
        cout << "Board Size: " << size << " cells" << endl;

        int snakeCount = 0;
        int ladderCount = 0;
        for(auto& pair : boardEntities) {
            if(pair.second->name() == "SNAKE") snakeCount++;
            else ladderCount++;
        }

        cout << "\nSnakes: " << snakeCount << endl;
        for(auto& pair : boardEntities) {
            if(pair.second->name() == "SNAKE") {
                pair.second->display();
            }
        }

        cout << "\nLadders: " << ladderCount << endl;
        for(auto& pair : boardEntities) {
            if(pair.second->name() == "LADDER") {
                pair.second->display();
            }
        }
        cout << "=========================" << endl;
    }

    ~Board() {
        for(auto& pair : boardEntities) {
            delete pair.second;
        }
    }
};

// Strategy Pattern for Board Setup
class BoardSetupStrategy {
public:
    virtual void setupBoard(Board* board) = 0;
    virtual ~BoardSetupStrategy() {}
};

// Custom Strategy - user provides exact snake/ladder positions
class CustomCountBoardSetupStrategy : public BoardSetupStrategy {
private:
    vector<pair<int, int>> snakePositions;
    vector<pair<int, int>> ladderPositions;

public:
    void addSnakePosition(int start, int end) {
        snakePositions.push_back(make_pair(start, end));
    }

    void addLadderPosition(int start, int end) {
        ladderPositions.push_back(make_pair(start, end));
    }

    void setupBoard(Board* board) override {
        for(auto& pos : snakePositions) {
            if(board->canAddEntity(pos.first)) {
                board->addBoardEntity(new Snake(pos.first, pos.second));
            }
        }

        for(auto& pos : ladderPositions) {
            if(board->canAddEntity(pos.first)) {
                board->addBoardEntity(new Ladder(pos.first, pos.second));
            }
        }
    }
};

// Standard Board Strategy - traditional Snake & Ladder positions
class StandardBoardSetupStrategy : public BoardSetupStrategy {
public:
    void setupBoard(Board* board) override {
        // Only works for 10x10 board (100 cells)
        if(board->getBoardSize() != 100) {
            cout << "Standard setup only works for 10x10 board!" << endl;
            return;
        }

        // Standard snake positions (based on traditional board)
        board->addBoardEntity(new Snake(99, 54));
        board->addBoardEntity(new Snake(95, 75));
        board->addBoardEntity(new Snake(92, 88));
        board->addBoardEntity(new Snake(89, 68));
        board->addBoardEntity(new Snake(74, 53));
        board->addBoardEntity(new Snake(64, 60));
        board->addBoardEntity(new Snake(62, 19));
        board->addBoardEntity(new Snake(49, 11));
        board->addBoardEntity(new Snake(46, 25));
        board->addBoardEntity(new Snake(16, 6));

        // Standard ladder positions
        board->addBoardEntity(new Ladder(2, 38));
        board->addBoardEntity(new Ladder(7, 14));
        board->addBoardEntity(new Ladder(8, 31));
        board->addBoardEntity(new Ladder(15, 26));
        board->addBoardEntity(new Ladder(21, 42));
        board->addBoardEntity(new Ladder(28, 84));
        board->addBoardEntity(new Ladder(36, 44));
        board->addBoardEntity(new Ladder(51, 67));
        board->addBoardEntity(new Ladder(71, 91));
        board->addBoardEntity(new Ladder(78, 98));
        board->addBoardEntity(new Ladder(87, 94));
    }
};

void Board::setupBoard(BoardSetupStrategy* strategy) {
    strategy->setupBoard(this);
}

// Player class
class SnakeAndLadderPlayer {
private:
    int playerId;
    string name;
    int position;

public:
    SnakeAndLadderPlayer(int playerId, string n) {
        this->playerId = playerId;
        name = n;
        position = 0;
    }

    string getName() {
        return name;
    }
    int getPosition() {
        return position;
    }
    void setPosition(int pos) {
        position = pos;
    }
};

// Game class
// Rules (valid move, new position, win condition) are inlined here
// since there was only ever one rule implementation. If a second
// rule set shows up later, pull this back out into a Strategy.
class SnakeAndLadderGame {
private:
    Board* board;
    Dice* dice;
    deque<SnakeAndLadderPlayer*> players;
    vector<IObserver*> observers;
    bool gameOver;

public:
    SnakeAndLadderGame(Board* b, Dice* d) {
        board = b;
        dice = d;
        gameOver = false;
    }

    void addPlayer(SnakeAndLadderPlayer* player) {
        players.push_back(player);
    }

    void addObserver(IObserver* observer) {
        observers.push_back(observer);
    }

    void notify(string msg) {
        for(auto observer : observers) {
            observer->update(msg);
        }
    }

    void displayPlayerPositions() {
        cout << "\n=== Current Positions ===" << endl;
        for(auto player : players) {
            cout << player->getName() << ": " << player->getPosition() << endl;
        }
        cout << "======================" << endl;
    }

    void play() {
        if(players.size() < 2) {
            cout << "Need at least 2 players!" << endl;
            return;
        }

        notify("Game started");
        board->display();

        while(!gameOver) {
            SnakeAndLadderPlayer* currentPlayer = players.front();

            cout << "\n" << currentPlayer->getName() << "'s turn. Press Enter to roll dice...";
            cin.ignore();
            cin.get();

            int diceValue = dice->roll();
            cout << "Rolled: " << diceValue << endl;

            int currentPos = currentPlayer->getPosition();
            int boardSize = board->getBoardSize();

            bool isValidMove = (currentPos + diceValue) <= boardSize;

            if(isValidMove) {
                int intermediatePos = currentPos + diceValue;
                BoardEntity* entity = board->getEntity(intermediatePos);
                int newPos = (entity != nullptr) ? entity->getEnd() : intermediatePos;

                currentPlayer->setPosition(newPos);

                if(entity != nullptr) {
                    bool isSnake = (entity->name() == "SNAKE");
                    if(isSnake) {
                        cout << "Oh no! Snake at " << intermediatePos << "! Going down to " << newPos << endl;
                        notify(currentPlayer->getName() + " encountered snake at " + to_string(intermediatePos) + " now going down to " + to_string(newPos));
                    }
                    else {
                        cout << "Great! Ladder at " << intermediatePos << "! Going up to " << newPos << endl;
                        notify(currentPlayer->getName() + " encountered ladder at " + to_string(intermediatePos) + " now going up to " + to_string(newPos));
                    }
                }

                notify(currentPlayer->getName() + " played. New Position : " + to_string(newPos));
                displayPlayerPositions();

                bool hasWon = (newPos == boardSize);
                if(hasWon) {
                    cout << "\n" << currentPlayer->getName() << " wins!" << endl;
                    notify("Game Ended. Winner is : " + currentPlayer->getName());
                    gameOver = true;
                }
                else {
                    players.pop_front();
                    players.push_back(currentPlayer);
                }
            }
            else {
                cout << "Need exact roll to reach " << boardSize << "!" << endl;
                players.pop_front();
                players.push_back(currentPlayer);
            }
        }
    }

    ~SnakeAndLadderGame() {
        // board and dice ownership stays with whoever created the game,
        // matching how main() cleans them up below.
    }
};

// Factory Pattern
class SnakeAndLadderGameFactory {
public:
    static SnakeAndLadderGame* createStandardGame() {
        Board* board = new Board(10);  // Standard 10x10 board
        BoardSetupStrategy* strategy = new StandardBoardSetupStrategy();
        board->setupBoard(strategy);
        delete strategy;

        Dice* dice = new Dice(6);  // Standard 6-faced dice

        return new SnakeAndLadderGame(board, dice);
    }

    static SnakeAndLadderGame* createCustomGame(int boardSize, BoardSetupStrategy* strategy) {
        Board* board = new Board(boardSize);
        board->setupBoard(strategy);

        Dice* dice = new Dice(6);

        return new SnakeAndLadderGame(board, dice);
    }
};

int main() {
    cout << "=== SNAKE AND LADDER GAME ===" << endl;

    // Short demo: standard 10x10 board, 2 players.
    // (For a custom board, build a CustomCountBoardSetupStrategy and
    // call SnakeAndLadderGameFactory::createCustomGame instead.)
    SnakeAndLadderGame* game = SnakeAndLadderGameFactory::createStandardGame();

    IObserver* notifier = new SnakeAndLadderConsoleNotifier();
    game->addObserver(notifier);

    game->addPlayer(new SnakeAndLadderPlayer(1, "Player1"));
    game->addPlayer(new SnakeAndLadderPlayer(2, "Player2"));

    game->play();

    delete game;
    delete notifier;

    return 0;
}