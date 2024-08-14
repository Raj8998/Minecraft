#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include<string>

class Tile: public Fl_Button{
    private:
        int tileValue;
        bool isPressed = false;
    protected:
        Tile(int value, int x, int y, int w, int h): Fl_Button(x, y, w, h){
            this->tileValue = value;
        }
        const char *int2charstar (int v) {
            char *s = new char[2];
            sprintf(s,"%d",v);
            const char *ans = s;
            return ans;
        }
    public:
        int getTileValue(){
            return this->tileValue;
        }
        void setTileValue(int tileValue){
            this->tileValue = tileValue;
        }
        bool getIsPressed(){
            return this->isPressed;
        }
        void setIsPressed(bool isPressed){
            this->isPressed = isPressed;
        }
        virtual void incrValue()=0;
        virtual bool isMine()=0;
        virtual void reveal(std::vector<std::vector<Tile *>> board)=0;
};

class DigitTile: public Tile{
    private:
        void revealSurroundings(int i, int j, vector<vector<Tile *>> board){
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int newRow = i + dx, newCol = j + dy;
                    if (newRow >= 0 && newRow < board.size() && newCol >= 0 && newCol < board[0].size() && !board[newRow][newCol]->getIsPressed() && !board[newRow][newCol]->isMine()) {
                        board[newRow][newCol] -> do_callback();
                    }
                }
            }
        }
    public:
        DigitTile(int x, int y, int w, int h): Tile(0, x, y, w, h){}
        virtual void incrValue() { setTileValue(getTileValue()+1); }
        virtual bool isMine(){ return false; }
        virtual void reveal(std::vector<std::vector<Tile *>> board){
            this->setIsPressed(true);
            this->setonly();
            if(this->getTileValue() == 0){
                revealSurroundings(this->x()/this->w(), this->y()/this->w(), board);
            }else {
                this->label(int2charstar(this->getTileValue()));
            }
            this->deactivate();
        }
};

class MineTile: public Tile{
    public:
        MineTile(int x, int y, int w, int h): Tile(-1, x, y, w, h){}
        virtual void incrValue() {}
        virtual bool isMine(){ return true; }
        virtual void reveal(std::vector<std::vector<Tile *>> board){
            this->setIsPressed(true);
            this->setonly();
            this->selection_color(FL_RED);
            this->label("M");
            this->deactivate();
            for(int i=0;i<board.size();i++){
                for(int j=0; j<board[0].size();j++){
                    if(board[i][j]->isMine()){
                        board[i][j]->setIsPressed(true);
                        board[i][j]->label("M");
                        board[i][j]->selection_color(FL_RED);
                        board[i][j]->setonly();
                        board[i][j]->deactivate();
                    }
                }
            }
        }
};