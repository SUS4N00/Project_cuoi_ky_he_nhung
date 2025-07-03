#include <gui/screen3_screen/Screen3View.hpp>
#include <gui/common/Global.hpp>

Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

void Screen3View::functionEasy()
{
    Global::gameMode = GAME_EASY;
    application().gotoScreen1ScreenBlockTransition();
}

void Screen3View::functionNormal()
{
    Global::gameMode = GAME_NORMAL;
    application().gotoScreen1ScreenBlockTransition();
}

void Screen3View::functionHard()
{
    Global::gameMode = GAME_HARD;
    application().gotoScreen1ScreenBlockTransition();
}
