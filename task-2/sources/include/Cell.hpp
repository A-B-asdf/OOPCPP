class Cell {
private:
    bool _is_alive;
public:
    Cell() : _is_alive(false) {}
    Cell(bool alive);
    const bool& IsAlive() const;
    void SetAlive(bool);
    Cell& operator=(const Cell&);
};
