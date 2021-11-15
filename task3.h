

//Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод, означающий задание переместиться на
//соседнюю позицию. Эти методы должны запускать классы-исключения OffTheField, если робот должен уйти с сетки, и IllegalCommand,
//если подана неверная команда (направление не находится в нужном диапазоне). Объект исключения должен содержать всю необходимую
//информацию — текущую позицию и направление движения. Написать функцию main, пользующуюся этим классом и перехватывающую все исключения
//от его методов, а также выводящую подробную информацию о всех возникающих ошибках.

#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include<vector>
#include <limits>




class OffTheField : public std::exception
{
private:

public:
    OffTheField(char *msg) : std::exception(msg)
    {
    }
};

class IllegalCommand : public std::exception
{
private:
    int m_sel_pos_x;
    int m_sel_pos_y;
    int m_move_to_x;
    int m_move_to_y;


public:
    IllegalCommand(const char *msg,
        int sel_pos_x , int sel_pos_y, int move_to_x, int move_to_y) : std::exception(msg) , m_sel_pos_x(sel_pos_x),
                        m_sel_pos_y(sel_pos_y), m_move_to_x(move_to_x) , m_move_to_y(move_to_y)
    {	}

     std::string  ErrorMsg() const
    {
        std::ostringstream o;

        o << "the robot cannot move from cell (" << m_sel_pos_x << " : " << m_sel_pos_y <<
            ") to cell ("<< m_move_to_x << " : " << m_move_to_y << ")\n" ;

        std::string a = o.str();

        return a;
    }

};

class Robot
{
private:
    std::vector<std::vector<int>> pole;
    int pos_x;
    int pos_y;
    void StepRobot()
    {
        pole[pos_y][pos_x] = 1;
    }
public:

    Robot()
    {
        for (int i = 0; i < 10; i++)
        {
            pole.push_back(std::vector<int>(10, 0));
        }
        pos_x = 4;
        pos_y = 4;
        StepRobot();
        PrintPole();
    }
    void step(int x, int y)
    {
        int temp_x = x - pos_x;
        int temp_y = y - pos_y;

        if (x > 9 || x < 0 || y > 9 || y < 0)
            throw OffTheField("the robot went out of the field\n");

        if ((temp_x > 1 || temp_x < -1) || (temp_y > 1 || temp_y < -1))
            throw IllegalCommand("Illegal Command\n" ,pos_x,pos_y,x,y);



        pole[pos_y][pos_x] = 0;

        pos_x = x;
        pos_y = y;
        StepRobot();
        PrintPole();
    }
    void PrintPole()
    {
        system("cls");
        std::cout << "Position Robot\n" << pos_x <<"\t"<< pos_y << "\n";

        for (size_t i = 0; i < pole.size(); i++)
        {
            for (size_t j = 0; j < pole[0].size(); j++)
            {
                std::cout << pole[i][j] << " ";
            }
            std::cout << std::endl;
        }

    }

};


void task3()
{
    Robot a;
    int x, y;
    while (true)
    {
        std::cin >> x >> y;

        try
        {
            a.step(x, y);

        }
        catch (const IllegalCommand &ex)
        {
            std::cout << ex.what() << ex.ErrorMsg();
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what();
        }
    }
}
