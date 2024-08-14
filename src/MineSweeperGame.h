#include <FL/Fl.H>
#include<vector>
#include "Frames.h"
#include "statics.h"
using namespace std;

class MineSweeperGame{
    private:
        vector<Frame *> gameFrames;
        Frame* featuresFrame;        
    public:
        MineSweeperGame(){
        }

        void initialize(){
            
            Frame* gameFrame = new MineSweeperBoardFrame(DEFAULT_WINDOW_SIZE, DEFAULT_NUMBER_OF_ROWS, DEFAULT_NUMBER_OF_COLS, DEFAULT_TILE_SIZE, DEFAULT_NUMBER_OF_MINES);
            gameFrame->initialize();
            gameFrames.push_back(gameFrame);

            FeaturesFrame* featureFrame = new FeaturesFrame(DEFAULT_FEATURES_WINDOW_SIZE, DEFAULT_FEATURES_WINDOW_SIZE);
            featureFrame->initialize();
            featureFrame->getAddNewFrameButton()->callback(MineSweeperGame::addNewFrame, &gameFrames);
            featureFrame->getResetButton()->callback(MineSweeperGame::resetGame, &gameFrames);
            this->featuresFrame = featureFrame;
        }

        int run(){
            return Fl::run();
        }

        static void addNewFrame(Fl_Widget* widget, void *data){
            std::vector<Frame *>* frames = static_cast<std::vector<Frame *>*>(data);
            Frame *newFrame = new MineSweeperBoardFrame(DEFAULT_WINDOW_SIZE, DEFAULT_NUMBER_OF_ROWS, DEFAULT_NUMBER_OF_COLS, DEFAULT_TILE_SIZE, DEFAULT_NUMBER_OF_MINES);
            newFrame->initialize();
            frames->push_back(newFrame);
        }

        static void resetGame(Fl_Widget* widget, void *data){
            std::vector<Frame *>* frames = static_cast<std::vector<Frame *>*>(data);
            while(frames->size() > 0){
                frames->back()->getFrame()->hide();
                frames->pop_back();
            }
            Frame *newFrame = new MineSweeperBoardFrame(DEFAULT_WINDOW_SIZE, DEFAULT_NUMBER_OF_ROWS, DEFAULT_NUMBER_OF_COLS, DEFAULT_TILE_SIZE, DEFAULT_NUMBER_OF_MINES);
            newFrame->initialize();
            frames->push_back(newFrame);
        }
};