class Cell {
private:
    bool _alive;
public:
    Cell() : _alive(false) {}
    Cell(bool alive);
    const bool& IsAlive() const;
    void SetAlive(bool);
    Cell& operator=(const Cell&);
};
