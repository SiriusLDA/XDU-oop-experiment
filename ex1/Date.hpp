class Date
{
    private:
    int day_difference;
    public:
    int calculate_difference(struct tm Time);
    void init(int y, int m, int d);
    void add_year(int y);
    void add_month(int m);
    void add_day(int d);
};

