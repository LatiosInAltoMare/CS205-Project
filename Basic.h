#include <iostream>
#include <utility>
#include <vector>
#ifndef BASIC_H
#define BASIC_H
using namespace std;

//箱子
class Box{
private:
    int Row;
    int Column;
    vector<vector<bool>> Wall;//真为有墙，假为无墙
public:
    Box():Row(1),Column(1){}
    Box(int R, int C, vector<vector<bool>> Wal):Row(R),Column(C),Wall(std::move(Wal)){}
    int getRow();
    int getColumn();
    vector<vector<bool>> getWall();
    void setRow(int R);
    void setColumn(int C);
    void setWall(int R,int C);//将当前情况反转
};

//关卡（不考虑无穷进入和无穷退出）
class Level{
    //对于普通的关卡，我们将地图视为一个全面封闭的盒子即可

    //对于无限嵌套的关卡，玩家在一个箱子中，不需要有OuterMap
    //嵌套关卡中箱子数也是确定的，有一个主体的箱子，这个主体的箱子就是无限嵌套的箱子
    //也会存在其他箱子，这两种箱子需要分开处理
private:
    //关卡名称
    string Name;
    //主体箱子（只能有一个）
    //如果是普通的关卡将其视为全封闭的盒子，即外部的地图
    Box MainBox;
    //其他箱子
    vector<Box> OtherBox;
    //主体箱子的嵌套情况
    //如果是普通的关卡，那么RecurseOfMainBox就是一个空vector
    //如果是无穷嵌套的关卡，那么如果RecurseOfMainBox被嵌套在了B1箱子里，则RecurseOfMainBox[0]=B1
    vector<Box> RecurseOfMainBox;
    //主题箱子的初始位置
    //如果是普通关卡的话赋为-1
    int MainBoxRow{};
    int MainBoxColumn{};
    //其他箱子的初始信息（同上）
    vector<int> OtherBoxRow;
    vector<int> OtherBoxColumn;
    //玩家的初始信息
    int PlayerRow{};
    int PlayerColumn{};
    //储存终点和游戏信息
    vector<vector<Box>> RecurseOfBoxTerminal;
    vector<int> BoxTerminalRow;
    vector<int> BoxTerminalColumn;
    //储存玩家终点信息
    vector<Box> RecurseOfPlayerTerminal;
    int PlayerTerminalRow{};
    int PlayerTerminalColumn{};
public:
    //构造器
    Level()= default;
    Level(string CurrentName,
    Box CurrentMainBox,
    vector<Box> CurrentOtherBox,
    vector<Box> CurrentRecurseOfMainBox,
    int CurrentMainBoxRow,
    int CurrentMainBoxColumn,
    vector<int> CurrentOtherBoxRow,
    vector<int> CurrentOtherBoxColumn,
    int CurrentPlayerRow,
    int CurrentPlayerColumn,
    vector<vector<Box>> CurrentRecurseOfBoxTerminal,
    vector<int> CurrentBoxTerminalRow,
    vector<int> CurrentBoxTerminalColumn,
    vector<Box> CurrentRecurseOfPlayerTerminal,
    int CurrentPlayerTerminalRow,
    int CurrentPlayerTerminalColumn
    ){
        Name=std::move(CurrentName);
        MainBox=std::move(CurrentMainBox);
        OtherBox=std::move(CurrentOtherBox);
        RecurseOfMainBox=std::move(CurrentRecurseOfMainBox);
        MainBoxRow=CurrentMainBoxRow;
        MainBoxColumn=CurrentMainBoxColumn;
        OtherBoxRow=std::move(CurrentOtherBoxRow);
        OtherBoxColumn=std::move(CurrentOtherBoxColumn);
        PlayerRow=CurrentPlayerRow;
        PlayerColumn=CurrentPlayerColumn;
        RecurseOfBoxTerminal=std::move(CurrentRecurseOfBoxTerminal);
        BoxTerminalRow=std::move(CurrentBoxTerminalRow);
        BoxTerminalColumn=std::move(CurrentBoxTerminalColumn);
        RecurseOfPlayerTerminal=std::move(CurrentRecurseOfPlayerTerminal);
        PlayerTerminalRow=CurrentPlayerTerminalRow;
        PlayerTerminalColumn=CurrentPlayerTerminalColumn;
    }
    //各类getter和setter
    //TODO:补全所有的getter和setter
};

//控制游戏
class GameController{
    //进行游戏控制
private:
    //当前关卡
    Level CurrentLevel;
    //当前的箱子信息
    //主体箱子的嵌套情况
    //如果是普通的关卡，那么RecurseOfMainBox就是一个空vector
    //如果是无穷嵌套的关卡，那么如果RecurseOfMainBox被嵌套在了B1箱子里，则RecurseOfMainBox[0]=B1
    vector<Box> RecurseOfMainBox;
    //主题箱子的位置
    int MainBoxRow{};
    int MainBoxColumn{};
    //其他箱子的信息
    vector<vector<Box>> RecurseOfOtherBox;
    vector<int> OtherBoxRow;
    vector<int> OtherBoxColumn;
    //玩家的信息
    vector<Box> RecurseOfPlayer;
    int PlayerRow{};
    int PlayerColumn{};
    //储存终点和游戏信息
    vector<vector<Box>> RecurseOfBoxTerminal;
    vector<int> BoxTerminalRow;
    vector<int> BoxTerminalColumn;
    std::vector<bool> BoxAtTerminal;
    bool PlayerAtTerminal{};
    bool Win{};
public:
    //构造器
    GameController()= default;
    GameController(
    vector<Box> CurrentRecurseOfMainBox,
    int CurrentMainBoxRow,
    int CurrentMainBoxColumn,
    vector<vector<Box>> CurrentRecurseOfOtherBox,
    vector<int> CurrentOtherBoxRow,
    vector<int> CurrentOtherBoxColumn,
    vector<Box> CurrentRecurseOfPlayer,
    int CurrentPlayerRow,
    int CurrentPlayerColumn,
    vector<vector<Box>> CurrentRecurseOfBoxTerminal,
    vector<int> CurrentBoxTerminalRow,
    vector<int> CurrentBoxTerminalColumn
    ){

        RecurseOfMainBox=std::move(CurrentRecurseOfMainBox);
        MainBoxRow=CurrentMainBoxRow;
        MainBoxColumn=CurrentMainBoxColumn;
        RecurseOfOtherBox=std::move(CurrentRecurseOfOtherBox);
        OtherBoxRow=std::move(CurrentOtherBoxRow);
        OtherBoxColumn=std::move(CurrentOtherBoxColumn);
        RecurseOfPlayer=std::move(CurrentRecurseOfPlayer);
        PlayerRow=CurrentPlayerRow;
        PlayerColumn=CurrentPlayerColumn;
        RecurseOfBoxTerminal=std::move(CurrentRecurseOfBoxTerminal);
        BoxTerminalRow=std::move(CurrentBoxTerminalRow);
        BoxTerminalColumn=std::move(CurrentBoxTerminalColumn);
        Win=false;
        PlayerAtTerminal=false;
    }
    //各类getter和setter
    //TODO:补全所有的getter和setter
    //TODO:补全下面这些函数
    //控制玩家移动（使用W A S D 移动）需要更新数据
    void Move(char Direction);
    //判断玩家是否已经胜利
    bool PlayerWin();
};
#endif
