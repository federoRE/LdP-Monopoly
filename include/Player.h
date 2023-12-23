class Player{

    public:
        //Costruttori
        Player();

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
        int position;
        int roll;
        int fiorini;
        bool bot;
};