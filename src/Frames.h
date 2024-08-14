#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include<algorithm>
#include<vector>
#include<iostream>
#include <time.h>
using namespace std;

#include "MineSweeperButtons.h"
#include "FeaturesWindowButtons.h"

class Frame{
    private:
        int frameSizeHeight, frameSizeWidth;
        Fl_Window* window;
        virtual void initializeButtons()=0;
    public:
        Frame(int h, int w){
            this->frameSizeHeight = h;
            this->frameSizeWidth = w;
        }
        virtual void initialize()=0;
        // virtual int run()=0;
        int getFrameSizeHeight(){
            return this->frameSizeHeight;
        }
        int getFrameSizeWidth(){
            return this->frameSizeWidth;
        }
        Fl_Window* getFrame(){
            return this->window;
        }
    protected:
        void setFrameSizeHeight(int h){
            this->frameSizeHeight = h;
        }
        void setFrameSizeWidth(int w){
            this->frameSizeWidth = w;
        }
        void setFrame(Fl_Window *window){
            this->window = window;
        }
};

class MineSweeperBoardFrame: public Frame{
    private:
        int rowLength, colLength, tileSize, minesCount;
        vector<vector<Tile *>> board;
        virtual void initializeButtons(){
            int tempMineCount = this->minesCount;
            for (int i = 0; i < this->rowLength; ++i){
                vector<Tile *> row;
                for (int j = 0; j < this->colLength; ++j) {
                    Tile *tile;
                    int tileType = (rand()%(rowLength*colLength));
                    if(tempMineCount > 0 && tileType >= 0 && tileType <= (rowLength*colLength)/10){
                        tile = new MineTile(i * tileSize, j * tileSize, tileSize, tileSize);
                        tempMineCount -= 1;
                    } else{
                        tile = new DigitTile(i * tileSize, j * tileSize, tileSize, tileSize);
                    }
                    tile->callback(reveal_tile, this);
                    row.push_back(tile);
                }
                board.push_back(row);
            }
            defineValues();
        }

        void defineValues(){
            for(int i=0; i<this->rowLength; ++i){
                for(int j=0; j<colLength; ++j){
                    if(board[i][j]->isMine()){
                        if(i>0 && j>0) board[i-1][j-1]->incrValue();
                        if(i>0) board[i-1][j]->incrValue();
                        if(i>0 && j+1<this->colLength) board[i-1][j+1]->incrValue();
                        if(j>0) board[i][j-1]->incrValue();
                        if(j+1<this->colLength) board[i][j+1]->incrValue();
                        if(i+1<this->rowLength && j>0) board[i+1][j-1]->incrValue();
                        if(i+1<this->rowLength) board[i+1][j]->incrValue();
                        if(i+1<this->rowLength && j+1<this->colLength) board[i+1][j+1]->incrValue();
                    }
                }
            }
        }
        static void reveal_tile(Fl_Widget* widget, void *data){
            Tile *tile = (Tile *)widget;
            MineSweeperBoardFrame *game = (MineSweeperBoardFrame *)data;
            std::vector<std::vector<Tile *>> board = game->getBoard();
            if(!tile->getIsPressed()){
                tile->reveal(board);
            }
        }
    public:
        MineSweeperBoardFrame(int windowSize, int rowLength, int colLength, int tileSize, int minesCount) : Frame(windowSize, windowSize){
            this->rowLength = rowLength;
            this->colLength = colLength;
            this->tileSize = tileSize;
            this->minesCount = minesCount;
            srand(time(0));
        }

        virtual void initialize(){
            Fl_Window* window = new Fl_Window(this->getFrameSizeHeight(), this->getFrameSizeWidth(), "MineSweeper Game");
            initializeButtons();
            window->end();
            window->show();
            this->setFrame(window);
        }

        vector<vector<Tile *>> getBoard(){
            return this->board;
        }

        
};

class FeaturesFrame: public Frame{
    private:
        FeatureButtons *addNewFrameButton, *resetButton;
        virtual void initializeButtons(){
            this->addNewFrameButton = new AddNewButton();
            this->addNewFrameButton->color(FL_BLUE);
            this->addNewFrameButton->labelcolor(FL_WHITE);

            this->resetButton = new ResetButton();
            this->resetButton->color(FL_BLUE);
            this->resetButton->labelcolor(FL_WHITE);
        }
    public:
        FeaturesFrame(int height, int width): Frame(height, width){};

        virtual void initialize(){
            Fl_Window *window = new Fl_Window(this->getFrameSizeHeight(), this->getFrameSizeWidth(), "Game Features");
            initializeButtons();
            window->end();
            window->show();
            this->setFrame(window);
        }

        FeatureButtons* getAddNewFrameButton(){
            return this->addNewFrameButton;
        }

        FeatureButtons* getResetButton(){
            return this->resetButton;
        }
};