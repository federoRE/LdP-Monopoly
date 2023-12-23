#ifndef PLAYER_H
#define PLAYER_H

class Player{

    public:
        //Costruttori
        Player(bool bot);

        //Booleani
        bool isLose();
        bool isBot();

        //Getter
        int getPos();
        int getFiorini();
        int getRoll();

        //Setter
        void setPos(int position);
        void setFiorini(int fiorini);
        void setRoll(int roll);

        //Functions
        void incPos(int roll);

    private:
        int position_;
        int roll_;
        int fiorini_;
        bool bot_;
};

#endif