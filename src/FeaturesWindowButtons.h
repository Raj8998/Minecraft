#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include<string>
#include <FL/fl_draw.H> // For custom drawing

class FeatureButtons : public Fl_Button {
public:
    FeatureButtons(int x, int y, int w, int h, const char* label = nullptr) : Fl_Button(x, y, w, h, label) {}

    // Custom draw function to draw the button with specific appearance
    void draw() override {
        // Draw button background
        fl_draw_box(FL_FLAT_BOX, x(), y(), w(), h(), color());

        // Draw button label
        fl_color(this->labelcolor());
        fl_font(this->labelfont(), this->labelsize());
        fl_draw(label(), x(), y(), w(), h(), align());
    }
};

class AddNewButton: public FeatureButtons{
    public:
        AddNewButton(): FeatureButtons(10, 10, 80, 25, "Add New"){};
};

class ResetButton: public FeatureButtons{
    public:
        ResetButton(): FeatureButtons(10, 40, 80, 25, "Reset"){};
};