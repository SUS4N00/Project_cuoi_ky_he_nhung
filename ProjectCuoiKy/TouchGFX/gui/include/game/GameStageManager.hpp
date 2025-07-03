#pragma once
#include <gui/containers/ContainerEntity.hpp>
#include <game/Entity.hpp>

namespace game {
class GameStageManager {
public:
    GameStageManager(ContainerEntity* (&gridRef)[6][6]);
    void clearStageExceptPlayer(); // Xóa hết entity trừ người chơi
    void setupNewStage(int stage); // Thiết lập entity cho màn mới theo stage
    void onPlayerMove(); // Gọi mỗi khi người chơi di chuyển, tăng progress
    int getProgress() const { return progress; }
    int getMaxProgress() const { return max_progress; }
    void setMaxProgress(int val) { max_progress = val; }
    void spawnDoorIfNeeded(); // Nếu đủ progress thì spawn cửa đóng
    void resetProgress(); // Đặt lại progress khi qua màn mới
    void setMaxStage(int val) { max_stage = val; }
    int getMaxStage() const { return max_stage; }
    void setCurrentStage(int val) { current_stage = val; }
    int getCurrentStage() const { return current_stage; }
    bool isGameWin() const { return current_stage > max_stage; }
    void resetStages() { current_stage = 1; progress = 0; }
private:
    ContainerEntity* (&grid)[6][6];
    int progress = 0;
    int max_progress = 20;
    int max_stage = 5; // Số màn tối đa
    int current_stage = 1; // Màn hiện tại
};
} // namespace game
